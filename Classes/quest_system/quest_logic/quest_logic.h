#ifndef _QUEST_LOGIC_H
#define	_QUEST_LOGIC_H
#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"

namespace Game_Data
{
	struct Game_Element;
	struct game_quest_content;
}

namespace Game_Logic
{
	class quest_logic
	{
	public:
		quest_logic(void);
		~quest_logic(void);

		void init( void );
		static quest_logic* instance		(void);
		static bool accept_quest			( Game_Interface& gm_interface );
		static bool complete_quest			( Game_Interface& gm_interface );
		static bool give_quest_award		( Game_Interface& gm_interface );
		static bool giveup_quest			( Game_Interface& gm_interface );
		static bool submit_quest			( Game_Interface& gm_interface );		
		static bool proc_quest_content_cout	( Game_Interface& gm_interface );
		static bool proc_quest_content_cmd_analysis( Game_Interface& gm_interface );

		static bool is_quest_accepted		( Game_Interface& gm_interface );

		static bool is_can_accept_quest		( Game_Interface& gm_interface );		
		static bool is_can_submit_quest		( Game_Interface& gm_interface );
		static bool is_quest_in_process		( Game_Interface& gm_interface );
		
		static bool is_quest_content_counter_full( Game_Interface& gm_interface );
        static bool proc_login              ( Game_Interface& gm_interface );
        static bool proc_logout             ( Game_Interface& gm_interface );
		
		bool get_quest_counter				( const uint player_id, const uint quest_id, vector< unsigned int >& counter_vec );
		bool add_saved_quest				( const uint player_id, const uint quest_id, const uint quest_state, 
												const int ring_quest_bind_id, vector< unsigned int >& counter_vec );

		bool get_quest_content_element_list (const uint player_id, const uint quest_id, list<Game_Data::Game_Element>& ge_vec );

		bool is_ring_quest					( const uint quest_id, uint32& sel_quest_id);



	private:
		bool	proc_auto_accept_next_quest	( const uint player_id, const uint quest_id );
		bool	check_to_auto_submit_quest	( const uint player_id, const uint quest_id, const char* key_content );
		bool	proc_add_player_quest		( const uint player_id, const uint quest_id,uint ring_quest_bind_id = 0,bool saved_quest = false );
		bool	proc_analysis_quest			( const uint player_id, const uint quest_id, bool reg_b = false, 
												const uint operate_type = Game_Interface::OPERATE_NONE );

		bool	proc_analysis_quest_func_list( const uint player_id, const uint quest_id, bool reg_b = false );
		bool	proc_analysis_quest_cmd_func_list( const uint player_id, const uint quest_id, bool reg_b = false, const uint element_id = 0, 
			const char* keyword = "", const uint operate_type = Game_Interface::OPERATE_NONE,const uint para_data = 0 );
		
		bool	reg_quest_award_function_callback ( const char* cmd, quest_interface_handler_t handle );
		bool	reg_quest_function_callback ( const char* cmd, quest_interface_handler_t handle );
		bool	reg_quest_command_funciton_callback( const char* cmd, quest_interface_handler_t handle );
		
		bool	set_player_quest_state		( const uint player_id, const uint quest_id, bool reg_b = false, int send_update = 1);

		bool	proc_quest_award			( const uint player_id, const uint quest_id, const char* cmd );
		bool	do_proc_quest_award			( const uint player_id, const uint quest_id, const char* cmd, const list<Game_Data::Game_Element>& game_ele_vec );	
		bool	set_quest_content_element_list (const uint player_id, const uint quest_id, list<Game_Data::Game_Element>& ge_vec );

		void	remove_quest_event			( const vector<uint64>& para, const uint player_id, const uint quest_id );
		
		bool	compute_item_count			(const vector<unsigned int>& para,Game_Data::Game_Element& ge, const uint player_id, const uint element_id);
		bool	compute_useanyitem_count	( const vector<unsigned int>& para, Game_Data::Game_Element& ge,const uint player_id, const uint element_id );
		bool	compute_monsterbylevel_count( const vector<unsigned int>& para, Game_Data::Game_Element& ge,const uint player_id, const uint element_id );
		bool	compute_giveitemtonpc_count	( const vector<unsigned int>& para, Game_Data::Game_Element& ge,const uint player_id, 
												const uint element_id, const vector<uint64>& para_org );
 		bool	compute_friends			    (const vector<unsigned int>& para,Game_Data::Game_Element& ge, const uint player_id, const uint element_id);
        bool    compute_equip_book_req_qa    (const vector<unsigned int>& para,Game_Data::Game_Element& ge, 
                const uint player_id, const uint element_id);
        bool    compute_gerneral_req_qa     (const vector<unsigned int>& para,Game_Data::Game_Element& ge, 
                const uint player_id, const uint element_id);
        bool    compute_all_equip_req_qa     (const vector<unsigned int>& para,Game_Data::Game_Element& ge, 
                const uint player_id, const uint element_id);
        bool    compute_skill_req_level     (const vector<unsigned int>& para,Game_Data::Game_Element& ge, 
                const uint player_id, const uint element_id);
        bool    compute_money_req        (const vector<unsigned int>& para,Game_Data::Game_Element& ge, 
                const uint player_id, const uint element_id);
        bool    compute_equip_item_all     (const vector<unsigned int>& para,Game_Data::Game_Element& ge, 
            const uint player_id, const uint element_id);

		bool	check_quest_is_complet		(const uint32 player_id, const uint32 quest_id, int send_update = 1 );

		void	upate_npc_quest_operate		( const uint32 player_id, const uint32 quest_id, const Game_Data::game_quest_content& qc, 
												const uint8 npc_opr, bool remove_other = false );

		bool	process_update_ring_quest_content( const uint32 player_id, const uint32 quest_id, const uint32 ring_id,const uint32 select_ring_quest_id );
		void	upate_npc_quest_operate_remove_other( const uint32 player_id, const uint32 quest_id, const uint8 npc_opr, vector<uint>& para_vec );
		void	get_content_element_id_by_key( const uint32 player_id,  const uint32 quest_id, vector<uint>& para_vec, const char*  keycontent );

		void    send_msg_radiate_player(uint32 player_id,uint quest_id);
		
		static quest_logic* instance_p_;

		quest_interface_handler_map_t	quest_award_func_interface_map_;
		quest_interface_handler_map_t quest_func_interface_map_;
		quest_interface_handler_map_t quest_cmd_func_interface_map_;
		
		vector<string> award_cmd_str_list;
	};

}

#endif

