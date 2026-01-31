--- @class DebugState
debugState = {
    tag = "debugState",

    update = function ()
        if engine:getJustKey(SDL.SDLK_R) then engine:restart() end
    end,

    entities = {
        Player:new(),
        Wall:new(Vector2D:new(32, 32))
    }
}