#include "Hero.h"
#include "../Utils/BaseUtils.h"
#include "YNCamera.h"
#include "Effect.h"
#include "ClientLogic/GameScene/GameScene.h"
#include "ClientLogic/Actor/Guardian.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player.h"

USING_NS_CC;
using namespace cocostudio;
using namespace CocosDenshion;

bool Hero::init()
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    
    initFightData(player->get_job());
    
    initViewRes();
    initFightState();
    
    buffManager = BuffManager::create();
    addChild(buffManager);
    
    setDir(DIRECT::NONE);
    return true;
}

void Hero::initFightData(int idx)
{
    blackActor = new BlackActor();
    blackActor->readFile(idx, ACTOR_FILE);
    currSkill = nullptr;
    currSkillTag = nullptr;
    killSkill = nullptr;
    killSkillTag = nullptr;
    
    flipX = false;
    currKey = frameCommand = 0;
    isValidAtk = true;
    rush = false;
    rushReady = false;
    rushAtkReady = false;
    
    deHitDownVal = currHitDownVal = blackActor->getDeHitDownVal();
    
    walkSpeedX = blackActor->getMoveSpeed();
    rushSpeedX = blackActor->getRushSpeed();
    
    atkStiff = hurtStiff = false;
    
    localBonePoint = Point::ZERO;
    hurtMoveSpeed = 0;
    backInAir = false;
    comboNum = maxCombo = 0;
    showCombo = false;
    killer = nullptr;
    killers.clear();
    bHero = true;
    dying = false;
    dieLie = false;
    
    keyCommand = -1;
}

void Hero::addHurtListener()
{
//    hurtListener = EventListenerCustom::create(HERO_HURT_TAG, CC_CALLBACK_1(FightActor::parseHurtEvent, this));
//    punchListener = EventListenerCustom::create(MONSTER_RESET_PUNCH, CC_CALLBACK_1(FightActor::resetPunchTag, this));
//    
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(hurtListener, -1);
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(punchListener, -1);
    
    hurtListener = getEventDispatcher()->addCustomEventListener(HERO_HURT_TAG, CC_CALLBACK_1(FightActor::parseHurtEvent, this));
    punchListener = getEventDispatcher()->addCustomEventListener(MONSTER_RESET_PUNCH, CC_CALLBACK_1(FightActor::resetPunchTag, this));

}
void Hero::removeHurtListener()
{
    getEventDispatcher()->removeEventListener(hurtListener);
    getEventDispatcher()->removeEventListener(punchListener);
    buffManager->removeAllBuff();
//	getEventDispatcher()->removeCustomEventListeners(HERO_HURT_TAG);
//	getEventDispatcher()->removeCustomEventListeners(MONSTER_RESET_PUNCH);

}
Hero::~Hero()
{
	removeHurtListener();
}
void Hero::exitState(int currState)
{
    switch (currState) {
//        case ACTORSTATE::IDLE:
//            
//            break;
        
        case ACTORSTATE::FELLDOWN:
            currHitDownVal = deHitDownVal;
            break;
        case ACTORSTATE::ANY:
            frontEffectLayer->removeChildByTag(ATTACK_EFFECT_TAG);
        case ACTORSTATE::XULI:
            frontEffectLayer->removeChildByTag(XULI_EFFECT_TAG);
            break;
        default:
            break;
    }
}

void Hero::enterState(int nextState)
{
    switch (nextState) {
        case ACTORSTATE::IDLE:
            rush = false;
            stopMove();
            break;
        case ACTORSTATE::ATTACK:
            stopMove();
            break;
        case ACTORSTATE::SKILL:
            rush = false;
            stopMove();
            break;
        case ACTORSTATE::INAIR:
//            if (stateMachine->getNextAction() == HEROACTION::AIRHITDOWN) {
//                if (action == HEROACTION::AIRHITUP) {
//                    fallAccY = 0.2f;
//                    fallSpeedY = 3.0f;
//                }else{
//                    fallAccY = 0.07f;
//                    fallSpeedY = 0.8f;
//                }
//            }
            break;
        case ACTORSTATE::XULI:
        {
            std::string resPath = "armature/charge.ExportJson";
            ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);
            
            auto eff1 = Effect::create();
            eff1->initWithArmature("charge");
            eff1->setTag(XULI_EFFECT_TAG);
            eff1->setFollowY(false);
            frontEffectLayer->addChild(eff1);
        }
            break;

        default:
            break;
    }
}

void Hero::dispatchResetPunchTag()
{
    EventCustom event(HERO_RESET_PUNCH);
    event.setUserData(this);
    getEventDispatcher()->dispatchEvent(&event);
}

