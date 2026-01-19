--- @class SpriteComponent
SpriteComponent = {
    tag = "sprite",
    --- @type string|nil
    path = "",
    fps = 60,
    angle = 0,
    nTextures = 1,
    --- @type Rect
    size = nil
}
SpriteComponent.__index = SpriteComponent

--- @param path string
--- @param size Rect|nil
--- @param nTextures integer|nil
--- @param fps integer|nil
--- @return SpriteComponent
function SpriteComponent:new(path, size, nTextures, fps)
    local c = {}

    setmetatable(c, SpriteComponent)

    c.tag = "sprite"

    c.path = path
    c.size = size
    c.nTextures = nTextures
    c.angle = 0

    c.fps = fps

    return c
end

--- Get how much frame is store
--- @return integer
function SpriteComponent:getFrame() return self.nTextures end

--- @param entity Entity
function SpriteComponent:refresh(entity)
    entity:setTexture(self.path, self.size, self.nTextures)
end

return SpriteComponent