#include "UI_Button_Layer.h"
#include "UI_Role_Info_Layer.h"
using namespace cocos2d;

#define TAG_MENU 10
using namespace ui;
UI_Button_Layer::UI_Button_Layer(void)
{
}


UI_Button_Layer::~UI_Button_Layer(void)
{
}

bool UI_Button_Layer::init()
{
	if(!cocos2d::Layer::init())
	{
		return false;
	}

	MenuItemImage* p_roleInfo = MenuItemImage::create("animationbuttonnormal.png","animationbuttonpressed.png",this,menu_selector(UI_Button_Layer::buttonRoleCallback));
	if(!p_roleInfo)
	{
		CCLOG(" p_roleInfo == NULL ");
		return false;
	}
	p_roleInfo->setPosition(Vec2(500,100));
	
	CCMenu* p_menu = CCMenu::create(p_roleInfo,NULL);
	p_menu->setPosition(CCPointZero);
	if(!p_menu)
	{
		CCLOG(" p_menu == NULL ");
		return false;
	}
	this->addChild(p_menu,TAG_MENU);

	return true;
}


void UI_Button_Layer::buttonRoleCallback(Ref* pSender)//,Widget::TouchEventType type
{
	UI_Role_Info_Layer* uril = UI_Role_Info_Layer::create();
	this->addChild(uril,20);

	CCLOG("buttonRoleCallback");
}

