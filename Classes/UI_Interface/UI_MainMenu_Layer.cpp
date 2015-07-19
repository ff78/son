#include "UI_MainMenu_Layer.h"
//#include "cocos-ext.h"
//#include "UI_Role_Info_Layer.h"
#include "UI_Bag_Info_Layer.h"
//#include "UI_Instance_Layer.h"
//#include "UI_Skill_Info_Layer/UI_Skill_Info_Layer.h"
#include "UI_Skill_Info_Layer/SkillView.h"
#include "UI_Society_Layer/UI_Society_Layer.h"
#include "UI_Ranking_List_Layer/UI_Ranking_List_Layer.h"
//#include "UI_Settlement_Layer.h"
//#include "UI_HeartMethod_Layer.h"
#include "UI_Mission_Layer.h"
#include "UI_Arena_Layer.h"
#include "UI_Material_Fragment_Layer.h"
#include "UI_ChatBoard_Layer.h"
#include "UI_NpcDialogue_Layer.h"
#include "UI_MissionDialogue_Layer.h"
//#include "UI_HeartMethod_Combine_Layer.h"
//#include "UI_HeartMethod_Quality_Up_Layer.h"
#include "UI_ModalDialogue_Layer.h"
//#include "UI_Ranking_List_Layer.h"
#include "UI/Loading_Scene.h"
//#include "UI/NPC.h"
#include "Common/VisibleRect.h"
//#include "UI_Instance_Describe_Layer.h"
//#include "UI_Secondary_Instance_Layer.h"
#include "CocoStu_UI_Scene_Interface.h"
//#include "UI_Role_Quality_Up.h"
#include "UI_Daily_Mission.h"
//#include "UI_Item_Combine_Layer.h"
//#include "UI_Residual_Page_Layer.h"
#include "UI_New_Function_Open.h"
#include "UI_Fate_Layer.h"
#include "Joiner_Guidance.h"
//#include "UI_Sweep_Desc_Layer.h"
#include "UI_Shop_Center_Layer.h"
#include "UI_Trade_Layer.h"
//#include "UI_Activity_Layer.h"
//#include "UI_Activity_Six_Sect_Layer.h"
#include "UI_Interface/UI_PowerChangeTips.h"
#include "Item_System/Item_Logic_Cl.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Character.h"
#include "Character_System/Player_Config_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Player_Logic_Cl.h"
#include "Character_System/CommonNpc_Config_Mgr.h"

#include "Item_System/Item_Data.h"
#include "Item_System/Item_Mgr_Cl.h"
//#include "Skill_System/Skill/Skill_Logic.h"
//#include "Game_Utils.h"
#include "UI/Actor_Layer.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Common/GameDefine.h"
#include "Item_System/Item_Config_Mgr.h"
#include "quest_system/quest_data/quest_data_mgr.h"
#include "Play_System/Instance_Data_Mgr.h"
#include "Play_System/Formula_Function_Instance.h"
#include "Character_System/CommonNpc.h"
//#include "Fight_System/Fight_Config_Mgr.h"
#include "Login_Reward_System//Login_Reward_Mgr_Cl.h"
#include "Activity_System/Activity_Config_Mgr.h"

#include "Game_Interface/game_event_mgr.h"
#include "Game_Interface/Game_Element_Parse.h"
#include "Game_Interface/game_content_interface.h"
//#include "Game/Effect_Cfg_Data_Mgr.h"
//#include "Runtime.h"

#include "Junior_Guide_System/Junior_Guide_Config_Data.h"
#include "Junior_Guide_System/Junior_Guide_Mgr.h"
#include "Function_Open_System/Function_Open_Logic.h"
#include "ClientLogic/Utils/GameReader.h"

#include "UI_Exchange_Code_Layer.h"
#include "UI_Banks_Layer.h"
#include "UI_Login_Award_Layer.h"
#include "Common/GameResource.h"
#include "Common/VisibleRect.h"
#include <string>
#include "Common/Utils.h"

//#include "Dialogue_System/Dialogue_Common.h"
//#include "Dialogue_System/DialogueManager.h"

#include "../Title_System/Title_Client.h"
#include "../BossBattle_System/Boss_Client.h"
#include "../Fate_System/Fate_Client.h"
#include "../Arena_System/Arena_Client.h"

#include "../ClientLogic/GameScene/CityLayer.h"
#include "../ClientLogic/GameScene/ResultLayer.h"
#include "../ClientLogic/Actor/City_Player.h"
#include "../DataModule/Little.h"
#include "../Task_System/Task_Client.h"
#include "../Pet_System/Pet_Client.h"
#include "../God_System/God_Client.h"
#include "../Star_System/Star_Client.h"
#include "../EndlessTower_System/Endless_Client.h"
#include "../Secretary_System/Secretary_Client.h"
#include "../Reward_System/Reward_Client.h"
#include "../Sign_System/Sign_Client.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d;
using namespace UI;
using namespace Game_Data;
using namespace cocostudio;

UI_MainMenu_Layer* UI_MainMenu_Layer::m_instance_ = NULL;
std::map<int, std::map<std::string, GuideData>> UI_MainMenu_Layer::levelGuide;
int UI_MainMenu_Layer::oldLevel = 0;
bool UI_MainMenu_Layer::showMissionFinish= false;

UI_MainMenu_Layer::UI_MainMenu_Layer(void)
:m_pBagInfo(NULL),
//m_pRoleInfo(NULL),
m_pSkillInfo(NULL),
//m_pInstanceDes(NULL),
//m_pHeartMethod(NULL),
m_pEquipmentStrenthen(NULL),
m_pEquipmentStarUp(NULL),
m_pMission(NULL),
m_pArena(NULL),
m_pMaterialFragment(NULL),
m_pChatBoard(NULL),
m_pNpcDialogue(NULL),
m_pMissionDialogue(NULL),
//m_pHeartMethodCombineLayer(NULL),
//m_pHeartMethodQualityUpLayer(NULL),
//m_pSecondaryInstanceLayer(NULL),
m_pAllSetting(NULL),
m_bt_state(1),
//m_pRankingList(NULL),
m_pFateLayer(NULL),
//m_pRoleQualityUpLayer(NULL),
m_pDailyMissionLayer(NULL),
//m_pItemCombineLayer(NULL),
//m_pResidualPageLayer(NULL),
//m_pSkillDescLayer(NULL),
m_pFuncOpenLayer(NULL),
m_pBtnChatBoard(NULL),
m_pImgFindWay(NULL),
m_pLabFindWayFont(NULL),
m_pImgFontShadow(NULL),
m_lab_fighting_capacity(NULL),
juniorGuide(NULL),
m_pExchangeCodeLayer(NULL),
m_pBancksLayer(NULL),
m_nOpenActNum(0),
recordNum(0),
m_pLoginAwardLayer(NULL),
//m_pSweepDescLayer(NULL),
m_pShopCenterLayer(NULL),
m_trade_layer(NULL),
//m_activity_layer(NULL),
selBattleLayer(NULL)
//m_activity_six_sect_layer(NULL)
{
}

UI_MainMenu_Layer::~UI_MainMenu_Layer(void)
{
	m_instance_ = NULL;
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_UI_MIAN);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_UI_ITEM);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_INSTANCE_STAGE);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_STAGE);
#if 1//MISSION_DIALOG
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_MISSION_DIALOG);
#endif	
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_FRIEND_LIST);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_SKILL);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_ARENA);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_COUNT_DOWN_TIME);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_UI_NPCDIALOG);
//	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_UI_ROLE_QUALITY_UP);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_UI_COMPOUND_FRAGMENT);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_UI_FATE);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_FRIEND_DETAIL);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_UI_BANKS);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_UI_RANK);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_UI_LOGIN_AWARD);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_UI_INSTANCE_SWEEP);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_UI_GEM_INLAY);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_UI_OPERATE_GEM);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_UI_GEM_LEVEL_UP);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_UI_SHOP);
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_UI_DAILY_TASK);
	/*====================================   dely   ====================================*/
	remove_event_update_ui(Game_Logic::Game_Event::EVENT_TYPE_UI_CHAT);
	/*====================================   dely   ====================================*/
}

bool UI_MainMenu_Layer::init()
{
	if ( !cocos2d::Layer::init() )
		return false;
	_rootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("town/town.ExportJson");
	addChild(_rootWidget);

	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	auto player = (Game_Data::Player*)CHARACTER_MGR::instance()->get_character(role_id);
	_headImg = (ui::ImageView*)cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "headicon");
	int job = player->get_job();
	if (job >= 3)
		job = 3;
	Value pre("img/headIcon/job_");
	Value suff(job);
	Value path(pre.asString() + suff.asString() + ".png");
	_headImg->loadTexture(path.asString());

	_titleImg = dynamic_cast<cocos2d::ui::ImageView*>( Helper::seekWidgetByName(_rootWidget, "title_1") );
	_titleImg->setVisible(true);
	_titleImg->setTouchEnabled(true);
	_titleImg->addTouchEventListener( CC_CALLBACK_2(UI_MainMenu_Layer::onClickTitleCallback,this) );

    
//	_sports[sArena] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget, "Btn_Arena"));
//	_sports[sArena]->setVisible(true);
//	_sports[sArena]->setTouchEnabled(true);
//	_sports[sArena]->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::onClickArenaCallback, this));
//	_sports[sArena]->setPosition(Vec2(_sports[sArena]->getPosition().x - VisibleRect::cutLength(), _sports[sArena]->getPosition().y));
//	_sportsPosition[sArena] = _sports[sArena]->getPosition();

	//_sports[sParty] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget, "Btn_Party"));
	//_sports[sParty]->setVisible(true);
	//_sports[sParty]->setTouchEnabled(true);
	//_sports[sParty]->setPosition(Vec2(_sports[sParty]->getPosition().x - VisibleRect::cutLength(), _sports[sParty]->getPosition().y));
	//_sportsPosition[sParty] = _sports[sParty]->getPosition();
//	_sportsDestinationCbx = (cocos2d::ui::CheckBox*)Helper::seekWidgetByName(_rootWidget, "challenge");
//	_sportsDestinationCbx->setZOrder(1);
//	_sportsDestinationCbx->setPosition(Vec2(_sportsDestinationCbx->getPosition().x - VisibleRect::cutLength(), _sportsDestinationCbx->getPosition().y));
//	_sportsDestinationCbx->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::sportsToggle, this));
//	_sportsDestination = _sportsDestinationCbx->getPosition();
//	for (int i = 0; i < int(sNum); i++)
//		_sports[i]->setPosition(_sportsDestination);
	//	sportsToggle(_sportsDestinationCbx, Widget::TouchEventType::ENDED);
	//sportsToggle(_sportsDestinationCbx, Widget::TouchEventType::ENDED);
	// 无尽塔按钮
	_campaign[cEndless] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget, "Btn_Endless"));
	_campaign[cEndless]->setVisible(true);
	_campaign[cEndless]->setTouchEnabled(true);
	_campaign[cEndless]->setPosition(Vec2(_campaign[cEndless]->getPosition().x - VisibleRect::cutLength(), _campaign[cEndless]->getPosition().y));
	_campaign[cEndless]->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::btnEndlessTowerCallback, this));
	_campaignPosition[cEndless] = _campaign[cEndless]->getPosition();

	//_campaign[cRob] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget, "Btn_Rob"));
	//_campaign[cRob]->setVisible(true);
	//_campaign[cRob]->setTouchEnabled(true);
	//_campaign[cRob]->setPosition(Vec2(_campaign[cRob]->getPosition().x - VisibleRect::cutLength(), _campaign[cRob]->getPosition().y));
	//_campaign[cRob]->addTouchEventListener( this, toucheventselector(UI_MainMenu_Layer::onClickRobCallback) );
	//_campaignPosition[cRob] = _campaign[cRob]->getPosition();

//	_campaign[cBoss] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget, "Btn_Boss"));
//	_campaign[cBoss]->setVisible(true);
//	_campaign[cBoss]->setTouchEnabled(true);
//	_campaign[cBoss]->setPosition(Vec2(_campaign[cBoss]->getPosition().x - VisibleRect::cutLength(), _campaign[cBoss]->getPosition().y));
//	_campaign[cBoss]->addTouchEventListener( this, toucheventselector(UI_MainMenu_Layer::onClickBossCallback) );
//	_campaignPosition[cBoss] = _campaign[cBoss]->getPosition();

	_campaignDestinationCbx = (cocos2d::ui::CheckBox*)Helper::seekWidgetByName(_rootWidget, "Btn_Active");
	_campaignDestinationCbx->setZOrder(1);
	_campaignDestinationCbx->setPosition(Vec2(_campaignDestinationCbx->getPosition().x - VisibleRect::cutLength(), _campaignDestinationCbx->getPosition().y));
	_campaignDestinationCbx->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::campaignToggle, this) );
	_campaignDestination = _campaignDestinationCbx->getPosition();
	for (int i = 0; i < int(cNum); i++)
		_campaign[i]->setPosition(_campaignDestination);
	//campaignToggle(_campaignDestinationCbx, Widget::TouchEventType::ENDED);

	auto rank = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget, "ranking"));
	rank->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::buttonRankingList, this));
    log("before refresh main");
	auto assist = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget, "Img_Assist"));
	assist->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::buttonAssist, this));
    log("mid refresh main");


	auto reward = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget, "wanted"));
	reward->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::buttonReward, this));
	auto sign = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget, "Btn_Sign"));
	sign->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::buttonSign, this));

	_tryonceBtn = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget, "Button_249"));
	_tryonceBtn->setVisible(true);
	_tryonceBtn->setTouchEnabled(true);
	_tryonceBtn->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::buttonPathFinding, this));
    auto tryTxt = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(_rootWidget, "txt_quest"));
    tryTxt->setVisible(false);
//    auto missionSpt = Sprite::create("town/main_mission.png");
//    missionSpt->setAnchorPoint(Vec2(0, 0));
//    _tryonceBtn->addChild(missionSpt);
    log("after refresh main");

	//经验条初始化
//	m_pPercentVisible = ProgressTimer::create(cocos2d::Sprite::create(CURRENT_EXP_PIC));
//	if(m_pPercentVisible)
//	{
//		m_pPercentVisible->setType(kCCProgressTimerTypeBar);
//		m_pPercentVisible->setMidpoint(Vec2(0,0));
//		m_pPercentVisible->setBarChangeRate(Vec2(0, 1));
//		m_pPercentVisible->setPosition(Vec2(56+VisibleRect::cutLength(),658));
//		m_pPercentVisible->setVisible(false);
//		this->addChild(m_pPercentVisible);
//	}
	
	
//	m_pFunctionalBtn[FT_Pan] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget, "Button_204"));
//	m_ptBtnOrigenPos[FT_Pan] = m_pFunctionalBtn[FT_Pan]->getPosition();
//	m_pFunctionalBtn[FT_Pan]->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::onClickStarCallback, this));

	m_pFunctionalBtn[FT_God] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget, "Button_203"));
	m_ptBtnOrigenPos[FT_God] = m_pFunctionalBtn[FT_God]->getPosition();
	m_pFunctionalBtn[FT_God]->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::onClickRobCallback, this));

	m_pFunctionalBtn[FT_Pet] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget, "Btn_Pet"));
	m_ptBtnOrigenPos[FT_Pet] = m_pFunctionalBtn[FT_Pet]->getPosition();
	m_pFunctionalBtn[FT_Pet]->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::onClickPetCallback, this));

