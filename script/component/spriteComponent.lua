SpriteComponent = {
    tag = "sprite",
    path = "",
    size = { w = 32, h = 32 },
    fitSizeWithHitbox = false
}
SpriteComponent.__index = SpriteComponent

--- @param path string
--- @param size table|nil
function SpriteComponent:new(path, size)
    local c = {}

    setmetatable(c, SpriteComponent)

    c.tag = "sprite"
    c.path = path
    if size ~= nil then
        c.size = size
        c.fitSizeWithHitbox = false
    else
        c.fitSizeWithHitbox = true
    end

    return c
end

return SpriteComponent