#include "UI_PowerChangeTips.h"
#define TAG_POWER  889
using namespace ui;
UI_PowerChangeTips* UI_PowerChangeTips::instance=0;
UI_PowerChangeTips::UI_PowerChangeTips()
{
	
	
	

}
UI_PowerChangeTips* UI_PowerChangeTips::sharedInstance()
{
	if(instance==0)
	{
		instance=new UI_PowerChangeTips();
	}
	return instance;
}
void UI_PowerChangeTips::showPower(int powerValue)
{
	//1����������������ʱ�������������������ȥ
	//2�������ʱ������3�����ȥ

	Scene* sc=Director::getInstance()->getRunningScene();
	if(sc)
	{
		cocos2d::Sprite* sp=(cocos2d::Sprite*)sc->getChildByTag(TAG_POWER);
		if(!sp)
		{
			sprite=cocos2d::Sprite::create("pic_power_bg.png");
			sprite->retain();
			label=LabelAtlas::create("0123456789","pic_power_shuzi.png",19,29,'0');
			label->setAnchorPoint(Vec2(0.5f,0.5f));
			label->setPosition(Vec2(sprite->getContentSize().width/2,sprite->getContentSize().height/2-17));
			up=Vec2(VisibleRect::center().x,VisibleRect::top().y+sprite->getContentSize().height/2);
			down=Vec2(VisibleRect::center().x,VisibleRect::top().y-sprite->getContentSize().height/2);
			sprite->setPosition(up);
			sprite->addChild(label);
			sc->addChild(sprite,30,TAG_POWER);
		}
	}

	label->setString(CCString::createWithFormat("%d",powerValue)->getCString());
	Point pt=sprite->getPosition();
	if(fabs(pt.y-up.y)>10)
	{
		//����������
		ActionInterval* moveDown=CCMoveTo::create(0.1f,down);
		ActionInterval* delay=CCDelayTime::create(3.0f);
		ActionInterval* moveUp=CCMoveTo::create(0.1f,up);
		FiniteTimeAction* remove=CallFuncN::create(this,callfuncN_selector(UI_PowerChangeTips::remove));
		FiniteTimeAction* se=CCSequence::create(moveDown,delay,moveUp,remove,NULL);
		sprite->runAction(se);

	}
	else
	{
		//������������
		sprite->stopAllActions();
		sprite->setPosition(down);
		ActionInterval* delay=CCDelayTime::create(3.0f);
		ActionInterval* moveUp=CCMoveTo::create(0.1f,up);
		FiniteTimeAction* remove=CallFuncN::create(this,callfuncN_selector(UI_PowerChangeTips::remove));
		FiniteTimeAction* se=CCSequence::create(delay,moveUp,remove,NULL);
		sprite->runAction(se);
	}
}
void UI_PowerChangeTips::remove(Node* node)
{
	if(!node)
	{
		node->removeFromParentAndCleanup(true);
	}
}