//	m_pFunctionalBtn[FT_Refine] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget, "Btn_Refine"));
//	m_ptBtnOrigenPos[FT_Refine] = m_pFunctionalBtn[FT_Refine]->getPosition();

//	m_pFunctionalBtn[FT_Fate] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget, "Btn_Fate"));
//	m_pFunctionalBtn[FT_Fate]->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::onClickFateCallback, this));
//	m_ptBtnOrigenPos[FT_Fate] = m_pFunctionalBtn[FT_Fate]->getPosition();

	m_pFunctionalBtn[FT_Property] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget, "Btn_Property"));
	m_pFunctionalBtn[FT_Property]->setPosition(Vec2(m_pFunctionalBtn[FT_Property]->getPosition().x - VisibleRect::cutLength(), m_pFunctionalBtn[FT_Property]->getPosition().y));
	m_pFunctionalBtn[FT_Property]->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::openPropertyCallback, this));
	m_ptBtnOrigenPos[FT_Property] = m_pFunctionalBtn[FT_Property]->getPosition();

	m_pFunctionalBtn[FT_Bag] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget,"bag"));
	m_pFunctionalBtn[FT_Bag]->setPosition(Vec2(m_pFunctionalBtn[FT_Bag]->getPosition().x-VisibleRect::cutLength(),m_pFunctionalBtn[FT_Bag]->getPosition().y));
	m_pFunctionalBtn[FT_Bag]->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::buttonBagInfo, this));
	m_ptBtnOrigenPos[FT_Bag] = m_pFunctionalBtn[FT_Bag]->getPosition();

	m_pFunctionalBtn[FT_Skill] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget,"skill"));
	m_pFunctionalBtn[FT_Skill]->setPosition(Vec2(m_pFunctionalBtn[FT_Skill]->getPosition().x-VisibleRect::cutLength(),m_pFunctionalBtn[FT_Skill]->getPosition().y));
	m_pFunctionalBtn[FT_Skill]->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::buttonSkillInfo, this));
	m_ptBtnOrigenPos[FT_Skill] = m_pFunctionalBtn[FT_Skill]->getPosition();

	//m_pFunctionalBtn[FT_Billboard] = (cocos2d::ui::Button*)Helper::seekWidgetByName(_rootWidget,"Btn_Task");
	//m_pFunctionalBtn[FT_Billboard]->setPosition(Vec2(m_pFunctionalBtn[FT_Billboard]->getPosition().x-VisibleRect::cutLength(),m_pFunctionalBtn[FT_Billboard]->getPosition().y));
	//m_pFunctionalBtn[FT_Billboard]->addTouchEventListener(this, toucheventselector(UI_MainMenu_Layer::onClickTaskCallback) );
	//m_ptBtnOrigenPos[FT_Billboard] = m_pFunctionalBtn[FT_Billboard]->getPosition();

//	m_pFunctionalBtn[FT_Relationship] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget,"friend"));
//	m_pFunctionalBtn[FT_Relationship]->setPosition(Vec2(m_pFunctionalBtn[FT_Relationship]->getPosition().x-VisibleRect::cutLength(),m_pFunctionalBtn[FT_Relationship]->getPosition().y));
//	m_pFunctionalBtn[FT_Relationship]->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::buttonSocialActivity, this));
//	m_ptBtnOrigenPos[FT_Relationship] = m_pFunctionalBtn[FT_Relationship]->getPosition();

	m_pFunctionalBtn[FT_SystemSetting] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget,"option"));
	m_pFunctionalBtn[FT_SystemSetting]->setPosition(Vec2(m_pFunctionalBtn[FT_SystemSetting]->getPosition().x-VisibleRect::cutLength(),m_pFunctionalBtn[FT_SystemSetting]->getPosition().y));
	m_pFunctionalBtn[FT_SystemSetting]->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::buttonSetting, this));
	m_ptBtnOrigenPos[FT_SystemSetting] = m_pFunctionalBtn[FT_SystemSetting]->getPosition();

	//商城按钮
	//m_pBtnGiftBag = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(_rootWidget,"shop"));
	//m_pBtnGiftBag->setPosition(Vec2(m_pBtnGiftBag->getPosition().x-VisibleRect::cutLength(),m_pBtnGiftBag->getPosition().y));

	//聊天
	m_pBtnChatBoard = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget,"chat"));
	m_pBtnChatBoard->setPosition(Vec2(m_pBtnChatBoard->getPosition().x+VisibleRect::cutLength(),m_pBtnChatBoard->getPosition().y));
	m_pBtnChatBoard->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::buttonChatBoard, this));
	m_pChatBoard = UI_ChatBoard_Layer::create();
	float rate=Director::getInstance()->getVisibleSize().width/Director::getInstance()->getWinSize().width;
	m_pChatBoard->setScale(rate);
	addChild(m_pChatBoard, 20, CHAT_LAYER);
	m_pChatBoard->setVisible(false);

//	_emailButton = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "mail"));
//	_emailButton->setTouchEnabled(true);
//	_emailButton->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::buttonSocialActivity, this) );

	m_pBtnToggle = (cocos2d::ui::CheckBox*)Helper::seekWidgetByName(_rootWidget,"group");
	m_pBtnToggle->setZOrder(1);
	m_pBtnToggle->setPosition(Vec2(m_pBtnToggle->getPosition().x-VisibleRect::cutLength(),m_pBtnToggle->getPosition().y));
	m_pBtnToggle->addTouchEventListener(CC_CALLBACK_2(UI_MainMenu_Layer::toggleFunctionalBtns, this));
	m_ptDestinyPos = m_pBtnToggle->getPosition();
	for (int i = 0; i < int(FT_Num); i++)
		m_pFunctionalBtn[i]->setPosition(Vec2(m_ptDestinyPos.x, m_ptDestinyPos.y));

	m_pImgFontShadow = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(_rootWidget, "Image_12"));
	m_pImgFontShadow->setVisible(false);

	m_lab_fighting_capacity = dynamic_cast<cocos2d::ui::TextAtlas*>(Helper::seekWidgetByName(_rootWidget,"battle_value_label_0_0"));
	m_lab_fighting_capacity->setString("0");

	joyStick = SneakyJoystick::create();
	joyStick->initWithRect(Rect::ZERO, false);
	joyStick->setAutoCenter(true);
	joyStick->setHasDeadzone(true);
	joyStick->setDeadRadius(10);

	auto btnBack = dynamic_cast<ImageView*>(Helper::seekWidgetByName(_rootWidget,"pad_back"));
	btnBack->setVisible(false);
	auto joySkin = SneakyJoystickSkinnedBase::create();
	joySkin->setBackgroundSprite(Sprite::create("img/joystick/pad_back.png"));
	joySkin->setThumbSprite(Sprite::create("img/joystick/pad.png"));

	joySkin->setPosition(btnBack->getPosition());
	joySkin->setJoystick(joyStick);
	btnBack = dynamic_cast<ImageView*>(Helper::seekWidgetByName(_rootWidget,"pad"));
	btnBack->setVisible(false);
	this->addChild(joySkin);
    
    //ff >>>
    if (levelGuide.size()==0) {
        oldLevel = player->get_character_level();
//        ui::TextAtlas* role_level = (ui::TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "level");
//        int nLevel = player->get_character_level();
//        role_level->setString(CCString::createWithFormat("%d", nLevel)->getCString());

        auto doc = GameReader::getDocInstance("GameData/scene_guide.json");
        if (doc->IsArray()){
            int size = doc->Size();
            for (int i = 0; i < size; i++) {
                const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
                int guideLevel = DICTOOL->getIntValue_json(dic, "level");
                if (guideLevel <= player->get_character_level()) {
                    continue;
                }
                GuideData guideData;
                guideData.level = guideLevel;
                guideData.itemName = DICTOOL->getStringValue_json(dic, "itemName");
                guideData.armStr = DICTOOL->getStringValue_json(dic, "arm");
                guideData.tableId = DICTOOL->getIntValue_json(dic, "ID");
                guideData.destItmeName = DICTOOL->getStringValue_json(dic, "destItemName");
                guideData.offX = DICTOOL->getFloatValue_json(dic, "offx");
                guideData.offY = DICTOOL->getFloatValue_json(dic, "offy");
                guideData.scaleX = DICTOOL->getFloatValue_json(dic, "scaleX");
                guideData.scaleY = DICTOOL->getFloatValue_json(dic, "scaleY");
                guideData.moveX = DICTOOL->getFloatValue_json(dic, "moveX");
                guideData.moveY = DICTOOL->getFloatValue_json(dic, "moveY");
                guideData.nextStepId = DICTOOL->getIntValue_json(dic, "next");
                guideData.tipStr = DICTOOL->getStringValue_json(dic, "tips");
                if (guideData.destItmeName != "null") {
                    guideData.operateType = OperateType::OP_DRAG;
                } else if (guideData.moveX * guideData.moveY != 0) {
                    guideData.operateType = OP_MOVE;
                } else {
                    guideData.operateType = OP_CLICK;
                }
                levelGuide[guideLevel][guideData.itemName] = guideData;
            }
        }
    }
    auto s = Director::getInstance()->getWinSize();
    tipBg = Sprite::create("img/battle/notblue.png");
    tipLabel = Label::createWithSystemFont("", "arial", 16);
    tipLabel->setPosition(tipBg->getContentSize().width/2, tipBg->getContentSize().height/2);
    tipLabel->setColor(Color3B::WHITE);
    tipBg->addChild(tipLabel);
    tipBg->setPosition(s.width/2, s.height/2);
    addChild(tipBg);
    tipBg->setVisible(false);
    //ff <<<

	reg_event_update_ui("update_main_ui_info", UI_MainMenu_Layer::update_main_ui_info, Game_Logic::Game_Event::EVENT_TYPE_UI_MIAN);
	reg_event_update_ui("update_item_ui_info", UI_MainMenu_Layer::update_item_ui_info, Game_Logic::Game_Event::EVENT_TYPE_UI_ITEM);
	reg_event_update_ui("update_skill", UI_MainMenu_Layer::update_skill, Game_Logic::Game_Event::EVENT_TYPE_INSTANCE_STAGE);
	reg_event_update_ui("update_arena", UI_MainMenu_Layer::update_arena, Game_Logic::Game_Event::EVENT_TYPE_STAGE);
	reg_event_update_ui("update_count_down_time", UI_MainMenu_Layer::update_count_down_time, Game_Logic::Game_Event::EVENT_TYPE_COUNT_DOWN_TIME);
	reg_event_update_ui("update_instance_stage", UI_MainMenu_Layer::update_instance_stage, Game_Logic::Game_Event::EVENT_TYPE_SKILL);
	reg_event_update_ui("update_stage", UI_MainMenu_Layer::update_stage, Game_Logic::Game_Event::EVENT_TYPE_ARENA);
#if 1//MISSION_DIALOG
	reg_event_update_ui("update_mission_dialog", UI_MainMenu_Layer::update_mission_dialog, Game_Logic::Game_Event::EVENT_TYPE_ARENA);
#endif
    reg_event_update_ui("update_stage_all", UI_MainMenu_Layer::update_stage_all, Game_Logic::Game_Event::EVENT_TYPE_STAGE_ALL);
    
	reg_event_update_ui("update_friend_list", UI_MainMenu_Layer::update_friend_list, Game_Logic::Game_Event::EVENT_TYPE_FRIEND_LIST);
	reg_event_update_ui("update_npcdialog", UI_MainMenu_Layer::update_npc_dialog, Game_Logic::Game_Event::EVENT_TYPE_UI_NPCDIALOG);
//	reg_event_update_ui("update_role_quality_up", UI_MainMenu_Layer::update_role_quality_up, Game_Logic::Game_Event::EVENT_TYPE_UI_ROLE_QUALITY_UP);
//	reg_event_update_ui("update_compound_fragment", UI_MainMenu_Layer::update_compound_fragment, Game_Logic::Game_Event::EVENT_TYPE_UI_COMPOUND_FRAGMENT);
	reg_event_update_ui("update_fate", UI_MainMenu_Layer::update_fate, Game_Logic::Game_Event::EVENT_TYPE_UI_FATE);
	reg_event_update_ui("update_selected_relation_spine", UI_MainMenu_Layer::update_friend_detail, Game_Logic::Game_Event::EVENT_TYPE_FRIEND_DETAIL);
	reg_event_update_ui("update_banks", UI_MainMenu_Layer::update_banks, Game_Logic::Game_Event::EVENT_TYPE_UI_BANKS);
	reg_event_update_ui("update_rank", UI_MainMenu_Layer::update_rank, Game_Logic::Game_Event::EVENT_TYPE_UI_RANK);
	reg_event_update_ui("update_login_award", UI_MainMenu_Layer::update_login_award, Game_Logic::Game_Event::EVENT_TYPE_UI_LOGIN_AWARD);
	reg_event_update_ui("update_instance_sweep", UI_MainMenu_Layer::update_instance_sweep, Game_Logic::Game_Event::EVENT_TYPE_UI_INSTANCE_SWEEP);
	reg_event_update_ui("update_gem_inlay", UI_MainMenu_Layer::update_gem_inlay, Game_Logic::Game_Event::EVENT_TYPE_UI_GEM_INLAY);
	reg_event_update_ui("update_operate_gem", UI_MainMenu_Layer::update_operate_gem, Game_Logic::Game_Event::EVENT_TYPE_UI_OPERATE_GEM);
	reg_event_update_ui("update_gem_level_up", UI_MainMenu_Layer::update_gem_level_up, Game_Logic::Game_Event::EVENT_TYPE_UI_GEM_LEVEL_UP);
	reg_event_update_ui("update_shop", UI_MainMenu_Layer::update_shop, Game_Logic::Game_Event::EVENT_TYPE_UI_SHOP);
	reg_event_update_ui("update_daily_task", UI_MainMenu_Layer::update_daily_task, Game_Logic::Game_Event::EVENT_TYPE_UI_DAILY_TASK);
	/************************ dely *********************/
	reg_event_update_ui("update_chat", UI_MainMenu_Layer::update_chat, Game_Logic::Game_Event::EVENT_TYPE_UI_CHAT);
	/************************ dely *********************/

    RefreshMainUIInfo();
	return true;

}