void Hero::updateAI()
{
//    log("curr combo : %d", comboNum);
//    log("max combo : %d", maxCombo);

    auto boneMoveVec2 = calBoneMove();
    
    updateFrontEffect();
    updateBackEffect();

    
    //状态内执行
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
                float sx = blackActor->getScaleRate();
                armature->setScaleX((flipX) ? -sx : sx);
            }
            
            //移动
            posX = getPositionX() + speedX;
            posY = getPositionY() + speedY;
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
                    }
                }
            }else{
                if (hurtStiff) {
                    posX = getPositionX() + hurtMoveSpeed;
                }else{
                    posX = getPositionX();
                }
            }

        }
            break;
          
        case ACTORSTATE::IDLE:
        {
//            currHitDownVal++;
//            currHitDownVal = MIN(deHitDownVal, currHitDownVal);
        }
            break;
        case ACTORSTATE::FELLDOWN:
        {
            if (action == HEROACTION::LIESHOCK) {
                posX = getPositionX() + lieShockSpeed;
            }
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
                
                if (killSkill!=nullptr) {
                    if (action == HEROACTION::AIRHIT)
                    {
                        boneMoveVec2.y =
                        killSkillTag->getAirAtkUpVal();
                    }else if (action == HEROACTION::AIRHITUP && killSkillTag->getFloatRate() != 99) {
                        boneMoveVec2.y *= killSkillTag->getFloatRate();
                    }
                    float hitSpeed = killSkillTag->getAirHitBackSpeed();
                    if (killSkillTag->gethitFlyRate() != 99) {
                        hitSpeed *= killSkillTag->gethitFlyRate();
                        hitSpeed += fallAccX;
                        fallAccX *= 1.25;
                        hitSpeed = MIN(10, hitSpeed);
                    }
                    hurtMoveSpeed = hitSpeed * ((currDir==DIRECT::RIGHT) ? -1 : 1);
                    posX = getPositionX() + hurtMoveSpeed;
                    
                }else{
                    posX = getPositionX() - 0.5 *((flipX) ? -1 : 1);
                }
            }
            
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
    if (getIsInvincible()){
        bool visual = armature->isVisible();
        armature->setVisible(!visual);
    }

    if (killSkillTag != nullptr) {
        if (killSkillTag->gethitFlyRate() != 99) {
            boneMoveVec2.x *= killSkillTag->gethitFlyRate();
        }
    }
    setActorShowPos(boneMoveVec2);
}
void Hero::resetWalkOrRush(int moveCmd, int dir)
{
    switch (moveCmd) {
        case KEYCOMMAND::CMD_STOPMOVE:
            rush = false;
//            stopMove();
            break;
        case KEYCOMMAND::CMD_WALK:
            rush = false;
//            getActionByTag(READY_RUSH_TAG)->stop();
//            setDir(dir);
//            startMove();
            break;
        case KEYCOMMAND::CMD_RUSH:
            rush = true;
            readyRushAtk();
//            setDir(dir);
//            startMove();
            break;
        default:
            break;
    }
    joyCommand = moveCmd;
}
void Hero::updateState()
{
//    if (rushReady && (currDir & (DIRECT::RIGHT | DIRECT::LEFT))!=0)
//    {
//        if (((currDir & DIRECT::LEFT)!=0) == flipX)
//        {
////            log("rush dir %d", currDir);
//
//            rush = true;
//            readyRushAtk();
//        }else{
//            getActionByTag(READY_RUSH_TAG)->stop();
//            rushReady = false;
//        }
//        
//    }
    bool needChange = false;
    
//    if (autoControll) {
//        switch (state) {
//            case ACTORSTATE::IDLE:
//                if (event != stateMachine->action_undefined)
//                {
//                    needChange = true;
//                    break;
//                }
//                
////                if (对方阵营没有人) {
////                    needChange = false;
////                     break;
////                }
//                if (!canFoundOpponent()) {
//                    foundSomeOneOutView();
//                    event = stateMachine->findEventVal("EVENT_MOVE2NEWVIEW");
//                    needChange = true;
//                }else{
//                    std::string skillKey = canUseSomeSkill();
//                    if (skillKey != "NONE") {
//                        event = stateMachine->findEventVal(skillKey);
//                        needChange = true;
//                    } else if (canAttackTarget()) {
//                        event = stateMachine->findEventVal("EVENT_AUTOATTACK");
//                        needChange = true;
//                    } else if (canRushAttack()) {
//                        event = stateMachine->findEventVal("EVENT_RUSHATTACK");
//                        needChange = true;
//                    } else {
//                        event = stateMachine->findEventVal("EVENT_AUTOCHASE");
//                        needChange = true;
//                    }
//                }
//                break;
//            case ACTORSTATE::MOVE:
//                if (event != stateMachine->action_undefined) {
//                    needChange = true;
//                    break;
//                }
//                if (canAttackTarget()) {
//                    event = stateMachine->findEventVal("EVENT_AUTOATTACK");
//                    needChange = true;
//                } else if (canRushAttack()) {
//                    event = stateMachine->findEventVal("EVENT_RUSHATTACK");
//                    needChange = true;
//                } else if (arriveTargetPos()) {
//                    event = stateMachine->findEventVal("EVENT_ARRIVE_TARGET");
//                    needChange = true;
//                }
//                break;
//            case ACTORSTATE::CHASE:
//                if (event != stateMachine->action_undefined) {
//                    needChange = true;
//                    break;
//                }
//                if (canAttackTarget()) {
//                    event = stateMachine->findEventVal("EVENT_AUTOATTACK");
//                    needChange = true;
//                } else if (canRushAttack()) {
//                    event = stateMachine->findEventVal("EVENT_RUSHATTACK");
//                    needChange = true;
//                } else if (arriveTargetPos()) {
//                    event = stateMachine->findEventVal("EVENT_ARRIVE_TARGET");
//                    needChange = true;
//                }
//                break;
//            default:
//                break;
//        }
//    }
    
    
    //此处相关的判断，应移交lua处理
    switch (state)
	{
        case ACTORSTATE::IDLE:
        {
            if (event == stateMachine->findEventVal("EVENT_XULI")) {
                needChange = true;
            }

            if (event != stateMachine->action_undefined) {
                needChange = true;
                break;
            }
            
            
            if (joyCommand == KEYCOMMAND::CMD_WALK)
            {
                event = stateMachine->findEventVal("EVENT_MOVE");
                needChange = true;
            }
            if (joyCommand == KEYCOMMAND::CMD_RUSH)
            {
                event = stateMachine->findEventVal("EVENT_RUSH");
                needChange = true;
            }
            
            if (currKey == GAMEKEY::BUTTON_A)
            {
                event = stateMachine->findEventVal("EVENT_ATTACK1");
                needChange = true;
            }
            if (currKey == GAMEKEY::BUTTON_SP)
            {
                if (canUseSkill(blackActor->equipSkills[SKILLS_KEY]) == SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_SKILL4");
                    needChange = true;
                }
            }
            if (keyCommand == GAMEKEY::BUTTON_S1) {
                if (canUseSkill(blackActor->equipSkills[SKILLA_KEY]) == SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_SKILLA");
                    needChange = true;
                }
            }
            if (keyCommand == GAMEKEY::BUTTON_S2) {
                if (canUseSkill(blackActor->equipSkills[SKILLB_KEY]) == SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_SKILLB");
                    needChange = true;
                }
            }
            if (keyCommand == GAMEKEY::BUTTON_S3) {
                if (canUseSkill(blackActor->equipSkills[SKILLC_KEY]) == SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_SKILLC");
                    needChange = true;
                }
            }

            if (keyCommand == GAMEKEY::BUTTON_J) {
                if (canUseSkill(blackActor->equipSkills[SKILLD_KEY]) == SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_SKILLD");
                    needChange = true;
                }
            }

        }
            break;
        case ACTORSTATE::MOVE:
            if (event != stateMachine->action_undefined) {
                needChange = true;
                break;
            }
            
            if (joyCommand == KEYCOMMAND::CMD_STOPMOVE)
            {
//                rush = false;
                event = stateMachine->findEventVal("EVENT_STOPMOVE");
                needChange = true;
            }

            if (joyCommand == KEYCOMMAND::CMD_RUSH) {
                event = stateMachine->findEventVal("EVENT_RUSH");
                needChange = true;
            }
            if (currKey == GAMEKEY::BUTTON_A)
            {
                event = stateMachine->findEventVal("EVENT_ATTACK1");
                needChange = true;
            }
            if (currKey == GAMEKEY::BUTTON_SP)
            {
                if (canUseSkill(blackActor->getSkillSPID()) == SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_SKILL4");
                    needChange = true;
                }
            }
            
            if (keyCommand == GAMEKEY::BUTTON_J) {
                if (canUseSkill(blackActor->equipSkills[SKILLD_KEY]) == SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_SKILLD");
                    needChange = true;
                }
            }
            if (keyCommand == GAMEKEY::BUTTON_S1) {
                if (canUseSkill(blackActor->equipSkills[SKILLA_KEY]) == SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_SKILLA");
                    needChange = true;
                }
            }
            if (keyCommand == GAMEKEY::BUTTON_S2) {
                if (canUseSkill(blackActor->equipSkills[SKILLB_KEY]) == SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_SKILLB");
                    needChange = true;
                }
            }
            if (keyCommand == GAMEKEY::BUTTON_S3) {
                if (canUseSkill(blackActor->equipSkills[SKILLC_KEY]) == SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_SKILLC");
                    needChange = true;
                }
            }

            break;
        case ACTORSTATE::RUSH:
        {
            if (event == stateMachine->findEventVal("EVENT_XULI")) {
                needChange = true;
            }

            if (event != stateMachine->action_undefined) {
                needChange = true;
                break;
            }
            
            if (joyCommand == KEYCOMMAND::CMD_STOPMOVE)
            {
                event = stateMachine->findEventVal("EVENT_STOPMOVE");
                needChange = true;
            }
            if (joyCommand == KEYCOMMAND::CMD_WALK) {
                event = stateMachine->findEventVal("EVENT_MOVE");
                needChange = true;
            }
            if (currKey == GAMEKEY::BUTTON_SP)
            {
                if (canUseSkill(blackActor->getSkillSPID()) == SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_SKILL4");
                    needChange = true;
                }
            }
            
            if (keyCommand == GAMEKEY::BUTTON_J) {
                if (canUseSkill(blackActor->equipSkills[SKILLD_KEY]) == SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_SKILLD");
                    needChange = true;
                }
            }
            if (keyCommand == GAMEKEY::BUTTON_S1) {
                if (canUseSkill(blackActor->equipSkills[SKILLA_KEY]) == SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_SKILLA");
                    needChange = true;
                }
            }
            if (keyCommand == GAMEKEY::BUTTON_S2) {
                if (canUseSkill(blackActor->equipSkills[SKILLB_KEY]) == SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_SKILLB");
                    needChange = true;
                }
            }
            if (keyCommand == GAMEKEY::BUTTON_S3) {
                if (canUseSkill(blackActor->equipSkills[SKILLC_KEY]) == SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_SKILLC");
                    needChange = true;
                }
            }
            if (currKey == GAMEKEY::BUTTON_A)
            {
                if (rushAtkReady) {
                    rushAtkReady = false;
                    if (canUseSkill(blackActor->getRunAttack1ID()) == SKILL_NONE_ERROR) {
                        event = stateMachine->findEventVal("EVENT_RUNATTACK1");
                    }
                }else{
                    if (canUseSkill(blackActor->getRunAttack2ID()) == SKILL_NONE_ERROR) {
                        event = stateMachine->findEventVal("EVENT_RUNATTACK2");
                    }
                }
                
                needChange = true;
            }
       }
            break;
        case ACTORSTATE::ATTACK:
            if (getIsValidAtk()) {
                if (currKey == GAMEKEY::BUTTON_A)
                {
//                    if ((frameCommand & HEROFRAMECOMMAND::COMMAND_PUNCHA2) != 0) {
//                        event = stateMachine->findEventVal("EVENT_ATTACK");
//                    }
                    if ((frameCommand & HEROFRAMECOMMAND::COMMAND_PUNCHA2) != 0) {
                        event = stateMachine->findEventVal("EVENT_ATTACK2");
                    }
                    if ((frameCommand & HEROFRAMECOMMAND::COMMAND_PUNCHA3) != 0) {
                        event = stateMachine->findEventVal("EVENT_ATTACK3");
                    }
                    if ((frameCommand & HEROFRAMECOMMAND::COMMAND_PUNCHA4) != 0) {
                        event = stateMachine->findEventVal("EVENT_ATTACK4");
                    }
                }
            }
            
            if (armature->getAnimation()->isComplete())
            {
                if (event == StateMachine::action_undefined) {
                    if (action == HEROACTION::ATTACKPART1) {
                        event = stateMachine->findEventVal("ATTACKPART1");
                    }else {
                        event = stateMachine->findEventVal("EVENT_ACTIONOVER");
                    }
                }
                needChange = true;
            }
            break;

        case ACTORSTATE::RUNATTACK:
            if (currKey == GAMEKEY::BUTTON_A)
            {
                if (currSkill->getLinkID() != -1) {
                    if (canUseSkill(currSkill->getLinkID()) == SKILL_NONE_ERROR) {
                        event = stateMachine->findEventVal("EVENT_RUNATTACK");
                    }
                }
                
            }
            if (armature->getAnimation()->isComplete()) {
                if (event == StateMachine::action_undefined) {
                    event = stateMachine->findEventVal("EVENT_ACTIONOVER");
                }
                needChange = true;
            }            
            break;
            
        case ACTORSTATE::XULI:
        {
            if (event != stateMachine->action_undefined) {
                needChange = true;
                break;
            }
            int baseSkillId = -1;
            if (keyCommand == GAMEKEY::BUTTON_S1) {
                baseSkillId = blackActor->equipSkills[SKILLA_KEY];
                event = stateMachine->findEventVal("EVENT_SKILLA");
                needChange = true;
            }else if (keyCommand == GAMEKEY::BUTTON_S2) {
                baseSkillId = blackActor->equipSkills[SKILLB_KEY];
                event = stateMachine->findEventVal("EVENT_SKILLB");
                needChange = true;
            }else if (keyCommand == GAMEKEY::BUTTON_S3) {
                baseSkillId = blackActor->equipSkills[SKILLC_KEY];
                event = stateMachine->findEventVal("EVENT_SKILLC");
                needChange = true;
            }else if (keyCommand == GAMEKEY::BUTTON_J) {
                baseSkillId = blackActor->equipSkills[SKILLD_KEY];
                event = stateMachine->findEventVal("EVENT_SKILLD");
                needChange = true;
            }
            if (baseSkillId != -1) {
                auto baseSkill = blackActor->selSkills[baseSkillId];
                int linkSkillId = baseSkill->getXuliId();
                if (canUseSkill(linkSkillId) != SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_ACTIONOVER");
                }
            }
        }
            break;
        case ACTORSTATE::SKILL:
//            if (event != stateMachine->action_undefined) {
//                needChange = true;
//                break;
//            }
            if (event == stateMachine->findEventVal("EVENT_HEADHURT")|| event == stateMachine->findEventVal("EVENT_WAISTHURT") || event == stateMachine->findEventVal("EVENT_HEADFELLGROUND") || event == stateMachine->findEventVal("EVENT_WAISTFELLGROUND") || event == stateMachine->findEventVal("EVENT_HIT2AIR") || event == stateMachine->findEventVal("EVENT_AIRHIT")) {
                state = ACTORSTATE::ANY;
                needChange = true;
                break;
            }
            
            if (keyCommand == GAMEKEY::BUTTON_S1) {
                event = stateMachine->findEventVal("EVENT_SKILLA");
            }
            if (keyCommand == GAMEKEY::BUTTON_S2) {
                event = stateMachine->findEventVal("EVENT_SKILLB");
            }
            if (keyCommand == GAMEKEY::BUTTON_S3) {
                event = stateMachine->findEventVal("EVENT_SKILLC");
            }
            if (keyCommand == GAMEKEY::BUTTON_J) {
                event = stateMachine->findEventVal("EVENT_SKILLD");
            }
            if (currKey == GAMEKEY::BUTTON_A)
            {
                keyCommand = StateMachine::action_undefined;
                event = stateMachine->findEventVal("EVENT_ATTACK1");
            }
            
//            log("skill event: %d", event);
            if (armature->getAnimation()->isComplete()) {
                log("event active: %d", event);
                if (event == StateMachine::action_undefined) {
                    event = stateMachine->findEventVal("EVENT_ACTIONOVER");
                }
                int skillId = -1;
                if (event == stateMachine->findEventVal("EVENT_SKILLA")) {
                    skillId = blackActor->equipSkills[SKILLA_KEY];
                }else if (event == stateMachine->findEventVal("EVENT_SKILLB")) {
                    skillId = blackActor->equipSkills[SKILLB_KEY];
                }else if (event == stateMachine->findEventVal("EVENT_SKILLC")) {
                    skillId = blackActor->equipSkills[SKILLC_KEY];
                }else if (event == stateMachine->findEventVal("EVENT_SKILLD")) {
                    skillId = blackActor->equipSkills[SKILLD_KEY];
                }
                if (skillId != -1) {
                    if (canUseSkill(skillId) != SKILL_NONE_ERROR) {
                        event = stateMachine->findEventVal("EVENT_ACTIONOVER");
                    }
                }
                
                needChange = true;
            }
            break;
        case ACTORSTATE::SPSKILL:
        {
            if (event != stateMachine->action_undefined) {
                needChange = true;
                break;
            }
            if (armature->getAnimation()->isComplete()) {
                event = stateMachine->findEventVal("EVENT_ACTIONOVER");
                needChange = true;
            }
        }
            break;
        case ACTORSTATE::FAINT:
            if (!isFaint) {
                event = stateMachine->findEventVal("EVENT_ACTIONOVER");
                needChange = true;
            }
            break;

        case ACTORSTATE::HURT:
            if (currKey == GAMEKEY::BUTTON_SP)
            {
                if (canUseSkill(blackActor->getSkillSPID()) == SKILL_NONE_ERROR) {
                    event = stateMachine->findEventVal("EVENT_SKILL4");
                    needChange = true;
//                    break;
                }
            }
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
                
            }
            
            break;
        case ACTORSTATE::FELLDOWN:
            if (event == stateMachine->findEventVal("EVENT_KG")) {
                needChange = true;
                break;
            }
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
                    }

                    event = stateMachine->findEventVal("GETUP");
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
                dying = true;
                needChange = false;
            }
            break;
        case ACTORSTATE::INAIR:
            if (event == stateMachine->findEventVal("EVENT_HIT2AIR") ||
                event == stateMachine->findEventVal("EVENT_HEADHURT") ||
                event == stateMachine->findEventVal("EVENT_WAISTHURT") ||
                event == stateMachine->findEventVal("EVENT_HEADFELLGROUND") ||
                event == stateMachine->findEventVal("EVENT_WAISTFELLGROUND")) {
                
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
        {
            if (armature->getAnimation()->isComplete()) {
                event = stateMachine->findEventVal("EVENT_KGE");
                needChange = true;
            }
        }
            break;
        default:
            break;
	}
    if (event == stateMachine->findEventVal("EVENT_HEADHURT")|| event == stateMachine->findEventVal("EVENT_WAISTHURT") || event == stateMachine->findEventVal("EVENT_HEADFELLGROUND") || event == stateMachine->findEventVal("EVENT_WAISTFELLGROUND") || event == stateMachine->findEventVal("EVENT_HIT2AIR") || event == stateMachine->findEventVal("EVENT_AIRHIT")) {
        state = ACTORSTATE::ANY;
        needChange = true;
    }

    
    clearKey();
    //确定要转换时，再进入状态机进行状态跳转
    if (needChange) {
        switch2NextState(state, event);
        
        needChange = false;
        event = StateMachine::action_undefined;
        keyCommand = StateMachine::action_undefined;
    }
}


