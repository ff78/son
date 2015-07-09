#include "UI_Activity_Layer.h"
#include "Common/GameResource.h"

#include "Item_System/Item_Config_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Activity_System/Activity_Config_Mgr.h"
#include "Activity_System/Activity_Logic_Cl.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"

#include "Player_Account/Account_Data_Mgr.h"

#include "UI_Interface/UI_MainMenu_Layer.h"

#include "Common/GameDefine.h"
using namespace ui;
UI_Activity_Layer::UI_Activity_Layer(void)
{
    memset(m_activity_type,0,sizeof(m_activity_type));
    m_select_index = 0;
}


UI_Activity_Layer::~UI_Activity_Layer(void)
{
}

bool UI_Activity_Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());

		m_root_widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Activity_Layer/Activity_Layer.ExportJson");
		this->addChild(m_root_widget);

		initComponent();

		bRet = true;
	} while (0);

	return bRet;
}

void UI_Activity_Layer::setVisible(bool visible)
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

void UI_Activity_Layer::initComponent()
{
	m_btn_close = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_root_widget,"btn_close"));
	m_btn_close->addTouchEventListener(this, toucheventselector(UI_Activity_Layer::btnCloseCallback));

	cocos2d::ui::ImageView* img_scroll_root_back = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_root_widget,"img_scroll_root_back"));

	//信息显示区域
	m_lab_title_level = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_title_level"));
	m_lab_title_level->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UA_LEVEL_FONT));
	m_lab_level_info = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_level_info"));
	
	m_lab_title_time = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_title_time"));
	m_lab_title_time->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UA_TIME_FONT));
	m_lab_time_info = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_time_info"));
	
	m_lab_title_intr = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_title_intr"));
	m_lab_title_intr->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UA_INTR_FONT));
	m_tea_intr_info = dynamic_cast<cocos2d::ui::TextField*>(Helper::seekWidgetByName(m_root_widget,"tea_info"));
	
	m_lab_title_award = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_title_award"));
	m_lab_title_award->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UA_AWARD_FONT));
	m_lab_award_info = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_award_info"));

	m_btn_enter = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_root_widget,"btn_enter"));
	m_btn_enter->addTouchEventListener(this, toucheventselector(UI_Activity_Layer::btnEnterCallback));
	m_lab_enter_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_enter_font"));
	m_lab_enter_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UA_ENTER_FONT));

	cocos2d::ui::PageView* page_view = createScrollViewLayer();
	img_scroll_root_back->addChild(page_view);

    reset_select_effect_ui();
    m_img_select_effect[0]->setVisible(true);
    m_img_select_effect[0]->setPosition(m_img_icon_root_back[0][0]->getPosition());
}

void UI_Activity_Layer::reset_select_effect_ui()
{
	for (int i=0; i<PAGE_SUM_NUM_ACT; ++i)
	{
		m_img_select_effect[i]->setVisible(false);
	}
}

void UI_Activity_Layer::btnCloseCallback( Ref* pSender ,Widget::TouchEventType type)
{
	setVisible(false);
}

void UI_Activity_Layer::btnEnterCallback( Ref* pSender,Widget::TouchEventType type )
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	show_activity_layer();
	break;
    default:
	break;
}
}

cocos2d::ui::PageView* UI_Activity_Layer::createScrollViewLayer()
{
	m_page_view = cocos2d::ui::PageView::create();
	m_page_view->setTouchEnabled(true);
	m_page_view->setSize(Size(SCROLL_LAYER_WIDTH,SCROLL_LAYER_HEIGHT));
	m_page_view->setAnchorPoint(Vec2(0.5f, 0.5f));

	for ( int i=0; i<PAGE_SUM_NUM_ACT; ++i )
	{
		cocos2d::ui::Layout* layout = cocos2d::ui::Layout::create();
		layout->setSize(Size(SCROLL_LAYER_WIDTH, SCROLL_LAYER_HEIGHT));

		m_img_select_effect[i] = cocos2d::ui::ImageView::create();
		m_img_select_effect[i]->loadTexture(ACTIVITY_BG_FRAME_SELECT);
m_img_select_effect[i]->setScale9Enabled(true);
		m_img_select_effect[i]->setSize(Size(300,130)); //280,115
		m_img_select_effect[i]->setPosition(Vec2(-320 + SCROLL_LAYER_WIDTH/2, +70 + SCROLL_LAYER_HEIGHT/2));
		m_img_select_effect[i]->setVisible(false);
		layout->addChild(m_img_select_effect[i]);

		for ( int j=0; j<EACH_PAGE_NUM_ACT; ++j )
		{
			//1 出售物品大背景
			m_img_icon_root_back[i][j] = cocos2d::ui::ImageView::create();
			m_img_icon_root_back[i][j]->loadTexture(ACTIVITY_BG_FRAME);
			m_img_icon_root_back[i][j]->setTouchEnabled(true);
	m_img_icon_root_back[i][j]->setScale9Enabled(true);
	m_img_icon_root_back[i][j]->setSize(Size(300,130));
			m_img_icon_root_back[i][j]->setAnchorPoint(Vec2(0.5f, 0.5f));

			layout->addChild(m_img_icon_root_back[i][j]);
			m_img_icon_root_back[i][j]->setPosition(Vec2(320*(j%3)-320 + SCROLL_LAYER_WIDTH/2, 
				-140*(j/3)+70 + SCROLL_LAYER_HEIGHT/2) );
	m_img_icon_root_back[i][j]->setTag(i*EACH_PAGE_NUM_ACT+j);
			m_img_icon_root_back[i][j]->addTouchEventListener(this, toucheventselector(UI_Activity_Layer::clickActivityInfo));
			
			//2 出售物品icon背景
			m_img_icon_texture_back[i][j] = cocos2d::ui::ImageView::create();
			m_img_icon_texture_back[i][j]->loadTexture(GIFT_BG_FRAME);
			m_img_icon_root_back[i][j]->addChild(m_img_icon_texture_back[i][j]);
			m_img_icon_texture_back[i][j]->setPosition(Vec2(-85, 0));

			//3 出售物品图标
			m_img_icon_texture[i][j] = cocos2d::ui::ImageView::create();
			m_img_icon_texture_back[i][j]->addChild(m_img_icon_texture[i][j]);

			//4 副本名称
			m_lab_activity_name[i][j] = cocos2d::ui::Text::create();
			m_lab_activity_name[i][j]->setFontSize(FONT_SIZE_ACT);
			m_img_icon_root_back[i][j]->addChild(m_lab_activity_name[i][j]);
			m_lab_activity_name[i][j]->setPosition(Vec2(50, 20));
			//m_lab_activity_name[i][j]->setString(CCString::createWithFormat("%d", i*EACH_PAGE_NUM_ACT+j)->getCString());

			//5 副本开放时间
			m_lab_activity_time[i][j] = cocos2d::ui::Text::create();
			m_lab_activity_time[i][j]->setFontSize(FONT_SIZE_ACT);
			m_img_icon_root_back[i][j]->addChild(m_lab_activity_time[i][j]);
			m_lab_activity_time[i][j]->setPosition(Vec2(50, -20));
		}
	
		m_page_view->addPage(layout);
	}
	
	return m_page_view;
}

