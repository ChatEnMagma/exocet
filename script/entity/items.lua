--- @class Items
Items = {
    entity = Entity:new("items"),
    tag = "gen",
    allTags = {
        "waterMask"
    },

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

function Items:update()
    self.entity:setVelocity(Vector2D:new(mainState.vx, 0))

    if self.entity:isOutsideScreen() and self.entity:getPosition().x < engine.getCameraPosition().x then
        self.entity:destroy()
    end

    if self.entity:getCollideEntity(engine.mainEntities.player) then
        self.entity:destroy()
    end
end

return Items