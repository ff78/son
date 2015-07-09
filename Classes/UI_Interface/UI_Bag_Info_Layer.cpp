#pragma once
#include "UI_Bag_Info_Layer.h"

#include "cocostudio/CocoStudio.h"

#include "../Player_Account/Account_Data_Mgr.h"
#include "../Character_System/Character_Mgr.h"
#include "../Character_System/Player.h"

#include "UI_MainMenu_Layer.h"
#include "UI_Equipment_Gem_Layer/UI_Equipment_Gem_Layer.h"
#include "UI_Interface/UI_Bag_Gem_Layer/UI_Bag_Gem_Layer.h"
#include "UI_Equipment_Strength_Layer/UI_Equipment_Strengthen_Layer.h"
#include "UI_Equipment_StarUp_Layer/UI_Equipment_StarUp_Layer.h"
#include "UI_Wash_Layer/WashLayer.h"
#include "Joiner_Guidance.h"

#include "../DataModule/Little.h"

USING_NS_CC;
using namespace ui;
using namespace cocos2d;
using namespace cocostudio;

Value UI_Bag_Info_Layer::sIsProperty(false);
Value UI_Bag_Info_Layer::sCurPageIdx(0);
Value UI_Bag_Info_Layer::sGold(0);
Value UI_Bag_Info_Layer::sToken(0);
Value UI_Bag_Info_Layer::sName(0);
Value UI_Bag_Info_Layer::sPower(0);
Value UI_Bag_Info_Layer::sTili(0);
Value UI_Bag_Info_Layer::sExp(0);
Value UI_Bag_Info_Layer::sHP(0);
Value UI_Bag_Info_Layer::sAtk(0);
Value UI_Bag_Info_Layer::sGuard(0);
Value UI_Bag_Info_Layer::sMP(0);
Value UI_Bag_Info_Layer::sLevel(0);
Value UI_Bag_Info_Layer::sJob(3);
Value UI_Bag_Info_Layer::sJobStrings[5] = { Value("sword1"), Value("sword2"), Value("sword3"), Value("sword4"), Value("sword5") };

UI_Bag_Info_Layer::UI_Bag_Info_Layer(void)
{
	m_nCurrentEquipTag = -1;

	memset(m_img_equipment_bar, 0, sizeof(m_img_equipment_bar));
	memset(m_bar_ids, 0, sizeof(m_bar_ids));
}

bool UI_Bag_Info_Layer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		CC_BREAK_IF(!initRoot());
		CC_BREAK_IF(!initData());
		//CC_BREAK_IF(!initIconInfo());
		bRet = true;

	} while (false);

	return bRet;
}

bool UI_Bag_Info_Layer::initRoot()
{
	bool bRet = false;
	do
	{
		ITEM_CONFIG_MGR::instance()->load_icon_config_data();
		//root = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/bag_new_1/bag_new_1.ExportJson");
		root = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/bag_all.json");
		CC_BREAK_IF(!root);

		//auto tidy = dynamic_cast<Text*>(Helper::seekWidgetByName(root, "Label_40"));
		//CC_BREAK_IF(!tidy);
		//tidy->setVisible(false);
		//tidy->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::tidyCallback, this));

		/*auto sellEquip = dynamic_cast<Button*>(Helper::seekWidgetByName(root, "Button_227_0"));
		CC_BREAK_IF(!sellEquip);
		sellEquip->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::sellEquipCallback,this));*/
        auto title = dynamic_cast<Text*>(Helper::seekWidgetByName(root, "Txt_Top_property"));
        auto bagTitle = dynamic_cast<Text*>(Helper::seekWidgetByName(root, "Txt_Top_bag"));
        title->setVisible(sIsProperty.asBool());
        bagTitle->setVisible(!sIsProperty.asBool());
        
		auto sellEquip = dynamic_cast<Button*>(Helper::seekWidgetByName(root, "Btn_Sell"));
		CC_BREAK_IF(!sellEquip);
		sellEquip->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::sellEquipCallback, this));

		//auto head = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, "headicon"));
		auto head = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, "Img_Head"));
		CC_BREAK_IF(!head);
		int role_id = Account_Data_Mgr::instance()->get_current_role_id();
		auto player = (Game_Data::Player*)CHARACTER_MGR::instance()->get_character(role_id);
		int job = player->get_job();
		if (job >= 3)
			job = 3;
		Value pre("img/headIcon/role");
		Value suff(job);
		Value path(pre.asString() + suff.asString() + ".png");
		head->loadTexture(path.asString());
		head->setTouchEnabled(true);
		head->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::headCallback, this));

		//auto closeCompare = dynamic_cast<Button*>(Helper::seekWidgetByName(root, "Btn_Compare"));
		auto closeCompare = dynamic_cast<Button*>(Helper::seekWidgetByName(root, "Btn_Close_Compare"));
		CC_BREAK_IF(!closeCompare);
		closeCompare->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::closeCompareCallback, this));

		auto closeProperty = dynamic_cast<Button*>(Helper::seekWidgetByName(root, "Btn_Close_Property"));
		CC_BREAK_IF(!closeProperty);
		closeProperty->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::closePropertyCallback, this));

		//auto closeAnotherBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(root, "Btn_Close_EntityAndMaterial"));
		auto closeAnotherBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(root, "Btn_Close_Use_Left"));
		CC_BREAK_IF(!closeAnotherBtn);
		closeAnotherBtn->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::closeUseCallback, this));

		closeBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(root, "Btn_Close_Bag"));
		CC_BREAK_IF(!closeBtn);
		closeBtn->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::closeBagCallBack, this));


		equBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(root, "Btn_Equip"));
		CC_BREAK_IF(!equBtn);
		equBtn->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
		equBtn->setTouchEnabled(true);
		equBtn->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::equipmentCallback, this));

		entityBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(root, "Btn_Entity"));
		CC_BREAK_IF(!entityBtn);
		entityBtn->setTouchEnabled(true);
		entityBtn->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::entityCallback, this));


		materialBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(root, "Btn_Material"));
		CC_BREAK_IF(!materialBtn);
		materialBtn->setTouchEnabled(true);
		materialBtn->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::materialCallback, this));

		unwearBtn = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(root, "Btn_Unwear"));
		CC_BREAK_IF(!unwearBtn);
		unwearBtn->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::unwearCallback, this));

		//wearBtn = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(root, "Button_228"));
		wearBtn = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(root, "Btn_Wear"));
		CC_BREAK_IF(!wearBtn);
		wearBtn->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::wearCallback, this));

		rightScroll = dynamic_cast<cocos2d::ui::ScrollView*>(Helper::seekWidgetByName(root, "right_scroll"));
		CC_BREAK_IF(!rightScroll);

		refine = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(root, "Btn_Refine"));
		CC_BREAK_IF(!refine);
		refine->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::refineCallback, this));

		refineLeft = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(root, "Btn_Refine_Left"));
		CC_BREAK_IF(!refineLeft);
		refineLeft->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::refineCallback, this));

		initBagGrid();
		initBarGrid();	

		addChild(root);

		bRet = true;

	} while (false);

	return bRet;

}

