//
//  DialogLayer.cpp
//  son
//
//  Created by ff on 15-6-2.
//
//

#include "DialogLayer.h"
#include "DialogManager.h"
#include "ClientLogic/Utils/BaseUtils.h"


USING_NS_CC;
using namespace ui;
using namespace cocostudio;

bool DialogLayer::init()
{
    currLine = currSeg = -1;
    
    Layout *root = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromJsonFile("ui/quest_accept/quest_accept.ExportJson"));
    addChild(root);
    
    leftHeadIcon = dynamic_cast<ImageView *>(Helper::seekWidgetByName(root, "Image_head_l"));
    rightHeadIcon = dynamic_cast<ImageView *>(Helper::seekWidgetByName(root, "Image_head_r"));
    
    leftName = dynamic_cast<Text*>(Helper::seekWidgetByName(root, "txt_name_l"));
    rightName = dynamic_cast<Text*>(Helper::seekWidgetByName(root, "txt_name_r"));
    
    content = dynamic_cast<Text *>(Helper::seekWidgetByName(root, "txt_quest"));
    nextPage();
    
    root->addTouchEventListener(CC_CALLBACK_2(DialogLayer::touchBegan, this));
//    auto listener1 = EventListenerTouchOneByOne::create();
//    listener1->setSwallowTouches(true);
//    listener1->onTouchBegan = CC_CALLBACK_2(DialogLayer::touchBegan, this);
//    
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
//    _touchListener = listener1;
    return true;
}

void DialogLayer::nextPage()
{
    auto group = DialogManager::instance()->getCurrGroup();
    if (group==nullptr) {
        return;
    }
    
    auto seg = group->getCurrSeg();
    if (seg == nullptr) {
        return;
    }
    
    auto line = seg->getCurrLine();
    if (line == nullptr) {
        return;
    }
    if (seg->getDir() == 0) {
        rightHeadIcon->setVisible(false);
        leftHeadIcon->loadTexture("img/Dialogue_Role_Img/"+seg->getFaceIcon()+".png");
        leftHeadIcon->setVisible(true);
        
        rightName->setVisible(false);
        leftName->setString(seg->getFaceName());
        leftName->setVisible(true);
    }else{
        leftHeadIcon->setVisible(false);
        rightHeadIcon->loadTexture("img/Dialogue_Role_Img/"+seg->getFaceIcon()+".png");
        rightHeadIcon->setVisible(true);
        
        leftName->setVisible(false);
        rightName->setString(seg->getFaceName());
        rightName->setVisible(true);
    }
    
    content->setString(line->getContent());
    currSeg = seg->getSegId();
    currLine = seg->getCurrLineIdx();
}

void DialogLayer::touchBegan(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
        {
            if(!DialogManager::instance()->nextPage())
            {
                removeFromParent();
                return;
            }
            
            nextPage();
        }
            break;
            
        default:
            break;
    }
}