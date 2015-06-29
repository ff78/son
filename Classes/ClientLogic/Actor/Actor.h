//
//  Actor.h
//  cocosGame
//
//  Created by ff on 14-11-5.
//
//

#ifndef __cocosGame__Actor__
#define __cocosGame__Actor__

#include "cocos2d.h"
#include "cocoStudio/CocoStudio.h"
#include "../FightDefine.h"
#include "../StateMachine/StateMachine.h"

class Actor : public cocos2d::Node
{
public:
    /**
     *	@brief	角色逻辑
     *
     *	@param 	dt 	float duration
     */
    void logic(float dt);
	/******************************** dely *********************************/
	virtual ~Actor(){};
	/******************************** dely *********************************/
    
    /**
     *	@brief	更新状态
     *
     */
    virtual void updateState(){};
    
    /**
     *	@brief	执行状态内AI
     *
     */
    virtual void updateAI(){};
    
    /**
     *	@brief	退出状态时要做的处理
     *
     *	@param 	currState 	int 当前状态
     */
    virtual void exitState(int currState){};
    
    /**
     *	@brief	进入下一状态时要做的准备
     *
     *	@param 	nextState 	int 进入状态
     */
    virtual void enterState(int nextState){};
    
    /**
     *	@brief	改变状态
     *
     *	@param 	nextState 	int 进入状态
     */
    void changeState(int nextState);
    
    /**
     *	@brief	切换动作
     *
     *	@param 	nextAction 	int 执行动作
     */
    virtual void changeActionWithName(int nextAction){};
    
//    virtual void changeAction(int nextAction){};
    
    
    /**
     *	@brief	设定方向
     *
     *	@param 	dir 	int 方向
     */
    void setDir(int dir);
    
    /**
     *	@brief	执行后续操作，如下落检测等
     *
     *	@param 	nextFlag 	int 附加标签
     */
    virtual void doFlag(int nextFlag){};
    
    void switch2NextState(int state, int event);
    
    void stopMove();
    void startMove();
    
    cocos2d::Rect getBodyRect();
    
    cocos2d::Point calBoneMove();
    
    void setActorShowPos(cocos2d::Point boneMoveVec2);
    
    void Move2Target(cocos2d::Point p);
    
    void Run2Target(cocos2d::Point p);
    
    bool arrivePos(cocos2d::Point p);
    
    bool arriveTargetPos();
    
    void idleTimeEnough();
    
    void readyRush();
    
    bool animOver();
    
    bool isOutWindow();
protected:
    cocos2d::Sprite *shadow;
    CC_SYNTHESIZE_READONLY(cocostudio::Armature*, armature, Armature);
    CC_SYNTHESIZE_READONLY(float, scaleRate, ScaleRate);
    CC_SYNTHESIZE(bool, flipX, FlipX);
    CC_SYNTHESIZE_READONLY(bool, rush, Rush);
    CC_SYNTHESIZE(float, posX, PosX);
    CC_SYNTHESIZE(float, posY, PosY);
    CC_SYNTHESIZE(cocos2d::Point, localBonePoint, LocalBonePoint);
    CC_SYNTHESIZE_READONLY(cocos2d::Point, targetMovePos, TargetMovePos);
    CC_SYNTHESIZE(bool, rushReady, RushReady);
    
    StateMachine *stateMachine;
    int event;
    int delayEvent = StateMachine::action_undefined;

    int state;
    int action;
    int currDir;
    int speedX, speedY;
    float walkSpeedX ;
    float rushSpeedX ;
    
    bool idleTimeOut;
    float idleDuration = 3;

};

#endif /* defined(__cocosGame__Actor__) */
