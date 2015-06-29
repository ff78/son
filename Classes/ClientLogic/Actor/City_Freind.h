//
//  City_Freind.h
//  son
//
//  Created by ff on 15-5-29.
//
//

#ifndef __son__City_Freind__
#define __son__City_Freind__

#include "Actor.h"
#include "../../DataModule/BlackActor.h"
#include "Guardian.h"
#include "Colossus.h"

#include "Player_Account/Account_Data_Mgr.h"

#include "Character_System/Character_Mgr.h"
#include "Character_System/Player.h"

class City_Freind : public Actor
{
public:
    bool init();
    
    CREATE_FUNC(City_Freind);
    
    void initWithId(int idx, Game_Data::Player* player);
    
    void updateState();
    
    void updateAI();
    
    void exitState(int currState);
    
    void enterState(int nextState);
    
    //    void changeAction(int nextAction);
    
    void changeActionWithName(int nextAction);
    
    void doFlag(int nextFlag);
private:
    BlackActor *blackActor;

    /************************** dely **************************/
    CC_SYNTHESIZE(int,m_nTitle,Title);
    CC_SYNTHESIZE(std::string, m_sName,Name);
    
    CC_SYNTHESIZE(Guardian *, guard, Guard);
    CC_SYNTHESIZE(Colossus *, colossus, Colossus);
    /************************** dely **************************/
};

#endif /* defined(__son__City_Freind__) */
