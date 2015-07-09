#include <string>
#include "Player_Account/Account_Data.h"
#include "Player_Account/Account_Msg_Proc.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Network_Common/message_stream.h"
#include "Network_Common/global_macros.h"
#include "Network_Common/message.h"
#include "Network/msg_manager.h"
#include "Network_Common/NetManager.h"
#include "Game_Interface/Game_Element_Parse.h"
#include "UI_Interface/CocoStu_UI_Scene_Interface.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/event_define.h"
#include "Game_Interface/game_event_mgr.h"
#include "Player_Account/Account_Logic.h"
#include "UI/Main_City_Scene.h"
#include "Profile.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Common/GameDefine.h"
#include "UI_Interface/UI_ModalDialogue_Layer.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player_Logic_Cl.h"
//#include "Runtime.h"
#include "Item_System/Item_Logic_Cl.h"
//#include "Skill_System/Skill/Skill_Logic.h"
#include "RecentlyServer.h"
#include "Shield_Word/ShieldManager.h"

#include "DataModule/BlackCity.h"
#include "ClientLogic/FightDefine.h"
#include "../Faction_System/Faction_Client.h"
#include "../Pet_System/Pet_Client.h"
#include "../God_System/God_Client.h"
#ifdef GAME_CLIENT
#include "cocos2d.h"
#include "Platform_Dependence/Dependence.h"
#endif
using namespace std;
#define ERROR_ROLE_AMOUNT_FULL          -1102
#define ERROR_ROLE_NAME_HAS_EXIST       -1103
#define ERROR_ROLE_NAME_ILLEGAL         -1105


std::string Account_Msg_Proc::server_id_save;
std::string Account_Msg_Proc::server_name_save;
std::string Account_Msg_Proc::nn_uid = "";
std::string Account_Msg_Proc::channel_id = "";
int Account_Msg_Proc::create_time = 0;

Account_Msg_Proc* Account_Msg_Proc::instance_ = 0;

Account_Msg_Proc::Account_Msg_Proc(){

}

Account_Msg_Proc::~Account_Msg_Proc(){

}

Account_Msg_Proc* Account_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Account_Msg_Proc;

    return instance_;
}

bool Account_Msg_Proc::send_player_login(Game_Logic::Game_Interface& gm_interface)
{
	////CCLog("--------windows $$$$$$$$$$Account_Msg_Proc::send_player_login --- to gate");
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
        return false;

    int next_ui_id = (int)para[0];

    Account_Data_Mgr::instance()->set_next_ui_config_id( next_ui_id );

    string login_str = gm_interface.get_keyword();

    vector<string> login_list;
    Game_Data::Game_Element_Parse::instance()->get_content_from_string( login_list, login_str.data(), "|" );
    if( login_list.size() < 2 )
        return false;

    char msg_buf[1024] = {0};
    message_stream body_ms(msg_buf, sizeof(msg_buf));

    std::string account = login_list[0].data();
    std::string key = login_list[1].data();
    std::string timestamp ="8888";
	std::string version		= Account_Data_Mgr::instance()->get_version();
	int os_type     = 4;
    int addicted_st = 0;
    int result  = 0;
    int err_no	= 0;

    Account_Data_Mgr::instance()->set_self_account(account.data());

    body_ms << CLIENT_AUTH_SESSION;
	body_ms << version;
	body_ms << os_type;
    body_ms << account;
    body_ms << key;
    body_ms << timestamp;
    body_ms << addicted_st;

    if( -1 == CNetManager::GetMe()->send_msg( body_ms ) )
    {
        const char* exitInfo = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SERVER_DISCONNECT);
        UI_ModalDialogue_Layer::DoModal("",exitInfo,UI_ModalDialogue_Layer::DT_OK,[]()
        {
            Account_Logic::releaseData();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
            MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
            return;
#endif
            
            Director::getInstance()->end();
            
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
#endif
        }
        );
        return false;
    }
	const char* loadFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MODEL_LOADING_FONT);
    CocoStu_UI_Scene_Interface::get_instance()->lockScreen("载入中","");
	Profile::setStringForKey(PROFILE_KEY_FIRST_USERNAME,account.c_str());
	Profile::setStringForKey(PROFILE_KEY_FIRST_PASSWORD,key.c_str());
	Profile::flush();

    return true;
}

