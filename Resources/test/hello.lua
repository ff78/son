-- require "Cocos2d"
-- require "Cocos2dConstants"

str = "Happy new year!"
tb1 = {name = "ff", id = 005}
function add( a, b )
return a + b
end

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

local function main()
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)

    -- local visibleSize = cc.Director:getInstance():getVisibleSize()
    -- local origin = cc.Director:getInstance():getVisibleOrigin()

    -- add the moving dog
    local function createLayerMap()
        local layerWorldMap = cc.Layer:create()

        local bg = cc.Sprite:create("scene_26.png")
        -- bg:setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2)
        bg:setPosition(VisibleRect:center())
        layerWorldMap:addChild(bg)

        return layerWorldMap
    end

    cc.Director:getInstance():getRunningScene():addChild(createLayerMap())

end



xpcall(main, __G__TRACKBACK__)
