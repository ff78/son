//
//  FightActor.cpp
//  soul
//
//  Created by ff on 14-9-15.
//
//

#include "FightActor.h"
#include "Hero.h"
#include "Effect.h"
#include "../Utils/BaseUtils.h"
#include "YNCamera.h"
#include "ClientLogic/GameScene/HitEffectLayer.h"
#include "ClientLogic/GameScene/ActorLayer.h"
#include "ClientLogic/GameScene/GameScene.h"
#include "DataModule/FightFormula.h"
#include "TouchSkill/SkillDefine.h"
#include "Colossus.h"
#include "Guardian.h"

USING_NS_CC;
using namespace cocostudio;
using namespace CocosDenshion;

FightActor::FightActor()
{
	walkSpeedX = WALK_SPEED;
	rushSpeedX = RUSH_SPEED;

	fallSpeedY = 3;
	fallAccY = 0.3;
    fallAccX = 0;
    startFallSpeedY = 0;
	chatterOffX[0] = -3;
	chatterOffX[1] = 3;
	chatterOffX[2] = -3;
	chatterLoop = 0;
	chatterIndex = 0;

	totalComboDuration = 0;
	comboDuration = 5;
    schedule(schedule_selector(FightActor::skillCDClock), 0);
    schedule(schedule_selector(FightActor::recoverAttr), 0.2);
}
void FightActor::skillCDClock(float dt)
{
    for (int i = KEY_SKILL::SKILLA_KEY; i <= KEY_SKILL::SKILLD_KEY; i++) {
        int skillId = blackActor->equipSkills[i];
        if (skillId <= 0) {
            continue;
        }
        
        blackActor->selSkills[skillId]->updateClock(dt);
    }
}
void FightActor::recoverAttr(float dt)
{
    setMp(blackActor->getMp()+blackActor->getMpRecover());
}

FightActor::~FightActor()
{
    unscheduleAllSelectors();
//	removeHurtListener();
}

void FightActor::removeHurtListener()
{
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(MONSTER_HURT_TAG);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(HERO_RESET_PUNCH);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(HERO_HURT_TAG);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(MONSTER_RESET_PUNCH);
}

void FightActor::changeActionWithName(int nextAction)
{
    if (nextAction == HEROACTION::AIRHITDOWN) {
        if (action == HEROACTION::BOUNDBACK){
            fallAccY = 0.2f;
            fallSpeedY = 15.0f;
        }else if (action == HEROACTION::AIRHITUP) {
            fallAccY = 0.2f;
            if (startFallSpeedY == 0) {
                fallSpeedY = 3.0f;
            }else{
                fallSpeedY = startFallSpeedY/3;
            }
            
        }else{
            fallAccY = 0.07f;
            if (startFallSpeedY == 0) {
                fallSpeedY = 0.8f;
            }else{
                fallSpeedY = startFallSpeedY/3;
            }
        }
    }
    
    int actAction = getSkillAction(nextAction);
    std::vector<std::string> actionName = stateMachine->findActionNames(actAction);
    if (actionName.size() != 0) {
        if (actionName.size() == 1)
        {
            armature->getAnimation()->play(actionName[0]);
        }else{
            armature->getAnimation()->playWithNames(actionName, -1, false);
        }
    }
    
    frameCommand = 0;
    
    atking = attackHead = attackWaist = attackFoot = hit2Air = false;
    hit2Ground = hit2Wall = false;
    attackTag = -1;
    isValidAtk = false;
    action = actAction;
    localBonePoint = Point::ZERO;
    dispatchResetPunchTag();
}


Rect FightActor::getAtkRect(bool flip)
{
    if(flip)
    {
        return Rect(-220, 0, 320, 100);
    }
    return Rect(-100, 0, 320, 100);
}

Rect FightActor::getBombAtkRect()
{
    return Rect(-100, -35, 200, 70);
}

void FightActor::DeStiff()
{
    hurtStiff = false;
    atkStiff = false;
    armature->getAnimation()->resume();
    auto frt = frontEffectLayer->getChildren();
    for (auto effObj : frt) {
        auto eff = dynamic_cast<Effect *>(effObj);
        eff->getArmature()->getAnimation()->resume();
    }
    auto back = backEffectLayer->getChildren();
    for (auto effObj : back) {
        auto eff = dynamic_cast<Effect *>(effObj);
        eff->getArmature()->getAnimation()->resume();
    }
//    hurtMoveSpeed = 0;
//    if (killer != nullptr) {
//        log("de stiff");
//        killer->DeStiff();
////        killer = nullptr;
//    }
    
}


void FightActor::startAtkStiff(float duration)
{
    hurtStiff = false;
    atkStiff = true;
    armature->getAnimation()->pause();
    auto frt = frontEffectLayer->getChildren();
    for (auto effObj : frt) {
        auto eff = dynamic_cast<Effect *>(effObj);
        eff->getArmature()->getAnimation()->pause();
    }
    auto back = backEffectLayer->getChildren();
    for (auto effObj : back) {
        auto eff = dynamic_cast<Effect *>(effObj);
        eff->getArmature()->getAnimation()->pause();
    }
    
    auto func1 = CallFunc::create(CC_CALLBACK_0(FightActor::DeStiff, this));
    
    runAction(Sequence::create(DelayTime::create(duration), func1, NULL));
}

void FightActor::startHurtStiff(float duration)
{
    hurtStiff = true;
    atkStiff = false;
//    armature->getAnimation()->pause();
    auto func1 = CallFunc::create(CC_CALLBACK_0(FightActor::DeStiff, this));
    
    runAction(Sequence::create(DelayTime::create(duration), func1, NULL));

}

void FightActor::addCombo()
{
//    changeCombo = true;
    totalComboDuration += comboDuration;
    comboNum++;
    showCombo = true;
    maxCombo = MAX(maxCombo, comboNum);
    auto comboClearDalay = DelayTime::create(comboDuration);
    auto func1 = CallFunc::create(CC_CALLBACK_0(FightActor::clearCombo, this));
    runAction(Sequence::create(comboClearDalay, func1, NULL));
    
    if (typeid(* this) == typeid(Hero)) {
        GameScene::changeCombo();
    }
}

void FightActor::clearCombo()
{    
    totalComboDuration -= comboDuration;
    if (totalComboDuration <= 0) {
        showCombo = false;
        comboNum = 0;
    }
}

int FightActor::getCurrAction()
{
    return action;
}

bool FightActor::isLandGround()
{
    return armature->getPositionY() <= 0;
}

void FightActor::resetPunchTag(cocos2d::EventCustom* event)
{
//    killerTag = -1;
//    killerAction = -1;
    if(dieLie)
    {
        return;
    }
    if(killers.empty())
    {
        return;
    }
    Actor *killActor = static_cast<Actor *>(event->getUserData());
    auto actor = killers.find(killActor);
    if (actor != killers.end()) {
        killers.erase(actor);
    }
    //    killer = nullptr;
    //    log("reset killer tag");
}

void FightActor::parseHurtEvent(EventCustom* event)
{
    auto pair = static_cast<fightPair *>(event->getUserData());
    
    if ((*pair).defender != this) {
        return;
    }
    
    if (typeid(*(*pair).attacker) == typeid(Bullet)) {
        auto collider = static_cast<Bullet *>((*pair).attacker);
        auto oldKill = killers.find(collider);
        if (oldKill != killers.end()) {
            int actionAndTag = oldKill->second;
            int tag = actionAndTag;
            
            if (tag == collider->getAttackTag()) {
                return;
            }
        }
        
        if(dieLie)
        {
            return;
        }
        
        if (state == ACTORSTATE::FELLDOWN)
        {
            if (!collider->getHit2Ground()) {
                return;
            }
        }
        else if (state == ACTORSTATE::INIT)
        {
            return;
        }
        
        
        killers[collider] = collider->getAttackTag();
        
        
        killBullet = collider;
        
        if (killBullet->getAtking()) {
            skillBulletHurt();
        }
    } else {
        auto collider = static_cast<FightActor *>((*pair).attacker);
        auto oldKill = killers.find(collider);
        if (oldKill != killers.end()) {
            int actionAndTag = oldKill->second;
            int tag = actionAndTag;
            
            if (tag == collider->getAttackTag()) {
                return;
            }
        }
        if(dieLie)
        {
            return;
        }
        
        if (state == ACTORSTATE::FELLDOWN)
        {
            if (!collider->getHit2Ground()) {
                return;
            }
        }
        else if (state == ACTORSTATE::INIT)
        {
            return;
        }
        
        
        killers[collider] = collider->getAttackTag();
        
        
        killer = collider;
        
        if (killer->getAtking()) {
            hurt();
        }else if(killer->getAsBomb()){
            bodyHurt();
        }
    }
    
    

}

