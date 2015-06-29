
#ifndef __ITEM_CONTAINER_MSG_PROC_H__
#define __ITEM_CONTAINER_MSG_PROC_H__

#include "Game_Interface/common.h"

namespace Game_Logic
{
    struct Game_Interface;
}

class Item_Container_Msg_Proc
{

public:
	Item_Container_Msg_Proc();
	virtual ~Item_Container_Msg_Proc();

    static Item_Container_Msg_Proc* instance();

public:
    static bool send_load_item_container(Game_Logic::Game_Interface& gm_interface);
    static bool send_add_item_container(Game_Logic::Game_Interface& gm_interface);

    static bool on_load_item_container(Game_Logic::Game_Interface& gm_interface);
    static bool on_add_item_container(Game_Logic::Game_Interface& gm_interface);
    static bool on_update_item_container(Game_Logic::Game_Interface& gm_interface);

    bool add_item_container(int bag_type);
    
private:
    static Item_Container_Msg_Proc* instance_;

};
#endif // __ITEM_CONTAINER_MSG_PROC_H__
