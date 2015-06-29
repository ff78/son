#ifndef _EVENT_DEFINE_H
#define	_EVENT_DEFINE_H
#include "common.h"
namespace Game_Data
{
	struct 	Game_Element;
}
namespace Game_Logic
{
	struct Game_Interface
	{
		enum OPERATE_TYPE
		{
			OPERATE_NONE = 0,
			OPERATE_GIVEUPQUEST,
			OPERATE_ADDSAVEDQUEST
		};
		Game_Interface():keyword_str_(""),reg_state_b_(false),pre_condition_b_(false), error_type_(0),
            data_p_(NULL),operate_type_(OPERATE_NONE),buff_size_(0),read_size_(0) 
        {para_vec_.clear();memset(buff_,0x00, _MAX_MSGSIZE -1 );}
		Game_Interface( vector<uint64> para ) {para_vec_.clear(); para_vec_ = para; memset(buff_,0x00, _MAX_MSGSIZE -1 ); }
		Game_Interface( const Game_Interface& gi )
		{
			para_vec_.clear();
			para_vec_ 				= gi.get_para();
			keyword_str_ 			= gi.get_keyword();
			reg_state_b_ 			= gi.get_reg_state();
			pre_condition_b_ 	    = gi.get_pre_condition();			
			error_type_ 			= gi.get_error_type();
			data_p_ 				= gi.get_data_point();
			operate_type_ 		    = gi.get_operate_type();
            memcpy(buff_,gi.get_buff(), _MAX_MSGSIZE -1 );
            buff_size_              = gi.get_buff_size();

		}
		/*Game_Interface & operator = (const Game_Interface& gi)
		{
			para_vec_.clear();
			para_vec_ 				= gi.get_para();
			keyword_str_ 			= gi.get_keyword();
			reg_state_b_ 			= gi.get_reg_state();
			pre_condition_b_ 	    = gi.get_pre_condition();			
			error_type_ 			= gi.get_error_type();
			data_p_ 			    = gi.get_data_point();
			operate_type_ 		    = gi.get_operate_type();

            memcpy(buff_, gi.get_buff(), _MAX_MSGSIZE -1 );
            buff_size_ = gi.get_buff_size();
			return *this;
		}*/
		~Game_Interface() {}
		void set_para( vector<uint64> para )
		{
			para_vec_.clear();
			para_vec_ = para;
		}
		const vector<uint64>& get_para(void)const { return para_vec_;}
		void get_para ( vector<uint64>& para ) { para.clear(); para = para_vec_; }
		void set_reg_state( bool state_b ) { reg_state_b_ = state_b; }
		 bool get_reg_state( void )const { return reg_state_b_; }
		void set_error_type( int err ) { error_type_ = err; }
		 int get_error_type( void )const { return error_type_; }
		void set_pre_condition ( bool cond ) { pre_condition_b_ = cond; }
	        bool get_pre_condition ( void )const { return pre_condition_b_; }
		void set_keyword( const char* key ) { keyword_str_= key; }
	        const char* get_keyword( void ) const{ return keyword_str_.data(); }
		void* get_data_point( void ) const {return data_p_;}
		 int get_operate_type( void ) const { return operate_type_; }
		void set_operate_type( const int op_type ) { operate_type_ = op_type; }
        void  set_buff(const char* buff, int len)
        {
            if( len < _MAX_MSGSIZE )
            {
                memcpy(buff_,buff,len);
                buff_size_ = len;
            }
        }

        const char* get_buff(void) const {return buff_;}    
        int get_buff_size(void) const {return buff_size_;}

        void set_read_size(int size ) { read_size_ = size;}
        
        int get_read_size(void) const {return read_size_;}
	private:
		vector<uint64> para_vec_;
		string keyword_str_;
		bool	reg_state_b_;
		bool	pre_condition_b_;
		int		error_type_;
		mutable void* data_p_;
		int 	operate_type_;
        char    buff_[_MAX_MSGSIZE];
        int     buff_size_;
        int     read_size_;
	};

