//
//  City_NPC.cpp
//  cocosGame
//
//  Created by ff on 14-11-7.
//
//

#include "City_NPC.h"

USING_NS_CC;
using namespace cocostudio;

bool City_NPC::init()
{
    if (!Node::init()) {
        return false;
    }
    
    return true;
}

void City_NPC::initWithId(int idx)
{
    walkSpeedX = WALK_SPEED;
    rushSpeedX = RUSH_SPEED;
    
    cityActor = new CityActor();
    cityActor->readFile(idx, NPC_FILE);
    
    shadow = Sprite::create(SHADOW_FILE);
    shadow->setAnchorPoint(Vec2(0.5, 0.5));
    shadow->setPosition(Vec2(0, 0));
    addChild(shadow);
    
    //初始化和资源载入
    std::string resPath = ARM_DIR + cityActor->getResStr() + ".ExportJson";
    ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);
    armature = Armature::create(cityActor->getResStr());
    scaleRate = cityActor->getScaleRate();
    armature->setScale(scaleRate);
//    armature->setAnchorPoint(Point(0.5, 0));
    addChild(armature);
    
    //加载状态机
    stateMachine = new StateMachine();
    std::string machinePath = STATE_MACHINE_DIR + cityActor->getStateMachineFile();
    stateMachine->loadFromFile(machinePath);
    //初始状态和动作
    state = ACTORSTATE::UNDEFINED;
    event = StateMachine::action_undefined;
    changeState(ACTORSTATE::IDLE);
//    changeAction(HEROACTION::STAND);
    changeActionWithName(HEROACTION::STAND);
}

void City_NPC::updateState()
{
    bool needChange = false;
    switch (state) {
        case ACTORSTATE::IDLE:
        {
            if (event != stateMachine->action_undefined) {
                needChange= true;
                break;
            }
        }
            break;
        case ACTORSTATE::MOVE:
        {
            if (arrivePos(targetMovePos)) {
                event = stateMachine->findEventVal("EVENT_ARRIVE_TARGET");
                needChange = true;
            }
        }
            break;
        default:
            break;
    }
    
    if (needChange) {
        switch2NextState(state, event);
        
        needChange = false;
        event = StateMachine::action_undefined;
    }
}

void City_NPC::updateAI()
{
    posX = getPositionX();
    posY = getPositionY();
    auto boneMoveVec2 = calBoneMove();
    
    if (currDir != DIRECT::NONE) {
        if (((currDir & DIRECT::LEFT)!=0) != flipX)
        {
            flipX = !flipX;
//            if (flipX) {
//                armature->setScaleX(-1);
//            }
            armature->setScaleX((flipX) ? -1 : 1);
        }
    }
    
//    switch (state) {
//        case ACTORSTATE::IDLE:
//        {
//
//        }
//            break;
//        case ACTORSTATE::MOVE:
//        {
//            
//        }
//            break;
//        default:
//            break;
//    }
    
    setActorShowPos(boneMoveVec2);
}

void City_NPC::exitState(int currState)
{
    switch (currState) {
        case ACTORSTATE::IDLE:
        {
            idleTimeOut = true;
            stopActionByTag(IDLE_TIMEOUT_TAG);
        }
            break;
            
        case ACTORSTATE::MOVE:
        {
            stopActionByTag(MOVE_ACTION_TAG);
        }
            break;
        default:
            break;
    }
}

void City_NPC::enterState(int nextState)
{
    switch (nextState) {
        case ACTORSTATE::IDLE:
        {
            idleTimeOut = false;
            auto func = CallFunc::create(CC_CALLBACK_0(Actor::idleTimeEnough, this));
            
            stopActionByTag(IDLE_TIMEOUT_TAG);
            idleDuration = 2 + abs(rand()%10);
            auto s = Sequence::create(DelayTime::create(idleDuration),func, NULL);
            s->setTag(IDLE_TIMEOUT_TAG);
            runAction(s);
            stopMove();
        }
            break;
        case ACTORSTATE::MOVE:
        {
            float xDis = rand() % 1000;
            float yDis = rand() % 1000;
            float distX = getPositionX() + xDis;
            float distY = getPositionY() + yDis;
            distX = MIN(MAP_AREA_RIGHT, distX);
            distX = MAX(MAP_AREA_LEFT, distX);
			distY = MIN(distY, MAP_AREA_TOP);
			distY = MAX(distY, MAP_AREA_BOTTOM);
            targetMovePos = Point(distX, distY);
            
            Move2Target(targetMovePos);
        }
            break;
            
        default:
            break;
    }
}

//void City_NPC::changeAction(int nextAction)
//{
//    armature->getAnimation()->playWithIndex(nextAction);
//}

void City_NPC::changeActionWithName(int nextAction)
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

void City_NPC::doFlag(int nextFlag)
{
    
}
