local entities = require("entities")

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
    tag = "debugState",
    
    init = function ()
        print("debug state")    
    end,

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
                },
                {
                    tag = "sprite",
                    path = "realexocet.png",
                    fitSizeWithHitbox = true
                }
            }
        },
        {
            entity = Entity:new("wall2"),
            
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