#ifndef __GOD_WEAPON_CONFIG_MGR__
#define __GOD_WEAPON_CONFIG_MGR__

#include "God_Weapon_Config_Data.h"

namespace Game_Data
{
	class God_Weapon_Config_Mgr
	{
	public:
		God_Weapon_Config_Mgr();
		virtual ~God_Weapon_Config_Mgr();

		static God_Weapon_Config_Mgr* instance();

		int initialize(void);
		int release(void);

	public:
		int load_get_god_weapon_config_data();
		int load_god_weapon_config_data();

		god_weapon_config_data* get_god_weapon_config_data(int id);
		god_weapon_skill_config_data* get_god_weapon_skill_config_data(int id);

		int get_create_god_weapon_id(int player_lv,int player_job);
	private:
		static God_Weapon_Config_Mgr*         instance_;

		map_god_weapon_config		m_map_god_weapon;
		map_god_weapon_skill_config_data	m_map_god_weapon_skill;
		map_get_god_weapon_config	m_map_get_god_weapon;
	};
}
typedef Game_Data::God_Weapon_Config_Mgr GOD_WEAPON_CONFIG_MGR;

#endif