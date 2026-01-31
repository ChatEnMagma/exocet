--- @class AnchorComponent
--- @field tag string the tag of Component
--- @field hitbox Rect
--- @field position Vector2D
AnchorComponent = {}

--- @param hitbox Rect
--- @param position Vector2D?
function AnchorComponent:new(hitbox, position)
    local c = setmetatable({}, AnchorComponent)

    c.tag = "anchor"

    c.hitbox = hitbox
    c.position = position

    return c
end