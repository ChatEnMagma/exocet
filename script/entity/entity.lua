local engine = require("engine")
local Vector2D = require("vector2D")
local string = require("string")

--- Class Entity has essential functions
--- @class Entity
Entity = { 
    --- The C pointer from Entity
    --- @private
    --- @type integer
    _ptr = 0,

    --- The tag of the entity, i.e. the name of entity
    --- @type string
    tag = "gen-entity"
}

Entity.__index = Entity

function Entity:__tostring()
    return "Entity: " .. string.format("%x",  self._ptr)
end

--- @param tag string|nil
function Entity:new(tag)
    local e = setmetatable({}, Entity)
    
    if tag ~= nil then
        e.tag = tag
    end

    return e
end

--- Get all entities are collide
--- @return table
function Entity:getCollideEntities()
    return Entity.cGetCollideEntities(self._ptr)
end

--- Check if the entity is well collide
--- @param entity any
--- @return boolean
function Entity:getCollideEntity(entity)
    return Entity.cGetCollideEntity(self._ptr, entity.entity._ptr)
end

--- Kill the entity
function Entity:destroy()
    self.cDestroy(self._ptr)
end

--- Set the texture to the Entity. You must add SpriteComponent
--- @param path string
function Entity:setTexture(path)
    engine.cSetTexture(self._ptr, path);
end

--- Fit the size of the sprite with hitbox
function Entity:fitSizeWithHitbox()
    self.cFitSizeWithHitbox(self._ptr)
end

--- Function set the pointer of CEntity
--- @private
--- @param pointer interger The C pointer from Entity
function Entity:setEntity(pointer)
    self._ptr = pointer
end

--- Function returns the position of the entity
--- @return Vector2D
function Entity:getPosition()
    local x, y = self.cGetPosition(self._ptr) -- call CFunction
    return Vector2D:new(x, y)
end

--- Function returns the velocity of the entity
--- @return Vector2D
function Entity:getVelocity()
    local x, y = self.cGetVelocity(self._ptr) -- call CFunction
    return Vector2D:new(x, y)
end

--- Set the position of the entity
--- @param vec Vector2D The new position in Vector2D with integer
function Entity:setPosition(vec)
    self.cSetPosition(self._ptr, vec.x, vec.y) -- call CFunction
end

--- Set the velocity of the entity
--- @param vec Vector2D The new velocity in Vector2D with number
function Entity:setVelocity(vec)
    self.cSetVelocity(self._ptr, vec.x, vec.y) -- call CFunction
end

return Entity