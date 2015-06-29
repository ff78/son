#ifndef __UI_ACTIVITY_LAYER__
#define __UI_ACTIVITY_LAYER__

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
USING_NS_CC;
using namespace ui;
//USING_NS_CC_EXT;

#define PAGE_SUM_NUM_ACT	2
#define EACH_PAGE_NUM_ACT	6

#define GRID_NUM_ACT        PAGE_SUM_NUM_ACT*EACH_PAGE_NUM_ACT		//总格子数

#define FONT_SIZE_ACT		25

#define SCROLL_LAYER_WIDTH		940
#define SCROLL_LAYER_HEIGHT		280

#define  pTagPageView			88
class UI_Activity_Layer : public cocos2d::Layer
{
public:
	UI_Activity_Layer(void);
	~UI_Activity_Layer(void);

	virtual bool init();
	virtual void setVisible(bool visible);
	CREATE_FUNC(UI_Activity_Layer);

    void update();

private:
	void reset_select_effect_ui();
	void initComponent();
	cocos2d::ui::PageView* createScrollViewLayer();
	void clickActivityInfo( Ref* pSender ,Widget::TouchEventType type);
	void btnCloseCallback( Ref* pSender ,Widget::TouchEventType type);
	void btnEnterCallback( Ref* pSender ,Widget::TouchEventType type);

    void update_grid(int index,int icon,int name,int time);
    void remove_grid(int index);
    
    void show_activity_layer();
    void show_activity_info();

private:
	cocos2d::ui::Widget*			m_root_widget;
	cocos2d::ui::PageView*			m_page_view;

	cocos2d::ui::Button*				m_btn_close;

	//滚动层显示区
	cocos2d::ui::ImageView*			m_img_icon_root_back[PAGE_SUM_NUM_ACT][EACH_PAGE_NUM_ACT];
	cocos2d::ui::ImageView*			m_img_icon_texture_back[PAGE_SUM_NUM_ACT][EACH_PAGE_NUM_ACT];
	cocos2d::ui::ImageView*			m_img_icon_texture[PAGE_SUM_NUM_ACT][EACH_PAGE_NUM_ACT];
	cocos2d::ui::Text*				m_lab_activity_name[PAGE_SUM_NUM_ACT][EACH_PAGE_NUM_ACT];
	cocos2d::ui::Text*				m_lab_activity_time[PAGE_SUM_NUM_ACT][EACH_PAGE_NUM_ACT];
	cocos2d::ui::ImageView*			m_img_select_effect[PAGE_SUM_NUM_ACT];

	//信息显示区域
	cocos2d::ui::Text*				m_lab_title_level;
	cocos2d::ui::Text*				m_lab_level_info;
	cocos2d::ui::Text*				m_lab_title_time;
	cocos2d::ui::Text*				m_lab_time_info;
	cocos2d::ui::Text*				m_lab_title_intr;
	cocos2d::ui::TextField*				m_tea_intr_info;
	cocos2d::ui::Text*				m_lab_title_award;
	cocos2d::ui::Text*				m_lab_award_info;

	cocos2d::ui::Button*				m_btn_enter;
	cocos2d::ui::Text*				m_lab_enter_font;

    int                     m_activity_type[GRID_NUM_ACT];
    int                     m_select_index;

};

#endif //__UI_ACTIVITY_LAYER__