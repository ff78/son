//
//  Monster.cpp
//  soul
//
//  Created by ff on 14-9-15.
//
//

#include "Monster.h"
#include "cocostudio/CocoStudio.h"
#include "../Utils/BaseUtils.h"
#include "YNCamera.h"
#include "Effect.h"
#include "../GameScene/ActorLayer.h"
#include "Guardian.h"


USING_NS_CC;
using namespace cocostudio;
using namespace CocosDenshion;

bool Monster::init()
{
    
//    initFightData(1);
//
//    initViewRes();
//    
//    initFightState();
//    
//    setDir(DIRECT::LEFT);
    buffManager = BuffManager::create();
    addChild(buffManager);
    
    ghostList.clear();
//    auto p1 = Vec2(1700, getPositionY());
//    auto p2 = Vec2(1000, getPositionY());
//    partolPosVec.push_back(p1);
//    partolPosVec.push_back(p2);
    return true;
}
void Monster::initFightData(int idx)
{
    blackActor = new BlackActor();
    blackActor->readFile(idx, ACTOR_FILE);
    blackActor->initSelSkill();
    blackActor->initSelSkillTag();
    
    currSkill = nullptr;
    currSkillTag = nullptr;
    killSkill = nullptr;

    killSkillTag = nullptr;

    targetActor = nullptr;
    flipX = false;
    flipX = false;
    deHitDownVal = currHitDownVal = blackActor->getDeHitDownVal();
    atkStiff = hurtStiff = false;
    hurtMoveSpeed = 0;
    backInAir = false;
    
    viewSize = Size(Director::getInstance()->getWinSize().width, MAP_AREA_TOP-MAP_AREA_BOTTOM);
    
    killer = nullptr;
    killers.clear();
    bHero = false;
    dying = false;
    dieLie = false;
}

void Monster::addPartolPoint(Point p1, Point p2)
{
    partolPosVec.clear();
    partolPosVec.push_back(p1);
    partolPosVec.push_back(p2);
}
void Monster::addHurtListener()
{
//    hurtListener = EventListenerCustom::create(MONSTER_HURT_TAG, CC_CALLBACK_1(FightActor::parseHurtEvent, this));
//    punchListener = EventListenerCustom::create(HERO_RESET_PUNCH, CC_CALLBACK_1(FightActor::resetPunchTag, this));
//    getEventDispatcher()->addEventListenerWithFixedPriority(hurtListener, -1);
//    getEventDispatcher()->addEventListenerWithFixedPriority(punchListener, -1);

    hurtListener = getEventDispatcher()->addCustomEventListener(MONSTER_HURT_TAG, CC_CALLBACK_1(FightActor::parseHurtEvent, this));
    punchListener = getEventDispatcher()->addCustomEventListener(HERO_RESET_PUNCH, CC_CALLBACK_1(FightActor::resetPunchTag, this));
}

void Monster::removeHurtListener()
{
    getEventDispatcher()->removeEventListener(hurtListener);
    getEventDispatcher()->removeEventListener(punchListener);
//    getEventDispatcher()->removeCustomEventListeners(MONSTER_HURT_TAG);
//	getEventDispatcher()->removeCustomEventListeners(HERO_RESET_PUNCH);

}

Monster::~Monster()
{
	removeHurtListener();
    ghostList.clear();
}

void Monster::exitState(int currState)
{
    switch (currState) {
        case ACTORSTATE::IDLE:
            idleTimeOut = true;
            stopActionByTag(IDLE_TIMEOUT_TAG);
            break;
        case ACTORSTATE::PATROL:
            stopActionByTag(MOVE_ACTION_TAG);
            leavePartolPos = getPosition();
            break;
        case ACTORSTATE::RETURN:
            stopActionByTag(MOVE_ACTION_TAG);
            break;
        case ACTORSTATE::CHASE:
            stopActionByTag(MOVE_ACTION_TAG);
            break;
        case ACTORSTATE::FELLDOWN:
            currHitDownVal = deHitDownVal;
            break;
        case ACTORSTATE::WAIT:
            waitTimeOut = true;
            stopActionByTag(WAIT_TIMEOUT_TAG);
            break;
        case ACTORSTATE::ANY:
            frontEffectLayer->removeChildByTag(ATTACK_EFFECT_TAG);
        case ACTORSTATE::XULI:
            frontEffectLayer->removeChildByTag(XULI_EFFECT_TAG);
            break;
        case ACTORSTATE::BOUNDWALL:
        {
            hurtMoveSpeed *= -1;
            backInAir = true;
            asBomb = false;
        }
            break;
        case ACTORSTATE::INAIR:
            backInAir = false;
            break;
        default:
            break;
    }

}

