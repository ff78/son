
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
    // ����״̬
    enum Item_Container_Type
    {
        ICT_STORE = 0,                      // �ֿ�
        ICT_BAG,                            // ����
    };

    struct Item_Container
    {
        uint64                  id;                         // ID
        int                     character_id;               // ��ɫID
        int                     type;                       // ���ͣ�0���ֿ⣬1��������2���ķ��鼮����3��װ���������4���ķ��鼮�������
        int                     index;                      // �±� ���ڱ�����ֿ��λ�ã�
        int                     is_num_type;                // �Ƿ��Ǽ����͵���(�Ƿ���Ե���)(0:���ɵ���, ��0�����Ե���)
        uint64                  item_id;                    // ����ID�������͵��߼�¼item_base_id���Ǽ����͵��߼�¼item_id��
        int                     item_count;                 // ���߸���
        int                     destroy;                    // �ݻ�״̬��0Ϊ������1Ϊ�ݻ٣�
    };

    typedef map<uint64, Item_Container*>            Item_Container_Map;
    typedef Item_Container_Map::iterator            Item_Container_Map_Iter;

    typedef list<Item_Container*>                   Item_Container_List;
    typedef Item_Container_List::iterator           Item_Container_List_Iter;

    typedef vector<Item_Container*>                 Item_Container_Vector;
    typedef Item_Container_Vector::iterator         Item_Container_Vector_Iter;
}

#endif /* __ITEM_CONTAINER_DATA_H__ */

