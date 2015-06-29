//
//  Effect.h
//  ssoul
//
//  Created by ff on 14-10-10.
//
//

#ifndef __ssoul__Effect__
#define __ssoul__Effect__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../FightDefine.h"

class Effect : public cocos2d::Node
{
public:
    bool init();
    
    CREATE_FUNC(Effect);
    
    bool initWithRes(std::string boneName, float scale = 1);
    
    
    bool initWithArmature(std::string boneName, float scale = 1);
    bool initWithArmatureAR(std::string boneName, float scale = 1);
    
    bool initWithNumber(std::string numImgName, int num, int width, int height);
    
    bool initWithImg(std::string imgName);
    void animationEvent(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID);

private:
    CC_SYNTHESIZE_READONLY(std::string, resName, ResName);
    CC_SYNTHESIZE_READONLY(cocostudio::Armature *, armature, Armature);
    CC_SYNTHESIZE_READONLY(float, scaleRate, ScaleRate)
    CC_SYNTHESIZE(float, originX, OriginX);
    CC_SYNTHESIZE(float, originY, OriginY);
    
    CC_SYNTHESIZE(bool, followY, FollowY);
    
    CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas *, hurtText, HurtText);
    CC_SYNTHESIZE_READONLY(cocos2d::Sprite *, flagSpt, FlagSpt);
};

#endif /* defined(__ssoul__Effect__) */
