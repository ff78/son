#ifndef _UI_Add_Friend_Layer_
#define _UI_Add_Friend_Layer_

#include "cocos2d.h"
#include "Relation_System/Relation_Common.h"

USING_NS_CC;

using namespace ui;
class UI_Add_Friend_Layer :public cocos2d::Layer
{
public:
	UI_Add_Friend_Layer();
	~UI_Add_Friend_Layer();
	CREATE_FUNC(UI_Add_Friend_Layer);
	virtual bool init();

	virtual void onExit();
	virtual void onEnter();

private:
	//---成员变量---//
	

public:
	//---相关界面刷新逻辑---//
	
private:
	//---按钮方法回调---//	
	void								OnBtnCloseCallBack(Ref* pSender, Widget::TouchEventType type);						// 关闭按钮方法回调
	void								OnBtnSubmitCallBack(Ref* pSender, Widget::TouchEventType type);						// 提交按钮方法回调

private:
	//---Cocostudio文件---//
	
};

#endif