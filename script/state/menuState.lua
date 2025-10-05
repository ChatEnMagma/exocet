local entities = require("entities")

--- @class Player
local player = Player:new()
player:setUpdateScript(
    function ()
        player:update()
    end
)

engine.mainEntities = {
    player = player
}

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
        player,
        {
            entity = Entity:new("wall3"),
            
            components = {
                {
                    tag = "physic",
                    position = {
                        x = 0,
                        y = 100
                    },
                    hitbox = {
                        x = 0,
                        y = 0,
                        w = 64,
                        h = 450
                    },
                    masse = 999.9
                },
                {
                    tag = "sprite",
                    path = "realexocet.png",
                    fitSizeWithHitbox = true
                }
            }
        },
    }
}