bool Hero::setCurrKey(int key)
{
	if (currKey != 0)
	{
        //没松开任何一个键时，不允许再处理另外一个按键
		return false;
	}
	currKey = key;
    if (Guard != nullptr) {
        (dynamic_cast<Guardian *>(Guard))->setCurrKey(currKey);
    }
    return true;
}


void Hero::clearKey()
{
	currKey = 0;
    keyCommand = -1;
}

void Hero::readyRushAtk()
{
    setRushAtkReady(true);
    auto func2 = CallFunc::create(CC_CALLBACK_0(Hero::setRushAtkReady, this, false));
    auto rushAtkAction = Sequence::create(DelayTime::create(RUSH_LINK_TIME), func2, NULL);
    runAction(rushAtkAction);
    rushAtkAction->setTag(READY_RUSHATK_TAG);
}


void Hero::doFlag(int nextFlag)
{
    switch (nextFlag) {
        case StateAIFlag::invincible:
            addSingleBUff(true, 34, 100);
            break;
        case StateAIFlag::startFall:
        {
//            float originOffy = armature->getBone("OriginPoint")->getWorldInfo()->y;
//            fallStartY += armature->getBone(localBodyName)->getWorldInfo()->y - originOffy;
//            armature->setPositionY(fallStartY);
        }
            break;
        case StateAIFlag::endFall:
//            fallStartY = 0;
//            armature->setPositionY(0);
        default:
            break;
    }
    
    
}

