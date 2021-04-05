local function enum(tbl)
    
    local e = {}

    for i=1,#tbl do
        local v = tbl[i]
        e[v] = i
    end

    return e 
end


local const = {}

const.DISPLAY_SCALE = 4
const.TEXT_RATE = 2
const.DIALOGUE_STATE = enum {
    "WAIT",
    "TYPE",
    "CHOOSE"
}

return const