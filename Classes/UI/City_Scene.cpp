#include "City_Scene.h"

#include "UI_Interface/UI_Interface.h"
#include "UI_Interface/UI_Config_Data_Mgr.h"
#include "Game_Interface/game_content_interface.h"
#include "UI_Interface/UI_Logic.h"
#include "Network_Common/NetManager.h"
#include "Game/Audio_Manager.h"
#include "Common/Utils.h"
#include "Message_Layer.h"
#include "UI_Interface/UI_MainMenu_Layer.h"
#include "Event_System/event_system_logic.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"

#include "../Network_Common/NetManager.h"

#include "../ClientLogic/SneakyJoy/SneakyJoyStickSkinnedBase.h"

#include "../Player_Account/Account_Data_Mgr.h"
#include "../Character_System/Character_Mgr.h"
#include "../Character_System/Player.h"

using namespace ui;

namespace UI
{
	int City_Scene::sceneId = 0;

    City_Scene::~City_Scene()
    {
//        _hudLayer->removeFromParent();

        Director::getInstance()->purgeCachedData();
    }

	bool City_Scene::init()
	{
        ITEM_CONFIG_MGR::instance()->load_icon_config_data();
        log("load icon");
		addLoadFunc(Loading_Scene::LoadFunc(&City_Scene::loadData));
		addLoadFunc(Loading_Scene::LoadFunc(&City_Scene::loadBackLayer));
		addLoadFunc(Loading_Scene::LoadFunc(&City_Scene::loadMidLayer));		
		addLoadFunc(Loading_Scene::LoadFunc(&City_Scene::loadFrontLayer));
        addLoadFunc(Loading_Scene::LoadFunc(&City_Scene::loadActorLayer));
		addLoadFunc(Loading_Scene::LoadFunc(&City_Scene::loadCamera));
		addLoadFunc(Loading_Scene::LoadFunc(&City_Scene::loadAudio));
		addLoadFunc(Loading_Scene::LoadFunc(&City_Scene::loadHUD));
        log("add loadings");
		if (!Loading_Scene::init())
			return false;
		
		return true;

	}

	//void City_Scene::load_Message_layer()
	//{
	//  log("load message");
	//	_msglayer = Message_Layer::create();
	//	_msglayer->setVisible(false);
	//	addChild(_msglayer, 720, TAG_MSG);
	//}

	void City_Scene::loadHUD()
	{
        log("load main menu");
		_hudLayer = UI_MainMenu_Layer::get_instance();
		_hudLayer->setVisible(false);
        
		addChild(_hudLayer, 25, TAG_BTN_UI);
	}

	void City_Scene::loadAudio()
	{
        log("load audio");
        std::string musicFile("music/city.mp3");

        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(musicFile.c_str());
	}

	void City_Scene::onLoadFinish()
	{
        log("finish load");
		Loading_Scene::onLoadFinish();
		//初始化事件系统
		vector<uint64> para;
		para.clear();
		Game_Logic::Game_Content_Interface::instance()->exec_interface("loadeventsystemdata", para);

		int player_id = Account_Data_Mgr::instance()->get_current_role_id();
		event_system_logic::sharedInstance()->init_event_system(player_id);

        std::string musicFile("music/city.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(musicFile.c_str(), true);
		//请求公告：
		if (!Account_Data_Mgr::instance()->get_is_first_login())
		{
			vector<uint64> para2;
			para2.clear();
			Game_Logic::Game_Content_Interface::instance()->exec_interface("send_ask_pubilc_annoucement", para2);
		}

		_hudLayer->setVisible(true);
        _hudLayer->showGuide();
		//_scheduler->scheduleSelector(schedule_selector(City_Scene::update), this, 0.1f, kRepeatForever, 0, false);
		scheduleUpdate();

		return;
	}

	void City_Scene::update(float delta)
	{
		CNetManager::GetMe()->WaitPacket();

		_sceneLayer->controlByJoyStick(_hudLayer->getJoyStick(), delta);
		_sceneLayer->reorderPlayer();

        if( _sceneLayer->isCollideDoor() ) {
			_sceneLayer->onCollideDoor();
        }

	}

	void City_Scene::onExit()
	{
		Scene::onExit();

        unscheduleUpdate();
        cocostudio::ArmatureDataManager::destroyInstance();
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	}

	void City_Scene::loadData()
	{

		int player_id = Account_Data_Mgr::instance()->get_current_role_id();
		Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
		if (player)
			sceneId = player->get_main_city_scene_id();

		_sceneLayer = CityLayer::create();
		_sceneLayer->initData(sceneId);
        
		addChild(_sceneLayer,10,TAG_ACT);
        
	}

	void City_Scene::loadCamera()
	{
		_sceneLayer->initCamera();
	}

	void City_Scene::loadFrontLayer()
	{
		_sceneLayer->initFrontLayer();
	}

	void City_Scene::loadMidLayer()
	{
		_sceneLayer->initMidLayer();
	}

	void City_Scene::loadBackLayer()
	{
		_sceneLayer->initBackLayer();

		//    backLayer = Layer::create();
		//    bgSpt = Sprite::create("img/scene/scene_26_back.png");
		//    bgSpt->setAnchorPoint(Point(0, 1));
		//    bgSpt->setPosition(Vec2(0, 660));
		//    backLayer->addChild(bgSpt);
		//    
		//    backLayer->setPosition(Vec2(0, -5));
		//    addChild(backLayer);
	}
    
    void City_Scene::changeGuardianArmature(std::string armName, bool first)
    {
        if(first)
        {
            _sceneLayer->addGuard2Hero();
        }else{
            _sceneLayer->player->getGuard()->getArmature()->init(armName);
        }
        
        _sceneLayer->player->getGuard()->getArmature()->getAnimation()->playWithIndex(0);
    }
    
	void City_Scene::loadActorLayer()
	{
		_sceneLayer->initActorLayer();
        
		int player_id = Account_Data_Mgr::instance()->get_current_role_id();
//		Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
//		if ( NULL == player)
//		{
//			CCLOG("player id(%d) is wrong!!!\n", Account_Data_Mgr::instance()->get_current_role_id());
//			return;
//		}

		// 连击清零
		//player->set_character_combo(0);
		//Game_Utils::instance()->reset_character(player_id);
		//Game_Utils::instance()->reset_character(player->get_fight_general_id());

		//to do scene load finish
		//cout << "=======================scene load finish===========================" << endl;
		//if (Game_Utils::instance()->is_in_city())
		//{
			/*std::vector<uint64> para;
			Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_item_container", para);

			para.push_back(Account_Data_Mgr::instance()->get_current_role_id());
			Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_skill", para);*/

			//PLAYER_LOGIC::instance()->get_main_city_player();
        vector<uint64> para;
        para.push_back( player_id );
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sendreqnpcquest",para);

//		UI_MainMenu_Layer::get_instance()->refreshFindWay();

//		Game_Logic::Game_Event_Response::instance()->on_finish_scene_load();
		
	}

};