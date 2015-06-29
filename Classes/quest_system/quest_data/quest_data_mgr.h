#ifndef _QUEST_DATA_MGR_H
#define	_QUEST_DATA_MGR_H
#include "Game_Interface/common.h"
#include "Game_Interface/game_element.h"
namespace Game_Data
{
	struct game_quest_content
	{		
		game_quest_content( void ) 
		{
			quest_element_vec_.clear();
			quest_command_element_vec_.clear();
		}
		
		~game_quest_content( void ) {}
		
		void reset()
		{
			quest_element_vec_.clear();
			quest_command_element_vec_.clear();
		}
		
		game_quest_content( const game_quest_content& gqc ) 
		{
			quest_element_vec_.clear();
			quest_element_vec_	= gqc.get_quest_element();
			quest_command_element_vec_ 	= gqc.get_quest_command_element();
		}
		
		game_quest_content & operator = (const game_quest_content& gqc)
		{
			quest_element_vec_.clear();
			quest_element_vec_	= gqc.get_quest_element();
			quest_command_element_vec_ 	= gqc.get_quest_command_element();
			return *this;
		}	
		void set_quest_element( const game_element_list_t& gev ) { quest_element_vec_.clear(); quest_element_vec_ = gev; }
		void get_quest_element( game_element_list_t& gev ) { gev.clear(); gev = quest_element_vec_; }

		const game_element_list_t get_quest_element( void ) const {return quest_element_vec_;}

		void set_quest_command_element ( const game_command_element_vec_t& gcev ) { quest_command_element_vec_.clear(); quest_command_element_vec_ = gcev; } 
		void get_quest_command_element ( game_command_element_vec_t& gcev ) { gcev.clear(); gcev = quest_command_element_vec_; } 
		const game_command_element_vec_t& get_quest_command_element ( void ) const { return quest_command_element_vec_; } 
	private:
		game_element_list_t quest_element_vec_;
		game_command_element_vec_t quest_command_element_vec_;
	};

	struct quest_data
	{
		enum quest_state_def
		{
			QUEST_STATE_NONE = 99,
			QUEST_STATE_SUBMITABLE = 1,
			QUEST_STATE_ACCEPTABLE,
			QUEST_STATE_INPROCESS,
			QUEST_STATE_REMOVE,
			QUEST_STATE_COMPLETED,
			QUEST_STATE_FAIL,
			QUEST_STATE_GIVEUP,
			QUEST_STATE_CHALLENGE,
			QUEST_STATE_DIALOGTO,
			QUEST_STATE_GIVE_ITEM_TO_NPC
		};
		enum quest_type
		{
			QUEST_TYPE_FRESHMAN = 0,
			QUEST_TYPE_TRUNK,
			QUEST_TYPE_BRANCH,
			QUEST_TYPE_ROUTINE,
			QUEST_TYPE_RING

		};
		quest_data( void ):quest_id_n_(0),
		state_(QUEST_STATE_NONE),
		dirty_mark_(0),
		ring_quest_bind_id_(0),
		quest_name_str_(""),
		quest_info_str_(""),
		quest_trace_exec_str_(""),
		quest_trace_comp_str_(""),
		quest_accept_dialog_str_(""),
		quest_submit_dialog_str_(""),
		quest_award_str_(""),
        quest_name_id_(0),
        quest_info_id_(0),
        quest_accept_dialog_id_(0),
        quest_submit_dialog_id_(0),
        quest_exec_dialog_id_(0),
	    quest_type_(0),
        quest_time_(0)
		{
			quest_content_.reset();
			quest_accept_.reset();
			quest_complete_.reset();
			quest_award_.reset();
			quest_select_award_.reset();
		    pre_cond_vec_.clear();
		    pre_cond_vec_.clear();
		}
		quest_data( int qid ):quest_id_n_(qid),
        state_(QUEST_STATE_NONE),
		dirty_mark_(0),
		ring_quest_bind_id_(0),
		quest_name_str_(""),
		quest_info_str_(""),
		quest_trace_exec_str_(""),
		quest_trace_comp_str_(""),
		quest_accept_dialog_str_(""),
		quest_submit_dialog_str_(""),
		quest_award_str_(""),
        quest_name_id_(0),
        quest_info_id_(0),
        quest_accept_dialog_id_(0),
        quest_submit_dialog_id_(0),
        quest_exec_dialog_id_(0),
	    quest_type_(0),
        quest_time_(0)
		{
			quest_content_.reset();
			quest_accept_.reset();
			quest_complete_.reset();
			quest_award_.reset();
			quest_select_award_.reset();
		    pre_cond_vec_.clear();
		    pre_cond_vec_.clear();
		}

