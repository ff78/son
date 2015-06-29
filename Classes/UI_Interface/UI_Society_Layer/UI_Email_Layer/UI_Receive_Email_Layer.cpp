#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Game_Interface/common.h"
#include "Common/GameDefine.h"
#include "Network_Common/global_macros.h"

#include "Emai_System/Email_Common_Config_Data.h"
#include "Emai_System/Email_Client.h"

#include "../UI_Society_Layer.h"
#include "UI_Email_Layer.h"
#include "UI_Send_Email_Layer.h"
#include "UI_Receive_Email_Layer.h"

using namespace ui;
using namespace cocos2d;
using namespace cocostudio;

UI_Receive_Email_Layer::UI_Receive_Email_Layer()
{
	m_nCurrentEmailIndex = 0;
}


UI_Receive_Email_Layer::~UI_Receive_Email_Layer()
{

}


bool UI_Receive_Email_Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	ui::Widget* pLayer				= cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Social_Receive_Email/Social_Receive_Email.ExportJson");
	addChild(pLayer);

	// 收件箱按钮
	ui::Button * pAllEmailBtn		= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "All_Email_Button"));
	pAllEmailBtn->setTouchEnabled(true);
	pAllEmailBtn->addTouchEventListener(this, toucheventselector(UI_Receive_Email_Layer::OnBtnAllEmailCallBack));

	// 回信按钮
	ui::Button * pSendEmailBtn		= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Write_Back_Email_Button"));
	pSendEmailBtn->setTouchEnabled(true);
	pSendEmailBtn->addTouchEventListener(this, toucheventselector(UI_Receive_Email_Layer::OnBtnSendEmailCallBack));

	// 领取附件按钮
	ui::Button * pReceivePresentBtn = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Receive_Present_Button"));
	pReceivePresentBtn->setTouchEnabled(true);
	pReceivePresentBtn->addTouchEventListener(this, toucheventselector(UI_Receive_Email_Layer::OnBtnReceivePresentCallBack));

	// 删除按钮
	ui::Button * pDeleteEmailBtn	= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Delete_Email_Button"));
	pDeleteEmailBtn->setTouchEnabled(true);
	pDeleteEmailBtn->addTouchEventListener(this, toucheventselector(UI_Receive_Email_Layer::OnBtnDeleteEmailCallBack));

	// 寄信人名字文本
	m_pWriterNameText				= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Writer_Name_Text"));

	// 内容天数文本
	m_pContentText					= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Email_Content_Text"));

	return true;
}


void UI_Receive_Email_Layer::onExit()
{
	Layer::onExit();
}


void UI_Receive_Email_Layer::onEnter()
{
	Layer::onEnter();

	// 1. 通过逻辑层更换当前邮件页面状态
	EMAIL_MODEL::instance()->SetCurrentEmailLayerState(Current_Email_Layer_State_Receive);

	// 2. 刷新当前界面
	RefreshCurrentLayer();
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 页面刷新相关逻辑
void UI_Receive_Email_Layer::RefreshCurrentLayer()
{
	/************************************************************************/
	// 刷新当前界面
	// 1. 从逻辑层获取详细单显示信息
	//Email_Detail_Data_For_Show strData;
	if (!EMAIL_MODEL::instance()->UIRequestTargetIndexDetailShowInfo(m_nCurrentEmailIndex, NULL))
		return;

	// 2. 显示信息
	auto data = EMAIL_MODEL::instance()->getDetailData()[m_nCurrentEmailIndex];
	m_pWriterNameText->setString( data.szSenderName.c_str() );
	m_pContentText->setString( data.szContent.c_str() );
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 按钮点击方法回调	
void UI_Receive_Email_Layer::OnBtnAllEmailCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 收件箱按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 1. 打开邮件列表界面
	UI_Society_Layer * pLayer = dynamic_cast<UI_Society_Layer *>(this->getParent());
	if (pLayer == NULL)
		return;

	UI_Email_Layer * pEmailLayer = UI_Email_Layer::create();
	pEmailLayer->setTag(998);
	pLayer->addChild(pEmailLayer);

	// 2. 删除当前界面
	this->removeFromParent();
}

void UI_Receive_Email_Layer::OnBtnSendEmailCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 回信按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 1. 打开发送邮件界面
	UI_Society_Layer * pLayer = dynamic_cast<UI_Society_Layer *>(this->getParent());
	if (pLayer == NULL)
		return;

	UI_Send_Email_Layer * pSendEmailLayer = UI_Send_Email_Layer::create();
	pSendEmailLayer->setNameAndContent();
	pSendEmailLayer->setTag(998);
	pLayer->addChild(pSendEmailLayer);

	// 2. 删除当前界面
	this->removeFromParent();
}

void UI_Receive_Email_Layer::OnBtnReceivePresentCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 领取附件按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;
}

void UI_Receive_Email_Layer::OnBtnDeleteEmailCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 删除按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 1. 通知逻辑层删除目标邮件
	EMAIL_MODEL::instance()->UIRequestDeleteTargetIndexEmail(m_nCurrentEmailIndex);

	// 2. 关闭当前界面
	this->removeFromParent();
}