void Monster::enterState(int nextState)
{
    switch (nextState) {
        case ACTORSTATE::IDLE:
        {
//            killer = nullptr;
            idleTimeOut = false;
            auto func = CallFunc::create(CC_CALLBACK_0(Actor::idleTimeEnough, this));

            stopActionByTag(IDLE_TIMEOUT_TAG);
            auto s = Sequence::create(DelayTime::create(idleDuration),func, NULL);
            s->setTag(IDLE_TIMEOUT_TAG);
            runAction(s);
            stopMove();
        }
            break;
        case ACTORSTATE::CHASE:
        {
            setTargetToActor(targetActor);
            Move2Target(targetMovePos);
        }
            break;
        case ACTORSTATE::RETURN:
        {
            Move2Target(leavePartolPos);
        }
            break;
        case ACTORSTATE::PATROL:
        {
            Move2Target(partolPosVec.at(partolIndex));
        }
            break;
        case ACTORSTATE::WAIT:
        {
            waitTimeOut = false;
            auto func = CallFunc::create(CC_CALLBACK_0(Monster::waitTimeEnough, this));
            
            stopActionByTag(WAIT_TIMEOUT_TAG);
            auto s = Sequence::create(DelayTime::create(waitDuration),func, NULL);
            s->setTag(WAIT_TIMEOUT_TAG);
            runAction(s);
        }
            break;
        case ACTORSTATE::ATTACK:
            
            stopMove();
            break;

        case ACTORSTATE::HURT:
            stopActionByTag(MOVE_ACTION_TAG);
            break;
        case ACTORSTATE::INAIR:
            stopActionByTag(MOVE_ACTION_TAG);
            break;
        case ACTORSTATE::XULI:
        {
            std::string resPath = "armature/charge.ExportJson";
            ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);
            
            auto eff = Armature::create("charge");
//            armature->setScale(0.5f);
            eff->getAnimation()->playWithIndex(0);
            eff->setTag(XULI_EFFECT_TAG);
            frontEffectLayer->addChild(eff);
        }
            break;
        case ACTORSTATE::INIT:
        {
            auto fade = Blink::create(0.5, 3);
            auto func = CallFunc::create(CC_CALLBACK_0(Monster::hasFadeIn, this));
            auto seq = Sequence::create(fade, func, NULL);
            armature->setOpacity(122);
            armature->runAction(seq);
        }
            break;
        case ACTORSTATE::SNEAK:
        {
            bool trianglePath = false;
//            bool trianglePath = (abs(rand()%100)>50);
            
            auto tp = targetActor->getPosition();
            float randBackDis = abs(rand()%100);
            if (randBackDis<10) {
                randBackDis = 0;
            }

            int disxFlag = (tp.x < getPositionX())?1:-1;
            float startPointX = getPositionX() + disxFlag * randBackDis;
            startPointX = MIN(MAP_AREA_RIGHT, startPointX);
            startPointX = MAX(MAP_AREA_LEFT, startPointX);
            
            
            auto startPoint = Point(startPointX, getPositionY());
            
            int disyFlag = (tp.y > (MAP_AREA_TOP + MAP_AREA_BOTTOM) / 2)?-1:1;
            
            float endPointY = getPositionY() + disyFlag * (60 + abs(rand()%10));
            endPointY = MAX(MAP_AREA_BOTTOM, endPointY);
            endPointY = MIN(MAP_AREA_TOP, endPointY);
            
            float dis = abs(tp.x-startPointX) + 100;
            float endPointX = startPointX- (disxFlag*dis*(trianglePath?0.5:1)+rand()%20);
            endPointX = MIN(MAP_AREA_RIGHT, endPointX);
            endPointX = MAX(MAP_AREA_LEFT, endPointX);
            
            auto endPoint = Point(endPointX, endPointY);
            
            sneakPath.clear();
            sneakPath.push_back(endPoint);
            if(!trianglePath)
            {
                auto point2 = Point(startPointX, endPointY);
                sneakPath.push_back(point2);
            }
            Move2Target(startPoint);
//            sneakPath.push_back(startPoint);
        }
            break;
        case ACTORSTATE::SNEAKRUSH:
        {
            auto tp = targetActor->getPosition();
            float randBackDis = abs(rand()%40);
            int disxFlag = targetActor->getFlipX()?1:-1;
            float targetX = tp.x+disxFlag*(30+randBackDis);
            float targetY = tp.y+rand()%20;
            
            targetX = MIN(MAP_AREA_RIGHT, targetX);
            targetX = MAX(MAP_AREA_LEFT, targetX);
            targetY = MAX(MAP_AREA_BOTTOM, targetY);
            targetY = MIN(MAP_AREA_TOP, targetY);
            
            Run2Target(Point(targetX, targetY));
        }
            break;
        case ACTORSTATE::BOUNDWALL:
        {
            asBomb = true;
        }
            break;
        case ACTORSTATE::FELLDOWN:
        {
            fallSpeedY = startFallSpeedY = 0;
            fallAccX = 0;
        }
            break;
        case ACTORSTATE::DIE:
        {
//            auto scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
//            auto hero = dynamic_cast<ActorLayer *>(getParent())->getHero();
//            if (hero == nullptr) {
//                break;
//            }
//            
//            auto guard = hero->Guard;
//            if (guard == nullptr) {
//                break;
//            }
//            
//            popItem();
        }
            break;
        default:
            break;
    }
}

void Monster::popItem()
{
    auto ghostPoint = ItemSpirit::create();
    ghostPoint->initPos(posX, posY+135);
    ghostList.push_back(ghostPoint);
    dynamic_cast<ActorLayer *>(getParent())->getGhostLayer()->addChild(ghostPoint);
}

