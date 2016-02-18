#include "Login_Scene.h"
#include "UI_Interface/UI_LogoLayer.h"
#include "UI_Interface/UI_LoginLayer.h"
#include "Platform_Dependence/Dependence.h"
#include "Partition_System/Partition_Msg_Proc_Cl.h"
#include "game_interface/game_content_interface.h"
#include "Update_Logic/MessageInfo.h"
#include "Update_Logic/UpdateHelper.h"
#include "Network_Common/NetManager.h"
#include "Common/GameDefine.h"
#include "UI/Login_Scene.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#if 1
#include "Game_Interface/game_content_interface.h"
#include "Network_Common/NetManager.h"

#include "AppMacros.h"
//#include "SimpleAudioEngine.h"
//#include "Game/Runtime.h"
//#include "AI_System/AI_Controller.h" 
#include "UI_Interface/UI_Interface.h"
#include "UI_Interface/UI_Config_Data_Mgr.h"
//#include "Effect_Cfg_Data_Mgr.h"
#include "UI_Interface/UI_Logic.h"
#include "UI_Interface/CocoStu_UI_Scene_Config_Mgr.h"
#include "UI_Interface/UI_Json_Manager.h"
#include "Network/msg_proc.h"
#include "Network_Common/global_macros.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player_Config_Mgr.h"
#include "Character_System/FightNpc_Config_Mgr.h"
#include "Cool_Time_System/Cool_Time_Config_Mgr.h"
#include "Acupoint_System/Acupoint_Config_Mgr.h"
//#include "Fight_System/Fight_Config_Mgr.h"
#include "Item_System/Item_Config_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Play_System/Instance_Data_Mgr.h"
#include "Play_System/Formula_Logic.h"
#if 1//yypp
#include "Relation_System/Relation_Mgr.h"
#endif
//#include "Dialogue_System/DialogueManager.h"
#include "Rank_System/Rank_Mgr_Cl.h"
#include "Character_System/CommonNpc_Config_Mgr.h"
#include "Shop_System/Shop_Config_Mgr.h"
#include "Activity_System/Activity_Config_Mgr.h"
#include "Daily_Task_System/Daily_Task_Config_Mgr.h"
#include "quest_system/quest_data/quest_data_mgr.h"
#include "game_play_controler/game_play_controler_logic/gameplay_ctrl_db_proc.h"
#include "Platform_Dependence/Dependence.h"
//#include "Monster_Wave_Cfg_Data_Mgr.h"
#include "Network_Common/NetManager.h"
#include "UI/Login_Scene.h"
#include "Game/Audio_Manager.h"
#include "UI/DownLoading_Layer.h"
#include "Random_System/Name_Random_Mgr.h"
#include "Junior_Guide_System/Junior_Guide_Mgr.h"
#include "Function_Open_System/Function_Open_Config_Mgr.h"
#include "Login_Reward_System/Login_Reward_Config_Mgr.h"
//#include "Game/Monster_Cfg_Data_Mgr.h"
#include "Shield_Word/ShieldManager.h"
#include "../Faction_System/Faction_Config_Mgr.h"
#endif

#include "../DataModule/Little.h"
#include "../Dialogue_System/Dialogue_Client.h"
#include "../God_System/God_Weapon_Config_Mgr.h"
#include "../Pet_System/Pet_Client.h"
//#define LITTLE_PATH "GameData/little/little"

#include "TouchSkill/SkillMsgProc.h"

Login_Scene* Login_Scene::instance_=0;

Login_Scene::Login_Scene()
{
}

Login_Scene::~Login_Scene()
{
}

Login_Scene* Login_Scene::sharedInstance()
{
	return instance_;
}

bool Login_Scene::init()
{
	bool ret=false;
#if 0
	do 
	{
		CC_BREAK_IF(!Scene::init());
#if(USELOGO==1)
		UI_LogoLayer* logoLayer=UI_LogoLayer::create();
		this->addChild(logoLayer,0,UI_LOGO_LAYER);
		this->scheduleOnce(schedule_selector(Login_Scene::removeLogo),1.2f);
		this->scheduleOnce(schedule_selector(Login_Scene::showLogin),1.5f);
#else
		UI_LoginLayer* login=UI_LoginLayer::create();
		this->addChild(login,1,UI_LOGIN_LAYER);
		this->scheduleOnce(schedule_selector(Login_Scene::showLogin),0.5f);
#endif

		instance_=this;
		pthread_mutex_init(&messageQueueMutex,NULL);
		this->scheduleUpdate();
		ret=true;
	} while (0);

#else
	do 
	{

		addLoadFunc( Loading_Scene::LoadFunc(&Login_Scene::loadOne) );
		addLoadFunc(Loading_Scene::LoadFunc(&Login_Scene::loadTwo));
		addLoadFunc( Loading_Scene::LoadFunc(&Login_Scene::loadThree) );
		addLoadFunc( Loading_Scene::LoadFunc(&Login_Scene::loadFour) );
		addLoadFunc( Loading_Scene::LoadFunc(&Login_Scene::loadFive) );
		addLoadFunc( Loading_Scene::LoadFunc(&Login_Scene::loadSix) );
		addLoadFunc( Loading_Scene::LoadFunc(&Login_Scene::loadSeven) );
		addLoadFunc(Loading_Scene::LoadFunc(&Login_Scene::loadEight));
		addLoadFunc(Loading_Scene::LoadFunc(&Login_Scene::loadNine));
		addLoadFunc(Loading_Scene::LoadFunc(&Login_Scene::loadTen));
		addLoadFunc(Loading_Scene::LoadFunc(&Login_Scene::LoadEleven));
		CC_BREAK_IF(!Loading_Scene::init());			
		ret=true;

	} while (0);
#endif
	return ret;

}

