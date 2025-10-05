--- @class Cloud An Entity class
Cloud = {
    --- @type Entity
    entity = nil,

    tag = "cloud",

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
            tag = "script",
            update = nil
        }
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
    self.entity:setVelocity(Vector2D:new(-5, 0))

    if self.entity:getPosition().x < engine.getCameraPosition().x - 64 then
        self.entity:destroy()
    end

    if self.entity:getCollideEntity(engine.mainEntities.player) then
        local pvec = engine.mainEntities.player.entity:getVelocity()
        pvec = pvec + Vector2D:new(0, -10)
        engine.mainEntities.player.entity:setVelocity(pvec)
    end
end

return Cloud