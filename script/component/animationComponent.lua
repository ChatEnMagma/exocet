--- @class AnimationComponent
AnimationComponent = {
    tag = "animation",
    isSheetTexture = false,
    --- @type string|nil
    path = nil,
    textures = {},
    fps = 60,
    --- @type Rect
    size = {}
}
AnimationComponent.__index = AnimationComponent

--- @param fps integer
--- @param size Rect
--- @param textures table
--- @param path string|nil
function AnimationComponent:new(fps, size, textures, path)
    local c = {}

    setmetatable(c, AnimationComponent)

    c.tag = "animation"

    c.isSheetTexture = (path ~= nil)
    c.path = path

    c.fps = fps
    c.size = size
    c.textures = textures

    return c
end

return AnimationComponent