
#include <fstream>
#ifdef GAME_CLIENT
#include "json/json_header.h"
#include "cocos2d.h"
#else
#include "json/json.h"
#endif
#include "Skill_Mgr.h"
#include "Technical_Mgr.h"
#include "quest_system/quest_data/quest_json_config.h"


#ifdef GAME_CLIENT
#define TECHNICAL_FILE_NAME "game_data/skill/technical_config.json"
#else
#define TECHNICAL_FILE_NAME "../config/skill/technical_config.json"
#endif

Technical_Mgr* Technical_Mgr::instance_ = 0;
Technical_Mgr::Technical_Mgr(void)
{
}

Technical_Mgr* Technical_Mgr::instance()
{
    if( NULL == instance_ )
        instance_ = new Technical_Mgr;

    return instance_;

}

Technical_Mgr::~Technical_Mgr(void)
{
}

void Technical_Mgr::cleanup()
{
	m_mapTechnical.clear();
}

int Technical_Mgr::initialize()
{
	m_mapTechnical.clear();

	load_technical_data();

	return 0;
}

int Technical_Mgr::load_technical_data()
{
	#ifdef GAME_CLIENT
        ssize_t size = 0;
        unsigned char* pData = 0;
		CCLOG("Technical_Mgr::load_technical_data begin");
        pData = cocos2d::FileUtils::getInstance()->getFileData
            (TECHNICAL_FILE_NAME, "rb", &size);

        //         cocos2d::CCFileData data(Player_Base_Attr_Config_Data_FILE_PATH, "rb");
        //         unsigned long nBufSize = data.getSize();
        //         char* pBuffer = (char*) data.getBuffer();	 

        Json::Reader j_reader;
        Json::Value root_value;
        if (!j_reader.parse((const char*) pData,(const char*) (pData+size), root_value))
        {	
            //cout << "parse failed!" << j_reader.getFormatedErrorMessages().c_str() << endl;
            //  exit(0);
			CCLOG("Technical_Mgr::load_technical_data parse error!!!");
            CC_SAFE_DELETE_ARRAY(pData);   
            return -1;
        }
#else
        std::ifstream fin(TECHNICAL_FILE_NAME);
        if (!fin)
        {
            return -1;
        }
        Json::Reader j_reader;
        Json::Value root_value;
        if (!j_reader.parse(fin, root_value))
        {
            printf("/n%s/n", j_reader.getFormatedErrorMessages().c_str());
            return -1;
        }
#endif

	Technical_Data* con_cfg = NULL;
	
	for (Json::Value::iterator iter = root_value.begin();
		iter != root_value.end();
		++iter)
	{
		con_cfg = new Technical_Data;
		//memset(con_cfg, 0, sizeof(Technical_Data)); (¿Óµù)

		Json::Value &v = (*iter)["technical_id"];
		if (!v.empty())
		{
			con_cfg->technical_id = v.asInt();
		}
		v = (*iter)["quality"];
		if (!v.empty())
		{
			con_cfg->quality = v.asInt();
		}
		v = (*iter)["icon_index"];
		if (!v.empty())
		{
			con_cfg->icon_index = v.asInt();
		}
		v = (*iter)["name_index"];
		if (!v.empty())
		{
			con_cfg->name_index = v.asInt();
		}
		v = (*iter)["desc_index"];
		if (!v.empty())
		{
			con_cfg->desc_index = v.asInt();
		}
		v = (*iter)["charater_type"];
		if (!v.empty())
		{
			con_cfg->charater_type = v.asInt();
		}
		v = (*iter)["learn_base_money"];
		if (!v.empty())
		{
			con_cfg->learn_base_money = v.asInt();
		}
		v = (*iter)["learn_level_money"];
		if (!v.empty())
		{
			con_cfg->learn_level_money = v.asInt();
		}
		v = (*iter)["levelup_max"];
		if (!v.empty())
		{
			con_cfg->levelup_max = v.asInt();
		}
		v = (*iter)["skill_base"];
		if(!v.empty())
		{
			con_cfg->skill_base = v.asInt();
		}
		v = (*iter)["upgrade_skill_grow"];
		if (!v.empty())
		{
			con_cfg->upgrade_skill_grow = v.asInt();
		}
		v = (*iter)["skill_percent"];
		if (!v.empty())
		{
			con_cfg->skill_percent = v.asInt();
		}
		v = (*iter)["upgrade_skill_percent"];
		if (!v.empty())
		{
			con_cfg->upgrade_skill_percent = v.asInt();
		}

		item_content ic;
		v = (*iter)["skill_list"];
		if(!v.empty())
		{
			string cell_str = v.asString();
			proc_string(cell_str, ic);
		}
		con_cfg->set_skill_list(ic);
		
		m_mapTechnical.insert(make_pair(con_cfg->technical_id, con_cfg));
	}

	return 0;
}

void Technical_Mgr::get_character_technical_list(int charater_type, std::list<int> * list)
{
	Technical_Data* data = NULL;
	std::map<int, Technical_Data*>::iterator it = m_mapTechnical.begin();
	for (; it != m_mapTechnical.end(); it++)
	{
		data = it->second;
		if ( data && charater_type == data->charater_type )
		{
			list->push_back(data->technical_id);
		}
	}
}

Technical_Data* Technical_Mgr::GetTechnicalData(int technical_id)
{
	std::map<int, Technical_Data*>::iterator it = m_mapTechnical.find(technical_id);
	if ( it != m_mapTechnical.end() )
		return it->second;

	return NULL;
}

void Technical_Mgr::proc_string(const string& content_str, item_content &ic)
{
	game_element_list_t game_element_vec;
	game_content_parse::instance()->game_element_parse_cell(content_str, game_element_vec);
	ic.set_element(game_element_vec);
}