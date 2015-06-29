#ifndef _UI_HEART_METHOD_QUALITY_UP_LAYER_
#define _UI_HEART_METHOD_QUALITY_UP_LAYER_

#include "cocos2d.h"
//#include "cocos-ext.h"
#include "Game_Interface/common.h"
#include "Common/GameDefine.h"
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
//USING_NS_CC_EXT;
//USING_NS_CC;
using namespace ui;
class UI_Icon_Info_Layer;


class UI_HeartMethod_Quality_Up_Layer : public cocos2d::Layer
{
public: 
	UI_HeartMethod_Quality_Up_Layer(void);
	~UI_HeartMethod_Quality_Up_Layer(void);

public:
	virtual bool init();
	CREATE_FUNC(UI_HeartMethod_Quality_Up_Layer);
	void setVisible( bool visible );
	void set_up_item_id(uint64 item_id){m_item_id = item_id;}
	void update();
	
	void clickMaterialCallback( Ref* pSender ,Widget::TouchEventType type);
    void update_need_material(int cur_quality);

private:
	cocos2d::ui::Text*			m_lab_quality_before_font;
	cocos2d::ui::Text*			m_lab_quality_after_font;
	uint64									m_item_id;
	UI_Icon_Info_Layer*						m_pLayerIconInfo;

public:
	cocos2d::ui::Widget*			m_HM_Quality_Up_Widget;
	//成员
	/*********************上面的四个按钮和关闭按钮************************************/
	cocos2d::ui::Button*						button_close;//关闭按钮
	cocos2d::ui::Button*						button_heart_method;//心法
	cocos2d::ui::Button*						button_combine;//合成
	cocos2d::ui::Button*						m_btn_canye;//残页
	void buttonCloseCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonHeartMethodCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonCombineCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonCanyeCallback( Ref* pSender ,Widget::TouchEventType type);
	/*******************************************************************************/
	cocos2d::ui::ImageView*				m_img_fighting_mark;
	cocos2d::ui::ImageView*                m_img_head_effect;
	cocos2d::ui::ImageView*				m_img_click_head_event[UI_HEAD_SUM_NUM];
	cocos2d::ui::ImageView*				m_img_head_photo[UI_HEAD_SUM_NUM];
	int						                    m_select_character_id;
	void update_role();
	void update_role(int character_id);
	void headPhotoClickEvent(Ref* pSender,Widget::TouchEventType type);
	void setSelectBook();
	
	/*****************************************************************************************/
	/********************************中间的人物装备和战力值*************************************/
	//玩家名字
	cocos2d::ui::Text*							m_lab_role_name;
	//equipment icon
	cocos2d::ui::ImageView*					m_img_equipment_bar[6];
	//equipment back
	cocos2d::ui::ImageView*                    m_img_equipment_bar_back[6];
	//显示选中的装备
	cocos2d::ui::ImageView*					m_img_equipment_select_effect;
	//战力值
	LabelAtlas*			m_fighting_capacity;
	//这里面是装备的id
	uint64									    m_bar_item_id[6];
	void update_grid_item(int index,int count,int quality,int icon,bool is_bag);
	void remove_grid_item(int index,bool is_bag);
	void ShowCharAvatar();
	void click_equipment_bar(Ref* pSender,Widget::TouchEventType type);
	/*****************************************************************************************/
	/********************************右边的一些控件********************************************/
	//升品前的 图片框
	cocos2d::ui::ImageView*		m_img_hm_quality_before_back;
	//升品前的 图标
	cocos2d::ui::ImageView*		m_img_hm_quality_before;
	//心法名
	cocos2d::ui::Text*			m_lab_hm_name;
	//心法等级
	cocos2d::ui::Text*			m_lab_before_level;
	//前面的描述
	cocos2d::ui::Text*			m_lab_desc[4];
	cocos2d::ui::Text*			m_lab_quality_up_before_info[4];


	//升品后的 图片框
	cocos2d::ui::ImageView*		m_img_hm_quality_after_back;
	cocos2d::ui::ImageView*		m_img_hm_quality_after;
	//心法名
	cocos2d::ui::Text*			m_lab_after_name;
	//心法等级
	cocos2d::ui::Text*			m_lab_after_level;
	//升品前  升品后的属性
	cocos2d::ui::Text*			m_lab_quality_up_after_info[4];

	//升品所需材料的3个框
	cocos2d::ui::ImageView*		m_img_material[3];
	cocos2d::ui::ImageView*		m_img_material_back[3];
	cocos2d::ui::Text*		m_lab_material_need_num[3];

	//升品按钮 
	cocos2d::ui::Button*						m_tbn_quality_up;
	//按钮的点击事件
	void buttonQualityUpCallback( Ref* pSender ,Widget::TouchEventType type);
	/*****************************************************************************************/

private:
	enum guide_index
	{
		GUIDE_XF_QUA_UP_STEP_0 = 300,
		GUIDE_XF_QUA_UP_STEP_1,
		GUIDE_XF_QUA_UP_STEP_2,
		GUIDE_XF_QUA_UP_STEP_3,
		GUIDE_XF_QUA_UP_STEP_4,
		GUIDE_XF_QUA_UP_STEP_5,
	};
	void showGuide();
	void changeGuide();

};

#endif //_UI_HEART_METHOD_QUALITY_UP_LAYER_