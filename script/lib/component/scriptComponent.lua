--- @class ScriptComponent
ScriptComponent = {}

--- @overload fun(ScriptComponent, entity:Entity, update: function):ScriptComponent
--- @param entity Entity
--- @param initFun function
--- @param updateFun function
--- @param renderFun function?
--- @return ScriptComponent ...
function ScriptComponent:new(entity, initFun, updateFun, renderFun) end