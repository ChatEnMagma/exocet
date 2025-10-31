--- @class ButtonComponent
ButtonComponent = {
    tag = "button",
    --- @type Rect
    rect = {},
    --- @type function
    func = nil
}
ButtonComponent.__index = ButtonComponent

--- @param rect Rect
--- @param func function
--- @return ButtonComponent
function ButtonComponent:new(rect, func)
    local c = {}

    setmetatable(c, ButtonComponent)

    c.tag = "button"
    c.rect = rect
    c.func = func

    return c
end

return ButtonComponent