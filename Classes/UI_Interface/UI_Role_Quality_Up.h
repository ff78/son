#ifndef __UI_ROLE_QUALITY_UP__
#define __UI_ROLE_QUALITY_UP__

#include "cocos2d.h"
//#include "cocos-ext.h"
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
#include "cocostudio/CocoStudio.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
//USING_NS_CC;
//USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;
#define ROLE_QUALITY_ATTR_NUM       9         //人物升品前后各 9 个属性

class UI_Icon_Info_Layer;
class UI_Role_Quality_Up : public cocos2d::Layer
{
public:
	UI_Role_Quality_Up(void);
	~UI_Role_Quality_Up(void);

	bool init();
	CREATE_FUNC(UI_Role_Quality_Up);
    void setVisible( bool visible );
    void update_role();
    void update();

private:
	void btnCloseCallback(Ref* pSender,Widget::TouchEventType type);
	void btnRoleCallback(Ref* pSender,Widget::TouchEventType type);
	void btnBagCallback(Ref* pSender,Widget::TouchEventType type);
	void btnSkillCallback(Ref* pSender,Widget::TouchEventType type);
	//升品按钮
	void btnRoleQualiryUpCallback(Ref* pSender,Widget::TouchEventType type);
	//头像点击事件
	void imgHeadClickEventProc(Ref* pSender,Widget::TouchEventType type);
    void clickMaterialCallback( Ref* pSender ,Widget::TouchEventType type);

    void update_character_attr();
    void update_need_material(int cur_quality);

private: //指针声明完毕 记得初始化  《WARNING》
	//头像 点击事件  头像图标 
	cocos2d::ui::ImageView*			m_img_click_head_event[UI_HEAD_SUM_NUM];
	cocos2d::ui::ImageView*			m_img_head_icon[UI_HEAD_SUM_NUM];

	//升品所需要的 3 个材料格子图片   以及 每个格子中材料的数量
	cocos2d::ui::ImageView*			m_img_material_back[3];
	cocos2d::ui::ImageView*			m_img_material[3];
	cocos2d::ui::Text*				m_lab_material_need_num[3];

	//生品前后的 各自 9 个属性
	cocos2d::ui::Text*				m_lab_qua_befor_attr[ROLE_QUALITY_ATTR_NUM];
	cocos2d::ui::Text*				m_lab_qua_after_attr[ROLE_QUALITY_ATTR_NUM];

	//升品前后的头像背景框 以及 头像
	cocos2d::ui::ImageView*			m_img_role_qua_before_back;
	cocos2d::ui::ImageView*			m_img_role_qua_after_back;
	cocos2d::ui::ImageView*			m_img_role_quality_before;
	cocos2d::ui::ImageView*			m_img_role_quality_after;


	//角色名称
	cocos2d::ui::Text*				m_lab_role_name_font;
	cocos2d::ui::Text*				m_lab_role_name_font_after;

	//角色等级
	cocos2d::ui::Text*				m_Label_original_level;
	cocos2d::ui::Text*				m_Label_after_level;

    int                     m_character_id;
    cocos2d::ui::ImageView*            m_img_head_effect;			//头像点击效果背景
    cocos2d::ui::ImageView*		    m_img_fighting_mark;		//出战标记贴图
	cocos2d::ui::Button*				m_btn_quality_up;

	//Icon 信息显示框
	UI_Icon_Info_Layer*			m_pLayerIconInfo;

private:
	enum guide_index
	{
		GUIDE_ROLE_QUA_0 = 200,
		GUIDE_ROLE_QUA_1,
		GUIDE_ROLE_QUA_2,
		GUIDE_ROLE_QUA_3,
		GUIDE_ROLE_QUA_4,
	};
	void showGuide();
	void changeGuide();

};

#endif //__UI_ROLE_QUALITY_UP__
