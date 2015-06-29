
#ifndef __ITEM_CONTAINER_DATA_H__
#define __ITEM_CONTAINER_DATA_H__

#define ADD_ITEM_CONTAINER_COST                     10

#include "Game_Interface/common.h"

#include <list>
#include <map>
#include <vector>

#ifdef YN_LINUX
#include <string.h>
#endif

using namespace std;
namespace Game_Data
{
    // 道具状态
    enum Item_Container_Type
    {
        ICT_STORE = 0,                      // 仓库
        ICT_BAG,                            // 背包
    };

    struct Item_Container
    {
        uint64                  id;                         // ID
        int                     character_id;               // 角色ID
        int                     type;                       // 类型（0：仓库，1：背包，2：心法书籍包，3：装备佩戴栏，4：心法书籍佩戴栏）
        int                     index;                      // 下标 （在背包或仓库的位置）
        int                     is_num_type;                // 是否是计数型道具(是否可以叠加)(0:不可叠加, 非0都可以叠加)
        uint64                  item_id;                    // 道具ID（计数型道具记录item_base_id，非计数型道具记录item_id）
        int                     item_count;                 // 道具个数
        int                     destroy;                    // 摧毁状态（0为正常，1为摧毁）
    };

    typedef map<uint64, Item_Container*>            Item_Container_Map;
    typedef Item_Container_Map::iterator            Item_Container_Map_Iter;

    typedef list<Item_Container*>                   Item_Container_List;
    typedef Item_Container_List::iterator           Item_Container_List_Iter;

    typedef vector<Item_Container*>                 Item_Container_Vector;
    typedef Item_Container_Vector::iterator         Item_Container_Vector_Iter;
}

#endif /* __ITEM_CONTAINER_DATA_H__ */

