local entities = require("entities")

--- @class Player
local player = entities.Player:new()
player:setUpdateScript(
    function ()
        player:update()
    end
)

state = {
    tag = "menuState",
    
    entities = {
        {
            entity = Entity:new("wall"),

            components = {
                {
                    tag = "physic",
                    position = {
                        x = -64,
                        y = -64
                    },
                    hitbox = {
                        x = 0,
                        y = 0,
                        w = 64,
                        h = 450
                    },
                    masse = 999.9
                }
            }
        },
        player
    }
}