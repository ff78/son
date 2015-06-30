//
//  CityLayer.h
//  cocosGame
//
//  Created by ff on 14-11-5.
//
//

#ifndef __cocosGame__CityLayer__
#define __cocosGame__CityLayer__

#include "cocos2d.h"
#include "../Actor/City_NPC.h"
#include "../Actor/City_Player.h"
#include "../Actor/City_Freind.h"
#include "DataModule/BlackCity.h"
#include "../Actor/YNCamera.h"
#include "../SneakyJoy/SneakyJoyStick.h"

typedef void(*CallBackFun)(int);

class CityLayer : public cocos2d::Layer
{
public:
    bool init();
    
    CREATE_FUNC(CityLayer);
    
    void initData(int idx);
    
    void initBackLayer();

    void initMidLayer();
    
    void initFrontLayer();
    
    void addSceneEffect(std::string groupName, Node *parent, bool alignTop);
    
    void initActorLayer();
    
    void initCamera();
    
    void setViewWindow();
    
    void controlByJoyStick(SneakyJoystick *joyStick, float delta);
    
    void reorderPlayer();
    
    City_NPC* getNPCbyId(int idx);
    
    bool isCollideDoor();
    
    void onCollideDoor();
    
    std::vector<int> getNpcIds();
    
    int getNpcCount();
    
    void setNpcTipSprite(int npcId, std::string path, bool isPlist=false);
    
    void autoMove2NPC(int npcId);
    
    void autoMove2NPC(int npcId, CallBackFun func, int param);
    
    City_Player *player;
    
private:
    cocos2d::Sprite *bgSpt;
    
    BlackCity *blackCity;
    
    City_NPC *door;
    std::vector<City_Freind *> freindsVec;
    YNCamera *camera;
    bool pressJoy;
    int joyDir[8];
    

    CC_SYNTHESIZE_READONLY(cocos2d::Layer*, backLayer, BackLayer);
    CC_SYNTHESIZE_READONLY(cocos2d::Layer*, midLayer, MidLayer);
    CC_SYNTHESIZE_READONLY(cocos2d::Layer*, actorLayer, ActorLayer);
    CC_SYNTHESIZE_READONLY(cocos2d::Layer*, frontLayer, FrontLayer);
    
public:
    static bool playerInDoors;
};

#endif /* defined(__cocosGame__CityLayer__) */
