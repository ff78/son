#include "UI_Instance_Layer.h"
//#include "Runtime.h"
#include "UI_MainMenu_Layer.h"

#include "Play_System/Instance_Data_Mgr.h"
#include "Game_Interface/game_content_interface.h"
//#include "Game_Scene.h"
//#include "GameUI_Layer.h"
//#include "UI/Loading_Scene.h"
#include "UI/City_Scene.h"

#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Player_Account/Account_Data_Mgr.h"

#include "Joiner_Guidance.h"

//USING_NS_CC_EXT;
using namespace ui;
UI_Instance_Layer::UI_Instance_Layer(void) : 
	juniorGuide(NULL)
{
	memset(m_btn_pic_mountain, 0, sizeof(m_btn_pic_mountain));
	memset(m_btn_button, 0, sizeof(m_btn_button));
	memset(m_lab_mountain_name, 0, sizeof(m_lab_mountain_name));
	memset(m_lab_level_limit, 0, sizeof(m_lab_level_limit));
}


UI_Instance_Layer::~UI_Instance_Layer(void)
{

}

bool UI_Instance_Layer::init()
{
	if ( !cocos2d::Layer::init() )
	{
		return false;
	}
	cocos2d::ui::Widget* inatanceWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/WorldMap/WorldMap.ExportJson");
	addChild( inatanceWidget );

	char key[32] = {0};
	for (int i=0; i<5; ++i)
	{
        //可点击的图片
		memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
		sprintf_s(key, "btn_img_%d" , i+1);
#else
		sprintf(key, "btn_img_%d" , i+1);
#endif
		m_btn_pic_mountain[i] = static_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(inatanceWidget,key));
		m_btn_pic_mountain[i]->addTouchEventListener(this, toucheventselector(UI_Instance_Layer::button_clicked_area));
        m_btn_pic_mountain[i]->setVisible(false);
		m_btn_pic_mountain[i]->setTouchEnabled(false);

        //可点击的按钮
        memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
        sprintf_s(key, "btn_mountain_%d" , i+1);
#else
        sprintf(key, "btn_mountain_%d" , i+1);
#endif
        m_btn_button[i] = static_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(inatanceWidget,key));
        m_btn_button[i]->addTouchEventListener(this, toucheventselector(UI_Instance_Layer::button_clicked_area));
        m_btn_button[i]->setVisible(false);
		m_btn_button[i]->setTouchEnabled(false);

        //设置副本区域的名称
        memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
        sprintf_s(key, "lab_name_%d" , i+1);
#else
        sprintf(key, "lab_name_%d" , i+1);
#endif
        m_lab_mountain_name[i] = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(inatanceWidget,key));
        m_lab_mountain_name[i]->setVisible(false);

        //设置副本区域的等级限制
        memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
        sprintf_s(key, "lab_level_%d" , i+1);
#else
        sprintf(key, "lab_level_%d" , i+1);
#endif
        m_lab_level_limit[i] = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(inatanceWidget,key));
        m_lab_level_limit[i]->setVisible(false);
	}
	
    Map_Area_UI_Config &config_map = INSTANCE_DATA_MGR::instance()->get_area_ui_config_map();
    Map_Area_UI_Config_Iter iter = config_map.begin();
    Area_UI_Config* config = NULL;
    int index = 0;
    const char* desc = NULL;
    for(;iter != config_map.end();++iter)
    {
        config = &(iter->second);
        if (config)
        {
          m_btn_pic_mountain[index]->setTag(config->area_id);
          m_btn_button[index]->setTag(config->area_id);

            desc = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(config->name_id);
            m_lab_mountain_name[index]->setString(desc);
            desc = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(config->level_id);
            m_lab_level_limit[index]->setString(desc);

            ++index;
        }
    }

	cocos2d::ui::Button* textButton = static_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(inatanceWidget,"tbn_back"));
	textButton->addTouchEventListener(this,toucheventselector(UI_Instance_Layer::backCallback));

	//手势
// 	if(!juniorGuide)
// 	{
// 		juniorGuide = Joiner_Guidance::create();
// 		this->addChild(juniorGuide);
// 		juniorGuide->setVisible(true);
// 		juniorGuide->setZOrder(999);
// 	}
// 	Point point(525, 235);
// 	juniorGuide->showGuideContent(point, JUNIOR_GUIDE_ASTAR);



	return true;
}