bool UI_Bag_Info_Layer::initData()
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
			UI_Bag_Info_Layer::sToken = player->get_token();
			UI_Bag_Info_Layer::sGold = player->get_gold();

			UI_Bag_Info_Layer::sName = player->get_character_name();
			UI_Bag_Info_Layer::sPower = player->get_fighting_capacity();
            UI_Bag_Info_Layer::sTili = player->get_energy();
			//int Exp = player->get_character
			UI_Bag_Info_Layer::sHP = player->get_character_cur_hp();
			UI_Bag_Info_Layer::sAtk = player->get_character_attack();
			UI_Bag_Info_Layer::sGuard = player->get_character_define();
			UI_Bag_Info_Layer::sMP = player->get_character_cur_mp();
			UI_Bag_Info_Layer::sLevel = player->get_character_level();
			UI_Bag_Info_Layer::sJob = player->get_job();
		}
        auto title = dynamic_cast<Text*>(Helper::seekWidgetByName(root, "Txt_Top_property"));
        auto bagTitle = dynamic_cast<Text*>(Helper::seekWidgetByName(root, "Txt_Top_bag"));
        title->setVisible(sIsProperty.asBool());
        bagTitle->setVisible(!sIsProperty.asBool());

		//curPageNum = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(root, "AtlasLabel_44"));
		//CC_BREAK_IF(!curPageNum);
		//auto curPageStr = sCurPageIdx.asString();
		//curPageNum->setString(curPageStr);

		tokenAtlas = dynamic_cast<Text*>(Helper::seekWidgetByName(root, "AtlasLabel_38"));
		CC_BREAK_IF(!tokenAtlas);
		auto tokenStr = sToken.asString();
		tokenAtlas->setString(tokenStr);

		goldAtlas = dynamic_cast<Text*>(Helper::seekWidgetByName(root, "AtlasLabel_39"));
		CC_BREAK_IF(!goldAtlas);
		auto goldStr = sGold.asString();
		goldAtlas->setString(goldStr);

		//nameTxt = dynamic_cast<Text*>(Helper::seekWidgetByName(root, "name"));
		nameTxt = dynamic_cast<Text*>(Helper::seekWidgetByName(root, "Txt_Name"));
		CC_BREAK_IF(!nameTxt);
		auto nameStr = sName.asString();
		nameTxt->setString(nameStr);

		//powerAtlas = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(root, "bp_atlas"));
		powerAtlas = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(root, "Tts_Power_Value"));
		CC_BREAK_IF(!powerAtlas);
		auto powerStr = sPower.asString();
		powerAtlas->setString(powerStr);
        
        tiliAtlas = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(root, "tili"));
        CC_BREAK_IF(!tiliAtlas);
        auto tiliStr = sTili.asString();
        tiliAtlas->setString(powerStr);

		hpAtlas = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(root, "HP_atlas"));
		CC_BREAK_IF(!hpAtlas);
		auto hpStr = sHP.asString();
		hpAtlas->setString(hpStr);

		atkAtlas = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(root, "ATK_atlas"));
		CC_BREAK_IF(!atkAtlas);
		auto atkStr = sAtk.asString();
		atkAtlas->setString(atkStr);

		guardAtlas = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(root, "Guard_atlas"));
		CC_BREAK_IF(!guardAtlas);
		auto guardStr = sGuard.asString();
		guardAtlas->setString(guardStr);

		mpAtlas = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(root, "MP_atlas"));
		CC_BREAK_IF(!mpAtlas);
		auto mpStr = sAtk.asString();
		mpAtlas->setString(mpStr);

		levelAtlas = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(root, "level_01_atlas"));
		auto levelAtlas1 = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(root, "Tts_Level"));
		CC_BREAK_IF(!levelAtlas);
		auto levelStr = sLevel.asString();
		levelAtlas->setString(levelStr);
		levelAtlas1->setString(levelStr);

		jobTxt = dynamic_cast<Text*>(Helper::seekWidgetByName(root, "job_txt"));
		CC_BREAK_IF(!jobTxt);
		int jobIdx = player->get_job();		
		jobTxt->setString(Little::jobs[jobIdx].name);

		//setTypeIndex(INDEX_0); //INDEX_0|INDEX_1|INDEX_2

		bRet = true;

	} while (false);

	return bRet;
}

