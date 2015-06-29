
#include "CommonNpc_Logic.h"

#include "Game_Interface/game_content_interface.h"

#include "CommonNpc_Config_Mgr.h"
//#include "../CommonNpc/CommonNpc_Mgr.h"

CommonNpc_Logic* CommonNpc_Logic::instance_ = NULL;
CommonNpc_Logic::CommonNpc_Logic()
{

}

CommonNpc_Logic::~CommonNpc_Logic()
{

}

CommonNpc_Logic* CommonNpc_Logic::instance()
{
    if(instance_ == NULL)
    {
        instance_ = new CommonNpc_Logic;
    }

    return instance_;
}

bool CommonNpc_Logic::create_CommonNpc(Game_Logic::Game_Interface& gm_interface)
{
	//printf("hello create CommonNpc \n");

    CommonNpc_Config_MGR::instance()->initialize();

	return true;
}