	typedef bool ( *game_interface_handler_t )( Game_Interface& gm_interface );
	typedef vector<game_interface_handler_t> game_interface_handler_vec_t;
	typedef map< string, game_interface_handler_t > game_interface_handler_map_t;
	typedef map< string, game_interface_handler_vec_t > game_interface_multi_handler_map_t;
	typedef map< uint, game_interface_handler_t > game_interface_handler_uint_map_t;

	typedef bool ( *quest_interface_handler_t )( Game_Interface& gm_interface, Game_Data::Game_Element& gm_elt );
	typedef map< string, quest_interface_handler_t > quest_interface_handler_map_t;

	struct Game_Event
	{
		enum EVENT_TYPE_DEF
		{
			//atom type
			EVENT_TYPE_PLAYER = 1,			// 主角
			EVENT_TYPE_MONSTER,				// 怪物
			EVENT_TYPE_NPC,					// NPC
			EVENT_TYPE_DEPUTY_GENERAL,		// 副将
			EVENT_TYPE_FIGHT_PLAYER,        // pk玩家
			EVENT_TYPE_QUEST,
			EVENT_TYPE_PLAYER_LEVEL,
			EVENT_TYPE_SKILL_LEVEL,
			EVENT_TYPE_ADDFRIENDS,
			EVENT_TYPE_DIALOGTO,
			EVENT_TYPE_GIVEITEMTONPC,
			EVENT_TYPE_SELOCCUP,
			EVENT_TYPE_PLAYERLEVELUP,
            EVENT_TYPE_AI,
            EVENT_TYPE_ITEM,
            EVENT_TYPE_PK_PLAYER,
            EVENT_TYPE_COST_GOLD,
            EVENT_TYPE_PLAYER_QUALITY_UP,
            EVENT_TYPE_BOOK_QUALITY_UP,
            EVENT_TYPE_GERNERAL_REQ_QA,
            EVENT_TYPE_ALL_EQUIP_REQ_QA,
            EVENT_TYPE_SKILL_REQ_LEVEL,
            EVENT_TYPE_MONEY_REQ,
			
			EVENT_TYPE_ACTIVITY,
			EVENT_TYPE_QUEST_COMPLETE,
			EVENT_TYPE_RING_QUEST_COMPLETE,
			EVENT_TYPE_RING_ITEM_USED,
            EVENT_TYPE_PLAYER_DIE,
            EVENT_FINISH_SCENE_LOAD,
            //UI EVENT
            EVENT_TYPE_UI_MIAN,
            EVENT_TYPE_UI_ITEM,
            EVENT_TYPE_SKILL,
            EVENT_TYPE_ARENA,
            EVENT_TYPE_INSTANCE_STAGE,
            EVENT_TYPE_STAGE,
            #if 1//MISSION_SUPPORT
			EVENT_TYPE_MISSION_DIALOG,
			#endif
            EVENT_TYPE_STAGE_ALL,
			EVENT_TYPE_FRIEND_LIST,
			EVENT_TYPE_FRIEND_DETAIL,
            EVENT_TYPE_UI_GAME_CHILD,
            EVENT_TYPE_UI_NPCDIALOG,
            EVENT_TYPE_COUNT_DOWN_TIME,
            EVENT_TYPE_UI_ROLE_QUALITY_UP,
            EVENT_TYPE_UI_COMPOUND_FRAGMENT,
			EVENT_TYPE_UI_FATE,
			EVENT_TYPE_UI_BANKS,
			EVENT_TYPE_UI_RANK,
			EVENT_TYPE_UI_LOGIN_AWARD,
            EVENT_TYPE_UI_INSTANCE_SWEEP,
            EVENT_TYPE_UI_GEM_INLAY,
            EVENT_TYPE_UI_OPERATE_GEM,
            EVENT_TYPE_UI_GEM_LEVEL_UP,
            EVENT_TYPE_UI_SHOP,
            EVENT_TYPE_UI_DAILY_TASK,
			/************************ dely *********************/
			EVENT_TYPE_UI_CHAT,
			/************************ dely *********************/
			//cmd type
            EVENT_TYPE_HURT,
			EVENT_TYPE_USEITEM,
			EVENT_TYPE_KILLMONSTER,
			EVENT_TYPE_COLLIDED_SOMETHING,
			EVENT_TYPE_ARRIVE,
			EVENT_TYPE_GETITEM,
			EVENT_TYPE_COLLECT,
			EVENT_TYPE_ENEMYMONSTER,
			EVENT_TYPE_SEARCH,
			EVENT_TYPE_PATROL,
			EVENT_TYPE_NPCCHALLENGE,
			EVENT_TYPE_DAILY_REWARD,
            EVENT_TYPE_INSTANCE,
            EVENT_TYPE_EQUIPMENT_LEVEL_UP,
            EVENT_TYPE_INSTANCE_SUC,
            EVENT_TYPE_ITEM_EQUIP,
            EVENT_TYPE_BOOK_EQUIP,
            EVENT_TYPE_SKILL_UPGRADE,
            EVENT_TYPE_BOOK_LEVEL_UP,
            EVENT_TYPE_EQUIPMENT_QUALITY_UP,
			EVENT_TYPE_EVENT_SYSTEM,
            EVENT_TYPE_INSTANCE_DIALOG_FINISH,
            EVENT_TYPE_ITEM_EQUIP_ALL,
            EVENT_TYPE_BOOK_FRAGMENT_COMPOUND,
            EVENT_TYPE_MATERIAL_FRAGMENT_COMPOUND,
            EVENT_TYPE_FIGHT_GENERAL, 
            EVENT_TYPE_ACUPOINT_OPEN,
		};

