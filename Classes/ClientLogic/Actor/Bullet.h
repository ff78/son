//
//  Bullet.h
//  cocosGame
//
//  Created by ff on 14-12-15.
//
//

#ifndef __cocosGame__Bullet__
#define __cocosGame__Bullet__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "../../DataModule/BlackBullet.h"
#include "../../DataModule/SkillTag.h"
#include "../../DataModule/Skill.h"
#include "Actor.h"

class FightActor;

class Bullet : public Actor
{
public:
    virtual bool init();
    CREATE_FUNC(Bullet);
    void initWithId(int idx, FightActor *owner, float gunPosX, float gunPosY);
    void initAttr(SkillTag *skill, FightActor *owner);
    void Logic(float dt);
    cocos2d::Rect getAtkRect();
    
    bool isOutsideCamera(float cameraX);
    
    bool isAnimationOver();
    
    void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
private:
    CC_SYNTHESIZE_READONLY(bool, flipX, FlipX);
    CC_SYNTHESIZE_READONLY(float, speed, Speed);
    CC_SYNTHESIZE(int, hitDownVal, HitDownVal);
    
    CC_SYNTHESIZE_READONLY(cocostudio::Armature *, armature, Armature);
    CC_SYNTHESIZE_READONLY(float, scaleRate, ScaleRate);

    CC_SYNTHESIZE(FightActor *, owner, Owner);
    CC_SYNTHESIZE(bool, isAlive, Alive);
    CC_SYNTHESIZE(SkillTag *, skillTag, SkillTag);
    CC_SYNTHESIZE_READONLY(BlackBullet *, blackBullet, BlackBullet);

    CC_SYNTHESIZE_READONLY(int, skillId, SkillId);
    CC_SYNTHESIZE_READONLY(int, attackTag, AttackTag);
    CC_SYNTHESIZE_READONLY(bool, atking, Atking);
    CC_SYNTHESIZE_READONLY(bool, attackHead, AttackHead);
    CC_SYNTHESIZE_READONLY(bool, attackWaist, AttackWaist);
    
    CC_SYNTHESIZE_READONLY(bool, hit2Air, Hit2Air);
    CC_SYNTHESIZE_READONLY(bool, hit2Ground, Hit2Ground);
    CC_SYNTHESIZE_READONLY(bool, hit2Wall, Hit2Wall);
    
    CC_SYNTHESIZE_READONLY(Skill *, currSkill, CurrSkill);
    CC_SYNTHESIZE_READONLY(SkillTag *, currSkillTag, CurrSkillTag);
};

#endif /* defined(__cocosGame__Bullet__) */
