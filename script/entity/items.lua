--- @class Items
Items = {
    entity = Entity:new("items"),
    tag = "gen",
    allTags = {
        "waterMask",
        "jetpack"
    },

    next = 0,

    components = {}
}
Items.__index = Items

function Items:new(position)
    local e = {}

    setmetatable(e, Items)

    e.tag = Items.allTags[math.random(#Items.allTags)]
    e.entity = Entity:new("item_" .. e.tag)

    e.components = {
        PhysicComponent:new(Rect:new(64, 64), position),
        ScriptComponent:new(function () e:update() end),
        SpriteComponent:new(e.tag .. ".png")
    }

    return e
end

function Items:updateHatch(vec)
    if self.next <= 0 then
        local e = Items:new(vec)

        engine:addEntity(e)

        self.next = math.random(110 + mainState.step, 300 + mainState.step)
    end
    self.next = self.next - 1
end

function Items:update()
    self.entity:setVelocity(Vector2D:new(mainState.vx, 0))

    if self.entity:isOutsideScreen() and self.entity:getPosition().x < engine:getCameraPosition().x then
        self.entity:destroy()
    end

    if self.entity:getCollideEntity(engine.mainEntities.player) then
        engine.mainEntities.player.components[3] = playerAnimations[self.tag]
        engine.mainEntities.player.components[3]:refresh(engine.mainEntities.player.entity)
        engine.mainEntities.player.tagPower = self.tag
        engine.mainEntities.player.timePower = os.time() + 5
        self.entity:destroy()
    end
end

return Items