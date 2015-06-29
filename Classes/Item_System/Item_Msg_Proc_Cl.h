
#ifndef __ITEM_MSG_PROC_H__
#define __ITEM_MSG_PROC_H__

#include "Game_Interface/common.h"

namespace Game_Logic
{
    struct Game_Interface;
}

class Item_Msg_Proc
{

public:
	Item_Msg_Proc();
	virtual ~Item_Msg_Proc();

    static Item_Msg_Proc* instance();

public:
    static bool send_load_item(Game_Logic::Game_Interface& gm_interface);
    static bool send_load_material_fragment(Game_Logic::Game_Interface& gm_interface);
    static bool send_load_book_fragment(Game_Logic::Game_Interface& gm_interface);
    static bool send_tidy_item(Game_Logic::Game_Interface& gm_interface);
    static bool send_equip_equipment(Game_Logic::Game_Interface& gm_interface);
    static bool send_take_off_equipmen(Game_Logic::Game_Interface& gm_interface);
    static bool send_equip_book(Game_Logic::Game_Interface& gm_interface);
    static bool send_take_off_book(Game_Logic::Game_Interface& gm_interface);
    static bool send_equipment_level_up(Game_Logic::Game_Interface& gm_interface);
    static bool send_equipment_quality_up(Game_Logic::Game_Interface& gm_interface);
    static bool send_book_level_up(Game_Logic::Game_Interface& gm_interface);
    static bool send_book_quality_up(Game_Logic::Game_Interface& gm_interface);
    static bool send_sell_item(Game_Logic::Game_Interface& gm_interface);
    static bool send_use_item(Game_Logic::Game_Interface& gm_interface);
    static bool send_compound_material_fragment(Game_Logic::Game_Interface& gm_interface);
    static bool send_compound_book_fragment(Game_Logic::Game_Interface& gm_interface);
    static bool send_set_on_gem(Game_Logic::Game_Interface& gm_interface);
    static bool send_set_off_gem(Game_Logic::Game_Interface& gm_interface);
    static bool send_gem_level_up(Game_Logic::Game_Interface& gm_interface);

    static bool on_load_item(Game_Logic::Game_Interface& gm_interface);
    static bool on_load_material_fragment(Game_Logic::Game_Interface& gm_interface);
    static bool on_load_book_fragment(Game_Logic::Game_Interface& gm_interface);
    static bool on_tidy_item(Game_Logic::Game_Interface& gm_interface);
    static bool on_equip_equipment(Game_Logic::Game_Interface& gm_interface);
    static bool on_take_off_equipmen(Game_Logic::Game_Interface& gm_interface);
    static bool on_equip_book(Game_Logic::Game_Interface& gm_interface);
    static bool on_take_off_book(Game_Logic::Game_Interface& gm_interface);
    static bool on_equipment_level_up(Game_Logic::Game_Interface& gm_interface);
    static bool on_equipment_quality_up(Game_Logic::Game_Interface& gm_interface);
    static bool on_book_level_up(Game_Logic::Game_Interface& gm_interface);
    static bool on_book_quality_up(Game_Logic::Game_Interface& gm_interface);
    static bool on_sell_item(Game_Logic::Game_Interface& gm_interface);
    static bool on_use_item(Game_Logic::Game_Interface& gm_interface);
    static bool on_compound_material_fragment(Game_Logic::Game_Interface& gm_interface);
    static bool on_compound_book_fragment(Game_Logic::Game_Interface& gm_interface);
    static bool on_set_on_gem(Game_Logic::Game_Interface& gm_interface);
    static bool on_set_off_gem(Game_Logic::Game_Interface& gm_interface);
    static bool on_gem_level_up(Game_Logic::Game_Interface& gm_interface);

    static bool on_create_item(Game_Logic::Game_Interface& gm_interface);
    static bool on_create_material_fragment(Game_Logic::Game_Interface& gm_interface);
    static bool on_create_book_fragment(Game_Logic::Game_Interface& gm_interface);
    static bool on_item_client_show(Game_Logic::Game_Interface& gm_interface);
    
private:
    static Item_Msg_Proc* instance_;

};
#endif // __ITEM_MSG_PROC_H__