void Account_Msg_Proc::send_info_to_sdk(int server_id,string rolename)
{
	//µ˜”√Java£¨œÚSDk¥´µ›’À∫≈–≈œ¢

}

bool Account_Msg_Proc::on_player_login(Game_Logic::Game_Interface& gm_interface)
{
    CocoStu_UI_Scene_Interface::get_instance()->unlockScreen();
    //CCLog("-------------------->Account_Msg_Proc::on_player_login");
	vector<uint64> para;
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	
	int is_same_version = 0;
	std::string channel_id_str = "";
	std::string game_server_id = "";
	std::string game_server_name;
	body_ms >> is_same_version >> channel_id_str >> game_server_id >> game_server_name;
	Account_Msg_Proc::channel_id = channel_id_str;
	server_name_save=game_server_name;
	server_id_save=game_server_id;
	//CCLog("-------------------------->servername is %s",server_name_save.c_str());
	//CCLog("-------------------------->serverid is %s",server_id_save.c_str());
	
	if (0 == is_same_version)
	{
		std::string note_text = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(VERSION_BOT_SAME);
		UI_ModalDialogue_Layer::DoModal("", note_text.c_str(), UI_ModalDialogue_Layer::DT_OK );
		return false;
	}
	else if (2 == is_same_version)
	{
		std::string note_text = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MAX_PLAYER);;
		UI_ModalDialogue_Layer::DoModal("", note_text.c_str(), UI_ModalDialogue_Layer::DT_OK );
		return false;
	}
	
	//CCLog("-----------------11111111111111111111111111111111111-----------------------");
    int is_online = 0;
    body_ms >> is_online;
    if (is_online == 1)
    {
        std::string note_text = "This account is online!";
        UI_ModalDialogue_Layer::DoModal("", note_text.c_str(), UI_ModalDialogue_Layer::DT_OK );
        return false;
    }

	//CCLog("-----------------2222222222222222222222222222222222222-----------------------");
   Account_Data_Mgr* ptr = Account_Data_Mgr::instance();

   
	
    Account_Data ad;
    ad.reset();
    ad.set_account(Account_Data_Mgr::instance()->get_self_account());
    Account_Data_Mgr::instance()->add_acount(ad);
	
    int role_count = 0;
    body_ms >> role_count;
	Account_Data_Mgr* pADMgr = Account_Data_Mgr::instance();
	role_count = MIN(role_count,MAX_ROLE_COUNT);
	pADMgr->set_role_num(role_count);
	//CCLog("-----------------3333333333333333333333333333333333333333-----------------------");
	if ( role_count <= 0  )
	{
		//CCLog("-----------------44444444444444444444444444444444444444444-----------------------");
//		int next_ui_id = ptr->get_next_ui_config_id();
//		CocoStu_UI_Scene_Interface::get_instance()->run_test(next_ui_id);
//
//		Profile::setBoolForKey("PROFILE_KEY_FIRST_ENTERGAME",false);
//		Profile::flush();

		CocoStu_UI_Scene_Interface::get_instance()->run_test(2005);
		UI::Main_City_Actor_Layer::get_instance()->loadSelectRoleSexList();
		UI::Main_City_Actor_Layer::get_instance()->loadSelectJob();
		
	}
	else
	{
		//CCLog("-----------------555555555555555555555555555555555555555555555555-----------------------");
		//CCLog("---------------------------------num is %d",pADMgr->get_role_num());
       for (int i = 0;i < pADMgr->get_role_num()&&i<1;++i)
       {
		   //CCLog("--------------888888888888888888888888888888888888888888888--------------");
			   body_ms >> pADMgr->m_RoleData[i].m_nRoleID;
			   //CCLog("--------------999999999999999999999999999999999999999999--------------");
			   body_ms >> pADMgr->m_RoleData[i].m_nBaseID;
			   //CCLog("--------------aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa--------------");
			   body_ms >> pADMgr->m_RoleData[i].m_nLevel;
			   //CCLog("--------------bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb--------------");
			   body_ms >> pADMgr->m_RoleData[i].m_nSex;
			    //CCLog("--------------ccccccccccccccccccccccccccccccccccccccccccccc--------------");
			   body_ms >> pADMgr->m_RoleData[i].m_strName;
			   //CCLog("--------------dddddddddddddddddddddddddddddddddddddddddddddddddd%s--------------",pADMgr->m_RoleData[i].m_strName.c_str());
			   //CCLog("--------------7777777777777777777777777777777777777777777777777777777777--------------");
		  
		pADMgr->set_current_select(0);
		vector<uint64> para;
		para.push_back(2001);
		Game_Logic::Game_Content_Interface::instance()->exec_interface("send_player_start_game", para);
		//CCLog("-----------------66666666666666666666666666666666666666666666666666666-----------------------");
		return true;

       }
	   pADMgr->set_current_select(0);
	   UI::Main_City_Actor_Layer::get_instance()->loadRoleList();

    }
	
	//CCLog("---------------end on_player_login------------------");
    return true;

}

