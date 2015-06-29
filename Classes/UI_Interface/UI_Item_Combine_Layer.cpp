#include "UI_Item_Combine_Layer.h"

USING_NS_CC;
using namespace ui;
UI_Item_Combine_Layer::UI_Item_Combine_Layer(void):
	m_pScrollView(NULL),
	m_pPanelForIcon(NULL),
	m_pLabIconName(NULL),
	m_pImgCombineIconBack(NULL),
	m_pImgCombineTexture(NULL),
	m_pLabCombineFont(NULL),
	m_pTeaCombineDesc(NULL),
	m_pTeaCombineResultDesc(NULL),
	m_pLabAutoFindWayFont(NULL)
{
	memset(m_pImgMaterialBack, 0, sizeof(m_pImgMaterialBack));
	memset(m_pImgMaterialTexture, 0, sizeof(m_pImgMaterialTexture));
	memset(m_pLabNeedMaterialNum, 0, sizeof(m_pLabNeedMaterialNum));
}


UI_Item_Combine_Layer::~UI_Item_Combine_Layer(void)
{
}

bool UI_Item_Combine_Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());

		rootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/FragmentCombine/FragmentCombine.ExportJson");
		addChild(rootWidget);

		cocos2d::ui::Button* btnClose = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(rootWidget,"btn_close"));
		btnClose->addTouchEventListener(this, toucheventselector(UI_Item_Combine_Layer::btnCloseCallback));

		cocos2d::ui::Button* m_pBtnCombine = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(rootWidget,"btn_combine"));
		m_pBtnCombine->addTouchEventListener(this, toucheventselector(UI_Item_Combine_Layer::btnCombineCallback));

		initComponentOfUI();

		showMaterialInfo(10);

		bRet = true;
	} while (0);

	return bRet;
}

void UI_Item_Combine_Layer::btnCloseCallback( Ref* pSender,Widget::TouchEventType type )
{
	setVisible(false);
}

void UI_Item_Combine_Layer::refresh()
{

}

void UI_Item_Combine_Layer::initComponentOfUI()
{
	m_pScrollView = dynamic_cast<cocos2d::ui::ScrollView*>(Helper::seekWidgetByName(rootWidget,"ScrollView"));
	m_pScrollView->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
	m_pPanelForIcon = dynamic_cast<cocos2d::ui::Layout*>(Helper::seekWidgetByName(rootWidget,"panel_for_icon"));

	m_pLabIconName = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(rootWidget,"lab_role_name_font"));
	m_pImgCombineIconBack = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(rootWidget,"img_icon_combine_back"));
	m_pImgCombineTexture = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(rootWidget,"img_icon_combine"));

	m_pLabCombineFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(rootWidget,"lab_quality_up_font"));

	m_pTeaCombineDesc = dynamic_cast<cocos2d::ui::TextField*>(Helper::seekWidgetByName(rootWidget,"tea_combine_desc"));
	m_pTeaCombineResultDesc = dynamic_cast<cocos2d::ui::TextField*>(Helper::seekWidgetByName(rootWidget,"tea_result_desc"));

	m_pLabAutoFindWayFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(rootWidget,"lab_auto_find_way_font"));
}

void UI_Item_Combine_Layer::setVisible(bool visible)
{
	cocos2d::Layer::setVisible(visible);
}

void UI_Item_Combine_Layer::btnCombineCallback( Ref* pSender,Widget::TouchEventType type )
{

}

void UI_Item_Combine_Layer::showMaterialInfo(int iconNum)
{
	if(iconNum<7)
		m_pPanelForIcon->setSize(Size(960,130));
	else
		m_pPanelForIcon->setSize(Size(950/7*iconNum,130));
	for(int i=0; i<iconNum; ++i)
	{
		cocos2d::ui::ImageView* iconBack = cocos2d::ui::ImageView::create();
		iconBack->loadTexture("frame.png", UI_TEX_TYPE_PLIST);
		m_pPanelForIcon->addChild(iconBack);
		iconBack->setPosition(Vec2(iconBack->getContentSize().width/2+135*i, iconBack->getContentSize().height/2));

		cocos2d::ui::ImageView* iconTexture = cocos2d::ui::ImageView::create();
		iconTexture->loadTexture("");
		iconBack->addChild(iconTexture);
	}
	
}
