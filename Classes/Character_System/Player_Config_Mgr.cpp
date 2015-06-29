

#include <fstream>
#include "Player_Config_Data.h"

#ifdef GAME_CLIENT
#include "json/json_header.h"
#include "cocos2d.h"
#else
#include "json/json.h"
#endif

#include "Player_Config_Mgr.h"

#ifdef GAME_CLIENT
#define Player_Base_Attr_Config_Data_FILE_PATH "game_data/Character_System/player_base_attr_config.json"
#define Player_Level_Attr_Config_Data_FILE_PATH "game_data/Character_System/player_level_attr_config.json"
#define PLAYER_PORTRAIT_CONFIG_DATA_FILE_PATH "game_data/Character_System/player_portrait_config.json"
#else
#define Player_Base_Attr_Config_Data_FILE_PATH "../config/character_system/player_base_attr_config.json"
#define Player_Level_Attr_Config_Data_FILE_PATH "../config/character_system/player_level_attr_config.json"
#endif

namespace Game_Data
{
    Player_Mgr* Player_Mgr::instance_ = NULL;
	Player_Mgr::Player_Mgr()
	{

	}

	Player_Mgr::~Player_Mgr()
	{

	}

    Player_Mgr* Player_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Player_Mgr;
        }

        return instance_;
    }
	
	int Player_Mgr::initialize( void )
	{
        player_base_attr_data_map_.clear();
		player_level_attr_data_list_.clear();

		load_player_base_attr_config_data();
		load_player_level_attr_config_data();

		load_player_portrait_config();
		return 0;
	}

	Player_Base_Attr_Config_Data* Player_Mgr::get_player_base_attr(int id)
	{
		map<int, Player_Base_Attr_Config_Data>::iterator it = player_base_attr_data_map_.find(id);
		if ( it == player_base_attr_data_map_.end() )
			return NULL;

		return &(*it).second;
	}
	
	Player_Level_Attr_Config_Data* Player_Mgr::get_player_level_attr(int level_id, int level)
	{
		list<Player_Level_Attr_Config_Data>::iterator it = player_level_attr_data_list_.begin();
		for (; it != player_level_attr_data_list_.end(); it++)
		{
			if ( (*it).get_player_id() == level_id + level )
			{
				return &(*it);
			}
		}

		return NULL;
	}
	
    int Player_Mgr::load_player_base_attr_config_data()
	{
#ifdef GAME_CLIENT
        ssize_t size = 0;
        unsigned char* pData = 0;

        pData = cocos2d::FileUtils::getInstance()->getFileData
            (Player_Base_Attr_Config_Data_FILE_PATH, "rb", &size);

        //         cocos2d::CCFileData data(Player_Base_Attr_Config_Data_FILE_PATH, "rb");
        //         unsigned long nBufSize = data.getSize();
        //         char* pBuffer = (char*) data.getBuffer();	 

        Json::Reader j_reader;
        Json::Value root_value;
        if (!j_reader.parse((const char*) pData,(const char*) (pData+size), root_value))
        {	
            //cout << "parse failed!" << j_reader.getFormatedErrorMessages().c_str() << endl;
            //  exit(0);
			CCLOG("Player_Mgr::load_player_base_attr_config_data parse error!!! \n");
            CC_SAFE_DELETE_ARRAY(pData);   
            return -1;
        }
#else
        std::ifstream fin(Player_Base_Attr_Config_Data_FILE_PATH);
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

        Player_Base_Attr_Config_Data ge;
		for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
		{
			ge.reset();
			Json::Value &v = (*iter)["player_id"];
			if (!v.empty())
			{
                ge.set_player_id(v.asUInt());
			}
			v = (*iter)["player_level_id"];
            if (!v.empty())
            {
                ge.set_player_level_id(v.asUInt());
            }
            v = (*iter)["name"];
            if (!v.empty())
            {
                ge.set_player_name(v.asUInt());
            }
            v = (*iter)["player_prefession"];
            if (!v.empty())
            {
				ge.set_player_prefession(v.asString());
            }
            v = (*iter)["player_title"];
            if (!v.empty())
            {
                ge.set_player_title(v.asString());
            }
            v = (*iter)["player_quality"];
            if (!v.empty())
            {
                ge.set_player_quality(v.asUInt());
            }
            v = (*iter)["addition"];
            if (!v.empty())
            {
                ge.set_player_addition(v.asUInt());
            }
            v = (*iter)["player_model"];
            if (!v.empty())
            {
                ge.set_player_model(v.asUInt());                     
            }
            v = (*iter)["player_scale_rate"];
            if (!v.empty())
            {
                ge.set_player_scale_rate(v.asUInt());
            }
            v = (*iter)["player_face_mode_id"];
            if (!v.empty())
            {
                ge.set_player_face_mode_id(v.asUInt());
            }
            v = (*iter)["player_sex"];
            if (!v.empty())
            {
                ge.set_player_sex(v.asUInt());
            }
            v = (*iter)["player_binding_grain_effect_id"];
            if (!v.empty())
            {
                ge.set_player_binding_grain_effect_id(v.asUInt());
            }
            v = (*iter)["player_move_speed"];
            if (!v.empty())
            {
                ge.set_player_move_speed(v.asUInt());
            }
            v = (*iter)["player_behit_effect"];
            if (!v.empty())
            {
                ge.set_player_behit_effect(v.asUInt());
            }
            v = (*iter)["player_behit_sound"];
            if (!v.empty())
            {
               ge.set_player_behit_sound(v.asUInt());
            }
            v = (*iter)["player_max_level"];
            if (!v.empty())
            {
               ge.set_player_max_level(v.asUInt());
            }
			////
			v = (*iter)["technical_id1"];
            if (!v.empty())
            {
                ge.set_player_skill_id(0, v.asUInt());                      
            }
            v = (*iter)["technical_id2"];
            if (!v.empty())
            {
                ge.set_player_skill_id(1, v.asUInt());                      
            }
			v = (*iter)["technical_id3"];
            if (!v.empty())
            {
                ge.set_player_skill_id(2, v.asUInt());                      
            }
			v = (*iter)["technical_id4"];
            if (!v.empty())
            {
                ge.set_player_skill_id(3, v.asUInt());                      
            }
			v = (*iter)["technical_id5"];
            if (!v.empty())
            {
                ge.set_player_skill_id(4, v.asUInt());                      
            }
			v = (*iter)["technical_id6"];
            if (!v.empty())
            {
                ge.set_player_skill_id(5, v.asUInt());                      
            }
			v = (*iter)["technical_id7"];
            if (!v.empty())
            {
                ge.set_player_skill_id(6, v.asUInt());                      
            }
			v = (*iter)["technical_id8"];
            if (!v.empty())
            {
                ge.set_player_skill_id(7, v.asUInt());                      
            }
			v = (*iter)["technical_id9"];
            if (!v.empty())
            {
                ge.set_player_skill_id(8, v.asUInt());                      
            }
			v = (*iter)["technical_id10"];
            if (!v.empty())
            {
                ge.set_player_skill_id(9, v.asUInt());                      
            }
			v = (*iter)["king_technical_id"];
            if (!v.empty())
            {
                ge.set_player_king_skill_id(v.asUInt());                      
            }
      
            player_base_attr_data_map_.insert(make_pair(ge.get_player_id(), ge));
		}

		return 0;
	}

	int Player_Mgr::load_player_level_attr_config_data(void)
	{
#ifdef GAME_CLIENT
        ssize_t size = 0;
        unsigned char* pData = 0;

        pData = cocos2d::FileUtils::getInstance()->getFileData
            (Player_Level_Attr_Config_Data_FILE_PATH, "rb", &size);

        //         cocos2d::CCFileData data(Player_Level_Attr_Config_Data_FILE_PATH, "rb");
        //         unsigned long nBufSize = data.getSize();
        //         char* pBuffer = (char*) data.getBuffer();	 

        Json::Reader j_reader;
        Json::Value root_value;
        if (!j_reader.parse((const char*) pData,(const char*) (pData+size), root_value))
        {	
            //cout << "parse failed!" << j_reader.getFormatedErrorMessages().c_str() << endl;
            //  exit(0);
			CCLOG("Player_Mgr::load_player_level_attr_config_data parse error!!! \n");
            CC_SAFE_DELETE_ARRAY(pData);   
            return -1;
        }
#else
        std::ifstream fin(Player_Level_Attr_Config_Data_FILE_PATH);
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

		Player_Level_Attr_Config_Data ge;
		for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
		{
			ge.reset();
			Json::Value &v = (*iter)["player_id"];
			if (!v.empty())
			{
                ge.set_player_id(v.asUInt());
			}
            v = (*iter)["player_level"];
            if (!v.empty())
            {
                ge.set_player_level(v.asUInt());
            }
            v = (*iter)["player_levelup_exp"];
            if (!v.empty())
            {
                ge.set_player_levelup_exp(v.asUInt());                       
            }
            v = (*iter)["player_max_hp"];
            if (!v.empty())
            {
                ge.set_player_max_hp(v.asUInt());
            }
            v = (*iter)["player_hp_recover_speed"];
            if (!v.empty())
            {
                ge.set_player_hp_recover_speed(v.asUInt());
            }
            v = (*iter)["player_max_mp"];
            if (!v.empty())
            {
                ge.set_player_max_mp(v.asUInt());
            }
            v = (*iter)["player_max_gp"];
            if (!v.empty())
            {
                ge.set_player_max_gp(v.asUInt());
            }
            v = (*iter)["player_gp_reduce_hurt"];
            if (!v.empty())
            {
                ge.set_player_gp_reduce_hurt(v.asUInt());
            }
            v = (*iter)["player_gp_behit_time"];
            if (!v.empty())
            {
                ge.set_player_gp_behit_time(v.asUInt());
            }
            v = (*iter)["player_gp_recover_speed"];
            if (!v.empty())
            {
               ge.set_player_gp_recover_speed(v.asUInt());
            }
            v = (*iter)["player_attack"];
            if (!v.empty())
            {
               ge.set_player_attack(v.asUInt());
            }
			v = (*iter)["player_define"];
			if (!v.empty())
			{
				ge.set_player_define(v.asUInt());
			}
			v = (*iter)["player_hit_ratio"];
			if (!v.empty())
			{
				ge.set_player_hit_ratio(v.asUInt());
			}
			v = (*iter)["player_avoidance"];
			if (!v.empty())
			{
				ge.set_player_avoidance(v.asUInt());
			}
			v = (*iter)["player_crit_rate"];
			if (!v.empty())
			{
				ge.set_player_crit_rate(v.asUInt());
			}
			v = (*iter)["player_tenacity"];
			if (!v.empty())
			{
				ge.set_player_tenacity(v.asUInt());
			}
			v = (*iter)["player_crit"];
			if (!v.empty())
			{
				ge.set_player_crit(v.asUInt());
			}
			v = (*iter)["power"];
			if (!v.empty())
			{
				ge.set_player_power(v.asUInt());                      
			}
            
			player_level_attr_data_list_.push_back( ge );
		}

		return 0;
	}

