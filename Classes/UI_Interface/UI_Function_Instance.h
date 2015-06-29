
#if !defined(EA_0DD82B0F_A1BC_467f_AF6C_F0FE1A9D36C6__INCLUDED_)
#define EA_0DD82B0F_A1BC_467f_AF6C_F0FE1A9D36C6__INCLUDED_

#include "Game_Interface/event_define.h"
#include "Game_Interface/game_element.h"
#include "cocos2d.h"
//#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;
class City_Scene;
class UI_Function_Instance
{

public:
	UI_Function_Instance();
	virtual ~UI_Function_Instance();

	static bool enter_scene(Game_Logic::Game_Interface& gm_interface);

	//Register_UI 新用户注册界面按钮事件
	static bool next_layer(Game_Logic::Game_Interface& gm_interface);
	static bool create_role(Game_Logic::Game_Interface& gm_interface);
	static bool button_register(Game_Logic::Game_Interface& gm_interface);
	static bool go_serverlist_scene(Game_Logic::Game_Interface& gm_interface);

	//UI_Login  UI_Select_Role  登陆界面以及选择角色界面 按钮事件
	static bool login_in(Game_Logic::Game_Interface& gm_interface);
	static bool game_register(Game_Logic::Game_Interface& gm_interface);
	static bool enter_game(Game_Logic::Game_Interface& gm_interface);
	static bool select_role(Game_Logic::Game_Interface& gm_interface);

	//新用户注册界面 内容信息

};
#endif // !defined(EA_0DD82B0F_A1BC_467f_AF6C_F0FE1A9D36C6__INCLUDED_)