void UI_MainMenu_Layer::showGuide()
{
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if (!player) return;


	//任务接受 战斗操作 提交任务
	if (JUNIOR_GUIDE_STEP_1 == player->get_guide_id()
		|| JUNIOR_GUIDE_STEP_4 == player->get_guide_id()
		|| JUNIOR_GUIDE_STEP_5 == player->get_guide_id()		
		|| JUNIOR_GUIDE_STEP_12 == player->get_guide_id()
		)
	{
		Joiner_Guidance::receiveCurPosWidget(_tryonceBtn);
		Point point = _tryonceBtn->getWorldPosition();
		Joiner_Guidance::showGuide(point.x, point.y, _tryonceBtn);
		return;
	}
	if (0 == getToggleState())
	{
		if (BAG_GUIDE_STEP_0 == player->get_guide_id() 				//背包引导
			|| EQUIP_GUIDE_STEP_0 == player->get_guide_id()				//装备强化
			|| XF_ASSEMBLE_STEP_0 == player->get_guide_id() 			//心法拼装
			|| XF_EQUIP_GUIDE_STEP_0 == player->get_guide_id() 			//心法装备
			|| FRAGEMENT_COMB_STEP_0 == player->get_guide_id()			//碎片合成（背包）
			|| EQUIP_QUA_UP_STEP_0 == player->get_guide_id() 			//装备升品
			|| SKILL_LEVEL_UP_STEP_0 == player->get_guide_id()			//招式升级
			|| XF_COMBINE_STEP_0 == player->get_guide_id()				//心法合成
			|| ARENA_FIGHT_STEP_0 == player->get_guide_id()				//竞技场
			|| ROLE_QUA_UP_STEP_0 == player->get_guide_id()				//人物升品
			|| ARENA_GET_REWARD_STEP_0 == player->get_guide_id()		//领取每日奖励
			|| LIEUTENANT_FIGHT_STEP_0 == player->get_guide_id()		//副将出战
			|| USE_LIEU_FIGHT_STEP_0 == player->get_guide_id()			//使用副将战斗
			|| FATE_LEVEL_UP_STEP_0 == player->get_guide_id()			//升级天命
			|| XF_QUA_UP_STEP_0 == player->get_guide_id()				//心法升品
			)
		{
//			Joiner_Guidance::receiveCurPosWidget(m_pBtnToggle);
			return;
		}
	}
	else
	{
		Joiner_Guidance::hideGuide();
	}

}

void UI_MainMenu_Layer::addGoldCallback(Ref* pSender, Widget::TouchEventType type)
{
	CCLOG("addGoldCallback");
}

void UI_MainMenu_Layer::addStrengthCallback(Ref* pSender, Widget::TouchEventType type)
{

	int role_id;
	Game_Data::Player* player;
	const char* szString;
	const char* purchaseInfo;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		role_id = Account_Data_Mgr::instance()->get_current_role_id();
		player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
		if (!player)
		{
			return;
		}

		szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MODEL_PURCHASE_ENERGY_FONT);
		purchaseInfo = CCString::createWithFormat(szString, player->get_buy_energy_cost())->getCString();
		UI_ModalDialogue_Layer::DoModal("", purchaseInfo, UI_ModalDialogue_Layer::DT_YES_NO, []()
		{
			PLAYER_LOGIC::instance()->player_buy_energy();
		}
		);

		break;
	default:
		break;
	}
}

void UI_MainMenu_Layer::caculateOpenNumFunc()
{
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if (!player)
	{
		return;
	}

	m_nOpenActNum = 0;
	//if (player->get_function_open_id() >= ICON_BAG_TAG)
	//{
	//	m_nOpenActNum++;
	//}
	//if (player->get_function_open_id() >= ICON_EQUIP_TAG)
	//{
	//	m_nOpenActNum++;
	//}
	//if (player->get_function_open_id() >= ICON_XINFA_TAG)
	//{
	//	m_nOpenActNum++;
	//}
	//if (player->get_function_open_id() >= ICON_SKILL_TAG)
	//{
	//	m_nOpenActNum++;
	//}
	//if (player->get_function_open_id() >= ICON_ARENA_TAG)
	//{
	//	m_nOpenActNum++;
	//}
	CCLog("player->get_function_open_id = %d", player->get_function_open_id());
	CCLog("open Icon Num = %d", m_nOpenActNum);
}

void UI_MainMenu_Layer::openToggleGuide(float dt)
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return;

	if( BAG_GUIDE_STEP_0 == player->get_guide_id() || FRAGEMENT_COMB_STEP_0 == player->get_guide_id() )
	{
		player->change_guide_id(player->get_guide_id() + 1);
		Joiner_Guidance::receiveCurPosWidget(m_pFunctionalBtn[FT_Bag]);
	}
	#if 0
	else if (EQUIP_GUIDE_STEP_0 == player->get_guide_id()
		|| EQUIP_QUA_UP_STEP_0 == player->get_guide_id())
	{
		player->change_guide_id(player->get_guide_id() + 1);
		Joiner_Guidance::receiveCurPosWidget(m_pFunctionalBtn[FT_Equipment]);
	}
	#endif
	#if 0
	else if (XF_ASSEMBLE_STEP_0 == player->get_guide_id()
		|| XF_EQUIP_GUIDE_STEP_0 == player->get_guide_id()
		|| XF_COMBINE_STEP_0 == player->get_guide_id()
		|| XF_QUA_UP_STEP_0 == player->get_guide_id())
	{
		player->change_guide_id(player->get_guide_id() + 1);
		Joiner_Guidance::receiveCurPosWidget(m_pFunctionalBtn[FT_XinFa]);
	}
	#endif
	else if (SKILL_LEVEL_UP_STEP_0 == player->get_guide_id())
	{
		player->change_guide_id(player->get_guide_id() + 1);
		Joiner_Guidance::receiveCurPosWidget(m_pFunctionalBtn[FT_Skill]);
	}
	#if 0
	else if (ARENA_FIGHT_STEP_0 == player->get_guide_id()
		|| ARENA_GET_REWARD_STEP_0 == player->get_guide_id())
	{
		player->change_guide_id(player->get_guide_id() + 1);
		Joiner_Guidance::receiveCurPosWidget(m_pFunctionalBtn[FT_Competition]);
	}
	#endif
	#if 0
	else if (ROLE_QUA_UP_STEP_0 == player->get_guide_id()
		|| LIEUTENANT_FIGHT_STEP_0 == player->get_guide_id())
	{
		player->change_guide_id(player->get_guide_id() + 1);
		Joiner_Guidance::receiveCurPosWidget(m_pFunctionalBtn[FT_MainWarrior]);
	}
	#endif
	#if 0
	else if (FATE_LEVEL_UP_STEP_0 == player->get_guide_id())
	{
		player->change_guide_id(player->get_guide_id() + 1);
		Joiner_Guidance::receiveCurPosWidget(m_pFunctionalBtn[FT_Fate]);
	}
    #endif
	else if (USE_LIEU_FIGHT_STEP_0 == player->get_guide_id())
	{
		CCLog("use lieu fighting !!!");
	}
}

void UI_MainMenu_Layer::closeToggleGuide()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	if (BAG_GUIDE_STEP_1 == player->get_guide_id()
		|| EQUIP_GUIDE_STEP_1 == player->get_guide_id()
		|| XF_ASSEMBLE_STEP_1 == player->get_guide_id()
		|| XF_EQUIP_GUIDE_STEP_1 == player->get_guide_id()
		|| FRAGEMENT_COMB_STEP_1 == player->get_guide_id()
		|| EQUIP_QUA_UP_STEP_1 == player->get_guide_id()
		|| SKILL_LEVEL_UP_STEP_1 == player->get_guide_id()
		|| XF_COMBINE_STEP_1 == player->get_guide_id()
		|| ARENA_FIGHT_STEP_1 == player->get_guide_id()
		|| ROLE_QUA_UP_STEP_1 == player->get_guide_id()				//人物升品
		|| ARENA_GET_REWARD_STEP_1 == player->get_guide_id()		//领取每日奖励
		|| LIEUTENANT_FIGHT_STEP_1 == player->get_guide_id()		//副将出战
		|| USE_LIEU_FIGHT_STEP_1 == player->get_guide_id()			//使用副将战斗
		|| FATE_LEVEL_UP_STEP_1 == player->get_guide_id()			//升级天命
		|| XF_QUA_UP_STEP_1 == player->get_guide_id()				//心法升品
		)
	{
		// 		player->change_guide_id(player->get_guide_id()-1);
		// 		Joiner_Guidance::receiveCurPosWidget(m_pBtnToggle);
		Joiner_Guidance::hideGuide();
	}
}

void UI_MainMenu_Layer::toggleFunctionalBtns(Ref* pSender, Widget::TouchEventType type)
{
	std::vector<uint64> para;
	int player_id;
	Game_Data::Player* player;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
        dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
		player_id = Account_Data_Mgr::instance()->get_current_role_id();
		player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
		if (!player)
			return;

		for (int i = 0; i < int(FT_Num); i++)
		{
			m_pFunctionalBtn[i]->setVisible(true);
			m_pFunctionalBtn[i]->stopAllActions();
		}

		if (m_bt_state == 0)//打开toggle
		{
			m_bt_state = 1;
//			if (NULL == pSender)
//				m_pBtnToggle->setSelectedState(true);

			for (int i = 0; i < int(FT_Num); i++)
			{
				m_pFunctionalBtn[i]->setVisible(true);//caculateOpenNumFunc();
				m_pFunctionalBtn[i]->setTouchEnabled(true);//recordNum = m_nOpenActNum;
				m_pFunctionalBtn[i]->runAction(CCMoveTo::create(0.3f,Vec2(m_ptBtnOrigenPos[i].x,m_ptBtnOrigenPos[i].y)));
			}
			scheduleOnce(schedule_selector(UI_MainMenu_Layer::openToggleGuide), 0.15f);
		}
		else//关闭toggle
		{
			m_bt_state = 0;
//			if (NULL == pSender)
//				m_pBtnToggle->setSelectedState(false);

			for (int i = 0; i < int(FT_Num); i++)
				m_pFunctionalBtn[i]->runAction( CCSequence::create(CCMoveTo::create(0.3f, m_ptDestinyPos),CallFunc::create( CC_CALLBACK_0(UI_MainMenu_Layer::hideButtons,this,i) ), NULL) );
			
			//m_pImgBottomBack->setVisible(false);
			//m_pBtnChatBoard->setVisible(true);
			//m_pBtnChatBoard->setTouchEnabled(true);
			closeToggleGuide();

		}

	}
		break;
	default:
		break;
	}
}

void UI_MainMenu_Layer::campaignToggle(Ref* pSender, Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
		return;
    dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
	for (int i = 0; i < int(cNum); i++)
	{
		_campaign[i]->setVisible(true);
		_campaign[i]->stopAllActions();
	}

	if (_campaignState == 0)//打开toggle
	{
		_campaignState = 1;
//		if (NULL == pSender)
//			_campaignDestinationCbx->setSelectedState(true);

		for (int i = 0; i < int(cNum); i++)
		{
			_campaign[i]->setVisible(true);//caculateOpenNumFunc();
			_campaign[i]->setTouchEnabled(true);//recordNum = m_nOpenActNum;
			auto move = MoveTo::create(0.3f, _campaignPosition[i]);
			_campaign[i]->runAction( move );

		}

	}
	else
	{
		_campaignState = 0;
//		if (NULL == pSender)
//			_campaignDestinationCbx->setSelectedState(false);

		for (int i = 0; i < int(cNum); i++)
		{
			_campaign[i]->setVisible(true);
			auto move = MoveTo::create(0.3f, _campaignDestination);
			auto hide = CallFunc::create( CC_CALLBACK_0(UI_MainMenu_Layer::hideCampaign, this,i) );
			auto seq = Sequence::create(move, hide,nullptr);
			_campaign[i]->runAction( seq );
		}

	}

}

void UI_MainMenu_Layer::sportsToggle(Ref* pSender, Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
		return;

	for (int i = 0; i < int(sNum); i++)
	{
		_sports[i]->setVisible(true);
		_sports[i]->stopAllActions();
	}

	if (_sportsState == 0)//打开toggle
	{
		_sportsState = 1;
//		if (NULL == pSender)
//			_sportsDestinationCbx->setSelectedState(true);

		for (int i = 0; i < int(sNum); i++)
		{
			_sports[i]->setVisible(true);//caculateOpenNumFunc();
			_sports[i]->setTouchEnabled(true);//recordNum = m_nOpenActNum;
			auto move = MoveTo::create(0.3f, _sportsPosition[i]);
			_sports[i]->runAction(move);

		}

	}
	else
	{
		_sportsState = 0;
//		if (NULL == pSender)
//			_sportsDestinationCbx->setSelectedState(false);

		for (int i = 0; i < int(sNum); i++)
		{
			auto move = MoveTo::create(0.3f, _sportsDestination);
			auto hide = CallFunc::create( CC_CALLBACK_0(UI_MainMenu_Layer::hideSports,this,i) );
			auto seq = Sequence::create(move, hide,nullptr);
			_sports[i]->runAction(seq);

		}

	}

}

void UI_MainMenu_Layer::setToggleState(int state)
{
	m_bt_state = state;
	toggleFunctionalBtns(NULL, Widget::TouchEventType::ENDED);
	campaignToggle(NULL, Widget::TouchEventType::ENDED);
	sportsToggle(NULL, Widget::TouchEventType::ENDED);
}

int UI_MainMenu_Layer::getToggleState()
{
	CCLog("Toggle State = %d", m_bt_state);
	return m_bt_state;
}

void UI_MainMenu_Layer::showNpcDialogue(int nNpcID)
{
	if (!m_pNpcDialogue)
	{
		m_pNpcDialogue = UI_NpcDialogue_Layer::create();
		float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
		m_pNpcDialogue->setScale(rate);
		addChild(m_pNpcDialogue, 20, DIALOGUE_LAYER);
		m_pNpcDialogue->setVisible(true);
	}
	else
	{
		m_pNpcDialogue->setVisible(true);
	}
	m_pNpcDialogue->showDialogueWithNpcTypeID(nNpcID);
}

void UI_MainMenu_Layer::buttonMainRoleInfo(Ref* pSender, Widget::TouchEventType type)
{
//	int player_id;
//	Game_Data::Player* player;
//
//	switch (type)
//	{
//	case cocos2d::ui::Widget::TouchEventType::ENDED:
//		player_id = Account_Data_Mgr::instance()->get_current_role_id();
//		player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
//		if (!player)
//		{
//			return;
//		}
//		if (ROLE_QUA_UP_STEP_1 == player->get_guide_id()
//			|| LIEUTENANT_FIGHT_STEP_1 == player->get_guide_id()
//			)
//		{
//			player->change_guide_id(player->get_guide_id() + 1);
//		}
//
//
//		if (!m_pRoleInfo)
//		{
//			m_pRoleInfo = UI_Role_Info_Layer::create();
//			float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
//			m_pRoleInfo->setScale(rate);
//			this->addChild(m_pRoleInfo, 20, ROLE_LAYER);
//		}
//		m_pRoleInfo->setVisible(true);
//
//		//setToggleState(1);
//
//		break;
//	default:
//		break;
//	}
}

void UI_MainMenu_Layer::buttonChatBoard(Ref* pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
        dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
		m_pBtnChatBoard->stopAllActions();
		m_pBtnChatBoard->setVisible(true);
		m_pChatBoard->setVisible(true);

		Joiner_Guidance::hideGuide();
	}

		break;
	default:
		break;
	}
}

