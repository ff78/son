#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Game_Interface/common.h"
#include "Common/GameDefine.h"
#include "Network_Common/global_macros.h"

#include "Emai_System/Email_Client.h"
#include "Emai_System/Email_Common_Config_Data.h"

#include "UI_Friend_Layer/UI_Friend_Layer.h"
//#include "UI_Faction_Layer/FactionLayer.h"
#include "Faction_System/Faction_Client.h"

//#include "UI_Email_Layer/UI_Receive_Email_Layer.h"
//#include "UI_Email_Layer/UI_Send_Email_Layer.h"
#include "UI_Email_Layer/UI_Email_Layer.h"
#include "UI_Society_Layer.h"

using namespace ui;
using namespace cocos2d;
using namespace cocostudio;


UI_Society_Layer::UI_Society_Layer()
{
	m_eCurrentSociety_State		= Current_Society_Layer_State_Error;
}


UI_Society_Layer::~UI_Society_Layer()
{
	
}


bool UI_Society_Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	ui::Widget* pLayer = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Social/social.ExportJson");
	addChild(pLayer);

	// 关闭按钮
	ui::Button * pCloseBtn		= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Btn_Close"));
	pCloseBtn->setTouchEnabled(true);
	pCloseBtn->addTouchEventListener( this,toucheventselector(UI_Society_Layer::OnBtnCloseCallBack) );

	//ui::Text * pEmailText		= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Txt_Mail"));
	//pEmailText->setTouchEnabled(true);
	//pEmailText->addTouchEventListener( this, toucheventselector(UI_Society_Layer::OnBtnEmailCallBack) );

	_friendButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Btn_Friend"));
	_friendButton->setBrightStyle(BrightStyle::NORMAL);
	_friendButton->setTouchEnabled(true);
	_friendButton->addTouchEventListener( this, toucheventselector(UI_Society_Layer::OnBtnFriendCallBack) );

	//ui::Text * pFactionText		= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Txt_Guild"));
	//pFactionText->setTouchEnabled(true);
	//pFactionText->addTouchEventListener( this, toucheventselector(UI_Society_Layer::OnBtnFactionCallBack) );

	_guildButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Btn_Guild"));
	_guildButton->setBrightStyle(BrightStyle::NORMAL);
	_guildButton->setTouchEnabled(true);
	_guildButton->addTouchEventListener( this, toucheventselector(UI_Society_Layer::OnBtnFactionCallBack) );
	
	//ui::Text * pFriendText		= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Txt_Friend"));
	//pFriendText->setTouchEnabled(true);
	//pFriendText->addTouchEventListener( this, toucheventselector(UI_Society_Layer::OnBtnFriendCallBack) );

	_emailButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Btn_Email") );
	_emailButton->setBrightStyle(BrightStyle::HIGHLIGHT );
	_emailButton->setTouchEnabled(true);
	_emailButton->addTouchEventListener( this, toucheventselector(UI_Society_Layer::OnBtnEmailCallBack) );
	
	return true;
}


void UI_Society_Layer::onExit()
{
	Layer::onExit();

}


