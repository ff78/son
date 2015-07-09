#include "../UI_Equipment_Strength_Layer/UI_Equipment_Strengthen_Layer.h"
#include "../UI_Equipment_StarUp_Layer/UI_Equipment_StarUp_Layer.h"
#include "../UI_MainMenu_Layer.h"
#include "../UI_Bag_Info_Layer.h"

#include "cocostudio/CocoStudio.h"
#include "../../Item_System/Item_Mgr_Cl.h"
#include "../../Item_System/Item_Desc_Config_Mgr.h"
#include "../../Item_System/Item_Logic_Cl.h"
#include "../../Item_System/Item_Config_Data.h"
#include "../../Player_Account/Account_Data_Mgr.h"
#include "../../Character_System/Character_Mgr.h"
#include "../../Character_System/Player.h"

Value UI_Equipment_Strengthen_Layer::sGold(0);
Value UI_Equipment_Strengthen_Layer::sToken(0);

void UI_Equipment_Strengthen_Layer::update()
{
	//buttonOpenOrNot();
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if (!player)
	{
		return;
	}

	Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(role_id);
	if (!character)
	{
		return;
	}
	Game_Data::Item* item = NULL;
	item = ITEM_MGR::instance()->get_item(mItemId);
	if (!item)
		return;
	const char* szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(item->config->icon);
    std::string p("icon/");
    p+=szPath;
	const char* name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(item->config->name);

	curEquip->loadTexture(p.c_str());

	curName->setString(name);

	levelNeeded->setString(CCString::createWithFormat("Lv.%d", item->level)->getCString());

	levelCur->setString(CCString::createWithFormat("%d", item->level)->getCString());

	levelAfter->setString(CCString::createWithFormat("%d", item->level + 1)->getCString());

	powerTxt->setString(CCString::createWithFormat("%d", player->get_fighting_capacity())->getCString());

	int cost = ITEM_CONFIG_MGR::instance()->get_equipment_level_up_cost(item->config->base_id, item->level);
	int nextcost = ITEM_CONFIG_MGR::instance()->get_equipment_level_up_cost(item->config->base_id, item->level + 1);
	moneyNeeded->setString(CCString::createWithFormat("%d", cost)->getCString());
	nextMoneyNeeded->setString(CCString::createWithFormat("%d", nextcost)->getCString());

	int index = 0;
	for (int i = Game_Data::EAT_HEALTH; i < MAX_ATTR_COUNT && index < attr_num; ++i)
	{
		int before_attr = ITEM_CONFIG_MGR::instance()->get_equipment_attr(item->config->base_id, item->level, item->current_quality, i);
		if (before_attr > 0)
		{
			const char* attr_desc = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(i);
			int after_attr = ITEM_CONFIG_MGR::instance()->get_equipment_attr(item->config->base_id, item->level + 1, item->current_quality, i);
			mCurAttrs[index]->setString(CCString::createWithFormat("%s:%d", attr_desc, before_attr)->getCString());
			mCurAttrs[index]->setVisible(true);
			//mAfterAttrs[index]->setString(CCString::createWithFormat("%d(+%d)", after_attr, after_attr - before_attr)->getCString());
			mAfterAttrs[index]->setString(CCString::createWithFormat("%d(+%d)", before_attr, after_attr - before_attr)->getCString());
			mAfterAttrs[index]->setVisible(true);
			if (after_attr < before_attr)
			{
				//取消增加箭头的显示
			}
			++index;
		}

	}

	bool strengthenable = true;
	if (item->config->type != Game_Data::IT_EQUIPMENT)
	{
		strengthenable =  false;
	}

	if (item->general_id > 0)
	{
		Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(item->general_id);
		if (!character)
		{
			strengthenable = false;

		}

		if (item->level >= character->get_character_level())
		{
			strengthenable = false;

		}
	}
	else
	{
		if (item->level >= player->get_character_level())
		{
			strengthenable = false;

		}
	}

	int tmpCost = ITEM_CONFIG_MGR::instance()->get_equipment_level_up_cost(item->config->base_id, item->level);
	if (player->get_gold() < tmpCost)
	{
		strengthenable = false;

	}

	if (strengthenable)
	{
		strengthenBtn->setTouchEnabled(true);
		strengthenBtn->setBright(true);	
	}
	else
	{
		strengthenBtn->setTouchEnabled(false);
		strengthenBtn->setBright(false);
	}

	initData();

}

UI_Equipment_Strengthen_Layer::UI_Equipment_Strengthen_Layer()
{

}

UI_Equipment_Strengthen_Layer::~UI_Equipment_Strengthen_Layer()
{

}

