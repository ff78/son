#include "UI_Daily_Mission.h"
#include "UI_MainMenu_Layer.h"
#include "UI_Mission_Layer.h"
#include "Item_System/Item_Desc_Config_Mgr.h"

#include "Daily_Task_System/Daily_Task_Mgr_Cl.h"
#include "Daily_Task_System/Daily_Task_Logic_Cl.h"
#include "Daily_Task_System/Daily_Task_Config_Mgr.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"

using namespace Game_Data;
using namespace ui;
UI_Daily_Mission::UI_Daily_Mission(void):
	m_prRotWidget(NULL)
{
	
}


UI_Daily_Mission::~UI_Daily_Mission(void)
{
}

bool UI_Daily_Mission::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());

		m_prRotWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Daily_Mission/Daily_Mission.ExportJson");
		this->addChild(m_prRotWidget);

		initComponent();

		bRet = true;
	} while (0);

	return bRet;
}


void UI_Daily_Mission::setVisible(bool visible)
{
	cocos2d::Layer::setVisible(visible);
    if (visible)
    {
        update();
    }
}

void UI_Daily_Mission::tokenFinishCallback( Ref* pSender ,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    DAILY_TASK_LOGIC::instance()->token_complete_daily_task();
	break;
    default:
	break;
}
}

void UI_Daily_Mission::oneKeyGainAllStarsCallback( Ref* pSender,Widget::TouchEventType type )
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    DAILY_TASK_LOGIC::instance()->set_daily_task_star_level_max();
	break;
    default:
	break;
}
}

void UI_Daily_Mission::opMissionCallback( Ref* pSender ,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    DAILY_TASK_LOGIC::instance()->op_daily_task();
	break;
    default:
	break;
}
}

void UI_Daily_Mission::refreshStarsLevelUpCallback( Ref* pSender,Widget::TouchEventType type )
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    DAILY_TASK_LOGIC::instance()->refresh_daily_task_star_level();
	break;
    default:
	break;
}
}

void UI_Daily_Mission::btnGiftGainOrNotCallback( Ref* pSender ,Widget::TouchEventType type)
{
cocos2d::ui::Button* button;
int curTag;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    button = dynamic_cast<cocos2d::ui::Button*>(pSender);
    if (button)
    {
        curTag =button->getTag();
        switch (curTag)
        {
        case DTGT_ONE:
            {
                DAILY_TASK_LOGIC::instance()->get_daily_task_gift_one();
            }
            break;

        case DTGT_TWO:
            {
                DAILY_TASK_LOGIC::instance()->get_daily_task_gift_two();
            }
            break;

        case DTGT_THREE:
            {
                DAILY_TASK_LOGIC::instance()->get_daily_task_gift_three();
            }
            break;

        default:
            break;
        }
    }

	break;
    default:
	break;
}
}

