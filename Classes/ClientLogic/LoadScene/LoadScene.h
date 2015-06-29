//
//  LoadScene.h
//  cosoul
//
//  Created by ff on 14-10-23.
//
//

#ifndef __cosoul__LoadScene__
#define __cosoul__LoadScene__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class LoadScene :public cocos2d::Layer {
public:
    //实现init，初始化界面等
    virtual bool init();
    
    CREATE_FUNC(LoadScene);
    
    void updateLoadBar(float percent);
    
public:
    cocos2d::LayerColor *bgLayer;
    
    cocos2d::ProgressTimer *progress;
    cocos2d::ui::LoadingBar *bar;
	/****************************** dely ********************************/
	std::string commet_text_1;
	cocos2d::LabelTTF *comment_label_1;
	/****************************** dely ********************************/

};

#endif /* defined(__cosoul__LoadScene__) */
