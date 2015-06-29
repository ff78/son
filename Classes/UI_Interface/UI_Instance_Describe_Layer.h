#ifndef _UI_INSTANCE_DESCRIBE_LAYER_
#define _UI_INSTANCE_DESCRIBE_LAYER_
#include "cocos2d.h"
//#include "cocos-ext.h"
#include "Game_Interface/common.h"
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
class UI_Icon_Info_Layer;
class Joiner_Guidance;
class UI_Instance_Describe_Layer : public cocos2d::Layer
{
private:
	UI_Instance_Describe_Layer(void);
	virtual ~UI_Instance_Describe_Layer(void);

public:
	virtual bool init();
	CREATE_FUNC(UI_Instance_Describe_Layer);
	virtual void setVisible(bool visible);
	void showGuide();

	void buttonSweepCallback(Ref* pSender, Widget::TouchEventType type);
	void enterInstanceCallback(Ref* pSender, Widget::TouchEventType type);
	void closeCallback(Ref* pSender, Widget::TouchEventType type);

	void initInstanceDescribe(int get_icon_instance_id);
	void clickMaterialCallback(Ref* pSender, Widget::TouchEventType type);

	void ordinaryBtnCallback(Ref* pSender, Widget::TouchEventType type);
	void eliteBtnCallback(Ref* pSender, Widget::TouchEventType type);
	void showStarNum();
private:
	int show_instance_content(int instance_id);
	int get_elite_instance_id(int instance_id);
	int show_item_icon(std::vector<uint>& para, int item_count);
	void check_instance_sweep();

	//�رհ�ť
	cocos2d::ui::Button*			m_pBtnClose;
	//��ͼ��ͼ
	cocos2d::ui::ImageView*		m_pImgViewMap;
	//������Ʒ��ͼ����
	cocos2d::ui::ImageView*		m_pImgAwardGoodsTextureBack[3];
	//������Ʒ��ͼ  
	cocos2d::ui::ImageView*		m_pImgAwardGoodsTexture[3];
	//����ֵ
	cocos2d::ui::Text*			m_pLabNeedPowerNum;
	//���齱��ֵ
	cocos2d::ui::Text*			m_pLabAwardExpNum;
	//��Ǯ����ֵ
	cocos2d::ui::Text*			m_pLabAwardMoneyNum;
	//����ȼ�
	cocos2d::ui::Text*			m_pLabSuggestLevel;

	//��ͨ or ��Ӣ ��ť
	cocos2d::ui::ImageView*		m_pImgOrdinary;
	cocos2d::ui::ImageView*		m_pImgElite;

	//ͨ������
	cocos2d::ui::TextField*			m_pTeaPassCondition;
	//������ʾ
	cocos2d::ui::ImageView*		m_pImgStars[3];
	//"���ܻ��" ��������
	cocos2d::ui::Text*			m_pLabMaybeGain[3];
	cocos2d::ui::TextField*         m_lab_Dungeon_Desc;

	// ɨ����ť
	cocos2d::ui::Button*           m_btn_sweep_instance;
	cocos2d::ui::Text*			m_lab_sweep_instance_font;
	int ui_instance_elite_;


	//Icon ��Ϣ��ʾ��
	UI_Icon_Info_Layer*						m_pLayerIconInfo;

	cocos2d::ui::Button*								btn_enter_instance;
	Joiner_Guidance*						juniorGuide;
	cocos2d::ui::Widget* m_pCocoWidget_instance_;
private:
	enum guide_step
	{
		JUNIOR_GUIDE_STEP_6 = 6,
	};
};

#endif //_UI_INSTANCE_DESCRIBE_LAYER_
