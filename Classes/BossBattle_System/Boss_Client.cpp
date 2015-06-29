#include "Boss_Client.h"

#include "cocostudio/CocoStudio.h"

BOSS_MODEL* BOSS_MODEL::getInstance()
{
	static BossData instance_;
	return &instance_;

}

void BOSS_VIEW::onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
		return;
	auto spawnAction = cocos2d::Spawn::createWithTwoActions(cocos2d::DelayTime::create(0.1), cocos2d::CallFunc::create(CC_CALLBACK_0(BOSS_VIEW::removeFromParent, this)));
	this->runAction(spawnAction);

}

void BOSS_VIEW::onEnter()
{
	Layer::onEnter();
}

void BOSS_VIEW::onExit()
{
	Layer::onExit();
}

bool BOSS_VIEW::init()
{
	if( !Layer::init() )
		return false;
	
	_rootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/boss_battle/boss_battle.ExportJson");
	if( _rootWidget == nullptr )
		return false;
	addChild(_rootWidget);

	_closeButton  = dynamic_cast<cocos2d::ui::Button*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Button_9_0") );
	_closeButton->setVisible(true);
	_closeButton->setTouchEnabled(true);
	_closeButton->addTouchEventListener(CC_CALLBACK_2(BOSS_VIEW::onCloseCallback, this));

	return true;

}

bool Game_Net::send_on_load(Game_Logic::Game_Interface& gm_interface)
{
	return false;
}