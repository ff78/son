#include "Main_City_Scene.h"
#include "Common/VisibleRect.h"
#include "UI_Interface/UI_Interface.h"
#include "UI_Interface/UI_Logic.h"
#include "UI_Interface/CocoStu_UI_Scene_Interface.h"
#include "Network_Common/NetManager.h"
#include "UI_Interface/Select_Server_UI.h"
#include "Game_Interface/game_content_interface.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Player_Account/Account_Data.h"
#include "Common/GameMacro.h"
#include "cocos2d.h"
#include "json/json_header.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Common/GameDefine.h"
#include "UI_Interface/MyEditBox.h"
#include "Common/GameResource.h"
#include "Player_Account/Account_Logic.h"

#include "UI_Interface/UI_ModalDialogue_Layer.h"
#include "Random_System/Name_Random_Mgr.h"
#include <time.h>
#include "UI_Interface/UI_StartGameLayer.h"
#include "Platform_Dependence/Dependence.h"
#include "Player_Account/RecentlyServer.h"

#include "cocos2d.h"
#include "Common/Utils.h"

using namespace Game_Data;

namespace UI
{
	bool Main_City_Scene::init()
	{
		cocos2d::CCLog("{ Main_City_Scene::init}\n");
		_bgLayer = Main_City_Background_Layer::create();

		this->addChild(_bgLayer);

		Main_City_Actor_Layer* al = Main_City_Actor_Layer::get_instance();
		al->init();
		al->removeFromParent();
		al->setVisible(true);
		this->addChild(al);

		_scheduler->scheduleSelector(schedule_selector(Main_City_Scene::update), this, (float)0.1, kRepeatForever, 0, false);
		std::string musicFile("music/login.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(musicFile.c_str());
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(musicFile.c_str(), true);
		return true;
	}

	Main_City_Scene* Main_City_Scene::scene()
	{
		Main_City_Scene* s = 0;
		do
		{
			s = new Main_City_Scene();
			s->init();
			s->autorelease();
		} while (0);
		return s;
	}

	void Main_City_Scene::update(float delta)
	{
		_bgLayer->update(delta);
		Main_City_Actor_Layer::get_instance()->update(delta);
		CNetManager::GetMe()->WaitPacket();

	}

	void Main_City_Scene::current_server(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
	{
		//int dd = get_instance()->get_total_num();
		const char* exitInfo;
		int id;
		vector<uint64> para;
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			id = pSender->_ID;
			if (id <= 0)
				return;
			else
			{
				para.push_back(id);
				if (!Game_Logic::Game_Content_Interface::instance()->exec_interface("connecttogate", para))
				{
					exitInfo = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SERVER_DISCONNECT);
					UI_ModalDialogue_Layer::DoModal("", exitInfo, UI_ModalDialogue_Layer::DT_OK, []()
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
				}

			}
			break;
		default:
			break;
		}

	}

	std::string Main_City_Scene::getRandomName(int sex)
	{
		std::string retName;
		int family_name_id;
		const char* name_front;
		//cocos2d::ui::TextField* pEditBox;
		char name_f[32] = { 0 };
		int family_name_called_id = 0;
		char name_r[64] = { 0 };
		const char* name_rear;
		std::string family_name_called;
		std::string family_name;
		CCLOG(" random role name ");
		srand((unsigned)time(NULL));
		family_name_id = rand() % 264 + 1;
		CCLOG("family_name_id = %d", family_name_id);
		name_front = Name_Random_Mgr::get_instance()->get_name_by_id(family_name_id);

		memcpy(name_f, name_front, strlen(name_front) - 1);
		family_name = name_f;


		if (0 == sex) //随机女性名称
			family_name_called_id = rand() % (1808 - 1500) + 1501;
		if (1 == sex) //随机男性名称
			family_name_called_id = rand() % (956 - 500) + 501;

		CCLOG("family_name_called_id = %d", family_name_called_id);
		name_rear = Name_Random_Mgr::get_instance()->get_name_by_id(family_name_called_id);

		memcpy(name_r, name_rear, strlen(name_rear) - 1);
		family_name_called = name_r;

		retName = family_name + family_name_called;
		CCLOG("name = %s", retName.c_str());
		return retName;
	}


    bool Main_City_Background_Layer::init()
    {
        init_bg();
        
        return true;
    }
    
    void Main_City_Background_Layer::init_bg()
    {
        // to do: 从配置文件中获取背图图
        cocos2d::log("Main_City_Background_Layer::init_bg");
        cocos2d::Sprite* sp = cocos2d::Sprite::create("scene_res/login_bg.png");
		sp->setOpacity(0);
		auto fadeIn = FadeIn::create(2);
		auto seq = Sequence::create(fadeIn,nullptr);
		sp->runAction(seq);
        sp->setPosition(VisibleRect::center());
		float screenWidth = Director::getInstance()->getWinSize().width;
		float screenHight = Director::getInstance()->getWinSize().height;
		float spWidth = sp->getContentSize().width;
		float spHight = sp->getContentSize().height;
		float scaleX = screenWidth / spWidth;
		float scaleY = screenHight / spHight;
		sp->setScaleX(scaleX);
		sp->setScaleY(scaleY);
        this->addChild(sp);

		//ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/charge.ExportJson");
		//_armatureRepeat = cocostudio::Armature::create("charge");
		//_armatureRepeat->getAnimation()->play("charge");
		//_armatureRepeat->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
		//this->addChild(_armatureRepeat);

		//ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/city_npc1.ExportJson");
		//_armatureOnce = cocostudio::Armature::create("city_npc1");
		//_armatureOnce->getAnimation()->playWithIndex(0, 0, 0);
		//_armatureOnce->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
		////armatureOnce->getAnimation()->setFrameEventCallFunc( CC_CALLBACK_0(Main_City_Background_Layer::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		//this->addChild(_armatureOnce);
		
        // 创建版本信息
        std::string str_version = Account_Data_Mgr::instance()->get_version();
        LabelTTF *lable_version = LabelTTF::create(str_version.c_str(), "Thonburi", 30.f);
        //lable_version->setVisible(true);
        lable_version->setAnchorPoint(Vec2(0, 1));
        this->addChild(lable_version);
        lable_version->setPosition(VisibleRect::leftTop());
        
    }

	void Main_City_Background_Layer::onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
	{
	}

	void Main_City_Background_Layer::update(float delta)
	{
		//if (_armatureOnce->getAnimation()->isComplete())
		//{
		//	Main_City_Actor_Layer::get_instance()->setVisible(true);
		//}
	}


    Text* Main_City_Actor_Layer::curSv = NULL;

    Main_City_Actor_Layer* Main_City_Actor_Layer::instance_ = NULL;

    bool Main_City_Actor_Layer::init()
    {
        //UI_Recent_Server_Layer* recentServer = UI_Recent_Server_Layer::create();
        //addChild(recentServer);
        UI_StartGameLayer* startgame = UI_StartGameLayer::create();
        addChild(startgame,1,"StartGame");
        
        //         cocos2d::CCLog("Main_City_Actor_Layer::init");
        //         CocoStu_UI_Scene_Interface::get_instance()->run_test(2003);
        //         vector<uint64> para; para.clear();
        //
        //         loadServerList();
        m_sex = 1;
        m_job = 3;
        return true;
    }

	Main_City_Actor_Layer::Main_City_Actor_Layer()
	{
		_outAction = nullptr;
		_effectSequence = nullptr;
		_roleImg = nullptr;
		_effectSprite = nullptr;

	}

    Main_City_Actor_Layer::~Main_City_Actor_Layer()
    {
		_outAction = nullptr;
		_effectSequence = nullptr;
		_roleImg = nullptr;
		_effectSprite = nullptr;
		ArmatureDataManager::destroyInstance();
		Director::getInstance()->purgeCachedData();
    }

    void Main_City_Actor_Layer::onExit()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        removeAllChildren();
        Layer::onExit();
    }

