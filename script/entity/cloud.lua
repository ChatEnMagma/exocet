--- @class Cloud An Entity class
Cloud = {
    --- @type Entity
    entity = nil,

    components = {
        PhysicComponent:new( { x = 0, y = 0, w = 300, h = 200 }),
        {
            tag = "script",
            update = nil
        },
        SpriteComponent:new("nuage.png"),
    },
}

Cloud.__index = Cloud

--- @return Cloud
--- @param vec Vector2D
function Cloud:new(vec)
    local c = setmetatable({}, Cloud)

    c.entity = Entity:new("cloud")

    c.components[1].position = {
        x = vec.x,
        y = vec.y
    }

    return c
end

function Cloud:update()
    self.entity:setVelocity(Vector2D:new(mainState.vx, 0))

    if self.entity:getPosition().x < engine.getCameraPosition().x - 64 then
        self.entity:destroy()
    end

    if self.entity:getCollideEntity(engine.mainEntities.player) then
        local pvec = engine.mainEntities.player.entity:getVelocity()
        pvec = pvec + Vector2D:new(0, -10)
        engine.mainEntities.player.entity:setVelocity(pvec)
        engine.mainEntities.player.momentum = engine.mainEntities.player.momentum + 1
    end
end

return Cloud