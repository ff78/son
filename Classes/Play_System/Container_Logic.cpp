

#include "Container_Logic.h"

#include "Game_Interface/game_content_interface.h"

#include "Container_Mgr.h"
Container_Logic* Container_Logic::instance_ = 0;
Container_Logic::Container_Logic()
{

}

Container_Logic::~Container_Logic()
{

}

Container_Logic* Container_Logic::instance()
{
    if( NULL == instance_ )
    {
        instance_ = new Container_Logic;
    }

    return instance_;
}

bool Container_Logic::create_container(Game_Logic::Game_Interface& /*gm_interface*/)
{
	printf("hello create container \n");

	Game_Data::Container_Mgr::instance()->initialize();
	return true;
}
