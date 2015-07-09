#include "Title_Client.h"

#include "cocostudio/CocoStudio.h"

TITLE_MODEL* TITLE_MODEL::getInstance()
{
	static TitleData instance_;
	return &instance_;

}

void TITLE_VIEW::onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
		return;
	auto spawnAction = cocos2d::Spawn::createWithTwoActions( cocos2d::DelayTime::create(0.1), cocos2d::CallFunc::create( CC_CALLBACK_0(TitleLayer::removeFromParent,this) ) );
	this->runAction(spawnAction);

}

void TITLE_VIEW::onEnter()
{
	Layer::onEnter();
}

void TITLE_VIEW::onExit()
{
	Layer::onExit();
}

bool TITLE_VIEW::init()
{
	if( !Layer::init() )
		return false;
	
	_rootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/title.json");
	if( _rootWidget == nullptr )
		return false;
	addChild(_rootWidget);

	_closeButton  = dynamic_cast<cocos2d::ui::Button*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Btn_Close_0_0") );
	_closeButton->setVisible(true);
	_closeButton->setTouchEnabled(true);
	_closeButton->addTouchEventListener( CC_CALLBACK_2(TITLE_VIEW::onCloseCallback, this) );

	return true;

}