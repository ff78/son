#include "UI_Instance_Describe_Layer.h"
//#include "Runtime.h"

#include "Game_Interface/game_content_interface.h"
#include "Play_System/Instance_Data_Mgr.h"
#include "Play_System/Instance_Sweep_Data_Mgr.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Game_Interface/game_event_mgr.h"
#include "Play_System/Client_Instance_Msg_Proc.h"
#include "Play_System/Formula_Function_Instance.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Item_System/Item_Config_Mgr.h"
#include "Item_System/Item_Config_Data.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player.h"

#include "UI_Icon_Info_Layer.h"
#include "UI_Interface/UI_ModalDialogue_Layer.h"
#include "Common/GameDefine.h"
#include "Joiner_Guidance.h"
#include "UI_MainMenu_Layer.h"
using namespace ui;
UI_Instance_Describe_Layer::UI_Instance_Describe_Layer(void) :
m_pBtnClose(NULL),
m_pImgViewMap(NULL),
m_pLabNeedPowerNum(NULL),
m_pLabAwardExpNum(NULL),
m_pLabAwardMoneyNum(NULL),
m_pLabSuggestLevel(NULL),
m_pImgOrdinary(NULL),
m_pImgElite(NULL),
m_pTeaPassCondition(NULL),
m_lab_Dungeon_Desc(NULL),
m_btn_sweep_instance(NULL),
ui_instance_elite_(0),
juniorGuide(NULL)
{
	memset(m_pImgAwardGoodsTextureBack, 0, sizeof(m_pImgAwardGoodsTextureBack));
	memset(m_pImgAwardGoodsTexture, 0, sizeof(m_pImgAwardGoodsTexture));
	memset(m_pImgStars, 0, sizeof(m_pImgStars));
	memset(m_pLabMaybeGain, 0, sizeof(m_pLabMaybeGain));
}


UI_Instance_Describe_Layer::~UI_Instance_Describe_Layer(void)
{

}


