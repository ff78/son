#include "UI_Sweep_Desc_Layer.h"

#include "Common/GameDefine.h"
#include "Play_System/Instance_Sweep_Data_Mgr.h"
#include "Play_System/Instance_Data_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Item_System/Item_Config_Mgr.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player_Config_Data.h"

#include "Play_System/Formula_Function_Instance.h"

using namespace Game_Data;
using namespace ui;

UI_Sweep_Desc_Layer::UI_Sweep_Desc_Layer(void) :
	m_root_widget(NULL),
	m_btn_close(NULL),
	m_lab_sweep_record_font(NULL),
	m_lab_sweep_times_font(NULL),
	m_lab_current_energy_font(NULL),
	m_lab_current_energy(NULL),
	m_lab_suggest_level_font(NULL),
	m_lab_suggest_level(NULL),
	m_lab_current_sweep_num_font(NULL),
	m_lab_current_sweep_num(NULL),
	m_btn_sweep_one(NULL),
	m_btn_sweep_two(NULL),
	m_btn_sweep_three(NULL)
{   
    memset(m_lab_sweep_font, 0, sizeof(m_lab_sweep_font));
	memset(m_lab_copy_award_font, 0, sizeof(m_lab_copy_award_font));
	memset(m_lab_copy_award_goods_font, 0, sizeof(m_lab_copy_award_goods_font));
	memset(m_tea_copy_award_info, 0, sizeof(m_tea_copy_award_info));
	memset(m_tea_copy_award_goods_info, 0, sizeof(m_tea_copy_award_goods_info));

	memset(m_lab_sweep_sum_times_font, 0, sizeof(m_lab_sweep_sum_times_font));
	memset(m_lab_button_sweep_font, 0, sizeof(m_lab_button_sweep_font));
    is_elite_instance_ = 0;
}


UI_Sweep_Desc_Layer::~UI_Sweep_Desc_Layer(void)
{
}

bool UI_Sweep_Desc_Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! cocos2d::Layer::init());

		m_root_widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Sweep_Copy_Layer/Sweep_Copy_Layer.ExportJson");
		this->addChild(m_root_widget);

		initComponent();

		bRet = true;
	} while (0);

	return bRet;
}

void UI_Sweep_Desc_Layer::setVisible( bool visible )
{
	Layer::setVisible(visible);
	if (visible)
	{
        update();
	}
	else
	{
        INSTANCE_SWEEP_DATA_MGR::instance()->reset();
	}
}

void UI_Sweep_Desc_Layer::buttonSweepOnce( cocos2d::Ref *pSender ,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	CCLog("sweep once");
    INSTANCE_SWEEP_DATA_MGR::instance()->start_sweep(1,is_elite_instance_);
    update();

	break;
    default:
	break;
}
}

void UI_Sweep_Desc_Layer::buttonSweepTwice( cocos2d::Ref *pSender ,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	CCLog("sweep twice");
    INSTANCE_SWEEP_DATA_MGR::instance()->start_sweep(2,is_elite_instance_);
    update();

	break;
    default:
	break;
}
}

void UI_Sweep_Desc_Layer::buttonSweepThrice( Ref *pSender ,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	CCLog("sweep thrice");
    INSTANCE_SWEEP_DATA_MGR::instance()->start_sweep(3,is_elite_instance_);
    update();

	break;
    default:
	break;
}
}

void UI_Sweep_Desc_Layer::buttonCloseCallback( Ref* pSender,Widget::TouchEventType type )
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(false);
    INSTANCE_SWEEP_DATA_MGR::instance()->reset();

	break;
    default:
	break;
}
}

void UI_Sweep_Desc_Layer::initComponent()
{
	m_btn_close = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_root_widget,"btn_close"));
	m_btn_close->addTouchEventListener(this, toucheventselector(UI_Sweep_Desc_Layer::buttonCloseCallback));

	//left area
	m_lab_sweep_record_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_sweep_record_font"));
	m_lab_sweep_record_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COPY_SWEEP_RECORD));
	
	char key[32] = {0};
	for (int i = 0; i < SWEEP_MAX_NUM; i++)
	{
		memset(key, 0, sizeof(key));
		sprintf(key, "lab_sweep_times_font_%d", i);
		m_lab_sweep_font[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,key));
		const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COPY_SWEEP_PER_TIMES);
		m_lab_sweep_font[i]->setString(CCString::createWithFormat(szFont,i+1)->getCString());

		memset(key, 0, sizeof(key));
		sprintf(key, "lab_copy_award_font_%d", i);
		m_lab_copy_award_font[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,key));
		szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COPY_AWARD);
		m_lab_copy_award_font[i]->setString(szFont);

		memset(key, 0, sizeof(key));
		sprintf(key, "lab_copy_award_goods_font_%d", i);
		m_lab_copy_award_goods_font[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,key));
		szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COPY_DROP_GOODS);
		m_lab_copy_award_goods_font[i]->setString(szFont);

		memset(key, 0, sizeof(key));
		sprintf(key, "tea_copy_award_info_%d", i);
		m_tea_copy_award_info[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,key));
		m_tea_copy_award_info[i]->setString("");

		memset(key, 0, sizeof(key));
		sprintf(key, "tea_copy_award_goods_info_%d", i);
		m_tea_copy_award_goods_info[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,key));
		m_tea_copy_award_goods_info[i]->setString("");
	}

	//right area
	m_lab_sweep_times_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_sweep_times_font"));
	m_lab_sweep_times_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COPY_SWEEP_TIMES));

	m_lab_current_energy_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_current_energy_font"));
	m_lab_current_energy_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COPY_CURRENT_ENERGY));

	m_lab_current_energy = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_current_energy"));
	m_lab_current_energy->setString("");

	for (int i=0; i<SWEEP_MAX_NUM; ++i)
	{
		memset(key, 0, sizeof(key));
		sprintf(key, "lab_sweep_sum_times_font_%d", i);
		m_lab_sweep_sum_times_font[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,key));
		m_lab_sweep_sum_times_font[i]->setString("");

		memset(key, 0, sizeof(key));
		sprintf(key, "lab_button_sweep_font_%d", i);
		m_lab_button_sweep_font[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,key));
		const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COPY_SWEEP_PER_TIMES);
		m_lab_button_sweep_font[i]->setString(CCString::createWithFormat(szFont, i+1)->getCString());
	}
	
	m_lab_suggest_level_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_suggest_level_font"));
	m_lab_suggest_level_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_SUGGEST_LEVEL));

	m_lab_suggest_level = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_suggest_level"));
	m_lab_suggest_level->setString("");

	m_lab_current_sweep_num_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_current_sweep_num_font"));
	m_lab_current_sweep_num_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COPY_CURRENT_TIMES));

	m_lab_current_sweep_num = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_current_sweep_num"));
	m_lab_current_sweep_num->setString("");

	m_btn_sweep_one = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_root_widget,"btn_sweep_one"));
	m_btn_sweep_one->addTouchEventListener(this, toucheventselector(UI_Sweep_Desc_Layer::buttonSweepOnce));
	m_btn_sweep_two = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_root_widget,"btn_sweep_two"));
	m_btn_sweep_two->addTouchEventListener(this, toucheventselector(UI_Sweep_Desc_Layer::buttonSweepTwice));
	m_btn_sweep_three = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_root_widget,"btn_sweep_three"));
	m_btn_sweep_three->addTouchEventListener(this, toucheventselector(UI_Sweep_Desc_Layer::buttonSweepThrice));
}

