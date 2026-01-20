---@class Liner
Liner = {
    --- @type Entity
    entity = Entity:new("liner"),
    next = 0,
    components = {}
}
Liner.__index = Liner

function Liner:updateHatch()
    if self.next <= 0 then
        local e = Liner:new(Vector2D:new(-0, 300))
        --- @type Liner
        --local e = Liner:new(engine.mainEntities.player.entity:getPosition())

        engine:addEntity(e)

        --self.next = math.random(1000 - mainState.step, 5000 - mainState.step)
        self.next = 10
    end
    self.next = self.next - 1
end

--- @param position Vector2D
--- @return Liner
function Liner:new(position)
    local e = setmetatable({}, Liner)

    e.entity = Entity:new("liner")

    e.components = {
        PhysicComponent:new(Polygon:new( {
                Vector2D:new(0, 200),
                Vector2D:new(200, 100),
                Vector2D:new(400, 300),
                Vector2D:new(400, 300),
                Vector2D:new(0, 300)
            }
        ), position),
        SpriteComponent:new("paquebot.png"),
        ScriptComponent:new(function () e:update() end)
    }

    return e
end

function Liner:update()
    self.entity:setVelocity(Vector2D:new(-mainState.vx - 2 , 0))
    if self.entity:isOutsideScreen() and self.entity:getPosition().x > engine:getCameraPosition().x +  engine:getWinWidth() then
        self.entity:destroy()
    end

    if self.entity:getCollideEntity(engine.mainEntities.player) then
        engine.mainEntities.player.gameover = true
    end
end

return Liner