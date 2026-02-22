--- @class Sprite
Sprite = {}

--- @param position Vector2D
--- @param width integer
--- @param height integer
--- @param frame integer?
function Sprite:render(position, width, height, frame)end
--- @param position Vector2D
--- @param width integer
--- @param height integer
--- @param frame integer?
function Sprite:renderAnchor(position, width, height, frame)end

--- @param position Vector2D
--- @param angle number
--- @param width integer
--- @param height integer
--- @param frame integer?
function Sprite:renderAngle(position, angle, width, height, frame)end
--- @param position Vector2D
--- @param angle number
--- @param width integer
--- @param height integer
--- @param frame integer?
function Sprite:renderAnchorAngle(position, angle, width, height, frame)end

--- @return integer ...
function Sprite:getWidth()end
--- @return integer ...
function Sprite:getHeight()end