//void Hero::changeSkill(int event)
//{
//    currSkill = nullptr;
//    currSkillTag = nullptr;
//    if(stateMachine->eventName.find(event) == stateMachine->eventName.end())
//    {
//        return;
//    }
//    
//    auto name = stateMachine->eventName[event];
//
//    if (name.find("EVENT_SKILL") != std::string::npos) {
//        int currIdx = -1;
//        int tagIdx = -1;
//        if (name.find("EVENT_SKILLA") != std::string::npos) {
//            currIdx = SKILLA_KEY;
//            tagIdx = SKILLA_LINK_TIMEOUT_TAG;
//        }else if (name.find("EVENT_SKILLB") != std::string::npos) {
//            currIdx = SKILLB_KEY;
//            tagIdx = SKILLB_LINK_TIMEOUT_TAG;
//        }else if (name.find("EVENT_SKILLC") != std::string::npos) {
//            currIdx = SKILLC_KEY;
//            tagIdx = SKILLC_LINK_TIMEOUT_TAG;
//        }else if (name.find("EVENT_SKILLD") != std::string::npos) {
//            currIdx = SKILLD_KEY;
//            tagIdx = SKILLD_LINK_TIMEOUT_TAG;
//        }
//        if (currIdx == -1) {
//            return;
//        }
//        
//        currSkill = blackActor->selSkills[blackActor->equipSkills[currIdx]];
//        if (name.find("_E") != std::string::npos) {
//            int xuliSkillId = currSkill->getXuliId();
//            currSkill = blackActor->selSkills[xuliSkillId];
//        }
//        currSkillTag = blackActor->selSkillTags[currSkill->getSkillID()*100 + 1];
//        
//        if (currSkill->getLinkID() != -1) {
//            blackActor->equipSkills[currIdx] = currSkill->getLinkID();
//            auto func = CallFunc::create(CC_CALLBACK_0(Hero::backSkill2Base, this, blackActor->equipSkills[currIdx], currIdx));
//            
//            stopActionByTag(tagIdx);
//            auto s = Sequence::create(DelayTime::create(currSkill->getLinkDur()),func, NULL);
//            s->setTag(tagIdx);
//            runAction(s);
//            dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene())->showLinkBar(SKILLA_BTN + (currIdx - SKILLA_KEY), blackActor->selSkills[currSkill->getLinkID()]->geticonStr(),currSkill->getLinkDur());
//        } else {
//            backSkill2Base(blackActor->equipSkills[currIdx], currIdx);
//        }
//    } else if (name.find("ATTACKPART") != std::string::npos) {
//        size_t idx = name.find_first_not_of("ATTACKPART");
//        size_t len = name.length()-idx;
//        auto num = name.substr(idx, len);
//        int index = atoi(num.c_str());
//        switch (index) {
//            case 1:
//                blackActor->equipSkills[ATK_KEY] = blackActor->getAtk1SkillID();
//                break;
//            case 2:
//                blackActor->equipSkills[ATK_KEY] = blackActor->getAtk2SkillID();
//                break;
//            case 3:
//                blackActor->equipSkills[ATK_KEY] = blackActor->getAtk3SkillID();
//                break;
//            case 4:
//                blackActor->equipSkills[ATK_KEY] = blackActor->getAtk4SkillID();
//                break;
//                
//            default:
//                return;
//        }
//        
//        currSkill = blackActor->selSkills[blackActor->equipSkills[ATK_KEY]];
//        currSkillTag = blackActor->selSkillTags[currSkill->getSkillID()*100 + 1];
//        
//    } else if (name.find("EVENT_RUNATTACK") != std::string::npos) {
//        size_t idx = name.find_first_not_of("EVENT_RUNATTACK");
//        if (idx != std::string::npos) {
//            size_t len = name.length()-idx;
//            auto num = name.substr(idx, len);
//            int index = atoi(num.c_str());
//            switch (index) {
//                case 1:
//                {
//                    blackActor->setRunAttackID(blackActor->getRunAttack1ID());
//                }
//
//                    break;
//                case 2:
//                {
//                    blackActor->setRunAttackID(blackActor->getRunAttack2ID());
//                }
//                    break;
//                default:
//                    return;
//            }
//        }
//        
//        blackActor->equipSkills[RUN_ATK_KEY] = blackActor->getRunAttackID();
//        currSkill = blackActor->selSkills[blackActor->equipSkills[RUN_ATK_KEY]];
//        currSkillTag = blackActor->selSkillTags[currSkill->getSkillID()*100+1];
//        if (currSkill->getLinkID() != -1) {
//            blackActor->setRunAttackID(currSkill->getLinkID());
//        }else if(blackActor->getSkillCID() != currSkill->getBaseSkillID()) {
//            blackActor->setRunAttackID(currSkill->getBaseSkillID());
//        }
//        
//    } else if(event == stateMachine->findEventVal("SKILLATK4")) {
//        blackActor->equipSkills[SKILLS_KEY] = blackActor->getSkillSPID();
//        currSkill = blackActor->selSkills[blackActor->equipSkills[SKILLS_KEY] ];
//        currSkillTag = blackActor->selSkillTags[currSkill->getSkillID()*100+1];
//    }
//    
//    if (currSkill != nullptr) {
//        SimpleAudioEngine::getInstance()->setEffectsVolume(0.8);
//        SimpleAudioEngine::getInstance()->playEffect(currSkillTag->getSkillSoundRes().c_str(),false,1,0,0.5);
//    }
//}

