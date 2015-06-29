#include "game_condition.h"
#include "game_element.h"


#ifdef GAME_SERVER
#include "Character_System/Player_Logic.h"
#include "game_interface/game_data_exchange.h"
#endif

namespace Game_Logic
{

	Game_Condition* Game_Condition::m_pInstance = 0;

	Game_Condition::Game_Condition(void)
	{
	}

	Game_Condition::~Game_Condition(void)
	{
		if( m_pInstance )
			delete m_pInstance;
	}
	
	void Game_Condition::init(void)
	{
		game_condition_interface_map_.clear();
		reg_game_condition_function_callback("level", Game_Condition::player_level);
		reg_game_condition_function_callback("gender", Game_Condition::player_gender);
		reg_game_condition_function_callback("money", Game_Condition::player_money);
		reg_game_condition_function_callback("item", Game_Condition::player_item);
		reg_game_condition_function_callback("levelrange", Game_Condition::player_levelrange);
		reg_game_condition_function_callback("country", Game_Condition::player_country);
		reg_game_condition_function_callback("strength",Game_Condition::player_vigour);
		reg_game_condition_function_callback("bind",Game_Condition::player_bind);
        reg_game_condition_function_callback("energy",Game_Condition::player_energy);
	}
		
	bool Game_Condition::reg_game_condition_function_callback  ( const char* cmd, game_interface_handler_t handle )
	{
		game_interface_handler_map_t::iterator itgm;
		itgm = game_condition_interface_map_.find( cmd );
		if( itgm != game_condition_interface_map_.end() )
		{
			return false; 
		}
		else
		{
			game_condition_interface_map_.insert( make_pair( cmd, handle ) );
		}	
		return true;
	}
	
	
	bool Game_Condition::analysis_game_condition( const int player_id, const list<Game_Data::Game_Element>& game_ele_vec )
	{
		list<Game_Data::Game_Element> tmp_game_ele_vec = game_ele_vec;
		list<Game_Data::Game_Element>::iterator itgv = tmp_game_ele_vec.begin();
		for(; itgv != tmp_game_ele_vec.end(); ++ itgv )
		{
			game_interface_handler_map_t::iterator itgm;
			itgm = game_condition_interface_map_.find( (*itgv).get_command() );
			if( itgm != game_condition_interface_map_.end() )
			{
				Game_Interface gm_arg;
				vector<uint64> para;
				para.push_back( player_id );//player id
				//add addition para
				list<uint> para_ele;
				para_ele.clear();
				para_ele = (*itgv).get_para_list();
				list<uint>::iterator itvi;
				for( itvi = para_ele.begin(); itvi != para_ele.end(); ++ itvi )
				{
					para.push_back( *itvi );
				}
				gm_arg.set_para( para );
				if(!(itgm->second)(gm_arg))
					return false;
			}
		}
		
		return true;
	}
	
	Game_Condition* Game_Condition::instance(void)
	{
		if( NULL == m_pInstance )
		{
			m_pInstance = new Game_Condition;
		}
		
		return m_pInstance;
	}

	bool Game_Condition::player_level( Game_Interface& gm_interface )
	{
		Game_Interface gm_inf = gm_interface ;
		vector<uint64> para;
		gm_inf.get_para(para);
		if( para.size() < 3 )
			return false; 
		uint32 player_id = (uint32)para[0];
		uint level_min = (uint)para[1];
        uint level_max = (uint)para[2];
#ifdef GAME_SERVER
        uint cur_level = Game_Logic::game_data_exchange::instance()->get_player_level(player_id);
        if( cur_level < level_min || cur_level > level_max )
        {
            //Game_Logic::game_data_exchange::instance()->send_error_message( player_id, 90275, cur_level );
        }
        return  cur_level >= level_min && cur_level <= level_max;
#endif
		return  true;
	}
	bool Game_Condition::player_gender( Game_Interface& gm_interface )
	{
		Game_Interface gm_inf = gm_interface ;
		vector<uint64> para;
		gm_inf.get_para(para);
		if( para.size() < 2 )
			return false; 
		//uint32 player_id = (uint32)para[0];
		//uint gender =(uint)para[1];
		return true;
	}
		
