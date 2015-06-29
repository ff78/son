
#include "UI_Function_Instance.h"
//#include "cocos-ext.h"
//#include "Runtime.h"
//#include "FSM_Game.h"
#include "CocoStu_UI_Scene_Interface.h"
#include "UI/Main_City_Scene.h"
#include "MyEditBox.h"
#include "Select_Server_UI.h"
#include "Game_Interface/game_content_interface.h"
#include "cocos2d.h"
#include "Player_Account/Account_Msg_Proc.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "UI/Main_City_Scene.h"

#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Common/Utils.h"
#include "../UI/City_Scene.h"

using namespace ui;

bool UI_Function_Instance::enter_scene(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
        return false;

    int scene_id = (int)para[0];

    log("create city %d\n", scene_id);
    auto city = UI::City_Scene::create();
	Director::getInstance()->replaceScene(city);
//    cocostudio::ArmatureDataManager::destroyInstance();


//    Runtime::instance()->enter_city_scene(scene_id);
    return true;
}

bool UI_Function_Instance::next_layer( Game_Logic::Game_Interface& gm_interface )
{

    //选择服务器  注册  开始游戏 等按键响应(暂时)
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
        return false;
    uint32 read_json_id = (uint)para[0];

    CocoStu_UI_Scene_Interface::get_instance()->run_test(read_json_id);


    UI::Main_City_Actor_Layer::get_instance()->addChild(MyEditBox::get_instance());

    return true;
}

bool UI_Function_Instance::create_role( Game_Logic::Game_Interface& gm_interface )
{

    vector<uint64> para;
    const char* pName = UI::Main_City_Actor_Layer::get_instance()->getRigisterName();
	int jobIndex = UI::Main_City_Actor_Layer::get_instance()->getJob();

    para.push_back(UI::Main_City_Actor_Layer::get_instance()->getRigisterSex());
    Game_Logic::Game_Content_Interface::instance()->exec_interface("send_create_role", para, pName);
    return true;
}

bool UI_Function_Instance::login_in( Game_Logic::Game_Interface& gm_interface )
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
        return false;
    uint32 read_json_id = (uint)para[0];

   string name =MyEditBox::get_instance()->getName();
    string password = MyEditBox::get_instance()->getPassword();

#ifdef NET_SUPPORT
    para.clear();
    para.push_back(read_json_id);

    stringstream ss;
    ss << name << "|" << password;
    Game_Logic::Game_Content_Interface::instance()->exec_interface("send_player_login", para, ss.str().c_str());
#else
    CocoStu_UI_Scene_Interface::get_instance()->run_test(read_json_id);
#endif

    return true;
}

bool UI_Function_Instance::enter_game( Game_Logic::Game_Interface& gm_interface )
{

    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
        return false;
    uint32 read_json_id = (uint)para[0];
#ifdef NET_SUPPORT
    para.clear();
    para.push_back(read_json_id);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("send_player_start_game", para);
    //Account_Msg_Proc::instance()->create_role("");
#else
    CCLOG("-----------UI_Function_Instance::enter game 1");
    Account_Data_Mgr::instance()->set_current_role_id(1000);

    Game_Data::Player* player = new Game_Data::Player;
    player->set_database_character_id(Account_Data_Mgr::instance()->get_current_role_id());
    player->set_character_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
    player->init_attr_data(1001, level);
    player->set_gold(200000);
    player->set_exp(0);

    CHARACTER_MGR::instance()->insert_character(player);

    para.clear();
    para.push_back(1);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("enterscene", para);
    CCLOG("-----------UI_Function_Instance::enter game 3");
#endif
    return true;
}

bool UI_Function_Instance::game_register( Game_Logic::Game_Interface& gm_interface )
{


    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
        return false;
    uint32 read_json_id = (uint)para[0];

    CocoStu_UI_Scene_Interface::get_instance()->run_test(read_json_id);

    return true;
}

//注册UI界面  注册按钮事件
bool UI_Function_Instance::button_register(Game_Logic::Game_Interface& gm_interface)
{

    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
        return false;
    uint32 read_json_id = (uint)para[0];

    CocoStu_UI_Scene_Interface::get_instance()->run_test(read_json_id);

    return true;
}

//到服务器列表界面
bool UI_Function_Instance::go_serverlist_scene(Game_Logic::Game_Interface& gm_interface)
{

    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
        return false;
    uint32 read_json_id = (uint)para[0];

    CocoStu_UI_Scene_Interface::get_instance()->run_test(read_json_id);

    UI::Main_City_Actor_Layer::get_instance()->loadServerList();

    return true;
}

//选择角色
bool UI_Function_Instance::select_role(Game_Logic::Game_Interface& gm_interface)
{

    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
        return false;
    int select_id = (int)para[0];

    if( Account_Data_Mgr::instance()->get_role_num() < 0 || select_id < 0 || select_id >= Account_Data_Mgr::instance()->get_role_num() )
    {
        CocoStu_UI_Scene_Interface::get_instance()->run_test(2005);
        UI::Main_City_Actor_Layer::get_instance()->loadSelectRoleSexList();
		UI::Main_City_Actor_Layer::get_instance()->loadSelectJob();
        return false;
    }
    Account_Data_Mgr::instance()->set_current_select(select_id);

    UI::Main_City_Actor_Layer::get_instance()->refreshCurrentSelect();

    return true;
}