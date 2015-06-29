
#ifndef __SHOP_MSG_PROC_H__
#define __SHOP_MSG_PROC_H__

#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"

namespace Game_Logic
{
    struct Game_Interface;
}

class Shop_Msg_Proc
{

public:
    Shop_Msg_Proc();
    virtual ~Shop_Msg_Proc();
    static Shop_Msg_Proc* instance();

public:
    static bool send_load_shoping_record(Game_Logic::Game_Interface& gm_interface);
    static bool send_buy_item(Game_Logic::Game_Interface& gm_interface);

	static bool on_load_shoping_record(Game_Logic::Game_Interface& gm_interface);
    static bool on_buy_item(Game_Logic::Game_Interface& gm_interface);

private:
    static Shop_Msg_Proc* instance_;
};
#endif // __SHOP_MSG_PROC_H__