		Game_Event(): game_event_id_ul_(0),
					event_owner_id_ul_(0),
					event_owner_type_un_(0),
					event_char_id_ul_(0),
					event_char_type_us_(0),
					event_active_id_ul_(0),
					event_active_type_us_(0),
					data_p_(NULL)
		{ para_vec_.clear(); }

		Game_Event( const unsigned long& evt_id ): game_event_id_ul_( evt_id ) {}
		void reset()
		{
			game_event_id_ul_ = 0;
			event_owner_id_ul_ = 0;
			event_owner_type_un_ = 0;
			event_char_id_ul_ = 0;
			event_char_type_us_ = 0;
			event_active_id_ul_ = 0;
			event_active_type_us_= 0;
			data_p_ = NULL;	
			para_vec_.clear();
		}
		Game_Event( const Game_Event& ge )
		{
			para_vec_.clear();
			para_vec_ = ge.get_para();
			game_event_id_ul_		= 0;
			event_owner_id_ul_ 		= ge.get_event_owner_id();	
			event_owner_type_un_	= ge.get_event_owner_type();	//game logic type: quest item ai skill .......

			event_char_id_ul_		= ge.get_char_id();	 
			event_char_type_us_ 	= ge.get_char_type();  //  who register(just character): player, Monster, Pet ....

			event_active_id_ul_		= ge.get_event_active_id();
			event_active_type_us_	= ge.get_event_active_type();	
			
			data_p_ 				= ge.get_data_point();
		}

		/*Game_Event & operator = (const Game_Event& ge)
		{
			para_vec_.clear();
			para_vec_ = ge.get_para();
			game_event_id_ul_			= 0;
			event_owner_id_ul_ 		= ge.get_event_owner_id();	
			event_owner_type_un_	= ge.get_event_owner_type();	//game logic type: quest item ai skill .......

			event_char_id_ul_			= ge.get_char_id();	 
			event_char_type_us_ 	= ge.get_char_type();  //  who register(just character): player, Monster, Pet ....

			event_active_id_ul_		= ge.get_event_active_id();
			event_active_type_us_	= ge.get_event_active_type();	
			
			data_p_ 							=	ge.get_data_point();
			return *this;		
		}*/
		~Game_Event() {}
		void add_para( uint64 pd )
		{
			para_vec_.push_back( pd );
		}
		void set_para( vector<uint64>  para )
		{
			para_vec_.clear();
			para_vec_ = para;
		}

		void get_para( vector<uint64> & para ) const
		{
			para.clear();
			para = para_vec_;
		}
		
