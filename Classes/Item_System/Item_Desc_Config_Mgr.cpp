

//#include <fstream>
#ifdef YN_LINUX
#include <string.h>
#endif

#ifdef GAME_CLIENT
#include "json/json_header.h"
#include "cocos2d.h"
//#include "Game_Utils.h"
#else
#include "json/json.h"
#endif

#include "Item_Desc_Config_Mgr.h"
#include "Item_Config_Mgr.h"
#include "Common/GameDefine.h"

#ifdef GAME_CLIENT
#define EQUIPMENT_CONFIG_FILE_PATH "game_data/item_system/item_desc_config.json"
#else
#define EQUIPMENT_CONFIG_FILE_PATH "../config/item_system/item_desc_config.json"
#endif

namespace Game_Data
{
	Item_Desc_Config_Mgr* Item_Desc_Config_Mgr::instance_ = NULL;
	Item_Desc_Config_Mgr::Item_Desc_Config_Mgr(void)
	{
		m_map_dictionary.clear();
		memset(m_quality_icon_id,0,sizeof(m_quality_icon_id));
		memset(m_charactor_quality_circle_icon_id,0,sizeof(m_charactor_quality_circle_icon_id));
		memset(m_skill_square_icon_id,0,sizeof(m_skill_square_icon_id));
		memset(m_skill_circle_icon_id,0,sizeof(m_skill_circle_icon_id));
		memset(m_quality_desc_id,0,sizeof(m_quality_desc_id));
		memset(m_attr_desc_id,0,sizeof(m_attr_desc_id));
		memset(m_vein_level_icon_id,0,sizeof(m_vein_level_icon_id));
		memset(m_vein_level_desc_id,0,sizeof(m_vein_level_desc_id));
	}

	Item_Desc_Config_Mgr::~Item_Desc_Config_Mgr(void)
	{
	}

	Item_Desc_Config_Mgr* Item_Desc_Config_Mgr::instance()
	{
		if(instance_ == NULL)
		{
			instance_ = new Item_Desc_Config_Mgr;
		}

		return instance_;
	}

	int Item_Desc_Config_Mgr::initialize()
	{
#ifdef GAME_CLIENT
		init_quality_icon_data();
		init_vein_level_icon_data();
#else
#endif
		init_quality_desc_data();
		init_attr_desc_data();
		load_item_desc_data();
		init_vein_level_desc_data();

		return 0;
	}

#ifdef GAME_CLIENT

	void Item_Desc_Config_Mgr::init_quality_icon_data()
	{
		m_quality_icon_id[QT_WHITE] = 2901;
		m_quality_icon_id[QT_GREEN] = 2902;
		m_quality_icon_id[QT_BLUE] = 2903;
		m_quality_icon_id[QT_PURPLE] = 2904;
		m_quality_icon_id[QT_ORANGE] = 2905;
		m_quality_icon_id[QT_MAX] = 2906;

		m_charactor_quality_circle_icon_id[QT_WHITE] = 4013;
		m_charactor_quality_circle_icon_id[QT_GREEN] = 4014;
		m_charactor_quality_circle_icon_id[QT_BLUE] = 4015;
		m_charactor_quality_circle_icon_id[QT_PURPLE] = 4016;
		m_charactor_quality_circle_icon_id[QT_ORANGE] = 4017;
		m_charactor_quality_circle_icon_id[QT_MAX] = 4023;

		m_skill_circle_icon_id[QT_WHITE] = 4013;
		m_skill_circle_icon_id[QT_GREEN] = 4014;
		m_skill_circle_icon_id[QT_BLUE] = 4015;
		m_skill_circle_icon_id[QT_PURPLE] = 4016;
		m_skill_circle_icon_id[QT_ORANGE] = 4017;

		m_skill_square_icon_id[QT_WHITE] = 4018;
		m_skill_square_icon_id[QT_GREEN] = 4019;
		m_skill_square_icon_id[QT_BLUE] = 4020;
		m_skill_square_icon_id[QT_PURPLE] = 4021;
		m_skill_square_icon_id[QT_ORANGE] = 4022;

	}