void UI_MainMenu_Layer::buttonBagInfo(Ref* pSender, Widget::TouchEventType type)
{
	int player_id;
	Game_Data::Player* player;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
            dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
		player_id = Account_Data_Mgr::instance()->get_current_role_id();
		player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
		if (!player)
		{
			return;
		}
		if (BAG_GUIDE_STEP_1 == player->get_guide_id()
			|| FRAGEMENT_COMB_STEP_1 == player->get_guide_id()
			)
		{
			player->change_guide_id(player->get_guide_id() + 1);
		}

		if (!m_pBagInfo)
		{
			m_pBagInfo = UI_Bag_Info_Layer::create();
			float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
			m_pBagInfo->setScale(rate);
			this->addChild(m_pBagInfo, 20, BAG_LAYER);
		}
		if (player)
		{
			UI_Bag_Info_Layer::sIsProperty = false;
			UI_Bag_Info_Layer::sName = player->get_character_name();
			UI_Bag_Info_Layer::sPower = player->get_fighting_capacity();
            UI_Bag_Info_Layer::sTili = player->get_energy();
			//Exp = player->get_character
			UI_Bag_Info_Layer::sHP = player->get_character_cur_hp();
			UI_Bag_Info_Layer::sAtk = player->get_character_attack();
			UI_Bag_Info_Layer::sGuard = player->get_character_define();
			UI_Bag_Info_Layer::sMP = player->get_character_cur_mp();
			UI_Bag_Info_Layer::sLevel = player->get_character_level();
			UI_Bag_Info_Layer::sJob = player->get_job();
		}
		m_pBagInfo->initData();

		m_pBagInfo->setVisible(true);

//		setToggleState(1);

		break;
	default:
		break;
	}
}

void UI_MainMenu_Layer::quest_show_bag(int item_base_id)
{
	if (!m_pBagInfo)
	{
		m_pBagInfo = UI_Bag_Info_Layer::create();
		float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
		m_pBagInfo->setScale(rate);
		this->addChild(m_pBagInfo, 20, BAG_LAYER);
		//return;
	}

	m_pBagInfo->setVisible(true);
}

void UI_MainMenu_Layer::quest_show_skill(int skill_base_id)
{
	//if (!m_pSkillInfo)
	//{
	//	m_pSkillInfo = UI_Skill_Layer::create();
	//	float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
	//	m_pSkillInfo->setScale(rate);
	//	this->addChild(m_pSkillInfo, 20, BAG_LAYER);
	//	m_pSkillInfo->setVisible(true);
	//	return;
	//}

	//m_pSkillInfo->setVisible(true);
}

void UI_MainMenu_Layer::quest_show_equipment(int item_base_id)
{
	//if (!m_pEquipment)
	//{
	//	m_pEquipment = UI_Equipment_Layer::create();
	//	float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
	//	m_pEquipment->setScale(rate);
	//	this->addChild(m_pEquipment, 20, BAG_LAYER);
	//	m_pEquipment->setVisible(true);
	//	return;
	//}

	//m_pEquipment->setVisible(true);
}

void UI_MainMenu_Layer::quest_show_book_bag(int item_base_id)
{
//	if (!m_pHeartMethod)
//	{
//		m_pHeartMethod = UI_HeartMethod_Layer::create();
//		float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
//		m_pHeartMethod->setScale(rate);
//		this->addChild(m_pHeartMethod, 20, BAG_LAYER);
//		m_pHeartMethod->setVisible(true);
//		return;
//	}
//
//	m_pHeartMethod->setVisible(true);
}

void UI_MainMenu_Layer::show_arena()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	//if (player->get_character_level() < PLAYER_OFFLINE_FIGHT_LEVEL)
	//{
	//	const char* string = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_OPEN_LEVEL);
	//	string = CCString::createWithFormat(string,PLAYER_OFFLINE_FIGHT_LEVEL)->getCString();
	//	Game_Utils::instance()->show_alert(string);
	//	return;
	//}

	if (!m_pArena)
	{
		m_pArena = UI_Arena_Layer::create();
		float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
		m_pArena->setScale(rate);
		this->addChild(m_pArena, 20, ARENA_LAYER);
	}

	if (ARENA_FIGHT_STEP_1 == player->get_guide_id())
	{
		player->change_guide_id(player->get_guide_id() + 1);
	}

	m_pArena->setVisible(true);
	//setToggleState(1);
}

void UI_MainMenu_Layer::buttonSkillInfo(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;

    dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
	SkillView * pLayer = SkillView::create();
	pLayer->setTag(998);
	addChild(pLayer);

	/*
	int role_id;
	Player* player;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		role_id = Account_Data_Mgr::instance()->get_current_role_id();
		player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
		if (!player)
		{
			return;
		}
		CCLog("buttonSkillInfo player->get_guide_id = %d", player->get_guide_id());
		if (SKILL_LEVEL_UP_STEP_1 == player->get_guide_id())
		{
			player->change_guide_id(player->get_guide_id() + 1);
			Joiner_Guidance::showGuide();
		}

		if (!m_pSkillInfo)
		{
			m_pSkillInfo = UI_Skill_Layer::create();
			float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
			m_pSkillInfo->setScale(rate);
			this->addChild(m_pSkillInfo, 20, SKILL_LAYER);
		}
		m_pSkillInfo->setVisible(true);
		//setToggleState(1);


		

		break;
	default:
		break;
	}*/
}

void UI_MainMenu_Layer::buttonEquipment(Ref* pSender, Widget::TouchEventType type)
{
	int role_id;
	Player* player;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		role_id = Account_Data_Mgr::instance()->get_current_role_id();
		player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
		if (!player) return;
		if (EQUIP_GUIDE_STEP_1 == player->get_guide_id()
			|| EQUIP_QUA_UP_STEP_1 == player->get_guide_id())
		{
			player->change_guide_id(player->get_guide_id() + 1);
		}

		//if (!m_pEquipment)
		//{
		//	m_pEquipment = UI_Equipment_Layer::create();
		//	float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
		//	m_pEquipment->setScale(rate);
		//	this->addChild(m_pEquipment, 20, EQUIPMENT_LAYER);
		//}
		//m_pEquipment->setVisible(true);

		//setToggleState(1);

		break;
	default:
		break;
	}

}

void UI_MainMenu_Layer::buttonSetting(Ref* pSender, Widget::TouchEventType type)
{
	// 以下代码为测试代码
	// 潘杰（01.26）
	if (type != Widget::TouchEventType::ENDED)
		return;
    dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
	std::string pop( Little::pops[1].name );
	UI_ModalDialogue_Layer::DoModal("", pop.c_str(), UI_ModalDialogue_Layer::DT_YES_NO, [=]()
	{
		log("exiting");
		Director::getInstance()->end();
	});
	return;
	// 以上代码为测试代码
	// 潘杰（01.26）

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
													   /*
													   const char* exitInfo = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SURE_TO_EXIT_GAME);
													   UI_ModalDialogue_Layer::DoModal("", exitInfo, UI_ModalDialogue_Layer::DT_YES_NO, [&](){ this->btnCallBackExit(); } );
													   */
													   //setToggleState(1);

													   if (!m_pAllSetting)
													   {
														   m_pAllSetting = UI_AllSetting_Layer::create();
														   float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
														   m_pAllSetting->setScale(rate);
														   this->addChild(m_pAllSetting, 20, ALL_SETTING);
													   }
													   m_pAllSetting->setVisible(true);



													   //Joiner_Guidance::hideGuide();
	}
		break;
	default:
		break;
	}
}

void UI_MainMenu_Layer::buttonRankingList(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;

    dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
    
	UI_Ranking_List_Layer * pLayer = UI_Ranking_List_Layer::create();
	addChild(pLayer);

	//				float rate;
	//				switch (type)
	//				{
	//				case cocos2d::ui::Widget::TouchEventType::ENDED:
	//				{
	//					//setToggleState(1);
	//				
	//					//if (!m_pRankingList)
	//					//{
	//					//	m_pRankingList = UI_Ranking_List_Layer::create();
	//					//	rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
	//					//	m_pRankingList->setScale(rate);
	//					//	this->addChild(m_pRankingList, 20, RANK_LIST_LAYER);
	//					//}
	//					//m_pRankingList->setVisible(true);
	//					vector<uint64> para;
	//				
	//					Game_Logic::Game_Content_Interface::instance()->exec_interface("sendjoinguild", para);
	//				}
	//					break;
	//				default:
	//					break;
	//				}

}

void UI_MainMenu_Layer::buttonAssist(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
    dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
	SECRETARY_VIEW * assist = SECRETARY_VIEW::create();
	addChild(assist);
}

void UI_MainMenu_Layer::buttonReward(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;

    dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
	REWARD_VIEW * reward = REWARD_VIEW::create();
	addChild(reward);
}

void UI_MainMenu_Layer::buttonSign(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;

    dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
	SIGN_VIEW * reward = SIGN_VIEW::create();
	addChild(reward);
}


void UI_MainMenu_Layer::buttonSocialActivity(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 点击社交按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;
	UI_Society_Layer * pLayer = UI_Society_Layer::create();
	addChild(pLayer);

}

void UI_MainMenu_Layer::buttonCompetition(Ref* pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		show_arena();

		break;
	default:
		break;
	}
}

void UI_MainMenu_Layer::buttonFragment(Ref* pSender, Widget::TouchEventType type)
{
	if (!m_pMaterialFragment)
	{
		m_pMaterialFragment = UI_Material_Fragment_Layer::create();
		float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
		m_pMaterialFragment->setScale(rate);
		this->addChild(m_pMaterialFragment, 20, FRAGMENT_LAYER);
	}
	m_pMaterialFragment->setVisible(true);

	//setToggleState(1);
	//Joiner_Guidance::hideGuide();
}

void UI_MainMenu_Layer::buttonFate(Ref* pSender, Widget::TouchEventType type)
{
    auto dest = Helper::seekWidgetByName(_rootWidget, "Btn_Fate");
    dest->removeChildByTag(1000);
	int player_id;
	Game_Data::Player* player;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		player_id = Account_Data_Mgr::instance()->get_current_role_id();
		player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
		if (!player)
		{
			return;
		}
		if (FATE_LEVEL_UP_STEP_1 == player->get_guide_id())
		{
			player->change_guide_id(player->get_guide_id() + 1);
		}

		if (!m_pFateLayer)
		{
			m_pFateLayer = UI_Fate_Layer::create();
			float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
			m_pFateLayer->setScale(rate);
			this->addChild(m_pFateLayer, 20, FATE_LAYER);
		}
		m_pFateLayer->setVisible(true);

		//setToggleState(1);
		//Joiner_Guidance::hideGuide();

		break;
	default:
		break;
	}
}

void UI_MainMenu_Layer::HideAllWindow()
{
	if (m_pBagInfo)
	{
		m_pBagInfo->setVisible(false);
	}
	//if (m_pSkillInfo)
	//{
	//	m_pSkillInfo->setVisible(false);
	//}
//	if (m_pRoleInfo)
//	{
//		m_pRoleInfo->setVisible(false);
//	}
//	if (m_pHeartMethod)
//	{
//		m_pHeartMethod->setVisible(false);
//	}

}

//区域选择界面
void UI_MainMenu_Layer::buttonAreaInstance()
{
	//////////////////////////////////////////////////////////////////////////
	/*std::vector<uint64> para;
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_item_container", para);

	para.push_back(Account_Data_Mgr::instance()->get_current_role_id());
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_skill", para);*/
	//////////////////////////////////////////////////////////////////////////

	HideAllWindow();

//	if (!m_pAreaInstance)
//	{
//		m_pAreaInstance = UI_Instance_Layer::create();
//		float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
//		m_pAreaInstance->setScale(rate);
//		this->addChild(m_pAreaInstance, 20, INSTANCE_LAYER);
//	}
//	m_pAreaInstance->setVisible(true);
}

UI_MainMenu_Layer* UI_MainMenu_Layer::get_instance()
{
	if (!m_instance_)
	{
		m_instance_ = UI_MainMenu_Layer::create();
	}
	return m_instance_;
}

void UI_MainMenu_Layer::buttonInstanceDes(int instance_id)
{
	//if (!m_pInstanceDes)
	//{
	//	m_pInstanceDes = UI_Instance_Describe_Layer::create();
	//	float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
	//	m_pInstanceDes->setScale(rate);
	//	this->addChild(m_pInstanceDes, 20, SETTLEMENT_LAYER);
	//}
	//m_pInstanceDes->initInstanceDescribe(instance_id);
	//m_pInstanceDes->setVisible(true);
}

bool UI_MainMenu_Layer::update_main_ui_info(const Game_Logic::Game_Event& gm_evt)
{
	if (m_instance_)
	{
		m_instance_->RefreshMainUIInfo();
		m_instance_->refreshFindWay();
	}

	return true;
}

bool UI_MainMenu_Layer::update_item_ui_info(const Game_Logic::Game_Event& gm_evt)
{
	if (get_instance()->m_pBagInfo)
	{
		get_instance()->m_pBagInfo->update();
	}

	//if (get_instance()->m_pRoleInfo)
	//{
	//	get_instance()->m_pRoleInfo->update();
	//}

	//if (get_instance()->m_pHeartMethod)
	//{
	//	get_instance()->m_pHeartMethod->update();
	//}

	//if (get_instance()->m_pEquipment)
	//{
	//	get_instance()->m_pEquipment->update();
	//}
	/***************************** dely *****************************/
	if (get_instance()->m_pEquipmentStrenthen)
	{
		get_instance()->m_pEquipmentStrenthen->update();
	}
	if (get_instance()->m_pEquipmentStarUp)
	{
		get_instance()->m_pEquipmentStarUp->update();
	}
	/***************************** dely *****************************/

	//if (get_instance()->m_pEquipmentQualityUpLayer)
	//{
	//	get_instance()->m_pEquipmentQualityUpLayer->update();
	//}

	//if (get_instance()->m_pHeartMethodCombineLayer)
	//{
	//	get_instance()->m_pHeartMethodCombineLayer->update();
	//}

	//if (get_instance()->m_pHeartMethodQualityUpLayer)
	//{
	//	get_instance()->m_pHeartMethodQualityUpLayer->update();
	//}

	return true;
}

bool UI_MainMenu_Layer::update_arena(const Game_Logic::Game_Event& gm_evt)
{
	if (get_instance()->m_pArena)
	{
		get_instance()->m_pArena->update();
	}

	return true;
}

bool UI_MainMenu_Layer::update_count_down_time(const Game_Logic::Game_Event& gm_evt)
{
	if (get_instance()->m_pArena)
	{
		vector<uint64> para;
		gm_evt.get_para(para);
		if (para.size() > 0)
		{
			get_instance()->m_pArena->update_time((int)para[0]);
		}
	}

	if (get_instance()->m_pFateLayer)
	{
		get_instance()->m_pFateLayer->update_time();
	}

	return true;
}

bool UI_MainMenu_Layer::update_skill(const Game_Logic::Game_Event& gm_evt)
{
	SkillView * pLayer = dynamic_cast<SkillView*>(get_instance()->getChildByTag(998));
	if (pLayer == NULL)
		return false;
	
	//pLayer->CurrentShowSkillUpgradeSuccese();
	return true;
}

bool UI_MainMenu_Layer::update_stage_all(const Game_Logic::Game_Event& gm_evt)
{
	get_instance()->selBattleLayer = SelectBattleLayer::create();
	get_instance()->selBattleLayer->updateData();
	get_instance()->addChild(get_instance()->selBattleLayer);
	return true;
}

