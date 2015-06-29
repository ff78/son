#ifndef _GAME_DATA_EXCHANGE_CLIENT_H
#define	_GAME_DATA_EXCHANGE_CLIEN_H

#include "Game_Interface/common.h"
#include "Network_Common/global_macros.h"

class game_data_exchange_client
{
friend class GameMover;
public:
	game_data_exchange_client(void);
	~game_data_exchange_client(void);
	static game_data_exchange_client* instance(void);

	bool on_player_login			( const int player_id );
	bool on_player_logout			( const int player_id );

     int get_quest_act_txt( int player_id, int quest_id, char* txt );

private:
	static game_data_exchange_client* instance_p_;


};

#endif


