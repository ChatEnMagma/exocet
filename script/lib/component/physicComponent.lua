--- @class PhysicComponent
--- @field tag string the tag of Component
--- @field hitbox Rect
--- @field position Vector2D
PhysicComponent = {}

--- @param hitbox Rect
--- @param position Vector2D?
function PhysicComponent:new(hitbox, position)
    local c = setmetatable({}, PhysicComponent)

    c.tag = "physic"

    c.hitbox = hitbox
    c.position = position or Vector2D:new()

    return c
end