
#ifndef __ITEM_MGR_H__
#define __ITEM_MGR_H__

#include "Item_Data.h"
#include "Item_Container_System/Item_Container_Data.h"

class message_stream;
namespace Game_Data
{
    class Player;
    class Item_Mgr
    {
    public:
        Item_Mgr();
        virtual ~Item_Mgr();

        static Item_Mgr* instance();

        void release();

    public:
        void load_item(Player* player,message_stream& ms);
        void load_material_fragment(Player* player,message_stream& ms);
        void load_book_fragment(Player* player,message_stream& ms);
        void equip_equipment(Player* player,message_stream& ms);
        void take_off_equipmen(Player* player,message_stream& ms);
        void equip_book(Player* player,message_stream& ms);
        void take_off_book(Player* player,message_stream& ms);
        void equipment_level_up(Player* player,message_stream& ms);
        void equipment_quality_up(Player* player,message_stream& ms);
        void book_level_up(Player* player,message_stream& ms);
        void book_quality_up(Player* player,message_stream& ms);
        void sell_item(Player* player,message_stream& ms);
        void use_item(Player* player,message_stream& ms);
        void compound_material_fragment(Player* player,message_stream& ms);
        void compound_book_fragment(Player* player,message_stream& ms);
        void set_on_gem(Player* player,message_stream& ms);
        void set_off_gem(Player* player,message_stream& ms);

        void create_item(Player* player,message_stream& ms);
        void create_material_fragment(Player* player,message_stream& ms);
        void create_book_fragment(Player* player,message_stream& ms);
        void item_client_show(Player* player,message_stream& ms);

        void show_book_level_up(Item* up_item,Item_List* list_item,int& up_level,int& surplus_exp);
        bool check_quality_upgrade_need_material(Player* player,int module_type,int cur_quality);
        void remove_quality_upgrade_need_material(Player* player,int module_type,int cur_quality);
        void pathfinding_quality_upgrade_need_material(int module_type,int cur_quality,int item_base_id);

        bool is_load_item(){return m_is_load_item;}
        void insert_item(Item* item);
        void remove_item(int id);
        Item* get_item(uint64 id);
        Item_Map* get_item_map(){return &m_map_item;}

        bool is_load_material_fragment(){return m_is_load_material_fragment;}
        bool is_load_book_fragment(){return m_is_load_book_fragment;}
        void insert_material_fragment(Item* item);
        void remove_material_fragment(int base_id);
        void insert_book_fragment(Item* item);
        void remove_book_fragment(int base_id);
        Item* get_material_fragment(int base_id);
        Item* get_book_fragment(int base_id);
        int get_all_material_fragment(Item_List& list);
        int get_all_book_fragment(Item_List& list);

        bool is_need_tidy_item(Player* player);
        Item_Config* get_item_config_from_container(Item_Container* container);

        int get_can_set_gem_pos(Item* item);

        int get_equipment_attr(Item* item,int attr_type);
        int get_equipment_gem_attr(Item* item,int attr_type);

    private:
        bool check_pile_item(Item_Container_Map& bag_item_map);
        bool check_sort_item(Item_Container_Map& bag_item_map);
        bool is_change(Item_Container* container_1,Item_Container* container_2);

    private:
        static Item_Mgr*    instance_;

        bool                m_is_load_item;
        bool                m_is_load_material_fragment;
        bool                m_is_load_book_fragment;
        Item_Map            m_map_item;
        Item_Map            m_map_material_fragment;
        Item_Map            m_map_book_fragment;
    };
}

typedef Game_Data::Item_Mgr ITEM_MGR;


#endif /* __ITEM_MGR_H__ */
