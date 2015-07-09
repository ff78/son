#ifndef _GAME_EVENT_RESPONSE_H
#define	_GAME_EVENT_RESPONSE_H

#include "common.h"

namespace Game_Logic
{
	class Game_Event_Response
	{
	public:
		Game_Event_Response(void);
		~Game_Event_Response(void);
		static Game_Event_Response* instance(void);

		int on_hurt( const int char_type, const int char_id );
        int on_character_die( const int char_id, const int char_type, float posX= 0.f,float posY = 0.f,int player_id = 0);
        int on_finish_show_dialog( int player_id, int instance_id );

        void on_update_main_ui_info(int player_id);
        void on_update_item_ui_info(int player_id);
        void on_update_game_ui_child_info(int player_id);
        void on_update_instance_stage_info( int player_id );
        void on_update_stage( int player_id );
        void on_update_stage_all(int player_id);//更新副本选择数据
#if 1//MISSION_DIALOG
		void on_update_mission_dialog(int player_id, int quest_id);
#endif
        void on_update_friend_ui_list(int player_id);
        void on_update_skill(int player_id);
        void on_update_arena(int player_id);
        void on_update_count_down_time(int player_id,int time);
        void on_update_npcdialog(int player_id);
		void on_collided_something(int item_id,int player_id);
		void on_useitem_something(int item_id,int player_id);
//        void on_update_role_quality_up(int player_id);
//        void on_update_compound_fragment(int player_id,int change);
        void on_update_fate(int player_id);
		void on_update_selected_relation_spine( int player_id );
		void on_update_banks(int player_id);
        void on_update_rank(int player_id,int rank_type);
		void on_update_login_award(int player_id);
        void on_update_instance_sweep(int player_id);
        void on_update_gem_inlay(int player_id,int gem_pos);
        void on_update_operate_gem(int player_id,int gem_id);
        void on_update_gem_level_up(int player_id);
        void on_update_shop(int player_id);
        void on_update_daily_task(int player_id);

        int on_finish_scene_load(void);
        int on_kill_monster( int player_id, int monster_id, int kill_counts );

        //---------------------------------------------------------------------------
        int on_item( int player_id, int item_id );
        int on_equipment_quality_up( int player_id, int item_id );
        int on_equipment_level_up( int player_id, int item_id );
        int on_book_equip( int player_id, int item_id );
        int on_instance_suc( int player_id, int instance_id );
        int on_item_equip( int player_id, int item_id );
        int on_book_fragment_compound( int player_id, int item_id );
        int on_material_fragment_compound( int player_id, int item_id );
        int on_skill_upgrade( int player_id, int skill_id );
        int on_book_level_up( int player_id, int item_id );
        int on_pk_finish( int player_id );
        int on_fight_general( int player_id );
        int on_acupoint_open( int player_id );
        int on_addfriends( int player_id );
        int on_cost_gold( int player_id );
        int on_player_quality_up( int player_id );
        int on_book_quality_up( int player_id, int book_id );
        int on_gerneral_qa_up( int player_id );
        int on_add_money( int player_id );

        //----------------------------------------------------------------------------
		bool on_complete_quest		( const int player_id, const int quest_id,bool give_up_quest = false, int ring_quest_id = 0 );
		/********************* dely *******************/
		void on_update_chat(int player_id);
		/********************* dely *******************/
	private:
		static Game_Event_Response* instance_p_;

	};

}

#endif
