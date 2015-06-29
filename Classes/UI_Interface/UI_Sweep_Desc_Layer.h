#ifndef __UI_SWEEP_DESC_LAYER_H__
#define __UI_SWEEP_DESC_LAYER_H__

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
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;
//USING_NS_CC;
//USING_NS_CC_EXT;

#define SWEEP_MAX_NUM	3

class UI_Sweep_Desc_Layer : public cocos2d::Layer
{
public:
	UI_Sweep_Desc_Layer(void);
	~UI_Sweep_Desc_Layer(void);
	
	virtual bool init();
	CREATE_FUNC(UI_Sweep_Desc_Layer);
	
	virtual void setVisible(bool visible);

    void set_is_elite_instance(int is){is_elite_instance_ = is;}
    void update();

private:
	void buttonSweepOnce( Ref *pSender ,Widget::TouchEventType type);
	void buttonSweepTwice( Ref *pSender ,Widget::TouchEventType type);
	void buttonSweepThrice( Ref *pSender ,Widget::TouchEventType type);
	void buttonCloseCallback( Ref* pSender ,Widget::TouchEventType type);
	void initComponent();

private:
	cocos2d::ui::Widget*			m_root_widget;
	cocos2d::ui::Button*			m_btn_close;

	//left area
	cocos2d::ui::Text*			m_lab_sweep_record_font;
	cocos2d::ui::Text*			m_lab_sweep_font[SWEEP_MAX_NUM];
	cocos2d::ui::Text*			m_lab_copy_award_font[SWEEP_MAX_NUM];
	cocos2d::ui::Text*			m_lab_copy_award_goods_font[SWEEP_MAX_NUM];
	cocos2d::ui::Text*			m_tea_copy_award_info[SWEEP_MAX_NUM];
	cocos2d::ui::Text*			m_tea_copy_award_goods_info[SWEEP_MAX_NUM];

	//right area
	cocos2d::ui::Text*			m_lab_sweep_times_font;
	cocos2d::ui::Text*			m_lab_current_energy_font;
	cocos2d::ui::Text*			m_lab_current_energy;
	cocos2d::ui::Text*			m_lab_sweep_sum_times_font[SWEEP_MAX_NUM];
	cocos2d::ui::Text*			m_lab_suggest_level_font;
	cocos2d::ui::Text*			m_lab_suggest_level;
	cocos2d::ui::Text*			m_lab_current_sweep_num_font;
	cocos2d::ui::Text*			m_lab_current_sweep_num;
	
	cocos2d::ui::Button*			m_btn_sweep_one;
	cocos2d::ui::Button*			m_btn_sweep_two;
	cocos2d::ui::Button*			m_btn_sweep_three;
	cocos2d::ui::Text*			m_lab_button_sweep_font[SWEEP_MAX_NUM];

    int                 is_elite_instance_;
};

#endif //__UI_SWEEP_DESC_LAYER_H__