--- @class Wave An Entity class
Wave = {
    --- @type Entity
    entity = nil,

    components = {
        {
            tag = "physic",
            hitbox = {
                x = 0,
                y = 0,
                w = 128,
                h = 128
            }
        },
        {
            tag = "script",
            update = nil
        },
        {
            tag = "sprite",
            path = "vague.png",
            fitSizeWithHitbox = true
        }
    },
}
Wave.__index = Wave

--- @return Wave
--- @param vec Vector2D
function Wave:new(vec)
    local e = setmetatable({}, Wave)

    e.entity = Entity:new("wave")

    e.components[1].position = {
        x = vec.x,
        y = vec.y
    }

    return e
end

function Wave:update()
    self.entity:setVelocity(Vector2D:new(mainState.vx, 0))

    if self.entity:getPosition().x < engine.getCameraPosition().x - 64 then
        self.entity:destroy()
    end

    if self.entity:getCollideEntity(engine.mainEntities.player) then
        local pvec = engine.mainEntities.player.entity:getVelocity()
        pvec = pvec + Vector2D:new(0, -10)
        engine.mainEntities.player.entity:setVelocity(pvec)
    end
end

return Wave