void FightActor::bulletHurt(Bullet *bullet)
{
    if (state == ACTORSTATE::FELLDOWN || state == ACTORSTATE::INIT || dieLie)
    {
        return;
    }
    
    auto hitEffect = dynamic_cast<HitEffectLayer *>(hurtEffectLayer->getParent());
//    if(abs(rand())%100<10)
//    {
//        hitEffect->addMissFlag(getPosition());
//        return;
//    }
    
    bool crit = false;
    if (bullet->getOwner() != nullptr) {
        auto gun = dynamic_cast<FightActor *>(bullet->getOwner());
        if (gun->dieLie) {
            crit = false;
        }else{
            crit = FightFormula::instance()->isCirt(gun->getBlackActor(), blackActor);
        }
    }else{
        crit = false;
    }
    
    float hurtVal = 0;
    hurtVal = FightFormula::instance()->calBulletHurt(bullet->getBlackBullet(), blackActor);
    
    if (crit) {
        hurtVal *= 2;
        if (typeid(*this) != typeid(Hero))
        {
            hitEffect->addCritHurtNum(hurtVal, getPosition());
            hitEffect->addCritFlag(getPosition());
        }
        
    }else{
        if (typeid(*this) != typeid(Hero))
        {
            hitEffect->addHurtNum(hurtVal, getPosition());
        }
    }
    
    
    float hp = blackActor->getHp() - hurtVal;
    hp = MAX(0, hp);
    setHp(hp);
    
    if(bullet->getOwner() != nullptr)
    {
        if (!dynamic_cast<FightActor *>(bullet->getOwner())->getDieLie()) {
            dynamic_cast<FightActor *>(bullet->getOwner())->addCombo();
        }
    }
    

    addBuff(false, bullet->getSkillTag());
    if (currSkill != nullptr) {
        if(!currSkill->getCanBreak())
        {
            return;
        }
    }
    if (isPA && hp > 0) {
        return;
    }

    currHitDownVal -= bullet->getHitDownVal();
    
    if (armature->getPositionY()>0) {
        this->event = stateMachine->findEventVal("EVENT_AIRHIT");
    } else {
        this->event = stateMachine->findEventVal("EVENT_WAISTHURT");
        if(currHitDownVal <= 0) {
            if (FightFormula::instance()->isHitDown(this->getBlackActor())) {
                this->delayEvent = stateMachine->findEventVal("EVENT_WAISTFELLGROUND");
                currHitDownVal = 0;
            }else{
                currHitDownVal = 1;
                addSingleBUff(true, 34, 100);
            }
            
        }
    }
    if (blackActor->getHp() <= 0 && !hpEmpty) {
        hpEmpty = true;
        this->delayEvent = stateMachine->findEventVal("EVENT_WAISTFELLGROUND");
        currHitDownVal = 0;
        if (typeid(*this) == typeid(Monster)) {
            if(dynamic_cast<ActorLayer *>(getParent())->getHero()->Guard != nullptr)
            {
                dynamic_cast<Monster *>(this)->popItem();
            }
        }
    }
    
    if (bullet->getFlipX()) {
        setDir(DIRECT::RIGHT);
    } else {
        setDir(DIRECT::LEFT);
    }
    
    float hitSpeed = 0;
    if (armature->getPositionY() > 0) {
        chatterLoop = 1;
        chatterOffX[0] = -3;
        chatterOffX[1] = 3;
        chatterOffX[2] = -3;
        hitSpeed = 5;
    }else{
        chatterLoop = 1;
        chatterOffX[0] = -3;
        chatterOffX[1] = 3;
        chatterOffX[2] = -3;
        hitSpeed = 3;
    }
    hurtMoveSpeed = hitSpeed * ((bullet->getFlipX()) ? -1 : 1);
    lieShockSpeed = hurtMoveSpeed/3;
    
    //            SimpleAudioEngine::getInstance()->preloadEffect(killSkill->getHitSoundRes().c_str());
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.8);
    SimpleAudioEngine::getInstance()->playEffect(bullet->getSkillTag()->getHitSoundRes().c_str(),false,1,0,0.5);
    
    armature->getAnimation()->pause();
    

//    bullet->getOwner()->addCombo();
//    killer->addCombo();
    
    auto hurtEffect = Effect::create();
    hurtEffect->initWithRes(bullet->getSkillTag()->getHitEffect(), 1);
    std::string boneName("WaistHurtPoint");
    auto info = armature->getBone(boneName)->getWorldInfo();
    
    hurtEffect->setOriginX((flipX?-1:1) * info->x+rand()%10);
    hurtEffect->setOriginY(info->y+rand()%10);
    
    hurtEffect->setPosition(Vec2(hurtEffect->getOriginX(), hurtEffect->getOriginY()));
    
    auto arm = hurtEffect->getArmature();
    arm->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(FightActor::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    
    hurtEffectLayer->addChild(hurtEffect);
    
}
void FightActor::bodyHurt()
{
    float hp;
    auto hitEffect = dynamic_cast<HitEffectLayer *>(hurtEffectLayer->getParent());
    bool crit = false;
    crit = FightFormula::instance()->isCirt(killer->getBlackActor(), blackActor);
    float hurtVal = killer->getBombHitVal()/2;
    
    if (crit) {
        hurtVal *= 2;
        if (typeid(*this) != typeid(Hero))
        {
            hitEffect->addCritHurtNum(hurtVal, getPosition());
            hitEffect->addCritFlag(getPosition());
        }
        
    }else{
        if (typeid(*this) != typeid(Hero))
        {
            hitEffect->addHurtNum(hurtVal, getPosition());
        }
    }
    
    hp = blackActor->getHp() - hurtVal;
    hp = MAX(0, hp);
    setHp(hp);
    
    if (isPA && hp > 0) {
        return;
    }
    
    currHitDownVal -= killer->getBombHitDownVal();

    if (armature->getPositionY() > 0) {
        this->event = stateMachine->findEventVal("EVENT_AIRHIT");
    } else {
            this->event = stateMachine->findEventVal("EVENT_HEADHURT");
        if (blackActor->getHp() <= 0) {
            this->delayEvent = stateMachine->findEventVal("EVENT_WAISTFELLGROUND");
            currHitDownVal = 0;
        }else if(currHitDownVal <= 0){
            if (FightFormula::instance()->isHitDown(this->getBlackActor())) {
                this->delayEvent = stateMachine->findEventVal("EVENT_WAISTFELLGROUND");
                currHitDownVal = 0;
            }else{
                currHitDownVal = 1;
                addSingleBUff(true, 34, 100);
            }
            
        }
    }
    
    if (killer->getFlipX()) {
        setDir(DIRECT::RIGHT);
    }else{
        setDir(DIRECT::LEFT);
    }
    
    chatterLoop = 5;
    chatterOffX[0] = -3;
    chatterOffX[1] = 3;
    chatterOffX[2] = -3;
    hurtMoveSpeed = 6 * ((killer->flipX) ? -1 : 1);
    lieShockSpeed = hurtMoveSpeed/3;
    
    //            SimpleAudioEngine::getInstance()->preloadEffect(killSkill->getHitSoundRes().c_str());
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.8);
    SimpleAudioEngine::getInstance()->playEffect("hit2.wav",false,1,0,0.5);
    
    auto hurtEffect = Effect::create();
    hurtEffect->initWithRes("effect_hit2", 1);
    std::string boneName("HeadHurtPoint");
    auto info = armature->getBone(boneName)->getWorldInfo();
    
    hurtEffect->setOriginX((flipX?-1:1) * info->x+rand()%10);
    hurtEffect->setOriginY(info->y+rand()%10);
    
    hurtEffect->setPosition(Vec2(hurtEffect->getOriginX(), hurtEffect->getOriginY()));
    
    auto arm = hurtEffect->getArmature();
    arm->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(FightActor::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    
    hurtEffectLayer->addChild(hurtEffect);
}

