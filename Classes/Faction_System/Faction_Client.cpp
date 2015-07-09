#include "Faction_Client.h"
#include "Faction_Config_Mgr.h"

#include "cocostudio/CocoStudio.h"

#include "../UI_Interface/MyEditBox.h"
#include "../DataModule/Little.h"
#include "../Player_Account/Account_Data_Mgr.h"
#include "../Character_System/Character_Mgr.h"
#include "../Character_System/Player.h"
#include "../Network_Common/NetManager.h"
#include "../Network_Common/message.h"
#include "Faction_Config_Mgr.h"

using namespace cocos2d::ui;

using namespace Game_Model;
using namespace Game_View;
using namespace Game_Controller;

//model
bool FACTION_MODEL::init()
{
	auto create_data = FACTION_CONFIG_MGR::instance()->get_create_faction();
	int limit = create_data->level;
	int coin = create_data->gold;
	int tokenn = create_data->token;

	FACTION_MODEL::getInstance()->setLevelLimit(limit);
	FACTION_MODEL::getInstance()->setCoin(coin);
	FACTION_MODEL::getInstance()->setToken(tokenn);
	//auto common_data = FACTION_CONFIG_MGR::instance()->get_faction_data_by_lv(1);

	std::string faction_name = FACTION_MODEL::getInstance()->faction_db.faction_name;
	int  faction_level = FACTION_MODEL::getInstance()->faction_db.faction_level;
	int  cur_exp = FACTION_MODEL::getInstance()->faction_db.curr_exp;
	vector<faction_member_data*> members = FACTION_MODEL::getInstance()->faction_db.member_list;
	int  cur_size = members.size();
	int  active_num = FACTION_MODEL::getInstance()->faction_db.active_num;

	faction_name = "Protoss";
	faction_level = 20;
	cur_size = 30;
	active_num = 10000;

	//FACTION_MODEL::getInstance()->setName(faction_name);
	//FACTION_MODEL::getInstance()->setLevel(faction_level);
	//FACTION_MODEL::getInstance()->setNum(cur_size);
	FACTION_MODEL::getInstance()->setExp(cur_exp);

	//FACTION_MODEL::getInstance()->setActive(active_num);
	FACTION_MODEL::getInstance()->setAttack(10);
	FACTION_MODEL::getInstance()->setDefense(10);
	FACTION_MODEL::getInstance()->setLife(10);
	FACTION_MODEL::getInstance()->setWind(10);
	FACTION_MODEL::getInstance()->setFire(10);
	FACTION_MODEL::getInstance()->setThunder(10);

	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_FACTION,nullptr);

	return true;

}
FACTION_MODEL* FACTION_MODEL::getInstance()
{
	static FACTION_MODEL _instance;
	return &_instance;
}

FACTION_BOSS_MODEL* FACTION_BOSS_MODEL::getInstance()
{
	static FACTION_BOSS_MODEL _instance;
	return &_instance;

}

//view
bool FACTION_VIEW::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		CC_BREAK_IF(!FACTION_MODEL::getInstance()->init());
		CC_BREAK_IF(!FACTION_NET::getInstance()->init());

		//bool bJoined = FACTION_CONTROLLER::getInstance()->isJoined();
		bool bJoined = FACTION_MODEL::getInstance()->isJoined();
		if (bJoined)
		{
			auto main = FACTION_MAIN_VIEW::create();
			CC_BREAK_IF(!main);
			addChild(main);
			//m_pRoot = dynamic_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/guild_main/guild_main.ExportJson"));
		}
		else
		{
			auto apply = FACTION_APPLY_VIEW::create();
			CC_BREAK_IF(!apply);
			addChild(apply);
			//m_pRoot = dynamic_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/guild_apply/guild_apply.ExportJson"));
		}
		//auto reopenListner = EventListenerCustom::create(EVENT_REOPEN_FACTION, CC_CALLBACK_1( FACTION_VIEW::eventReopen,this) );
		Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_REOPEN_FACTION, CC_CALLBACK_1(FACTION_VIEW::eventReopen, this) );
		Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_FACTION_CREATE_SUCCESS, CC_CALLBACK_1(FACTION_VIEW::event_create_faction_success, this));

		bRet = true;

	} while (false);

	return bRet;

}

void FACTION_VIEW::onEnter()
{
	Layer::onEnter();
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FACTION_SEND_GET_DATA, nullptr);

}

void FACTION_VIEW::onExit()
{
	Layer::onExit();
}

void FACTION_VIEW::onCloseCallback(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;

	this->removeFromParent();
	

}

void FACTION_VIEW::eventReopen(EventCustom* evt)
{	
	this->init();
	this->onEnter();
	//bool bJoined = FACTION_MODEL::getInstance()->isJoined();
	//if (bJoined)
	//{
	//	auto main = FACTION_MAIN_VIEW::create();
	//	if (main == nullptr)
	//		return;
	//	addChild(main);
	//	//m_pRoot = dynamic_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/guild_main/guild_main.ExportJson"));
	//}
}

void FACTION_VIEW::event_create_faction_success(EventCustom* event)
{
	FACTION_MODEL::getInstance()->setJoined(true);
	this->removeAllChildrenWithCleanup(true);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REOPEN_FACTION, nullptr);
	//FACTION_CONTROLLER::getInstance()->setJoined(true);
	//auto delay = DelayTime::create(0.2f);
	//auto callback1 = CallFunc::create(CC_CALLBACK_0(FACTION_APPLY_VIEW::removeFromParent, this));
	//auto callback2 = CallFunc::create(CC_CALLBACK_0(FACTION_APPLY_VIEW::eventCallback, this));
	//this->runAction( Sequence::create(delay, callback1, callback2, nullptr) );
	//FACTION_MODEL::getInstance()->setJob(1);//for test 1 member 2 fubangzhu 3 bangzhu
	//FACTION_MODEL::getInstance()->setJob(3);
	//FACTION_MODEL::getInstance()->setDigTime(3);
}

bool FACTION_MAIN_VIEW::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		auto board = BoardEditBox::create();
		board->SetPositionAndMaxLength(-300, 300, 280);
		addChild(board, 1,"Board");

		m_pRoot = nullptr;
		m_pRoot = dynamic_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/guild_main.json"));
		CC_BREAK_IF(!m_pRoot);
		addChild(m_pRoot);

		auto confirm = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pRoot, "Btn_Confirm"));
		confirm->addTouchEventListener(this, toucheventselector(FactionMainLayer::onClickConfirmSign));

		auto renotice = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pRoot, "Btn_Board_Edit"));
		renotice->addTouchEventListener(this, toucheventselector(FactionMainLayer::onClickRenotice));
		int job = FACTION_MODEL::getInstance()->getJob();
		if (job != 1)
		{
			renotice->setTouchEnabled(true);
			renotice->setBright(true);
		}
		else
		{
			renotice->setTouchEnabled(false);
			renotice->setBright(false);
		}
		
		auto imgSign = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pRoot, "Img_Sign_In"));
		imgSign->addTouchEventListener(this, toucheventselector(FactionMainLayer::onClickSign));

		bool bSigned = FACTION_CONTROLLER::getInstance()->isSigned();
		if (bSigned)
		{
			imgSign->setTouchEnabled(false);
			auto txtSigned = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pRoot, "Txt_Sign_Value"));
			txtSigned->setString("1/1");
			txtSigned->enableGlow(Color4B(255,0,0,255));
			//txtSigned->setFontName("fonts/Marker Felt.ttf");
			//auto  testLbl = Label::createWithTTF("1/1", "fonts/Marker Felt.ttf", 12);
			//testLbl->setPosition(Vec2(200, 200));
			//addChild(testLbl,1000000);
		}
		else
			imgSign->setTouchEnabled(true);

		auto imgBoss = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pRoot, "Img_Boss"));
		imgBoss->addTouchEventListener(this, toucheventselector(FactionMainLayer::onClickBoss));

		auto imgWorship = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pRoot, "Img_Worship"));
		imgWorship->addTouchEventListener(this, toucheventselector(FactionMainLayer::onClickWorship));

		auto imgDig = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pRoot, "Img_Mine"));
		imgDig->addTouchEventListener(this, toucheventselector(FactionMainLayer::onClickDig));

		auto imgTotem = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pRoot, "Img_Totem"));
		imgTotem->addTouchEventListener(this, toucheventselector(FactionMainLayer::onClickTotem));

		auto imgMember = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pRoot, "Img_Member"));
		imgMember->addTouchEventListener(this, toucheventselector(FactionMainLayer::onClickMember));

		Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_REFRESH_FACTION, CC_CALLBACK_1(FACTION_MAIN_VIEW::eventRefresh, this));
		Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_REFRESH_BOARD, CC_CALLBACK_1(FACTION_MAIN_VIEW::eventRefreshBoard, this));
		this->runAction(Sequence::create(DelayTime::create(0.2f), CallFunc::create([]()
		{
			std::vector<uint64> para;
			para.clear();
			Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_GET_DATA, para);

		}), nullptr));

		bRet = true;

	} while (false);

	return bRet;

}

void FACTION_MAIN_VIEW::onClickRenotice(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FACTION_SEND_RENOTICE, nullptr);
	std::vector<uint64> para;
	para.clear();
	auto box = (BoardEditBox*)(this->getChildByName("Board") );
	auto notice = box->getContent();
	FACTION_MODEL::getInstance()->setNotice(notice);
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_RENOTICE, para,notice.c_str() );

}

void FACTION_MAIN_VIEW::onClickSign(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	auto signSuccess = dynamic_cast<Widget*>(Helper::seekWidgetByName(m_pRoot, "Pnl_Sign_Success"));

	signSuccess->setVisible(true);
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_FACTION, nullptr);

}

void FACTION_MAIN_VIEW::onClickConfirmSign(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	auto signSuccess = dynamic_cast<Widget*>(Helper::seekWidgetByName(m_pRoot, "Pnl_Sign_Success"));
	auto txtSigned = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pRoot, "Txt_Sign_Value"));
	auto imgSign = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pRoot, "Img_Sign_In"));

	imgSign->setTouchEnabled(false);
	 txtSigned->setString("1/1");
	//txtSigned->setString("签到");
	signSuccess->setVisible(false);
	FACTION_CONTROLLER::getInstance()->setSigned(true);

}

