#ifndef __GOG_WEAPON_CONFIG_DATA__
#define __GOG_WEAPON_CONFIG_DATA__

#include <map>
#include <vector>
#include <string>
#include "Network_Common/global_macros.h"

struct god_weapon_config_data
{
	int id;
	int up_money;
	int level;
	int level_up_id;
	std::string anim_path;
};

struct god_weapon_skill_config_data
{
	int ID;
	int rate;
	int Colossus;
	int skillId;
	std::string icon;
	std::string action;
};

struct get_god_weapon_data
{
	int id;					// 神兵的ID
	int level_limit;		// 获得神兵所需的等级
	int job;				// 职业
};

typedef std::map<int, god_weapon_config_data*>		 map_god_weapon_config;
typedef map_god_weapon_config::iterator				 god_weapon_config_iter;

typedef std::map<int, god_weapon_skill_config_data*> map_god_weapon_skill_config_data;
typedef map_god_weapon_skill_config_data::iterator	 god_weapon_skill_config_iter;


typedef std::map<int, get_god_weapon_data*>			 map_get_god_weapon_config;
typedef map_get_god_weapon_config::iterator          get_god_weapon_config_iter;

#endif