void FightActor::skillBulletHurt()
{
    killSkill = killBullet->getCurrSkill();
    killSkillTag = killBullet->getCurrSkillTag();
    
    float hp;
    auto hitEffect = dynamic_cast<HitEffectLayer *>(hurtEffectLayer->getParent());
    
    bool crit = false;
    if (killBullet->getOwner() != nullptr) {
        auto gun = dynamic_cast<FightActor *>(killBullet->getOwner());
        if (gun->dieLie) {
            crit = false;
        }else{
            crit = FightFormula::instance()->isCirt(gun->getBlackActor(), blackActor);
        }
    }else{
        crit = false;
    }
    
    float hurtVal = 0;
    if (killBullet->getOwner() != nullptr) {
        hurtVal = FightFormula::instance()->calSkillHurt(killSkillTag, killBullet->getOwner()->getBlackActor(), blackActor);
    }else{
        hurtVal = FightFormula::instance()->calBulletHurt(killBullet->getBlackBullet(), blackActor);
    }
    
    if (crit) {
        hurtVal *= 2;
        if (typeid(*this) != typeid(Hero))
        {
            hitEffect->addCritHurtNum(hurtVal, getPosition());
            hitEffect->addCritFlag(getPosition());
        }
        
    }else{
        if (typeid(*this) != typeid(Hero))
        {
            hitEffect->addHurtNum(hurtVal, getPosition());
        }
    }
    
    hp = blackActor->getHp() - hurtVal;
    hp = MAX(0, hp);
    setHp(hp);
    
    addBuff(false, killSkillTag);
    if(killBullet->getOwner() != nullptr)
    {
        if (!dynamic_cast<FightActor *>(killBullet->getOwner())->getDieLie()) {
            dynamic_cast<FightActor *>(killBullet->getOwner())->addCombo();
        }
    }
    
    if (currSkill != nullptr) {
        if(!currSkill->getCanBreak() && hp > 0)
        {
            return;
        }
    }
    if (isPA && hp > 0) {
        return;
    }
    
    currHitDownVal -= killSkillTag->getHitDownVal();

    int isbound2Air = 0;
    if (killBullet->getHit2Air() || killBullet->getHit2Ground() || killBullet->getHit2Wall()) {
        if (FightFormula::instance()->isHit2Air(blackActor)) {
            isbound2Air = 1;
        }else{
            isbound2Air = 2;
        }
        
    }
    
    if (armature->getPositionY()>0) {
        
        if (killBullet->getHit2Wall() && (isbound2Air == 1)) {
            currHitDownVal = 0;
            bombHitDownVal = killSkillTag->getHitDownVal();
            bombHitVal = hurtVal;
            this->event = stateMachine->findEventVal("EVENT_KW");
        } else {
            this->event = stateMachine->findEventVal("EVENT_AIRHIT");
            if (fallSpeedY != 0) {
                startFallSpeedY = fallSpeedY;
            }
            fallAccX = 2;
            backInAir = false;
        }
    }else if (killBullet->getHit2Air() && (isbound2Air == 1)) {
        currHitDownVal = 0;
        this->event = stateMachine->findEventVal("EVENT_HIT2AIR");
    }else if (killBullet->getHit2Wall() && (isbound2Air == 1)) {
        currHitDownVal = 0;
        bombHitDownVal = killSkillTag->getHitDownVal();
        bombHitVal = hurtVal;
        this->event = stateMachine->findEventVal("EVENT_KW");
    }else if(killBullet->getHit2Ground() && (isbound2Air == 1)) {
        this->event = stateMachine->findEventVal("EVENT_KG");
    } else {
//        log("hit down val :%.2f",currHitDownVal);

        if (isbound2Air == 2) {
            addSingleBUff(true, 34, 100);
        }
        if (killBullet->getAttackHead()) {
            this->event = stateMachine->findEventVal("EVENT_HEADHURT");
        }else if (killBullet->getAttackWaist()){
            this->event = stateMachine->findEventVal("EVENT_WAISTHURT");
            //        }else if (killer->getAttackFoot()){
            //            this->event = stateMachine->findEventVal("EVENT_LEGHURT");
        }


        if(currHitDownVal <= 0){
            if (FightFormula::instance()->isHitDown(this->getBlackActor())) {
                if (killSkillTag->getHitDownVal() >= deHitDownVal ) {
                    this->delayEvent = stateMachine->findEventVal("EVENT_WAISTFELLGROUND");
                }else{
                    this->delayEvent = stateMachine->findEventVal("EVENT_HEADFELLGROUND");
                }
                currHitDownVal = 0;
            }else{
                currHitDownVal = 1;
                addSingleBUff(true, 34, 100);
            }
        }
    }
    if (blackActor->getHp() <= 0 && !hpEmpty) {
        hpEmpty = true;
        this->delayEvent = stateMachine->findEventVal("EVENT_WAISTFELLGROUND");
        currHitDownVal = 0;
        if (typeid(*this) == typeid(Monster)) {
            if(dynamic_cast<ActorLayer *>(getParent())->getHero()->Guard != nullptr)
            {
                dynamic_cast<Monster *>(this)->popItem();
            }
        }
    }
    
    if (killBullet->getFlipX()) {
        setDir(DIRECT::RIGHT);
    } else {
        setDir(DIRECT::LEFT);
    }
    
    float hitSpeed = 0;
    if (killSkill != nullptr) {
        if (armature->getPositionY() > 0) {
            chatterLoop = killSkillTag->getAirChatterLoop();
            chatterOffX[0] = -killSkillTag->getChatterRange();
            chatterOffX[1] = killSkillTag->getChatterRange();
            chatterOffX[2] = -killSkillTag->getChatterRange();
            hitSpeed = killSkillTag->getAirHitBackSpeed();
        }else{
            chatterLoop = killSkillTag->getChatterLoop();
            chatterOffX[0] = -killSkillTag->getChatterRange();
            chatterOffX[1] = killSkillTag->getChatterRange();
            chatterOffX[2] = -killSkillTag->getChatterRange();
            hitSpeed = killSkillTag->getHitBackSpeed();
        }
        
        
        hurtMoveSpeed = hitSpeed * ((killBullet->getFlipX()) ? -1 : 1);
        lieShockSpeed = hurtMoveSpeed/3;
        
        //            SimpleAudioEngine::getInstance()->preloadEffect(killSkill->getHitSoundRes().c_str());
        SimpleAudioEngine::getInstance()->setEffectsVolume(0.8);
        SimpleAudioEngine::getInstance()->playEffect(killSkillTag->getHitSoundRes().c_str(),false,1,0,0.5);
        
    }
    
    armature->getAnimation()->pause();
    
    auto hurtEffect = Effect::create();
    hurtEffect->initWithRes(killSkillTag->getHitEffect(), 1);
    std::string boneName;
    if ((this->event == stateMachine->findEventVal("EVENT_HEADHURT")) || (this->event == stateMachine->findEventVal("EVENT_HEADFELLGROUND"))) {
        boneName = "HeadHurtPoint";
    }else if (this->event == stateMachine->findEventVal("EVENT_WAISTHURT") || (this->event == stateMachine->findEventVal("EVENT_WAISTFELLGROUND")) || (this->event == stateMachine->findEventVal("EVENT_HIT2AIR")) ||
              (this->event == stateMachine->findEventVal("EVENT_AIRHIT")) ||
              (this->event == stateMachine->findEventVal("EVENT_KG")) ||
              (this->event == stateMachine->findEventVal("EVENT_KW"))) {
        boneName = "WaistHurtPoint";
    }
    auto info = armature->getBone(boneName)->getWorldInfo();
    
    hurtEffect->setOriginX((flipX?-1:1) * info->x+rand()%10);
    hurtEffect->setOriginY(info->y+rand()%10);
    
    hurtEffect->setPosition(Vec2(hurtEffect->getOriginX(), hurtEffect->getOriginY()));
    
    auto arm = hurtEffect->getArmature();
    arm->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(FightActor::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    
    hurtEffectLayer->addChild(hurtEffect);
}

void FightActor::hurt()
{
    killSkill = killer->getCurrSkill();
    killSkillTag = killer->getCurrSkillTag();
    float hp;
    auto hitEffect = dynamic_cast<HitEffectLayer *>(hurtEffectLayer->getParent());
    if (killSkill->getSkillType() == TARGET_SKILL_TYPE_LINK || killSkill->getSkillType() == TARGET_SKILL_TYPE_SELECT) {
        if(FightFormula::instance()->isMiss(killer->getBlackActor(), blackActor))
        {
            hitEffect->addMissFlag(getPosition());
            return;
        }
    }
    
    bool crit = false;
    crit = FightFormula::instance()->isCirt(killer->getBlackActor(), blackActor);
    
    float hurtVal = 0;
    hurtVal = FightFormula::instance()->calSkillHurt(killSkillTag, killer->getBlackActor(), blackActor);
    if (crit) {
        hurtVal *= 2;
        if (typeid(*this) != typeid(Hero))
        {
            hitEffect->addCritHurtNum(hurtVal, getPosition());
            hitEffect->addCritFlag(getPosition());
        }
        
    }else{
        if (typeid(*this) != typeid(Hero))
        {
            hitEffect->addHurtNum(hurtVal, getPosition());
        }
    }
    
    if (hp>0 && hurtVal>=blackActor->getHurtAThreshold()) {
        addAv(1);
//        blackActor->addAv();
    }
    if (killer->blackActor->getHp() > 0 && hurtVal >= blackActor->getAtkAThreshold()) {
        killer->addAv(1);
//        killer->blackActor->addAv();
    }
    
    hp = blackActor->getHp() - hurtVal;
    hp = MAX(0, hp);
    setHp(hp);
    killer->addCombo();
//    for (int i = 0; i < killSkillTag->getHitCount(); i++) {
//        
//    }
    
    addBuff(false, killSkillTag);
    if (currSkill != nullptr)
    {
        if (typeid(*this) == typeid(Hero))
        {
            if(!currSkill->getCanBreak() && hp > 0)
            {
                return;
            }
        }
    }

    if (isPA && hp > 0) {
        return;
    }
    
    int isbound2Air = 0;
    if (killer->getHit2Air() || killer->getHit2Ground() || killer->getHit2Wall()) {
        if (FightFormula::instance()->isHit2Air(blackActor)) {
            isbound2Air = 1;
        }else{
            isbound2Air = 2;
        }
        
    }
    
    if (armature->getPositionY()>0) {
        
        if (killer->getHit2Wall() && (isbound2Air == 1)) {
            currHitDownVal = 0;
            bombHitDownVal = killSkillTag->getHitDownVal();
            bombHitVal = hurtVal;
            this->event = stateMachine->findEventVal("EVENT_KW");
        } else {
            this->event = stateMachine->findEventVal("EVENT_AIRHIT");
            if (fallSpeedY != 0) {
                startFallSpeedY = fallSpeedY;
            }
            fallAccX = 2;
            backInAir = false;
        }
    }else if (killer->getHit2Air() && (isbound2Air == 1)) {
        currHitDownVal = 0;
        this->event = stateMachine->findEventVal("EVENT_HIT2AIR");
    }else if (killer->getHit2Wall() && (isbound2Air == 1)) {
        currHitDownVal = 0;
        bombHitDownVal = killSkillTag->getHitDownVal();
        bombHitVal = hurtVal;
        this->event = stateMachine->findEventVal("EVENT_KW");
    }else if(killer->getHit2Ground() && (isbound2Air == 1)) {
        this->event = stateMachine->findEventVal("EVENT_KG");
    } else {
        if (typeid(*this) == typeid(Hero))
        {
            if (currHitDownVal <= 0) {
                return;
            }
        }
        
        if (isbound2Air == 2) {
            addSingleBUff(true, 34, 100);
        }
        
        if (killer->getAttackHead()) {
            this->event = stateMachine->findEventVal("EVENT_HEADHURT");
        }else if (killer->getAttackWaist()){
            this->event = stateMachine->findEventVal("EVENT_WAISTHURT");
            //        }else if (killer->getAttackFoot()){
            //            this->event = stateMachine->findEventVal("EVENT_LEGHURT");
        }
        
        currHitDownVal -= killSkillTag->getHitDownVal();
//        log("hit down val :%.2f",currHitDownVal);
        
        if(currHitDownVal <= 0){
            if (FightFormula::instance()->isHitDown(this->getBlackActor())) {
                if (killSkillTag->getHitDownVal() >= deHitDownVal ) {
                    this->delayEvent = stateMachine->findEventVal("EVENT_WAISTFELLGROUND");
                }else{
                    this->delayEvent = stateMachine->findEventVal("EVENT_HEADFELLGROUND");
                }
                currHitDownVal = 0;
            }else{
                currHitDownVal = 1;
                addSingleBUff(true, 34, 100);
            }
            
        }
    }
    if (blackActor->getHp() <= 0 && !hpEmpty) {
        hpEmpty = true;
        this->delayEvent = stateMachine->findEventVal("EVENT_WAISTFELLGROUND");
        currHitDownVal = 0;
        if (typeid(*this) == typeid(Monster)) {
            if(dynamic_cast<ActorLayer *>(getParent())->getHero()->Guard != nullptr)
            {
                dynamic_cast<Monster *>(this)->popItem();
            }

        }
    }
    
    if(killSkillTag->getFullScreenRange())
    {
        if (killer->getPositionX()<getPositionX()) {
            setDir(DIRECT::LEFT);
        }else{
            setDir(DIRECT::RIGHT);
        }
    }else{
        if (killer->getFlipX()) {
            setDir(DIRECT::RIGHT);
        }else{
            setDir(DIRECT::LEFT);
        }
    }
    
    
    float hitSpeed = 0;
    if (killSkill != nullptr) {
        if (armature->getPositionY() > 0) {
            chatterLoop = killSkillTag->getAirChatterLoop();
            chatterOffX[0] = -killSkillTag->getChatterRange();
            chatterOffX[1] = killSkillTag->getChatterRange();
            chatterOffX[2] = -killSkillTag->getChatterRange();
            hitSpeed = killSkillTag->getAirHitBackSpeed();
        }else{
            chatterLoop = killSkillTag->getChatterLoop();
            chatterOffX[0] = -killSkillTag->getChatterRange();
            chatterOffX[1] = killSkillTag->getChatterRange();
            chatterOffX[2] = -killSkillTag->getChatterRange();
            hitSpeed = killSkillTag->getHitBackSpeed();
        }
        
        
        hurtMoveSpeed = hitSpeed * ((killer->flipX) ? -1 : 1);
        lieShockSpeed = hurtMoveSpeed/3;
        
        //            SimpleAudioEngine::getInstance()->preloadEffect(killSkill->getHitSoundRes().c_str());
        SimpleAudioEngine::getInstance()->setEffectsVolume(0.8);
        SimpleAudioEngine::getInstance()->playEffect(killSkillTag->getHitSoundRes().c_str(),false,1,0,0.5);
        
    }
    
    armature->getAnimation()->pause();
    
    //        DeStiff();
    if (!killer->getAtkStiff()) {
        if (state == ACTORSTATE::INAIR || state == ACTORSTATE::JUMP || state == ACTORSTATE::JUMPATTACK) {
            killer->startAtkStiff(killSkillTag->getAirAtkStiffDur());
        }else{
            killer->startAtkStiff(killSkillTag->getAtkStiffDur());
        }
    }
    

    auto hurtEffect = Effect::create();
    hurtEffect->initWithRes(killSkillTag->getHitEffect(), 1);
    std::string boneName;
    if ((this->event == stateMachine->findEventVal("EVENT_HEADHURT")) || (this->event == stateMachine->findEventVal("EVENT_HEADFELLGROUND"))) {
        boneName = "HeadHurtPoint";
    }else if (this->event == stateMachine->findEventVal("EVENT_WAISTHURT") || (this->event == stateMachine->findEventVal("EVENT_WAISTFELLGROUND")) || (this->event == stateMachine->findEventVal("EVENT_HIT2AIR")) ||
              (this->event == stateMachine->findEventVal("EVENT_AIRHIT")) ||
              (this->event == stateMachine->findEventVal("EVENT_KG")) ||
              (this->event == stateMachine->findEventVal("EVENT_KW"))) {
        boneName = "WaistHurtPoint";
    }
    auto info = armature->getBone(boneName)->getWorldInfo();
    
    hurtEffect->setOriginX((flipX?-1:1) * info->x+rand()%10);
    hurtEffect->setOriginY(info->y+rand()%10);
    
    hurtEffect->setPosition(Vec2(hurtEffect->getOriginX(), hurtEffect->getOriginY()));
    
    auto arm = hurtEffect->getArmature();
    arm->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(FightActor::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    
    hurtEffectLayer->addChild(hurtEffect);
    
}
void FightActor::effAnimEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if (movementType == MovementEventType::COMPLETE)
    {
        auto scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
        scene->getscrFrtLayer()->removeChild(armature->getParent());
    }
}

void FightActor::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if (movementType == MovementEventType::COMPLETE)
    {
        if (armature->getParent() == nullptr) {
            return;
        }
        hurtEffectLayer->removeChild(armature->getParent());
    }
}