void UI_Equipment_Strengthen_Layer::setVisible(bool visible)
{
	Layer::setVisible(visible);
	if (visible)
	{
		update();
	}
}

bool UI_Equipment_Strengthen_Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	root = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/refine.json");
	addChild(root);

	// 关闭按钮
	m_pCloseBtn = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(root, "Btn_Close"));
	m_pCloseBtn->setTouchEnabled(true);
	m_pCloseBtn->addTouchEventListener(CC_CALLBACK_2(UI_Equipment_Strengthen_Layer::OnBtnCloseCallBack, this));

	// 强化按钮
	m_pEquipStrengthenText = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(root, "Btn_Strengthen"));
	m_pEquipStrengthenText->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
	m_pEquipStrengthenText->setTouchEnabled(true);
	m_pEquipStrengthenText->addTouchEventListener( CC_CALLBACK_2(UI_Equipment_Strengthen_Layer::OnBtnStrengthenTextCallBack, this) );

	// 升星按钮
	m_pEquipStarUpText = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(root, "Btn_Stars"));
	m_pEquipStarUpText->setBrightStyle(Widget::BrightStyle::NORMAL);
	m_pEquipStarUpText->setTouchEnabled(true);
	m_pEquipStarUpText->addTouchEventListener( CC_CALLBACK_2(UI_Equipment_Strengthen_Layer::OnBtnStarUpTextCallBack, this) );

	// 宝石按钮
	m_pEquipGemText = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(root, "Btn_Gem"));
	m_pEquipGemText->setBrightStyle(Widget::BrightStyle::NORMAL);
	m_pEquipGemText->setTouchEnabled(true);
	m_pEquipGemText->addTouchEventListener( CC_CALLBACK_2(UI_Equipment_Strengthen_Layer::OnBtnGemCallBack, this) );

	_washButton = dynamic_cast<ui::Button*>( Helper::seekWidgetByName(root, "Btn_Wash") );
	_washButton->setBrightStyle(Widget::BrightStyle::NORMAL);
	_washButton->setTouchEnabled(true);
	_washButton->addTouchEventListener( CC_CALLBACK_2(UI_Equipment_Strengthen_Layer::onWashCallBack, this) );

	strengthenBtn = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(root, "Btn_Strenth"));
	strengthenBtn->setTouchEnabled(true);
	strengthenBtn->addTouchEventListener( CC_CALLBACK_2(UI_Equipment_Strengthen_Layer::strengthenCallback, this) );
	
	// 洗练按钮
	// 暂时当做关闭按钮

	//m_pEquipWashText = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Wash"));
	//m_pEquipWashText->setTouchEnabled(true);
	//m_pEquipWashText->addTouchEventListener(CC_CALLBACK_2(UI_Equipment_Strengthen_Layer::OnBtnCloseCallBack, this));
	auto grid = dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(root, "Img_Icon"));
	curEquip = ImageView::create();
	curEquip->setAnchorPoint(Vec2(0.5, 0.5));
	curEquip->setPosition(Vec2(32, 32));
	grid->addChild(curEquip);

	curName = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Icon_Name"));

	levelNeeded = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Lv_Needed"));

	levelCur = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Strenth_Value"));

	levelAfter = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Strenth_Value_Right"));

	powerTxt = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Power_Value"));

	moneyNeeded = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Money_Value"));
	nextMoneyNeeded = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Money_Value_Right"));

	mCurAttrs[0] = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Atk"));
	mCurAttrs[1] = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Defense"));

	mAfterAttrs[0] = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Atk_Right"));
	mAfterAttrs[1] = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Defense_Right"));

	update();

	return true;

}

void UI_Equipment_Strengthen_Layer::onExit()
{
	Layer::onExit();
}

void UI_Equipment_Strengthen_Layer::onEnter()
{
	Layer::onEnter();
	update();
}

/*-------------------------------------------- Callbacks  ---------------------------------------------*/
void UI_Equipment_Strengthen_Layer::OnBtnCloseCallBack(Ref*pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 关闭按钮点击回调
	if (type != Widget::TouchEventType::ENDED)
		return;
	//CC_SAFE_RETAIN(this);
	//this->removeFromParent();

	auto root = (Widget*)this->getParent();
	auto Pnl_Equip_Bar = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Equip_Bar"));
	Pnl_Equip_Bar->setVisible(true);
	auto Pnl_Use = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Use"));
	Pnl_Use->setVisible(false);
	////auto compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_2"));
	////compare->setVisible(true);
	//auto panel_right = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Panel_Right"));
	//panel_right->setVisible(false);
	////auto panel_right1 = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Panel_Right_1"));
	////panel_right1->setVisible(true);

	auto Pnl_Bag = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Bag"));
	Pnl_Bag->setVisible(true);
	auto Pnl_Property = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Property"));
	Pnl_Property->setVisible(false);

	this->setVisible(false);
    UI_Bag_Info_Layer::sIsProperty = false;
	//this->removeFromParent();
}