void UI_Bag_Info_Layer::tidyCallback(Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
										  ITEM_LOGIC::instance()->tidy_item();
	}
		break;
	default:
		break;
	}

}

void UI_Bag_Info_Layer::sellEquipCallback(Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
										  ITEM_LOGIC::instance()->sell_item(mPara[1], 1);
										  /*auto left = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer"));
										  left->setVisible(true);*/
										  auto Pnl_Equip_Bar = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Equip_Bar"));
										  Pnl_Equip_Bar->setVisible(true);
										  /*auto anotherLeft = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_1"));
										  anotherLeft->setVisible(false);*/
										  auto Pnl_Use = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Use"));
										  Pnl_Use->setVisible(false);

										  /*auto compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_2"));
										  compare->setVisible(false);*/
										  auto Pnl_Compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Compare"));
										  Pnl_Compare->setVisible(false);

										  /*auto right = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer_1"));
										  right->setVisible(false);*/
										  auto Pnl_Property = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Property"));
										  Pnl_Property->setVisible(false);

										  /*auto right1 = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer"));
										  right1->setVisible(true);*/
										  auto Pnl_Bag = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Bag"));
										  Pnl_Bag->setVisible(true);
	}
		break;
	default:
		break;
	}

}

void UI_Bag_Info_Layer::headCallback(Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
										  /*auto right = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer"));
										  right->setVisible(false);*/
										  auto Pnl_Bag = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Bag"));
										  Pnl_Bag->setVisible(false);

										  /*auto right1 = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer_1"));
										  right1->setVisible(true);*/
										  auto Pnl_Property = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Property"));
										  Pnl_Property->setVisible(true);
	}
		break;
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void UI_Bag_Info_Layer::closeCompareCallback(Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{

										  /*auto left = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer"));
										  left->setVisible(true);*/
										  auto Pnl_Equip_Bar = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Equip_Bar"));
										  Pnl_Equip_Bar->setVisible(true);

										  /*auto anotherLeft = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_1"));
										  anotherLeft->setVisible(false);*/
										  auto Pnl_Use = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Use"));
										  Pnl_Use->setVisible(false);

										  /*auto compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_2"));
										  compare->setVisible(false);*/
										  auto Pnl_Compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Compare"));
										  Pnl_Compare->setVisible(false);

										  /*auto right = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer_1"));
										  right->setVisible(false);*/
										  auto Pnl_Property = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Property"));
										  Pnl_Property->setVisible(false);

										  /*auto right1 = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer"));
										  right1->setVisible(true);*/
										  auto Pnl_Bag = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Bag"));
										  Pnl_Bag->setVisible(true);
	}
		break;
	default:
		break;
	}
}

void UI_Bag_Info_Layer::closePropertyCallback(Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
										  if (UI_Bag_Info_Layer::sIsProperty.asBool())
										  {
											  closeBagCallBack(nullptr, type);
											  return;
										  }
										  /*auto right = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer_1"));
										  right->setVisible(false);*/
										  auto Pnl_Property = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Property"));
										  Pnl_Property->setVisible(false);

										  /*auto right1 = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer"));
										  right1->setVisible(true);*/
										  auto Pnl_Bag = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Bag"));
										  Pnl_Bag->setVisible(true);
	}
		break;
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void UI_Bag_Info_Layer::closeUseCallback(Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
										  /*auto left = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer"));
										  left->setVisible(true);*/
										  auto Pnl_Equip_Bar = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Equip_Bar"));
										  Pnl_Equip_Bar->setVisible(true);

										  /*auto anotherLeft = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_1"));
										  anotherLeft->setVisible(false);*/
										  auto Pnl_Use = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Use"));
										  Pnl_Use->setVisible(false);
	}
		break;
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void UI_Bag_Info_Layer::closeBagCallBack(Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
										  /*CC_SAFE_RETAIN(this);
										  this->removeFromParentAndCleanup(true);*/
										  /*auto left = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer"));
										  left->setVisible(true);*/
										  auto Pnl_Equip_Bar = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Equip_Bar"));
										  Pnl_Equip_Bar->setVisible(true);

										  /*auto anotherLeft = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_1"));
										  anotherLeft->setVisible(false);*/
										  auto Pnl_Use = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Use"));
										  Pnl_Use->setVisible(false);

										  /*auto right1 = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer"));
										  right1->setVisible(true);*/
										  auto Pnl_Bag = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Bag"));
										  Pnl_Bag->setVisible(true);

										  /*auto right = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer_1"));
										  right->setVisible(false);*/
										  auto Pnl_Property = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Property"));
										  Pnl_Property->setVisible(false);

										  /*auto compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_2"));
										  compare->setVisible(false);*/
										  auto Pnl_Compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Compare"));
										  Pnl_Compare->setVisible(false);

										  auto cursor = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, "Image_116_0"));
										  cursor->setPosition(Vec2(116, 458));
										  update();
										  setTypeIndex(INDEX_0);
										  equBtn->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
										  entityBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
										  materialBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
										  setVisible(false);
	}
		break;
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void UI_Bag_Info_Layer::equipmentCallback(Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
										  equBtn->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
										  entityBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
										  materialBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
										  auto cursor = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, "Image_116_0"));
										  cursor->setPosition(Vec2(116, 458));
										  update();
										  setTypeIndex(INDEX_0);

	}
		break;
	default:
		break;
	}
}

