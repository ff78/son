#include "quest_data_mgr.h"
#include "quest_json_config.h"

#ifdef GAME_SERVER 
	#include "logger.h"
	static cute::logger *quest_data_mgr_log =
		cute::log_manager::instance()->get_logger("root.quest_data_mgr");
#endif

namespace Game_Data
{
 
	quest_data_mgr* quest_data_mgr::m_pInstance = 0;

	quest_data_mgr::quest_data_mgr(void)
	{
#ifdef YN_LINUX		
		pthread_mutex_init(&quest_data_mutex_,NULL);
#endif
	}

	quest_data_mgr::~quest_data_mgr(void)
	{
#ifdef YN_LINUX			
		pthread_mutex_destroy(&quest_data_mutex_);
#endif		
		quest_data_map_.clear();

		if( m_pInstance )
			delete m_pInstance;
	}

	quest_data_mgr* quest_data_mgr::instance(void)
	{
		if( NULL == m_pInstance )
		{
			m_pInstance = new quest_data_mgr;
		}
		
		return m_pInstance;
	}

	void quest_data_mgr::reload( void )
	{
		quest_config::instance()->load_config(quest_static_data_map_, root_str_.data() );
	}
	void quest_data_mgr::init(  const char *root  )
	{
		root_str_.clear();
		root_str_ = root;		
		quest_acceptable_data_map_.clear();
		
		quest_complete_data_map_.clear();
		quest_data_map_.clear();
		
		quest_data_vec_tmp_.clear();
		player_npc_bind_quest_.clear();
		npc_bind_quest_list_.clear();

        player_current_npc_lst_.clear();

		quest_config::instance()->load_config(quest_static_data_map_, root );
		proc_analysis_npc_quest_bind_list();

	}

    void quest_data_mgr::release ( void )
    {
        root_str_.clear();
        quest_acceptable_data_map_.clear();

        quest_complete_data_map_.clear();
        quest_data_map_.clear();

        quest_data_vec_tmp_.clear();
        player_npc_bind_quest_.clear();
        npc_bind_quest_list_.clear();
    }

	void quest_data_mgr::proc_analysis_npc_quest_bind_list( void )
	{
#ifdef YN_LINUX		
	  //	         Game_Logic::map_mutex m(&quest_data_mutex_);
#endif
		npc_bind_quest nbq;
		uint32 npc_accept_id = 0, npc_submit_id = 0;
		vector< uint32> npc_dialog_id_list;
		quest_data::quest_one_data_map_t::iterator itqm;
		for( itqm = quest_static_data_map_.begin(); itqm != quest_static_data_map_.end(); itqm ++ )
		{
			npc_bind_quest* nbq_accept_p = NULL;


			npc_accept_id = get_quest_bind_npc_id(itqm->second.get_quest_id(), itqm->second.get_quest_accept(),"npctalk");
			nbq.reset();
			nbq_accept_p = get_npc_quest_bind_data(npc_accept_id);
			if(NULL != nbq_accept_p)
			{
				nbq = *nbq_accept_p;
			}	

			if( 0 != npc_accept_id )
			{
				nbq.add_accept_quest_list( itqm->second.get_quest_id());
				nbq.set_npc_id(npc_accept_id );
				add_npc_quest_bind_data(nbq);
			}

			npc_submit_id = get_quest_bind_npc_id(itqm->second.get_quest_id(), itqm->second.get_quest_complete(), "npctalk");
			nbq.reset();
			npc_bind_quest* nbq_submit_p = NULL;
			 nbq_submit_p = get_npc_quest_bind_data(npc_submit_id);
			if(NULL != nbq_submit_p)
			{
				nbq = *nbq_submit_p;
			}

			if( 0 != npc_submit_id )
			{
				nbq.add_submit_quest_list( itqm->second.get_quest_id());
				nbq.set_npc_id(npc_submit_id );
				add_npc_quest_bind_data(nbq);
			}

			vector<uint> para_vec; para_vec.clear();
			get_org_quest_command_para( itqm->second.get_quest_id(), "challenge", para_vec );
			vector<uint>::iterator itu;
			for( itu = para_vec.begin(); itu != para_vec.end(); itu ++)
			{
				npc_bind_quest* nbq_challenge_p = NULL;
				nbq.reset();
				nbq_challenge_p = get_npc_quest_bind_data((*itu));
				if( NULL != nbq_challenge_p)
				{					
					nbq = *nbq_challenge_p;
				}		
				nbq.add_challenge_quest_list(itqm->second.get_quest_id());
				nbq.set_npc_id( *itu);
				add_npc_quest_bind_data(nbq);

			}

			npc_dialog_id_list.clear(); 
            get_quest_dialog_npc_id( itqm->second.get_quest_id(), itqm->second.get_quest_content(), npc_dialog_id_list );
			if( 0 != npc_dialog_id_list.size() )
			{
				vector<uint>::iterator itv;
				for( itv = npc_dialog_id_list.begin(); itv != npc_dialog_id_list.end(); itv ++ )
				{
					nbq.reset();
					npc_bind_quest* nbp_dialog_p = NULL;
					nbp_dialog_p = get_npc_quest_bind_data((*itv));
					if(NULL != nbp_dialog_p)
					{
						nbq = *nbp_dialog_p;
					}
					nbq.add_dialog_quest_list((*itv));
					add_npc_quest_bind_data(nbq);
				}
			}
		}
	}

