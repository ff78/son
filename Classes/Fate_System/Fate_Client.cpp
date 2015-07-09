#include "Fate_Client.h"

#include "cocostudio/CocoStudio.h"

FATE_MODEL* FATE_MODEL::getInstance()
{
	static FateData instance_;
	return &instance_;

}

void FATE_VIEW::onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
		return;
	auto spawnAction = cocos2d::Spawn::createWithTwoActions(cocos2d::DelayTime::create(0.1), cocos2d::CallFunc::create(CC_CALLBACK_0(FATE_VIEW::removeFromParent, this)));
	this->runAction(spawnAction);

}

void FATE_VIEW::onEnter()
{
	Layer::onEnter();
}

void FATE_VIEW::onExit()
{
	Layer::onExit();
}

bool FATE_VIEW::init()
{
	if( !Layer::init() )
		return false;
	
	_rootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/chart.json");
	if( _rootWidget == nullptr )
		return false;
	addChild(_rootWidget);

	_closeButton  = dynamic_cast<cocos2d::ui::Button*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "btn_close_0") );
	_closeButton->setVisible(true);
	_closeButton->setTouchEnabled(true);
	_closeButton->addTouchEventListener(CC_CALLBACK_2(FATE_VIEW::onCloseCallback, this));

	return true;

}

bool Game_Net::send_on_load(Game_Logic::Game_Interface& gm_interface)
{
	return false;
}