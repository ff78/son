
#ifndef __LOGIN_REWARD_H__
#define __LOGIN_REWARD_H__

#include <map>

#include "Network_Common/global_macros.h"

#ifdef YN_LINUX
#include <string.h>
#endif

using namespace std;
namespace Game_Data
{
    typedef map<int,int>                    Award_Item_Map;
    typedef Award_Item_Map::iterator	    Award_Item_Map_Iter;

    struct Instance_Sweep_Data
    {
        Instance_Sweep_Data()
        {
            reset();
        }

        ~Instance_Sweep_Data()
        {
            reset();
        }

        void reset()
        {
            flag_ = 0;
            award_exp_ = 0;                       
            award_gold_ = 0;
            award_item_map_.clear();
        }

        void set_award_item(int item_id,int item_count){award_item_map_.insert(make_pair(item_id, item_count));}
        Award_Item_Map& get_award_item_map(){return award_item_map_;}

        int                     flag_;
        int                     award_exp_;
        int                     award_gold_;
        Award_Item_Map          award_item_map_;
    };
}

#endif /* __LOGIN_REWARD_H__ */