void FACTION_MAIN_VIEW::onClickBoss(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	m_pBossRoot = dynamic_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/guild_boss.json"));

	auto one = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pBossRoot, "Img_Boss1"));
	one->addTouchEventListener(this, toucheventselector(FACTION_MAIN_VIEW::onClickOne));

	auto two = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pBossRoot, "Img_Boss2"));
	two->addTouchEventListener(this, toucheventselector(FACTION_MAIN_VIEW::onClickTwo) );

	auto three = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pBossRoot, "Img_Boss3"));
	three->addTouchEventListener(this, toucheventselector(FACTION_MAIN_VIEW::onClickThree));

	auto four = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pBossRoot, "Img_Boss4"));
	four->addTouchEventListener(this, toucheventselector(FACTION_MAIN_VIEW::onClickFour));

	auto closeBoss = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pBossRoot, "Btn_Close"));
	closeBoss->setTouchEnabled(true);
	closeBoss->addTouchEventListener( this, toucheventselector(FACTION_MAIN_VIEW::onCloseBoss) );

	auto wish = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pBossRoot, "Btn_Wish"));
	wish->setTouchEnabled(true);
	wish->addTouchEventListener( this, toucheventselector(FACTION_MAIN_VIEW::onClickWish) );

	auto challenge = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pBossRoot, "Btn_challenge"));
	challenge->setTouchEnabled(true);
	challenge->addTouchEventListener(this, toucheventselector(FACTION_MAIN_VIEW::onClickChallenge));

	auto cursor = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pBossRoot, "Img_Cursor"));
	auto cursor_show = cursor->clone();
	auto pos = one->getPosition();
	cursor_show->setPosition(pos);
	cursor_show->setName("Img_Cursor_Show");
	auto parent = one->getParent();
	parent->addChild(cursor_show);

	Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_REFRESH_BOSS, CC_CALLBACK_1(FACTION_MAIN_VIEW::eventRefreshBoss, this));
	addChild(m_pBossRoot, 2, 124);

	//eventRefreshBoss(nullptr
	this->scheduleOnce(schedule_selector(FACTION_MAIN_VIEW::delayRefreshBoss), 0.03f);
}

void FACTION_MAIN_VIEW::delayRefreshBoss(float dt)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_BOSS, nullptr);

}

void FACTION_MAIN_VIEW::onClickOne(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	int level = FACTION_MODEL::getInstance()->getLevel();
	auto config = FACTION_CONFIG_MGR::instance()->get_faction_data_by_lv(level);
	int boss_id = config->boss_id;
	FACTION_BOSS_MODEL::getInstance()->setBossId(boss_id);
	auto me = (ImageView*)pSender;
	auto parent = me->getParent();
	auto pos = me->getPosition();
	auto cursor = parent->getChildByName("Img_Cursor_Show");

	cursor->setPosition(pos);
}

void FACTION_MAIN_VIEW::onClickTwo(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	int level = FACTION_MODEL::getInstance()->getLevel();
	auto config = FACTION_CONFIG_MGR::instance()->get_faction_data_by_lv(level);
	int boss_id = config->boss_id;
	FACTION_BOSS_MODEL::getInstance()->setBossId(boss_id);
	auto me = (ImageView*)pSender;
	auto parent = me->getParent();
	auto pos = me->getPosition();
	auto cursor = parent->getChildByName("Img_Cursor_Show");

	cursor->setPosition(pos);
}

void FACTION_MAIN_VIEW::onClickThree(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	int level = FACTION_MODEL::getInstance()->getLevel();
	auto config = FACTION_CONFIG_MGR::instance()->get_faction_data_by_lv(level);
	int boss_id = config->boss_id;
	FACTION_BOSS_MODEL::getInstance()->setBossId(boss_id);
	auto me = (ImageView*)pSender;
	auto parent = me->getParent();
	auto pos = me->getPosition();
	auto cursor = parent->getChildByName("Img_Cursor_Show");

	cursor->setPosition(pos);
}

void FACTION_MAIN_VIEW::onClickFour(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	int level = FACTION_MODEL::getInstance()->getLevel();
	auto config = FACTION_CONFIG_MGR::instance()->get_faction_data_by_lv(level);
	int boss_id = config->boss_id;
	FACTION_BOSS_MODEL::getInstance()->setBossId(boss_id);
	auto me = (ImageView*)pSender;
	auto parent = me->getParent();
	auto pos = me->getPosition();
	auto cursor = parent->getChildByName("Img_Cursor_Show");

	cursor->setPosition(pos);
}

void FACTION_MAIN_VIEW::onClickBuff1(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	FACTION_BOSS_MODEL::getInstance()->setBuffId(1);

}

void FACTION_MAIN_VIEW::onClickBuff2(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	FACTION_BOSS_MODEL::getInstance()->setBuffId(2);

}

void FACTION_MAIN_VIEW::onClickBuff3(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	FACTION_BOSS_MODEL::getInstance()->setBuffId(3);
}

void FACTION_MAIN_VIEW::onClickBuff4(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	FACTION_BOSS_MODEL::getInstance()->setBuffId(4);

}

void FACTION_MAIN_VIEW::eventRefreshBoss(EventCustom* evt)
{
	int curLevel = FACTION_MODEL::getInstance()->getLevel();
	faction_data_common* common = FACTION_CONFIG_MGR::instance()->get_faction_data_by_lv(curLevel);
	if (common == nullptr)
		return;
	FACTION_BOSS_MODEL::getInstance()->setBossId(common->boss_id);
	//FACTION_BOSS_MODEL::getInstance()->setCurTimes(common->boss_num);
	FACTION_BOSS_MODEL::getInstance()->setTotalTimes(common->boss_num);
	FACTION_BOSS_MODEL::getInstance()->setActive(common->kill_boss_active_num);
	FACTION_BOSS_MODEL::getInstance()->setContribute(common->kill_boss_values);
	int curTime = FACTION_BOSS_MODEL::getInstance()->getCurTimes();
	int totalTime = FACTION_BOSS_MODEL::getInstance()->getTotalTimes();
	auto txtBoss = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pRoot, "Txt_Boss_Value"));
	char timeBuff[50];
	sprintf(timeBuff, "%d/%d", curTime, totalTime);
	txtBoss->setString(timeBuff);

	auto bossData = FACTION_BOSS_MODEL::getInstance();
	//int oneLvl = bossData->getOneLevel();
	//int oneVal = bossData->getOneValue();
	//int twoLvl = bossData->getTwoLevel();
	//int twoVal = bossData->getTwoValue();
	//int threeLvl = bossData->getThreeLevel();
	//int threeVal = bossData->getThreeValue();
	//int fourLvl = bossData->getFourLevel();
	//int fourVal = bossData->getFourValue();

	auto oneLevel = dynamic_cast<Text*>(Helper::seekWidgetByName( m_pBossRoot,"Txt_Boss1_Level") );
	char oneLevelBuff[50];
	sprintf(oneLevelBuff, "活跃 + %d", common->kill_boss_active_num);
	oneLevel->setString(oneLevelBuff);
	
	auto oneValue = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pBossRoot, "Label_120"));
	char oneValueBuff[50];
	sprintf(oneValueBuff, "贡献 + %d", common->kill_boss_values);
	oneValue->setString(oneValueBuff);

	auto twoLevel = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pBossRoot, "Txt_Boss2_Level"));
	char twoLevelBuff[50];
	sprintf(twoLevelBuff, "活跃 + %d", common->kill_boss_active_num);
	twoLevel->setString(twoLevelBuff);

	auto twoValue = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pBossRoot, "Label_119_1"));
	char twoValueBuff[50];
	sprintf(twoValueBuff, "贡献 + %d", common->kill_boss_values);
	twoValue->setString(twoValueBuff);

	auto threeLevel = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pBossRoot, "Txt_Boss3_Level"));
	char threeLevelBuff[50];
	sprintf(threeLevelBuff, "活跃 + %d", common->kill_boss_active_num);
	threeLevel->setString(threeLevelBuff);

	auto threeValue = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pBossRoot, "Label_119_3"));
	char threeValueBuff[50];
	sprintf(threeValueBuff, "贡献 + %d", common->kill_boss_values);
	threeValue->setString(threeValueBuff);

	auto fourLevel = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pBossRoot, "Label_119_4"));
	char fourLevelBuff[50];
	sprintf(fourLevelBuff, "活跃 + %d", common->kill_boss_active_num);
	fourLevel->setString(fourLevelBuff);

	auto fourValue = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pBossRoot, "Label_119_5"));
	char fourValueBuff[50];
	sprintf(fourValueBuff, "贡献 + %d", common->kill_boss_values);
	fourValue->setString(fourValueBuff);

	auto timeTxt = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pBossRoot, "Label_138"));
	char totalTimeBuff[50];
	sprintf(totalTimeBuff, "%d / %d", FACTION_BOSS_MODEL::getInstance()->getCurTimes(), FACTION_BOSS_MODEL::getInstance()->getTotalTimes() );
	timeTxt->setString(totalTimeBuff);
}

void FACTION_MAIN_VIEW::onClickWish(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	log("Wish here!");
}

void FACTION_MAIN_VIEW::onClickChallenge(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	log("Challenge here!");
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FACTION_SEND_CHALLENGE,nullptr);
	int curTime = FACTION_BOSS_MODEL::getInstance()->getCurTimes();
	if (curTime <= 0)
		return;
	vector<uint64> para;
	para.clear();
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_CHALLENGE, para);
}

void FACTION_MAIN_VIEW::onCloseBoss(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	//this->getChildByTag(124)->removeFromParent();
	m_pBossRoot->removeFromParent();
}

void FACTION_MAIN_VIEW::eventRefreshWorship(EventCustom* evt)
{
	auto txtWorshipOuter = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pRoot, "Txt_Worship_Value"));
	int cur = FACTION_MODEL::getInstance()->getWorshipCurTime();
	int total = FACTION_MODEL::getInstance()->getWorshipTotalTime();
	char txtBuff[50];
	sprintf(txtBuff,"%d / %d",cur,total);
	txtWorshipOuter->setString(txtBuff);

	auto txtWorshipInner = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pWorshipRoot, "Txt_Times"));
	txtWorshipInner->setString(txtBuff);

}

