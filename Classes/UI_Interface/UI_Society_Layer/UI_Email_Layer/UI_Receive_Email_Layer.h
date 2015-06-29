#ifndef _UI_Receive_Email_Layer_
#define _UI_Receive_Email_Layer_

#include "cocos2d.h"

USING_NS_CC;

using namespace ui;
class UI_Receive_Email_Layer :public cocos2d::Layer
{
public:
	UI_Receive_Email_Layer();
	~UI_Receive_Email_Layer();
	CREATE_FUNC(UI_Receive_Email_Layer);
	virtual bool init();

	virtual void onExit();
	virtual void onEnter();

private:
	//---成员变量---//
	int									m_nCurrentEmailIndex;													// 当前邮件索引

public:
	//---相关界面刷新逻辑---//
	void								RefreshCurrentLayer();													// 刷新当前界面

private:
	//---按钮方法回调---//	
	void								OnBtnAllEmailCallBack(Ref* pSender, Widget::TouchEventType type);		// 收件箱按钮回调
	void								OnBtnSendEmailCallBack(Ref* pSender, Widget::TouchEventType type);		// 回信按钮回调
	void								OnBtnReceivePresentCallBack(Ref* pSender, Widget::TouchEventType type);	// 领取附件按钮回调
	void								OnBtnDeleteEmailCallBack(Ref* pSender, Widget::TouchEventType type);	// 删除按钮回调

private:
	//---Cocostudio文件---//
	ui::Text*							m_pWriterNameText;														// 寄信人名字文本
	ui::Text*							m_pContentText;															// 内容天数文本

public:
	//---获取和设置成员变量---//
	inline void SetCurrentEmailIndex(const int nIndex)
	{
		m_nCurrentEmailIndex = nIndex;
	}
};

#endif