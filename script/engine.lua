--- Engine class makes link between C-engine and Lua-engine
--- @class Engine
engine = {
    --- The C pointer from Handler
    --- @private
    --- @type integer
    _handler = nil,
    --- The current state
    --- @type integer
    state = 0
}

--- @private
--- @param handler integer The C pointer from Handler
function engine.setHandler(handler)
    engine._handler = handler
end

--- Close the window game
function engine.closeGame()
    engine.cCloseGame(engine._handler)
end

--- Add a new entity
--- @param entity any The entity will add
function engine.addEntity(entity)
    engine.cAddEntity(engine._handler, entity)
end

--- Get the position of the camera, i.e the offset
--- @return Vector2D
function engine.getCameraPosition()
    local x, y = engine.cGetCameraPosition(engine._handler)
    return Vector2D:new(x, y)
end

--- Set the camera on the entity
--- @param entity Entity The entity will center
function engine.centerOnEntity(entity)
    engine.cCenterOnEntity(engine._handler, entity._ptr)
end

--- Get the window frame width
---@return integer
function engine.getWinWidth()
    return engine.cHandlerGetWinWidth(engine._handler)
end

--- Get the window frame height
---@return integer
function engine.getWinHeight()
    return engine.cHandlerGetWinHeight(engine._handler)
end

--- Get boolean if the key is pressing
---@return boolean
function engine.getKey(scancode)
    return engine.cHandlerGetKey(engine._handler, scancode)
end

--- Get the scancode is pressing
---@return integer
function engine.getKeyCode()
    return engine.cHandlerGetKeyCode(engine._handler)
end

return engine