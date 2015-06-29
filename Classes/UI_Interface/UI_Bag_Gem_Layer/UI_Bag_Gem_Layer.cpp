#include "cocos2d.h"
#include <fstream>	
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Game_Interface/common.h"

#include "Item_System/Item_Data.h"
#include "Item_Container_System/Item_Container_Data.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player.h"
#include "Game_Interface/game_content_interface.h"

#include "Item_System/Item_Config_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Item_Container_System/Item_Container_Data.h"
#include "Item_Container_System/Item_Container_Mgr_Cl.h"
#include "Item_System/Item_Logic_Cl.h"
#include "Item_System/Item_Mgr_Cl.h"
#include "Item_System/Item_Config_Data.h"

#include "UI_Interface/UI_Bag_Info_Layer.h"
#include "UI_Bag_Gem_Layer.h"

using namespace ui;

#define Line_Count 5								// ScrollView总行数
#define Row_Count  4 								// ScrollView总列数
#define MAX_TAG_COUNT  Line_Count * Row_Count		// Cell标识的最大数量

UI_Bag_Gem_Layer::UI_Bag_Gem_Layer()
{
	m_nCellTagID			= 0;
	m_nCurrentSelectedTagID = -1;
	m_nCurrentEquipPos		= -1;

	m_mapTargetTagItem.clear();
}


UI_Bag_Gem_Layer::~UI_Bag_Gem_Layer()
{

}


bool UI_Bag_Gem_Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Widget* pLayer	= cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/bag_Gem/bag_Gem.ExportJson");
	this->addChild(pLayer);

	// 镶嵌按钮
	m_pFillInButton		= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "FillIn_Text"));
	m_pFillInButton->setTouchEnabled(true);
	m_pFillInButton->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Gem_Layer::OnBtnFillInCallBack, this));

	// 合成按钮
	m_pCompoundButton	= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "compound_Text"));
	m_pCompoundButton->setTouchEnabled(true);
	m_pCompoundButton->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Gem_Layer::OnBtnCompoundTextCallBack, this));

	// 关闭按钮
	m_pCloseButton		= dynamic_cast<ui::Button*>(Helper::seekWidgetByName(pLayer, "Btn_Close_Bag"));
	m_pCloseButton->setTouchEnabled(true);
	m_pCloseButton->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Gem_Layer::OnBtnCloseCallBack, this));

	// 宝石名字
	m_pGemNameText		= dynamic_cast<ui::Text*>(Helper::seekWidgetByName(pLayer, "Name_Text"));

	// 元宝文本
	m_pGoldTextAtlas	= dynamic_cast<ui::TextAtlas*>(Helper::seekWidgetByName(pLayer, "AtlasLabel_38"));

	// 铜钱文本
	m_pMoneyTextAtlas	= dynamic_cast<ui::TextAtlas*>(Helper::seekWidgetByName(pLayer, "AtlasLabel_39"));

	// 滚动层
	m_pBagGemScrollView = dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(pLayer, "right_scroll"));

	return true;
}


void UI_Bag_Gem_Layer::onExit()
{
	Layer::onExit();
}


