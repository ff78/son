// -*- C++ -*-

#ifndef MSG_PROC_H_
#define MSG_PROC_H_

#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"

class message_stream;

namespace Game_Logic
{
	struct Game_Interface;
}

class Msg_Proc
{
public:
    Msg_Proc();
    ~Msg_Proc();
    static Msg_Proc* instance();

    int init( void );

    
	static bool process_message(Game_Logic::Game_Interface& gm_interface);

    int process_network_message(message_stream& msg);

    bool reg_interface( int cmd, Game_Logic::game_interface_handler_t handle);
    bool exec_interface( int cmd, const vector<uint64>& para, const char* key_word, int size, int& read_size );

private:

    int do_process_message(char* buff, int size);

    static Msg_Proc* instance_;

    Game_Logic::game_interface_handler_uint_map_t msg_hanler_;

};

#endif // GATE_SVC_H_

