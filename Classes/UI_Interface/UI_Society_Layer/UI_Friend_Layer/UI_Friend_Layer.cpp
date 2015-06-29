#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Game_Interface/common.h"
#include "Common/GameDefine.h"
#include "Network_Common/global_macros.h"

#include "Relation_System/Relation_Common.h"
#include "Relation_System/Relation_Mgr.h"

#include "UI_Add_Friend_Layer.h"

#include "UI_Friend_Cell_Layer.h"
#include "UI_Friend_Layer.h"

#define firend_row 4

using namespace ui;
using namespace cocos2d;
using namespace cocostudio;

UI_Friend_Layer::UI_Friend_Layer()
{
	m_nCurrentCellCount		= 0;
	m_nCurrentCellIndex		= 0;

	m_eCurrentLayerState	= CURRENT_FRIEND_LAYER_STATE_ERROR;
}


UI_Friend_Layer::~UI_Friend_Layer()
{

}


bool UI_Friend_Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	ui::Widget* pLayer				= cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Social_Friend/Social_Friend.ExportJson");
	addChild(pLayer);

	// 已有好友操作界面
	m_pOwnFriendOperatePanel		= dynamic_cast<ui::Layout*>(Helper::seekWidgetByName(pLayer, "Friend_Normal_Deal_Panel"));

	// 申请好友操作界面
	m_pApplyFriendOperatePanel		= dynamic_cast<ui::Layout*>(Helper::seekWidgetByName(pLayer, "Friend_Apply_Deal_Panel"));

	// 添加好友文本
	//m_pAddFriendText = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Normal_Add_Friend"));
	//m_pAddFriendText->setTouchEnabled(true);
	//m_pAddFriendText->addTouchEventListener(CC_CALLBACK_2(UI_Friend_Layer::OnBtnAddFriendCallBack, this));
	m_pAddFriendButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Btn_Add"));
	m_pAddFriendButton->setTouchEnabled(true);
	m_pAddFriendButton->addTouchEventListener(CC_CALLBACK_2(UI_Friend_Layer::OnBtnAddFriendCallBack, this));

	// 申请文本
	//m_pApplyText					= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Normal_Apply"));
	//m_pApplyText->setTouchEnabled(true);
	//m_pApplyText->addTouchEventListener(CC_CALLBACK_2(UI_Friend_Layer::OnBtnApplyCallBack, this));
	m_pApplyButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Button_11"));
	m_pApplyButton->setTouchEnabled(true);
	m_pApplyButton->addTouchEventListener(CC_CALLBACK_2(UI_Friend_Layer::OnBtnApplyCallBack, this));
	
	// 邮件文本
	//m_pEmailText					= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Normal_Email"));
	//m_pEmailText->setTouchEnabled(true);
	//m_pEmailText->addTouchEventListener(CC_CALLBACK_2(UI_Friend_Layer::OnBtnEmailCallBack, this));
	m_pEmailButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Button_12"));
	m_pEmailButton->setTouchEnabled(true);
	m_pEmailButton->addTouchEventListener(CC_CALLBACK_2(UI_Friend_Layer::OnBtnEmailCallBack, this));

	;
	// 删除文本
	//m_pDeleteText					= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Normal_Delete"));
	//m_pDeleteText->setTouchEnabled(true);
	//m_pDeleteText->addTouchEventListener(CC_CALLBACK_2(UI_Friend_Layer::OnBtnDeleteCallBack, this));
	m_pDeleteButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Btn_Delete"));
	m_pDeleteButton->setTouchEnabled(true);
	m_pDeleteButton->addTouchEventListener(CC_CALLBACK_2(UI_Friend_Layer::OnBtnDeleteCallBack, this));
	
	// 好友文本
	//m_pFriendText					= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Apply_Friend"));
	//m_pFriendText->setTouchEnabled(true);
	//m_pFriendText->addTouchEventListener(CC_CALLBACK_2(UI_Friend_Layer::OnBtnFriendCallBack, this));
	m_pFriendButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Btn_Apply_Friend"));
	m_pFriendButton->setTouchEnabled(true);
	m_pFriendButton->addTouchEventListener(CC_CALLBACK_2(UI_Friend_Layer::OnBtnFriendCallBack, this));
	
	;
	// 同意文本
	//m_pSureText						= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Apply_Allow"));
	//m_pSureText->setTouchEnabled(true);
	//m_pSureText->addTouchEventListener(CC_CALLBACK_2(UI_Friend_Layer::OnBtnAllowCallBack, this));
	m_pSureButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Btn_Apply_Allow"));
	m_pSureButton->setTouchEnabled(true);
	m_pSureButton->addTouchEventListener(CC_CALLBACK_2(UI_Friend_Layer::OnBtnAllowCallBack, this));
	// 申请删除文本
	//m_pApplyDeleteEmailText			= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Apply_Delete"));								
	//m_pApplyDeleteEmailText->setTouchEnabled(true);
	//m_pApplyDeleteEmailText->addTouchEventListener(CC_CALLBACK_2(UI_Friend_Layer::OnBtnApplyDeleteCallBack, this));
	m_pApplyDeleteEmailButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Btn_Apply_Delete"));
	m_pApplyDeleteEmailButton->setTouchEnabled(true);
	m_pApplyDeleteEmailButton->addTouchEventListener(CC_CALLBACK_2(UI_Friend_Layer::OnBtnApplyDeleteCallBack, this));
	
	// 好友滚动层
	m_pFriendScrollView				= dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(pLayer, "Friend_List_ScrollView"));

	return true;
}


