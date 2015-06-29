#ifndef __UI_FRAGMENT_LAYER__
#define __UI_FRAGMENT_LAYER__

#define FRAGMENT_TYPE_COUNT     20
#define SCROLLVIEW_WIDTH		520
#define SCROLLVIEW_HEIGHT		510
#define EACH_SCROLL_PAGE_NUM	4

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
#include "cocostudio/CocoStudio.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
#include <list>
using namespace std;
USING_NS_CC;
using namespace ui;
class UI_Icon_Info_Layer;
class UI_Material_Fragment_Layer : public cocos2d::Layer
{
public:
	UI_Material_Fragment_Layer(void);
	~UI_Material_Fragment_Layer(void);

	virtual bool init();
	CREATE_FUNC(UI_Material_Fragment_Layer);
	virtual void setVisible(bool visible);
	void showGuide();

    void update(int change);

private:
	void buttonCloseCallback(Ref* pSender,Widget::TouchEventType type);
	void initComponentOfUI();
	void btnBagCallback(Ref* pSender,Widget::TouchEventType type);
	void selectCurMaterial(Ref* pSender,Widget::TouchEventType type);
    void compoundMaterial(Ref* pSender,Widget::TouchEventType type);
    void materialShow(int item_base_id);

    void change_refresh();
    void no_change_refresh();

    void reset_ui();
	void residualPageFindWay(Ref* pSender,Widget::TouchEventType type);

private:
	cocos2d::ui::ImageView*			m_pImgCombineBefore;			//合成前图片背景
	cocos2d::ui::ImageView*			m_pImgCombineBeforeTexture;		//合成前图片
	cocos2d::ui::ImageView*			m_pImgCombineAfter;				//合成后图片背景
	cocos2d::ui::ImageView*			m_pImgCombineAfterTexture;		//合成后图片

	cocos2d::ui::TextField*				m_pTeaFragmentDesc;		//碎片描述
	cocos2d::ui::TextField*				m_pTeaCombineDesc;		//合成道具描述
	cocos2d::ui::TextField*				m_pTeaMaterialDesc;		//材料产出描述
	cocos2d::ui::TextField*				m_pTeaResultDesc;		//道具产出描述

	cocos2d::ui::Text*				m_pLabAutoFindWayFont;	//自动寻路字体
	
	cocos2d::ui::ScrollView*			m_pScrollView;			//滚动层
	//cocos2d::ui::Layout*				m_pLabPanelForScroll;	//滚动层上的层容器

	cocos2d::ui::ImageView*			m_pImgEffect;			//选中效果
	cocos2d::ui::ImageView*			m_pImgTipsShow;			//提示没有碎片
	cocos2d::ui::Text*				m_pLabTipsFont;			//（尚未获得碎片，努力收集吧）

    cocos2d::ui::ImageView*            m_fragmentBack[FRAGMENT_TYPE_COUNT];
    cocos2d::ui::ImageView*            m_fragmentIconBack[FRAGMENT_TYPE_COUNT];
    cocos2d::ui::ImageView*            m_iconTexture[FRAGMENT_TYPE_COUNT];
    cocos2d::ui::Text*                m_labIconName[FRAGMENT_TYPE_COUNT];
    cocos2d::ui::Text*                m_labIconNum[FRAGMENT_TYPE_COUNT];
    cocos2d::ui::Button*               m_btnCombine[FRAGMENT_TYPE_COUNT];
    cocos2d::ui::Text*                m_labBtnShow[FRAGMENT_TYPE_COUNT];
cocos2d::ui::Widget* rootWidget ;
    list<int>      m_list_fragment;

	//Icon 信息显示框
	UI_Icon_Info_Layer*			m_pLayerIconInfo;

	enum guide_step
	{
		GUIDE_BAG_COMBINE_0 = 100,
		GUIDE_BAG_COMBINE_1,
		GUIDE_BAG_COMBINE_2,
		GUIDE_BAG_COMBINE_3,
	};
};

#endif //__UI_FRAGMENT_LAYER__
