#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Game_Interface/common.h"
#include "Common/GameDefine.h"
#include "Network_Common/global_macros.h"

#include "Emai_System/Email_Common_Config_Data.h"
#include "Emai_System/Email_Client.h"

#include "../UI_Society_Layer.h"
#include "UI_Receive_Email_Layer.h"
#include "UI_Send_Email_Layer.h"
#include "UI_Email_Cell_Layer.h"
#include "UI_Email_Layer.h"

#define Emails_row 3

using namespace ui;
using namespace cocos2d;
using namespace cocostudio;

UI_Email_Layer::UI_Email_Layer()
{
	m_nCellsCount		= 0;
	m_nCurrentCellIndex = 0;
}


UI_Email_Layer::~UI_Email_Layer()
{

}


bool UI_Email_Layer::init()
{
	if (!Layer::init())
		return false;
	vector<uint64> para;
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_EMAIL_SEND_LOAD, para);

	ui::Widget* pLayer				= cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Social_All_Email/Social_All_Email.ExportJson");
	addChild(pLayer);

	// 发送邮件按钮
	ui::Button * pSendEmailBtn		= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Write_Email_Button"));
	pSendEmailBtn->setTouchEnabled(false);
	pSendEmailBtn->addTouchEventListener(this, toucheventselector(UI_Email_Layer::OnBtnSendEmailCallBack));

	ui::Button * openButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Open_Email_Button"));
	openButton->setVisible(true);
	openButton->addTouchEventListener(this, toucheventselector(UI_Email_Layer::onOpenCallBack));

	// 删除邮件按钮
	ui::Button * pDeleteEmailBtn	= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Delete_Email_Button"));
	pDeleteEmailBtn->setTouchEnabled(true);
	pDeleteEmailBtn->addTouchEventListener(this, toucheventselector(UI_Email_Layer::OnBtnDeleteEmailCallBack));

	// 删除所有邮件按钮
	ui::Button * pDeleteAllEmailBtn = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "All_Delete_Button"));
	pDeleteAllEmailBtn->setTouchEnabled(true);
	pDeleteAllEmailBtn->addTouchEventListener(this, toucheventselector(UI_Email_Layer::OnBtnDeleteAllEmailCallBack));

	// 邮件滚动层
	m_pEmailsScrollView				= dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(pLayer, "Eamil_List_ScrollView"));
	return true;
}


void UI_Email_Layer::onExit()
{
	Layer::onExit();

	unschedule(schedule_selector(UI_Email_Layer::WaitForRefreshWholeLayer));
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_EMAIL_SHOW_DELETE);
}


void UI_Email_Layer::onEnter()
{
	Layer::onEnter();

	// 1. 通过逻辑层更换当前邮件页面状态
	EMAIL_MODEL::instance()->SetCurrentEmailLayerState(Current_Email_Layer_State_All);

	// 2. 开启Updata刷新界面
	schedule(schedule_selector(UI_Email_Layer::WaitForRefreshWholeLayer), 0.1f);

	// 3. 刷新当前界面
	//RefreshWholeLayer();
	Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_EMAIL_SHOW_DELETE, CC_CALLBACK_0(UI_Email_Layer::eventShowDelete, this));
	
}