bool UI_Instance_Describe_Layer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	m_pCocoWidget_instance_ = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Dungeon_Decription/Dungeon_Decription.ExportJson");
	addChild(m_pCocoWidget_instance_);

	//字体显示内容统一设定
	const char* szFont = nullptr;

	m_lab_Dungeon_Desc = dynamic_cast<cocos2d::ui::TextField*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "lab_Dungeon_Desc"));

	//扫荡按钮
	m_btn_sweep_instance = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "btn_sao_dang"));
	m_btn_sweep_instance->addTouchEventListener(this, toucheventselector(UI_Instance_Describe_Layer::buttonSweepCallback));
	m_lab_sweep_instance_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "lab_sao_dang_font"));
	m_lab_sweep_instance_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COPY_SWEEP));

	//进入副本按钮
	btn_enter_instance = static_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "btn_Enter"));
	btn_enter_instance->addTouchEventListener(this, toucheventselector(UI_Instance_Describe_Layer::enterInstanceCallback));

	//进入副本  (字体)
	cocos2d::ui::Text* lab_enter_font = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "lab_enter_font"));
	szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(BUTTON_FONT_ENTER);
	lab_enter_font->setString(szFont);

	//通关条件 （字体)
	cocos2d::ui::Text* lab_pass_font = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "img_Condition_Text"));
	szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_PASS_CONDITION);
	lab_pass_font->setString(szFont);
	lab_pass_font->setVisible(true);

	//通关条件
	m_pTeaPassCondition = dynamic_cast<cocos2d::ui::TextField*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "tea_condition"));
	m_pTeaPassCondition->setVisible(true);


	//需要体力  (字体) (数值)
	cocos2d::ui::Text* lab_need_power_font = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "lab_NeedPower"));
	szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_NEED_POWER);
	lab_need_power_font->setString(szFont);
	m_pLabNeedPowerNum = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "lab_NeedPower_Num"));


	//经验奖励  (字体) (数值)
	cocos2d::ui::Text* lab_award_exp_font = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "lab_ExperienceAward"));
	szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_AWARD_EXP);
	lab_award_exp_font->setString(szFont);
	m_pLabAwardExpNum = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "lab_ExperienceAward_Num"));

	//金钱奖励  (字体) (数值)
	cocos2d::ui::Text* lab_award_money_font = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "lab_MoneyAward"));
	szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_AWARD_MONEY);
	lab_award_money_font->setString(szFont);
	m_pLabAwardMoneyNum = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "lab_MoneyAward_Num"));

	//建议等级  (字体) (数值)
	cocos2d::ui::Text* lab_suggest_level_font = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "lab_SuggestLvl"));
	szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_SUGGEST_LEVEL);
	lab_suggest_level_font->setString(szFont);
	m_pLabSuggestLevel = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "lab_SuggestLvl_Num"));

	//任务难易 显示图标 （普通 or  精英）
	m_pImgOrdinary = static_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "img_ordinary_normal"));
	m_pImgOrdinary->setTouchEnabled(true);
	m_pImgOrdinary->addTouchEventListener(this, toucheventselector(UI_Instance_Describe_Layer::ordinaryBtnCallback));

	m_pImgElite = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "img_elite_normal"));
	m_pImgElite->addTouchEventListener(this, toucheventselector(UI_Instance_Describe_Layer::eliteBtnCallback));
	m_pImgElite->setVisible(false);
	m_pImgElite->setTouchEnabled(false);
	ui_instance_elite_ = 0;

	//关闭按钮
	m_pBtnClose = static_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "btn_Close"));
	m_pBtnClose->addTouchEventListener(this, toucheventselector(UI_Instance_Describe_Layer::closeCallback));

	//初始化 地图贴图
	m_pImgViewMap = static_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "img_map_texture"));

	//初始化 奖励物品的贴图
	char key[32] = { 0 };
	for (int i = 0; i < 3; ++i)
	{
		memset(key, 0, sizeof(key));
		sprintf(key, "img_AwardItem_%d", i + 1);
		m_pImgAwardGoodsTextureBack[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, key));
		m_pImgAwardGoodsTextureBack[i]->setTag(i);
		m_pImgAwardGoodsTextureBack[i]->addTouchEventListener(this, toucheventselector(UI_Instance_Describe_Layer::clickMaterialCallback));
		m_pImgAwardGoodsTextureBack[i]->setVisible(false);
		m_pImgAwardGoodsTextureBack[i]->setTouchEnabled(false);

		memset(key, 0, sizeof(key));
		sprintf(key, "img_award_goods_%d", i + 1);
		m_pImgAwardGoodsTexture[i] = static_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, key));
		m_pImgAwardGoodsTexture[i]->setVisible(false);

		//初始化 星星显示数量 (初始化都显示)
		memset(key, 0, sizeof(key));
		sprintf(key, "img_Star_%d", i + 1);
		m_pImgStars[i] = static_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, key));
		m_pImgStars[i]->setVisible(false);
	}


	//创建物品信息显示框 function init()
	m_pLayerIconInfo = UI_Icon_Info_Layer::create();
	this->addChild(m_pLayerIconInfo, THISLAYERZORDERE, THISLAYERTAG);
	m_pLayerIconInfo->setVisible(false);

	return true;
}


void UI_Instance_Describe_Layer::setVisible(bool visible)
{
	if (visible)
	{
		showGuide();
	}
	else
	{
		ui_instance_elite_ = 0;
		m_pLayerIconInfo->setVisible(false);
	}
	Layer::setVisible(visible);
}

void UI_Instance_Describe_Layer::showGuide()
{
	m_pBtnClose->setTouchEnabled(true);

	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if (!player) return;
	if (JUNIOR_GUIDE_STEP_6 == player->get_guide_id())
	{
		m_pBtnClose->setTouchEnabled(false);
		Joiner_Guidance::receiveCurPosWidget(btn_enter_instance);
	}
}

void UI_Instance_Describe_Layer::buttonSweepCallback(Ref* pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		UI_MainMenu_Layer::get_instance()->visibleSweepDescLayer(ui_instance_elite_);
		setVisible(false);

		break;
	default:
		break;
	}
}

