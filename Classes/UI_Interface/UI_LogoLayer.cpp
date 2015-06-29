#include "UI_LogoLayer.h"
#include <string>
#include "Platform_Dependence/Dependence.h"
using namespace std;
using namespace ui;
bool UI_LogoLayer::init()
{
	bool ret=false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		cocos2d::Size sz=Director::getInstance()->getVisibleSize();
		string  logoName;
#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32||CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		logoName="ui/Loading/logo_for_windows.png";
#elif(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		logoName=Dependence::getLogoName();
#else
		logoName="ui/Loading/logo_for_windows.png";
#endif
		//create logo sprite
		CCLog("%s",logoName.c_str());
		cocos2d::Sprite *logo=cocos2d::Sprite::create(logoName.c_str());
		logo->setPosition(Vec2(sz.width/2,sz.height/2));
		this->addChild(logo);
		ret=true;
	} while (0);
	return ret;
}
