#include "quest_logic.h"
#include "Game_Interface/event_define.h"
#ifdef GAME_SERVER
#include "Character_System/Player_Logic.h"
#include "quest_system/quest_logic/quest_func_proc.h"
#include "quest_system/quest_logic/quest_cmd_func_proc.h"
#include "game_interface/game_data_exchange.h"
#endif
#include "quest_system/quest_data/quest_data_mgr.h"
#include "Game_Interface/game_event_response.h"
#include "Game_Interface/game_event_mgr.h" 
#include "Game_Interface/game_condition.h"
#include "Game_Interface/game_content_interface.h"
//#include "Game_Interface/system_msg.h"

#ifdef GAME_SERVER
#include "quest_system/quest_logic/quest_rec.h"
#include "quest_system/quest_logic/quest_rec_db.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "svc_config.h"
#include "gate_svc.h"
#include "logger.h"
static cute::logger *quest_logic_log =
		cute::log_manager::instance()->get_logger("root.quest");
#endif


namespace Game_Logic
{
	quest_logic* quest_logic::instance_p_ = 0;

	quest_logic::quest_logic(void)
	{
	}

	quest_logic::~quest_logic(void)
	{
		if( instance_p_ )
			delete instance_p_;
	}

	quest_logic* quest_logic::instance(void)
	{
		if( NULL == instance_p_ )
		{
			instance_p_ = new quest_logic;
		}
		
		return instance_p_;
	}