void UI_Instance_Describe_Layer::enterInstanceCallback(Ref* pSender, Widget::TouchEventType type)
{
	int instance_id;
	int role_id;
	Game_Data::Player* player;
	vector<uint> para;
	int instance_id_send;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		//juniorGuide->setVisible(false);
		role_id = Account_Data_Mgr::instance()->get_current_role_id();
		player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));

		if (!player) return;
		if (6 == player->get_guide_id())
		{
			Joiner_Guidance::hideGuide();
			player->change_guide_id(player->get_guide_id() + 1);
		}

		instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
		if (ui_instance_elite_ == current_instance_data::INSTANCE_TYPE_ELITE)
		{
			instance_id = get_elite_instance_id(instance_id);
		}
		//需要体力
		Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute", "condition", "energy", para);
		if (para.size() > 0)
		{
			if (player->get_energy() < (int)para[0])
			{
				DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_ENERGY);
				return;
			}
		}

		//建议等级
		Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute", "condition", "level", para);
		if (para.size() > 0)
		{
			if (player->get_character_level() < (int)para[0])
			{
				DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_ROLE_LEVEL);
				return;
			}
		}

		instance_id_send = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
		if (player->get_bag_empty_count() == 0)
		{
			const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(INTO_INSTANCE_BAG_FULL);
			UI_ModalDialogue_Layer::DoModal("", szString, UI_ModalDialogue_Layer::DT_YES_NO, [=]()
			{
				vector<uint64> param;
				param.push_back(instance_id_send);
				param.push_back(ui_instance_elite_);
				Game_Logic::Game_Content_Interface::instance()->exec_interface("selectinstance", param);
			}
			);
		}
		else
		{
			vector<uint64> param;
			param.push_back(instance_id_send);
			param.push_back(ui_instance_elite_);
			Game_Logic::Game_Content_Interface::instance()->exec_interface("selectinstance", param);
		}
		break;
	default:
		break;
	}

}

void UI_Instance_Describe_Layer::closeCallback(Ref* pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Joiner_Guidance::hideGuide();
		setVisible(false);

		break;
	default:
		break;
	}
}


