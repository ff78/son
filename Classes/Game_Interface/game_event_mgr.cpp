#include "game_event_mgr.h"


#ifdef GAME_SERVER
#include <errno.h> 
#include "logger.h"
static cute::logger *game_event_mgr_log =
		cute::log_manager::instance()->get_logger("root.quest_event_mgr");
#endif

namespace Game_Logic
{             
	Game_Event_Mgr* Game_Event_Mgr::instance_p_ = 0;

	Game_Event_Mgr::Game_Event_Mgr(void)
	{
#ifdef YN_LINUX		
		pthread_mutex_init(&game_event_mutex_,NULL);  
#endif			
	}	

	Game_Event_Mgr::~Game_Event_Mgr(void)
	{
#ifdef YN_LINUX				
		pthread_mutex_destroy(&game_event_mutex_);
#endif		
		if( instance_p_)
			delete instance_p_;
	}

	Game_Event_Mgr* Game_Event_Mgr::instance(void)
	{
		if( NULL == instance_p_ )
		{
			instance_p_ = new Game_Event_Mgr;
		}
		
		return instance_p_;
	}

	void Game_Event_Mgr::proc_event( const int player_id_n, const char* cmd, const Game_Event& gm_evt )
	{	    
#ifdef YN_LINUX
	  //	map_mutex m(&game_event_mutex_);
#endif
		if( -1 == player_id_n )
		{
			game_event_handler_multi_map_t::iterator itgm;
			itgm = game_event_handler_multi_map_.find( cmd );
			if( itgm != game_event_handler_multi_map_.end() )
			{
				proc_common_event_by_command( itgm->second );
			}
		}
		else
		{
			game_event_handler_multi_player_map_t::iterator itgpm;
			itgpm = game_event_handler_multi_player_map_.find( player_id_n );
			if( itgpm !=  game_event_handler_multi_player_map_.end() )
			{
				game_event_handler_multi_map_t::iterator itgm;
				itgm = itgpm->second.find( cmd );
				if( itgm != itgpm->second.end() )
				{
					proc_player_event_by_command( itgm->second, cmd, gm_evt );
				}
			}
		}
	}
	void Game_Event_Mgr::reg_event( const char* cmd, const game_event_handler_t handle, const Game_Event& gm_evt )
	{
		//METHOD_TRACE(game_event_mgr_log);
		if( gm_evt.get_char_type() == Game_Event::EVENT_TYPE_PLAYER )
		{
			reg_player_event( gm_evt.get_char_id(), cmd, handle, gm_evt ); //register player event only
			return;
		}
#ifdef YN_LINUX		
				map_mutex m(&game_event_mutex_);
#endif	
		Game_Event_Callback gm_evt_cb;
		gm_evt_cb.set_game_event_handler( handle );
		gm_evt_cb.set_game_event_data( gm_evt );

		game_event_handler_multi_map_t::iterator itgm;
		itgm = game_event_handler_multi_map_.find( cmd );
		if( itgm != game_event_handler_multi_map_.end() )
		{
			game_event_handler_vec_t::iterator itgv;
			itgv = find_if( itgm->second.begin(), itgm->second.end(), bind2nd( equal_to<Game_Event_Callback>(), gm_evt_cb ));
			if( itgv == itgm->second.end() )
				itgm->second.push_back(gm_evt_cb);
		}
		else
		{
			game_event_handler_vec_t tmp_handler_vec;
			tmp_handler_vec.push_back(gm_evt_cb);
			game_event_handler_multi_map_.insert(make_pair(cmd,tmp_handler_vec));
		}	

	}

	void Game_Event_Mgr::reg_player_event( const int player_id_n, const char* cmd, const game_event_handler_t handle, const Game_Event& gm_evt )
	{
#ifdef YN_LINUX		
	   	map_mutex m(&game_event_mutex_);
#endif	
		game_event_handler_multi_player_map_t::iterator itgpm;
		itgpm = game_event_handler_multi_player_map_.find( player_id_n );
		if( itgpm !=  game_event_handler_multi_player_map_.end() )
		{
			game_event_handler_multi_map_t::iterator itgm;
			itgm = itgpm->second.find( cmd );
			if( itgm != itgpm->second.end() )
			{
				Game_Event_Callback gm_evt_cb;
				gm_evt_cb.set_game_event_handler( handle );
				gm_evt_cb.set_game_event_data( gm_evt );
				game_event_handler_vec_t::iterator itgv;
				itgv = find_if( itgm->second.begin(), itgm->second.end(), bind2nd( equal_to<Game_Event_Callback>(), gm_evt_cb ));
				if( itgv == itgm->second.end() )
					itgm->second.push_back(gm_evt_cb);
			}
			else
			{
				reg_player_event_when_null( cmd, handle, gm_evt,itgpm->second);
			}
		}
		else
		{
			game_event_handler_multi_map_t tmp_game_event_handler_multi_map;
			reg_player_event_when_null( cmd, handle, gm_evt,tmp_game_event_handler_multi_map );
			game_event_handler_multi_player_map_.insert(make_pair( player_id_n, tmp_game_event_handler_multi_map ));
		}
	}

