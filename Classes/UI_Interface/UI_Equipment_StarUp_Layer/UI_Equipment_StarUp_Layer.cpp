#include "UI_Equipment_StarUp_Layer.h"
#include "cocostudio/CocoStudio.h"
#include "../UI_MainMenu_Layer.h"
#include "../UI_Bag_Info_Layer.h"
#include "../../Item_System/Item_Mgr_Cl.h"
#include "../../Item_System/Item_Desc_Config_Mgr.h"
#include "../../Item_System/Item_Logic_Cl.h"
#include "../../Item_System/Item_Config_Data.h"
#include "../../Player_Account/Account_Data_Mgr.h"
#include "../../Character_System/Character_Mgr.h"
#include "../../Character_System/Player.h"
#include "../UI_ModalDialogue_Layer.h"


Value UI_Equipment_StarUp_Layer::sGold(0);
Value UI_Equipment_StarUp_Layer::sToken(0);

UI_Equipment_StarUp_Layer::UI_Equipment_StarUp_Layer()
{

}

UI_Equipment_StarUp_Layer::~UI_Equipment_StarUp_Layer()
{

}

bool UI_Equipment_StarUp_Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	root = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/refine_starup/refine_starup.ExportJson");
	addChild(root);
	// 关闭按钮
	m_pCloseBtn = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(root, "Btn_Close"));
	m_pCloseBtn->setTouchEnabled(true);
	m_pCloseBtn->addTouchEventListener(CC_CALLBACK_2(UI_Equipment_StarUp_Layer::onCloseCallBack, this));

	// 强化按钮
	m_pEquipStrengthenText = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(root, "Btn_Strengthen"));
	m_pEquipStrengthenText->setBrightStyle(Widget::BrightStyle::NORMAL);
	m_pEquipStrengthenText->setTouchEnabled(true);
	m_pEquipStrengthenText->addTouchEventListener(CC_CALLBACK_2(UI_Equipment_StarUp_Layer::onStrengthenTextCallBack, this));

	// 升星按钮
	m_pEquipStarUpText = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(root, "Btn_Stars"));
	m_pEquipStarUpText->setTouchEnabled(true);
	m_pEquipStarUpText->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
	m_pEquipStarUpText->addTouchEventListener(CC_CALLBACK_2(UI_Equipment_StarUp_Layer::onStarUpTextCallBack, this));

	// 宝石按钮
	m_pEquipGemText = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(root, "Btn_Gem"));
	m_pEquipGemText->setTouchEnabled(true);
	m_pEquipGemText->setBrightStyle(Widget::BrightStyle::NORMAL);
	m_pEquipGemText->addTouchEventListener(CC_CALLBACK_2(UI_Equipment_StarUp_Layer::onGemCallBack, this));

	auto wash = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(root, "Btn_Wash"));
	wash->setTouchEnabled(true);
	wash->setBrightStyle(Widget::BrightStyle::NORMAL);
	wash->addTouchEventListener(CC_CALLBACK_2(UI_Equipment_StarUp_Layer::onWashCallBack, this));
	
	starupBtn = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(root, "Btn_Starup"));
	starupBtn->addTouchEventListener(CC_CALLBACK_2(UI_Equipment_StarUp_Layer::starupCallback, this));

	auto grid = dynamic_cast<ui::ImageView*>(Helper::seekWidgetByName(root, "Img_Icon"));
	curEquip = ImageView::create();
	curEquip->setAnchorPoint(Vec2(0.5, 0.5));
	curEquip->setPosition(Vec2(32, 32));
	grid->addChild(curEquip);

	curName = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Icon_Name"));

	levelNeeded = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Lv_Needed"));

	for (int i = 0; i < 9;i++)
	{
		std::string starLevelName("Txt_Star_");
		Value suff(i + 1);
		std::string starLevelNameSuff = suff.asString();
		starLevelName += starLevelNameSuff;
		starLevelTxt[i] = dynamic_cast<Text*>(Helper::seekWidgetByName(root, starLevelName.c_str() ) );


		std::string starsName("Img_Starup_");
		Value tmp1(i+1);
		std::string starsNameSuff = tmp1.asString();
		starsName += starsNameSuff;
		stars[i] = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, starsName.c_str()));

		std::string starsAfterName("Img_Starup_Right_");
		Value tmp2(i + 1);
		std::string starsAfterNameSuff = tmp2.asString();
		starsAfterName += starsAfterNameSuff;
		starsAfter[i] = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, starsAfterName.c_str()));

	}

	starsLeft = dynamic_cast<Text*>(Helper::seekWidgetByName(root, "Txt_Starup_Title"));
	starsRight = dynamic_cast<Text*>(Helper::seekWidgetByName(root, "Txt_Starup_Title_Right"));
	//mStarsCur = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Strenth_Value"));

	//mStarsAfter = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Strenth_Value_Right"));

	powerTxt = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Power_Value"));

	moneyNeeded = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Money_Value"));
	nextMoneyNeeded = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Money_Value_Right"));

	mCurAttrs[0] = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Atk"));
	mCurAttrs[1] = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Defense"));

	mAfterAttrs[0] = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Atk_Right"));
	mAfterAttrs[1] = dynamic_cast<ui::Text*>(Helper::seekWidgetByName(root, "Txt_Defense_Right"));


	retainToken = dynamic_cast<cocos2d::ui::TextAtlas*>(Helper::seekWidgetByName(root, "Ats_Retain_Token"));
	retainGold = dynamic_cast<cocos2d::ui::TextAtlas*>(Helper::seekWidgetByName(root, "Ats_Retain_Gold"));
	
	return true;

}

