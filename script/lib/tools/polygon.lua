---@meta
---@class Polygon
Polygon = {
    ---@type Vector2D[]
    vertices = nil
}

--- @param polygons Vector2D[]
--- @return Polygon
function Polygon:new(polygons)
    ---@type Polygon
    local p = setmetatable({}, Polygon)
    p.vertices = polygons
    return p
end

function Polygon:__index(key)
    return self.vertices[key]
end

function Polygon:__len()
    return #self.vertices
end

function Polygon:__tostring()
    return "yah" .. self.vertices[1]:__tostring()
end