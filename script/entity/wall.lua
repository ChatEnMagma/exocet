---@class WallData
Wall = {}
Wall.__index = Wall

---@param position Vector2D
---@return Wall
function Wall:new(position)
    --- @class Wall: Entity
    local e = Entity:new("wall")

    setmetatable(e.data, Wall)

    AnchorComponent:new(e, Rect:new(32, 32), position)
    SpriteComponent:new(e, engine:getSprite("tileWall"), 15):fitSizeWithHitbox()

    return e
end