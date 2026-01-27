--- @class Rect
Rect = {x = 0,y = 0,w = 0,h = 0}
Rect.__index = Rect
--- @overload fun(Rect): Rect
--- @overload fun(Rect, w:integer, h:integer): Rect
--- @param x integer
--- @param y integer
--- @param w integer
--- @param h integer
--- @return Rect ...
function Rect:new(x, y, w, h)end
function Rect:__tostring() end