void FACTION_MAIN_VIEW::delayRefreshWorship(float dt)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_WORSHIP, nullptr);

}

void FACTION_MAIN_VIEW::onClickWorship(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	m_pWorshipRoot = dynamic_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/guild_worship.json"));
	addChild(m_pWorshipRoot, 2, 125);
	int curTime = FACTION_MODEL::getInstance()->getWorshipCurTime();
	int totalTime = FACTION_MODEL::getInstance()->getWorshipTotalTime();

	auto txtWorship = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pWorshipRoot, "Txt_Times"));
	char worshipBuff[50];
	sprintf(worshipBuff, "%d / %d", curTime, totalTime);
	txtWorship->setString(worshipBuff);

	auto imgWorship = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pWorshipRoot, "Img_Worship"));
	int id = FACTION_MODEL::getInstance()->getCurSelectMemberId();
	if (id == -1)
		imgWorship->setVisible(false);
	else
		imgWorship->setVisible(true);

	imgWorship->addTouchEventListener(this, toucheventselector(FACTION_MAIN_VIEW::onClickMemberWorship));

	auto closeWorship = dynamic_cast<Widget*>(Helper::seekWidgetByName(m_pWorshipRoot, "Btn_Close"));
	closeWorship->setTouchEnabled(true);
	closeWorship->addTouchEventListener(this, toucheventselector(FACTION_MAIN_VIEW::onCloseWorship));

	auto scrMembers = dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pWorshipRoot, "Scr_Members"));
	auto cell = dynamic_cast<ui::Layout*>(Helper::seekWidgetByName(m_pWorshipRoot, "Pnl_Cell"));

	vector<faction_member_data> list = FACTION_MODEL::getInstance()->getMembers();
	sort(list.begin(), list.end(), [](faction_member_data m1, faction_member_data m2){
		return m1.fighting_capacity > m2.fighting_capacity;
	});

	int i = 0;
	for (auto& member:list)
	{
		int player_id = member.player_id;
		std::string member_name(member.name.c_str());
		int member_lv = member.lv;
		int member_job = member.job;
		int member_power = member.fighting_capacity;

		auto cellShow = cell->clone();
		auto nameTxt = dynamic_cast<Text*>(cellShow->getChildByName("Txt_Name"));
		Value name_buff(member_name.c_str());
		nameTxt->setString( name_buff.asString().c_str() );

		auto levelTxt = dynamic_cast<Text*>(cellShow->getChildByName("Txt_Lv"));
		Value level_buff(member_lv);
		levelTxt->setString(level_buff.asString().c_str());

		auto powerTxt = dynamic_cast<Text*>(cellShow->getChildByName("Txt_Power"));
		Value power_buff(member_power);
		powerTxt->setString(power_buff.asString().c_str());

		cellShow->setPosition( Vec2( 0,220-10-40-40*i ) );
		cellShow->addTouchEventListener(this, toucheventselector(FACTION_MAIN_VIEW::onClickWorshipCell));
		cellShow->setTag(member.player_id);

		scrMembers->addChild(cellShow);
		i++;
		if (i >= 9)
			break;

	}
	auto cursor = dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(m_pWorshipRoot, "Img_Cursor"));
	auto cursorShow = cursor->clone();
	cursorShow->setPosition(Vec2(0, 800));
	cursorShow->setName("Img_Cursor_Show");
	scrMembers->addChild(cursorShow);

	Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_REFRESH_WORSHIP, CC_CALLBACK_1(FACTION_MAIN_VIEW::eventRefreshWorship, this));

	this->scheduleOnce(schedule_selector(FACTION_MAIN_VIEW::delayRefreshWorship), 0.03f);


}

void FACTION_MAIN_VIEW::onClickWorshipCell(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	auto imgWorship = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pWorshipRoot, "Img_Worship"));
	imgWorship->setVisible(true);
	imgWorship->setTouchEnabled(true);
	auto member = (Layout*)pSender;
	int player_id = member->getTag();
	FACTION_MODEL::getInstance()->setCurSelectMemberId(player_id);
	Vec2 pos = member->getPosition();
	auto cursor = dynamic_cast<ImageView*>( Helper::seekWidgetByName(m_pWorshipRoot, "Img_Cursor_Show") );
	cursor->setVisible(true);
	cursor->setPosition(pos);
}

void FACTION_MAIN_VIEW::onClickMemberWorship(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	auto cursor = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pWorshipRoot, "Img_Cursor_Show"));
	cursor->setVisible(false);
	auto imgWorship = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pWorshipRoot, "Img_Worship"));
	imgWorship->setVisible(false);

	int target_id = FACTION_MODEL::getInstance()->getCurSelectMemberId();
	FACTION_MODEL::getInstance()->setCurSelectMemberId(-1);
	int cur_time = FACTION_MODEL::getInstance()->getWorshipCurTime();
	if (cur_time <= 0)
		return;

	vector<uint64> para;
	para.push_back(target_id);
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_WORSHIP, para);

}

void FACTION_MAIN_VIEW::onCloseWorship(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	this->getChildByTag(125)->removeFromParent();

}

void FACTION_MAIN_VIEW::onClickDig(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	m_pMineRoot = dynamic_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/guild_dig.json"));
	addChild(m_pMineRoot, 2, 126);

	auto closeMine = dynamic_cast<Widget*>(Helper::seekWidgetByName(m_pMineRoot, "Btn_Close"));
	closeMine->setTouchEnabled(true);
	closeMine->addTouchEventListener(this, toucheventselector(FACTION_MAIN_VIEW::onCloseDig));

	int curTime = FACTION_MODEL::getInstance()->getDigCurTime();
	int totalTime = FACTION_MODEL::getInstance()->getDigTotalTime();
	auto timesTxt = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pMineRoot, "Txt_Dig_Count"));
	auto timesTxtInner = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pMineRoot, "Txt_Dig_Count"));
	char timesBuff[50];
	
	sprintf(timesBuff, "%s%d / %d", Little::litles[8].name.c_str(), curTime, totalTime);
	timesTxtInner->setString(timesBuff);

	auto resultTxt = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pMineRoot, "Txt_Show_Result"));

	auto imgStone = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMineRoot, "Img_Stone"));
	imgStone->setTouchEnabled(true);
	imgStone->setVisible(true);
	imgStone->addTouchEventListener( this, toucheventselector(FACTION_MAIN_VIEW::onClickConfirmDig) );

	auto imgDig = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMineRoot, "Img_Dig"));
	imgDig->setTouchEnabled(true);
	imgDig->setVisible(true);
	imgDig->addTouchEventListener(this, toucheventselector(FACTION_MAIN_VIEW::onClickConfirmDig));

	Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_REFRESH_DIG, CC_CALLBACK_1(FACTION_MAIN_VIEW::eventRefressDig, this) );
	//this->scheduleOnce(schedule_selector(FACTION_MAIN_VIEW::delayRefreshDig), 0.03f);

}

void FACTION_MAIN_VIEW::onClickConfirmDig(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	int curTime = FACTION_MODEL::getInstance()->getDigCurTime();
	if (curTime <= 0)
		return;
	vector<uint64> para;
	para.clear();
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_DIG, para);
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FACTION_SEND_DIG, nullptr);
	
}

void FACTION_MAIN_VIEW::eventRefressDig(EventCustom* evt)
{
	auto timesTxtOuter = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pRoot, "Txt_Mine_Value"));
	int curTime = FACTION_MODEL::getInstance()->getDigCurTime();
	int totalTime = FACTION_MODEL::getInstance()->getDigTotalTime();
	char timeBuff[50];
	sprintf(timeBuff,"%d / %d",curTime,totalTime);
	timesTxtOuter->setString(timeBuff);

	auto timesTxtInner = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pMineRoot, "Txt_Dig_Count"));
	char timesBuff[50];
	sprintf(timesBuff, "%s:%d / %d", Little::litles[8].name.c_str(),curTime, totalTime);
	timesTxtInner->setString(timesBuff);

	auto resultTxt = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pMineRoot, "Txt_Show_Result"));
	auto imgStone = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMineRoot, "Img_Stone"));
	imgStone->setVisible(false);
	auto imgDig = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMineRoot, "Img_Dig"));
	imgDig->setVisible(false);

	
	auto cell = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(m_pMineRoot, "Txt_Cell"));
	auto cell_clone = (Text*)(cell->clone());
	auto scroll = dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pMineRoot, "Scr_Show"));
	scroll->removeAllChildren();
	std::deque<std::string> msgs;
	std::deque<std::string>::iterator it = msgs.begin();

	for (int count = 0;it < msgs.end();it++)
	{
		count++;
		cell_clone->setString("the first time");
		cell_clone->setPosition(Vec2(0,70 - count*15));
		scroll->addChild(cell_clone);
		if (count > 5)
		{
			float tmpY = count * 15.f;
			Size new_size(480, tmpY);
			scroll->setInnerContainerSize(new_size);
			scroll->jumpToBottom();
		}
		else
		{
			scroll->setInnerContainerSize(Size(480, 70));
			scroll->jumpToTop();
		}

	}

}

void FACTION_MAIN_VIEW::delayRefreshDig(float dt)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_DIG, nullptr);
}

void FACTION_MAIN_VIEW::onCloseDig(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	this->getChildByTag(126)->removeFromParent();

}

