//
//  Actor.cpp
//  cocosGame
//
//  Created by ff on 14-11-5.
//
//

#include "Actor.h"
#include "YNCamera.h"

USING_NS_CC;

void Actor::setDir(int dir)
{
    if (state == ACTORSTATE::ATTACK )
    {
        //攻击状态下，不移动
        return;
    }
    currDir = dir;
    
}

Rect Actor::getBodyRect()
{
    return Rect(-35, 0, 70, 200);
}

void Actor::logic(float dt)
{
    updateAI();
    updateState();
}

void Actor::switch2NextState(int state, int event)
{
    stateMachine->setCurrTactics(state);
    stateMachine->setCurrEvent(event);
    stateMachine->nextState();
    doFlag(stateMachine->getNextFlag());
    if(stateMachine->getNextAction() == StateMachine::action_undefined)
    {
        return;
    }
    if(stateMachine->getNextTactics() != this->state)
    {
        changeState(stateMachine->getNextTactics());
    }
    
//    changeAction(stateMachine->getNextAction());
    changeActionWithName(stateMachine->getNextAction());
}

void Actor::changeState(int nextState)
{
    exitState(state);
    enterState(nextState);
    state = nextState;
}

void Actor::stopMove()
{
    speedX = speedY = 0;
    currDir = DIRECT::NONE;
}

void Actor::startMove()
{
    //各方向叠加速度
    if ((currDir & UP) != 0)
    {
        speedY = 3;
    }
    if ((currDir & DOWN) != 0)
    {
        speedY = -3;
    }
    if ((currDir & LEFT) != 0)
    {
        speedX = -(rush?rushSpeedX:walkSpeedX);
    }
    if ((currDir & RIGHT) != 0)
    {
        speedX = rush?rushSpeedX:walkSpeedX;
    }
    
    //清除不需要方向的速度
    if ((currDir & (DIRECT::UP | DIRECT::DOWN)) == 0)
    {
        speedY = 0;
    }
    if ((currDir & (DIRECT::LEFT | DIRECT::RIGHT)) == 0)
    {
        speedX = 0;
    }
    
}

Point Actor::calBoneMove()
{
    auto originInfo = armature->getBone("OriginPoint")->getWorldInfo();
    auto boneInfo = armature->getBone("localPoint")->getWorldInfo();
    
    auto boneVec2 = Point(boneInfo->x, boneInfo->y)-Point(originInfo->x, originInfo->y);
    auto boneMoveVec2 = boneVec2 - localBonePoint;
    localBonePoint = Point(boneInfo->x, boneInfo->y)-Point(originInfo->x, originInfo->y);
    
    return boneMoveVec2;
}

void Actor::setActorShowPos(Point boneMoveVec2)
{
    posX += boneMoveVec2.x*((flipX) ? -1 : 1);
    posX = MIN(MAP_AREA_RIGHT, posX);
    posX = MAX(MAP_AREA_LEFT, posX);
    setPositionX(posX);
    posY = MIN(posY, MAP_AREA_TOP);
    posY = MAX(posY, MAP_AREA_BOTTOM);
    setPositionY(posY);
    
    armature->setPositionY(armature->getPositionY()+boneMoveVec2.y);
}

void Actor::Move2Target(Point p)
{
    targetMovePos = p;
    if(targetMovePos.x>getPositionX())
    {
        setDir(DIRECT::RIGHT);
    }else{
        setDir(DIRECT::LEFT);
    }
    
    stopActionByTag(MOVE_ACTION_TAG);
    auto dis = getPosition().getDistance(targetMovePos);
    float dur = dis/(walkSpeedX*60);
    
    auto mt = MoveTo::create(dur, targetMovePos);
    mt->setTag(MOVE_ACTION_TAG);
    runAction(mt);
}

void Actor::Run2Target(Point p)
{
    targetMovePos = p;
    if(targetMovePos.x>getPositionX())
    {
        setDir(DIRECT::RIGHT);
    }else{
        setDir(DIRECT::LEFT);
    }
    
    stopActionByTag(MOVE_ACTION_TAG);
    auto dis = getPosition().getDistance(targetMovePos);
    float dur = dis/(rushSpeedX*60);
    
    auto mt = MoveTo::create(dur, targetMovePos);
    mt->setTag(MOVE_ACTION_TAG);
    runAction(mt);
}

bool Actor::arrivePos(Vec2 p)
{
    return getPosition() == p;
}

bool Actor::arriveTargetPos()
{
    return arrivePos(targetMovePos);
}
bool Actor::animOver()
{
    return armature->getAnimation()->isComplete();
}
bool Actor::isOutWindow()
{
    return YNCamera::getInstance()->isOutWindow(getPosition());
}
void Actor::idleTimeEnough()
{
    idleTimeOut = true;
    event = stateMachine->findEventVal("EVENT_IDLETIMEOUT");
}

void Actor::readyRush()
{
    setRushReady(true);
    auto func1 = CallFunc::create(CC_CALLBACK_0(Actor::setRushReady, this, false));
    auto rushAction = Sequence::create(DelayTime::create(RUSH_LINK_TIME),func1, NULL);
    rushAction->setTag(READY_RUSH_TAG);
    runAction(rushAction);
}
