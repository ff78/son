#ifndef _UI_BUTTON_LAYER_
#define _UI_BUTTON_LAYER_

#include "cocos2d.h"
//#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include "ui/UITextField.h"
#include "ui/UILoadingBar.h"
#include "ui/UILayout.h"
#include "ui/UISlider.h"
#include "ui/UICheckBox.h"
#include "ui/UIWidget.h"
#include "ui/UIScrollView.h"
#include "ui/UIDeprecated.h"
#include "ui/UIHelper.h"
#include "ui/UIPageView.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "base/ccMacros.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;
class UI_Button_Layer : public cocos2d::Layer
{
public:
	UI_Button_Layer(void);
	~UI_Button_Layer(void);

	virtual bool init();
	CREATE_FUNC(UI_Button_Layer);

	void buttonRoleCallback(Ref* pSender);//,Widget::TouchEventType type

};

#endif //_UI_BUTTON_LAYER_