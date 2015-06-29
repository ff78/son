#include "cocos2d.h"
#include <fstream>	
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Game_Interface/common.h"

#include "Item_System/Item_Config_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Item_Container_System/Item_Container_Data.h"
#include "Item_Container_System/Item_Container_Mgr_Cl.h"
#include "Item_System/Item_Logic_Cl.h"
#include "Item_System/Item_Mgr_Cl.h"
#include "Item_System/Item_Config_Data.h"

#include "UI_Interface/UI_Bag_Info_Layer.h"
#include "UI_Equipment_Gem_Layer.h"
#include "UI_Equipment_Gem_Cell_Layer.h"

using namespace ui;

UI_Equipment_Gem_Cell_Layer::UI_Equipment_Gem_Cell_Layer()
{
	m_nCellTagID = -1;
	m_nCellGemID = 0;
}


UI_Equipment_Gem_Cell_Layer::~UI_Equipment_Gem_Cell_Layer()
{

}


bool UI_Equipment_Gem_Cell_Layer::init()
{
	if (!Layout::init())
	{
		return false;
	}

	Widget* pLayer				= cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/bag_equip_gem_cell/bag_equip_gem_cell.ExportJson");
	this->addChild(pLayer);

	m_pIconTitleText			= dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(pLayer, "Gem_Title"));
	m_pIconImageViwe			= dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Gem_Icon"));
	m_pIconImageBGViwe			= dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(pLayer, "bg"));
	m_pGemSelectedBoxImageViwe	= dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Gem_Icon_SelectBox"));
	m_pIconImageBGViwe->addTouchEventListener(CC_CALLBACK_2(UI_Equipment_Gem_Cell_Layer::OnBtnClickCellCallBack, this));

	return true;
}


void UI_Equipment_Gem_Cell_Layer::onExit()
{
	Layout::onExit();
}


void UI_Equipment_Gem_Cell_Layer::onEnter()
{
	Layout::onEnter();
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 页面刷新相关逻辑
void UI_Equipment_Gem_Cell_Layer::SetCurrentGemInfoForShow(const uint64 nGemID)
{
	/************************************************************************/
	// 设置当前的宝石用于显示的信息
	// 1. 判断宝石ID是否异常
	if (nGemID == 0)
		return;
		
	// 2. 判断宝石Config是否异常
	Game_Data::Gem_Config* config = ITEM_CONFIG_MGR::instance()->get_gem_config(nGemID);
	if (config == NULL)
		return;

	/************************************************************************/
	// 条件满足,显示宝石的信息并存储宝石ID
	// 1. 存储宝石ID
	m_nCellGemID = nGemID;

	// 2. 显示宝石的信息
	const char* szTemp = ITEM_CONFIG_MGR::instance()->get_icon_path(config->icon);
	int nTemp = strcmp(szTemp, "");
	if (nTemp > 0)
	{
		m_pIconImageViwe->loadTexture(szTemp, UI_TEX_TYPE_PLIST);
		m_pIconImageViwe->setVisible(true);
	}

	szTemp = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(config->name);
	m_pIconTitleText->setString(szTemp);	
	m_pIconTitleText->setVisible(true);
}


void UI_Equipment_Gem_Cell_Layer::ClearGemInfo()
{
	/************************************************************************/
	// 清除宝石信息
	m_nCellGemID = 0;
	m_pIconImageViwe->setVisible(false);
	m_pIconTitleText->setVisible(false);
	m_pGemSelectedBoxImageViwe->setVisible(false);
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 按钮点击方法回调
void UI_Equipment_Gem_Cell_Layer::OnBtnClickCellCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 点击Cell按钮方法回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 1. 设置父页面当前宝石的信息
	UI_Equipment_Gem_Layer *pLayer = dynamic_cast<UI_Equipment_Gem_Layer*>(this->getParent()->getParent()->getParent()->getParent()->getParent()->getParent());
	if (pLayer == NULL)
		return;

	pLayer->SetCurrentCellTagID(m_nCellTagID);
	pLayer->ShowTargetCellGemInfo();
}