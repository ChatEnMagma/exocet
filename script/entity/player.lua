--- Class Player has all methods for the player of the game
--- @class Player: Entity
Player = {}
Player.__index = function (table, key)
    return Player[key] or Entity[key]
end

playerAnimations = {
    --- @type SpriteComponent
    normal = SpriteComponent:new("exocet_anim.png", Rect:new(7, 1, 32, 32), 7, 10),
    --- @type SpriteComponent
    waterMask  = SpriteComponent:new("exocet_anim_waterMask.png", Rect:new(7, 1, 32, 32), 7, 10),
    --- @type SpriteComponent
    jetpack = SpriteComponent:new("exocet_anim_jetpack.png", Rect:new(7, 1, 32, 32), 7, 10),
}

function Player:new()
    --- @class Player: Entity
    local p = setmetatable(Entity:new("Player"), Player)

    p.components = {
        physic = PhysicComponent:new(Rect:new(64, 64), Vector2D:new(0, -500)),
        script = ScriptComponent:new(function () p:update() end),
        sprite = SpriteComponent:new("exocet_anim.png", Rect:new(7, 1, 32, 32), 7, 10)
    }

    return p
end

function Player:update()
    self:fitSizeWithHitbox()

    engine:centerOnEntity(self)
end