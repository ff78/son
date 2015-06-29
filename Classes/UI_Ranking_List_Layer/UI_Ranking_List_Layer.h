#ifndef _UI_Ranking_List_Layer_
#define _UI_Ranking_List_Layer_

#include "cocos2d.h"
#include "Rank_System/Rank_Data.h"

USING_NS_CC;

using namespace ui;
class UI_Ranking_List_Layer :public cocos2d::Layer
{
public:
	UI_Ranking_List_Layer();
	~UI_Ranking_List_Layer();
	CREATE_FUNC(UI_Ranking_List_Layer);
	virtual bool init();

	virtual void onExit();
	virtual void onEnter();

private:
	//---成员变量---//
	int					m_nCellHeight;															// 单元的高度
	int					m_nCurrentCellCount;													// 当前的单元个数
	int					m_nCurrentCellIndex;													// 当前选中的单元索引

public:
	//---相关界面刷新逻辑---//
	void				RefreshWholeLayer();													// 刷新当前整个界面
	void				EnterTargetRankLayer(const Rank_Type eType);							// 进入目标排行榜界面
	void				RemoveAllCell();														// 移除所有的单元
	void				GetEachCellShowInfo();													// 获取每个单元的显示信息
	void				TargetCellBeSelected(const int nIndex);									// 目标单元被选中
	void				RequestTargetCellSimpleInfo(const int nIndex);							// 请求目标单元的简单信息
	void				RequestPlayerRankingSimpleInfo();										// 请求玩家本身名次的简单信息
	void				SetTitleStringByRankType(const Rank_Type eType);						// 通过排行榜类型设置标题
	void				GetCurrentRankStateList(const Rank_Type eType);							// 获取当前类型排行榜列表数据是否到
	void				UpdateRankingListIsChange(float dt);									// 刷新排行列表是否改变

	bool				LoadScrollView();														// 载入滚动层

private:
	//---按钮方法回调---//	
	void				OnBtnPVPCallBack(Ref* pSender, Widget::TouchEventType type);			// 竞技场按钮回调
	void				OnBtnLevelCallBack(Ref* pSender, Widget::TouchEventType type);			// 等级按钮回调
	void				OnBtnFightingPowerCallBack(Ref* pSender, Widget::TouchEventType type);	// 战斗力按钮回调
	void				OnBtnMoneyCallBack(Ref* pSender, Widget::TouchEventType type);			// 金钱按钮回调
	void				OnBtnRenownCallBack(Ref* pSender, Widget::TouchEventType type);			// 声望按钮回调
	void				OnBtnCloseCallBack(Ref* pSender, Widget::TouchEventType type);			// 关闭按钮方法回调

private:
	//---Cocostudio文件---//
	ui::Button*			m_pCloseBtn;															// 关闭按钮
	ui::Button*			m_pPVPBtn;																// 竞技场按钮
	ui::Button*			m_pLevelBtn;															// 等级按钮
	ui::Button*			m_pFightingPowerBtn;													// 战斗力按钮
	ui::Button*			m_pMoneyBtn;															// 金钱按钮
	ui::Button*			m_pRenownBtn;															// 声望按钮

	ui::Text*			m_pTargetRankingText;													// 目标排名玩家排名名次文本
	ui::Text*			m_pMyRankingText;														// 玩家自己排名名次文本
	ui::Text*			m_pRemainTimeText;														// 剩余时间文本
	ui::Text**			m_pChangeTitleText;														// 会改变标题文本

	ui::Layout*			m_pMyRankingPanel;														// 我的排名界面

	ui::ImageView*		m_pTargetRankingPresentImg;												// 目标排行奖励图片
	ui::ImageView*		m_pMyRankingPresentImg;													// 玩家自己的排行奖励图片

	ui::ScrollView*		m_pRankingListScrollView;												// 排行榜滚动层

public:
	//---获取和设置成员变量---//
};

#endif