	uint32 quest_data_mgr::get_quest_bind_npc_id( uint32 /*quest_id*/, const game_quest_content& qc, const char* cmp_key )
	{
#ifdef YN_LINUX		
	 	   Game_Logic::map_mutex m(&quest_data_mutex_);
#endif
		game_element_list_t::iterator itge;
		game_element_list_t gev; gev.clear();
		game_quest_content qc_tmp = qc;
		gev  = qc.get_quest_element();
		string key;
		for( itge = gev.begin(); itge != gev.end(); itge ++ )
		{
			key.clear(); key = (*itge).get_command();
			if( !key.compare(cmp_key))
            {
				vector<uint> para;
                (*itge).get_para_list_in_vector(para);
                if( para.size() > 0 )
                    return para[0];
            }
		}
		return 0;
	}

	void quest_data_mgr::get_quest_dialog_npc_id( uint32 /*quest_id*/, const game_quest_content& /*qc*/,vector<uint32> /*npc_id_lst*/ )
	{
	}
	void quest_data_mgr::add_npc_quest_bind_data( const npc_bind_quest& nbq)
	{
#ifdef YN_LINUX		
	   Game_Logic::map_mutex m(&quest_data_mutex_);
#endif
		npc_bind_quest::npc_bind_quest_map_t::iterator itbq;
		itbq = npc_bind_quest_list_.find( nbq.get_npc_id() );
		if(itbq != npc_bind_quest_list_.end() )
		{
			itbq->second = nbq;
		}
		else
		{
			npc_bind_quest_list_.insert(make_pair( nbq.get_npc_id(), nbq ));
		}

	}
    int quest_data_mgr::get_npc_quest_bind_data  ( const uint32 npc_id, npc_bind_quest& nbq )
    {
#ifdef YN_LINUX		
     Game_Logic::map_mutex m(&quest_data_mutex_);
#endif
        npc_bind_quest::npc_bind_quest_map_t::iterator itbq;
		itbq = npc_bind_quest_list_.find( npc_id);
		if(itbq != npc_bind_quest_list_.end())
        {
            nbq = itbq->second;
            return 0;
        }
        return -1;
    }
	npc_bind_quest* quest_data_mgr::get_npc_quest_bind_data( const uint32 npc_id )
	{
#ifdef YN_LINUX		
	   Game_Logic::map_mutex m(&quest_data_mutex_);
#endif
		npc_bind_quest::npc_bind_quest_map_t::iterator itbq;
		itbq = npc_bind_quest_list_.find( npc_id);
		return itbq != npc_bind_quest_list_.end() ? &itbq->second : NULL;
	}

	void quest_data_mgr::add_player_npc_quest_bind_data( uint32 player_id, const npc_bind_quest& nbq )
	{
#ifdef YN_LINUX		
	  Game_Logic::map_mutex m(&quest_data_mutex_);
#endif
		npc_bind_quest::multi_npc_bind_quest_map_t::iterator itmn;
		itmn = player_npc_bind_quest_.find(player_id);
		if(itmn == player_npc_bind_quest_.end())
		{
			npc_bind_quest::npc_bind_quest_vec_t npc_bind_list;
			npc_bind_list.clear();
			npc_bind_list.push_back(nbq);
			player_npc_bind_quest_.insert(make_pair( player_id, npc_bind_list));

		}
		else 
		{
			itmn->second.push_back(nbq);
		}
	}
	void quest_data_mgr::get_player_npc_quest_bind_data( uint32 player_id, npc_bind_quest::npc_bind_quest_vec_t& npc_bind_list )
	{
#ifdef YN_LINUX		
	   Game_Logic::map_mutex m(&quest_data_mutex_);
#endif
		npc_bind_list.clear();
		npc_bind_quest::multi_npc_bind_quest_map_t::iterator itmn;
		itmn = player_npc_bind_quest_.find(player_id);
		if(itmn != player_npc_bind_quest_.end())
		{
			npc_bind_list = itmn->second;
		}
	}
	void quest_data_mgr::remove_player_npc_quest_bind_data( uint32 player_id )
	{
#ifdef YN_LINUX		
	         Game_Logic::map_mutex m(&quest_data_mutex_);
#endif
		npc_bind_quest::multi_npc_bind_quest_map_t::iterator itmn;
		itmn = player_npc_bind_quest_.find(player_id);
		if(itmn != player_npc_bind_quest_.end())
		{
			player_npc_bind_quest_.erase(itmn);
		}
	}

