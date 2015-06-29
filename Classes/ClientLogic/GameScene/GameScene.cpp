#include "GameScene.h"
#include "../SneakyJoy/SneakyJoyStickSkinnedBase.h"
#include "../Utils/BaseUtils.h"
#include "DataModule/MonsterTeam.h"
#include "DataModule/BlackBullet.h"
#include "DataModule/Skill.h"
#include "DataModule/SkillTag.h"

#include "../../Player_Account/Account_Data_Mgr.h"
#include "../../Character_System/Character_Mgr.h"
#include "../../Character_System/Player.h"

#include "UI_Interface/UI_ModalDialogue_Layer.h"
#include "../../DataModule/Little.h"
#include "ClientLogic/Actor/Colossus.h"
#include "ClientLogic/Actor/Guardian.h"

#include "Dialogue_System/DialogManager.h"
#include "Dialogue_System/DialogLayer.h"


#define HP_FULL_PERCENT 100										// 血量满格时的百分比
#define HP_BG_FULL_PERCENT 300									// 血量背景满格时的百分比
#define HP_MULTIPLE 3                                           // 血量倍数

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

Text* GameScene::hp_num;
Text* GameScene::mp_num;
LoadingBar* GameScene::hpBar;
LoadingBar* GameScene::hpBGBar;
LoadingBar* GameScene::mpBar;
//LoadingBar* GameScene::avBar;
LabelAtlas *GameScene::comboNum1;
ImageView* GameScene::apBg[4];
ProgressTimer* GameScene::ghostProg;

int nPercent			= HP_FULL_PERCENT;
int nCurrentPer			= HP_FULL_PERCENT;
int nBgPer				= HP_BG_FULL_PERCENT;

int iMpPercent          = HP_FULL_PERCENT;
int iCurrMpPercent      = HP_FULL_PERCENT;
int iBgMpPer            = HP_BG_FULL_PERCENT;

int nMonsterPercent		= HP_FULL_PERCENT;
int nMonsterCurrentPer	= HP_FULL_PERCENT;
int nMonsterBgPer		= HP_BG_FULL_PERCENT;

int apPercent = HP_FULL_PERCENT;
int ghostPercent = 0;
int GameScene::gameMode;
int GameScene::cacheGameMode;

