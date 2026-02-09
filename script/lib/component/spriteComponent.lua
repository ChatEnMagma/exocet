--- @class SpriteComponent
--- @field tag string
--- @field key string
--- @field path string?
--- @field size Rect
--- @field nTextures integer
--- @field fps integer
SpriteComponent = {}
SpriteComponent.__index = SpriteComponent

--- @overload fun(SpriteComponent, key: string)
--- @overload fun(SpriteComponent, key: string, size: Rect, nTextures: integer, fps: integer)
--- @param key string
--- @param path string
--- @param size Rect?
--- @param nTextures integer?
--- @param fps integer?
--- @return SpriteComponent
function SpriteComponent:new(key, path, size, nTextures, fps)
    local c = {}

    setmetatable(c, SpriteComponent)

    c.tag = "sprite"

    c.key = key
    c.path = path
    c.size = size
    c.nTextures = nTextures
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