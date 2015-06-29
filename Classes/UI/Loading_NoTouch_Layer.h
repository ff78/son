
#ifndef _LOADING_NOTOUCH_LAYER_H_
#define _LOADING_NOTOUCH_LAYER_H_
#include "cocos2d.h"
#include "Common/Utils.h"
//#include "ui/CocosGUI.h"
//USING_NS_CC;
//using namespace ui;
namespace UI
{

	class Loading_NoTouch_Layer : public cocos2d::Layer
	{
	public:
		Loading_NoTouch_Layer();
		~Loading_NoTouch_Layer();
		CREATE_FUNC (Loading_NoTouch_Layer);
		virtual bool init();

		//virtual void registerWithTouchDispatcher(); 

		virtual bool TouchBegan (cocos2d::Touch *pTouch, cocos2d::Event *pEvent); 
		virtual void TouchMoved (cocos2d::Touch *pTouch, cocos2d::Event *pEvent); 
		virtual void TouchEnded (cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

	};

}

#endif //_LOADING_NOTOUCH_LAYER_H_