		~quest_data( void ) {}

        void reset()
        {
			quest_id_n_ 		=0;
			state_ 				= 0;
			dirty_mark_			= 0;
			ring_quest_bind_id_	= 0;
			quest_name_str_.clear();
			quest_info_str_.clear();
			quest_trace_exec_str_.clear();
			quest_trace_comp_str_.clear();
			quest_accept_dialog_str_.clear();
			quest_submit_dialog_str_.clear();
			quest_award_str_.clear();
            quest_content_.reset();
			quest_accept_.reset();
			quest_award_.reset();
			quest_select_award_.reset();
            quest_complete_.reset();
			quest_type_			    = 0;
			quest_time_			    = 0;
            pre_cond_vec_.clear();
			post_cond_vec_.clear();
            quest_name_id_          = 0;
            quest_info_id_          = 0;
            quest_accept_dialog_id_ = 0;
            quest_submit_dialog_id_ = 0;
            quest_exec_dialog_id_   = 0;

        }
		quest_data & operator = (const quest_data& qst)
		{
			quest_id_n_ 		= qst.get_quest_id();
			state_ 				= qst.get_quest_state();
			dirty_mark_			= qst.get_quest_dirty_mark();
			ring_quest_bind_id_	= qst.get_ring_quest_bind_id();
			quest_name_str_		= qst.get_quest_name();
			quest_info_str_		= qst.get_quest_info();
			quest_trace_exec_str_ = qst.get_quest_trace_exec();
			quest_trace_comp_str_ = qst.get_quest_trace_comp();
			quest_accept_dialog_str_ = qst.get_quest_accept_dialog();
			quest_submit_dialog_str_ = qst.get_quest_submit_dialog();
			quest_award_str_ = qst.get_quest_award_str();
			quest_content_ 		= qst.get_quest_content();
			quest_accept_		= qst.get_quest_accept();
			quest_award_		= qst.get_quest_award();
			quest_select_award_ = qst.get_quest_select_award();
			quest_complete_		= qst.get_quest_complete();
			quest_type_			= qst.get_quest_type();
			quest_time_			= qst.get_quest_time();
			pre_cond_vec_		= qst.get_pre_cond();
			post_cond_vec_		= qst.get_post_cond();			
            quest_name_id_      = qst.get_quest_name_id();
            quest_info_id_      = qst.get_quest_info_id();
            quest_accept_dialog_id_ = qst.get_quest_accept_dialog_id();
            quest_submit_dialog_id_ = qst.get_quest_submit_dialog_id();
            quest_exec_dialog_id_ = qst.get_quest_exec_dialog_id();
			return *this;
		}
		bool operator==(const quest_data& qd)const
		{
			return (qd.get_quest_id() == quest_id_n_);
		}

		typedef vector< quest_data > quest_data_vec_t;
		typedef map< int, quest_data_vec_t > quest_data_map_t;
		typedef map< int, quest_data > quest_one_data_map_t;

		void set_quest_id( int qid ) { quest_id_n_ = qid; }
		int get_quest_id( void ) const  { return quest_id_n_; }
		void set_quest_content( const game_quest_content& gqc ) { quest_content_ = gqc; }
		void get_quest_content( game_quest_content& gqc ) { gqc = quest_content_; }
		game_quest_content get_quest_content( void ) const { return quest_content_; }
		
		void set_quest_award( const game_quest_content& gqc ) { quest_award_ = gqc; }
		void get_quest_award( game_quest_content& gqc ) { gqc = quest_award_; }
		game_quest_content get_quest_award( void ) const { return quest_award_; }		
		
		void set_quest_select_award( const game_quest_content& gqc ) { quest_select_award_ = gqc; }
		void get_quest_select_award( game_quest_content& gqc ) { gqc = quest_select_award_; }
		game_quest_content get_quest_select_award( void ) const { return quest_select_award_; }