bool UI_MainMenu_Layer::update_instance_stage(const Game_Logic::Game_Event& gm_evt)
{
//	get_instance()->m_pSecondaryInstanceLayer->update();
	return true;
}
#if 1//MISSION_DIALOG
bool UI_MainMenu_Layer::update_mission_dialog(const Game_Logic::Game_Event& gm_evt)
{
	if (get_instance()->m_pMissionDialogue)
	{
		get_instance()->m_pMissionDialogue->setVisible(true);	
		get_instance()->m_pMissionDialogue->update(gm_evt.get_event_active_id());
	}
	else
	{
		get_instance()->m_pMissionDialogue = UI_MissionDialogue_Layer::create();
		get_instance()->addChild(get_instance()->m_pMissionDialogue, 20, MISSION_DIALOGUE_LAYER);
		get_instance()->m_pMissionDialogue->setVisible(true);
		get_instance()->m_pMissionDialogue->update(gm_evt.get_event_active_id());
	}
	return true;
}
#endif
bool UI_MainMenu_Layer::update_stage(const Game_Logic::Game_Event& gm_evt)
{
	//get_instance()->m_pAreaInstance->update();
	return true;
}

bool UI_MainMenu_Layer::update_friend_list(const Game_Logic::Game_Event& gm_evt)
{
	return true;
}

bool UI_MainMenu_Layer::update_npc_dialog(const Game_Logic::Game_Event& gm_evt)
{
	if (get_instance()->m_pNpcDialogue)
	{
		get_instance()->m_pNpcDialogue->updateDetail();
	}
	return true;
}

//bool UI_MainMenu_Layer::update_role_quality_up(const Game_Logic::Game_Event& gm_evt)
//{
//	if (get_instance()->m_pRoleQualityUpLayer)
//	{
//		get_instance()->m_pRoleQualityUpLayer->update_role();
//		get_instance()->m_pRoleQualityUpLayer->update();
//	}
//	return true;
//}

//bool UI_MainMenu_Layer::update_compound_fragment(const Game_Logic::Game_Event& gm_evt)
//{
//	if (get_instance()->m_pMaterialFragment)
//	{
//		vector<uint64> para;
//		gm_evt.get_para(para);
//		if (para.size() > 0)
//		{
//			get_instance()->m_pMaterialFragment->update((int)para[0]);
//		}
//	}
//
//	if (get_instance()->m_pResidualPageLayer)
//	{
//		vector<uint64> para;
//		gm_evt.get_para(para);
//		if (para.size() > 0)
//		{
//			get_instance()->m_pResidualPageLayer->update((int)para[0]);
//		}
//	}
//
//	return true;
//}

bool UI_MainMenu_Layer::update_fate(const Game_Logic::Game_Event& gm_evt)
{
	if (get_instance()->m_pFateLayer)
	{
		get_instance()->m_pFateLayer->update();
	}

	return true;
}

void UI_MainMenu_Layer::buttonPathFinding(Ref* pSender, Widget::TouchEventType type)
{
	std::vector<uint64> para;
	int player_id;
	Game_Data::Player* player;
	quest_data::quest_data_vec_t vec_accepted_quest;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		//setToggleState(1);
		//////////////////////////////////////////////////////////////////////////

		/*Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_item_container", para);

		para.push_back(Account_Data_Mgr::instance()->get_current_role_id());
		Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_skill", para);*/
		//////////////////////////////////////////////////////////////////////////

        dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
		player_id = Account_Data_Mgr::instance()->get_current_role_id();
		player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
		if (!player)
		{
			return;
		}

		if (JUNIOR_GUIDE_STEP_1 == player->get_guide_id()
			|| JUNIOR_GUIDE_STEP_4 == player->get_guide_id()
			|| JUNIOR_GUIDE_STEP_12 == player->get_guide_id()
			)
		{
			Joiner_Guidance::hideGuide();
			player->change_guide_id(player->get_guide_id() + 1);
		}

		vec_accepted_quest = quest_data_mgr::instance()->get_quest_data_list(player_id);
		if (vec_accepted_quest.size() == 0)
		{
			move_to_accept_quest_npc();
		}
		else
		{
			move_to_quest_npc();
		}
		break;
	default:
		break;
	}

}

void UI_MainMenu_Layer::buttonHeartMethod(Ref* pSender, Widget::TouchEventType type)
{
//	int role_id;
//	Player* player;
//	switch (type)
//	{
//	case cocos2d::ui::Widget::TouchEventType::ENDED:
//		role_id = Account_Data_Mgr::instance()->get_current_role_id();
//		player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
//		if (!player) return;
//		if (XF_EQUIP_GUIDE_STEP_1 == player->get_guide_id()
//			|| XF_COMBINE_STEP_1 == player->get_guide_id()
//			|| XF_ASSEMBLE_STEP_1 == player->get_guide_id()
//			|| XF_QUA_UP_STEP_1 == player->get_guide_id()
//			)
//		{
//			player->change_guide_id(player->get_guide_id() + 1);
//		}
//
//		if (!m_pHeartMethod)
//		{
//			m_pHeartMethod = UI_HeartMethod_Layer::create();
//			float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
//			m_pHeartMethod->setScale(rate);
//			this->addChild(m_pHeartMethod, 20, BAG_LAYER);
//		}
//		m_pHeartMethod->setVisible(true);
//
//		//setToggleState(1);
//
//		break;
//	default:
//		break;
//	}
}

void UI_MainMenu_Layer::buttonMission(Ref* pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		//setToggleState(1);

		if (!m_pMission)
		{
			m_pMission = UI_Mission_Layer::create();
			float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
			m_pMission->setScale(rate);
			this->addChild(m_pMission, 20, MISSION_LAYER);
		}
		m_pMission->setVisible(true);

		//Joiner_Guidance::hideGuide();

		break;
	default:
		break;
	}
}
void UI_MainMenu_Layer::hidePop()
{
    tipBg->setVisible(false);
}
void UI_MainMenu_Layer::popTip(std::string content)
{
    tipBg->stopAllActions();
    tipLabel->setString(content);
    tipBg->setScale(0.1, 0.1);
    tipBg->setVisible(true);
    Vector<FiniteTimeAction *> actionVec;
    auto scale1 = ScaleTo::create(0.2, 1.2);
    auto scale2 = ScaleTo::create(0.2, 1.0);
    
    auto func = CallFunc::create(CC_CALLBACK_0(UI_MainMenu_Layer::hidePop, this));
    actionVec.pushBack(scale1);
    actionVec.pushBack(scale2);
    actionVec.pushBack(DelayTime::create(0.5));
    actionVec.pushBack(func);
    auto seq = Sequence::create(actionVec);
    seq->setTag(TIP_TIMEOUT_TAG);
    tipBg->runAction(seq);
    
}


void UI_MainMenu_Layer::RefreshMainUIInfo()
{
	/************************************************************************/
	// 刷新主界面上UI信息
	// 1. 获取当前玩家
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if (player == NULL)
		return;

	//for (int index = (int)ICON_NONE; index < (int)ICON_SUM; ++index)
	//{
	//	if (index <= player->get_function_open_id())
	//	{
	//		arr[index] = true;
	//	}
	//	else
	//	{
	//		arr[index] = false;
	//	}
	//}

	// 2. 设置人物头像
	//const char* picRoleHead = ITEM_CONFIG_MGR::instance()->get_icon_path(player->get_face_mode_id());
	//ui::ImageView* img_head_photo = dynamic_cast<ui::ImageView*>(getChildByName("headicon"));

	// 3. 设置主界面角色等级属性
	ui::TextAtlas* role_level = (ui::TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "level");
	role_level->setColor(Color3B(255, 255, 255));
	int nLevel = player->get_character_level();
//    role_level->getString()
//    int rLevel = atoi(role_level->getString().c_str());
    if (oldLevel != nLevel) {
        log("up level from %d to %d", oldLevel, nLevel);
        oldLevel = nLevel;
        std::string tip("null");
        for(auto obj : levelGuide[nLevel]){
            
//            for (auto data : obj) {
//                
//            }
            std::string path("armature/");
            std::string jsonPath = path + obj.second.armStr+".ExportJson";
            ArmatureDataManager::getInstance()->addArmatureFileInfo(jsonPath);
            auto tipArmature = Armature::create(obj.second.armStr);
//            tipArmature->setAnchorPoint(Vec2(0, 0));
            tipArmature->setScaleX(obj.second.scaleX);
            tipArmature->setScaleY(obj.second.scaleY);
            
            tipArmature->getAnimation()->playWithIndex(0);
            auto dest = Helper::seekWidgetByName(_rootWidget, obj.second.itemName);
            tipArmature->setPosition(Vec2(dest->getContentSize().width/2+obj.second.offX, dest->getContentSize().height/2+obj.second.offY));
            dest->addChild(tipArmature, 0, 1000);
            if (obj.second.tipStr != "null") {
                tip = obj.second.tipStr;
            }
        }
        if (tip!="null") {
            popTip(tip);
        }
        
        levelGuide[nLevel].clear();
        levelGuide.erase(nLevel);
        
        Game_Utils::instance()->get_actor_layer()->player->levelup();
    }
	role_level->setString(CCString::createWithFormat("%d", nLevel)->getCString());
    
    // 4. 设置金币数量
	ui::TextAtlas* gold_coin_num = (ui::TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "lab_gold_coin_num");
	int gold = player->get_gold();
	gold_coin_num->setString(CCString::createWithFormat("%d", gold)->getCString());

	// 5. 设置元宝数量
	ui::TextAtlas* role_gold_ingot_num = (ui::TextAtlas*)(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "lab_gold_ingot_num"));
	int token = player->get_token();
	role_gold_ingot_num->setString(CCString::createWithFormat("%d", token)->getCString());

	// 6. 战力值增加的话，弹出提示
	int nPower	= player->get_fighting_capacity();
	ui::TextAtlas* pPowerText = (ui::TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "battle_value_label_0_0");
	pPowerText->setColor(ccc3(255, 255, 255));
	pPowerText->setString(CCString::createWithFormat("%d", nPower)->getCString());
    
    int tiliVal = player->get_energy();
    auto tili = dynamic_cast<ui::TextAtlas*>(Helper::seekWidgetByName(_rootWidget, "tilishuzhi"));
    tili->setString(CCString::createWithFormat("%d", tiliVal)->getCString());
    
    int vipVal = player->get_vip_lv();
    auto vip = dynamic_cast<ui::TextAtlas*>(Helper::seekWidgetByName(_rootWidget, "vipshuzi"));
    vip->setString(CCString::createWithFormat("%d", vipVal)->getCString());
}

void UI_MainMenu_Layer::visibleRoleQualityUp()
{
//	if (!m_pRoleQualityUpLayer)
//	{
//		m_pRoleQualityUpLayer = UI_Role_Quality_Up::create();
//		float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
//		m_pRoleQualityUpLayer->setScale(rate);
//		this->addChild(m_pRoleQualityUpLayer, 20);
//	}
//	m_pRoleQualityUpLayer->setVisible(true);
}

void UI_MainMenu_Layer::visibleExchange()
{
	if (!m_pExchangeCodeLayer)
	{
		this->m_pExchangeCodeLayer = UI_Exchange_Code_Layer::create();
		addChild(m_pExchangeCodeLayer, 25, EXCHANGE_LAYER);
		float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
		m_pExchangeCodeLayer->setScale(rate);
	}
	m_pExchangeCodeLayer->setVisible(!m_pExchangeCodeLayer->isVisible());
}

void UI_MainMenu_Layer::visibleLoginAward()
{
	if (!m_pLoginAwardLayer)
	{
		this->m_pLoginAwardLayer = UI_Login_Award_Layer::create();
		float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
		m_pLoginAwardLayer->setScale(rate);
		addChild(m_pLoginAwardLayer, 25, LOGIN_AWARD_LAYER);
	}
	m_pLoginAwardLayer->setVisible(!m_pLoginAwardLayer->isVisible());
}

void UI_MainMenu_Layer::visibleDailyMission()
{
	if (!m_pDailyMissionLayer)
	{
		m_pDailyMissionLayer = UI_Daily_Mission::create();
		this->addChild(m_pDailyMissionLayer);
	}
	m_pDailyMissionLayer->setVisible(true);
}

//void UI_MainMenu_Layer::visibleFragmentCombine()
//{
//	if (!m_pItemCombineLayer)
//	{
//		m_pItemCombineLayer = UI_Item_Combine_Layer::create();
//		this->addChild(m_pItemCombineLayer);
//	}
//	m_pItemCombineLayer->setVisible(true);
//}

//void UI_MainMenu_Layer::visibleResidualPage()
//{
//	if (!m_pResidualPageLayer)
//	{
//		m_pResidualPageLayer = UI_Residual_Page_Layer::create();
//		float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
//		m_pResidualPageLayer->setScale(rate);
//		this->addChild(m_pResidualPageLayer);
//	}
//	m_pResidualPageLayer->setVisible(true);
//}

void UI_MainMenu_Layer::visibleSkillUpLayer(bool visible, int skillId, int characterId)
{
	//if (!m_pSkillDescLayer)
	//{
	//	m_pSkillDescLayer = UI_Skill_Icon_Info_Layer::create();
	//	float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
	//	m_pSkillDescLayer->setScale(rate);
	//	this->addChild(m_pSkillDescLayer, 20, SKILL_LAYER + 1);
	//}
	//m_pSkillDescLayer->showSelectSkillInfo(skillId, characterId);
	//m_pSkillDescLayer->setVisible(visible);
}

void UI_MainMenu_Layer::visibleFuncOpen(int iconNameId, int iconOpenId)
{
	if (!m_pFuncOpenLayer)
	{
		m_pFuncOpenLayer = UI_New_Function_Open::create();
		this->addChild(m_pFuncOpenLayer, MAX_LAYER);
	}

	m_pFuncOpenLayer->setVisible(true);
	m_pFuncOpenLayer->showPromptInfo(iconNameId, iconOpenId);
}

//void UI_MainMenu_Layer::visibleSweepDescLayer(int ui_instance_elite)
//{
//	if (!m_pSweepDescLayer)
//	{
//		m_pSweepDescLayer = UI_Sweep_Desc_Layer::create();
//		this->addChild(m_pSweepDescLayer, MAX_LAYER);
//	}
//
//	if (ui_instance_elite == 0)
//	{
//		m_pSweepDescLayer->set_is_elite_instance(0);
//	}
//	else
//	{
//		m_pSweepDescLayer->set_is_elite_instance(1);
//	}
//
//	m_pSweepDescLayer->setVisible(true);
//}

void UI_MainMenu_Layer::visibleEquipmentInlayLayer()
{
	//if (!m_equipment_inlay_layer)
	//{
	//	m_equipment_inlay_layer = UI_Equipment_Inlay_Gem::create();
	//	this->addChild(m_equipment_inlay_layer, MAX_LAYER);
	//}
	//m_equipment_inlay_layer->setVisible(true);
}

void UI_MainMenu_Layer::visibleEquipmentGemCombine()
{
	//if (!m_equipment_gem_combine)
	//{
	//	m_equipment_gem_combine = UI_Equipment_Gem_Combine::create();
	//	this->addChild(m_equipment_gem_combine, MAX_LAYER);
	//}
	//m_equipment_gem_combine->setVisible(true);
}

void UI_MainMenu_Layer::visibleTradeLayer(uint64 goods_id, int style)
{
	if (!m_trade_layer)
	{
		m_trade_layer = UI_Trade_Layer::create();
		this->addChild(m_trade_layer, MAX_LAYER + 1);
	}
	m_trade_layer->set_style_show_info(goods_id, style);
	//m_trade_layer->setTouchPriority(-128);
	m_trade_layer->setVisible(true);
}