bool Account_Msg_Proc::send_player_start_game(Game_Logic::Game_Interface& gm_interface)
{

    //CCLog("-------------------->Account_Msg_Proc::send_player_start_game ---to gate");
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
        return false;

    int next_ui_id = (int)para[0];
    Account_Data_Mgr::instance()->set_next_ui_config_id( next_ui_id );

	Account_Data_Mgr* pADMgr = Account_Data_Mgr::instance();
	
	const Account_Data_Mgr::SRoleData* pData = pADMgr->get_current_select();
	if (!pData)
	{
		const char* szInfo = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SELECT_ROLE_FIRST);
		UI_ModalDialogue_Layer::DoModal("", szInfo, UI_ModalDialogue_Layer::DT_OK);
		return false;
	}

    Account_Data ad;
    if( 0 == Account_Data_Mgr::instance()->get_self_account( ad ))
    {
        Account_Data_Mgr::instance()->set_avatar_id(pData->m_nSex);
		Account_Data_Mgr::instance()->set_current_role_id(pData->m_nRoleID);
        ad.add_role_id( pData->m_nRoleID );
        Account_Data_Mgr::instance()->modi_account_data_by_name(ad.get_account(), ad );

        char body[256] = {0};
        message_stream body_ms(body, sizeof(body));
        body_ms << CLIENT_START_GAME;
        body_ms << pData->m_nRoleID;

        if( -1 == CNetManager::GetMe()->send_msg( body_ms ) )
        {
            const char* exitInfo = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SERVER_DISCONNECT);
            UI_ModalDialogue_Layer::DoModal("",exitInfo,UI_ModalDialogue_Layer::DT_OK,[]()
            {
                //Account_Logic::releaseData();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
                MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
                return;
#endif
                
                Director::getInstance()->end();
                
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                exit(0);
#endif
            }
            );
            return false;
        }

		const char* loadFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MODEL_LOADING_FONT);
        CocoStu_UI_Scene_Interface::get_instance()->lockScreen("载入中","");
        return true;
    }

    return false;
}

bool Account_Msg_Proc::on_player_start_game(Game_Logic::Game_Interface& gm_interface)
{
    //CCLog("-------------------->Account_Msg_Proc::on_player_start_game");
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    std::string ip;
    int port = 0;
	std::string server_id;
    std::string key;
	std::string nn_uid_tmp;
	std::string channel_id_tmp;
	int create_time_tmp;
    body_ms >> ip >> port >> key >> nn_uid_tmp >> channel_id_tmp >> create_time_tmp >> server_id;
	
	Account_Msg_Proc::nn_uid = nn_uid_tmp;
	Account_Msg_Proc::create_time = create_time_tmp;




    CCLOG ("close gate server connection ");
    vector<uint64> para;
    Game_Logic::Game_Content_Interface::instance()->exec_interface("closeserver", para, "gate");


    //CCLog("begin connect to game server %s ",ip.data());
    para.clear();
    para.push_back(port);
    if(!Game_Logic::Game_Content_Interface::instance()->exec_interface("connecttogame", para, ip.data()))
    {
        //to do game server error, return to main menu 2013-09-09
        const char* exitInfo = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SERVER_DISCONNECT);
        UI_ModalDialogue_Layer::DoModal("",exitInfo,UI_ModalDialogue_Layer::DT_OK,[]()
        {
            Account_Logic::releaseData();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
            MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
            return;
#endif
            
            Director::getInstance()->end();
            
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
#endif
        }
        );
        return false;
    }

    CCLOG ("connect to engein success %s ",ip.data());


    instance()->login_to_engine(Account_Data_Mgr::instance()->get_current_role_id(), key.data());

    return true;
}

