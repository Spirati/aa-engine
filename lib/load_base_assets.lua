local fs = require "lib/fs"

local glyphs = fs.gameSettings.glyphs or "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!?.☞「」()『』\"↓↑:+,/*'_˖。%‥~《》&☆♪- "

local assets = {
    ui = {
        textbox = fs.loadImage("ui/textbox"),
        textbox_name = fs.loadImage("ui/textbox_name"),
    },
    sfx = {
        blip_low = fs.loadSFX("sfx/bliplow"),
        blip_high = fs.loadSFX("sfx/bliphigh")
    },
    font = {
        text = fs.loadFont("font/text", glyphs),
        name = love.graphics.newFont(8)
    }
}

assets.ui.wait_arrow = {animIndex = 0}
assets.ui.wait_arrow.array, assets.ui.wait_arrow.length = fs.sliceGridImage("ui/wait_arrow", 16, 16)

assets.sfx.blip_low:setVolume(0.5)

return assets