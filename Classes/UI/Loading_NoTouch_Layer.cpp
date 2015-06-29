#include "Loading_NoTouch_Layer.h"

using namespace cocos2d;


UI::Loading_NoTouch_Layer::Loading_NoTouch_Layer()
{

}

UI::Loading_NoTouch_Layer::~Loading_NoTouch_Layer()
{

}

bool UI::Loading_NoTouch_Layer::init()
{
	if (!Layer::init() )  
	{  
		return false;  
	}  
	setTouchEnabled(true);  
	return true;  
}
#if 0
void UI::Loading_NoTouch_Layer::registerWithTouchDispatcher()
{
	Director* pDirector = Director::getInstance();  
	//pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128, true);  
	Layer::registerWithTouchDispatcher();
}
#endif
bool UI::Loading_NoTouch_Layer::TouchBegan( cocos2d::Touch *pTouch, cocos2d::Event *pEvent )
{
	return true;
}

void UI::Loading_NoTouch_Layer::TouchMoved( cocos2d::Touch *pTouch, cocos2d::Event *pEvent )
{

}

void UI::Loading_NoTouch_Layer::TouchEnded( cocos2d::Touch *pTouch, cocos2d::Event *pEvent )
{

}
