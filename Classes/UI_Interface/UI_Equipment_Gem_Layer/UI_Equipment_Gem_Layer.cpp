#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Game_Interface/common.h"
#include "Common/GameDefine.h"
#include "Network_Common/global_macros.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Game_Interface/game_content_interface.h"

#include "Item_System/Item_Config_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Item_Container_System/Item_Container_Data.h"
#include "Item_Container_System/Item_Container_Mgr_Cl.h"
#include "Item_System/Item_Logic_Cl.h"
#include "Item_System/Item_Mgr_Cl.h"
#include "Item_System/Item_Config_Data.h"

#include "../UI_Bag_Info_Layer.h"
#include "../UI_Bag_Gem_Layer/UI_Bag_Gem_Layer.h"
#include "UI_Equipment_Gem_Cell_Layer.h"
#include "UI_Equipment_Gem_Layer.h"

#define gem_row 3

using namespace ui;
using namespace cocos2d;
using namespace cocostudio;

UI_Equipment_Gem_Layer::UI_Equipment_Gem_Layer() 
{
	m_nEquipItemID			= 0;
	m_nCellCount			= 0;
	m_nScrollviewHeight		= 0;
	m_nCellHeight			= 0;
	m_nCurrentCellID		= -1;
}


UI_Equipment_Gem_Layer::~UI_Equipment_Gem_Layer()
{

}


bool UI_Equipment_Gem_Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	ui::Widget* pLayer = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/refine_gem.json");
	addChild(pLayer);
    
//    // 关闭按钮
//    m_pCloseBtn = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Close_Btn_0_0"));
//    m_pCloseBtn->setTouchEnabled(true);
//    m_pCloseBtn->addTouchEventListener(CC_CALLBACK_2(UI_Equipment_Gem_Layer::onCloseCallBack, this));
    
	// 强化按钮
	m_pEquipStrengthenText	= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Btn_Strengthen"));
	m_pEquipStrengthenText->setBrightStyle(Widget::BrightStyle::NORMAL);
	m_pEquipStrengthenText->setTouchEnabled(true);
	m_pEquipStrengthenText->addTouchEventListener(CC_CALLBACK_2(UI_Equipment_Gem_Layer::OnBtnStrengthenTextCallBack, this));

	// 升星按钮
	m_pEquipStarUpText = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Btn_Stars"));
	m_pEquipStarUpText->setBrightStyle(Widget::BrightStyle::NORMAL);
	m_pEquipStarUpText->setTouchEnabled(true);
	m_pEquipStarUpText->addTouchEventListener(CC_CALLBACK_2(UI_Equipment_Gem_Layer::OnBtnStarUpTextCallBack, this));

	_gemButtom = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Btn_Gem"));
	_gemButtom->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
	_gemButtom->setTouchEnabled(true);
	_gemButtom->addTouchEventListener(CC_CALLBACK_2(UI_Equipment_Gem_Layer::onGemCallback, this));

	// 洗练按钮
	m_pEquipWashText = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Btn_Wash"));
	m_pEquipWashText->setBrightStyle(Widget::BrightStyle::NORMAL);
	m_pEquipWashText->setTouchEnabled(true);
	m_pEquipWashText->addTouchEventListener(CC_CALLBACK_2(UI_Equipment_Gem_Layer::OnBtnWashCallBack, this));

	// 卸下宝石按钮
	m_pEquipSetOffGemBtn	= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Set_Off_Gem"));
	m_pEquipSetOffGemBtn->setTouchEnabled(true);
	m_pEquipSetOffGemBtn->addTouchEventListener(CC_CALLBACK_2(UI_Equipment_Gem_Layer::OnBtnSetOffGemhCallBack, this));

	// 装备描述
	m_pEquipDescribeText	= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Describe_Text"));

	// 装备名字
	m_pEquipNameText		= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Txt_Icon_Name"));

	// 装备需要等级
	m_pEquipLevelText		= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Txt_Lv_Needed"));

	// 装备图片
	m_pEquipIcon			= dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Img_Icon"));		

	// 装备描述背景图片
	m_pEquipDescribeBGImage = dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Des_BG"));

	// 滚动层
	m_pGemScrollView		= dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(pLayer, "ScrollView_Gem"));

	return true;
}


void UI_Equipment_Gem_Layer::onExit()
{
	Layer::onExit();
}


