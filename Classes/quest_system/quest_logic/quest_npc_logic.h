

#ifndef QUEST_NPC_LOGIC_H
#define	QUEST_NPC_LOGIC_H
namespace Game_Logic
{
	struct Game_Interface;
	class quest_npc_logic
	{

	public:
		quest_npc_logic();
		virtual ~quest_npc_logic();

		static quest_npc_logic* instance();

		static bool proc_npc_quest_bind( Game_Interface& gm_interface );
        static bool proc_npc_list_quest_bind( Game_Interface& gm_interface );

	private:
        int proc_analysis_npc_list_quest_bind( const uint32 player_id, vector<int> npc_lst );
		void proc_check_quest_list(const uint32 player_id, vector<uint32>& qst_lst,const char* key, bool send_update = true); //check quest can be accepted or be submit
		void proc_check_quest_in_proc_list(const uint32 player_id, vector<uint32>& qst_lst,const char* key); //check challgeng or dialog when the quest state is in process
		void check_accepted_quest_bind( const uint32 player_id );
		void check_accepted_quest_key_element_bind( const uint32 player_id, const uint32 quest_id, const char* key_content );
		static quest_npc_logic* instance_p_;

	};
}
#endif // !defined(EA_944F2BAF_C2B9_48d4_834F_3F4987569E11__INCLUDED_)
