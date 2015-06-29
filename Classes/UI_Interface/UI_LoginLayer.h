#ifndef _H_UI_LOGINLAYER_H___
#define _H_UI_LOGINLAYER_H___
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
#include "cocostudio/CocoStudio.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
//USING_NS_CC;
//USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;

class UI_LoginLayer:public cocos2d::Layer
{
public:
	enum CHILD_TAG
	{
		TAG_LABEL_TEXT,
	};
	cocos2d::ui::Text*			m_labTips;
	virtual bool init();
	CREATE_FUNC(UI_LoginLayer);
	void btnCallBack(Ref* pSender,Widget::TouchEventType type);
	void closeDialogCallBack(Ref* pSender,Widget::TouchEventType type);
	void notNowCallBack(Ref* pSender,Widget::TouchEventType type);
	void continueCallBack(Ref* pSender,Widget::TouchEventType type);
public:
	cocos2d::ui::Widget*			m_pWidget;
	cocos2d::ui::Button*			m_btnLogin;
	//¶Ô»°¿ò
	cocos2d::ui::ImageView*		m_imgDialog;
	cocos2d::ui::Button*			m_btnClose;
	cocos2d::ui::TextField*			m_teaUpdateTips;
	cocos2d::ui::Button*		m_tbnNotNow;
	cocos2d::ui::Text*			m_labNotNow;
	cocos2d::ui::Button*		m_tbnContinue;
	cocos2d::ui::Text*			m_labContinue;

};
#endif //_H_UI_LOGINLAYER_H___
