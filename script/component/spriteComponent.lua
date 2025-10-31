SpriteComponent = {
    tag = "sprite",
    path = "",
    --- @type Rect|nil
    size = nil,
    fitSizeWithHitbox = false
}
SpriteComponent.__index = SpriteComponent

--- @param path string
--- @param size Rect|nil
function SpriteComponent:new(path, size)
    local c = {}

    setmetatable(c, SpriteComponent)

    c.tag = "sprite"
    c.path = path
    c.size = size
    c.fitSizeWithHitbox = (size == nil)

    return c
end

return SpriteComponent