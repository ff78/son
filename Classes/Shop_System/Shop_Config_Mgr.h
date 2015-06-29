

#ifndef __SHOP_CONFIG_MGR_H__
#define __SHOP_CONFIG_MGR_H__

#include "Game_Interface/common.h"
#include "Shop_Config_Data.h"

namespace Game_Data
{
    class Shop_Config_Mgr
    {
    public:
        Shop_Config_Mgr();
        virtual ~Shop_Config_Mgr();

        static Shop_Config_Mgr* instance();

        int initialize();
        int release();

        shop_config* get_shop_config(int goods_id);
        shop_config_map& get_shop_config_map_by_shop_type(int shop_type);

    private:
        int load_shop_config();

    private:
        static Shop_Config_Mgr*         instance_;

        shop_config_map                 shop_config_map_;
        shop_config_map                 gold_shop_config_map_;
        shop_config_map                 token_shop_config_map_;
        shop_config_map                 special_shop_config_map_;
    };
}


typedef Game_Data::Shop_Config_Mgr SHOP_CONFIG_MGR;


#endif /* __SHOP_CONFIG_MGR_H__ */
