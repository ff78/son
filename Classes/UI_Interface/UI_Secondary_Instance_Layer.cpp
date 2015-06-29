#include "UI_Secondary_Instance_Layer.h"
#include "UI_MainMenu_Layer.h"

#include "Game_Interface/game_content_interface.h"
#include "Play_System/Instance_Data_Mgr.h"
#include "Item_System/Item_Config_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Common/GameDefine.h"
#include "Player_Account/Account_Data_Mgr.h"
//#include "Game/Effect_Cfg_Data_Mgr.h"
#include "Joiner_Guidance.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"

USING_NS_CC;
//USING_NS_CC_EXT;
using namespace ui;
UI_Secondary_Instance_Layer::UI_Secondary_Instance_Layer(void)
{
	memset(m_img_star, 0, sizeof(m_img_star));
	memset(m_btn_mission, 0, sizeof(m_btn_mission));
	m_lab_title_font = NULL;
	m_img_cur_instance = NULL;
	m_img_cur_instance_effect = NULL;
	m_img_cur_material = NULL;
	instance_id = 0;
	juniorGuide = NULL;
}


UI_Secondary_Instance_Layer::~UI_Secondary_Instance_Layer(void)
{
}

bool UI_Secondary_Instance_Layer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	cocos2d::ui::Widget* m_pSecondaryWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Secondary_Interface/Secondary_Interface.ExportJson");
	addChild(m_pSecondaryWidget);

	char key[32] = { 0 };
	char imagename[8 * 1024] = { 0 };
	for (int i = 0; i < INSTANCE_SUM_NUM; ++i)
	{
		memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
		sprintf_s(key, "btn_mission_%d", i + 1);
		sprintf_s(imagename, "img_line_%d", i);
#else
		sprintf(key, "btn_mission_%d", i + 1);
		sprintf(imagename, "img_line_%d", i);
#endif
		line[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pSecondaryWidget, imagename));
		line[i]->setVisible(false);
		m_btn_mission[i] = static_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pSecondaryWidget, key));
		//		m_btn_mission[i]->addPushDownEvent(this,coco_pushselector(UI_Secondary_Instance_Layer::buttonPushDownCallback));
		//	m_btn_mission[i]->addCancelEvent(this,coco_cancelselector(UI_Secondary_Instance_Layer::buttonCancelCallback));
		m_btn_mission[i]->addTouchEventListener(this, toucheventselector(UI_Secondary_Instance_Layer::button_clicked_instance));
		m_btn_mission[i]->setTouchEnabled(false);
		m_btn_mission[i]->setVisible(false);

		for (int j = 0; j < 3; ++j)
		{
			memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
			sprintf_s(key, "img_star_back_%d", j + 1);
#else
			sprintf(key, "img_star_back_%d", j + 1);
#endif
			m_img_star[i][j] = static_cast<cocos2d::ui::ImageView*>(m_btn_mission[i]->getChildByName(key));
			m_img_star[i][j]->setVisible(false);
		}
	}

	//当前任务图标设置
	m_img_cur_instance = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pSecondaryWidget, "img_cur_instance"));
	m_img_cur_instance->setPosition(Vec2(m_btn_mission[0]->getPosition().x, m_btn_mission[0]->getPosition().y + m_btn_mission[0]->getContentSize().height / 2));
	m_img_cur_instance->setVisible(false);
	//当前副本的特效
	m_img_cur_instance_effect = cocos2d::ui::ImageView::create();
	m_img_cur_instance_effect->setPosition(CCPointZero);
	m_img_cur_instance_effect->setVisible(false);
	m_img_cur_instance_effect->setZOrder(m_img_cur_instance->getZOrder() - 1);
	m_img_cur_instance->getParent()->addChild(m_img_cur_instance_effect);
	//当前材料副本
	m_img_cur_material = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pSecondaryWidget, "img_cur_material"));
	m_img_cur_material->setPosition(Vec2(m_btn_mission[0]->getPosition().x, m_btn_mission[0]->getPosition().y + m_btn_mission[0]->getContentSize().height / 2));
	m_img_cur_material->setVisible(false);

	//title font
	m_lab_title_font = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pSecondaryWidget, "lab_title_font"));

	//back font
	cocos2d::ui::Text* lab_back_font = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pSecondaryWidget, "lab_back_font"));
	const char* desc = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_BACK);
	lab_back_font->setString(desc);

	//button back 
	m_pBtnBack = static_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pSecondaryWidget, "btn_back"));
	m_pBtnBack->addTouchEventListener(this, toucheventselector(UI_Secondary_Instance_Layer::buttonBackCallback));

	return true;
}

void UI_Secondary_Instance_Layer::setVisible(bool visible)
{
	if (visible)
	{
		update();
		showGuide();
	}
	else
	{
		INSTANCE_DATA_MGR::instance()->set_current_prompt_instance_id(0, 0, 0);
		m_img_cur_instance->setVisible(false);
		m_img_cur_material->setVisible(false);
		m_img_cur_instance_effect->setVisible(false);
	}

	cocos2d::Layer::setVisible(visible);
}