void UI_Bag_Gem_Layer::onEnter()
{
	Layer::onEnter();

	LoadScrollView();			 // 载入滚动层
	RefreshWholeLayer();		 // 刷新整个当前界面
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 页面刷新相关逻辑
void UI_Bag_Gem_Layer::LoadScrollView()
{
	/************************************************************************/
	// 载入滚动层
	// 1. 获取Json文件中设置的ScrollView的宽和高
	int nWholeWidth			= m_pBagGemScrollView->getInnerContainerSize().width;
	int nScrollviewHeight	= m_pBagGemScrollView->getInnerContainerSize().height;

	// 2. 设置ScrollView需要的宽和高
	int nCellHeight			= nScrollviewHeight / 3;
	int nCellWidth			= nWholeWidth / Row_Count;
	int nTotalHeight		= nCellHeight * Line_Count;
	int nWholeHeight		= nTotalHeight > nScrollviewHeight ? nTotalHeight : nScrollviewHeight;
	m_pBagGemScrollView->setInnerContainerSize(Size(nWholeWidth, nWholeHeight));
	m_pBagGemScrollView->jumpToTop();

	// 3. 读取资源添加Cell
	for (int nIndex_1 = 0; nIndex_1 < Line_Count; ++nIndex_1)
	{
		for (int nIndex_2 = 0; nIndex_2 < Row_Count; ++nIndex_2, ++m_nCellTagID)
		{
			Widget* pLayer = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/bag_Gem_Cell/bag_Gem_Cell.ExportJson");
			pLayer->setPosition(ccp(3 + nCellWidth * nIndex_2 , nWholeHeight - (nIndex_1 + 1) * nCellHeight));
			pLayer->setTag(m_nCellTagID);
			m_pBagGemScrollView->addChild(pLayer);
		}
	}
}


void UI_Bag_Gem_Layer::RefreshMoneyAndGold()
{
	/************************************************************************/
	// 刷新背包界面上的元宝和铜钱
	// 1. 判断玩家的数据是否异常
	int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* pPlayer = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(nPlayerID));
	if (pPlayer == NULL)
		return;

	const char* szTemp = NULL;
	// 2. 设置金币数量
	int nMoney = pPlayer->get_gold();
	if (nMoney >= 100000)
	{
		szTemp = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90626);
		m_pMoneyTextAtlas->setString(CCString::createWithFormat(szTemp , nMoney / 10000)->getCString());
	}
	else
	{
		m_pMoneyTextAtlas->setString(CCString::createWithFormat("%d", nMoney)->getCString());
	}

	// 3. 设置元宝数量
	int nGold = pPlayer->get_token();
	if (nGold >= 100000)
	{
		szTemp = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90626);
		m_pGoldTextAtlas->setString(CCString::createWithFormat(szTemp , nGold / 10000)->getCString());
	}
	else
	{
		m_pGoldTextAtlas->setString(CCString::createWithFormat("%d", nGold)->getCString());
	}
}


void UI_Bag_Gem_Layer::SetSelectedCellID()
{
	/************************************************************************/
	// 设置当前默认选中的单元ID
	// 1. 如果之前已经记录了当前的单元标识ID,则判断物品是否还存在
	if (m_nCurrentSelectedTagID > -1 && m_nCurrentSelectedTagID < MAX_TAG_COUNT)
	{
		map<int, Game_Data::Item_Container*>::const_iterator itor = m_mapTargetTagItem.find(m_nCurrentSelectedTagID);
		if (itor != m_mapTargetTagItem.end())
		{
			return;
		}
	}

	// 2. 判断玩家的数据是否异常
	int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* pPlayer = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(nPlayerID));
	if (pPlayer == NULL)
		return;

	// 3. 获取第一个材料的TagID
	int nIndex = 0;
	Game_Data::Item_Container_Map& map_bag_container = pPlayer->get_bag_item_container_map();
	Game_Data::Item_Container_Map_Iter iter = map_bag_container.begin();
	for (; iter != map_bag_container.end(); ++iter)
	{
		// 3_1. 
		if (iter->second->is_num_type == 0)
			continue;

		// 3_2. 
		uint64 nItemID = iter->second->item_id;
		Game_Data::Item_Config* pItemConfig = ITEM_CONFIG_MGR::instance()->get_item_config(nItemID);
		if (pItemConfig == NULL)
			continue;

		// 3_3. 判断物品的类型是不是材料
		int nType = pItemConfig->type;
		if (nType != 9)
			continue;

		// 3_4. 判断索引是否异常
		if (nIndex >= MAX_TAG_COUNT)
			break;

		/************************************************************************/
		// 条件满足设置默认的选择标识ID
		m_nCurrentSelectedTagID = nIndex;
		return;
	}

	// 4. 如果所有的条件都不满足的话,则设置m_nCurrentSelectedTagID为默认值
	m_nCurrentSelectedTagID = -1;
}