GameScene::~GameScene()
{
    battle = nullptr;
    m_pCurrentMonster = NULL;
    Director::getInstance()->getEventDispatcher()->removeEventListener(nextTeamListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(monsterDyingListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(deadTeamListener);
//    Director::getInstance()->getEventDispatcher()->removeEventListener(selStageListener);
    ArmatureDataManager::destroyInstance();
	Director::getInstance()->purgeCachedData();
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
    
    gameMode = cacheGameMode = -1;
    
	joyDir[0] = DIRECT::RIGHT;
	joyDir[1] = DIRECT::RIGHT | DIRECT::UP;
	joyDir[2] = DIRECT::UP;
	joyDir[3] = DIRECT::LEFT | DIRECT::UP;
	joyDir[4] = DIRECT::LEFT;
	joyDir[5] = DIRECT::LEFT | DIRECT::DOWN;
	joyDir[6] = DIRECT::DOWN;
	joyDir[7] = DIRECT::RIGHT | DIRECT::DOWN;

    battle = nullptr;
    ghostPercent = 0;
    apPercent = HP_FULL_PERCENT;
    nPercent			= HP_FULL_PERCENT;
    nCurrentPer			= HP_FULL_PERCENT;
    nBgPer				= HP_BG_FULL_PERCENT;
    
    iMpPercent          = HP_FULL_PERCENT;
    iCurrMpPercent      = HP_FULL_PERCENT;
    iBgMpPer            = HP_BG_FULL_PERCENT;
    
    nMonsterPercent		= HP_FULL_PERCENT;
    nMonsterCurrentPer	= HP_FULL_PERCENT;
    nMonsterBgPer		= HP_BG_FULL_PERCENT;
    
    nextTeamListener = EventListenerCustom::create("delayNextTeam", CC_CALLBACK_1(GameScene::getNextTeam, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(nextTeamListener, -1);

    monsterDyingListener = EventListenerCustom::create("monsterDied", CC_CALLBACK_1(GameScene::monsterLogicDie, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(monsterDyingListener, -1);

    deadTeamListener = EventListenerCustom::create("arrangeDieTeam", CC_CALLBACK_1(GameScene::getDeadTeam, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(deadTeamListener, -1);
    
   
    initWithHpShow();		   // 初始化血量展示的成员变量
    
    resetGameMode(Game_Scene_State_Loading);
	return true;
}

void GameScene::initWithHpShow()
{
    /************************************************************************/
    // 初始化血量展示的成员变量
    nPercent = iMpPercent = HP_FULL_PERCENT;
    nCurrentPer = iCurrMpPercent = HP_FULL_PERCENT;
    nBgPer = iBgMpPer = HP_BG_FULL_PERCENT;
    
    nMonsterPercent = HP_FULL_PERCENT;
    nMonsterCurrentPer = HP_FULL_PERCENT;
    nMonsterBgPer = HP_BG_FULL_PERCENT;
    
    m_pCurrentMonster = NULL;
}

void GameScene::onExit()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    actorLayer->unscheduleUpdate();
    unscheduleUpdate();
//	removeAllChildren();
    Scene::onExit();
}


void GameScene::load(float dt)
{
    log("count:%d", loadCount);
    switch (loadCount) {
        case 0:
//            Skill::readFile("GameData/data_skill.json");
//            SkillTag::readFile("GameData/data_skillTag.json");
            break;
        case 1:
        {
            battle = BattleField::instance();
            battle->readFile("GameData/scene_fight.json");
//            battle = new BattleField();
        }
            break;
            
        case 2:
        {
            backLayer = Layer::create();
            if (battle->getBgImgName() != "null") {
                std::string resDir("img/scene/");
//                bgSpt = Sprite::create(resDir + battle->getBgImgName() + ".pvr.ccz");
                bgSpt = Sprite::create(resDir + battle->getBgImgName() + ".png");
                
                bgSpt->setAnchorPoint(Point(0, 1));
                bgSpt->setPosition(Vec2(0, 660));
                backLayer->addChild(bgSpt);
                addSceneEffect("bgAnim", bgSpt, true);
            }
            
            backLayer->setPosition(Vec2(0, -5));
            addChild(backLayer);
            
            midLayer = Layer::create();
            if (battle->getMidImgName() != "null") {
                std::string resDir("img/scene/");
                auto midSpt = Sprite::create(resDir + battle->getMidImgName() +".png");
                midSpt->setAnchorPoint(Point(0, 0));
                midLayer->addChild(midSpt);
                addSceneEffect("midAnim", midSpt, false);
            }
            
            midLayer->setPosition(Vec2(0, -5));
            addChild(midLayer);
            
            flashLayer = LayerColor::create(Color4B::GRAY);
            addChild(flashLayer);
            flashLayer->setVisible(false);

        }
            break;
        case 3:
        {
            std::string tiledDir = "scene/";
            auto tmx = experimental::TMXTiledMap::create(tiledDir+battle->getTiledMapName());
            
            auto transGroup = tmx->getObjectGroup("doors");
            auto npcObjs = transGroup->getObjects();
            for (auto npc : npcObjs) {
                auto dict = npc.asValueMap();
                auto npcType = dict["type"].asString();
                auto x = dict["x"].asFloat();
                auto y = dict["y"].asFloat();
                
                if (npcType == "born") {
                    hero = Hero::create();
                    hero->addHurtListener();
                    hero->setAnchorPoint(Vec2(0.5, 0));
                    hero->setPosX(x);
                    hero->setPosY(y);
                    hero->setPosition(Vec2(x, y));
                    hero->getBlackActor()->initPlayerData();
                    
                }else if (npcType == "door"){
//                    auto npcId = dict["id"].asInt();
//                    door = City_NPC::create();
//                    door->setPosition(Vec2(x, y));
//                    door->initWithId(npcId);
//                    
//                    actorLayer->addChild(door);
                }else if(npcType == "bgAnim") {
                    auto gid = dict["gid"].asInt();
                    
                    auto mapInfo = TMXMapInfo::create("");
                    auto tilesetVec = mapInfo->getTilesets();
                    for (auto tileset : tilesetVec)
                    {
                        if(tileset->_firstGid == gid)
                        {
                            break;
                        }
                    }
                }
                
            }
            hero->preloadSkillRes();
            
            actorLayer = ActorLayer::create();
            actorLayer->addChild(hero);
            actorLayer->setHero(hero);
            actorLayer->setPosition(Vec2(0, -5));
            addChild(actorLayer);
            actorLayer->fillHitEffect();
            
            auto gearGroup = tmx->getObjectGroup("trap");
            if (gearGroup == nullptr)
            {
                break;
            }
            auto gearObjs = gearGroup->getObjects();
            for (auto npc : gearObjs) {
                auto dict = npc.asValueMap();
                auto npcType = dict["actorId"].asInt();
                auto x = dict["x"].asFloat();
                auto y = dict["y"].asFloat();
                auto flipX = (dict["direct"].asInt() == 1);
                
                actorLayer->addGear(npcType, x, y, flipX);
            }


            
        }
            break;
        case 4:
        {
            if (hero->getBlackActor()->getGuardId() > 0) {
                auto guard = Guardian::create();
                hero->Guard = guard;
                guard->initFightData(hero->getBlackActor()->getGuardId());
                guard->initViewRes();
                guard->initFightState();
                guard->setMan(hero);
                guard->setPosX(hero->getPositionX());
                guard->setPosY(hero->getPositionY());
                guard->setPosition(hero->getPosition());
                guard->preloadSkillRes();
                
                actorLayer->addChild(guard);
                actorLayer->addActorHitEffect(guard);
            }
            
            if (hero->getBlackActor()->getColossusId() > 0) {
                auto col = Colossus::create();
                col->initFightData(hero->getBlackActor()->getColossusId());
                col->initViewRes();
                col->initFightState();
                col->setMan(hero);
                col->setPosX(hero->getPositionX());
                col->setPosY(hero->getPositionY());
                col->setPosition(hero->getPosition());
                col->preloadSkillRes();
                hero->colossus = col;
                actorLayer->addChild(col);
                actorLayer->addActorHitEffect(col);
            }
        }
            break;
        case 5:
        {
            camera = YNCamera::create();
            addChild(camera);
            
            scrFrtLayer = Layer::create();
            scrFrtLayer->setAnchorPoint(Vec2(0.5, 0.5));
            Size winSize = Director::getInstance()->getWinSize();
            scrFrtLayer->setPosition(Vec2(winSize.width/2, winSize.height/2));
            addChild(scrFrtLayer);
            
        }
            break;
        case 6:
        {
            ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/battle_fire/battle_fire.ExportJson");
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/hit1.wav");
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/hit2.wav");
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/hit3.wav");
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/nohit1.wav");
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/nohit2.wav");
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/wdj_skill1.wav");
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/wdj_skill3.wav");
            std::string musicFile("music/battle.mp3");
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(musicFile.c_str());
        }
            break;
        case 7:
        {
            frontLayer = Layer::create();
            if(battle->getFrontImgName() != "null")
            {
                std::string resDir("img/scene/");

                auto frontSpt = Sprite::create(resDir + battle->getFrontImgName() + ".png");
                frontSpt->setAnchorPoint(Point(0, 0));
                frontLayer->addChild(frontSpt);
                addSceneEffect("frtAnim", frontSpt, false);
            }
            
            frontLayer->setPosition(Vec2(0, -5));
            addChild(frontLayer);
        }
            break;

        case 8:
        {
            camera->setCameraCenter(hero->getPosition());
            setViewWindow();
            
            pressJoy = false;
            
            auto suc = battle->start1stWave();
            if (!suc)
            {
                break;
            }

            
            auto mons = battle->getCurrMonsterWave()->getWaitSendMons();
            sendMonster2Scene(mons);
            
            actorLayer->scheduleUpdate();

//            std::string luaFile("test/hello4.lua");
//            std::map<std::string, Value> params;
////            ValueMap params;
////            params["a"] = 1;
////            params["b"] = 2;
////            std::string sum = PublicSendLuaData::getInstance()->callLuaFuncParReturn(luaFile.c_str(), "add", params);
////            log("add: %i",atoi(sum.c_str()));
//            params["num"] = 5;
//            params["posx"] = 102.6;
//            params["posy"] = 1200.3;
//            params["action"] = "jump";
////            params["bHappy"] = true;
////          log("%s", PublicSendLuaData::getInstance()->getLuaVarString(luaFile, "str"));
////          std::string luaFile("test/hello3.lua");
//            PublicSendLuaData::getInstance()->callLuaFuncParWithTable(luaFile, "pass", params);
            
//            std::string luaFile("test/hello3.lua");
//            log("%s", PublicSendLuaData::getInstance()->callLuaFuncParWithObj(luaFile, "showactorpos", hero));
        }
            break;
        case 9:
        {
            enterGame();
        }
            break;
        default:
            break;
    }
    loadCount++;
    
    loadLayer->updateLoadBar(loadCount*10);
    if (loadCount>=10) {
        if (battle->getStartDialogId() == -1 || !firstPass) {
            resetGameMode(Game_Scene_State_Normal);
        }else{
            DialogManager::instance()->setDialogId(battle->getStartDialogId());
            DialogManager::instance()->setGroupId(battle->getStartGroupId());
            cacheGameMode = Game_Scene_State_Normal;
            resetGameMode(Game_Scene_State_Dialogue);
        }
    }
}

void GameScene::addSceneEffect(std::string groupName, Node *parent, bool alignTop)
{
    std::string tiledDir("scene/");
    auto tmx = experimental::TMXTiledMap::create(tiledDir+battle->getTiledMapName());
    
    auto midGroup = tmx->getObjectGroup(groupName);
    
    if (midGroup==nullptr) {
        return;
    }
    
    auto midObjs = midGroup->getObjects();
    for (auto npc : midObjs) {
        auto dict = npc.asValueMap();
        auto animName = dict["name"].asString();
        auto x = dict["x"].asFloat();
        auto y = dict["y"].asFloat();
        
        auto gid = dict["gid"].asInt();
        auto mapInfo = TMXMapInfo::create(tiledDir+battle->getTiledMapName());
        auto tilesetVec = mapInfo->getTilesets();
        for (auto tileset : tilesetVec)
        {
            if(tileset->_firstGid == gid)
            {
                x += tileset->_tileSize.width/2;
                y += tileset->_tileSize.height/2;
                break;
            }
        }
        if (alignTop) {
            y = bgSpt->getContentSize().height - (tmx->getMapSize().height * tmx->getTileSize().height - y);
        }
        
        auto effect = Effect::create();
        effect->initWithArmature(animName, 1);
        effect->setPosition(Vec2(x, y));
        parent->addChild(effect);
    }
}

void GameScene::enterGame()
{
    uiLayer = Layer::create();
    
    auto winSize = Director::getInstance()->getWinSize();
    Layout *battleRoot = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromJsonFile("ui/battle/battle.ExportJson"));
    battleRoot->setTag(BATTLE_LAYOUT);

    uiLayer->addChild(battleRoot);
    auto head = dynamic_cast<ImageView*>(Helper::seekWidgetByName(battleRoot, "headicon"));
    int role_id = Account_Data_Mgr::instance()->get_current_role_id();
    auto player = (Game_Data::Player*)CHARACTER_MGR::instance()->get_character(role_id);
    int job = player->get_job();
    if (job >= 3)
        job = 3;
    Value pre("img/headIcon/job_");
    Value suff(job);
    Value path(pre.asString() + suff.asString() + ".png");
    head->loadTexture(path.asString());
    attackBtn_A = dynamic_cast<Button*>(battleRoot->getChildByName("Button_14"));
    attackBtn_A->addTouchEventListener(CC_CALLBACK_2(GameScene::touchAttackEvent, this));
    
    std::string iconPath("img/joystick/");
    skillBtn_A = dynamic_cast<Button*>(battleRoot->getChildByName("skillButtonA"));
    skillBtn_A->addTouchEventListener(CC_CALLBACK_2(GameScene::touchSkill1Event, this));
    skillBtn_A->setTag(SKILLA_BTN);
    int skillId = hero->getBlackActor()->getSkillAID();
//    std::string iconName = Skill::skills[skillId].geticonStr();
    std::string iconName = hero->getBlackActor()->selSkills[skillId]->geticonStr();
    skillBtn_A->loadTextureNormal(iconPath + iconName + ".png");
    skillBtn_A->loadTexturePressed(iconPath + iconName + "_down.png");
    
    skillBtn_B = dynamic_cast<Button*>(battleRoot->getChildByName("skillButtonB"));
    skillBtn_B->addTouchEventListener(CC_CALLBACK_2(GameScene::touchSkill2Event, this));
    skillBtn_B->setTag(SKILLB_BTN);
    skillId = hero->getBlackActor()->getSkillBID();
    iconName = hero->getBlackActor()->selSkills[skillId]->geticonStr();
    skillBtn_B->loadTextureNormal(iconPath + iconName + ".png");
    skillBtn_B->loadTexturePressed(iconPath + iconName + "_down.png");

    
    skillBtn_C = dynamic_cast<Button*>(battleRoot->getChildByName("skillButtonC"));
    skillBtn_C->addTouchEventListener(CC_CALLBACK_2(GameScene::touchSkill3Event, this));
    skillBtn_C->setTag(SKILLC_BTN);
    skillId = hero->getBlackActor()->getSkillCID();
    iconName = hero->getBlackActor()->selSkills[skillId]->geticonStr();
    skillBtn_C->loadTextureNormal(iconPath + iconName + ".png");
    skillBtn_C->loadTexturePressed(iconPath + iconName + "_down.png");
    
    auto skill_Y_Bg = dynamic_cast<ImageView*>(Helper::seekWidgetByName(battleRoot, "pet_skill_back"));
    
    skillBtn_Y = dynamic_cast<Button*>(Helper::seekWidgetByName(battleRoot, "pet_skill"));
    skillBtn_Y->setTag(SKILLY_BTN);
    if (hero->Guard != nullptr) {
        skillBtn_Y->addTouchEventListener(CC_CALLBACK_2(GameScene::touchSkillYEvent, this));
//        skillId = hero->Guard->getBlackActor()->getSkillAID();
//        iconName = hero->Guard->getBlackActor()->selSkills[skillId]->geticonStr();
//        skillBtn_Y->loadTextureNormal(iconPath + iconName + ".png");
//        skillBtn_Y->loadTexturePressed(iconPath + iconName + "_down.png");
    }
    ghostProg = ProgressTimer::create(Sprite::create("img/joystick/pet_energy.png"));
    ghostProg->setPosition(skill_Y_Bg->getContentSize().width/2, skill_Y_Bg->getContentSize().height/2);
    ghostProg->setType( ProgressTimer::Type::BAR);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    ghostProg->setMidpoint(Vec2(0,0));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    ghostProg->setBarChangeRate(Vec2(0, 1));
//    ghostProg->setReverseDirection(false);
    ghostProg->setPercentage(0);
    skill_Y_Bg->addChild(ghostProg, 0);
    if (hero->Guard == nullptr) {
        skill_Y_Bg->setVisible(false);
        skillBtn_Y->setVisible(false);
    }
    
    spSkillBtn = dynamic_cast<Button*>(battleRoot->getChildByName("Button_15"));
    spSkillBtn->addTouchEventListener(CC_CALLBACK_2(GameScene::touchSPEvent, this));
    
    jumpBtn = dynamic_cast<Button*>(battleRoot->getChildByName("jumpButton"));
//    jumpBtn->setColor(Color3B(45, 45, 45));
    jumpBtn->addTouchEventListener(CC_CALLBACK_2(GameScene::touchJumpEvent, this));
    jumpBtn->setTag(SKILLD_BTN);
    skillId = hero->getBlackActor()->getSkillDID();
    iconName = hero->getBlackActor()->selSkills[skillId]->geticonStr();
    jumpBtn->loadTextureNormal(iconPath + iconName + ".png");
    jumpBtn->loadTexturePressed(iconPath + iconName + "_down.png");

    
    exitBtn = dynamic_cast<Button*>(battleRoot->getChildByName("run"));
    exitBtn->addTouchEventListener(CC_CALLBACK_2(GameScene::touchExitButton, this));
    
    joyStick = SneakyJoystick::create();
    joyStick->initWithRect(Rect(0, 0, 427,winSize.height), true);
    joyStick->setAutoCenter(true);
    joyStick->setHasDeadzone(true);
    joyStick->setDeadRadius(10);
    rushPart = 0;
    pressJoy1 = false;
    pressDur[0] = 0;
    pressDur[1] = 0;
    releaseDur = 0;
    lastRushCmd = rushCmd = KEYCOMMAND::CMD_STOPMOVE;
    lastDir = DIRECT::NONE;
//    joyStick->setScale(0.8f);
    
    auto btnBack = dynamic_cast<ImageView*>(battleRoot->getChildByName("pad_back_0"));
    btnBack->setVisible(false);
    auto joySkin = SneakyJoystickSkinnedBase::create();
    joySkin->setBackgroundSprite(Sprite::create("img/joystick/pad_back.png"));
    joySkin->setThumbSprite(Sprite::create("img/joystick/pad.png"));
    
    joySkin->setPosition(btnBack->getPosition());
    joySkin->setJoystick(joyStick);
    btnBack = dynamic_cast<ImageView*>(battleRoot->getChildByName("pad_0"));
    btnBack->setVisible(false);

    uiLayer->addChild(joySkin);
    
    comboBack = Sprite::create("img/battle/comboBg.png");
    comboBack->setAnchorPoint(Vec2(0.5, 0.5));
    comboBack->setPosition(Vec2(winSize.width-120, winSize.height-160));
    comboBack->setVisible(false);
    uiLayer->addChild(comboBack);
    
    comboLabel = Sprite::create("img/battle/comboLable.png");
    comboLabel->setAnchorPoint(Vec2(0.5, 0.5));
    comboLabel->setPosition(Vec2(winSize.width-60, winSize.height-180));
    comboLabel->setVisible(false);
    uiLayer->addChild(comboLabel);
    
    comboNum = LabelAtlas::create("0123456789", "img/battle/comboNum.png", 50, 60, '0');
    comboNum->setString("65");
    comboNum->setAnchorPoint(Vec2(1, 0.5));
    comboNum->setPosition(Vec2(winSize.width-140, winSize.height-160));
    comboNum->setVisible(false);
    uiLayer->addChild(comboNum);
    
    comboNum1 = LabelAtlas::create("0123456789", "img/battle/comboNum.png", 50, 60, '0');
    comboNum1->setString("65");
    comboNum1->setAnchorPoint(Vec2(0, 0.5));
    comboNum1->setPosition(Vec2(winSize.width-140, winSize.height-160));
    comboNum1->setVisible(false);
    uiLayer->addChild(comboNum1);

    this->addChild(uiLayer);

    skillALinkBg = Sprite::create("img/battle/skillLinkBg.png");
    skillALinkBg->setTag(SKILLA_LBG);
    addChild(skillALinkBg);
    skillALinkBg->setVisible(false);

    skillBLinkBg = Sprite::create("img/battle/skillLinkBg.png");
    skillBLinkBg->setTag(SKILLB_LBG);
    addChild(skillBLinkBg);
    skillBLinkBg->setVisible(false);
    
    skillCLinkBg = Sprite::create("img/battle/skillLinkBg.png");
    skillCLinkBg->setTag(SKILLC_LBG);
    addChild(skillCLinkBg);
    skillCLinkBg->setVisible(false);

    skillDLinkBg = Sprite::create("img/battle/skillLinkBg.png");
    skillDLinkBg->setTag(SKILLD_LBG);
    addChild(skillDLinkBg);
    skillDLinkBg->setVisible(false);
    
    skillAClock = TextAtlas::create("0123456789", "img/battle/CDNum.png", 28, 35, "0");
    addChild(skillAClock, 4999, SKILLA_TEXT);
    skillAClock->setVisible(false);

    skillBClock = TextAtlas::create("0123456789", "img/battle/CDNum.png", 28, 35, "0");
    addChild(skillBClock, 4999, SKILLB_TEXT);
    skillBClock->setVisible(false);
    
    skillCClock = TextAtlas::create("0123456789", "img/battle/CDNum.png", 28, 35, "0");
    addChild(skillCClock, 4999, SKILLC_TEXT);
    skillCClock->setVisible(false);
    
    skillDClock = TextAtlas::create("0123456789", "img/battle/CDNum.png", 28, 35, "0");
    addChild(skillDClock, 4999, SKILLD_TEXT);
    skillDClock->setVisible(false);
    schedule(schedule_selector(GameScene::skillACDClock), 0);

    /****************************************** dely ***************************************/
    auto tLevel = dynamic_cast<Text*>(Helper::seekWidgetByName(battleRoot, "level"));
    
    tLevel->setString(Convert2String(hero->getBlackActor()->getLevel()));
    
    hp_num = dynamic_cast<Text*>(Helper::seekWidgetByName(battleRoot, "hp num"));
    mp_num = dynamic_cast<Text*>(Helper::seekWidgetByName(battleRoot, "mp num"));
    
    std::string curHpNum(Convert2String(hero->getBlackActor()->getHp()));
    std::string maxHpNum(Convert2String(hero->getBlackActor()->getMaxHp()));
    Value hpString(curHpNum + "/" + maxHpNum);
    hp_num->setString(hpString.asString());
    std::string tStr;
    
    tStr = Convert2String(hero->getBlackActor()->getMp());
    tStr += "/";
    tStr += Convert2String(hero->getBlackActor()->getMaxMp());
    mp_num->setString( tStr );
    
    hpBar = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(battleRoot,"hp_bar"));
    hpBar->setPercent(hero->getBlackActor()->getHp()/(hero->getBlackActor()->getMaxHp())*100);
    
    hpBGBar = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(battleRoot, "hp_bar_back"));
    hpBGBar->setPercent(hero->getBlackActor()->getHp() / (hero->getBlackActor()->getMaxHp()) * 100);
    
    mpBar = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(battleRoot, "mp_bar"));
    mpBar->setPercent(hero->getBlackActor()->getMp()/(hero->getBlackActor()->getMaxMp())*100);
    
//    avBar = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(battleRoot, "energy"));
//    avBar->setPercent(0);
    for (int i = 0; i<4; i++) {
        std::string boardName = "Image_50_";
        boardName += Convert2String(i);
        apBg[i] = dynamic_cast<ImageView *>(Helper::seekWidgetByName(battleRoot, boardName));
        if(hero->getBlackActor()->getAp() <= i)
        {
            apBg[i]->setVisible(false);
            auto arm = Armature::create("battle_fire");
            arm->getAnimation()->playWithIndex(0);
            arm->setPosition(apBg[i]->getContentSize().width/2, apBg[i]->getContentSize().height/2);
            apBg[i]->addChild(arm);
        }
    }
    
    monsterHpBar = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(battleRoot, "boss_hp_bar"));
    monsterHpBar->setVisible(false);
    monsterHpBg = dynamic_cast<ImageView*>(Helper::seekWidgetByName(battleRoot, "boss_hp_back"));
    monsterHpBg->setVisible(false);
    
    monsterHpBGBar = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(battleRoot, "boss_hp_bg_bar"));
    monsterHpBGBar->setVisible(false);
    
    monsterHpBg = dynamic_cast<ImageView*>(Helper::seekWidgetByName(battleRoot, "boss_hp_back"));
    monsterHpBg->setVisible(false);

    auto runOut = dynamic_cast<Button*>(Helper::seekWidgetByName(battleRoot, "run") );
    runOut->setTouchEnabled(true);
    runOut->addTouchEventListener( CC_CALLBACK_2(GameScene::runOut,this) );

    goalLayer = Layer::create();
    int type = battle->getCondition();
    if (type<0 || type>boss)
        _sendType = normal;
    else
    {
        _sendType = type;
    }
    if (_sendType == suvival)
    {
        _limitTime = battle->getTime(); _firstTime = _currentTime = _lastTime = 0;
        _showTimeRed   = TextAtlas::create("0123456789:;<", "red.png", 46, 48, "0");
        _showTimeGreen = TextAtlas::create("0123456789:;<", "green.png", 46, 48, "0");
        _showTimeRed->setPosition( Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2 +150) );
        _showTimeRed->setAnchorPoint( Vec2(0.5f, 0.5f) );
        goalLayer->addChild(_showTimeRed,4999);
        
    }else if (_sendType == count)
    {
        _limitTime = battle->getTime(); _firstTime = _currentTime = _lastTime = 0;
        _showTimeRed = TextAtlas::create("0123456789:;<", "red.png", 46, 48, "0");
        _showTimeGreen = TextAtlas::create("0123456789:;<", "green.png", 46, 48, "0");
        _showTimeRed->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2 + 150));
        _showTimeRed->setAnchorPoint(Vec2(0.5f, 0.5f));
        goalLayer->addChild(_showTimeRed, 4999);
        
        _limitCount = battle->getCount(); _currentCount = 0;
        _showCountGreen = TextAtlas::create( "0123456789:;<", "green.png", 46, 48, "0"); _showCountGreen->setAnchorPoint(Vec2(1.f, 0.5f) );
        _showCountGreen->setPosition( Vec2(Director::getInstance()->getWinSize().width - 200, Director::getInstance()->getWinSize().height - 150) );
        goalLayer->addChild(_showCountGreen, 4999);
        
        _showCountRed = TextAtlas::create( "0123456789:;<", "red.png", 46, 48, "0"); _showCountRed->setAnchorPoint(Vec2(1.f, 0.5f) );
        _showCountRed->setPosition( Vec2(Director::getInstance()->getWinSize().width - 50, Director::getInstance()->getWinSize().height - 150) );
        goalLayer->addChild(_showCountRed, 4999);
        
    }else if (_sendType == hp)
    {
        _limitHp = battle->getHp();
        _showPreRed = Text::create();
        _showPreRed->setAnchorPoint(Vec2(1.f, 0.5f)); _showPreRed->setFontName("/fonts/ktwz.ttf"); _showPreRed->setFontSize(48); _showPreRed->setColor(Color3B::RED);
        _showPreRed->setPosition( Vec2(Director::getInstance()->getWinSize().width - 290, Director::getInstance()->getWinSize().height - 150) );
        _showPreRed->setString(Little::helps[1].name);
        goalLayer->addChild(_showPreRed, 4999);
        
        _showHpRed = TextAtlas::create( "0123456789:;<", "red.png", 46, 48, "0"); _showHpRed->setAnchorPoint(Vec2(1.f, 0.5f) );
        _showHpRed->setPosition( Vec2(Director::getInstance()->getWinSize().width - 130, Director::getInstance()->getWinSize().height - 150) );
        Value midStr(_limitHp);
        _showHpRed->setString(midStr.asString() + "<");
        goalLayer->addChild(_showHpRed, 4999);
        
        _showSuffRed = Text::create();
        _showSuffRed->setAnchorPoint(Vec2(1.f, 0.5f)); _showSuffRed->setFontName("/fonts/ktwz.ttf"); _showSuffRed->setFontSize(48); _showSuffRed->setColor(Color3B::RED);
        _showSuffRed->setPosition(Vec2(Director::getInstance()->getWinSize().width - 20, Director::getInstance()->getWinSize().height - 150));
        _showSuffRed->setString(Little::helps[2].name);
        goalLayer->addChild(_showSuffRed, 4999);
        
        
    }else
    {
        
    }
    addChild(goalLayer);
   
    tipBg = Sprite::create("img/battle/recommend_top.png");
    tipLabel = Label::createWithSystemFont("", "arial", 16);
    tipLabel->setPosition(tipBg->getContentSize().width/2, tipBg->getContentSize().height/2);
    tipLabel->setColor(Color3B::BLUE);
    tipBg->addChild(tipLabel);
    tipBg->setPosition(Vec2(winSize.width/2, winSize.height/2));
    addChild(tipBg);
    tipBg->setVisible(false);
    /****************************************** dely ***************************************/

    std::string musicFile("music/battle.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(musicFile.c_str(), true);
    battle->notifyServerTime();
    
    scheduleUpdate();
}