		void set_quest_accept( const game_quest_content& gqc ) { quest_accept_ = gqc; }
		void get_quest_accept( game_quest_content& gqc ) { gqc = quest_accept_; }
		game_quest_content get_quest_accept( void ) const { return quest_accept_; }

		void set_quest_complete( const game_quest_content& gqc ) { quest_complete_ = gqc; }
		void get_quest_complete( game_quest_content& gqc ) { gqc = quest_complete_; }
		game_quest_content get_quest_complete( void ) const { return quest_complete_; }
				
		void set_quest_state( const int state ) { state_ = state; }
		int get_quest_state( void )const  { return state_; }

		void push_pre_cond( const int quest_id ) { pre_cond_vec_.push_back( quest_id ); }
		void get_pre_cond( vector<int>& pre_cond_vec ) { pre_cond_vec = pre_cond_vec_; }
		vector<int> get_pre_cond( void ) const { return pre_cond_vec_; }
		
		void push_post_cond( const int quest_id ) { post_cond_vec_.push_back( quest_id ); }
		void get_post_cond( vector<int>& post_cond_vec) {post_cond_vec = post_cond_vec_;}
		vector<int> get_post_cond( void ) const { return post_cond_vec_; }
		
		void push_accept_cond( const Game_Element& ge ) 
		{
			game_element_list_t gev; 
			quest_accept_.get_quest_element( gev );
			gev.push_back(ge);
			quest_accept_.set_quest_element( gev );

		}

		void push_complete_content( const Game_Element& ge ) 
		{
			game_element_list_t gev; 
			quest_complete_.get_quest_element( gev );
			gev.push_back(ge);
			quest_complete_.set_quest_element( gev );

		}

		void push_award_content( const Game_Element& ge ) 
		{
			game_element_list_t gev; 
			quest_award_.get_quest_element( gev );
			gev.push_back(ge);
			quest_award_.set_quest_element( gev );

		}
		void push_select_award_content( const Game_Element& ge ) 
		{
			game_element_list_t gev; 
			quest_select_award_.get_quest_element( gev );
			gev.push_back(ge);
			quest_select_award_.set_quest_element( gev );

		}

		void set_quest_type( const int type )
		{
			quest_type_ = type;
		}

		int get_quest_type( void ) const
		{
			return quest_type_;
		}

		void set_quest_time( const time_t qst_time )
		{
			quest_time_ = qst_time;
		}

		time_t get_quest_time( void ) const
		{
			return quest_time_;
		}

		const char* get_quest_name( void ) const {return quest_name_str_.data();}
		void set_quest_name( const char* qst_name ) { quest_name_str_ = qst_name; }

		const char* get_quest_info( void ) const { return quest_info_str_.data(); }
		void set_quest_info( const char* qst_info ) { quest_info_str_ = qst_info;}

		const char* get_quest_trace_exec( void ) const { return quest_trace_exec_str_.data(); }
		void set_quest_trace_exec( const char* qst_exec ) { quest_trace_exec_str_ = qst_exec;}

		const char* get_quest_trace_comp( void ) const { return quest_trace_comp_str_.data(); }
		void set_quest_trace_comp( const char* qst_comp ) { quest_trace_comp_str_ = qst_comp;}

		const char* get_quest_accept_dialog( void ) const { return quest_accept_dialog_str_.data(); }
		void set_quest_accept_dialog( const char* qst_accept_dialog ) { quest_accept_dialog_str_ = qst_accept_dialog;}

		const char* get_quest_submit_dialog( void ) const { return quest_submit_dialog_str_.data(); }
		void set_quest_submit_dialog( const char* qst_submit_dialog ) { quest_submit_dialog_str_ = qst_submit_dialog;}

		void set_quest_dirty_mark ( int qdm ) { dirty_mark_ = qdm; }
		int get_quest_dirty_mark ( void ) const { return dirty_mark_; }

		void set_ring_quest_bind_id( int id ) { ring_quest_bind_id_ = id; }
		int get_ring_quest_bind_id( void ) const { return ring_quest_bind_id_; }

		const char* get_quest_award_str( void ) const { return quest_award_str_.data(); }
		void set_quest_award_str( const char* award_str ) { quest_award_str_ = award_str; }

