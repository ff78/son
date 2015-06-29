//
//  City_NPC.h
//  cocosGame
//
//  Created by ff on 14-11-7.
//
//

#ifndef __cocosGame__City_NPC__
#define __cocosGame__City_NPC__

#include "Actor.h"
#include "../../DataModule/CityActor.h"

class City_NPC : public Actor
{
public:
    bool init();
    
    CREATE_FUNC(City_NPC);
    
    void initWithId(int idx);
    
    void updateState();
    
    void updateAI();
    
    void exitState(int currState);
    
    void enterState(int nextState);
    
//    void changeAction(int nextAction);
    
    void changeActionWithName(int nextAction);
    
    void doFlag(int nextFlag);
    
private:
    CC_SYNTHESIZE_READONLY(CityActor*, cityActor, CityActor);
    
};

#endif /* defined(__cocosGame__City_NPC__) */
