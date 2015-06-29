//#ifndef __UI_RANKING_LIST_LAYER__
//#define __UI_RANKING_LIST_LAYER__
//
//#include "Rank_System/Rank_Data.h"
//
//#include "cocos2d.h"
////#include "cocos-ext.h"
//#include "ui/UIButton.h"
//#include "ui/UIImageView.h"
//#include "ui/UITextField.h"
//#include "ui/UILoadingBar.h"
//#include "ui/UILayout.h"
//#include "ui/UISlider.h"
//#include "ui/UICheckBox.h"
//#include "ui/UIWidget.h"
//#include "ui/UIScrollView.h"
//#include "cocostudio/CocoStudio.h"
//#include "ui/UIText.h"
//#include "ui/CocosGUI.h"
//#include "Common/Utils.h"
////USING_NS_CC;
////USING_NS_CC_EXT;
//USING_NS_CC;
//using namespace ui;
//#define EACH_TEXTURE_WIDTH	880
//#define EACH_TEXTURE_HEIGHT	50
//#define FONT_SIZE			25
//
//class UI_Ranking_List_Layer : public cocos2d::Layer
//{
//public:
//	UI_Ranking_List_Layer(void);
//	~UI_Ranking_List_Layer(void);
//
//public:
//	virtual bool init();
//	virtual void setVisible(bool visible);
//	CREATE_FUNC(UI_Ranking_List_Layer);
//
//	void update(int rank_type);
//
//private:
//	void initComponent();
//	void btnCloseCallback( Ref* pSender ,Widget::TouchEventType type);
//	void btnLevelCallback( Ref* pSender ,Widget::TouchEventType type);
//	void btnFightingCallback( Ref* pSender ,Widget::TouchEventType type);
//	void btnMoneyCallback( Ref* pSender ,Widget::TouchEventType type);
//
//	void btnRoleInfoCallback( Ref* pSender ,Widget::TouchEventType type);
//	void initScrollViewInfo();
//
//    void reset_ui();
//
//private:
//	cocos2d::ui::Widget*				m_pRootWidget;
//	cocos2d::ui::Button*				m_pBtnClose;
//	cocos2d::ui::Text*				m_pRankingNum;
//
//	cocos2d::ui::Button*				m_pBtnLevel;
//	cocos2d::ui::Button*				m_pBtnFighting;
//	cocos2d::ui::Button*				m_pBtnMoney;
//	cocos2d::ui::ImageView*			m_pImgCurSelectEffect;
//
//	cocos2d::ui::ScrollView*			m_pScrollView;
//
//	//已经组装好的控件
//	cocos2d::ui::Button*				m_pBtnRoleInfoTemp;
//	cocos2d::ui::Text*				m_pLabRoleRankingTemp;
//	cocos2d::ui::Text*				m_pLabRoleAttrTemp;
//	cocos2d::ui::Text*				m_pLabRoleNameTemp;
//	cocos2d::ui::Text*				m_pLabRoleUnitedTemp;
//
//	cocos2d::ui::Button*				m_pBtnRoleViewInfo[RANK_MAX];
//	cocos2d::ui::Text*				m_pLabRoleRankingNum[RANK_MAX];
//	cocos2d::ui::Text*				m_pLabRoleAttr[RANK_MAX];
//	cocos2d::ui::Text*				m_pLabRoleName[RANK_MAX];
//	cocos2d::ui::Text*				m_pLabRoleUnited[RANK_MAX];
//
//	//属性名称 lab_attr_font
//	cocos2d::ui::Text*				m_pLabAttrFont;
//
//};
//
//#endif //__UI_RANKING_LIST_LAYER__
