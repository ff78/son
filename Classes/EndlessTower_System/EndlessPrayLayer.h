//
//  EndlessPrayLayer.h
//  son
//
//  Created by ff on 15-6-8.
//
//

#ifndef __son__EndlessPrayLayer__
#define __son__EndlessPrayLayer__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class EndlessPrayLayer : public cocos2d::Layer
{
public:
    bool init();
    CREATE_FUNC(EndlessPrayLayer);
    void									onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
};

#endif /* defined(__son__EndlessPrayLayer__) */