void Monster::updateGhostPoint()
{
    if (ghostList.empty()) {
        return;
    }
    
    for (auto it = ghostList.begin(); it != ghostList.end(); ) {
        auto ghost = *(it);
        ghost->updatePos();
        if (ghost->getAct() == RELEASE) {
            if (ghost->getCount() > 25) {
                if (addGhost2Guard(ghost)) {
                    ghostList.erase(it);
                    continue;
                }
            }
        }
        ++it;
    }
}
void Monster::addAllGhost2Guard()
{
    if (ghostList.empty()) {
        return;
    }
    
    for (auto it = ghostList.begin(); it != ghostList.end(); ) {
        auto ghost = *(it);
        ghost->updatePos();
        if (ghost->getAct() == RELEASE) {
//            if (ghost->getCount() > 15) {
                if (addGhost2Guard(ghost)) {
                    ghostList.erase(it);
                    continue;
                }
//            }
        }
        ghostList.erase(it);
        ghost->removeFromParent();
        ++it;
    }
}
bool Monster::addGhost2Guard(ItemSpirit *ghost)
{
    ghost->setAct(ABSORB);
    auto hero = dynamic_cast<ActorLayer *>(getParent())->getHero();
    if (hero == nullptr) {
        return false;
    }
    
    auto guard = dynamic_cast<Guardian *>(hero->Guard);
    if (guard == nullptr) {
        return false;
    }
    guard->add2GhostList(ghost);
    return true;
}

