

#ifndef __ITEM_DATA_H__
#define __ITEM_DATA_H__

#include <list>
#include <map>
#include "Game_Interface/common.h"

#ifdef YN_LINUX
#include <string.h>
#endif

#include "Item_Config_Data.h"
#include "Item_Config_Mgr.h"

namespace Game_Data
{
    struct Item
    {
        uint64                  id;                         // ID
        uint64                  container_id;               // 所在容器ID
        int                     character_id;               // 角色ID
        int                     general_id;                 // 佩戴主角或副将的ID
        Item_Config*            config;                     // 基本信息
        int                     is_bind;                    // 是否绑定
        int                     bar_pos;                    // 所在佩戴栏位置
        int                     level;                      // 当前等级
        int                     exp;                        // 当前经验
        int                     current_quality;            // 当前品质（0：白，1：红，2：黑，3：灰，4：黄，5：绿，6：蓝，7：紫，8：橙）
        int                     count;                      // 个数
        int				        get_time_point;             // 获得时间点
        int				        use_time_point;             // 使用时间点
        int                     create_way;                 // 生成方式
        int                     destroy_way;                // 摧毁方式
        int                     gem_id[SET_GEM_COUNT];      // 镶嵌的宝石
    };

    typedef map<uint64, Item*>          Item_Map;
    typedef Item_Map::iterator		    Item_Map_Iter;

    typedef list<Item*>                 Item_List;
    typedef Item_List::iterator		    Item_List_Iter;

    typedef vector<Item*>               Item_Vector;
    typedef Item_Vector::iterator		Item_Vector_Iter;
}

#endif /* __ITEM_DATA_H__ */

