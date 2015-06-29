#include "UI_TimeLimitedInstance_Layer.h"

using namespace ui;
UI_TimeLimitedInstance_Layer::UI_TimeLimitedInstance_Layer()
{
	allTime=10;
}
bool UI_TimeLimitedInstance_Layer::init()
{
	bool ret=false;
	do 
	{
		CC_BREAK_IF(!Layer::init());
		cocos2d::Size size=Director::getInstance()->getVisibleSize();

		m_pLabelAtlas = LabelAtlas::create("0123456789:", "countdown.png", 29, 39, '0');
		CC_BREAK_IF( !m_pLabelAtlas );
		m_pLabelAtlas->setPosition(Vec2(size.width/2,size.height*3/4));
		this->addChild(m_pLabelAtlas);

		ret=true;
	} while (0);
	return ret;
}
UI_TimeLimitedInstance_Layer* UI_TimeLimitedInstance_Layer::instance=NULL;
UI_TimeLimitedInstance_Layer* UI_TimeLimitedInstance_Layer::sharedInstance()
{
	if(instance==NULL)
	{
		instance =new UI_TimeLimitedInstance_Layer();
		if(instance&&instance->init())
		{
			return instance;
		}
		else
		{
			delete instance;
			instance=NULL;
		}
	}
	return instance;
}
void UI_TimeLimitedInstance_Layer::showTime(int timeInSecond)
{
	//???????????
	Scene* scene=Director::getInstance()->getRunningScene();
	if(!scene)
	{
		return;
	}

	UI_TimeLimitedInstance_Layer* child=dynamic_cast<UI_TimeLimitedInstance_Layer*>(scene->getChildByTag(TAG_TIMELIMITED_UI));
	if(!child)
	{

		child = this;
		scene->addChild(child, TAG_TIMELIMITED_UI,TAG_TIMELIMITED_UI);
	}
	allTime=timeInSecond;
	this->m_pLabelAtlas->setString("");
	//????????
	this->schedule(schedule_selector(UI_TimeLimitedInstance_Layer::scheduleCallBack),1,-1,0);
}
void UI_TimeLimitedInstance_Layer::scheduleCallBack(float dt)
{
	allTime-=1;
	if(allTime<=0)
	{
		allTime=0;
	}
	setLabelText();
}
void UI_TimeLimitedInstance_Layer::setLabelText()
{
	int	minute=allTime/60;
	int second=allTime%60;
	char temp[64]={0};
	if(minute<10 && second<10)
	{
		SPRINTF(temp,"0%d:0%d",minute,second);
	}
	else if( minute < 10 )
	{
		SPRINTF(temp,"0%d:%d",minute,second);
	}
	else if( second < 10 )
	{
		SPRINTF(temp,"%d:0%d",minute,second);
	}
	else
	{
		SPRINTF(temp,"%d:%d",minute,second);
	}
	
	m_pLabelAtlas->setString(temp);
}
void UI_TimeLimitedInstance_Layer::removeTime()
{
	Scene* scene=Director::getInstance()->getRunningScene();
	if(!scene)
	{
		return;
	}

	UI_TimeLimitedInstance_Layer* child=dynamic_cast<UI_TimeLimitedInstance_Layer*>(scene->getChildByTag(TAG_TIMELIMITED_UI));
	if(child)
	{
		child->m_pLabelAtlas->setString("");
		scene->removeChildByTag(TAG_TIMELIMITED_UI);
	}
}