int GameScene::decodeJoyStick(float delta)
{
    int dir = -1;
    if (joyStick->getPress()) {
        //8方向
        float dirDegree = joyStick->getDegrees();
        dir = ((dirDegree - 22) / 45 + 1);
        
        if (pressJoy1) {
            //hold press
            switch (rushPart) {
                case 1://第一次持续按左右方向，则计时
                    pressDur[0] += delta;
                    if (pressDur[0] > 0.2) {
                        rushPart = 0;
                    }
                    break;
                case 3://左右方向下双击后的持续计时
                    pressDur[1] += delta;
                    if (pressDur[1] > 0.5) {
                        rushCmd = KEYCOMMAND::CMD_WALK;
                        rushPart = 0;
                        lastDir = DIRECT::NONE;
                    }
                    break;
                default:
                    break;
            }
            
        } else {
            //press down
            pressJoy1 = true;

            int currDir_X = joyDir[dir % 8];
            currDir_X &= ~DIRECT::UP;
            currDir_X &= ~DIRECT::DOWN;
            

            if (currDir_X == DIRECT::NONE) {//本次没有左右分量
                rushCmd = KEYCOMMAND::CMD_WALK;
                rushPart = 0;
            }else if (lastDir == currDir_X) {//同方向点两下,且必有左右分量
                switch (rushPart) {
                    case 0:
                        rushCmd = KEYCOMMAND::CMD_WALK;
                        rushPart = 1;
                        pressDur[0] = 0;
                        break;
                    case 2:
                    if (releaseDur <= 0.2) {
                        rushCmd = KEYCOMMAND::CMD_RUSH;
                        rushPart = 3;
                        pressDur[1] = 0;
                    }else{
                        rushCmd = KEYCOMMAND::CMD_WALK;
                        rushPart = 0;
                        lastDir = DIRECT::NONE;
                    }
                        break;
                        
                    default:
                        break;
                }
                
            }else{//首次确定左右
                rushCmd = KEYCOMMAND::CMD_WALK;
                rushPart = 1;
                pressDur[0] = 0;
            }
                
            lastDir = currDir_X;
        }
    } else {
        pressJoy1 = false;
        //松开左右
        if (lastDir != DIRECT::NONE) {
            switch (rushPart) {
                case 1://第一次点击后松开
                    releaseDur = 0;
                    rushPart
                    = 2;
                    break;
                case 2://松开计时
                    releaseDur += delta;
                    if (releaseDur > 0.2) {
                        rushPart = 0;
                        lastDir = DIRECT::NONE;
                    }
                    break;
                case 3:
                {//已经开始冲刺时，松开按键应对其无影响
                    pressDur[1] += delta;
                    if (pressDur[1] > 0.5) {
                        rushPart = 0;
                        lastDir = DIRECT::NONE;
                    }
                }
                    return rushCmd;
                default:
                    break;
            }
        }
        rushCmd = KEYCOMMAND::CMD_STOPMOVE;
    }
    if (dir == -1) {
        return -1;
    }
    return joyDir[dir % 8];
}