	void quest_data_mgr::clear_player_quest_data(const int player_id)
	{	
	  remove_player_acceptable_quest(player_id);
#ifdef YN_LINUX		
	   Game_Logic::map_mutex m(&quest_data_mutex_);
#endif	
		quest_data::quest_data_map_t::iterator itqm;
		itqm = quest_data_map_.find( player_id );
		if( itqm != quest_data_map_.end() )
		{
			quest_data_map_.erase(itqm);
		}
				
	}
	void quest_data_mgr::addquest( const int player_id, const quest_data& qd )
	{
#ifdef YN_LINUX		
        Game_Logic::map_mutex m(&quest_data_mutex_);
#endif		
		quest_data::quest_data_map_t::iterator itqm;
		itqm = quest_data_map_.find( player_id );
		if( itqm != quest_data_map_.end() )
		{

			quest_data::quest_data_vec_t::iterator itqv;
			itqv = find_if( itqm->second.begin(), itqm->second.end(), bind2nd( equal_to<quest_data>(), quest_data(qd.get_quest_id()) ));

			if( itqv == itqm->second.end())
				itqm->second.push_back(qd);
		}			
		else
		{
			quest_data::quest_data_vec_t qd_vec;
			qd_vec.clear();
			qd_vec.push_back(qd);
			quest_data_map_.insert(make_pair(player_id, qd_vec ));			
		}
	}
	void quest_data_mgr::removequest( const int player_id, const int quest_id )
	{
#ifdef YN_LINUX		
        Game_Logic::map_mutex m(&quest_data_mutex_);
#endif			
		quest_data::quest_data_map_t::iterator itqm;
		itqm = quest_data_map_.find( player_id );

		if( itqm != quest_data_map_.end() )
		{
			quest_data::quest_data_vec_t::iterator itqv;
			itqv = find_if( itqm->second.begin(), itqm->second.end(), bind2nd( equal_to<quest_data>(), quest_data(quest_id) ));

			if( itqv !=  itqm->second.end())
				itqm->second.erase(itqv);
		}

	}
	void quest_data_mgr::clear_quest_dirty_mark( const int player_id, const int quest_id )
	{
#ifdef YN_LINUX		
		Game_Logic::map_mutex m(&quest_data_mutex_);
#endif			
		quest_data::quest_data_map_t::iterator itqm;
		itqm = quest_data_map_.find( player_id );

		if( itqm != quest_data_map_.end() )
		{
			quest_data::quest_data_vec_t::iterator itqv;
			itqv = find_if( itqm->second.begin(), itqm->second.end(), bind2nd( equal_to<quest_data>(), quest_data(quest_id)));

			if( itqv !=  itqm->second.end())
			{
				if( 0 != (*itqv).get_quest_dirty_mark())
					(*itqv).set_quest_dirty_mark( 0 );
			}
		}
	}
	void quest_data_mgr::modi_quest_data(  const int player_id, const quest_data& qd )
	{
#ifdef YN_LINUX		
		Game_Logic::map_mutex m(&quest_data_mutex_);
#endif			
		quest_data::quest_data_map_t::iterator itqm;
		itqm = quest_data_map_.find( player_id );

		if( itqm != quest_data_map_.end() )
		{
			quest_data::quest_data_vec_t::iterator itqv;
			itqv = find_if( itqm->second.begin(), itqm->second.end(), bind2nd( equal_to<quest_data>(), quest_data(qd.get_quest_id())));

			if( itqv !=  itqm->second.end())
			{
				if( 0 == (*itqv).get_quest_dirty_mark())
					(*itqv).set_quest_dirty_mark( 1 );
				(*itqv) = qd;
			}
		}
	}
	quest_data* quest_data_mgr::get_quest_data( const int player_id, const int quest_id )
	{
#ifdef YN_LINUX		
	 	Game_Logic::map_mutex m(&quest_data_mutex_);
#endif			
		quest_data::quest_data_map_t::iterator itqm;
		itqm = quest_data_map_.find( player_id );
		if( itqm != quest_data_map_.end() )
		{
			quest_data::quest_data_vec_t::iterator itqv;
			itqv = find_if( itqm->second.begin(), itqm->second.end(), bind2nd( equal_to<quest_data>(), quest_data(quest_id) ));

			if( itqv != itqm->second.end() )
			{
				return &(*itqv);
			}
		}		
		return NULL;		
	}
	quest_data::quest_data_vec_t quest_data_mgr::get_quest_data_list( const int player_id )
	{
#ifdef YN_LINUX		
	 	Game_Logic::map_mutex m(&quest_data_mutex_);
#endif			
		quest_data::quest_data_map_t::iterator itqm;
		itqm = quest_data_map_.find( player_id );
		if( itqm != quest_data_map_.end() )
		{
			return itqm->second;	
		}
		
		return quest_data_vec_tmp_;
	}
	quest_data* quest_data_mgr::get_org_quest_data( const int quest_id )
	{
		//Game_Logic::map_mutex m(&quest_data_mutex_);
		quest_data::quest_one_data_map_t::iterator itqm;
		itqm = quest_static_data_map_.find( quest_id );
		return (itqm != quest_static_data_map_.end()) ? &(itqm->second) : NULL;	
	}
    int quest_data_mgr::get_org_quest_data( const int quest_id, quest_data& qd )
    {
		quest_data::quest_one_data_map_t::iterator itqm;
		itqm = quest_static_data_map_.find( quest_id );
		if (itqm != quest_static_data_map_.end())
        {
          qd = itqm->second;
          return 0;
        }
        return -1;
    }
	void quest_data_mgr::get_org_quest_command_para( const int quest_id_n, const char* command_c, vector< unsigned int >& para_vec )
	{
		//Game_Logic::map_mutex m(&quest_data_mutex_);
		quest_data::quest_one_data_map_t::iterator itqm;
		itqm = quest_static_data_map_.find( quest_id_n );
		if( itqm != quest_static_data_map_.end() )
		{
			quest_data qst = itqm->second;
			Game_Data::game_quest_content gqc;
			qst.get_quest_content( gqc );

			Game_Data::game_command_element_vec_t gce_vec;
			gqc.get_quest_command_element(gce_vec);

			Game_Data::game_command_element_vec_t::iterator itgc;
			Game_Data::game_element_list_t ge_vec;
			Game_Data::game_element_list_t::iterator itgv;

			for( itgc = gce_vec.begin(); itgc != gce_vec.end(); ++ itgc )
			{	
				ge_vec.clear();
				(*itgc).get_game_element_data(ge_vec);

				for( itgv = ge_vec.begin(); itgv != ge_vec.end(); ++ itgv )
				{
					if( !strcmp((*itgv).get_command(), command_c) )
					{
                        (*itgv).get_para_list_in_vector(para_vec);
						return;
					}
				}
			}
		}
	}
	