		const vector<uint64> & get_para( void ) const
		{
			return para_vec_;
		}

		unsigned short get_char_type( void ) const { return event_char_type_us_; }
		unsigned long get_char_id( void ) const { return event_char_id_ul_; }
		void set_char_type( unsigned short char_type  ) { event_char_type_us_ = char_type; }
		void set_char_id( unsigned long char_id ) { event_char_id_ul_ = char_id; }

		void set_event_owner_id( unsigned long owner_id ) { event_owner_id_ul_ = owner_id; }
		void set_event_owner_type( unsigned int owner_type ) { event_owner_type_un_ = owner_type; }

		unsigned long get_event_owner_id( void ) const { return event_owner_id_ul_; }
		unsigned short get_event_owner_type( void ) const { return event_owner_type_un_; }

		void set_event_active_id( unsigned long active_id ) { event_active_id_ul_ = active_id; }
		void set_event_active_type( unsigned short active_type ) { event_active_type_us_ = active_type; }

		unsigned long get_event_active_id( void ) const { return event_active_id_ul_; }
		unsigned short get_event_active_type( void ) const { return event_active_type_us_; }
		void* get_data_point(void ) const {return data_p_;}
		bool operator==(const Game_Event& ge)const
		{
			return (ge.get_event_owner_id() == get_event_owner_id() && ge.get_event_active_id() == get_event_active_id() && ge.get_char_id() == get_char_id() );
		}

	private:
		vector<uint64>  para_vec_;
		unsigned long game_event_id_ul_;

		unsigned long event_owner_id_ul_;	
		unsigned int event_owner_type_un_;	//game logic type: quest item ai skill .......

		unsigned long event_char_id_ul_;	 
		unsigned short event_char_type_us_;  //  who register(just character): player, Monster, Pet ....

		unsigned long event_active_id_ul_;
		unsigned short event_active_type_us_; // who response: player quest item pet skill .....
		mutable void* data_p_;
	};

	typedef bool ( *game_event_handler_t )( const Game_Event& gm_evt );

	struct Game_Event_Callback
	{
		Game_Event_Callback():event_handle_(0),game_event_(0)  {}
		/*Game_Event_Callback(const Game_Event_Callback& gec ) 
		{
			event_handle_ = gec.get_game_event_handler();
			game_event_ = gec.get_game_event_data();
		}
		Game_Event_Callback & operator = (const Game_Event_Callback& gec)
		{
			event_handle_ = gec.get_game_event_handler();
			game_event_ = gec.get_game_event_data();
			return *this;
		}*/
		~Game_Event_Callback() {}

		void set_game_event_handler( game_event_handler_t handle ) { event_handle_ = handle; }
		void set_game_event_data( Game_Event gm_evt ) { game_event_ = gm_evt; }
		void get_game_event_handler( game_event_handler_t& handle ) { handle = event_handle_; }
		void get_game_event_data( Game_Event& gm_evt ) {  gm_evt = game_event_; }
	 	const Game_Event& get_game_event_data( void )const {  return game_event_; }

		const game_event_handler_t& get_game_event_handler(void) const{ return	event_handle_;}
		bool operator==(const Game_Event_Callback& gec)const
		{
			Game_Event_Callback gec_tmp = gec;
			Game_Event ge;
			gec_tmp.get_game_event_data(ge);

			return (ge.get_event_owner_id() == game_event_.get_event_owner_id() && 
				ge.get_event_owner_type() == game_event_.get_event_owner_type() &&
				ge.get_event_active_id() == game_event_.get_event_active_id() && 
				ge.get_char_id() == game_event_.get_char_id() );
		}

	private:
		game_event_handler_t	event_handle_;
		Game_Event				game_event_;
	};

	typedef vector<Game_Event_Callback> game_event_handler_vec_t;
	typedef map< string, Game_Event_Callback> game_event_handler_map_t;
	typedef map< string, game_event_handler_vec_t > game_event_handler_multi_map_t;
	typedef map<int, game_event_handler_multi_map_t > game_event_handler_multi_player_map_t;

}
#endif
