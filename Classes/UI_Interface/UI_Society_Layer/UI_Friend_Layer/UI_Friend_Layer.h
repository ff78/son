#ifndef _UI_Friend_Layer_
#define _UI_Friend_Layer_

#include "cocos2d.h"
#include "Relation_System/Relation_Common.h"

USING_NS_CC;

using namespace ui;
class UI_Friend_Layer :public cocos2d::Layer
{
public:
	UI_Friend_Layer();
	~UI_Friend_Layer();
	CREATE_FUNC(UI_Friend_Layer);
	virtual bool init();

	virtual void onExit();
	virtual void onEnter();

private:
	//---成员变量---//
	int									m_nCurrentCellCount;												// 当前的单元个数
	int									m_nCurrentCellIndex;												// 当前被选中的单元索引

	CURRENT_FRIEND_LAYER_STATE			m_eCurrentLayerState;												// 当前页面状态

public:
	//---相关界面刷新逻辑---//
	void								RefreshWholeLayer();												// 刷新当前整个界面
	void								GetCellCount();														// 获取单元个数
	void								LoadScrollView();													// 载入好友滚动层
	void								RemoveAllFriendCell();												// 移除所有的好友单元
	void								GetEachCellRoleID();												// 获取每个单元的好友ID
	void								GetEachCellShowInfo();												// 获取每个单元的显示信息
	void								ChangeCurrentLayerState(CURRENT_FRIEND_LAYER_STATE eState);			// 切换当前页面状态
	void								TargetCellBeSelected(int nIndex);									// 目标单元被选中

	void								UpdateFriendListIsGet(float dt);									// 刷新好友列表是否获取
	void								WaitForRefreshWholeLayer(float dt);									// 等待刷新好友列表
	void								SetPanelState(bool bValue_1 = false, bool bValue_2 = false);		// 设置界面状态
private:
	//---按钮方法回调---//	
	void								OnBtnAddFriendCallBack(Ref* pSender, Widget::TouchEventType type);	// 添加好友按钮回调
	void								OnBtnApplyCallBack(Ref* pSender, Widget::TouchEventType type);		// 申请按钮回调
	void								OnBtnEmailCallBack(Ref* pSender, Widget::TouchEventType type);		// 邮件按钮回调
	void								OnBtnDeleteCallBack(Ref* pSender, Widget::TouchEventType type);		// 删除件按钮回调
	void								OnBtnFriendCallBack(Ref* pSender, Widget::TouchEventType type);		// 好友按钮回调
	void								OnBtnAllowCallBack(Ref* pSender, Widget::TouchEventType type);		// 同意按钮回调
	void								OnBtnApplyDeleteCallBack(Ref* pSender, Widget::TouchEventType type);// 申请删除按钮回调

private:
	//---Cocostudio文件---//
	// 已有好友界面相关文件
	//ui::Text*							m_pAddFriendText;													// 添加好友文本
	//ui::Text*							m_pApplyText;														// 申请文本
	//ui::Text*							m_pEmailText;														// 邮件文本
	//ui::Text*							m_pDeleteText;														// 删除文本

	ui::Button*							m_pAddFriendButton;													// 添加好友文本
	ui::Button*							m_pApplyButton;														// 申请文本
	ui::Button*							m_pEmailButton;														// 邮件文本
	ui::Button*							m_pDeleteButton;														// 删除文本

	ui::Layout*							m_pOwnFriendOperatePanel;											// 已有好友操作界面

	// 申请好友界面相关文件
	//ui::Text*							m_pFriendText;														// 好友文本
	//ui::Text*							m_pSureText;														// 同意文本
	//ui::Text*							m_pApplyDeleteEmailText;											// 申请删除文本
	ui::Button*							m_pFriendButton;														// 好友文本
	ui::Button*							m_pSureButton;														// 同意文本
	ui::Button*							m_pApplyDeleteEmailButton;											// 申请删除文本

	ui::Layout*							m_pApplyFriendOperatePanel;											// 申请好友操作界面

	ui::ScrollView*						m_pFriendScrollView;												// 好友滚动层
public:
	//---获取和设置成员变量---//
};

#endif