void UI_Activity_Layer::clickActivityInfo( Ref* pSender ,Widget::TouchEventType type)
{
cocos2d::ui::ImageView* curImg;
int curImgTag;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    curImg = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
	curImgTag = curImg->getTag();
    if (m_activity_type[curImgTag] > 0)
    {
        m_select_index = curImgTag;
        show_activity_info();

        reset_select_effect_ui();
        m_img_select_effect[curImgTag/EACH_PAGE_NUM_ACT]->setVisible(true);
        m_img_select_effect[curImgTag/EACH_PAGE_NUM_ACT]->setPosition(curImg->getPosition());
    }

	break;
    default:
	break;
}
}

void UI_Activity_Layer::show_activity_layer()
{
    int activity_type = m_activity_type[m_select_index];
    if (ACTIVITY_LOGIC::instance()->check_activity(activity_type) == false)
    {
        return;
    }

    switch (activity_type)
    {
    case Game_Data::AT_SIX_SECT:
        {
			UI_MainMenu_Layer::get_instance()->visibleActivityEnterLayer(NULL,Widget::TouchEventType::ENDED);
        }
        break;

    default:
        break;
    }

	setVisible(false);
}

void UI_Activity_Layer::show_activity_info()
{
    m_lab_level_info->setVisible(false);
    m_lab_time_info->setVisible(false);
    m_tea_intr_info->setVisible(false);
    m_lab_award_info->setVisible(false);

    Game_Data::activity_config* config = ACTIVITY_CONFIG_MGR::instance()->get_activity_config_by_type(m_activity_type[m_select_index]);
    if (config)
    {
        const char* string = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UA_LEVEL_LIMIT);
        m_lab_level_info->setString(CCString::createWithFormat(string,config->get_level_limit())->getCString());
        string = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(config->get_open_time_desc());
        m_lab_time_info->setString(string);
        string = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(config->get_activity_desc());
        m_tea_intr_info->setText(string);
        string = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(config->get_reward_desc());
        m_lab_award_info->setString(string);

        m_lab_level_info->setVisible(true);
        m_lab_time_info->setVisible(true);
        m_tea_intr_info->setVisible(true);
        m_lab_award_info->setVisible(true);
    }
}

void UI_Activity_Layer::update_grid(int index,int icon,int name,int time)
{
    int row = index/EACH_PAGE_NUM_ACT;
    int col = index%EACH_PAGE_NUM_ACT;

    const char* szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(icon);
    std::string p("icon/");
    p+=szPath;
    m_img_icon_texture[row][col]->loadTexture(p.c_str());
    m_img_icon_texture[row][col]->setVisible(true);

    const char *szName = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(name);
    m_lab_activity_name[row][col]->setString(szName);
    m_lab_activity_name[row][col]->setVisible(true);

    const char *szTime = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(time);
    m_lab_activity_time[row][col]->setString(szTime);
    m_lab_activity_time[row][col]->setVisible(true);
}

void UI_Activity_Layer::remove_grid(int index)
{
    int row = index/EACH_PAGE_NUM_ACT;
    int col = index%EACH_PAGE_NUM_ACT;
    m_img_icon_texture[row][col]->setVisible(false);
    m_lab_activity_name[row][col]->setVisible(false);
    m_lab_activity_time[row][col]->setVisible(false);
}

void UI_Activity_Layer::update()
{
    for (int i = 0; i<GRID_NUM_ACT; ++i)
    {
        m_activity_type[i] = 0;
        remove_grid(i);
    }

    int index = 0;
    Game_Data::activity_config* config = NULL;
    Game_Data::activity_config_map& config_map = ACTIVITY_CONFIG_MGR::instance()->get_activity_config_map();
    Game_Data::activity_config_map_iter iter = config_map.begin();
    for (;iter != config_map.end();++iter)
    {
        config = iter->second;
        if (config)
        {
            m_activity_type[index] = config->get_type();
            update_grid(index,config->get_icon(),config->get_name(),config->get_week_open_day_desc());
            ++index;
        }
    }
    
    show_activity_info();
}
