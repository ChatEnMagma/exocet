--- @class DebugState
debugState = {
    tag = "debugState",

    init = function ()
        TileBuilder:new(5, 5)
            :addLine(0, 0, 0, 0, 0)
            :addLine(0, 2, 0, 0, 1)
            :addLine(0, 0, 1, 0, 0)
            :addLine(0, 0, 0, 0, 0)
            :addLine(0, 0, 0, 0, 1)
        :settupTiles()

        engine.setSizeTile(32)

        --- @type Sprite
        local backgroundSprite = engine.getSprite("background", "plage_background.jpg")
        engine.getBackground():setSize(backgroundSprite:getWidth(), backgroundSprite:getHeight())
        engine.getBackground():append(backgroundSprite)

        engine.addEntity(Player:new(Vector2D:new(0, 0)))
        engine.addEntity(Wall:new(Vector2D:new(500, 0)))
        engine.addEntity(Box:new(Vector2D:new(128, 0)))

        --[[for i = 1,10000,1 do
            engine.addEntity(Box:new(Vector2D:new(i * 500, 500)))
            engine.addEntity(Wall:new(Vector2D:new(500, 500)))
        end ]]

        print("test")
    end,

    update = function ()
        if engine.getJustKey(SDL.SDLK_R) then engine.restart() end
    end,

    render = function ()
        
    end
}