void UI_Bag_Info_Layer::entityCallback(Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
										  equBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
										  entityBtn->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
										  materialBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
										  auto cursor = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, "Image_116_0"));
										  cursor->setPosition(Vec2(224, 458));
										  update();
										  setTypeIndex(INDEX_1);
	}
		break;
	default:
		break;
	}

}

void UI_Bag_Info_Layer::materialCallback(Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
										  equBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
										  entityBtn->setBrightStyle(Widget::BrightStyle::NORMAL);
										  materialBtn->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
										  auto cursor = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, "Image_116_0"));
										  cursor->setPosition(Vec2(328, 458));
										  update();
										  setTypeIndex(INDEX_2);
	}
		break;
	default:
		break;
	}
}

void UI_Bag_Info_Layer::cellEquCallback(Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
										  /*auto left = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer"));
										  left->setVisible(false);*/

										  auto left_refine = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Btn_Refine_Left"));
										  left_refine->setVisible(false);

										  auto left_UnWear = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Btn_Unwear"));
										  left_UnWear->setVisible(false);


										  auto left_Sell = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Btn_Sell"));
										  left_Sell->setVisible(true);

										  auto left_Wear = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Btn_Wear"));
										  left_Wear->setVisible(true);

										  auto Pnl_Equip_Bar = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Equip_Bar"));
										  Pnl_Equip_Bar->setVisible(false);

										  /*auto anotherLeft = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_1"));
										  anotherLeft->setVisible(false);*/
										  auto Pnl_Use = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Use"));
										  Pnl_Use->setVisible(false);

										  /*auto compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_2"));
										  compare->setVisible(true);*/
										  auto Pnl_Compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Compare"));
										  Pnl_Compare->setVisible(true);

										  /*auto right = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer"));
										  right->setVisible(false);*/
										  auto Pnl_Bag = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Bag"));
										  Pnl_Bag->setVisible(false);

										  /*auto right1 = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer_1"));
										  right1->setVisible(false);*/
										  auto Pnl_Property = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Property"));
										  Pnl_Property->setVisible(false);

										  int curRole = Account_Data_Mgr::instance()->get_current_role_id();
										  auto imgv = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
										  int idx = imgv->getTag();
										  mCurIndex = idx;
										  //uint64 container_id = m_bag_container_id[idx];
										  //mCurItemId = m_bag_container_id[idx];
										  mCurItemId = m_bag_equip_id[idx];
										  //std::vector<uint64> para;
										  mPara.clear();
										  mPara.push_back(curRole);
										  mPara.push_back(m_bag_container_id[idx]);
										  //ITEM_LOGIC::instance()->equip_equipment(curRole, idx);

	}
		break;
	default:
		break;
	}

}

void UI_Bag_Info_Layer::cellEntityCallback(Ref*pSender, Widget::TouchEventType type)
{

}

void UI_Bag_Info_Layer::cellMaterialCallback(Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
										  auto Pnl_Equip_Bar = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Equip_Bar"));
										  Pnl_Equip_Bar->setVisible(true);

										  auto Pnl_Use = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Use"));
										  Pnl_Use->setVisible(true);
	}
		break;
	default:
		break;
	}
}

void UI_Bag_Info_Layer::cellBarCallback(Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
										  /*auto left = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer"));
										  left->setVisible(false);*/


										  auto left_refine = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Btn_Refine_Left"));
										  left_refine->setVisible(true);

										  auto left_UnWear = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Btn_Unwear"));
										  left_UnWear->setVisible(true);

										  auto left_Sell = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Btn_Sell"));
										  left_Sell->setVisible(false);

										  auto left_Wear = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Btn_Wear"));
										  left_Wear->setVisible(false);


										  auto Pnl_Equip_Bar = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Equip_Bar"));
										  Pnl_Equip_Bar->setVisible(false);

										  /*auto anotherLeft = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_1"));
										  anotherLeft->setVisible(false);*/
										  auto Pnl_Use = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Use"));
										  Pnl_Use->setVisible(false);

										  ////auto compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_2"));
										  ////compare->setVisible(true);
										  /*auto panel_right = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Panel_Right"));
										  panel_right->setVisible(true);*/
										  auto Pnl_Compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Compare"));
										  Pnl_Compare->setVisible(true);
										  ////auto panel_right1 = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Panel_Right_1"));
										  ////panel_right1->setVisible(true);

										  /*auto right = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer"));
										  right->setVisible(false);*/
										  auto Pnl_Bag = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Bag"));
										  Pnl_Bag->setVisible(false);

										  /*auto right1 = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer_1"));
										  right1->setVisible(false);*/
										  auto Pnl_Property = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Property"));
										  Pnl_Property->setVisible(false);

										  int curRole = Account_Data_Mgr::instance()->get_current_role_id();
										  auto imgv = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
										  int idx = imgv->getTag();
										  m_nCurrentEquipTag = idx;										 // 记录玩家身上当前装备的Pos
										  uint64 bar_id = m_bar_ids[idx];

										  mCurIndex = idx;
										  //uint64 bar_id = m_bar_ids[mCurIndex];
										  mCurItemId = m_bar_ids[mCurIndex];

										  //std::vector<uint64> para;
										  mPara.clear();
										  mPara.push_back(curRole);
										  mPara.push_back(mCurItemId);
	}
		break;
	default:
		break;
	}
}

