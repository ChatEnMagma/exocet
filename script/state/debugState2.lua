--- @class DebugState
debugState2 = {
    tag = "debugState2",

    init = function ()
        local e = Wall:new(Vector2D:new(0, 0))
        engine.centerOnEntity(e)
    end,

    update = function ()
        if engine.getJustKey(SDL.SDLK_R) then engine.restart() end
        if engine.getJustKey(SDL.SDLK_N) then engine.setState(0) end
    end
}