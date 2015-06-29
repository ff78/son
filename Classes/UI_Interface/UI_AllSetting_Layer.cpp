#include "UI_AllSetting_Layer.h"
#include "Common/GameDefine.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "UI_ModalDialogue_Layer.h"
#include "Platform_Dependence/Dependence.h"
#include "UI_Interface/UI_Public_Announcement.h"
#include "UI/Loading_Scene.h"
#include "UI/Login_Scene.h"
#include "Joiner_Guidance.h"
#include "UI_Interface/UI_MainMenu_Layer.h"
#include "Item_System/Item_Desc_Config_Mgr.h"

using namespace ui;
UI_AllSetting_Layer::UI_AllSetting_Layer(void):
	m_pSystemSetting(NULL)
{
}


UI_AllSetting_Layer::~UI_AllSetting_Layer(void)
{
}
bool UI_AllSetting_Layer::init()
{
	bool ret=false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());
		m_pwidget=cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Setting_All/Setting_All.ExportJson");
		addChild(m_pwidget);
		

		m_pButtonSystemSetting=dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pwidget,"btn_system_settings"));
		


		m_pButtonSystemSetting->addTouchEventListener(this,toucheventselector(UI_AllSetting_Layer::btnCallBackSystemSetting));

		m_close_settingall=dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pwidget,"btn_close"));
		m_close_settingall->addTouchEventListener(this,toucheventselector(UI_AllSetting_Layer::btnCallBackClose));

		m_pButtonAccountManage=dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pwidget,"btn_account_manage"));
		m_pButtonAccountManage->addTouchEventListener(this,toucheventselector(UI_AllSetting_Layer::btnCallBackAccountSetting));

		m_pButtonGoBackToLogin=dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pwidget,"btn_goback_to_login"));
		m_pButtonGoBackToLogin->addTouchEventListener(this,toucheventselector(UI_AllSetting_Layer::btnCallBackGoBackToLogin));

		m_pStratergy_Guaide=dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pwidget,"btn_strategy_guide"));
		m_pStratergy_Guaide->addTouchEventListener(this,toucheventselector(UI_AllSetting_Layer::btnCallBackStratergy));

	
		m_pButtonShowServer=dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pwidget,"btn_coustomer_server"));
		m_pButtonShowServer->addTouchEventListener(this,toucheventselector(UI_AllSetting_Layer::btnCallBackShowServer));

		lab_name_item=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pwidget,"lab_name_item"));
		const char* textfunction=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SYSTEM_FUNCTION);
		lab_name_item->setString(textfunction);

		lab_system_setting=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pwidget,"lab_system_settings"));
		const char* txetsysset=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SYSTEM_SETTING);
		lab_system_setting->setString(txetsysset);

		lab_account_manage=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pwidget,"lab_account_manage"));
		const char* textaccount=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ACCOUNT_MANAGE);
		lab_account_manage->setString(textaccount);

		lab_goback_to_login=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pwidget,"lab_goback_to_login"));
		const char* txetlogin=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(GOBACK_TO_LOGIN);
		lab_goback_to_login->setString(txetlogin);

		lab_strategy_guide=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pwidget,"lab_strategy_guide"));
		const char* textstrategy=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(STRATEGY_GUIDE);
		lab_strategy_guide->setString(textstrategy);

		lab_game_notice=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pwidget,"lab_game_notice"));
		const char* textnotice=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(GAME_NOTICE);
		lab_game_notice->setString(textnotice);

		lab_show_server=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pButtonShowServer,"Label"));
		const char* textserver=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(GAME_SERVER_FOR_CLIENT);
		lab_show_server->setString(textserver);
		
		btn_public_annoucement_ =  dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pwidget,"btn_game_notice")); 
		btn_public_annoucement_->addTouchEventListener(this,toucheventselector(UI_AllSetting_Layer::btnCallBackShowPublicAnnoucement));


		ret=true;
	} while (0);
	return ret;
}

void UI_AllSetting_Layer::setVisible(bool visible)
{
	cocos2d::Layer::setVisible(visible);
	if (visible)
	{
		Joiner_Guidance::hideGuide();
	}
	else
	{
//		UI_MainMenu_Layer::get_instance()->showGuide();
	}
}


//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
// 按钮点击回调
void UI_AllSetting_Layer::btnCallBackSystemSetting(Ref* pSender,Widget::TouchEventType type)
{
	/************************************************************************/
	// 系统设置按钮点击回调
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
		return;
	
	if (!m_pSystemSetting)
	{
		m_pSystemSetting = UI_SystemSetting_Layer::create();
		addChild(m_pSystemSetting, 10, UI_SYSTEMSETTING);
	}
	else
	{
		m_pSystemSetting->setVisible(true);
	}
}


void UI_AllSetting_Layer::btnCallBackClose(Ref* pSender,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	CCLog("close ------------------");
	setVisible(false);

	break;
    default:
	break;
}
}


void UI_AllSetting_Layer::btnCallBackAccountSetting(Ref* pSender,Widget::TouchEventType type)
{
	
}
void UI_AllSetting_Layer::btnCallBackGoBackToLogin(Ref* pSender,Widget::TouchEventType type)
{
	// 现在的版本点击返回登陆程序会宕机
	// ...
	return;

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
void UI_AllSetting_Layer::btnCallBackShowServer(Ref* pSender,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
#if 0//(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//	Dependence::showGameCenter();
#endif

	break;
    default:
	break;
}

}

void UI_AllSetting_Layer::btnCallBackShowPublicAnnoucement( Ref* pSender,Widget::TouchEventType type )
{
	/************************************************************************/
	// 游戏公告按钮点击回调
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
		return;

	this->setVisible(false);
	//this->removeFromParent();

	CCLayer * pMainMenuLayer = dynamic_cast<Layer*>(Director::getInstance()->getRunningScene()->getChildByTag(UI::TAG_BTN_UI));
	if (pMainMenuLayer == NULL)
		return;
	
	cocos2d::Layer * pAnnoucementLayer = dynamic_cast<Layer*>(pMainMenuLayer->getChildByTag(UI::TAG_PUBLIC_ANNOUCEMENT));
	if (pAnnoucementLayer == NULL)
	{
		pAnnoucementLayer = UI_Public_Announcement::create();
		if (pAnnoucementLayer == NULL)
			return;

		Director::getInstance()->getRunningScene()->getChildByTag(UI::TAG_BTN_UI)->addChild(pAnnoucementLayer, 20, UI::TAG_PUBLIC_ANNOUCEMENT);
	}
	pAnnoucementLayer->setVisible(true);
}


void UI_AllSetting_Layer::btnCallBackStratergy(Ref* pSender,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
#if 0//(CC_PLATFORM_ANDROID==CC_TARGET_PLATFORM)
//	Dependence::showAd();
#endif
	DICTIONARY_CONFIG_MGR::instance()->show_alert(FUNCTION_WITHOUT);

	break;
    default:
	break;
}
}
