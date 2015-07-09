#include "Secretary_Client.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "../Player_Account/Account_Data_Mgr.h"
#include "../Character_System/Character_Mgr.h"
#include "../Character_System/Player.h"

SECRETARY_MODEL* SECRETARY_MODEL::getInstance()
{
	static SECRETARY_MODEL instance_;
	return &instance_;

}

void SECRETARY_VIEW::onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
		return;
	auto spawnAction = cocos2d::Spawn::createWithTwoActions(cocos2d::DelayTime::create(0.1), cocos2d::CallFunc::create(CC_CALLBACK_0(SECRETARY_VIEW::removeFromParent, this)));
	this->runAction(spawnAction);

}
void SECRETARY_VIEW::onFuncCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    for (int i = 0; i<6; i++) {
        funcBtns[i]->setBrightStyle(ui::Widget::BrightStyle::NORMAL);
    }
    dynamic_cast<cocos2d::ui::Button*>(pSender)->setBrightStyle(ui::Widget::BrightStyle::HIGHLIGHT);
//    if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
//        return;
//    auto spawnAction = cocos2d::Spawn::createWithTwoActions(cocos2d::DelayTime::create(0.1), cocos2d::CallFunc::create(CC_CALLBACK_0(SECRETARY_VIEW::removeFromParent, this)));
//    this->runAction(spawnAction);
    
}

void SECRETARY_VIEW::onEnter()
{
	Layer::onEnter();
}

void SECRETARY_VIEW::onExit()
{
	Layer::onExit();
}

bool SECRETARY_VIEW::init()
{
	if( !Layer::init() )
		return false;
	
	_rootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/secretary.json");
	if( _rootWidget == nullptr )
		return false;
	addChild(_rootWidget);

	_closeButton  = dynamic_cast<cocos2d::ui::Button*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "btn_close_0") );
	_closeButton->setVisible(true);
	_closeButton->setTouchEnabled(true);
	_closeButton->addTouchEventListener(CC_CALLBACK_2(SECRETARY_VIEW::onCloseCallback, this));

    
    funcBtns[0] = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "btn_today"));
    funcBtns[1] = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "btn_strong"));
    funcBtns[2] = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "btn_moeny"));
    funcBtns[3] = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "btn_reputation"));
    funcBtns[4] = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "btn_gold"));
    funcBtns[5] = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "btn_resource"));
    for (int i = 0; i<6; i++) {
        funcBtns[i]->addTouchEventListener(CC_CALLBACK_2(SECRETARY_VIEW::onFuncCallback, this));
    }
	return true;

}

bool Game_Net::send_on_load(Game_Logic::Game_Interface& gm_interface)
{
	return false;
}