	void quest_logic::init( void )
	{
		quest_func_interface_map_.clear();
		quest_cmd_func_interface_map_.clear();				
		quest_award_func_interface_map_.clear();
		
		//init callback
#ifdef GAME_SERVER
		reg_quest_function_callback ( "monster", quest_func_proc::quest_fun_monster);
		reg_quest_function_callback ( "item", quest_func_proc::quest_fun_item);
		reg_quest_function_callback ( "monsterbylevel", quest_func_proc::quest_fun_monsterbylevel);	
		reg_quest_function_callback ( "playerlevel", quest_func_proc::quest_fun_playerlevel);	
		reg_quest_function_callback ( "skilllevel", quest_func_proc::quest_fun_skilllevel);	
		reg_quest_function_callback ( "useanyitem", quest_func_proc::quest_fun_useanyitem);	
		reg_quest_function_callback ( "useitematpos", quest_func_proc::quest_fun_useitematpos);	
		reg_quest_function_callback ( "collect", quest_func_proc::quest_fun_collect );

		reg_quest_function_callback ( "dialogto", quest_func_proc::quest_fun_dialogto );
		reg_quest_function_callback ( "giveitemtonpc", quest_func_proc::quest_fun_giveitemtonpc );
  		reg_quest_function_callback ( "seloccup", quest_func_proc::quest_fun_seloccup );
        //----------------------------------------------------------------------------------
  		reg_quest_function_callback ( "instance", quest_func_proc::quest_fun_instance );
        reg_quest_function_callback ( "equip_equipment", quest_func_proc::quest_fun_equip_equipment );
        reg_quest_function_callback ( "equip_book", quest_func_proc::quest_fun_equip_book );
        reg_quest_function_callback ( "up_skill", quest_func_proc::quest_fun_up_skill );
		reg_quest_function_callback ( "up_equipment_level", quest_func_proc::quest_fun_up_equipment_level);
        reg_quest_function_callback ( "up_book_level", quest_func_proc::quest_fun_up_book_level);
        reg_quest_function_callback ( "up_equipment_quality", quest_func_proc::quest_fun_up_equipment_quality);
        reg_quest_function_callback ( "friends", quest_func_proc::quest_fun_friends);
        reg_quest_function_callback ( "player_pk", quest_func_proc::quest_fun_player_pk);
        reg_quest_function_callback ( "general_fight", quest_func_proc::quest_fun_general_fight);
        reg_quest_function_callback ( "open_acupoint", quest_func_proc::quest_fun_open_acupoint);
        reg_quest_function_callback ( "costgold", quest_func_proc::quest_fun_cost_gold);
        reg_quest_function_callback ( "up_player_quality", quest_func_proc::quest_fun_up_player_quality);
        reg_quest_function_callback ( "up_book_quality", quest_func_proc::quest_fun_up_book_quality);
        reg_quest_function_callback ( "gerneralreqqa", quest_func_proc::quest_fun_gerneral_req_qa);
        reg_quest_function_callback ( "allequipreqqa", quest_func_proc::quest_fun_all_equip_req_qa);
        reg_quest_function_callback ( "skillreqlevel", quest_func_proc::quest_fun_skill_req_level);
        reg_quest_function_callback ( "moneyreq", quest_func_proc::quest_fun_player_money_req);
        reg_quest_function_callback ( "equipbookreqqa", quest_func_proc::quest_fun_equip_book_req_qa);
        reg_quest_function_callback ( "equip_item_all", quest_func_proc::quest_fun_equip_item_all );
        reg_quest_function_callback ( "compound_book_fragment", quest_func_proc::quest_fun_book_fragment_compound );
        reg_quest_function_callback ( "compound_material_fragment", quest_func_proc::quest_fun_material_fragment_compound );
        //-----------------------------------------------------------------------------------
		//enemy nation system function interface
		reg_quest_function_callback ( "enemymonster", quest_func_proc::quest_fun_enemymonster );
		reg_quest_function_callback ( "ranmomenemy", quest_func_proc::quest_fun_ranmomenemy );	
				
		//award function
		reg_quest_award_function_callback ( "awardremoveitem", quest_func_proc::quest_fun_awardremoveitem);
		reg_quest_award_function_callback ( "awardmoney", quest_func_proc::quest_fun_awardmoney);
		reg_quest_award_function_callback ( "awardbindmoney", quest_func_proc::quest_fun_awardbindmoney);
		reg_quest_award_function_callback ( "awarditem", quest_func_proc::quest_fun_awarditem);
		reg_quest_award_function_callback ( "awardexp", quest_func_proc::quest_fun_awardexp);
		reg_quest_award_function_callback ( "awarditembyoccup", quest_func_proc::quest_fun_awarditembyoccup);
        reg_quest_award_function_callback ( "awardgeneral", quest_func_proc::quest_fun_awardgeneral);

		//quest command function
		reg_quest_command_funciton_callback( "useitem", quest_cmd_func_proc::quest_cmd_useitem );
		reg_quest_command_funciton_callback( "killmonster", quest_cmd_func_proc::quest_cmd_killmonster );
		reg_quest_command_funciton_callback( "getitem", quest_cmd_func_proc::quest_cmd_getitem );
		reg_quest_command_funciton_callback( "delitem", quest_cmd_func_proc::quest_cmd_delitem );
		reg_quest_command_funciton_callback( "arrive", quest_cmd_func_proc::quest_cmd_arrive );
		reg_quest_command_funciton_callback( "collect", quest_cmd_func_proc::quest_cmd_collect );
		reg_quest_command_funciton_callback( "search", quest_cmd_func_proc::quest_cmd_search );

		reg_quest_command_funciton_callback( "patrol", quest_cmd_func_proc::quest_cmd_patrol );
		reg_quest_command_funciton_callback( "monstergroup", quest_cmd_func_proc::quest_cmd_monstergroup );
		reg_quest_command_funciton_callback( "challenge", quest_cmd_func_proc::quest_cmd_challenge );
		//enemy nation system command function interface
		reg_quest_command_funciton_callback( "dialogto", quest_cmd_func_proc::quest_cmd_dialogto);
#endif
		//award quest interface string index list
		award_cmd_str_list.clear();
		award_cmd_str_list.push_back( "awardexpbylevel" );
		award_cmd_str_list.push_back( "awardtitle" );
		award_cmd_str_list.push_back( "awardguilddevote" );
		award_cmd_str_list.push_back( "awardhonor" );
		award_cmd_str_list.push_back( "awardremoveitem" );
		award_cmd_str_list.push_back( "awardmoney" );
		award_cmd_str_list.push_back( "awardbindmoney" );
		award_cmd_str_list.push_back( "awarditem" );
		award_cmd_str_list.push_back( "awardexp" );
		award_cmd_str_list.push_back( "awarditembyoccup" );
		award_cmd_str_list.push_back( "awardgroup" );
        award_cmd_str_list.push_back( "awardgeneral" );

  }
    bool quest_logic::proc_logout( Game_Interface& gm_interface )
    {
        vector<uint64>  para;
		gm_interface.get_para(para);
		if( para.size() < 1)
			return false;
		uint player_id = (uint)para[0];

        Game_Data::quest_data_mgr::instance()->clear_player_quest_data(player_id);
        return true;
    }
    bool quest_logic::proc_login( Game_Interface& gm_interface )
    {
		vector<uint64>  para;
		gm_interface.get_para(para);
		if( para.size() < 1)
			return false;
		uint player_id = (uint)para[0];

        Game_Data::quest_data_mgr::instance()->clear_player_quest_data(player_id);

#ifdef GAME_SERVER

        para.clear();
        para.push_back(player_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("loadallquestdb", para);


#endif
        return true;
    }

	bool quest_logic::accept_quest( Game_Interface& gm_interface )
	{
		vector<uint64>  para;
		gm_interface.get_para(para);
		if( para.size() < 2)
			return false;
		uint player_id = (uint)para[0];
		uint quest_id = (uint)para[1];
		
		
		Game_Data::quest_data* org_qst = NULL;
		org_qst = Game_Data::quest_data_mgr::instance()->get_org_quest_data( quest_id);
		if( org_qst == NULL  )
		{
			return false;
		}

		Game_Data::game_quest_content gqc = org_qst->get_quest_accept();
		if(!Game_Condition::instance()->analysis_game_condition( player_id, gqc.get_quest_element() ))
		{
			//invalide quest accept condition
#ifdef GAME_SERVER
			quest_logic_log->rinfo("%d invalide quest accept condition %d\n",player_id,quest_id);
#endif
			return false;
		}
		
		if( !instance()->proc_add_player_quest( player_id, quest_id ) )
		{
#ifdef GAME_SERVER
			quest_logic_log->rinfo("%d add quest fail %d\n",player_id,quest_id);
#endif
			return false;
		}
		//send to client, quest complet, remove the quest
		instance()->upate_npc_quest_operate( player_id,  quest_id, org_qst->get_quest_accept(),Game_Data::quest_data::QUEST_STATE_REMOVE );	
		//send to client remove acceptable
		instance()->set_player_quest_state( player_id, quest_id, true );

		vector<uint64>  para_out;
		para_out.clear();
		para_out.push_back( player_id );
		//Game_Content_Interface::instance()->exec_interface("procnpcquestbind",para_out);
		return true;
	}

	bool quest_logic::complete_quest( Game_Interface& gm_interface )
	{
		vector<uint64>  para;
		gm_interface.get_para(para);
		if( para.size() < 2)
			return false;
		uint player_id = (uint)para[0];
		uint quest_id = (uint)para[1];

		//quest_logic_log->rinfo("%d complet quest %d\n",player_id,quest_id);

		Game_Data::quest_data* qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
		if( qst == NULL )
			return false;	
#ifdef GAME_SERVER
		instance()->send_msg_radiate_player(player_id,quest_id);
#endif

		instance()->upate_npc_quest_operate( player_id, quest_id, qst ->get_quest_content(), Game_Data::quest_data::QUEST_STATE_REMOVE, true );

		//check is can complete quest
		instance()->set_player_quest_state( player_id, quest_id );
		
		return false;
	}
		
	bool quest_logic::give_quest_award( Game_Interface& gm_interface )
	{
		//METHOD_TRACE(quest_logic_log);
		vector<uint64>  para;
		gm_interface.get_para(para);
		if( para.size() < 2)
			return false;		
		uint player_id = (uint)para[0];
		uint quest_id = (uint)para[1];

		//quest_logic_log->rinfo("%d give quest %d award\n",player_id,quest_id);
		
		for( unsigned int i = 0; i < instance()->award_cmd_str_list.size(); ++ i )
		{
			instance()->proc_quest_award( player_id, quest_id, instance()->award_cmd_str_list[i].data());
		}		
		return true;
	}

	bool quest_logic::giveup_quest( Game_Interface& gm_interface )
	{		

		vector<uint64>  para;
		gm_interface.get_para(para);
		if( para.size() < 2)
			return false;		
		uint player_id = (uint)para[0];
		uint quest_id = (uint)para[1];

		//quest_logic_log->rinfo("%d give up quest %d\n",player_id,quest_id);

		instance()->proc_analysis_quest_cmd_func_list( player_id, quest_id, false, 0, "", Game_Interface::OPERATE_GIVEUPQUEST );

		//tell system, quest complet
		vector<unsigned int> req_para;
		req_para.clear();
		int ring_id = 0;
		//if ring bind quest, valide is can continue play the quest
		Game_Data::quest_data_mgr::instance()->get_org_quest_command_para( quest_id, "ringbind", req_para);
		if( 0 != req_para.size() )
		{
			ring_id = req_para[0];
		}
		int act_id = 0;
		Game_Data::quest_data_mgr::instance()->get_org_quest_command_para( quest_id, "actbind", req_para);
		if( 0 != req_para.size() )
		{
			act_id = req_para[0];			
		}
		//Game_Event_Response::instance()->on_complete_quest( player_id, quest_id, true, ring_id );

		//get quest data	
		Game_Data::quest_data* qst = NULL;		
		qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id);
		if( qst == NULL )
			return false;

	 	Game_Data::quest_data tmp_qst = *qst;
  		//send to client, quest complet, remove the quest
		if( Game_Data::quest_data::QUEST_STATE_SUBMITABLE == tmp_qst.get_quest_state())
		{
			instance()->upate_npc_quest_operate( player_id,  quest_id, tmp_qst.get_quest_complete(),Game_Data::quest_data::QUEST_STATE_REMOVE );	
			instance()->upate_npc_quest_operate( player_id,  quest_id, tmp_qst.get_quest_content(), Game_Data::quest_data::QUEST_STATE_REMOVE, true );		
		}
		else if (Game_Data::quest_data::QUEST_STATE_INPROCESS == tmp_qst.get_quest_state())
			instance()->upate_npc_quest_operate( player_id,  quest_id, tmp_qst.get_quest_accept(),Game_Data::quest_data::QUEST_STATE_REMOVE );	


		tmp_qst.set_quest_state(Game_Data::quest_data::QUEST_STATE_GIVEUP);	
		Game_Data::quest_data_mgr::instance()->modi_quest_data( player_id, tmp_qst );

		vector<uint64> para_out;
		para_out.clear();
		para_out.push_back(player_id);
		para_out.push_back(quest_id);
		Game_Content_Interface::instance()->exec_interface("updatequestcontent", para_out );

 		//remove the item when accept quest
		Game_Data::game_quest_content gqc;
		tmp_qst.get_quest_award( gqc );

		instance()->do_proc_quest_award(player_id, quest_id, "awardremoveitem", gqc.get_quest_element());


		//remove quest data
		Game_Data::quest_data_mgr::instance()->removequest( player_id, quest_id );
			
		//remove quest related event
		instance()->remove_quest_event( para, player_id, quest_id );	

		para_out.clear();
		para_out.push_back( player_id );
		//Game_Content_Interface::instance()->exec_interface("procnpcquestbind",para_out);
			
		return true;
	}

	bool quest_logic::submit_quest( Game_Interface& gm_interface )
	{		
		//METHOD_TRACE(quest_logic_log);
		vector<uint64>  para;
		gm_interface.get_para(para);
		if( para.size() < 2)
			return false;		
		uint player_id = (uint)para[0];
		uint quest_id = (uint)para[1];

		//quest_logic_log->rinfo("%d submit quest %d\n",player_id,quest_id);

		//is can submit quest
		if(!instance()->check_quest_is_complet( player_id, quest_id ))
		{
			//cout << "[player:" << player_id << "] [quest:" << quest_id << "] is not complete !!!" << endl;
			return false;
		}

		//get quest data	
		Game_Data::quest_data* qst = NULL;		
		qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id);
		if( qst == NULL )
			return false;

				
		//tell system, quest complet
		vector<unsigned int> req_para;
		req_para.clear();
		int ring_id = 0;
		//if ring bind quest, valide is can continue play the quest
		Game_Data::quest_data_mgr::instance()->get_org_quest_command_para( quest_id, "ringbind", req_para);
		if( 0 != req_para.size() )
		{
			ring_id = req_para[0];
		}
		int act_id = 0;
		Game_Data::quest_data_mgr::instance()->get_org_quest_command_para( quest_id, "actbind", req_para);
		if( 0 != req_para.size() )
		{
			act_id = req_para[0];			
		}
		Game_Event_Response::instance()->on_complete_quest( player_id, quest_id, false, ring_id );

