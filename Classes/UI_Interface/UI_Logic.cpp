
#include "UI_Logic.h"
#include "Game_Interface/game_content_interface.h"
#include "UI_Function_Instance.h"
#include "UI_Config.h"
#include "UI_Config_Data_Mgr.h"
#include "Common/Utils.h"
using namespace ui;
UI_Logic* UI_Logic::instance_p_ = 0;
UI_Logic::UI_Logic()
{

}

UI_Logic::~UI_Logic()
{

}

UI_Logic* UI_Logic::instance()
{
	if(!instance_p_)
		instance_p_ = new UI_Logic;
	return instance_p_;
}

int UI_Logic::init_UI_system()
{
	UI_function_call_list_.clear();

	//Register_UI 新用户注册界面按钮事件
 	Game_Logic::Game_Content_Interface::instance()->reg_function_callback("next_layer_button",UI_Function_Instance::next_layer,UI_function_call_list_);
	Game_Logic::Game_Content_Interface::instance()->reg_function_callback("button_register",UI_Function_Instance::button_register,UI_function_call_list_);
	
	//UI_Login  UI_Select_Role  登陆界面以及选择角色界面 按钮事件
	Game_Logic::Game_Content_Interface::instance()->reg_function_callback("login_in",UI_Function_Instance::login_in,UI_function_call_list_);
	Game_Logic::Game_Content_Interface::instance()->reg_function_callback("create_role",UI_Function_Instance::create_role,UI_function_call_list_);
 	Game_Logic::Game_Content_Interface::instance()->reg_function_callback("game_register",UI_Function_Instance::game_register,UI_function_call_list_);
    Game_Logic::Game_Content_Interface::instance()->reg_function_callback("enter_game",UI_Function_Instance::enter_game,UI_function_call_list_);
	Game_Logic::Game_Content_Interface::instance()->reg_function_callback("go_serverlist_scene",UI_Function_Instance::go_serverlist_scene,UI_function_call_list_);
	Game_Logic::Game_Content_Interface::instance()->reg_function_callback("select_role",UI_Function_Instance::select_role,UI_function_call_list_);
	return 0;

}

int UI_Logic::exec_UI_function(const char* cmd, vector<uint64> para/*, const char* key */)
{
	return Game_Logic::Game_Content_Interface::instance()->exec_function(cmd, para, UI_function_call_list_/*, key */) ? 0 : -1;

}

bool UI_Logic::exec_UI(Game_Logic::Game_Interface& gm_interface)
{

	vector<uint64>  para;
	gm_interface.get_para(para);
	if( para.size() < 1)
		return false;
	uint32 ui_id = (uint)para[0];
	
	Game_Data::UI_Config UIc;
	UIc.reset();
	if (-1 == Game_Data::UI_Config_Data_Mgr::instance()->get_ui_config_data_by_id( ui_id, UIc ))
		return false;

	std::list<Game_Data::Game_Element> gm_lst;
	UIc.get_func_list(gm_lst);
	std::list<Game_Data::Game_Element>::iterator itr;
	vector<uint> para_u;
	vector<uint64> para_lst;
	vector<uint>::iterator itu;
	for( itr = gm_lst.begin(); itr != gm_lst.end(); ++ itr )
	{
		para_u.clear();
		para_lst.clear();
        (*itr).get_para_list_in_vector(para_u);
		for( itu = para_u.begin(); itu != para_u.end(); ++itu)
			para_lst.push_back(*itu);
		UI_Logic::instance()->exec_UI_function((*itr).get_command(), para_lst/*, ""*/);
	}

	return true;
}