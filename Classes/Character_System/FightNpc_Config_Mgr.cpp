

#include <fstream>

#ifdef GAME_CLIENT
#include "json/json_header.h"
#include "cocos2d.h"
#else
#include "json/json.h"
#endif

#include "FightNpc_Config_Data.h"
#include "FightNpc_Config_Mgr.h"

#define FIGHTNPC_BASE_ATTR_CONFIG_DATA_FILE_PATH "game_data/Character_System/fightnpc_base_attr_config.json"

#define FIGHTNPC_LEVEL_ATTR_CONFIG_DATA_FILE_PATH "game_data/Character_System/fightnpc_level_attr_config.json"

namespace Game_Data
{
    FightNpc_Mgr* FightNpc_Mgr::instance_ = NULL;
	FightNpc_Mgr::FightNpc_Mgr()
	{

	}

	FightNpc_Mgr::~FightNpc_Mgr()
	{

	}

    FightNpc_Mgr* FightNpc_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new FightNpc_Mgr;
        }

        return instance_;
    }
	
	int FightNpc_Mgr::initialize( void )
	{
        FightNpc_base_attr_data_list_.clear();
		FightNpc_level_attr_data_list_.clear();

		load_FightNpc_Base_Attr_Config_Data();
		load_FightNpc_Level_Attr_Config_Data();

		return 0;
	}

	FightNpc_Base_Attr_Config_Data* FightNpc_Mgr::get_base_attr_config_data(int id)
	{
		std::list<FightNpc_Base_Attr_Config_Data>::iterator it = FightNpc_base_attr_data_list_.begin();
		for(; it != FightNpc_base_attr_data_list_.end(); it++)
		{
			if( (*it).get_fightnpc_id() == id )
				return &(*it);
		}

		return NULL;
	}
		
	FightNpc_Level_Attr_Config_Data* FightNpc_Mgr::get_level_attr_config_data(int id, int level_id, int level)
	{
		std::list<FightNpc_Level_Attr_Config_Data>::iterator it = FightNpc_level_attr_data_list_.begin();
		for(; it != FightNpc_level_attr_data_list_.end(); it++)
		{
			if( (*it).get_fightnpc_id() == level_id + level )
				return &(*it);
		}

		return NULL;
	}
	
    int FightNpc_Mgr::load_FightNpc_Base_Attr_Config_Data()
	{
#ifdef GAME_CLIENT
        ssize_t size = 0;
        unsigned char* pData = 0;

        pData = cocos2d::FileUtils::getInstance()->getFileData
            (FIGHTNPC_BASE_ATTR_CONFIG_DATA_FILE_PATH, "rb", &size);

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
        std::ifstream fin(FIGHTNPC_BASE_ATTR_CONFIG_DATA_FILE_PATH);
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

        FightNpc_Base_Attr_Config_Data ge;
		for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
		{
			ge.reset();
			Json::Value &v = (*iter)["FightNpc_id"];
			if (!v.empty())
			{
                ge.set_fightnpc_id(v.asUInt());
			}
			v = (*iter)["FightNpc_level_id"];
            if (!v.empty())
            {
                ge.set_fightnpc_level_id(v.asUInt());                      
            }
            v = (*iter)["FightNpc_model"];
            if (!v.empty())
            {
                ge.set_fightnpc_model(v.asUInt());                      
            }
            v = (*iter)["FightNpc_scale_rate"];
            if (!v.empty())
            {
                ge.set_fightnpc_scale_rate(v.asUInt());
            }
            v = (*iter)["FightNpc_face_mode_id"];
            if (!v.empty())
            {
                ge.set_fightnpc_face_mode_id(v.asUInt());
            }
			v = (*iter)["FightNpc_camp"];
            if (!v.empty())
            {
                ge.set_fightnpc_camp(v.asUInt());
            }
			v = (*iter)["FightNpc_ai"];
            if (!v.empty())
            {
                ge.set_fightnpc_ai(v.asUInt());
            }
            v = (*iter)["FightNpc_binding_grain_effect_id"];
            if (!v.empty())
            {
                ge.set_fightnpc_binding_grain_effect_id(v.asUInt());
            }
            v = (*iter)["FightNpc_move_speed"];
            if (!v.empty())
            {
                ge.set_fightnpc_move_speed(v.asUInt());
            }
			v = (*iter)["FightNpc_moveback_speed"];
            if (!v.empty())
            {
                ge.set_fightnpc_moveback_speed(v.asUInt());
            }
            v = (*iter)["FightNpc_behit_effect"];
            if (!v.empty())
            {
                ge.set_fightnpc_behit_effect(v.asUInt());
            }
            v = (*iter)["FightNpc_behit_sound"];
            if (!v.empty())
            {
               ge.set_fightnpc_behit_sound(v.asUInt());
            }
            v = (*iter)["FightNpc_max_level"];
            if (!v.empty())
            {
               ge.set_fightnpc_max_level(v.asUInt());
            }
			v = (*iter)["FightNpc_dead_drop_id"];
			if (!v.empty())
			{
				ge.set_fightnpc_dead_drop_id(v.asUInt());
			}
			v = (*iter)["FightNpc_relive_time_interval"];
			if (!v.empty())
			{
				ge.set_fightnpc_relive_time_interval(v.asUInt());
			}
			v = (*iter)["FightNpc_relive_max_count"];
			if (!v.empty())
			{
				ge.set_fightnpc_relive_max_count(v.asUInt());
			}
			//////////////////
			v = (*iter)["technical_id1"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_id(0, v.asUInt());                      
            }
            v = (*iter)["technical_id2"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_id(1, v.asUInt());                      
            }
			v = (*iter)["technical_id3"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_id(2, v.asUInt());                      
            }
			v = (*iter)["technical_id4"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_id(3, v.asUInt());                      
            }
			v = (*iter)["technical_id5"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_id(4, v.asUInt());                      
            }
			v = (*iter)["technical_id6"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_id(5, v.asUInt());                      
            }
			v = (*iter)["technical_id7"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_id(6, v.asUInt());                      
            }
			v = (*iter)["technical_id8"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_id(7, v.asUInt());                      
            }
			v = (*iter)["technical_id9"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_id(8, v.asUInt());                      
            }
			v = (*iter)["technical_id10"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_id(9, v.asUInt());                      
            }
			//////////////////
			v = (*iter)["technical_level1"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_level(0, v.asUInt());                      
            }
            v = (*iter)["technical_level2"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_level(1, v.asUInt());                      
            }
			v = (*iter)["technical_level3"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_level(2, v.asUInt());                      
            }
			v = (*iter)["technical_level4"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_level(3, v.asUInt());                      
            }
			v = (*iter)["technical_level5"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_level(4, v.asUInt());                      
            }
			v = (*iter)["technical_level6"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_level(5, v.asUInt());                      
            }
			v = (*iter)["technical_level7"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_level(6, v.asUInt());                      
            }
			v = (*iter)["technical_level8"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_level(7, v.asUInt());                      
            }
			v = (*iter)["technical_level9"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_level(8, v.asUInt());                      
            }
			v = (*iter)["technical_level10"];
            if (!v.empty())
            {
                ge.set_fightnpc_skill_level(9, v.asUInt());                      
            }
			/////
			v = (*iter)["king_technical_id"];
            if (!v.empty())
            {
                ge.set_fightnpc_king_skill_id(v.asUInt());                      
            }
			v = (*iter)["king_technical_level"];
            if (!v.empty())
            {
                ge.set_fightnpc_king_skill_level(v.asUInt());                      
            }

			FightNpc_base_attr_data_list_.push_back(ge);
		}

		return 0;
	}

	int FightNpc_Mgr::load_FightNpc_Level_Attr_Config_Data(void)
	{
#ifdef GAME_CLIENT
        ssize_t size = 0;
        unsigned char* pData = 0;

        pData = cocos2d::FileUtils::getInstance()->getFileData
            (FIGHTNPC_LEVEL_ATTR_CONFIG_DATA_FILE_PATH, "rb", &size);

        //         cocos2d::CCFileData data(FightNpc_Level_Attr_Config_Data_FILE_PATH, "rb");
        //         unsigned long nBufSize = data.getSize();
        //         char* pBuffer = (char*) data.getBuffer();	 

        Json::Reader j_reader;
        Json::Value root_value;
        if (!j_reader.parse((const char*) pData,(const char*) (pData+size), root_value))
        {	
            //cout << "parse failed!" << j_reader.getFormatedErrorMessages().c_str() << endl;
            //  exit(0);
			CCLOG("FightNpc_Mgr::load_FightNpc_Level_Attr_Config_Data parse error!!! \n");
            CC_SAFE_DELETE_ARRAY(pData);   
            return -1;
        }
#else
        std::ifstream fin(FIGHTNPC_LEVEL_ATTR_CONFIG_DATA_FILE_PATH);
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
		
        FightNpc_Level_Attr_Config_Data ge;
		for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
		{
			ge.reset();
			Json::Value &v = (*iter)["FightNpc_id"];
			if (!v.empty())
			{
                ge.set_fightnpc_id(v.asUInt());
			}
            v = (*iter)["FightNpc_level"];
            if (!v.empty())
            {
                ge.set_fightnpc_level(v.asUInt());
            }
            v = (*iter)["FightNpc_max_hp"];
            if (!v.empty())
            {
                ge.set_fightnpc_max_hp(v.asUInt());
            }
            v = (*iter)["FightNpc_max_mp"];
            if (!v.empty())
            {
                ge.set_fightnpc_max_mp(v.asUInt());
            }
            v = (*iter)["FightNpc_max_gp"];
            if (!v.empty())
            {
                ge.set_fightnpc_max_gp(v.asUInt());
            }
            v = (*iter)["FightNpc_gp_reduce_hurt"];
            if (!v.empty())
            {
                ge.set_fightnpc_gp_reduce_hurt(v.asUInt());
            }
            v = (*iter)["FightNpc_gp_behit_time_interval"];
            if (!v.empty())
            {
                ge.set_fightnpc_gp_behit_time_interval(v.asUInt());
            }
            v = (*iter)["FightNpc_gp_recover_speed"];
            if (!v.empty())
            {
               ge.set_fightnpc_gp_recover_speed(v.asUInt());
            }
            v = (*iter)["FightNpc_attack"];
            if (!v.empty())
            {
               ge.set_fightnpc_attack(v.asUInt());
            }
			v = (*iter)["FightNpc_define"];
			if (!v.empty())
			{
				ge.set_fightnpc_define(v.asUInt());
			}
			v = (*iter)["FightNpc_hit_ratio"];
			if (!v.empty())
			{
				ge.set_fightnpc_hit_ratio(v.asUInt());
			}
			v = (*iter)["FightNpc_avoidance"];
			if (!v.empty())
			{
				ge.set_fightnpc_avoidance(v.asUInt());
			}
			v = (*iter)["FightNpc_crit_rate"];
			if (!v.empty())
			{
				ge.set_fightnpc_crit_rate(v.asUInt());
			}
			v = (*iter)["FightNpc_tenacity"];
			if (!v.empty())
			{
				ge.set_fightnpc_tenacity(v.asUInt());
			}
			v = (*iter)["FightNpc_crit"];
			if (!v.empty())
			{
				ge.set_fightnpc_crit(v.asUInt());
			}
            
            FightNpc_level_attr_data_list_.push_back(ge);
		}

		return 0;
	}
}