		Game_Data::quest_data tmp_qst = *qst;
		tmp_qst.set_quest_state(Game_Data::quest_data::QUEST_STATE_COMPLETED);

		Game_Data::quest_data_mgr::instance()->modi_quest_data( player_id, tmp_qst );

		vector<uint64> para_out;
		para_out.clear();
		para_out.push_back(player_id);
		para_out.push_back(quest_id);
		Game_Content_Interface::instance()->exec_interface("updatequestcontent", para_out );

		//send to client, quest complet, remove the quest
		instance()->upate_npc_quest_operate( player_id,  quest_id, qst->get_quest_complete(),Game_Data::quest_data::QUEST_STATE_REMOVE );		

		//give quest award to player
		for( uint i = 0; i < instance()->award_cmd_str_list.size(); i++ )
		{
			instance()->proc_quest_award( player_id, quest_id, instance()->award_cmd_str_list[i].data());
		}	

		//remove quest data
		Game_Data::quest_data_mgr::instance()->removequest( player_id, quest_id );	
			
		//remove quest related event
		instance()->remove_quest_event( para, player_id, quest_id );

#ifdef GAME_SERVER
		if( 0 == ring_id && 0 == act_id ) //if not ring quest and not act quest, set sign quest complete 
		{
			game_data_exchange::instance()->set_quest_done( player_id, quest_id );
		}
#endif

		para_out.clear();
		para_out.push_back( player_id );
        para_out.push_back( quest_id );
		Game_Content_Interface::instance()->exec_interface("sendsubmitquestresult",para_out);
#if 1//yypp
		instance()->proc_auto_accept_next_quest( player_id, quest_id );
#endif

		return true;
	}
	bool quest_logic::proc_auto_accept_next_quest( const uint player_id, const uint quest_id )
	{

		Game_Data::quest_data* org_qst = NULL;
		org_qst = Game_Data::quest_data_mgr::instance()->get_org_quest_data( quest_id );
		if( org_qst == NULL  )
		{
			return false;
		}

		vector<int> post_quest_cond;
		org_qst->get_post_cond(post_quest_cond);
		if( post_quest_cond.size() == 0 )
			return false;
		uint next_quest_id = post_quest_cond[0];

   		Game_Data::quest_data* next_org_qst = Game_Data::quest_data_mgr::instance()->get_org_quest_data( next_quest_id );
		if( next_org_qst == NULL  )
		{
			return false;
		}

	 	vector<uint64> para_vec;
		para_vec.clear();
		para_vec.push_back(player_id);
		para_vec.push_back( next_quest_id  );
		Game_Content_Interface::instance()->exec_interface("acceptquest",para_vec);

		//send auto accecp quest
		Game_Content_Interface::instance()->exec_interface("autoacceptquest",para_vec);
		return true;

	}

	bool quest_logic::is_quest_accepted( Game_Interface& gm_interface )
	{
		vector<uint64>  para;
		gm_interface.get_para(para);
		if( para.size() < 2)
			return false;		
		uint player_id = (uint)para[0];
		uint quest_id = (uint)para[1];

		//get quest data
		return Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id ) != NULL;
	}

	bool quest_logic::is_can_accept_quest( Game_Interface& gm_interface )
	{
		vector<uint64>  para;
		gm_interface.get_para(para);
		if( para.size() < 2)
			return false;		
		uint player_id = (uint)para[0];
		uint quest_id = (uint)para[1];

		//if quest already accepted, return 
		if(Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id ) != NULL)
			return false;
		
		//if quest already completed, return	
#ifdef GAME_SERVER
		if(Game_Logic::game_data_exchange::instance()->is_quest_done( player_id, quest_id ))
		{
			return false;
		}
#else
        para.clear();
        para.push_back( player_id);
        para.push_back( quest_id );
        if( Game_Logic::Game_Content_Interface::instance()->exec_interface("isquestdone", para) )
        {
            return false;
        }
