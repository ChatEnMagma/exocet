config = {
    init_state = 0,

    showHitbox = true,
    showPointerEntities = true,
    logOpenLuaFiles = true,

    states = {
        "debugState",
    },

    init = function ()
       engine.addTile(engine.getSprite("tileBrique", "sheet.png", 0, 0, 32, 32), 0)
       engine.addTile(engine.getSprite("tileWall", "sheet.png", 1, 0, 32, 32), 0)

       print("Success to initiate the config game")
    end
}