        void set_quest_name_id( int id ) {quest_name_id_=id;}
        int get_quest_name_id( void ) const {return quest_name_id_;}

        void set_quest_info_id( int id ) { quest_info_id_ = id; }
        int get_quest_info_id( void ) const { return quest_info_id_; }

        void set_quest_accept_dialog_id( int id ) { quest_accept_dialog_id_ = id; }
        int get_quest_accept_dialog_id( void ) const { return quest_accept_dialog_id_; }

        void set_quest_submit_dialog_id( int id ) { quest_submit_dialog_id_ = id; }
        int get_quest_submit_dialog_id( void ) const { return quest_submit_dialog_id_; }

        void set_quest_exec_dialog_id( int id ) { quest_exec_dialog_id_ = id; }
        int get_quest_exec_dialog_id( void ) const { return quest_exec_dialog_id_; }
	private:
		int quest_id_n_;
		int state_;
		int dirty_mark_;
		int ring_quest_bind_id_;
		string quest_name_str_;
		string quest_info_str_;
		string quest_trace_exec_str_;
		string quest_trace_comp_str_;
		string quest_accept_dialog_str_;
		string quest_submit_dialog_str_;
		string quest_award_str_;
        int quest_name_id_;
        int quest_info_id_;
        int quest_accept_dialog_id_;
        int quest_submit_dialog_id_;
        int quest_exec_dialog_id_;
		game_quest_content quest_accept_;
		game_quest_content quest_content_;
		game_quest_content quest_complete_;
		game_quest_content quest_award_;
		game_quest_content quest_select_award_;

		//extend content
		int quest_type_;
		vector<int> pre_cond_vec_;
		vector<int> post_cond_vec_;
		time_t quest_time_;
	};

	struct quest_state_data
	{
		quest_state_data(void):quest_id(0) {}
		quest_state_data(const int qst_id):quest_id(qst_id) {}
		~quest_state_data(void) {}
		
		quest_state_data( const quest_state_data& qsd )
		{
			quest_id = qsd.get_quest_id();
		}
		quest_state_data & operator = (const quest_state_data& qsd)
		{
			quest_id = qsd.get_quest_id();
			return *this;
		}
		void set_quest_id( const int qst_id ) { quest_id = qst_id; }
	        int get_quest_id( void ) const { return quest_id; }

		bool operator==(const quest_state_data& qd)const
		{
			return (qd.get_quest_id() == get_quest_id());
		}
		typedef vector<quest_state_data> qst_st_data_vec_t;
		typedef map<int, qst_st_data_vec_t> qst_st_data_map_t;

	private:
		int quest_id;
	};

	struct npc_bind_quest
	{
		npc_bind_quest():npc_id_(0) 
		{
			 accept_quest_list.clear();
			 submit_quest_list.clear();
			 dialog_quest_list.clear();
			 challenge_quest_list.clear();
			 give_item_to_npc_quest_list.clear();
             inprocess_quest_list.clear();
		}
		~npc_bind_quest() {}
		npc_bind_quest( uint32 npcid ): npc_id_(npcid) 
		{
			 accept_quest_list.clear();
			 submit_quest_list.clear();
			 dialog_quest_list.clear();
			 challenge_quest_list.clear();
			 give_item_to_npc_quest_list.clear();
             inprocess_quest_list.clear();
		}

		bool operator==(const npc_bind_quest& nbq)const
		{
			return (nbq.get_npc_id() == npc_id_);
		}