void UI_Email_Layer::eventShowDelete()
{
	auto datas = EMAIL_MODEL::instance()->getAllData();
	auto simpleDatas = EMAIL_MODEL::instance()->getSimpleData();
	int index = EMAIL_MODEL::instance()->getCurrentIndex();
	if (index >= datas.size())
		return;
	m_pEmailsScrollView->removeChildByTag( EMAIL_MODEL::instance()->getCurrentEmailId() );
	datas.erase(datas.begin()+index);
	EMAIL_MODEL::instance()->setAllData(datas);
	simpleDatas.erase(simpleDatas.begin()+index);
	EMAIL_MODEL::instance()->setSimpleData(simpleDatas);
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 页面刷新相关逻辑
void UI_Email_Layer::RefreshWholeLayer()
{
	/************************************************************************/
	// 刷新当前整个界面
	RemoveAllCell();								// 移除所有的单元
	GetCellCount();									// 获取单元个数
	LoadScrollView();								// 载入滚动层
	GetEachCellShowInfo();							// 获取所有单元的显示信息
	TargetCellBeSelected(m_nCurrentCellIndex);		// 设置选中状态
}

void UI_Email_Layer::GetCellCount()
{
	/************************************************************************/
	// 获取单元个数
	// 1. 判断个数是否异常
	m_nCellsCount = EMAIL_MODEL::instance()->GetPlayerAllEmailsCount();
}

void UI_Email_Layer::LoadScrollView()
{
	/************************************************************************/
	// 载入好友滚动层
	// 1. 判断邮件个数是否异常
	if (m_nCellsCount <= 0)
		return;

	// 2. 载入可选滚动层
	int nWholeWidth			= m_pEmailsScrollView->getInnerContainerSize().width;
	int nWholeHeight		= m_pEmailsScrollView->getInnerContainerSize().height;

	int nCellHeight			= nWholeHeight / Emails_row;
	int nTotalHeight		= nCellHeight * m_nCellsCount;
	int nScrollviewHeight	= nTotalHeight > nWholeHeight ? nTotalHeight : nWholeHeight;
	m_pEmailsScrollView->setInnerContainerSize(Size(nWholeWidth, nScrollviewHeight));
	m_pEmailsScrollView->jumpToTop();

	// 3. 载入邮件滚动层单元
	int nCount = 0;
	auto simpleDatas = EMAIL_MODEL::instance()->getSimpleData();
	std::vector<Email_Simple_Data_For_Show>::iterator it = simpleDatas.begin();
	for (; it != simpleDatas.end(); it++)
	{
		if (nCount >=20)
			break;
		UI_Email_Cell_Layer * pCell = UI_Email_Cell_Layer::create();
		pCell->setPosition(ccp(-10, nScrollviewHeight - (nCount+1)* nCellHeight));
		//pCell->SetCurrentCellIndex(nCount);
		//pCell->RequestCurrentCellShowInfo();
		if (nCount == 0)
		{
			pCell->m_pSelectBoxImg->setVisible(true);
			EMAIL_MODEL::instance()->setCurrentIndex(0);
			EMAIL_MODEL::instance()->setCurrentEmailId( (*it)._id);
		}
		//m_pOfficialImg->setVisible(data[m_nCurrentCellIndex]->bIsOfficialEmail);
		//m_pBeReadImg->setVisible(data[m_nCurrentCellIndex]->bIsRead);
		//m_pNameText->setString(data[m_nCurrentCellIndex]->szSenderName.c_str());
		//m_pContentText->setString(data[m_nCurrentCellIndex]->szTitle.c_str());
		//m_pDateText->setString(data[m_nCurrentCellIndex]->szCreatTime.c_str());
		//pCell->m_pSelectBoxImg->setVisible(false);
		pCell->m_pOfficialImg->setVisible( (*it).bIsOfficialEmail );
		pCell->m_pBeReadImg->setVisible( (*it).bIsRead );
		pCell->m_pNameText->setString( (*it).szSenderName.c_str() );
		pCell->m_pContentText->setString( (*it).szTitle.c_str() );
		pCell->m_pDateText->setString( (*it).szCreatTime.c_str() );

		int id = (*it)._id;
		pCell->setTag(id);
		pCell->m_pNameText->setTag(nCount);
		if (nCount>=3)
			m_pEmailsScrollView->jumpToBottom();
		m_pEmailsScrollView->addChild(pCell);
		nCount++;

	}
	


	//for (int nIndex = 0; nIndex < m_nCellsCount; ++nIndex)
	//{
	//	UI_Email_Cell_Layer * pCell = UI_Email_Cell_Layer::create();
	//	pCell->setPosition(ccp(-10, nScrollviewHeight - (nIndex + 1) * nCellHeight));
	//	pCell->setTag(nIndex);
	//	pCell->SetCurrentCellIndex(nIndex);
	//	m_pEmailsScrollView->addChild(pCell);
	//	if (nIndex >= 20)
	//		break;
	//}

}


void UI_Email_Layer::TargetCellBeSelected(int nIndex)
{
	/************************************************************************/
	// 目标单元被选中
	// 1.  判断索引是否异常,默认所有的异常所有重置
	if (nIndex < 0 || nIndex >= m_nCellsCount)
	{
		nIndex = 0;
	}

	// 2. 遍历所有的Cell并设置选中框状态
	for (int nIndex_1 = 0; nIndex_1 < m_nCellsCount; ++nIndex_1)
	{
		UI_Email_Cell_Layer * pCell = dynamic_cast<UI_Email_Cell_Layer*>(m_pEmailsScrollView->getChildByTag(nIndex_1));
		if (pCell == NULL)
			continue;

		pCell->CurrentCellBeSelected(nIndex_1 == nIndex);
	}

	// 3. 记录当前被选中的Cell索引
	m_nCurrentCellIndex = nIndex;
}

void UI_Email_Layer::RemoveAllCell()
{
	/************************************************************************/
	// 移除所有的单元
	// 移除每个Cell
	for (int nIndex = 0; nIndex < m_nCellsCount; ++nIndex)
	{
		UI_Email_Cell_Layer * pCell = dynamic_cast<UI_Email_Cell_Layer*>(m_pEmailsScrollView->getChildByTag(nIndex));
		if (pCell == NULL)
			continue;

		pCell->RemoveCurrentCell();
	}
}


void UI_Email_Layer::GetEachCellShowInfo()
{
	/************************************************************************/
	// 获取所有单元的显示信息
	for (int nIndex = 0; nIndex < m_nCellsCount; ++nIndex)
	{
		UI_Email_Cell_Layer * pCell = dynamic_cast<UI_Email_Cell_Layer*>(m_pEmailsScrollView->getChildByTag(nIndex));
		if (pCell == NULL)
			continue;

		pCell->RequestCurrentCellShowInfo();
	}
}


void UI_Email_Layer::TargetCellRequestOpenReceiveEmailLayer()
{
	/************************************************************************/
	// 目标单元请求打开读信界面
	// 1. 打开发邮件界面
	UI_Society_Layer * pLayer = dynamic_cast<UI_Society_Layer *>(this->getParent());
	if (pLayer == NULL)
		return;

	UI_Receive_Email_Layer * pReceiveLayer = UI_Receive_Email_Layer::create();
	pReceiveLayer->setTag(998);
	pReceiveLayer->SetCurrentEmailIndex( EMAIL_MODEL::instance()->getCurrentIndex() );
	pLayer->addChild(pReceiveLayer);

	// 2. 删除当前界面
	this->removeFromParent();

}


void UI_Email_Layer::WaitForRefreshWholeLayer(float dt)
{
	/************************************************************************/
	// 等待刷新邮件列表
	// 1. 判断已有好友列表是否发生改变的消息是否返回
	if (!EMAIL_MODEL::instance()->GetCurrentEmailListIsChangeState())
		return;

	// 2. 更改状态
	EMAIL_MODEL::instance()->SetCurrentEmailListIsChangeState(false);

	// 3. 刷新界面
	RefreshWholeLayer();
}
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 按钮点击方法回调	
void UI_Email_Layer::OnBtnSendEmailCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 发送邮件按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 1. 打开发邮件界面
	UI_Society_Layer * pLayer = dynamic_cast<UI_Society_Layer *>(this->getParent());
	if (pLayer == NULL)
		return;

	UI_Send_Email_Layer * pSendEmailLayer = UI_Send_Email_Layer::create();
	pSendEmailLayer->setTag(998);
	pLayer->addChild(pSendEmailLayer);

	// 2. 删除当前界面
	this->removeFromParent();
}

void UI_Email_Layer::onOpenCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	vector<uint64> para;
	para.clear();
	int id = EMAIL_MODEL::instance()->getCurrentEmailId();
	para.push_back(id);
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_EMAIL_SEND_OPEN, para);
}

void UI_Email_Layer::OnBtnDeleteEmailCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 删除邮件按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;
	vector<uint64> para;
	para.clear();
	para.push_back( EMAIL_MODEL::instance()->getCurrentEmailId() );
	Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_EMAIL_SEND_DELETE, para);
}

void UI_Email_Layer::OnBtnDeleteAllEmailCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 删除所有邮件按钮回调
	if (type != Widget::TouchEventType::ENDED)
		return;
}
