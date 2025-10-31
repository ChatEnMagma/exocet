--- @class Bird An Entity class
Bird = {
    --- @type Entity
    entity = nil,

    components = {},
}
Bird.__index = Bird

--- @return Bird
--- @param vec Vector2D
function Bird:new(vec)
    local c = setmetatable({}, Bird)

    c.entity = Entity:new("bird")

    c.components = {
        PhysicComponent:new(Rect:new(128, 128), vec),
        ScriptComponent:new(function () c:update() end),
        SpriteComponent:new("fou_de_bassan.png")
    }

    return c
end

function Bird:update()
    self.entity:setVelocity(Vector2D:new(mainState.vx - 1.5, 0))

    if self.entity:isOutsideScreen() and self.entity:getPosition().x < engine.getCameraPosition().x then
        self.entity:destroy()
    end

    if self.entity:getCollideEntity(engine.mainEntities.player) then
        engine.mainEntities.player.gameover = true
    end
end

return Bird