void UI_Bag_Info_Layer::wearCallback(Ref*pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
													   ITEM_LOGIC::instance()->equip_equipment(mPara[0], mPara[1]);
													   /*auto left = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer"));
													   left->setVisible(true);*/
													   auto Pnl_Equip_Bar = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Equip_Bar"));
													   Pnl_Equip_Bar->setVisible(true);

													   /*auto anotherLeft = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_1"));
													   anotherLeft->setVisible(false);*/
													   auto Pnl_Use = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Use"));
													   Pnl_Use->setVisible(false);

													   /*auto compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_2"));
													   compare->setVisible(false);*/
													   auto Pnl_Compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Compare"));
													   Pnl_Compare->setVisible(false);

													   /*auto right = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer_1"));
													   right->setVisible(false);*/
													   auto Pnl_Property = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Property"));
													   Pnl_Property->setVisible(false);

													   /*auto right1 = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer"));
													   right1->setVisible(true);*/
													   auto Pnl_Bag = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Bag"));
													   Pnl_Bag->setVisible(true);

	}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

}

void UI_Bag_Info_Layer::unwearCallback(Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
													   ITEM_LOGIC::instance()->take_off_equipmen(mPara[0], mPara[1]);
													   /*auto left = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer"));
													   left->setVisible(true);*/
													   auto Pnl_Equip_Bar = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Equip_Bar"));
													   Pnl_Equip_Bar->setVisible(true);

													   /*auto anotherLeft = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_1"));
													   anotherLeft->setVisible(false);*/
													   auto Pnl_Use = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Use"));
													   Pnl_Use->setVisible(false);

													   /*auto compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_2"));
													   compare->setVisible(false);*/
													   auto Pnl_Compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Compare"));
													   Pnl_Compare->setVisible(false);

													   /*auto panel_right = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Panel_Right"));
													   panel_right->setVisible(true);
													   auto panel_right1 = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Panel_Right_1"));
													   panel_right1->setVisible(false);*/

													   /*auto right = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer_1"));
													   right->setVisible(false);*/
													   auto Pnl_Property = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Property"));
													   Pnl_Property->setVisible(false);

													   /*auto right1 = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer"));
													   right1->setVisible(true);*/
													   auto Pnl_Bag = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Bag"));
													   Pnl_Bag->setVisible(true);
	}
		break;
	default:
		break;
	}

}

void UI_Bag_Info_Layer::refineCallback(Ref*pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;
	/*auto left = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer"));
	left->setVisible(false);*/
	auto Pnl_Equip_Bar = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Equip_Bar"));
	Pnl_Equip_Bar->setVisible(false);

	/*auto anotherLeft = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_1"));
	anotherLeft->setVisible(false);*/
	auto Pnl_Use = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Use"));
	Pnl_Use->setVisible(false);

	/*auto compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "left_layer_2"));
	compare->setVisible(true);*/
	auto Pnl_Compare = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Compare"));
	Pnl_Compare->setVisible(false);

	/*auto right = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer"));
	right->setVisible(false);*/
	auto Pnl_Bag = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Bag"));
	Pnl_Bag->setVisible(false);

	/*auto right1 = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "right_layer_1"));
	right1->setVisible(false);*/
	auto Pnl_Property = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Property"));
	Pnl_Property->setVisible(false);

	int curRole = Account_Data_Mgr::instance()->get_current_role_id();
	//auto imgv = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
	//int idx = imgv->getTag();
	//uint64 bar_id = m_bar_ids[mCurIndex];

	ChangeLayerState(Layer_State_Strengthen);
	//RequestTargetEquipInfo(mCurItemId, mCurIndex, Layer_State_Strengthen);

}

void UI_Bag_Info_Layer::updateBag()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	Game_Data::Item_Container* container = NULL;
	Game_Data::Item_Container_Map& map_bag_container = player->get_bag_item_container_map();
	Game_Data::Item_Container_Map_Iter iter = map_bag_container.begin();
	for (; iter != map_bag_container.end(); ++iter)
	{
		container = iter->second;
		if (!container)
		{
			continue;
		}

		if (container->item_id > 0)
		{
			m_bag_container_id[container->index] = container->id;
			if (container->is_num_type == 0)
			{
				updateUnfoldable(container);
			}
			else
			{
				updateFoldable(container);
			}

		}
		else
		{
			removeAll(container);
		}

	}

}

void UI_Bag_Info_Layer::updateBar()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(player_id);
	if (!character)
	{
		return;
	}

	Game_Data::Item** equipment_bar = character->get_equipment_array();
	for (int i = 0; i < BAR_NUM; ++i)
	{
		Game_Data::Item* item = NULL;
		item = equipment_bar[i];
		if (item)
		{
			m_bar_ids[i] = item->id;
			updateEquips(i, item->config->type, item->current_quality, item->config->icon, false);
		}
		else
		{
			removeEquips(i, false);
		}

	}

}

void UI_Bag_Info_Layer::update()
{
	memset(m_bag_container_id, 0, sizeof(m_bag_container_id));
	memset(m_bag_equip_id, 0, sizeof(m_bag_equip_id));
	memset(m_bar_ids, 0, sizeof(m_bar_ids));

	updateBag();

	updateBar();

	initData();
	setTypeIndex(INDEX_0);

}

