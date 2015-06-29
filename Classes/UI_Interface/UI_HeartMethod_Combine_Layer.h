#ifndef _UI_HEART_METHOD_COMBINE_LAYER_
#define _UI_HEART_METHOD_COMBINE_LAYER_

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
//USING_NS_CC;
//USING_NS_CC_EXT;

#define ROLE_EQUIP_BOOK_SUM_NUM	6


class UI_Icon_Info_Layer;
class UI_HeartMethod_Combine_Layer : public cocos2d::Layer
{
public:
	UI_HeartMethod_Combine_Layer(void);
	~UI_HeartMethod_Combine_Layer(void);

	virtual bool init();
	CREATE_FUNC(UI_HeartMethod_Combine_Layer);
	virtual void setVisible(bool visible);


	void setTouchEvent(bool touchOrNot);

	void click_bag_grid(Ref* pSender,Widget::TouchEventType type);
	void click_equipment_bar(Ref* pSender,Widget::TouchEventType type);
	void showChangeInfo();

	void update();

	void buttonCloseCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonEquipmentCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonResidualPageCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonXinFaMainCallback( Ref* pSender ,Widget::TouchEventType type);

private:
	void update_grid_item(int index,int count,int quality,int icon,bool is_bag);
	void remove_grid_item(int index,bool is_bag);
	void ShowCharAvatar();
	void buttonQualityUpCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonOpenOrNot();

	void btnEatCallback( Ref* pSender ,Widget::TouchEventType type);
	void btnResetCallback( Ref* pSender ,Widget::TouchEventType type);

	void update_role();
	void headPhotoClickEvent( Ref* pSender ,Widget::TouchEventType type);
	int                         m_quest_item_base_id;

private:
	cocos2d::ui::Widget*					m_pMethodWidget;

	int						    m_select_character_id;
	uint64						m_bag_item_id[GRID_NUM];
	uint64						m_bar_item_id[EACH_PAGE_NUM]; //存放数量 更改宏定义
    int				            m_select_equip_book_index;

	//角色所穿心法 6个框
	cocos2d::ui::ImageView*				m_img_equipment_bar[ROLE_EQUIP_BOOK_SUM_NUM];
	cocos2d::ui::ImageView*                m_img_equipment_bar_back[ROLE_EQUIP_BOOK_SUM_NUM];
	cocos2d::ui::ImageView*				m_img_equipment_select_effect;
	cocos2d::ui::Text*					m_lab_role_name;

	//头像栏 控件的获取 m_select_character_id
	cocos2d::ui::ImageView*				m_img_click_head_event[UI_HEAD_SUM_NUM];
	cocos2d::ui::ImageView*				m_img_head_photo[UI_HEAD_SUM_NUM];
	cocos2d::ui::ImageView*                m_img_head_effect;
	cocos2d::ui::ImageView*				m_img_fighting_mark;

	cocos2d::ui::Button*					m_pBtnClose;
	cocos2d::ui::Button*					m_btn_xinfa_main;		//心法
	cocos2d::ui::Button*					m_btn_xinfa_canye;		//残页
	cocos2d::ui::Button*					m_btn_xinfa_quality_up;	//升品

	//背包栏 区域
	UI_Goods_Grid_Layer*		m_pGoodsLayer;

	//心法内容变化信息显示区
	cocos2d::ui::Text*				m_lab_xinfa_name;
	cocos2d::ui::Text*				m_lab_xinfa_level;
	cocos2d::ui::LoadingBar*			m_load_xinfa_exp;
	cocos2d::ui::Text*				m_lab_xinfa_need_money;

private:
	enum guide_step
	{
		GUIDE_XF_COMB_STEP_0 = 160,
		GUIDE_XF_COMB_STEP_1,
		GUIDE_XF_COMB_STEP_2,
		GUIDE_XF_COMB_STEP_3,
		GUIDE_XF_COMB_STEP_4,
		GUIDE_XF_COMB_STEP_5,
		GUIDE_XF_COMB_STEP_6,
	};
};

#endif  //_UI_HEART_METHOD_COMBINE_LAYER_