void UI_MainMenu_Layer::visibleActivityEnterLayer(Ref* pSender, Widget::TouchEventType type)
{
//	if (!m_activity_six_sect_layer)
//	{
//		m_activity_six_sect_layer = UI_Activity_Six_Sect_Layer::create();
//		this->addChild(m_activity_six_sect_layer, MAX_LAYER + 1);
//	}
//	m_activity_six_sect_layer->setVisible(true);
}

void UI_MainMenu_Layer::visibleHeartMethodCombine(int character_id)
{
//	if (!m_pHeartMethodCombineLayer)
//	{
//		m_pHeartMethodCombineLayer = UI_HeartMethod_Combine_Layer::create();
//		float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
//		m_pHeartMethodCombineLayer->setScale(rate);
//		this->addChild(m_pHeartMethodCombineLayer, 20);
//	}
//
//	m_pHeartMethodCombineLayer->setVisible(true);
}

void UI_MainMenu_Layer::visibleEquipmentQualityUp(uint64 item_id)
{
	//if (!m_pEquipmentQualityUpLayer)
	//{
	//	m_pEquipmentQualityUpLayer = UI_Equipment_Quality_Up_Layer::create();
	//	float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
	//	m_pEquipmentQualityUpLayer->setScale(rate);
	//	this->addChild(m_pEquipmentQualityUpLayer, 20);
	//}

	////m_pEquipmentQualityUpLayer->set_up_item_id(item_id);
	//m_pEquipmentQualityUpLayer->setVisible(true);
}

void UI_MainMenu_Layer::visibleSecondaryInstance(int area_id)
{
#if 1
//if (!selBattleLayer)
//{
//	selBattleLayer = SelectBattleLayer::create();
//	this->addChild(get_instance()->selBattleLayer);
//	selBattleLayer->setVisible(true);
//}
#else
//	if (!m_pSecondaryInstanceLayer)
//	{
//		m_pSecondaryInstanceLayer = UI_Secondary_Instance_Layer::create();
//		float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
//		m_pSecondaryInstanceLayer->setScale(rate);
//		this->addChild(m_pSecondaryInstanceLayer, 20);
//	}
//
//	m_pSecondaryInstanceLayer->init_instance_date(area_id);
//	m_pSecondaryInstanceLayer->setVisible(true);
#endif
}

void UI_MainMenu_Layer::visibleHeartMethodQualityUp(uint64 item_id)
{
//	if (!m_pHeartMethodQualityUpLayer)
//	{
//		m_pHeartMethodQualityUpLayer = UI_HeartMethod_Quality_Up_Layer::create();
//		float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
//		m_pHeartMethodQualityUpLayer->setScale(rate);
//		this->addChild(m_pHeartMethodQualityUpLayer, 20);
//	}
//
//	//m_pHeartMethodQualityUpLayer->set_up_item_id(item_id);
//	m_pHeartMethodQualityUpLayer->setVisible(true);
}

#if 0
void UI_MainMenu_Layer::keyBackClicked(void)
{
	const char* exitInfo = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SURE_TO_EXIT_GAME);
	UI_ModalDialogue_Layer::DoModal("", exitInfo, UI_ModalDialogue_Layer::DT_YES_NO, [&](){ this->btnCallBackExit(); } );
}
#endif

void UI_MainMenu_Layer::btnCallBackExit()
{
	Director::getInstance()->end();
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	exit(0);
#endif
}

void UI_MainMenu_Layer::addChatContent(const char* szChatContent, int channel, const char* sender, const char* receiver)
{
	if (m_pChatBoard)
	{
		if (m_pChatBoard->isVisible() == false && channel == CHAT_CHANNEL_PRIVATE)
		{
			ActionInterval* blink = CCBlink::create(1.5f, 2);
			CCAction* action = CCRepeatForever::create(blink);
			m_pBtnChatBoard->runAction(action);
		}

		m_pChatBoard->addChatContent(channel, sender, receiver, szChatContent);
	}
}

void UI_MainMenu_Layer::privateChatFromRelationList(const char* receiver)
{
	if (receiver == NULL)
	{
		return;
	}

//	if (m_pChatBoard)
//	{
//		m_pChatBoard->setVisible(true);
//		m_pChatBoard->openPrivateChat(receiver);
//	}

}

void UI_MainMenu_Layer::refreshFindWay()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (player == NULL)
	{
		return;
	}

	//经验条设置
	int current_exp = player->get_exp();
	int current_level_sum_exp = player->get_player_levelup_exp();
//	m_pPercentVisible->setPercentage((float)(current_exp * 100 / current_level_sum_exp));
//	m_pPercentVisible->setVisible(false);
	const quest_data::quest_data_vec_t vecData = quest_data_mgr::instance()->get_quest_data_list(player_id);
	if (vecData.size() == 0)
	{
		refresh_accept_quest_show();
	}
	else
	{
		refresh_quest_show();
	}
}

void UI_MainMenu_Layer::buttonExchangeCode(Ref* pSender, Widget::TouchEventType type)
{
	float rate;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		//setToggleState(1);

		this->m_pLoginAwardLayer = UI_Login_Award_Layer::create();
		rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
		m_pLoginAwardLayer->setScale(rate);
		addChild(m_pLoginAwardLayer, 25, LOGIN_AWARD_LAYER);
		m_pLoginAwardLayer->setVisible(true);

		//Joiner_Guidance::hideGuide();

		break;
	default:
		break;
	}
}

void UI_MainMenu_Layer::btnShoppingCenter(Ref* pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		//setToggleState(1);
		if (!m_pShopCenterLayer)
		{
			m_pShopCenterLayer = UI_Shop_Center_Layer::create();
			this->addChild(m_pShopCenterLayer);
		}
		m_pShopCenterLayer->setVisible(true);

		break;
	default:
		break;
	}
}

void UI_MainMenu_Layer::btnPayMoneyCallback(Ref* pSender, Widget::TouchEventType type)
{

}

void UI_MainMenu_Layer::btnActivityCallback(Ref* pSender, Widget::TouchEventType type)
{

//	switch (type)
//	{
//	case cocos2d::ui::Widget::TouchEventType::ENDED:
//		if (!m_activity_layer)
//		{
//			m_activity_layer = UI_Activity_Layer::create();
//			this->addChild(m_activity_layer, MAX_LAYER);
//		}
//		m_activity_layer->setVisible(true);
//
//		break;
//	default:
//		break;
//	}
}

void UI_MainMenu_Layer::move_to_accept_quest_npc()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	quest_data* qst = Game_Data::quest_data_mgr::instance()->get_guide_quest_in_acceptable_quest(player_id);
	if (!qst)
	{
		return;
	}

	game_quest_content ele_cont;
	qst->get_quest_accept(ele_cont);

	Game_Data::game_element_list_t ele_list;
	ele_cont.get_quest_element(ele_list);

	vector<uint> para;
	Game_Data::Game_Element_Parse::instance()->get_para_from_require_element("npctalk", ele_list, para);
	if (para.size() > 0)
	{
		City_NPC* retNPC = Game_Utils::instance()->get_npc_by_id((int)para[0]);
		if (retNPC)
		{
			Point pt = retNPC->getPosition();
			Game_Utils::instance()->quest_auto_move((int)para[0], Game_Utils::show_npc_dialog, (int)para[0]);
		}
	}
}

void UI_MainMenu_Layer::move_to_quest_npc()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	const quest_data::quest_data_vec_t vec_accepted_quest = quest_data_mgr::instance()->get_quest_data_list(player_id);
	int index = 0;
	if (vec_accepted_quest.size() >= 2)
	{
		for (int i = 1; i < (int)vec_accepted_quest.size(); ++i)
		{
			if (vec_accepted_quest[i].get_quest_id() < vec_accepted_quest[i - 1].get_quest_id())
			{
				index = i;
			}
		}
	}

	const quest_data& refData = vec_accepted_quest[index];
	quest_data* qd = Game_Data::quest_data_mgr::instance()->get_quest_data(player_id, refData.get_quest_id());
	if (!qd)
	{
		return;
	}

	if (qd->get_quest_state() == quest_data::QUEST_STATE_INPROCESS)
	{
		game_quest_content ele_cont;
		qd->get_quest_content(ele_cont);

		Game_Data::game_element_list_t ele_list;
		ele_cont.get_quest_element(ele_list);

		Game_Data::game_element_list_t::iterator itg;
		for (itg = ele_list.begin(); itg != ele_list.end(); ++itg)
		{
			Game_Element& element = (*itg);
			if (element.get_count() == element.get_count_require())
			{
				continue;
			}

			vector<uint> para;
			element.get_para_list_in_vector(para);
			if (strcmp(element.get_command(), "monster") == 0 || strcmp(element.get_command(), "item") == 0) //副本
			{
				if (para.size() > 2)
				{
					int instance_id = para[2];
					Instance_UI_Config* config = INSTANCE_DATA_MGR::instance()->get_instance_ui_config(instance_id);
					INSTANCE_DATA_MGR::instance()->set_current_prompt_instance_id(PT_QUEST,instance_id);
					Game_Utils::instance()->quest_auto_move(1011, Game_Utils::clicked_area, config->area_id);
					break;
				}
			}
			else if (strcmp(element.get_command(), "equip_equipment") == 0) //穿装备
			{
				if (para.size() > 0)
				{
					int item_base_id = para[0];
					UI_MainMenu_Layer::get_instance()->quest_show_bag(item_base_id);
					break;
				}
			}
			else if (strcmp(element.get_command(), "instance") == 0) //副本完成
			{
				if (para.size() > 0)
				{
					int instance_id = para[0];
					Instance_UI_Config* config = INSTANCE_DATA_MGR::instance()->get_instance_ui_config(instance_id);
					INSTANCE_DATA_MGR::instance()->set_current_prompt_instance_id(PT_QUEST,instance_id);
					Game_Utils::instance()->quest_auto_move(1011, Game_Utils::clicked_area, config->area_id);
					break;
				}
			}
			else if (strcmp(element.get_command(), "up_skill") == 0) //招式升级
			{
				if (para.size() > 1)
				{
					int skill_base_id = para[0];

					UI_MainMenu_Layer::get_instance()->quest_show_skill(skill_base_id);
					break;
				}
			}
			else if (strcmp(element.get_command(), "up_equipment_level") == 0) //装备强化
			{
				if (para.size() > 0)
				{
					int item_base_id = para[0];
					UI_MainMenu_Layer::get_instance()->quest_show_equipment(item_base_id);
					break;
				}
			}
			else if (strcmp(element.get_command(), "equip_book") == 0) //装备心法
			{
				if (para.size() > 0)
				{
					int item_base_id = para[0];
					UI_MainMenu_Layer::get_instance()->quest_show_book_bag(item_base_id);
					break;
				}
			}
			else if (strcmp(element.get_command(), "up_equipment_quality") == 0) //装备升品
			{
				if (para.size() > 0)
				{
					int item_base_id = para[0];
					UI_MainMenu_Layer::get_instance()->quest_show_equipment(item_base_id);
					break;
				}
			}
			else if (strcmp(element.get_command(), "up_book_level") == 0) //心法合成
			{
				if (para.size() > 0)
				{
					int role_id = Account_Data_Mgr::instance()->get_current_role_id();
					Game_Data::Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
					UI_MainMenu_Layer::get_instance()->visibleHeartMethodCombine(role_id);
					break;
				}
			}
			else if (strcmp(element.get_command(), "equip_item_all") == 0)   //全装备
			{
				if (para.size() > 0)
				{
					UI_MainMenu_Layer::get_instance()->buttonBagInfo(NULL, Widget::TouchEventType::ENDED);
					break;
				}
			}
			else if (strcmp(element.get_command(), "up_player_quality") == 0) //人物升品   playerqaup(1)  1：升品次数
			{
				if (para.size() > 0)
				{
					UI_MainMenu_Layer::get_instance()->visibleRoleQualityUp();
					break;
				}
			}
			else if (strcmp(element.get_command(), "up_book_quality") == 0) //心法升品    equipbookqaup(0,1,140)
			{
				if (para.size() > 0)
				{
					int role_id = Account_Data_Mgr::instance()->get_current_role_id();
					Game_Data::Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
					UI_MainMenu_Layer::get_instance()->visibleHeartMethodCombine(role_id);
					break;
				}
			}
			else if (strcmp(element.get_command(), "allequipreqqa") == 0) //一身装备达到绿色品质  allequipreqqa(1)
			{
				if (para.size() > 0)
				{
					int item_base_id = para[0];
					UI_MainMenu_Layer::get_instance()->quest_show_equipment(item_base_id);
					break;
				}
			}
		}
	}
	else if (qd->get_quest_state() == quest_data::QUEST_STATE_SUBMITABLE)
	{
		game_quest_content ele_cont;
		qd->get_quest_complete(ele_cont);

		Game_Data::game_element_list_t ele_list;
		ele_cont.get_quest_element(ele_list);

		vector<uint> para;
		Game_Data::Game_Element_Parse::instance()->get_para_from_require_element("npctalk", ele_list, para);
		if (para.size() > 0)
		{
			Game_Data::CommonNpc* npc = Character_Mgr::instance()->get_common_npc_by_static_id(para[0]);
			if (npc)
			{
			#if 1
				City_NPC* retNPC = Game_Utils::instance()->get_npc_by_id((int)para[0]);
				if (retNPC)
				{
					Point pt = retNPC->getPosition();
					Game_Utils::instance()->quest_auto_move((int)para[0], Game_Utils::show_npc_dialog, (int)para[0]);
				}
			#else
				//int npcinstanceid = npc->get_database_character_id();
				//UI::NPC* retNPC = Game_Utils::instance()->get_npc_by_id(npcinstanceid);
				//if(retNPC)
				//{
				//	Point pt = retNPC->getPosition();
				//	Game_Utils::instance()->quest_auto_move(int(pt.x),int(pt.y),UI::Actor_Layer::show_npc_dialogue,retNPC->sprite_id());
				//}
			#endif
			}
		}
	}
}

