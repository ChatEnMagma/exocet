--- @class Oxygen An Entity class
Oxygen = {
    --- @type Entity
    entity = nil,
    next = 0,
    components = {},
}
Oxygen.__index = Oxygen

--- @return Oxygen
--- @param position Vector2D
function Oxygen:new(position)
    local o = setmetatable({}, Oxygen)

    o.entity = Entity:new("oxygen")

    o.components = {
        PhysicComponent:new(Rect:new(300, 200), position),
        ScriptComponent:new(function () o:update() end),
        SpriteComponent:new("orage.png")
    }

    return o
end

function Oxygen:updateHatch(vec)
    if self.next <= 0 then
        local e = Oxygen:new(vec)

        engine:addEntity(e)

        local playerPos = engine.mainEntities.player.entity:getPosition()
        if playerPos.y < 500 then
            self.next = math.random(100 + mainState.step, 300 + mainState.step)
        else
            self.next = math.random(400 + mainState.step, 1000 + mainState.step)
        end
    end
    self.next = self.next - 1
end

function Oxygen:update()
    self.entity:setVelocity(Vector2D:new(mainState.vx, 0))

    if self.entity:isOutsideScreen() and self.entity:getPosition().x < engine:getCameraPosition().x then
        self.entity:destroy()
    end

    if self.entity:getCollideEntity(engine.mainEntities.player) then
        engine.mainEntities.player.oxygen = engine.mainEntities.player.oxygen + 25
        if engine.mainEntities.player.oxygen > 100 then
            engine.mainEntities.player.oxygen = 100
        end
    end
    local rainPos = self.entity:getPosition() + Vector2D:new(math.random(0, self.entity:getRect().w), self.entity:getRect().h)

    engine:addEntity(Rain:new(self.entity:getPosition(), rainPos))
end

return Oxygen