void FACTION_MAIN_VIEW::onClickTotem(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	auto totem = dynamic_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/guild_totem.json"));
	addChild(totem, 2, 127);

	auto closeTotem = dynamic_cast<Button*>(Helper::seekWidgetByName(totem, "Btn_Close"));
	closeTotem->setTouchEnabled(true);
	closeTotem->addTouchEventListener(this, toucheventselector(FACTION_MAIN_VIEW::onCloseTotem));


	auto active = dynamic_cast<Text*>(Helper::seekWidgetByName(totem, "Txt_Liveness"));
	char active_buff[50];
	int nActive = FACTION_MODEL::getInstance()->getActive();
	std::string sActive = Little::litles[1].name;
	sprintf(active_buff, "%s %d", sActive.c_str(), nActive);
	active->setString(active_buff);

	auto attackImg = dynamic_cast<ImageView*>(Helper::seekWidgetByName(totem, "Img_Attack"));
	attackImg->setTouchEnabled(true);
	attackImg->addTouchEventListener(CC_CALLBACK_2(FACTION_MAIN_VIEW::onClickAttackUp, this));
	auto attack = dynamic_cast<Text*>(Helper::seekWidgetByName(totem, "Txt_Attack_Key"));
	char attack_buff[50];
	int nAttack = FACTION_MODEL::getInstance()->getAttack();
	std::string sAttack = Little::litles[2].name;
	sprintf(attack_buff, "%s %d", sAttack.c_str(), nAttack);
	attack->setString(attack_buff);

	auto attack_value = dynamic_cast<Text*>(Helper::seekWidgetByName(totem, "Txt_Attack_Value"));
	
	auto defenseImg = dynamic_cast<ImageView*>(Helper::seekWidgetByName(totem, "Img_Defense"));
	defenseImg->setTouchEnabled(true);
	defenseImg->addTouchEventListener(CC_CALLBACK_2(FACTION_MAIN_VIEW::onClickDefenceUp, this));
	auto defence = dynamic_cast<Text*>(Helper::seekWidgetByName(totem, "Txt_Defense_Key"));
	char defence_buff[50];
	int nDefence = FACTION_MODEL::getInstance()->getDefense();
	std::string sDefence = Little::litles[3].name;
	sprintf(defence_buff, "%s %d", sDefence.c_str(), nDefence);
	defence->setString(defence_buff);

	auto defence_value = dynamic_cast<Text*>(Helper::seekWidgetByName(totem, "Txt_Defense_Value"));

	auto lifeImg = dynamic_cast<ImageView*>(Helper::seekWidgetByName(totem, "Img_Life"));
	lifeImg->setTouchEnabled(true);
	lifeImg->addTouchEventListener(CC_CALLBACK_2(FACTION_MAIN_VIEW::onClickLifeUp, this));
	auto life = dynamic_cast<Text*>(Helper::seekWidgetByName(totem, "Txt_Life_Key"));
	char life_buff[50];
	int nLife = FACTION_MODEL::getInstance()->getLife();
	std::string sLife = Little::litles[4].name;
	sprintf(life_buff, "%s %d", sLife.c_str(), nLife);
	life->setString(life_buff);

	auto life_value = dynamic_cast<Text*>(Helper::seekWidgetByName(totem, "Txt_Life_Value"));

	auto windImg = dynamic_cast<ImageView*>(Helper::seekWidgetByName(totem, "Img_Wind"));
	windImg->setTouchEnabled(true);
	windImg->addTouchEventListener(CC_CALLBACK_2(FACTION_MAIN_VIEW::onClickWindUp, this));
	auto wind = dynamic_cast<Text*>(Helper::seekWidgetByName(totem, "Txt_Wind_Key"));
	char wind_buff[50];
	int nWind = FACTION_MODEL::getInstance()->getWind();
	std::string sWind = Little::litles[5].name;
	sprintf(wind_buff, "%s %d", sWind.c_str(), nWind);
	wind->setString(wind_buff);

	auto wind_value = dynamic_cast<Text*>(Helper::seekWidgetByName(totem, "Txt_Wind_Value"));

	auto fireImg = dynamic_cast<ImageView*>(Helper::seekWidgetByName(totem, "Img_Fire"));
	fireImg->setTouchEnabled(true);
	fireImg->addTouchEventListener(CC_CALLBACK_2(FACTION_MAIN_VIEW::onClickFireUp, this));
	auto fire = dynamic_cast<Text*>(Helper::seekWidgetByName(totem, "Txt_Fire_Key"));
	char fire_buff[50];
	int nFire = FACTION_MODEL::getInstance()->getFire();
	std::string sFire = Little::litles[6].name;
	sprintf(fire_buff, "%s %d", sFire.c_str(),nFire);
	fire->setString(fire_buff);

	auto fire_value = dynamic_cast<Text*>(Helper::seekWidgetByName(totem, "Txt_Fire_Value"));

	auto thunderImg = dynamic_cast<ImageView*>(Helper::seekWidgetByName(totem, "Img_Thunder"));
	thunderImg->setTouchEnabled(true);
	thunderImg->addTouchEventListener(CC_CALLBACK_2(FACTION_MAIN_VIEW::onClickThunderUp, this));
	auto thunder = dynamic_cast<Text*>(Helper::seekWidgetByName(totem, "Txt_Thunder_Key"));
	char thunder_buff[50];
	int nThunder = FACTION_MODEL::getInstance()->getThunder();
	std::string sThunder = Little::litles[7].name;
	sprintf(thunder_buff, "%s %d", sThunder.c_str(), nThunder);
	thunder->setString(thunder_buff);

	auto thunder_value = dynamic_cast<Text*>(Helper::seekWidgetByName(totem, "Txt_Thunder_Value"));
	
}

void FACTION_MAIN_VIEW::onClickAttackUp(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	FACTION_MODEL::getInstance()->setCurTotemType(0);
	vector<uint64> para;
	para.push_back(0);
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_TOTEMUP, para);
}

void FACTION_MAIN_VIEW::onClickDefenceUp(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	FACTION_MODEL::getInstance()->setCurTotemType(1);
	vector<uint64> para;
	para.push_back(1);
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_TOTEMUP, para);
}

void FACTION_MAIN_VIEW::onClickLifeUp(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	FACTION_MODEL::getInstance()->setCurTotemType(2);
	vector<uint64> para;
	para.push_back(2);
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_TOTEMUP, para);
}

void FACTION_MAIN_VIEW::onClickWindUp(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	FACTION_MODEL::getInstance()->setCurTotemType(3);
	vector<uint64> para;
	para.push_back(3);
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_TOTEMUP, para);
}

void FACTION_MAIN_VIEW::onClickFireUp(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	FACTION_MODEL::getInstance()->setCurTotemType(4);
	vector<uint64> para;
	para.push_back(4);
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_TOTEMUP, para);
}

void FACTION_MAIN_VIEW::onClickThunderUp(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	FACTION_MODEL::getInstance()->setCurTotemType(5);
	vector<uint64> para;
	para.push_back(5);
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_TOTEMUP, para);
}

void FACTION_MAIN_VIEW::onCloseTotem(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	this->getChildByTag(127)->removeFromParent();

}

void FACTION_MAIN_VIEW::onClickMember(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	m_pMemberRoot = dynamic_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/guild_member.json"));
	addChild(m_pMemberRoot, 2, 128);

	vector<faction_member_data> list = FACTION_MODEL::getInstance()->getMembers();
	//for (auto& member:list)
	//{
	//	member->player_id;
	//	member->name;
	//	member->lv;
	//	member->job;
	//	member->fighting_capacity;

	//}

	//int nJob = 3;
	//int nPower = 2000;
	//for (int i = 0; i < 5;i++)
	//{
	//	faction_member_data* mb = new faction_member_data;
	//	mb->player_id = 10;
	//	mb->name = "Davie";
	//	mb->lv = 10;
	//	mb->job = 1;
	//	if (i<3)
	//		mb->fighting_capacity = ++nPower;
	//	else
	//		mb->fighting_capacity = --nPower;
	//	list.push_back(mb);
	//}
	sort(list.begin(), list.end(), [](faction_member_data m1, faction_member_data m2){
		return m1.fighting_capacity > m2.fighting_capacity;
	});
	//FACTION_MODEL::getInstance()->setMembers(list);

	auto scr = dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(m_pMemberRoot, "Scr_Members"));
	auto cursor = dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Cursor_1"));
	auto cursorShow = cursor->clone();
	cursorShow->setPosition( Vec2(0,800) );
	cursorShow->setName("Img_Cursor_Show");
	scr->addChild(cursorShow);

	auto para = LayoutParameter::create();
	auto mg = Margin(0,10,0,10);
	para->setMargin(mg);
	scr->getInnerContainer()->setLayoutParameter(para);

	int i = 0;
	for (auto& member:list)
	{
		member.player_id;
		member.name;
		member.lv;
		member.job;
		member.fighting_capacity;

		auto cell = dynamic_cast<ui::Layout*>(Helper::seekWidgetByName(m_pMemberRoot, "Pnl_Cell"));
		auto cellShow = cell->clone(); 
		auto tipTxt = dynamic_cast<Text*>(cellShow->getChildByName("Txt_Tip"));
		if (member.job == 3)
			tipTxt->setString(Little::litles[9].name.c_str());
		else if(member.job == 2)
			tipTxt->setString(Little::litles[10].name.c_str());
		else 
			tipTxt->setString("");

		auto nameTxt = dynamic_cast<Text*>(cellShow->getChildByName("Txt_Name"));
		auto lvTxt = dynamic_cast<Text*>(cellShow->getChildByName("Txt_Lv"));
		auto powerTxt = dynamic_cast<Text*>(cellShow->getChildByName("Txt_Power"));

		nameTxt->setString(member.name);

		char lv_buff[50];
		sprintf(lv_buff,"%d",member.lv);
		lvTxt->setString(lv_buff);

		Value power_buff(member.fighting_capacity);
		powerTxt->setString( power_buff.asString() );
		cellShow->setPosition( Vec2(0,220-10-40-40*i) );
		cellShow->setTag(member.player_id);
		cellShow->addTouchEventListener( this, toucheventselector(FACTION_MAIN_VIEW::onClickCell) );
		//auto cursor = cellShow->getChildByName("Img_Cursor");
		//cursor->setVisible(false);
		scr->addChild(cellShow);
		i++;

	}

	auto closeMember = dynamic_cast<Button*>(Helper::seekWidgetByName( m_pMemberRoot, "Btn_Close") );
	closeMember->setTouchEnabled(true);
	closeMember->addTouchEventListener( this, toucheventselector(FACTION_MAIN_VIEW::onCloseMember) );

	auto closeRejob = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pMemberRoot, "Btn_Close_Frame"));
	closeRejob->addTouchEventListener(this, toucheventselector(FACTION_MAIN_VIEW::onCloseFrame));

	auto imgRejob = dynamic_cast<ImageView*>( Helper::seekWidgetByName(m_pMemberRoot, "Img_Degree") );
	imgRejob->addTouchEventListener( this, toucheventselector(FACTION_MAIN_VIEW::onClickRejob) );
	imgRejob->setVisible(false);

	auto imgDonate = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Donate"));
	imgDonate->addTouchEventListener(this, toucheventselector(FACTION_MAIN_VIEW::onClickDonate));
	imgDonate->setVisible(false);

	auto imgExit = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Exit"));
	imgExit->addTouchEventListener(this, toucheventselector(FACTION_MAIN_VIEW::onClickExit));
	imgExit->setVisible(false);
}