#endif
		//get org quest data
		Game_Data::quest_data* org_qst = NULL;
		org_qst = Game_Data::quest_data_mgr::instance()->get_org_quest_data( quest_id);
		if( org_qst == NULL  )
		{
			return false;
		}
		
		//check pre quest is complete?
		vector<int> pre_quest_cond;
		vector<int>::iterator itpq;
		org_qst->get_pre_cond(pre_quest_cond);
		for( itpq = pre_quest_cond.begin(); itpq != pre_quest_cond.end(); ++itpq )
		{
			if( 0 == *itpq)
				continue;
#ifdef GAME_SERVER
			if(!Game_Logic::game_data_exchange::instance()->is_quest_done( player_id, *itpq ))
			{
				return false;
			}
#else
            para.clear();
            para.push_back( player_id);
            para.push_back( quest_id );
            if( Game_Logic::Game_Content_Interface::instance()->exec_interface("isquestdone", para) )
            {
                return false;
            }
#endif
		}
				
		Game_Data::game_quest_content gqc = org_qst->get_quest_accept();
		if(!Game_Condition::instance()->analysis_game_condition( player_id, gqc.get_quest_element() ))
		{
			//invalide quest accept condition
			return false;
		}

		return true;
	}		
	bool quest_logic::is_can_submit_quest( Game_Interface& gm_interface )
	{
		
		vector<uint64>  para;
		gm_interface.get_para(para);
		if( para.size() < 3)
			return false;		
		uint player_id = (uint)para[0];
		uint quest_id = (uint)para[1];
        uint send_update =   (uint)para[2];
		//return is quest can be submit
		return instance()->check_quest_is_complet( player_id, quest_id, send_update );
	}
	bool  quest_logic::is_quest_in_process( Game_Interface& gm_interface )
	{
		vector<uint64>  para;
		gm_interface.get_para(para);
		if( para.size() < 2)
			return false;		
		uint player_id = (uint)para[0];
		uint quest_id = (uint)para[1];

		//get quest data	
		Game_Data::quest_data* qst = NULL;		
		qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
		if( qst == NULL )
			return false;	
		
		//return is quest can be deliver
		return (Game_Data::quest_data::QUEST_STATE_INPROCESS == qst->get_quest_state()) ? true : false;
	}
	bool quest_logic::check_quest_is_complet(const uint32 player_id, const uint32 quest_id,int send_update)
	{
		//check is can complete quest
		set_player_quest_state( player_id, quest_id , false, send_update);

		//get quest data	
		Game_Data::quest_data* qst = NULL;		
		qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id);
		if( qst == NULL )
			return false;	
		
		//return is quest can be deliver
		return (Game_Data::quest_data::QUEST_STATE_SUBMITABLE == qst->get_quest_state()) ? true : false;
	}
	
	bool quest_logic::proc_quest_content_cmd_analysis( Game_Interface& gm_interface )
	{
		vector<uint64>  para_vec;
		para_vec.clear();
		gm_interface.get_para(para_vec);
		if( para_vec.size() < 3)
			return false;
		uint player_id = (uint)para_vec[0];
		uint quest_id = (uint)para_vec[1];
		uint element_id = (uint)para_vec[2];
		uint para_data = 0;
		if( para_vec.size() > 3 )
			para_data = (uint)para_vec[3];
		string keyword = gm_interface.get_keyword();
		
		return instance()->proc_analysis_quest_cmd_func_list( player_id, quest_id, false, element_id, keyword.data(), Game_Interface::OPERATE_NONE, para_data );
	}
	bool quest_logic::proc_quest_content_cout( Game_Interface& gm_interface )
	{
		vector<uint64>  para_vec;
		para_vec.clear();
		gm_interface.get_para(para_vec);
		if( para_vec.size() < 3)
			return false;		
		uint player_id = (uint)para_vec[0];
		uint quest_id = (uint)para_vec[1];
		uint element_id = (uint)para_vec[2];

		//get content element list
		Game_Data::game_element_list_t ge_vec;
		if( !instance()->get_quest_content_element_list(player_id, quest_id,ge_vec ) )
			return false;		

		Game_Data::game_element_list_t::iterator itgv;

		bool modi_b = false;
		for( itgv = ge_vec.begin(); itgv != ge_vec.end(); ++ itgv )
		{
            Game_Data::Game_Element& element =  *itgv;
			if( !strcmp(element.get_command(), gm_interface.get_keyword()))
			{
				vector<unsigned int> para;
				para.clear(); 
				element.get_para_list_in_vector(para);
				if( !strcmp(element.get_command(),"item"))
				{
					if(instance()->compute_item_count(para,element, player_id, element_id ))
					{
						modi_b = true;						
					}
					break;
				}
				else if( !strcmp(element.get_command(),"useanyitem"))
				{
					if(instance()->compute_useanyitem_count(para,element, player_id, element_id ))
					{
						modi_b = true;			
					}
					break;
				}
				else if( !strcmp(element.get_command(),"monsterbylevel"))
				{
					if(instance()->compute_monsterbylevel_count(para,element, player_id, element_id ))
					{
						modi_b = true;
					}
					break;
				}
				else if( !strcmp(element.get_command(),"playerlevel"))
				{
  					element.set_count( element_id );
					modi_b = true;
					break;
				}
 				else if( !strcmp(element.get_command(),"friends"))
				{
                    if(instance()->compute_friends(para,element, player_id, element_id ))
					{
						modi_b = true;						
					}
					break;
                }
                else if( !strcmp(element.get_command(),"equipbookreqqa"))
                {
                    if(instance()->compute_equip_book_req_qa(para,element, player_id, element_id ))
					{
						modi_b = true;						
					}
					break;
                }
                else if( !strcmp(element.get_command(),"gerneralreqqa"))
                {
                    if(instance()->compute_gerneral_req_qa(para,element, player_id, element_id ))
					{
						modi_b = true;						
					}
					break;
                }
                else if( !strcmp(element.get_command(),"allequipreqqa"))
                {
                    if(instance()->compute_all_equip_req_qa(para,element, player_id, element_id ))
					{
						modi_b = true;						
					}
					break;
                }
                else if( !strcmp(element.get_command(),"skillreqlevel"))
                {
                    if(instance()->compute_skill_req_level(para,element, player_id, element_id ))
					{
						modi_b = true;						
					}
					break;
                }
                else if( !strcmp(element.get_command(),"moneyreq"))
                {
                    if(instance()->compute_money_req(para,element, player_id, element_id ))
					{
						modi_b = true;						
					}
					break;
                }
                else if( !strcmp(element.get_command(),"equip_item_all"))
                {
                    if(instance()->compute_equip_item_all(para,element, player_id, element_id ))
                    {
                        modi_b = true;						
                    }
                    break;
                }
				else if( para[0] == (unsigned long)element_id && (unsigned int)element.get_count() < para[1] )
				{
					element.count_add();
					modi_b = true;		
					break;
				}
                else if( para[0] == 0 && (unsigned int)element.get_count() < para[1] ) //the function is not require object id, any object do
				{
					element.count_add();
					modi_b = true;		
					break;
				}
                else if( 1 == para.size())
                {
                    if( element.get_count() < para[0] )
                    {
                        element.count_add();
					    modi_b = true;		
					    break;
                    }
                }
			}
		}

		if( modi_b)
		{
			if(!instance()->set_quest_content_element_list(player_id, quest_id,ge_vec ))
				return false;

		}
		
		return true;
	}
	
	bool quest_logic::is_quest_content_counter_full( Game_Interface& gm_interface )
	{
		vector<uint64>  para_vec;
		para_vec.clear();
		gm_interface.get_para(para_vec);
		if( para_vec.size() < 3)
			return false;		
		uint player_id = (uint)para_vec[0];
		uint quest_id = (uint)para_vec[1];
		uint element_id = (uint)para_vec[2];
			//get content element list
		Game_Data::game_element_list_t ge_vec;
		if( !instance()->get_quest_content_element_list(player_id, quest_id,ge_vec ) )
			return false;		

		Game_Data::game_element_list_t::iterator itgv;
		for( itgv = ge_vec.begin(); itgv != ge_vec.end(); ++ itgv )
		{
			if(!strcmp(gm_interface.get_keyword(), "israndomenemy") && !strcmp((*itgv).get_command(),"randomenemy"))
			{
				if( 0 !=(*itgv).get_count() )
					return true;
				else 
					return false;
			}
			if( !strcmp((*itgv).get_command(), gm_interface.get_keyword()))
			{
				vector<unsigned int> para;
				para.clear(); 
				(*itgv).get_para_list_in_vector(para);
				if( !strcmp((*itgv).get_command(),"item") )
				{
					
					if( para.size() > 1 )
					{
						if( (unsigned int)(*itgv).get_count() >= para[1] && (unsigned int)element_id == para[0])
							return true;
					}
				}
				else if( !strcmp((*itgv).get_command(),"randomenemy"))
				{
					return element_id == ((*itgv).get_count());
				}
			}
		}	
				
		return false;
	}

///////////////////////////////////////////////////////////////////////////////////////