void Monster::updateState()
{
//    bool needChange = false;
//    std::string luaFile("test/hello4.lua");
//    std::map<std::string, Value> baseData;
//    baseData["state"] = stateMachine->stateName[state];
//    if (event==stateMachine->action_undefined) {
//        baseData["event"] = "action_undefined";
//    }else{
//        baseData["event"] = stateMachine->eventName[event];
//    }
//    baseData["sneak_empty"] = (sneakPath.empty()?1:0);
//    if (delayEvent==stateMachine->action_undefined) {
//        baseData["delayEvent"] = "action_undefined";
//    }else{
//        baseData["delayEvent"] = stateMachine->eventName[delayEvent];
//    }
//    if (action==stateMachine->action_undefined) {
//        baseData["action"] = "action_undefined";
//    }else{
//        baseData["action"] = stateMachine->eventName[action];
//    }
//    std::map<std::string, void*> objParam;
//    objParam["Monster"] = this;
//    
//    baseData["isFaint"] = (isFaint ? 1 : 0);
//    
//    std::string event_back = PublicSendLuaData::getInstance()->callLuaFuncParReturn(luaFile, "switch_state", baseData, objParam);
////    log("lua switch_state: %s", event_back.c_str());
////    log("lua switch_state: %s", PublicSendLuaData::getInstance()->callLuaFuncParReturn(luaFile, "switch_state", baseData));
//    
//    if (event_back == "NONE") {
//        needChange = false;
//    } else {
//        needChange = true;
//        if(event_back == "delayEvent") {
//            event = delayEvent;
//            delayEvent = StateMachine::action_undefined;
//        }else if(event_back == "action") {
//            event = action;
//        }else if(event_back != "event") {
//            event = stateMachine->findEventVal(event_back);
////        }else {
////            event = event;
//        }
//    }
//    
//    switch (state) {
//        case ACTORSTATE::PATROL:
//            if (event == stateMachine->findEventVal("EVENT_ARRIVE_TARGET")) {
//                if(partolForward){
//                    if (partolIndex>=partolPosVec.size()-1) {
//                        partolIndex--;
//                        partolForward = false;
//                    }else{
//                        partolIndex++;
//                    }
//                    
//                }else{
//                    if (partolIndex == 0) {
//                        partolIndex++;
//                        partolForward = true;
//                    }else{
//                        partolIndex--;
//                    }
//                }
//                
//                posX = getPositionX();
//                posY = getPositionY();
//            }
//            break;
//        case ACTORSTATE::SNEAK:
//            if (event == stateMachine->findEventVal("EVENT_ARRIVE_TARGET")) {
//                sneakPath.pop_back();
//            }
//            break;
//        case ACTORSTATE::FELLDOWN:
//            if (event == stateMachine->findEventVal("EVENT_DIE")) {
//                dieLie = true;
//            }
//            break;
//        case ACTORSTATE::BOUNDWALL:
//            if (event == stateMachine->findEventVal("EVENT_KWG")) {
//                asBomb = true;
//            }
//            break;
//        case ACTORSTATE::DIE:
//            if (armature->getAnimation()->isComplete()) {
//                //                armature->setOpacity(122);
//                //                armature->runAction(Blink::create(0.3, 3));
//                dying = true;
//                needChange = false;
//            }
//            break;
//        case ACTORSTATE::WAIT:
////            log("wait Enough: %d" , waitTimeOut);
////            log("event>>>>>==== %s", event_back.c_str());
//            break;
//        default:
//            break;
//    }
    
    bool needChange = false;
    switch (state) {
        case ACTORSTATE::INIT:
            if (event != stateMachine->action_undefined) {
                needChange= true;
                break;
            }
            break;
        case ACTORSTATE::IDLE:
//            if (event == stateMachine->findEventVal("EVENT_IDLETIMEOUT")) {
//                needChange= true;
//            }
            
            if (event != stateMachine->action_undefined) {
                needChange= true;
                break;
            }

            if (canFindOpponent()) {
                event = stateMachine->findEventVal("EVENT_FIND_ENEMY");
                needChange = true;
            }
            break;
        case ACTORSTATE::PATROL:
            if (event != stateMachine->action_undefined) {
                needChange= true;
                break;
            }

            if (canFindOpponent()) {
                event = stateMachine->findEventVal("EVENT_FIND_ENEMY");
                needChange = true;
            }
            if (arrivePos(targetMovePos)) {
                if(partolForward){
                    if (partolIndex>=partolPosVec.size()-1) {
                        partolIndex--;
                        partolForward = false;
                    }else{
                        partolIndex++;
                    }
                    
                }else{
                    if (partolIndex == 0) {
                        partolIndex++;
                        partolForward = true;
                    }else{
                        partolIndex--;
                    }
                }
                
                posX = getPositionX();
                posY = getPositionY();
                event = stateMachine->findEventVal("EVENT_ARRIVE_TARGET");
                needChange = true;
            }
            break;
        case ACTORSTATE::CHASE:
            if (event != stateMachine->action_undefined) {
                needChange= true;
                break;
            }

            if (arrivePos(targetMovePos)) {
                event = stateMachine->findEventVal("EVENT_ARRIVE_TARGET");
                needChange = true;
            }
            break;
        case ACTORSTATE::BACK:
            if (event != stateMachine->action_undefined) {
                needChange= true;
                break;
            }

            if (arrivePos(targetMovePos)) {
                event = stateMachine->findEventVal("EVENT_ARRIVE_TARGET");
                needChange = true;
            }
            
            break;
            
        case ACTORSTATE::RETURN:
            if (event != stateMachine->action_undefined) {
                needChange= true;
                break;
            }

            if (arrivePos(targetMovePos)) {
                event = stateMachine->findEventVal("EVENT_ARRIVE_TARGET");
                needChange = true;
            }
            if (canFindOpponent()) {
                event = stateMachine->findEventVal("EVENT_FIND_ENEMY");
                needChange = true;
            }
            
            break;
        case ACTORSTATE::SNEAK:

            if (event != stateMachine->action_undefined) {
                needChange= true;
                break;
            }
            if (arrivePos(targetMovePos)) {
                if (sneakPath.empty()) {
                    event = stateMachine->findEventVal("EVENT_ENDSNEAK");
                }else{
                    Move2Target(sneakPath[sneakPath.size()-1]);
                    sneakPath.pop_back();
                    event = stateMachine->findEventVal("EVENT_ARRIVE_TARGET");
                }
                
                needChange = true;
            }
            break;
        case ACTORSTATE::SNEAKRUSH:
            if (event != stateMachine->action_undefined) {
                needChange= true;
                break;
            }
            if (arrivePos(targetMovePos)) {
                event = stateMachine->findEventVal("EVENT_ARRIVE_TARGET");
                needChange = true;
            }
            break;
        case ACTORSTATE::ATTACK:
            if (event != stateMachine->action_undefined) {
                needChange= true;
                break;
            }

            if (armature->getAnimation()->isComplete()) {
                event = stateMachine->findEventVal("EVENT_ACTIONOVER");
                needChange = true;
            }
            break;
        case ACTORSTATE::WAIT:
            if (event != stateMachine->action_undefined) {
                needChange= true;
                break;
            }

            
            if (waitTimeOut) {
                if (lostTarget()) {
                    event = stateMachine->findEventVal("EVENT_LOSTTARGET");
                    needChange = true;
                }else{
                    if (canAttackTarget()) {
                        event = stateMachine->findEventVal("EVENT_CANATTACK");
                        needChange = true;
                    }else if (canChase()){
                        if (needSneak()) {
                            event = stateMachine->findEventVal("EVENT_NEEDSNEAK");
                            needChange = true;
                        }else{
                            event = stateMachine->findEventVal("EVENT_CANCHASE");
                            needChange = true;
                        }
                    }
                }
                
            }
            break;
        case ACTORSTATE::FAINT:
            if (!isFaint) {
                
                event = stateMachine->findEventVal("EVENT_CANATTACK");
                needChange = true;
            }
            break;
        case ACTORSTATE::HURT:
            
            if (event == stateMachine->findEventVal("EVENT_HEADHURT")) {
                needChange = true;
                break;
            }
            if (event == stateMachine->findEventVal("EVENT_WAISTHURT")) {
                needChange = true;
                break;
            }
            if (event == stateMachine->findEventVal("EVENT_HIT2AIR")) {
                needChange = true;
                break;
            }
            
            if (armature->getAnimation()->isComplete()) {
                if (delayEvent == stateMachine->findEventVal("EVENT_HEADFELLGROUND")) {
                    event = delayEvent;
                    delayEvent = StateMachine::action_undefined;
                    needChange = true;
                    break;
                }
                if (delayEvent == stateMachine->findEventVal("EVENT_WAISTFELLGROUND")) {
                    event = delayEvent;
                    delayEvent = StateMachine::action_undefined;
                    needChange = true;
                    break;
                }
                if (isFaint) {
                    event = stateMachine->findEventVal("EVENT_FAINT");
                    needChange = true;
                    break;
                }
                if (action == HEROACTION::HEADHIT) {
                    event = stateMachine->findEventVal("HEADHIT");
                }
                if (action == HEROACTION::WAISTHIT) {
                    event = stateMachine->findEventVal("WAISTHIT");
                }
                
                needChange = true;
//                if (blackActor->getHp() <= 0) {
//                    dying = true;
//                    needChange = false;
//                }
            }

            break;
        case ACTORSTATE::FELLDOWN:
//            if (event == stateMachine->findEventVal("EVENT_KG")) {
//                needChange = true;
//                break;
//            }
            if (armature->getAnimation()->isComplete()) {
                if (action == HEROACTION::HEADFELLDOWN) {
                    event = stateMachine->findEventVal("HEADFELLDOWN");
                    if (blackActor->getHp() <= 0) {
                        event = stateMachine->findEventVal("EVENT_DIE");
                        dieLie = true;
                    }
                }
                if (action == HEROACTION::WAISTFELLDOWN) {
                    event = stateMachine->findEventVal("WAISTFELLDOWN");
                    if (blackActor->getHp() <= 0) {
                        event = stateMachine->findEventVal("EVENT_DIE");
                        dieLie = true;
                    }
                }
                if (action == HEROACTION::GETUP) {
                    if (isFaint) {
                        event = stateMachine->findEventVal("EVENT_FAINT");
                        needChange = true;
                        break;
                    }else {
                        event = stateMachine->findEventVal("GETUP");
                    }
                    
                }
                if (action == HEROACTION::LIE) {
                    event = stateMachine->findEventVal("LIE");
                }
                if (action == HEROACTION::LIESHOCK) {
                    event = stateMachine->findEventVal("LIESHOCK");
                    if (blackActor->getHp() <= 0) {
                        event = stateMachine->findEventVal("EVENT_DIE");
                        dieLie = true;
                    }
                }
                needChange = true;
            }
            break;
            
        case ACTORSTATE::DIE:
            if (armature->getAnimation()->isComplete()) {
//                armature->setOpacity(122);
//                armature->runAction(Blink::create(0.3, 3));
                dying = true;
                needChange = false;
            }
            break;
            
        case ACTORSTATE::INAIR:
            if (event == stateMachine->findEventVal("EVENT_HIT2AIR") ||
                event == stateMachine->findEventVal("EVENT_HEADHURT") ||
                event == stateMachine->findEventVal("EVENT_WAISTHURT") ||
                event == stateMachine->findEventVal("EVENT_HEADFELLGROUND") ||
                event == stateMachine->findEventVal("EVENT_WAISTFELLGROUND") ||
                event == stateMachine->findEventVal("EVENT_FAINT")) {
                
                event = stateMachine->findEventVal("EVENT_AIRHIT");
                needChange = true;
                break;
            }
            if (isLandGround() && action == HEROACTION::AIRHITDOWN) {
                event = stateMachine->findEventVal("EVENT_LANDGROUND");
                needChange = true;
            }
            if (armature->getAnimation()->isComplete()) {
                if (action == HEROACTION::AIRHITDOWN) {
                    break;
                }
                event = action;
                needChange = true;
            }
            break;
        case ACTORSTATE::BOUNDGROUND:
            if (armature->getAnimation()->isComplete()) {
                event = stateMachine->findEventVal("EVENT_KGE");
                needChange = true;
            }
            break;
        case ACTORSTATE::BOUNDWALL:
            if (action == HEROACTION::BOUND2W) {
                if (YNCamera::getInstance()->isOutWindow(getPosition())) {
                    event = stateMachine->findEventVal("EVENT_KWG");
                    needChange = true;
                    asBomb = false;
                } else if (armature->getAnimation()->isComplete()) {
                    event = stateMachine->findEventVal("EVENT_ACTIONOVER");
                    needChange = true;
                }
            } else {
                if (armature->getAnimation()->isComplete()) {
                    event = stateMachine->findEventVal("EVENT_KWE");
                    needChange = true;
                }
            }
            break;
        default:
            break;
    }
    if(event == stateMachine->action_undefined){
        needChange = false;
        return;
    }
    
    std::string eventStr = stateMachine->eventName[event];
    if (eventStr == "EVENT_HEADHURT" || eventStr == "EVENT_WAISTHURT" || eventStr == "EVENT_HEADFELLGROUND" || eventStr == "EVENT_WAISTFELLGROUND" || eventStr == "EVENT_HIT2AIR" || eventStr == "EVENT_AIRHIT" || eventStr == "EVENT_KW" || eventStr == "EVENT_KG") {
        state = ACTORSTATE::ANY;
        needChange = true;
    }
//    if (event == stateMachine->findEventVal("EVENT_HEADHURT")|| event == stateMachine->findEventVal("EVENT_WAISTHURT") || event == stateMachine->findEventVal("EVENT_HEADFELLGROUND") || event == stateMachine->findEventVal("EVENT_WAISTFELLGROUND") || event == stateMachine->findEventVal("EVENT_HIT2AIR") || event == stateMachine->findEventVal("EVENT_AIRHIT") || event == stateMachine->findEventVal("EVENT_KW") || event == stateMachine->findEventVal("EVENT_KG")) {
//        state = ACTORSTATE::ANY;
//        needChange = true;
//    }
    
    if (needChange) {
        switch2NextState(state, event);
        
        needChange = false;
        event = StateMachine::action_undefined;
    }
}

