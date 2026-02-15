--- @class AnchorComponent
AnchorComponent = {}

--- @param entity Entity
--- @param hitbox Rect
--- @param position Vector2D?
--- @return AnchorComponent ...
function AnchorComponent:new(entity, hitbox, position)end

--- @param entity Engine
--- @return boolean ...
function AnchorComponent:isCollide(entity)end

--- @return Vector2D ...
function AnchorComponent:getPosition()end