	int  quest_data_mgr::get_org_quest_counter_size ( const int quest_id_n )
	{
		quest_data::quest_one_data_map_t::iterator itqm;
		itqm = quest_static_data_map_.find( quest_id_n );
		if( itqm != quest_static_data_map_.end() )
		{
			quest_data qst = itqm->second;
			
			//get quest content
			Game_Data::game_quest_content gqc;
			qst.get_quest_content( gqc );
			//get content element list
			Game_Data::game_element_list_t ge_vec; ge_vec.clear();
			gqc.get_quest_element( ge_vec );	
			return ge_vec.size();
		}
		return 0;
	}

	///////////////
	void quest_data_mgr::add_acceptable_quest_id( const int player_id, const int quest_id )
	{	
#ifdef YN_LINUX		
	 	Game_Logic::map_mutex m(&quest_data_mutex_);
#endif			
		quest_state_data::qst_st_data_map_t::iterator itqm;
		itqm = quest_acceptable_data_map_.find( player_id );
		if( itqm != quest_acceptable_data_map_.end())
		{
			quest_state_data::qst_st_data_vec_t::iterator itqv = find_if(itqm->second.begin(), itqm->second.end(), bind2nd( equal_to<quest_state_data>(), quest_state_data(quest_id) ));
			if(itqv == itqm->second.end())
				itqm->second.push_back( quest_id);
		}
		else 
		{
			quest_state_data::qst_st_data_vec_t  qst_apt_data_vec;
			qst_apt_data_vec.clear();
			qst_apt_data_vec.	push_back(quest_state_data(quest_id));
			quest_acceptable_data_map_.insert(make_pair(player_id, qst_apt_data_vec ));
		}
	}
	void quest_data_mgr::remove_acceptable_quest_id( const int player_id, const int quest_id )
	{
#ifdef YN_LINUX		
	 		Game_Logic::map_mutex m(&quest_data_mutex_);
#endif			
		quest_state_data::qst_st_data_map_t::iterator itqm;
		itqm = quest_acceptable_data_map_.find( player_id );
		if( itqm != quest_acceptable_data_map_.end())
		{
				quest_state_data::qst_st_data_vec_t::iterator itqv = find_if(itqm->second.begin(), itqm->second.end(), bind2nd( equal_to<quest_state_data>(), quest_state_data(quest_id) ));
				if(itqv != itqm->second.end())
					itqm->second.erase(itqv);
		}
	}
	bool quest_data_mgr::is_in_quest_acceptable_list( const int player_id, const int quest_id )
	{
#ifdef YN_LINUX		
	 	Game_Logic::map_mutex m(&quest_data_mutex_);
#endif			
		quest_state_data::qst_st_data_map_t::iterator itqm;
		itqm = quest_acceptable_data_map_.find( player_id );
		if( itqm != quest_acceptable_data_map_.end())
		{
				quest_state_data::qst_st_data_vec_t::iterator itqv = find_if(itqm->second.begin(), itqm->second.end(), bind2nd( equal_to<quest_state_data>(), quest_state_data(quest_id) ));
				if(itqv != itqm->second.end())
					return true;
		}
		return false;
	}
	void quest_data_mgr::get_acceptable_quest_list( const int player_id, quest_state_data::qst_st_data_vec_t&  qst_apt_data_vec )
	{
#ifdef YN_LINUX		
	  //	Game_Logic::map_mutex m(&quest_data_mutex_);
#endif			
		qst_apt_data_vec.clear();
		quest_state_data::qst_st_data_map_t::iterator itqm;
		itqm = quest_acceptable_data_map_.find( player_id );
		if( itqm != quest_acceptable_data_map_.end())
		{
			qst_apt_data_vec = itqm->second;
		}
	}
	void quest_data_mgr::remove_player_acceptable_quest( const int player_id )
	{
#ifdef YN_LINUX		
		Game_Logic::map_mutex m(&quest_data_mutex_);
#endif			
		quest_state_data::qst_st_data_map_t::iterator itqm;
		itqm = quest_acceptable_data_map_.find( player_id );
		if( itqm != quest_acceptable_data_map_.end())
		{
			quest_acceptable_data_map_.erase( itqm );
		}
	}
	///////////////


