--- Just moving box
--- @class BoxData
Box = {}
Box.__index = Box

--- @class Box: Entity
BoxEntity = {
    components = {
        --- @type PhysicComponent
        PhysicComponent = nil,
        --- @type SpriteComponent
        SpriteComponent = nil,
    }
}

--- @param position Vector2D?
--- @return Box
function Box:new(position)
    --- @class Box: Entity
    local e = Entity:new("box")

    setmetatable(e.data, Box)

    PhysicComponent:new(e, Rect:new(128, 128), position):setMasse(1)
    SpriteComponent:new(e, engine:getSprite("wall", "wall.png")):fitSizeWithHitbox()
    ScriptComponent:new(e, function ()
        e.data.update(e)
    end)

    return e
end

--- @param e Box
function Box.update(e)
    e.components.PhysicComponent:setVelocity(Vector2D:new(1, 0))
end