void UI_Bag_Info_Layer::updateFoldable(Game_Data::Item_Container* container)
{
	Game_Data::Item_Config* config = NULL;
	config = ITEM_CONFIG_MGR::instance()->get_item_config((int)container->item_id);
	if (!config)
	{
		CCLOG("no such config");
		return;
	}

	switch (config->type)
	{
	case 1://equip
		//updateEquips(container->index, config->type, config->current_quality, item->config->icon, isBag);
		break;
	case 2://entity
	case 4:
		updateEntities(container->index, config->type, config->icon, true);
	case 3://material
	case 5:
	case 6:
	case 9:
		updateMaterials(container->index, config->type, config->icon, container->item_count, true);
		break;
	default:
		break;
	}

}

void UI_Bag_Info_Layer::updateUnfoldable(Game_Data::Item_Container* container)
{
	//bool isBag = container->type == 1 ? true : false;

	Game_Data::Item* item = NULL;
	item = ITEM_MGR::instance()->get_item(container->item_id);
	if (!item)
	{
		CCLOG("no such item");
		return;
	}

	switch (item->config->type)
	{
	case 1://equip
		updateEquips(container->index, item->config->type, item->current_quality, item->config->icon, true);
		m_bag_equip_id[container->index] = item->id;
		break;
	case 2://entity

		updateEntities(container->index, item->config->type, item->config->icon, true);
		break;
	case 3://material
		updateMaterials(container->index, item->config->type, item->config->icon, container->item_count, true);
		break;
	case 4:
		updateEntities(container->index, item->config->type, item->config->icon, true);
	case 5:
		updateMaterials(container->index, item->config->type, item->config->icon, container->item_count, true);
		break;
	case 6:
		updateMaterials(container->index, item->config->type, item->config->icon, container->item_count, true);
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		updateMaterials(container->index, item->config->type, item->config->icon, container->item_count, true);
		break;
	default:
		break;
	}

}

void UI_Bag_Info_Layer::removeAll(Game_Data::Item_Container* container)
{
	removeEquips(container->index, true);
	removeEntities(container->index, true);
	removeMaterials(container->index, true);

}

/** ==================================== items ==================================== */
void UI_Bag_Info_Layer::updateEquips(int index, int type,/* int count,*/ int quality, int icon, bool isBag)
{
	if (isBag)
	{
		if (index > 23)
		{
			return;
		}
		int row = index / COL_NUM;
		int col = index%COL_NUM;

		ITEM_CONFIG_MGR::instance()->load_icon_config_data();

		const char * szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(icon);
        std::string p("icon/");
        p+=szPath;
		//materials[row][col]->loadTexture(szPath);
		equips[row][col]->loadTexture(p.c_str());
		equips[row][col]->setTouchEnabled(true);
		equips[row][col]->setVisible(true);
	}
	else
	{
		//m_img_equipment_bar[]
		const char *szPath = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(quality);

		szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(icon);
        std::string p("icon/");
        p+=szPath;
		m_img_equipment_bar[index]->loadTexture(p.c_str());
		m_img_equipment_bar[index]->setVisible(true);
        m_img_equipment_bar[index]->setTouchEnabled(true);
	}
}

void UI_Bag_Info_Layer::removeEquips(int index, bool isBag)
{
	if (isBag)
	{

		if (index > 23)
		{
			return;
		}
		int row = index / COL_NUM;
		int col = index%COL_NUM;
		const char *szPath = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(Game_Data::QT_MAX);
		equips[row][col]->setTouchEnabled(false);
		equips[row][col]->setVisible(false);
	}
	else
	{
		const char *szPath = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(Game_Data::QT_MAX);
		m_img_equipment_bar[index]->setVisible(false);
		m_bag_equip_id[index] = 0;

	}

}

void UI_Bag_Info_Layer::updateEntities(int index, int type,/* int count,*/ /*int quality,*/ int icon, bool isBag)
{
	if (isBag)
	{
		if (index > 23)
		{
			return;
		}
		int row = index / COL_NUM;
		int col = index%COL_NUM;

		const char * szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(icon);
        std::string p("icon/");
        p+=szPath;
		//materials[row][col]->loadTexture(szPath);
		entities[row][col]->loadTexture(p.c_str());
		entities[row][col]->setTouchEnabled(true);
		entities[row][col]->setVisible(true);

	}
	else
	{

	}
}

void UI_Bag_Info_Layer::removeEntities(int index, bool isBag)
{
	if (isBag)
	{

		if (index > 23)
		{
			return;
		}
		int row = index / COL_NUM;
		int col = index%COL_NUM;
		const char *szPath = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(Game_Data::QT_MAX);
		entities[row][col]->setTouchEnabled(false);
		entities[row][col]->setVisible(false);
	}
	else
	{
		//const char *szPath = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(Game_Data::QT_MAX);

	}

}

void UI_Bag_Info_Layer::updateMaterials(int index, int type,/* int count,*/ /*int quality,*/ int icon, int count, bool isBag)
{
	if (isBag)
	{
		if (index > 23)
		{
			return;
		}
		int row = index / COL_NUM;
		int col = index%COL_NUM;

		const char * szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(icon);
        std::string p("icon/");
        p+=szPath;
		//materials[row][col]->loadTexture(szPath);
		materials[row][col]->loadTexture(p.c_str());
		cocos2d::Vector<cocos2d::Node*> vec = materials[row][col]->getChildren();
		TextAtlas* tmpA = nullptr;
		if (vec.size()<=0)
		{

			tmpA = TextAtlas::create("0123456789", "vip_number.png", 20, 22, "0");
			materials[row][col]->addChild(tmpA);
		}
		else
		{
			tmpA = (TextAtlas*)vec.at(0);
		}
		Value tmpV(count);
		tmpA->setString(tmpV.asString());
		tmpA->setAnchorPoint(Vec2(0.5, 0.5));
		tmpA->setPosition(Vec2(32, 32));
		
		materials[row][col]->setTouchEnabled(true);
		materials[row][col]->setVisible(true);

	}
	else
	{

	}
}

