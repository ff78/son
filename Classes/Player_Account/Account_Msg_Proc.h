
#if !defined(EA_B1091879_26ED_4f75_A9D2_7C09691FAB06__INCLUDED_)
#define EA_B1091879_26ED_4f75_A9D2_7C09691FAB06__INCLUDED_

#include "Game_Interface/common.h"
#include <string>
using namespace std;
namespace Game_Logic
{
    struct Game_Interface;
}
class Account_Msg_Proc
{

public:
	Account_Msg_Proc();
	virtual ~Account_Msg_Proc();

    static Account_Msg_Proc* instance();

	
    static bool send_player_login(Game_Logic::Game_Interface& gm_interface);
    static bool send_player_start_game(Game_Logic::Game_Interface& gm_interface);
    static bool send_keep_alive(Game_Logic::Game_Interface& gm_interface);
	static bool send_create_role( Game_Logic::Game_Interface& gm_interface );

    static bool on_player_login(Game_Logic::Game_Interface& gm_interface);
	static void send_info_to_sdk(int server_id,string rolename);
    static bool on_player_create_role(Game_Logic::Game_Interface& gm_interface);
    static bool on_player_start_game(Game_Logic::Game_Interface& gm_interface);
    static bool on_player_enter_scene(Game_Logic::Game_Interface& gm_interface);
    static bool on_player_error_msg(Game_Logic::Game_Interface& gm_interface);
    
    static bool on_save_player(Game_Logic::Game_Interface& gm_interface);

#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	static bool send_player_login();
	static void save_android_property(std::string localtokenId,std::string localdevicename,std::string localdeviceversion,std::string localclientversion,int iapn,std::string localimei,std::string loaclmacaddress);
    static std::string tokenid;
	static std::string devname;
	static std::string devversion;
	static std::string clientversion;
	static int apn;
	static std::string imei;
	static std::string macaddress;
#endif



	static std::string nn_uid;
	static std::string channel_id;
	static int create_time;
	static std::string server_id_save;
	static std::string server_name_save;

private:
    int login_to_engine( int role_id, const char* key );
    static Account_Msg_Proc* instance_;

};
#endif // !defined(EA_B1091879_26ED_4f75_A9D2_7C09691FAB06__INCLUDED_)
