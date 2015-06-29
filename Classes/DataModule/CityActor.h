//
//  CityActor.h
//  cocosGame
//
//  Created by ff on 14-11-7.
//
//

#ifndef __cocosGame__CityActor__
#define __cocosGame__CityActor__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class CityActor
{
public:
    CityActor();
    ~CityActor();
    
    void readFile(int idx, std::string filename);
    
    bool initData(int idx, rapidjson::Document& _doc);
    
    static void initIdTable(rapidjson::Document &_doc);
    
private:
    CC_SYNTHESIZE_READONLY(int, actorId, ActorId);
    CC_SYNTHESIZE(std::string, name, Name);
    CC_SYNTHESIZE_READONLY(std::string, resName, ResStr);
    CC_SYNTHESIZE_READONLY(float, scaleRate, ScaleRate);
    CC_SYNTHESIZE_READONLY(std::string, stateMachineFile, StateMachineFile);
    
    CC_SYNTHESIZE_READONLY(int, iconId, IconId);
    CC_SYNTHESIZE_READONLY(int, appearCondition, AppearCondition);
    CC_SYNTHESIZE_READONLY(int, npcType, NpcType);
    CC_SYNTHESIZE_READONLY(int, dialogId, DialogID);
    CC_SYNTHESIZE_READONLY(int, triggerRule, TriggerRule);
    CC_SYNTHESIZE_READONLY(int, waitAction, waitAction);
    CC_SYNTHESIZE_READONLY(int, shopId1, ShopId1);
    CC_SYNTHESIZE_READONLY(int, shopId2, ShopId2);
    CC_SYNTHESIZE_READONLY(int, shopId3, ShopId3);
    
public:
    static std::map<int, int> idTable;
};

#endif /* defined(__cocosGame__CityActor__) */
