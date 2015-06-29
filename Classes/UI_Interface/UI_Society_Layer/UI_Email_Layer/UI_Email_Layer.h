#ifndef _UI_Email_Layer_
#define _UI_Email_Layer_

#include "cocos2d.h"

USING_NS_CC;

using namespace ui;
class UI_Email_Layer :public cocos2d::Layer
{
public:
	UI_Email_Layer();
	~UI_Email_Layer();
	CREATE_FUNC(UI_Email_Layer);
	virtual bool init();

	virtual void onExit();
	virtual void onEnter();

	void eventShowDelete();
private:
	//---成员变量---//
	int									m_nCellsCount;																// 单元个数
	int									m_nCurrentCellIndex;														// 当前单元的索引
	
public:
	//---相关界面刷新逻辑---//
	void								RefreshWholeLayer();														// 刷新当前整个界面
	void								GetCellCount();																// 获取单元的个数
	void								LoadScrollView();															// 载入邮件滚动层
	void								TargetCellBeSelected(int nIndex);											// 目标单元被选中
	void								RemoveAllCell();															// 移除所有的单元
	void								GetEachCellShowInfo();														// 获取所有单元的显示信息
	void								TargetCellRequestOpenReceiveEmailLayer();									// 目标单元请求打开读信界面

	void								WaitForRefreshWholeLayer(float dt);											// 等待刷新邮件列表

private:
	//---按钮方法回调---//	
	void								OnBtnSendEmailCallBack(Ref* pSender, Widget::TouchEventType type);			// 发送邮件按钮回调
	void								onOpenCallBack(Ref* pSender, Widget::TouchEventType type);			
	void								OnBtnDeleteEmailCallBack(Ref* pSender, Widget::TouchEventType type);		// 删除邮件按钮回调
	void								OnBtnDeleteAllEmailCallBack(Ref* pSender, Widget::TouchEventType type);		// 删除所有邮件按钮回调

private:
	//---Cocostudio文件---//
	ui::ScrollView*						m_pEmailsScrollView;														// 邮件滚动层

public:
	//---获取和设置成员变量---//
};

#endif