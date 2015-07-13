//
//  DialogLayer.h
//  son
//
//  Created by ff on 15-6-2.
//
//

#ifndef __son__DialogLayer__
#define __son__DialogLayer__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class DialogLayer : public cocos2d::Layer
{
public:
    bool init();
    
    CREATE_FUNC(DialogLayer);
    
    void nextPage();
    
    void update(float delta);
    
    void touchBegan(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
private:
    CC_SYNTHESIZE_READONLY(int, currSeg, CurrSeg);
    CC_SYNTHESIZE_READONLY(int, currLine, currLine);
    
    CC_SYNTHESIZE_READONLY(cocos2d::ui::ImageView *, leftHeadIcon, LeftHeadIcon);
    CC_SYNTHESIZE_READONLY(cocos2d::ui::ImageView *, rightHeadIcon, RightHeadIcon);
    
    CC_SYNTHESIZE_READONLY(cocos2d::ui::Text *, leftName, LeftName);
    CC_SYNTHESIZE_READONLY(cocos2d::ui::Text *, rightName, RightName);
    
    CC_SYNTHESIZE_READONLY(cocos2d::ui::Text *, content, Content);
    CC_SYNTHESIZE_READONLY(bool, stayOver, StayOver);
    float currentTime;
};

#endif /* defined(__son__DialogLayer__) */