void UI_Sweep_Desc_Layer::update()
{
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if (!player)
	{
		return;
	}
	m_lab_current_energy->setString(CCString::createWithFormat("%d/%d",player->get_energy(),PLAYER_MAX_ENERGY)->getCString());

	int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
    if (is_elite_instance_ == 1)
    {
        instance_id = Formula_Function_Instance::instance()->get_elite_instance_id(instance_id);
        if (instance_id == -1)
        {
            return;
        }
    }

	vector<uint> para;
	Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute","began_content","energyconsume",para);
	if ( para.size() <= 0)
	{
		return;
	}

    Instance_Sweep_Data* data = INSTANCE_SWEEP_DATA_MGR::instance()->get_instance_sweep_data();
    for (int i = 0;i < SWEEP_MAX_NUM;++i)
    {
		const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COPY_SWEEP_NEED_ENERGY);
		m_lab_sweep_sum_times_font[i]->setString(CCString::createWithFormat(szFont, i+1, (i+1)*para[0])->getCString());

        if (data[i].flag_ == 1)
        {
            const char* format = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(RANKING_LIST_GOLD);
            std::string reward = CCString::createWithFormat("%s+%d",format,data[i].award_gold_)->getCString();
            format = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_EXP_FONT);
            reward += CCString::createWithFormat("%s+%d",format,data[i].award_exp_)->getCString();
            m_tea_copy_award_info[i]->setString(reward.c_str());
			
            reward.clear();
            int item_id = 0;
            int item_count = 0;
            const char* item_name = NULL;
            format = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_GAIN_INFO);
            Item_Config* item_config = NULL;
            Award_Item_Map& item_map = data[i].get_award_item_map();
            Award_Item_Map::iterator iter = item_map.begin();
            for (;iter != item_map.end();++iter)
            {
                item_id = iter->first;
                item_count =iter->second;
                
                Item_Config* item_config = ITEM_CONFIG_MGR::instance()->get_item_config(item_id);
                if (!item_config)
                {
                    continue;
                }
                
                Item_Config* config = NULL;
                if (item_config->type == Game_Data::IT_EQUIPMENT_DEPOT)
                {
                    Equipment_Depot_Config* equipment_depot_config = reinterpret_cast<Game_Data::Equipment_Depot_Config*>(item_config);
                    config = ITEM_CONFIG_MGR::instance()->get_item_config(equipment_depot_config->item_base_id);
                }
                else
                {
                    config = item_config;
                }

                if (config)
                {
                    item_name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(config->name);
                    reward += CCString::createWithFormat(format,item_name,item_count)->getCString();
                }
                
            }

            m_tea_copy_award_goods_info[i]->setString(reward.c_str());

            m_tea_copy_award_info[i]->setVisible(true);
            m_tea_copy_award_goods_info[i]->setVisible(true);
            m_lab_copy_award_font[i]->setVisible(true);
            m_lab_copy_award_goods_font[i]->setVisible(true);
            m_lab_sweep_font[i]->setVisible(true);
        }
        else
        {
            m_tea_copy_award_info[i]->setVisible(false);
            m_tea_copy_award_goods_info[i]->setVisible(false);
            m_lab_copy_award_font[i]->setVisible(false);
            m_lab_copy_award_goods_font[i]->setVisible(false);
            m_lab_sweep_font[i]->setVisible(false);
        }
    }

	para.clear();
	Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute","condition","level",para);
	if ( para.size() >= 1)
	{
		char txt[256];
		sprintf( txt, "%d", para[0]);
		m_lab_suggest_level->setString(txt);
	}

	int current_times = INSTANCE_SWEEP_DATA_MGR::instance()->get_cur_sweep_count();
	int all_times = INSTANCE_SWEEP_DATA_MGR::instance()->get_all_sweep_count();
	m_lab_current_sweep_num->setString(CCString::createWithFormat("%d/%d", current_times, all_times)->getCString());
}