void FACTION_MAIN_VIEW::onClickCell(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	auto imgDegree = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Degree"));
	imgDegree->setVisible(true);
	int job = FACTION_MODEL::getInstance()->getJob();
	if (job == 3)
		imgDegree->setVisible(true);
	else
		imgDegree->setVisible(false);

	auto imgDonate = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Donate"));
	imgDonate->setVisible(true);
	auto imgExit = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Exit"));
	imgExit->setVisible(true);

	auto member = (Layout*)pSender;
	int player_id = member->getTag();
	FACTION_MODEL::getInstance()->setCurSelectMemberId(player_id);
	Vec2 pos = member->getPosition();
	auto cursor = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Cursor_Show"));
	cursor->setVisible(true);
	cursor->setPosition(pos);

}

void FACTION_MAIN_VIEW::onClickRejob(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	int member_id = FACTION_MODEL::getInstance()->getCurSelectMemberId();
	if (member_id == -1)
		return;
	auto frame = dynamic_cast<Widget*>(Helper::seekWidgetByName(m_pMemberRoot, "Pnl_Frame"));
	frame->setVisible(true);
	m_pRejobRoot = dynamic_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/guild_rejob.json"));
	addChild(m_pRejobRoot, 2, 666);
	
	auto ckbHead = dynamic_cast<cocos2d::ui::CheckBox*>(Helper::seekWidgetByName(m_pRejobRoot, "Ckb_Head"));
	ckbHead->setSelectedState(true);
	ckbHead->addEventListener(CC_CALLBACK_2(FACTION_MAIN_VIEW::onSelectHead, this));

	auto ckbAssist = dynamic_cast<cocos2d::ui::CheckBox*>(Helper::seekWidgetByName(m_pRejobRoot, "Ckb_Assist"));
	ckbAssist->addEventListener(CC_CALLBACK_2(FACTION_MAIN_VIEW::onSelectAssist, this));

	auto ckbMember = dynamic_cast<cocos2d::ui::CheckBox*>(Helper::seekWidgetByName(m_pRejobRoot, "Ckb_Member"));
	ckbMember->addEventListener(CC_CALLBACK_2(FACTION_MAIN_VIEW::onSelectMember, this));

	auto confirm_rejob = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pRejobRoot, "Btn_Confirm"));
	confirm_rejob->addTouchEventListener( this, toucheventselector(FACTION_MAIN_VIEW::onClickConfirmRejob) );


}

void FACTION_MAIN_VIEW::onSelectHead(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type)
{
	if (type == CheckBox::EventType::SELECTED)
	{
		//auto ckbHead = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pRejobRoot, "Ckb_Head"));
		//ckbHead->setSelectedState(false);
		auto ckbAssist = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pRejobRoot, "Ckb_Assist"));
		ckbAssist->setSelectedState(false);
		auto ckbMember = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pRejobRoot, "Ckb_Member"));
		ckbMember->setSelectedState(false);

		FACTION_MODEL::getInstance()->setCurSelectJobId(3);
	}
	else
	{

	}

}

void FACTION_MAIN_VIEW::onSelectAssist(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type)
{
	if (type == CheckBox::EventType::SELECTED)
	{
		auto ckbHead = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pRejobRoot, "Ckb_Head"));
		ckbHead->setSelectedState(false);
		//auto ckbAssist = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pRejobRoot, "Ckb_Assist"));
		//ckbAssist->setSelectedState(false);
		auto ckbMember = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pRejobRoot, "Ckb_Member"));
		ckbMember->setSelectedState(false);
		FACTION_MODEL::getInstance()->setCurSelectJobId(2);

	}
	else
	{

	}

}

void FACTION_MAIN_VIEW::onSelectMember(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type)
{
	if (type == CheckBox::EventType::SELECTED)
	{
		auto ckbHead = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pRejobRoot, "Ckb_Head"));
		ckbHead->setSelectedState(false);
		auto ckbAssist = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pRejobRoot, "Ckb_Assist"));
		ckbAssist->setSelectedState(false);
		//auto ckbMember = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pRejobRoot, "Ckb_Member"));
		//ckbMember->setSelectedState(false);
		FACTION_MODEL::getInstance()->setCurSelectJobId(1);

	}
	else
	{

	}

}

void FACTION_MAIN_VIEW::onClickConfirmRejob(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type!=Widget::TouchEventType::ENDED)
		return;
	vector<uint64> para;
	para.clear();
	int target_id = FACTION_MODEL::getInstance()->getCurSelectMemberId();
	int job_id = FACTION_MODEL::getInstance()->getCurSelectJobId();
	para.push_back(target_id);
	para.push_back(job_id);

	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_REJOB, para);
	FACTION_MODEL::getInstance()->setCurSelectMemberId(-1);
	auto imgRejob = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Degree"));
	imgRejob->setVisible(false);
	auto imgDonate = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Donate"));
	imgDonate->setVisible(false);
	auto imgExit = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Exit"));
	imgExit->setVisible(false);
	auto cursor = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Cursor_Show"));
	cursor->setVisible(false);
	auto frame = dynamic_cast<Widget*>(Helper::seekWidgetByName(m_pMemberRoot, "Pnl_Frame"));
	frame->setVisible(false);
	removeChildByTag(666);
	removeChildByTag(668);
	removeChildByTag(680);

}

void FACTION_MAIN_VIEW::onClickDonate(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	int member_id = FACTION_MODEL::getInstance()->getCurSelectMemberId();
	if (member_id == -1)
		return;
	auto frame = dynamic_cast<Widget*>(Helper::seekWidgetByName(m_pMemberRoot, "Pnl_Frame"));
	frame->setVisible(true);
	m_pDonateRoot = dynamic_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/guild_donate.json"));
	addChild(m_pDonateRoot, 2, 668);

	auto ckbOne = dynamic_cast<cocos2d::ui::CheckBox*>(Helper::seekWidgetByName(m_pDonateRoot, "Ckb_One"));
	ckbOne->addEventListener(CC_CALLBACK_2(FACTION_MAIN_VIEW::onSelectOne, this));
	ckbOne->setSelectedState(true);

	auto ckbTwo = dynamic_cast<cocos2d::ui::CheckBox*>(Helper::seekWidgetByName(m_pDonateRoot, "Ckb_Two"));
	ckbTwo->addEventListener(CC_CALLBACK_2(FACTION_MAIN_VIEW::onSelectTwo, this));

	auto ckbFive = dynamic_cast<cocos2d::ui::CheckBox*>(Helper::seekWidgetByName(m_pDonateRoot, "Ckb_Five"));
	ckbFive->addEventListener(CC_CALLBACK_2(FACTION_MAIN_VIEW::onSelectFive, this));

	auto confirm_donate = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pDonateRoot, "Btn_Confirm"));
	confirm_donate->addTouchEventListener(this, toucheventselector(FACTION_MAIN_VIEW::onClickConfirmDonate));

}

void FACTION_MAIN_VIEW::onSelectOne(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type)
{
	if (type == CheckBox::EventType::SELECTED)
	{
		//auto ckbOne = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pDonateRoot, "Ckb_One"));
		//ckbOne->setSelectedState(false);
		auto ckbTwo = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pDonateRoot, "Ckb_Two"));
		ckbTwo->setSelectedState(false);
		auto ckbFive = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pDonateRoot, "Ckb_Five"));
		ckbFive->setSelectedState(false);
		FACTION_MODEL::getInstance()->setCurSelectDonateId(100);
	}
	else
	{

	}

}

void FACTION_MAIN_VIEW::onSelectTwo(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type)
{
	if (type == CheckBox::EventType::SELECTED)
	{
		auto ckbOne = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pDonateRoot, "Ckb_One"));
		ckbOne->setSelectedState(false);
		//auto ckbTwo = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pDonateRoot, "Ckb_Two"));
		//ckbTwo->setSelectedState(false);
		auto ckbFive = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pDonateRoot, "Ckb_Five"));
		ckbFive->setSelectedState(false);
		FACTION_MODEL::getInstance()->setCurSelectDonateId(200);

	}
	else
	{

	}

}

void FACTION_MAIN_VIEW::onSelectFive(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type)
{
	if (type == CheckBox::EventType::SELECTED)
	{
		auto ckbOne = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pDonateRoot, "Ckb_One"));
		ckbOne->setSelectedState(false);
		auto ckbTwo = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pDonateRoot, "Ckb_Two"));
		ckbTwo->setSelectedState(false);
		//auto ckbFive = dynamic_cast<CheckBox*>(Helper::seekWidgetByName(m_pDonateRoot, "Ckb_Five"));
		//ckbFive->setSelectedState(false);
		FACTION_MODEL::getInstance()->setCurSelectDonateId(500);

	}
	else
	{

	}

}

void FACTION_MAIN_VIEW::onClickConfirmDonate(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	vector<uint64> para;
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_DONATE,para);
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FACTION_SEND_REJOB, nullptr);
	FACTION_MODEL::getInstance()->setCurSelectMemberId(-1);
	auto imgRejob = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Degree"));
	imgRejob->setVisible(false);
	auto imgDonate = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Donate"));
	imgDonate->setVisible(false);
	auto imgExit = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Exit"));
	imgExit->setVisible(false);
	auto cursor = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Cursor_Show"));
	cursor->setVisible(false);
	auto frame = dynamic_cast<Widget*>(Helper::seekWidgetByName(m_pMemberRoot, "Pnl_Frame"));
	frame->setVisible(false);
	removeChildByTag(666);
	removeChildByTag(668);
	removeChildByTag(680);

}

