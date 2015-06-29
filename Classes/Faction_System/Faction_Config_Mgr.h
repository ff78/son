#ifndef __FACTION_CONFIG_MGR_H__
#define __FACTION_CONFIG_MGR_H__

#include "Game_Interface/common.h"
#include "Faction_data.h"

namespace Game_Data
{

	class Faction_Config_Mgr
	{
	public:
		Faction_Config_Mgr();
		~Faction_Config_Mgr();

		static Faction_Config_Mgr* instance();

		faction_data_common* get_faction_data_by_lv(int lv);

		create_faction* get_create_faction();

		int initialize(void);

	private:
		static Faction_Config_Mgr*         instance_;

		int load_faction_config_data();
		int load_create_faction_config_data();


		faction_config_map	m_faction_data;

		create_faction*  m_create_faction;
	};
}

typedef Game_Data::Faction_Config_Mgr FACTION_CONFIG_MGR;

#endif