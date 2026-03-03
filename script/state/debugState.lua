--- @class DebugState
debugState = {
    tag = "debugState",

    init = function ()
        local backgroundSprite = engine:getSprite("background", "/plage_background.jpg")
        engine:getBackground():setSize(backgroundSprite:getWidth(), backgroundSprite:getHeight())
        engine:getBackground():append(backgroundSprite)

        engine:addEntity(Player:new(Vector2D:new(0, 0)))
        -- engine:addEntity(Wall:new(Vector2D:new(32, 64)))
         engine:addEntity(Box:new(Vector2D:new(128, 0)))
    end,

    update = function ()
        if engine:getJustKey(SDL.SDLK_R) then engine:restart() end
    end
}