--- @class Cloud An Entity class
Cloud = {
    --- @type Entity
    entity = nil,

    next = 0,

    components = {},
    oldWhooshPath = "whoosh" .. tostring(math.random(0, 1)) .. ".wav",
    newWhooshPath = ""
}

Cloud.__index = Cloud

function Cloud:updateHatch(vec)
    local player = engine.mainEntities.player

    if self.next <= 0 and player.entity:getVelocity().y < 500 then
        local e = Cloud:new(vec)

        engine:addEntity(e)

        if engine.mainEntities.player.entity:getPosition().y <= 8000 then
            self.next = math.random(30, 100)
        else
            self.next = math.random(100 + mainState.step, 250 + mainState.step)
        end
    end
    self.next = self.next - 1
end

--- @return Cloud
--- @param vec Vector2D
function Cloud:new(vec)
    local c = setmetatable({}, Cloud)

    c.entity = Entity:new("cloud")
    c.components = {
        PhysicComponent:new(Rect:new(300, 200), vec),
        ScriptComponent:new(function () c:update() end),
        SpriteComponent:new("nuage.png")
    }

    c.oldWhooshPath = "whoosh" .. tostring(math.random(0, 1)) .. ".wav"

    return c
end

function Cloud:update()
    self.entity:setVelocity(Vector2D:new(mainState.vx, 0))

    if self.entity:isOutsideScreen() and self.entity:getPosition().x < engine:getCameraPosition().x then
        self.entity:destroy()
    end

    if self.entity:getCollideEntity(engine.mainEntities.player) then
        local pvec = engine.mainEntities.player.entity:getVelocity()
        pvec = pvec + Vector2D:new(0, -10)
        engine.mainEntities.player.entity:setVelocity(pvec)
        engine.mainEntities.player.momentum = engine.mainEntities.player.momentum + 1
        
        if engine:isPlayingSong(self.oldWhooshPath) == false then
            self.newWhooshPath = "whoosh" .. tostring(math.random(0, 1)) .. ".wav"
            engine:playSong(self.newWhooshPath)
            self.oldWhooshPath = self.newWhooshPath
        end
    end
end

return Cloud