	void Item_Desc_Config_Mgr::init_vein_level_icon_data()
	{
		m_vein_level_icon_id[0] = 2801;
		m_vein_level_icon_id[1] = 2802;
		m_vein_level_icon_id[2] = 2803;
		m_vein_level_icon_id[3] = 2804;
		m_vein_level_icon_id[4] = 2805;
		m_vein_level_icon_id[5] = 2806;
	}

	void Item_Desc_Config_Mgr::show_alert(int desc_id)
	{
		const char* str = get_string_by_id(desc_id);
		//Game_Utils::instance()->show_alert(str);
	}

	void Item_Desc_Config_Mgr::show_alert(const char* desc)
	{
		//Game_Utils::instance()->show_alert(desc);
	}

#else
#endif

	void Item_Desc_Config_Mgr::init_quality_desc_data()
	{
		m_quality_desc_id[QT_WHITE] = 2901;
		m_quality_desc_id[QT_GREEN] = 2902;
		m_quality_desc_id[QT_BLUE] = 2903;
		m_quality_desc_id[QT_PURPLE] = 2904;
		m_quality_desc_id[QT_ORANGE] = 2905;
	}

	void Item_Desc_Config_Mgr::init_attr_desc_data()
	{
		m_attr_desc_id[RAT_HEALTH] = 2906;
		m_attr_desc_id[RAT_MAGIC] = 2907;
		m_attr_desc_id[RAT_ATTACK] = 2908;
		m_attr_desc_id[RAT_DEFENSE] = 2909;
		m_attr_desc_id[RAT_HIT] = 2910;
		m_attr_desc_id[RAT_DODGE] = 2911;
		m_attr_desc_id[RAT_CRIT] = 2912;
		m_attr_desc_id[RAT_TENACITY] = 2913;
		//m_attr_desc_id[RAT_HURT] = 2915;
		m_attr_desc_id[RAT_HURT] = 90503;

		m_attr_desc_id[RAT_HP_RECOBER] = 2916;
		m_attr_desc_id[RAT_MP_RECOBER] = 2917;
		m_attr_desc_id[RAT_MAGIC_SUB] = 2918;
		m_attr_desc_id[RAT_MAGIC_SPEED] = 2919;
		m_attr_desc_id[RAT_POW] = 90504;
	}

	void Item_Desc_Config_Mgr::init_vein_level_desc_data()
	{
		m_vein_level_desc_id[0] = 90311;
		m_vein_level_desc_id[1] = 90312;
		m_vein_level_desc_id[2] = 90313;
		m_vein_level_desc_id[3] = 90314;
		m_vein_level_desc_id[4] = 90315;
		m_vein_level_desc_id[5] = 90316;
	}

	int Item_Desc_Config_Mgr::load_item_desc_data()
	{
		m_map_dictionary.clear();

#ifdef GAME_CLIENT
		//unsigned long size = 0;
		ssize_t size = 0;
		unsigned char* pData = 0;

		pData = cocos2d::FileUtils::getInstance()->getFileData
			(EQUIPMENT_CONFIG_FILE_PATH, "rb", &size);

		//         cocos2d::CCFileData data(Player_Base_Attr_Config_Data_FILE_PATH, "rb");
		//         unsigned long nBufSize = data.getSize();
		//         char* pBuffer = (char*) data.getBuffer();	 
		Json::Reader j_reader;
		Json::Value root_value;
		if (!j_reader.parse((const char*) pData,(const char*) (pData+size), root_value))
		{
			//cout << "parse failed!" << j_reader.getFormatedErrorMessages().c_str() << endl;
			//  exit(0);
			CC_SAFE_DELETE_ARRAY(pData);   
			return -1;
		}

#else
		std::ifstream fin(EQUIPMENT_CONFIG_FILE_PATH);
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

		int id = 0; 
		for (Json::Value::iterator iter = root_value.begin();iter != root_value.end();++iter)
		{
			Json::Value &v = (*iter)["base_id"];
			if (!v.empty())
			{
				id = v.asInt();
			}

			string str;
			v = (*iter)["desc"];
			if (!v.empty())
			{
				str = v.asString();
				/*char space = str.back();
				if (space == ' ')
				{
				str = str.substr(0, str.size() - 1);
				}*/
			}

			m_map_dictionary.insert(make_pair(id, str));

		}
		return 0;
	}

