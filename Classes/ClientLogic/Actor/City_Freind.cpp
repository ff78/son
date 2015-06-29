//
//  City_Freind.cpp
//  son
//
//  Created by ff on 15-5-29.
//
//

#include "City_Freind.h"


#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;

bool City_Freind::init()
{
    if (!Node::init()) {
        return false;
    }
    
    return true;
}

void City_Freind::initWithId(int idx, Game_Data::Player* player)
{
    posX = rand() % MAP_AREA_WIDTH;
    posY = rand() % (MAP_AREA_TOP-MAP_AREA_BOTTOM) + MAP_AREA_BOTTOM;
    posX = MIN(MAP_AREA_RIGHT, posX);
    posX = MAX(MAP_AREA_LEFT, posX);
    posY = MIN(posY, MAP_AREA_TOP);
    posY = MAX(posY, MAP_AREA_BOTTOM);
    setPosition(posX, posY);
    
    rush = false;
    rushReady = false;
    walkSpeedX = WALK_SPEED;
    rushSpeedX = RUSH_SPEED;
    
    blackActor = new BlackActor();
    blackActor->readFile(idx, ACTOR_FILE);
    
    shadow = Sprite::create(SHADOW_FILE);
    shadow->setAnchorPoint(Vec2(0.5, 0.5));
    shadow->setPosition(Vec2(0, 0));
    addChild(shadow);
    
    std::string resPath = ARM_DIR + blackActor->getResName() + ".ExportJson";
    ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);
    armature = Armature::create(blackActor->getResName());
    scaleRate = blackActor->getScaleRate();
    armature->setScale(scaleRate);
    //    armature->setAnchorPoint(Point(0.5, 0));
    addChild(armature);
    
    
    stateMachine = new StateMachine();
    std::string machinePath = STATE_MACHINE_DIR + blackActor->getStateMachineFile();
    stateMachine->loadFromFile(machinePath);

    state = ACTORSTATE::UNDEFINED;
    event = StateMachine::action_undefined;
    changeState(ACTORSTATE::IDLE);
    //    changeAction(HEROACTION::STAND);
    changeActionWithName(HEROACTION::STAND);
    
    /************************  dely *************************/
    std::string nameStr = player->get_title_name();
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

void City_Freind::updateAI()
{
    posX = getPositionX();
    posY = getPositionY();
    auto boneMoveVec2 = calBoneMove();
    
    switch (state) {
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
                armature->setScaleX((flipX) ? -1 : 1);
            }
            return;
        }
            break;
    }
    
    setActorShowPos(boneMoveVec2);
}

void City_Freind::updateState()
{
    bool needChange = false;
    
    switch(state)
    {
        case ACTORSTATE::IDLE:
        {
            if (event != stateMachine->action_undefined) {
                needChange = true;
                break;
            }
            
        }
            break;
        case ACTORSTATE::AUTOMOVE:
        {
            if (event != stateMachine->action_undefined) {
                needChange = true;
                break;
            }
            
            if (arrivePos(targetMovePos)) {
                stopMove();
                event = stateMachine->findEventVal("EVENT_ARRIVE_TARGET");
                needChange = true;
            }
        }
            
            break;
    }
    
    if (needChange) {
        switch2NextState(state, event);
        
        needChange = false;
        event = StateMachine::action_undefined;
    }
}

void City_Freind::enterState(int nextState)
{
    switch (nextState) {
        case ACTORSTATE::IDLE:
        {
            idleTimeOut = false;
            auto func = CallFunc::create(CC_CALLBACK_0(Actor::idleTimeEnough, this));
            
            stopActionByTag(IDLE_TIMEOUT_TAG);
            idleDuration = 8 + abs(rand()%30);
            auto s = Sequence::create(DelayTime::create(idleDuration),func, NULL);
            s->setTag(IDLE_TIMEOUT_TAG);
            runAction(s);
            stopMove();
        }
            break;
        case ACTORSTATE::AUTOMOVE:
        {
            float xDis = rand() % 1000;
            float yDis = rand() % 100;

            xDis += (xDis/abs(xDis)*100);
            yDis += (yDis/abs(yDis)*10);
            
            float distX = getPositionX() + xDis;
            float distY = getPositionY() + yDis;
            distX = MIN(MAP_AREA_RIGHT, distX);
            distX = MAX(MAP_AREA_LEFT, distX);
            if (distX == MAP_AREA_RIGHT || distX == MAP_AREA_LEFT) {
                distX = getPositionX() - xDis;
            }
            distY = MIN(distY, MAP_AREA_TOP);
            distY = MAX(distY, MAP_AREA_BOTTOM);
            if (distY == MAP_AREA_TOP || distY == MAP_AREA_BOTTOM) {
                distY = getPositionY() - yDis;
            }
            targetMovePos = Point(distX, distY);
            
            Move2Target(targetMovePos);
        }
            break;
            
        default:
            break;
    }
}

void City_Freind::exitState(int currState)
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

void City_Freind::changeActionWithName(int nextAction)
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

void City_Freind::doFlag(int nextFlag)
{
    
}
