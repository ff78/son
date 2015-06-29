
#include "Game_Interface/game_content_interface.h"
#ifdef GAME_SERVER
#include "game_interface/game_data_exchange.h"
#endif
#include "quest_system/quest_data/quest_data_mgr.h"

//#include "npc_system/npc_data/npc_data_mgr.h"
//#include "area_system/area_data/area_data_mgr.h"

#include "quest_npc_logic.h"
#ifdef GAME_SERVER
#include "quest_system/quest_logic/quest_logic.h"
#endif

#ifdef GAME_CLIENT
#include "Common/Game_Utils.h"
#endif
#include "Common/Utils.h"
namespace Game_Logic
{
	quest_npc_logic* quest_npc_logic::instance_p_ = 0;
	quest_npc_logic::quest_npc_logic(){

	}

	quest_npc_logic::~quest_npc_logic()
	{

	}

	quest_npc_logic* quest_npc_logic::instance()
	{
		if( NULL == instance_p_ )
		{
			instance_p_ = new  quest_npc_logic;
		}
		
		return instance_p_;
	}

    bool quest_npc_logic::proc_npc_list_quest_bind( Game_Interface& gm_interface )
    {
        //printf("quest_npc_logic::proc_npc_list_quest_bind\n");
        vector<uint64> para;
		
		
		gm_interface.get_para(para);
        if( para.size() < 2 )
            return false;

        int player_id = (int)para[0];
        int npc_size = (int)para[1];
        if( (int)para.size() < 2 + npc_size)
            return false;

        vector<int> npc_lst;
        for ( uint i = 0 ; i < (uint )npc_size; i ++ )
        {
            npc_lst.push_back((int)para[i+2]);
        }

         instance()->proc_analysis_npc_list_quest_bind( player_id, npc_lst);
		 return true;
    }

	bool quest_npc_logic::proc_npc_quest_bind( Game_Interface& gm_interface )
	{
		vector<uint64> para;
		
		gm_interface.get_para(para);
		if( para.size() < 1 )
			return false;
		uint32 player_id = (uint32)para[0];
		vector<int>	npc_vec;
		npc_vec.clear();
	
#ifdef GAME_CLIENT
    map<int,int> npc_map;
    map<int,int>::iterator iti;

    Game_Utils::instance()->get_npc_list( npc_map );
    for( iti = npc_map.begin(); iti != npc_map.end(); ++iti)
    {
        npc_vec.push_back(iti->first);
    }
#else
      Game_Data::quest_data_mgr::instance()->add_player_current_npc_lst( player_id,  npc_vec);
#endif
		
        instance()->proc_analysis_npc_list_quest_bind( player_id, npc_vec);
		return true;
	}

    int quest_npc_logic::proc_analysis_npc_list_quest_bind( const uint32 player_id, vector<int> npc_lst )
    {
		Game_Data::npc_bind_quest nbq_temp;
		vector<int>::iterator itvn;
		vector<uint32> accept_qst_lst;
		vector<uint32> submit_qst_lst;
		vector<uint32> challenge_qst_lst;
        vector<uint32> inprocess_qst_lst;
		
		
		for( itvn = npc_lst.begin(); itvn != npc_lst.end(); itvn ++ )
		{
			Game_Data::npc_bind_quest* nbq= Game_Data::quest_data_mgr::instance()->get_npc_quest_bind_data( *itvn );
			if( NULL == nbq )
				continue;

			//proc accept quest list
			nbq->get_accept_quest_list(accept_qst_lst);
			instance()->proc_check_quest_list( player_id, accept_qst_lst, "iscanacceptquest", false);

			//proc submit quest list
			nbq->get_submit_quest_list( submit_qst_lst);
			instance()->proc_check_quest_list( player_id, submit_qst_lst, "iscansubmitquest", false);

			//proc challenge quest list
			nbq->get_challenge_quest_list( challenge_qst_lst );
			instance()->proc_check_quest_in_proc_list( player_id, challenge_qst_lst, "challenge");

			//proc inprocess quest list
			nbq->get_accept_quest_list( inprocess_qst_lst );
			instance()->proc_check_quest_in_proc_list( player_id, inprocess_qst_lst, "inprocess");
			
			nbq_temp.reset();
			nbq_temp.set_npc_id(*itvn);
			nbq_temp.set_accept_quest_list( accept_qst_lst );
			nbq_temp.set_submit_quest_list( submit_qst_lst );
			nbq_temp.set_challenge_quest_list(challenge_qst_lst);
            nbq_temp.set_inprocess_quest_list(inprocess_qst_lst);

			if( 0 != accept_qst_lst.size() || 0 != submit_qst_lst.size() || 0 !=  inprocess_qst_lst.size())
				Game_Data::quest_data_mgr::instance()->add_player_npc_quest_bind_data(player_id, nbq_temp);
			
		}
		//check self accepted ring quest bind data
		instance()->check_accepted_quest_bind(player_id);

		//send acceptable quest list and submitable quest list for npc state set
		vector<uint64> para_out; para_out.clear();
		para_out.push_back( player_id );
		Game_Content_Interface::instance()->exec_interface("updatenpcquestlist",para_out);
        return 0;
    }
	void quest_npc_logic::check_accepted_quest_bind(const uint32 player_id)
	{
		Game_Data::quest_data::quest_data_vec_t qst_list = Game_Data::quest_data_mgr::instance()->get_quest_data_list( player_id );
		Game_Data::quest_data::quest_data_vec_t::iterator itq;
		vector<uint32> para_vec;
		vector<uint32> quest_id_lst;
		Game_Data::npc_bind_quest nbq_temp;
		
		
		for ( itq = qst_list.begin(); itq  != qst_list.end(); itq ++ )
		{
			check_accepted_quest_key_element_bind( player_id, (*itq).get_quest_id(), "dialogto");
			check_accepted_quest_key_element_bind( player_id, (*itq).get_quest_id(), "giveitemtonpc");
			para_vec.clear();

			if( Game_Data::quest_data::QUEST_STATE_SUBMITABLE == (*itq).get_quest_state() )
				continue;

			Game_Data::quest_data_mgr::instance()->get_org_quest_command_para( (*itq).get_ring_quest_bind_id(), "challenge", para_vec );
			if( 0 == para_vec.size() )
				continue;

			uint32 npc_id = para_vec[0];
			if( 0 == npc_id )
				continue;

			quest_id_lst.push_back((*itq).get_quest_id());
			nbq_temp.reset();
			nbq_temp.set_npc_id(npc_id);
			nbq_temp.set_challenge_quest_list(quest_id_lst);
			Game_Data::quest_data_mgr::instance()->add_player_npc_quest_bind_data(player_id, nbq_temp);

		}
	}
	void quest_npc_logic::check_accepted_quest_key_element_bind( const uint32 player_id, const uint32 quest_id, const char* key_content )
	{
 		Game_Data::quest_data* qst = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id);
		
