local entities = require("entities")
local engine = require("engine")

local player = entities.Player:new()
player:setUpdateScript(
    function ()
        -- print("state: menuState ; player_ptr: ", player.entity._ptr, player.entity:getPosition(), engine.getWinWidth())
        if engine.getKey(117) then
            player.entity:setPosition(0, 0)
        end
    end
)

state = {
    tag = "menuState",
    
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
        player
    }
}