--- @class MenuState
menuState = {
    tag = "menuState",

    highscore = 0,
    
    init = function ()
        local file = io.open("save.json", "r")
        if file == nil then
            return
        end
        local content = file:read("*a")
        file:close()
        local config = json.decode(content)
        menuState.highscore = config["highscore"]
    end,

    update = function ()
        engine.setBackgroundSize(Rect:new(engine.getWinWidth(), engine.getWinHeight()))
    end,

    background = {
        size = Rect:new(engine.getWinWidth(), engine.getWinHeight()),
        textures = {
            {
                path = "plage_background.jpg",
                zindex = 0,
                postion = Vector2D:new()
            }
        }
    },

    uis = {
        {
            entity = Entity:new("player_button"),
            components = {
                ButtonComponent:new(
                    Rect:new(
                        engine.getWinWidth() // 2 - 128 // 2,
                        engine.getWinHeight() // 2 - 64 // 2,
                        128,
                        64
                    ),
                    function () engine.setState(1) end
                ),
                ScriptComponent:new(
                    function ()
                        menuState.uis[1].entity:setRect(Rect:new( engine.getWinWidth() // 2 - 128 // 2, engine.getWinHeight() // 2 - 64 // 2, 128, 64))
                    end,
                    function ()
                        local pos = menuState.uis[1].entity:getPosition()
                        engine.setColor(0, 0, 0, 0xFF)
                        engine.renderAnchorRect(pos, 128, 64)
                        engine.renderText(0, 0, 259, 32, tostring(menuState.highscore))
                        engine.setColor(0xff, 0xff, 0xff, 0xff)
                        engine.renderText(pos.x, pos.y, 128, 64, "JOUER")
                    end
                )
            }
        },
        {
            entity = Entity:new("quit_button"),
            components = {
                ButtonComponent:new(
                    Rect:new(
                        engine.getWinWidth() - 128,
                        engine.getWinHeight() - 64,
                        128,
                        64
                    ),
                    function () engine.closeGame() end
                ),
                ScriptComponent:new(
                    function ()
                        menuState.uis[2].entity:setRect(Rect:new(engine.getWinWidth() - 128, engine.getWinHeight() - 64, 128, 64))
                    end,
                    function ()
                        local pos = menuState.uis[2].entity:getPosition()
                        engine.setColor(0, 0, 0, 0xFF)
                        engine.renderAnchorRect(pos, 128, 64)
                        engine.setColor(0xff, 0xff, 0xff, 0xff)
                        engine.renderText(pos.x, pos.y, 128, 64, "QUIT")
                    end
                )
            }
        }
    }
}