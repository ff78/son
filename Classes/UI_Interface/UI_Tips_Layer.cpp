#include "UI_Tips_Layer.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Common/GameDefine.h"
#include "Common/Utils.h"
//#include "Runtime.h"
//#include "Game_Utils.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Game_Interface/game_content_interface.h"
#include "Play_System/Instance_Data_Mgr.h"

#include "Common/GameMacro.h"
#include "Character_System/Player_Msg_Proc_Cl.h"
#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Player_Config_Data.h"
#include "Character_System/Character_Mgr.h"
//#include "GameUI_Layer.h"
//USING_NS_CC_EXT;
USING_NS_CC;
using namespace Game_Data;
using namespace ui;
UI_Tips_Layer::UI_Tips_Layer(void)
	:m_mTimeLeft(NULL),
	count_down_time_(-1)//,
	//m_lab_confirm_time(NULL)

{
}


UI_Tips_Layer::~UI_Tips_Layer(void)
{
}

bool UI_Tips_Layer::init()
{

	if( !cocos2d::Layer::init() )
	{
		return false;
	}

	cocos2d::ui::Widget* m_pTipsWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Tips/Tips.ExportJson");
	addChild(m_pTipsWidget);
	m_img_root_dlg=dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pTipsWidget,"img_root_back"));

	const char* pzName = nullptr;
	//大侠出师不利
	//cocos2d::ui::Text* lab_role_dead = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pTipsWidget,"lab_dead_info"));
	//pzName = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_ROLE_DEAD);
	//lab_role_dead->setString(pzName);


	//搜集更强的装备与心法等来强化自己
	// cocos2d::ui::Text *fight_info=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pTipsWidget,"fight_info"));
	// const char* textfight=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(FIGHT_FAIL_TIPS);
	 //fight_info->setString(textfight);



	//倒计时数字
	m_mTimeLeft = dynamic_cast<cocos2d::ui::TextAtlas*>(Helper::seekWidgetByName(m_pTipsWidget,"number_time"));
	count_down_time_ = COUNT_DOWN_TIME_MAX;
	m_lab_confirm_time=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pTipsWidget,"lab_confirm_time"));
	set_count_time_down(count_down_time_);

	//秒后副本失败
	//cocos2d::ui::Text* lab_time_count = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pTipsWidget,"lab_time_count"));
	//pzName = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_TIME_COUNT);
	//lab_time_count->setString(pzName);

	/*
	//换人字体
	cocos2d::ui::Text* lab_change_role = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pTipsWidget,"lab_change_role"));
	pzName = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_CHANGE_ROLE);
	lab_change_role->setString(pzName);
	*/

	//复活字体
	cocos2d::ui::Text* lab_recovery = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pTipsWidget,"lab_recovery"));
	pzName = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_RECOVERY);
	lab_recovery->setString(pzName);

	//复活搜需要的元宝
	cocos2d::ui::Text* lab_yuanbao_count=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pTipsWidget,"lab_expense_count"));
	char tempcount[32]={0};
	SPRINTF(tempcount,"%d",PLAYER_REVIVE_COST);
	lab_yuanbao_count->setString(tempcount);


	//副本即将结束
	 cocos2d::ui::Text *instance_end=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pTipsWidget,"lab_failing"));
	 const char* textfight=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(INSTANCE_WILL_END);
	instance_end->setString(textfight);




	//放弃字体
	cocos2d::ui::Text* lab_give_up = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pTipsWidget,"lab_give_up"));
	pzName = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(FIGHT_EXIT_INSTANCE);
	lab_give_up->setString(pzName);

	/*
	//换人按钮
	m_btn_change_role = static_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pTipsWidget,"btn_change_role"));
	m_btn_change_role->addTouchEventListener(this, toucheventselector(UI_Tips_Layer::buttonChangeRoleCallback));
    m_btn_change_role->setTouchEnabled(false);
	*/

	//复活按钮
	m_btn_recovery = static_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pTipsWidget,"btn_recovery"));
	m_btn_recovery->addTouchEventListener(this, toucheventselector(UI_Tips_Layer::buttonRecoveryCallback));
	m_btn_recovery->setTouchEnabled(false);

	//放弃按钮
	m_btn_give_up = static_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pTipsWidget,"btn_give_up"));
	m_btn_give_up->addTouchEventListener(this, toucheventselector(UI_Tips_Layer::buttonGiveUpCallback));
    m_btn_give_up->setTouchEnabled(false);

	/*****************************复活系统***************************************/
	m_img_confirm_dlg=dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pTipsWidget,"img_root_back_confirm"));
	m_img_confirm_dlg->setVisible(false);

	m_lab_fight_again=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pTipsWidget,"lab_fight_again"));
	const char* fightagaintext=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_FIGHT_AGAIN);
	m_lab_fight_again->setText(fightagaintext);

	m_money_expend_number=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pTipsWidget,"lab_expend_money"));
    m_money_expend_number->setText(CCString::createWithFormat("%d",PLAYER_REVIVE_COST)->getCString());

	m_lab_yuanbaotext=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pTipsWidget,"lab_yuanbao"));
	const char* yuanbaotext=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_YUANBAO);
	m_lab_yuanbaotext->setString(yuanbaotext);

	m_lab_expendtext=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pTipsWidget,"lab_expend"));
	const char* expenedtext=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_EXPEND);
	m_lab_expendtext->setString(expenedtext);

	m_btn_sure=dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pTipsWidget,"btn_sure"));
	m_btn_sure->addTouchEventListener(this,toucheventselector( UI_Tips_Layer::btnCallBackSure));
    m_btn_sure->setTouchEnabled(false);

	m_btn_cancel=dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pTipsWidget,"btn_cancel"));
	m_btn_cancel->addTouchEventListener(this,toucheventselector(UI_Tips_Layer::btnCallBackCancel));
    m_btn_cancel->setTouchEnabled(false);

	m_lab_canceltext=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pTipsWidget,"lab_canceltext"));
	const char* canceltext=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_GIVE_UP);
	m_lab_canceltext->setString(canceltext);

	m_lab_suretext=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pTipsWidget,"lab_suretext"));
	const char* suretext=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SURE_EXIT);
	m_lab_suretext->setString(suretext);
	/****************************************************************************/




	schedule(schedule_selector(UI_Tips_Layer::update_time), 1.f);
	return true;
}

