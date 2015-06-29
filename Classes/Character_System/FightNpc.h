#pragma once

#include "Character.h"

namespace Game_Data
{
	struct FightNpc_Base_Attr_Config_Data;
	struct FightNpc_Level_Attr_Config_Data;
	class FightNpc : public Character
	{
	public:
		FightNpc(void);
		~FightNpc(void);
	public:
		void set_base_attr_config_data(FightNpc_Base_Attr_Config_Data*  m_base_attr_p_);
		void set_level_attr_config_data(FightNpc_Level_Attr_Config_Data* m_level_attr_p_);
		virtual void init_attr_data(int static_id, int level);
	public:
		virtual int get_character_max_hp( void );
		virtual int get_character_max_mp( void );
		virtual int get_character_max_gp( void );
		virtual int get_character_gp_reduce_hurt( void );
		virtual int get_character_attack( void );
		virtual int get_character_define( void );
		virtual int get_character_hit_ratio( void );
		virtual int get_character_avoidance( void );
		virtual int get_character_crit_rate( void );
		virtual int get_character_tenacity( void );
		virtual int get_character_crit( void );
		virtual int get_skill_level(int skillid);
		virtual int get_skill_quality(int skillid);
		virtual int get_character_invincible( void );
		virtual float get_character_move_speed_rate();
		virtual void set_skill_level(int skillid, int level);
        virtual int get_face_mode_id();
        virtual int get_model();
	private:
		FightNpc_Base_Attr_Config_Data*  m_base_attr_p_;
		FightNpc_Level_Attr_Config_Data* m_level_attr_p_;
	};
}