//
//  LoadScene.cpp
//  cosoul
//
//  Created by ff on 14-10-23.
//
//

#include "LoadScene.h"
/****************************** dely ********************************/
#include "DataModule/Little.h"
/****************************** dely ********************************/

USING_NS_CC;
using namespace ui;

bool LoadScene::init() {
    if (!Layer::init()) {
        return false;
    }
    
    bgLayer = LayerColor::create(Color4B::BLACK);
    addChild(bgLayer);
    auto loadBg = Sprite::create("ui/loading_back.png");
    auto winSize = Director::getInstance()->getWinSize();
//    loadBg->setPosition(Vec2(winSize.width/2, winSize.height/2));
    loadBg->setPosition(Vec2(winSize.width/2, 100));
    addChild(loadBg);
    bar = LoadingBar::create("ui/loading_bar.png");
//    bar->setPosition(Vec2(winSize.width/2, winSize.height/2));
    bar->setPosition(Vec2(winSize.width/2, 100));
    addChild(bar);
	/****************************** dely ********************************/
	comment_label_1 = NULL;
	commet_text_1 = "";
	commet_text_1 = Little::tips[5].content;
	comment_label_1 = LabelTTF::create(commet_text_1.c_str(), "Arial", 40);
	comment_label_1->setPosition(Vec2(winSize.width / 2, 200));
	comment_label_1->setColor(ccc3(254, 255, 217));
	this->addChild(comment_label_1, 100);
	/****************************** dely ********************************/
    return true;
}

void LoadScene::updateLoadBar(float percent)
{
	/****************************** dely ********************************/
	if (comment_label_1)
	{
		int proportion = percent;
		char buff[128] = { 0 };
		std::sprintf(buff, "( %d", proportion);

		std::string tmp = buff;
		tmp += "% )";
		tmp = commet_text_1 + tmp;
		comment_label_1->setString(tmp.c_str());
	}
	/****************************** dely ********************************/

    bar->setPercent(percent);
}