//void Hero::backSkill2Base(int skillId, int key)
//{
//    auto skl = blackActor->selSkills[skillId];
//    blackActor->equipSkills[key] = skl->getBaseSkillID();
//    skl = blackActor->selSkills[skl->getBaseSkillID()];
//    
//    dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene())->hideLinkBar(SKILLA_BTN + (key - SKILLA_KEY),skl->geticonStr(), skl->getCoolDownDur());
//}

void Hero::backSkillAtkBase()
{
    auto skl = blackActor->selSkills[blackActor->equipSkills[ATK_KEY]];
//    auto skl = blackActor->selSkills[blackActor->getAtkSkillID()];
    blackActor->setAtkSkillID(skl->getBaseSkillID());
//    dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene())->hideLinkBar(SKILLD_BTN, blackActor->selSkills[blackActor->getSkillDID()]->geticonStr(), blackActor->selSkills[blackActor->getSkillDID()]->getCoolDownDur());
}

void Hero::startXuli(int key)
{
    int skillId=-1;
    switch (key) {
        case GAMEKEY::BUTTON_S1:
//            skillId = blackActor->getSkillAID();
            skillId = blackActor->equipSkills[SKILLA_KEY];
            break;
        case GAMEKEY::BUTTON_S2:
//            skillId = blackActor->getSkillBID();
            skillId = blackActor->equipSkills[SKILLB_KEY];
            break;
        case GAMEKEY::BUTTON_S3:
//            skillId = blackActor->getSkillCID();
            skillId = blackActor->equipSkills[SKILLC_KEY];;
            break;
        case GAMEKEY::BUTTON_J:
//            skillId = blackActor->getSkillDID();
            skillId = blackActor->equipSkills[SKILLD_KEY];;
            break;
        default:
            break;
    }
    
    if (skillId == -1) {
        return;
    }
    
    auto skl = blackActor->selSkills[skillId];
    if (skl->getXuliId() == -1) {
        keyCommand = key;
        return;
    }
    
    isXuliEnough = false;
    stopActionByTag(XULI_ENOUGH_TAG);
    auto func = CallFunc::create(CC_CALLBACK_0(Hero::xuliEnough, this));
    auto s = Sequence::create(DelayTime::create(skl->getXuliDur()), func, nullptr);
    s->setTag(XULI_ENOUGH_TAG);
    runAction(s);
}