bool Account_Msg_Proc::on_player_error_msg(Game_Logic::Game_Interface& gm_interface)
{
    ////CCLog("-------------------->Account_Msg_Proc::on_player_start_game");
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = 0;
    int error_code = 0;
    int require_value = 0;
    body_ms >> player_id  >> error_code >> require_value;

    DICTIONARY_CONFIG_MGR::instance()->show_alert(error_code);

    return true;
}

bool Account_Msg_Proc::send_create_role( Game_Logic::Game_Interface& gm_interface )
{
    ////CCLog("-------------------->Account_Msg_Proc::send_create_role ---to gate");
	const char* role_name = gm_interface.get_keyword();
	if (strlen(role_name)<=0)
	{
        const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(INPUT_YOUR_NAME);
		UI_ModalDialogue_Layer::DoModal("",szString,UI_ModalDialogue_Layer::DT_OK);
		return false;
	}

    int sex = 1;
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() >= 1)
    {
        sex = (int)para[0];
    }
	//‘⁄’‚¿ÔºÏ≤‚ «∑Ò∫¨”–∑«∑®◊÷∂Œ
	bool valueRet=ShieldManager::sharedShieldManager()->isNameContainShield(role_name);
	if(valueRet)
	{
		//∞¸∫¨∆¡±Œ◊÷£¨œ‘ æ∂‘ª∞øÚ
		const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(CONTAIN_SHIELD);
		UI_ModalDialogue_Layer::DoModal("",szString,UI_ModalDialogue_Layer::DT_OK);
		return false;
	}

	std::string dev_name_tmp = "win";
	std::string dev_version_tmp = "window7";
	std::string channel_id_tmp = "test";
	int         apn        = 0;
	std::string imei;
	std::string macaddress;
	int job = UI::Main_City_Actor_Layer::get_instance()->getJob();
	//ƒø«∞÷ªø™∑≈3 Œ‰∂∑º“÷∞“µ
	//job = 3;
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	dev_name_tmp = Account_Msg_Proc::devname;
	dev_version_tmp = Account_Msg_Proc::devversion;
	channel_id_tmp = Account_Msg_Proc::channel_id;
	apn        = Account_Msg_Proc::apn;
	imei       = Account_Msg_Proc::imei;
	macaddress = Account_Msg_Proc::macaddress;
#endif

    char body[512] = {0};
	//char* tmp_name = "undertaker";
    message_stream body_ms(body, sizeof(body));
    body_ms << CLIENT_CREATE_ROLE;
	body_ms << role_name;
	//body_ms << tmp_name;
    body_ms << sex;    // sex
    body_ms << (int)1;    // career
    body_ms << (int)1;    // country
	body_ms << channel_id_tmp;
	body_ms << dev_name_tmp;
	body_ms << dev_version_tmp;
	body_ms << apn;
	body_ms << imei;
	body_ms << macaddress;
	body_ms << job;

    CNetManager::GetMe()->send_msg( body_ms );

	const char* loadFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MODEL_LOADING_FONT);
	CocoStu_UI_Scene_Interface::get_instance()->lockScreen("载入中","");

    return 0;
}

