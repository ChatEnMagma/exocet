local os = require("os")

local engine = require("engine")
local Vector2D = require("vector2D")

--- Class Player has all methods for the player of the game
--- @class Player
Player = {
    --- @class Entity
    entity = nil,

    momentum = 0,
    nextCloud = 0,
    nextDescOxy = 0,
    nextOxy = 0,
    oxygen = 100,
    dieTime=0,
    gameover = false,
    beginGame = os.time(),

    components = {
        PhysicComponent:new({ x = 0, y = 0, w = 64, h = 64 }, Vector2D:new(0, 100)),
        AnimationComponent:new(10, { w = 64, h = 64 },  {
            { x = 32 * 0, y = 0, w = 32, h = 32 },
            { x = 32 * 0, y = 0, w = 32, h = 32 },
            { x = 32 * 0, y = 0, w = 32, h = 32 },

            { x = 32 * 1, y = 0, w = 32, h = 32 },
            { x = 32 * 1, y = 0, w = 32, h = 32 },
            { x = 32 * 1, y = 0, w = 32, h = 32 },

            { x = 32 * 2, y = 0, w = 32, h = 32 },
            { x = 32 * 2, y = 0, w = 32, h = 32 },
            { x = 32 * 2, y = 0, w = 32, h = 32 },

            { x = 32 * 3, y = 0, w = 32, h = 32 },
            { x = 32 * 3, y = 0, w = 32, h = 32 },
            { x = 32 * 3, y = 0, w = 32, h = 32 },

            { x = 32 * 4, y = 0, w = 32, h = 32 },
            { x = 32 * 4, y = 0, w = 32, h = 32 },
            { x = 32 * 4, y = 0, w = 32, h = 32 },

            { x = 32 * 3, y = 0, w = 32, h = 32 },
            { x = 32 * 3, y = 0, w = 32, h = 32 },
            { x = 32 * 3, y = 0, w = 32, h = 32 },

            { x = 32 * 2, y = 0, w = 32, h = 32 },
            { x = 32 * 2, y = 0, w = 32, h = 32 },
            { x = 32 * 2, y = 0, w = 32, h = 32 },

            { x = 32 * 1, y = 0, w = 32, h = 32 },
            { x = 32 * 1, y = 0, w = 32, h = 32 },
            { x = 32 * 1, y = 0, w = 32, h = 32 },

            { x = 32 * 0, y = 0, w = 32, h = 32 },
            { x = 32 * 0, y = 0, w = 32, h = 32 },
            { x = 32 * 0, y = 0, w = 32, h = 32 },
        }, "exocet_anim.png"),
        {
            tag = "script",
            update = nil,
            render = nil
        },
        { tag = "drag" }
    }
}
Player.__index = Player

function Player:new()
    local p = setmetatable({}, Player)
    
    p.entity = Entity:new("player")
    p.nextDescOxy = os.time()
    
    return p
end

function Player:setPointerEntity(pointer)
    self["_ptr"] = pointer
end

function Player:setUpdateScript(s_update)
    self.components[3]["update"] = s_update
end

function Player:setRenderScript(s_update)
    self.components[3]["render"] = s_update
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

function Player:gamealive()
    if self.entity:getPosition().y < 850 then
        engine.centerOnEntity(self.entity)
    end
    
    self:momentumCalculus()

    if os.time() > self.nextDescOxy + 1 then
        self.oxygen = self.oxygen - 10
        self.nextDescOxy = os.time()
    end

    if self.oxygen <= 0 then
        self.gameover = true
    end
    
    if os.time() > self.beginGame + 1 then
        mainState.score = mainState.score + 1
        self.beginGame = os.time()
    end
end

function Player:update()
    self.entity:fitSizeWithHitbox()
    
    if self.entity:getPosition().y >= 1000 then
        self.gameover = true;
        self.entity:setVelocity(Vector2D:new(0, 0))
    end

    if self.gameover == false then
        self:gamealive()
    else
        mainState.vx = 0
        if self.dieTime == 0 then
            self.dieTime = os.time()
        end
    end

    if self.gameover and os.time() >= self.dieTime + 2 then
        engine.restart()
    end
end

function Player:__tostring()
    return tostring(self.entity.tag)
end

return Player