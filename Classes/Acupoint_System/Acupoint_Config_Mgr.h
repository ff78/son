
#ifndef __ACUPOINT_CONFIG_MGR_H__
#define __ACUPOINT_CONFIG_MGR_H__

#include "Acupoint_Config_Data.h"

namespace Game_Data
{
    class Acupoint_Config_Mgr
    {
    public:
        Acupoint_Config_Mgr();
        virtual ~Acupoint_Config_Mgr();

        static Acupoint_Config_Mgr* instance();

        int initialize();
        int release();

        acupoint_config* get_acupoint_config(int vein_type,int acupoint_pos);
        vein_config* get_vein_config(int vein_type);

        int get_acupoint_attr(int vein_type,int acupoint_pos,int vein_level);
        int get_vein_attr(int vein_type,int acupoint_pos,int vein_level);

    private:
        int load_acupoint_config_data();
        int load_vein_config_data();

    private:
        static Acupoint_Config_Mgr*             instance_;

        acupoint_config*                        acupoint_config_array_[VEIN_COUNT_MAX][ACUPOINT_POS_MAX];
        vein_config*                            vein_config_array_[VEIN_COUNT_MAX];
    };
}


typedef Game_Data::Acupoint_Config_Mgr ACUPOINT_CONFIG_MGR;


#endif /* __ACUPOINT_CONFIG_MGR_H__ */
