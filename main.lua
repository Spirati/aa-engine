const = require "lib/const"
script = require "lib/script"
fs = {}
assets = {}

frameCount = 0

function love.load(arg)
    drawCanvas = love.graphics.newCanvas(256, 192)
    love.window.setMode(256 * const.DISPLAY_SCALE, 192 * const.DISPLAY_SCALE)

    GAME_FOLDER = "games/" .. arg[1]

    if not love.filesystem.getInfo(GAME_FOLDER) then
        print("Couldn't find that path!")
        love.event.push("quit", 0)
    end


    fs = require "lib/fs"

    assets = require "lib/load_base_assets"

    script.loadScript("main")


    gameState = const.DIALOGUE_STATE.TYPE

end

function love.update()

    frameCount = (frameCount + 1) % 65536

    if not script.inBlock then script.advance() end

    if frameCount % 10 == 0 then
        if assets.character then assets.character.animIndex = (assets.character.animIndex+1)%assets.character.length end
    end

    if frameCount % 3 == 0 then
        assets.ui.wait_arrow.animIndex = (assets.ui.wait_arrow.animIndex+1)%assets.ui.wait_arrow.length
    end

    if gameState == const.DIALOGUE_STATE.TYPE then
        if frameCount % const.TEXT_RATE == 0 then
            if script.type() then
                gameState = const.DIALOGUE_STATE.WAIT
                assets.character = {animIndex=0}                        
                assets.character.array, assets.character.length = fs.sliceGridImage("char/" .. script.character.name:lower() .. "/" .. script.character.emotion .. "(blink)")
            end
        end

    elseif gameState == const.DIALOGUE_STATE.CHOOSE then

    end

end

function love.mousepressed(x, y, button, istouch, presses)
    local buttons = {"mouse1","mouse2"}

    advanceHandler(buttons[button], {x=x, y=y})

end

function love.keypressed(key, scancode, isrepeat)
    advanceHandler(key, {x=0, y=0})
end

function advanceHandler(key, location)
    if (key == "space" or key == "return") and gameState == const.DIALOGUE_STATE.WAIT then
        if not script.advance() or #script.lines == 0 then
            love.event.push("quit", 0)
        end

        gameState = const.DIALOGUE_STATE.TYPE
        if script.talkAnimate then
            assets.character = {animIndex=0}         
            assets.character.array, assets.character.length = fs.sliceGridImage("char/" .. script.character.name:lower() .. "/" .. script.character.emotion .. "(talk)")
        end
    end
end

function love.draw()
    beginDraw()

    if assets.bg then
        love.graphics.draw(assets.bg)
    end

    if assets.character then
        love.graphics.drawLayer(assets.character.array, assets.character.animIndex+1)
    end

    if assets.fg then
        love.graphics.draw(assets.fg)
    end

    if gameState == const.DIALOGUE_STATE.TYPE or gameState == const.DIALOGUE_STATE.WAIT then
        if script.character == nil or script.character.nickname == "" then
            love.graphics.draw(assets.ui.textbox, 0, 127)
        else
            love.graphics.draw(assets.ui.textbox_name, 0, 116)
            love.graphics.printf(script.character.nickname or "", assets.font.name, 2, 118, 45, "center")
        end
    end

    if gameState == const.DIALOGUE_STATE.WAIT then
        love.graphics.drawLayer(assets.ui.wait_arrow.array, assets.ui.wait_arrow.animIndex+1, 256-17, 167)
    end

    love.graphics.printf(script.lineProgress or "", assets.font.text, 8, 127+6, 220)
    if frameCount % const.TEXT_RATE == 0 and gameState == const.DIALOGUE_STATE.TYPE and not ((script.lineProgress or ""):sub(-1) == " ") then
        assets.sfx.blip_high:play()
    end

    endDraw()
end


function beginDraw()
    love.graphics.setCanvas(drawCanvas)
    love.graphics.clear()
    drawCanvas:setFilter("nearest", "nearest")
end

function endDraw()
    love.graphics.setCanvas()
    love.graphics.draw(drawCanvas, 0, 0, 0, const.DISPLAY_SCALE, const.DISPLAY_SCALE)
end