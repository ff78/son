#ifndef _UI_Society_Layer_
#define _UI_Society_Layer_

#include "cocos2d.h"

USING_NS_CC;

// 当前社交界面的状态
enum Current_Society_Layer_State
{
	Current_Society_Layer_State_Email	= 0,			  // 邮件页面
	Current_Society_Layer_State_Faction	= 1,			  // 公会界面
	Current_Society_Layer_State_Friend	= 2,			  // 好友界面
	Current_Society_Layer_State_Error
};

using namespace ui;
class UI_Society_Layer :public cocos2d::Layer
{
public:
	UI_Society_Layer();
	~UI_Society_Layer();
	CREATE_FUNC(UI_Society_Layer);
	virtual bool init();

	virtual void onExit();
	virtual void onEnter();

private:
	//---成员变量---//
	Current_Society_Layer_State			m_eCurrentSociety_State;															// 当前社交界面的状态
	
public:
	//---相关界面刷新逻辑---//
	void								OpenTargetSocietyLayerState(const Current_Society_Layer_State eState);				// 开启目标社交界面


private:
	//---按钮方法回调---//	
	void								OnBtnCloseCallBack(Ref* pSender, Widget::TouchEventType type);						// 关闭按钮方法回调
	void								OnBtnEmailCallBack(Ref* pSender, Widget::TouchEventType type);						// 邮件按钮回调
	void								OnBtnFactionCallBack(Ref* pSender, Widget::TouchEventType type);					// 公会按钮回调
	void								OnBtnFriendCallBack(Ref* pSender, Widget::TouchEventType type);						// 好友按钮回调

private:
	cocos2d::ui::Button* _friendButton;
	cocos2d::ui::Button* _guildButton;
	cocos2d::ui::Button* _emailButton;
};

#endif