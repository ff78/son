#ifndef _UI_TIPS_LAYER_
#define _UI_TIPS_LAYER_

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
#include "ui/UIText.h"
#include "ui/UITextAtlas.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
//#include "LabelAtlas.h"

#include "cocostudio/CocoStudio.h"
using namespace cocos2d::ui;
USING_NS_CC;
using namespace ui;
#define COUNT_DOWN_TIME_MAX 15

class UI_Tips_Layer : public cocos2d::Layer
{
public:
	UI_Tips_Layer(void);
	~UI_Tips_Layer(void);

	virtual bool init();
	CREATE_FUNC(UI_Tips_Layer);

	virtual void setVisible(bool visible);

	void buttonChangeRoleCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonRecoveryCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonGiveUpCallback( Ref* pSender ,Widget::TouchEventType type);

    void show();

private:
	void set_count_time_down(int count_down_time);
	void update_time(float dt);
	void back_to_city();
private:
	//cocos2d::ui::Text* lab_time_num_;
	int count_down_time_;
	cocos2d::ui::ImageView*					m_img_root_dlg;
	/*****************************¸´»îÏµÍ³***************************************/
	cocos2d::ui::ImageView*					m_img_confirm_dlg;
	cocos2d::ui::Text*						m_lab_confirm_time;
	cocos2d::ui::Text*						m_lab_fight_again;
	cocos2d::ui::Text*						m_money_expend_number;
	cocos2d::ui::Text*						m_lab_yuanbaotext;
	cocos2d::ui::Text*						m_lab_expendtext;
   // UIButton*						m_btn_change_role;

	cocos2d::ui::TextAtlas*					m_mTimeLeft;
    cocos2d::ui::Button*						m_btn_recovery;
    cocos2d::ui::Button*						m_btn_give_up;
	cocos2d::ui::Button*						m_btn_sure;
	cocos2d::ui::Button*						m_btn_cancel;
	cocos2d::ui::Text*						m_lab_canceltext;
	cocos2d::ui::Text*						m_lab_suretext;
	void btnCallBackSure(Ref* pSender,Widget::TouchEventType type);
	void btnCallBackCancel(Ref* pSender,Widget::TouchEventType type);
	/****************************************************************************/


};

#endif //_UI_TIPS_LAYER_