void UI_Bag_Info_Layer::removeMaterials(int index, bool isBag)
{
	if (isBag)
	{

		if (index > 23)
		{
			return;
		}
		int row = index / COL_NUM;
		int col = index%COL_NUM;
		const char *szPath = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(Game_Data::QT_MAX);
		materials[row][col]->setTouchEnabled(false);
		materials[row][col]->setVisible(false);
	}
	else
	{
		//const char *szPath = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(Game_Data::QT_MAX);

	}

}

void UI_Bag_Info_Layer::setVisible(bool visible)
{
	cocos2d::Layer::setVisible(visible);
	if (visible)
	{
		Joiner_Guidance::hideGuide();
		for (int i = 0; i < ROW_NUM; ++i)
		{
			for (int j = 0; j < COL_NUM; ++j)
			{
				equips[i][j]->setVisible(true);
				entities[i][j]->setVisible(false);
				materials[i][j]->setVisible(false);
			}

		}
		//ShowCharAvatar();
		update();
		setTypeIndex(INDEX_0);

		//showGuide();
	}
	else
	{
		//guideControl();
	}
}

void UI_Bag_Info_Layer::setTypeIndex(int index)
{
	for (int i = 0; i < ROW_NUM; ++i)
	{
		for (int j = 0; j < COL_NUM; ++j)
		{
			if (index == 1)
			{
				if (equips[i][j]->isTouchEnabled())
				{

					equips[i][j]->setVisible(true);
				}
				else
				{

				}

				entities[i][j]->setVisible(false);
				materials[i][j]->setVisible(false);
				//sCurPageIdx = 0;
				//auto curPageStr = sCurPageIdx.asString();
				//curPageNum->setString(curPageStr);
			}
			if (index == 2)
			{
				equips[i][j]->setVisible(false);
				//if (entities[i][j]->isVisible())
				if (entities[i][j]->isTouchEnabled())
				{

					entities[i][j]->setVisible(true);
				}
				else
				{

				}
				materials[i][j]->setVisible(false);
				//sCurPageIdx = 24;
				//auto curPageStr = sCurPageIdx.asString();
				//curPageNum->setString(curPageStr);
			}

			if (index == 4)
			{
				equips[i][j]->setVisible(false);
				entities[i][j]->setVisible(false);
				//if (materials[i][j]->isVisible())
				if (materials[i][j]->isTouchEnabled())
				{

					materials[i][j]->setVisible(true);
				}
				else
				{

				}
				//sCurPageIdx = 48;
				//auto curPageStr = sCurPageIdx.asString();
				//curPageNum->setString(curPageStr);
			}

		}

	}

}

void UI_Bag_Info_Layer::initBagGrid()
{
	for (int i = 0; i < ROW_NUM; ++i)
	{
		for (int j = 0; j < COL_NUM; ++j)
		{
			std::string gridName("Image_117_0_");
			Value tmp1(i*COL_NUM + j);
			std::string gridNameSuff = tmp1.asString();
			gridName += gridNameSuff;
			ImageView* grid = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, gridName.c_str()));
			//equips[i][j] = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, "Img_Template") ); 
			equips[i][j] = ImageView::create();
			equips[i][j]->setAnchorPoint(Vec2(0.5, 0.5));
			equips[i][j]->setPosition(Vec2(32, 32));
			//equips[i][j]->setPosition(pos);
			equips[i][j]->setTouchEnabled(false);
			equips[i][j]->setTag(i*COL_NUM + j);
			equips[i][j]->setVisible(false);
			equips[i][j]->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::cellEquCallback, this));
			grid->addChild(equips[i][j]);

			entities[i][j] = ImageView::create();
			entities[i][j]->setAnchorPoint(Vec2(0.5, 0.5));
			entities[i][j]->setPosition(Vec2(32, 32));
			entities[i][j]->setTouchEnabled(false);
			entities[i][j]->setTag(i*COL_NUM + j);
			entities[i][j]->setVisible(false);
			entities[i][j]->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::cellEntityCallback, this));

			grid->addChild(entities[i][j]);

			materials[i][j] = ImageView::create();
			materials[i][j]->setAnchorPoint(Vec2(0.5, 0.5));
			materials[i][j]->setPosition(Vec2(32, 32));
			materials[i][j]->setTouchEnabled(false);
			materials[i][j]->setTag(i*COL_NUM + j);
			materials[i][j]->setVisible(false);
			materials[i][j]->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::cellMaterialCallback, this));
			grid->addChild(materials[i][j]);

		}

	}

}

