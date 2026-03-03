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
function PhysicComponent:getAcceleration()end
--- @return number ...
function PhysicComponent:getMasse()end
--- @return Vector2D ...
function PhysicComponent:getPosition()end
--- @return Vector2D ...
function PhysicComponent:getVelocity()end
--- @return Vector2D ...
function PhysicComponent:getFriction()end
--- @return Vector2D ...
function PhysicComponent:getSpeed()end
--- @return Vector2D ...
function PhysicComponent:getMaxSpeed()end

--- @param acceleration Vector2D
function PhysicComponent:setAcceleration(acceleration)end
--- @param masse number
function PhysicComponent:setMasse(masse)end
--- @param position Vector2D
function PhysicComponent:setPosition(position)end
--- @param velocity Vector2D
function PhysicComponent:setVelocity(velocity)end
--- @param friction Vector2D
function PhysicComponent:setFriction(friction)end
--- @param speed Vector2D
function PhysicComponent:setSpeed(speed)end
--- @param maxSpeed Vector2D
function PhysicComponent:setMaxSpeed(maxSpeed)end