local engine = require("engine")
local Vector2D = require("vector2D")

-- Class Entity
--- @class Entity
Entity = { 
    --- @private
    --- @type number
    _ptr = 0,
    tag = "genericEntity",
}
Entity.__index = Entity

function Entity:new()
    local e = {}
    setmetatable(e, Entity)
    return e
end

function Entity:setTag(tag)
    self.tag = tag
end

-- Function set the pointer of CEntity
function Entity:setEntity(pointer)
    self._ptr = pointer
end

-- Function returns the position of the entity
function Entity:getPosition()
    local x, y = self.cGetPosition(self._ptr) -- call CFunction
    return Vector2D:new(x, y)
end

-- Function returns the velocity of the entity
function Entity:getVelocity()
    local x, y = self.cGetVelocity(self._ptr) -- call CFunction
    return Vector2D:new(x, y)
end

--- @param x number
--- @param y number
-- Set the position of the entity
function Entity:setPosition(x, y)
    self.cSetPosition(self._ptr, x, y) -- call CFunction
end

-- Class Player

-- Class Player, all method for the player of the game
Player = {
    entity = Entity:new(),
    momentum = 0,

    tag = "player",

    components = {
        {
            tag = "player",
            hitbox = {
                 x = 0,
                y = 0,
                w = 64,
                h = 64
            }
        },
        {
            tag = "script",
            update = nil
        }
    }
}
Player.__index = Player

function Player:new()
    local p = {}

    setmetatable(p, Player)
    p.entity:setTag("player")

    return p
end

function Player:setPointerEntity(pointer)
    self["_ptr"] = pointer
end

function Player:setUpdateScript(s_update)
    self.components[2]["update"] = s_update
end

function Player:update()
    print(engine.getKey(117), self.entity["_ptr"])
    print(self.entity:getPosition())
end

function Player:__tostring()
    return tostring(self.entity.tag)
end

--- @meta
entities = {
    Player = Player
}

return entities