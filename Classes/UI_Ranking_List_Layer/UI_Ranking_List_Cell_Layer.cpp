#include "cocos2d.h"
#include <fstream>	
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Game_Interface/common.h"

#include "Rank_System/Rank_Data.h"
#include "Rank_System/Rank_Mgr_Cl.h"

#include "UI_Ranking_List_Layer.h"
#include "UI_Ranking_List_Cell_Layer.h"
using namespace ui;

UI_Ranking_List_Cell_Layer::UI_Ranking_List_Cell_Layer()
{
	m_nCurrentCellIndex		=	-1;
}


UI_Ranking_List_Cell_Layer::~UI_Ranking_List_Cell_Layer()
{

}


bool UI_Ranking_List_Cell_Layer::init()
{
	if (!Layout::init())
		return false;

	Widget* pLayer			= cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Rank_List_Cell.json");
	this->addChild(pLayer);													

	// 名次文本
	m_pRankingText			= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Rank_Title_Label"));

	// 名字文本
	m_pNameText				= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Name_Title_Label"));

	// 战斗力文本
	m_pChangeAttributeText	= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Change_Title_Label"));

	// 职业文本
	m_pJobText				= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Job_Title_Label"));

	// 选中框图片
	m_pSelectBoxImg			= dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Rank_Select_Box"));

	// 背景图
	ui::ImageView* pBG		= dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Ranl_List_Info_BG"));
	pBG->setTouchEnabled(true);
	pBG->addTouchEventListener(CC_CALLBACK_2(UI_Ranking_List_Cell_Layer::OnBtnBGCallBack, this));

	return true;
}


void UI_Ranking_List_Cell_Layer::onExit()
{
	Layout::onExit();
}


void UI_Ranking_List_Cell_Layer::onEnter()
{
	Layout::onEnter();
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 页面刷新相关逻辑
void UI_Ranking_List_Cell_Layer::RemoveCurrentCell()
{
	/************************************************************************/
	// 移除当前单元
	this->removeFromParent();
}


void UI_Ranking_List_Cell_Layer::RequestCurrentCellShowInfo()
{
	/************************************************************************/
	// 获取当前单元的显示信息
	// 1. 从逻辑层获取显示信息
	TARGET_INDEX_INFO_FOR_SHOW strData;
	if (!Rank_Manager::instance()->UIRequestTargetIndexShowInfo(m_nCurrentCellIndex, &strData))
		return;

	// 2. 显示信息
	m_pRankingText->setString(CCString::createWithFormat("%d", strData.nRanking)->getCString());
	m_pNameText->setString(strData.szTargetPlayerName);
	m_pChangeAttributeText->setString(CCString::createWithFormat("%d", strData.nAttributeValue)->getCString());
	m_pJobText->setString(strData.szTargetPlayerJobName);
}


void UI_Ranking_List_Cell_Layer::CurrentCellBeSelected(const bool bValue /*= false*/)
{
	/************************************************************************/
	// 当前单元是否被选中
	// 设置选中框状态
	m_pSelectBoxImg->setVisible(bValue);
}
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 按钮点击方法回调
void UI_Ranking_List_Cell_Layer::OnBtnBGCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 背景图片点击回调		
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 通知父页面当前的Cell被选中
	UI_Ranking_List_Layer *pLayer = dynamic_cast<UI_Ranking_List_Layer*>(this->getParent()->getParent()->getParent()->getParent()->getParent()->getParent());
	if (pLayer == NULL)
		return;

	pLayer->TargetCellBeSelected(m_nCurrentCellIndex);
}