void UI_Society_Layer::onEnter()
{
	Layer::onEnter();
	// 默认打开好友界面
	//OpenTargetSocietyLayerState(Current_Society_Layer_State_Friend);
	OpenTargetSocietyLayerState(Current_Society_Layer_State_Email);

}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 页面刷新相关逻辑
void UI_Society_Layer::OpenTargetSocietyLayerState(const Current_Society_Layer_State eState)
{
	/************************************************************************/
	//// 开启目标社交界面
	//// 1. 关闭当前页面
	//switch (m_eCurrentSociety_State)
	//{
	//case Current_Society_Layer_State_Email:
	//{
	//	// 1. 获取当前的邮件界面状态
	//	Current_Email_Layer_State eState = Email_Manager::instance()->GetCurrentEmailLayerState();

	//	// 2. 根据当前的邮件界面状态,删除当前界面
	//	// 2_1. 如果当前处于所有邮件界面状态
	//	if (eState == Current_Email_Layer_State_All)
	//	{
	//		UI_Email_Layer * pLayer = dynamic_cast<UI_Email_Layer *>(this->getChildByTag(998));
	//		if (pLayer != NULL)
	//		{
	//			//pLayer->removeFromParent();
	//		}
	//	}
	//	// 2_2. 如果当前处于发送邮件界面状态
	//	else if (eState == Current_Email_Layer_State_Send)
	//	{
	//		//UI_Send_Email_Layer * pLayer = dynamic_cast<UI_Send_Email_Layer *>(this->getChildByTag(998));
	//		//if (pLayer != NULL)
	//		//{
	//		//	pLayer->removeFromParent();
	//		//}
	//	}
	//	// 2_1. 如果当前处于接收邮件界面状态
	//	else if (eState == Current_Email_Layer_State_Receive)
	//	{
	//		//UI_Receive_Email_Layer * pLayer = dynamic_cast<UI_Receive_Email_Layer *>(this->getChildByTag(998));
	//		//if (pLayer != NULL)
	//		//{
	//		//	pLayer->removeFromParent();
	//		//}
	//	}
	//	else
	//	{

	//	}
	//	
	//}
	//	break;
	//case Current_Society_Layer_State_Faction:
	//{
	//	//auto pLayer = dynamic_cast<FactionLayer*>(this->getChildByTag(Current_Society_Layer_State_Faction));
	//	auto pLayer = dynamic_cast<FACTION_VIEW*>(this->getChildByTag(Current_Society_Layer_State_Faction));	
	//	if (pLayer != NULL)
	//	{			
	//		//pLayer->removeFromParent();
	//	}

	//}
	//	break;
	//case Current_Society_Layer_State_Friend:
	//{
	//	UI_Friend_Layer * pLayer = dynamic_cast<UI_Friend_Layer *>(this->getChildByTag(998));
	//	if (pLayer != NULL)
	//	{
	//		pLayer->removeFromParent();
	//	}	
	//}
	//	break;
	//case Current_Society_Layer_State_Error:
	//	break;
	//default:
	//	break;
	//}
	auto email = this->getChildByTag(Current_Society_Layer_State_Email);
	if (email != nullptr)
		email->removeFromParent();

	auto faction = this->getChildByTag(Current_Society_Layer_State_Faction);
	if (faction != nullptr)
		faction->removeFromParent();

	auto frd = this->getChildByTag(Current_Society_Layer_State_Friend);
	if (frd != nullptr)
		frd->removeFromParent();

	// 2. 开启目标界面
	switch (eState)
	{
	case Current_Society_Layer_State_Email:
	{
		UI_Email_Layer * pLayer = UI_Email_Layer::create();
		pLayer->setTag(Current_Society_Layer_State_Email);
		this->addChild(pLayer);
	}
		break;
	case Current_Society_Layer_State_Faction:
	{
		FACTION_VIEW* pLayer = FACTION_VIEW::create();
		//FactionLayer* pLayer = FactionLayer::create();
		pLayer->setTag(Current_Society_Layer_State_Faction);
		this->addChild(pLayer);

	}
		break;
	case Current_Society_Layer_State_Friend:
	{
		UI_Friend_Layer * pLayer = UI_Friend_Layer::create();
		pLayer->setTag(Current_Society_Layer_State_Friend);
		this->addChild(pLayer);
	}
		break;
	case Current_Society_Layer_State_Error:
		break;
	default:
		break;
	}

	// 3. 记录当前的页面状态
	if (eState < Current_Society_Layer_State_Email || eState >= Current_Society_Layer_State_Error)
		return;
	
	m_eCurrentSociety_State = eState;
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 按钮点击方法回调	
void UI_Society_Layer::OnBtnCloseCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 点击关闭件按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 关闭当前界面
	this->removeAllChildren();
	this->removeFromParent();
}

void UI_Society_Layer::OnBtnEmailCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 点击邮件按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;
	_emailButton->setBrightStyle(BrightStyle::HIGHLIGHT);
	_friendButton->setBrightStyle(BrightStyle::NORMAL);
	_guildButton->setBrightStyle(BrightStyle::NORMAL);

	// 1. 如果当前界面状态是邮件界面则不进行任何操作
	if (m_eCurrentSociety_State == Current_Society_Layer_State_Email)
		return;

	// 2. 创建邮件界面
	OpenTargetSocietyLayerState(Current_Society_Layer_State_Email);
}

void UI_Society_Layer::OnBtnFactionCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 点击公会按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;
	_emailButton->setBrightStyle(BrightStyle::NORMAL);
	_friendButton->setBrightStyle(BrightStyle::NORMAL);
	_guildButton->setBrightStyle(BrightStyle::HIGHLIGHT);
	// 1. 如果当前界面状态是公会界面则不进行任何操作
	if (m_eCurrentSociety_State == Current_Society_Layer_State_Faction)
		return;

	// 2. 创建公会界面
	OpenTargetSocietyLayerState(Current_Society_Layer_State_Faction);
}

void UI_Society_Layer::OnBtnFriendCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 点击好友按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;
	_emailButton->setBrightStyle(BrightStyle::NORMAL);
	_friendButton->setBrightStyle(BrightStyle::HIGHLIGHT);
	_guildButton->setBrightStyle(BrightStyle::NORMAL);
	// 1. 如果当前界面状态是好友界面则不进行任何操作
	if (m_eCurrentSociety_State == Current_Society_Layer_State_Friend)
		return;

	// 2. 创建好友界面
	OpenTargetSocietyLayerState(Current_Society_Layer_State_Friend);
}