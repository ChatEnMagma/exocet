--- Class Player has all methods for the player of the game
--- @class PlayerData
Player = {}
Player.__index = Player

--- @class Player: Entity
PlayerEntity = {
    components = {
        --- @type PhysicComponent
        PhysicComponent=nil,
        --- @type ScriptComponent
        ScriptComponent=nil,
        --- @type SpriteComponent
        SpriteComponent=nil
    }
}

--- @param position Vector2D?
--- @return Player
function Player:new(position)
    --- @class Player: Entity
    local e = Entity:new("Player")

    setmetatable(e.data, Player)

    PhysicComponent:new(e, Rect:new(64, 64), position)
    ScriptComponent:new(e, function () e.data.update(e) end)
    SpriteComponent:new(e, engine:getSprite("exocet", "exocet_anim.png", 7, 1, 32, 32, 7), 10):fitSizeWithHitbox()

    e.components.PhysicComponent:setSpeed(Vector2D:new(5, 5))
    e.components.PhysicComponent:setMaxSpeed(Vector2D:new(40, 40))
    e.components.PhysicComponent:setFriction(Vector2D:new(0.1, 0.1))

    e.data.test = 0

    return e
end

--- @param e Player
function Player.update(e)
    --- @type PhysicComponent
    local physic = e.components.PhysicComponent

    local speed = e.components.PhysicComponent:getSpeed()
    if engine:getKey(SDL.SDLK_Z) then physic:setVelocity(physic:getVelocity() + Vector2D:new(0, -speed.y)) end
    if engine:getKey(SDL.SDLK_S) then physic:setVelocity(physic:getVelocity() + Vector2D:new(0, speed.y)) end
    if engine:getKey(SDL.SDLK_Q) then physic:setVelocity(physic:getVelocity() + Vector2D:new(-speed.x, 0)) end
    if engine:getKey(SDL.SDLK_D) then physic:setVelocity(physic:getVelocity() + Vector2D:new(speed.x, 0)) end

    if engine:getKey(SDL.SDLK_U) then engine:addEntity(Wall:new(physic:getPosition())) end

    if engine:getJustKey(SDL.SDLK_H) then engine:getSong("plouf", "plouf.wav"):play() end
    if engine:getJustKey(SDL.SDLK_G) then engine:getSong("whoosh", "whoosh0.wav"):play(300) end

    engine:centerOnEntity(e)
end