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
#define ROLE_QUALITY_ATTR_NUM       9         //������Ʒǰ��� 9 ������

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
	//��Ʒ��ť
	void btnRoleQualiryUpCallback(Ref* pSender,Widget::TouchEventType type);
	//ͷ�����¼�
	void imgHeadClickEventProc(Ref* pSender,Widget::TouchEventType type);
    void clickMaterialCallback( Ref* pSender ,Widget::TouchEventType type);

    void update_character_attr();
    void update_need_material(int cur_quality);

private: //ָ��������� �ǵó�ʼ��  ��WARNING��
	//ͷ�� ����¼�  ͷ��ͼ�� 
	cocos2d::ui::ImageView*			m_img_click_head_event[UI_HEAD_SUM_NUM];
	cocos2d::ui::ImageView*			m_img_head_icon[UI_HEAD_SUM_NUM];

	//��Ʒ����Ҫ�� 3 �����ϸ���ͼƬ   �Լ� ÿ�������в��ϵ�����
	cocos2d::ui::ImageView*			m_img_material_back[3];
	cocos2d::ui::ImageView*			m_img_material[3];
	cocos2d::ui::Text*				m_lab_material_need_num[3];

	//��Ʒǰ��� ���� 9 ������
	cocos2d::ui::Text*				m_lab_qua_befor_attr[ROLE_QUALITY_ATTR_NUM];
	cocos2d::ui::Text*				m_lab_qua_after_attr[ROLE_QUALITY_ATTR_NUM];

	//��Ʒǰ���ͷ�񱳾��� �Լ� ͷ��
	cocos2d::ui::ImageView*			m_img_role_qua_before_back;
	cocos2d::ui::ImageView*			m_img_role_qua_after_back;
	cocos2d::ui::ImageView*			m_img_role_quality_before;
	cocos2d::ui::ImageView*			m_img_role_quality_after;


	//��ɫ����
	cocos2d::ui::Text*				m_lab_role_name_font;
	cocos2d::ui::Text*				m_lab_role_name_font_after;

	//��ɫ�ȼ�
	cocos2d::ui::Text*				m_Label_original_level;
	cocos2d::ui::Text*				m_Label_after_level;

    int                     m_character_id;
    cocos2d::ui::ImageView*            m_img_head_effect;			//ͷ����Ч������
    cocos2d::ui::ImageView*		    m_img_fighting_mark;		//��ս�����ͼ
	cocos2d::ui::Button*				m_btn_quality_up;

	//Icon ��Ϣ��ʾ��
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
