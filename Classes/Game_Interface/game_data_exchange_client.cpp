
#include "Network_Common/message.h"
#include "Network_Common/message_coder.h"
#include "Network_Common/message_stream.h"

#include "game_data_exchange_client.h"
#include "Game_Interface/game_event_response.h"
#include "Game_Interface/game_event_mgr.h"
#include "quest_system/quest_data/quest_data_mgr.h"

#include "game_play_controler/game_play_controler_logic/gameplay_ctrl_logic.h"
#include "game_play_controler/game_play_controler_data/gameplay_ctrl_data_mgr.h"

game_data_exchange_client* game_data_exchange_client::instance_p_ = 0;

game_data_exchange_client::game_data_exchange_client(void)
{

}

game_data_exchange_client::~game_data_exchange_client(void)
{

	if( instance_p_ )
		delete instance_p_;
}

game_data_exchange_client* game_data_exchange_client::instance(void)
{
	if( NULL == instance_p_ )
	{
		instance_p_ = new game_data_exchange_client;
	}
	
	return instance_p_;
}

bool game_data_exchange_client::on_player_login( const int player_id )
{

    return true;
}

bool game_data_exchange_client::on_player_logout( const int player_id )
{
    return true;
}

int game_data_exchange_client::get_quest_act_txt( int player_id, int quest_id, char* txt )
{
    Game_Data::quest_data* qd = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id);
    if( NULL == qd)
    {
        qd = Game_Data::quest_data_mgr::instance()->get_org_quest_data( quest_id );
    }

    if( NULL == qd )
        return -1;

    vector<unsigned int> reqpara;
	reqpara.clear();
    Game_Data::quest_data_mgr::instance()->get_org_quest_command_para( qd->get_quest_id(), "actbind", reqpara);
    if( 0 != reqpara.size() )
    {
        int act_id = reqpara[0];
        act_data_client adc;
        if( 0 == gameplay_ctrl_data_mgr::instance()->get_player_act_data_client( player_id, act_id, adc ) )
        {
            sprintf(txt, " ( %d / %d )", adc.get_act_count(),  adc.get_act_total_count() );
            return 0;
        }
    }

    return -1;
}