//private quest logic
	void quest_logic::remove_quest_event( const vector<uint64> & para, const uint player_id, const uint quest_id )
	{
		//remove quest related event
		Game_Event gm_para;
		gm_para.set_para( para );
		gm_para.set_char_type( Game_Event::EVENT_TYPE_PLAYER );
		gm_para.set_char_id(player_id);
		gm_para.set_event_owner_type( Game_Event::EVENT_TYPE_QUEST );
		gm_para.set_event_owner_id( quest_id );
		Game_Event_Mgr::instance()->remove_event( player_id, gm_para );
	}

	bool quest_logic::proc_add_player_quest( const uint player_id, const uint quest_id, uint ring_quest_bind_id , bool saved_quest )
	{

		//if activity bind then do accept activity
		vector<unsigned int> reqpara;
		reqpara.clear();
		Game_Data::quest_data_mgr::instance()->get_org_quest_command_para( quest_id, "actbind", reqpara);
		if( 0 != reqpara.size() )
		{
			int act_id = reqpara[0];
#ifdef GAME_SERVER
			if( !game_data_exchange::instance()->can_accept_activity( player_id, act_id ))
            {
                Game_Logic::game_data_exchange::instance()->send_error_message( player_id, 90280, act_id );
				return false;
            }
			game_data_exchange::instance()->do_accept_activity( player_id, act_id );
#endif
		}

		//get quest data
		Game_Data::quest_data* qst = NULL;	
		qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
		if( qst != NULL  ) //if quest exist
			return false; 

		Game_Data::quest_data* org_qst = NULL;
		org_qst = Game_Data::quest_data_mgr::instance()->get_org_quest_data( quest_id);
		if( org_qst == NULL  )
		{
			return false;
		}
		
		Game_Data::quest_data tmp_qst = *org_qst;
			
		tmp_qst.set_quest_state(Game_Data::quest_data::QUEST_STATE_INPROCESS);

		tmp_qst.set_quest_dirty_mark(true);
		
        Game_Data::quest_data_mgr::instance()->addquest( player_id, tmp_qst );
		//do add quest
        if( ! saved_quest )
        {

            vector<uint64> para;
            para.clear();
            para.push_back(player_id);
            para.push_back(quest_id);
            Game_Logic::Game_Content_Interface::instance()->exec_interface("insternewquesttodb",para);
        }
		
		//if ring bind quest, valide is can continue play the quest
		reqpara.clear();
		int select_ring_quest_id = ring_quest_bind_id;
		Game_Data::quest_data_mgr::instance()->get_org_quest_command_para( quest_id, "ringbind", reqpara);
		if( 0 != reqpara.size() )
		{
			int ring_id = reqpara[0];
			//if( !game_data_exchange::instance()->do_accept_ring_quest( player_id, quest_id, ring_id,select_ring_quest_id ))
			//{
			//	Game_Data::quest_data_mgr::instance()->removequest( player_id, quest_id );
			//	return false;
			//}

			instance()->process_update_ring_quest_content( player_id, quest_id, ring_id,select_ring_quest_id );

			instance()->upate_npc_quest_operate( player_id, quest_id, org_qst->get_quest_accept(),  Game_Data::quest_data::QUEST_STATE_CHALLENGE, true ); //add ring quest challenge bind

		}
		return true;
	}

	bool quest_logic::proc_analysis_quest( const uint player_id, const uint quest_id, bool reg_b, const uint operate_type  )
	{
		//analysis quest command function list
		proc_analysis_quest_cmd_func_list( player_id, quest_id, reg_b, 0, "", operate_type );

		//analysis quest function list
		return proc_analysis_quest_func_list( player_id, quest_id, reg_b );
	}
	bool quest_logic::proc_analysis_quest_func_list(const uint player_id, const uint quest_id, bool reg_b )
	{
		Game_Data::game_element_list_t ge_vec;
		if( !get_quest_content_element_list(player_id, quest_id, ge_vec ) )
			return false;

		Game_Data::game_element_list_t::iterator itgv;

		bool result_b = true;
		for( itgv = ge_vec.begin(); itgv != ge_vec.end(); itgv++  )
		{
            Game_Data::Game_Element& element = (*itgv);
			quest_interface_handler_map_t::iterator itgm;
			itgm = quest_func_interface_map_.find( element.get_command() );
			if( itgm != quest_func_interface_map_.end() )
			{
				Game_Interface gm_arg;
				gm_arg.set_reg_state(reg_b);
				vector<uint64>  para;
				para.push_back( player_id );//player id
				para.push_back( quest_id );//quest id

				//add addition para
				vector<unsigned int> para_ele;
				para_ele.clear();
                element.get_para_list_in_vector(para_ele);
				vector<unsigned int>::iterator itvi;
				for( itvi = para_ele.begin(); itvi != para_ele.end(); itvi++  )
				{
					para.push_back( *itvi );
				}
				gm_arg.set_para( para );

				//callback the function
				if(!(itgm->second)( gm_arg, element ) && result_b)
					result_b = false;
			}
#ifdef GAME_SERVER
            vector<uint> para;
            element.get_para_list_in_vector( para);
            if (strcmp(element.get_command(),"equip_equipment") == 0)
            {
                if (para.size() > 1)
                {
                    result_b = PLAYER_LOGIC::instance()->check_equip_equipment(player_id,para[0]);
                    if (result_b)
                    {
                        element.set_count(para[1]);
                    }
                }
            }
            else if (strcmp(element.get_command(),"up_equipment_level") == 0)
            {
                if (para.size() > 1)
                {
                    result_b = PLAYER_LOGIC::instance()->check_up_equipment_level(player_id,para[0],para[1]);
                    if (result_b)
                    {
                        element.set_count(para[1]);
                    }
                }
            }
            else if (strcmp(element.get_command(),"equip_book") == 0)
            {
                if (para.size() > 1)
                {
                    result_b = PLAYER_LOGIC::instance()->check_equip_book(player_id,para[0]);
                    if (result_b)
                    {
                        element.set_count(para[1]);
                    }
                }
            }
            else if (strcmp(element.get_command(),"up_equipment_quality") == 0)
            {
                if (para.size() > 1)
                {
                    result_b = PLAYER_LOGIC::instance()->check_up_equipment_quality(player_id,para[0],para[1]);
                    if (result_b)
                    {
                        element.set_count(para[1]);
                    }
                }
            }
            else if (strcmp(element.get_command(),"up_book_level") == 0)
            {
                if (para.size() > 1)
                {
                    result_b = PLAYER_LOGIC::instance()->check_up_book_level(player_id,para[0]);
                    if (result_b)
                    {
                        element.set_count(para[1]);
                    }
                }
            }
            else if (strcmp(element.get_command(),"up_player_quality") == 0)
            {
                if (para.size() > 1)
                {
                    result_b = PLAYER_LOGIC::instance()->check_up_player_quality(player_id,para[1]);
                    if (result_b)
                    {
                        element.set_count(para[1]);
                    }
                }
            }
            else if (strcmp(element.get_command(),"up_book_quality") == 0)
            {
                if (para.size() > 1)
                {
                    result_b = PLAYER_LOGIC::instance()->check_up_book_quality(player_id,para[0],para[1]);
                    if (result_b)
                    {
                        element.set_count(para[1]);
                    }
                }
            }
            else if (strcmp(element.get_command(),"up_skill") == 0)
            {
                if (para.size() > 1)
                {
                    result_b = PLAYER_LOGIC::instance()->check_up_skill(player_id,para[1]);
                    if (result_b)
                    {
                        element.set_count(para[1]);
                    }
                }
            }
            if (strcmp(element.get_command(),"equip_item_all") == 0)
            {
                if (para.size() > 1)
                {
                    result_b = PLAYER_LOGIC::instance()->check_equipitem_all(player_id);
                    if (result_b)
                    {
                        element.set_count(para[1]);
                    }
                }
            }
#endif
		}

		if( reg_b )
		{
			if(!instance()->set_quest_content_element_list(player_id, quest_id,ge_vec ))
				return false;
				
			vector<uint64> para_out;
			para_out.clear();
			para_out.push_back(player_id);
			para_out.push_back(quest_id);
			Game_Content_Interface::instance()->exec_interface("updatequestcontent", para_out );
		}
		
		return result_b;
	}
	bool quest_logic::proc_analysis_quest_cmd_func_list( const uint player_id, const uint quest_id, bool reg_b, const uint element_id, const char * keyword, const uint operate_type, const uint para_data )
	{
		//get quest data
		Game_Data::quest_data* qst = NULL;
		qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
		if( qst == NULL )
			return false;
						
		if(Game_Data::quest_data::QUEST_STATE_SUBMITABLE == qst->get_quest_state() && Game_Interface::OPERATE_NONE == operate_type )
		{
			return true;
		}
		//get quest content
		Game_Data::game_quest_content gqc;
		qst->get_quest_content( gqc );

		Game_Data::game_command_element_vec_t gce_vec;
		gqc.get_quest_command_element(gce_vec);

		Game_Data::game_command_element_vec_t::iterator itgc;
		Game_Data::game_element_list_t ge_vec;
		Game_Data::game_element_list_t::iterator itgv;
		bool pre_cond_b = true;
		bool now_cond_b = true;	
		for( itgc = gce_vec.begin(); itgc != gce_vec.end(); ++ itgc )
		{
			pre_cond_b = true;
			ge_vec.clear();
			(*itgc).get_game_element_data(ge_vec);

			for( itgv = ge_vec.begin(); itgv != ge_vec.end(); ++ itgv )
			{
				quest_interface_handler_map_t::iterator itgm;
				itgm = quest_cmd_func_interface_map_.find( (*itgv).get_command() );
				if( itgm != quest_cmd_func_interface_map_.end() )
				{
					Game_Interface gm_arg;
					gm_arg.set_reg_state(reg_b);
					gm_arg.set_operate_type(operate_type);
					vector<uint64>  para;
					para.push_back( player_id );//player id
					para.push_back( quest_id );//quest id
					para.push_back( element_id );

					gm_arg.set_keyword( keyword );

					//add addition para
					vector<unsigned int> para_ele;
					para_ele.clear();
                    (*itgv).get_para_list_in_vector(para_ele);
					vector<unsigned int>::iterator itvi;
					for( itvi = para_ele.begin(); itvi != para_ele.end(); ++ itvi )
					{
						para.push_back(*itvi);
					}
					para.push_back(para_data);
					gm_arg.set_para(para);
					//callback the function
					gm_arg.set_pre_condition(pre_cond_b);
					now_cond_b = (itgm->second)( gm_arg, (*itgv) );
					if( now_cond_b == false && pre_cond_b == true )
					{
						pre_cond_b = false;
					}					
				}
			}
		}
		return true;
	}

	bool quest_logic::reg_quest_function_callback ( const char* cmd, quest_interface_handler_t handle )
	{
		quest_interface_handler_map_t::iterator itgm;
		itgm = quest_func_interface_map_.find( cmd );
		if( itgm != quest_func_interface_map_.end() )
		{
			return false; 
		}
		else
		{
			quest_func_interface_map_.insert( make_pair( cmd, handle ) );
		}	
		return true;
	}
	
	bool quest_logic::reg_quest_award_function_callback ( const char* cmd, quest_interface_handler_t handle )
	{
		quest_interface_handler_map_t::iterator itgm;
		itgm = quest_award_func_interface_map_.find( cmd );
		if( itgm != quest_award_func_interface_map_.end() )
		{
			return false; 
		}
		else
		{
			quest_award_func_interface_map_.insert( make_pair( cmd, handle ) );
		}	
		return true;
	}
	bool quest_logic::reg_quest_command_funciton_callback( const char* cmd, quest_interface_handler_t handle )
	{
		quest_interface_handler_map_t::iterator itgm;
		itgm = quest_cmd_func_interface_map_.find( cmd );
		if( itgm != quest_cmd_func_interface_map_.end() )
		{
			return false; 
		}
		else
		{
			quest_cmd_func_interface_map_.insert( make_pair( cmd, handle ) );
		}	
		return true;
	}
	
	bool quest_logic::get_quest_counter( const uint player_id, const uint quest_id, vector< unsigned int >& counter_vec )
	{
		counter_vec.clear();
				
		Game_Data::quest_data* qst = NULL;
		qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
					
		if( qst == NULL )
			return false;
			
		//get quest content
		Game_Data::game_quest_content gqc;
		qst->get_quest_content( gqc );

		//get content element list
		Game_Data::game_element_list_t ge_vec;
		ge_vec = gqc.get_quest_element();		
		Game_Data::game_element_list_t::iterator itgv;
		for( itgv = ge_vec.begin(); itgv != ge_vec.end(); ++ itgv )
		{
			counter_vec.push_back((*itgv).get_count());
		}		
		return true; 
	}
	
  bool quest_logic::set_player_quest_state( const uint player_id, const uint quest_id, bool reg_b, int /*send_update*/ )
	{
		Game_Data::quest_data* qst = NULL;

		bool ret = false;

		//get quest data        
		qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
		if( qst == NULL )
			return ret;

        qst->set_quest_dirty_mark(false);
        Game_Data::quest_data_mgr::instance()->modi_quest_data( player_id, *qst );

		if( instance()->proc_analysis_quest( player_id, quest_id, reg_b ) )  // quest complete
		{
			if( Game_Data::quest_data::QUEST_STATE_SUBMITABLE == qst->get_quest_state() )
				return true;
			//get quest data
			qst = NULL;
			qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
			if( qst == NULL)
				return ret;
							
			qst->set_quest_state(Game_Data::quest_data::QUEST_STATE_SUBMITABLE);
			qst->set_quest_dirty_mark(true);
			Game_Data::quest_data_mgr::instance()->modi_quest_data( player_id, *qst );	

			upate_npc_quest_operate( player_id, quest_id, qst->get_quest_complete(),Game_Data::quest_data::QUEST_STATE_REMOVE, true );
			upate_npc_quest_operate( player_id, quest_id, qst->get_quest_complete(),Game_Data::quest_data::QUEST_STATE_SUBMITABLE);

			if(check_to_auto_submit_quest( player_id, quest_id, "giveitemtonpc" ))
			{
				vector<uint64> para_out;
				para_out.clear();
				para_out.push_back(player_id);
				para_out.push_back(quest_id);
				Game_Content_Interface::instance()->exec_interface("submitquest", para_out );
			}
				
			ret = true;
		}
		else  //quest not complete
		{

			//get quest data
			qst = NULL;
			qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
			if( qst == NULL )
				return ret;	
			if( Game_Data::quest_data::QUEST_STATE_SUBMITABLE == qst->get_quest_state() )//if submitable state ,change it
			{
				qst->set_quest_state(Game_Data::quest_data::QUEST_STATE_INPROCESS);
				qst->set_quest_dirty_mark(true);
				Game_Data::quest_data_mgr::instance()->modi_quest_data( player_id, *qst );	
				//to do:   update quest state, send to client, update to db
				upate_npc_quest_operate( player_id, quest_id, qst->get_quest_complete(),Game_Data::quest_data::QUEST_STATE_REMOVE);
				ret = false;
			}	
		}
			
		//if quest data dirty sign,  update
		//to do:   update quest state, send to client, update to db  
		Game_Data::quest_data* qst_up = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
		if( qst_up != NULL )
		{
			if( qst_up->get_quest_dirty_mark()   )
			{
				vector<uint64> para_out;
				para_out.clear();
				para_out.push_back(player_id);
				para_out.push_back(quest_id);
				Game_Content_Interface::instance()->exec_interface("updatequestcontent", para_out );
			}
		}
		return ret;
	}
	
	bool quest_logic::add_saved_quest( const uint player_id, const uint quest_id, const uint quest_state, const int ring_quest_bind_id, vector< unsigned int >& counter_vec )
	{
#ifdef GAME_SERVER
		if( game_data_exchange::instance()->is_quest_done( player_id, quest_id ))
		{
			return false;
		}
#else
        vector<uint64> para;
        para.clear();
        para.push_back( player_id);
        para.push_back( quest_id );
        if( Game_Logic::Game_Content_Interface::instance()->exec_interface("isquestdone", para) )
        {
            return false;
        }
#endif
		Game_Data::quest_data* qst = NULL;
		qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
		if( qst != NULL )
			return false;

		proc_add_player_quest( player_id, quest_id, ring_quest_bind_id, true );

		//get quest data
		qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
		if( qst == NULL )
			return false;
			
		//get quest content
		Game_Data::game_quest_content gqc;
		qst->get_quest_content( gqc );

		//get content element list
		Game_Data::game_element_list_t ge_vec;
		gqc.get_quest_element( ge_vec );	
		
		if( ge_vec.size() == counter_vec.size())
        {	

		    Game_Data::game_element_list_t::iterator itgv;
		    unsigned int i = 0;
		    for( itgv = ge_vec.begin(); itgv != ge_vec.end(); ++ itgv )
		    {
			    (*itgv).set_count(counter_vec[i]); ++i;
            }
        }

		gqc.set_quest_element(ge_vec);
		qst->set_quest_content(gqc);
		qst->set_quest_state(quest_state);
		qst->set_ring_quest_bind_id(ring_quest_bind_id);
		Game_Data::quest_data_mgr::instance()->modi_quest_data( player_id, *qst );
			
		//quest not complete
		if(!proc_analysis_quest( player_id, quest_id, true, Game_Interface::OPERATE_ADDSAVEDQUEST ))
		{
			//get quest data
			qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
			if( qst == NULL )
				return false;
				
			//if error quest complete state, reregister command function event of quest 
			if( Game_Data::quest_data::QUEST_STATE_SUBMITABLE == quest_state )
			{
				qst->set_quest_state(Game_Data::quest_data::QUEST_STATE_INPROCESS);
				Game_Data::quest_data_mgr::instance()->modi_quest_data( player_id, *qst );
					
				proc_analysis_quest_cmd_func_list( player_id, quest_id, true);
			}
		}
		//if quest completed, set to submitable state
		else if( Game_Data::quest_data::QUEST_STATE_SUBMITABLE != quest_state &&  Game_Data::quest_data::QUEST_STATE_FAIL != quest_state )
		{
			//get quest data
			qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
			if( qst == NULL )
				return false;

			qst->set_quest_state(Game_Data::quest_data::QUEST_STATE_SUBMITABLE);
			Game_Data::quest_data_mgr::instance()->modi_quest_data( player_id, *qst );

		}
		
		return true;
	}
	
	bool quest_logic::proc_quest_award( const uint player_id, const uint quest_id, const char * cmd )
	{
		//get quest data
		Game_Data::quest_data* qst = NULL;
		qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
		if( qst == NULL )
			return false;

        Game_Data::quest_data* org_qst = Game_Data::quest_data_mgr::instance()->get_org_quest_data( quest_id );

		Game_Data::game_quest_content gqc;
		org_qst->get_quest_award( gqc );

		do_proc_quest_award(player_id, quest_id, cmd, gqc.get_quest_element());

		//get content element list
		Game_Data::game_element_list_t ge_vec;
		if( !get_quest_content_element_list(player_id, quest_id, ge_vec ) )
			return false;	
			
		do_proc_quest_award(player_id, quest_id, cmd, ge_vec);

		return true;		
	}	

	bool quest_logic::do_proc_quest_award( const uint player_id, const uint quest_id, const char* cmd, const list<Game_Data::Game_Element>& game_ele_vec )
	{
		Game_Data::game_element_list_t tm_ge_vec = game_ele_vec;
		Game_Data::game_element_list_t::iterator itgv;

		for( itgv = tm_ge_vec.begin(); itgv != tm_ge_vec.end(); ++ itgv )
		{
			quest_interface_handler_map_t::iterator itgm;
			itgm = quest_award_func_interface_map_.find( cmd );
			if( !strcmp((*itgv).get_command(), cmd) && itgm != quest_award_func_interface_map_.end() )
			{
				Game_Interface gm_arg;
				gm_arg.set_reg_state(false);
				vector<uint64>  para;
				para.push_back( player_id );//player id
				para.push_back( quest_id );//quest id

				//add addition para
				vector<unsigned int> para_ele;
				para_ele.clear();
                (*itgv).get_para_list_in_vector(para_ele);
				vector<unsigned int>::iterator itvi;
				for( itvi = para_ele.begin(); itvi != para_ele.end(); ++ itvi )
				{
					para.push_back( *itvi );
				}
				gm_arg.set_para( para );

				//callback the function
				(itgm->second)( gm_arg, (*itgv) );

			}
		}
		return true;
	}
	bool quest_logic::set_quest_content_element_list (const uint player_id, const uint quest_id, list<Game_Data::Game_Element>& ge_vec )
	{
		//get quest data
		Game_Data::quest_data* qst = NULL;
		qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
		if( qst == NULL )
			return false;

		//get quest content
		Game_Data::game_quest_content gqc;
		qst->get_quest_content( gqc );

		gqc.set_quest_element(ge_vec);
		qst->set_quest_content(gqc);
		Game_Data::quest_data_mgr::instance()->modi_quest_data( player_id, *qst );
		return true;

	}
	bool quest_logic::get_quest_content_element_list(const uint player_id, const uint quest_id, list<Game_Data::Game_Element>& ge_vec )
	{
		//get quest data
		Game_Data::quest_data* qst = NULL;
		qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
		if( qst == NULL )
			return false;

		//get content element list
		ge_vec.clear();
		ge_vec  = qst->get_quest_content().get_quest_element( );

		return true;
	}
	
  void quest_logic::upate_npc_quest_operate( const uint32 player_id, const uint32 /*quest_id*/, const Game_Data::game_quest_content&/* qc*/,  const uint8 /*npc_opr*/, bool /*remove_other*/ )
	{

		vector<uint64> para; para.clear();

		para.clear();
		para.push_back(player_id);

		Game_Content_Interface::instance()->exec_interface("updatenpcquestopr",para);

	}
	void quest_logic::upate_npc_quest_operate_remove_other(	const uint32 player_id, const uint32 quest_id, const uint8 npc_opr, vector<uint>& para_vec )
	{
	   if( Game_Data::quest_data::QUEST_STATE_REMOVE != npc_opr )
		   return;

		get_content_element_id_by_key( player_id,  quest_id, para_vec, "dialogto" );
		get_content_element_id_by_key( player_id,  quest_id, para_vec, "giveitemtonpc" );

		Game_Data::quest_data* qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
		if( qst == NULL  ) //if quest exist
			return;

		if(Game_Data::quest_data::QUEST_STATE_SUBMITABLE !=  qst->get_quest_state() )
			return;

		uint32 ring_quest_id;
		if(is_ring_quest( quest_id, ring_quest_id )) //if ring quest
		{
			Game_Data::quest_data_mgr::instance()->get_org_quest_command_para( qst->get_ring_quest_bind_id(), "challenge", para_vec );
		}
		else
			Game_Data::quest_data_mgr::instance()->get_org_quest_command_para( quest_id, "challenge", para_vec );


	}

   	void quest_logic::get_content_element_id_by_key( const uint32 player_id,  const uint32 quest_id, vector<uint>& para_vec, const char*  keycontent )
	{
 		Game_Data::quest_data* qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id);
		if( qst == NULL )
			return;

	   	//get content element list
		Game_Data::game_element_list_t ge_vec = qst->get_quest_content().get_quest_element( );

		Game_Data::game_element_list_t::iterator itgv;
		for( itgv = ge_vec.begin(); itgv != ge_vec.end(); ++ itgv )
		{
			if( !strcmp((*itgv).get_command(), keycontent))
			{

				vector<unsigned int> para; para.clear(); 
                (*itgv).get_para_list_in_vector(para);
				if( para.size() < 2)
					continue;
	
				if( (*itgv).get_count() < para[1])
					continue;

				para_vec.push_back(para[0]);
			}
		}
	}
	bool quest_logic::process_update_ring_quest_content( const uint32 player_id, const uint32 quest_id, const uint32 /*ring_id*/,const uint32 select_ring_quest_id )
	{
		//get quest data
		Game_Data::quest_data* qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
		if( qst == NULL  ) //if quest exist
			return false; 

		Game_Data::quest_data* sel_qst = Game_Data::quest_data_mgr::instance()->get_org_quest_data( select_ring_quest_id );

		if( NULL == sel_qst )
			return false;

		Game_Data::quest_data tmp_qst = *qst;

		//add org quest content to select quest content
		Game_Data::game_quest_content sel_content = sel_qst->get_quest_content();
		Game_Data::game_quest_content org_content = qst->get_quest_content();

		Game_Data::game_command_element_vec_t org_gcev;
		org_content.get_quest_command_element(org_gcev);

		Game_Data::game_command_element_vec_t sel_gcev;
		sel_content.get_quest_command_element(sel_gcev);

		Game_Data::game_command_element_vec_t::iterator itg;
		for( itg = org_gcev.begin(); itg != org_gcev.end(); itg ++)
			sel_gcev.push_back((*itg));

		sel_content.set_quest_command_element(sel_gcev);
		//end of add org quest content to select quest content

		tmp_qst.set_quest_content(sel_content);		
		tmp_qst.set_quest_info( sel_qst->get_quest_info() );
		tmp_qst.set_ring_quest_bind_id( select_ring_quest_id );
		tmp_qst.set_quest_accept_dialog( sel_qst->get_quest_accept_dialog() );
		tmp_qst.set_quest_submit_dialog( sel_qst->get_quest_submit_dialog() );
		tmp_qst.set_quest_trace_exec( sel_qst->get_quest_trace_exec() );
		tmp_qst.set_quest_trace_comp( sel_qst->get_quest_trace_comp() );

		tmp_qst.set_quest_dirty_mark(true);
		Game_Data::quest_data_mgr::instance()->modi_quest_data( player_id, tmp_qst );	

		return true;
	}

	bool quest_logic::is_ring_quest( const uint quest_id, uint32& sel_quest_id )
	{

		vector<unsigned int> req_para;
		req_para.clear();
		//if ring bind quest, valide is can continue play the quest
		req_para.clear();
		Game_Data::quest_data_mgr::instance()->get_org_quest_command_para( quest_id, "ringbind", req_para);
		if( 0 != req_para.size() )
		{
			if( 0 != req_para[0] )
			{
				sel_quest_id = req_para[0];
				return true;
			}
		}
		return false;
	}