void UI_Secondary_Instance_Layer::showGuide()
{
	m_pBtnBack->setTouchEnabled(true);

	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if (!player) return;
	if (JUNIOR_GUIDE_STEP_5 == player->get_guide_id())
	{
		m_pBtnBack->setTouchEnabled(false);
		Joiner_Guidance::receiveCurPosWidget(m_btn_mission[0]);
	}
}

void UI_Secondary_Instance_Layer::buttonPushDownCallback(Ref* pSender, Widget::TouchEventType type)
{
	// 	cocos2d::ui::Button* this_btn = dynamic_cast<cocos2d::ui::Button*>(pSender);
	// 	ActionInterval* sacle = CCScaleTo::create(0.2f,1.5f);
	// 	this_btn->runAction(CCSequence::create(sacle,NULL));
}

void UI_Secondary_Instance_Layer::button_clicked_instance(Ref* pSender, Widget::TouchEventType type)
{
	int role_id;
	Game_Data::Player* player;
	cocos2d::ui::Button* this_btn;
	CallFunc* callFunction;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		role_id = Account_Data_Mgr::instance()->get_current_role_id();
		player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
		if (!player)
		{
			return;
		}

		if (5 == player->get_guide_id())
		{
			Joiner_Guidance::hideGuide();
			player->change_guide_id(player->get_guide_id() + 1);
		}

		this_btn = dynamic_cast<cocos2d::ui::Button*>(pSender);
		if (!this_btn)
			return;
		//juniorGuide->setVisible(false);
		instance_id = this_btn->getTag();

		callFunction = CallFunc::create(this,
			callfunc_selector(UI_Secondary_Instance_Layer::openDescUI));
		this_btn->runAction(CCSequence::create(CCScaleTo::create(0.1f, 1.5f),
			CCScaleTo::create(0.1f, 1.0f),
			callFunction,
			NULL));

		break;
	default:
		break;
	}
}

void UI_Secondary_Instance_Layer::openDescUI()
{
	INSTANCE_DATA_MGR::instance()->set_current_instance_id(instance_id);
	UI_MainMenu_Layer::get_instance()->buttonInstanceDes(instance_id);
}

void UI_Secondary_Instance_Layer::buttonBackCallback(Ref* pSender, Widget::TouchEventType type)
{
	int player_id;
	vector<uint64> para;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Joiner_Guidance::hideGuide();
		setVisible(false);
		UI_MainMenu_Layer::get_instance()->buttonAreaInstance();

		player_id = Account_Data_Mgr::instance()->get_current_role_id();

		para.push_back(player_id);
		para.push_back(1000);
		//    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendrequirestage", para);
		Game_Logic::Game_Content_Interface::instance()->exec_interface("sendrequireallstage", para);
		break;
	default:
		break;
	}
}

void UI_Secondary_Instance_Layer::init_instance_date(int area_id)
{
	Area_UI_Config* area_config = INSTANCE_DATA_MGR::instance()->get_area_ui_config(area_id);
	if (area_config)
	{
		INSTANCE_DATA_MGR::instance()->set_current_instance_stage_id(area_id);
		const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(area_config->name_id);
		m_lab_title_font->setString(szString);

		int index = 0;
		Instance_UI_Config* instance_config = NULL;
		list<int>::iterator iter = area_config->list_instance_id.begin();
		for (; iter != area_config->list_instance_id.end(); ++iter)
		{
			instance_config = INSTANCE_DATA_MGR::instance()->get_instance_ui_config(*iter);
			if (instance_config)
			{
				szString = get_instance_icon_by_type(instance_config->type);
				m_btn_mission[index]->loadTextures(szString, szString, szString, UI_TEX_TYPE_PLIST);
				m_btn_mission[index]->setVisible(false);
				line[index]->setVisible(false);
				m_btn_mission[index]->setTouchEnabled(false);
				m_btn_mission[index]->setTag(instance_config->instance_id);

				szString = ITEM_CONFIG_MGR::instance()->get_icon_path(II_STAR_HOLLOW);
				for (int i = 0; i < 3; ++i)
				{
					m_img_star[index][i]->loadTexture(szString, UI_TEX_TYPE_PLIST);
					m_img_star[index][i]->setVisible(true);
				}

				++index;
			}
		}
	}
}

