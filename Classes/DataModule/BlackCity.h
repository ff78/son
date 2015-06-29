//
//  BlackCity.h
//  cocosGame
//
//  Created by ff on 14-11-5.
//
//

#ifndef __cocosGame__BlackCity__
#define __cocosGame__BlackCity__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
//#include "../ClientLogic/Utils/GameUtil.h"

class BlackCity{
//: public Singleton<BlackCity>{
    
public:
    void readFile(int idx, std::string filename);
    
    bool initData(int idx, rapidjson::Document& _doc);
    
    bool canEnter(int level, int campId);
    
    static void initIdTable(rapidjson::Document &_doc);
    
    void onCollideDoor();
public:
    static std::map<int, int> idTable;
    
private:
    CC_SYNTHESIZE_READONLY(int, sceneId, SceneId);
    CC_SYNTHESIZE_READONLY(std::string, tiledMapPath, TiledMapPath);
    CC_SYNTHESIZE_READONLY(std::string, name, Name);
    CC_SYNTHESIZE_READONLY(int, permissionLvl, PermissionLevel);
    CC_SYNTHESIZE_READONLY(int, campId, CampId);
    CC_SYNTHESIZE_READONLY(std::string, bgPath, BgPath);
    CC_SYNTHESIZE_READONLY(std::string, midPath, MidPath);
    CC_SYNTHESIZE_READONLY(std::string, frontPath, FrontPath);
};

#endif /* defined(__cocosGame__BlackCity__) */
