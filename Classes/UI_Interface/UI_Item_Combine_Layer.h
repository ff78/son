#ifndef __UI_FRAGMENT_COMBINE__
#define __UI_FRAGMENT_COMBINE__

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
#include "ui/UIDeprecated.h"
#include "ui/UIHelper.h"
#include "ui/UIPageView.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;
class UI_Item_Combine_Layer : public cocos2d::Layer
{
public:
	UI_Item_Combine_Layer(void);
	~UI_Item_Combine_Layer(void);

	virtual bool init();
	CREATE_FUNC(UI_Item_Combine_Layer);
	virtual void setVisible(bool visible);

private:
	void refresh();
	void initComponentOfUI();
	void btnCloseCallback(Ref* pSender,Widget::TouchEventType type);
	void btnCombineCallback(Ref* pSender,Widget::TouchEventType type);
	void showMaterialInfo(int iconNum);

private:
	cocos2d::ui::ScrollView*			m_pScrollView;
	cocos2d::ui::Layout*				m_pPanelForIcon;
	
	cocos2d::ui::Text*				m_pLabIconName;
	cocos2d::ui::ImageView*			m_pImgCombineIconBack;
	cocos2d::ui::ImageView*			m_pImgCombineTexture;
	cocos2d::ui::ImageView*			m_pImgMaterialBack[3];
	cocos2d::ui::ImageView*			m_pImgMaterialTexture[3];
	cocos2d::ui::Text*				m_pLabNeedMaterialNum[3];

	cocos2d::ui::Text*				m_pLabCombineFont;

	cocos2d::ui::TextField*				m_pTeaCombineDesc;			//合成道具描述
	cocos2d::ui::TextField*				m_pTeaCombineResultDesc;	//道具产出描述
cocos2d::ui::Widget* rootWidget ;
	cocos2d::ui::Text*				m_pLabAutoFindWayFont;
};

#endif //__UI_FRAGMENT_COMBINE__