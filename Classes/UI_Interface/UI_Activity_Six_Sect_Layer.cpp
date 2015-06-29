#include "UI_Activity_Six_Sect_Layer.h"

#include "Item_System/Item_Config_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Activity_System/Activity_Config_Mgr.h"
#include "Activity_System/Activity_Logic_Cl.h"
#include "Activity_System/Activity_Record_Mgr_Cl.h"

#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Play_System/Formula_Function_Instance.h"
#include "Player_Account/Account_Data_Mgr.h"

#include "Common/GameDefine.h"
using namespace ui;
UI_Activity_Six_Sect_Layer::UI_Activity_Six_Sect_Layer(void)
{
    memset(m_six_sect_id,0,sizeof(m_six_sect_id));
}


UI_Activity_Six_Sect_Layer::~UI_Activity_Six_Sect_Layer(void)
{
}

bool UI_Activity_Six_Sect_Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());

 		m_root_widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Activity_Six_Sect_Layer/Activity_Six_Sect_Layer.ExportJson");
 		this->addChild(m_root_widget);

		initComponent();

		bRet = true;
	} while (0);

	return bRet;
}

void UI_Activity_Six_Sect_Layer::setVisible(bool visible)
{
	cocos2d::Layer::setVisible(visible);
	if (visible)
	{
        update();
	}
	else
	{
	}
}

void UI_Activity_Six_Sect_Layer::initComponent()
{
	m_btn_close = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_root_widget,"btn_close"));
	m_btn_close->addTouchEventListener(this, toucheventselector(UI_Activity_Six_Sect_Layer::btnCloseCallback));

	char key[32] = {0};
	for (int i=0; i<CUR_LAY_AREA_NUM; ++i)
	{
		memset(key, 0, sizeof(key));
		sprintf(key, "img_copy_back_%d", i);
		m_img_root_back[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_root_widget,key));

		m_lab_area_title_font[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_img_root_back[i],"lab_copy_title_font"));
		m_img_area_texture[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_img_root_back[i],"img_scene_texture"));

		m_lab_pass_award_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_img_root_back[i],"lab_info_name_0"));
		m_lab_pass_award_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UA_PASS_AWARD));
		m_lab_pass_award[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_img_root_back[i],"lab_info_0"));
		m_lab_open_level_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_img_root_back[i],"lab_info_name_1"));
		m_lab_open_level_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UA_OPEN_LEVEL));
		m_lab_open_level[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_img_root_back[i],"lab_info_1"));
		m_lab_need_energy_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_img_root_back[i],"lab_info_name_2"));
		m_lab_need_energy_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UA_NEED_ENERGY));
		m_lab_need_energy[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_img_root_back[i],"lab_info_2"));
		m_lab_open_time_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_img_root_back[i],"lab_info_name_3"));
		m_lab_open_time_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UA_OPEN_TIME));
		m_lab_open_time[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_img_root_back[i],"lab_info_3"));
		m_lab_enter_times_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_img_root_back[i],"lab_info_name_4"));
		m_lab_enter_times_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UA_ENTER_TIMES));
		m_lab_enter_times[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_img_root_back[i],"lab_info_4"));

		m_btn_real_enter[i] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_img_root_back[i],"btn_enter"));
m_btn_real_enter[i]->setTag(i);
		m_btn_real_enter[i]->addTouchEventListener(this, toucheventselector(UI_Activity_Six_Sect_Layer::btnRealEnterCallback));

		m_lab_enter_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_img_root_back[i],"lab_enter_font"));
		m_lab_enter_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UA_ENTER_FONT));
	}
}

void UI_Activity_Six_Sect_Layer::btnCloseCallback( Ref* pSender ,Widget::TouchEventType type)
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

void UI_Activity_Six_Sect_Layer::btnRealEnterCallback( Ref* pSender ,Widget::TouchEventType type)
{
cocos2d::ui::Button* curButton;
int base_id;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	curButton = dynamic_cast<cocos2d::ui::Button*>(pSender);
    base_id = m_six_sect_id[curButton->getTag()];
    ACTIVITY_LOGIC::instance()->activity_six_sect(base_id);
    setVisible(false);

	break;
    default:
	break;
}
}

void UI_Activity_Six_Sect_Layer::update_grid(int index,int name,int icon,int time,int reward,int level,int energy,int cur_count,int join_count)
{
    const char* szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(icon);
    m_img_area_texture[index]->loadTexture(szPath, UI_TEX_TYPE_PLIST);
    m_img_area_texture[index]->setVisible(true);

    const char *szName = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(name);
    m_lab_area_title_font[index]->setString(szName);
    m_lab_area_title_font[index]->setVisible(true);

    const char *szReward = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(reward);
    m_lab_pass_award[index]->setString(szReward);
    m_lab_pass_award[index]->setVisible(true);

    const char *szFormat = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UA_LEVEL);
    m_lab_open_level[index]->setString(CCString::createWithFormat(szFormat,level)->getCString());
    m_lab_open_level[index]->setVisible(true);

    szFormat = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UA_ENERGY);
    m_lab_need_energy[index]->setString(CCString::createWithFormat(szFormat,energy)->getCString());
    m_lab_need_energy[index]->setVisible(true);

    const char *szTime = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(time);
    m_lab_open_time[index]->setString(szTime);
    m_lab_open_time[index]->setVisible(true);

    m_lab_enter_times[index]->setString(CCString::createWithFormat("%d/%d",cur_count,join_count)->getCString());
    m_lab_enter_times[index]->setVisible(true);
}

void UI_Activity_Six_Sect_Layer::remove_grid(int index)
{
    m_img_area_texture[index]->setVisible(false);
    m_lab_area_title_font[index]->setVisible(false);
    m_lab_pass_award[index]->setVisible(false);
    m_lab_open_level[index]->setVisible(false);
    m_lab_need_energy[index]->setVisible(false);
    m_lab_open_time[index]->setVisible(false);
    m_lab_enter_times[index]->setVisible(false);
}

void UI_Activity_Six_Sect_Layer::update()
{
    for (int i = 0; i<CUR_LAY_AREA_NUM; ++i)
    {
        m_six_sect_id[i] = 0;
        remove_grid(i);
    }

    int type = ACTIVITY_CONFIG_MGR::instance()->get_activity_six_sect_type();
    if (type == -1)
    {
        DICTIONARY_CONFIG_MGR::instance()->show_alert(UA_TIME_OUT);
        return;
    }
    
    int index = 0;
    Game_Data::activity_six_sect_config* config = NULL;
    Game_Data::activity_six_sect_config_map& config_map = ACTIVITY_CONFIG_MGR::instance()->get_activity_six_sect_config_map_by_type(type);
    Game_Data::activity_six_sect_config_map_iter iter = config_map.begin();
    for (;iter != config_map.end();++iter)
    {
        config = iter->second;
        if (config)
        {
            m_six_sect_id[index] = config->get_base_id();

            int need_energy = 0;
            vector<uint> para;
            Formula_Function_Instance::instance()->get_para_list_from_instance_data(config->get_instance_id(),
                "instance_attribute","began_content","energyconsume",para);
            if ( para.size() > 0)
            {
                need_energy = para[0];
            }

            int join_count = ACTIVITY_RECORD_MGR::instance()->get_six_sect_join_count(config->get_type());
            update_grid(index,config->get_name(),config->get_icon(),config->get_open_time_desc(),config->get_reward_desc(),
                config->get_level_limit(),need_energy,join_count,config->get_join_count());
            ++index;
        }
    }
}
