local os = require("os")

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
    timePower = 0,
    tagPower = "normal",
    components = {}
}
Player.__index = Player

playerAnimations = {
    --- @type SpriteComponent
    normal = SpriteComponent:new("exocet_anim.png", Rect:new(7, 1, 32, 32), 7, 10),
    --- @type SpriteComponent
    waterMask  = SpriteComponent:new("exocet_anim_waterMask.png", Rect:new(7, 1, 32, 32), 7, 10),
    --- @type SpriteComponent
    jetpack = SpriteComponent:new("exocet_anim_jetpack.png", Rect:new(7, 1, 32, 32), 7, 10),
}

function Player:new()
    --- @class Player
    local p = setmetatable({}, Player)

    p.entity = Entity:new("player")

    p.components = {
        PhysicComponent:new(Rect:new(64, 64), Vector2D:new(0, -500)),
        ScriptComponent:new(function () p:update() end),
        playerAnimations.normal
    }

    p.nextDescOxy = os.time()
    p.oxygen = 100
    p.tagPower = "normal"

    return p
end

function Player:updatePower()
    if self.tagPower == "normal" then
        return
    end

    if os.time() >= self.timePower then
        if self.tagPower == "jetpack" then
            mainState.vx = mainState.vx + 2
        end
        self.tagPower = "normal"
        self.components[3] = playerAnimations.normal
        self.components[3]:refresh(self.entity)
    elseif self.tagPower == "waterMask" then
        self.oxygen = 100
    end
end

function Player:momentumCalculus()
    if engine:getJustAnyKey() then
        self.momentum = self.momentum // 2
    end
    if engine:getAnyKey() then
        self.momentum = self.momentum + 1

        local vel = self.entity:getVelocity() + Vector2D:new(0, self.momentum * 2)
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

    if self.momentum > 100 then
        self.momentum = 100
    end
end

function Player:gamealive()
    if self.entity:getPosition().y < 850 then
        engine:centerOnEntity(self.entity)
    end

    self:momentumCalculus()

    if os.time() > self.nextDescOxy + 1 then
        self.oxygen = self.oxygen - 10
        self.nextDescOxy = os.time()
    end

    if self.oxygen <= 0 then
        self.gameover = true
    end

    self:updatePower()

    if os.time() > self.beginGame + 1 then
        local addscore = 1
        if(self.tagPower == "jetpack") then
            addscore = 2
        else
            addscore = 1
        end
        mainState.score = mainState.score + addscore
        self.beginGame = os.time()
    end
end

function Player:update()
    self.entity:fitSizeWithHitbox()
    self.entity:setTextureAngle(self.momentum * math.sin(self.entity:getVelocity().y))

    if self.entity:getPosition().y >= mainState.seaLevel and self.gameover == false then
        self.gameover = true
        self.entity:setVelocity(Vector2D:new(0, 0))
        engine:playSong("plouf.wav")
    end

    if self.gameover == false then
        self:gamealive()
    else
        mainState.vx = 0
        if self.dieTime == 0 then
            self.dieTime = os.time()
        end

         if self.gameover and (os.time() >= (self.dieTime + 2)) then
            engine:restart()
        end
    end

    if engine:getKey(SDL.SDLK_U) then
        local e = {
            entity = Entity:new("particle"),
            components = {
                ParticleComponent:new(self.entity:getPosition(), 100),
                SpriteComponent:new("vague.png")
            }
        }

        engine:addEntity(e)
    end
end

function Player:__tostring()
    return tostring(self.entity.tag)
end

return Player