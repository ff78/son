

#ifndef __ITEM_CONFIG_MGR_H__
#define __ITEM_CONFIG_MGR_H__

#include "Game_Interface/common.h"
#include "Item_Config_Data.h"

namespace Game_Data
{
    class Item_Config_Mgr
    {
    public:
        Item_Config_Mgr();
        virtual ~Item_Config_Mgr();

        static Item_Config_Mgr* instance();

        int initialize(void);
        int release(void);

        Item_Config* get_item_config(int base_id);
        Equipment_Depot_Config* get_equipment_depot_config(int base_id);
        Item_Fragment_Config* get_item_fragment_config(int base_id);
        Equipment_Config* get_equipment_config(int base_id);
        Usable_Item_Config* get_usable_item_config(int base_id);
        Book_Config* get_book_config(int base_id);
        Gem_Config* get_gem_config(int base_id);

        quality_upgrade_config* get_quality_upgrade_config(int module_type,int cur_quality);
        void get_quality_upgrade_need_material(int module_type,int cur_quality,game_element_list_t& material);

        int get_item_type_by_base_id(int base_id);

        int get_book_max_level(int base_id,int quality);

        int get_equipment_level_up_cost(int base_id,int level);
        int get_book_level_up_need_exp(int base_id,int level,int quality);

        int get_equipment_offer_money(int base_id,int level);
        int get_book_offer_exp(int base_id,int level,int quality);

        int get_equipment_attr(int base_id,int level,int quality,int attr_type);
        int get_book_attr(int base_id,int level,int quality,int attr_type);

        int get_item_sell_income(int base_id,int level,int count);

        const char* get_icon_path(int icon_id);
        const char* get_lock_grid();
        const char* get_gem_pos_not_open_icon();
        const char* get_gold_icon();
        const char* get_token_icon();

        void get_item_use_level(int base_id,int& level_down,int& level_up);
        int get_gift_type(int base_id);
        int load_icon_config_data();
    private:
        int load_equipment_depot_config_data();
        int load_equipment_config_data();
        int load_usable_item_config_data();
        int load_quest_item_config_data();
        int load_material_item_config_data();
        int load_material_fragment_config_data();
        int load_book_fragment_config_data();
        int load_gift_item_config_data();
        int load_book_config_data();
        int load_book_attr_config_data();
        int load_gem_config_data();
        
        int load_quality_upgrade_config_data();

        void proc_string(const string& content_str, item_content &ic);

    private:
        static Item_Config_Mgr*         instance_;

        Item_Config_Map                 m_map_item_config;
        Equipment_Depot_Config_Map      m_map_equipment_depot_config;
        Item_Fragment_Config_Map        m_map_item_fragment_config;
        Equipment_Config_Map            m_map_equipment_config;
        Usable_Item_Config_Map          m_map_usable_item_config;
        Book_Config_Map                 m_map_book_config;
        Gem_Config_Map                  m_map_gem_config;
        Icon_Map						m_map_icon;
        quality_upgrade_config*         quality_upgrade_config_array_[QMT_MAX][QT_MAX-1];
    };
}


typedef Game_Data::Item_Config_Mgr ITEM_CONFIG_MGR;


#endif /* __ITEM_CONFIG_MGR_H__ */