		void set_npc_id ( const uint32 npcid ) { npc_id_ = npcid; }
		uint32 get_npc_id ( void ) const { return npc_id_; }
		void add_accept_quest_list( uint32 quest_id ) { accept_quest_list.push_back( quest_id); }
		void set_accept_quest_list( vector<uint32> qst_lst ) { accept_quest_list.clear(); accept_quest_list = qst_lst; } 
		void get_accept_quest_list( vector<uint32>& qst_lst) { qst_lst = accept_quest_list; }
		bool is_accept_quest( const uint32 questid) 
		{
			vector<uint32>::iterator itv;
			itv = find( accept_quest_list.begin(), accept_quest_list.end(), questid );
			return itv != accept_quest_list.end();
		}
		void add_submit_quest_list( uint32 quest_id ) { submit_quest_list.push_back( quest_id); }
		void set_submit_quest_list( vector<uint32> qst_lst ) { submit_quest_list.clear(); submit_quest_list = qst_lst; } 
		void get_submit_quest_list( vector<uint32>& qst_lst) { qst_lst = submit_quest_list; }
		bool is_submit_quest( const uint32 questid) 
		{
			vector<uint32>::iterator itv;
			itv = find( submit_quest_list.begin(), submit_quest_list.end(), questid );
			return itv != submit_quest_list.end();
		}
		void add_dialog_quest_list( uint32 quest_id ) { dialog_quest_list.push_back( quest_id); }
		void add_dialog_quest_list( vector<uint32> quest_id_lst ) 
		{ 
			vector<uint32>::iterator itv;
			for( itv = quest_id_lst.begin(); itv != quest_id_lst.end(); itv++)
				dialog_quest_list.push_back( (*itv) ); 
		}
		void set_dialog_quest_list( vector<uint32> qst_lst ) { dialog_quest_list.clear(); dialog_quest_list = qst_lst; } 
		void get_dialog_quest_list( vector<uint32>& qst_lst) { qst_lst = dialog_quest_list; }
		bool is_dialog_quest( const uint32 questid) 
		{
			vector<uint32>::iterator itv;
			itv = find( dialog_quest_list.begin(), dialog_quest_list.end(), questid );
			return itv != dialog_quest_list.end();
		}
		void add_challenge_quest_list( uint32 quest_id ) { challenge_quest_list.push_back( quest_id); }
		void add_challenge_quest_list( vector<uint32> quest_id_lst ) 
		{ 
			vector<uint32>::iterator itv;
			for( itv = quest_id_lst.begin(); itv != quest_id_lst.end(); itv++)
				challenge_quest_list.push_back( (*itv) ); 
		}
		void set_challenge_quest_list( vector<uint32> qst_lst ) { challenge_quest_list.clear(); challenge_quest_list = qst_lst; } 
		void get_challenge_quest_list( vector<uint32>& qst_lst) { qst_lst = challenge_quest_list; }
		bool is_challenge_quest( const uint32 questid) 
		{
			vector<uint32>::iterator itv;
			itv = find( challenge_quest_list.begin(), challenge_quest_list.end(), questid );
			return itv != challenge_quest_list.end();
		}
		void add_give_item_to_npc_quest_list( uint32 quest_id ) { give_item_to_npc_quest_list.push_back( quest_id); }
		void add_give_item_to_npc_quest_list( vector<uint32> quest_id_lst ) 
		{ 
			vector<uint32>::iterator itv;
			for( itv = quest_id_lst.begin(); itv != quest_id_lst.end(); itv++)
				give_item_to_npc_quest_list.push_back( (*itv) ); 
		}
		void set_give_item_to_npc_quest_list( vector<uint32> qst_lst ) { give_item_to_npc_quest_list.clear(); give_item_to_npc_quest_list = qst_lst; } 
		void get_give_item_to_npc_quest_list( vector<uint32>& qst_lst) { qst_lst = give_item_to_npc_quest_list; }
		bool is_give_item_to_npc_quest_list( const uint32 questid) 
		{
			vector<uint32>::iterator itv;
			itv = find( give_item_to_npc_quest_list.begin(), give_item_to_npc_quest_list.end(), questid );
			return itv != give_item_to_npc_quest_list.end();
		}
		void reset( void )
		{
			npc_id_ = 0;
			accept_quest_list.clear();
			submit_quest_list.clear();
			dialog_quest_list.clear();
			challenge_quest_list.clear();
			give_item_to_npc_quest_list.clear();

		}
		void add_inprocess_quest_list( uint32 quest_id ) { inprocess_quest_list.push_back( quest_id); }
		void set_inprocess_quest_list( vector<uint32> qst_lst ) { inprocess_quest_list.clear(); inprocess_quest_list = qst_lst; } 
		void get_inprocess_quest_list( vector<uint32>& qst_lst) { qst_lst = inprocess_quest_list; }
		bool is_inprocess_quest( const uint32 questid) 
		{
			vector<uint32>::iterator itv;
			itv = find( inprocess_quest_list.begin(), inprocess_quest_list.end(), questid );
			return itv != inprocess_quest_list.end();
		}

