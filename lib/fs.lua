local fs = {}


if GAME_FOLDER then
    fs.gameSettings = require(GAME_FOLDER .. "/game_conf") or {}
else
    fs.gameSettings = {}
end

local function resolvePath(path, ext, root)

    if not root then
        if love.filesystem.getInfo(GAME_FOLDER .. "/assets/" .. path .. ext) then
            return GAME_FOLDER .. "/assets/" .. path .. ext
        elseif love.filesystem.getInfo("assets/" .. path .. ext) then
            return "assets/" .. path .. ext
        end
    else
        if love.filesystem.getInfo(GAME_FOLDER .. "/" .. path .. ext) then
            return GAME_FOLDER .. "/" .. path .. ext
        elseif love.filesystem.getInfo(path .. ext) then
            return path .. ext
        end
    end
end

fs.loadFile = function(path, ext, root)
    local filePath = resolvePath(path, ext, root)

    if not filePath then return end


    local lines = love.filesystem.lines(filePath)
    local tbl = {}
    for line in lines do
        table.insert( tbl, line )
    end

    return tbl
end

fs.loadImage = function(path)

    local imagePath = resolvePath(path, ".png")

    if imagePath then
        return love.graphics.newImage(imagePath)
    end

end

fs.sliceGridImage = function(path, width, height)

    local SCREEN_WIDTH = width or 256
    local SCREEN_HEIGHT = height or 192

    local imagePath = resolvePath(path, ".png")
    local imageProps = resolvePath(path, ".txt")

    if not imagePath then 
        return love.graphics.newArrayImage({love.image.newImageData(SCREEN_WIDTH,SCREEN_HEIGHT)}), 1
    end

    local props = {grid={1,1},length=1,loop=true}

    if imageProps then
        local propsData = fs.loadFile(path, ".txt")

        for _,line in pairs(propsData) do
            if line:match("grid") then
                local x,y = line:match("(%d+)x(%d+)")
                props.grid = {tonumber(x), tonumber(y)}
            elseif line:match("length") then
                local length = line:match("(%d+)")
                props.length = tonumber(length)
            elseif line:match("loops?") then
                local loop = line:match("[Tt]rue")
                if loop then props.loop = true end
            end
        end
    end

    local grid = love.image.newImageData(imagePath)
    local slices = {}

    for cell=0,props.length-1 do
        local slice = love.image.newImageData(SCREEN_WIDTH, SCREEN_HEIGHT)
        local column = cell%props.grid[1]
        local row = math.floor(cell/props.grid[1])

        slice:paste(grid, 0, 0, SCREEN_WIDTH*column, SCREEN_HEIGHT*row, SCREEN_WIDTH, SCREEN_HEIGHT)

        table.insert(slices, slice)
    end

    return love.graphics.newArrayImage(slices), props.length, props.loop
end

fs.loadSFX = function(path)
    local soundExtensions = {".ogg", ".mp3", ".wav", ".flac"}
    for num,ext in pairs(soundExtensions) do
        local soundPath = resolvePath(path, ext)
        if soundPath then return love.audio.newSource(soundPath, "static") end
    end
end

fs.loadMusic = function(path)
    local soundExtensions = {".ogg", ".mp3", ".wav", ".flac"}
    for num,ext in pairs(soundExtensions) do
        local soundPath = resolvePath(path, ext)
        if soundPath then return love.audio.newSource(soundPath, "stream") end
    end
end

fs.loadFont = function(path, glyphs)
    local fontPath = resolvePath(path, ".png")

    if fontPath then
        return love.graphics.newImageFont(fontPath, glyphs, fs.gameSettings.extraFontSpacing or 0)
    end
end

fs.loadDefaultFont = function()
    return love.graphics.newImageFont("assets/font/default_v2.png", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!?.☞「」()『』\"↓↑:+,/*'_˖。%‥~《》&☆♪- ")
end

return fs