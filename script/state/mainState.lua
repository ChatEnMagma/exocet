--- @class MainState
mainState = {
    tag = "mainState",

    score = 1,
    nextPalier = 10,
    vx = -3.0,
    seaLevel = 1000,
    step = 0,

    init = nil,
    update = function ()
        mainState:updateGeneration()

        if engine.mainEntities.player.entity:getPosition().y >= 0 then

            local vol = (engine.mainEntities.player.entity:getPosition().y * 128) // 4000

            if engine.isPlayingSong("sea_wave.wav") == false then
                engine.playSong("sea_wave.wav")
            end

            engine.setVolume("sea_wave.wav", vol)
        else
            engine.setVolume("sea_wave.wav", 0)
        end
    end,

    background = {
        size = Rect:new(5360 * 2, 3015),
        textures = {
            {
                path = "backgroundchunk.png",
                zindex = 0,
                postion = Vector2D:new()
            }
        },
        loop = true
    },
    uis = {},
    entities = {}
}

mainState.init = function ()
    math.randomseed(os.time(), os.time() - 100)

    engine.setSong("alarm_boat.wav")
    engine.setSong("plouf.wav")
    engine.setSong("sea_wave.wav")
    engine.setSong("whoosh0.wav")
    engine.setSong("whoosh1.wav")

    mainState.score = 1
    mainState.nextPalier = 10
    mainState.vx = -3.0
    mainState.step = 0
    
    mainState.background.textures[1].postion.y = -2000

    local player = Player:new()

    engine.mainEntities.player = player

    mainState.entities = {
        player,
        {
            entity = Entity:new("limite"),
            components = {
                PhysicComponent:new(Rect:new(engine.getWinWidth()*2, 1684), Vector2D:new(-engine.getWinWidth(), mainState.seaLevel)),
                SpriteComponent:new("mer.png"),
                ScriptComponent:new(function ()
                    mainState.entities[2].entity:setRect(Rect:new(engine.getWinWidth() * 2, 1684))
                end)
            }
        },
    }

    local score = {
        entity = Entity:new("score_ui"),
        components = {
            {
                tag = "ui",
            },
            ScriptComponent:new(nil, function ()
                    engine.setColor(0x77, 0x77, 0x77, 0xFF)
                    engine.renderAnchorFillRect(Vector2D:new(0, 0), engine.getWinWidth(), 80)

                    engine.setColor(0xff, 0xFF, 0xFF, 0xFF)
                    local size_score = (1 + math.floor(math.log(mainState.score, 10))) * 32

                    engine.renderText(engine.getWinWidth() // 2 - size_score, 10, size_score , 80, tostring(mainState.score))

                    if player.gameover == false then
                        engine.setColor(0xff, 0xFF, 0x00, 0xFF)
                        engine.renderText(0, 0, 64, 64, "O2: " .. player.oxygen .. "%")
                    end
                    if player.gameover then
                        engine.setColor(0xff, 0x00, 0x00, 0xFF)
                        engine.renderText(0, 0, engine.getWinWidth(), 128, "GAME OVER")
                    end
                end
            ),
        }
    }
    muteButton = {
        entity = Entity:new("button_mute"),
        components = {
            ButtonComponent:new(Rect:new(500, 0, 32, 32), function ()
                    if engine.isMuting() then
                        engine.mute() 
                    else
                        engine.unmute()
                    end
                end),
            ScriptComponent:new(nil, function ()
                engine.setColor(0xff, 0xff, 0, 0xff)
                engine.renderAnchorFillRect(muteButton.entity:getPosition(), 32, 32)
                engine.setColor(0, 0, 0, 0xff)
                engine.renderText(muteButton.entity:getPosition().x, muteButton.entity:getPosition().y, 32, 32, "MUTE")
            end)
        }
    }
    mainState.uis = {
        score,
        muteButton
    }

    --mainState.entities[1]:setUpdateScript(function() mainState.entities[1]:update() end)
end

--- @return Vector2D
function mainState.getRandomPositionScreen()
    return Vector2D:new(
            engine.getWinWidth() + 20,
            -engine.getCameraPosition().y + math.random(
                engine.getCameraPosition().y - engine.getWinHeight(),
                engine.getCameraPosition().y + engine.getWinHeight()
            )
        )
end

function mainState:updateGeneration()
    if engine.mainEntities.player.gameover then
        return
    end

    Cloud:updateHatch(self.getRandomPositionScreen())
    Oxygen:updateHatch(self.getRandomPositionScreen())
    Bird:updateHatch(self.getRandomPositionScreen())
    Wave:updateHatch()
    Items:updateHatch(self.getRandomPositionScreen())
    Liner:updateHatch()
    Ufo:updateHatch(self.getRandomPositionScreen())

    local newVx = 3.0 + self.step
    if engine.mainEntities.player.tagPower == "jetpack" then
        newVx = 3.0 + self.step + 2
    end
    mainState.vx = -newVx

    if self.step < 100 and mainState.score >= mainState.nextPalier then
        mainState.nextPalier = mainState.nextPalier + 30
        self.step = self.step + 1
    end
    engine.setBackgroundPosition(engine.getBackgroundPosition() + Vector2D:new(mainState.vx, 0))
end