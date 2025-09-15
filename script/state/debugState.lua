state = {
    tag = "menuState",
    
    entities = {
        {
            tag = "player",
            components = {
                {
                    tag = "player",
                    position = {
                        x = 67,
                        y = 10
                    },
                    hitbox = {
                        x = 0,
                        y = 0,
                        w = 64,
                        h = 64
                    }
                }
            }
        },
        {
            tag = "wall",
            components = {
                {
                    tag = "physic",
                    position = {
                        x = -64,
                        y = -64
                    },
                    hitbox = {
                        x = 0,
                        y = 0,
                        w = 64,
                        h = 450
                    },
                    masse = 999.9
                }
            }
        },
        {
            tag = "wall2",
            components = {
                {
                    tag = "physic",
                    position = {
                        x = -64,
                        y = 500
                    },
                    hitbox = {
                        x = 0,
                        y = 0,
                        w = 720,
                        h = -64
                    },
                    masse = 999.9
                }
            }
        },
        {
            tag = "ball",
            components = {
                {
                    tag = "physic",
                    position = {
                        x = 100,
                        y = 100
                    },
                    hitbox = {
                        x = 0,
                        y = 0,
                        w = 32,
                        h = 32
                    },
                    color = { 0x00, 0xff, 0xff }
                }
            }
        },
    }
}