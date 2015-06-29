

#include <fstream>

#ifdef GAME_CLIENT
#include "json/json_header.h"
#include "cocos2d.h"
#else
#include "json/json.h"
#endif

#include "CommonNpc.h"
#include "CommonNpc_Config_Mgr.h"

#ifdef GAME_CLIENT
		#define COMMONNPC_ATTR_CONFIG_DATA_FILE_PATH "game_data/Character_System/commonnpc_attr_config.json"
#else
        #define COMMONNPC_ATTR_CONFIG_DATA_FILE_PATH "../config/Character_System/commonnpc_attr_config.json"
#endif

namespace Game_Data
{
    CommonNpc_Config_Mgr* CommonNpc_Config_Mgr::instance_ = NULL;
	CommonNpc_Config_Mgr::CommonNpc_Config_Mgr()
	{

	}

	CommonNpc_Config_Mgr::~CommonNpc_Config_Mgr()
	{

	}

    CommonNpc_Config_Mgr* CommonNpc_Config_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new CommonNpc_Config_Mgr;
        }

        return instance_;
    }

	int CommonNpc_Config_Mgr::initialize( void )
	{
		load_CommonNpc_Attr_Config_Data();
		return 0;
	}

	int CommonNpc_Config_Mgr::load_CommonNpc_Attr_Config_Data(void)
	{
#ifdef GAME_CLIENT
		//unsigned long size = 0;
		ssize_t size = 0;
		unsigned char* pData = 0;

		pData = cocos2d::FileUtils::getInstance()->getFileData
			(COMMONNPC_ATTR_CONFIG_DATA_FILE_PATH, "rb", &size);

		//         cocos2d::CCFileData data(FightNpc_Base_Attr_Config_Data_FILE_PATH, "rb");
		//         unsigned long nBufSize = data.getSize();
		//         char* pBuffer = (char*) data.getBuffer();	 

		Json::Reader j_reader;
		Json::Value root_value;
		if (!j_reader.parse((const char*) pData,(const char*) (pData+size), root_value))
		{	
			//cout << "parse failed!" << j_reader.getFormatedErrorMessages().c_str() << endl;
			//  exit(0);
			CCLOG("FightNpc_Mgr::load_FightNpc_Base_Attr_Config_Data parse error!!! \n");
			CC_SAFE_DELETE_ARRAY(pData);   
			return -1;
		}
#else
		std::ifstream fin(COMMONNPC_ATTR_CONFIG_DATA_FILE_PATH);
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

		CommonNpcConfig ge;
		for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
		{
			ge.reset();
			Json::Value &v = (*iter)["static_character_id"];
			if (!v.empty())
			{
				ge.set_static_character_id(v.asUInt());
			}
            v = (*iter)["face_mode_id"];
            if (!v.empty())
            {
                ge.set_face_mode_id(v.asUInt());                      
            }
			v = (*iter)["appear_condition"];
			if (!v.empty())
			{
				ge.set_appear_condition(v.asUInt());                      
			}
			v = (*iter)["npc_type"];
			if (!v.empty())
			{
				ge.set_npc_type(v.asUInt());                      
			}
			v = (*iter)["dialog_id"];
			if (!v.empty())
			{
				ge.set_dialog_id(v.asUInt());
			}
			v = (*iter)["trigger_rule"];
			if (!v.empty())
			{
				ge.set_trigger_rule(v.asUInt());
			}
			v = (*iter)["wait_action"];
			if (!v.empty())
			{
				ge.set_wait_action(v.asString());                      
			}
			v = (*iter)["shop_id1"];
			if (!v.empty())
			{
				ge.set_shop_id(0, v.asUInt());
			}
			v = (*iter)["shop_id2"];
			if (!v.empty())
			{
				ge.set_shop_id(1, v.asUInt());
			}
			v = (*iter)["shop_id3"];
			if (!v.empty())
			{
				ge.set_shop_id(2, v.asUInt());
			}

			CommonNpc_attr_data_list_.push_back(ge);
		}

		return 0;
	}

	CommonNpcConfig* CommonNpc_Config_Mgr::get_commomnpc_by_id(int id)
	{
		std::list<CommonNpcConfig>::iterator it = CommonNpc_attr_data_list_.begin();
		for (; it != CommonNpc_attr_data_list_.end(); it++)
		{
			if ( (*it).get_static_character_id() == id )
			{
				return &(*it);
			}
		}

		return NULL;
	}
}

