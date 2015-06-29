#pragma once

#include "cocos2d.h"
#include "FightActor.h"
#include "cocostudio/CocoStudio.h"
#include "../StateMachine/StateMachine.h"

enum HEROFRAMECOMMAND
{
    COMMAND_PUNCH = 0x1,
    COMMAND_PUNCHA2 = 0x2,
    COMMAND_PUNCHA3 = 0x4,
    COMMAND_PUNCHA4 = 0x8,
    COMMAND_SKL_XFT = 0x10,
    COMMAND_SKL_SLT = 0x20,
    COMMAND_JUMP_ATK = 0x40
};

class Hero : public FightActor
{
public:
	~Hero();

    bool init();
    
    virtual void initFightData(int idx);
    
    void addHurtListener();
	void removeHurtListener();

	CREATE_FUNC(Hero);

    void exitState(int currState);
    void enterState(int nextState);
    
    void updateState();
    void updateAI();
    void doFlag(int nextFlag);
    
//    virtual void changeSkill(int event);
    virtual void dispatchResetPunchTag();
    
    void backSkillAtkBase();
    
//    void backSkill2Base(int skillId, int key);
    
    void startXuli(int key);
    void endXuli(int key);
    void xuliEnough();
    
	/**
     *	@brief	由UI按键转成逻辑按键值
     *
     *	@param 	key 	int 当前按键，不包含方向键
     */
    bool setCurrKey(int key);


	void clearKey();
    
    void readyRushAtk();

//    void clearCombo();
    
//    void addCombo();
    
    virtual void setHp(float hp);
    virtual void setMp(float val);
    virtual void addAv(float val);
    virtual void useAp(float val);
    virtual void setGhost(float val);
    
    void resetWalkOrRush(int, int);
    
//    virtual void addBuff();
private:

//    std::string localBodyName;

//    bool rushReady;

    float fallStartY = 0;

    CC_SYNTHESIZE(bool, rushAtkReady, RushAtkReady);
	CC_SYNTHESIZE_READONLY(int, currKey, CurrKey);
    CC_SYNTHESIZE_READONLY(int, keyCommand, KeyCommand);
    CC_SYNTHESIZE_READONLY(int, joyCommand, JoyCommand);
    CC_SYNTHESIZE_READONLY(bool, isXuliEnough, IsXuliEnough);
    CC_SYNTHESIZE(bool, autoControll, AutoControll);
};