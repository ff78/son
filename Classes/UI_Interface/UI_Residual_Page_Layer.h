#ifndef __UI_RESIDUAL_PAGE_LAYER__
#define __UI_RESIDUAL_PAGE_LAYER__

#define RESIDUAL_PAGE_TYPE_COUNT     40
#define SCROLLVIEW_WIDTH		520
#define SCROLLVIEW_HEIGHT		510
#define EACH_SCROLL_PAGE_NUM	4

#include "cocos2d.h"
//#include "cocos-ext.h"
#include <list>
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
using namespace std;
USING_NS_CC;
using namespace ui;
class UI_Icon_Info_Layer;
class UI_Residual_Page_Layer : public cocos2d::Layer
{
public:
	UI_Residual_Page_Layer(void);
	~UI_Residual_Page_Layer(void);

	virtual bool init();
	CREATE_FUNC(UI_Residual_Page_Layer);
	virtual void setVisible(bool visible);
	void showGuide();

    void update(int change);

private: 
	void buttonCloseCallback(Ref* pSender,Widget::TouchEventType type);
	void buttonBookLayerCallback(Ref* pSender,Widget::TouchEventType type);
	void buttonCombineCallback(Ref* pSender,Widget::TouchEventType type);
	void buttonQualityUpCallback(Ref* pSender,Widget::TouchEventType type);
	void initComponentOfUI();

    void selectCurMaterial(Ref* pSender,Widget::TouchEventType type);
    void compoundMaterial(Ref* pSender,Widget::TouchEventType type);
    void materialShow(int item_base_id);

    void change_refresh();
    void no_change_refresh();

    void reset_ui();
	void residualPageFindWay(Ref* pSender,Widget::TouchEventType type);

	void buttonOpenOrNot();
private:
	cocos2d::ui::Button*				btnBook;
	cocos2d::ui::Button*				btnCombine;
	cocos2d::ui::Button*				btnQualityUp;
	cocos2d::ui::ImageView*			m_pImgCombineBefore;			//�ϳ�ǰͼƬ����
	cocos2d::ui::ImageView*			m_pImgCombineBeforeTexture;		//�ϳ�ǰͼƬ
	cocos2d::ui::ImageView*			m_pImgCombineAfter;				//�ϳɺ�ͼƬ����
	cocos2d::ui::ImageView*			m_pImgCombineAfterTexture;		//�ϳɺ�ͼƬ

	cocos2d::ui::TextField*				m_pTeaFragmentDesc;		//��Ƭ����
	cocos2d::ui::TextField*				m_pTeaCombineDesc;		//�ϳɵ�������
	cocos2d::ui::TextField*				m_pTeaMaterialDesc;		//���ϲ�������
	cocos2d::ui::TextField*				m_pTeaResultDesc;		//���߲�������

	cocos2d::ui::Text*				m_pLabAutoFindWayFont;	//�Զ�Ѱ·����

	cocos2d::ui::ScrollView*			m_pScrollView;			//������

	cocos2d::ui::ImageView*			m_pImgEffect;			//ѡ��Ч��
	cocos2d::ui::ImageView*			m_pImgTipsShow;			//��ʾû�в�ҳ
	cocos2d::ui::Text*				m_pLabTipsFont;			//����δ��ò�ҳ��Ŭ���ռ��ɣ�

    cocos2d::ui::ImageView*            m_fragmentBack[RESIDUAL_PAGE_TYPE_COUNT];
    cocos2d::ui::ImageView*            m_fragmentIconBack[RESIDUAL_PAGE_TYPE_COUNT];
    cocos2d::ui::ImageView*            m_iconTexture[RESIDUAL_PAGE_TYPE_COUNT];
    cocos2d::ui::Text*                m_labIconName[RESIDUAL_PAGE_TYPE_COUNT];
    cocos2d::ui::Text*                m_labIconNum[RESIDUAL_PAGE_TYPE_COUNT];
    cocos2d::ui::Button*               m_btnCombine[RESIDUAL_PAGE_TYPE_COUNT];
    cocos2d::ui::Text*                m_labBtnShow[RESIDUAL_PAGE_TYPE_COUNT];

    list<int>      m_list_fragment;

	//Icon ��Ϣ��ʾ��
	UI_Icon_Info_Layer*			m_pLayerIconInfo;
	cocos2d::ui::Widget* rootWidget;
	enum guide_step
	{
		GUIDE_XF_PINZHUANG_0 = 60,
		GUIDE_XF_PINZHUANG_1,
		GUIDE_XF_PINZHUANG_2,
		GUIDE_XF_PINZHUANG_3,
		GUIDE_XF_PINZHUANG_4,

	};
};

#endif //__UI_RESIDUAL_PAGE_LAYER__