//////////////////////////////do compute/////////////////////////////////////////////////////////
    bool quest_logic::compute_equip_book_req_qa(const vector<unsigned int>& para,Game_Data::Game_Element& ge, 
                const uint player_id, const uint /*element_id*/)
   {
        if(para.size() < 2)
			return false;		
        uint qa = para[0];
        int count = (int)para[1]; int saved_count = count;
#ifdef GAME_SERVER
        if(Game_Logic::game_data_exchange::instance()->player_equip_book_count(player_id, count, qa))
        {
            if( count > saved_count )
                count = saved_count;
            ge.set_count(count);
			return true;
        }
        else 
        {
            ge.set_count(count);
            return true;
        }
#endif
        return false;
    }
 	bool quest_logic::compute_gerneral_req_qa(const vector<unsigned int>& para,Game_Data::Game_Element& ge, 
        const uint player_id, const uint /*element_id*/)
    {
        if(para.size() < 2)
			return false;		
        uint qa = para[0];
        int count = (int)para[1]; int saved_count = count;
#ifdef GAME_SERVER
        if(Game_Logic::game_data_exchange::instance()->player_have_general(player_id, count, qa))
        {
            if( count > saved_count )
                count = saved_count;
            ge.set_count(count);
			return true;
        }
        else
        {
             ge.set_count(count);
			return true;
        }
#endif
        return false;
    }

    bool quest_logic::compute_all_equip_req_qa(const vector<unsigned int>& para,Game_Data::Game_Element& ge, 
                const uint player_id, const uint /*element_id*/)
    {
        if(para.size() < 1)
			return false;		
        uint qa = para[0];

#ifdef GAME_SERVER
        if(Game_Logic::game_data_exchange::instance()->player_all_equipment_reach_quality(player_id, qa))
        {
            ge.set_count(1);
			return true;
        }
        else
        {
            ge.set_count(0);
            return true;
        }
#endif
        return false;
    }

    bool quest_logic::compute_skill_req_level     (const vector<unsigned int>& para,Game_Data::Game_Element& ge, 
                const uint player_id, const uint element_id)
    {
        if(para.size() < 2)
			return false;		
        uint level = para[0];
        int count = (int)para[1]; int saved_count = count;
#ifdef GAME_SERVER
        if(Game_Logic::game_data_exchange::instance()->player_have_skill(player_id, count, level))
        {
            if( count > saved_count )
                count = saved_count;
            ge.set_count(count);
			return true;
        }
     #endif
        return false;
    }
   bool quest_logic::compute_money_req        (const vector<unsigned int>& para,Game_Data::Game_Element& ge, 
                const uint player_id, const uint element_id)
   {
		if(para.size() < 1)
			return false;		
        uint money_count = 0;
#ifdef GAME_SERVER
		money_count = (uint)Game_Logic::game_data_exchange::instance()->get_player_money(player_id );
#endif
		if( (unsigned long)money_count <= para[0] && money_count != ge.get_count() )
		{
			ge.set_count(money_count);
			return true;
		}
		else if ((unsigned long)money_count > para[0] &&  money_count != ge.get_count() )
		{
			ge.set_count(para[0]);
			return true;
		}	
		return false;	
       return false;
   }

   bool quest_logic::compute_equip_item_all(const vector<unsigned int>& para,Game_Data::Game_Element& ge, 
       const uint player_id, const uint /*element_id*/)
   {
#ifdef GAME_SERVER
       if(PLAYER_LOGIC::instance()->check_equipitem_all(player_id))
       {
           ge.set_count(1);
           return true;
       }
       else
       {
           ge.set_count(0);
           return true;
       }
#endif
       return false;
   }

	bool quest_logic::compute_friends(const vector<unsigned int>& para,Game_Data::Game_Element& ge, 
        const uint player_id, const uint /*element_id*/)
    {
		if(para.size() < 1)
			return false;		
        uint friends_count = 0;
#ifdef GAME_SERVER
		friends_count = (uint)Game_Logic::game_data_exchange::instance()->get_friends_count(player_id );
#endif
		if( (unsigned long)friends_count <= para[0] && friends_count != ge.get_count() )
		{
			ge.set_count(friends_count);
			return true;
		}
		else if ((unsigned long)friends_count > para[0] &&  friends_count != ge.get_count() )
		{
			ge.set_count(para[0]);
			return true;
		}	
		return false;	
    }
	bool quest_logic::compute_item_count(const vector<unsigned int>& para,Game_Data::Game_Element& ge, const uint player_id, const uint element_id )
	{
		if(para.size() < 2)
			return false;		
        uint item_count = 0;
#ifdef GAME_SERVER
		item_count = game_data_exchange::instance()->get_item_amount_by_id(player_id,element_id );
#endif
		if( (unsigned long)item_count <= para[1] && item_count != ge.get_count() )
		{
			ge.set_count(item_count);
			return true;
		}
		else if ((unsigned long)item_count > para[1] &&  item_count != ge.get_count() )
		{
			ge.set_count(para[1]);
			return true;
		}	
		return false;	
	}
	
	bool quest_logic::compute_useanyitem_count(const vector<unsigned int>& para,Game_Data::Game_Element& ge,const uint /*player_id*/, const uint element_id )
	{	
		vector<unsigned int> tmp_para = para;
		vector<unsigned int>::iterator iti = find(tmp_para.begin(), tmp_para.end(),(unsigned int)element_id);
		if( iti == tmp_para.end() )
			return false;
			
		if( (unsigned int)ge.get_count() < para[0] )
		{
			ge.count_add();
			return true;
		}		
		return false;
	}
  bool quest_logic::compute_monsterbylevel_count(const vector<unsigned int>& para,Game_Data::Game_Element& ge,const uint player_id, const uint /*element_id*/ )
	{
		if(para.size() < 3)
			return false;
       uint monster_level = 0, player_level = 0;
#ifdef GAME_SERVER
		player_level	= game_data_exchange::instance()->get_player_level(player_id);				
#endif	
		//if kill enough monster, need not count
		if((unsigned int)ge.get_count() >= para[0])
			return false;
			
		bool modi_b = false;

		uint level_down	= (uint)para[1];
		uint level_up	= (uint)para[2];
		if ( player_level >= monster_level && (player_level - monster_level ) <= level_down )
		{						
			modi_b = true;
		}
		else if ( monster_level >= player_level && ( monster_level - player_level ) <= level_up )
		{
			modi_b = true;	
		}
		if( modi_b )
		{
			ge.count_add();
			return true;
		}		
		return false;
	}

  bool	quest_logic::compute_giveitemtonpc_count( const vector<unsigned int>& para, Game_Data::Game_Element& ge,const uint /*player_id*/, const uint element_id, const vector<uint64>& para_org )
   {
	   if( para.size() < 3 )
		   return false;

	   uint32 req_npc_id = (uint32)para[0];
	   uint32 req_item_id = (uint32)para[1];
	   uint32 req_item_count = (uint32)para[2];

	   if( req_npc_id != element_id )
		   return false;

	   if( para_org.size() < 7 )
		   return false;
	   uint32 item_id	= (uint32)para_org[3];
	   uint32 item_count = (uint32)para_org[4];

	   //uint32 item_idx	= (uint32)para_org[5];
	   // uint32 item_pos = (uint32)para_org[6];
	   if( item_id != req_item_id )
		   return false;

	   if( item_count != req_item_count )
		   return false;

	   //game_data_exchange::instance()->remove_player_item_by_pos( player_id, item_idx,item_pos, item_count);

	   ge.set_count( item_count );
	   return true;
   }

	bool quest_logic::check_to_auto_submit_quest( const uint player_id, const uint quest_id, const char* key_content )
	{
 		Game_Data::quest_data* qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id);
		if( qst == NULL )
			return false;

	   	//get content element list
		Game_Data::game_element_list_t ge_vec = qst->get_quest_content().get_quest_element( );

		Game_Data::game_element_list_t::iterator itgv;
		for( itgv = ge_vec.begin(); itgv != ge_vec.end(); ++ itgv )
		{
			if( !strcmp((*itgv).get_command(), key_content))
			{
				return true;
			}
		}

		return false;
	}

	void quest_logic::send_msg_radiate_player(uint32 player_id,uint quest_id)
	{
#ifdef GAME_SERVER
		char buff[512] ={0};
		char str[65] = {0};
		Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
		Game_Data::quest_data* qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
		if (qst == NULL)
		{
			return;
		}
		
		std::string player_name(player->get_character_name());
		std::string quest_name(qst->get_quest_name());
		message_stream msg_radiate(buff,sizeof(buff));
		msg_radiate << 7;
		msg_radiate << 1;
		msg_radiate << quest_id;
		msg_radiate << player_name;
		msg_radiate << quest_name;
		SVC_CONFIG::instance()->get_gate_svc()->send_msg(INNER_RADIATE_PLAYER,0,0,&msg_radiate);
#endif
	}

}


