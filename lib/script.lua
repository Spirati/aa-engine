local fs = require "lib/fs"

local script = {}

local keywords = { "bg", "fg", "char", "script" }

script.loadScript = function(scriptFile)

    script.lineIndex = 0
    currentScript = scriptFile

    script.inBlock = false

    script.lines = fs.loadFile("script/" .. scriptFile, ".txt", true)

    return true
end

script.advance = function()

    if not script.lines then return end

    local line = table.remove(script.lines, 1)

    --print(line)
    script.lineIndex = script.lineIndex+1

    if line == nil then return false end

    if line:match("//.+") then 
        script.lineIndex = script.lineIndex+1
        return true 
    end

    if line:match("^}") then
        if script.inBlock then
            script.inBlock = false
            return true
        else
            print(string.format("Unexpected closing brace on line %i of script file %s", script.lineIndex, currentScript))
            love.event.push("quit", 1) 
        end
    end

    if not script.inBlock then

        for _,keyword in pairs(keywords) do

            if line:match("^"..keyword) then
                local argString = line:sub(keyword:len()+1)
                local args = {}
                local argsIndex = 1
                for arg in argString:gmatch("%S+") do

                    args[argsIndex] = arg
                    argsIndex = argsIndex + 1

                    if arg:match("^{") and keyword == "char" then

                        script.inBlock = true
                        if argsIndex > 2 then
                            script.character = {name=args[1],emotion="normal"}
                            assets.character = {animIndex=0}
                            assets.character.array, assets.character.length = fs.sliceGridImage("char/" .. script.character.name:lower() .. "/normal(talk)")
                        else
                            script.character = ""
                        end
                        script.advance()
                        return true
                    elseif keyword == "char" and argsIndex == 3 then
                        script.inBlock = true
                        script.character = {name=args[1],emotion=args[2]}
                        assets.character = {animIndex=0}                        
                        assets.character.array, assets.character.length = fs.sliceGridImage("char/" .. script.character.name:lower() .. "/" .. args[2] .. "(talk)")
                        
                        script.advance()
                        return true
                    end

                    if keyword == "bg" or keyword == "fg" then
                        assets[keyword] = fs.loadImage(keyword .. "/" .. arg)
                    end

                    if keyword == "script" then
                        return script.loadScript(args[1])
                    end

                end
            end

        end
    else
        local tagPattern = "<(.+)%s?(.-)>(.-)</%1>"
        local currentLine = line:match("^%s*(.+)$"):gsub("\\n","\n")
        while currentLine:match(tagPattern) do
            currentLine = currentLine:gsub(tagPattern, "%3")
        end

        function parseTags(s)

            local tagString = "(){([^%s]+)%s?([^}]+)}()"
        
            local totalTagLength = 0
            local tagIndices = {}
            local tags = {}
        
            local tagRegions = {}
        
            local content = ""
        
            for i,tag,args,j in s:gmatch(tagString) do
                if not tags[tag] then tags[tag] = {} end
        
                table.insert(tagIndices,i)
                table.insert(tagIndices,j)
        
                table.insert(tags[tag], {args=args,indices={i,j}})
        
                totalTagLength = totalTagLength + i + j
        
                if not (#tagIndices/2 == 1) then
                    content = content .. s:sub(tagIndices[#tagIndices-2], tagIndices[#tagIndices-1]-1)
                end
            end

            if #tagIndices == 0 then return {cleanedText=s, coloredText={{1,1,1}, s}} end

            content = content .. s:sub(tagIndices[#tagIndices])
        
            if tags.c then
        
                local function colorProcessor(colors) 
                    local nums = {}
                    for num in colors:gmatch("%S+") do 
                        table.insert(nums, tonumber(num)) 
                    end
                    return nums 
                end
        
                local coloredText = {}
        
                for i=1,#tags.c-1 do
                    local tag = tags.c[i]
                    local nextTag = tags.c[i+1]
        
                    table.insert(
                        coloredText,
                        colorProcessor(tag.args)
                    )
        
                    local tosub = s:sub(tag.indices[2], nextTag.indices[1]-1):gsub(tagString, "")
        
                    table.insert(
                        coloredText,
                        tosub
                    )
                end
        
                local tosub = s:sub(tags.c[#tags.c].indices[2]):gsub(tagString, "")
        
                if tags.c[#tags.c] then
                    table.insert( coloredText, colorProcessor(tags.c[#tags.c].args))
                    table.insert( coloredText, tosub )
                end
        
                return {cleanedText=content, coloredText = coloredText}
            end
        
            return {cleanedText=content, coloredText = {{1,1,1}, content}}
        end

        script.currentLine = parseTags(currentLine).cleanedText

        script.lineProgress = nil
    end

    (callback or function() return end)()

    return true
end

script.type = function()
    if not script.currentLine then return end

    if not script.lineProgress then script.lineProgress = "" end

    script.lineProgress = script.currentLine:sub(1, script.lineProgress:len()-script.currentLine:len())
    return script.lineProgress:len() == script.currentLine:len()

end

return script