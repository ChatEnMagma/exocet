--- @class Rain
Rain = {
    ---@type Entity
    entity = nil,
    components = {}
}
Rain.__index = Rain

---@param position Vector2D
---@param velocity Vector2D
---@return Rain
function Rain:new(position, velocity)
    --- @type Rain
    local e = setmetatable({}, Rain)

    e.entity = Entity:new("rain")
    e.components = {
        ParticleComponent:new(10, position, velocity),
        SpriteComponent:new("jetpack.png")
    }

    return e
end

return Rain