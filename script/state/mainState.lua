local EntityGen = {
    entity = Entity:new("cloud_gen"),
    components = {
        {
            tag = "script",
        }
    },

    nextCloud = 0,
    nextOxy = 0,
    nextBird = 0,
    nextWave = 0
}
EntityGen.__index = EntityGen

function EntityGen:new()
    local e = {}
    setmetatable(e, EntityGen)

    e.entity = Entity:new("gen")

    return e
end

function EntityGen:update() 
    if engine.mainEntities.player.gameover then
        return
    end

    if self.nextCloud <= 0 then
        local pos = Vector2D:new(
            engine.getWinWidth(),
            math.min(
                math.random(0, 800),
                math.random(
                    engine.getCameraPosition().y - engine.getWinHeight() / 2, 
                    engine.getCameraPosition().y + engine.getWinHeight() + engine.getWinHeight() / 2
                )
            )
        )

        local c = Cloud:new(pos)
        
        c.components[2]["update"] = function ()
            c:update()
        end

        
        engine.addEntity(c)
        
        if engine.mainEntities.player.entity:getPosition().y >= 850 then
            self.nextCloud = math.random(30, 100)
        else 
            self.nextCloud = math.random(100, 250)
        end
    end

    if self.nextOxy <= 0 then
        local pos = Vector2D:new(
            engine.getWinWidth(),
            math.min(
                800,
                math.random(engine.getCameraPosition().y, engine.getCameraPosition().y + engine.getWinHeight())
            )
        )

        local o = Oxygen:new(pos)
        
        o.components[2]["update"] = function ()
            o:update()
        end
        
        engine.addEntity(o)

        self.nextOxy = math.random(1000, 5000)
    end

    if (self.nextBird <= 0) and (engine.mainEntities.player.entity:getPosition().y <= 1000) then
        local pos = Vector2D:new(
            engine.getWinWidth(),
            math.min(
                800,
                math.random(engine.getCameraPosition().y, engine.getCameraPosition().y + engine.getWinHeight())
            )
        )

        local e = Bird:new(pos)
        
        e.components[2]["update"] = function ()
            e:update()
        end
        
        engine.addEntity(e)

        self.nextBird = math.random(110, 1000)
    end

    if self.nextWave <= 0 then
        local pos = Vector2D:new(
            engine.getWinWidth(),
            1000 - 100
        )

        local e = Wave:new(pos)
        
        e.components[2]["update"] = function ()
            e:update()
        end
        
        engine.addEntity(e)

        self.nextWave = math.random(110, 300)
    end

    self.nextCloud = self.nextCloud - 1
    self.nextOxy = self.nextOxy - 1
    self.nextBird = self.nextBird - 1
    self.nextWave = self.nextWave - 1

    if mainState.score >= mainState.nextPalier then
        mainState.vx = mainState.vx - 1
        mainState.nextPalier = mainState.nextPalier + 15
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
    mainState.score = 1
    mainState.nextPalier = 10
    mainState.vx = -5

    mainState.background.textures[1].postion.y = -2000

    local player = Player:new()
    player:setUpdateScript(function ()
        player:update()
    end)

    engine.mainEntities.player = player

    local entitygen = EntityGen:new()
    entitygen.components[1].update = function ()
        entitygen:update()
    end

    mainState.entities = {
        player,
        entitygen,
        {
            entity = Entity:new("limite"),
            components = {
                {
                    tag = "physic",
                    position = {
                        x = -engine.getWinWidth(),
                        y = 1000
                    },
                    hitbox = {
                        x = 0,
                        y = 0,
                        w = engine.getWinWidth() * 2,
                        h = 1684
                    }
                },
                {
                    tag = "sprite",
                    path = "mer.png",
                    fitSizeWithHitbox = true
                }
            }
        },
    }

    local score = {
        entity = Entity:new("score_ui"),
        components = {
            {
                tag = "ui",
            },
            {
                tag = "script",
                render = function ()
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
            }
        }
    }
    mainState.uis[1] = score

    --mainState.entities[1]:setUpdateScript(function() mainState.entities[1]:update() end)
end