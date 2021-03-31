local fs = require "lib/fs"

local script = {}

local keywords = { "bg", "fg", "char" }

script.loadScript = function(gameFolder, scriptFile)

    script.lineIndex = 0
    currentScript = scriptFile

    script.inBlock = false

    script.lines = fs.loadFile("script/" .. scriptFile, ".txt", true)

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

                end
            end

        end
    else
        local tagPattern = "<(.+)%s?(.-)>(.-)</%1>"
        local currentLine = line:match("^%s*(.+)$"):gsub("\\n","\n")
        while currentLine:match(tagPattern) do
            currentLine = currentLine:gsub(tagPattern, "%3")
        end

        function traverseTags(hierarchy, str)


            for tag,args,content in str:gmatch(tagPattern) do
                if not hierarchy[#hierarchy+1] then table.insert(hierarchy, {}) end
          
                table.insert(hierarchy[#hierarchy], {tag,args,content})
          
                traverseTags(hierarchy[#hierarchy], content)
                
            end
        end

        script.currentLine = currentLine

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