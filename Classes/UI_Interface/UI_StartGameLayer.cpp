#include "UI_StartGameLayer.h"
#include "UI/Login_Scene.h"
#include "UI_Interface/CocoStu_UI_Scene_Interface.h"
#include "UI/Main_City_Scene.h"
#include "Player_Account/Account_Data.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "UI_Interface/UI_ModalDialogue_Layer.h"
#include "Player_Account/RecentlyServer.h"
#include "Game_Interface/game_content_interface.h"
#include "Common/GameDefine.h"
#include "Player_Account/Account_Logic.h"
#include "Common/VisibleRect.h"
#include "Common/Utils.h"

using namespace ui;

bool UI_StartGameLayer::init()
{
	bool ret=false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());

		setKeypadEnabled(true);

		m_pWidgetStartGame = dynamic_cast<Widget*>(cocostudio::GUIReader::shareReader()->widgetFromJsonFile("ui/Start_Game.json"));
		this->addChild(m_pWidgetStartGame);

		m_btnStartGame = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidgetStartGame, "Button_9"));
		if (m_btnStartGame)
			m_btnStartGame->addTouchEventListener(this, toucheventselector(UI_StartGameLayer::startGame));
		//m_btnStartGame->setTag(-1);

		////切换账号按钮
		//m_btnChangeAccount = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidgetStartGame, "btn_changeaccount"));
		//if (m_btnChangeAccount)
		//{
		//	m_btnChangeAccount->setPosition(Vec2(m_btnChangeAccount->getPosition().x - VisibleRect::cutLength(), m_btnChangeAccount->getPosition().y));
		//	m_btnChangeAccount->addTouchEventListener(this, toucheventselector(UI_StartGameLayer::changeAccount));
		//}
		////查看所有服务器
		m_btnSeeAllServer = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidgetStartGame, "Label_12"));
		if (m_btnSeeAllServer)
			m_btnSeeAllServer->addTouchEventListener(this, toucheventselector(UI_StartGameLayer::seeAllServer));

		//退出按钮
		m_btnExit = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidgetStartGame, "Button_13"));
		m_btnExit->addTouchEventListener(this, toucheventselector(UI_StartGameLayer::goExit));

		ret=true;

	} while (0);
	return ret;
}
void UI_StartGameLayer::startGame(Ref* pSender, Widget::TouchEventType type)
{
	cocos2d::ui::Button* btn;
	int config_id;
	vector<uint64> para;
	const char* exitInfo;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		btn = dynamic_cast<cocos2d::ui::Button*>(pSender);
		if (btn->getTag() != -1)
		{
			//进入游戏
			config_id = btn->getTag();

			para.push_back(config_id);
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
		else
		{
			//提示选择服务器
			exitInfo = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SERVER_ERROR);
			UI_ModalDialogue_Layer::DoModal("", exitInfo, UI_ModalDialogue_Layer::DT_OK, [&](){});
		}
		break;
	default:
		break;
	}

}

void UI_StartGameLayer::changeAccount(Ref* pSender, Widget::TouchEventType type)
{
	Scene* sc;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		sc = Login_Scene::create();
		if (sc)
		{
			Director::getInstance()->replaceScene(sc);
		}

		break;
	default:
		break;
	}
}

void UI_StartGameLayer::seeAllServer(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		CocoStu_UI_Scene_Interface::get_instance()->run_test(2003);
		UI::Main_City_Actor_Layer::get_instance()->loadServerList();

	}
		break;
	default:
		break;
	}
}

void UI_StartGameLayer::goExit(Ref* pSender, Widget::TouchEventType type)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void UI_StartGameLayer::setServerStateUI(Server_List_Data sld)
{
	if (m_labserverName)
		m_labserverName->setString(sld.get_server_name());
	m_btnStartGame->setTag(sld.get_id());
	//设置火爆和推荐
	if (sld.get_state() == Server_List_Data::STATE_HOT)
	{
		if (m_img_hot)
			m_img_hot->setVisible(true);
		if (m_img_hot_red)
			m_img_hot_red->setVisible(true);
		if (m_img_recomend)
			m_img_recomend->setVisible(false);
		if (m_img_recomend_green)
			m_img_recomend_green->setVisible(false);
	}
	if (sld.get_state() == Server_List_Data::STATE_RECOMEND)
	{
		if (m_img_hot)
			m_img_hot->setVisible(false);
		if (m_img_hot_red)
			m_img_hot_red->setVisible(false);
		if (m_img_recomend)
			m_img_recomend->setVisible(true);
		if (m_img_recomend_green)
			m_img_recomend_green->setVisible(true);
	}
}
#if 0
void UI_StartGameLayer::keyBackClicked()
{
	const char* exitInfo = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SURE_TO_EXIT_GAME);
	UI_ModalDialogue_Layer::DoModal("", exitInfo, UI_ModalDialogue_Layer::DT_YES_NO, [&]()
	{ 
		this->btnCallBackExit(); 
	} 
	);
}
#endif
void UI_StartGameLayer::btnCallBackExit()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}