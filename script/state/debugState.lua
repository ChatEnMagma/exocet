local entities = require("entities")

local player = entities.Player:new()

player:setUpdateScript(
    function ()
        print("state: debugState", player.entity._ptr)
    end
)

state = {
    tag = "debugState",
    
    entities = {
        {
            tag = "wall",
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
        {
            tag = "wall2",
            components = {
                {
                    tag = "physic",
                    position = {
                        x = 100,
                        y = 56
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