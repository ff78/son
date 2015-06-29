#include "Task_Client.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "../Player_Account/Account_Data_Mgr.h"
#include "../Character_System/Character_Mgr.h"
#include "../Character_System/Player.h"

TASK_MODEL* TASK_MODEL::getInstance()
{
	static TASK_MODEL instance_;
	return &instance_;

}

void TASK_VIEW::onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
		return;
	auto spawnAction = cocos2d::Spawn::createWithTwoActions(cocos2d::DelayTime::create(0.1), cocos2d::CallFunc::create(CC_CALLBACK_0(TASK_VIEW::removeFromParent, this)));
	this->runAction(spawnAction);

}

void TASK_VIEW::onEnter()
{
	Layer::onEnter();
}

void TASK_VIEW::onExit()
{
	Layer::onExit();
}

bool TASK_VIEW::init()
{
	if( !Layer::init() )
		return false;
	
	_rootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/task/task.ExportJson");
	if( _rootWidget == nullptr )
		return false;
	addChild(_rootWidget);

	_closeButton  = dynamic_cast<cocos2d::ui::Button*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Btn_Close_0_0_1") );
	_closeButton->setVisible(true);
	_closeButton->setTouchEnabled(true);
	_closeButton->addTouchEventListener(CC_CALLBACK_2(TASK_VIEW::onCloseCallback, this));

	return true;

}

bool Game_Net::send_on_load(Game_Logic::Game_Interface& gm_interface)
{
	return false;
}