int Player_Mgr::load_player_portrait_config(void)
	 {
		 player_portrait_config.clear();
#ifdef GAME_CLIENT
		 ssize_t size = 0;
         unsigned char* pData = 0;

         pData = cocos2d::FileUtils::getInstance()->getFileData(PLAYER_PORTRAIT_CONFIG_DATA_FILE_PATH, "rb", &size);

         Json::Reader j_reader;
         Json::Value root_value;
         if (!j_reader.parse((const char*) pData,(const char*) (pData+size), root_value))
         {	
             //cout << "parse failed!" << j_reader.getFormatedErrorMessages().c_str() << endl;
             //  exit(0);
             CC_SAFE_DELETE_ARRAY(pData);   
             return -1;
         }

         int base_id = 0;
         for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
         {

             Json::Value &v = (*iter)["base_id"];
             if (!v.empty())
             {
                 base_id = v.asUInt();
             }

			 v = (*iter)["path"];
			 player_portrait_config[base_id] = v.asString();
		 }
#endif
		 return 0;
	 }

	 const char* Player_Mgr::get_player_portrait(int icon_id)
	 {
		 std::map<int,std::string>::iterator it = player_portrait_config.find(icon_id);
		 if(it!=player_portrait_config.end())
		 {
			 return (*it).second.c_str();
		 }
		 return "";
	 }

     int Player_Mgr::get_name_id(int base_id)
     {
         std::map<int, Player_Base_Attr_Config_Data>::iterator iter = player_base_attr_data_map_.find(base_id);
         if (iter != player_base_attr_data_map_.end())
         {
             Player_Base_Attr_Config_Data& data = iter->second;
             return data.get_player_name();
         }
         
         return 0;
     }
}

