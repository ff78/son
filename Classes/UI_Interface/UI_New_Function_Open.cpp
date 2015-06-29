#include "UI_New_Function_Open.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "UI_MainMenu_Layer.h"
#include "Joiner_Guidance.h"

using namespace Game_Data;
using namespace ui;
UI_New_Function_Open::UI_New_Function_Open(void) :
	m_pRootWidget(NULL),
	//m_pImgIconBack(NULL),
//	m_pImgIconPic(NULL),
	m_pLabFuncName(NULL)
{
}


UI_New_Function_Open::~UI_New_Function_Open(void)
{
}

bool UI_New_Function_Open::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF( !cocos2d::Layer::init() );

		m_pRootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Open_New_Icon/Open_New_Icon.ExportJson");
		addChild(m_pRootWidget);
		
		initComponentUI();

		bRet = true;
	} while (0);

	return bRet;
}

void UI_New_Function_Open::setVisible( bool visible )
{
	cocos2d::Layer::setVisible(visible);
	if (visible)
	{
		m_pImgIconPic->setVisible(true);
		m_pImgIconPic->setPosition(m_pImgIconBack->getPosition());
	}
}

void UI_New_Function_Open::initComponentUI()
{
	m_pRootPanel = dynamic_cast<cocos2d::ui::Layout*>(Helper::seekWidgetByName(m_pRootWidget,"Panel"));
	m_pRootPanel->addTouchEventListener(this, toucheventselector(UI_New_Function_Open::clickPanel));

	m_pImgIconBack = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pRootWidget,"img_function_back"));
	m_pImgIconPic = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pRootWidget,"img_function_pic"));
	m_pLabFuncName = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_open_function_name"));
}

void UI_New_Function_Open::clickPanel( Ref* pSender,Widget::TouchEventType type )
{
Point posPoint ;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	posPoint = UI_MainMenu_Layer::get_instance()->m_pBtnToggle->getPosition();
#if 0
	m_pImgIconPic->runAction(
		CCSequence::create(
		CCScaleTo::create(0.2f, 0.5f),
		CallFunc::create(this, callfunc_selector(UI_New_Function_Open::othersVisibleCallback)),
		CCMoveTo::create(1.0f, posPoint),
		CallFunc::create(this, callfunc_selector(UI_New_Function_Open::closeOpenNotice)),
		NULL ));
#endif

	break;
    default:
	break;
}
}

void UI_New_Function_Open::closeOpenNotice()
{
	setVisible(false);
//	UI_MainMenu_Layer::get_instance()->showGuide();
}

void UI_New_Function_Open::othersVisibleCallback()
{
	m_pImgIconBack->setVisible(false);
}

void UI_New_Function_Open::showPromptInfo( int iconNameId, int iconOpenId )
{
	Joiner_Guidance::hideGuide();
	const char* iconName = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(iconNameId);
	m_pLabFuncName->setString(iconName);

	switch (iconOpenId)
	{
	case ICON_BAG_TAG:
		m_pImgIconPic->loadTexture("bag_.png", UI_TEX_TYPE_PLIST);
		break;
//	case ICON_EQUIP_TAG:
//		m_pImgIconPic->loadTexture("equipment.png", UI_TEX_TYPE_PLIST);
//		break;
//	case ICON_XINFA_TAG:
//		m_pImgIconPic->loadTexture("method.png", UI_TEX_TYPE_PLIST);
//		break;
	case ICON_SKILL_TAG:
		m_pImgIconPic->loadTexture("knife_.png", UI_TEX_TYPE_PLIST);
		break;
	//case ICON_ARENA_TAG:
	//	m_pImgIconPic->loadTexture("arena.png", UI_TEX_TYPE_PLIST);
	//	break;
	//case ICON_FATE_TAG:
	//	m_pImgIconPic->loadTexture("fate.png", UI_TEX_TYPE_PLIST);
	//	break;
	default:
		m_pImgIconPic->loadTexture("pic_life.png", UI_TEX_TYPE_PLIST);
		break;
	}
}