void GameScene::update(float delta)
{
    battle->waitPacket();
    
    switch (gameMode) {
        case Game_Scene_State_Dialogue:
            if (DialogManager::instance()->getDialogOver()) {
                resetGameMode(cacheGameMode);
                cacheGameMode = -1;
            }
            break;
        case Game_Scene_State_Normal:
        {
            if (updateSendByType(_sendType, delta)) {
                return;
            }
            
            int dir = decodeJoyStick(delta);
            if (joyStick->getPress()) {
                hero->setDir(dir);
                hero->startMove();
            }
            if (lastRushCmd != rushCmd) {
                hero->resetWalkOrRush(rushCmd, dir);
                lastRushCmd = rushCmd;
            }
            
            hero->logic(delta);
            hero->adjustHurtEffectPos();
            camera->setCameraCenter(hero->getPosition());
            setViewWindow();

        }
            break;
            
        default:
            break;
    }
    
    if (hero->getComboNum() >= 10 && hero->getShowCombo()) {
        comboNum->setString(Convert2String(hero->getComboNum()/10));
        comboNum->setVisible(true);
    }else if (!hero->getShowCombo()) {
        comboNum->setVisible(false);
    }
    
    comboNum1->setString(Convert2String(hero->getComboNum()%10));
    comboNum1->setVisible(hero->getShowCombo());
    comboBack->setVisible(hero->getShowCombo());
    comboLabel->setVisible(hero->getShowCombo());
    showMonster();
    
    if (nCurrentPer > nPercent)
    {
        --nCurrentPer;
        if (hpBar == NULL)
            return;
        
        hpBar->setPercent(nCurrentPer);
    }else if (nCurrentPer < nPercent) {
        nCurrentPer = nPercent;
        hpBar->setPercent(nCurrentPer);
        hpBGBar->setPercent(nCurrentPer);
    }
    int nTemp = nBgPer / HP_MULTIPLE;
    if (nTemp > nPercent)
    {
        --nBgPer;
        if (hpBGBar == NULL)
            return;
        
        hpBGBar->setPercent(nTemp);
    }
    
    mpBar->setPercent(iMpPercent);
    
}