void FACTION_MAIN_VIEW::onClickExit(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	int member_id = FACTION_MODEL::getInstance()->getCurSelectMemberId();
	if (member_id == -1)
		return;
	auto frame = dynamic_cast<Widget*>(Helper::seekWidgetByName(m_pMemberRoot, "Pnl_Frame"));
	frame->setVisible(true);
	auto exit = dynamic_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/guild_exit.json"));
	addChild(exit, 2, 680);

	auto confirm = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(exit, "Btn_Confirm"));
	confirm->addTouchEventListener(CC_CALLBACK_2(FACTION_MAIN_VIEW::onClickKick, this));
}

void FACTION_MAIN_VIEW::onClickKick(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	vector<uint64> para;
	para.clear();
	int target_id = FACTION_MODEL::getInstance()->getCurSelectMemberId();
	para.push_back(target_id);
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_KICK, para);
	FACTION_MODEL::getInstance()->setCurSelectMemberId(-1);
	auto imgRejob = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Degree"));
	imgRejob->setVisible(false);
	auto imgDonate = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Donate"));
	imgDonate->setVisible(false);
	auto imgExit = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Exit"));
	imgExit->setVisible(false);
	auto cursor = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pMemberRoot, "Img_Cursor_Show"));
	cursor->setVisible(false);
	auto frame = dynamic_cast<Widget*>(Helper::seekWidgetByName(m_pMemberRoot, "Pnl_Frame"));
	frame->setVisible(false);
	removeChildByTag(666);
	removeChildByTag(668);
	removeChildByTag(680);

}

void FACTION_MAIN_VIEW::onCloseFrame(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	auto frame = dynamic_cast<Widget*>(Helper::seekWidgetByName(m_pMemberRoot, "Pnl_Frame"));
	frame->setVisible(false);
	removeChildByTag(666);
	removeChildByTag(668);
	removeChildByTag(680);

}

void FACTION_MAIN_VIEW::onCloseMember(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	this->getChildByTag(128)->removeFromParent();

}

FACTION_MAIN_VIEW::FactionMainLayer()
{

}

FACTION_MAIN_VIEW::~FactionMainLayer()
{
	m_pRoot = nullptr;
	m_pBossRoot = nullptr;
	m_pWorshipRoot = nullptr;
	m_pMemberRoot = nullptr;
	m_pRejobRoot = nullptr;
	m_pDonateRoot = nullptr;
	m_pMineRoot = nullptr;
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_REFRESH_FACTION);
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_REFRESH_BOARD);

}

void FACTION_MAIN_VIEW::onEnter()
{
	Layer::onEnter();


}

void FACTION_MAIN_VIEW::onExit()
{
	Layer::onExit();

}

void FACTION_MAIN_VIEW::eventRefresh(EventCustom* evt)
{
	if (!this->m_pRoot)
		return;
	auto data = FACTION_MODEL::getInstance();

	std::string name = data->getName();
	log("name:%s", name.c_str());

	int	num  = data->getNum();
	char num_buff[50];
	sprintf(num_buff, "%d/30", num);
	log("num:%d", num);

	int	level = data->getLevel();
	char level_buff[50];
	sprintf(level_buff, "%d", level);
	log("level:%d", level);

	int exp = data->getExp();
	log("exp:%d", exp);

	std::string notice(data->getNotice());
	auto nameTxt  = dynamic_cast<Text*>(Helper::seekWidgetByName( this->m_pRoot, "Txt_Name_Value")  );
	if (nameTxt)
	{
		nameTxt->setString(name.c_str());
		nameTxt->enableGlow(Color4B(128,128,0,255));
		//nameTxt->enableOutline(Color4B(255,0,0,255),2);
		//nameTxt->enableShadow(Color4B(0,0,255,255),Size(2,-2),0);
	}

	auto numTxt = dynamic_cast<Text*>(Helper::seekWidgetByName(this->m_pRoot, "Txt_Count_Value"));
	if (numTxt)
	{
		numTxt->setString(num_buff);
		//numTxt->enableGlow(Color4B(255, 0, 0, 255));
		numTxt->enableOutline(Color4B(128, 0, 128, 255));
		//numTxt->enableShadow(Color4B(0, 0, 255, 255), Size(2, -2), 0);
	}

	auto levelTxt = dynamic_cast<Text*>(Helper::seekWidgetByName(this->m_pRoot, "Txt_Level_Value"));
	if (levelTxt)
	{
		levelTxt->setString(level_buff);
		//levelTxt->enableGlow(Color4B(255, 0, 0, 255));
		//levelTxt->enableOutline(Color4B(255, 0, 0, 255), 2);
		levelTxt->enableShadow(Color4B(0, 128, 128, 255), Size(2, -2), 1);
	}

	auto bar = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(this->m_pRoot, "Prb_Exp"));
	bar->setPercent( (float)exp / 100);

	auto box = (BoardEditBox*)(this->getChildByName("Board"));
	box->setContent(notice);
	
	int curTime = FACTION_BOSS_MODEL::getInstance()->getCurTimes();
	int totalTime = FACTION_BOSS_MODEL::getInstance()->getTotalTimes();
	auto txtBoss = dynamic_cast<Text*>(Helper::seekWidgetByName(this->m_pRoot, "Txt_Boss_Value"));
	char timeBuff[50];
	sprintf(timeBuff, "%d/%d", curTime, totalTime);
	txtBoss->setString(timeBuff);

	int curWorshipTime = FACTION_MODEL::getInstance()->getWorshipCurTime();
	int totalWorshipTime = FACTION_MODEL::getInstance()->getWorshipTotalTime();
	auto txtWorship = dynamic_cast<Text*>(Helper::seekWidgetByName(this->m_pRoot, "Txt_Worship_Value"));
	char worshipTimeBuff[50];
	sprintf(worshipTimeBuff, "%d/%d", curWorshipTime, totalWorshipTime);
	txtWorship->setString(worshipTimeBuff);

	int curDigTime = FACTION_MODEL::getInstance()->getDigCurTime();
	int totalDigTime = FACTION_MODEL::getInstance()->getDigTotalTime();
	auto txtDig = dynamic_cast<Text*>(Helper::seekWidgetByName(this->m_pRoot, "Txt_Mine_Value"));
	char digTimeBuff[50];
	sprintf(digTimeBuff, "%d/%d", curDigTime, totalDigTime);
	txtDig->setString(digTimeBuff);

}

void FACTION_MAIN_VIEW::eventRefreshBoard(EventCustom* evt)
{
	auto box = (BoardEditBox*)(this->getChildByName("Board"));
	box->setContent(FACTION_MODEL::getInstance()->getNotice());
}

void FACTION_APPLY_VIEW::eventCallback()
{
	//Layer::removeFromParent();
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REOPEN_FACTION, nullptr);

}

void FACTION_APPLY_VIEW::onClickButtonJoin(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;

}

void FACTION_APPLY_VIEW::onClickButtonSearch(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FACTION_SEND_SEARCH, nullptr);

	std::vector<uint64> para;
	auto box = (SearchEditBox*)this->getChildByName("searchbox");
	auto name = box->getContent();
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_SEARCH, para,name.c_str() );

}

void FACTION_APPLY_VIEW::onClickButtonOpenFrame(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	m_pFrame->setVisible(true);

	auto condition = dynamic_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/guild_create_c.json"));
	addChild(condition,2,234);

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	auto player = (Game_Data::Player*)CHARACTER_MGR::instance()->get_character(player_id);

	int curlevel = player->get_character_level();
	int curcoin = player->get_gold();
	int curtoken = player->get_token();

	//FACTION_CONDITION_MODEL cur_condition = FACTION_CONTROLLER::getInstance()->getCurrentCondition();
	//FACTION_CONDITION_MODEL needed_condition = FACTION_CONTROLLER::getInstance()->getNeededCondition();
	int neededlevel = FACTION_MODEL::getInstance()->getLevelLimit();
	int neededcoin = FACTION_MODEL::getInstance()->getCoin();
	int neededtoken = FACTION_MODEL::getInstance()->getToken();

	char level_buff[40];
	sprintf(level_buff, "%d/%d", curlevel, neededlevel);
	auto level = dynamic_cast<Text*>( Helper::seekWidgetByName(condition, "Txt_Level_Value") );
	level->setString(level_buff);

	char coin_buff[40];
	sprintf(coin_buff, "%d/%d", curcoin, neededcoin);
	auto coin  = dynamic_cast<Text*>( Helper::seekWidgetByName(condition, "Txt_Coin_Value" ) );
	coin->setString(coin_buff);

	char token_buff[40];
	sprintf(token_buff, "%d/%d", curtoken, neededtoken);
	auto token = dynamic_cast<Text*>( Helper::seekWidgetByName(condition, "Txt_Token_Value") );
	token->setString(token_buff);

	auto condition_confirm = dynamic_cast<Widget*>(Helper::seekWidgetByName(condition, "Btn_Condition_Confirm"));
	condition_confirm->addTouchEventListener(this, toucheventselector(FACTION_APPLY_VIEW::onClickButtonConditionConfirm));
	auto isCan = FACTION_CONTROLLER::getInstance()->isCanCreate();
	isCan = true;//for test
	if (!isCan)
		condition_confirm->setTouchEnabled(false);
	else 
		condition_confirm->setTouchEnabled(true);

	auto condition_cancel = dynamic_cast<Widget*>(Helper::seekWidgetByName(condition, "Btn_Condition_Cancel"));
	condition_cancel->addTouchEventListener(this, toucheventselector(FACTION_APPLY_VIEW::onClickButtonConditionCancel));

}

void FACTION_APPLY_VIEW::onClickButtonCloseFrame(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	//m_pFrame->removeChildByTag(123);
	m_pFrame->setVisible(false);
	removeChildByTag(234);
	removeChildByTag(235);
}

