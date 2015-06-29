#include "WashLayer.h"
#include "cocostudio/CocoStudio.h"

#include "../UI_Bag_Info_Layer.h"

WashLayer::WashLayer()
{
}

WashLayer::~WashLayer()
{
}

void WashLayer::setVisible(bool visible)
{
	Layer::setVisible(visible);
}

bool WashLayer::init()
{
	if ( !Layer::init() )
		return false;
	
	auto root = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/refine_wash/refine_wash.ExportJson");
	addChild(root);

	_closeButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(root, "Btn_Close_0_0"));
	_closeButton->setTouchEnabled(true);
	_closeButton->addTouchEventListener( CC_CALLBACK_2(WashLayer::onCloseCallBack, this) );

	_strenthButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(root, "Button_155_0_0"));
	_strenthButton->setBrightStyle(Widget::BrightStyle::NORMAL);
	_strenthButton->setTouchEnabled(true);
	_strenthButton->addTouchEventListener( CC_CALLBACK_2(WashLayer::onStrenthCallback, this) );

	_starupButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(root, "Button_155_1_0"));
	_starupButton->setBrightStyle(Widget::BrightStyle::NORMAL);
	_starupButton->setTouchEnabled(true);
	_starupButton->addTouchEventListener( CC_CALLBACK_2(WashLayer::onStarupCallback, this) );

	_gemButton = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(root, "Button_155_2_0"));
	_gemButton->setBrightStyle(Widget::BrightStyle::NORMAL);
	_gemButton->setTouchEnabled(true);
	_gemButton->addTouchEventListener( CC_CALLBACK_2(WashLayer::onGemCallBack, this) );

	_washButton = dynamic_cast<ui::Button*>( Helper::seekWidgetByName(root, "Button_155_3") );
	_washButton->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
//	_washButton->setTouchEnabled(true);
//	_washButton->addTouchEventListener(CC_CALLBACK_2(WashLayer::onWashCallBack, this));

	return true;

}

void WashLayer::onExit()
{
	Layer::onExit();
}

void WashLayer::onEnter()
{
	Layer::onEnter();
}

void WashLayer::onStrenthCallback(Ref*pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;

	UI_Bag_Info_Layer * pBagLayer = dynamic_cast<UI_Bag_Info_Layer *>(this->getParent());
	if (pBagLayer == NULL)
		return;

	this->setVisible(false);
	pBagLayer->ChangeLayerState(Layer_State_Strengthen);
}

void WashLayer::onCloseCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;

	auto root = (Widget*)(this->getParent());
	//this->setVisible(false);

	auto Pnl_Equip_Bar = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Equip_Bar"));
	Pnl_Equip_Bar->setVisible(true);
	auto Pnl_Use = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Use"));
	Pnl_Use->setVisible(false);

	auto Pnl_Bag = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Bag"));
	Pnl_Bag->setVisible(true);
	auto Pnl_Property = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Property"));
	Pnl_Property->setVisible(false);

	auto delay = DelayTime::create(0.3);
	auto remove = CallFunc::create( CC_CALLBACK_0( WashLayer::removeFromParent,this ) );
	auto seq = Sequence::createWithTwoActions(delay,remove);
	this->runAction(seq);
	//this->removeFromParent();

}


void WashLayer::onStarupCallback(Ref*pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;

	UI_Bag_Info_Layer * pBagLayer = dynamic_cast<UI_Bag_Info_Layer *>(this->getParent());
	if (pBagLayer == NULL)
		return;

	auto delay = DelayTime::create(0.3);
	auto remove = CallFunc::create(CC_CALLBACK_0(WashLayer::removeFromParent, this));
	auto seq = Sequence::createWithTwoActions(delay, remove);
	this->runAction(seq);
	pBagLayer->ChangeLayerState(Layer_State_StarUp);

}

void WashLayer::onGemCallBack(Ref*pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;

	UI_Bag_Info_Layer * pBagLayer = dynamic_cast<UI_Bag_Info_Layer *>(this->getParent());
	if (pBagLayer == NULL)
		return;

	auto delay = DelayTime::create(0.3);
	auto remove = CallFunc::create(CC_CALLBACK_0(WashLayer::removeFromParent, this));
	auto seq = Sequence::createWithTwoActions(delay, remove);
	this->runAction(seq);
	pBagLayer->ChangeLayerState(Layer_State_Gem);

}

void WashLayer::onWashCallBack(Ref*pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;

	UI_Bag_Info_Layer * pBagLayer = dynamic_cast<UI_Bag_Info_Layer *>(this->getParent());
	if (pBagLayer == NULL)
		return;

	auto delay = DelayTime::create(0.3);
	auto remove = CallFunc::create(CC_CALLBACK_0(WashLayer::removeFromParent, this));
	auto seq = Sequence::createWithTwoActions(delay, remove);
	this->runAction(seq);

	//_strenthButton->setBrightStyle(Widget::BrightStyle::NORMAL);
	//_starupButton->setBrightStyle(Widget::BrightStyle::NORMAL);
	//_gemButton->setBrightStyle(Widget::BrightStyle::NORMAL);
	//_washButton->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);

}