void GameScene::changeCombo()
{
    comboNum1->stopActionByTag(COMBOBOOM_TAG);
    auto scale1 = ScaleTo::create(0.01, 0.8);
    auto scale2 = ScaleTo::create(0.05, 1.8);
    auto scale3 = ScaleTo::create(0.03, 1);
    auto seq = Sequence::create(scale1, scale2, scale3, NULL);
    seq->setTag(COMBOBOOM_TAG);
    comboNum1->runAction(seq);
}

void GameScene::setViewWindow()
{
	Vec2 off;
	auto winSize = Director::getInstance()->getWinSize();

	off.x = fmax(camera->getPositionX() - winSize.width / 2, 0);
	off.x = fmin(off.x, MAP_AREA_WIDTH - winSize.width);
	off.y =  YNCamera::bShake?camera->vShake():0;

    if (bgSpt != nullptr) {
        int bgWidth = bgSpt->getTexture()->getPixelsWide();
        float bgOffx = fmax(MAP_AREA_WIDTH - bgWidth, 0) / (MAP_AREA_WIDTH - winSize.width)*off.x;
        backLayer->setPosition(Vec2(0, -5) - off + Vec2(bgOffx, 0));
    }
	midLayer->setPosition(Vec2(0, -5) - off);
	actorLayer->setPosition(Vec2(0, -5) - off);
	frontLayer->setPosition(Vec2(0, -5) - off);
    if (YNCamera::flashCount > 0) {
        if (YNCamera::flashCount % 2 == 0) {
            backLayer->setVisible(false);
            midLayer->setVisible(false);
            frontLayer->setVisible(false);
            flashLayer->setVisible(true);
        }else{
            backLayer->setVisible(true);
            midLayer->setVisible(true);
            frontLayer->setVisible(true);
            flashLayer->setVisible(false);
        }
        YNCamera::flashCount--;
    }
}