bool Account_Msg_Proc::on_player_create_role(Game_Logic::Game_Interface& gm_interface)
{
    CocoStu_UI_Scene_Interface::get_instance()->unlockScreen();
    ////CCLog("-------------------->Account_Msg_Proc::on_player_create_role");
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int result;
    body_ms >> result;

    if( -1 == result )
    {
        int error;
        body_ms >> error;

        CCLOG ("Create Role Error------------------------------:%d ",error);
        const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(CREATE_ROLE_FAILED);
        switch (error)
        {
        case ERROR_ROLE_AMOUNT_FULL:
            szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ROLE_AMOUNT_FULL);
            break;

        case ERROR_ROLE_NAME_ILLEGAL:
            szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(NAME_INPUT_TYPE_TIPS);
            break;

        case ERROR_ROLE_NAME_HAS_EXIST:
            szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(NAME_ALREADY_EXIST);
            break;

        default:
            szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(CREATE_ROLE_FAILED);
            break;
        }

        UI_ModalDialogue_Layer::DoModal("",szString,UI_ModalDialogue_Layer::DT_OK);
        return false;
    }
	else
	{
	    int role_id = 0;
		int role_base_id = 0;
		int role_level = 0;
        int role_sex = 0;
		std::string role_name;
		body_ms >> role_id;
		body_ms >> role_base_id;
		body_ms >> role_level;
        body_ms >> role_sex;
		body_ms >> role_name;

		Account_Data_Mgr* pADMgr = Account_Data_Mgr::instance();
		int role_count = pADMgr->get_role_num();

		if (role_count>=MAX_ROLE_COUNT)
		{
			return false;
		}
		pADMgr->set_current_select(role_count);
		pADMgr->m_RoleData[role_count].m_nRoleID = role_id;
		pADMgr->m_RoleData[role_count].m_nBaseID = role_base_id;
		pADMgr->m_RoleData[role_count].m_nLevel = role_level;
        pADMgr->m_RoleData[role_count].m_nSex = role_sex;
		pADMgr->m_RoleData[role_count].m_strName = role_name;
		pADMgr->set_role_num(role_count+1);

		//CocoStu_UI_Scene_Interface::get_instance()->run_test(2006);
		//UI::Main_City_Actor_Layer::get_instance()->loadRoleList();

		
		pADMgr->set_current_select(0);
		vector<uint64> para;
		para.push_back(2001);
		Game_Logic::Game_Content_Interface::instance()->exec_interface("send_player_start_game", para);

	}

    return true;
}

int Account_Msg_Proc::login_to_engine( int role_id, const char* key )
{
    ////CCLog("-------------------->Account_Msg_Proc::login_to_engine---to game");

	std::string devname_local = "win";
	std::string devversion_local = "windows7";
	std::string clientversion_local = "";
	std::string version = Account_Data_Mgr::instance()->get_version();
	int apn = 0;
	std::string imei = "";
	std::string macaddress = "";

#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	devname_local = Account_Msg_Proc::devname;
	devversion_local = Account_Msg_Proc::devversion;
	clientversion_local = Account_Msg_Proc::clientversion;
	apn                 =  Account_Msg_Proc::apn;
	imei                = Account_Msg_Proc::imei;
	macaddress			= Account_Msg_Proc::macaddress;
#endif
    char body[512] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << CLIENT_ENTER_SCENE;
    body_ms << key;
	body_ms << role_id;
	body_ms << devname_local;
	body_ms << devversion_local;
	body_ms << clientversion_local;
	body_ms << Account_Msg_Proc::nn_uid;
	body_ms << Account_Msg_Proc::channel_id;
	body_ms << Account_Msg_Proc::create_time;
	body_ms << version;
	body_ms << apn;
	body_ms << imei;
	body_ms << macaddress;

    log("send enter_scene");
	CNetManager::GetMe()->send_msg( body_ms );

    return 0;
}

