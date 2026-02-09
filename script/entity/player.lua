--- Class Player has all methods for the player of the game
--- @class Player: Entity
Player = {}
Player.__index = function (_, key) return Player[key] or Entity[key] end

--- @param position Vector2D?
--- @return Player
function Player:new(position)
    --- @class Player: Entity
    local p = setmetatable(Entity:new("Player"), Player)

    p.components = {
        physic = PhysicComponent:new(Rect:new(64, 64), position),
        script = ScriptComponent:new(function () p:update() end),
        sprite = SpriteComponent:new("exocet", "exocet_anim.png", Rect:new(7, 1, 32, 32), 7, 10)
    }

    return p
end

function Player:move()
    if engine:getKey(SDL.SDLK_UP) then
        self:setVelocity(self:getVelocity() + Vector2D:new(0, -1))
    end
    if engine:getKey(SDL.SDLK_DOWN) then
        self:setVelocity(self:getVelocity() + Vector2D:new(0, 1))
    end
    if engine:getKey(SDL.SDLK_LEFT) then
        self:setVelocity(self:getVelocity() + Vector2D:new(-1, 0))
    end
    if engine:getKey(SDL.SDLK_RIGHT) then
        self:setVelocity(self:getVelocity() + Vector2D:new(1, 0))
    end
end

function Player:update()
    self:move()

    self:fitSizeWithHitbox()
    engine:centerOnEntity(self)
end