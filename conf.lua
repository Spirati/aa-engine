function love.conf(t)
    t.identity = "Visn"

    t.console = true

    t.version = "11.3"
    t.accelerometerjoystick = false
    t.window.title = "Visn Demo"
    
    t.modules.data = false
    t.modules.physics = false
    t.modules.thread = false
    t.modules.video = false
end