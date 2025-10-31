--- @class PhysicComponent
PhysicComponent = {
    tag = "physic",
    --- @type Rect
    hitbox = {},
    --- @type Vector2D
    position = Vector2D:new(0, 0)
}

--- @param hitbox Rect
--- @param position Vector2D|nil
function PhysicComponent:new(hitbox, position)
    local c = {}

    setmetatable(c, PhysicComponent)

    c.tag = "physic"
    
    c.hitbox = hitbox
    c.position = position

    return c
end

return PhysicComponent