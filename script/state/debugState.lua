--- @class DebugState
debugState = {
    tag = "debugState",

    init = function ()
        -- engine:getSprite("exocet_anim.png", "exocet", Rect:new(7, 1, 32, 32), 7, 10)
    end,

    update = function ()
        if engine:getJustKey(SDL.SDLK_R) then engine:restart() end
    end,

    entities = {
        Player:new(),
        Wall:new(Vector2D:new(32, 32))
    }
}