void UI_Instance_Describe_Layer::initInstanceDescribe(int get_icon_instance_id)
{
	int is_elite_ = INSTANCE_DATA_MGR::instance()->get_current_instance_type();
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
	vector<uint> para;
	//副本名称字典id
	para.clear();
	Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute", "instance_name", "instance_name", para);
	int name_dic_id = -1;
	if (para.size() >= 1)
	{
		name_dic_id = para[0];
	}
	else
	{
		return;
	}

	const char* sz_name_dic = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(name_dic_id);
	cocos2d::ui::Text* lab_dungeon_name = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pCocoWidget_instance_, "lab_Dungeon_Desc_Title"));
	lab_dungeon_name->setString(sz_name_dic);

	//设置通关条件
	para.clear();
	Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute", "condition", "info", para);
	if (para.size() > 0)
	{
		const char* szINSTANCEPASS = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(para[0]);
		m_pTeaPassCondition->setText(szINSTANCEPASS);
	}

	para.clear();
	int elite_instance_id = get_elite_instance_id(instance_id);

	if (elite_instance_id > 0)
	{
		current_instance_data cid;
		cid.set_instance_id(instance_id);
		if (0 == INSTANCE_DATA_MGR::instance()->get_player_instance_from_list(player_id, cid))
		{
			m_pImgElite->setVisible(true);
			m_pImgElite->setTouchEnabled(true);
			if (0 == is_elite_)
			{
				ui_instance_elite_ = 0;
				m_pImgElite->loadTexture("elite_2.png", UI_TEX_TYPE_PLIST);
				m_pImgOrdinary->loadTexture("ordinary_1.png", UI_TEX_TYPE_PLIST);
				show_instance_content(instance_id);
			}
			else
			{
				m_pImgElite->loadTexture("elite_1.png", UI_TEX_TYPE_PLIST);
				m_pImgOrdinary->loadTexture("ordinary_2.png", UI_TEX_TYPE_PLIST);
				ui_instance_elite_ = current_instance_data::INSTANCE_TYPE_ELITE;

				int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
				int elite_instance_id = get_elite_instance_id(instance_id);
				show_instance_content(elite_instance_id);
			}

		}
		else
		{
			m_pImgOrdinary->loadTexture("ordinary_1.png", UI_TEX_TYPE_PLIST);
			m_pImgElite->setVisible(false);
			m_pImgElite->setTouchEnabled(false);

			show_instance_content(instance_id);
		}
	}

	if (-1 == elite_instance_id)
	{
		m_pImgOrdinary->loadTexture("ordinary_1.png", UI_TEX_TYPE_PLIST);
		m_pImgElite->setVisible(false);
		m_pImgElite->setTouchEnabled(false);

		show_instance_content(instance_id);
	}

	check_instance_sweep();
}
int UI_Instance_Describe_Layer::get_elite_instance_id(int instance_id)
{
	vector<uint> para;
	para.clear();
	Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute", "began_content", "elite_instance", para);
	if (para.size() > 0)
	{
		return (int)para[0];
	}

	return -1;
}
int UI_Instance_Describe_Layer::show_instance_content(int instance_id)
{
	vector<uint> para;
	//副本说明字典id
	int instance_info_dic_id = -1;
	para.clear();
	Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute", "info", "info", para);
	if (para.size() >= 1)
	{
		instance_info_dic_id = para[0];
	}

	const char* szDesc = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(instance_info_dic_id);
	m_lab_Dungeon_Desc->setText(szDesc);

	//副本缩略图路径
	string res_path;
	Formula_Function_Instance::instance()->get_string_content_from_instance_data(instance_id, "instance_attribute", "insance_res_name", "insance_res_name", res_path);
	m_pImgViewMap->loadTexture(res_path.c_str());

	//显示玩家上次的星级
	current_instance_data cid;
	cid.reset();
	cid.set_instance_id(instance_id);
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	INSTANCE_DATA_MGR::instance()->get_player_instance_from_list(player_id, cid);
	int instance_score = 0;
	instance_score = cid.get_instance_score();
	int visibelStarsNum = 0;//	分数线的划分85含85以上为三星、45分不含45分以下为1星，其余情况为二星
	if (instance_score >= 85)
	{
		visibelStarsNum = 3;
	}
	else if (instance_score < 85 && instance_score >= 45)
	{
		visibelStarsNum = 2;
	}
	else if (instance_score > 0)
	{
		visibelStarsNum = 1;
	}

	for (int i = 0; i < 3; ++i)
	{
		if (i < visibelStarsNum)
		{
			m_pImgStars[i]->setVisible(true);
		}
		else
		{
			m_pImgStars[i]->setVisible(false);
		}
	}

	//设置 道具奖励 图标
	for (int i = 0; i < 3; ++i)
	{
		m_pImgAwardGoodsTextureBack[i]->setVisible(false);
		m_pImgAwardGoodsTextureBack[i]->setTouchEnabled(false);
		m_pImgAwardGoodsTexture[i]->setVisible(false);
	}

	Game_Data::game_element_list_t ele_lst;
	Formula_Function_Instance::instance()->get_element_list_from_instance_data(instance_id, "instance_attribute", "result_content", "award_item", ele_lst);

	string comp_key = "award_item";
	Game_Data::game_element_list_t::iterator itg;

	int item_count = 0;
	for (itg = ele_lst.begin(); itg != ele_lst.end(); ++itg)
	{
		if (!comp_key.compare((*itg).get_command()))
		{
			para.clear();
			(*itg).get_para_list_in_vector(para);
			if (para.size() > 2)
			{

				show_item_icon(para, item_count);
				++item_count;
			}
		}

	}

	//今日次数
	Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute", "began_content", "energyconsume", para);
	if (para.size() >= 1)
	{
		char txt[256];
		sprintf(txt, "%d", para[0]);
	}

	//需要体力
	Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute", "condition", "energy", para);
	if (para.size() >= 1)
	{
		char txt[256];
		sprintf(txt, "%d", para[0]);
		m_pLabNeedPowerNum->setString(txt);
	}

	//建议等级
	Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute", "condition", "level", para);
	if (para.size() >= 1)
	{
		char txt[256];
		sprintf(txt, "%d", para[0]);
		m_pLabSuggestLevel->setString(txt);
	}

	//经验奖励
	para.clear();
	Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute", "result_content", "award_exp_compute", para);
	if (para.size() >= 1)
	{
		char txt[256];
		sprintf(txt, "%d", para[0]);
		m_pLabAwardExpNum->setString(txt);
	}

	//金钱奖励
	para.clear();
	Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute", "result_content", "award_money", para);
	if (para.size() >= 1)
	{
		char txt[256];
		sprintf(txt, "%d", para[0]);
		m_pLabAwardMoneyNum->setString(txt);
	}

	return 0;
}

int UI_Instance_Describe_Layer::show_item_icon(std::vector<uint>& para, int item_count)
{
	int item_id = 0;
	int item_size = 0;
	if (para.size() >= 2)
	{
		item_id = (int)para[0];
		item_size = (int)para[1];

		CCLOG("item_cout=%d", item_count);

		m_pImgAwardGoodsTextureBack[item_count]->setVisible(true);
		m_pImgAwardGoodsTextureBack[item_count]->setTouchEnabled(true);
		m_pImgAwardGoodsTexture[item_count]->setVisible(true);

		Game_Data::Item_Config* item_config = ITEM_CONFIG_MGR::instance()->get_item_config(item_id);
		Item_Config* config = NULL;
		if (item_config->type == IT_EQUIPMENT_DEPOT)
		{
			Equipment_Depot_Config* equipment_depot_config = reinterpret_cast<Equipment_Depot_Config*>(item_config);
			config = ITEM_CONFIG_MGR::instance()->get_item_config(equipment_depot_config->item_base_id);
		}
		else
		{
			config = item_config;
		}

		const char* szTexture = ITEM_CONFIG_MGR::instance()->get_icon_path(config->icon);
		m_pImgAwardGoodsTexture[item_count]->loadTexture(szTexture, UI_TEX_TYPE_PLIST);
		m_pImgAwardGoodsTextureBack[item_count]->setTag(item_id);
	}

	return 0;
}


