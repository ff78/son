#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Game_Interface/common.h"
#include "Common/GameDefine.h"
#include "Network_Common/global_macros.h"

#include "Item_System/Item_Config_Mgr.h"

#include "Rank_System/Rank_Data.h"
#include "Rank_System/Rank_Mgr_Cl.h"

#include "UI_Ranking_List_Cell_Layer.h"
#include "UI_Ranking_List_Layer.h"

#define ranking_list_row 6

using namespace ui;
using namespace cocos2d;
using namespace cocostudio;

UI_Ranking_List_Layer::UI_Ranking_List_Layer()
{
	m_nCellHeight					=	0;
	m_nCurrentCellCount				=	0;
	m_nCurrentCellIndex				=	-1;

	m_pChangeTitleText				=	NULL;
}


UI_Ranking_List_Layer::~UI_Ranking_List_Layer()
{
	CC_SAFE_DELETE_ARRAY(m_pChangeTitleText);
}


bool UI_Ranking_List_Layer::init()
{
	if (!Layer::init())
		return false;

	ui::Widget* pLayer				= cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Rank_List.json");
	addChild(pLayer);

	// 竞技场按钮
	m_pPVPBtn						= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "PVP_Btn"));
	m_pPVPBtn->setTouchEnabled(true);
	m_pPVPBtn->addTouchEventListener(CC_CALLBACK_2(UI_Ranking_List_Layer::OnBtnPVPCallBack, this));

	// 等级按钮
	m_pLevelBtn						= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Level_Btn"));
	m_pLevelBtn->setTouchEnabled(true);
	m_pLevelBtn->addTouchEventListener(CC_CALLBACK_2(UI_Ranking_List_Layer::OnBtnLevelCallBack, this));

	// 战斗力按钮
	m_pFightingPowerBtn				= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Power_Btn"));
	m_pFightingPowerBtn->setTouchEnabled(true);
	m_pFightingPowerBtn->addTouchEventListener(CC_CALLBACK_2(UI_Ranking_List_Layer::OnBtnFightingPowerCallBack, this));

	// 金钱按钮
	m_pMoneyBtn						= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Money_Btn"));
	m_pMoneyBtn->setTouchEnabled(true);
	m_pMoneyBtn->addTouchEventListener(CC_CALLBACK_2(UI_Ranking_List_Layer::OnBtnMoneyCallBack, this));

	// 声望按钮
	m_pRenownBtn					= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Renown_Btn"));
	m_pRenownBtn->setTouchEnabled(true);
	m_pRenownBtn->addTouchEventListener(CC_CALLBACK_2(UI_Ranking_List_Layer::OnBtnRenownCallBack, this));

	// 关闭按钮
	m_pCloseBtn						= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Close_Btn"));
	m_pCloseBtn->setTouchEnabled(true);
	m_pCloseBtn->addTouchEventListener(CC_CALLBACK_2(UI_Ranking_List_Layer::OnBtnCloseCallBack, this));

	// 目标排名玩家排名名次文本
	m_pTargetRankingText			= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Target_Rank_Number_Label"));

	// 玩家自己排名名次文本
	m_pMyRankingText				= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Me_Rank_Number_Label"));

	// 剩余时间文本
	m_pRemainTimeText				= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Me_Remain_Label"));

	// 目标排行奖励图片
	m_pTargetRankingPresentImg		= dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Target_Present_Img"));

	// 玩家自己的排行奖励图片
	m_pMyRankingPresentImg			= dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Me_Present_Img"));

	// 排行榜滚动层
	m_pRankingListScrollView		= dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(pLayer, "Ranking_List_ScrollView"));

	// 我的排名界面
	m_pMyRankingPanel				= dynamic_cast<ui::Layout*>(Helper::seekWidgetByName(pLayer, "Me_Ranking_Other_Info_Panel"));

	// 会改变标题文本
	char strTemp[32]	= { 0 };
	m_pChangeTitleText	= new Text * [int(Rank_Type_Error)];
	for (int nIndex = 0; nIndex < int(Rank_Type_Error); ++nIndex)
	{
		// 技能图片的状态
        std::string s("Change_Title_Label_");
        Value v(nIndex + 1);
        s += v.asString();

		m_pChangeTitleText[nIndex] = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, s));
	}

	// 获得单元的高度
	int nWholeHeight				= m_pRankingListScrollView->getInnerContainerSize().height;
	m_nCellHeight					= nWholeHeight / ranking_list_row;
	
	return true;
}


