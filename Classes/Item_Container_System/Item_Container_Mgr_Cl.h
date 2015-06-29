
#ifndef __ITEM_CONTAINER_MGR_H__
#define __ITEM_CONTAINER_MGR_H__

#include "Item_Container_System/Item_Container_Data.h"

class message_stream;
namespace Game_Data
{
    class Player;
    class Item_Container_Mgr
    {
    public:
        Item_Container_Mgr();
        virtual ~Item_Container_Mgr();

        static Item_Container_Mgr* instance();

        void release();

    public:
        void load_item_container(Player* player,message_stream& ms);
        void update_item_container(Player* player,message_stream& ms);
        void create_item_container(Player* player,message_stream& ms);
        void tidy_item_container(Player* player,message_stream& ms);

        bool is_load(){return m_is_load;}
        void insert_item_container(Item_Container* container);
        void remove_item_container(int id);
        Item_Container* get_item_container(uint64 id);
        Item_Container_Map* get_item_container_map(){return &m_map_item_container;}

    private:
        static Item_Container_Mgr*      instance_;

        bool                            m_is_load;
        Item_Container_Map              m_map_item_container;
    };
}

typedef Game_Data::Item_Container_Mgr ITEM_CONTAINER_MGR;


#endif /* __ITEM_CONTAINER_MGR_H__ */