void UI_Bag_Info_Layer::initBarGrid()
{
	for (int i = 0; i < BAR_NUM; ++i)
	{
		std::string gridName("Img_Bar_0_");
		Value tmp1(i + 1);
		std::string gridNameSuff = tmp1.asString();
		gridName += gridNameSuff;
		ImageView* grid = dynamic_cast<ImageView*>(Helper::seekWidgetByName(root, gridName.c_str()));

		m_img_equipment_bar[i] = ImageView::create();
		m_img_equipment_bar[i]->setAnchorPoint(Vec2(0.5, 0.5));
		m_img_equipment_bar[i]->setPosition(Vec2(32, 32));
		//equips[i][j]->setPosition(pos);
		m_img_equipment_bar[i]->setTouchEnabled(true);

		m_img_equipment_bar[i]->setTag(i);
		m_img_equipment_bar[i]->setVisible(false);
		m_img_equipment_bar[i]->addTouchEventListener(CC_CALLBACK_2(UI_Bag_Info_Layer::cellBarCallback, this));
		grid->addChild(m_img_equipment_bar[i]);

	}

}
#include <fstream>		
void UI_Bag_Info_Layer::RequestTargetEquipInfo(const uint64 nItemId, const int nEquipPos, const Child_Layer_State eType)
{
	/************************************************************************/
	// 请求目标角色的目标位置装备信息(设置点击精炼按钮的默认打开界面)
	// 1. 获取目标角色的目标位置的ContainerID
	uint64 itemID = nItemId;
	auto mainMenu = (UI_MainMenu_Layer*)this->getParent();

	switch (eType)
	{
	case Layer_State_Gem:
	{
							return;
	}
		break;
	case Layer_State_Strengthen:
	{
								   if (!mainMenu->m_pEquipmentStrenthen)
								   {
									   mainMenu->m_pEquipmentStrenthen = UI_Equipment_Strengthen_Layer::create();
									   mainMenu->m_pEquipmentStrenthen->setItemId(nItemId);
									   this->addChild(mainMenu->m_pEquipmentStrenthen, 100, "Strenthen");
								   }

								   // 2. 关闭背包信息界面
								   mainMenu->m_pEquipmentStrenthen->setItemId(nItemId);
								   mainMenu->m_pEquipmentStrenthen->setVisible(true);
	}
		break;
	case Layer_State_StarUp:
	{
							   if (!mainMenu->m_pEquipmentStarUp)
							   {
								   mainMenu->m_pEquipmentStarUp = UI_Equipment_StarUp_Layer::create();
								   mainMenu->m_pEquipmentStarUp->setItemId(nItemId);
								   this->addChild(mainMenu->m_pEquipmentStarUp, 100, "StarUp");
							   }

							   // 2. 关闭背包信息界面
							   mainMenu->m_pEquipmentStarUp->setItemId(nItemId);
							   mainMenu->m_pEquipmentStarUp->setVisible(true);
	}
		break;
	case Layer_State_Wash:
	{
		auto wash = WashLayer::create();
		addChild(wash);
	}
		break;
	default:
		break;
	}
}

void UI_Bag_Info_Layer::RequestCharacterTargetPosEquipInfo(const int nCharacterID, const int nEquipPos)
{
	/************************************************************************/
	// 请求目标角色的目标位置装备信息(设置点击精炼按钮的默认打开界面)
	// 1. 获取目标角色的目标位置的ContainerID
	uint64 nItemID = 0;
	nItemID = ITEM_LOGIC::instance()->GetTargetPosEquipItemID(nCharacterID, nEquipPos);
	if (nItemID <= 0)
		return;

	// 2. 关闭背包信息界面
	OpenBagInfoLayer(false);

	// 3. 默认打开宝石镶嵌界面,并存储当前的ContainerID
	UI_Bag_Gem_Layer * pGemLayer = UI_Bag_Gem_Layer::create();
	pGemLayer->setTag(998);
	pGemLayer->SetCurrentEquipPos(nEquipPos);
	addChild(pGemLayer);

	UI_Equipment_Gem_Layer * pLayer = UI_Equipment_Gem_Layer::create();
	pLayer->setTag(999);
	pLayer->SetCurrentEquipItemID(nItemID);
	pGemLayer->addChild(pLayer);
}

void UI_Bag_Info_Layer::OpenBagInfoLayer(const bool bValue)
{
	auto left = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Equip_Bar"));
	if (left == NULL)
		return;

	left->setVisible(bValue);

	auto right1 = dynamic_cast<Widget*>(Helper::seekWidgetByName(root, "Pnl_Bag"));
	if (right1 == NULL)
		return;

	right1->setVisible(bValue);
}

void UI_Bag_Info_Layer::RefreshGemLayer()
{
	/************************************************************************/
	// 刷新宝石相关的所有界面
	// 1. 刷新宝石背包界面
	UI_Bag_Gem_Layer * pGemLayer = dynamic_cast<UI_Bag_Gem_Layer*>(this->getChildByTag(998));
	if (pGemLayer == NULL)
		return;

	pGemLayer->RefreshWholeLayer();

	// 2. 刷新玩家装备上的宝石界面
	UI_Equipment_Gem_Layer * pLayer = dynamic_cast<UI_Equipment_Gem_Layer*>(pGemLayer->getChildByTag(999));
	if (pLayer == NULL)
		return;

	pLayer->RefreshEquipGemLayer();
}

void UI_Bag_Info_Layer::ChangeLayerState(const Child_Layer_State eType)
{
	/************************************************************************/
	// 切换页面状态
	switch (eType)
	{
	case Layer_State_Gem:
	{
							int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();
							RequestCharacterTargetPosEquipInfo(nPlayerID, m_nCurrentEquipTag);

	}
		break;
	case Layer_State_Strengthen:
	{
								   RequestTargetEquipInfo(mCurItemId, mCurIndex, Layer_State_Strengthen);
	}
		break;
	case Layer_State_StarUp:
	{
							   RequestTargetEquipInfo(mCurItemId, mCurIndex, Layer_State_StarUp);
	}
		break;
	case Layer_State_Wash:
	{
								RequestTargetEquipInfo(mCurItemId, mCurIndex, Layer_State_Wash);

	}
		break;
	default:
		break;
	}
}
/** ==================================== items ==================================== */