void UI_Equipment_Strengthen_Layer::OnBtnStrengthenTextCallBack(Ref*pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 强化按钮点击回调
	if (type != Widget::TouchEventType::ENDED)
		return;
	//auto mainmenu = (UI_MainMenu_Layer*)this->getParent()->getParent();
	//mainmenu->m_pEquipmentStrengthen->setVisible(true);
	//mainmenu->m_pEquipmentStarUp->setVisible(false);
	m_pEquipStrengthenText->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
	m_pEquipStarUpText->setBrightStyle(Widget::BrightStyle::NORMAL);
	m_pEquipGemText->setBrightStyle(Widget::BrightStyle::NORMAL);
	_washButton->setBrightStyle(Widget::BrightStyle::NORMAL);
}

void UI_Equipment_Strengthen_Layer::OnBtnStarUpTextCallBack(Ref*pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 升星按钮点击回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	UI_Bag_Info_Layer * pBagLayer = dynamic_cast<UI_Bag_Info_Layer *>(this->getParent());
	if (pBagLayer == NULL)
		return;

	this->setVisible(false);
	pBagLayer->ChangeLayerState(Layer_State_StarUp);

}

void UI_Equipment_Strengthen_Layer::OnBtnGemCallBack(Ref*pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 宝石按钮点击回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	UI_Bag_Info_Layer * pBagLayer = dynamic_cast<UI_Bag_Info_Layer *>(this->getParent());
	if (pBagLayer == NULL)
		return;

	this->setVisible(false);
	pBagLayer->ChangeLayerState(Layer_State_Gem);

	//m_pEquipStrengthenText->setBrightStyle(Widget::BrightStyle::NORMAL);
	//m_pEquipStarUpText->setBrightStyle(Widget::BrightStyle::NORMAL);
	//m_pEquipGemText->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);

}

void UI_Equipment_Strengthen_Layer::onWashCallBack(Ref*pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;

	UI_Bag_Info_Layer * pBagLayer = dynamic_cast<UI_Bag_Info_Layer *>(this->getParent());
	if (pBagLayer == NULL)
		return;

	this->setVisible(false);
	pBagLayer->ChangeLayerState(Layer_State_Wash);

}

void UI_Equipment_Strengthen_Layer::strengthenCallback(Ref* pSender, Widget::TouchEventType type)
{
	int role_id;
	Game_Data::Player* player;
	bool ok;
	Game_Data::Item* item;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
													   role_id = Account_Data_Mgr::instance()->get_current_role_id();
													   player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
													   if (!player)
													   {
														   return;
													   }

													   ok = ITEM_LOGIC::instance()->equipment_level_up(mItemId);
													   if (ok)
													   {
														   /*if (GUIDE_EQUIP_STEP_3 == player->get_guide_id())
														   {
														   player->change_guide_id(player->get_guide_id() + 1);
														   showGuide();
														   }
														   if (GUIDE_EQUIP_STEP_2 == player->get_guide_id())
														   {
														   player->change_guide_id(player->get_guide_id() + 2);
														   showGuide();
														   }

														   item = ITEM_MGR::instance()->get_item(m_bar_item_id[m_select_index]);
														   if (item && item->config->base_id == m_quest_item_base_id)
														   {
														   m_quest_item_base_id = 0;
														   }*/
													   }
	}	
		break;
	default:
		break;
	}

}
/*-------------------------------------------- Callbacks  ---------------------------------------------*/

bool UI_Equipment_Strengthen_Layer::initData()
{
	bool bRet = false;
	do
	{
		int player_id;
		Game_Data::Player* player;
		player_id = Account_Data_Mgr::instance()->get_current_role_id();
		player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
		if (player)
		{
			UI_Equipment_Strengthen_Layer::sToken = player->get_token();
			UI_Equipment_Strengthen_Layer::sGold = player->get_gold();
		}

		retainToken = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(root, "Ats_Retain_Token"));
		CC_BREAK_IF(!retainToken);
		auto tokenStr = sToken.asString();
		retainToken->setString(tokenStr);

		retainGold = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(root, "Ats_Retain_Gold"));
		CC_BREAK_IF(!retainGold);
		auto goldStr = sGold.asString();
		retainGold->setString(goldStr);

		bRet = true;

	} while (false);

	return bRet;

}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 发送消息

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 接收消息