void UI_Friend_Layer::onExit()
{
	unschedule(schedule_selector(UI_Friend_Layer::WaitForRefreshWholeLayer));

	Layer::onExit();
}


void UI_Friend_Layer::onEnter()
{
	Layer::onEnter();

	// 切换至已有好友界面
	ChangeCurrentLayerState(CURRENT_FRIEND_LAYER_STATE_OWN);

	// 开启Updata刷新界面
	schedule(schedule_selector(UI_Friend_Layer::WaitForRefreshWholeLayer), 0.1f);
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 页面刷新相关逻辑
void UI_Friend_Layer::RefreshWholeLayer()
{
	/************************************************************************/
	// 刷新当前整个界面
	RemoveAllFriendCell();										// 移除所有的好友单元
	GetCellCount();												// 获取单元个数
	LoadScrollView();											// 载入好友滚动层
	GetEachCellRoleID();										// 获取每个单元的好友ID
	GetEachCellShowInfo();										// 获取每个单元的显示信息
	TargetCellBeSelected(m_nCurrentCellIndex);					// 设置选中状态
}


void UI_Friend_Layer::UpdateFriendListIsGet(float dt)
{
	/************************************************************************/
	// 刷新好友列表是否获取
	// 1. 判断好友列表是否获取到
	if (m_eCurrentLayerState == CURRENT_FRIEND_LAYER_STATE_OWN)
	{
		if (!Relation_Manager::instance()->GetOwnFriendListGetState())
			return;
	}
	if (m_eCurrentLayerState == CURRENT_FRIEND_LAYER_STATE_APPLY)
	{
		if (!Relation_Manager::instance()->GetApplyFriendListGetState())
			return;
	}
	
	// 2. 如果已有的好友列表已经获取到则停止Update
	unschedule(schedule_selector(UI_Friend_Layer::UpdateFriendListIsGet));

	// 3. 刷新界面
	RefreshWholeLayer();
}


void UI_Friend_Layer::WaitForRefreshWholeLayer(float dt)
{
	/************************************************************************/
	// 等待刷新好友列表
	// 1. 判断已有好友列表是否发生改变的消息是否返回
	if (m_eCurrentLayerState == CURRENT_FRIEND_LAYER_STATE_OWN)
	{
		if (!Relation_Manager::instance()->GetOwnFriendListChangeState())
			return;

		Relation_Manager::instance()->SetOwnFriendListChangeMsgBackState(false);
	}
	else if (m_eCurrentLayerState == CURRENT_FRIEND_LAYER_STATE_APPLY)
	{
		if (!Relation_Manager::instance()->GetApplyFriendListChangeState())
			return;

		Relation_Manager::instance()->SetApplyFriendListChangeState(false);
	}
	else
	{
		return;
	}

	// 2. 刷新界面
	RefreshWholeLayer();
}


void UI_Friend_Layer::RemoveAllFriendCell()
{
	/************************************************************************/
	// 移除所有的好友单元
	// 移除每个Cell
	for (int nIndex = 0; nIndex < m_nCurrentCellCount; ++nIndex)
	{
		UI_Friend_Cell_Layer * pCell = dynamic_cast<UI_Friend_Cell_Layer*>(m_pFriendScrollView->getChildByTag(nIndex));
		if (pCell == NULL)
			continue;

		pCell->RemoveCurrentCell();
	}
}


void UI_Friend_Layer::GetCellCount()
{
	/************************************************************************/
	// 获取单元个数
	m_nCurrentCellCount = Relation_Manager::instance()->UIRequestCellCount();
}


void UI_Friend_Layer::LoadScrollView()
{
	/************************************************************************/
	// 载入好友滚动层
	// 1. 判断好友个数是否异常
	if (m_nCurrentCellCount <= 0)
		return;

	// 2. 载入可选滚动层
	int nWholeWidth			= m_pFriendScrollView->getInnerContainerSize().width;
	int nWholeHeight		= m_pFriendScrollView->getInnerContainerSize().height;

	int nCellHeight			= nWholeHeight / firend_row;
	int nTotalHeight		= nCellHeight * m_nCurrentCellCount;
	int nScrollviewHeight	= nTotalHeight > nWholeHeight ? nTotalHeight : nWholeHeight;
	m_pFriendScrollView->setInnerContainerSize(Size(nWholeWidth, nScrollviewHeight));
	m_pFriendScrollView->jumpToTop();

	// 3. 载入好友滚动层单元
	for (int nIndex = 0; nIndex < m_nCurrentCellCount; ++nIndex)
	{
		UI_Friend_Cell_Layer * pCell = UI_Friend_Cell_Layer::create();
		pCell->setPosition(ccp(-10, nScrollviewHeight - (nIndex + 1) * nCellHeight));
		pCell->setTag(nIndex);
		pCell->SetCurrentCellIndex(nIndex);
		m_pFriendScrollView->addChild(pCell);
	}
}


void UI_Friend_Layer::GetEachCellRoleID()
{
	/************************************************************************/
	// 获取每个单元的好友ID
	// 1. 从逻辑层获取好友ID
	std::list<int> friend_role_id_list;
	if (!Relation_Manager::instance()->UIRequestFriendRoleID(&friend_role_id_list))
		return;
	
	// 2. 判断索引的个数是否异常
	if (friend_role_id_list.size() != m_nCurrentCellCount)
		return;
	
	// 3. 给每个单元赋值
	int nIndex = 0;
	std::list<int>::const_iterator friend_index_iter = friend_role_id_list.begin();
	for (friend_index_iter; friend_index_iter != friend_role_id_list.end(); ++friend_index_iter)
	{
		UI_Friend_Cell_Layer * pCell = dynamic_cast<UI_Friend_Cell_Layer*>(m_pFriendScrollView->getChildByTag(nIndex));
		if (pCell == NULL)
			continue;

		pCell->SetCurrentCellRoleID(*friend_index_iter);
		++nIndex;
	}
}

void UI_Friend_Layer::GetEachCellShowInfo()
{
	/************************************************************************/
	// 获取每个单元的显示信息
	for (int nIndex = 0; nIndex < m_nCurrentCellCount; ++nIndex)
	{
		UI_Friend_Cell_Layer * pCell = dynamic_cast<UI_Friend_Cell_Layer*>(m_pFriendScrollView->getChildByTag(nIndex));
		if (pCell == NULL)
			continue;

		pCell->RequestCurrentCellShowInfo();
	}
}


void UI_Friend_Layer::ChangeCurrentLayerState(CURRENT_FRIEND_LAYER_STATE eState)
{
	/************************************************************************/
	// 切换当前页面状态
	// 1. 判断页面状态是否异常
	if (eState == CURRENT_FRIEND_LAYER_STATE_ERROR)
		return;

	// 2. 如果当前页面状态与目标状态则不进行任何操作
	if (m_eCurrentLayerState == eState)
		return;

	// 3. 根据状态显示不同的内容
	if (eState == CURRENT_FRIEND_LAYER_STATE_APPLY)
	{
		SetPanelState(false, true);
	}
	if (eState == CURRENT_FRIEND_LAYER_STATE_OWN)
	{
		SetPanelState(true, false);
	}

	// 4. 通知逻辑打开好友界面,如果没有获取到好友列表则开启计时器
	if (!Relation_Manager::instance()->UIRequestEnterTargetLayerState(eState))
		return;

	/************************************************************************/
	// 条件满足,刷新界面
	// 1. 记录当前界面状态
	m_eCurrentLayerState = eState;

	// 2. 开启Update
	schedule(schedule_selector(UI_Friend_Layer::UpdateFriendListIsGet), 0.1f);
}

void UI_Friend_Layer::TargetCellBeSelected(int nIndex)
{
	/************************************************************************/
	// 目标单元被选中
	// 1.  判断索引是否异常,默认所有的异常所有重置
	if (nIndex < 0 || nIndex >= m_nCurrentCellCount)
	{
		nIndex = 0;
	}

	// 2. 遍历所有的Cell并设置选中框状态
	for (int nIndex_1 = 0; nIndex_1 < m_nCurrentCellCount; ++nIndex_1)
	{
		UI_Friend_Cell_Layer * pCell = dynamic_cast<UI_Friend_Cell_Layer*>(m_pFriendScrollView->getChildByTag(nIndex_1));
		if (pCell == NULL)
			continue;

		pCell->CurrentCellBeSelected(nIndex_1 == nIndex);
	}

	// 3. 记录当前被选中的Cell索引
	m_nCurrentCellIndex = nIndex;	
}


void UI_Friend_Layer::SetPanelState(bool bValue_1, bool bValue_2 )
{
	/************************************************************************/
	// 设置界面状态
	m_pOwnFriendOperatePanel->setVisible(bValue_1);
	m_pApplyFriendOperatePanel->setVisible(bValue_2);
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 按钮点击方法回调	
void UI_Friend_Layer::OnBtnAddFriendCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 添加好友按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 添加好友添加界面
	UI_Add_Friend_Layer * pLayer = UI_Add_Friend_Layer::create();
	addChild(pLayer);
}

void UI_Friend_Layer::OnBtnApplyCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 申请按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 切换当前页面状态
	ChangeCurrentLayerState(CURRENT_FRIEND_LAYER_STATE_APPLY);
}

