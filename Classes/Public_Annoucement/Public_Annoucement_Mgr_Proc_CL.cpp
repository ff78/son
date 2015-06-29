
#include "Network_Common/NetManager.h"
#include "Network_Common/message.h"
#include "Network_Common/message_coder.h"
#include "Network_Common/message_stream.h"

#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"

#include "Public_Annoucement_Mgr_Proc_CL.h"
#include "Public_Annoucement_Data_Mgr.h"
#include "Common/GameDefine.h"

#include "UI_Interface/UI_MainMenu_Layer.h"
#include "UI_Interface/UI_ModalDialogue_Layer.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"

#include "UI_Interface/UI_Public_Announcement.h"
#include "UI/Loading_Scene.h"


Public_Annoucement_Msg_Proc* Public_Annoucement_Msg_Proc::instance_ = 0;
bool Public_Annoucement_Msg_Proc::showed = false;
Public_Annoucement_Msg_Proc::Public_Annoucement_Msg_Proc()
{

}

Public_Annoucement_Msg_Proc::~Public_Annoucement_Msg_Proc()
{

}

Public_Annoucement_Msg_Proc* Public_Annoucement_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Public_Annoucement_Msg_Proc;

    return instance_;
}

bool Public_Annoucement_Msg_Proc::send_ask_pubilc_annoucement( Game_Logic::Game_Interface& gm_interface )
{
	if (!showed)
	{
		char body[256] = {0};
		message_stream body_ms(body, sizeof(body));
		body_ms << C2S_ASK_PUBLIC_ANNOUCEMENT;
		CNetManager::GetMe()->send_msg(body_ms);
	}
	return true;
}

bool Public_Annoucement_Msg_Proc::on_ask_pubilc_annoucement( Game_Logic::Game_Interface& gm_interface )
{

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return false;
	}
	Game_Data::Public_Annoucement_Data_Mgr::instance()->cleanup();
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int nums = 0;

	body_ms >> nums;

	for (int i = 0; i < nums; ++i)
	{
		uint64 id;
		std::string title;
		std::string content;
		body_ms >> title;
		body_ms >> content;
		body_ms >> id;

		Game_Data::PAD tmp = Game_Data::PAD();
		tmp.title = title;
		tmp.content = content;
		tmp.id = id;
		Game_Data::Public_Annoucement_Data_Mgr::instance()->add_pad(tmp);
	}

	cocos2d::Layer* public_announcement = UI_Public_Announcement::create();
	public_announcement->setVisible(true);
	Director::getInstance()->getRunningScene()->getChildByTag(UI::TAG_BTN_UI)->addChild(public_announcement, 20,UI::TAG_PUBLIC_ANNOUCEMENT);
	showed = true;

	return true;
}