    Main_City_Actor_Layer * Main_City_Actor_Layer::get_instance()
    {
        if (!instance_){
            instance_ = new Main_City_Actor_Layer;
        }
        return instance_;
    }

    void Main_City_Actor_Layer::goBackCallBack(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        UI_StartGameLayer* startgame;
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                startgame = UI_StartGameLayer::create();
                addChild(startgame);
                break;
            default:
                break;
        }
        
    }

    void Main_City_Actor_Layer::loadServerList()
    {
        CC_ASSERT(m_pUILayer);

        cocos2d::ui::Button* tbn_go_back = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, "Btn_Refresh"));
        if (tbn_go_back)
            tbn_go_back->addTouchEventListener(this, toucheventselector(Main_City_Actor_Layer::goBackCallBack));
        
        
        //auto next = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, "Button_78"));
        auto next = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, "Btn_Enter"));
        if (next)
            next->addTouchEventListener(UI::Main_City_Actor_Layer::get_instance(), toucheventselector(Main_City_Scene::current_server));
        
        Main_City_Actor_Layer::curSv = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pWidget, "Txt_Current"));
        
        for (int i = 0; i < 10; i++)
        {
            std::string preStr("Btn_Cell_R");
            Value suff(i);
            std::string suffStr = suff.asString();
            preStr += suffStr;
            Button* cell = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, preStr.c_str()));
            //cell->addTouchEventListener(CC_CALLBACK_2(Main_City_Scene::clickAServer, UI::Main_City_Actor_Layer::get_instance()));
            cell->addTouchEventListener(UI::Main_City_Actor_Layer::get_instance(), toucheventselector(Main_City_Actor_Layer::clickAServer));
            
            cell->setTag(i);
        }
        
    }
    
    void Main_City_Actor_Layer::refreshCurrentSelect()
    {
        const Account_Data_Mgr::SRoleData* pData = Account_Data_Mgr::instance()->get_current_select();
        cocos2d::ui::Text* lab_create_role = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget, "lab_create_role_info"));
        
        if (pData)
        {
            lab_create_role->setVisible(false);
            CC_ASSERT(m_pUILayer);
            cocos2d::ui::Text* pLabelName = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget, "lab_Name"));
            pLabelName->setFontSize(30);
            
            char szUIName[64] = { 0 };
            SPRINTF(szUIName, "%s(LV.%d)", pData->m_strName.c_str(), pData->m_nLevel);
            pLabelName->setString(szUIName);
        }
        else
            lab_create_role->setVisible(true);
    }
    
    void Main_City_Actor_Layer::roleSelectCallback(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        cocos2d::ui::ImageView* img_front;
        cocos2d::ui::ImageView* img_effect_back;
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                img_front = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
                img_effect_back = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "img_effect_back"));
                img_effect_back->setPosition(img_front->getPosition());
                
                Account_Data_Mgr::instance()->set_current_select(img_front->getTag());
                refreshCurrentSelect();
                break;
            default:
                break;
        }
        
    }
    
    const char* Main_City_Actor_Layer::getRigisterName()
    {
        /*CC_ASSERT(m_pUILayer);
         cocos2d::ui::TextField* pEditBox = dynamic_cast<cocos2d::ui::TextField*>(Helper::seekWidgetByName(m_pWidget, "tfd_Name"));
         CC_ASSERT(pEditBox);
         
         return pEditBox->getStringValue().c_str();*/
        return this->name.c_str();
    }
     
    void Main_City_Actor_Layer::loadRoleList()
    {
        CC_ASSERT(m_pUILayer);
        if (m_pUILayer)
        {
            Account_Data_Mgr* pADMgr = Account_Data_Mgr::instance();
            CC_ASSERT(pADMgr);
            for (int i = 0; i < pADMgr->get_role_num() && i < 1; i++)
            {
                const Account_Data_Mgr::SRoleData& refData = pADMgr->m_RoleData[i];
                
                char szUIName[64] = { 0 };
                SPRINTF(szUIName, "img_Role_%d", i + 1);
                cocos2d::ui::ImageView* pImgBkg = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, szUIName));
                CC_ASSERT(pImgBkg);
                pImgBkg->setTag(i);
                pImgBkg->addTouchEventListener(this, toucheventselector(Main_City_Actor_Layer::roleSelectCallback));
                
                int actor_id = 0;
                if (refData.m_nSex == 1)
                {
                    actor_id = 1;
                }
                else
                {
                    actor_id = 2;
                }
                
                cocos2d::ui::Widget* maleNode = createNode(actor_id);
                maleNode->setPosition(Vec2(0.f, -100.f));
                pImgBkg->addChild(maleNode);
            }
        }
        refreshCurrentSelect();
    }
    
    void Main_City_Actor_Layer::loadSelectJob()
    {
        CC_ASSERT(m_pUILayer);
        if (m_pUILayer)
        {
            auto layer = LayerColor::create(Color4B::BLACK);
            addChild(layer,m_pUILayer->getLocalZOrder()-1);

			auto size = Director::getInstance()->getWinSize();
			cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/nvqiang.ExportJson");
			_nvqiangArmature = cocostudio::Armature::create("nvqiang");
			_nvqiangArmature->getAnimation()->play("stand");
			_nvqiangArmature->setPosition(Vec2(size.width / 2, size.height / 2 - 200));
			_nvqiangArmature->setVisible(false);
            _nvqiangArmature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Main_City_Actor_Layer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
//			_nvqiangActionNames.push_back("stand");
//			_nvqiangActionNames.push_back("nq_xfq");
			addChild(_nvqiangArmature);

			cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/wdj.ExportJson");
			_wudoujiaArmature = cocostudio::Armature::create("wdj");
			_wudoujiaArmature->getAnimation()->play("stand");
			_wudoujiaArmature->setPosition( Vec2(size.width / 2, size.height / 2-200) );
            _wudoujiaArmature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Main_City_Actor_Layer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
//			_wudoujiaActionNames.push_back("stand");
//			_wudoujiaActionNames.push_back("blq");
			addChild(_wudoujiaArmature);

			auto shadow = Sprite::create("img/scene/shadow.png");
			shadow->setAnchorPoint(Vec2(0.5, 0.5));
			shadow->setPosition(Vec2(size.width / 2, 110));
			addChild(shadow);
			//dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_37"))->setPosition(Vec2(277, 340));

			_outAction = ActionManagerEx::getInstance()->getActionByName("Create_Role.ExportJson", "move_out");

			auto animation = cocos2d::Animation::create();
			Value preFileName("create-role/effects/boom_");
			Value suffFileName(".png");
			for (int i = 0; i < 15; i++)
			{
				Value midFileName(i + 1);
				Value fileName(preFileName.asString() + midFileName.asString() + suffFileName.asString());
				animation->addSpriteFrameWithFileName(fileName.asString());
			}
			animation->setDelayPerUnit(0.7 / 15);
			//animation->setRestoreOriginalFrame(true);
			//animation->setLoops(true);
			auto animate = Animate::create(animation);
			auto func = CallFunc::create(CC_CALLBACK_0(Main_City_Actor_Layer::hideEffectSprite, this) );
			_effectSequence = Sequence::create(animate, func, nullptr);
			_effectSequence->retain();

			_roleImg = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_41"));
			_rolePosDefault = _roleImg->getPosition();
			auto pos = _rolePosDefault;
			auto posAdapt = Vec2(-150,0);
//			pos += posAdapt;
			_effectSprite = Sprite::create();
            _effectSprite->setScale(1.5);
			_effectSprite->setPosition(pos);
			_roleImg->getParent()->addChild(_effectSprite, _roleImg->getLocalZOrder() + 1);

			//job1 = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, "Button_32"));
   //         job1->addTouchEventListener(this, toucheventselector(Main_City_Actor_Layer::clickJob1));
			//auto head1 = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_105"));
			//head1->setTouchEnabled(true);
			//head1->addTouchEventListener(this, toucheventselector(Main_City_Actor_Layer::clickJob1));

			job2 = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, "Button_100"));
			job2->setHighlighted(false);
			job2->addTouchEventListener(this, toucheventselector(Main_City_Actor_Layer::clickJob2));

			job3 = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, "Button_100_0"));
			job3->setHighlighted(true);
			job3->addTouchEventListener(this, toucheventselector(Main_City_Actor_Layer::clickJob3));
   //         job2 = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, "Button_33"));
   //         job2->addTouchEventListener(this, toucheventselector(Main_City_Actor_Layer::clickJob2));
			//auto head2 = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_106"));
			//head2->setTouchEnabled(true);
			//head2->addTouchEventListener(this, toucheventselector(Main_City_Actor_Layer::clickJob2));

   //         job3 = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, "Button_34"));
   //         job3->addTouchEventListener(this, toucheventselector(Main_City_Actor_Layer::clickJob3));
			//auto head3 = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_107"));
			//head3->setTouchEnabled(true);
			//head3->addTouchEventListener(this, toucheventselector(Main_City_Actor_Layer::clickJob3));

   //         job4 = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, "Button_35"));
			//job4->setTouchEnabled(false);
   //         job4->addTouchEventListener(this, toucheventselector(Main_City_Actor_Layer::clickJob4));
			//auto head4 = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_108"));
			//head4->setTouchEnabled(false);
			//head4->addTouchEventListener(this, toucheventselector(Main_City_Actor_Layer::clickJob4));

   //         job5 = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, "Button_36"));
			//job5->setTouchEnabled(false);
   //         job5->addTouchEventListener(this, toucheventselector(Main_City_Actor_Layer::clickJob5));
			//auto head5 = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_109"));
			//head5->setTouchEnabled(false);
			//head5->addTouchEventListener(this, toucheventselector(Main_City_Actor_Layer::clickJob5));

        }
    }
    
    void Main_City_Actor_Layer::loadSelectRoleSexList()
    {
        
        CC_ASSERT(m_pUILayer);
        if (m_pUILayer)
        {
            //m_pSelectState = cocos2d::Sprite::create();
            //Effect_Cfg_Data_Mgr::instance()->get_effect(m_pSelectState, "3007");
            //m_pUILayer->addChild(m_pSelectState, 10);
            
            cocos2d::ui::Button*	btn_random_name = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, "Button_39"));
            btn_random_name->addTouchEventListener(this, toucheventselector(Main_City_Actor_Layer::randomRoleName));
            
            nameTxt = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget, "Label_96"));
            //nameTxt->setString();
            /*cocos2d::ui::ImageView* img_roleMale = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "img_RoleBack_M"));
             img_roleMale->addTouchEventListener(this,toucheventselector(Main_City_Actor_Layer::clickMaleEventCallback));
             cocos2d::ui::ImageView* img_roleFemale = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "img_RoleBack_F"));
             img_roleFemale->addTouchEventListener(this,toucheventselector(Main_City_Actor_Layer::clickFemaleEventCallback));*/
            
            /*if(m_pSelectState)
             {
             m_pSelectState->setPosition(img_roleMale->getPosition());
             }*/
            
            //以下内容可显示角色的 骨骼动画
            //             cocos2d::ui::ImageView* img_roleChildM = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pUILayer,"img_male_avator"));
            //             cocos2d::ui::ImageView* img_roleChileF = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pUILayer,"img_female_avator"));
            //
            //             cocos2d::ui::Widget* maleNode = createNode(1);
            //             maleNode->setPosition(Vec2(img_roleChildM->getPosition().x+10, img_roleChildM->getPosition().y-110));
            //             img_roleMale->addChild(maleNode);
            //
            //             cocos2d::ui::Widget* femaleNode = createNode(2);
            //             femaleNode->setPosition(Vec2(img_roleChileF->getPosition().x, img_roleChileF->getPosition().y-130));
            //             img_roleFemale->addChild(femaleNode);
            
            cocos2d::ui::Button* buttonReturn = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, "btn_back"));
            // 			buttonReturn->setTouchEnabled(false);
            // 			buttonReturn->setVisible(false);
            //			buttonReturn->addTouchEventListener(this,toucheventselector(Main_City_Actor_Layer::createRoleBtnBackCallback));
            int family_name_id;
            const char* name_front;
            //cocos2d::ui::TextField* pEditBox;
            char name_f[32] = { 0 };
            int family_name_called_id = 0;
            char name_r[64] = { 0 };
            const char* name_rear;
            this->name;
            std::string family_name_called;
            std::string family_name;
            CCLOG(" random role name ");
            srand((unsigned)time(NULL));
            family_name_id = rand() % 264 + 1;
            CCLOG("family_name_id = %d", family_name_id);
            name_front = Name_Random_Mgr::get_instance()->get_name_by_id(family_name_id);
            
            memcpy(name_f, name_front, strlen(name_front) - 1);
            family_name = name_f;
            
            
            if (0 == m_sex) //随机女性名称
                family_name_called_id = rand() % (1808 - 1500) + 1501;
            if (1 == m_sex) //随机男性名称
                family_name_called_id = rand() % (956 - 500) + 501;
            
            CCLOG("family_name_called_id = %d", family_name_called_id);
            name_rear = Name_Random_Mgr::get_instance()->get_name_by_id(family_name_called_id);
            
            memcpy(name_r, name_rear, strlen(name_rear) - 1);
            family_name_called = name_r;
            
            name = family_name + family_name_called;
            CCLOG("name = %s", name.c_str());
            
            /*pEditBox = dynamic_cast<cocos2d::ui::TextField*>(Helper::seekWidgetByName(m_pWidget, "Image_38"));
             pEditBox->setText(name.c_str());*/
            nameTxt->setString(name.c_str());
            
        }
        
    }
    
    void Main_City_Actor_Layer::createRoleBtnBackCallback(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                m_pSelectState->setVisible(false);
                CCLog("-----------Create Role UI back button callback----------");
                CocoStu_UI_Scene_Interface::get_instance()->run_test(2006);
                loadRoleList();
                break;
            default:
                break;
        }
        
    }
    
    void Main_City_Actor_Layer::randomRoleName(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        int family_name_id;
        const char* name_front;
        //cocos2d::ui::TextField* pEditBox;
        char name_f[32] = { 0 };
        int family_name_called_id = 0;
        char name_r[64] = { 0 };
        const char* name_rear;
        this->name;
        std::string family_name_called;
        std::string family_name;
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                CCLOG(" random role name ");
                srand((unsigned)time(NULL));
                family_name_id = rand() % 264 + 1;
                CCLOG("family_name_id = %d", family_name_id);
                name_front = Name_Random_Mgr::get_instance()->get_name_by_id(family_name_id);
                
                memcpy(name_f, name_front, strlen(name_front) - 1);
                family_name = name_f;
                
                
                if (0 == m_sex) //随机女性名称
                    family_name_called_id = rand() % (1808 - 1500) + 1501;
                if (1 == m_sex) //随机男性名称
                    family_name_called_id = rand() % (956 - 500) + 501;
                
                CCLOG("family_name_called_id = %d", family_name_called_id);
                name_rear = Name_Random_Mgr::get_instance()->get_name_by_id(family_name_called_id);
                
                memcpy(name_r, name_rear, strlen(name_rear) - 1);
                family_name_called = name_r;
                
                name = family_name + family_name_called;
                CCLOG("name = %s", name.c_str());
                
                /*pEditBox = dynamic_cast<cocos2d::ui::TextField*>(Helper::seekWidgetByName(m_pWidget, "Image_38"));
                 pEditBox->setText(name.c_str());*/
                nameTxt->setString(name.c_str());
                break;
            default:
                break;
        }
        
    }
    
    cocos2d::ui::Widget* Main_City_Actor_Layer::createNode(int actor_id)
    {
#if 0
        Account_Data_Mgr* pADMgr = Account_Data_Mgr::instance();
        const Account_Data_Mgr::SRoleData& refData = pADMgr->m_RoleData[0];
        Json::Value& actor = Prototype_Cfg_Data_Mgr::shared_instance()->get_Prototype_cfg(actor_id);
        Json::Value &avatar = actor["avatar"];
        std::string skeleton_file = "spine_res/";
        skeleton_file += avatar["skeleton_data"].asString();
        std::string atals_file = "spine_res/";
        atals_file += avatar["atlas"].asString();
        
        SkeletonAnimation* pAvatar = SkeletonAnimation::createWithFile(skeleton_file.c_str(),atals_file.c_str(),1.0f);
        pAvatar->addAnimationState();
        pAvatar->timeScale = 1.0f;
        pAvatar->setAnimation("std",true);
#endif
        cocos2d::ui::Widget* pNode = cocos2d::ui::Widget::create();
        //pNode->addChild(pAvatar);
        return pNode;
        
    }
    
    void Main_City_Actor_Layer::clickMaleEventCallback(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        cocos2d::ui::ImageView* img_roleMale;
        cocos2d::ui::ImageView* img_rootBack;
        cocos2d::ui::ImageView* img_selectEffect;
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                img_roleMale = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "img_RoleBack_M"));
                img_rootBack = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "img_RootBack"));
                img_rootBack->loadTexture(CREATE_ROLE_MALE_BACK);
                //img_rootBack->loadTexture(CREATE_ROLE_MALE_BACK);
                
                img_selectEffect = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "img_select_effect_back"));
                img_selectEffect->setPosition(img_roleMale->getPosition());
                
                if (m_pSelectState)
                {
                    
                    m_pSelectState->setPosition(Vec2(img_roleMale->getPosition().x, img_roleMale->getPosition().y));
                }
                
                m_sex = 1;
                
                break;
            default:
                break;
        }
    }
    
    void Main_City_Actor_Layer::clickFemaleEventCallback(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        cocos2d::ui::ImageView* img_roleFemale;
        cocos2d::ui::ImageView* img_rootBack;
        cocos2d::ui::ImageView* img_selectEffect;
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                img_roleFemale = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "img_RoleBack_F"));
                img_rootBack = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "img_RootBack"));
                
                img_rootBack->loadTexture(CREATE_ROLE_FEMALE_BACK);
                img_selectEffect = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "img_select_effect_back"));
                img_selectEffect->setPosition(img_roleFemale->getPosition());
                
                if (m_pSelectState)
                {
                    m_pSelectState->setPosition(img_roleFemale->getPosition());
                }
                
                m_sex = 0;
                
                break;
            default:
                break;
        }
    }
    
    void Main_City_Actor_Layer::clickAServer(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                Button* bb = (Button*)pSender;
                Value idx(bb->getTag());
                std::string pre(idx.asString());
                std::string suff("Stage");
                pre += suff;
                Main_City_Actor_Layer::curSv->setString(pre.c_str());
            }
            default:
                break;
        }
    }
     
    void Main_City_Actor_Layer::clickJob1(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        switch (type)
		{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
			{
			}
				 break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                m_job = 1;

                //dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_37"))->setPosition(Vec2(277, 540));
				//dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_37"))->setPosition(Vec2(160, 540));
                job1->setHighlighted(true);
                job2->setHighlighted(false);
                //job3->setHighlighted(false);
                //job4->setHighlighted(false);
                //job5->setHighlighted(false);

				if (_isChanging)
					return;
				_isChanging = true;
				_outAction->play();
				this->_effectSprite->setVisible(true);
				_effectSprite->runAction(_effectSequence);

            }
                break;
            default:
                break;
        }
    }
    
    void Main_City_Actor_Layer::clickJob2(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                m_job = 2;
				//dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_37"))->setPosition(Vec2(277, 440));
				//dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_37"))->setPosition(Vec2(160, 440));
                //job1->setHighlighted(false);
                job2->setHighlighted(true);
                job3->setHighlighted(false);
                //job4->setHighlighted(false);
                //job5->setHighlighted(false);
				_nvqiangArmature->getAnimation()->play("nq_xfq");
//				_nvqiangArmature->getAnimation()->playWithNames(_nvqiangActionNames);
				_nvqiangArmature->setVisible(true);
				_wudoujiaArmature->setVisible(false);
				if (_isChanging)
					return;
				_isChanging = true;
				_outAction->play();
				this->_effectSprite->setVisible(true);
				_effectSprite->runAction(_effectSequence);

            }
                break;
            default:
                break;
        }
    }
    
    void Main_City_Actor_Layer::clickJob3(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                m_job = 3;
				//dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_37"))->setPosition(Vec2(277, 338));
				//dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_37"))->setPosition(Vec2(160, 338));
                //job1->setHighlighted(false);
                job2->setHighlighted(false);
                job3->setHighlighted(true);
                //job4->setHighlighted(false);
                //job5->setHighlighted(false);
				_nvqiangArmature->setVisible(false);
				_wudoujiaArmature->setVisible(true);
                
				_wudoujiaArmature->getAnimation()->play("blq");
				if (_isChanging)
					return;
				_isChanging = true;
				_outAction->play();
				this->_effectSprite->setVisible(true);
				_effectSprite->runAction(_effectSequence);
            }
                break;
            default:
                break;
        }
    }
    
    void Main_City_Actor_Layer::clickJob4(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                m_job = 4;
				//dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_37"))->setPosition(Vec2(277, 240));
				dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_37"))->setPosition(Vec2(160, 240));
                job1->setHighlighted(false);
                job2->setHighlighted(false);
                job3->setHighlighted(false);
                job4->setHighlighted(true);
                job5->setHighlighted(false);
				if (_isChanging)
					return;
				_isChanging = true;
				_outAction->play();
				this->_effectSprite->setVisible(true);
				_effectSprite->runAction(_effectSequence);
            }
                break;
            default:
                break;
        }
    }
    
    void Main_City_Actor_Layer::clickJob5(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                m_job = 5;
				//dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_37"))->setPosition(Vec2(277, 134));
				dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_37"))->setPosition(Vec2(160, 134));
                job1->setHighlighted(false);
                job2->setHighlighted(false);
                job3->setHighlighted(false);
                job4->setHighlighted(false);
                job5->setHighlighted(true);
				if (_isChanging)
					return;
				_isChanging = true;
				_outAction->play();
				this->_effectSprite->setVisible(true);
				_effectSprite->runAction(_effectSequence);
            }
                break;
            default:
                break;
        }
    }

	void Main_City_Actor_Layer::update(float dt)
	{
		if (_effectSequence != nullptr)
		{
			if (_effectSequence->isDone())
				_isChanging = false;
		}

		if (_outAction != nullptr&& _roleImg!=nullptr )
		{
			float cur = _outAction->getCurrentTime();
			float tot = _outAction->getTotalTime();
			if ((cur - tot) < 0.0f)
			{
				Value pre("create-role/role");
				Value mid(m_job);
				Value suff(".png");
				Value fileName( pre.asString()+mid.asString()+suff.asString() );
				_roleImg->loadTexture( fileName.asString() );
				_isReachMax = true;
			}

		}
		
	}

	void Main_City_Actor_Layer::hideEffectSprite()
	{
		this->_effectSprite->setVisible(false);
	}
    
    void Main_City_Actor_Layer::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
    {
        if (movementType == MovementEventType::COMPLETE)
        {
            if (movementID == "blq" || movementID == "nq_xfq") {
                armature->getAnimation()->play("stand");
            }
        }
    }
 
};