void Monster::updateAI()
{
    posX = getPositionX();
    posY = getPositionY();
    auto boneMoveVec2 = calBoneMove();

    updateFrontEffect();
    updateBackEffect();
    
    //状态内执行
//    switch (state) {
//        case ACTORSTATE::WALK:
    if (currDir != DIRECT::NONE) {
        if (((currDir & DIRECT::LEFT)!=0) != flipX)
        {
            flipX = !flipX;
            float sx = blackActor->getScaleRate();
            armature->setScaleX((flipX) ? -sx : sx);
        }
    }
    switch (state) {
        case ACTORSTATE::IDLE:
        {
//            currHitDownVal++;
//            currHitDownVal = MIN(deHitDownVal, currHitDownVal);
        }
            break;
        case ACTORSTATE::MOVE:
        case ACTORSTATE::PATROL:
        case ACTORSTATE::RETURN:
        case ACTORSTATE::CHASE:
        case ACTORSTATE::BACK:
        
        {
            return;
        }
            break;
        case ACTORSTATE::SNEAK:
        case ACTORSTATE::SNEAKRUSH:
        {
            flipX = (getPositionX()>targetActor->getPositionX());
            float sx = blackActor->getScaleRate();
            armature->setScaleX((flipX) ? -sx : sx);
        }
            break;
        case ACTORSTATE::WAIT:
        case ACTORSTATE::ATTACK:
            if (targetActor == nullptr) {
                break;
            }
            if (event != stateMachine->action_undefined) {
                break;
            }
            if(targetActor->getPositionX() > getPositionX())
            {
                setDir(DIRECT::RIGHT);
            }else{
                setDir(DIRECT::LEFT);
            }
            break;
        case ACTORSTATE::HURT:
        {
            if (chatterLoop != 0) {
                armature->getAnimation()->pause();
                posX = getPositionX() + chatterOffX[chatterIndex]*((flipX) ? -1 : 1);
                chatterIndex++;
                if (chatterIndex >= 3) {
                    chatterLoop--;
                    chatterIndex = 1;
                    if (chatterLoop == 0) {
                        if (killSkill != nullptr) {
                            startHurtStiff(killSkillTag->getHitStiffDur());
                        }else{
                            startHurtStiff(0.1);
                        }
//                        startHurtStiff(killSkill->getHitStiffDur());
                    }
                }
            }else{
                if (hurtStiff) {
                    posX = getPositionX() + hurtMoveSpeed;
                }else{
                    posX = getPositionX();
                }
            }
            
            
//            posX = MIN(1900, posX);
//            posX = MAX(20, posX);
//            setPositionX(posX);
        }
            break;
        case ACTORSTATE::FELLDOWN:
            if (action == HEROACTION::LIESHOCK) {
                posX = getPositionX() + lieShockSpeed;
            }
            break;
        case ACTORSTATE::BOUNDGROUND:
            if (killSkill != nullptr ) {
                boneMoveVec2.y *= killSkillTag->getBoundUpRate();
            }
            break;
        case ACTORSTATE::INAIR:
        {
            if (chatterLoop != 0) {
                armature->getAnimation()->pause();
                posX = getPositionX() + chatterOffX[chatterIndex]*((flipX) ? -1 : 1);
                chatterIndex++;
                if (chatterIndex >= 3) {
                    chatterLoop--;
                    chatterIndex = 1;
                    if (chatterLoop == 0) {
                        startHurtStiff(killSkillTag->getAirHitStiffDur());
                    }
                }
            }else{
                if (action == HEROACTION::AIRHITDOWN) {
                    fallSpeedY += fallAccY;
                    fallAccY *= 1.15;
                    fallSpeedY = MIN(30, fallSpeedY);
                    boneMoveVec2.y = -fallSpeedY;
                }
                
                if (killSkill != nullptr) {
                    if (action == HEROACTION::AIRHIT)
                    {
                        boneMoveVec2.y = killSkillTag->getAirAtkUpVal();
                    }else if (action == HEROACTION::AIRHITUP) {
                        if(killSkillTag->getFloatRate() != 99){
                            boneMoveVec2.y *= killSkillTag->getFloatRate();
                        }
                    }
                    float hitSpeed = killSkillTag->getAirHitBackSpeed();
                    if (killSkillTag->gethitFlyRate() != 99) {
                        hitSpeed *= killSkillTag->gethitFlyRate();
                    }
                    
                    if (killSkillTag->getHitDownVal() > getDeHitDownVal()) {
                        if (hurtMoveSpeed == 0) {
                            hurtMoveSpeed = hitSpeed * ((currDir==DIRECT::RIGHT) ? -1 : 1) * (backInAir?-1:1);
                        }
                        hurtMoveSpeed += fallAccX* ((currDir==DIRECT::RIGHT) ? -1 : 1) * (backInAir?-1:1);
                        fallAccX *= 1.25;
                        if (hurtMoveSpeed > 0) {
                            hurtMoveSpeed = MIN(10, hurtMoveSpeed);
                        }else{
                            hurtMoveSpeed = MAX(-10, hurtMoveSpeed);
                        }
                    }else{
                        hurtMoveSpeed = hitSpeed * ((currDir==DIRECT::RIGHT) ? -1 : 1) * (backInAir?-1:1);
                    }
                    
                    posX = getPositionX() + hurtMoveSpeed;
                    
                }else{
                    posX = getPositionX() - 0.5 *((flipX) ? -1 : 1) * (backInAir?-1:1);
                }
//                if (hurtStiff) {
//                    posX = getPositionX() + hurtMoveSpeed;
//                }else{
//                    posX = getPositionX();
//                }
            }
            
                
//            }
        }
            break;
            
        case ACTORSTATE::DIE:
        {
            bool visual = armature->isVisible();
            armature->setVisible(!visual);
        }
            break;
        default:
            break;
    }
    
    if (killSkillTag != nullptr) {
        if (killSkillTag->gethitFlyRate() != 99) {
            boneMoveVec2.x *= killSkillTag->gethitFlyRate();
        }
    }
    setActorShowPos(boneMoveVec2);
    
    updateGhostPoint();
}

