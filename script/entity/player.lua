local engine = require("engine")
local Vector2D = require("vector2D")

--- Class Player has all methods for the player of the game
--- @class Player
Player = {
    --- @class Entity
    entity = nil,

    momentum = 0,
    nextCloud = 0,

    components = {
        {
            tag = "physic",
            hitbox = {
                x = 0,
                y = 0,
                w = 64,
                h = 64
            }
        },
        {
            tag = "sprite",
            path = "realexocet.png",
            size = {
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
    local p = setmetatable({}, Player)
    
    p.entity = Entity:new("player")
    
    return p
end

function Player:setPointerEntity(pointer)
    self["_ptr"] = pointer
end

function Player:setUpdateScript(s_update)
    self.components[3]["update"] = s_update
end

function Player:momentumCalculus()
    if engine.getKey(SDL.SDLK_S) then
        self.momentum = self.momentum + 1
        
        local vel = self.entity:getVelocity() + Vector2D:new(0, self.momentum )
        self.entity:setVelocity(vel)
    else
        if self.momentum > 0 then
            local vel = self.entity:getVelocity() - Vector2D:new(0, self.momentum * 0.5)
            self.entity:setVelocity(vel)

            self.momentum = self.momentum - 1
        else
            local vel = self.entity:getVelocity() + Vector2D:new(0, 1.2)
            self.entity:setVelocity(vel)
        end
    end
end

function Player:update()
    engine.centerOnEntity(self.entity)

    self.entity:fitSizeWithHitbox()

    self:momentumCalculus()

    if self.nextCloud <= 0 then
        local cpos = Vector2D:new(
            engine.getWinWidth(),
            math.random(engine.getCameraPosition().y, engine.getCameraPosition().y + engine.getWinHeight())
        )

        local c = Cloud:new(cpos)
        
        c.components[2]["update"] = function ()
            c:update()
        end

        
        engine.addEntity(c)
        
        self.nextCloud = math.random(10, 50)
    end
    self.nextCloud = self.nextCloud - 1
end

function Player:__tostring()
    return tostring(self.entity.tag)
end

return Player