void UI_Ranking_List_Layer::onExit()
{
	unschedule(schedule_selector(UI_Ranking_List_Layer::UpdateRankingListIsChange));

	Layer::onExit();
}


void UI_Ranking_List_Layer::onEnter()
{
	Layer::onEnter();

	// 默认进入竞技场排行榜界面
	EnterTargetRankLayer(Rank_Type_PVP);

	// 开启Updata刷新界面
	schedule(schedule_selector(UI_Ranking_List_Layer::UpdateRankingListIsChange), 0.1f);
}


void UI_Ranking_List_Layer::UpdateRankingListIsChange(float dt)
{
	/************************************************************************/
	// 刷新排行榜数据是否改变
	// 1. 判断好友列表是否获取到
	if (!Rank_Manager::instance()->GetCurrentRankTypeIsChangeState())
		return;

	// 2. 更改状态
	Rank_Manager::instance()->SetCurrentRankTypeIsChangeState(false);

	// 3. 刷新界面
	RefreshWholeLayer();
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 页面刷新相关逻辑
void UI_Ranking_List_Layer::GetCurrentRankStateList(const Rank_Type eType)
{
	/************************************************************************/
	// 获取当前类型排行榜列表数据是否到
	Rank_Manager::instance()->RequestTargetRankTypeList(); 
}

void UI_Ranking_List_Layer::EnterTargetRankLayer(const Rank_Type eType)
{
	/************************************************************************/
	// 进入目标排行榜界面
	// 1. 通知逻辑层请求进入目标排行榜页面
	if (!Rank_Manager::instance()->UIRequestEnterTargetRankLayer(eType))
		return;

	// 2. 设置标题
	SetTitleStringByRankType(eType);

	// 3. 获取目标排行榜的数据列表
	GetCurrentRankStateList(eType);

	// 4. 刷新当前界面
	RefreshWholeLayer();
}

void UI_Ranking_List_Layer::RefreshWholeLayer()
{
	/************************************************************************/
	// 刷新当前整个界面
	// 1. 载入好友滚动层
	if (!LoadScrollView())
		return;

	// 2. 获取每个单元的显示信息
	GetEachCellShowInfo();										
	
	// 3. 设置选中状态(切换状态目标排行榜第一名为默认选中)
	TargetCellBeSelected(0);

	// 4. 请求玩家本身名次的简单信息
	RequestPlayerRankingSimpleInfo();
}


void UI_Ranking_List_Layer::RemoveAllCell()
{
	/************************************************************************/
	// 移除所有的好友单元
	// 移除每个Cell
	for (int nIndex = 0; nIndex < m_nCurrentCellCount; ++nIndex)
	{
		UI_Ranking_List_Cell_Layer * pCell = dynamic_cast<UI_Ranking_List_Cell_Layer*>(m_pRankingListScrollView->getChildByTag(nIndex));
		if (pCell == NULL)
			continue;

		pCell->RemoveCurrentCell();
	}
}

bool UI_Ranking_List_Layer::LoadScrollView()
{
	/************************************************************************/
	// 载入滚动层
	// 1. 请求当前排行榜类型的个数
	int nCount				=	-1;
	nCount					=	Rank_Manager::instance()->UIRequestCurrentRankTypeCount();

	// 2. 判断当前排行榜类型的个数是否异常
	if (nCount < 0)
		return false;

	// 3. 载入可选滚动层
	int nWholeWidth			= m_pRankingListScrollView->getInnerContainerSize().width;
	int nWholeHeight		= m_nCellHeight * ranking_list_row;
	int nTotalHeight		= m_nCellHeight * nCount;
	int nScrollviewHeight	= nTotalHeight > nWholeHeight ? nTotalHeight : nWholeHeight;
	m_pRankingListScrollView->setInnerContainerSize(Size(nWholeWidth, nScrollviewHeight));
	m_pRankingListScrollView->jumpToTop();
	
	// 4. 获得的个数与之前的相比较然后对Cell的分数进行添加或者删除
	int nMinCount = nCount > m_nCurrentCellCount ? m_nCurrentCellCount : nCount;
	int nMaxCount = nCount > m_nCurrentCellCount ? nCount : m_nCurrentCellCount;
	if (nCount > m_nCurrentCellCount)
	{
		for (int nIndex = nMinCount; nIndex < nMaxCount; ++nIndex)
		{
			UI_Ranking_List_Cell_Layer * pCell = UI_Ranking_List_Cell_Layer::create();
			pCell->setTag(nIndex);
			pCell->SetCurrentCellIndex(nIndex);
			m_pRankingListScrollView->addChild(pCell);
		}
	}
	else
	{
		for (int nIndex = nMinCount; nIndex < nMaxCount; ++nIndex)
		{
			UI_Ranking_List_Cell_Layer * pCell = dynamic_cast<UI_Ranking_List_Cell_Layer*>(m_pRankingListScrollView->getChildByTag(nIndex));
			if (pCell == NULL)
				continue;

			pCell->RemoveCurrentCell();
		}
	}

	// 5. 重置每个单元的位置
	for (int nIndex = 0; nIndex < nCount; ++nIndex)
	{
		UI_Ranking_List_Cell_Layer * pCell = dynamic_cast<UI_Ranking_List_Cell_Layer*>(m_pRankingListScrollView->getChildByTag(nIndex));
		if (pCell == NULL)
			continue;

		pCell->setPosition(ccp(-10, nScrollviewHeight - (nIndex + 1) * m_nCellHeight));
	}


	// 6. 记录当前的单元个数
	m_nCurrentCellCount		= nCount;

	return true;
}


void UI_Ranking_List_Layer::GetEachCellShowInfo()
{
	/************************************************************************/
	// 获取每个单元的显示信息
	for (int nIndex = 0; nIndex < m_nCurrentCellCount; ++nIndex)
	{
		UI_Ranking_List_Cell_Layer * pCell = dynamic_cast<UI_Ranking_List_Cell_Layer*>(m_pRankingListScrollView->getChildByTag(nIndex));
		if (pCell == NULL)
			continue;

		pCell->RequestCurrentCellShowInfo();
	}
}


void UI_Ranking_List_Layer::TargetCellBeSelected(const int nIndex)
{
	/************************************************************************/
	// 目标单元被选中
	// 1.  判断索引是否异常,默认所有的异常所有重置
	if (nIndex < 0 || nIndex >= m_nCurrentCellCount)
		return;
	
	// 2. 遍历所有的Cell并设置选中框状态
	for (int nIndex_1 = 0; nIndex_1 < m_nCurrentCellCount; ++nIndex_1)
	{
		UI_Ranking_List_Cell_Layer * pCell = dynamic_cast<UI_Ranking_List_Cell_Layer*>(m_pRankingListScrollView->getChildByTag(nIndex_1));
		if (pCell == NULL)
			continue;

		pCell->CurrentCellBeSelected(nIndex_1 == nIndex);
	}

	// 3. 记录当前被选中的Cell索引
	m_nCurrentCellIndex = nIndex;


	// 4. 请求目标选中单元的简单信息
	RequestTargetCellSimpleInfo(m_nCurrentCellIndex);
}


void UI_Ranking_List_Layer::RequestTargetCellSimpleInfo(const int nIndex)
{
	/************************************************************************/
	// 请求目标单元的详细信息
	// 1. 向逻辑层请求目标索引的简单显示数据 
	TARGET_INDEX_SIMPLE_INFO_FOR_SHOW strData;
	if (!Rank_Manager::instance()->UIRequestTargetIndexSimpleShowInfo(m_nCurrentCellIndex, &strData))
		return;

	// 2. 显示目标排名玩家排名名次
	int nRanking = strData.nRanking;
	m_pTargetRankingText->setString(CCString::createWithFormat("%d", nRanking)->getCString());

	// 3. 显示目标名次的奖励物品Icon
	int nTemp = 0;
	const char * szTemp;
	szTemp = ITEM_CONFIG_MGR::instance()->get_icon_path(strData.nIconID);
    std::string p("icon/");
    p+=szTemp;
	nTemp = strcmp(szTemp, "");
	if (nTemp <= 0)
		return;

	m_pTargetRankingPresentImg->loadTexture(p.c_str());
	m_pTargetRankingPresentImg->setVisible(true);
}


void UI_Ranking_List_Layer::RequestPlayerRankingSimpleInfo()
{
	/************************************************************************/
	// 请求玩家本身名次的简单信息
	// 1. 向逻辑层请求玩家的简单显示数据 
	TARGET_INDEX_SIMPLE_INFO_FOR_SHOW strData;
	if (!Rank_Manager::instance()->UIRequestPlayerRankingSimpleShowInfo(&strData))
	{
		m_pMyRankingText->setVisible(false);
		m_pMyRankingPanel->setVisible(false);
		return;
	}

	// 2. 显示目标排名玩家排名名次
	m_pMyRankingText->setVisible(true);
	m_pMyRankingText->setString(CCString::createWithFormat("%d", strData.nRanking)->getCString());

	// 3. 玩家自身排名奖励页面是否可见
	if (!strData.bPresentVisible)
	{
		m_pMyRankingPanel->setVisible(false);
		return;
	}
	else
	{
		m_pMyRankingPanel->setVisible(true);
	}
	
	// 4. 显示目标名次的奖励物品Icon
	int nTemp = 0;
	const char * szTemp;
	szTemp = ITEM_CONFIG_MGR::instance()->get_icon_path(strData.nIconID);
    std::string p("icon/");
    p+=szTemp;
	nTemp = strcmp(szTemp, "");
	if (nTemp <= 0)
		return;

	m_pMyRankingPresentImg->loadTexture(p.c_str());
	m_pMyRankingPresentImg->setVisible(true);
}


void UI_Ranking_List_Layer::SetTitleStringByRankType(const Rank_Type eType)
{
	/************************************************************************/
	// 通过排行榜类型设置标题
	if (eType >= Rank_Type_Error)
		return;
	
	for (int nIndex = 0 ; nIndex < (int)Rank_Type_Error ; ++nIndex)
	{
		m_pChangeTitleText[nIndex]->setVisible(nIndex == (int)eType);
	}
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 按钮点击方法回调	
void UI_Ranking_List_Layer::OnBtnCloseCallBack(Ref*pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 关闭按钮点击回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 1. 通知逻辑层关闭当前排行榜页面状态
	Rank_Manager::instance()->UIRequestCloseRankingListLayer();
	auto delay = DelayTime::create(0.2);
	auto remove = CallFunc::create( CC_CALLBACK_0(UI_Ranking_List_Layer::removeFromParent,this) );
	auto seq = Sequence::create(delay, remove, nullptr);
	this->runAction(seq);
	// 2. 关闭当前界面
	//this->removeFromParent();
}
void UI_Ranking_List_Layer::OnBtnPVPCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 竞技场按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 请求进入竞技场排行榜界面
	EnterTargetRankLayer(Rank_Type_PVP);
    m_pPVPBtn->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
    m_pLevelBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
    m_pFightingPowerBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
    m_pMoneyBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
    m_pRenownBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
}

void UI_Ranking_List_Layer::OnBtnLevelCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 等级按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 请求进入等级排行榜界面
	EnterTargetRankLayer(Rank_Type_Level);
    m_pLevelBtn->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
    m_pPVPBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
    m_pFightingPowerBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
    m_pMoneyBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
    m_pRenownBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
}

void UI_Ranking_List_Layer::OnBtnFightingPowerCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 战斗力按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 请求进入战斗力排行榜界面
	EnterTargetRankLayer(Rank_Type_Fighting_Power);
    m_pFightingPowerBtn->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
    m_pPVPBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
    m_pLevelBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
    m_pMoneyBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
    m_pRenownBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
}

void UI_Ranking_List_Layer::OnBtnMoneyCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 金钱按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 请求进入金钱排行榜界面
	EnterTargetRankLayer(Rank_Type_Money);
    m_pMoneyBtn->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
    m_pPVPBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
    m_pFightingPowerBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
    m_pLevelBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
    m_pRenownBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
}

void UI_Ranking_List_Layer::OnBtnRenownCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 声望按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 请求进入声望排行榜界面
	EnterTargetRankLayer(Rank_Type_Renown);
    m_pRenownBtn->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
    m_pPVPBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
    m_pFightingPowerBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
    m_pLevelBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
    m_pMoneyBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
}