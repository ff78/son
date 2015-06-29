#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../../Game_Interface/common.h"

#define attr_num 2

USING_NS_CC;

using namespace ui;

class WashLayer : public cocos2d::Layer
{
private:

	void								onStrenthCallback(Ref* pSender, Widget::TouchEventType type);
	void								onStarupCallback(Ref* pSender, Widget::TouchEventType type);	
	void								onGemCallBack(Ref* pSender, Widget::TouchEventType type);					
	void								onWashCallBack(Ref* pSender, Widget::TouchEventType type);

	void								onCloseCallBack(Ref* pSender, Widget::TouchEventType type);	

	ui::Button*							_strenthButton;					
	ui::Button*							_starupButton;					
	ui::Button*							_gemButton;						
	ui::Button*							_washButton;					

	ui::Button*							_closeButton;			

public:
	WashLayer();
	~WashLayer();
	CREATE_FUNC(WashLayer);

	virtual bool init() override;
	virtual void onExit() override;
	virtual void onEnter() override;
	virtual void setVisible(bool visible) override;

};