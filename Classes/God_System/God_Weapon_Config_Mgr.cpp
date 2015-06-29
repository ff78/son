#include "God_Weapon_Config_Data.h"
#include "God_Weapon_Config_Mgr.h"
#include "../json/json_header.h"
#include "Play_System/Container_Mgr.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "json/document.h"

#define  GET_GOD_WEAPON_CONFIG_FILE_PATH  "game_data/god_weapon_system/get_god_weapon.json"
#define  GOD_WEAPON_CONFIG_FILE_PATH	"game_data/god_weapon_system/god_weapon.json"
#define  GOD_WEAPON_SKILL_CONFIG_FILE_PATH	"game_data/god_weapon_system/data_ClsSkill.json"

namespace Game_Data
{
	God_Weapon_Config_Mgr* God_Weapon_Config_Mgr::instance_ = NULL;
	God_Weapon_Config_Mgr::God_Weapon_Config_Mgr(){}

	God_Weapon_Config_Mgr::~God_Weapon_Config_Mgr(){}

	God_Weapon_Config_Mgr* God_Weapon_Config_Mgr::instance()
	{
		if (instance_ == NULL)
		{
			instance_ = new God_Weapon_Config_Mgr;
		}

		return instance_;
	}

	int God_Weapon_Config_Mgr::initialize(void)
	{
		m_map_god_weapon.clear();
		m_map_get_god_weapon.clear();
		m_map_god_weapon_skill.clear();

		load_get_god_weapon_config_data();
		load_god_weapon_config_data();

		return 0;
	}

	int God_Weapon_Config_Mgr::load_get_god_weapon_config_data()
	{
		Json::Value root_value;
		Container_Mgr::instance()->get_json_value_by_file_name(root_value, GET_GOD_WEAPON_CONFIG_FILE_PATH);

		get_god_weapon_data* config = NULL;
		char key[255] = { 0 };
		char values[255] = { 0 };
		for (Json::Value::iterator iter = root_value.begin(); iter != root_value.end(); ++iter)
		{
			config = new get_god_weapon_data;

			Json::Value &v = (*iter)["id"];
			if (!v.empty())
			{
				config->id = v.asUInt();
			}
			v = (*iter)["level_limit"];
			if (!v.empty())
			{
				config->level_limit = v.asUInt();
			}
			v = (*iter)["job"];
			if (!v.empty())
			{
				config->job = v.asUInt();
			}
			m_map_get_god_weapon[config->job] = config;
		}

		return 0;
	}

	int God_Weapon_Config_Mgr::load_god_weapon_config_data()
	{
		god_weapon_skill_config_data* skill_config = nullptr;
		std::string content_string = cocos2d::FileUtils::getInstance()->getStringFromFile(GOD_WEAPON_SKILL_CONFIG_FILE_PATH);
		rapidjson::Document doc1;
		doc1.Parse<0>(content_string.c_str());
		if (doc1.IsArray())
		{
			for (int i = 0; i < doc1.Size(); i++)
			{
				skill_config = new god_weapon_skill_config_data;

				int id = cocostudio::DICTOOL->getIntValue_json(doc1[i], "ID");
				skill_config->ID = id;
				int rate = cocostudio::DICTOOL->getIntValue_json(doc1[i], "rate");
				skill_config->rate = rate;

				int Colossus = cocostudio::DICTOOL->getIntValue_json(doc1[i], "Colossus");
				skill_config->Colossus = Colossus;

				int skillId = cocostudio::DICTOOL->getIntValue_json(doc1[i], "skillId");
				skill_config->skillId = skillId;

				std::string icon = cocostudio::DICTOOL->getStringValue_json(doc1[i], "icon");
				skill_config->icon = icon;

				std::string action = cocostudio::DICTOOL->getStringValue_json(doc1[i], "action");
				skill_config->action = action;

				m_map_god_weapon_skill[skill_config->ID] = skill_config;

			}

		}
		//Json::Value root_value;
		//Container_Mgr::instance()->get_json_value_by_file_name(root_value, GOD_WEAPON_CONFIG_FILE_PATH);
		//god_weapon_config_data* config = NULL;
		//char key[255] = { 0 };
		//char values[255] = { 0 };
		//for (Json::Value::iterator iter = root_value.begin(); iter != root_value.end(); ++iter)
		//{
		//	config = new god_weapon_config_data;

		//	Json::Value &v = (*iter)["id"];
		//	if (!v.empty())
		//	{
		//		config->id = v.asUInt();
		//	}
		//	v = (*iter)["level"];
		//	if (!v.empty())
		//	{
		//		config->level = v.asUInt();
		//	}
		//	v = (*iter)["up_money"];
		//	if (!v.empty())
		//	{
		//		config->up_money = v.asUInt();
		//	}
		//	v = (*iter)["level_up_id"];
		//	if (!v.empty())
		//	{
		//		config->level_up_id = v.asUInt();
		//	}
		//	v = (*iter)["anim_path"];
		//	if (!v.empty())
		//	{
		//		config->anim_path = v.asString();
		//	}
		//	m_map_god_weapon[config->id] =  config;
		//}
		god_weapon_config_data* config = nullptr;
		std::string content_string1 = cocos2d::FileUtils::getInstance()->getStringFromFile(GOD_WEAPON_CONFIG_FILE_PATH);
		rapidjson::Document doc;
		doc.Parse<0>( content_string1.c_str() );
		if ( doc.IsArray() )
		{
			for (int i = 0; i < doc.Size();i++)
			{
				config = new god_weapon_config_data;

				int id = cocostudio::DICTOOL->getIntValue_json(doc[i], "id");
				config->id = id;
				int level = cocostudio::DICTOOL->getIntValue_json(doc[i], "level");
				config->level = level;

				int up_money = cocostudio::DICTOOL->getIntValue_json(doc[i], "up_money");
				config->up_money = up_money;

				int level_up_id = cocostudio::DICTOOL->getIntValue_json(doc[i], "level_up_id");
				config->level_up_id = level_up_id;

				std::string anim = cocostudio::DICTOOL->getStringValue_json(doc[i], "anim_path");
				config->anim_path = anim;

				m_map_god_weapon[config->id] = config;

			}

		}

		return 0;
	}

	god_weapon_config_data* God_Weapon_Config_Mgr::get_god_weapon_config_data(int id)
	{
		god_weapon_config_iter _iter = m_map_god_weapon.begin();
		for (; _iter != m_map_god_weapon.end(); ++_iter)
		{
			if ((*_iter).second->id == id)
			{
				return (*_iter).second;
			}
		}

		return NULL;
	}

	god_weapon_skill_config_data* God_Weapon_Config_Mgr::get_god_weapon_skill_config_data(int id)
	{
		god_weapon_skill_config_iter _iter = m_map_god_weapon_skill.begin();
		for (; _iter != m_map_god_weapon_skill.end(); ++_iter)
		{
			if ((*_iter).second->ID == id)
			{
				return (*_iter).second;
			}
		}

		return NULL;
	}

	int God_Weapon_Config_Mgr::get_create_god_weapon_id(int player_lv, int player_job)
	{
		get_god_weapon_config_iter _iter = m_map_get_god_weapon.find(player_job);
		if (_iter != m_map_get_god_weapon.end())
		{
			if ((*_iter).second->level_limit <= player_lv)
			{
				return (*_iter).second->id;
			}
		}
		return 0;

	}

}
