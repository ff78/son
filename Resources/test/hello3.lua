--require "Hero"

-- cclog
cclog = function(...)
    print(string.format(...))
end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    cclog("----------------------------------------")
    cclog("LUA ERROR: " .. tostring(msg) .. "\n")
    cclog(debug.traceback())
    cclog("----------------------------------------")
end

function showactorpos( actor )
-- local hero = tolua.cast(actor, "Hero")
return actor:getBlackActor():getStateMachineFile()
end

function add( a, b )
return a + b
end