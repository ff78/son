#include "UI_ModalDialogue_Layer.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Common/GameDefine.h"

USING_NS_CC;
//USING_NS_CC_EXT;
using namespace ui;
#define MODAL_DIALOGUE_ZORDER 9999


UI_ModalDialogue_Layer* UI_ModalDialogue_Layer::s_pInstance = NULL;

UI_ModalDialogue_Layer::UI_ModalDialogue_Layer(void)
{
}

UI_ModalDialogue_Layer::~UI_ModalDialogue_Layer(void)
{

}

bool UI_ModalDialogue_Layer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	cocos2d::ui::Widget* pWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Model_Dialogue/Model_Dialogue.ExportJson");
	addChild( pWidget );

	m_pLabCaption = (cocos2d::ui::Text*)Helper::seekWidgetByName(pWidget,"lbl_Caption");
	m_pLabContent = (cocos2d::ui::Text*)Helper::seekWidgetByName(pWidget, "lbl_Content");

	m_pBtn_Ok = (cocos2d::ui::Button*)Helper::seekWidgetByName(pWidget,"btn_OK");
	m_pBtn_Ok->addTouchEventListener(this,toucheventselector(UI_ModalDialogue_Layer::btn_Click));
	m_pBtn_Ok->setTag(RT_OK);

	m_pBtn_Yes = (cocos2d::ui::Button*)Helper::seekWidgetByName(pWidget,"btn_Yes");
	m_pBtn_Yes->addTouchEventListener(this,toucheventselector(UI_ModalDialogue_Layer::btn_Click));
	m_pBtn_Yes->setTag(RT_YES);

	m_pBtn_No = (cocos2d::ui::Button*)Helper::seekWidgetByName(pWidget,"btn_No");
	m_pBtn_No->addTouchEventListener(this,toucheventselector(UI_ModalDialogue_Layer::btn_Click));
	m_pBtn_No->setTag(RT_NO);

	const char* pzName = nullptr;

	m_pLab_Ok = (cocos2d::ui::Text*)(Helper::seekWidgetByName(pWidget,"lab_OK_confirm"));
	pzName = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SURE_EXIT);
	m_pLab_Ok->setString(pzName);

	m_pLab_Yes = (cocos2d::ui::Text*)(Helper::seekWidgetByName(pWidget,"lab_confirm"));
	pzName = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SURE_EXIT);
	m_pLab_Yes->setString(pzName);

	m_pLab_No = (cocos2d::ui::Text*)(Helper::seekWidgetByName(pWidget,"lab_cancel"));
	pzName = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(CANCEL_EXIT);
	m_pLab_No->setString(pzName);
	
	return true;
}

void UI_ModalDialogue_Layer::btn_Click( Ref* pSender,Widget::TouchEventType type )
{
cocos2d::ui::Button* pBtn;
int nTag;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	HideModal();
	
	if (m_pFunc)
	{
		pBtn = dynamic_cast<cocos2d::ui::Button*>(pSender);
		CC_ASSERT( pBtn );
		nTag =pBtn->getTag();
		if ( RT_OK==nTag || RT_YES==nTag )
		{
			m_pFunc();
		}
	}

	break;
    default:
	break;
}
}

void UI_ModalDialogue_Layer::updateLayer(const char* szTitle,const char* szContent,DialogueType type,pCall p)
{
	s_pInstance->m_pLabCaption->setString(szTitle);
	s_pInstance->m_pLabContent->setString(szContent);
	s_pInstance->m_Type = type;
	s_pInstance->m_pFunc = p;

	if (DT_NORMAL==s_pInstance->m_Type)
	{
		m_pBtn_Ok->setVisible(false);
		m_pBtn_Yes->setVisible(false);
		m_pBtn_No->setVisible(false);
	}
	else if (DT_OK==m_Type)
	{
		m_pBtn_Ok->setVisible(true);
		m_pBtn_Yes->setVisible(false);
		m_pBtn_No->setVisible(false);
	}
	else if (DT_YES_NO==m_Type)
	{
		m_pBtn_Ok->setVisible(false);
		m_pBtn_Yes->setVisible(true);
		m_pBtn_No->setVisible(true);
	}
	else
	{
		CCLOG("UI_ModalDialogue_Layer::error m_Type");
	}
}

void UI_ModalDialogue_Layer::DoModal(const char* szTitle,const char* szContent,DialogueType type,pCall p)
{
	if (!s_pInstance)
	{
		s_pInstance = UI_ModalDialogue_Layer::create();
		s_pInstance->retain(); //let it leak,that's allright
	}
	CC_ASSERT(s_pInstance);
	s_pInstance->HideModal();

	s_pInstance->updateLayer(szTitle,szContent,type,p);

	Scene* pCurrentScene = Director::getInstance()->getRunningScene();
	CC_ASSERT(pCurrentScene);
	pCurrentScene->addChild(s_pInstance,MODAL_DIALOGUE_ZORDER);

	//CCLOG("UI_ModalDialogue_Layer::ShowModal()");

}

void UI_ModalDialogue_Layer::HideModal()
{
	if (s_pInstance&&s_pInstance->getParent())
	{
		s_pInstance->removeFromParent();
		//CCLOG("UI_ModalDialogue_Layer::HideModal()");
	}
}