void UI_Instance_Describe_Layer::clickMaterialCallback(Ref* pSender, Widget::TouchEventType type)
{
	cocos2d::ui::ImageView* curBtn;
	int item_base_id;
	Game_Data::Item_Config* item_config;
	int quality = 0;
	int level = 1;
	Item_Config* config = NULL;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		curBtn = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
		item_base_id = curBtn->getTag();

		item_config = ITEM_CONFIG_MGR::instance()->get_item_config(item_base_id);
		if (item_config->type == IT_EQUIPMENT_DEPOT)
		{
			Equipment_Depot_Config* equipment_depot_config = reinterpret_cast<Equipment_Depot_Config*>(item_config);
			config = ITEM_CONFIG_MGR::instance()->get_item_config(equipment_depot_config->item_base_id);
			quality = equipment_depot_config->quality;
			level = equipment_depot_config->level;
		}
		else
		{
			config = item_config;
			quality = config->quality;
		}

		if (config->type == IT_BOOK)
		{
			m_pLayerIconInfo->showButton(config->base_id, config->icon, config->name, level, quality,
				TIPS_STYLE_OK | TIPS_STYLE_BOOK_ATTR | TIPS_STYLE_LEVEL);
		}
		else if (config->type == IT_EQUIPMENT)
		{
			m_pLayerIconInfo->showButton(config->base_id, config->icon, config->name, level, quality,
				TIPS_STYLE_OK | TIPS_STYLE_EQUIPMENT_ATTR | TIPS_STYLE_LEVEL);
		}
		else
		{
			m_pLayerIconInfo->showButton(config->base_id, config->icon, config->name, level, quality, TIPS_STYLE_OK);
		}

		m_pLayerIconInfo->setVisible(true);

		break;
	default:
		break;
	}

}

void UI_Instance_Describe_Layer::ordinaryBtnCallback(Ref* pSender, Widget::TouchEventType type)
{
	int instance_id;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		ui_instance_elite_ = 0;
		m_pImgElite->loadTexture("elite_2.png", UI_TEX_TYPE_PLIST);
		m_pImgOrdinary->loadTexture("ordinary_1.png", UI_TEX_TYPE_PLIST);
		instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
		show_instance_content(instance_id);
		check_instance_sweep();

		break;
	default:
		break;
	}
}

void UI_Instance_Describe_Layer::eliteBtnCallback(Ref* pSender, Widget::TouchEventType type)
{
	int instance_id;
	int elite_instance_id;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		m_pImgElite->loadTexture("elite_1.png", UI_TEX_TYPE_PLIST);
		m_pImgOrdinary->loadTexture("ordinary_2.png", UI_TEX_TYPE_PLIST);
		ui_instance_elite_ = current_instance_data::INSTANCE_TYPE_ELITE;

		instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
		elite_instance_id = get_elite_instance_id(instance_id);
		show_instance_content(elite_instance_id);
		check_instance_sweep();
		break;
	default:
		break;
	}

}

void UI_Instance_Describe_Layer::showStarNum()
{

}


void UI_Instance_Describe_Layer::check_instance_sweep()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
	if (current_instance_data::INSTANCE_TYPE_ELITE == ui_instance_elite_)
	{
		instance_id = Formula_Function_Instance::instance()->get_elite_instance_id(instance_id);
	}

	current_instance_data cid;
	cid.reset();
	cid.set_instance_id(instance_id);
	if (-1 == INSTANCE_DATA_MGR::instance()->get_player_instance_from_list(player_id, cid))
	{
		m_btn_sweep_instance->setBright(false);
		m_btn_sweep_instance->setTouchEnabled(false);
	}
	else
	{
		m_btn_sweep_instance->setBright(true);
		m_btn_sweep_instance->setTouchEnabled(true);
	}
}
