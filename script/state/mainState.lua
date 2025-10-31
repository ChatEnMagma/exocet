local EntityGen = {
    components = {
        {
            tag = "script",
        }
    },

    nextCloud = 0,
    nextOxy = 0,
    nextBird = 0,
    nextWave = 0,
    nextItem = 0,
    step = 0
}
EntityGen.__index = EntityGen

--- @return Vector2D
function EntityGen.getRandomPositionScreen()
    return Vector2D:new(
            engine.getWinWidth() + 20,
            -engine.getCameraPosition().y + math.random(engine.getCameraPosition().y, engine.getCameraPosition().y + engine.getWinHeight())
        )
end

function EntityGen:genCloud()
    if self.nextCloud <= 0 then
        local c = Cloud:new(self.getRandomPositionScreen())
        
        engine.addEntity(c)
        
        if engine.mainEntities.player.entity:getPosition().y >= 500 then
            self.nextCloud = math.random(30, 100)
        else 
            self.nextCloud = math.random(100 + self.step, 250 + self.step)
        end
    end

    self.nextCloud = self.nextCloud - 1
end
function  EntityGen:genOxy()
    if self.nextOxy <= 0 then
        local o = Oxygen:new(self.getRandomPositionScreen())
        
        engine.addEntity(o)
        local playerPos = engine.mainEntities.player.entity:getPosition()
        if playerPos.y < 500 then
            self.nextOxy = math.random(100 + self.step, 300 + self.step)
        else
            self.nextOxy = math.random(400 + self.step, 1000 + self.step)
        end
    end
    
    self.nextOxy = self.nextOxy - 1
end
function EntityGen:genBird()
    local playerPos = engine.mainEntities.player.entity:getPosition()

    if (mainState.score > 10) and (self.nextBird <= 0) and (playerPos.y <= 500) then
        local e = Bird:new(self.getRandomPositionScreen())
        
        engine.addEntity(e)
        if(playerPos.y <= 500) then
            self.nextBird = math.random(110, 1000)
        else
            self.nextBird = math.random(50, 500)
        end
    end

    self.nextBird = self.nextBird - 1
end
function EntityGen:genWave()
    if self.nextWave <= 0 then
        local pos = Vector2D:new(
            engine.getWinWidth(),
            1000 - 100
        )

        local e = Wave:new(pos)
        
        engine.addEntity(e)

        self.nextWave = math.random(300 + self.step, 1000 + self.step)
    end

    self.nextWave = self.nextWave - 1
end

function EntityGen:genItems()
    if self.nextItem <= 0 then
        local e = Items:new(EntityGen.getRandomPositionScreen())
        
        engine.addEntity(e)

        self.nextItem = math.random(110 + self.step, 300 + self.step)
    end

    self.nextItem = self.nextItem - 1
end

function EntityGen:update() 
    if engine.mainEntities.player.gameover then
        return
    end

    self:genCloud()
    self:genOxy()
    self:genBird()
    self:genWave()
    self:genItems()

    if mainState.score >= mainState.nextPalier then
        mainState.vx = mainState.vx - 1
        mainState.nextPalier = mainState.nextPalier + 15
        self.step = (mainState.score % mainState.nextPalier) * 2
    end


    engine.setBackgroundPosition(engine.getBackgroundPosition() + Vector2D:new(mainState.vx, 0))
end


--- @class MainState
mainState = {
    tag = "mainState",

    score = 1,
    nextPalier = 10,
    vx = -5,

    init = nil,
    update = function ()
        EntityGen:update()
        
        if engine.mainEntities.player.entity:getPosition().y >= 0 then

            local vol = (engine.mainEntities.player.entity:getPosition().y * 128) // 1000

            if engine.isPlayingSong("sea_wave.wav") == false then
                engine.playSong("sea_wave.wav")
            end

            engine.setVolume("sea_wave.wav", vol)
        else
            engine.setVolume("sea_wave.wav", 0)
        end
    end,

    background = {
        size = {
            w = 5360,
            h = 3015
        },
        textures = {
            {
                path = "plage_background.jpg",
                zindex = 0,
                postion = {
                    x = 0,
                    y = -2000
                }
            }
        },
        loop = true
    },
    uis = {},
    entities = {}
}

mainState.init = function ()
    math.randomseed(os.time(), os.time() - 100)

    engine.setSong("plouf.wav")
    engine.setSong("whoosh0.wav")
    engine.setSong("whoosh1.wav")
    engine.setSong("sea_wave.wav")

    mainState.score = 1
    mainState.nextPalier = 10
    mainState.vx = -5

    mainState.background.textures[1].postion.y = -2000

    local player = Player:new()

    engine.mainEntities.player = player

    mainState.entities = {
        player,
        {
            entity = Entity:new("limite"),
            components = {
                PhysicComponent:new({ x=0,y=0,w=engine.getWinWidth()*2,h=1684}, Vector2D:new(-engine.getWinWidth(), 1000)),
                SpriteComponent:new("mer.png")
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
            ButtonComponent:new(Rect:new(500, 0, 32, 32), function () print("test") engine.mute() end),
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