	void Game_Event_Mgr::reg_player_event_when_null( const char* cmd, const game_event_handler_t handle, const Game_Event& gm_evt, game_event_handler_multi_map_t& tmp_game_event_handler_multi_map )
	{		
		//METHOD_TRACE(game_event_mgr_log);
		Game_Event_Callback gm_evt_cb;
		gm_evt_cb.set_game_event_handler( handle );
		gm_evt_cb.set_game_event_data( gm_evt );

		game_event_handler_vec_t tmp_handler_vec;
		tmp_handler_vec.clear();
		tmp_handler_vec.push_back(gm_evt_cb);

		tmp_game_event_handler_multi_map.insert(make_pair(cmd,tmp_handler_vec));

	}

	void Game_Event_Mgr::remove_event( const int player_id_n, const Game_Event& gm_evt )
	{
#ifdef YN_LINUX		
	  	map_mutex m(&game_event_mutex_);
#endif	
		game_event_handler_multi_player_map_t::iterator itgpm;
		itgpm = game_event_handler_multi_player_map_.find( player_id_n );
		if( itgpm !=  game_event_handler_multi_player_map_.end() )
		{
			game_event_handler_multi_map_t::iterator itgm;
			for( itgm = itgpm->second.begin(); itgm != itgpm->second.end(); ++ itgm )
			{
				game_event_handler_vec_t::iterator itgv;
				itgv = itgm->second.begin();
				for(; itgv != itgm->second.end();)
				{
					Game_Event gm_arg;
					(*itgv).get_game_event_data( gm_arg );
					if( gm_arg.get_char_type() == gm_evt.get_char_type() &&
						gm_arg.get_char_id() == gm_evt.get_char_id() &&
						gm_arg.get_event_owner_type() == gm_evt.get_event_owner_type() && 
						gm_arg.get_event_owner_id() == gm_evt.get_event_owner_id () &&
                        gm_arg.get_event_active_id() == gm_evt.get_event_active_id() &&
                        gm_arg.get_event_active_type() == gm_evt.get_event_active_type() )
					{

						itgv =itgm->second.erase(itgv);
						if( itgv == itgm->second.end())
							break;
					}
					else
					{
						++itgv;
					}
				}
			}
		}
	}

	void Game_Event_Mgr::remove_event_by_player_id( const int player_id_n )
	{
#ifdef YN_LINUX		
	  	  	map_mutex m(&game_event_mutex_);
#endif	
		game_event_handler_multi_player_map_t::iterator itgpm;
		itgpm = game_event_handler_multi_player_map_.find( player_id_n );
		if( itgpm !=  game_event_handler_multi_player_map_.end() )
		{
			game_event_handler_multi_player_map_.erase( itgpm );
		}
	}
	
	void Game_Event_Mgr::proc_player_event_by_command(const game_event_handler_vec_t& gm_evt_list, const char* /*cmd*/, const Game_Event& gm_evt)
	{
#ifdef YN_LINUX		
	  //		map_mutex m(&game_event_mutex_);
#endif		
		game_event_handler_vec_t tmp_gm_evt_list = gm_evt_list;
		game_event_handler_vec_t::iterator itgv;
		itgv = tmp_gm_evt_list.begin();
		for(; itgv != tmp_gm_evt_list.end(); ++itgv)
		{	
			Game_Event gm_arg =	(*itgv).get_game_event_data( );
			vector<uint64>::iterator itu;
			vector<uint64> tmppara = gm_evt.get_para();
			for( itu = tmppara.begin(); itu != tmppara.end(); itu ++ )
				gm_arg.add_para( (*itu));
			
			if( gm_arg.get_char_type() == gm_evt.get_char_type() &&
				gm_arg.get_char_id() == gm_evt.get_char_id() &&
				gm_arg.get_event_active_type() == gm_evt.get_event_active_type() &&
				gm_arg.get_event_active_id() == gm_evt.get_event_active_id() )
			{
				game_event_handler_t handle = (*itgv).get_game_event_handler();
				((handle))(gm_arg);
                continue;
			}
			if( gm_arg.get_char_type() == gm_evt.get_char_type() &&
				gm_arg.get_char_id() == gm_evt.get_char_id() &&
				gm_arg.get_event_active_type() == gm_evt.get_event_active_type() &&
				0 == gm_arg.get_event_active_id() )
			{
				game_event_handler_t handle = (*itgv).get_game_event_handler();
				gm_arg.set_event_active_id(gm_evt.get_event_active_id());
                tmppara = gm_evt.get_para();
                for( itu = tmppara.begin(); itu != tmppara.end(); itu ++ )
				    gm_arg.add_para((*itu));
				((handle))(gm_arg);
			}
			else 
				continue;
		}		
	}
	
	void  Game_Event_Mgr::proc_common_event_by_command(const game_event_handler_vec_t& gm_evt_list)
	{
		game_event_handler_vec_t tmp_gm_evt_list = gm_evt_list;
		game_event_handler_vec_t::iterator itgv;
			
		itgv = tmp_gm_evt_list.begin();
			
		for(; itgv != tmp_gm_evt_list.end(); ++itgv)
		{
			game_event_handler_t handle = (*itgv).get_game_event_handler();
			Game_Event gm_arg = (*itgv).get_game_event_data();
			(handle)(gm_arg);
		}
	}
}
                                          
