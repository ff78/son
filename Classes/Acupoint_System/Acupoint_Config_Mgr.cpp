
//#include <fstream>
#ifdef YN_LINUX
#include <string.h>
#endif

#ifdef GAME_CLIENT
#include "json/json_header.h"
#include "cocos2d.h"
#else
#include "json/json.h"
#endif

#include "Acupoint_Config_Mgr.h"
#include "Play_System/Container_Mgr.h"
#include "Network_Common/global_macros.h"

#ifdef GAME_CLIENT
#define ACUPOINT_CONFIG_FILE_PATH "game_data/acupoint_system/acupoint_config.json"
#define VEIN_CONFIG_FILE_PATH "game_data/acupoint_system/vein_config.json"
#else
#define ACUPOINT_CONFIG_FILE_PATH "../config/acupoint_system/acupoint_config.json"
#define VEIN_CONFIG_FILE_PATH "../config/acupoint_system/vein_config.json"
#endif

namespace Game_Data
{
    Acupoint_Config_Mgr* Acupoint_Config_Mgr::instance_ = NULL;
    Acupoint_Config_Mgr::Acupoint_Config_Mgr()
    {

    }

    Acupoint_Config_Mgr::~Acupoint_Config_Mgr()
    {

    }

    Acupoint_Config_Mgr* Acupoint_Config_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Acupoint_Config_Mgr;
        }

        return instance_;
    }

    int Acupoint_Config_Mgr::initialize()
    {
        memset(acupoint_config_array_,0,sizeof(acupoint_config_array_));
        memset(vein_config_array_,0,sizeof(vein_config_array_));

        load_acupoint_config_data();
        load_vein_config_data();

        return 0;
    }

    int Acupoint_Config_Mgr::release()
    {
        for (int i = 0;i < VEIN_COUNT_MAX;++i)
        {
            for (int j = 0;j < ACUPOINT_POS_MAX;++j)
            {
                delete (acupoint_config_array_[i][j]);
            }
        }

        for (int i = 0;i < VEIN_COUNT_MAX;++i)
        {
            delete (vein_config_array_[i]);
        }

        memset(acupoint_config_array_,0,sizeof(acupoint_config_array_));
        memset(vein_config_array_,0,sizeof(vein_config_array_));
        return 0;
    }

    int Acupoint_Config_Mgr::load_acupoint_config_data()
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, ACUPOINT_CONFIG_FILE_PATH);

        acupoint_config* config = NULL;
        char key[255] = {0};
        for (Json::Value::iterator iter = root_value.begin();iter != root_value.end();++iter)
        {
            config = new acupoint_config;
            Json::Value &v = (*iter)["base_id_"];
            if (!v.empty())
            {
                config->base_id_ =  v.asUInt();
            }

            v = (*iter)["type"];
            if (!v.empty())
            {
                config->type_ = v.asUInt();
            }

            v = (*iter)["pos"];
            if (!v.empty())
            {
                config->pos_ = v.asUInt();
            }

            v = (*iter)["pos_x"];
            if (!v.empty())
            {
                config->pos_x_ = v.asUInt();
            }

            v = (*iter)["pos_y"];
            if (!v.empty())
            {
                config->pos_y_ = v.asUInt();
            }

            v = (*iter)["name_x"];
            if (!v.empty())
            {
                config->name_x_ = v.asUInt();
            }

            v = (*iter)["name_y"];
            if (!v.empty())
            {
                config->name_y_ = v.asUInt();
            }

            v = (*iter)["name"];
            if (!v.empty())
            {
                config->name_ = v.asUInt();
            }

            v = (*iter)["attr_type"];
            if (!v.empty())
            {
                config->attr_type_ = v.asUInt();
            }

            for (int i = 0;i < VEIN_LEVEL_MAX;++i)
            {
                memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
                sprintf_s(key,"cur_attr_%d",i);
#else
                sprintf(key,"cur_attr_%d",i);
#endif
                v = (*iter)[key];
                if (!v.empty())
                {
                    config->level_data_[i].cur_attr_ = v.asUInt();
                }

                memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
                sprintf_s(key,"total_attr_%d",i);
#else
                sprintf(key,"total_attr_%d",i);
#endif
                v = (*iter)[key];
                if (!v.empty())
                {
                    config->level_data_[i].total_attr_ = v.asUInt();
                }

                memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
                sprintf_s(key,"prestige_cost_%d",i);
#else
                sprintf(key,"prestige_cost_%d",i);
#endif
                v = (*iter)[key];
                if (!v.empty())
                {
                    config->level_data_[i].prestige_cost_ = v.asUInt();
                }

                memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
                sprintf_s(key,"gold_cost_%d",i);
#else
                sprintf(key,"gold_cost_%d",i);
#endif
                v = (*iter)[key];
                if (!v.empty())
                {
                    config->level_data_[i].gold_cost_ = v.asUInt();
                }

                memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
                sprintf_s(key,"suc_rate_%d",i);
#else
                sprintf(key,"suc_rate_%d",i);
#endif
                v = (*iter)[key];
                if (!v.empty())
                {
                    config->level_data_[i].suc_rate_ = v.asUInt();
                }
            }

            acupoint_config_array_[config->type_][config->pos_] = config;
        }

        return 0;
    }

    int Acupoint_Config_Mgr::load_vein_config_data()
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, VEIN_CONFIG_FILE_PATH);

        vein_config* config = NULL;
        char key[255] = {0};
        for (Json::Value::iterator iter = root_value.begin();iter != root_value.end();++iter)
        {
            config = new vein_config;
            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                config->base_id_ =  v.asUInt();
            }

            v = (*iter)["type"];
            if (!v.empty())
            {
                config->type_ = v.asUInt();
            }

            v = (*iter)["name"];
            if (!v.empty())
            {
                config->name_ = v.asUInt();
            }

            for (int i = 0;i < VEIN_LEVEL_MAX;++i)
            {
                memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
                sprintf_s(key,"open_level_%d",i);
#else
                sprintf(key,"open_level_%d",i);
#endif
                v = (*iter)[key];
                if (!v.empty())
                {
                    config->level_data_[i].open_level_ = v.asUInt();
                }

                memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
                sprintf_s(key,"attr_type_%d",i);
#else
                sprintf(key,"attr_type_%d",i);
#endif
                v = (*iter)[key];
                if (!v.empty())
                {
                    config->level_data_[i].attr_type_ = v.asUInt();
                }

                memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
                sprintf_s(key,"attr_%d",i);
#else
                sprintf(key,"attr_%d",i);
#endif
                v = (*iter)[key];
                if (!v.empty())
                {
                    config->level_data_[i].attr_ = v.asUInt();
                }
            }

            vein_config_array_[config->type_] = config;
        }

        return 0;
    }

    acupoint_config* Acupoint_Config_Mgr::get_acupoint_config(int vein_type,int acupoint_pos)
    {
        return acupoint_config_array_[vein_type%VEIN_COUNT_MAX][acupoint_pos%ACUPOINT_POS_MAX];
    }

    vein_config* Acupoint_Config_Mgr::get_vein_config(int vein_type)
    {
        return vein_config_array_[vein_type%VEIN_COUNT_MAX];
    }

    int Acupoint_Config_Mgr::get_acupoint_attr(int vein_type,int acupoint_pos,int vein_level)
    {
        int attr = 0;
        acupoint_config* config = get_acupoint_config(vein_type,acupoint_pos);
        if (config)
        {
            attr = config->level_data_[vein_level].total_attr_;
        }

        return attr;
    }

    int Acupoint_Config_Mgr::get_vein_attr(int vein_type,int acupoint_pos,int vein_level)
    {
        int attr = 0;
        vein_config* config = get_vein_config(vein_type);
        if (config)
        {
            if (acupoint_pos == (ACUPOINT_POS_MAX-1))
            {
                vein_level += 1;
            }

            for (int i = 0;i < vein_level;++i)
            {
                attr += config->level_data_[i].attr_;
            }
        }

        return attr;
    }
}