	bool Game_Condition::player_money( Game_Interface& gm_interface )
	{
		Game_Interface gm_inf = gm_interface ;
		vector<uint64> para;
		gm_inf.get_para(para);
		if( para.size() < 2 )
			return false; 
		//uint32 player_id = (uint32)para[0];
		//uint money_amount_require = (uint)para[1];	
		
		return true;
	}
	bool Game_Condition::player_item( Game_Interface& gm_interface )
	{
		Game_Interface gm_inf = gm_interface ;
		vector<uint64> para;
		gm_inf.get_para(para);
		if( para.size() < 3 )
			return false; 
		//uint32 player_id = (uint32)para[0];
		//uint64 item_id = para[1];
		//uint16 item_amount_require = (uint16)para[2];
				
		return true;
	}
	bool Game_Condition::player_levelrange( Game_Interface& gm_interface )
	{
		Game_Interface gm_inf = gm_interface ;
		vector<uint64> para;
		gm_inf.get_para(para);
		if( para.size() < 3 )
			return false; 
		//uint32 player_id = (uint32)para[0];
		//uint16 level_down =(uint16)para[1];
		//uint16 level_up =  (uint16)para[2];

		return true;

	}
	bool Game_Condition::player_country	( Game_Interface& gm_interface )
	{
		Game_Interface gm_inf = gm_interface ;
		vector<uint64> para;
		gm_inf.get_para(para);
		if( para.size() < 2 )
			return false; 
		//uint32 player_id = (uint32)para[0];
		//uint player_country =(uint16)para[1];

		return true;
	}
	bool Game_Condition::player_title( Game_Interface& /*gm_interface*/ )
	{
		return true;		
	}
	bool Game_Condition::player_team( Game_Interface& /*gm_interface*/ )
	{
		return true;		
	}
	bool Game_Condition::player_guilddevote( Game_Interface& /*gm_interface*/ )
	{
		return true;		
	}
	bool Game_Condition::player_guild( Game_Interface& /*gm_interface*/ )
	{
		return true;		
	}
	bool Game_Condition::player_honor( Game_Interface& /*gm_interface*/ )
	{
		return true;		
	}

	bool Game_Condition::player_vigour( Game_Interface& gm_interface )
	{
		vector<uint64> para;
		gm_interface.get_para(para);
		if( para.size() < 2 )
			return false; 
		//uint32 player_id = (uint32)para[0];
		//uint vigour =(uint)para[1];

		return false;
	}
	bool Game_Condition::player_bind( Game_Interface& gm_interface )
	{
		vector<uint64> para;
		gm_interface.get_para(para);
		if( para.size() < 2 )
			return false; 
		uint32 player_id = (uint32)para[0];
		uint32 player_id_checked =(uint32)para[1];

		return player_id == player_id_checked;	
	}

	bool Game_Condition::player_vip( Game_Interface& gm_interface )
	{
		vector<uint64> para;
		gm_interface.get_para(para);
		if( para.size() < 2 )
			return false; 
		//uint32	player_id	=	(uint32)para[0];
		uint	level		=	(uint)para[1];
		uint	vip_level	=	0;
		return vip_level >= level;	
	}
    bool Game_Condition::player_energy   ( Game_Interface& gm_interface )
    {
#ifdef GAME_SERVER
		vector<uint64> para;
		gm_interface.get_para(para);
		if( para.size() < 2 )
			return false;
        int player_id = (int)para[0];
        int energy_value = (int) para[1];

        int player_energy = PLAYER_LOGIC::instance()->get_energy(player_id);
        if( energy_value > player_energy )
        {
            Game_Logic::game_data_exchange::instance()->send_error_message( player_id, 90274, energy_value );
        }
        return energy_value <= player_energy;
#else
        return true;
#endif
    }
}

