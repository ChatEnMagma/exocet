--- @class PhysicComponent
PhysicComponent = {
    tag = "physic",
    hitbox = {
        x = 0,
        y = 0,
        w = 32,
        h = 32
    },
    position = {
        x = 0,
        y = 0
    }
}

--- @param hitbox table
--- @param position Vector2D|nil
function PhysicComponent:new(hitbox, position)
    local c = {}

    setmetatable(c, PhysicComponent)

    c.tag = "physic"
    c.hitbox = hitbox

    if position == nil then
        local position = {
            x = 0,
            y = 0
        }
    end
    c.position = position

    return c
end

return PhysicComponent