#ifndef __UI_TRADE_LAYER_H__
#define __UI_TRADE_LAYER_H__

#include "Game_Interface/common.h"

#include "cocos2d.h"
//#include "cocos-ext.h"
#include "ui/CocosGUI.h"

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
//USING_NS_CC;
//USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;
#define ATTR_SUM_NUM	2

#define	STYLE_SELL_GOODS			1 //出售物品界面
#define STYLE_BUY_GOODS				2 //购买物品界面（无属性）
#define STYLE_BUY_ATTR_GOODS		4 //购买物品界面（有属性）


class UI_Trade_Layer : public cocos2d::Layer
{
public:
	UI_Trade_Layer(void);
	~UI_Trade_Layer(void);

	virtual bool init();
	virtual void setVisible(bool visible);
	CREATE_FUNC(UI_Trade_Layer);

    void set_goods_id(uint64 goods_id){m_para = goods_id;}
	void set_style_show_info(uint64 goods_id, int style);

private:
	void removeFrame();
	void initComponent();

	void buttonSellMinusCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonBuyMinusCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonCancelCallback( Ref* pSender ,Widget::TouchEventType type);
	void setComponentVisible(bool visible);

	void showSellGoodsInfo();
	void buttonSellAddCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonSellCallback( Ref* pSender ,Widget::TouchEventType type);
	void updateSellGoodsInfo();

	void showBuyGoodsInfo();
	void showBuyAttrGoodsInfo();
	void buttonBuyAddCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonBuyCallback( Ref* pSender ,Widget::TouchEventType type);
	void updateBuyAttrGoodsInfo();
	void showAttrGoodsIconInfo();
	

private:
	static UI_Trade_Layer* instance;

private:
	cocos2d::ui::Widget*			m_wid_root;
	cocos2d::ui::Layout*			m_pan_root;

	cocos2d::ui::ImageView*		m_img_root;
	//一下控件，以分割线 m_img_line_xxx 为分界线
	cocos2d::ui::Text*			m_lab_title;
	cocos2d::ui::ImageView*		m_img_line_first;

	cocos2d::ui::TextField*			m_tea_icon_info;
	cocos2d::ui::ImageView*		m_img_line_second;

	cocos2d::ui::Text*			m_lab_attr_add[ATTR_SUM_NUM];
	cocos2d::ui::ImageView*		m_img_line_third;

	cocos2d::ui::Text*			m_lab_gain_font;
	cocos2d::ui::Text*			m_lab_trade_goods_num;
	cocos2d::ui::Text*			m_lab_gain_sum_money;
	cocos2d::ui::Text*			m_lab_btn_buy_font;
	cocos2d::ui::Text*			m_lab_btn_cancel_font;
	cocos2d::ui::ImageView*        m_img_money;
	cocos2d::ui::Button*			m_btn_minus;
	cocos2d::ui::Button*			m_btn_add;
	cocos2d::ui::Button*			m_btn_buy;
	cocos2d::ui::Button*			m_btn_cancel;
	cocos2d::ui::ImageView*		m_img_line_fourth;

	uint64              m_para;
    int                 m_trade_count;
};

#endif //__UI_BUY_LAYER_H__