void Hero::endXuli(int key)
{
    stopActionByTag(XULI_ENOUGH_TAG);
    int skillId=-1;
//    switch (key) {
//        case GAMEKEY::BUTTON_S1:
//            skillId = blackActor->getSkillAID();
//            break;
//        case GAMEKEY::BUTTON_S2:
//            skillId = blackActor->getSkillBID();
//            break;
//        case GAMEKEY::BUTTON_S3:
//            skillId = blackActor->getSkillCID();
//            break;
//        case GAMEKEY::BUTTON_J:
//            skillId = blackActor->getSkillDID();
//            break;
//        default:
//            break;
//    }
    switch (key) {
        case GAMEKEY::BUTTON_S1:
            skillId = blackActor->equipSkills[SKILLA_KEY];
            break;
        case GAMEKEY::BUTTON_S2:
            skillId = blackActor->equipSkills[SKILLB_KEY];
            break;
        case GAMEKEY::BUTTON_S3:
            skillId = blackActor->equipSkills[SKILLC_KEY];
            break;
        case GAMEKEY::BUTTON_J:
            skillId = blackActor->equipSkills[SKILLD_KEY];
            break;
        default:
            break;
    }
    if (skillId == -1) {
        return;
    }
    
    auto skl = blackActor->selSkills[skillId];
    if (skl->getXuliId() == -1) {
        return;
    }

    keyCommand = key;
    isXuliEnough = false;
}

