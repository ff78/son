#ifndef __UI_SHOP_CENTER_LAYER__
#define __UI_SHOP_CENTER_LAYER__

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
USING_NS_CC;
using namespace ui;
USING_NS_CC;
//USING_NS_CC_EXT;

#define PAGE_SUM_NUM_S		3
#define EACH_PAGE_NUM_S		9
#define FONT_SIZE_S			25

#define GRID_NUM_S          PAGE_SUM_NUM_S*EACH_PAGE_NUM_S		//总格子数

class UI_Shop_Center_Layer : public cocos2d::Layer
{
public:
	UI_Shop_Center_Layer(void);
	~UI_Shop_Center_Layer(void);

	virtual bool init();
	virtual void setVisible(bool visible);
	CREATE_FUNC(UI_Shop_Center_Layer);

    void update();

private:
	void initComponent();
	void buttonCloseCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonFirstCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonSecondCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonThirdCallback( Ref* pSender ,Widget::TouchEventType type);
	void leftArrowCallback( Ref* pSender ,Widget::TouchEventType type);
	void rightArrowCallback( Ref* pSender ,Widget::TouchEventType type);
	void controlVisibleOrNot( bool visible );

	cocos2d::ui::ImageView* createPageView();
	void pageViewEvent(Ref *pSender, cocos2d::ui::PageViewEventType type);
	void goodsSellInfoCallback( Ref* pSender ,Widget::TouchEventType type);
	void btnChargeMoneyCallback( Ref* pSender ,Widget::TouchEventType type);

    void update_grid_item(int index,int icon,int name,int money_type,int cost,int discount,int last_count);
    void remove_grid_item(int index);
	void show_player_info(int money_type);

private:
	cocos2d::ui::Widget*				m_root_widget;
	cocos2d::ui::Button*				m_btn_close;

	//按钮切换区
	cocos2d::ui::Button*			m_tbn_first;
	cocos2d::ui::Text*				m_lab_first_font;
	cocos2d::ui::Button*			m_tbn_second;
	cocos2d::ui::Text*				m_lab_second_font;
	cocos2d::ui::Button*			m_tbn_third;
	cocos2d::ui::Text*				m_lab_third_font;

	cocos2d::ui::ImageView*			m_img_player_cur_money_texture;
	cocos2d::ui::Text*				m_lab_player_cur_money;

	//物品滑动区
	cocos2d::ui::ImageView*			m_img_left_arrow;
	cocos2d::ui::ImageView*			m_img_right_arrow;
	cocos2d::ui::ImageView*			m_img_second_back;

	cocos2d::ui::ImageView*			m_img_scroll_back;
	cocos2d::ui::ImageView*			m_img_scroll_copy_back;
	cocos2d::ui::PageView*				m_page_view;
	cocos2d::ui::ImageView*			m_img_icon_root_back[PAGE_SUM_NUM_S][EACH_PAGE_NUM_S];
	cocos2d::ui::ImageView*			m_img_icon_texture_back[PAGE_SUM_NUM_S][EACH_PAGE_NUM_S];
	cocos2d::ui::ImageView*			m_img_icon_texture[PAGE_SUM_NUM_S][EACH_PAGE_NUM_S];
	cocos2d::ui::Text*				m_lab_icon_number[PAGE_SUM_NUM_S][EACH_PAGE_NUM_S];
	cocos2d::ui::Text*				m_lab_icon_name[PAGE_SUM_NUM_S][EACH_PAGE_NUM_S];

	cocos2d::ui::ImageView*			m_img_delete_line[PAGE_SUM_NUM_S][EACH_PAGE_NUM_S];
	cocos2d::ui::ImageView*			m_img_original_texture[PAGE_SUM_NUM_S][EACH_PAGE_NUM_S];
	cocos2d::ui::Text*				m_lab_original_price[PAGE_SUM_NUM_S][EACH_PAGE_NUM_S];
	cocos2d::ui::ImageView*			m_img_discount_texture[PAGE_SUM_NUM_S][EACH_PAGE_NUM_S];
	cocos2d::ui::Text*				m_lab_discount_price[PAGE_SUM_NUM_S][EACH_PAGE_NUM_S];

	cocos2d::ui::ImageView*			m_img_light_reflect_cur_page[PAGE_SUM_NUM_S];
	cocos2d::ui::Text*				m_lab_vision_page;
	cocos2d::ui::Button*				m_btn_charge_money;
	cocos2d::ui::Text*				m_lab_btn_font;

	int						m_cur_shop_type;	        //当前商店类型
    int						m_goods_id[GRID_NUM_S];	    //当前商店类型

};

#endif //__UI_SHOP_CENTER_LAYER__