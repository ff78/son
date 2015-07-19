//
//  City_Player.h
//  cocosGame
//
//  Created by ff on 14-11-7.
//
//

#ifndef __cocosGame__City_Player__
#define __cocosGame__City_Player__

#include "Actor.h"
#include "../../DataModule/BlackActor.h"
#include "Guardian.h"
#include "Colossus.h"

typedef void(*CallBackFun)(int);

class City_Player : public Actor
{
public:
    bool init();
    
    CREATE_FUNC(City_Player);
    
    void initWithId(int idx);
    
    void updateState();
    
    void updateAI();
    
    void exitState(int currState);
    
    void enterState(int nextState);
    
//    void changeAction(int nextAction);
    
    void changeActionWithName(int nextAction);
    
    void doFlag(int nextFlag);
    
    void startAutoMove(cocos2d::Point p);
    
    void levelup();
private:
    BlackActor *blackActor;
    CC_SYNTHESIZE(CallBackFun, arriveFunc, ArrvieFunc);
    CC_SYNTHESIZE(int, arriveParam, ArriveParam);
    CC_SYNTHESIZE(bool, joyPress, JoyPress);
	/************************** dely **************************/
	CC_SYNTHESIZE(int,m_nTitle,Title);
	CC_SYNTHESIZE(std::string, m_sName,Name);

    CC_SYNTHESIZE(Guardian *, guard, Guard);
    CC_SYNTHESIZE(Colossus *, colossus, Colossus);
	/************************** dely **************************/
};

#endif /* defined(__cocosGame__City_Player__) */