bool Account_Msg_Proc::on_player_enter_scene(Game_Logic::Game_Interface& gm_interface)
{
	//CCLog("------------------------->Account_Msg_Proc::on_player_enter_scene");
    CocoStu_UI_Scene_Interface::get_instance()->unlockScreen();
    //CCLog("-------------------->Account_Msg_Proc::on_player_enter_scene");
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int base_id = 0;
    int sex = 0;
    int level = 0;
    int quality = 0;
    int present_token = 0;
    int recharge_token = 0;
    int gold = 0;
    int exp = 0;
    int energy = 0;
    int buy_energy_count = 0;
    int prestige = 0;
    int offline_fight_count = 0;
    int buy_offline_fight_count = 0;
    int offline_fight_rank_reward_count = 0;
    int general_id = 0;
    int banks_exchange_count = 0;
    int function_open_id = 0;
    int is_first_login = 0;
	int camp_tag = 0;
	int main_city_scene_id = 0;
	int job = 0;

	int faction_job;
	int contribute_num;
	int curr_digging_num;
	int curr_worship_num;
	int curr_boss_num;
	int faction_id;
	std::string  faction_name;
	int cur_god_id;
	int cur_pet_id;
	int list_size;

    std::string name;
    body_ms >> base_id;
    body_ms >> sex;
    body_ms >> level;
    body_ms >> quality;
    body_ms >> present_token;
    body_ms >> recharge_token;
    body_ms >> gold;
    body_ms >> exp;
    body_ms >> energy;
    body_ms >> buy_energy_count;
    body_ms >> prestige;
    body_ms >> offline_fight_count;
    body_ms >> buy_offline_fight_count;
    body_ms >> offline_fight_rank_reward_count;
    body_ms >> general_id;
    body_ms >> banks_exchange_count;
    body_ms >> function_open_id;
    body_ms >> name;
    body_ms >> is_first_login;
	body_ms >> camp_tag;
	body_ms >> main_city_scene_id;
	body_ms >> job;

	body_ms >> faction_job;
	FACTION_MODEL::getInstance()->setJob(faction_job);
	body_ms >> contribute_num;
	body_ms >> curr_digging_num;
	FACTION_MODEL::getInstance()->setDigCurTime(curr_digging_num);
	body_ms >> curr_worship_num;
	FACTION_MODEL::getInstance()->setWorshipCurTime(curr_worship_num);
	body_ms >> curr_boss_num;
	FACTION_BOSS_MODEL::getInstance()->setCurTimes(curr_boss_num);
	body_ms >> faction_id;
	body_ms >> faction_name;
	bool isEmpty = faction_name.empty();
	bool hasLenth = (0!=faction_name.length());
	FACTION_MODEL::getInstance()->setJoined( !isEmpty && hasLenth );
	if (FACTION_MODEL::getInstance()->isJoined())
		FACTION_MODEL::getInstance()->setName(faction_name.c_str());
	//FACTION_MODEL::getInstance()->setJob(1);//for test 1 member 2 fubangzhu 3 bangzhu

	body_ms >> cur_god_id;
	body_ms >> cur_pet_id;
	//PET_MODEL::getInstance()->setCurrentPetId(cur_pet_id);
	//PET_MODEL::getInstance()->setCurrentPetId(201);
	body_ms >> list_size;
	for (int i = 0; i < list_size;i++)
	{
		uint64 first;
		int    second;
		body_ms >> first;
		body_ms >> second;

		Game_Model::Pet pet;
		pet.guid = first;
		pet.id = second;
		pet.isEquiped = false;

		if (pet.id == cur_pet_id)pet.isEquiped = true;

		PET_MODEL::getInstance()->getPets()->push_back(pet);
	}

    Account_Data_Mgr::instance()->set_is_first_login(is_first_login);
   
    Game_Data::Player* player = new Game_Data::Player;
	player->set_database_character_id(Account_Data_Mgr::instance()->get_current_role_id());
    player->set_character_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
    player->init_attr_data(base_id, level);
    player->set_character_quality(quality);
    player->set_sex(sex);
    player->set_present_token(present_token);
    player->set_recharge_token(recharge_token);
    player->set_gold(gold);
    player->set_exp(exp);
    player->set_energy(energy);
    player->set_buy_energy_count(buy_energy_count);
    player->set_prestige(prestige);
    player->set_offline_fight_count(offline_fight_count);
    player->set_buy_offline_fight_count(buy_offline_fight_count);
    player->set_offline_fight_rank_reward_count(offline_fight_rank_reward_count);
//    player->set_fight_general_id(general_id);
    player->set_banks_exchange_count(banks_exchange_count);
    player->set_function_open_id(function_open_id); //17
    player->set_character_name(name.c_str());
	player->set_camp_tag(camp_tag);
	player->set_main_city_scene_id(main_city_scene_id);
	player->set_job(job);
	//player->set_job(2);
	player->set_title(6);
	
	if (cur_god_id > 0)player->set_cur_god_id(cur_god_id);
	else player->set_cur_god_id(0);
    GOD_MODEL::getInstance()->setCurrentGodId(cur_god_id);
    GOD_MODEL::getInstance()->load();
    //GOD_MODEL::getInstance()->setCurrentGodId(1003);

	PET_MODEL::getInstance()->setCurrentPetId(cur_pet_id);
	auto pets = PET_MODEL::getInstance()->getPets();
	std::vector<Game_Model::Pet>::iterator it =	pets->begin();
	for (; it != pets->end();it++)
	{
		uint64 guid = (*it).guid;
		int id = (*it).id;

		player->add_pet(guid, id);
	}
	player->set_cur_pet_id(cur_pet_id);
	

    CHARACTER_MGR::instance()->insert_character(player);

	vector<uint64> parameter;
	parameter.clear();
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_get_main_city_player", parameter);

	return true;
}