void UI_Bag_Gem_Layer::OpenMaterialTextAndBtn(const bool bValue_1 , const bool bValue_2 , const bool bValue_3 )
{
	/************************************************************************/
	// 是否打开材料的名字和按钮	
	// 1. 宝石名字文本
	m_pGemNameText->setVisible(bValue_1);

	// 2. 宝石镶嵌按钮
	m_pFillInButton->setVisible(bValue_2);
	m_pFillInButton->setEnabled(bValue_2);

	// 3. 宝石合成按钮
	m_pCompoundButton->setVisible(bValue_3);
	m_pCompoundButton->setEnabled(bValue_3);

	// 4. 设置选中框的状态
	for (int nIndex = 0; nIndex < MAX_TAG_COUNT; ++nIndex)
	{
		// 4_1. 读取Json文件获取包裹每一个单元格
		Widget *pLayer = dynamic_cast<Widget*>(m_pBagGemScrollView->getChildByTag(nIndex));
		if (pLayer == NULL)
			return;

		// 4_2. 设置物品选中框
		ImageView * pMaterialSelectedImage = dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Select_Box"));
		if (pMaterialSelectedImage == NULL)
			return;

		pMaterialSelectedImage->setVisible(m_nCurrentSelectedTagID == nIndex);
	}

}

void UI_Bag_Gem_Layer::RefreshWholeLayer()
{
	/************************************************************************/
	// 刷新整个当前界面
	RefreshMoneyAndGold();		 // 刷新背包界面上的元宝和铜钱
	RefreshBagMaterial();		 // 刷新背包里的材料
	SetSelectedCellID();		 // 设置当前默认选中的单元ID	
	SetSelcectedInfoForShow();	 // 设置默认选择的材料的显示信息
}

void UI_Bag_Gem_Layer::RefreshBagMaterial()
{
	/************************************************************************/
	// 刷新背包里的材料
	// 1. 判断玩家的数据是否异常
	int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* pPlayer = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(nPlayerID));
	if (pPlayer == NULL)
		return;

	// 2. 清除每个Cell里面的信息
	ClearEachCell();

	// 3. 获取玩家的所有的背包里物品数据
	int nIndex = 0;
	m_mapTargetTagItem.clear();
	Game_Data::Item_Container_Map& map_bag_container = pPlayer->get_bag_item_container_map();
	Game_Data::Item_Container_Map_Iter iter = map_bag_container.begin();
	for (; iter != map_bag_container.end(); ++iter)
	{
		// 注:下面的判断跟小邓确认下 参考UiBagInfoLayer2
		// 潘杰（12.15）
		// ...

		// 3_1. 
		// ...
		if (iter->second->is_num_type == 0)
			continue;

		// 3_2. 
		// ...
		uint64 nItemID = iter->second->item_id;
		Game_Data::Item_Config* pItemConfig = ITEM_CONFIG_MGR::instance()->get_item_config(nItemID);
		if (pItemConfig == NULL)
			continue;

		// 3_3. 判断物品的类型是不是材料
		// 这里的类型还要跟小邓确认下(注释写的是3 但是这里如果换成3的话没用)
		// 潘杰（12.15）
		// ...
		int nType = pItemConfig->type;
		if (nType != 9)
			continue;

		// 3_4. 判断索引是否异常
		if (nIndex >= MAX_TAG_COUNT)
			break;

		// 3_5. 设置该物品用于显示的数据
		if (!SetSingleCellInfo(nIndex, iter->second))
			continue;

		// 3_6. 将TagID和ItemContainer存到Map中
		m_mapTargetTagItem[nIndex] = iter->second;
		++nIndex;
	}
}


