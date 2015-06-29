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
#include "UI_Interface/MyEditBox.h"

using namespace ui;
using namespace cocos2d;
using namespace cocostudio;

UI_Send_Email_Layer::UI_Send_Email_Layer()
{

}


UI_Send_Email_Layer::~UI_Send_Email_Layer()
{

}


bool UI_Send_Email_Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	_root			= cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Social_Send_Email/Social_Send_Email.ExportJson");
	addChild(_root);
	auto contentTxt = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(_root, "Email_Content_Text"));
	_contentToSend = contentTxt->getString();
	
	auto name = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(_root, "Receiver_Name_Text"));
	name->setVisible(false);
	Vec2 namePosition = name->getPosition();
	auto nameBox = SearchEditBox::create();
	nameBox->SetPositionAndMaxLength(-100, namePosition.y, 200);
	addChild(nameBox, 1,"box");

	Size size(600,250);
	auto content = CommonEditBox::create(size);
	content->SetPositionAndMaxLength(-60, contentTxt->getPosition().y + 50, 280);
	addChild(content,1,"content");

	// 收件箱按钮
	ui::Button * pAllEmailBtn = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(_root, "All_Email_Button"));
	pAllEmailBtn->setTouchEnabled(true);
	pAllEmailBtn->addTouchEventListener(this, toucheventselector(UI_Send_Email_Layer::OnBtnAllEmailCallBack));

	// 发送邮件按钮
	ui::Button * pSendEmailBtn = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(_root, "Send_Email_Button"));
	pSendEmailBtn->setTouchEnabled(true);
	pSendEmailBtn->addTouchEventListener(this, toucheventselector(UI_Send_Email_Layer::OnBtnSendEmailCallBack));

	return true;
}


void UI_Send_Email_Layer::onExit()
{
	Layer::onExit();
}


void UI_Send_Email_Layer::onEnter()
{
	Layer::onEnter();

	// 1. 通过逻辑层更换当前邮件页面状态
	EMAIL_MODEL::instance()->SetCurrentEmailLayerState(Current_Email_Layer_State_Send);

}

void UI_Send_Email_Layer::OnBtnSendEmailCallBack(Ref* pSender, Widget::TouchEventType type)
{

	if (type != Widget::TouchEventType::ENDED)
		return;
	std::vector<uint64> para;
	auto name = (SearchEditBox*)this->getChildByName("box");
	EMAIL_MODEL::instance()->setTargetNameToSend(name->getContent());
	auto content = (CommonEditBox*)this->getChildByName("content");
	EMAIL_MODEL::instance()->setMsgToSend(content->getContent());
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_EMAIL_SEND_SEND, para);
}

void UI_Send_Email_Layer::OnBtnAllEmailCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 收件箱按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 1. 打开发邮件界面
	UI_Society_Layer * pLayer = dynamic_cast<UI_Society_Layer *>(this->getParent());
	if (pLayer == NULL)
		return;

	UI_Email_Layer * pAllEmailLayer = UI_Email_Layer::create();
	pAllEmailLayer->setTag(998);
	pLayer->addChild(pAllEmailLayer);

	// 2. 删除当前界面
	this->removeFromParent();
}

void UI_Send_Email_Layer::setNameAndContent()
{
	auto nameBox = (SearchEditBox*)getChildByName("box");
	auto contentBox = (CommonEditBox*)getChildByName("content");
	auto detailData = (Email_Detail_Data_For_Show)EMAIL_MODEL::instance()->getDetailData().at( EMAIL_MODEL::instance()->getCurrentIndex() );
	
	nameBox->setContent( detailData.szSenderName.c_str() );
	contentBox->setContent( detailData.szContent.c_str() );

}