bool  Account_Msg_Proc::send_keep_alive(Game_Logic::Game_Interface& gm_interface)
{

    ////CCLog("-------------------->Account_Msg_Proc::send_keep_alive---to game");
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << SERVER_KEEP_ALIVE;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
void Account_Msg_Proc::save_android_property(std::string localtokenId,std::string localdevicename,std::string localdeviceversion,std::string localclientversion,int iapn,std::string localimei,std::string loaclmacaddress)
{
	Account_Msg_Proc::tokenid=localtokenId;
	////CCLog("cpp value %s",tokenid.c_str());
	Account_Msg_Proc::devname=localdevicename;
	////CCLog("cpp value %s",devname.c_str());
	Account_Msg_Proc::devversion=localdeviceversion;
	////CCLog("cpp value %s",devversion.c_str());
	Account_Msg_Proc::clientversion=localclientversion;
	////CCLog("cpp value %s",clientversion.c_str());
	Account_Msg_Proc::apn=iapn;
	//CCLog("------------------in cpp apn %d",iapn);
	Account_Msg_Proc::imei=localimei;
	//CCLog("------------------in cpp imei %s",localimei.c_str());
	Account_Msg_Proc::macaddress=loaclmacaddress;
	//CCLog("------------------in cpp imei %s",loaclmacaddress.c_str());

}
bool Account_Msg_Proc::send_player_login()
{
	////CCLog("-------------------android->Account_Msg_Proc::send_player_login ---to gate");

#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	int os_type = 1;
#endif
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	int os_type = 2;
#endif
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	int os_type = 3;
#endif

	std::string version		= Account_Data_Mgr::instance()->get_version();
	char msg_buf[1024] = {0};
	message_stream body_ms(msg_buf, sizeof(msg_buf));
	////CCLog("send type is %d",os_type);

	body_ms << CLIENT_AUTH_SESSION;
	body_ms << version;
	body_ms << os_type;
	body_ms << Account_Msg_Proc::tokenid;
	body_ms << Account_Msg_Proc::devname;
	body_ms << Account_Msg_Proc::devversion;
	body_ms << Account_Msg_Proc::clientversion; 

    CNetManager::GetMe()->send_msg( body_ms );

	Account_Data_Mgr::instance()->set_next_ui_config_id( 2006 );

	return true;
}

std::string Account_Msg_Proc::tokenid;
std::string Account_Msg_Proc::devname;
std::string Account_Msg_Proc::devversion;
std::string Account_Msg_Proc::clientversion;
int Account_Msg_Proc::apn=0;
std::string Account_Msg_Proc::imei;
std::string Account_Msg_Proc::macaddress;
#endif