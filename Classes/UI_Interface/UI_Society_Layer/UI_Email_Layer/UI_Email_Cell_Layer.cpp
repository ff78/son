#include "cocos2d.h"
#include <fstream>	
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Game_Interface/common.h"

#include "Emai_System/Email_Common_Config_Data.h"
#include "Emai_System/Email_Client.h"

#include "Relation_System/Relation_Common.h"
#include "Relation_System/Relation_Mgr.h"

#include "UI_Email_Layer.h"
#include "UI_Email_Cell_Layer.h"
using namespace ui;

UI_Email_Cell_Layer::UI_Email_Cell_Layer()
{
	m_nCurrentCellIndex			= 0;


	m_bCurrentCellBeSelected	= false;
}


UI_Email_Cell_Layer::~UI_Email_Cell_Layer()
{

}


bool UI_Email_Cell_Layer::init()
{
	if (!Layout::init())
		return false;

	Widget* pLayer		= cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Social_Email_Cell/Social_Email_Cell.ExportJson");
	this->addChild(pLayer);

	// 名字文本
	m_pNameText			= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Name_Text"));	

	// 内容文本
	m_pContentText		= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Content_Text"));	

	// 日期文本
	m_pDateText			= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Date_Text"));

	// 天数文本
	m_pDaysText			= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Days_Text"));														

	// 是否为官方图片
	m_pOfficialImg		= dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Official_Img"));		

	// 是否被阅读图片
	m_pBeReadImg		= dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Be_Read_Img"));					

	// 选中框图片
	m_pSelectBoxImg		= dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Friend_SelectBox"));
	m_pSelectBoxImg->setVisible(false);
	// 附件图片
	m_pPresentImg		= dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Present_Img"));

	ui::ImageView* pBG	= dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "BG"));
	pBG->setTouchEnabled(true);
	pBG->addTouchEventListener(CC_CALLBACK_2(UI_Email_Cell_Layer::OnBtnBGCallBack, this));

	return true;
}

void UI_Email_Cell_Layer::eventShowOpen()
{
	UI_Email_Layer *pLayer = dynamic_cast<UI_Email_Layer*>(this->getParent()->getParent()->getParent()->getParent()->getParent());
	if (pLayer == NULL)
		return;
	pLayer->TargetCellRequestOpenReceiveEmailLayer();

}

void UI_Email_Cell_Layer::onExit()
{
	Layout::onExit();
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_EMAIL_SHOW_OPEN);

}


void UI_Email_Cell_Layer::onEnter()
{
	Layout::onEnter();

	Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_EMAIL_SHOW_OPEN, CC_CALLBACK_0(UI_Email_Cell_Layer::eventShowOpen, this));

}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 页面刷新相关逻辑
void UI_Email_Cell_Layer::CurrentCellBeSelected(const bool bValue /*= false*/)
{
	/************************************************************************/
	// 当前单元是否被选中
	// 1. 设置选中框状态
	m_pSelectBoxImg->setVisible(bValue);

	// 2. 记录当前单元是否被选中的状态
	m_bCurrentCellBeSelected	= bValue;
}


void UI_Email_Cell_Layer::RemoveCurrentCell()
{
	/************************************************************************/
	// 移除当前单元
	this->removeFromParent();
}


void UI_Email_Cell_Layer::RequestCurrentCellShowInfo()
{
	/************************************************************************/
	// 获取当前单元的显示信息
	// 1. 从逻辑层获取简单显示信息
	if (!EMAIL_MODEL::instance()->UIRequestTargetIndexShowInfo(m_nCurrentCellIndex))
		return;

	// 2. 显示信息
	auto data = EMAIL_MODEL::instance()->getSimpleData();
	m_pOfficialImg->setVisible(data[m_nCurrentCellIndex].bIsOfficialEmail);
	m_pBeReadImg->setVisible(data[m_nCurrentCellIndex].bIsRead);
	m_pNameText->setString(data[m_nCurrentCellIndex].szSenderName.c_str());
	m_pContentText->setString(data[m_nCurrentCellIndex].szTitle.c_str());
	m_pDateText->setString(data[m_nCurrentCellIndex].szCreatTime.c_str());
}
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 按钮点击方法回调

void UI_Email_Cell_Layer::OnBtnBGCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 背景图片点击回调		
	if (type != Widget::TouchEventType::ENDED)
		return;
	auto scrollView = (ui::ScrollView*)this->getParent();
	auto children = scrollView->getChildren();
	cocos2d::Vector<Node*>::iterator iterator = children.begin();
	int count = 0;
	for (; iterator != children.end();iterator++)
	{
		UI_Email_Cell_Layer* cell = (UI_Email_Cell_Layer*)(*iterator);
		cell->m_pSelectBoxImg->setVisible(false);

		count++;
	}
	m_pSelectBoxImg->setVisible(true);
	int index = this->m_pNameText->getTag();
	int  id = this->getTag();
	EMAIL_MODEL::instance()->setCurrentIndex(index);
	EMAIL_MODEL::instance()->setCurrentEmailId(id);

}