void FightActor::onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
    
    //    CCLOG("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), evt.c_str(), currentFrameIndex);
    auto *val = evt.c_str();
    if (strcmp(val, "") == 0) {
        return;
    }
    
    auto result = YNBaseUtil::splitString(evt, ",");
    for (int i = 0; i<result.size(); i++) {
//        if (strcmp(result[i].c_str(), "atk") == 0) {
//            frameCommand |= HEROFRAMECOMMAND::COMMAND_PUNCH;
//        }
//        if (strcmp(result[i].c_str(), "atkend") == 0) {
//            frameCommand &= !HEROFRAMECOMMAND::COMMAND_PUNCH;
//        }
        if (strcmp(result[i].c_str(), "atk2") == 0) {
            frameCommand |= HEROFRAMECOMMAND::COMMAND_PUNCHA2;
        }
        if (strcmp(result[i].c_str(), "atk3") == 0) {
            frameCommand |= HEROFRAMECOMMAND::COMMAND_PUNCHA3;
        }
        
        if (strcmp(result[i].c_str(), "atk4") == 0) {
            frameCommand |= HEROFRAMECOMMAND::COMMAND_PUNCHA4;
        }
        if (strcmp(result[i].c_str(), "atk4end") == 0) {
            frameCommand &= !HEROFRAMECOMMAND::COMMAND_PUNCHA4;
        }
        
        if (strcmp(result[i].c_str(), "slt") == 0) {
            frameCommand |= HEROFRAMECOMMAND::COMMAND_SKL_SLT;
        }
        if (strcmp(result[i].c_str(), "xft") == 0) {
            frameCommand |= HEROFRAMECOMMAND::COMMAND_SKL_XFT;
        }
        
        if (strcmp(result[i].c_str(), "jatk") == 0) {
            frameCommand |= HEROFRAMECOMMAND::COMMAND_JUMP_ATK;
        }
        if (strcmp(result[i].c_str(), "jatkend") == 0) {
            frameCommand &= !HEROFRAMECOMMAND::COMMAND_JUMP_ATK;
        }
        if (strcmp(result[i].c_str(), "startAttack") == 0) {
            //            log("start Attack @ %d", action);
            atking = true;
        }
        if (strcmp(result[i].c_str(), "endAttack") == 0) {
            atking = false;
        }
        if (strcmp(result[i].c_str(), "attackHead") == 0) {
            attackHead = true;
            attackWaist = attackFoot = false;
        }
        if (strcmp(result[i].c_str(), "attackWaist") == 0) {
            attackWaist = true;
            attackHead = attackFoot = false;
        }
        if (strcmp(result[i].c_str(), "attackFoot") == 0) {
            attackFoot = true;
            attackWaist = attackHead = false;
        }
        if (strcmp(result[i].c_str(), "hit2air") == 0) {
            hit2Air = true;
        }
        if (strcmp(result[i].c_str(), "move2Center") == 0) {
            Size winsize = Director::getInstance()->getWinSize();
            
            posX = YNCamera::getInstance()->getPositionX();
            posX = MAX(winsize.width/2, posX);
            posX = MIN(MAP_AREA_WIDTH-winsize.width/2, posX);
        }
        if (strncmp(result[i].c_str(), "frontEffect", strlen("frontEffect")) == 0) {
            size_t tagLen = strlen("frontEffect");
            size_t sLen = result[i].length();
            int effTag = atoi(result[i].substr(tagLen, sLen - tagLen).c_str())-1;
            if (currSkill != nullptr) {
                if((strcmp(currSkill->getFrontEffectStr()[effTag].c_str(), "") != 0 && (strcmp(currSkill->getFrontEffectStr()[effTag].c_str(),"null") != 0))) {
                    //初始化和资源载入
                    std::string resPath = ARM_DIR + currSkill->getFrontEffectStr()[effTag] + ".ExportJson";
                    ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);
                    
                    auto eff1 = Effect::create();
                    eff1->initWithArmature(currSkill->getFrontEffectStr()[effTag], currSkill->getFrontScale()[effTag]);
                    eff1->setFollowY(currSkill->getEffectFollowY());
                    eff1->setTag(ATTACK_EFFECT_TAG);
                    frontEffectLayer->addChild(eff1);
                }
            }
        }
        if (strncmp(result[i].c_str(), "screenFrontEffect", strlen("screenFrontEffect")) == 0) {
            size_t tagLen = strlen("screenFrontEffect");
            size_t sLen = result[i].length();
            int effTag = atoi(result[i].substr(tagLen, sLen - tagLen).c_str())-1;
            if (currSkill != nullptr) {
                if((strcmp(currSkill->getFrontEffectStr()[effTag].c_str(), "") != 0 && (strcmp(currSkill->getFrontEffectStr()[effTag].c_str(),"null") != 0))) {
                    //初始化和资源载入
                    auto hurtEffect = Effect::create();
                    hurtEffect->initWithRes(currSkill->getFrontEffectStr()[effTag], currSkill->getFrontScale()[effTag]);
                    
                    auto arm = hurtEffect->getArmature();
                    arm->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(FightActor::effAnimEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                    
                    auto scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
                    scene->getscrFrtLayer()->addChild(hurtEffect);
                }
            }
        }
        if (strncmp(result[i].c_str(), "backEffect", strlen("backEffect")) == 0) {
            size_t tagLen = strlen("backEffect");
            size_t sLen = result[i].length();
            int effTag = atoi(result[i].substr(tagLen, sLen - tagLen).c_str())-1;
            if (currSkill != nullptr) {
                if((strcmp(currSkill->getBackEffectStr()[effTag].c_str(), "") != 0 && (strcmp(currSkill->getBackEffectStr()[effTag].c_str(),"null") != 0))) {
                    //初始化和资源载入
                    std::string resPath = ARM_DIR + currSkill->getBackEffectStr()[effTag] + ".ExportJson";
                    ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);
                    
                    auto eff1 = Effect::create();
                    eff1->initWithArmature(currSkill->getBackEffectStr()[effTag], currSkill->getBackScale()[effTag]);
                    eff1->setFollowY(currSkill->getEffectFollowY());
                    backEffectLayer->addChild(eff1);
                    
                }
            }
        }
        if (strcmp(result[i].c_str(), "bullet") == 0) {
            if (currSkillTag->getBulletID() != 0) {
                auto originInfo = armature->getBone("OriginPoint")->getWorldInfo();
                auto boneInfo = armature->getBone("bullet")->getWorldInfo();
                
                auto boneVec2 = Point(boneInfo->x, boneInfo->y)-Point(originInfo->x, originInfo->y);
                dynamic_cast<ActorLayer *>(getParent())->addBullet(currSkillTag->getBulletID(), this, boneInfo->y, boneInfo->x, currSkillTag);
            }
        }
        
        if (strncmp(result[i].c_str(), "attackTag", strlen("attackTag")) == 0) {
            size_t tagLen = strlen("attackTag");
            size_t sLen = result[i].length();
            attackTag = atoi(result[i].substr(tagLen, sLen - tagLen).c_str());
            attackTag += currSkill->getSkillID()*100;
            currSkillTag = blackActor->selSkillTags[attackTag];
            addBuff(true, currSkillTag);
            if (!currSkillTag->coloSkill.empty()) {
                if (colossus != nullptr) {
                    dynamic_cast<Colossus *>(colossus)->selColSkills(currSkillTag);
                }
            }
        }
        
        if (strncmp(result[i].c_str(), "shake",strlen("shake")) == 0) {
            size_t tagLen = strlen("shake");
            size_t sLen = result[i].length();
            YNCamera::shakeRange = atoi(result[i].substr(tagLen, sLen - tagLen).c_str());
            YNCamera::bShake = true;
        }
        if (strcmp(result[i].c_str(), "dust") == 0)
        {
            //初始化和资源载入
            std::string resPath = "armature/effect_dust.ExportJson";
            ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);
            
            auto eff1 = Effect::create();
            eff1->initWithArmature("effect_dust", 1);
            eff1->setFollowY(false);
            backEffectLayer->addChild(eff1);
        }
        
        if (strncmp(result[i].c_str(), "flash",strlen("flash")) == 0)
        {
            size_t tagLen = strlen("flash");
            size_t sLen = result[i].length();
            YNCamera::flashCount = atoi(result[i].substr(tagLen, sLen - tagLen).c_str())*2;
        }
        
        if (strcmp(result[i].c_str(), "bound2Air") == 0)
        {
            hit2Ground = true;
        }
        
        if (strcmp(result[i].c_str(), "bound2Wall") == 0) {
            hit2Wall = true;
        }
        
        if (strcmp(result[i].c_str(), "wallEffect") == 0) {
            auto info = armature->getBone("WaistHurtPoint")->getWorldInfo();
            
            auto hitEffect = dynamic_cast<HitEffectLayer *>(hurtEffectLayer->getParent());
            hitEffect->addArmatureEff("effect_hit4", getPosition()+Vec2(info->x, info->y + rand()%10));
        }
    }
    
}


