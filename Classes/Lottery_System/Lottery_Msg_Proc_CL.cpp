
#include "Network_Common/NetManager.h"
#include "Network_Common/message.h"
#include "Network_Common/message_coder.h"
#include "Network_Common/message_stream.h"

#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"

#include "Lottery_Msg_Proc_CL.h"
#include "Common/GameDefine.h"

#include "UI_Interface/UI_MainMenu_Layer.h"
#include "UI_Interface/UI_ModalDialogue_Layer.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"

#include "UI_Interface/UI_Public_Announcement.h"
#include "UI/Loading_Scene.h"


Lottery_Msg_Proc* Lottery_Msg_Proc::instance_ = 0;

Lottery_Msg_Proc::Lottery_Msg_Proc()
{

}

Lottery_Msg_Proc::~Lottery_Msg_Proc()
{

}

Lottery_Msg_Proc* Lottery_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Lottery_Msg_Proc;

    return instance_;
}

bool Lottery_Msg_Proc::on_ask_pubilc_annoucement( Game_Logic::Game_Interface& gm_interface )
{

	return true;
}

