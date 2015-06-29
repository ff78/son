#ifndef _UI_Send_Email_Layer_
#define _UI_Send_Email_Layer_

#include "cocos2d.h"

class UI_Send_Email_Layer :public cocos2d::Layer
{
public:
	UI_Send_Email_Layer();
	~UI_Send_Email_Layer();
	CREATE_FUNC(UI_Send_Email_Layer);
	virtual bool init();

	virtual void onExit();
	virtual void onEnter();

public:
	//---相关界面刷新逻辑---//
	void setNameAndContent();

private:

	void	OnBtnSendEmailCallBack(cocos2d::Ref* pSender, ui::Widget::TouchEventType type);		// 发送邮件按
	void	OnBtnAllEmailCallBack(cocos2d::Ref* pSender, ui::Widget::TouchEventType type);		// 收件箱按钮

private:
	cocos2d::ui::Widget* _root;

	std::string _contentToSend;
	int _currentIndex;

};

#endif