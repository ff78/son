//
//  Colossus.h
//  son
//
//  Created by ff on 15-5-25.
//
//

#ifndef __son__Colossus__
#define __son__Colossus__

#include "cocos2d.h"
#include "FightActor.h"
#include "DataModule/BlackColossus.h"


class Colossus : public FightActor
{
public:
    bool init();
    
    CREATE_FUNC(Colossus);
    
    virtual void initFightData(int idx);
    
    void exitState(int currState);
    void enterState(int nextState);
//
    void updateState();
    void updateAI();
//    void doFlag(int nextFlag);
//    
    bool lostHero();
    bool farFromHero();
//    bool pressSkill();
    void selColSkills(SkillTag *manCurrSkillTag);
private:
    CC_SYNTHESIZE(Actor *, man, Man);
    CC_SYNTHESIZE_READONLY(BlackColossus *, blackCol, BlackCol);
};

#endif /* defined(__son__Colossus__) */
