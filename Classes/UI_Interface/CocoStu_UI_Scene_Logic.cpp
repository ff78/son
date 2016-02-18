#include "CocoStu_UI_Scene_Logic.h"
#include "Game_Interface/game_content_interface.h"
#include "CocoStu_UI_Scene_Config.h"
#include "CocoStu_UI_Scene_Config_Mgr.h"
//#include "cocos-ext.h"
#include "UI/Main_City_Scene.h"
#include "UI_Interface/UI_Interface.h"
#include "Select_Server_UI.h"
#include "Common/VisibleRect.h"
#include "Player_Account/Account_Data_Mgr.h"

//USING_NS_CC_EXT;

CocoStu_UI_Scene_Logic* CocoStu_UI_Scene_Logic::instance_ = 0;

CocoStu_UI_Scene_Logic::CocoStu_UI_Scene_Logic(void)
{
}


CocoStu_UI_Scene_Logic::~CocoStu_UI_Scene_Logic(void)
{
}



CocoStu_UI_Scene_Logic* CocoStu_UI_Scene_Logic::get_instance()
{
	if ( !instance_ )
		instance_ = new CocoStu_UI_Scene_Logic();
	return instance_;
}

int CocoStu_UI_Scene_Logic::init_UI_Scene_system()
{
	UI_Json_fun_call_list_.clear();

	//Game_Logic::Game_Content_Interface::instance()->reg_function_callback("funName", UI_Json_Fun_Instance::fun_show, UI_Json_fun_call_list_);
	return 0;
}

int CocoStu_UI_Scene_Logic::excu_UI_Scene_fun( const char* cmd, std::vector<uint64> para/*, const char* key*/ )
{
	return Game_Logic::Game_Content_Interface::instance()->exec_function(cmd, para, UI_Json_fun_call_list_) ? 0 : -1;
}

bool CocoStu_UI_Scene_Logic::exec_UI_Scene( Game_Logic::Game_Interface& gm_interface )
{
	vector<uint64>  para;
	gm_interface.get_para(para);
	if( para.size() < 1)
		return false;
	uint32 ui_id = (uint)para[0];
	char temp[20];
	sprintf(temp,"%d",ui_id);

	CocoStudio::CocoStu_UI_Scene_Config UJC;
	CocoStudio::CocoStu_UI_Scene_Config_Mgr::get_instance()->get_ui_json_config_by_id(ui_id,UJC);
	const char* name = UJC.get_json_name();
	int type = UJC.get_json_type();
	bool enableAdapt = UJC.get_enableAdapt();
	bool scaleAdapt = UJC.get_scaleAdapt();
	bool equalProportions = UJC.get_equalProportions();

	//CCLOG("replaceUISceneWithFile");
	UI::Main_City_Actor_Layer::get_instance()->removeAllChildren();
	//CCUIHELPER->replaceUISceneWithFile(UI::Main_City_Actor_Layer::get_instance(), name, type, enableAdapt, scaleAdapt, equalProportions);
	cocos2d::Layer* pLayer = Layer::create();
	if(ui_id==2003||ui_id==2005)
	{
		//float rate=Director::getInstance()->getVisibleSize().width/Director::getInstance()->getWinSize().width;
		float rate=Director::getInstance()->getWinSize().width / 960;
		pLayer->setScaleX(rate);
	}
	

	pLayer->setTag(-9999);
	cocos2d::ui::Widget* pWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile(name);
	pLayer->addChild( pWidget );
	// 创建版本信息
	std::string str_version = Account_Data_Mgr::instance()->get_version();
	LabelTTF *lable_version = LabelTTF::create(str_version.c_str(),"Thonburi",30.f);
	lable_version->setAnchorPoint( Vec2(0,1) );
	pLayer->addChild(lable_version);
	lable_version->setPosition(VisibleRect::leftTop());

	UI::Main_City_Actor_Layer::get_instance()->addChild(pLayer);
	UI::Main_City_Actor_Layer::get_instance()->setUILayer(pLayer);
	UI::Main_City_Actor_Layer::get_instance()->setUILayerWidget(pWidget);
	list<int> widget_id_list;
	UJC.get_widget_id_list(widget_id_list);
	list<int>::iterator iter;
	for (iter = widget_id_list.begin(); iter != widget_id_list.end(); iter++)
	{
		UI_Interface::instance()->event_register(*iter);
	}

	return true;
}