int FightActor::getSkillAction(int event)
{
    changeSkill(event);
    
    if (currSkill == nullptr) {
        return event;
    }
    auto actionString = currSkill->getAction();
    int temp = stateMachine->findEventVal(actionString);
    return temp;
}

void FightActor::adjustHurtEffectPos()
{
    auto hitEffLayer = hurtEffectLayer->getChildren();
    
    for(int i = 0; i<hitEffLayer.size(); i++)
    {
        auto eff = (Effect *)hitEffLayer.at(i);
        eff->getArmature()->setScaleX((flipX) ? -1 : 1);
        eff->getArmature()->setPositionY(armature->getPositionY());
    }
    
    hurtEffectLayer->setPosition(getPosition());
}

void FightActor::updateFrontEffect()
{
    auto frontEffectVec = frontEffectLayer->getChildren();
    
    for (long i = frontEffectVec.size()-1; i >= 0; i--) {
        Effect *eff = (Effect *)(frontEffectVec.at(i));
        if(eff->getArmature()->getAnimation()->isComplete())
        {
            frontEffectLayer->removeChild(frontEffectVec.at(i));
        }
    }
    
    for(int i = 0; i<frontEffectVec.size(); i++)
    {
        Effect *eff = (Effect *)(frontEffectVec.at(i));
        if (eff->getFollowY()) {
            eff->setPositionY(armature->getPositionY());
        }
//        if (flipX) {
//            eff->setScaleX(-eff->getScaleRate());
//        }
        
//        float sx = eff->getScaleRate();
        eff->setScaleX((flipX) ? -1 : 1);
    }
    
}

