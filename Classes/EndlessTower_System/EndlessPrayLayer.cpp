//
//  EndlessPrayLayer.cpp
//  son
//
//  Created by ff on 15-6-8.
//
//

#include "EndlessPrayLayer.h"

USING_NS_CC;
using namespace ui;

bool EndlessPrayLayer::init()
{
    if( !Layer::init() )
        return false;
    
    auto _rootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/endlesstower_jackpot.json");
    if( _rootWidget == nullptr )
        return false;
    addChild(_rootWidget);
    
    auto _closeButton  = dynamic_cast<Button*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Button_close") );
    _closeButton->setVisible(true);
    _closeButton->setTouchEnabled(true);
    _closeButton->addTouchEventListener(CC_CALLBACK_2(EndlessPrayLayer::onCloseCallback, this));
    return true;
}

void EndlessPrayLayer::onCloseCallback(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
        return;
    removeFromParent();
}