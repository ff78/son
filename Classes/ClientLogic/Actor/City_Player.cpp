//
//  City_Player.cpp
//  cocosGame
//
//  Created by ff on 14-11-7.
//
//

#include "City_Player.h"
#include "Effect.h"
/************************  dely *************************/
#include "DataModule/Little.h"

#include "Player_Account/Account_Data_Mgr.h"

#include "Character_System/Character_Mgr.h"
#include "Character_System/Player.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
/************************  dely *************************/

USING_NS_CC;
using namespace cocostudio;

bool City_Player::init()
{
    if (!Node::init()) {
        return false;
    }

    return true;
}

void City_Player::initWithId(int idx)
{
    rush = false;
    rushReady = false;
    walkSpeedX = WALK_SPEED;
    rushSpeedX = RUSH_SPEED;
    arriveFunc = nullptr;
    arriveParam = -1;
    
    blackActor = new BlackActor();
    blackActor->readFile(idx, ACTOR_FILE);
    
    shadow = Sprite::create(SHADOW_FILE);
    shadow->setAnchorPoint(Vec2(0.5, 0.5));
    shadow->setPosition(Vec2(0, 0));
    addChild(shadow);
    
    //初始化和资源载入
    std::string resPath = ARM_DIR + blackActor->getResName() + ".ExportJson";
    ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);
    armature = Armature::create(blackActor->getResName());
    scaleRate = blackActor->getScaleRate();
    armature->setScale(scaleRate);
//    armature->setAnchorPoint(Point(0.5, 0));
    addChild(armature);
    
    //加载状态机
    stateMachine = new StateMachine();
    std::string machinePath = STATE_MACHINE_DIR + blackActor->getStateMachineFile();
    stateMachine->loadFromFile(machinePath);
    //初始状态和动作
    state = ACTORSTATE::UNDEFINED;
    event = StateMachine::action_undefined;
    changeState(ACTORSTATE::IDLE);
//    changeAction(HEROACTION::STAND);
    changeActionWithName(HEROACTION::STAND);

	/************************  dely *************************/
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	int tmpTitle = player->get_title();
	std::string nameStr = Little::titles[player->get_title()].name;
	nameStr += player->get_character_name();
	ui::Text* name = ui::Text::create();
	name->setString(nameStr);
	name->setFontSize(25);
	name->setAnchorPoint( Vec2(0.5f,0.5f) );
	name->setColor( Color3B::GREEN );
	name->setTextVerticalAlignment( TextVAlignment::CENTER );
	name->setTextHorizontalAlignment( TextHAlignment::CENTER );
	name->setPosition( Vec2(0,200) );
	addChild(name);
	/************************  dely *************************/

}

void City_Player::updateState()
{
//    if (rushReady && (currDir & (DIRECT::RIGHT | DIRECT::LEFT))!=0)
//    {
//        if (((currDir & DIRECT::LEFT)!=0) == flipX)
//        {
//            //            log("rush dir %d", currDir);
//            
//            rush = true;
//        }else{
//            getActionByTag(READY_RUSH_TAG)->stop();
//            rushReady = false;
//        }
//        
//    }
    bool needChange = false;
    
    switch(state)
    {
        case ACTORSTATE::IDLE:
        {
            if (event != stateMachine->action_undefined) {
                needChange = true;
                break;
            }
            
            if (currDir != DIRECT::NONE)
            {
                event = stateMachine->findEventVal(rush?"EVENT_RUSH":"EVENT_MOVE");
                needChange = true;
            }
        }
            break;
        case ACTORSTATE::MOVE:
            if (event != stateMachine->action_undefined) {
                needChange = true;
                break;
            }
            
            if (currDir == DIRECT::NONE)
            {
                rush = false;
                event = stateMachine->findEventVal("EVENT_STOPMOVE");
                needChange = true;
            }
            
            if (rush) {
                event = stateMachine->findEventVal("EVENT_RUSH");
                needChange = true;
            }
            break;
        case ACTORSTATE::RUSH:
        {
            if (event != stateMachine->action_undefined) {
                needChange = true;
                break;
            }
            
            if (currDir == DIRECT::NONE)
            {
                rush = false;
                event = stateMachine->findEventVal("EVENT_STOPMOVE");
                needChange = true;
            }
        }
        case ACTORSTATE::AUTOMOVE:
        {
            if (event != stateMachine->action_undefined) {
                needChange = true;
                break;
            }
            
            if (currDir != DIRECT::NONE && joyPress)
            {
                event = stateMachine->findEventVal(rush?"EVENT_RUSH":"EVENT_MOVE");
                stopMove();
                stopActionByTag(MOVE_ACTION_TAG);
                needChange = true;
            }
            
            if (arrivePos(targetMovePos)) {
                stopMove();
                event = stateMachine->findEventVal("EVENT_ARRIVE_TARGET");
                needChange = true;
                if(arriveFunc!= nullptr)
                {
                    arriveFunc(arriveParam);
                    arriveFunc = nullptr;
                    arriveParam = -1;
                }
            }
        }
            
            break;
    }

    //确定要转换时，再进入状态机进行状态跳转
    if (needChange) {
        switch2NextState(state, event);
        
        needChange = false;
        event = StateMachine::action_undefined;
    }
}

void City_Player::updateAI()
{
    posX = getPositionX();
    posY = getPositionY();
    auto boneMoveVec2 = calBoneMove();
    
    switch (state) {
        case ACTORSTATE::MOVE:
        case ACTORSTATE::RUSH:
        {
            if(currDir == DIRECT::NONE)
            {
                break;
            }
            if (((currDir & DIRECT::LEFT)!=0) != flipX)
            {
                flipX = !flipX;
//                if (flipX)
//                {
//                    armature->setScaleX(-1);
//                }
                armature->setScaleX((flipX) ? -1 : 1);
            }
            
            //移动
            posX = getPositionX() + speedX;
            posY = getPositionY() + speedY;
        }
            break;
        case ACTORSTATE::AUTOMOVE:
        {
            if(currDir == DIRECT::NONE)
            {
                break;
            }
            if (((currDir & DIRECT::LEFT)!=0) != flipX)
            {
                flipX = !flipX;
//                if (flipX)
//                {
//                    armature->setScaleX(-1);
//                }
                armature->setScaleX((flipX) ? -scaleRate : scaleRate);
            }
            return;
        }
            break;
    }
    
    setActorShowPos(boneMoveVec2);
}

void City_Player::exitState(int currState)
{
    
}

void City_Player::enterState(int nextState)
{
    switch (nextState) {
        case ACTORSTATE::IDLE:
        {
            rush = false;
        }
            break;
            
        default:
            break;
    }
}

//void City_Player::changeAction(int nextAction)
//{
//    armature->getAnimation()->playWithIndex(nextAction);
//}

void City_Player::changeActionWithName(int nextAction)
{
    std::vector<std::string> actionName = stateMachine->findActionNames(nextAction);
    if (actionName.size() == 0) {
        return;
    }
    if (actionName.size() == 1)
    {
        armature->getAnimation()->play(actionName[0]);
    }else{
        armature->getAnimation()->playWithNames(actionName, -1, false);
    }
}

void City_Player::doFlag(int nextFlag)
{
    
}

void City_Player::startAutoMove(Point p)
{
    Move2Target(p);
    event = stateMachine->findEventVal("EVENT_AUTOMOVE");
}

void City_Player::levelup()
{
    auto effect = Effect::create();
    effect->initWithArmatureAR("levelup");
    addChild(effect, -1);
}
