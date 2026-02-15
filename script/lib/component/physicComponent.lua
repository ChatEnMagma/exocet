--- @class PhysicComponent
PhysicComponent = {}

--- @param entity Entity
--- @param hitbox Rect
--- @param position Vector2D?
--- @return PhysicComponent ...
function PhysicComponent:new(entity, hitbox, position) end

--- @param entity Engine
--- @return boolean ...
function PhysicComponent:isCollide(entity)end

--- @return Vector2D ...
function PhysicComponent:getPosition()end
--- @return Vector2D ...
function PhysicComponent:getVelocity()end

--- @param position Vector2D
function PhysicComponent:setPosition(position)end
--- @param velocity Vector2D
function PhysicComponent:setVelocity(velocity)end