void UI_Equipment_StarUp_Layer::onExit()
{
	Layer::onExit();

}

void UI_Equipment_StarUp_Layer::onEnter()
{
	Layer::onEnter();
}

void UI_Equipment_StarUp_Layer::setVisible(bool visible)
{
	Layer::setVisible(visible);
	if(visible)
		update();
	
}

void UI_Equipment_StarUp_Layer::update()
{
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
	const char* name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(item->config->name);

	curEquip->loadTexture(szPath, Widget::TextureResType::PLIST);

	curName->setString(name);

	levelNeeded->setString(CCString::createWithFormat("Lv.%d", item->level)->getCString());

	//levelCur->setString(CCString::createWithFormat("%d", item->level)->getCString());

	//levelAfter->setString(CCString::createWithFormat("%d", item->level + 1)->getCString());

	powerTxt->setString(CCString::createWithFormat("%d", player->get_fighting_capacity())->getCString());

	//int cost = ITEM_CONFIG_MGR::instance()->get_equipment_level_up_cost(item->config->base_id, item->level);
	Game_Data::quality_upgrade_config* starConfig = ITEM_CONFIG_MGR::instance()->get_quality_upgrade_config(item->config->type, item->current_quality);
	curCost = starConfig->get_token();
	moneyNeeded->setString(CCString::createWithFormat("%d", curCost)->getCString());
	
	//int nextcost = ITEM_CONFIG_MGR::instance()->get_equipment_level_up_cost(item->config->base_id, item->level + 1);
	Game_Data::quality_upgrade_config* starConfig1 = ITEM_CONFIG_MGR::instance()->get_quality_upgrade_config(item->config->type, item->current_quality+1);
	int nextcost = starConfig1->get_token();
	nextMoneyNeeded->setString(CCString::createWithFormat("%d", nextcost)->getCString());

	mStarsCur = item->current_quality;
	mStarsAfter = item->current_quality+1;

	starupBtn->setVisible(true);
	if (mStarsCur >= 8)
		starupBtn->setVisible(false);
	if (mStarsAfter >= 8)
		mStarsAfter = 8;
	starsLeft->setString(starLevelTxt[mStarsCur]->getString());
	starsRight->setString(starLevelTxt[mStarsAfter]->getString());
	for (int i = 0; i < 9; i++)
	{
		stars[i]->setVisible(false);
		starsAfter[i]->setVisible(false);
	}

	for (int i = 0; i < mStarsCur+1; i++)
	{
		stars[i]->setVisible(true);
	}
	for (int i = 0; i < mStarsAfter+1; i++)
	{
		starsAfter[i]->setVisible(true);

	}
	int index = 0;
	for (int i = Game_Data::EAT_HEALTH; i < MAX_ATTR_COUNT && index < attr_num; ++i)
	{
		int before_attr = ITEM_CONFIG_MGR::instance()->get_equipment_attr(item->config->base_id, item->level, item->current_quality, i);
		if (before_attr > 0)
		{
			const char* attr_desc = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(i);
			int after_attr = ITEM_CONFIG_MGR::instance()->get_equipment_attr(item->config->base_id, item->level, item->current_quality+1, i);
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

	bool starupable = true;
	if (item->config->type != Game_Data::IT_EQUIPMENT)
	{
		starupable = false;
	}

	if (item->general_id > 0)
	{
		Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(item->general_id);
		if (!character)
		{
			starupable = false;

		}

		//if (item->level > character->get_character_level())
		//{
		//	starupable = false;

		//}

		if (item->current_quality > character->get_character_level())
		{
			starupable = false;

		}
	}
	else
	{
		if (item->level >= player->get_character_level())
		{
			starupable = false;

		}
	}

	//int tmpCost = ITEM_CONFIG_MGR::instance()->get_equipment_level_up_cost(item->config->base_id, item->level);
	//if (player->get_gold() < tmpCost)
	//{
	//	starupable = false;

	//}

	if (starupable)
	{
		starupBtn->setTouchEnabled(true);
		starupBtn->setBright(true);
	}
	else
	{
		starupBtn->setTouchEnabled(false);
		starupBtn->setBright(false);
	}

	auto ten = dynamic_cast<ui::Button*>(Helper::seekWidgetByName( root, "Btn_Starup_ten") ); 

	ten->setTouchEnabled(false);
	ten->setBright(false);

	initData();

}

void UI_Equipment_StarUp_Layer::onCloseCallBack(Ref* pSender, ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	//CC_SAFE_RETAIN(this);
	//this->removeFromParent();
	this->setVisible(false);

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

}

void UI_Equipment_StarUp_Layer::onStrengthenTextCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 强化按钮点击回调
	if (type != Widget::TouchEventType::ENDED)
		return;

	UI_Bag_Info_Layer * pBagLayer = dynamic_cast<UI_Bag_Info_Layer *>(this->getParent());
	if (pBagLayer == NULL)
		return;

	this->setVisible(false);
	
	pBagLayer->ChangeLayerState(Layer_State_Strengthen);
}

void UI_Equipment_StarUp_Layer::onStarUpTextCallBack(Ref* pSender, Widget::TouchEventType type)
{
	/************************************************************************/
	// 升星按钮点击回调
	if (type != Widget::TouchEventType::ENDED)
		return;
	m_pEquipStrengthenText->setBrightStyle(Widget::BrightStyle::NORMAL);
	m_pEquipStarUpText->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
	m_pEquipGemText->setBrightStyle(Widget::BrightStyle::NORMAL);


}

void UI_Equipment_StarUp_Layer::onGemCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;

	UI_Bag_Info_Layer * pBagLayer = dynamic_cast<UI_Bag_Info_Layer *>(this->getParent());
	if (pBagLayer == NULL)
		return;

	auto mainMenu = (UI_MainMenu_Layer*)pBagLayer->getParent();
	this->setVisible(false);

	pBagLayer->ChangeLayerState(Layer_State_Gem);
}

