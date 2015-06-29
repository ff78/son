#ifndef __H_UI_POWERCHANGETIPS
#define __H_UI_POWERCHANGETIPS
#include "cocos2d.h"
#include "math.h"
#include "Common/VisibleRect.h"
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
#include "cocostudio/CocoStudio.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
USING_NS_CC;
USING_NS_CC;
using namespace ui;
class UI_PowerChangeTips:public Node
{
private:
	UI_PowerChangeTips();
	static UI_PowerChangeTips* instance;
	cocos2d::Sprite* sprite;
	LabelAtlas* label;
	Point up,down;

public:
	static UI_PowerChangeTips* sharedInstance();
	void showPower(int powerValue);
	void remove(Node* node);
};
#endif //__H_UI_POWERCHANGETIPS
