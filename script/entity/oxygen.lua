--- @class Oxygen An Entity class
Oxygen = {
    --- @type Entity
    entity = nil,

    components = {
        PhysicComponent:new({ x = 0, y = 0, w = 300, h = 200}),
        {
            tag = "script",
            update = nil
        },
        SpriteComponent:new("orage_nuage.jpg"),
    },
}
Oxygen.__index = Oxygen

--- @return Oxygen
--- @param vec Vector2D
function Oxygen:new(vec)
    local o = setmetatable({}, Oxygen)

    o.entity = Entity:new("oxygen")

    o.components[1].position = {
        x = vec.x,
        y = vec.y
    }

    return o
end

function Oxygen:update()
    self.entity:setVelocity(Vector2D:new(mainState.vx, 0))

    if self.entity:getPosition().x < engine.getCameraPosition().x - 64 then
        self.entity:destroy()
    end

    if self.entity:getCollideEntity(engine.mainEntities.player) then
        engine.mainEntities.player.oxygen = engine.mainEntities.player.oxygen + 25
        if engine.mainEntities.player.oxygen > 100 then
            engine.mainEntities.player.oxygen = 100
        end

        self.entity:destroy()
    end
end

return Oxygen