void Monster::doFlag(int nextFlag)
{
    switch (nextFlag) {
        case StateAIFlag::startFall:
        {
//            armature->setPositionY(localBonePoint.y);
//            localBonePoint.y = 0;
            //            float originOffy = armature->getBone("OriginPoint")->getWorldInfo()->y;
            //            fallStartY += armature->getBone(localBodyName)->getWorldInfo()->y - originOffy;
            //            armature->setPositionY(fallStartY);
        }
            break;
        case StateAIFlag::endFall:
            //            fallStartY = 0;
            armature->setPositionY(0);
        default:
            break;
    }

}


void Monster::Hurt(int hurtVal)
{

}

//void Monster::changeSkill(int event)
//{
//    currSkill = nullptr;
//    currSkillTag = nullptr;
//    if(event == stateMachine->findEventVal("ATTACKPART1")){
//        blackActor->equipSkills[ATK_KEY] = blackActor->getAtk1SkillID();
//        currSkill = blackActor->selSkills[blackActor->equipSkills[ATK_KEY]];
////        currSkill = blackActor->selSkills[blackActor->getAtk1SkillID()];
//        currSkillTag = blackActor->selSkillTags[currSkill->getSkillID()*100+1];
//    }
//    if(event == stateMachine->findEventVal("ATTACKPART2")){
//        blackActor->equipSkills[ATK_KEY] = blackActor->getAtk2SkillID();
//        currSkill = blackActor->selSkills[blackActor->equipSkills[ATK_KEY]];
////        currSkill = blackActor->selSkills[blackActor->getAtk2SkillID()];
//        currSkillTag = blackActor->selSkillTags[currSkill->getSkillID()*100+1];
//    }
//    if(event == stateMachine->findEventVal("ATTACKPART3")){
//        blackActor->equipSkills[ATK_KEY] = blackActor->getAtk3SkillID();
//        currSkill = blackActor->selSkills[blackActor->equipSkills[ATK_KEY]];
////        currSkill = blackActor->selSkills[blackActor->getAtk3SkillID()];
//        currSkillTag = blackActor->selSkillTags[currSkill->getSkillID()*100+1];
//    }
//    if(event == stateMachine->findEventVal("ATTACKPART4")){
//        blackActor->equipSkills[ATK_KEY] = blackActor->getAtk4SkillID();
//        currSkill = blackActor->selSkills[blackActor->equipSkills[ATK_KEY]];
////        currSkill = blackActor->selSkills[blackActor->getAtk4SkillID()];
//        currSkillTag = blackActor->selSkillTags[currSkill->getSkillID()*100+1];
//    }
//    
//    if (currSkill != nullptr) {
////        addBuff(true);
//        SimpleAudioEngine::getInstance()->setEffectsVolume(0.8);
//        SimpleAudioEngine::getInstance()->playEffect(currSkillTag->getSkillSoundRes().c_str(),false,1,0,0.5);
//    }
//}