void FACTION_APPLY_VIEW::onClickButtonConditionConfirm(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	removeChildByTag(234);
	return;

	auto rename = dynamic_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/guild_create_r.json"));
	addChild(rename, 2, 235);

	auto pnl = dynamic_cast<Layout*>(Helper::seekWidgetByName(rename, "Pnl_Create_Rename"));
	auto input = RenameEditBox::create();
	input->SetPositionAndMaxLength(-400,100,10);
	pnl->addChild(input, 1,666);

	auto rename_confirm = dynamic_cast<Widget*>(Helper::seekWidgetByName(rename, "Btn_Rename_Confirm"));
	rename_confirm->addTouchEventListener(this, toucheventselector(FACTION_APPLY_VIEW::onClickButtonRenameConfirm));

}

void FACTION_APPLY_VIEW::onClickButtonConditionCancel(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	m_pFrame->setVisible(false);
	removeChildByTag(234);
}

void FACTION_APPLY_VIEW::onClickButtonRenameConfirm(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	m_pFrame->setVisible(false);
	auto rename = (Widget*)( this->getChildByTag(235) );
	auto pnl = dynamic_cast<Layout*>(Helper::seekWidgetByName(rename,"Pnl_Create_Rename"));
	auto box = (RenameEditBox*)( pnl->getChildByTag(666) );
	std::string name = box->getContent();
	FACTION_MODEL::getInstance()->setName(name);
	removeChildByTag(235);

	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FACTION_CREATE_SUCCESS,nullptr);
	vector<uint64> para;
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_CREATE, para);
	//Game_Logic::Game_Content_Interface::instance()->exec_interface( EVENT_FACTION_SEND_JOIN, para,name.c_str() );
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FACTION_SEND_CREATE, nullptr);

}

void FACTION_APPLY_VIEW::onEnter()
{
	Layer::onEnter();
}

void FACTION_APPLY_VIEW::onExit()
{
	Layer::onExit();
}

bool FACTION_APPLY_VIEW::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		auto editor = SearchEditBox::create();
		editor->init();
		editor->SetPositionAndMaxLength(-280, 125, 10);
		addChild(editor, 1,"searchbox");

		m_pApplyRoot = dynamic_cast<Widget*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/guild_apply.json"));
		CC_BREAK_IF(!m_pApplyRoot);
		addChild(m_pApplyRoot);

		m_pFrame = dynamic_cast<Widget*>(Helper::seekWidgetByName(m_pApplyRoot, "Pnl_Frame"));
		m_pFrame->setVisible(false);

		auto buttonCloseFrame = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pApplyRoot, "Btn_Close_Frame"));
		CC_BREAK_IF(!buttonCloseFrame);
		buttonCloseFrame->addTouchEventListener( this, toucheventselector(FactionApplyLayer::onClickButtonCloseFrame) );

		auto buttonSearch = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pApplyRoot, "Btn_Search") );
		CC_BREAK_IF(!buttonSearch);
		buttonSearch->addTouchEventListener( this, toucheventselector(FactionApplyLayer::onClickButtonSearch) );
		
		auto buttonCreate = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pApplyRoot, "Btn_Create"));
		CC_BREAK_IF(!buttonCreate);
		//buttonCreate->addTouchEventListener(this, toucheventselector(FactionApplyLayer::onClickButtonOpenFrame));

		//Director::getInstance()->getEventDispatcher()->addCustomEventListener(event_faction_create_failed, CC_CALLBACK_1(FACTION_APPLY_VIEW::event_create_faction_success, this));

		bRet = true;

	} while (false);

	return bRet;

}

//controller
FACTION_CONTROLLER* FACTION_CONTROLLER::getInstance()
{
	static FACTION_CONTROLLER _instance;
	return &_instance;
}

bool FACTION_CONTROLLER::init()
{
	bool bRet = false;

	do
	{

	} while (false);

	bRet = true;

	return bRet;

}

bool FACTION_CONTROLLER::isCanCreate()
{
	auto cur = getCurrentCondition();
	//if (cur==NULL)
		//return false;
	auto needed = getNeededCondition();

	if ( cur.getLevel() < needed.getLevel() )
		return false;
	if ( cur.getCoin() < needed.getCoin() )
		return false;
	if ( cur.getToken() < needed.getToken() )
		return false;

	return true;

}

FACTION_CONDITION_MODEL FACTION_CONTROLLER::getCurrentCondition()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	auto player = (Game_Data::Player*)CHARACTER_MGR::instance()->get_character(player_id);
	int level = player->get_character_level();
	int coin = player->get_gold();
	int token = player->get_token();


	FACTION_CONDITION_MODEL current_condition;
	current_condition.setLevel(level);
	current_condition.setCoin(coin);
	current_condition.setToken(token);
	
	return current_condition;

}

FACTION_CONDITION_MODEL FACTION_CONTROLLER::getNeededCondition()
{
	FACTION_CONDITION_MODEL current_condition;
	current_condition.setLevel(30);
	current_condition.setCoin(100000);
	current_condition.setToken(300);

	return current_condition;
}

//net
bool FACTION_NET::send_get_faction_data(Game_Logic::Game_Interface& gm_interface)
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;

	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	body_ms << C2S_GET_FACTION_DATA;
	body_ms << player_id;

	CNetManager::GetMe()->send_msg(body_ms);
}

bool FACTION_NET::on_get_faction_data(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	faction_data_DB _db;
	
	body_ms >> _db.faction_level;
	body_ms >> _db.curr_exp;
	body_ms >> _db.msg_board;
	body_ms >> _db.active_num;

	FACTION_MODEL::getInstance()->faction_db = _db;
	FACTION_MODEL::getInstance()->setLevel(_db.faction_level);
	FACTION_MODEL::getInstance()->setExp(_db.curr_exp);
	FACTION_MODEL::getInstance()->setNotice(_db.msg_board);
	FACTION_MODEL::getInstance()->setActive(_db.active_num);
	vector<faction_member_data> para;
	para.clear();
	for (int i = 0; i < FACTION_TOTEMS_MAX; i++)
	{
		int totem_index;
		body_ms >> totem_index;

	}
	int len;
	body_ms >> len;
	FACTION_MODEL::getInstance()->setNum(len);
	for (int i = 0; i < len; i++)
	{
		faction_member_data member_data;
		//std::string member_name;
		body_ms >> member_data.fighting_capacity;
		body_ms >> member_data.job;
		body_ms >> member_data.lv;
		body_ms >> member_data.player_id;
		body_ms >> member_data.name;
		para.push_back(member_data);

	}
	FACTION_MODEL::getInstance()->setMembers(para);
	auto config = FACTION_CONFIG_MGR::instance()->get_faction_data_by_lv(_db.faction_level);
	//FACTION_BOSS_MODEL::getInstance()->setCurTimes(config->boss_num);
	FACTION_BOSS_MODEL::getInstance()->setTotalTimes(config->boss_num);
	//FACTION_MODEL::getInstance()->setWorshipCurTime(config->worship_num);
	FACTION_MODEL::getInstance()->setWorshipTotalTime(config->worship_num);
	FACTION_MODEL::getInstance()->setDigTotalTime(config->digging_num);

	FACTION_MODEL::getInstance()->setAttack(config->totoems_num[TOTMES_ATTACK]);
	FACTION_MODEL::getInstance()->setDefense(config->totoems_num[TOTMES_DEFENSE]);
	FACTION_MODEL::getInstance()->setLife(config->totoems_num[TOTMES_LIFE]);
	FACTION_MODEL::getInstance()->setWind(config->totoems_num[TOTMES_WIND]);
	FACTION_MODEL::getInstance()->setFire(config->totoems_num[TOTMES_FIRE]);
	FACTION_MODEL::getInstance()->setThunder(config->totoems_num[TOTMES_THUNDER]);

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_FACTION,nullptr);

	return true;

}

bool FACTION_NET::send_faction_search(Game_Logic::Game_Interface& gm_interface)
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;

	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	//std::string name("LostTemple");
	//std::string name = SearchEditBox::getContent();
	auto name = gm_interface.get_keyword();

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	//body_ms << C2S_CREATE_FACTION;
	//body_ms << player_id;
	//body_ms << name;

	CNetManager::GetMe()->send_msg(body_ms);
	return true;

}

bool FACTION_NET::on_faction_search(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int faction_level;
	int join_fighting_capacity;

	string faction_name;
	int faction_member_len;
	string chairman;
	body_ms >> faction_level;
	body_ms >> join_fighting_capacity;
	body_ms >> faction_name;
	body_ms >> faction_member_len;
	body_ms >> chairman;

	return true;
}

bool FACTION_NET::send_faction_create(Game_Logic::Game_Interface& gm_interface)
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;

	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	//std::string name("LostTemple");
	std::string name = FACTION_MODEL::getInstance()->getName();

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	body_ms << C2S_CREATE_FACTION;
	body_ms << player_id;
	body_ms << name;

	CNetManager::GetMe()->send_msg(body_ms);
	return true;

}

bool FACTION_NET::on_faction_create(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int			faction_id;
	int			faction_job;
	std::string	name;
	int			contribute_num;
	int			cur_digging_num;
	int			cur_worship_num;
	int			cur_boss_num;

	body_ms >> faction_id;
	body_ms >> faction_job;
	body_ms >> name;
	body_ms >> contribute_num;
	body_ms >> cur_digging_num;
	body_ms >> cur_worship_num;
	body_ms >> cur_boss_num;

	bool isSuccess = false;
	if (faction_id < 0)
		isSuccess = false;
	else
		isSuccess = true;
	if (isSuccess)
	{
		vector<uint64> para;
		//Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_FACTION_SEND_GET_DATA, para);

		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FACTION_CREATE_SUCCESS,nullptr);
	}
	else
	{

	}
	return true;
}

bool FACTION_NET::send_faction_join(Game_Logic::Game_Interface& gm_interface)
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;

	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	std::vector<uint64> para;
	//gm_interface.get_para(para);

	std::string name( gm_interface.get_keyword() );

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	body_ms << C2S_JOIN_FACTION;
	body_ms << player_id;
	body_ms << name;

	CNetManager::GetMe()->send_msg(body_ms);
	return true;
}

