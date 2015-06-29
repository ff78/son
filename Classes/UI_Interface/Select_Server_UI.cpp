#include "Select_Server_UI.h"
#include "UI/Main_City_Scene.h"
//#include "cocos-ext.h"
#include "UI_Interface/CocoStu_UI_Scene_Interface.h"
#include "MyEditBox.h"

#include "Game_Interface/event_define.h"
#include "Game_Interface/game_content_interface.h"

#include "UI_Interface/UI_ModalDialogue_Layer.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Common/GameDefine.h"
#include "Common/GameResource.h"
#include "Player_Account/Account_Logic.h"
#include "Common/Utils.h"
using namespace ui;
Select_Server_UI* Select_Server_UI::instance_ = 0;

Select_Server_UI::Select_Server_UI(void)
{
}

Select_Server_UI::~Select_Server_UI(void)
{
}

Select_Server_UI* Select_Server_UI::get_instance()
{
	if ( !instance_ )
		instance_ = new Select_Server_UI;
	return instance_;
}

void Select_Server_UI::reset()
{
	panel = (cocos2d::ui::Layout*)(cocos2d::ui::Helper::seekWidgetByName(panel,"dynamic_layer"));
	for (int i = 1; i <= sum_num_; ++i)
	{
		cocos2d::ui::Button* btn = (cocos2d::ui::Button*)(cocos2d::ui::Helper::seekWidgetByTag(panel,i));
		panel->removeChild(btn,true);
	}
}


 int Select_Server_UI::do_create_button_list( vector<uint64>& para )
 {
	//reset();
	cocos2d::CCScene* pScene = cocos2d::Director::getInstance()->getRunningScene();
	cocos2d::ui::Widget* pLayer = UI::Main_City_Actor_Layer::get_instance()->getUILayerWidget();

	panel = (cocos2d::ui::Layout*)(Helper::seekWidgetByName(pLayer, "dynamic_layer"));


	sum_num_ = para.size();
	Point p = panel->getPosition();
    cocos2d::ui::Button* button;
    vector<uint64>::iterator itu;
    int  count = 1;
    for (itu = para.begin(); itu != para.end(); ++itu )
	{
		button = cocos2d::ui::Button::create();

		button->setTouchEnabled(true);
		button->loadTextures(TIDY_BUTTON_NORMAL,TIDY_BUTTON_PRESSED,TIDY_BUTTON_DISABLED);
//		button->addTouchEventListener(UI::Main_City_Actor_Layer::get_instance(),toucheventselector(Select_Server_UI::current_server));

		button->setPosition(Vec2(p.x-290+((count-1)%4)*130,p.y+330-((count-1)/4)*80));
		button->_ID = (int)(*itu);
        button->setTag((int)(*itu));
		panel->addChild(button);
        count ++;
	}

     return 0;
 }
bool Select_Server_UI::create_button_list(Game_Logic::Game_Interface& gm_interface)
{

    vector<uint64> para;
    gm_interface.get_para(para);

    if( para.size() <= 0 )
        return false;
    
    get_instance()->do_create_button_list(para);

    return true;
}

bool Select_Server_UI::set_button_name(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() <= 0)
        return false;

    int button_id = (int)para[0];
    string button_name = gm_interface.get_keyword();
    get_instance()->set_name( button_id, button_name.data());
    return true;
}

void Select_Server_UI::current_server( Ref* pSender,Widget::TouchEventType type )
{
int dd;
int id;
vector<uint64> para;
const char* exitInfo;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	CCLog("----------------->Select_Server_UI::current_server");
	dd = get_instance()->get_total_num();
	id = pSender->_ID;
	if(id<=0 )
		return;
	else
	{
#ifdef NET_SUPPORT
        
        para.push_back(id);
		if(!Game_Logic::Game_Content_Interface::instance()->exec_interface("connecttogate", para))
		{
			exitInfo = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SERVER_DISCONNECT);
            UI_ModalDialogue_Layer::DoModal("",exitInfo,UI_ModalDialogue_Layer::DT_OK,[]()
            {
                Account_Logic::releaseData();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
                MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
                return;
#endif
                
                Director::getInstance()->end();
                
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                exit(0);
#endif
            }
            );
		}
#else
	CocoStu_UI_Scene_Interface::get_instance()->run_test(2004);
	UI::Main_City_Actor_Layer::get_instance()->addChild(MyEditBox::get_instance());
#endif

	}

	break;
    default:
	break;
}
}
bool Select_Server_UI::show_next_ui(Game_Logic::Game_Interface& gm_interface)
{
    vector< uint64 > para;
    gm_interface.get_para(para);
    if( para.size() <= 0) 
        return false;
    int ui = (int)para[0];
#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32||CC_TARGET_PLATFORM==CC_PLATFORM_IOS||CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	CocoStu_UI_Scene_Interface::get_instance()->run_test(ui);
	UI::Main_City_Actor_Layer::get_instance()->addChild(MyEditBox::get_instance());
#endif
    return true;
}
void Select_Server_UI::set_name( int id, const char* name )
{
	if(id<=0 )
		return;
	cocos2d::ui::Button* btn = (cocos2d::ui::Button*)(cocos2d::ui::Helper::seekWidgetByTag(panel,id));
//	btn->setFontName("ËÎÌו");
	//btn->setFontSize(25);
	btn->setTitleText(name);
	m_for_name_.insert(make_pair(id,name));
}

const char* Select_Server_UI::get_name(int id)
{
	std::map<int ,string>::iterator iter;
	iter = m_for_name_.find(id);
	if(iter!=m_for_name_.end())
		return (iter->second).c_str();
    return "";
}