		typedef map<uint32, npc_bind_quest> npc_bind_quest_map_t;
		typedef vector<npc_bind_quest> npc_bind_quest_vec_t;
		typedef map<uint32, npc_bind_quest_vec_t> multi_npc_bind_quest_map_t;
	private:
		uint32 npc_id_;
		vector<uint32> accept_quest_list;
		vector<uint32> submit_quest_list;
		vector<uint32> dialog_quest_list;
		vector<uint32> challenge_quest_list;
		vector<uint32> give_item_to_npc_quest_list;
        vector<uint32> inprocess_quest_list;
	};

	class quest_data_mgr
	{
	public:
		quest_data_mgr(void);
		~quest_data_mgr(void);
		static quest_data_mgr* instance(void);

		void init( const char *root );
        void release( void );
		void reload( void );

		void addquest							( const int player_id, const quest_data& qd );
		void removequest						( const int player_id, const int quest_id );
		void modi_quest_data					(  const int player_id, const quest_data& qd );
		void clear_quest_dirty_mark				( const int player_id, const int quest_id );
		quest_data* get_quest_data				( const int player_id, const int quest_id );
		quest_data::quest_data_vec_t get_quest_data_list( const int player_id );
		quest_data* get_org_quest_data			( const int quest_id );
        int get_org_quest_data                  ( const int quest_id, quest_data& qd );

		void get_org_quest_command_para			( const int quest_id_n, const char* command_str, vector< unsigned int >& para_vec );
		int  get_org_quest_counter_size			( const int quest_id_n );
		void clear_player_quest_data			(const int player_id);

		//npc quest bind proc
		void add_npc_quest_bind_data			( const npc_bind_quest& nbq);
		npc_bind_quest* get_npc_quest_bind_data	( const uint32 npc_id );
        int get_npc_quest_bind_data	            ( const uint32 npc_id, npc_bind_quest& nbq );
		void proc_analysis_npc_quest_bind_list	( void );
		uint32 get_quest_bind_npc_id			( uint32 quest_id, const game_quest_content& qc, const char* cmp_key );

        void get_quest_dialog_npc_id            ( uint32 quest_id, const game_quest_content& qc,vector<uint32> npc_id_lst );


		void add_player_npc_quest_bind_data		( uint32 player_id, const npc_bind_quest& nbq );
		void get_player_npc_quest_bind_data		( uint32 player_id, npc_bind_quest::npc_bind_quest_vec_t& npc_bind_list );
		void  remove_player_npc_quest_bind_data	( uint32 player_id );

		///////////////
		void add_acceptable_quest_id			( const int player_id, const int quest_id );
		void remove_acceptable_quest_id			( const int player_id, const int quest_id );
		bool is_in_quest_acceptable_list		( const int player_id, const int quest_id );
		void get_acceptable_quest_list			( const int player_id, quest_state_data::qst_st_data_vec_t&  qst_apt_data_vec );
		void remove_player_acceptable_quest		( const int player_id );
		///////////////
		int add_player_current_npc_lst         ( const int player_id, vector<int>& npc_lst);
        int get_player_current_npc_lst         ( const int player_id, vector<int>& npc_lst);
		///////////////
        quest_data* get_guide_quest_in_acceptable_quest(const int player_id);

	private:

		static quest_data_mgr* m_pInstance;

		quest_data::quest_data_map_t quest_data_map_;  //当前已接受和未提交的任务，也就是界面中右侧显示的任务
		quest_data::quest_one_data_map_t quest_static_data_map_;

		quest_state_data::qst_st_data_map_t quest_acceptable_data_map_;//当前可接受的任务列表
		quest_state_data::qst_st_data_map_t quest_complete_data_map_;
			
		string root_str_;
		
		quest_data::quest_data_vec_t quest_data_vec_tmp_;

		npc_bind_quest::npc_bind_quest_map_t npc_bind_quest_list_; //npc 绑定任务列表

		npc_bind_quest::multi_npc_bind_quest_map_t player_npc_bind_quest_;

        map< int, vector< int > > player_current_npc_lst_;

			
#ifdef YN_LINUX		
		pthread_mutex_t  quest_data_mutex_; 
#endif
	};

}

#endif