void UI_MainMenu_Layer::refresh_accept_quest_show()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	quest_data* org_qst = Game_Data::quest_data_mgr::instance()->get_guide_quest_in_acceptable_quest(player_id);
	if (org_qst)
	{
		game_quest_content ele_cont;
		org_qst->get_quest_accept(ele_cont);

		Game_Data::game_element_list_t ele_list;
		ele_cont.get_quest_element(ele_list);

		vector<uint> para;
		Game_Data::Game_Element_Parse::instance()->get_para_from_require_element("npctalk", ele_list, para);
		if (para.size() > 0)
		{
			Game_Data::CommonNpc* npc = Character_Mgr::instance()->get_common_npc_by_static_id(para[0]);
			if (npc)
			{
				int npcinstanceid = npc->get_static_character_id();

				//获取角色名称
				Scene* pScene = Director::getInstance()->getRunningScene();
				CC_ASSERT(pScene);
				Actor_Layer* pLayer = dynamic_cast<Actor_Layer*>(pScene->getChildByTag(TAG_ACT));
				CC_ASSERT(pLayer);
				int nTypeID = npc->get_database_character_id();
				//NPC* pNpc = pLayer->get_npc(nTypeID);

				//CommonNpcConfig* config = CommonNpc_Config_MGR::instance()->get_commomnpc_by_id(npcinstanceid);
				//if (config)
				//{
				int icon = npc->get_face_mode_id();
				const char* iconname = ITEM_CONFIG_MGR::instance()->get_icon_path(icon);
				//设置 提交任务的 NPC 头像   以及任务字体显示
					//m_pImgFindWay->loadTexture(iconname,UI_TEX_TYPE_PLIST);
					//m_pLabFindWayFont->setString(npc->get_character_name());
					//m_pLabFindWayFont->setVisible(true);
					//m_pImgFontShadow->setVisible(false);
				//}
			}

			game_quest_content ele_cont;
			org_qst->get_quest_content(ele_cont);

			Game_Data::game_element_list_t ele_list;
			ele_cont.get_quest_element(ele_list);

			Game_Data::game_element_list_t::iterator itg;
			for (itg = ele_list.begin(); itg != ele_list.end(); ++itg)
			{
				Game_Element& element = (*itg);
				para.clear();
				element.get_para_list_in_vector(para);
				if (strcmp(element.get_command(), "instance") == 0)
				{
					if (para.size() > 2)
					{
						int guide_step = para[2];
						if (1 == guide_step && para[0] == 10000 && player->get_guide_id() < 1)
						{
						
							player->change_guide_id(1);
							showGuide();
							break;
						}
					}
				}
			}
		}
		return;
	}

    //m_pImgFindWay->loadTexture("guide_.png");
	//m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
	//m_pBtnFindPath->loadTextures("guide_.png", "guide_.png", "guide_.png", UI_TEX_TYPE_PLIST);;
	//m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_PLIST);
	//	m_pLabFindWayFont->setVisible(false);
	//	m_pImgFontShadow->setVisible(false);
	return;
}

void UI_MainMenu_Layer::refresh_quest_show()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	const quest_data::quest_data_vec_t vecData = quest_data_mgr::instance()->get_quest_data_list(player_id);
	int index = 0;
	if (vecData.size() >= 2)
	{
		for (int i = 1; i < (int)vecData.size(); ++i)
		{
			if (vecData[i].get_quest_id() < vecData[i - 1].get_quest_id())
			{
				index = i;
			}
		}
	}

	const quest_data& refData = vecData[index];
	quest_data* qd = Game_Data::quest_data_mgr::instance()->get_quest_data(player_id, refData.get_quest_id());
	if (!qd)
	{
		return;
	}

	if (qd->get_quest_state() == quest_data::QUEST_STATE_INPROCESS)
	{
		game_quest_content ele_cont;
		qd->get_quest_content(ele_cont);

		Game_Data::game_element_list_t ele_list;
		ele_cont.get_quest_element(ele_list);

		Game_Data::game_element_list_t::iterator itg;
		for (itg = ele_list.begin(); itg != ele_list.end(); ++itg)
		{
			Game_Element& element = (*itg);
			if (element.get_count() == element.get_count_require())
			{
				continue;
			}

			vector<uint> para;
			element.get_para_list_in_vector(para);
			if (strcmp(element.get_command(), "monster") == 0 || strcmp(element.get_command(), "item") == 0)
			{
				if (para.size() > 2)
				{
					int instance_id = para[2];
					vector<uint> para;
					para.clear();
					Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute", "instance_name", "instance_name", para);

					int name_dic_id = -1;
					if (para.size() >= 1)
					{
						name_dic_id = para[0];
					}
					const char* sz_name_dic = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(name_dic_id);

					//m_pImgFindWay->loadTexture("guide_.png",UI_TEX_TYPE_LOCAL);

					//m_pLabFindWayFont->setString(sz_name_dic);
					//m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);
					break;

				}
			}
			else if (strcmp(element.get_command(), "equip_equipment") == 0)  //穿装备
			{
				if (para.size() > 0)
				{
					int item_base_id = para[0];

                    //m_pImgFindWay->loadTexture("guide_.png",UI_TEX_TYPE_LOCAL);
					   
					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_EQUIP_EQUIPMENT);
					//m_pLabFindWayFont->setString(szFont);
					//m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);

					if (para.size() > 2)
					{
						int guide_step = para[2];
						if (BAG_GUIDE_STEP_0 == guide_step
							&& player->get_guide_id() <= BAG_GUIDE_STEP_0
							&& qd->get_quest_id() == FUNCTION_OPEN_LOGIC::instance()->open_icon_array[ICON_BAG_TAG]
							)
						{
							player->change_guide_id(BAG_GUIDE_STEP_0);
							showGuide();
						}
					}
					break;
				}
			}
			else if (strcmp(element.get_command(), "instance") == 0) //副本完成
			{
				if (para.size() > 0)
				{
					int instance_id = para[0];
					vector<uint> para;
					para.clear();
					Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute", "instance_name", "instance_name", para);

					int name_dic_id = -1;
					if (para.size() >= 1)
					{
						name_dic_id = para[0];
					}
					const char* sz_name_dic = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(name_dic_id);

					//m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
					     
					//m_pLabFindWayFont->setString(sz_name_dic);
					//m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);
					break;
				}
			}
			else if (strcmp(element.get_command(), "up_skill") == 0) //招式升级
			{
				if (para.size() > 1)
				{
					int skill_base_id = para[0];

					//m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
					     
					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_SKILL_UP);
					//m_pLabFindWayFont->setString(szFont);
					//m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);

					if (para.size() > 2)
					{
						int guide_step = para[2];
						if (SKILL_LEVEL_UP_STEP_0 == guide_step
							&& player->get_guide_id() <= SKILL_LEVEL_UP_STEP_0
							&& qd->get_quest_id() == FUNCTION_OPEN_LOGIC::instance()->open_icon_array[ICON_SKILL_TAG])
						{
							player->change_guide_id(SKILL_LEVEL_UP_STEP_0);
							showGuide();
						}
					}
					break;
				}
			}
			#if 0
			else if (strcmp(element.get_command(), "up_equipment_level") == 0) //装备强化
			{
				if (para.size() > 0)
				{
					int item_base_id = para[0];

					m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_EQUIMENT_STRENGTHENING);
					m_pLabFindWayFont->setString(szFont);
					m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);

					if (para.size() > 2)
					{
						int guide_step = para[2];
						if (EQUIP_GUIDE_STEP_0 == guide_step
							&& player->get_guide_id() <= EQUIP_GUIDE_STEP_0
							&& qd->get_quest_id() == FUNCTION_OPEN_LOGIC::instance()->open_icon_array[ICON_EQUIP_TAG])
						{
							player->change_guide_id(EQUIP_GUIDE_STEP_0);
							//showGuide();
						}
					}
					break;
				}
			}
			#endif
			#if 0
			else if (strcmp(element.get_command(), "equip_book") == 0) //装备心法
			{
				if (para.size() > 0)
				{
					int item_base_id = para[0];

					m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_XINFA_EQUIP);
					m_pLabFindWayFont->setString(szFont);
					m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);

					if (para.size() > 2)
					{
						int guide_step = para[2];
						if (XF_EQUIP_GUIDE_STEP_0 == guide_step &&
							player->get_guide_id() <= XF_EQUIP_GUIDE_STEP_0 &&
							qd->get_quest_id() == FUNCTION_OPEN_LOGIC::instance()->open_icon_array[ICON_XINFA_EQUIP_BTN])
						{
							player->change_guide_id(XF_EQUIP_GUIDE_STEP_0);
							//showGuide();
						}
					}
					break;
				}
			}
			#endif
			else if (strcmp(element.get_command(), "up_equipment_quality") == 0) //装备升品
			{
				if (para.size() > 0)
				{
					//m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
					     
					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(EQUIPMENT_QUALITY_UP_TITLE);
					//m_pLabFindWayFont->setString(szFont);
					//m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);

					if (para.size() > 2)
					{
						int guide_step = para[2];
						if (EQUIP_QUA_UP_STEP_0 == guide_step
							&& player->get_guide_id() <= EQUIP_QUA_UP_STEP_0
							&& qd->get_quest_id() == 100016				//暂时标记当前引导人物ID 100016
							)
						{
							player->change_guide_id(EQUIP_QUA_UP_STEP_0);
							showGuide();
						}
					}
					break;
				}
			}
#if 0
			else if (strcmp(element.get_command(), "up_book_level") == 0) //心法合成
			{
				if (para.size() > 0)
				{
					m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);

					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(HEART_METHOD_COMBINE);
					m_pLabFindWayFont->setString(szFont);
					m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);

					if (para.size() > 2)
					{
						int guide_step = para[2];
						if (XF_COMBINE_STEP_0 == guide_step
							&& player->get_guide_id() <= XF_COMBINE_STEP_0
							&& qd->get_quest_id() == FUNCTION_OPEN_LOGIC::instance()->open_icon_array[ICON_XINFA_COMBINE_BTN]
							)
						{
							player->change_guide_id(XF_COMBINE_STEP_0);
							//showGuide();
						}
					}
					break;
				}
			}
#endif			
#if 0
			else if (strcmp(element.get_command(), "compound_book_fragment") == 0) //拼装心法
			{
				if (para.size() > 0)
				{
					m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
				
					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_PINZHUANG_XINFA);
					m_pLabFindWayFont->setString(szFont);
					m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);

					if (para.size() > 2)
					{
						int guide_step = para[2];
						if (XF_ASSEMBLE_STEP_0 == guide_step
							&& player->get_guide_id() <= XF_ASSEMBLE_STEP_0
							&& qd->get_quest_id() == FUNCTION_OPEN_LOGIC::instance()->open_icon_array[ICON_XINFA_TAG]
							)
						{
							player->change_guide_id(XF_ASSEMBLE_STEP_0);
							//showGuide();
						}
					}
					break;
				}
			}
#endif
#if 0
			else if (strcmp(element.get_command(), "compound_material_fragment") == 0) //拼装碎片 (字典表配置替换文字信息)
			{
				if (para.size() > 0)
				{
					m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
					
					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_PINZHUANG_XINFA);
					m_pLabFindWayFont->setString(szFont);
					m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);

					if (para.size() > 2)
					{
						int guide_step = para[2];
						if (FRAGEMENT_COMB_STEP_0 == guide_step
							&& player->get_guide_id() <= FRAGEMENT_COMB_STEP_0
							&& qd->get_quest_id() == FUNCTION_OPEN_LOGIC::instance()->open_icon_array[ICON_BAG_COMBINE_BTN]
							)
						{
							player->change_guide_id(FRAGEMENT_COMB_STEP_0);
							//showGuide();
						}
					}
					break;
				}
			}
#endif
#if 0
			else if (strcmp(element.get_command(), "player_pk") == 0)		//竞技场
			{
				if (para.size() > 0)
				{
					m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
				
					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_ARENE_TITLE);
					m_pLabFindWayFont->setString(szFont);
					m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);

					if (para.size() > 2)
					{
						int guide_step = para[2];
						if (ARENA_FIGHT_STEP_0 == guide_step
							&& player->get_guide_id() <= ARENA_FIGHT_STEP_0
							&& qd->get_quest_id() == FUNCTION_OPEN_LOGIC::instance()->open_icon_array[ICON_ARENA_TAG]
							)
						{
							player->change_guide_id(ARENA_FIGHT_STEP_0);
							//showGuide();
						}
					}
					break;
				}
			}
#endif
#if 0
			else if (strcmp(element.get_command(), "up_player_quality") == 0) //人物升品   playerqaup(1)  1：升品次数
			{
				if (para.size() > 0)
				{
					m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
					
					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_ROLE_QUALITY_UP);
					m_pLabFindWayFont->setString(szFont);
					m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);
					if (para.size() > 2)
					{
						int guide_step = para[2];
						if (ROLE_QUA_UP_STEP_0 == guide_step
							&& player->get_guide_id() <= ROLE_QUA_UP_STEP_0
							&& qd->get_quest_id() == FUNCTION_OPEN_LOGIC::instance()->open_icon_array[ICON_ROLE_QUA_BTN]
							)
						{
							player->change_guide_id(ROLE_QUA_UP_STEP_0);
							//showGuide();
						}
					}
					break;
				}
			}
#endif
			//领取每日奖励
			// 			else if (strcmp(element.get_command(), "") == 0)
			// 			{
			// 				if(para.size() > 0)
			// 				{
			// 
			// 					break;
			// 				}
			// 			}

			//副将出战
			#if 0
			else if (strcmp(element.get_command(), "general_fight") == 0)
			{
				if (para.size() > 0)
				{
					m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
					
					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_LIEUTENANT_FIGHT);
					m_pLabFindWayFont->setString(szFont);
					m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);
					if (para.size() > 2)
					{
						int guide_step = para[2];
						if (LIEUTENANT_FIGHT_STEP_0 == guide_step
							&& player->get_guide_id() <= LIEUTENANT_FIGHT_STEP_0
							&& qd->get_quest_id() == FUNCTION_OPEN_LOGIC::instance()->open_icon_array[ICON_LIEU_FIGHT_BTN]
							)
						{
							player->change_guide_id(LIEUTENANT_FIGHT_STEP_0);
							//showGuide();
						}
					}
					break;
				}
			}
