--- @class Ufo An Entity class
Ufo = {
    --- @type Entity
    entity = nil,
    next = 0,

    components = {},
}
Ufo.__index = Ufo

function Ufo:updateHatch(vec)
    local playerPos = engine.mainEntities.player.entity:getPosition()
    if self.next <= 0 and playerPos.y <= -700 then
        local e = Ufo:new(vec)

        engine.addEntity(e)

        self.next = math.random(1000 - mainState.step, 1500 - mainState.step)
    end
    self.next = self.next - 1
end
--- @return Ufo
--- @param vec Vector2D
function Ufo:new(vec)
    local e = setmetatable({}, Ufo)

    e.entity = Entity:new("ufo")

    e.components = {
        PhysicComponent:new(Rect:new(128, 256), vec),
        ScriptComponent:new(function () e:update() end),
        SpriteComponent:new("ovni.png")
    }

    return e
end

function Ufo:update()
    self.entity:setVelocity(Vector2D:new(mainState.vx - 1.5, 0))

    if self.entity:isOutsideScreen() and self.entity:getPosition().x < engine.getCameraPosition().x then
        self.entity:destroy()
    end

    if self.entity:getCollideEntity(engine.mainEntities.player) then
        engine.mainEntities.player.gameover = true
    end
end

return Ufo