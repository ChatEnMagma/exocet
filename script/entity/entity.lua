--- Class Entity has essential functions
--- @class Entity
Entity = { 
    --- The C pointer from Entity
    --- @private
    --- @type integer
    _ptr = 0,

    --- The tag of the entity, i.e. the name of entity
    --- @type string
    tag = "gen-entity"
}

Entity.__index = Entity

function Entity:__tostring()
    return "Entity: " .. string.format("%x",  self._ptr)
end

--- @param tag string
function Entity:new(tag)
    local e = setmetatable({}, Entity)
    e.tag = tag

    return e
end

--- @return integer
function Entity:getFrameAnimation()
    return Entity.cGetFrameAnimation(self._ptr)
end
---@param path string
---@param size Rect|nil
---@param frame integer|nil
function Entity:setTexture(path, size, frame)
    if frame == nil then
        frame = -1
    end
    if size == nil then
        size = Rect:new()
    end
    Entity.cSetTexture(self._ptr, path, size.x, size.y, size.w, size.h, frame)
end
--- @param angle number
function Entity:setTextureAngle(angle)
    Entity.cSetTextureAngle(self._ptr, angle)
end

--- Check if the mouse is well interact with mouse
--- @return boolean
function Entity:isInsideMouse()
    return Entity.cIsInsideMouse(self._ptr)
end
--- Check if the entity is outside of the screen
--- @return boolean
function Entity:isOutsideScreen()
    return Entity.cIsOutsideScreen(self._ptr)
end
--- Destroy the entity if it is outside of the screen
function Entity:destroyOutsideScreen()
    Entity.cDestroyOutsideScreen(self._ptr)
end
--- Get all entities are collide
--- @return table
function Entity:getCollideEntities()
    return Entity.cGetCollideEntities(self._ptr)
end
--- Set the rectangle hitbox or rect for HitboxComponent and UIComponent
--- @param rect Rect
function Entity:setRect(rect)
    Entity.cSetRect(self._ptr, rect.x, rect.y, rect.w, rect.h)
end
--- Get the rect of the entity
--- @return Rect
function Entity:getRect()
    local x, y, w, h = Entity.cGetRect(self._ptr)
    return Rect:new(x, y, w, h)
end
--- Check if the entity is well collide
--- @param entity any
--- @return boolean
function Entity:getCollideEntity(entity)
    return Entity.cGetCollideEntity(self._ptr, entity.entity._ptr)
end

--- Kill the entity
function Entity:destroy()
    self.cDestroy(self._ptr)
end

--- Fit the size of the sprite with hitbox
function Entity:fitSizeWithHitbox()
    self.cFitSizeWithHitbox(self._ptr)
end

--- Function set the pointer of CEntity
--- @private
--- @param pointer interger The C pointer from Entity
function Entity:setEntity(pointer)
    self._ptr = pointer
end

--- Function returns the position of the entity
--- @return Vector2D
function Entity:getPosition()
    local x, y = self.cGetPosition(self._ptr) -- call CFunction
    return Vector2D:new(x, y)
end

--- Function returns the velocity of the entity
--- @return Vector2D
function Entity:getVelocity()
    local x, y = self.cGetVelocity(self._ptr) -- call CFunction
    return Vector2D:new(x, y)
end

--- Set the position of the entity
--- @param vec Vector2D The new position in Vector2D with integer
function Entity:setPosition(vec)
    self.cSetPosition(self._ptr, vec.x, vec.y) -- call CFunction
end

--- Set the velocity of the entity
--- @param vec Vector2D The new velocity in Vector2D with number
function Entity:setVelocity(vec)
    self.cSetVelocity(self._ptr, vec.x, vec.y) -- call CFunction
end

--- Check if the entity is dragging
--- @return boolean
function Entity:isDragging()
    return self.cIsDragging(self._ptr)
end

--- Get the time before to die
--- @return integer
function Entity:getTime()
    return Entity.cGetTime(self._ptr)
end

return Entity