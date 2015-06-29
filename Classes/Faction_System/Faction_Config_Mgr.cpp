#include "Faction_Config_Mgr.h"
#include "json/json_header.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#define FACTION_CONFIG_FILE_PATH "game_data/faction_system/faction_data.json"
#define CREATE_FACTION_CONFIG_FILE_PATH "game_data/faction_system/create_faction.json"

USING_NS_CC;
using namespace cocostudio;

namespace Game_Data
{
	Faction_Config_Mgr* Faction_Config_Mgr::instance_ = NULL;
	Faction_Config_Mgr::Faction_Config_Mgr()
	{
		m_create_faction = NULL;
	}

	Faction_Config_Mgr::~Faction_Config_Mgr()
	{
	}

	// 单件
	Faction_Config_Mgr* Faction_Config_Mgr::instance()
	{
		if (instance_ == NULL)
		{
			instance_ = new Faction_Config_Mgr;
		}

		return instance_;
	}

	// 初始化
	int Faction_Config_Mgr::initialize()
	{
		load_faction_config_data();

		load_create_faction_config_data();

		return 0;
	}

	// 读取技能配置表
	int Faction_Config_Mgr::load_faction_config_data()
	{
        std::string contentStr = FileUtils::getInstance()->getStringFromFile(FACTION_CONFIG_FILE_PATH);
        rapidjson::Document doc;
        
        doc.Parse<0>(contentStr.c_str());
        bool ret = !doc.HasParseError();
        
        if (!ret) {
            return -1;
        }
        
        if (doc.IsArray()) {
            int size = doc.Size();
            faction_data_common* config = nullptr;
            for (int i = 0; i < size; i++) {
                config = new faction_data_common;
                config->lv = DICTOOL->getIntValue_json(doc[i], "level");
                config->buy_num = DICTOOL->getIntValue_json(doc[i], "buy_num");
                config->digging_num = DICTOOL->getIntValue_json(doc[i], "digging_num");
                config->digging_values = DICTOOL->getIntValue_json(doc[i], "digging_values");
                config->worship_num = DICTOOL->getIntValue_json(doc[i], "worship_num");
                config->worship_values = DICTOOL->getIntValue_json(doc[i], "worship_values");
                config->worship_active_num = DICTOOL->getIntValue_json(doc[i], "worship_active_num");
                config->digging_active_num = DICTOOL->getIntValue_json(doc[i], "digging_active_num");
                config->boss_id = DICTOOL->getIntValue_json(doc[i], "boss_id");
                config->boss_kill = DICTOOL->getIntValue_json(doc[i], "boss_kill");
                config->kill_boss_values = DICTOOL->getIntValue_json(doc[i], "kill_boss_values");
                config->kill_boss_active_num = DICTOOL->getIntValue_json(doc[i], "kill_boss_active_num");
                config->level_exp = DICTOOL->getIntValue_json(doc[i], "level_exp");
                config->totems_max = DICTOOL->getIntValue_json(doc[i], "totems_max");
                config->totems_lv[TOTMES_LIFE] = DICTOOL->getIntValue_json(doc[i], "totems_life_lv");
                config->totoems_num[TOTMES_LIFE] = DICTOOL->getIntValue_json(doc[i], "totems_life_num");
                config->totoems_num[TOTMES_ATTACK] = DICTOOL->getIntValue_json(doc[i], "totems_attack_lv");
                config->totems_lv[TOTMES_DEFENSE] = DICTOOL->getIntValue_json(doc[i], "totems_defense_lv");
                config->totoems_num[TOTMES_DEFENSE] = DICTOOL->getIntValue_json(doc[i], "totems_defense_num");
                config->totems_lv[TOTMES_ICE] = DICTOOL->getIntValue_json(doc[i], "totems_ice_lv");
                config->totoems_num[TOTMES_ICE] = DICTOOL->getIntValue_json(doc[i], "totems_ice_num");
                config->totems_lv[TOTMES_FIRE] = DICTOOL->getIntValue_json(doc[i], "totems_fire_lv");
                config->totems_lv[TOTMES_THUNDER] = DICTOOL->getIntValue_json(doc[i], "totems_thunder_lv");
                config->totoems_num[TOTMES_THUNDER] = DICTOOL->getIntValue_json(doc[i], "totems_thunder_num");
                config->totems_lv[TOTMES_WIND] = DICTOOL->getIntValue_json(doc[i], "totems_wind_lv");
                config->totoems_num[TOTMES_WIND] = DICTOOL->getIntValue_json(doc[i], "totems_wind_num");
                config->totems_lv[TOTMES_LIGHR] = DICTOOL->getIntValue_json(doc[i], "totems_light_lv");
                config->totoems_num[TOTMES_LIGHR] = DICTOOL->getIntValue_json(doc[i], "totems_light_num");
                config->totems_lv[TOTMES_DARK] = DICTOOL->getIntValue_json(doc[i], "totems_dark_lv");
                config->totoems_num[TOTMES_DARK] = DICTOOL->getIntValue_json(doc[i], "totems_dark_num");
                m_faction_data[config->lv] = config;
            }
        }
        
		return 0;
	}

	int Faction_Config_Mgr::load_create_faction_config_data()
	{
        std::string contentStr = FileUtils::getInstance()->getStringFromFile(CREATE_FACTION_CONFIG_FILE_PATH);
        rapidjson::Document doc;
        
        doc.Parse<0>(contentStr.c_str());
        bool ret = !doc.HasParseError();
        
        if (!ret) {
            return -1;
        }
        
        create_faction* config = nullptr;
        if (doc.IsArray()) {
            int size = doc.Size();
            
            for (int i = 0; i < size; i++) {
                config = new create_faction;
                config->level = DICTOOL->getIntValue_json(doc[i], "level_limit");
                config->gold = DICTOOL->getIntValue_json(doc[i], "gold");
                config->token = DICTOOL->getIntValue_json(doc[i], "token");
            }
        }

		m_create_faction = config;

		return 0;
	}

	faction_data_common* Faction_Config_Mgr::get_faction_data_by_lv(int lv)
	{
		map<int, faction_data_common*>::iterator _iter = m_faction_data.begin();
		for (_iter; _iter != m_faction_data.end(); ++_iter)
		{
			if ((*_iter).second->lv == lv)
			{
				return (*_iter).second;
			}
		}
		return NULL;
	}

	create_faction* Faction_Config_Mgr::get_create_faction()
	{
		return m_create_faction;
	}

	
}