void UI_Secondary_Instance_Layer::update()
{
	int stage_id = INSTANCE_DATA_MGR::instance()->get_current_instance_stage_id();
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Area_UI_Config* auc = INSTANCE_DATA_MGR::instance()->get_area_ui_config(stage_id);
	if (NULL == auc)
		return;

	list<int> stage_lst = auc->list_instance_id;
	list<int>::iterator iti;
	current_instance_data cid;
	int index = 0;
	int instance_id = 0;
	int instance_score = 0;
	bool first_instance = true;

	for (iti = stage_lst.begin(); iti != stage_lst.end(); ++iti)
	{
		cid.reset();
		cid.set_instance_id(*iti);

		if (INSTANCE_DATA_MGR::instance()->get_current_prompt_instance_id() == cid.get_instance_id())
		{
			cocos2d::ui::ImageView* imageview = m_img_cur_instance;
			if (INSTANCE_DATA_MGR::instance()->get_current_prompt_type() == PT_MATERIAL)
			{
				imageview = m_img_cur_material;
			}
			m_img_cur_instance_effect->setPosition(Vec2(m_btn_mission[index]->getPosition().x, m_btn_mission[index]->getPosition().y));
			m_img_cur_instance_effect->setVisible(true);
			m_img_cur_instance_effect->getVirtualRenderer()->stopAllActions();
			//Effect_Cfg_Data_Mgr::instance()->get_effect_without_position((cocos2d::Sprite*)(m_img_cur_instance_effect->getVirtualRenderer()),"3020");
			//imageview->setPosition(Vec2(m_btn_mission[index]->getPosition().x,m_btn_mission[index]->getPosition().y+m_btn_mission[index]->getContentSize().height/2+imageview->getContentSize().height/2));
			//imageview->setVisible(true);
			//imageview->getVirtualRenderer()->stopAllActions();
			//Effect_Cfg_Data_Mgr::instance()->get_effect_without_position((cocos2d::Sprite*)(imageview->getVirtualRenderer()),"3021");

		}

		if ((Account_Data_Mgr::instance()->get_is_show_all_stage() == 0) &&
			(-1 == INSTANCE_DATA_MGR::instance()->get_player_instance_from_list(player_id, cid)))
		{
			if (first_instance)
			{
				first_instance = false;

				m_btn_mission[index]->setVisible(true);
				line[index]->setVisible(true);
				m_btn_mission[index]->setTouchEnabled(true);
			}
			continue;
		}

		m_btn_mission[index]->setVisible(true);
		line[index]->setVisible(true);
		m_btn_mission[index]->setTouchEnabled(true);
		instance_id = cid.get_instance_id();
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

		for (int i = 0; i < visibelStarsNum; ++i)
		{
			const char* szString = ITEM_CONFIG_MGR::instance()->get_icon_path(II_STAR_SOLID);
			m_img_star[index][i]->loadTexture(szString, UI_TEX_TYPE_PLIST);
			m_img_star[index][i]->setVisible(true);
		}

		++index;
		first_instance = false;
	}

	Instance_UI_Config* instance_config = INSTANCE_DATA_MGR::instance()->get_instance_ui_config(instance_id);
	if (instance_config && instance_config->open_id > 0 && index <= 14)
	{
		m_btn_mission[index]->setVisible(true);
		line[index]->setVisible(true);
		m_btn_mission[index]->setTouchEnabled(true);
		if (INSTANCE_DATA_MGR::instance()->get_current_prompt_instance_id() == instance_config->open_id)
		{
			cocos2d::ui::ImageView* imageview = m_img_cur_instance;
			if (INSTANCE_DATA_MGR::instance()->get_current_prompt_type() == PT_MATERIAL)
			{
				imageview = m_img_cur_material;
			}
			m_img_cur_instance_effect->setPosition(Vec2(m_btn_mission[index]->getPosition().x, m_btn_mission[index]->getPosition().y));
			m_img_cur_instance_effect->setVisible(true);
			m_img_cur_instance_effect->getVirtualRenderer()->stopAllActions();
			//Effect_Cfg_Data_Mgr::instance()->get_effect_without_position((cocos2d::Sprite*)(m_img_cur_instance_effect->getVirtualRenderer()),"3020");
			//imageview->setPosition(Vec2(m_btn_mission[index]->getPosition().x,m_btn_mission[index]->getPosition().y+m_btn_mission[index]->getContentSize().height/2+imageview->getContentSize().height/2));
			//imageview->setVisible(true);
			//imageview->getVirtualRenderer()->stopAllActions();
			//Effect_Cfg_Data_Mgr::instance()->get_effect_without_position((cocos2d::Sprite*)(imageview->getVirtualRenderer()),"3021");
		}
	}
}

const char* UI_Secondary_Instance_Layer::get_instance_icon_by_type(int type)
{
	const char* szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(II_NORMAL_ENABLE);
	if (type == IT_ELITE)
	{
		szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(II_ELITE_ENABLE);
	}

	return szPath;
}


void UI_Secondary_Instance_Layer::buttonCancelCallback(Ref* pSender, Widget::TouchEventType type)
{
	cocos2d::ui::Button* this_btn = dynamic_cast<cocos2d::ui::Button*>(pSender);

	ActionInterval* sacle = CCScaleTo::create(0.2f, 1.0f);
	this_btn->runAction(CCSequence::create(sacle, NULL));
}