bool GameScene::attackDown(Touch* touch, Event* event)
{
	Vec2 locationInNode = attckBtn->convertToNodeSpace(touch->getLocation());
	Size s = attckBtn->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	if (rect.containsPoint(locationInNode))
	{
		std::string tex("img/joystick/buttonA_2.png");
		attckBtn->setTexture(tex);
		hero->setCurrKey(GAMEKEY::BUTTON_A);
		return true;
	}

	return false;
}

void GameScene::attackUp(Touch* touch, Event* event)
{

	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	if (target == attckBtn)
	{
		hero->clearKey();
		std::string tex("img/joystick/buttonA_1.png");
		attckBtn->setTexture(tex);
	}
}

void GameScene::attackCancel(Touch* touch, Event* event)
{
	attackUp(touch, event);
}

void GameScene::touchSkill1Event(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            hero->setCurrKey(GAMEKEY::BUTTON_S1);
            hero->startXuli(GAMEKEY::BUTTON_S1);
            break;
            
            
        case Widget::TouchEventType::ENDED:
        case Widget::TouchEventType::CANCELED:
        {
            hero->clearKey();
            hero->endXuli(GAMEKEY::BUTTON_S1);
        }
            break;
            
            
        default:
            break;
    }
}

void GameScene::hideLinkBar(int btnTag, std::string iconName, float cd)
{
    Layout *battleRoot = dynamic_cast<Layout *>(uiLayer->getChildByTag(BATTLE_LAYOUT));
    auto btn = dynamic_cast<Button *>(battleRoot->getChildByTag(btnTag));
    std::string iconPath("img/joystick/");
    btn->loadTextureNormal(iconPath + iconName + ".png");
    btn->loadTexturePressed(iconPath + iconName + "_down.png");
    
    stopActionByTag(btnTag + 12);
    auto linkBg = getChildByTag(btnTag + 4);
    linkBg->setVisible(false);
    btn->setColor(Color3B(100,100,100));
    btn->setEnabled(false);
    btn->setTouchEnabled(false);
    auto text = getChildByTag(btnTag + 16);
    text->setPosition(btn->getPosition());
    text->setVisible(true);
    
    removeChildByTag(btnTag + 8);
}

void GameScene::skillACDClock(float dt)
{
    Layout *battleRoot = dynamic_cast<Layout *>(uiLayer->getChildByTag(BATTLE_LAYOUT));
    for (int i = SKILLA_KEY; i <= SKILLD_KEY; i++) {
        int skillId = hero->getBlackActor()->equipSkills[i];
        if (skillId<=0) {
            continue;
        }
        
        auto skill = hero->getBlackActor()->selSkills[skillId];
        auto clockText = dynamic_cast<TextAtlas *>(getChildByTag(SKILLA_TEXT+i-SKILLA_KEY));
        if (skill->getCooling()) {
            float time = skill->getCoolTime();
            char str[10] = {0};
            sprintf(str, "%1.0f", time);
            
            clockText->setString( str );
            clockText->setVisible(true);
            return;
        }
        
        clockText->setVisible(false);
        auto btn = dynamic_cast<Button *>(battleRoot->getChildByTag(SKILLA_BTN+i-SKILLA_KEY));
        btn->setEnabled(true);
        btn->setTouchEnabled(true);
        btn->setColor(Color3B::WHITE);
    }

}

void GameScene::showLinkBar(int btnTag, std::string iconName, float duration)
{
    Layout *battleRoot = dynamic_cast<Layout *>(uiLayer->getChildByTag(BATTLE_LAYOUT));
    auto btn = dynamic_cast<Button *>(battleRoot->getChildByTag(btnTag));
    std::string iconPath("img/joystick/");
    btn->loadTextureNormal(iconPath + iconName + ".png");
    btn->loadTexturePressed(iconPath + iconName + "_down.png");
    
    auto linkBg = getChildByTag(btnTag + 4);
    linkBg->setPosition(btn->getPosition());
    linkBg->setVisible(true);
    
    stopActionByTag(btnTag + 12);
    auto to1 = Sequence::createWithTwoActions(ProgressTo::create(0, 100), ProgressTo::create(duration, 0));
    to1->setTag(btnTag +12);
    auto timeLeft = ProgressTimer::create(Sprite::create("img/battle/skillLinkBar.png"));
    timeLeft->setType( ProgressTimer::Type::RADIAL );
    timeLeft->setTag(btnTag + 8);
    timeLeft->setReverseDirection(true);
    addChild(timeLeft);
    timeLeft->setPosition(btn->getPosition());
    timeLeft->runAction(to1);
}

void GameScene::touchSkill2Event(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            hero->setCurrKey(GAMEKEY::BUTTON_S2);
            hero->startXuli(GAMEKEY::BUTTON_S2);
            break;
            
            
        case Widget::TouchEventType::ENDED:
        case Widget::TouchEventType::CANCELED:
            hero->clearKey();
            hero->endXuli(GAMEKEY::BUTTON_S2);
            break;
            
            
        default:
            break;
    }
}
void GameScene::touchSkill3Event(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            hero->setCurrKey(GAMEKEY::BUTTON_S3);
            hero->startXuli(GAMEKEY::BUTTON_S3);
            break;
            
            
        case Widget::TouchEventType::ENDED:
        case Widget::TouchEventType::CANCELED:
            hero->clearKey();
            hero->endXuli(GAMEKEY::BUTTON_S3);
            break;
            
            
        default:
            break;
    }
}
void GameScene::touchSkillYEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            hero->setCurrKey(GAMEKEY::BUTTON_Y);
            break;
            
            
        case Widget::TouchEventType::ENDED:
        case Widget::TouchEventType::CANCELED:
            hero->clearKey();
            break;
            
            
        default:
            break;
    }
}
void GameScene::touchSPEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            hero->setCurrKey(GAMEKEY::BUTTON_SP);
            break;
            
            
        case Widget::TouchEventType::ENDED:
        case Widget::TouchEventType::CANCELED:
            hero->clearKey();
            break;
            
            
        default:
            break;
    }
}

void GameScene::touchAttackEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            hero->setCurrKey(GAMEKEY::BUTTON_A);
            break;
            
            
        case Widget::TouchEventType::ENDED:
        case Widget::TouchEventType::CANCELED:
            hero->clearKey();
            break;

            
        default:
            break;
    }
}

void GameScene::touchJumpEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            hero->setCurrKey(GAMEKEY::BUTTON_J);
            hero->startXuli(GAMEKEY::BUTTON_J);
            break;
            
        case Widget::TouchEventType::ENDED:
        case Widget::TouchEventType::CANCELED:
            hero->clearKey();
            hero->endXuli(GAMEKEY::BUTTON_J);
        default:
            break;
    }
}