void Monster::dispatchResetPunchTag()
{
    EventCustom event(MONSTER_RESET_PUNCH);
    event.setUserData(this);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

//void Monster::waitTimeEnough()
//{
//    waitTimeOut = true;
//    event = stateMachine->findEventVal("EVENT_WAITTIMEOUT");
//}

void Monster::hasFadeIn()
{
    event = stateMachine->findEventVal("EVENT_FADEIN");
    armature->setOpacity(255);
}
//bool Monster::canFindOpponent()
//{
////    return false;
//    
//    auto enemiesInView = dynamic_cast<ActorLayer *>(getParent())->findEnemies(this);
//    if (enemiesInView.empty()) {
//        targetActor = nullptr;
//        return false;
//    }
//    
//    auto opponent = selectOpponent(enemiesInView);
//    if (opponent == nullptr) {
//        targetActor = nullptr;
//        return false;
//    }
//    
//    targetActor = opponent;
//    return true;
//}

//std::vector<FightActor *> Monster::findEnemies(Vector<FightActor *> actors)
//{
//    std::vector<FightActor *> result;
//    auto size = actors.size();
//    
//    auto viewRect = Rect(getPositionX()-viewSize.width/2, MAP_AREA_BOTTOM, viewSize.width, viewSize.height);
//    for (size_t i=0; i<size; i++) {
//        FightActor *actor = actors.at(i);
//        if (actor->getDying() || actor->getDieLie()) {
//            continue;
//        }
//        if (viewRect.containsPoint(actor->getPosition())) {
//            result.push_back(actor);
//        }
//    }
//    return result;
//}


//FightActor* Monster::selectOpponent(std::vector<FightActor *> enemies)
//{
//    FightActor *result = nullptr;
//    auto size = enemies.size();
//    int minDis = viewSize.width;
//    for (size_t i=0; i<size; i++) {
//        FightActor *actor = enemies.at(i);
//        if (actor->getDying() || actor->getDieLie()) {
//            continue;
//        }
//        if (abs(actor->getPosition().getDistance(getPosition())) < minDis) {
//            minDis = abs(actor->getPosition().getDistance(getPosition()));
//            result = actor;
//        }
//    }
//    
//    return result;
//}

//void Monster::setTargetToActor(FightActor *actor)
//{
//    auto originPos = actor->getPosition();
//
//    
//    float maxAtkDis = 0;
//    float minAtkDis = 0;
//    if (actor->getPositionX() >= getPositionX()) {
//        auto atkRect = getAtkRect(false);
//        maxAtkDis = atkRect.getMaxX();
//        minAtkDis = MAX(0, atkRect.getMinX());
//    }else{
//        auto atkRect = getAtkRect(true);
//        maxAtkDis = atkRect.getMinX();
//        minAtkDis = MIN(0,atkRect.getMaxX());
//    }
//    float tx = originPos.x + rand() % abs((int)(maxAtkDis - minAtkDis)) + minAtkDis;
//    float ty = originPos.y + rand() % 20;
//    
//    tx = MIN(MAP_AREA_RIGHT, tx);
//    tx = MAX(MAP_AREA_LEFT, tx);
//    ty = MIN(ty, MAP_AREA_TOP);
//    ty = MAX(ty, MAP_AREA_BOTTOM);
//    targetMovePos = Point(tx, ty);
//}

//bool Monster::lostTarget()
//{
////    return true;
//    if (targetActor == nullptr) {
//        return true;
//    }
//    if(targetActor->getDying() || targetActor->getDieLie())
//    {
//        targetActor = nullptr;
//        return true;
//    }
//    auto viewRect = Rect(getPositionX()-viewSize.width/2, MAP_AREA_BOTTOM, viewSize.width, viewSize.height);
//    if (!viewRect.containsPoint(targetActor->getPosition())) {
//        targetActor = nullptr;
//        return true;
//    }
//    return false;
//}

//bool Monster::canAttackTarget()
//{
////    return false;
//    if (targetActor->getDying() || targetActor->getDieLie()) {
//        targetActor = nullptr;
//        return false;
//    }
//    Rect atkRect;
//    if (targetActor->getPositionX() >= getPositionX()) {
//        atkRect = getAtkRect(false);
//    }else{
//        atkRect = getAtkRect(true);
//    }
//
//    atkRect.origin += getPosition();
//    atkRect.origin.y -= 40;
//    atkRect.size.height = 80;
//    if (atkRect.containsPoint(targetActor->getPosition())) {
//        return true;
//    }
//    return false;
//}

//bool Monster::canChase(){
////    return false;
//    if (targetActor->getDying() || targetActor->getDieLie()) {
//        targetActor = nullptr;
//        return false;
//    }
//    auto viewRect = Rect(getPositionX()-viewSize.width*2/3, MAP_AREA_BOTTOM, viewSize.width*4/3, viewSize.height);
//    return viewRect.containsPoint(targetActor->getPosition());
//}
//
//bool Monster::needSneak()
//{
////    return false;
//    if (targetActor == nullptr) {
//        return false;
//    }
//
//    if(targetActor->getAtking())
//    {
//        if (targetActor->getAtkRect(targetActor->getFlipX()).size.width > targetActor->getPosition().getDistance(getPosition())) {
//            return true;
//        }
//    }
//    return false;
//}

void Monster::setMp(float val)
{
    float mp = MAX(0, val);
    mp = MIN(blackActor->getMaxMp(), mp);
    blackActor->setMp(mp);
}

void Monster::addAv(float val)
{
    float av = blackActor->getAV() + val;
    if (av >= blackActor->getMaxAV()) {
        if (blackActor->getAp() >= blackActor->getMaxAp()) {
            blackActor->setAp(blackActor->getMaxAV()-1);
        }else{
            blackActor->setAV(0);
            blackActor->setAp(blackActor->getAp()+1);
        }
    }else{
        blackActor->setAV(av);
    }
}

void Monster::useAp(float val)
{
    float ap = blackActor->getAp() - val;
    ap = MAX(0, ap);
    blackActor->setAp(ap);
}

void Monster::setHp(float hp)
{
    blackActor->setHp(hp);
//    GameScene::updateHp(hp, blackActor->getMaxHp());
}