void UI_Daily_Mission::initComponent()
{
	//切换界面区
	m_btn_already_acp_mis = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_prRotWidget,"btn_accept"));
	m_btn_already_acp_mis->addTouchEventListener(this, toucheventselector(UI_Daily_Mission::btnAlreadyAcpCallback));
	m_btn_no_acp_mis = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_prRotWidget,"btn_wait"));
	m_btn_no_acp_mis->addTouchEventListener(this, toucheventselector(UI_Daily_Mission::btnNoAcpCallback));
	m_btn_close = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_prRotWidget,"btn_close"));
	m_btn_close->addTouchEventListener(this, toucheventselector(UI_Daily_Mission::btnCloseCallback));

	//任务区
	char szName[32] = {0};
	for (int i=0; i<STARTS_ALL_NUM; ++i)
	{
		memset(szName, 0, sizeof(szName));
		sprintf(szName, "img_star_back_%d", i);
		m_img_stars_back_texture[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_prRotWidget,szName));

		memset(szName, 0, sizeof(szName));
		sprintf(szName, "img_star_%d", i);
		m_img_stars_texture[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_prRotWidget,szName));
	}

	m_lab_mission_process_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"lab_daily_mission_progress"));
	//m_lab_mission_process_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id());
	m_lab_mission_process_percent = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"lab_progress_percent"));
	m_lab_vip_times_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"lab_vip_daily_times"));
	//m_lab_vip_times_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id());
	m_lab_vip_times_percent = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"lab_vip_times_percent"));

	m_lab_mission_name = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"lab_mission_type"));
	m_lab_mission_cur_state = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"lab_mission_state"));
	m_lab_mission_require = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"lab_mission_ask"));
	//m_lab_mission_require->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id());
	m_lab_mission_require_info = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"lab_mission_ask_info"));
	m_lab_mission_award_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"lab_mission_award_font"));
	//m_lab_mission_award_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id());
	m_lab_mission_award_exp = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"lab_mission_exp"));
	//m_lab_mission_award_exp->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id());
	m_lab_mission_award_exp_num = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"lab_mission_exp_num"));
	m_lab_mission_award_exp_times_num = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"lab_mission_exp_times_num"));
	m_lab_mission_award_silver = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"lab_mission_silver"));
	//m_lab_mission_award_silver->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id());
	m_lab_mission_award_silver_num = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"lab_mission_silver_num"));
	m_lab_mission_award_silver_times_num = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"lab_mission_silver_times_num"));

	m_btn_first = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_prRotWidget,"btn_first"));
	m_btn_first->addTouchEventListener(this, toucheventselector(UI_Daily_Mission::tokenFinishCallback));
	m_btn_first_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_btn_first,"Label"));
	//m_btn_first_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id());
	m_btn_second = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_prRotWidget,"btn_second"));
	m_btn_second->addTouchEventListener(this, toucheventselector(UI_Daily_Mission::oneKeyGainAllStarsCallback));
	m_lab_second_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_btn_second,"Label"));
	//m_lab_second_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id());
	m_btn_third = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_prRotWidget,"btn_third"));
	m_btn_third->addTouchEventListener(this, toucheventselector(UI_Daily_Mission::opMissionCallback));
	m_lab_third_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"Label"));
	//m_lab_third_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id());
	m_btn_fourth = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_prRotWidget,"btn_fourth"));
	m_btn_fourth->addTouchEventListener(this, toucheventselector(UI_Daily_Mission::refreshStarsLevelUpCallback));
	m_lab_fourth_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_prRotWidget,"m_btn_fourth"));
	//m_lab_fourth_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id());

	//礼包领取区
	char key[32] = {0};
	for (int i=0; i<DAILY_MISSION_GAIN_NUM; ++i)
	{
		memset(key, 0, sizeof(key));
		sprintf(key, "img_gift_%d", i);
		m_img_gift_texture[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_prRotWidget,key));
		m_lab_gift_daily_mis_compelete[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_img_gift_texture[i],"lab_complete_daily_mission"));
		m_lab_gift_daily_mis_percent[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_img_gift_texture[i],"lab_daily_mission_process"));
		m_btn_gift_gain_or_not[i] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_img_gift_texture[i],"btn_gain_or_not"));
        m_btn_gift_gain_or_not[i]->setTag(i);
		m_btn_gift_gain_or_not[i]->addTouchEventListener(this, toucheventselector(UI_Daily_Mission::btnGiftGainOrNotCallback));
		m_lab_gift_gain_or_not[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_img_gift_texture[i],"lab_gain_or_not"));
		//m_lab_gift_gain_or_not[i]->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id());
	}
	
}

void UI_Daily_Mission::btnAlreadyAcpCallback( Ref* pSender ,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(false);
	UI_Mission_Layer::get_instance()->buttonMissionAlreadyAccept(NULL,Widget::TouchEventType::ENDED);

	break;
    default:
	break;
}
}

void UI_Daily_Mission::btnNoAcpCallback( Ref* pSender ,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(false);
	UI_Mission_Layer::get_instance()->buttonMissionAbleAccept(NULL,Widget::TouchEventType::ENDED);

	break;
    default:
	break;
}
}

void UI_Daily_Mission::btnCloseCallback( Ref* pSender,Widget::TouchEventType type )
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(false);
	break;
    default:
	break;
}
}