void Hero::xuliEnough()
{
    isXuliEnough = true;
    event = stateMachine->findEventVal("EVENT_XULI");
}


void Hero::setHp(float hp)
{
    blackActor->setHp(hp);
    GameScene::updateHp(hp, blackActor->getMaxHp());
}

void Hero::setMp(float val)
{
    float mp = MAX(0, val);
    mp = MIN(blackActor->getMaxMp(), mp);
    blackActor->setMp(mp);
    GameScene::updateMp(mp, blackActor->getMaxMp());
}
void Hero::addAv(float val)
{
    float av = blackActor->getAV() + val;
    if (av >= blackActor->getMaxAV()) {
        if (blackActor->getAp() >= blackActor->getMaxAp()) {
            blackActor->setAV(blackActor->getMaxAV()-1);
            GameScene::updateAp(blackActor->getAp(), blackActor->getAV(), blackActor->getMaxAV());
        }else{
            blackActor->setAV(0);
            blackActor->setAp(blackActor->getAp()+1);
            GameScene::updateAp(blackActor->getAp(), blackActor->getAV(), blackActor->getMaxAV());
            GameScene::addAp(1, blackActor->getAp());
        }
    }else{
        blackActor->setAV(av);
        GameScene::updateAp(blackActor->getAp(), blackActor->getAV(), blackActor->getMaxAV());
    }
}
void Hero::useAp(float val)
{
    if (val <= 0) {
        return;
    }
    float ap = blackActor->getAp() - val;
    ap = MAX(0, ap);
    blackActor->setAp(ap);
    GameScene::updateAp(blackActor->getAp(), blackActor->getAV(), blackActor->getMaxAV());
}

void Hero::setGhost(float ghost)
{
//    if (Guard == nullptr) {
//        return;
//    }
//    float val = MAX(0, ghost);
//    val = MIN(Guard->getBlackActor()->getMaxGhost(), val);
//    Guard->getBlackActor()->setGhost(ghost);
//    GameScene::updateMp(ghost, Guard->getBlackActor()->getMaxGhost());
}