void UI_Bag_Gem_Layer::ClearEachCell()
{
	/************************************************************************/
	// 清除每个Cell里面的信息
	for (int nIndex = 0; nIndex < MAX_TAG_COUNT; ++nIndex)
	{
		// 1. 读取Json文件获取包裹每一个单元格
		Widget *pLayer = dynamic_cast<Widget*>(m_pBagGemScrollView->getChildByTag(nIndex));
		if (pLayer == NULL)
			return;

		// 2. 设置Icon
		ImageView * pMaterialImage = dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Icon_ImagerView"));
		if (pMaterialImage == NULL)
			return;

		pMaterialImage->setVisible(false);

		// 3. 设置物品选中框
		ImageView * pMaterialSelectedImage = dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Select_Box"));
		if (pMaterialSelectedImage == NULL)
			return;

		pMaterialSelectedImage->setVisible(false);

		// 4. 设置物品的个数
		TextAtlas * pMateriCount = dynamic_cast<ui::TextAtlas*>(Helper::seekWidgetByName(pLayer, "Count_Text"));
		if (pMateriCount == NULL)
			return;

		pMateriCount->setVisible(false);
	}
}


bool UI_Bag_Gem_Layer::SetSingleCellInfo(const int nTagID, Game_Data::Item_Container * pInfo)
{
	/************************************************************************/
	// 设置单个Cell的信息
	// 1. 判断索引ID是否异常
	if (nTagID >= MAX_TAG_COUNT)
		return false;

	// 2. 获取该物品的Config
	Game_Data::Item_Config * pItemConfig = ITEM_CONFIG_MGR::instance()->get_item_config(pInfo->item_id);
	if (pItemConfig == NULL)
		return false;

	// 3. 读取Json文件获取包裹每一个单元格
	Widget *pLayer = dynamic_cast<Widget*>(m_pBagGemScrollView->getChildByTag(nTagID));
	if (pLayer == NULL)
		return false;

	/************************************************************************/
	// 条件满足设置物品信息
	int nTemp = 0;
	const char * szTemp;
	// 1. 设置Icon
	ImageView * pMaterialImage = dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(pLayer, "Icon_ImagerView"));
	if (pMaterialImage == NULL)
		return false;

	szTemp	= ITEM_CONFIG_MGR::instance()->get_icon_path(pItemConfig->icon);
	nTemp	= strcmp(szTemp, "");
	if (nTemp <= 0)
		return false;

	pMaterialImage->loadTexture(szTemp, UI_TEX_TYPE_PLIST);
	pMaterialImage->setVisible(true);
	
	// 2. 设置物品的个数
	TextAtlas * pMateriCount = dynamic_cast<ui::TextAtlas*>(Helper::seekWidgetByName(pLayer, "Count_Text"));
	if (pMaterialImage == NULL)
		return false;

	pMateriCount->setString(CCString::createWithFormat("%d", pInfo->item_count)->getCString());
	pMateriCount->setVisible(true);

	// 3. 为每件物品注册点击事件
	pMaterialImage->setTag(nTagID);
	pMaterialImage->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Gem_Layer::OnBtnClickMaterialCallBack, this));
	return true;
}



//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 页面相关逻辑
void UI_Bag_Gem_Layer::HandleSelectMaterial(const int nTagID)
{
	/************************************************************************/
	// 处理选中的材料
	// 1. 判断TagID是否异常
	if (!JudgeTargetMaterialIsExist(nTagID))
		return;

	/************************************************************************/
	// 条件满足则记录TagID并刷新界面
	// 1. 存储并记录当前选中的材料标识ID
	m_nCurrentSelectedTagID = nTagID;

	// 2. 刷新界面
	SetSelcectedInfoForShow();
}


