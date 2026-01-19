--- @class Rect
Rect = {
    x = 0,
    y = 0,
    w = 0,
    h = 0
}
Rect.__index = Rect

--- @overload fun(): Rect
--- @overload fun(h, w:integer, h:integer): Rect
--- @param x integer
--- @param y integer
--- @param w integer
--- @param h integer
function Rect:new(x, y, w, h)
    local r = {}

    setmetatable(r, Rect)
    if (w == nil) and (h == nil) then
        w = x
        h = y
        x = 0
        y = 0
    end
    r.x = x
    r.y = y
    r.w = w
    r.h = h

    return r
end

function Rect:__tostring()
    return "(x: " .. self.x .." ; y: " .. self.y .. " ; w: " .. self.w .." ; h: " .. self.h ..")"
end


return Rect