

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
        uint64                  container_id;               // ��������ID
        int                     character_id;               // ��ɫID
        int                     general_id;                 // ������ǻ򸱽���ID
        Item_Config*            config;                     // ������Ϣ
        int                     is_bind;                    // �Ƿ��
        int                     bar_pos;                    // ���������λ��
        int                     level;                      // ��ǰ�ȼ�
        int                     exp;                        // ��ǰ����
        int                     current_quality;            // ��ǰƷ�ʣ�0���ף�1���죬2���ڣ�3���ң�4���ƣ�5���̣�6������7���ϣ�8���ȣ�
        int                     count;                      // ����
        int				        get_time_point;             // ���ʱ���
        int				        use_time_point;             // ʹ��ʱ���
        int                     create_way;                 // ���ɷ�ʽ
        int                     destroy_way;                // �ݻٷ�ʽ
        int                     gem_id[SET_GEM_COUNT];      // ��Ƕ�ı�ʯ
    };

    typedef map<uint64, Item*>          Item_Map;
    typedef Item_Map::iterator		    Item_Map_Iter;

    typedef list<Item*>                 Item_List;
    typedef Item_List::iterator		    Item_List_Iter;

    typedef vector<Item*>               Item_Vector;
    typedef Item_Vector::iterator		Item_Vector_Iter;
}

#endif /* __ITEM_DATA_H__ */

