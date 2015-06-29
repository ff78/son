
#ifndef __PLAYER_MSG_PROC_H__
#define __PLAYER_MSG_PROC_H__

enum GMCType
{
    CMDT_PARAM_7_ERROR		= -8,	
    CMDT_PARAM_6_ERROR		= -7,	
    CMDT_PARAM_5_ERROR		= -6,	
    CMDT_PARAM_4_ERROR		= -5,	
    CMDT_PARAM_3_ERROR		= -4,	
    CMDT_PARAM_2_ERROR		= -3,	
    CMDT_PARAM_1_ERROR		= -2,	
    CMDT_PARAM_0_ERROR		= -1,	
    CMDT_NONE				= 0,	

    CMDT_CHANGE_TOKEN,
    CMDT_CHANGE_ENERGY,
    CMDT_CHANGE_GOLD,
    CMDT_CHANGE_PRESTIGE,
    CMDT_CHANGE_EXP,				
    CMDT_CHANGE_LEVEL,				
    CMDT_ADD_ITEM,
    CMDT_SHOW_ALL_STAGE,
    CMDT_ADD_GENERAL,
    CMDT_SHOW_FPS,
    CMDT_SHOW_PLAYER,
    CMDT_OPEN_ALL_FUNCTION,
};

struct GMCResult
{
    void reset()
    {
        type = 0;
        memset(data1,0,sizeof(data1));
    }

    std::string     result;
    int		        type;
    int		        data1[4];
    std::string     data2[4];
};

namespace Game_Logic
{
    struct Game_Interface;
}
class Player_Msg_Proc
{

public:
	Player_Msg_Proc();
	virtual ~Player_Msg_Proc();

    static Player_Msg_Proc* instance();

    static bool send_get_main_city_player(Game_Logic::Game_Interface& gm_interface);
    static bool send_player_move(Game_Logic::Game_Interface& gm_interface);
	static bool send_get_player_info(Game_Logic::Game_Interface& gm_interface);
    static bool send_chat_msg(Game_Logic::Game_Interface& gm_interface);
    static bool send_player_revive(Game_Logic::Game_Interface& gm_interface);
    static bool send_player_buy_energy(Game_Logic::Game_Interface& gm_interface);
	static bool send_player_instance_collided_something(Game_Logic::Game_Interface& gm_interface);
	static bool send_player_useitem_something(Game_Logic::Game_Interface& gm_interface);
    static bool send_player_quality_up(Game_Logic::Game_Interface& gm_interface);

    static bool on_get_main_city_player(Game_Logic::Game_Interface& gm_interface);
    static bool on_player_move(Game_Logic::Game_Interface& gm_interface);
	static bool on_get_player_info(Game_Logic::Game_Interface& gm_interface);
    static bool on_player_chat(Game_Logic::Game_Interface& gm_interface);
    static bool on_gm_command(Game_Logic::Game_Interface& gm_interface);
	static bool on_player_revivie(Game_Logic::Game_Interface& gm_interface);
    static bool on_player_buy_energy(Game_Logic::Game_Interface& gm_interface);
    static bool on_player_quality_up(Game_Logic::Game_Interface& gm_interface);

    static bool on_player_into_main_city(Game_Logic::Game_Interface& gm_interface);
    static bool on_player_quit_main_city(Game_Logic::Game_Interface& gm_interface);
    static bool on_change_token(Game_Logic::Game_Interface& gm_interface);
    static bool on_add_recharge_token(Game_Logic::Game_Interface& gm_interface);
    static bool on_change_energy(Game_Logic::Game_Interface& gm_interface);
    static bool on_change_prestige(Game_Logic::Game_Interface& gm_interface);
    static bool on_change_gold(Game_Logic::Game_Interface& gm_interface);
    static bool on_change_exp(Game_Logic::Game_Interface& gm_interface);
	/*************************************** dely *******************************************/
	static bool send_chat_msg(int channel, const char* receiver_name, const char* chat);


	static bool send_chat_all_msg(int channel, const char* receiver_name, const char* chat);     //区域
	static bool send_chat_private_msg(int channel, const char* receiver_name, const char* chat); //私密
	static bool send_chat_team_msg(int channel, const char* receiver_name, const char* chat);    //组队
	static bool send_chat_friend_msg(int channel, const char* receiver_name, const char* chat);  //好友
	static bool send_chat_faction_msg(int channel, const char* receiver_name, const char* chat); //工会
	static bool send_chat_world_msg(int channel, const char* receiver_name, const char* chat);   //世界

	static bool receive_chat_all_msg(Game_Logic::Game_Interface& gm_interface);                  //区域
	static bool receive_chat_private_msg(Game_Logic::Game_Interface& gm_interface);              //私密
	static bool receive_chat_team_msg(Game_Logic::Game_Interface& gm_interface);                 //组队
	static bool receive_chat_friend_msg(Game_Logic::Game_Interface& gm_interface);               //好友
	static bool receive_chat_faction_msg(Game_Logic::Game_Interface& gm_interface);              //工会
	static bool receive_chat_world_msg(Game_Logic::Game_Interface& gm_interface);                //世界
	/*************************************** dely *******************************************/

private:
    static void operate_gm_command_reasult(int cmd_type,GMCResult& result,std::string& op_result);
    
    static Player_Msg_Proc* instance_;

};
#endif // __PLAYER_MSG_PROC_H__
