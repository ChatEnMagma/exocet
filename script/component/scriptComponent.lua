--- @class ScriptComponent
ScriptComponent = {
    tag = "script",
    ---@type function|nil
    update = nil,
    ---@type function|nil
    render = nil,
}
ScriptComponent.__index = ScriptComponent

--- @overload fun():ScriptComponent
--- @param updateFun function|nil
--- @param renderFun function|nil
--- @return ScriptComponent
function ScriptComponent:new(updateFun, renderFun)
    local c = {}

    setmetatable(c, ScriptComponent)

    c.tag = "script"
    c.update = updateFun
    c.render = renderFun

    return c
end