void UI_Daily_Mission::update()
{
    reset_ui();

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return;
    }

    daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();

    int need_count[] = {GET_DAILY_TASK_GIFT_ONE_NEED_COMPLETE_COUNT,
        GET_DAILY_TASK_GIFT_TWO_NEED_COMPLETE_COUNT,
        GET_DAILY_TASK_GIFT_THREE_NEED_COMPLETE_COUNT};
    int complete_count = data.complete_count_;
    for (int i=0; i<DAILY_MISSION_GAIN_NUM; ++i)
    {
        if (data.complete_count_ >= need_count[i])
        {
            complete_count = need_count[i];
        }

        m_lab_gift_daily_mis_percent[i]->setString(CCString::createWithFormat("(%d/%d)",complete_count,need_count[i])->getCString());
    }


    if (data.task_base_id_ == 0)
    {
        return;
    }

    daily_task_config* config = DAILY_TASK_CONFIG_MGR::instance()->get_daily_task_config(data.task_base_id_);
    if (!config)
    {
        return;
    }

    m_lab_mission_process_percent->setString(CCString::createWithFormat("(%d/%d)",data.exec_count_,DAILY_TASK_COUNT_MAX)->getCString());

    const char* name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(config->name_);
    m_lab_mission_name->setString(name);
    m_lab_mission_name->setVisible(true);
    //m_lab_mission_cur_state->setVisible(true);

    const char* desc = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(config->desc_); 
    m_lab_mission_require_info->setString(CCString::createWithFormat(desc,data.progress_,config->count_)->getCString());
    m_lab_mission_require->setVisible(true);
    m_lab_mission_require_info->setVisible(true);

    int role_level = player->get_character_level();
    int reward_exp = (int)(((role_level * (role_level + 100) / 10.0f) + 15) * config->exp_ / 100.0f);
    int reward_gold = (int)((100 + role_level * (role_level + 500) / 50.0f) * config->money_ / 100.0f);

    m_lab_mission_award_exp_num->setString(CCString::createWithFormat("%d",reward_exp)->getCString());
    m_lab_mission_award_exp_times_num->setString(CCString::createWithFormat("x%0.1f",(1 + (data.star_level_ - 1) * data.star_level_ / 10.0f))->getCString());
    m_lab_mission_award_silver_num->setString(CCString::createWithFormat("%d",reward_gold)->getCString());
    m_lab_mission_award_silver_times_num->setString(CCString::createWithFormat("x%0.1f",(float)data.star_level_)->getCString());

    m_lab_mission_award_font->setVisible(true);
    m_lab_mission_award_exp->setVisible(true);
    m_lab_mission_award_exp_num->setVisible(true);
    m_lab_mission_award_exp_times_num->setVisible(true);
    m_lab_mission_award_silver->setVisible(true);
    m_lab_mission_award_silver_num->setVisible(true);
    m_lab_mission_award_silver_times_num->setVisible(true);

    for (int i = 0;i < STARTS_ALL_NUM;++i)
    {
        m_img_stars_back_texture[i]->setVisible(true);
        if (data.star_level_ > i)
        {
            m_img_stars_texture[i]->setVisible(true);
        }
    }

    if (data.progress_ != config->count_)
    {
        m_btn_first->setVisible(true);
    }

    if (data.star_level_ < STAR_LEVEL_MAX)
    {
        m_btn_second->setVisible(true);
    }

    const char* op_task = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_QUIT);
    if (data.progress_ == config->count_)
    {
        op_task = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_OVER);
    }
    //m_lab_third_font->setString(op_task);
    m_btn_third->setVisible(true);

    if (data.star_level_ < STAR_LEVEL_MAX)
    {
        m_btn_fourth->setVisible(true);
    }
}

void UI_Daily_Mission::reset_ui()
{
    m_lab_vip_times_font->setVisible(false);
    m_lab_vip_times_percent->setVisible(false);

    m_lab_mission_name->setVisible(false);
    m_lab_mission_cur_state->setVisible(false);

    m_lab_mission_require->setVisible(false);
    m_lab_mission_require_info->setVisible(false);

    m_lab_mission_award_font->setVisible(false);
    m_lab_mission_award_exp->setVisible(false);
    m_lab_mission_award_exp_num->setVisible(false);
    m_lab_mission_award_exp_times_num->setVisible(false);
    m_lab_mission_award_silver->setVisible(false);
    m_lab_mission_award_silver_num->setVisible(false);
    m_lab_mission_award_silver_times_num->setVisible(false);

    for (int i = 0;i < STARTS_ALL_NUM;++i)
    {
        m_img_stars_back_texture[i]->setVisible(false);
        m_img_stars_texture[i]->setVisible(false);
    }

    m_btn_first->setVisible(false);
    m_btn_second->setVisible(false);
    m_btn_third->setVisible(false);
    m_btn_fourth->setVisible(false);
}