void GameScene::touchExitButton(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
        {
            //auto exitDialog = DialogueLayer::create();
            //addChild(exitDialog);  

        }
            break;
		case Widget::TouchEventType::ENDED:
		{
			/* ================================= dely =====================================*/
			/*auto hallScene = HallScene::create();
			Director::getInstance()->replaceScene(hallScene);*/
			/* ================================= dely =====================================*/
		}
			break;
        default:
            break;
    }
}

void GameScene::sendMonster2Scene(std::vector<mon> mons)
{
    for (auto mon : mons) {
        if (!mon.fromTmx) {
            mon.y = abs(rand())%(MAP_AREA_TOP-MAP_AREA_BOTTOM)+MAP_AREA_BOTTOM;
            auto winSize = Director::getInstance()->getWinSize();
            switch (mon.posType) {
                case 1:
                {
                    mon.x = camera->getPositionX() + winSize.width/2 + abs(rand()%(40));
                }
                    break;
                case 2:
                {
                    mon.x = camera->getPositionX() - winSize.width/2 - abs(rand()%(40));
                }
                    break;
                case 3:
                {
                    mon.x = camera->getPositionX() + rand()%((int)(winSize.width/2));
                }
                    break;
                default:
                    break;
            }
        }
        actorLayer->addMonster(mon.monId, mon.teamId, mon.x, mon.y);
    }
    battle->getCurrMonsterWave()->sendWaitOver();
}

void GameScene::getDeadTeam(EventCustom* event)
{
    MonsterTeam *team = static_cast<MonsterTeam *>(event->getUserData());
    int dialogId = team->getEndDialogueID();
    int groupId = team->getEndGroupID();
    MonsterWave::instance()->sendTeam(team->getDieTeamId());
    auto mons = battle->getCurrMonsterWave()->getWaitSendMons();
    sendMonster2Scene(mons);
    if (dialogId != -1 && firstPass) {
        DialogManager::instance()->setDialogId(dialogId);
        DialogManager::instance()->setGroupId(groupId);
        cacheGameMode = Game_Scene_State_Normal;
        resetGameMode(Game_Scene_State_Dialogue);
    }
}

void GameScene::getNextTeam(EventCustom* event)
{
    MonsterTeam *team = static_cast<MonsterTeam *>(event->getUserData());

    if (team->getNextTeamId() != 0) {
        auto func = CallFunc::create(CC_CALLBACK_0(GameScene::sendTeam2Scene, this, team));
        auto delay = DelayTime::create(team->getTeamInterval());

        runAction(Sequence::create(delay, func, NULL));
    }
}

void GameScene::sendTeam2Scene(MonsterTeam *team)
{
    MonsterWave::instance()->sendTeam(team->getNextTeamId());
    auto mons = battle->getCurrMonsterWave()->getWaitSendMons();
    sendMonster2Scene(mons);
    
    int dialogId = -1;
    int groupId = -1;
     MonsterTeam *realTeam = MonsterWave::instance()->getTeam(team->getNextTeamId());
    if (realTeam != nullptr) {
        dialogId = realTeam->getBeginDialogueID();
        groupId = realTeam->getBeginGroupId();
    }
    if (dialogId != -1 && firstPass) {
        DialogManager::instance()->setDialogId(dialogId);
        DialogManager::instance()->setGroupId(groupId);
        cacheGameMode = Game_Scene_State_Normal;
        resetGameMode(Game_Scene_State_Dialogue);
    }
}

void GameScene::monsterLogicDie(EventCustom* event)
{
    auto monster = static_cast<Monster *>(event->getUserData());
    int teamId = monster->getTeamId();
    _currentCount++;
    
    MonsterTeam *team = MonsterWave::instance()->getTeam(teamId);
    int dialogId = -1;
    int groupId = -1;
    if(MonsterWave::instance()->someOneDead(teamId))
    {
        if (team != nullptr) {
            dialogId = team->getEndDialogueID();
            groupId = team->getEndGroupID();
        }
        if(battle->change2NextWave())
        {
            auto mons = battle->getCurrMonsterWave()->getWaitSendMons();
            sendMonster2Scene(mons);
        }
        
        if (dialogId != -1 && firstPass) {
            DialogManager::instance()->setDialogId(dialogId);
            DialogManager::instance()->setGroupId(groupId);
            cacheGameMode = Game_Scene_State_Normal;
            resetGameMode(Game_Scene_State_Dialogue);
        }
        
    }
    
    
}

void GameScene::popSelStage()
{
	selBattleLayer = SelectBattleLayer::create();

	selBattleLayer->updateData();
	addChild(selBattleLayer);
}

/****************************************** dely ***************************************/
void GameScene::updateAp(int currAp, int currAv, int maxAv)
{
//    avBar->setPercent((float)currAv/maxAv*100);
    
    for (int i = 0; i < 4; i++) {
        apBg[i]->setVisible(i<currAp);
    }
}
void GameScene::addAp(int val, int currAp)
{
    for (int i = currAp-1; val > 0; val--) {
        if (apBg[i]->isVisible()) {
            auto effect = Effect::create();
            effect->initWithArmatureAR("blast");
            effect->setPosition(apBg[i]->getContentSize().width/2, apBg[i]->getContentSize().height/2);
//            effect->setPosition(Vec2(x, y));
            apBg[i]->addChild(effect);
        }
    }
}

void GameScene::updateHp(int curHp,int maxHp)
{
    nPercent = ((float)curHp / maxHp) * 100;
    
    //GameScene::hpBar->setPercent(GameScene::myHp / 10);
    
    
    //hpBar->setPercent( (curHp/maxHp)*100 );
    
//    Value curHpNum((int)curHp);
//    Value maxHpNum((int)maxHp);
    
    std::string curHpNum(Convert2String(curHp));
    std::string maxHpNum(Convert2String(maxHp));
    Value hpString(curHpNum + "/" + maxHpNum);
    hp_num->setString(hpString.asString());
    //GameScene::mpBar->setPercent(GameScene::myHp / 10);
    
}

void GameScene::updateGhost(int currGhost, int maxGhost)
{
    //...
    float tempPercent = ((float)currGhost / maxGhost) * 100;
    if (tempPercent == ghostPercent) {
        return;
    }
    ghostProg->stopActionByTag(GHOST_BAR_CHANGE_TAG);
    if (abs(tempPercent-ghostPercent) <= 10) {
        ghostProg->setPercentage(tempPercent);
    }else{
        auto to1 = ProgressTo::create(0.1, tempPercent);
        to1->setTag(GHOST_BAR_CHANGE_TAG);
        ghostProg->runAction(to1);
    }
    ghostPercent = tempPercent;
//    ghostPercent = (currGhost / maxGhost) * 100;
}

void GameScene::updateMp(int currMp, int maxMp)
{
    if(mp_num == nullptr)
    {
        return;
    }

    if (gameMode != Game_Scene_State_Normal) {
        return;
    }
    iMpPercent = ((float)currMp / maxMp) * 100;
//    Value curHpNum((int)currMp);
//    Value maxHpNum((int)maxMp);
    std::string curMpNum(Convert2String(currMp));
    std::string maxMpNum(Convert2String(maxMp));
    Value hpString(curMpNum + "/" + maxMpNum);
    mp_num->setString(hpString.asString());
}

void GameScene::showMonster()
{
    FightActor *mon = actorLayer->getShowMonster();
    if(mon == nullptr)
    {
        monsterHpBar->setVisible(false);
        monsterHpBg->setVisible(false);
        monsterHpBGBar->setVisible(false);
        return;
    }
	else
	{
		showMonsterHp(mon);		 // 显示当前怪物的Hp
	}
}

