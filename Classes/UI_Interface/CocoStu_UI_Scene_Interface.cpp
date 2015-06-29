#include "CocoStu_UI_Scene_Interface.h"
#include "Game_Interface/common.h"
#include "Game_Interface/game_content_interface.h"
#include "UI_Interface/UI_ModalDialogue_Layer.h"
#include "Common/Utils.h"

CocoStu_UI_Scene_Interface* CocoStu_UI_Scene_Interface::instance_point_ = NULL;
CocoStu_UI_Scene_Interface::CocoStu_UI_Scene_Interface(void)
{
}


CocoStu_UI_Scene_Interface::~CocoStu_UI_Scene_Interface(void)
{
}

CocoStu_UI_Scene_Interface* CocoStu_UI_Scene_Interface::get_instance()
{
	if ( !instance_point_ )
		instance_point_ = new CocoStu_UI_Scene_Interface();
	return instance_point_;
}

void CocoStu_UI_Scene_Interface::run_test( int id )
{
	vector<uint64> para;
	para.push_back( id );

	Game_Logic::Game_Content_Interface::instance()->exec_interface("cocostudioUI", para, "");
}

void CocoStu_UI_Scene_Interface::lockScreen(const char* szTitle,const char* szContent)
{
	UI_ModalDialogue_Layer::DoModal(szTitle,szContent,UI_ModalDialogue_Layer::DT_NORMAL);
}

void CocoStu_UI_Scene_Interface::unlockScreen()
{
	UI_ModalDialogue_Layer::HideModal();
}

