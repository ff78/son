

#include "FightNpc_Logic.h"

#include "Game_Interface/game_content_interface.h"

#include "FightNpc_Config_Mgr.h"
//#include "../FightNpc/FightNpc_Mgr.h"

FightNpc_Logic* FightNpc_Logic::instance_ = NULL;
FightNpc_Logic::FightNpc_Logic()
{

}

FightNpc_Logic::~FightNpc_Logic()
{

}

FightNpc_Logic* FightNpc_Logic::instance()
{
    if(instance_ == NULL)
    {
        instance_ = new FightNpc_Logic;
    }

    return instance_;
}

bool FightNpc_Logic::create_FightNpc(Game_Logic::Game_Interface& gm_interface)
{
	printf("hello create FightNpc \n");

    FIGHTNPC_MGR::instance()->initialize();

	return true;
}