void FightActor::updateBackEffect()
{
    auto backEffectVec = backEffectLayer->getChildren();
    
    for (long i = backEffectVec.size()-1; i >= 0; i--) {
        Effect *eff = (Effect *)(backEffectVec.at(i));
        if(eff->getArmature()->getAnimation()->isComplete())
        {
            backEffectLayer->removeChild(backEffectVec.at(i));
        }
    }
    
    for(int i = 0; i<backEffectVec.size(); i++)
    {
        Effect *eff = (Effect *)(backEffectVec.at(i));
        if (eff->getFollowY()) {
            eff->setPositionY(armature->getPositionY());
        }
//        float sx = eff->getScaleRate();
        eff->setScaleX((flipX) ? -1 : 1);
    }
    
}

void FightActor::initViewRes()
{
    backEffectLayer = Layer::create();
    addChild(backEffectLayer);
    
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
    
    armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(FightActor::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    
    addChild(armature);
    
    frontEffectLayer = Layer::create();
    addChild(frontEffectLayer);

}

void FightActor::preloadSkillRes()
{
    std::string resDir(ARM_DIR);
    for (auto skillIte : blackActor->selSkills) {
        auto skill = skillIte.second;
        for (auto frontEffStr : skill->getFrontEffectStr())
        {
            if (frontEffStr == "" || frontEffStr == "null") {
                continue;
            }
            std::string resPath = ARM_DIR + frontEffStr + ".ExportJson";
            ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);
        }
        
        for (auto backEffStr : skill->getBackEffectStr())
        {
            if (backEffStr == "" || backEffStr == "null") {
                continue;
            }
            std::string resPath = ARM_DIR + backEffStr + ".ExportJson";
            ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);
        }
    }
}
void FightActor::initFightState()
{
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
}

void FightActor::DealAttackRectByFlip(const bool flip , Rect * pRect)
{
    /************************************************************************/
    // 通过是否翻转处理攻击范围
    // 1. 获取x,y，宽度和高度
    int nPointX = pRect->origin.x;
    int nPointY = pRect->origin.y;
    int nWidth	= pRect->size.width;
    int nHeight = pRect->size.height;
    
    // 2. 根据Flip的值设置Rect
    if (flip)
    {
        pRect->setRect(nPointX , nPointY, nWidth, nHeight);
    }
    else
    {
        pRect->setRect(nPointX + nWidth - nHeight, nPointY, nWidth, nHeight);
    }
    
}


void FightActor::buffChangeHp(Buff *buff)
{
    log("buffChangeHp!");
    auto hitEffect = dynamic_cast<HitEffectLayer *>(hurtEffectLayer->getParent());
    
    float hurtVal = 0;
    if (buff->getValueType() == BUFF_EFFECT_ATTRIBUTE_VALUE_TYPE_INTEGER) {
        hurtVal = buff->getValue();
    }else if (buff->getValueType() == BUFF_EFFECT_ATTRIBUTE_VALUE_TYPE_PERCENT) {
        hurtVal = -1 * buff->getValue() * blackActor->getMaxHp() / 100;
    }
    hitEffect->addHurtNum(hurtVal, getPosition());
    
    
    float hp = blackActor->getHp() - hurtVal;
    hp = MAX(0, hp);
    setHp(hp);
}

void FightActor::buffChangeMaxHp(Buff *buff)
{
    log("buffChangeMaxHp!");
    
}
void FightActor::buffChangeHpRecover(Buff *buff)
{
    log("buffChangeHpRecover!");
}
void FightActor::buffChangeMp(Buff *buff)
{
    log("buffChangeMp!");
    float mp = blackActor->getMp();
    if (buff->getValueType() == BUFF_EFFECT_ATTRIBUTE_VALUE_TYPE_INTEGER) {
        mp += buff->getValue();
    } else if(buff->getValueType() == BUFF_EFFECT_ATTRIBUTE_VALUE_TYPE_PERCENT) {
        mp += buff->getValue() * blackActor->getMaxMp() / 100;
    }
    
    setMp(mp);
}
void FightActor::buffChangeMaxMp(Buff *buff)
{
    log("buffChangeMaxMp!");
}
void FightActor::buffChangeMpRecover(Buff *buff)
{
    log("buffChangeMpRecover!");
}
void FightActor::buffChangeAp(Buff *buff)
{
    log("buffChangeAp!");
}
void FightActor::buffChangeMaxAp(Buff *buff)
{
    log("buffChangeMaxAp!");
}
void FightActor::buffChangeApRecover(Buff *buff)
{
    log("buffChangeApRecover!");
}
void FightActor::buffChangeAttack(Buff *buff)
{
    log("buffChangeAttack!");
}
void FightActor::buffChangeDefence(Buff *buff)
{
    log("buffChangeDefence!");
}
void FightActor::buffChangeHitRatio(Buff *buff)
{
    log("Here!");
}
void FightActor::buffChangeDodgeRatio(Buff *buff)
{
    log("buffChangeDodgeRatio!");
}
void FightActor::buffChangeCritRatio(Buff *buff)
{
    log("buffChangeCritRatio!");
}
void FightActor::buffChangeTenacity(Buff *buff)
{
    log("buffChangeTenacity!");
}
void FightActor::buffChangeIceResist(Buff *buff)
{
    log("buffChangeIceResist!");
}
void FightActor::buffChangeFireResist(Buff *buff)
{
    log("buffChangeFireResist!");
}
void FightActor::buffChangeThunderResist(Buff *buff)
{
    log("buffChangeThunderResist!");
}
void FightActor::buffChangeWindResist(Buff *buff)
{
    log("buffChangeWindResist!");
}
void FightActor::buffChangeLightResist(Buff *buff)
{
    log("buffChangeLightResist!");
}
void FightActor::buffChangeDarkResist(Buff *buff)
{
    log("buffChangeDarkResist!");
}
void FightActor::buffChangeMoveSpeed(Buff *buff)
{
    log("buffChangeMoveSpeed!");
}
void FightActor::buffChangeDeHitDown(Buff *buff)
{
    log("buffChangeDeHitDown!");
}
void FightActor::buffChangeDeFloat(Buff *buff)
{
    log("buffChangeDeFloat!");
}
void FightActor::buffFaintState(Buff *buff)
{
    log("buffFaintState!");
    isFaint = true;
//    event = stateMachine->findEventVal("EVENT_FAINT");
}
void FightActor::buffImmuFaint(Buff *buff)
{
    log("buffImmuFaint!");
    isFaint = false;
//    event = stateMachine->findEventVal("EVENT_DEFAINT");
}
void FightActor::buffFixState(Buff *buff)
{
    log("buffFixState!");
    event = stateMachine->findEventVal("EVENT_FIX");
}
void FightActor::buffImmuFix(Buff *buff)
{
    log("buffImmuFix!");
    event = stateMachine->findEventVal("EVENT_DEFIX");
}
void FightActor::buffFrozenState(Buff *buff)
{
    log("buffFrozenState!");
    event = stateMachine->findEventVal("EVENT_FROZEN");
}
void FightActor::buffImmuFrozen(Buff *buff)
{
    log("buffImmuFrozen!");
}
void FightActor::buffImmuAll(Buff *buff)
{
    log("buffImmuAll!");
    isFaint = false;
    event = stateMachine->findEventVal("EVENT_DESTATE");
}
void FightActor::buffInvincible(Buff *buff)
{
    isInvincible = true;
}
void FightActor::buffPA(Buff *buff)
{
    isPA = true;
}
void FightActor::addSingleBUff(bool toMyself, int buffId, float rate)
{
    int target = BuffManager::targetTable[buffId];
    if (target == (toMyself?BUFF_AT_ENIMY:BUFF_AT_ME)) {
        return;
    }
    
    if (abs(rand()%100) > rate) {
        return;
    }
    
    if (BuffManager::deBuffTable[buffId]) {
        if (FightFormula::instance()->isImmuBuff(blackActor)) {
            return;
        }
    }
    
    int type = BuffManager::typeTable[buffId];
    if(buffManager->addBuff(buffId, buffFuncs[type], removeFuncs[type]))
    {
        auto result = static_cast<Buff *>(buffManager->getChildByTag(buffId));
        
        if (result->getEffectStr() != "null") {
            auto eff1 = Effect::create();
            eff1->initWithArmature(result->getEffectStr(), 1);
            eff1->setFollowY(true);
            eff1->setTag(result->getBuffId());
            frontEffectLayer->addChild(eff1);
        }
    }
    
}

void FightActor::addBuff(bool toMyself, SkillTag *skillTag)
{
    if (skillTag == nullptr) {
        return;
    }
    
    for(auto buff : skillTag->buffId)
    {
        addSingleBUff(toMyself, buff.first, buff.second);
//        int target = BuffManager::targetTable[buff.first];
//        if (target == (toMyself?BUFF_AT_ENIMY:BUFF_AT_ME)) {
//            continue;
//        }
//        
//        if (abs(rand()%100) > buff.second) {
//            continue;
//        }
//        
//        int type = BuffManager::typeTable[buff.first];
//        if(buffManager->addBuff(buff.first, buffFuncs[type], removeFuncs[type]))
//        {
//            auto result = static_cast<Buff *>(buffManager->getChildByTag(buff.first));
//            
//            if (result->getEffectStr() != "null") {
//                auto eff1 = Effect::create();
//                eff1->initWithArmature(result->getEffectStr(), 1);
//                eff1->setFollowY(true);
//                eff1->setTag(result->getBuffId());
//                frontEffectLayer->addChild(eff1);
//            }
//        }
        
    }
}