void UI_Equipment_StarUp_Layer::onWashCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	UI_Bag_Info_Layer * pBagLayer = dynamic_cast<UI_Bag_Info_Layer *>(this->getParent());
	if (pBagLayer == NULL)
		return;

	this->setVisible(false);
	pBagLayer->ChangeLayerState(Layer_State_Wash);

}

void UI_Equipment_StarUp_Layer::starupCallback(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	int role_id;
	Game_Data::Player* player;
	role_id = Account_Data_Mgr::instance()->get_current_role_id();
	player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if (!player)
		return;
	if (curCost > player->get_token())
	{
		UI_ModalDialogue_Layer::DoModal("", "元宝不足！", UI_ModalDialogue_Layer::DT_OK, [&]()
		{

			//Game_Utils::instance()->reset_role_actor();
		}
		);
		return;
	}
	/*if (!player)
	{
		return;
	}
	if (GUIDE_EQUIP_QUA_UP_3 == player->get_guide_id()
		|| GUIDE_EQUIP_QUA_UP_4 == player->get_guide_id()
		)
	{
		player->change_guide_id(GUIDE_EQUIP_QUA_UP_5 + 1);
		showGuide();
	}*/
	ITEM_LOGIC::instance()->equipment_quality_up(mItemId);

}

void UI_Equipment_StarUp_Layer::starupTenCallback(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
}

bool UI_Equipment_StarUp_Layer::initData()
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
			UI_Equipment_StarUp_Layer::sToken = player->get_token();
			UI_Equipment_StarUp_Layer::sGold = player->get_gold();
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