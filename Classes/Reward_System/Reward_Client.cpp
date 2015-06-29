#include "Reward_Client.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "../Player_Account/Account_Data_Mgr.h"
#include "../Character_System/Character_Mgr.h"
#include "../Character_System/Player.h"

REWARD_MODEL* REWARD_MODEL::getInstance()
{
	static REWARD_MODEL instance_;
	return &instance_;

}

void REWARD_VIEW::onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
		return;
	auto spawnAction = cocos2d::Spawn::createWithTwoActions(cocos2d::DelayTime::create(0.1), cocos2d::CallFunc::create(CC_CALLBACK_0(REWARD_VIEW::removeFromParent, this)));
	this->runAction(spawnAction);

}

void REWARD_VIEW::onEnter()
{
	Layer::onEnter();
}

void REWARD_VIEW::onExit()
{
	Layer::onExit();
}

bool REWARD_VIEW::init()
{
	if( !Layer::init() )
		return false;
	
	_rootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/quest_everyday/quest_everyday.ExportJson");
	if( _rootWidget == nullptr )
		return false;
	addChild(_rootWidget);

	_closeButton  = dynamic_cast<cocos2d::ui::Button*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "btn_close") );
	_closeButton->setVisible(true);
	_closeButton->setTouchEnabled(true);
	_closeButton->addTouchEventListener(CC_CALLBACK_2(REWARD_VIEW::onCloseCallback, this));

	return true;

}

bool Game_Net::send_on_load(Game_Logic::Game_Interface& gm_interface)
{
	return false;
}