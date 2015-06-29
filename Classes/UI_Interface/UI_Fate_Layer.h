#ifndef __UI_FATE_LAYER__
#define __UI_FATE_LAYER__

#include "cocos2d.h"
//#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
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
#include "ui/UIDeprecated.h"
#include "ui/UIHelper.h"
#include "ui/UIPageView.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
#include <string>
using namespace std;
USING_NS_CC;
//USING_NS_CC_EXT;
using namespace ui;
#define PAGE_NUM  8
#define EACH_PAGE_ACUPOINT_NUM 25


class UI_Fate_Layer : public cocos2d::Layer
{
public:
	UI_Fate_Layer(void);
	~UI_Fate_Layer(void);

	virtual bool init();
	CREATE_FUNC(UI_Fate_Layer);
	virtual void setVisible(bool visible);

    void update();
    void update_time();
	string getEffectId(int level);
private:
	void initComponent();
	void btnCloseCallback( Ref* pSender ,Widget::TouchEventType type);
	void pageSet( Ref* pSender ,Widget::TouchEventType type);
    void btnOpenAcupointCallback( Ref* pSender ,Widget::TouchEventType type);
	void btnLeftCallback( Ref* pSender ,Widget::TouchEventType type);
	void btnRightCallback( Ref* pSender ,Widget::TouchEventType type);

	cocos2d::ui::PageView* createPageView();
	void pageViewEvent(Ref *pSender, cocos2d::ui::PageViewEventType type);
	void initWidget();
    void update_attr();

private:
	cocos2d::ui::Widget*				m_pRootWidget;
	cocos2d::ui::ImageView*			m_pImgSecondBack;
	cocos2d::ui::PageView*				pageView;
	cocos2d::ui::ImageView*			m_pImgAcupoint[PAGE_NUM][EACH_PAGE_ACUPOINT_NUM];
	cocos2d::ui::ImageView*			m_pimg_effect[PAGE_NUM];
	cocos2d::ui::Text*				m_pLabAcupointName[PAGE_NUM][EACH_PAGE_ACUPOINT_NUM];

	cocos2d::ui::Text*				m_pLabAcuTitleName;
	cocos2d::ui::Text*				m_pLabChongNum;
	cocos2d::ui::Text*				m_pLabAcupointNameTitle;
	cocos2d::ui::Text*				m_pLabBonusToAttr;
	cocos2d::ui::Text*				m_pLabSuccessRate;
	cocos2d::ui::Text*				m_pLabAdditionNum;
	cocos2d::ui::Text*				m_pLabCurGain;
	cocos2d::ui::Text*				m_pLabAllOpenGive;
	cocos2d::ui::Text*				m_pLabCurChong;
	cocos2d::ui::Text*				m_pLabConsumptionRepu;
	cocos2d::ui::Text*				m_pLabHaveRepu;
	cocos2d::ui::Text*				m_pLabConsumptionGold;
	cocos2d::ui::Text*				m_pLabHaveGold;
	cocos2d::ui::Text*				m_pLabCountdown;
	cocos2d::ui::Text*				m_pBtnFont;
	cocos2d::ui::ImageView*			m_pImgLeftMove;
	cocos2d::ui::ImageView*			m_pImgRightMove;

    int                     m_select_type;

	cocos2d::ui::Text*				m_pLabAcupointNameFont;
	cocos2d::ui::Text*				m_pLabSuccessRateFont;
	cocos2d::ui::Text*				m_pLabAddAttrFont;
	cocos2d::ui::Text*				m_pLabNowGainFont;
	cocos2d::ui::Text*				m_pLabAllOpenGiftFont;
	cocos2d::ui::Text*				m_pLabXiuLianNumFont;
	cocos2d::ui::Text*				m_pLabHasRepuFont;
	cocos2d::ui::Text*				m_pLabNeedRepuFont;
	cocos2d::ui::Text*				m_pLabHasMoneyFont;
	cocos2d::ui::Text*				m_pLabNeedMoneyFont;
	cocos2d::ui::Text*				m_pLabCoolTimeFont;

	cocos2d::ui::Button*				m_pBtnChongXue;
private:
	enum guide_index
	{
		GUIDE_FATE_LEVEL_UP_0 = 280,
		GUIDE_FATE_LEVEL_UP_1,
		GUIDE_FATE_LEVEL_UP_2,
		GUIDE_FATE_LEVEL_UP_3,
	};
	void showGuide();
	void changeGuide();
};


#endif //__UI_FATE_LAYER__