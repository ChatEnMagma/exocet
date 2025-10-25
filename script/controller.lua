--- @class Controller
controller = {
    players = {
        { -- first player
            keyboard = {
                tag = "keyboard",
                down = SDL.SDLK_S
            }
        }
    }
}
controller.__index = controller

--- @private
--- @param player integer number of player
--- @return Vector2D
function controller.handleDirectionKeyboard(player)
    local dx = 0
    local dy = 0

    if engine.getKey(controller.players[player].keyboard.down) then
            dx = 1
    end
    return Vector2D(math.cos(dx), math.sin(dy))
end

--- @param player integer The index of player controls
--- @return Vector2D
function controller.getDirection(player)
    local dir = Vector2D:new(0, 0)

    for key, val in controller.players do
        if val.tag == "keyboard" then
            dir = controller.handleDirectionKeyboard(player)
        end
    end

    return dir
end