bool FACTION_NET::on_faction_join(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int			result;
	int		faction_id;
	int			faction_job;
	std::string name;
	int			contribute_num;
	int			cur_digging_num;
	int			cur_worship_num;
	int			cur_boss_num;

	body_ms >> result;
	body_ms >> faction_id;
	body_ms >> faction_job;//1成员 2副帮主 3 帮主
	body_ms >> name;
	body_ms >> contribute_num;
	body_ms >> cur_digging_num;
	body_ms >> cur_worship_num;
	body_ms >> cur_boss_num;

	return true;
}

bool FACTION_NET::send_faction_kick_member(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	int player_id;
	int member_id = para[0];
	player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	body_ms << C2S_KICK_MEMBER_FACTION;
	body_ms << player_id;
	body_ms << member_id;

	CNetManager::GetMe()->send_msg(body_ms);

	return true;

}

bool FACTION_NET::on_faction_kick_member(Game_Logic::Game_Interface& gm_interface)
{
	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));
	int player_id;
	int member_id;
	int result;

	body_ms >> player_id;
	body_ms >> member_id;
	body_ms >> result;

	return true;

}

bool FACTION_NET::send_faction_set_job(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	int player_id;
	int member_id = para[0];
	int job = para[1];

	player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;

	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;


	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	body_ms << C2S_SET_JOB_FACTION;
	body_ms << player_id;
	body_ms << member_id;
	body_ms << job;

	CNetManager::GetMe()->send_msg(body_ms);
	return true;


}

bool FACTION_NET::on_faction_set_job(Game_Logic::Game_Interface& gm_interface)
{

	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	//body_ms >> C2S_SET_JOB_FACTION;
	int		player_id;
	int		member_id;
	int		job;
	int		result;

	body_ms >> player_id;
	body_ms >> member_id;
	body_ms >> job;
	body_ms >> result;
	return true;


}

bool FACTION_NET::send_faction_set_notice(Game_Logic::Game_Interface& gm_interface)
{
	int player_id;
	std::string notice = FACTION_MODEL::getInstance()->getNotice();
	//std::string notice("DeepLostInMyMind");

	player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	body_ms << C2S_SET_MSG_BOARD_FACTION;
	body_ms << player_id;
	body_ms << notice;

	CNetManager::GetMe()->send_msg(body_ms);
	return true;

}

bool FACTION_NET::on_faction_set_notice(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	//body_ms >> C2S_SET_JOB_FACTION;
	int		result;

	body_ms >> result;
	if (result != 1)
		;
	else
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_BOARD, nullptr);

	return true;
}

bool FACTION_NET::send_faction_join_limit(Game_Logic::Game_Interface& gm_interface)
{
	int player_id;
	int capacity;

	player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;
	capacity = player->get_fighting_capacity();

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	body_ms << C2S_JOIN_FACTION;
	body_ms << player_id;
	body_ms << capacity;

	CNetManager::GetMe()->send_msg(body_ms);

	return true;

}

bool FACTION_NET::on_faction_join_limit(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	int		result;
	int		fighting_capacity;
	body_ms >> result;
	body_ms >> fighting_capacity;

	return true;

}

bool FACTION_NET::send_faction_totems_up(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	int player_id;
	int totmes_type;
	gm_interface.get_para(para);
	totmes_type = para[0];
	player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	body_ms << C2S_TOTEMS_UP_FACTION;
	body_ms << player_id;
	body_ms << totmes_type;

	CNetManager::GetMe()->send_msg(body_ms);

	return true;
}

bool FACTION_NET::on_faction_totems_up(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	int		result;
	int		totmes_type;

	body_ms >> result;
	body_ms >> totmes_type;
	return true;
}

bool FACTION_NET::send_faction_member_donation(Game_Logic::Game_Interface& gm_interface)
{
	return false;
}

bool FACTION_NET::send_faction_member_digging(Game_Logic::Game_Interface& gm_interface)
{
	int player_id;

	player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	body_ms << C2S_FACTION_DIGGIN;
	body_ms << player_id;

	CNetManager::GetMe()->send_msg(body_ms);
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_DIG, nullptr);
	return true;
}

bool FACTION_NET::on_faction_member_digging(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	char body[256] = { 0 };
	int			result;
	int			contribute_num;

	body_ms >> result;
	body_ms >> contribute_num;
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_DIG, nullptr);

	return true;

}

bool FACTION_NET::send_faction_member_worship(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	int player_id;
	int target_id = para[0];
	player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	body_ms << C2S_FACTION_WORSHIP;
	body_ms << player_id;
	body_ms << target_id;

	CNetManager::GetMe()->send_msg(body_ms);

	return true;
}

bool FACTION_NET::on_faction_member_worship(Game_Logic::Game_Interface& gm_interface)
{
	char body[256] = { 0 };
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int		   result;
	int		   contribute_num;

	body_ms >> result;
	body_ms >> contribute_num;

	int time = FACTION_MODEL::getInstance()->getWorshipCurTime();
	time--;
	FACTION_MODEL::getInstance()->setWorshipCurTime(time);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_WORSHIP, nullptr);
	return true;
}

bool FACTION_NET::send_faction_member_buy_item(Game_Logic::Game_Interface& gm_interface)
{
	return false;
}

bool FACTION_NET::send_faction_member_dekaron_boos(Game_Logic::Game_Interface& gm_interface)
{
	int player_id;
	int boss_id;
	boss_id = FACTION_BOSS_MODEL::getInstance()->getBossId();
	player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	body_ms << C2S_FACTION_DEKARON_BOSS;
	body_ms << player_id;
	body_ms << boss_id;
	CNetManager::GetMe()->send_msg(body_ms);

	return true;
}

bool FACTION_NET::on_faction_member_dekaron_boos(Game_Logic::Game_Interface& gm_interface)
{
	char body[256] = { 0 };
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int		   result;
	int		   boss_id;

	body_ms >> result;
	body_ms >> boss_id;

	int time = FACTION_BOSS_MODEL::getInstance()->getCurTimes();
	time--;
	FACTION_BOSS_MODEL::getInstance()->setCurTimes(time);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_BOSS, nullptr);

	if (result == 0)
		;
	else
	{
		//enterScene
	}
	return true;
}

bool FACTION_NET::send_faction_member_kill_boos(Game_Logic::Game_Interface& gm_interface)
{
	int player_id;
	int boss_id;
	player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	body_ms << C2S_FACTION_DEKARON_BOSS;
	body_ms << player_id;
	body_ms << boss_id;

	CNetManager::GetMe()->send_msg(body_ms);

	return true;

}

bool FACTION_NET::on_faction_member_kill_boos(Game_Logic::Game_Interface& gm_interface)
{
	char body[256] = { 0 };
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int		   result;
	int        contribute_num;
	body_ms >> result;
	body_ms >> contribute_num;
	return true;
}

bool FACTION_NET::send_faction_set_msg_board(Game_Logic::Game_Interface& gm_interface)
{
	return false;

}

FACTION_NET* FACTION_NET::getInstance()
{
	static FACTION_NET _instance;
	return &_instance;
}

bool FACTION_NET::init()
{
	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_SEND_SEARCH, CC_CALLBACK_1( FACTION_NET::send_faction_search, FACTION_NET::getInstance() ) );
	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_ON_SEARCH, CC_CALLBACK_1( FACTION_NET::on_faction_search, FACTION_NET::getInstance() ) );

	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_SEND_LIMIT, CC_CALLBACK_1( FACTION_NET::send_faction_join_limit, FACTION_NET::getInstance() ) );
	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_ON_LIMIT, CC_CALLBACK_1( FACTION_NET::on_faction_join_limit, FACTION_NET::getInstance() ) );

	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_SEND_CREATE, CC_CALLBACK_1( FACTION_NET::send_faction_create, FACTION_NET::getInstance() ) );
	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_ON_CREATE, CC_CALLBACK_1( FACTION_NET::on_faction_create, FACTION_NET::getInstance() ) );

	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_SEND_JOIN, CC_CALLBACK_1( FACTION_NET::send_faction_join, FACTION_NET::getInstance() ) );
	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_ON_JOIN, CC_CALLBACK_1( FACTION_NET::on_faction_join, FACTION_NET::getInstance() ) );

	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_SEND_RENOTICE, CC_CALLBACK_1( FACTION_NET::send_faction_set_notice, FACTION_NET::getInstance() ) );
	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_ON_RENOTICE, CC_CALLBACK_1( FACTION_NET::on_faction_set_notice, FACTION_NET::getInstance() ) );

	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_SEND_WISH, CC_CALLBACK_1( FACTION_NET::send_faction_set_notice, FACTION_NET::getInstance() ) );
	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_ON_WISH, CC_CALLBACK_1( FACTION_NET::on_faction_set_notice, FACTION_NET::getInstance() ) );

	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_SEND_CHALLENGE, CC_CALLBACK_1( FACTION_NET::send_faction_member_dekaron_boos, FACTION_NET::getInstance() ) );
	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_ON_CHALLENGE, CC_CALLBACK_1( FACTION_NET::on_faction_member_dekaron_boos, FACTION_NET::getInstance() ) );

	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_SEND_REJOB, CC_CALLBACK_1( FACTION_NET::send_faction_set_job, FACTION_NET::getInstance() ) );
	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_ON_REJOB, CC_CALLBACK_1( FACTION_NET::on_faction_set_job, FACTION_NET::getInstance() ) );

	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_SEND_DIG, CC_CALLBACK_1( FACTION_NET::send_faction_member_digging, FACTION_NET::getInstance() ) );
	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_ON_DIG, CC_CALLBACK_1( FACTION_NET::on_faction_member_digging, FACTION_NET::getInstance() ) );

	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_SEND_CHALLENGE, CC_CALLBACK_1( FACTION_NET::send_faction_member_dekaron_boos, FACTION_NET::getInstance() ) );
	//Director::getInstance()->getEventDispatcher()->addCustomEventListener( EVENT_FACTION_ON_CHALLENGE, CC_CALLBACK_1( FACTION_NET::on_faction_member_dekaron_boos, FACTION_NET::getInstance() ) );

	return true;

}