#ifndef _UI_HEART_METHOD_LAYER_
#define _UI_HEART_METHOD_LAYER_

#include "cocos2d.h"
//#include "cocos-ext.h"
#include "Common/GameDefine.h"
#include "Game_Interface/common.h"
#include "UI_Goods_Grid_Layer.h"
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
//USING_NS_CC_EXT;


namespace Game_Data
{
    struct Item;
}

class UI_Icon_Info_Layer;
class UI_HeartMethod_Layer : public cocos2d::Layer
{
public:
	UI_HeartMethod_Layer(void);
	~UI_HeartMethod_Layer(void);

	virtual bool init();
	CREATE_FUNC(UI_HeartMethod_Layer);
	virtual void setVisible(bool visible);
	void showGuide();
	void guideControl();
	void setTouchEvent(bool touchOrNot);

	void buttonCloseCallback( Ref* pSender ,Widget::TouchEventType type);

    void click_bag_grid(Ref* pSender,Widget::TouchEventType type);
    void click_equipment_bar(Ref* pSender,Widget::TouchEventType type);

    void refreshBagItemInfo(uint64 container_id);
    void refreshBarItemInfo(uint64 item_id);

    void update();

	void buttonEquipmentCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonResidualPageCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonCombineCallback( Ref* pSender ,Widget::TouchEventType type);
	void tbnCallBackColseConfirm(Ref* pSender,Widget::TouchEventType type);
private:
    void update_grid_item(int index,int count,int quality,int icon,bool is_bag);
    void remove_grid_item(int index,bool is_bag);
    void ShowCharAvatar();
	void buttonQualityUpCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonOpenOrNot();

private:
	void btnCallBack_Close_Icon_Info(Ref* pSender,Widget::TouchEventType type);

	//设置人物头像
	void update_role();
	void headPhotoClickEvent( Ref* pSender ,Widget::TouchEventType type);
    int                                         m_quest_item_base_id;
	//装备提示框
    int						                    m_select_character_id;

	uint64									    m_bag_container_id[GRID_NUM];
	uint64									    m_bar_item_id[6];

private:
	cocos2d::ui::Widget*						m_pMethodWidget;
	//equipment icon
    cocos2d::ui::ImageView*					m_img_equipment_bar[6];
	//equipment back
    cocos2d::ui::ImageView*                    m_img_equipment_bar_back[6];
	
	//点击效果的背景
	cocos2d::ui::ImageView*					m_img_equipment_select_effect;
	cocos2d::ui::Text*					m_lab_role_name;
	cocos2d::ui::ImageView*					m_img_icon_dlg;

	void pnlCallBackClose(Ref* pSender,Widget::TouchEventType type);
	//头像栏 控件的获取m_select_character_id
	cocos2d::ui::ImageView*				m_img_click_head_event[7];
	cocos2d::ui::ImageView*				m_img_head_photo[7];
    cocos2d::ui::ImageView*                m_img_head_effect;
	//出战 标记
	cocos2d::ui::ImageView*				m_img_fighting_mark;
	LabelAtlas*			m_fighting_capacity;
	//Icon 信息显示框
	UI_Icon_Info_Layer*			m_pLayerIconInfo;

	cocos2d::ui::Button*					m_pBtnClose;
	cocos2d::ui::ScrollView*				m_pScrollView;
	cocos2d::ui::Button*					m_pBtnResidualPage;	//残页按钮
	cocos2d::ui::Button*					m_pBtnCombine;		//合成按钮
	cocos2d::ui::Button*					m_pBtnXinFaQualityUp;//心法升品

	//背包栏 区域
	UI_Goods_Grid_Layer*		m_pGoodsLayer;

	enum guide_index
	{
		GUIDE_XF_PINZHUANG_0 = 60,
		GUIDE_XF_PINZHUANG_1,
		GUIDE_XF_PINZHUANG_2,
		GUIDE_XF_PINZHUANG_3,
		GUIDE_XF_PINZHUANG_4,

		GUIDE_XF_STEP_0 = 80,	//keep the order
		GUIDE_XF_STEP_1,
		GUIDE_XF_STEP_2,
		GUIDE_XF_STEP_3,
		GUIDE_XF_STEP_4,

		GUIDE_XF_COMB_STEP_0 = 160,
		GUIDE_XF_COMB_STEP_1,
		GUIDE_XF_COMB_STEP_2,
		GUIDE_XF_COMB_STEP_3,
		GUIDE_XF_COMB_STEP_4,

		GUIDE_XF_QUA_UP_STEP_0 = 300,
		GUIDE_XF_QUA_UP_STEP_1,
		GUIDE_XF_QUA_UP_STEP_2,
		GUIDE_XF_QUA_UP_STEP_3,
		GUIDE_XF_QUA_UP_STEP_4,
		GUIDE_XF_QUA_UP_STEP_5,
	};
};

#endif  //_UI_HEART_METHOD_LAYER_