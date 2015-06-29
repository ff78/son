#ifndef __UI_TIMELIMITEDINSTANCE_LAYER_H__
#define __UI_TIMELIMITEDINSTANCE_LAYER_H__
#include "cocos2d.h"
#include "UI/Loading_Scene.h"
#include "Common/GameMacro.h"
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
#include "Common/Utils.h"
USING_NS_CC;
using namespace UI;
#define MSG_FONT_SIZE 32
class UI_TimeLimitedInstance_Layer:public Layer
{

private:
	UI_TimeLimitedInstance_Layer();
	static UI_TimeLimitedInstance_Layer* instance;
	int allTime;
	void setLabelText();
public:
	virtual bool init();
	static UI_TimeLimitedInstance_Layer* sharedInstance();
	void showTime(int timeInSecond);
	void removeTime();
	void scheduleCallBack(float dt);

	LabelAtlas*		m_pLabelAtlas; 
};

#endif //__UI_TIMELIMITEDINSTANCE_LAYER_H__