void Login_Scene::removeLogo(float dt)
{
#if(USELOGO==1)
	//将logo从scene中移除,要确保这个层存在
	this->removeChildByTag(UI_LOGO_LAYER);
	//添加login层
	UI_LoginLayer* login=UI_LoginLayer::create();
	this->addChild(login,1,UI_LOGIN_LAYER);
	//弹出登录的界面
	#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32||CC_TARGET_PLATFORM==CC_PLATFORM_IOS||CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		vector<uint64> para2;
		para2.clear();
		Game_Logic::Game_Content_Interface::instance()->exec_interface("send_ask_partition_info",para2);
	#endif
#endif
}

void Login_Scene::showLogin(float dt)
{
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//	Dependence::showLogin();
#endif

#if(USELOGO==0)
#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32||CC_TARGET_PLATFORM==CC_PLATFORM_IOS||CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	vector<uint64> para2;
	para2.clear();
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_ask_partition_info",para2);
#endif
#endif
}

void Login_Scene::sendMessage(EVENTTYPE eventType)
{
	pthread_mutex_lock(&messageQueueMutex);
	messageQueue.push_back(eventType);
	pthread_mutex_unlock(&messageQueueMutex);
}

void Login_Scene::update(float dt)
{
	CNetManager::GetMe()->WaitPacket();
	int eventtype=-1;
	pthread_mutex_lock(&messageQueueMutex);
	if(0==messageQueue.size())
	{
		pthread_mutex_unlock(&messageQueueMutex);
		return;
	}
	eventtype=messageQueue.front();
	messageQueue.pop_front();
	if(eventtype==EVENT_TYPE_LOGIN_SUCCEED)
	{
		CCLog("--------------------------------login succeed！");
		//登录成功，检查更新
		UI_LoginLayer* login=(UI_LoginLayer*)(this->getChildByTag(UI_LOGIN_LAYER));
		if(login)
		{
			
				const char* login_succeed_checking_update = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(LOGIN_SUCCEED_CHECKING_UPDATE);
				login->m_labTips->setString(login_succeed_checking_update);
			
		}

	}
	else if(eventtype==EVENT_TYPE_NO_UPDATE)
	{
		//没有更新
		UI_LoginLayer* login=(UI_LoginLayer*)(this->getChildByTag(UI_LOGIN_LAYER));
		if(login)
		{
			
				const char* getting_info = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(GETTING_SERVER_INFO);
				login->m_labTips->setString(getting_info);
		
		}

		CCLog("------------------------------don't have  update ");
		

	}
	else if(eventtype==EVENT_TYPE_HAVE_UPDATE)
	{
#if 0//(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)

		UI_LoginLayer* login=(UI_LoginLayer*)(this->getChildByTag(UI_LOGIN_LAYER));
		if(login)
		{

			login->m_labTips->setString("");

		}

		//有更新，开始更新
		bool isWifiConnected=false;
		isWifiConnected=Dependence::isWiFiConnected();
		if(isWifiConnected)
		{
			//当前环境是WIFI环境，直接进入更新

		
		MessageInfo *msg=new MessageInfo();
		msg->what=MessageInfo::START_MESSION;
		UpdateHelper::sharedInstance()->sendMessage(msg);
		
		}
		else
		{
			//当前环境为非WIFI环境,提示用户需要消耗流量
			UI_LoginLayer* login=(UI_LoginLayer*)(this->getChildByTag(UI_LOGIN_LAYER));
			if(login)
			{
				login->m_imgDialog->setVisible(true);
			}
			
		}	
#endif
	}
	else if(eventtype==EVENT_TYPE_OBTAIN_SERVER)
	{
		vector<uint64> para2;
		para2.clear();
		Game_Logic::Game_Content_Interface::instance()->exec_interface("send_ask_partition_info",para2);
		//正在获取服务器信息
	}
	else if(eventtype==EVENT_TYPE_GOT_SERVER_FAILED)
	{
		//获取分区服务器失败啊
		UI_LoginLayer* login=(UI_LoginLayer*)(this->getChildByTag(UI_LOGIN_LAYER));
		if(login)
		{
				const char* server_error = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SERVER_ERROR);
				login->m_labTips->setString(server_error);
			
		}
	}
	pthread_mutex_unlock(&messageQueueMutex);
}
#if 1
void Login_Scene::onLoadFinish()
{
	Loading_Scene::onLoadFinish();
//#if(USELOGO==1)
//	UI_LogoLayer* logoLayer = UI_LogoLayer::create();
//	this->addChild(logoLayer, 0, UI_LOGO_LAYER);
//	this->scheduleOnce(schedule_selector(Login_Scene::removeLogo), 1.2f);
//	this->scheduleOnce(schedule_selector(Login_Scene::showLogin), 1.5f);
//#else
//	UI_LoginLayer* login = UI_LoginLayer::create();
//	this->addChild(login, 1, UI_LOGIN_LAYER);
//	this->scheduleOnce(schedule_selector(Login_Scene::showLogin), 0.5f);
//#endif
	instance_ = this;
	pthread_mutex_init(&messageQueueMutex, NULL);
	this->scheduleUpdate();
}

