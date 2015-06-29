#ifndef UI_SYSTEM_SETTING_LAYER
#define UI_SYSTEM_SETTING_LAYER
#include "cocos2d.h"
//#include "cocos-ext.h"
#include "Player_Account/RecentlyServer.h"
#include "Common/GameDefine.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include "ui/UITextField.h"
#include "ui/UILoadingBar.h"
#include "ui/UILayout.h"
#include "ui/UISlider.h"
#include "ui/UICheckBox.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "ui/UISlider.h"
#include "ui/UICheckBox.h"
#include "cocostudio/CocoStudio.h"
#include "Common/Utils.h"

USING_NS_CC;
using namespace ui;
//USING_NS_CC;
//USING_NS_CC_EXT;
class UI_SystemSetting_Layer:public cocos2d::Layer
{
public:
	UI_SystemSetting_Layer(void);
	virtual ~UI_SystemSetting_Layer(void);
	virtual bool init();
	CREATE_FUNC(UI_SystemSetting_Layer);

	
public:
	//---按钮点击回调---//	
	void					btnCallBackClose(Ref* pSender,Widget::TouchEventType type);

	void					sldCallBackMusic(Ref* pSender,Widget::TouchEventType type);
	void					sldCallBackEffect(Ref* pSender,Widget::TouchEventType type);
	void					sldCallBackMusicMoved(Ref* pSender,cocos2d::ui::SliderEventType type);
	void					sldCallBackEffectMoved(Ref* pSender,cocos2d::ui::SliderEventType type);
	
	void					ckbCallBackMusicUnSelect(Ref* pSender,CheckBoxEventType  type);
	void					ckbCallBackMusicSelect(Ref* pSender,CheckBoxEventType type);


	void					ckbCallBackEffectSelect(Ref* pSender,CheckBoxEventType  type);
	void					ckbCallBackEffectUnSelect(Ref* pSender,CheckBoxEventType  type);

	void					ckbCallBackShieldSelect(Ref* pSender,CheckBoxEventType  type);
	void					ckbCallBackShieldUnSelect(Ref* pSender,CheckBoxEventType  type);

private:
	//---CocoStudio文件---//
	ui::Text*				lab_name_item;
	ui::Text*				lab_music;
	ui::Text*				lab_effect;
	ui::Text*				lab_shield;
	ui::Text*				m_pshowmusic;
	ui::Text*				m_pshoweffec;

	
	ui::Slider*				m_psldmusic;
	ui::Slider*				m_psldeffect;

	ui::CheckBox*			m_pckbmusic;
	ui::CheckBox*			m_pckbeffect;
	ui::CheckBox*			m_ckbplayermodel;

	ui::Widget*				m_pwidget;

	ui::Button*				m_pbtnclose;
	
};
#endif //UI_SYSTEM_SETTING_LAYER