void UI_Bag_Gem_Layer::SetSelcectedInfoForShow()
{
	/************************************************************************/
	// 设置选中的材料用于显示的信息
	// 1. 如果当前并没有选择任何材料
	if (m_nCurrentSelectedTagID == -1)
	{
		OpenMaterialTextAndBtn(false ,false ,false);
	}
	// 2. 如果选择了某个材料
	else if (m_nCurrentSelectedTagID > -1)
	{
		// 2_1. 判断该材料的TagID是否异常
		if (!JudgeTargetMaterialIsExist(m_nCurrentSelectedTagID))
			return;

		/************************************************************************/
		// 条件满足设置显示信息
		// 1. 设置材料的名字
		Game_Data::Item_Container *pInfo = GetTargetMaterialInfo(m_nCurrentSelectedTagID);
		if (pInfo == NULL)
			return;

		uint64 nItemID = pInfo->item_id;
		Game_Data::Item_Config* pItemConfig = ITEM_CONFIG_MGR::instance()->get_item_config(nItemID);
		if (pItemConfig == NULL)
			return;

		const char * szTemp = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(pItemConfig->name);
		m_pGemNameText->setString(szTemp);

		// 2. 判断材料是否可以镶嵌到当前装备上
		bool bValue_1 = false;
		bValue_1 = JudgeTargetMaterialCanFillIn(m_nCurrentSelectedTagID);

		// 3. 判断当前材料是否可以合成
		bool bValue_2 = false;
		bValue_2 = JudgeTargetMaterialCanCompound(m_nCurrentSelectedTagID);

		// 4.设置按钮和显示文本的状态
		OpenMaterialTextAndBtn(true, bValue_1, bValue_2);
	}
	// 3. 错误的TagID
	else
	{
		return;
	}
}


void UI_Bag_Gem_Layer::CloseCurrentLayer()
{
	/************************************************************************/
	this->setVisible(true);
	auto root = (Widget*)this->getParent();
	//root->setVisible(false);
	auto Pnl_Equip_Bar = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Equip_Bar"));
	Pnl_Equip_Bar->setVisible(true);
	auto Pnl_Use = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Use"));
	Pnl_Use->setVisible(false);
	auto Pnl_Bag = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Bag"));
	Pnl_Bag->setVisible(true);
	auto Pnl_Property = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Property"));
	Pnl_Property->setVisible(false);
	// 2. 关闭当前界面
	auto delay = DelayTime::create(0.3);
	auto remove = CallFunc::create(CC_CALLBACK_0(UI_Bag_Gem_Layer::removeFromParent, this));
	auto seq = Sequence::createWithTwoActions(delay, remove);
	this->runAction(seq);
	//this->removeFromParent();
}

bool UI_Bag_Gem_Layer::JudgeTargetMaterialIsExist(const int nTagID)
{
	/************************************************************************/
	// 判断目标标识ID的材料是否存在
	Game_Data::Item_Container * pInfo = NULL;
	map<int, Game_Data::Item_Container*>::const_iterator itor = m_mapTargetTagItem.find(nTagID);
	if (itor != m_mapTargetTagItem.end())
	{
		pInfo = itor->second;
	}
	if (pInfo == NULL)
		return false;

	return true;
}


bool UI_Bag_Gem_Layer::JudgeTargetMaterialCanFillIn(const int nTagID)
{
	/************************************************************************/
	// 判读目标标识ID是否可以镶嵌
	// 1. 获取目标的ContainerID
	uint64 nContainerID = GetTargetCellContainerID(nTagID);
	if (nContainerID == 0)
	{
		return false;
	}

	// 2. 获取玩家的PlayerID
	int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();

	// 3. 条件满足判断目标可以镶嵌
	if (!ITEM_LOGIC::instance()->JudgeMaterialCanFillInTargetEquip(nPlayerID , nContainerID , m_nCurrentEquipPos))
	{
		return false;
	}
	return true;
}


