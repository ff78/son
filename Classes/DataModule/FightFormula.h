//
//  FightFormula.h
//  cocosGame
//
//  Created by ff on 14-12-25.
//
//

#ifndef __cocosGame__FightFormula__
#define __cocosGame__FightFormula__

#include "ClientLogic/Utils/GameUtil.h"
#include "Skill.h"
#include "BlackActor.h"
#include "BlackBullet.h"
#include "SkillTag.h"

class FightFormula : public Singleton<FightFormula>
{
private:
    float calAttrHurt(float baseHurt, SkillTag *skill, BlackActor *atk, BlackActor *def);
    float calBulletHurt(float baseHurt, BlackBullet *bullet, BlackActor *def);
    float calAttrHurt1(float baseHurt, float attackAttr, float defenceAttr);
public:
    float calSkillHurt(SkillTag *skillTag, BlackActor *atk, BlackActor *def);
    
    float calBulletHurt(BlackBullet *bullet, BlackActor *def);
    
    bool isMiss(BlackActor *attacker, BlackActor *defencer);
    
    bool isCirt(BlackActor *attacker, BlackActor *defencer);
    
    bool isImmuBuff(BlackActor *defencer);
   
    bool isHit2Air(BlackActor *def);
    
    bool isHitDown(BlackActor *def);
};

#endif /* defined(__cocosGame__FightFormula__) */