		if( qst == NULL )
			return;

		if( Game_Data::quest_data::QUEST_STATE_SUBMITABLE == qst->get_quest_state()	 )
			return;

	   	//get content element list
		Game_Data::game_element_list_t ge_vec = qst->get_quest_content().get_quest_element( );

		vector<uint32> quest_id_lst;
		Game_Data::npc_bind_quest nbq_temp;
		Game_Data::game_element_list_t::iterator itgv;
		for( itgv = ge_vec.begin(); itgv != ge_vec.end(); ++ itgv )
		{
			quest_id_lst.clear();
			if( !strcmp((*itgv).get_command(), key_content))
			{
				quest_id_lst.push_back( quest_id);
		  		nbq_temp.reset();
				vector<unsigned int> para;
				para.clear(); 
                (*itgv).get_para_list_in_vector(para);
				if( para.size() < 2)
					continue;
				if( (*itgv).get_count() >= para[1])
					continue;
				nbq_temp.set_npc_id(para[0]);
				if(	!strcmp("dialogto", key_content))
					nbq_temp.set_dialog_quest_list(quest_id_lst);
				if(	!strcmp("giveitemtonpc", key_content))
					nbq_temp.set_give_item_to_npc_quest_list(quest_id_lst);
				Game_Data::quest_data_mgr::instance()->add_player_npc_quest_bind_data(player_id, nbq_temp);
			}
		}

	}
	void quest_npc_logic::proc_check_quest_in_proc_list(const uint32 player_id, vector<uint32>& qst_lst,const char* key)
	{
		string key_str = key;
		vector<uint64> para_out;
		vector<uint32>::iterator itvu;
		
		
		for( itvu = qst_lst.begin(); itvu != qst_lst.end();)
		{
			para_out.clear();
			para_out.push_back( player_id);para_out.push_back((*itvu));
			if( !Game_Content_Interface::instance()->exec_interface("isquestinprocess", para_out)) //can not accepted or can not submit, ignor
			{
				itvu = qst_lst.erase(itvu);
				if(itvu == qst_lst.end() )
					break;
				else
					continue;
			}
			itvu++;
		}
	}

	void quest_npc_logic::proc_check_quest_list(const uint32 player_id, vector<uint32>& qst_lst,const char* key, bool send_update) //check quest can be accepted or be submit
	{
		string key_str = key;
		vector<uint64> para_out;
		vector<uint32>::iterator itvu;
		
		
		for( itvu = qst_lst.begin(); itvu != qst_lst.end();)
		{
			para_out.clear();
			para_out.push_back( player_id);para_out.push_back((*itvu)); 
            if( send_update)
                para_out.push_back(1);
            else
                para_out.push_back(0);
			if( !Game_Content_Interface::instance()->exec_interface(key, para_out)) //can not accepted or can not submit, ignor
			{
				itvu = qst_lst.erase(itvu);
				if(itvu == qst_lst.end() )
					break;
				else 
					continue;
			}

			//if sended, ignor
			if(!key_str.compare("iscansubmitquest") || Game_Data::quest_data_mgr::instance()->is_in_quest_acceptable_list(player_id, (*itvu)))
			{
				itvu++;
				continue;
			}

			Game_Data::quest_data_mgr::instance()->add_acceptable_quest_id(player_id, (*itvu));
			itvu++;

		}
	}

}