void GameScene::showMonsterHp(FightActor * pMonster)
{
    /************************************************************************/
    // 显示当前怪物的Hp
    nMonsterPercent = pMonster->getBlackActor()->getHp() / pMonster->getBlackActor()->getMaxHp() * 100;
    // 1. 如果跟上一次的怪物是一样的
    if (&(*m_pCurrentMonster) == &(*pMonster))
    {
        if (nMonsterCurrentPer > nMonsterPercent)
        {
            --nMonsterCurrentPer;
            monsterHpBar->setPercent(nMonsterCurrentPer);
        } else if (nMonsterCurrentPer < nMonsterPercent) {
            nMonsterCurrentPer = nMonsterPercent;
            monsterHpBar->setPercent(nMonsterCurrentPer);
        }
        int nPercent = nMonsterBgPer / HP_MULTIPLE;
        if (nPercent > nMonsterPercent)
        {
            --nMonsterBgPer;
            monsterHpBGBar->setPercent(nPercent);
        }
    }
    // 2. 如果跟上一次的怪物不一样
    else
    {
        nMonsterCurrentPer = nMonsterPercent;
        nMonsterBgPer =  nMonsterPercent * HP_MULTIPLE;
        monsterHpBar->setPercent(nMonsterPercent);
        if (m_pCurrentMonster == NULL)
        {
            monsterHpBGBar->setPercent(100);
        }
        else
        {
            monsterHpBGBar->setPercent(nMonsterPercent);
        }
    }
    // 3. 显示界面上展示的怪物的血量
    m_pCurrentMonster = pMonster;
    monsterHpBar->setVisible(true);
    monsterHpBg->setVisible(true);
    monsterHpBGBar->setVisible(true);
}

/****************************************** dely *****************/
void GameScene::runOut(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type!=Widget::TouchEventType::ENDED)
        return;
    ;
    UI_ModalDialogue_Layer::DoModal("", Little::pops[2].name.c_str(), UI_ModalDialogue_Layer::DT_YES_NO, [=]()
                                    {
                                        log("exiting");
                                        battle->setFightResult(false);
                                        battle->NotifyServerResult();
                                        battle->setLoseDialogId(-1);
                                        battle->setWinDialogId(-1);
                                        resetGameMode(Game_Scene_State_Result);
                                    });
    
}
void GameScene::hidePop()
{
    tipBg->setVisible(false);
}
void GameScene::popTip(std::string content)
{
    tipBg->stopAllActions();
    tipLabel->setString(content);
    tipBg->setScale(0.1, 0.1);
    tipBg->setVisible(true);
    Vector<FiniteTimeAction *> actionVec;
    auto scale1 = ScaleTo::create(0.2, 1.2);
    auto scale2 = ScaleTo::create(0.2, 1.0);
    
    auto func = CallFunc::create(CC_CALLBACK_0(GameScene::hidePop, this));
    actionVec.pushBack(scale1);
    actionVec.pushBack(scale2);
    actionVec.pushBack(DelayTime::create(0.5));
    actionVec.pushBack(func);
    auto seq = Sequence::create(actionVec);
    seq->setTag(TIP_TIMEOUT_TAG);
    tipBg->runAction(seq);
    
}

bool GameScene::updateSendByType(int type, float delta)
{
    _currentTime += delta;
    
    if(hero->getDying() && !battle->getGameFail())
    {
        battle->setFightResult(false);
        resetGameMode(Game_Scene_State_Result);
        return true;
    }else if (battle->getWaveOver()){
        battle->setFightResult(true);
        resetGameMode(Game_Scene_State_Result);
        return true;
    }
    
    
    switch (type)
    {
        case suvival:
        {
            
            int minutes = ((int)_currentTime) / 60; int seconds = ((int)_currentTime) % 60;
            Value minStr(minutes);
            Value secStr(seconds);
            Value timeStr( minStr.asString() + ":" + secStr.asString() );
            _showTimeRed->setString( timeStr.asString() );
            
            if (((int)_currentTime) >= _limitTime)
            {
                battle->setFightResult(true);
                resetGameMode(Game_Scene_State_Result);
                return true;
            }
            
        }
            break;
        case count:
        {
            Value limitCount(_limitCount);
            Value greenStr(_currentCount);
            _showCountGreen->setString( greenStr.asString() );
            _showCountRed->setString(";" + limitCount.asString());
            
            if (_currentCount >= _limitCount)
            {
                battle->setFightResult(true);
                resetGameMode(Game_Scene_State_Result);
                return true;
            }
            
            int minutes = ((int)_currentTime) / 60; int seconds = ((int)_currentTime) % 60;
            
            Value minStr(minutes);
            Value secStr(seconds);
            Value timeStr(minStr.asString() + ":" + secStr.asString());
            _showTimeRed->setString(timeStr.asString());
            
            if (((int)_currentTime) >= _limitTime)
            {
                battle->setFightResult(false);
                resetGameMode(Game_Scene_State_Result);
                return true;
            }
           
        }
            break;
        case hp:
        {
            Value midStr(_limitHp);
            _showHpRed->setString(midStr.asString()+"<");
            
            if (nPercent < _limitHp)
            {
                battle->setFightResult(false);
                resetGameMode(Game_Scene_State_Result);
                return true;
            }
            
        }
            break;
        case boss:
        {
            
        }
            break;
        case guard:
        {
            
        }
            break;
        default:
            break;
    }
    return false;
}

void GameScene::showOrHideDialogue(bool showOrHide)
{
    _rootDialogue->setVisible(showOrHide);
    _rootDialogue->setContentById(1);
}

void GameScene::resetGameMode(int nextMode)
{
    exitGameMode(gameMode);
    gameMode = nextMode;
    enterGameMode(nextMode);
}

bool GameScene::enterGameMode(int next)
{
    switch (next) {
        case Game_Scene_State_Loading:
        {
            loadCount = 0;
            loadLayer = LoadScene::create();
            addChild(loadLayer, 1000);
            schedule(schedule_selector(GameScene::load), 0.1f);
        }
            break;
        case Game_Scene_State_Normal:
        {
        }
            break;
        case Game_Scene_State_Dialogue:
        {
            DialogManager::instance()->loadDialog();
            auto diaLayer = DialogLayer::create();
            addChild(diaLayer);
        }
            break;
        case Game_Scene_State_Result:
        {
            if (battle->getFightResult()) {
                if (battle->getWinDialogId() != -1 && firstPass) {
                    DialogManager::instance()->setDialogId(battle->getWinDialogId());
                    DialogManager::instance()->setGroupId(battle->getWinGroupId());
                    battle->setWinDialogId(-1);
                    battle->setWinGroupId(-1);
                    cacheGameMode = Game_Scene_State_Result;
                    resetGameMode(Game_Scene_State_Dialogue);
                    return false;
                }
            } else {
                if (battle->getLoseDialogId() != -1 && firstPass) {
                    DialogManager::instance()->setDialogId(battle->getLoseDialogId());
                    DialogManager::instance()->setGroupId(battle->getLoseGroupId());
                    battle->setLoseDialogId(-1);
                    battle->setLoseGroupId(-1);
                    cacheGameMode = Game_Scene_State_Result;
                    resetGameMode(Game_Scene_State_Dialogue);
                    return false;
                }
            }
            goalLayer->setVisible(false);
            resultLayer = ResultLayer::create();
            addChild(resultLayer);
            battle->NotifyServerResult();
            
        }
            break;
        default:
            break;
    }
    return true;
}
void GameScene::exitGameMode(int currMode)
{
    switch (currMode) {
        case Game_Scene_State_Loading:
        {
            loadCount = 0;
            removeChild(loadLayer);
            unschedule(schedule_selector(GameScene::load));
        }
            break;
        case Game_Scene_State_Normal:
        {
        }
            break;
        case Game_Scene_State_Dialogue:
        {
            
        }
            break;
        case Game_Scene_State_Result:
        {
            
        }
            break;
        default:
            break;
    }
}

