--- Background from the state
--- @class Background
Background={}
--- Add a sprite into background
--- @param sprite Sprite
--- @param zindex integer?
function Background:append(sprite, zindex)end
--- @return Vector2D ...
function Background:getPosition()end
--- @return integer ...
function Background:getWidth()end
--- @return integer ...
function Background:getHeight()end
--- @param width integer
--- @param height integer
function Background:setSize(width, height)end