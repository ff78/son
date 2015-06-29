#pragma once

#include "Network_Common/global_macros.h"
#include "Character.h"

namespace Game_Data
{
	class FightPlayer : public Character
	{
	public:
		FightPlayer(void);
		~FightPlayer(void);
	public:
		virtual void init_attr_data(int static_id, int level);
		void set_base_attr_config_data(Player_Base_Attr_Config_Data*  m_base_attr_p_);
		Player_Base_Attr_Config_Data* get_base_attr_config_data(){return  m_base_attr_p_;};
		void set_level_attr_config_data(Player_Level_Attr_Config_Data* m_level_attr_p_);
		Player_Level_Attr_Config_Data* get_level_attr_config_data(){return  m_level_attr_p_;};
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
		virtual int get_model();
		const char* get_character_name()
		{
			return m_name;
		}

		void  set_character_name(const char* name)
		{
			memcpy(m_name, name, MAX_NAME_LEN);
		}
	private:
		char								m_name[MAX_NAME_LEN+1];
		Player_Base_Attr_Config_Data*       m_base_attr_p_;
		Player_Level_Attr_Config_Data*      m_level_attr_p_;
	};
}