void UI_Instance_Layer::setVisible( bool visible )
{
	cocos2d::Layer::setVisible(visible);
	if(visible)
	{
		Joiner_Guidance::hideGuide();
	}
}

void UI_Instance_Layer::bagCloseCallback( Ref* pSender,Widget::TouchEventType type )
{
	setVisible(false);
}

void UI_Instance_Layer::button_clicked_area( Ref* pSender ,Widget::TouchEventType type)
{
cocos2d::ui::Button* this_btn;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    this_btn = dynamic_cast<cocos2d::ui::Button*>(pSender);
    clicked_area(this_btn->getTag());
    setVisible(false);

	break;
    default:
	break;
}
}

void UI_Instance_Layer::clicked_area(int area_id)
{
    UI_MainMenu_Layer::get_instance()->visibleSecondaryInstance(area_id);

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();


    vector<uint64> para;
    para.push_back( player_id );
    para.push_back( area_id );
//    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendrequirestagestate", para);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendrequirestageall", para);


    INSTANCE_DATA_MGR::instance()->set_current_instance_stage_id( area_id );
}

void UI_Instance_Layer::show_npc_dialog(int sprite_id)
{
	Scene* pScene = Director::getInstance()->getRunningScene();
	CC_ASSERT(pScene);
	UI_MainMenu_Layer* pLayer = dynamic_cast<UI_MainMenu_Layer*>(pScene->getChildByTag(UI::TAG_BTN_UI));
	if (pLayer)
	{
		pLayer->showNpcDialogue(sprite_id);
	}
	else
	{
		CCLOG("NPC_Clicked pLayer=NULL");
	}


}

void UI_Instance_Layer::backCallback( Ref* pSender,Widget::TouchEventType type )
{
	setVisible(false);
}

void UI_Instance_Layer::update(void)
{
    map<int, int> stage_lst;
    INSTANCE_DATA_MGR::instance()->get_stage_data( stage_lst );

    int area_id = 0;
    int pass = -1;
    int index = 0;
    map<int, int>::iterator itm; int pre_stage = -1;
    for( itm = stage_lst.begin(); itm != stage_lst.end(); ++ itm )
    {
        //itm->first stage id
        //itm->secodn stage pass  0 pass -1 not pass
        area_id = itm->first;
        pass = itm->second;

        if (pass == 0 || (Account_Data_Mgr::instance()->get_is_show_all_stage() == 1))
        {
            m_btn_pic_mountain[index]->setVisible(true);
			m_btn_pic_mountain[index]->setTouchEnabled(true);

            m_btn_button[index]->setVisible(true);
			m_btn_button[index]->setTouchEnabled(true);

            m_lab_mountain_name[index]->setVisible(true);
            m_lab_level_limit[index]->setVisible(true);
            pre_stage = 0;
        }
        else if( 0 == pre_stage )
        {
            m_btn_pic_mountain[index]->setVisible(true);
			m_btn_pic_mountain[index]->setTouchEnabled(true);

			m_btn_button[index]->setVisible(true);
			m_btn_button[index]->setTouchEnabled(true);

            m_lab_mountain_name[index]->setVisible(true);
            m_lab_level_limit[index]->setVisible(true);
            pre_stage = -1;

        }
        else
        {
            pre_stage = -1;
            m_btn_pic_mountain[index]->setVisible(false);
			m_btn_pic_mountain[index]->setTouchEnabled(false);

			m_btn_button[index]->setVisible(false);
			m_btn_button[index]->setTouchEnabled(false);

            m_lab_mountain_name[index]->setVisible(false);
            m_lab_level_limit[index]->setVisible(false);
        }

        ++index;
    }

    m_btn_pic_mountain[0]->setVisible(true);
	m_btn_pic_mountain[0]->setTouchEnabled(true);

    m_btn_button[0]->setVisible(true);
	m_btn_button[0]->setTouchEnabled(true);

    m_lab_mountain_name[0]->setVisible(true);
    m_lab_level_limit[0]->setVisible(true);
}
