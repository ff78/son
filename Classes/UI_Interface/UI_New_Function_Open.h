#ifndef __UI_NEW_FUNCTION_OPEN__
#define __UI_NEW_FUNCTION_OPEN__

#include "cocos2d.h"
//#include "cocos-ext.h"
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
//USING_NS_CC;
//USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;
class UI_New_Function_Open : public cocos2d::Layer
{
public:
	UI_New_Function_Open(void);
	~UI_New_Function_Open(void);

	virtual bool init();
	virtual void setVisible(bool visible);
	CREATE_FUNC(UI_New_Function_Open);

public:
	void initComponentUI();
	void clickPanel( Ref* pSender ,Widget::TouchEventType type);
	void closeOpenNotice();
	void othersVisibleCallback();
	void showPromptInfo( int iconNameId, int iconOpenId );

private:
	cocos2d::ui::Widget			*m_pRootWidget;
	cocos2d::ui::Layout				*m_pRootPanel;
	cocos2d::ui::ImageView			*m_pImgIconBack;
	cocos2d::ui::ImageView			*m_pImgIconPic;
	cocos2d::ui::Text				*m_pLabFuncName;

};

#endif //__UI_NEW_FUNCTION_OPEN__