void UI_Tips_Layer::setVisible(bool visible)
{
	cocos2d::Layer::setVisible(visible);
}

void UI_Tips_Layer::buttonChangeRoleCallback( Ref* pSender ,Widget::TouchEventType type)
{
//	UI::GameUI_Layer::get_instance()->buttonChangeRoleCallback(pSender);
//	if(UI::GameUI_Layer::get_instance()->do_change_actor()){
//		removeFromParent();
//	}
}

void UI_Tips_Layer::buttonRecoveryCallback( Ref* pSender,Widget::TouchEventType type )
{
int player_id;
Game_Data::Player* player;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	player_id = Account_Data_Mgr::instance()->get_current_role_id();
	player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));

	if(PLAYER_REVIVE_COST <= player->get_token())
	{
	    m_img_root_dlg->setVisible(false);
        //m_btn_change_role->setTouchEnabled(false);
        m_btn_recovery->setTouchEnabled(false);
        m_btn_give_up->setTouchEnabled(false);

	    m_img_confirm_dlg->setVisible(true);
        m_btn_sure->setTouchEnabled(true);
        m_btn_cancel->setTouchEnabled(true);
	}
	else
	{
		DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_GOLD_INGOT);
	}

	break;
    default:
	break;
}

}

void UI_Tips_Layer::buttonGiveUpCallback( Ref* pSender ,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	back_to_city();

	break;
    default:
	break;
}
}

void UI_Tips_Layer::set_count_time_down( int count_down_time )
{
	char value_tiem[32]={0};
	if(count_down_time<10)
	{
		SPRINTF(value_tiem," %d",count_down_time);
	}
	else
	{
		SPRINTF(value_tiem,"%d",count_down_time);
	}
	m_mTimeLeft->setStringValue(value_tiem);

	const char* timelefttext=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_LEFT_TIME);
	const char* secondtext=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_SECOND);
	char temp[64]={0};
	SPRINTF(temp,"%s%d%s",timelefttext,count_down_time,secondtext);
	m_lab_confirm_time->setText(temp);
}

void UI_Tips_Layer::update_time( float dt )
{
	if(count_down_time_-- <= 0){
		unschedule(schedule_selector(UI_Tips_Layer::update_time));
		back_to_city();
	}
	else{
		set_count_time_down(count_down_time_);
	}
}

void UI_Tips_Layer::back_to_city()
{
    vector<uint64> para;
    para.clear();
    para.push_back(current_instance_data::INSTANCE_STATE_FAILE);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("oninstancefinish", para);

//	Runtime::instance()->back_to_city_scene();
//	Game_Utils::instance()->reset_role_actor();
}
void UI_Tips_Layer::btnCallBackSure(Ref* pSender,Widget::TouchEventType type)
{
		std::vector<uint64> para;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	m_img_confirm_dlg->setVisible(false);
    m_btn_sure->setTouchEnabled(false);
    m_btn_cancel->setTouchEnabled(false);

	//这里向服务器发送要求复活

//    para.push_back(Game_Utils::instance()->get_primary_actor_id());
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_player_revive", para);

	break;
    default:
	break;
}
}
void UI_Tips_Layer::btnCallBackCancel(Ref* pSender,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	m_img_root_dlg->setVisible(true);
   // m_btn_change_role->setTouchEnabled(true);
    m_btn_recovery->setTouchEnabled(true);
    m_btn_give_up->setTouchEnabled(true);

	m_img_confirm_dlg->setVisible(false);
    m_btn_sure->setTouchEnabled(false);
    m_btn_cancel->setTouchEnabled(false);

	break;
    default:
	break;
}
}

void UI_Tips_Layer::show()
{
    m_img_root_dlg->setVisible(true);
    //m_btn_change_role->setTouchEnabled(true);
    m_btn_recovery->setTouchEnabled(true);
    m_btn_give_up->setTouchEnabled(true);
}
