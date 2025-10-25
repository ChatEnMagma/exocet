--- @meta
--- @class Vector2D
Vector2D = {
    --- @type number
    x = 0,
    --- @type number
    y = 0
}
Vector2D.__index = Vector2D

function Vector2D:new(x, y)
    local v = {}
    setmetatable(v, Vector2D)

    v.x = x
    v.y = y

    return v
end

--- @param vec2D Vector2D
function Vector2D:__add(vec2D)
    return Vector2D:new(self.x + vec2D.x, self.y + vec2D.y)
end

--- @param vec2D Vector2D
function Vector2D:__sub(vec2D)
    return Vector2D:new(self.x - vec2D.x, self.y - vec2D.y)
end

--- @param vec2D Vector2D
function Vector2D:__mul(vec2D)
    return Vector2D:new(self.x * vec2D.x, self.y * vec2D.y)
end

function Vector2D:__tostring()
    return '(' .. self.x .. ',' .. self.y .. ')'
end

return Vector2D