void FightActor::removeCurrHpBuff(Buff *buff)
{
    log("removeCurrHpBuff!");
}
void FightActor::removeMaxHpBuff(Buff *buff)
{
    log("removeMaxHpBuff!");
}
void FightActor::removeHpRecoverBuff(Buff *buff)
{
    log("removeHpRecoverBuff!");
}
void FightActor::removeCurrMpBuff(Buff *buff)
{
    log("removeCurrMpBuff!");
}
void FightActor::removeMaxMpBuff(Buff *buff)
{
    log("removeMaxMpBuff!");
}
void FightActor::removeMpRecoverBuff(Buff *buff)
{
    log("removeMpRecoverBuff!");
}
void FightActor::removeCurrApBuff(Buff *buff)
{
    log("removeCurrApBuff!");
}
void FightActor::removeMaxApBuff(Buff *buff)
{
    log("removeMaxApBuff!");
}
void FightActor::removeApRecoverBuff(Buff *buff)
{
    log("removeApRecoverBuff!");
}
void FightActor::removeAttackBuff(Buff *buff)
{
    log("removeAttackBuff!");
}
void FightActor::removeDefenceBuff(Buff *buff)
{
    log("removeDefenceBuff!");
}
void FightActor::removeHitRatioBuff(Buff *buff)
{
    log("removeHitRatioBuff!");
}
void FightActor::removeDodgeRatioBuff(Buff *buff)
{
    log("removeDodgeRatioBuff!");
}
void FightActor::removeCritRatioBuff(Buff *buff)
{
    log("removeCritRatioBuff!");
}
void FightActor::removeTenacityBuff(Buff *buff)
{
    log("removeTenacityBuff!");
}
void FightActor::removeIceResistBuff(Buff *buff)
{
    log("removeIceResistBuff!");
}
void FightActor::removeFireResistBuff(Buff *buff)
{
    log("removeFireResistBuff!");
}
void FightActor::removeThunderResistBuff(Buff *buff)
{
    log("removeThunderResistBuff!");
}
void FightActor::removeWindResistBuff(Buff *buff)
{
    log("removeWindResistBuff!");
}
void FightActor::removeLightResistBuff(Buff *buff)
{
    log("removeLightResistBuff!");
}
void FightActor::removeDarkResistBuff(Buff *buff)
{
    log("removeDarkResistBuff!");
}
void FightActor::removeMoveSpeedBuff(Buff *buff)
{
    log("removeMoveSpeedBuff!");
}
void FightActor::removeDehitDownBuff(Buff *buff)
{
    log("removeDehitDownBuff!");
}
void FightActor::removeDefloatBuff(Buff *buff)
{
    log("removeDefloatBuff!");
}
void FightActor::removeFaintBuff(Buff *buff)
{
    log("removeFaintBuff!");
    isFaint = false;
    frontEffectLayer->removeChildByTag(buff->getBuffId());
}
void FightActor::removeFixBuff(Buff *buff)
{
    log("removeFixBuff!");
}
void FightActor::removeFrozenBuff(Buff *buff)
{
    log("removeFrozenBuff!");
}
void FightActor::removeImmuFaintBuff(Buff *buff)
{
    log("removeImmuFaintBuff!");
    buffManager->removeImmu(buff->getBuffId());

}
void FightActor::removeImmuFixBuff(Buff *buff)
{
    log("removeImmuFixBuff!");
}
void FightActor::removeImmuFrozenBuff(Buff *buff)
{
    log("removeImmuFrozenBuff!");
}
void FightActor::removeImmuAllDeBuff(Buff *buff)
{
    log("removeImmuAllDeBuff!");
    buffManager->removeImmu(buff->getBuffId());
}
void FightActor::removeInvincible(Buff *buff)
{
    isInvincible = false;
    armature->setVisible(true);
}
void FightActor::removePA(Buff *buff)
{
    isPA = false;
}

FightActor* FightActor::selectOpponent(std::vector<FightActor *> enemies)
{
    FightActor *result = nullptr;
    auto size = enemies.size();
    Size winsize = Director::getInstance()->getWinSize();
    int minDis = winsize.width;
    for (size_t i=0; i<size; i++) {
        FightActor *actor = enemies.at(i);
        if (actor->getDying() || actor->getDieLie()) {
            continue;
        }
        if (abs(actor->getPosition().getDistance(getPosition())) < minDis) {
            minDis = abs(actor->getPosition().getDistance(getPosition()));
            result = actor;
        }
    }
    
    return result;
}

bool FightActor::canFindOpponent()
{
    if (GameScene::gameMode != Game_Scene_State_Normal) {
        return false;
    }
    
    auto enemiesInView = dynamic_cast<ActorLayer *>(getParent())->findEnemies(this);
    if (enemiesInView.empty()) {
        targetActor = nullptr;
        return false;
    }
    
    auto opponent = selectOpponent(enemiesInView);
    if (opponent == nullptr) {
        targetActor = nullptr;
        return false;
    }
    
    targetActor = opponent;
    return true;
}

bool FightActor::lostTarget()
{
    if (GameScene::gameMode != Game_Scene_State_Normal) {
        return false;
    }

    if (targetActor == nullptr) {
        return true;
    }
    if(targetActor->getDying() || targetActor->getDieLie())
    {
        targetActor = nullptr;
        return true;
    }
    auto viewRect = Rect(getPositionX()-YNBaseUtil::WinSize.width/2, MAP_AREA_BOTTOM, YNBaseUtil::WinSize.width, YNBaseUtil::WinSize.height);
    if (!viewRect.containsPoint(targetActor->getPosition())) {
        targetActor = nullptr;
        return true;
    }
    return false;
}

bool FightActor::canAttackTarget()
{
    if (GameScene::gameMode != Game_Scene_State_Normal) {
        return false;
    }
    
    if (targetActor == nullptr) {
        return false;
    }

    if (targetActor->getDying() || targetActor->getDieLie()) {
        targetActor = nullptr;
        return false;
    }
    Rect atkRect;
    if (targetActor->getPositionX() >= getPositionX()) {
        atkRect = getAtkRect(false);
    }else{
        atkRect = getAtkRect(true);
    }
    
    atkRect.origin += getPosition();
    atkRect.origin.y -= atkRect.size.height/2;
    if (atkRect.containsPoint(targetActor->getPosition())) {
        return true;
    }
    return false;
}

bool FightActor::canChase(){
    if (GameScene::gameMode != Game_Scene_State_Normal) {
        return false;
    }

    if (targetActor == nullptr) {
        return false;
    }
    if (targetActor->getDying() || targetActor->getDieLie()) {
        targetActor = nullptr;
        return false;
    }
    auto viewRect = Rect(getPositionX()-YNBaseUtil::WinSize.width, MAP_AREA_BOTTOM, YNBaseUtil::WinSize.width*2, YNBaseUtil::WinSize.height);
    return viewRect.containsPoint(targetActor->getPosition());
}

bool FightActor::needSneak()
{
    if (GameScene::gameMode != Game_Scene_State_Normal) {
        return false;
    }

    if (targetActor == nullptr) {
        return false;
    }
    
    if(targetActor->getAtking())
    {
        if (targetActor->getAtkRect(targetActor->getFlipX()).size.width > targetActor->getPosition().getDistance(getPosition())) {
            return true;
        }
    }
    return false;
}

void FightActor::setTargetToActor(Actor *actor)
{
    auto originPos = actor->getPosition();
    
    
    float maxAtkDis = 0;
    float minAtkDis = 0;
    if (actor->getPositionX() >= getPositionX()) {
        auto atkRect = getAtkRect(false);
        maxAtkDis = atkRect.getMaxX();
        minAtkDis = MAX(0, atkRect.getMinX());
    }else{
        auto atkRect = getAtkRect(true);
        maxAtkDis = atkRect.getMinX();
        minAtkDis = MIN(0,atkRect.getMaxX());
    }
    float tx = originPos.x + rand() % abs((int)(maxAtkDis - minAtkDis)) + minAtkDis;
    float ty = originPos.y + rand() % 20;
    
    if (actor->getPositionX() >= getPositionX()) {
        tx = MAX(actor->getPositionX()+50, tx);
    }else{
        tx = MIN(actor->getPositionX()-50, tx);
    }
    tx = MIN(MAP_AREA_RIGHT, tx);
    tx = MAX(MAP_AREA_LEFT, tx);
    ty = MIN(ty, MAP_AREA_TOP);
    ty = MAX(ty, MAP_AREA_BOTTOM);
    targetMovePos = Point(tx, ty);
}

