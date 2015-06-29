

#ifndef __SHOP_CONFIG_DATA_H__
#define __SHOP_CONFIG_DATA_H__


#include <string>
#include <map>

using namespace std;
namespace Game_Data
{
    enum Shop_Type
    {
        ST_GOLD_SHOP = 1,             // 银两商店
        ST_TOKEN_SHOP,               // 元宝商店
        ST_SPECIAL_SHOP,             // 特价商店
    };

    enum Money_Type
    {
        MT_GOLD_MONEY = 1,
        MT_TOKEN_MONEY,
    };

    struct shop_config
    {
        shop_config()
        {
            reset();
        }

        ~shop_config()
        {
            reset();
        }

        void reset()
        {
            base_id_ = 0;
            type_ = 0;
            item_base_id_ = 0;
            money_type_ = 0;
            cost_ = 0;
            discount_ = 0;
            buy_count_ = 0;
        }

        int                     base_id_;           // 
        int                     type_;              //
        int                     item_base_id_;      //
        int                     money_type_;        //
        int                     cost_;              //
        int                     discount_;          // 
        int                     buy_count_;         //
    };

    typedef map<int,shop_config*>                   shop_config_map;
    typedef shop_config_map::iterator	            shop_config_map_iter;
}

#endif /* __SHOP_CONFIG_DATA_H__ */

