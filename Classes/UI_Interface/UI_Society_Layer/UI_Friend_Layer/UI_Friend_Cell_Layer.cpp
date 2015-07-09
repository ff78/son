#include "cocos2d.h"
#include <fstream>	
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Game_Interface/common.h"

#include "Relation_System/Relation_Common.h"
#include "Relation_System/Relation_Mgr.h"

#include "UI_Friend_Layer.h"
#include "UI_Friend_Cell_Layer.h"
using namespace ui;

UI_Friend_Cell_Layer::UI_Friend_Cell_Layer()
{
	m_nCurrentCellIndex		= 0;
	m_nCurrentCellRoleID	= 0;
}


UI_Friend_Cell_Layer::~UI_Friend_Cell_Layer()
{

}


bool UI_Friend_Cell_Layer::init()
{
	if (!Layout::init())
		return false;

	Widget* pLayer = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Social_Friend_Cell.json");
	this->addChild(pLayer);

	// 名字文本
	m_pNameText				= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Name_Text"));			

	// 等级文本
	m_pLevelText			= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Level_Text"));			

	// 战斗力文本
	m_pFighttingPowerText	= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Fightting_Power_Text"));			

	// 职业文本
	m_pJobText				= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Job_Text"));			

	// 选中框图片
	m_pSelectBoxImg			= dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Friend_SelectBox"));													

	// 背景图
	ui::ImageView* pBG		= dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "BG"));
	pBG->setTouchEnabled(true);
	pBG->addTouchEventListener(CC_CALLBACK_2(UI_Friend_Cell_Layer::OnBtnBGCallBack, this));

	return true;
}


void UI_Friend_Cell_Layer::onExit()
{
	Layout::onExit();
}


void UI_Friend_Cell_Layer::onEnter()
{
	Layout::onEnter();
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 页面刷新相关逻辑
void UI_Friend_Cell_Layer::RemoveCurrentCell()
{
	/************************************************************************/
	// 移除当前单元
	this->removeFromParent();
}

void UI_Friend_Cell_Layer::RequestCurrentCellShowInfo()
{
	/************************************************************************/
	// 获取当前单元的显示信息
	// 1. 从逻辑层获取显示信息
	TARGET_FRIEND_INFO_FOR_SHOW strData;
	if (!Relation_Manager::instance()->UIRequestFriendShowInfo(m_nCurrentCellRoleID, &strData))
		return;

	// 2. 显示信息
	m_pNameText->setString(strData.szFriendName);
	m_pLevelText->setString(CCString::createWithFormat("%d", strData.nFriendLevel)->getCString());
	m_pFighttingPowerText->setString(CCString::createWithFormat("%d", strData.nFriendFighttingPower)->getCString());
	m_pJobText->setString(strData.szFriendJobName);
}


void UI_Friend_Cell_Layer::CurrentCellBeSelected(const bool bValue /*= false*/)
{
	/************************************************************************/
	// 当前单元是否被选中
	// 设置选中框状态
	m_pSelectBoxImg->setVisible(bValue);
}


void UI_Friend_Cell_Layer::DeleteCurrentFriend()
{
	/************************************************************************/
	// 删除当前好友
	// 通知逻辑层请求删除好友
	Relation_Manager::instance()->UIRequestDeleteFriend(m_nCurrentCellRoleID);
}


void UI_Friend_Cell_Layer::AllowToAddFriend()
{
	/************************************************************************/
	// 允许添加好友
	// 通知逻辑层请求从申请列表添加好友
	Relation_Manager::instance()->UIRequestAddFriendFromApply(m_nCurrentCellRoleID);
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 按钮点击方法回调
void UI_Friend_Cell_Layer::OnBtnBGCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 背景图片点击回调		
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 通知父页面当前的Cell被选中
	UI_Friend_Layer *pLayer = dynamic_cast<UI_Friend_Layer*>(this->getParent()->getParent()->getParent()->getParent()->getParent());
	if (pLayer == NULL)
		return;

	pLayer->TargetCellBeSelected(m_nCurrentCellIndex);
}

