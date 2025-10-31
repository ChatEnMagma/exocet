--- @class Oxygen An Entity class
Oxygen = {
    --- @type Entity
    entity = nil,
    rain = {},
    components = {},
}
Oxygen.__index = Oxygen

--- @return Oxygen
--- @param vec Vector2D
function Oxygen:new(vec)
    local o = setmetatable({}, Oxygen)

    o.entity = Entity:new("oxygen")

    o.components = {
        PhysicComponent:new(Rect:new(300, 200), vec),
        ScriptComponent:new(function () o:update() end),
        SpriteComponent:new("orage.png")
    }
    
    o.rain = {
        vec + Vector2D:new(10, 200),
        vec + Vector2D:new(15, 200),
        vec + Vector2D:new(30, 200),
        vec + Vector2D:new(50, 200),
        vec + Vector2D:new(60, 200),
    }

    return o
end

function Oxygen:update()
    self.entity:setVelocity(Vector2D:new(mainState.vx, 0))

    if self.entity:isOutsideScreen() and self.entity:getPosition().x < engine.getCameraPosition().x then
        self.entity:destroy()
    end

    if self.entity:getCollideEntity(engine.mainEntities.player) then
        engine.mainEntities.player.oxygen = engine.mainEntities.player.oxygen + 25
        if engine.mainEntities.player.oxygen > 100 then
            engine.mainEntities.player.oxygen = 100
        end
    end
end

function Oxygen:render()
    engine.setColor(0, 0, 0xff, 0xff)
    for key,value in self.rain do
        engine.renderRect(value, 16, 128)
        value = value + Vector2D:new(mainState.vx, 1)

        if(value.y >= self.entity:getPosition().y + 200) then
            value.y = self.entity:getPosition().y
        end
    end
end

return Oxygen