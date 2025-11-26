--- @class Bird An Entity class
Bird = {
    --- @type Entity
    entity = nil,

    next = 0,

    components = {},
}
Bird.__index = Bird

function Bird:updateHatch(vec)
    local playerPos = engine.mainEntities.player.entity:getPosition()

    if self.next <= 0 and (mainState.score > 10) and (playerPos.y <= 500) then

        local e = Bird:new(vec)

        engine.addEntity(e)

        if(playerPos.y <= 500) then
            self.next = math.random(110, 1000)
        else
            self.next = math.random(50, 500)
        end
    end
    self.next = self.next - 1
end

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