--- Engine class makes link between C-engine and Lua-engine
--- @class Engine
engine = {
    --- The C pointer from Handler
    --- @private
    --- @type integer
    _handler = nil,
    --- The current state
    --- @type integer
    state = 0,
    mainEntities = {}
}

--- @private
--- @param handler integer The C pointer from Handler
function engine.setHandler(handler)
    engine._handler = handler
end

--===================================== ALL SUBSYS METHDOS =====================================--

--- Play a song with ticks during. You should initiate the song file before to play
--- @param path string
--- @param ticks integer|nil
function engine.playSong(path, ticks)
    if ticks == nil then ticks = -1 end
    engine.cPlaySong(engine._handler, path, ticks)
end
--- @param path string
--- @return integer
function engine.getVolume(path)
    return engine.cGetVolume(engine._handler, path)
end
--- @param path string
--- @param volume integer between 0 to 128
function engine.setVolume(path, volume)
    engine.cSetVolume(engine._handler, path, volume)
end
--- Check if the song is playing
--- @param path string
function engine.isPlayingSong(path)
    return engine.cIsPlayingSong(engine._handler, path)
end
--- @param path string
function engine.setSong(path)
    engine.cSetSong(engine._handler, path)
end
function engine.mute()
    engine.cMute(engine._handler)
end
function engine.unmute()
    engine.cUnmute(engine._handler)
end
function engine.isMuting()
    return engine.cIsMuting(engine._handler)
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
--- Close the window game
function engine.closeGame()
    engine.cCloseGame(engine._handler)
end
--- Get boolean if the key is pressing
---@return boolean
function engine.getKey(scancode)
    return engine.cHandlerGetKey(engine._handler, scancode)
end
--- Get any key is pressing
--- @return boolean
function engine.getAnyKey()
    return engine.cHandlerGetAnyKey(engine._handler)
end
--- Get boolean if the key is just pressing
---@return boolean
function engine.getJustKey(scancode)
    return engine.cHandlerGetJustKey(engine._handler, scancode)
end
--- Get the scancode is pressing
---@return integer
function engine.getKeyCode()
    return engine.cHandlerGetKeyCode(engine._handler)
end
--- Get boolean if the button is pressing
---@return boolean
function engine.getButton(scancode)
    return engine.cHandlerGetButton(engine._handler, scancode)
end
--- Get boolean if the button is just pressing
---@return boolean
function engine.getJustButton(scancode)
    return engine.cHandlerGetJustButton(engine._handler, scancode)
end
--- Get the scancode is pressing
---@return integer
function engine.getButtonCode()
    return engine.cHandlerGetButtonCode(engine._handler)
end
--- Get the position of the mouse in the game window
--- @return Vector2D
function engine.getMousePosition()
    local x, y = engine.cGetMoustPosition(engine._handler)
    return Vector2D:new(x, y)
end

--===================================== ALL STATE METHODS ====================================--

--- Set the current state
--- @param state integer the state will state
function engine.setState(state)
    engine.cSetState(engine._handler, state)
end
--- Get the current state
--- @return integer
function engine.getCurrentState()
    return engine.cGetCurrentState(engine._handler)
end
--- Restart the state
function engine.restart()
    engine.cRestart(engine._handler)
end
--- Set the next state
function engine.nextState()
    engine.cNextState(engine._handler)
end
--- Set the previous state
function engine.previousState()
    engine.cPreviousState(engine._handler)
end

--=================================== ALL GRAPHICS METHODS ===================================--

--- Set the color of graphics
--- @param red integer
--- @param green integer
--- @param blue integer
--- @param alpha integer
function engine.setColor(red, green, blue, alpha)
    engine.cSetColor(engine._handler, red, green, blue, alpha)
end
--- Render a rect
--- @param position Vector2D
--- @param width integer
--- @param height integer
function engine.renderRect(position, width, height)
    engine.cRenderRect(engine._handler, position.x, position.y, width, height)
end
--- Render a rect
--- @param position Vector2D
--- @param width integer
--- @param height integer
function engine.renderFillRect(position, width, height)
    engine.cRenderFillRect(engine._handler, position.x, position.y, width, height)
end
--- Render an anchor rect
--- @param position Vector2D
--- @param width integer
--- @param height integer
function engine.renderAnchorRect(position, width, height)
    engine.cRenderAnchorRect(engine._handler, position.x, position.y, width, height)
end
--- Render a filled anchor rect
--- @param position Vector2D
--- @param width integer
--- @param height integer
function engine.renderAnchorFillRect(position, width, height)
    engine.cRenderAnchorFillRect(engine._handler, position.x, position.y, width, height)
end
--- Render text
--- @param xpos integer
--- @param ypos integer
--- @param width integer
--- @param height integer
--- @param text string
function engine.renderText(xpos, ypos, width, height, text)
    engine.cRenderText(engine._handler, xpos, ypos, width, height, text)
end


--=================================== ALL CAMERA METHODS =====================================--

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

--================================= ALL BACKGROUND METHODS ===================================--

--- Get the position of the state background
--- @return Vector2D
function engine.getBackgroundPosition() 
    local x, y = engine.cGetBackgroundPosition(engine._handler)
    return Vector2D:new(x, y)
end
--- Set the position of the background state
--- @param postion Vector2D The new postion
function engine.setBackgroundPosition(postion) 
    engine.cSetBackgroundPosition(engine._handler, postion.x, postion.y)
end

--=================================== ALL ENTITY METHODS =====================================--

--- Add a new entity
--- @param entity any The entity will add
function engine.addEntity(entity)
    engine.cAddEntity(engine._handler, entity)
end

return engine