void Login_Scene::loadOne()
{
	CNetManager::GetMe()->Initial(NULL);
	Msg_Proc::instance()->init();

	
}

void Login_Scene::loadTwo()
{
	//initialize game play system 
	//SKILL_MGR::instance()->initialize();
	//BUFF_MGR::instance()->initialize();
	PLAYER_MGR::instance()->initialize();
	//FIGHTNPC_MGR::instance()->initialize();
	//TECHNICAL_MGR::instance()->initialize();
	//Job_Skill_Config_mgr::instance()->initialize();
    Game_Logic::Game_Interface temp;

	Rank_Manager::instance()->initialize();
	//DialogueManager::instance()->initialize();
	DICTIONARY_CONFIG_MGR::instance()->initialize();
	Name_Random_Mgr::get_instance()->initialize();
	Junior_Guide_Mgr::get_instance()->initialize();
}

void Login_Scene::loadThree()
{
	//CommonNpc_Config_MGR::instance()->initialize();
	SHOP_CONFIG_MGR::instance()->initialize();
	ACTIVITY_CONFIG_MGR::instance()->initialize();
	DAILY_TASK_CONFIG_MGR::instance()->initialize();
	CocoStudio::CocoStu_UI_Scene_Config_Mgr::get_instance()->init();
}

void Login_Scene::loadFour()
{
	//Shake_Manager::sharedInstance()->init();
	UI_Json_Manager::get_instance()->init();
	Game_Data::UI_Config_Data_Mgr::instance()->init();
	Game_Logic::Game_Content_Interface::instance()->init();
	UI_Logic::instance()->init_UI_system();
}

void Login_Scene::loadFive()
{
	// AI_Controller::instance()->initialize();
	//Effect_Cfg_Data_Mgr::instance()->load_config();
	//FIGHT_CONFIG_MGR::instance()->initialize();
	ACUPOINT_CONFIG_MGR::instance()->initialize();
	COOL_TIME_CONFIG_MGR::instance()->initialize();
}

void Login_Scene::loadSix()
{
	FUNCTION_OPEN_CONFIG_MGR::instance()->initialize();
	LOGIN_REWARD_CONFIG_MGR::instance()->initialize();
	//Monster_Cfg_Data_Mgr::instance()->initialize();
	ShieldManager::sharedShieldManager()->init();
	Account_Data_Mgr::instance()->init();
}

void Login_Scene::loadSeven()
{
	//init instance_system
	INSTANCE_DATA_MGR::instance()->initialize();
	Formula_Logic::instance()->init_formula_system();
}

void Login_Scene::loadEight()
{
	vector<uint64> para;
	para.clear();
	Game_Logic::Game_Content_Interface::instance()->exec_interface("createcontainer", para);
	para.clear();
	Game_Logic::Game_Content_Interface::instance()->exec_interface("loadformuladata", para);
}

void Login_Scene::loadNine()
{
	Game_Data::quest_data_mgr::instance()->init("");

	ITEM_CONFIG_MGR::instance()->initialize();
	//DICTIONARY_CONFIG_MGR::instance()->initialize();
	//Monster_Wave_Cfg_Data_Mgr::shared_instance()->load_config();

	Audio_Manager::shared_Audio_Manager()->preload_audio();

	//gameplay_ctrl_db_proc::instance()->load_activity_data();
}

void Login_Scene::loadTen()
{
	//Buff_Manager::instance()->initialize();
	FACTION_CONFIG_MGR::instance()->initialize();
	GOD_WEAPON_CONFIG_MGR::instance()->initialize();
	//Little::readFile(LITTLE_PATH);
	PET_MODEL::getInstance()->load();

}

void Login_Scene::LoadEleven()
{
	DIALOGUE_MODEL::getInstance()->initWithId(1);
	vector<uint64> para2;
	para2.clear();
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_ask_partition_info", para2);

}

#endif