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

--===================================== ALL SUBSYS METHDOS =====================================--

--- Play a song with ticks during. You should initiate the song file before to play
--- @param path string
--- @param ticks integer|nil
function engine:playSong(path, ticks) end

--- Get the main volume
--- @param path string
--- @return integer
--- @nodiscard
function engine:getVolume(path) end

--- @param path string
--- @param volume integer between 0 to 128
function engine:setVolume(path, volume) end

--- Check if the song is playing
--- @param path string
--- @return boolean
--- @nodiscard
function engine:isPlayingSong(path) end

--- Set a song
--- @param path string the path of the song
function engine:setSong(path) end

--- Tell if the game is muting
--- @return boolean
--- @nodiscard
function engine:isMuting() end

--- Mute all the game
function engine:mute() end

--- Unmute all the game
function engine:unmute() end

--- Get the window frame width
---@return integer
---@nodiscard
function engine:getWinWidth() end

--- Get the window frame height
---@return integer
---@nodiscard
function engine:getWinHeight() end

--- Get if the window is resizing
--- @return boolean
--- @nodiscard
function engine:isResizing() end

--- Close the window game
function engine:closeGame() end

--- Get boolean if the key is pressing
---@return boolean
---@nodiscard
function engine:getKey(scancode) end

--- Get any key is pressing
--- @return boolean
--- @nodiscard
function engine:getAnyKey() end

--- @return boolean
--- @nodiscard
function engine:getJustAnyKey() end

--- Get boolean if the key is just pressing
---@return boolean
---@nodiscard
function engine:getJustKey(scancode) end

--- Get the scancode is pressing
---@return integer
---@nodiscard
function engine:getKeyCode() end

--- Get boolean if the button is pressing
---@return boolean
---@nodiscard
function engine:getButton(scancode) end

--- Get boolean if the button is just pressing
---@return boolean
---@nodiscard
function engine:getJustButton(scancode) end

--- Get the scancode is pressing
---@return integer
---@nodiscard
function engine:getButtonCode() end

--- Get the position of the mouse in the game window
--- @return Vector2D
function engine.getMousePosition()
    local x, y = engine:cGetMoustPosition(engine._handler)
    return Vector2D:new(x, y)
end

--===================================== ALL STATE METHODS ====================================--

--- Set the current state
--- @param state integer the state will state
function engine:setState(state) end

--- Get the current state
--- @return integer
--- @nodiscard
function engine:getCurrentState() end

--- Restart the state
function engine:restart() end

--- Set the next state
function engine:nextState() end

--- Set the previous state
function engine:previousState() end

--=================================== ALL GRAPHICS METHODS ===================================--

--- Set the color of graphics
--- @param red integer
--- @param green integer
--- @param blue integer
--- @param alpha integer
function engine:setColor(red, green, blue, alpha) end

--- Render a rect
--- @param position Vector2D
--- @param width integer
--- @param height integer
function engine:renderRect(position, width, height) end

--- Render a rect
--- @param position Vector2D
--- @param width integer
--- @param height integer
function engine:renderFillRect(position, width, height) end

--- Render an anchor rect
--- @param position Vector2D
--- @param width integer
--- @param height integer
function engine:renderAnchorRect(position, width, height) end

--- Render a filled anchor rect
--- @param position Vector2D
--- @param width integer
--- @param height integer
function engine:renderAnchorFillRect(position, width, height) end

--- Render text
--- @param position Vector2D
--- @param width integer
--- @param height integer
--- @param text string
function engine:renderText(position, width, height, text) end

--- @param position Vector2D
--- @param polygon Polygon
function engine:renderPolygon(position, polygon) end

--=================================== ALL CAMERA METHODS =====================================--

--- Get the position of the camera, i.e the offset
--- @return Vector2D
function engine:getCameraPosition()
    local x, y = engine:cGetCameraPosition(self._handler)
    return Vector2D:new(x, y)
end
--- Set the camera on the entity
--- @param entity Entity The entity will center
function engine:centerOnEntity(entity) end

--================================= ALL BACKGROUND METHODS ===================================--

--- Get the position of the state background
--- @return Vector2D
function engine:getBackgroundPosition()
    local x, y = engine:cGetBackgroundPosition(self._handler)
    return Vector2D:new(x, y)
end
--- Set the position of the background state
--- @param postion Vector2D The new postion
function engine:setBackgroundPosition(postion) end

--- Set the size of the background
--- @param width integer
--- @param height integer
function engine:setBackgroundSize(width, height) end

--=================================== ALL ENTITY METHODS =====================================--

--- Add a new entity
--- @param entity any The entity will add
function engine:addEntity(entity) end

return engine