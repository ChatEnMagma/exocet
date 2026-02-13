--- @class DebugState
debugState = {
    tag = "debugState",

    init = function ()
        local sprite = engine:getSprite("exocet", "exocet_anim.png", 7, 1, 32, 32, 7)

        local e = Player:new(Vector2D:new(0, 0))

        engine:addEntity(e)
        engine:addEntity(Wall:new(Vector2D:new(32, 64)))
    end,

    update = function ()
        if engine:getJustKey(SDL.SDLK_R) then engine:restart() end
    end
}