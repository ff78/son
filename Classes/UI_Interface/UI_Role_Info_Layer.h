#ifndef _UI_ROLE_INFO_LAYER_CLASS_
#define _UI_ROLE_INFO_LAYER_CLASS_
//#include "cocos-ext.h"
#include "cocos2d.h"
#include "Game_Interface/common.h"
#include "Common/StrokeLabelTTF.h"
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
//USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;
namespace Game_Data
{
    struct Item;
}

class UI_Icon_Info_Layer;
class UI_Role_Info_Layer : public cocos2d::Layer
{
public:
	UI_Role_Info_Layer(void);
	virtual ~UI_Role_Info_Layer(void);
	CREATE_FUNC(UI_Role_Info_Layer);
	virtual bool init();
	void menuCloseCallback(Ref* pSender,Widget::TouchEventType type);
	void set_Info(std::vector<int> &para);
	virtual void setVisible(bool visible);

    void update();

	void btnBagCallBack(Ref* pSender,Widget::TouchEventType type);
	void btnSkillCallBack(Ref* pSender,Widget::TouchEventType type);
	void btnRoleQuaCallback(Ref* pSender,Widget::TouchEventType type);
    void btnCallBackFighting(Ref* pSender,Widget::TouchEventType type);
    void btnCallBackMissing(Ref* pSender,Widget::TouchEventType type);

private:
	void initStrength_bar_bg_frame();
    void update_grid_item(int index,int count,int quality,int icon);
    void remove_grid_item(int index);
    void RefreshUI();
    void ShowCharAvatar();

	void equipCallBack(Ref* pSender,Widget::TouchEventType type);
	void headPhotoClickEvent( Ref* pSender ,Widget::TouchEventType type);
	void update_role();

	void buttonOpenOrNot();
private:
	cocos2d::ui::Widget*					coco_;

    int						    m_select_character_id;

    cocos2d::ui::ImageView*                m_img_equipment_bar[6];
    cocos2d::ui::Button*                   m_btn_equipment_bar_back[6];
	cocos2d::ui::ImageView*				m_img_equipment_bar_pinzhi[6];

	cocos2d::ui::Text*					m_attr_lab[14];
	cocos2d::ui::Text*					m_attr_labvalue[14];
	cocos2d::ui::ImageView*				m_img_selected_effect;
	uint64					    m_bar_item_id[6];	
	void refreshDialog(uint64 item_id);
    void showTips(int item_base_id,int item_type,int quality,int level,int count,int icon,int name);
	
	/**************************************************************************************/

	//头像栏 控件
	cocos2d::ui::ImageView*				m_img_click_head_event[7];	//头像背景
	cocos2d::ui::ImageView*				m_img_head_photo[7];		//头像贴图
    cocos2d::ui::ImageView*                m_img_head_effect;			//头像点击效果背景

    cocos2d::ui::Button*               m_bt_fightingBtn;			//出战按钮

	cocos2d::ui::ImageView*				m_img_fighting_mark;		//出战标记贴图
    cocos2d::ui::Text*                    m_lab_fighting;             //出战按钮

	//
	StrokeLabelTTF*				m_role_strenght_stroke;
	StrokeLabelTTF*				m_role_exp_stroke_label;

	//
	cocos2d::ui::LoadingBar*				loading_EXP;
	cocos2d::ui::LoadingBar*				loading_Strength;

	//Icon 信息显示框
	UI_Icon_Info_Layer*			m_pLayerIconInfo;

	//button 
	cocos2d::ui::Button*					btnToRoleQuaUp;

	cocos2d::LabelAtlas*			m_fighting_capacity;

private:
	enum guide_index
	{
		GUIDE_ROLE_QUA_0 = 200,
		GUIDE_ROLE_QUA_1,
		GUIDE_ROLE_QUA_2,
		GUIDE_ROLE_QUA_3,
		GUIDE_ROLE_QUA_4,

		GUIDE_LIEU_FIGHT_0 = 240,
		GUIDE_LIEU_FIGHT_1,
		GUIDE_LIEU_FIGHT_2,
		GUIDE_LIEU_FIGHT_3,
		GUIDE_LIEU_FIGHT_4,
	};
	void showGuide();
	void changeGuide();
};

#endif  //_UI_ROLE_INFO_LAYER_CLASS_
