--- @class Wave An Entity class
Wave = {
    --- @type Entity
    entity = nil,

    components = {},
}
Wave.__index = Wave

--- @return Wave
--- @param vec Vector2D
function Wave:new(vec)
    local e = setmetatable({}, Wave)

    e.entity = Entity:new("wave")

    e.components = {
        PhysicComponent:new(Rect:new(128, 128), vec),
        ScriptComponent:new(function () e:update() end),
        SpriteComponent:new("vague.png")
    }

    return e
end

function Wave:update()
    self.entity:setVelocity(Vector2D:new(mainState.vx, 0))

    if self.entity:isOutsideScreen() and self.entity:getPosition().x < engine.getCameraPosition().x then
        self.entity:destroy()
    end

    if self.entity:getCollideEntity(engine.mainEntities.player) then
        local pvec = engine.mainEntities.player.entity:getVelocity()
        pvec = pvec + Vector2D:new(0, -10)
        engine.mainEntities.player.entity:setVelocity(pvec)
    end
end

return Wave