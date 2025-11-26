--- @class Wave An Entity class
Wave = {
    --- @type Entity
    entity = nil,
    next = 0,

    components = {},
}
Wave.__index = Wave

function Wave:updateHatch()
    if self.next <= 0 then
        local pos = Vector2D:new(
            engine.getWinWidth(),
            1000 - 120
        )
        local e = Wave:new(pos)

        engine.addEntity(e)

        self.next = math.random(256 + mainState.step, 500 + mainState.step)
    end
    self.next = self.next - 1
end

--- @return Wave
--- @param position Vector2D
function Wave:new(position)
    local e = setmetatable({}, Wave)

    e.entity = Entity:new("wave")

    e.components = {
        PhysicComponent:new(Rect:new(256, 128), position),
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
        pvec = pvec + Vector2D:new(0, -20)
        engine.mainEntities.player.entity:setVelocity(pvec)
        engine.mainEntities.player.momentum = engine.mainEntities.player + 10
        engine.mainEntities.player.oxygen = 100
    end
end

return Wave