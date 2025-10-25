--- @class MenuState
menuState = {
    tag = "menuState",

    background = {
        size = {
            w = engine.getWinWidth(),
            h = engine.getWinHeight()
        },
        textures = {
            {
                path = "plage_background.jpg",
                zindex = 0,
                postion = {
                    x = 0,
                    y = 0
                }
            }
        }
    },

    uis = {
        {
            entity = Entity:new("player_button"),
            components = {
                {
                    tag = "button",
                    rect = {
                        x = engine.getWinWidth() // 2 - 128 // 2,
                        y = engine.getWinHeight() // 2 - 64 // 2,
                        w = 128,
                        h = 64
                    },
                    func = function ()
                        engine.setState(1)
                    end
                },
                {
                    tag = "script",
                    render = function ()
                        local pos = Vector2D:new(engine.getWinWidth() // 2 - 128 // 2, engine.getWinHeight() // 2 - 64 // 2)
                        engine.setColor(0, 0, 0, 0xFF)
                        engine.renderAnchorRect(pos, 128, 64)
                        engine.setColor(0xff, 0xff, 0xff, 0xff)
                        engine.renderText(pos.x, pos.y, 128, 64, "JOUER")
                    end
                }
            }
        },
        {
            entity = Entity:new("quit_button"),
            components = {
                {
                    tag = "button",
                    rect = {
                        x = engine.getWinWidth() - 128,
                        y = engine.getWinHeight() - 64,
                        w = 128,
                        h = 64
                    },
                    func = function ()
                        engine.closeGame()
                    end
                },
                {
                    tag = "script",
                    render = function ()
                        local pos = Vector2D:new(engine.getWinWidth() - 128, engine.getWinHeight() - 64 )
                        engine.setColor(0, 0, 0, 0xFF)
                        engine.renderAnchorRect(pos, 128, 64)
                        engine.setColor(0xff, 0xff, 0xff, 0xff)
                        engine.renderText(pos.x, pos.y, 128, 64, "QUIT")
                    end
                }
            }
        }
    }
}