bool UI_Bag_Gem_Layer::JudgeTargetMaterialCanCompound(const int nTagID)
{
	/************************************************************************/
	// 判读目标标识ID是否可以合成
	// 1. 获取目标的ContainerID
	uint64 nContainerID = GetTargetCellContainerID(nTagID);
	if (nContainerID == 0)
	{
		return false;
	}

	// 2. 获取玩家的PlayerID
	int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();

	// 3.判断目标可以合成
	if (!ITEM_LOGIC::instance()->JudgeTargetGemCanCompound(nPlayerID, nContainerID))
	{
		return false;
	}
	return true;
}


Game_Data::Item_Container * UI_Bag_Gem_Layer::GetTargetMaterialInfo(const int nTagID)
{
	/************************************************************************/
	// 获取目标ID的信息
	Game_Data::Item_Container * pInfo = NULL;
	map<int, Game_Data::Item_Container*>::const_iterator itor = m_mapTargetTagItem.find(nTagID);
	if (itor != m_mapTargetTagItem.end())
	{
		pInfo = itor->second;
	}
	return pInfo;
}

uint64 UI_Bag_Gem_Layer::GetTargetCellContainerID(const int nTagID)
{
	/************************************************************************/
	// 获取目标单元格的ContainerID
	// 1. 判断该材料的TagID是否异常
	if (!JudgeTargetMaterialIsExist(m_nCurrentSelectedTagID))
		return 0;

	// 2. 获取ContainerID
	int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Item_Container *pInfo = GetTargetMaterialInfo(m_nCurrentSelectedTagID);
	if (pInfo == NULL)
		return 0;

	return pInfo->id;
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 按钮点击方法回调
void UI_Bag_Gem_Layer::OnBtnCloseCallBack(Ref*pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 关闭按钮点击回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	CloseCurrentLayer();
}


void UI_Bag_Gem_Layer::OnBtnFillInCallBack(Ref*pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 宝石镶嵌按钮方法回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 1. 判读目标标识ID是否可以镶嵌
	if (!JudgeTargetMaterialCanFillIn(m_nCurrentSelectedTagID))
		return;

	// 2. 获取目标的ContainerID
	uint64 nContainerID = GetTargetCellContainerID(m_nCurrentSelectedTagID);
	if (nContainerID == 0)
		return;

	// 3. 发送消息请求镶嵌宝石
	int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();
	ITEM_LOGIC::instance()->set_on_gem(nPlayerID, nContainerID);
}


void UI_Bag_Gem_Layer::OnBtnCompoundTextCallBack(Ref*pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 宝石合成按钮方法回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	// 1. 判读目标标识ID是否可以合成
 	if (!JudgeTargetMaterialCanCompound(m_nCurrentSelectedTagID))
		return;

	// 2. 获取宝石ID
	Game_Data::Item_Container *pInfo = GetTargetMaterialInfo(m_nCurrentSelectedTagID);
	if (pInfo == NULL)
		return;

	int nGemID = pInfo->item_id;

	// 3. 发送消息请求镶嵌宝石
	ITEM_LOGIC::instance()->gem_level_up(nGemID, 1);
}

void UI_Bag_Gem_Layer::OnBtnClickMaterialCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 点击材料的方法回调
 	if (type != Widget::TouchEventType::ENDED)
		return;

	// 1. 获取被点击的材料的TagID
	ImageView * pMaterialImage = dynamic_cast<ui::ImageView*>(pSender);
	if (pMaterialImage == NULL)
		return;

	int nTagID = pMaterialImage->getTag();
	
	// 2. 处理目标TagID的显示信息
	HandleSelectMaterial(nTagID);
}

void UI_Bag_Gem_Layer::ChildRequestChangeLayerState(const Child_Layer_State eType)
{
	/************************************************************************/
	// 子页面请求切换界面	
	UI_Bag_Info_Layer *pLayer = dynamic_cast<UI_Bag_Info_Layer*>(this->getParent());
	if (pLayer == NULL)
		return;

	// 1. 关闭当前界面
	//this->removeFromParent();
	this->setVisible(false);

	// 2. 请求父页面打开其他界面
	pLayer->ChangeLayerState(eType);
}