   int quest_data_mgr::add_player_current_npc_lst( const int player_id, vector<int>& npc_lst)
   {
#ifdef YN_LINUX		
         Game_Logic::map_mutex m(&quest_data_mutex_);
#endif
       map< int, vector< int > >::iterator itp;
       itp = player_current_npc_lst_.find( player_id );
       if( itp == player_current_npc_lst_.end() )
       {
           player_current_npc_lst_.insert(make_pair( player_id, npc_lst));
           return 0;
       }
       else
       {
           itp->second = npc_lst;
           return 0;
       }
       return -1;
   }
   int quest_data_mgr::get_player_current_npc_lst( const int player_id, vector<int>& npc_lst)
   {
#ifdef YN_LINUX		
      Game_Logic::map_mutex m(&quest_data_mutex_);
#endif

       map< int, vector< int > >::iterator itp;
       itp = player_current_npc_lst_.find( player_id );
       if( itp != player_current_npc_lst_.end() )
       {
           npc_lst = itp->second;
           return 0;
       }
       return -1;
   }

   quest_data* quest_data_mgr::get_guide_quest_in_acceptable_quest(const int player_id)
   {
       int min_quest_id = 0;
       quest_data* org_qst = NULL;
       quest_state_data::qst_st_data_vec_t qst_apt_data_vec;
       get_acceptable_quest_list(player_id,qst_apt_data_vec);
       if (qst_apt_data_vec.size() > 0)
       {
           min_quest_id = qst_apt_data_vec.front().get_quest_id();
           quest_state_data::qst_st_data_vec_t::iterator iter = qst_apt_data_vec.begin();
           ++iter;
           for (;iter != qst_apt_data_vec.end();++iter)
           {
               int id = (*iter).get_quest_id();
               if (id < min_quest_id)
               {
                   min_quest_id = id;
               }
           }
       }

       org_qst = Game_Data::quest_data_mgr::instance()->get_org_quest_data(min_quest_id);

       return org_qst;
   }
}

