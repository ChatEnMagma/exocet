---@class Wall: Entity
Wall = {}
Wall.__index = function (_, key) return Wall[key] or Entity[key] end

---@param position Vector2D
---@return Wall
function Wall:new(position)
    --- @class Wall: Entity
    local e = setmetatable(Entity:new("wall"), Wall)

    e.components = {
        anchor = AnchorComponent:new(Rect:new(32, 32), position)
    }

    return e
end