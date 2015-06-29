#ifndef __UI_ACTIVITY_SIX_SECT_LAYER__
#define __UI_ACTIVITY_SIX_SECT_LAYER__

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
USING_NS_CC;
//USING_NS_CC_EXT;
using namespace ui;
#define CUR_LAY_AREA_NUM	3

class UI_Activity_Six_Sect_Layer : public cocos2d::Layer
{
public:
	UI_Activity_Six_Sect_Layer(void);
	~UI_Activity_Six_Sect_Layer(void);

	virtual bool init();
	virtual void setVisible(bool visible);
	CREATE_FUNC(UI_Activity_Six_Sect_Layer);

    void update();

private:
	void initComponent();
	void btnCloseCallback( Ref* pSender ,Widget::TouchEventType type);
	void btnRealEnterCallback( Ref* pSender ,Widget::TouchEventType type);

    void update_grid(int index,int name,int icon,int time,int reward,int level,int energy,int cur_count,int join_count);
    void remove_grid(int index);

private:
	cocos2d::ui::Widget*				m_root_widget;
	cocos2d::ui::Button*				m_btn_close;

	//三个大框中的显示信息
	cocos2d::ui::ImageView*			m_img_root_back[CUR_LAY_AREA_NUM];
	cocos2d::ui::Text*				m_lab_area_title_font[CUR_LAY_AREA_NUM];
	cocos2d::ui::ImageView*			m_img_area_texture[CUR_LAY_AREA_NUM];

	cocos2d::ui::Text*				m_lab_pass_award_font;
	cocos2d::ui::Text*				m_lab_pass_award[CUR_LAY_AREA_NUM];
	cocos2d::ui::Text*				m_lab_open_level_font;
	cocos2d::ui::Text*				m_lab_open_level[CUR_LAY_AREA_NUM];
	cocos2d::ui::Text*				m_lab_need_energy_font;
	cocos2d::ui::Text*				m_lab_need_energy[CUR_LAY_AREA_NUM];
	cocos2d::ui::Text*				m_lab_open_time_font;
	cocos2d::ui::Text*				m_lab_open_time[CUR_LAY_AREA_NUM];
	cocos2d::ui::Text*				m_lab_enter_times_font;
	cocos2d::ui::Text*				m_lab_enter_times[CUR_LAY_AREA_NUM];

	cocos2d::ui::Button*				m_btn_real_enter[CUR_LAY_AREA_NUM];
	cocos2d::ui::Text*				m_lab_enter_font;

    int                     m_six_sect_id[CUR_LAY_AREA_NUM];
};

#endif //__UI_ACTIVITY_SIX_SECT_LAYER__