	const char* Item_Desc_Config_Mgr::get_string_by_id(int id)
	{
		if (id == 0)
		{
			return "";
		}

		map<int, string>::iterator it = m_map_dictionary.find(id);
		if ( it != m_map_dictionary.end() )
			return (it->second).c_str();

#if (defined WIN32 && defined GAME_CLIENT)
		char szMsg[128] = {0};
		sprintf(szMsg,"Error:Item_Desc_Config_Mgr::get_string_by_id=%d",id);
		CC_ASSERT(false && szMsg);
#endif

		return "";
	}


	const char* Item_Desc_Config_Mgr::get_quality_icon(int quality)
	{
		quality = quality % (QT_MAX+1);
		const char* path = ITEM_CONFIG_MGR::instance()->get_icon_path(m_quality_icon_id[quality]);
        std::string p("icon/");
        p+=path;
        return p.c_str();
	}

	const char* Item_Desc_Config_Mgr::get_charactor_quality_circle_icon(int quality)
	{
		quality = quality % (QT_MAX+1);
		const char* path = ITEM_CONFIG_MGR::instance()->get_icon_path(m_charactor_quality_circle_icon_id[quality]);
        std::string p("icon/");
        p+=path;
        return p.c_str();
	}

	const char* Item_Desc_Config_Mgr::get_skill_circle_icon( int quality )
	{
		quality = quality % (QT_MAX+1);
		const char* path = ITEM_CONFIG_MGR::instance()->get_icon_path(m_skill_circle_icon_id[quality]);
        std::string p("icon/");
        p+=path;
        return p.c_str();
	}

	const char* Item_Desc_Config_Mgr::get_skill_square_icon( int quality)
	{
		quality = quality % (QT_MAX+1);
		const char* path = ITEM_CONFIG_MGR::instance()->get_icon_path(m_skill_square_icon_id[quality]);
        std::string p("icon/");
        p+=path;
        return p.c_str();
	}

	const char* Item_Desc_Config_Mgr::get_quality_string(int quality)
	{
		quality = quality % QT_MAX;
		const char* desc = get_string_by_id(m_quality_desc_id[quality]);
		return desc;
	}

	const char* Item_Desc_Config_Mgr::get_attr_string(int attr_type)
	{
		attr_type = attr_type % RAT_MAX;
		const char* desc = get_string_by_id(m_attr_desc_id[attr_type]);
		return desc;
	}

	const char* Item_Desc_Config_Mgr::get_vein_level_icon(int level)
	{
		level = level % (VEIN_LEVEL_MAX);
		const char* path = ITEM_CONFIG_MGR::instance()->get_icon_path(m_vein_level_icon_id[level]);
        std::string p("icon/");
        p+=path;
		return p.c_str();
	}

	const char* Item_Desc_Config_Mgr::get_vein_level_string(int level)
	{
		level = level % (VEIN_LEVEL_MAX);
		const char* desc = get_string_by_id(m_vein_level_desc_id[level]);
		return desc;
	}

#ifdef GAME_CLIENT
    const char* Item_Desc_Config_Mgr::get_gem_inlay_string(int cur_item_quality,int need_item_quality)
    {
        const char* desc = get_string_by_id(GEM_NOT_INLAY);
        if (cur_item_quality < need_item_quality)
        {
            if (need_item_quality == 1)
            {
                desc = get_string_by_id(GEM_GREEN_QUA_OPEN);
            }
            else if (need_item_quality == 2)
            {
                desc = get_string_by_id(GEM_BLUE_QUA_OPEN);
            }
            else if (need_item_quality == 3)
            {
                desc = get_string_by_id(GEM_PURSE_QUA_OPEN);
            }
            else if (need_item_quality == 4)
            {
                desc = get_string_by_id(GEM_ORANGE_QUA_OPEN);
            }
        } 
        
        return desc;
    }
#else
	const char* Item_Desc_Config_Mgr::get_gem_inlay_string(int cur_item_quality,int need_item_quality)
	{
		return NULL;
	}
#endif
}