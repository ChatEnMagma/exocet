--- @class ParticleComponent
ParticleComponent = {
    tag = "particle",
    --- @type Vector2D
    position = nil,
    --- @type Vector2D|nil
    velocity = nil,
    --- @type integer
    time = nil
}
ParticleComponent.__index = ParticleComponent

--- @param time integer
--- @param position Vector2D
--- @param velocity Vector2D|nil
--- @return ParticleComponent
function ParticleComponent:new(time, position, velocity)
    --- @type ParticleComponent
    local c = setmetatable({}, ParticleComponent)

    c.tag = "particle"
    c.time = time
    c.position = position
    c.velocity = velocity

    return c
end