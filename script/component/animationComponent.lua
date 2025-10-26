--- @class AnimationComponent
AnimationComponent = {
    tag = "animation",
    isSheetTexture = false,
    path = nil,
    textures = {},
    fps = 60,
    size = {
        w = 32,
        h = 32
    }
}
AnimationComponent.__index = AnimationComponent

--- @param fps integer
--- @param size table
--- @param textures table
--- @param path string|nil
function AnimationComponent:new(fps, size, textures, path)
    local c = {}

    setmetatable(c, AnimationComponent)

    c.tag = "animation"

    if path ~= nil then
        c.isSheetTexture = true
        c.path = path
    else
        c.path = nil
    end
    c.fps = fps
    c.size = size
    c.textures = textures

    return c
end

return AnimationComponent