#endif
			//使用副将战斗
			// 			else if (strcmp(element.get_command(), "") == 0)
			// 			{
			// 				if(para.size() > 0)
			// 				{
			// 
			// 					break;
			// 				}
			// 			}

			//升级天命
			#if 0
			else if (strcmp(element.get_command(), "open_acupoint") == 0)
			{
				if (para.size() > 0)
				{
					m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
					
					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_FATE_LEVEL_UP);
					m_pLabFindWayFont->setString(szFont);
					m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);

					if (para.size() > 2)
					{
						int guide_step = para[2];
						if (FATE_LEVEL_UP_STEP_0 == guide_step
							&& player->get_guide_id() <= FATE_LEVEL_UP_STEP_0
							&& qd->get_quest_id() == FUNCTION_OPEN_LOGIC::instance()->open_icon_array[ICON_FATE_TAG]
							)
						{
							player->change_guide_id(FATE_LEVEL_UP_STEP_0);
							//showGuide();
						}
					}

					break;
				}
			}
			#endif
			//心法升品
			#if 0
			else if (strcmp(element.get_command(), "up_book_quality") == 0) //心法升品    equipbookqaup(0,1,140)
			{
				if (para.size() > 0)
				{
					m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
					
					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_XINFA_QUALITY_UP);
					m_pLabFindWayFont->setString(szFont);
					m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);

					if (para.size() > 2)
					{
						int guide_step = para[2];
						if (XF_QUA_UP_STEP_0 == guide_step
							&& player->get_guide_id() <= XF_QUA_UP_STEP_0
							&& qd->get_quest_id() == FUNCTION_OPEN_LOGIC::instance()->open_icon_array[ICON_XINFA_QUA_BTN]
							)
						{
							player->change_guide_id(XF_QUA_UP_STEP_0);
							//showGuide();
						}
					}

					break;
				}
			}
            #endif
			else if (strcmp(element.get_command(), "equip_item_all") == 0)   //全装备
			{
				if (para.size() > 0)
				{
					//m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
					    
					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_EQUIP_EQUIPMENT);
					//m_pLabFindWayFont->setString(szFont);
					//m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);

					break;
				}
			}

			else if (strcmp(element.get_command(), "allequipreqqa") == 0) //一身装备达到绿色品质  allequipreqqa(1)
			{
				if (para.size() > 0)
				{
					//m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
					
					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_ALL_GREEN_QUA_EQUIP);
					//m_pLabFindWayFont->setString(szFont);
					//m_pLabFindWayFont->setVisible(true);
					m_pImgFontShadow->setVisible(false);

					break;
				}
			}
		}
		showGuide();
	}
	else if (qd->get_quest_state() == quest_data::QUEST_STATE_SUBMITABLE)
	{

		//Game_Data::quest_data* qd_ori = Game_Data::quest_data_mgr::instance()->get_org_quest_data(qd->get_quest_id());
		//game_quest_content ele_cont;
		//qd_ori->get_quest_content(ele_cont);

		game_quest_content ele_cont;
		qd->get_quest_content(ele_cont);
		Game_Data::game_element_list_t ele_list;
		ele_cont.get_quest_element(ele_list);

		Game_Data::game_element_list_t::iterator itg;
		for (itg = ele_list.begin(); itg != ele_list.end(); ++itg)
		{
			Game_Element& element = (*itg);
			vector<uint> para;
			element.get_para_list_in_vector(para);
			if (strcmp(element.get_command(), "instance") == 0) //副本完成
			{
				player->change_guide_id(1);
				if (para.size() > 0)
				{
					int instance_id = para[0];
					if (Instance_Data_Mgr::instance()->get_quest_instance_state(player_id, instance_id)==0)
					{
						vector<uint64> para;
						para.push_back(player_id);
						para.push_back(refData.get_quest_id());
						Game_Logic::Game_Content_Interface::instance()->exec_interface("sendsubmitquest", para);
					}					
				}
			}
		}

#if 0
		para.clear();
		Game_Data::Game_Element_Parse::instance()->get_para_from_require_element("npctalk", ele_list, para);
		if (para.size() > 0)
		{
			Game_Data::CommonNpc* npc = Character_Mgr::instance()->get_common_npc_by_static_id(para[0]);
			if (npc)
			{
				int npcinstanceid = npc->get_static_character_id();
				CommonNpcConfig* config = CommonNpc_Config_MGR::instance()->get_commomnpc_by_id(npcinstanceid);

				//获取角色名称
				Scene* pScene = Director::getInstance()->getRunningScene();
				CC_ASSERT(pScene);
				Actor_Layer* pLayer = dynamic_cast<Actor_Layer*>(pScene->getChildByTag(TAG_ACT));
				CC_ASSERT(pLayer);
				int nTypeID = npc->get_database_character_id();
				//NPC* pNpc = pLayer->get_npc(nTypeID);

				//if (config)
				//{
				    int icon = npc->get_face_mode_id();
					const char* iconname = ITEM_CONFIG_MGR::instance()->get_icon_path(icon);
                std::string p("icon/");
                p+=iconname;
				//设置 提交任务的 NPC 头像   以及任务字体显示
					m_pImgFindWay->loadTexture(p.c_str());
				//	int type = config->get_npc_type();
				//	m_pLabFindWayFont->setString(pNpc->get_name());
				//	m_pLabFindWayFont->setVisible(true);
				//	m_pImgFontShadow->setVisible(false);
				//}
			}
		}
#endif
	}
}

bool UI_MainMenu_Layer::update_friend_detail(const Game_Logic::Game_Event& gm_evt)
{
	return true;
}

void UI_MainMenu_Layer::buttonBanks(Ref* pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		//setToggleState(1);

		this->m_pBancksLayer = UI_Banks_Layer::create();
		addChild(m_pBancksLayer, 25, BANKS_LAYER);
		m_pBancksLayer->setVisible(true);

		break;
	default:
		break;
	}
}

bool UI_MainMenu_Layer::update_banks(const Game_Logic::Game_Event& gm_evt)
{
	if (get_instance()->m_pBancksLayer)
	{
		get_instance()->m_pBancksLayer->update();
	}
	return true;
}

bool UI_MainMenu_Layer::update_rank(const Game_Logic::Game_Event& gm_evt)
{
	/*if (get_instance()->m_pRankingList)
	{
		vector<uint64> para;
		gm_evt.get_para(para);
		if (para.size() > 0)
		{
			get_instance()->m_pRankingList->update((int)para[0]);
		}
	}*/
	return true;
}

void UI_MainMenu_Layer::reg_event_update_ui(const char* cmd, const Game_Logic::game_event_handler_t handle, unsigned int owner_type)
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Logic::Game_Event event;
	event.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
	event.set_char_id(player_id);
	event.set_event_owner_type(owner_type);
	event.set_event_owner_id(0);
	event.set_event_active_type(0);
	event.set_event_active_id(0);
	Game_Logic::Game_Event_Mgr::instance()->reg_event(cmd, handle, event);
}

void UI_MainMenu_Layer::remove_event_update_ui(unsigned int owner_type)
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Logic::Game_Event event;
	event.reset();
	event.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
	event.set_char_id(player_id);
	event.set_event_owner_type(owner_type);
	event.set_event_owner_id(0);
	Game_Logic::Game_Event_Mgr::instance()->remove_event(player_id, event);
}

bool UI_MainMenu_Layer::update_login_award(const Game_Logic::Game_Event& gm_evt)
{
	if (get_instance()->m_pLoginAwardLayer)
	{
		get_instance()->m_pLoginAwardLayer->refresh();
	}
	return true;
}

bool UI_MainMenu_Layer::update_instance_sweep(const Game_Logic::Game_Event& gm_evt)
{
//	if (get_instance()->m_pSweepDescLayer)
//	{
//		get_instance()->m_pSweepDescLayer->update();
//	}
	return true;
}

bool UI_MainMenu_Layer::update_gem_inlay(const Game_Logic::Game_Event& gm_evt)
{
	/*if (get_instance()->m_equipment_inlay_layer)
	{
		vector<uint64> para;
		gm_evt.get_para(para);
		if (para.size() > 0)
		{
			get_instance()->m_equipment_inlay_layer->update((int)para[0]);
		}
		else
		{
			get_instance()->m_equipment_inlay_layer->update(-1);
		}
	}*/
	if (get_instance()->m_pBagInfo)
	{
		vector<uint64> para;
		gm_evt.get_para(para);
		get_instance()->m_pBagInfo->RefreshGemLayer();
		get_instance()->m_pBagInfo->update();

	}
	return true;
}

bool UI_MainMenu_Layer::update_operate_gem(const Game_Logic::Game_Event& gm_evt)
{
	//if (get_instance()->m_equipment_gem_combine)
	//{
	//	vector<uint64> para;
	//	gm_evt.get_para(para);
	//	if (para.size() > 0)
	//	{
	//		get_instance()->m_equipment_gem_combine->show_combine_ui((int)para[0]);
	//	}
	//}
	return true;
}

bool UI_MainMenu_Layer::update_gem_level_up(const Game_Logic::Game_Event& gm_evt)
{
	//if (get_instance()->m_equipment_gem_combine)
	//{
	//	get_instance()->m_equipment_gem_combine->update();
	//}
	//return true;
	if (get_instance()->m_pBagInfo)
	{
		vector<uint64> para;
		gm_evt.get_para(para);
		get_instance()->m_pBagInfo->RefreshGemLayer();
	}
	return true;
}

bool UI_MainMenu_Layer::update_shop(const Game_Logic::Game_Event& gm_evt)
{
	if (get_instance()->m_pShopCenterLayer)
	{
		get_instance()->m_pShopCenterLayer->update();
	}
	return true;
}

bool UI_MainMenu_Layer::update_daily_task(const Game_Logic::Game_Event& gm_evt)
{
	if (get_instance()->m_pDailyMissionLayer)
	{
		get_instance()->m_pDailyMissionLayer->update();
	}
	return true;
}

/*====================================   dely   ====================================*/
bool UI_MainMenu_Layer::update_chat(const Game_Logic::Game_Event& gm_evt)
{
	if (get_instance()->m_pChatBoard)
		get_instance()->m_pChatBoard->update();

	return true;

}

void UI_MainMenu_Layer::initJoystick()
{
	joyStick = SneakyJoystick::create();
	joyStick->initWithRect(Rect::ZERO, false);
	joyStick->setAutoCenter(true);
	joyStick->setHasDeadzone(true);
	joyStick->setDeadRadius(10);

	auto btnBack = dynamic_cast<ImageView*>(root->getChildByName("pad_back"));
	btnBack->setVisible(false);
	auto joySkin = SneakyJoystickSkinnedBase::create();
	joySkin->setBackgroundSprite(Sprite::create("img/joystick/pad_back.png"));
	joySkin->setThumbSprite(Sprite::create("img/joystick/pad.png"));

	joySkin->setPosition(btnBack->getPosition());
	joySkin->setJoystick(joyStick);
	btnBack = dynamic_cast<ImageView*>(root->getChildByName("pad"));
	btnBack->setVisible(false);
	root->addChild(joySkin);
}

/*====================================   dely   ====================================*/
void UI_MainMenu_Layer::btnEndlessTowerCallback(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 无尽塔按钮点击回调
	if (type != Widget::TouchEventType::ENDED)
		return;
 //   Joiner_Guidance::hideGuide();
	//SendMsgRequestChallengeEndlessTower();
    dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
	auto endless = ENDLESS_VIEW::create();
	addChild(endless);
}

void UI_MainMenu_Layer::SendMsgRequestChallengeEndlessTower()
{
	/************************************************************************/
	// 发生消息请求挑战无尽塔（无尽塔是相当于关卡的某一特定的章节,这里的值是章节ID）
	vector<uint64> para;
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	para.push_back(player_id);
	para.push_back(5000);

	Game_Logic::Game_Content_Interface::instance()->exec_interface("sendrequireallstage", para);
}

#if 1//MISSION_DIALOG
void UI_MainMenu_Layer::SendAllSubmitableQuest()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();

	const quest_data::quest_data_vec_t vecData = quest_data_mgr::instance()->get_quest_data_list(player_id);

	size_t len=vecData.size();
	for (int i = 0; i < len; i++)
	{
		quest_data qd = vecData[i];

		game_quest_content ele_cont;
		qd.get_quest_content(ele_cont);
		Game_Data::game_element_list_t ele_list;
		ele_cont.get_quest_element(ele_list);

		Game_Data::game_element_list_t::iterator itg;
		for (itg = ele_list.begin(); itg != ele_list.end(); ++itg)
		{
			Game_Element& element = (*itg);
			vector<uint> para;
			element.get_para_list_in_vector(para);
			if (strcmp(element.get_command(), "instance") == 0) //副本完成
			{
				if (para.size() > 0)
				{
					int instance_id = para[0];
					if (Instance_Data_Mgr::instance()->get_quest_instance_state(player_id, qd.get_quest_id())==0)
					{
						vector<uint64> para;
						para.push_back(player_id);
						para.push_back(qd.get_quest_id());
						Game_Logic::Game_Content_Interface::instance()->exec_interface("sendsubmitquest", para);
					}
				}
			}
		}
	}

}
#endif
void UI_MainMenu_Layer::openPropertyCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type)
{
	int player_id;
	Game_Data::Player* player;
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
        dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
        
		player_id = Account_Data_Mgr::instance()->get_current_role_id();
		player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
		if (!player)
		{
			return;
		}
		if (BAG_GUIDE_STEP_1 == player->get_guide_id()
			|| FRAGEMENT_COMB_STEP_1 == player->get_guide_id()
			)
		{
			player->change_guide_id(player->get_guide_id() + 1);
		}
		if (player)
		{
			UI_Bag_Info_Layer::sIsProperty = true;
			UI_Bag_Info_Layer::sName = player->get_character_name();
			UI_Bag_Info_Layer::sPower = player->get_fighting_capacity();
            UI_Bag_Info_Layer::sTili = player->get_energy();
			//Exp = player->get_character
			UI_Bag_Info_Layer::sHP = player->get_character_cur_hp();
			UI_Bag_Info_Layer::sAtk = player->get_character_attack();
			UI_Bag_Info_Layer::sGuard = player->get_character_define();
			UI_Bag_Info_Layer::sMP = player->get_character_cur_mp();
			UI_Bag_Info_Layer::sLevel = player->get_character_level();
			UI_Bag_Info_Layer::sJob = player->get_job();
		}
		if (!m_pBagInfo)
		{

			m_pBagInfo = UI_Bag_Info_Layer::create();
			float rate = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getWinSize().width;
			m_pBagInfo->setScale(rate);
			this->addChild(m_pBagInfo, 20, BAG_LAYER);

		}

		m_pBagInfo->initData();
		auto tRoot = m_pBagInfo->getRoot();
        auto right = dynamic_cast<Widget*>(Helper::seekWidgetByName(tRoot, "Pnl_Bag"));
        right->setVisible(false);
        auto right1 = dynamic_cast<Widget*>(Helper::seekWidgetByName(tRoot, "Pnl_Property"));
		right1->setVisible(true);
		m_pBagInfo->setVisible(true);

		//setToggleState(1);
	}
		break;
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;	}

}

void UI_MainMenu_Layer::onClickTitleCallback(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
    dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
	auto titleLayer = TITLE_VIEW::create();
	addChild(titleLayer);

}

void UI_MainMenu_Layer::onClickBossCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	auto bossLayer = BOSS_VIEW::create();
	addChild(bossLayer);
}

void UI_MainMenu_Layer::onClickFateCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
    dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
	auto fateLayer = FATE_VIEW::create();
	addChild(fateLayer);
}

void UI_MainMenu_Layer::onClickArenaCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	//auto taskLayer = TASK_VIEW::create(); taskLayer->setVisible(true);
	//addChild(taskLayer);
    dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
	auto arenaLayer = ARENA_VIEW::create();
	addChild(arenaLayer);
}

void UI_MainMenu_Layer::onClickRobCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
    dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
	auto god = GOD_VIEW::create();
	addChild(god);
}

void UI_MainMenu_Layer::onClickStarCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	auto star = STAR_VIEW::create();
	addChild(star);
}

void UI_MainMenu_Layer::hideCampaign(int index)
{
	//for (int i = 0; i < int(cNum); i++)
	//{
		_campaign[index]->setVisible(false);
	//}
}

void UI_MainMenu_Layer::hideSports(int index)
{
	//for (int i = 0; i < int(sNum); i++)
	//{
		_sports[index]->setVisible(false);
	//}
}

void UI_MainMenu_Layer::hideButtons(int index)
{
	m_pFunctionalBtn[index]->setVisible(false);
}

void UI_MainMenu_Layer::onEnter()
{
	Layer::onEnter();
//	campaignToggle(_campaignDestinationCbx, Widget::TouchEventType::ENDED);
//	sportsToggle(_sportsDestinationCbx, Widget::TouchEventType::ENDED);

}

void UI_MainMenu_Layer::onClickTaskCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type!=Widget::TouchEventType::ENDED)
		return;
	auto taskLayer = TASK_VIEW::create(); taskLayer->setVisible(true);
	addChild(taskLayer,10000);

}

void UI_MainMenu_Layer::onClickPetCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
    dynamic_cast<Widget *>(pSender)->removeChildByTag(1000);
	auto petLayer = PET_VIEW::create(); petLayer->setVisible(true);
	addChild(petLayer, 10000);

}