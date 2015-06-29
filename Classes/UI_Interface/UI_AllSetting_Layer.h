#ifndef UI_ALLSETTING_LAYER_H_H
#define UI_ALLSETTING_LAYER_H_H
#include "cocos2d.h"
//#include "cocos-ext.h"
#include "UI_SystemSetting_Layer.h"
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
USING_NS_CC;
//USING_NS_CC_EXT;
using namespace ui;
class UI_AllSetting_Layer:public cocos2d::Layer
{
public:

	enum UI_ALLSETTING {
		UI_SYSTEMSETTING=10,

	};
	UI_AllSetting_Layer(void);
	virtual ~UI_AllSetting_Layer(void);
	CREATE_FUNC(UI_AllSetting_Layer);
	virtual bool init();
	virtual void setVisible(bool visible);

public:
	//---成员变量---//
	UI_SystemSetting_Layer*		m_pSystemSetting;
	
public:
	//---按钮点击回调---//
	void						btnCallBackClose(Ref* pSender,Widget::TouchEventType type);
	void						btnCallBackSystemSetting(Ref* pSender,Widget::TouchEventType type);				// 系统设置按钮点击回调
	void						btnCallBackExit(Ref* pSender,Widget::TouchEventType type);
	void						btnCallBackAccountSetting(Ref* pSender,Widget::TouchEventType type);
	void						btnCallBackGoBackToLogin(Ref* pSender,Widget::TouchEventType type);
	void						btnCallBackShowServer(Ref* pSender,Widget::TouchEventType type);
	void						btnCallBackShowPublicAnnoucement(Ref* pSender,Widget::TouchEventType type);
	void						btnCallBackStratergy(Ref* pSender,Widget::TouchEventType type);
	
private:
	//---CocoStudio文件---//
	ui::Widget*					m_pwidget;
	ui::Button*					m_pButtonSystemSetting;					// 系统设置
	ui::Button*					m_close_settingall;
	ui::Button*					m_pButtonAccountManage;
	ui::Button*					m_pButtonGoBackToLogin;
	ui::Button*					m_pButtonShowServer;
	ui::Button*					m_pStratergy_Guaide;
	ui::Button*					btn_public_annoucement_;

	ui::Text*					lab_name_item;
	ui::Text*					lab_system_setting;
	ui::Text*					lab_account_manage;
	ui::Text*					lab_goback_to_login;
	ui::Text*					lab_strategy_guide;
	ui::Text*					lab_game_notice;
	ui::Text*					lab_show_server;
};
#endif //UI_ALLSETTING_LAYER_H_H