void UI_Equipment_Gem_Layer::onEnter()
{
	Layer::onEnter();

	LoadScrollView();
	SetScrollViweCell();
	RefreshEquipGemLayer();
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
#include <fstream>	
void UI_Equipment_Gem_Layer::RefreshEquipGemLayer()
{
	/************************************************************************/
	// 刷新整个当前界面
	RefreshEquipmentBaseInfo();		// 刷新装备的基础信息
	RefreshEquipmentGem();			// 刷新物品装备的宝石
	SetSelectedCellID();			// 设置当前默认的单元ID
	ShowTargetCellGemInfo();		// 设置默认选择的材料的显示信息
}

void UI_Equipment_Gem_Layer::SetSelectedCellID()
{
	/************************************************************************/
	// 设置当前默认的单元ID
	// 1. 判断该装备是不是的确存在
	Game_Data::Item* pEquipment = ITEM_MGR::instance()->get_item(m_nEquipItemID);
	if (pEquipment == NULL)
		return;

	// 2. 如果之前已经记录了当前的单元标识ID,则判断宝石是否还存在
	if (m_nCurrentCellID > -1 && m_nCurrentCellID < MAX_GEM_COUNT)
	{
		int nGemID = pEquipment->gem_id[m_nCurrentCellID];
		if (nGemID != 0)
			return;
	}
	
	// 3. 获取第一个宝石为选中的宝石
	for (int i = 0; i < MAX_GEM_COUNT; ++i)
	{
		int nGemID = pEquipment->gem_id[i];
		if (nGemID == 0)
			continue;

		m_nCurrentCellID = i;
		return;
	}
	
	// 4. 如果所有的条件都不满足的话,则设置m_nCurrentCellID为默认值
	m_nCurrentCellID = -1;
}


void UI_Equipment_Gem_Layer::RefreshEquipmentBaseInfo()
{
	/************************************************************************/
	// 刷新装备的基础信息
	// 1. 获取该装备的Config
	Game_Data::Item* pEquipment = ITEM_MGR::instance()->get_item(m_nEquipItemID);
	if (pEquipment == NULL)
		return;

	Game_Data::Item_Config * pItemConfig = pEquipment->config;
	if (pItemConfig == NULL)
		return;

	// 2. 设置装备的名字、Icon和需要的等级
	int nTemp = 0;
	const char * szTemp; 

	szTemp	= ITEM_CONFIG_MGR::instance()->get_icon_path(pItemConfig->icon);
    std::string p("icon/");
    p+=szTemp;
	nTemp	= strcmp(szTemp, "");
	if (nTemp > 0)
	{
		m_pEquipIcon->loadTexture(p.c_str());
	}
	
	szTemp = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(pItemConfig->name);						
	m_pEquipNameText->setString(szTemp);

	m_pEquipLevelText->setString(CCString::createWithFormat("Lv.%d", pEquipment->level)->getCString());		
}

void UI_Equipment_Gem_Layer::RefreshEquipmentGem()
{
	/************************************************************************/
	// 刷新物品装备的宝石
	// 1. 判断该装备是不是的确存在
	Game_Data::Item* pEquipment = ITEM_MGR::instance()->get_item(m_nEquipItemID);
	if (pEquipment == NULL)
		return;
	
	// 2. 清除每个Cell里面的信息
	ClearEachCell();

	// 3. 获取该装备上的宝石并显示在界面上
	for (int i = 0; i < MAX_GEM_COUNT; ++i)
	{
		int nGemID = pEquipment->gem_id[i];
		if (nGemID == 0)
			continue;
		
		UI_Equipment_Gem_Cell_Layer * pCell = dynamic_cast<UI_Equipment_Gem_Cell_Layer *>(m_pGemScrollView->getChildByTag(i));
		if (pCell == NULL)
			continue;

		pCell->SetCurrentGemInfoForShow(nGemID);
	}
}

void UI_Equipment_Gem_Layer::LoadScrollView()
{
	/************************************************************************/
	// 载入宝石滚动层
	// 1. 根据品质获取能镶嵌宝石的个数
	Game_Data::Item* pEquipment = ITEM_MGR::instance()->get_item(m_nEquipItemID);
	if (pEquipment == NULL)
		return;

    m_nCellCount = MAX_GEM_COUNT;

	// 2. 载入宝石滚动层
	int nWholeWidth		= m_pGemScrollView->getInnerContainerSize().width;
	int nWholeHeight	= m_pGemScrollView->getInnerContainerSize().height;

	m_nCellHeight		= nWholeHeight / gem_row;
	int nTotalHeight	= m_nCellHeight * m_nCellCount;
	m_nScrollviewHeight = nTotalHeight > nWholeHeight ? nTotalHeight : nWholeHeight;
	m_pGemScrollView->setInnerContainerSize(Size(nWholeWidth, m_nScrollviewHeight));
	m_pGemScrollView->jumpToTop();
}

void UI_Equipment_Gem_Layer::SetScrollViweCell()
{
	/************************************************************************/
	// 载入宝石滚动层单元
	for (int nIndex = 0; nIndex < m_nCellCount; ++nIndex)
	{
		UI_Equipment_Gem_Cell_Layer * pCell = UI_Equipment_Gem_Cell_Layer::create();
		pCell->setPosition(ccp(-10 , m_nScrollviewHeight - (nIndex + 1) * m_nCellHeight));
		pCell->setTag(nIndex);
		pCell->SetCellTagID(nIndex);
		m_pGemScrollView->addChild(pCell);
	}
}

void UI_Equipment_Gem_Layer::ShowTargetCellGemInfo()
{
	/************************************************************************/
	// 显示当前选中单元的宝石的信息
	// 1. 如果当前并没有选中任何的宝石
	if (m_nCurrentCellID == -1)
	{
		ShowCurrentGemDesAndBtn(false);
	}
	// 2. 如果当前选中了某个Cell
	else if (m_nCurrentCellID > -1 && m_nCurrentCellID < MAX_GEM_COUNT)
	{
		// 2_1. 判断该Cell里面是否有宝石
		UI_Equipment_Gem_Cell_Layer * pCell = dynamic_cast<UI_Equipment_Gem_Cell_Layer *>(m_pGemScrollView->getChildByTag(m_nCurrentCellID));
		if (pCell == NULL)
			return;
		
		uint64 nGemID = pCell->GetCellGemID();
		if (nGemID == 0)
			return;

		// 2_2. 目标装备中是否存在目标宝石
		if (!JudgeTargetGemInCurrentEquip(nGemID))
		{
			return;
		}

		/************************************************************************/
		// 条件满足设置显示信息
		// 1. 显示宝石的描述信息
		Game_Data::Gem_Config* config = ITEM_CONFIG_MGR::instance()->get_gem_config(nGemID);
		if (config == NULL)
		{
			return;
		}
		const char * szTemp = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(config->desc);
		m_pEquipDescribeText->setText(szTemp);

		// 2. 显示当前选中单元的描述信息和按钮
		ShowCurrentGemDesAndBtn(true);
	}
	// 3. 错误的TagID
	else
	{
		return;
	}
}

void UI_Equipment_Gem_Layer::ShowCurrentGemDesAndBtn(const bool bvalue)
{
	/************************************************************************/
	// 显示当前选中单元的描述信息和按钮
	// 1. 装备描述及背景图片
	m_pEquipDescribeBGImage->setVisible(bvalue);
	m_pEquipDescribeText->setVisible(bvalue);

	// 2. 卸下宝石按钮
	m_pEquipSetOffGemBtn->setVisible(bvalue);
	m_pEquipSetOffGemBtn->setEnabled(bvalue);

	// 3. 设置选中框的状态
	for (int nIndex = 0; nIndex < m_nCellCount; ++nIndex)
	{
		UI_Equipment_Gem_Cell_Layer * pCell = dynamic_cast<UI_Equipment_Gem_Cell_Layer *>(m_pGemScrollView->getChildByTag(nIndex));
		if (pCell == NULL)
			return;

		pCell->SetSelectedBoxState(m_nCurrentCellID == nIndex);
	}
}

void UI_Equipment_Gem_Layer::ClearEachCell()
{
	/************************************************************************/
	// 清除每个Cell里面的信息
	for (int nIndex = 0; nIndex < m_nCellCount; ++nIndex)
	{
		UI_Equipment_Gem_Cell_Layer * pCell = dynamic_cast<UI_Equipment_Gem_Cell_Layer *>(m_pGemScrollView->getChildByTag(nIndex));
		if (pCell == NULL)
			return;

		pCell->ClearGemInfo();
	}
	ShowCurrentGemDesAndBtn(false);
}

void UI_Equipment_Gem_Layer::ChangeOtherLayerState(const Child_Layer_State eType)
{
	/************************************************************************/
	// 切换到其余页面状态
	UI_Bag_Gem_Layer *pLayer = dynamic_cast<UI_Bag_Gem_Layer*>(this->getParent());
	if (pLayer == NULL)
		return;

	pLayer->ChildRequestChangeLayerState(eType);
}

bool UI_Equipment_Gem_Layer::JudgeTargetGemInCurrentEquip(const uint64 nGemID)
{
	/************************************************************************/
	// 目标装备中是否存在目标宝石
	Game_Data::Item* pEquipment = ITEM_MGR::instance()->get_item(m_nEquipItemID);
	if (pEquipment == NULL)
		return false;

	for (int i = 0; i < MAX_GEM_COUNT; ++i)
	{
		if (nGemID == pEquipment->gem_id[i])
		{
			return true;
		}
	}
	return false;
}

void UI_Equipment_Gem_Layer::OnBtnStrengthenTextCallBack(Ref*pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 强化按钮点击回调
	if (type != Widget::TouchEventType::ENDED)
		return;
	this->setVisible(false);

	ChangeOtherLayerState(Layer_State_Strengthen);
}

void UI_Equipment_Gem_Layer::OnBtnStarUpTextCallBack(Ref*pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 升星按钮点击回调
	if (type != Widget::TouchEventType::ENDED)
		return;
	UI_Bag_Info_Layer * pBagLayer = dynamic_cast<UI_Bag_Info_Layer *>(this->getParent()->getParent());
	if (pBagLayer == NULL)
		return;

	this->setVisible(false);

	ChangeOtherLayerState(Layer_State_StarUp);
}

void UI_Equipment_Gem_Layer::OnBtnWashCallBack(Ref*pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 洗炼按钮点击回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	if (type != Widget::TouchEventType::ENDED)
		return;
	UI_Bag_Info_Layer * pBagLayer = dynamic_cast<UI_Bag_Info_Layer *>(this->getParent()->getParent());
	if (pBagLayer == NULL)
		return;
	auto gem = this->getParent();
	auto delay = DelayTime::create(0.17);
	auto remove = CallFunc::create(CC_CALLBACK_0(UI_Bag_Gem_Layer::removeFromParent, gem) );
	auto seq = Sequence::createWithTwoActions(delay, remove);
	this->getParent()->runAction(seq);

	pBagLayer->ChangeLayerState(Layer_State_Wash);
}

void UI_Equipment_Gem_Layer::onGemCallback(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	_gemButtom->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
	m_pEquipStrengthenText->setBrightStyle(Widget::BrightStyle::NORMAL);
	m_pEquipStarUpText->setBrightStyle(Widget::BrightStyle::NORMAL);
	m_pEquipWashText->setBrightStyle(Widget::BrightStyle::NORMAL);

}

void UI_Equipment_Gem_Layer::OnBtnSetOffGemhCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 卸下宝石方法回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 1. 获取目标宝石ID
	UI_Equipment_Gem_Cell_Layer * pCell = dynamic_cast<UI_Equipment_Gem_Cell_Layer *>(m_pGemScrollView->getChildByTag(m_nCurrentCellID));
	if (pCell == NULL)
		return;

	uint64 nGemID = pCell->GetCellGemID();
	int nGemPos = pCell->GetCellTagID();
	if (nGemID == 0)
		return;

	// 2. 目标装备中是否存在目标宝石
	if (!JudgeTargetGemInCurrentEquip(nGemID))
		return;

	// 3. 发送消息请求镶嵌宝石
	Game_Data::Gem_Config* config = ITEM_CONFIG_MGR::instance()->get_gem_config(nGemID);
	if (config == NULL)
		return;

	ITEM_LOGIC::instance()->set_off_gem(m_nEquipItemID, nGemPos);
}

void UI_Equipment_Gem_Layer::onCloseCallBack(Ref* pSender, ui::Widget::TouchEventType type)
{
    if (type != Widget::TouchEventType::ENDED)
        return;
    //CC_SAFE_RETAIN(this);
    //this->removeFromParent();
    this->setVisible(false);
    
//    auto root = (Widget*)this->getParent();
//    auto Pnl_Equip_Bar = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Equip_Bar"));
//    Pnl_Equip_Bar->setVisible(true);
//    auto Pnl_Use = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Use"));
//    Pnl_Use->setVisible(false);
    ////auto compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_2"));
    ////compare->setVisible(true);
    //auto panel_right = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Panel_Right"));
    //panel_right->setVisible(false);
    ////auto panel_right1 = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Panel_Right_1"));
    ////panel_right1->setVisible(true);
    
//    auto Pnl_Bag = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Bag"));
//    Pnl_Bag->setVisible(true);
//    auto Pnl_Property = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Property"));
//    Pnl_Property->setVisible(false);
    
    UI_Bag_Info_Layer::sIsProperty = false;
}