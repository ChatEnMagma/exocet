--- @class Bird An Entity class
Bird = {
    --- @type Entity
    entity = nil,

    components = {
        PhysicComponent:new({ x = 0, y = 0, w = 128, h = 128 }),
        {
            tag = "script",
            update = nil
        },
        SpriteComponent:new("fou_de_bassan.png"),
    },
}
Bird.__index = Bird

--- @return Bird
--- @param vec Vector2D
function Bird:new(vec)
    local c = setmetatable({}, Bird)

    c.entity = Entity:new("bird")

    c.components[1].position = {
        x = vec.x,
        y = vec.y
    }

    return c
end

function Bird:update()
    self.entity:setVelocity(Vector2D:new(mainState.vx - 1.5, 0))

    if self.entity:getPosition().x < engine.getCameraPosition().x - 64 then
        self.entity:destroy()
    end

    if self.entity:getCollideEntity(engine.mainEntities.player) then
        engine.mainEntities.player.gameover = true
    end
end

return Bird