void UI_Friend_Layer::OnBtnEmailCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 邮件按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;
}

void UI_Friend_Layer::OnBtnDeleteCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 删除件按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 通知目标单元删除好友
	UI_Friend_Cell_Layer * pCell = dynamic_cast<UI_Friend_Cell_Layer*>(m_pFriendScrollView->getChildByTag(m_nCurrentCellIndex));
	if (pCell == NULL)
		return;

	pCell->DeleteCurrentFriend();
}

void UI_Friend_Layer::OnBtnFriendCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 好友按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 切换当前页面状态
	ChangeCurrentLayerState(CURRENT_FRIEND_LAYER_STATE_OWN);
}

void UI_Friend_Layer::OnBtnAllowCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 同意按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 通知目标单元从申请列表添加好友
	UI_Friend_Cell_Layer * pCell = dynamic_cast<UI_Friend_Cell_Layer*>(m_pFriendScrollView->getChildByTag(m_nCurrentCellIndex));
	if (pCell == NULL)
		return;

	pCell->AllowToAddFriend();
}

void UI_Friend_Layer::OnBtnApplyDeleteCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 申请删除按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 通知目标单元删除好友
	UI_Friend_Cell_Layer * pCell = dynamic_cast<UI_Friend_Cell_Layer*>(m_pFriendScrollView->getChildByTag(m_nCurrentCellIndex));
	if (pCell == NULL)
		return;

	pCell->DeleteCurrentFriend();
}