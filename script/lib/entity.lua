--- Class Entity has essential functions
--- @class Entity
--- @field components Components[]
--- @field data table
Entity = {}
Entity.__index = Entity

--- @param tag string
--- @return Entity ...
function Entity:new(tag) end