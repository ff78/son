#include "AppDelegate.h"
#include <vector>
#include <string>
#include "base/CCScriptSupport.h"
//#include "Shake_System/Shake_Manager.h"
#include "AppMacros.h"
//#include "SimpleAudioEngine.h"
//#include "Game/Runtime.h"
//#include "AI_System/AI_Controller.h" 
#include "UI_Interface/UI_Interface.h"
#include "UI_Interface/UI_Config_Data_Mgr.h"
#include "Common/Effect_Cfg_Data_Mgr.h"
#include "Game_Interface/game_content_interface.h"
#include "UI_Interface/UI_Logic.h"
#include "UI_Interface/CocoStu_UI_Scene_Config_Mgr.h"
#include "UI_Interface/UI_Json_Manager.h"
#include "Network/msg_proc.h"
#include "Network_Common/global_macros.h"

#include "Skill_System/Skill/Skill_Mgr.h"
#include "Skill_System/Buff/Buff_Mgr.h"

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
#include "Skill_System/Skill/Technical_Mgr.h"
#include "Character_System/CommonNpc_Config_Mgr.h"
#include "Shop_System/Shop_Config_Mgr.h"
//#include "Activity_System/Activity_Config_Mgr.h"
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
//#include "Game_Core.h"

//#include "CCLuaEngine.h"
//#include "lua_assetsmanager_test_sample.h"

#include "ClientLogic/Utils/BaseUtils.h"

using namespace CocosDenshion;
USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate() 
:is_first_(true)
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() 
{
//	auto pEngine = LuaEngine::getInstance();
//	ScriptEngineManager::getInstance()->setScriptEngine(pEngine);
//	auto stack = pEngine->getLuaStack();
//	auto lua_stack = stack->getLuaState();
//	stack->setXXTEAKeyAndSign( "2dxLua",strlen("2dxLua"),"XXTEA",strlen("XXTEA") );
//#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM==CC_PLATFORM_WIN32||CC_TARGET_PLATFORM==CC_PLATFORM_IOS||CC_TARGET_PLATFORM==CC_PLATFORM_MAC)
//	//register_assetsmanager_test_sample(lua_stack);
//#endif
//	pEngine->executeScriptFile("");

    //initialize network

    CNetManager* netmgr = new CNetManager;
    // initialize director
    auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	
	if(!glview) {
        glview = GLView::create("My Game");
		director->setOpenGLView(glview);
    }

    director->setOpenGLView(glview);
	
    // Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    // a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
#else

	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_HEIGHT);

#endif
    Size frameSize = glview->getFrameSize();
    vector<string> searchPath;
    std::string sdDir;
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//	searchPath.push_back(Dependence::getResourcesSearchPath()+"/data/ipad");
//	searchPath.push_back(FileUtils::getInstance()->getWritablePath());
    sdDir = Dependence::getWorkingDir();
    log("sd path: %s", sdDir.c_str());
    searchPath.push_back(sdDir);
#endif

    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.

    // if the frame's height is larger than the height of medium resource size, select large resource.
#if 0
	if (frameSize.height > mediumResource.size.height)
	{
        searchPath.push_back(mediumResource.directory);

       // director->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	}
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.height > smallResource.size.height)
    {
        searchPath.push_back(mediumResource.directory);
        
       // director->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
	else
    {
        searchPath.push_back(mediumResource.directory);

    //   director->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
    }
    // set searching path
    FileUtils::getInstance()->setSearchPaths(searchPath);
#endif
    
    FileUtils::getInstance()->setSearchPaths(searchPath);
    log("writablePath ====== %s",FileUtils::getInstance()->getWritablePath().c_str());
	//init_game_system();
    // turn on display FPS
    director->setDisplayStats(true);
    // set FPS. the default value is 1.0/60 if you don't call this
//    director->setAnimationInterval(1.0 / 30);

	// create a scene. it's an autorelease object
	Director::getInstance()->setContentScaleFactor(1.f);

	//start();
	ITEM_CONFIG_MGR::instance()->initialize();
	DICTIONARY_CONFIG_MGR::instance()->initialize();


    YNBaseUtil::WinSize = Size(director->getWinSize().width, director->getWinSize().height);
	//auto scene = FirstScene::getInstance();
	Scene* scene = Login_Scene::create();
	if (scene)
	{
		Director::getInstance()->runWithScene(scene);
	}

	return true;
}

void AppDelegate::init_game_system()
{
    CNetManager::GetMe()->Initial(NULL);
    Msg_Proc::instance()->init();

	//initialize game play system 
	SKILL_MGR::instance()->initialize();
	Buff_Manager::instance()->initialize();
	PLAYER_MGR::instance()->initialize();
    FIGHTNPC_MGR::instance()->initialize();
    TECHNICAL_MGR::instance()->initialize();
	DICTIONARY_CONFIG_MGR::instance()->initialize();
	Name_Random_Mgr::get_instance()->initialize();
	Junior_Guide_Mgr::get_instance()->initialize();
	CommonNpc_Config_MGR::instance()->initialize();
	SHOP_CONFIG_MGR::instance()->initialize();
//   ACTIVITY_CONFIG_MGR::instance()->initialize();
   DAILY_TASK_CONFIG_MGR::instance()->initialize();
	CocoStudio::CocoStu_UI_Scene_Config_Mgr::get_instance()->init();
	//Shake_Manager::sharedInstance()->init();
	UI_Json_Manager::get_instance()->init();
	Game_Data::UI_Config_Data_Mgr::instance()->init();
	Game_Logic::Game_Content_Interface::instance()->init();
	UI_Logic::instance()->init_UI_system();
   // AI_Controller::instance()->initialize();
	Effect_Cfg_Data_Mgr::instance()->load_config();
    //FIGHT_CONFIG_MGR::instance()->initialize();
    ACUPOINT_CONFIG_MGR::instance()->initialize();
    COOL_TIME_CONFIG_MGR::instance()->initialize();
   FUNCTION_OPEN_CONFIG_MGR::instance()->initialize();
    LOGIN_REWARD_CONFIG_MGR::instance()->initialize();
    //Monster_Cfg_Data_Mgr::instance()->initialize();
	ShieldManager::sharedShieldManager()->init();

    Account_Data_Mgr::instance()->init();

    //init instance_system
    INSTANCE_DATA_MGR::instance()->initialize();

    Formula_Logic::instance()->init_formula_system();

    vector<uint64> para;
    para.clear();
    Game_Logic::Game_Content_Interface::instance()->exec_interface("createcontainer", para);

    para.clear();
    Game_Logic::Game_Content_Interface::instance()->exec_interface("loadformuladata", para);

    Game_Data::quest_data_mgr::instance()->init("");



    //Monster_Wave_Cfg_Data_Mgr::shared_instance()->load_config();

	Audio_Manager::shared_Audio_Manager()->preload_audio();

    //gameplay_ctrl_db_proc::instance()->load_activity_data();

    
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	 SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	 SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}