void FightActor::waitTimeEnough()
{
    waitTimeOut = true;
    event = stateMachine->findEventVal("EVENT_WAITTIMEOUT");
}

int FightActor::canUseSomeSkill()
{
//    fd
    std::vector<int> validSkillIds;
    for (int i = SKILLA_KEY; i<SKEY_MAX; i++) {
        auto skill = blackActor->selSkills[blackActor->equipSkills[i]];
        if (skill==nullptr) {
            continue;
        }
        if (skill->getConsumeHP() >= blackActor->getHp() || skill->getConsumeMP() > blackActor->getMp() || skill->getConsumeAP() > blackActor->getAp()) {
            continue;
        }
        
    }
}


int FightActor::canUseSkill(int skillId)
{
    auto scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
    
    if(blackActor->selSkills.find(skillId) == blackActor->selSkills.end())
    {
        scene->popTip("技能异常！");
        return SKILL_OTHER_ERROR;
    }
    auto skill = blackActor->selSkills[skillId];
    if (skill->getConsumeHP() > 0 && skill->getConsumeHP() >= blackActor->getHp())
    {
        scene->popTip("耗血不足！");
        return SKILL_HP_ERROR;
    }
    if (skill->getConsumeMP() > 0 && skill->getConsumeMP() > blackActor->getMp())
    {
        scene->popTip("耗蓝不足！");
        return SKILL_MP_ERROR;
    }
    if (skill->getConsumeGhost() > 0 && skill->getConsumeGhost() > blackActor->getGhost())
    {
        scene->popTip("耗魂不足！");
        return SKILL_GHOST_ERROR;
    }
    if (skill->getConsumeAP() > 0 && skill->getConsumeAP() > blackActor->getAp())
    {
        scene->popTip("怒气点不足！");
        return SKILL_AP_ERROR;
    }

    
    return SKILL_NONE_ERROR;
}

void FightActor::useSkill(int skillId)
{
    auto skill = blackActor->selSkills[skillId];
//    blackActor->setHp(blackActor->getHp()-skill->getConsumeHP());
    setMp(blackActor->getMp()-skill->getConsumeMP());
//    blackActor->setMp(blackActor->getMp()-skill->getConsumeMP());
    useAp(skill->getConsumeAP());
    

    setGhost(blackActor->getGhost()-skill->getConsumeGhost());
    currSkill = skill;
    currSkillTag = blackActor->selSkillTags[skillId*100 + 1];
    
}

void FightActor::changeSkill(int event)
{
    currSkill = nullptr;
    currSkillTag = nullptr;
    if(stateMachine->eventName.find(event) == stateMachine->eventName.end())
    {
        return;
    }
    
    auto name = stateMachine->eventName[event];
    
    if (name.find("EVENT_SKILL") != std::string::npos) {
        int currIdx = -1;
        int tagIdx = -1;
        int currSkillId = -1;
        if (name.find("EVENT_SKILLA") != std::string::npos) {
            currIdx = SKILLA_KEY;
            tagIdx = SKILLA_LINK_TIMEOUT_TAG;
        }else if (name.find("EVENT_SKILLB") != std::string::npos) {
            currIdx = SKILLB_KEY;
            tagIdx = SKILLB_LINK_TIMEOUT_TAG;
        }else if (name.find("EVENT_SKILLC") != std::string::npos) {
            currIdx = SKILLC_KEY;
            tagIdx = SKILLC_LINK_TIMEOUT_TAG;
        }else if (name.find("EVENT_SKILLD") != std::string::npos) {
            currIdx = SKILLD_KEY;
            tagIdx = SKILLD_LINK_TIMEOUT_TAG;
        }
        if (currIdx == -1) {
            return;
        }
        
        currSkillId = blackActor->equipSkills[currIdx];
        if (name.find("_E") != std::string::npos) {
            currSkillId = blackActor->selSkills[currSkillId]->getXuliId();
        }
        if (canUseSkill(currSkillId) != SKILL_NONE_ERROR) {
            return;
        }
        
        useSkill(currSkillId);
        
        if (currSkill->getLinkID() != -1) {
            blackActor->equipSkills[currIdx] = currSkill->getLinkID();
            auto func = CallFunc::create(CC_CALLBACK_0(Hero::backSkill2Base, this, blackActor->equipSkills[currIdx], currIdx));
            
            stopActionByTag(tagIdx);
            auto s = Sequence::create(DelayTime::create(currSkill->getLinkDur()),func, NULL);
            s->setTag(tagIdx);
            runAction(s);
            dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene())->showLinkBar(SKILLA_BTN + (currIdx - SKILLA_KEY), blackActor->selSkills[currSkill->getLinkID()]->geticonStr(),currSkill->getLinkDur());
        } else {
            backSkill2Base(blackActor->equipSkills[currIdx], currIdx);
        }
    } else if (name.find("ATTACKPART") != std::string::npos) {
        size_t idx = name.find_first_not_of("ATTACKPART");
        size_t len = name.length()-idx;
        auto num = name.substr(idx, len);
        int index = atoi(num.c_str());
        switch (index) {
            case 1:
                blackActor->equipSkills[ATK_KEY] = blackActor->getAtk1SkillID();
                break;
            case 2:
                blackActor->equipSkills[ATK_KEY] = blackActor->getAtk2SkillID();
                break;
            case 3:
                blackActor->equipSkills[ATK_KEY] = blackActor->getAtk3SkillID();
                break;
            case 4:
                blackActor->equipSkills[ATK_KEY] = blackActor->getAtk4SkillID();
                break;
                
            default:
                return;
        }
        
        useSkill(blackActor->equipSkills[ATK_KEY]);
//        currSkill = blackActor->selSkills[blackActor->equipSkills[ATK_KEY]];
//        currSkillTag = blackActor->selSkillTags[currSkill->getSkillID()*100 + 1];
        
    } else if (name.find("EVENT_RUNATTACK") != std::string::npos) {
        size_t idx = name.find_first_not_of("EVENT_RUNATTACK");
        if (idx != std::string::npos) {
            size_t len = name.length()-idx;
            auto num = name.substr(idx, len);
            int index = atoi(num.c_str());
            switch (index) {
                case 1:
                {
                    blackActor->setRunAttackID(blackActor->getRunAttack1ID());
                }
                    
                    break;
                case 2:
                {
                    blackActor->setRunAttackID(blackActor->getRunAttack2ID());
                }
                    break;
                default:
                    return;
            }
        }
        
        if (canUseSkill(blackActor->getRunAttackID()) != SKILL_NONE_ERROR) {
            return;
        }
        
        blackActor->equipSkills[RUN_ATK_KEY] = blackActor->getRunAttackID();
        useSkill(blackActor->equipSkills[RUN_ATK_KEY]);
//        currSkill = blackActor->selSkills[blackActor->equipSkills[RUN_ATK_KEY]];
//        currSkillTag = blackActor->selSkillTags[currSkill->getSkillID()*100+1];
        if (currSkill->getLinkID() != -1) {
            blackActor->setRunAttackID(currSkill->getLinkID());
        }else if(blackActor->getSkillCID() != currSkill->getBaseSkillID()) {
            blackActor->setRunAttackID(currSkill->getBaseSkillID());
        }
        
    } else if(event == stateMachine->findEventVal("SKILLATK4")) {
        if (canUseSkill(blackActor->getSkillSPID()) != SKILL_NONE_ERROR) {
            return;
        }
        
        blackActor->equipSkills[SKILLS_KEY] = blackActor->getSkillSPID();

        useSkill(blackActor->equipSkills[SKILLS_KEY]);
//        currSkill = blackActor->selSkills[blackActor->equipSkills[SKILLS_KEY] ];
//        currSkillTag = blackActor->selSkillTags[currSkill->getSkillID()*100+1];
    }
    
    if (currSkill != nullptr) {
        SimpleAudioEngine::getInstance()->setEffectsVolume(0.8);
        SimpleAudioEngine::getInstance()->playEffect(currSkillTag->getSkillSoundRes().c_str(),false,1,0,0.5);
        if (currSkillTag->getHumanSoundRes() != "null") {
            SimpleAudioEngine::getInstance()->playEffect(currSkillTag->getHumanSoundRes().c_str(),false,1,0,0.5);
        }
        if (!currSkillTag->coloSkill.empty()) {
            if (colossus != nullptr) {
                dynamic_cast<Colossus *>(colossus)->selColSkills(currSkillTag);
            }
        }
    }
}

void FightActor::backSkill2Base(int skillId, int key)
{
    auto skl = blackActor->selSkills[skillId];
    blackActor->equipSkills[key] = skl->getBaseSkillID();
    skl = blackActor->selSkills[skl->getBaseSkillID()];
    skl->startCool();
    if (typeid(*this) != typeid(Hero)) {
        return;
    }
    
    dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene())->hideLinkBar(SKILLA_BTN + (key - SKILLA_KEY),skl->geticonStr(), skl->getCoolDownDur());
}
