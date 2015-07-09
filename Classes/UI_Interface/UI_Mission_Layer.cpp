#include "UI_Mission_Layer.h"
#include "Common/GameMacro.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/Game_Element_Parse.h"
#include "quest_system/quest_data/quest_data_mgr.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Play_System/Instance_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/CommonNpc.h"
#include "Character_System/Player.h"
#include "Item_System/Item_Config_Mgr.h"
//#include "Skill_System/Skill/Technical_Mgr.h"
#include "Play_System/Formula_Function_Instance.h"
//#include "UI/NPC.h"
//#include "UI_Instance_Layer.h"
#include "Common/GameDefine.h"
#include "UI_MainMenu_Layer.h"

#include "UI_Icon_Info_Layer.h"
//#include "Game/Monster_Cfg_Data_Mgr.h"
#include "Game_Interface/game_data_exchange_client.h"

#include "Item_System/Item_Mgr_Cl.h"
#include "Joiner_Guidance.h"

using namespace Game_Data;
using namespace ui;
UI_Mission_Layer* UI_Mission_Layer::instance_ = NULL;
UI_Mission_Layer::UI_Mission_Layer(void)
	:m_pMissionWidget(NULL),
	m_nCurrentPage(0),
	m_pBtnPageUp(NULL),
	m_pBtnPageDown(NULL),
	m_nMissionState(STATE_ALREADY_ACCEPT),
	mission_already_accept(NULL),
	mission_able_accept(NULL),
	daily_mission(NULL)
{
}


UI_Mission_Layer::~UI_Mission_Layer(void)
{
}

bool UI_Mission_Layer::init()
{
	if( !cocos2d::Layer::init() )
	{
		return false;
	}

	m_pMissionWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Mission_UI/Mission_UI.ExportJson");
	m_pMissionWidget->setVisible(true);
	addChild(m_pMissionWidget);

	cocos2d::ui::Button* close_button = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pMissionWidget,"btn_close"));
	close_button->addTouchEventListener(this,toucheventselector(UI_Mission_Layer::buttonCloseCallback));

	//已接任务按钮
	mission_already_accept = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pMissionWidget,"btn_accept"));
	mission_already_accept->addTouchEventListener(this,toucheventselector(UI_Mission_Layer::buttonMissionAlreadyAccept));

	//可接任务按钮
	mission_able_accept = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pMissionWidget,"btn_wait"));
	mission_able_accept->addTouchEventListener(this,toucheventselector(UI_Mission_Layer::buttonMissionAbleAccept));

	//每日任务按钮
	daily_mission = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pMissionWidget,"btn_everyday"));
	daily_mission->addTouchEventListener(this,toucheventselector(UI_Mission_Layer::buttonDailyMission));

	char szUIName[32];
	for (int i = 0; i < MISSION_NUM_PER_PAGE; i++)
	{
		//任务说明
		SPRINTF(szUIName,"lab_mission_intr_%d",i+1);
		m_UI[i].m_plab_mission_introducetext=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));
		const char* tempmissioninroduce=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_INTRODUCE);
		m_UI[i].m_plab_mission_introducetext->setString(tempmissioninroduce);
		//发布npc
		SPRINTF(szUIName,"lab_publish_npc_%d",i+1);
		m_UI[i].m_plab_mission_publish_npctext=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));
		const char* temppublishnpc=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_PUBLISH_NPC);
		m_UI[i].m_plab_mission_publish_npctext->setString(temppublishnpc);
		//完成npc
		SPRINTF(szUIName,"lab_complete_%d",i+1);
		m_UI[i].m_plab_mission_over_npctext=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));
		const char* textnameover=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_OVER_NPC);
		m_UI[i].m_plab_mission_over_npctext->setString(textnameover);
		//任务奖励
		SPRINTF(szUIName,"lab_award_experice_%d",i+1);
		m_UI[i].m_plab_mission_rewordtext=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));
		const char* textreword=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_REWORD);
		m_UI[i].m_plab_mission_rewordtext->setString(textreword);

		//经验
		SPRINTF(szUIName,"lab_jingyan_%d",i+1);
		m_UI[i].m_plab_mission_experiencetext=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));
		const char* textexp=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_EXPERIENCE);
		m_UI[i].m_plab_mission_experiencetext->setString(textexp);
		//金币
		SPRINTF(szUIName,"lab_gold_coin_%d",i+1);
		m_UI[i].m_plab_mission_goldtext=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));
		const char* goldtext=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_GOLD);
		m_UI[i].m_plab_mission_goldtext->setString(goldtext);

		SPRINTF(szUIName,"img_misson_info_%d",i+1);
		m_UI[i].m_pImgBkg = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));

		SPRINTF(szUIName,"tbn_go_%d",i+1);
		m_UI[i].m_pBtnGoNow = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));
		m_UI[i].m_pBtnGoNow->addTouchEventListener(this, toucheventselector(UI_Mission_Layer::buttonGoNowCallback));
	m_UI[i].m_pBtnGoNow->setTag(i);

		SPRINTF(szUIName,"tbn_accept_mission_%d",i+1);
		m_UI[i].m_pBtnAcceptMission = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));
		m_UI[i].m_pBtnAcceptMission->addTouchEventListener(this, toucheventselector(UI_Mission_Layer::btnAcceptMissionCallback));
		m_UI[i].m_pBtnAcceptMission->setTag(i);

		SPRINTF(szUIName,"tea_mission_type_%d",i+1);
		m_UI[i].m_pLabMissionName = dynamic_cast<cocos2d::ui::TextField*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));

		SPRINTF(szUIName,"lab_mission_intr_%d",i+1);
		m_UI[i].m_pLabMissionInfo = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));

		//publish mission NPC name
		SPRINTF(szUIName,"lab_accept_npc_name_%d",i+1);
		m_UI[i].m_pLabPublishNPCName = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));

		//mission complete NPC name
		SPRINTF(szUIName,"lab_finish_npc_name_%d",i+1);
		m_UI[i].m_pLabSubmitNpcName = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));

		//mission experience
		SPRINTF(szUIName,"lab_experise_num_%d",i+1);
		m_UI[i].m_pLabExperience = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));

		//mission award money
		SPRINTF(szUIName,"lab_gold_coin_num_%d",i+1);
		m_UI[i].m_pLabGoldCoin = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));

		//mission award icon picture back
		SPRINTF(szUIName, "img_award_goods_back_%d", i+1);
		m_UI[i].m_pImgAwardIconBack = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));
		m_UI[i].m_pImgAwardIconBack->addTouchEventListener(this, toucheventselector(UI_Mission_Layer::showInfoCallback));
		m_UI[i].m_pImgAwardIconBack->setVisible(false);
		//mission award icon picture
		SPRINTF(szUIName,"img_award_goods_%d",i+1);
		m_UI[i].m_pImgAwardIcon = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));
		//mission award icon num
		SPRINTF(szUIName, "lab_goods_num_%d", i+1);
		m_UI[i].m_pLabAwardIconNum = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));

		//任务名称
		SPRINTF(szUIName,"lab_mission_name_%d",i+1);
		m_UI[i].m_pMissionName = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));

		//任务标识
		SPRINTF(szUIName,"lab_mission_count_%d",i+1);
		m_UI[i].m_pMissionMark = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,szUIName));

	}

	m_pBtnPageUp = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pMissionWidget,"tbn_page_up"));
    m_pBtnPageUp->addTouchEventListener(this,toucheventselector(UI_Mission_Layer::btnCallback_Page));
	m_pBtnPageUp->setTag( Page_Up );
	m_pBtnPageDown = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pMissionWidget,"tbn_page_down"));
	m_pBtnPageDown->addTouchEventListener(this,toucheventselector(UI_Mission_Layer::btnCallback_Page));
m_pBtnPageDown->setTag( Page_Down );

	//title font
	m_pLabTitle = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,"lab_title_font"));
	m_pLabTitle->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_TITLE_ACCEPT));

	cocos2d::ui::Text* label_font = nullptr;
	const char* font_info = nullptr;

	//go to do mission 1 font
	label_font= static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,"lab_go_font_1"));
	font_info = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_GO);
	label_font->setString(font_info);

	//go to do mission 2 font
	label_font= static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,"lab_go_font_2"));
	label_font->setString(font_info);

	//page up font
	label_font= static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,"lab_page_up_font"));
	font_info = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_PAGE_UP);
	label_font->setString(font_info);

	//page down font
	label_font= static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMissionWidget,"lab_page_down_font"));
	font_info = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_PAGE_DOWN);
	label_font->setString(font_info);

	m_nCurrentPage = 0;

	//创建物品信息显示框 function init()
	m_pLayerIconInfo = UI_Icon_Info_Layer::create();
	this->addChild(m_pLayerIconInfo,THISLAYERZORDERE,THISLAYERTAG);
	m_pLayerIconInfo->setVisible(false);

	refreshUI();

	instance_ = this;

	return true;
}

void UI_Mission_Layer::setVisible(bool visible)
{
	cocos2d::Layer::setVisible(visible);

	mission_already_accept->setBrightStyle(BRIGHT_HIGHLIGHT);
    daily_mission->setBrightStyle(BRIGHT_NORMAL);
    mission_able_accept->setBrightStyle(BRIGHT_NORMAL);

	if (visible)
	{
		Joiner_Guidance::hideGuide();
		refreshUI();
		for (int i = 0; i < MISSION_NUM_PER_PAGE; i++)
		{
			//立即前往按钮
			m_UI[i].m_pBtnGoNow->setVisible(true);
			m_UI[i].m_pBtnGoNow->setTouchEnabled(true);
			//接取任务按钮
			m_UI[i].m_pBtnAcceptMission->setVisible(false);
			m_UI[i].m_pBtnAcceptMission->setTouchEnabled(false);
		}
	}
	else
	{
		m_pLayerIconInfo->setVisible(false);
	}
}

void UI_Mission_Layer::buttonCloseCallback( Ref* pSender ,Widget::TouchEventType type)
{
	setVisible(false);
}

void UI_Mission_Layer::buttonMissionAlreadyAccept( Ref* pSender ,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(true);
	for (int i = 0; i < MISSION_NUM_PER_PAGE; i++)
	{
		//立即前往按钮
		m_UI[i].m_pBtnGoNow->setVisible(true);
		m_UI[i].m_pBtnGoNow->setTouchEnabled(true);
		//接取任务按钮
		m_UI[i].m_pBtnAcceptMission->setVisible(false);
		m_UI[i].m_pBtnAcceptMission->setTouchEnabled(false);
	}


	m_pLabTitle->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_TITLE_ACCEPT));
	m_nMissionState = STATE_ALREADY_ACCEPT;
	refreshUI();

	mission_already_accept->setBrightStyle(BRIGHT_HIGHLIGHT);
	daily_mission->setBrightStyle(BRIGHT_NORMAL);
	mission_able_accept->setBrightStyle(BRIGHT_NORMAL);

	break;
    default:
	break;
}
}

void UI_Mission_Layer::buttonMissionAbleAccept( Ref* pSender,Widget::TouchEventType type )
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(true);
	for (int i = 0; i < MISSION_NUM_PER_PAGE; i++)
	{
		//立即前往按钮
		m_UI[i].m_pBtnGoNow->setVisible(false);
		m_UI[i].m_pBtnGoNow->setTouchEnabled(false);
		//接取任务按钮
		m_UI[i].m_pBtnAcceptMission->setVisible(true);
		m_UI[i].m_pBtnAcceptMission->setTouchEnabled(true);
	}
	m_pLabTitle->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_TITLE_ABLE_ACCEPT));
	m_nMissionState = STATE_CAN_ACCEPT;
	refreshUI();
	refreshAcceptableMissionUI();
	
	mission_already_accept->setBrightStyle(BRIGHT_NORMAL);
	daily_mission->setBrightStyle(BRIGHT_NORMAL);
	mission_able_accept->setBrightStyle(BRIGHT_HIGHLIGHT);

	break;
    default:
	break;
}
}

void UI_Mission_Layer::buttonDailyMission( Ref* pSender ,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
// 	daily_mission->setBrightStyle(BRIGHT_HIGHLIGHT);
// 	mission_already_accept->setBrightStyle(BRIGHT_NORMAL);
// 	mission_able_accept->setBrightStyle(BRIGHT_NORMAL);
	setVisible(false);
	UI_MainMenu_Layer::get_instance()->visibleDailyMission();

	break;
    default:
	break;
}
}


void UI_Mission_Layer::buttonGoNowCallback( Ref* pSender,Widget::TouchEventType type )
{
cocos2d::ui::Button* tbn;
int tag;
int player_id;
int index;
Game_Data::Player* player;
quest_data::quest_data_vec_t vecData ;
quest_data refData;
quest_data* qd ;
	vector<uint> para;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(false);
	tbn = (cocos2d::ui::Button*)(pSender);
	tag =tbn->getTag();
	index = m_nCurrentPage*MISSION_NUM_PER_PAGE+tag;

	player_id = Account_Data_Mgr::instance()->get_current_role_id();
	player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (player == NULL)
	{
		return;
	}

	vecData = quest_data_mgr::instance()->get_quest_data_list(player_id);

	if(vecData.size() == 0)
		return;

    if( index + 1 > (int)vecData.size())
        return;

	refData = vecData[index];
	qd = Game_Data::quest_data_mgr::instance()->get_quest_data(player_id,refData.get_quest_id());
	if (!qd)
	{
		return;
	}


	if (qd->get_quest_state() == quest_data::QUEST_STATE_INPROCESS)
	{
		game_quest_content ele_cont;
		qd->get_quest_content(ele_cont);

		Game_Data::game_element_list_t ele_list;
		ele_cont.get_quest_element(ele_list);

		Game_Data::game_element_list_t::iterator itg;
		for( itg = ele_list.begin(); itg != ele_list.end(); ++ itg)
		{
			Game_Element& element = (*itg);
			if (element.get_count() == element.get_count_require())
			{
				continue;
			}

			//Game_Element_Parse::instance()->get_para_from_require_element( "monster", ele_list, para);
			element.get_para_list_in_vector( para);
			if(strcmp(element.get_command(),"monster") == 0 || strcmp(element.get_command(),"item") == 0)
			{
				if( para.size() > 2 )
				{
#if 1
					int instance_id = para[2];
					Instance_UI_Config* config = INSTANCE_DATA_MGR::instance()->get_instance_ui_config(instance_id);
					INSTANCE_DATA_MGR::instance()->set_current_prompt_instance_id(PT_QUEST,instance_id);
				   Game_Utils::instance()->quest_auto_move(1011, Game_Utils::clicked_area, config->area_id);
					
					vector<uint> para;
					para.clear();
					Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute","instance_name","instance_name",para);

					int name_dic_id = -1;
					if( para.size() >=1 )
					{
						name_dic_id = para[0];
					} 
					const char* sz_name_dic = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(name_dic_id);

					UI_MainMenu_Layer::get_instance()->m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
					UI_MainMenu_Layer::get_instance()->m_pLabFindWayFont->setString(sz_name_dic);
					UI_MainMenu_Layer::get_instance()->m_pLabFindWayFont->setVisible(true);
					UI_MainMenu_Layer::get_instance()->m_pImgFontShadow->setVisible(false);
#endif
					break;
				}
			}
			else if (strcmp(element.get_command(),"equip_equipment") == 0)
			{
				if( para.size() > 0 )
				{
					int item_base_id = para[0];
					//UI_MainMenu_Layer::get_instance()->quest_show_bag(item_base_id);
					break;
				}
			}
            else if (strcmp(element.get_command(),"equip_item_all") == 0)
            {
                if( para.size() > 0 )
                {
                    //UI_MainMenu_Layer::get_instance()->quest_show_bag(item_base_id);
                    break;
                }
            }
            else if (strcmp(element.get_command(),"compound_book_fragment") == 0)
            {
                if( para.size() > 0 )
                {
                    //UI_MainMenu_Layer::get_instance()->quest_show_bag(item_base_id);
                    break;
                }
            }
            else if (strcmp(element.get_command(),"compound_material_fragment") == 0)
            {
                if( para.size() > 0 )
                {
                    //UI_MainMenu_Layer::get_instance()->quest_show_bag(item_base_id);
                    break;
                }
            }
            else if (strcmp(element.get_command(),"general_fight") == 0)
            {
                if( para.size() > 0 )
                {
                    //UI_MainMenu_Layer::get_instance()->quest_show_bag(item_base_id);
                    break;
                }
            }
            else if (strcmp(element.get_command(),"open_acupoint") == 0)
            {
                if( para.size() > 0 )
                {
                    //UI_MainMenu_Layer::get_instance()->quest_show_bag(item_base_id);
                    break;
                }
            }
            else if (strcmp(element.get_command(),"player_pk") == 0)
            {
                if( para.size() > 0 )
                {
                    //UI_MainMenu_Layer::get_instance()->quest_show_bag(item_base_id);
                    break;
                }
            }
			else if (strcmp(element.get_command(),"instance") == 0)
			{
				if( para.size() > 0 )
				{
					int instance_id = para[0];
					Instance_UI_Config* config = INSTANCE_DATA_MGR::instance()->get_instance_ui_config(instance_id);
					INSTANCE_DATA_MGR::instance()->set_current_prompt_instance_id(PT_QUEST,instance_id);
					Game_Utils::instance()->quest_auto_move(1011, Game_Utils::clicked_area, config->area_id);
					
					vector<uint> para;
					para.clear();
					Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute","instance_name","instance_name",para);

					int name_dic_id = -1;
					if( para.size() >=1 )
					{
						name_dic_id = para[0];
					} 
					UI_MainMenu_Layer::get_instance()->m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
					const char* sz_name_dic = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(name_dic_id);
					UI_MainMenu_Layer::get_instance()->m_pLabFindWayFont->setString(sz_name_dic);
					UI_MainMenu_Layer::get_instance()->m_pLabFindWayFont->setVisible(true);
					UI_MainMenu_Layer::get_instance()->m_pImgFontShadow->setVisible(false);

					break;
				}
			}
			else if (strcmp(element.get_command(),"up_skill") == 0)
			{
				if( para.size() > 1 )
				{
					int skill_base_id = para[0];
					
					//UI_MainMenu_Layer::get_instance()->quest_show_skill(skill_base_id);
					break;
				}
			}
			else if (strcmp(element.get_command(),"up_equipment_level") == 0)
			{
				if( para.size() > 0 )
				{
					int item_base_id = para[0];
					//UI_MainMenu_Layer::get_instance()->quest_show_equipment(item_base_id);
					break;
				}
			}
			else if (strcmp(element.get_command(),"equip_book") == 0)
			{
				if( para.size() > 0 )
				{
					int item_base_id = para[0];
					//UI_MainMenu_Layer::get_instance()->quest_show_book_bag(item_base_id);
					break;
				}
			}
			else if(strcmp(element.get_command(), "up_equipment_quality") == 0) //装备升品
			{
				if(para.size() > 0)
				{
					int item_base_id = para[0];
					//UI_MainMenu_Layer::get_instance()->quest_show_equipment(item_base_id);
					break;
				}
			}
			else if(strcmp(element.get_command(), "up_book_level") == 0) //心法合成
			{
				if( para.size() > 0 )
				{
					int role_id = Account_Data_Mgr::instance()->get_current_role_id();
					Game_Data::Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
					int nTypeID = player->get_static_character_id();
					int item_base_id = para[0];
					//UI_MainMenu_Layer::get_instance()->visibleHeartMethodCombine(nTypeID);
					break;
				}
			}
			else if (strcmp(element.get_command(),"up_player_quality") == 0) //人物升品   playerqaup(1)  1：升品次数
			{
				if (para.size() > 0)
				{
					UI_MainMenu_Layer::get_instance()->visibleRoleQualityUp();
					
					UI_MainMenu_Layer::get_instance()->m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_ROLE_QUALITY_UP);
					UI_MainMenu_Layer::get_instance()->m_pLabFindWayFont->setString(szFont);
					UI_MainMenu_Layer::get_instance()->m_pLabFindWayFont->setVisible(true);
					UI_MainMenu_Layer::get_instance()->m_pImgFontShadow->setVisible(false);

					break;
				}
			}
			else if(strcmp(element.get_command(), "up_book_quality") == 0) //心法升品    equipbookqaup(0,1,140)
			{
				if (para.size() > 0)
				{
					int role_id = Account_Data_Mgr::instance()->get_current_role_id();
					Game_Data::Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
					UI_MainMenu_Layer::get_instance()->visibleHeartMethodCombine(role_id);
					
					UI_MainMenu_Layer::get_instance()->m_pImgFindWay->loadTexture("guide_.png", UI_TEX_TYPE_LOCAL);
					const char* szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_XINFA_QUALITY_UP);
					UI_MainMenu_Layer::get_instance()->m_pLabFindWayFont->setString(szFont);
					UI_MainMenu_Layer::get_instance()->m_pLabFindWayFont->setVisible(true);
					UI_MainMenu_Layer::get_instance()->m_pImgFontShadow->setVisible(false);

					break;
				}
			}
		}
	}
	else if (qd->get_quest_state() == quest_data::QUEST_STATE_SUBMITABLE)
	{
		game_quest_content ele_cont;
		qd->get_quest_complete(ele_cont);

		Game_Data::game_element_list_t ele_list;
		ele_cont.get_quest_element(ele_list);

		Game_Data::Game_Element_Parse::instance()->get_para_from_require_element( "npctalk", ele_list, para);
		if( para.size() > 0 )
		{
			Game_Data::CommonNpc* npc = Character_Mgr::instance()->get_common_npc_by_static_id(para[0]);
			if(npc)
			{
			#if 1
				City_NPC* retNPC = Game_Utils::instance()->get_npc_by_id((int)para[0]);
				if (retNPC)
				{
					Point pt = retNPC->getPosition();
					Game_Utils::instance()->quest_auto_move((int)para[0], Game_Utils::show_npc_dialog, (int)para[0]);
				}
			#else
				int npcinstanceid = npc->get_database_character_id();
				UI::NPC* retNPC = Game_Utils::instance()->get_npc_by_id(npcinstanceid);
				if(retNPC)
				{
					Point pt = retNPC->getPosition();
					Game_Utils::instance()->quest_auto_move(int(pt.x),int(pt.y),UI::Actor_Layer::show_npc_dialogue,retNPC->sprite_id());
				}
			#endif
			}
		}
	}

	break;
    default:
	break;
}
}

void UI_Mission_Layer::btnAcceptMissionCallback( Ref* pSender,Widget::TouchEventType type )
{
int tag;
int index ;
int player_id;
int missionID;
	vector<uint> para;
	cocos2d::ui::Button* tbn ;
	quest_state_data::qst_st_data_vec_t vecDataCanAccept;
	quest_data* org_qst = NULL;
	quest_state_data::qst_st_data_vec_t qst_apt_data_vec;
	quest_state_data::qst_st_data_vec_t::iterator iter ;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	CCLOG("accept mission button callback");
	setVisible(false);
	tbn = (cocos2d::ui::Button*)(pSender);
	tag = tbn->getTag();
	index = m_nCurrentPage*MISSION_NUM_PER_PAGE+tag;

	player_id = Account_Data_Mgr::instance()->get_current_role_id();

	
	Game_Data::quest_data_mgr::instance()->get_acceptable_quest_list(player_id,vecDataCanAccept);
    if( index + 1 > (int)vecDataCanAccept.size())
        return;
	missionID = vecDataCanAccept[index].get_quest_id();

	//根据任务 id 查看 属于哪个 NPC  获取NPC 模型ID
	//  	int npcID = 0;
	//  	UI_MainMenu_Layer::get_instance()->showNpcDialogue(npcID);

	
	
	Game_Data::quest_data_mgr::instance()->get_acceptable_quest_list(player_id,qst_apt_data_vec);
	iter = qst_apt_data_vec.begin();
	for (;iter != qst_apt_data_vec.end();++iter)
	{
		org_qst = Game_Data::quest_data_mgr::instance()->get_org_quest_data(missionID);
		if (org_qst)
		{
			game_quest_content ele_cont;
			org_qst->get_quest_accept(ele_cont);

			Game_Data::game_element_list_t ele_list;
			ele_cont.get_quest_element(ele_list);

			para.clear();
			Game_Data::Game_Element_Parse::instance()->get_para_from_require_element( "npctalk", ele_list, para);

			if( para.size() > 0 )
			{
				Game_Data::CommonNpc* npc = Character_Mgr::instance()->get_common_npc_by_static_id(para[0]);
				if(npc)
				{
					int npcinstanceid = npc->get_database_character_id();
					UI_MainMenu_Layer::get_instance()->showNpcDialogue(npcinstanceid);
				}
			}

		}
	}

	break;
    default:
	break;
}

}


void UI_Mission_Layer::btnCallback_Page( Ref* pSender ,Widget::TouchEventType type)
{
cocos2d::ui::Button* pBtn ;
int player_id;
	int nMaxPage = 0;
	 quest_data::quest_data_vec_t vecData;
	quest_state_data::qst_st_data_vec_t vecDataCanAccept;
	int nTag;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	pBtn = dynamic_cast<cocos2d::ui::Button*>(pSender);
	CC_ASSERT( pBtn );

	player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if(STATE_ALREADY_ACCEPT == m_nMissionState)
	{
		vecData = quest_data_mgr::instance()->get_quest_data_list(player_id);
		nMaxPage= vecData.size()/MISSION_NUM_PER_PAGE + vecData.size()%MISSION_NUM_PER_PAGE;
	}
	else if(STATE_CAN_ACCEPT == m_nMissionState)
	{
		
		Game_Data::quest_data_mgr::instance()->get_acceptable_quest_list(player_id,vecDataCanAccept);
		nMaxPage= vecDataCanAccept.size()/MISSION_NUM_PER_PAGE + vecDataCanAccept.size()%MISSION_NUM_PER_PAGE;
	}
	else
	{
		//daily mission
	}


	nTag =pBtn->getTag();
	if (Page_Up==nTag)
	{
		if ( m_nCurrentPage>0 && (m_nCurrentPage-1)<nMaxPage )
		{
			m_nCurrentPage--;
			if(STATE_ALREADY_ACCEPT == m_nMissionState)
				refreshUI();
			else if(STATE_CAN_ACCEPT == m_nMissionState)
				refreshAcceptableMissionUI();
			else
			{
				//刷新每日任务界面
			}
		}
	}
	else if (Page_Down==nTag)
	{
		if ( m_nCurrentPage>=0 && (m_nCurrentPage+1)<nMaxPage )
		{
			m_nCurrentPage++;
			if(STATE_ALREADY_ACCEPT == m_nMissionState)
				refreshUI();
			else if(STATE_CAN_ACCEPT == m_nMissionState)
				refreshAcceptableMissionUI();
			else
			{
				//刷新每日任务界面
			}
		}
	}
	else
	{
		CC_ASSERT(false && "nTag");
	}

	break;
    default:
	break;
}
}

void UI_Mission_Layer::refreshUI()
{
	for(int i=0; i<MISSION_NUM_PER_PAGE; ++i)
	{
		m_UI[i].m_pImgBkg->setVisible(false);
	}
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	const quest_data::quest_data_vec_t vecData = quest_data_mgr::instance()->get_quest_data_list(player_id);

	for (int i = 0; i < MISSION_NUM_PER_PAGE; i++)
	{
		int nIndex = m_nCurrentPage*MISSION_NUM_PER_PAGE+i;
		if (nIndex < (int)vecData.size())
		{
			const quest_data refData = vecData[nIndex];
			const char* missionName = GET_STRING(refData.get_quest_name_id());

			char qst_name[1024] ={0};
			char count[256] = {0};
			if( 0 ==  game_data_exchange_client::instance()->get_quest_act_txt(player_id, refData.get_quest_id(), count) )
			{
				sprintf(qst_name, "%s%s", missionName,count );
			} 
			else
			{
				sprintf(qst_name, "%s", missionName );
			}


			const char* missionInfo = GET_STRING(refData.get_quest_info_id());
			m_UI[i].m_pMissionName->setString( qst_name );
			m_UI[i].m_pLabMissionName->setText( missionInfo );
			//m_UI[i].m_pLabMissionInfo->setString( missionInfo );	


			Game_Data::quest_data* qd = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, refData.get_quest_id() );
			if( NULL == qd)
				continue;

			commonUIPart(qd,i);
		}
	}
}
int UI_Mission_Layer::get_instance_name(Game_Data::Game_Element& ele_cont, const char* key_name, char* txt)
{

	vector<uint> para;
	string comp_key = key_name;
	string instance_name = "";

	if(!comp_key.compare(ele_cont.get_command()))
	{
		ele_cont.get_para_list_in_vector( para);
		if( para.size() > 0 )
		{
			int instance_id = para[0];
			vector<uint> para;
			para.clear();
			Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute","instance_name","instance_name",para);
			if(para.size() < 1 )
				return -1;

			instance_name = GET_STRING(para[0]);
			sprintf( txt, "%s  %s   %d / %d ", txt, instance_name.data(), (int)ele_cont.get_count(), (int)ele_cont.get_count_require());
			return 0;
		}
	}


	return 0;
}
int UI_Mission_Layer::get_skill_name(Game_Data::Game_Element& ele_cont, const char* key_name, char* txt)
{
//	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
//
//	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
//	if( NULL == player )
//		return -1;
//
//	int gender = player->get_sex();
//	vector<uint> para;
//
//	para.clear();
//	string comp_key = key_name;
//	string skill_name = "";
//
//	if(!comp_key.compare(ele_cont.get_command()))
//	{
//		ele_cont.get_para_list_in_vector( para);
//		if( para.size() > 1 )
//		{
//			Technical_Data* skill = TECHNICAL_MGR::instance()->GetTechnicalData(para[0]);
//			if(NULL == skill )
//				return -1;
//			skill_name = GET_STRING(skill->name_index);
//			sprintf( txt, "%s  %s   %d / %d ", txt, skill_name.data(), (int)ele_cont.get_count(), (int)para[2]);
//			return 0;
//		}
//	}
	return 0;
}
int UI_Mission_Layer::get_item_name(Game_Data::Game_Element& ele_cont, const char* key_name, char* txt)
{
	vector<uint> para;

	para.clear();
	string comp_key = key_name;
	string item_name = "";

	if(!comp_key.compare(ele_cont.get_command()))
	{
		ele_cont.get_para_list_in_vector( para);
		if( para.size() > 0 )
		{
			Item_Config* item = ITEM_CONFIG_MGR::instance()->get_item_config(para[0]);
			if(NULL == item )
            {
				item_name = "";
                get_counter_name(ele_cont, txt );
                return 0;
            }
            else
			    item_name = GET_STRING(item->name);
			sprintf( txt, "%s  %s   %d / %d ", txt, item_name.data(), (int)ele_cont.get_count(), (int)ele_cont.get_count_require());
			return 0;
		}
	}


	return 0;
}
int UI_Mission_Layer::get_monster_name(Game_Data::Game_Element& ele_cont, const char* key_name, char* txt)
{
	vector<uint> para;

	para.clear();
	string comp_key = key_name;
	string monster_name = "";
	if(!comp_key.compare(ele_cont.get_command()))
	{
		ele_cont.get_para_list_in_vector( para);
		if( para.size() > 0 )
		{
			//monster_config* config = Monster_Cfg_Data_Mgr::instance()->get_monster_config(para[0]);
			//monster_name = GET_STRING(config->monster_name_);
			//sprintf( txt, "%s  %s   %d / %d ", txt, monster_name.data(), (int)ele_cont.get_count(), (int)ele_cont.get_count_require());
			return 0;
		}
	}


	return -1;
}


const char* UI_Mission_Layer::get_npc_name( Game_Data::game_quest_content& ele_cont, const char* key_name )
{
	vector<uint> para;
	Game_Data::game_element_list_t ele_list;
	ele_list.clear();
	ele_cont.get_quest_element(ele_list);
	para.clear();
	Game_Element_Parse::instance()->get_para_from_require_element( key_name, ele_list, para);
	if( para.size() > 0 )
	{

		CommonNpc* npc = Character_Mgr::instance()->get_common_npc_by_static_id(para[0]);
		if( NULL != npc )
		{
			int npcinstanceid = npc->get_database_character_id();
			//UI::NPC * real_npc = Game_Utils::instance()->get_npc_by_id(npcinstanceid);
			//if( NULL != real_npc)
			//	return real_npc->get_name();
		}
	}
	return "";
}
#if 0
UI::NPC* UI_Mission_Layer::getNPCByIndex(int index)
{
	UI::NPC * retNPC=NULL;
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	const quest_data::quest_data_vec_t vecData = quest_data_mgr::instance()->get_quest_data_list(player_id);
	const quest_data& refData = vecData[index];
	Game_Data::quest_data* qd = Game_Data::quest_data_mgr::instance()->get_org_quest_data( refData.get_quest_id());
	if(NULL==qd)
		return NULL;

	Game_Data::game_quest_content ele_cont;
	qd->get_quest_complete(ele_cont);

	Game_Data::game_element_list_t ele_list;
	ele_cont.get_quest_element(ele_list);
	vector<uint> para;
	Game_Element_Parse::instance()->get_para_from_require_element( "npctalk", ele_list, para);
	if( para.size() > 0 )
	{

		CommonNpc* npc = Character_Mgr::instance()->get_common_npc_by_static_id(para[0]);
		if( NULL != npc )
		{
			int npcinstanceid = npc->get_database_character_id();
			retNPC = Game_Utils::instance()->get_npc_by_id(npcinstanceid);
			if( NULL != retNPC)
			{

				return retNPC;

			}
		}
	}
	return NULL;
}
#endif
//可接 但是 没有接受的任务显示
void UI_Mission_Layer::refreshAcceptableMissionUI()
{
	for(int i=0; i<MISSION_NUM_PER_PAGE; ++i)
	{
		m_UI[i].m_pImgBkg->setVisible(false);
		m_UI[i].m_pBtnAcceptMission->setVisible(true);
		m_UI[i].m_pBtnAcceptMission->setTouchEnabled(true);
	}
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	quest_state_data::qst_st_data_vec_t vecDataCanAccept;
	Game_Data::quest_data_mgr::instance()->get_acceptable_quest_list(player_id,vecDataCanAccept);

	quest_state_data::qst_st_data_vec_t::iterator iter = vecDataCanAccept.begin();
	int index = 0;
	for (;iter != vecDataCanAccept.end() && index<MISSION_NUM_PER_PAGE;++iter)
	{
		int nIndex = m_nCurrentPage*MISSION_NUM_PER_PAGE+index;
		if (nIndex < (int)vecDataCanAccept.size())
		{
			Game_Data::quest_data* vecData = Game_Data::quest_data_mgr::instance()->get_org_quest_data(vecDataCanAccept[nIndex].get_quest_id());

			const char* missionName = GET_STRING(vecData->get_quest_name_id());

			char qst_name[1024] ={0};
			char count[256] = {0};
			if( 0 ==  game_data_exchange_client::instance()->get_quest_act_txt(player_id, vecData->get_quest_id(), count) )
			{
				sprintf(qst_name, "%s%s", missionName,count );
			} 
			else
			{
				sprintf(qst_name, "%s", missionName );
			}


			const char* missionInfo = GET_STRING(vecData->get_quest_info_id());
			m_UI[index].m_pMissionName->setString( qst_name );
			m_UI[index].m_pLabMissionName->setText( missionInfo );


			commonUIPart(vecData,index);
			index++;
		}

	}
}

void UI_Mission_Layer::commonUIPart(Game_Data::quest_data* qd,int index)
{
	//set award experience money icon_texture
	Game_Data::game_quest_content ele_cont;

	qd->get_quest_award(ele_cont);
	Game_Data::game_element_list_t ele_list;
	ele_cont.get_quest_element(ele_list);
	vector<uint> para;
	Game_Element_Parse::instance()->get_para_from_require_element( "awardexp", ele_list, para);
	char txt[256];
	if( para.size() > 0)
	{	
		sprintf( txt, "%d", para[0]);
		//exp
		m_UI[index].m_pLabExperience->setString(txt);
	}
	para.clear();

	Game_Element_Parse::instance()->get_para_from_require_element( "awardmoney", ele_list, para);
	if( para.size() > 0)
	{
		sprintf( txt, "%d", para[0]);
		//money
		m_UI[index].m_pLabGoldCoin->setString(txt);
	}

	//奖励图标
	para.clear();
	Game_Element_Parse::instance()->get_para_from_require_element("awarditem", ele_list, para);
	if( para.size() > 1 )
	{
		m_UI[index].m_pImgAwardIconBack->setVisible(true);
		
        Game_Data::Item_Config* item_config = ITEM_CONFIG_MGR::instance()->get_item_config(para[0]);
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

		const char* iconName = ITEM_CONFIG_MGR::instance()->get_icon_path(config->icon);
        std::string p("icon/");
        p+=iconName;
		m_UI[index].m_pImgAwardIcon->loadTexture(p.c_str());
	m_UI[index].m_pImgAwardIconBack->setTag(para[0]);
        m_UI[index].m_pImgAwardIconBack->setVisible(true);
        m_UI[index].m_pImgAwardIconBack->setTouchEnabled(true);
		
		if( para[1] > 1 )
		{
			m_UI[index].m_pLabAwardIconNum->setString(CCString::createWithFormat("%d",para[1])->getCString());
			m_UI[index].m_pLabAwardIconNum->setVisible(true);
		}
		else
		{
			m_UI[index].m_pLabAwardIconNum->setVisible(false);
		}
	}
    else
    {
       m_UI[index].m_pImgAwardIconBack->setTag(0);
        m_UI[index].m_pImgAwardIconBack->setVisible(false);
        m_UI[index].m_pImgAwardIconBack->setTouchEnabled(false);
    }

	//npc名字
	ele_cont.reset();
	qd->get_quest_accept(ele_cont); 
	m_UI[index].m_pLabPublishNPCName->setString(get_npc_name(ele_cont, "npctalk"));

	ele_cont.reset();

	qd->get_quest_complete(ele_cont);
	m_UI[index].m_pLabSubmitNpcName->setString(get_npc_name(ele_cont,"npctalk"));


	//计数器
	ele_cont.reset();
	qd->get_quest_content(ele_cont);

	ele_list.clear();
	ele_cont.get_quest_element(ele_list);

	Game_Data::game_element_list_t::iterator itg;

	char output[512];
	memset(output,0,511);
	for( itg = ele_list.begin(); itg != ele_list.end(); ++ itg)
	{
		memset(txt,0,255);
		/*get_monster_name(*itg, "monster", txt);
		get_item_name( *itg, "item", txt);
		get_item_name( *itg, "equip_equipment", txt);
		get_item_name( *itg, "equip_book", txt);
		get_item_name( *itg, "up_book_level", txt);
		get_item_name( *itg, "up_equipment_level", txt);
        get_item_name( *itg, "up_equipment_quality", txt);
		get_skill_name( *itg, "up_skill", txt); */
		get_instance_name( *itg, "instance", txt);
        get_counter_name(*itg, txt );
		sprintf(output,"%s  %s", output, txt );
	}
	m_UI[index].m_pMissionMark->setString(output);
	m_UI[index].m_pImgBkg->setVisible(true);
}

//bug : (int)ele_cont.get_count() 需要修改这个值（去背包获取数量）
int UI_Mission_Layer::get_counter_name(Game_Data::Game_Element& ele_cont,  char* txt)
{
	vector<uint> para;

	para.clear();
	string comp_key = "";
	string item_name = "";

    int total = 0;
    ele_cont.get_para_list_in_vector( para);
	if( para.size() > 1 )
	{
        total = para[0];
    }

    comp_key = ele_cont.get_command();
    if( !comp_key.compare("player_pk") )
    {
        sprintf(txt, "%s %d / %d", DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90181), (int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("friends") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90180),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("costgold") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90178),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("up_player_quality") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90175),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("up_book_quality") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90172),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("monster") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90328),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("item") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90329),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("equip_equipment") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90330),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("equip_item_all") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90330),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("compound_book_fragment") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90516),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("compound_material_fragment") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90511),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("general_fight") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90330),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("open_acupoint") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90330),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("equip_book") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90331),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("up_book_level") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90332),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("up_equipment_level") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90333),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("up_equipment_quality") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90334),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("up_skill") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90335),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    /*else  if( !comp_key.compare("instance") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90336),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }*/
    else  if( !comp_key.compare("gerneralreqqa") )
    {
        string temp_str = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90176);

        int qa = 0;
        if( para.size() > 0)
            qa = para[0];
        string quality_str = DICTIONARY_CONFIG_MGR::instance()->get_quality_string(qa);

         Game_Element_Parse::instance()->replace_char_to_char_from_string(temp_str, "%s", quality_str.data());
        sprintf(txt, "%s %d / %d",temp_str.data(),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("allequipreqqa") )
    {
        string temp_str = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90171);

        int qa = 0;
        if( para.size() > 0)
            qa = para[0];
        string quality_str = DICTIONARY_CONFIG_MGR::instance()->get_quality_string(qa);

         Game_Element_Parse::instance()->replace_char_to_char_from_string(temp_str, "%s", quality_str.data());

        sprintf(txt, "%s %d / %d",temp_str.data(),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("skillreqlevel") )
    {
        string temp_str = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90174);
        
        int skill_level = 0;
        if(para.size() > 0)
            skill_level = para[0];

       char tmp_txt[256];
       sprintf( tmp_txt, "%d",skill_level);

        Game_Element_Parse::instance()->replace_char_to_char_from_string(temp_str, "%d", tmp_txt);
        
        sprintf(txt, "%s %d / %d",temp_str.data(),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("moneyreq") )
    {
        sprintf(txt, "%s %d / %d",DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90177),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    else  if( !comp_key.compare("equipbookreqqa") )
    {
        string temp_str = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90173);

        int qa = 0;
        if( para.size() > 0)
            qa = para[0];
        string quality_str = DICTIONARY_CONFIG_MGR::instance()->get_quality_string(qa);

         Game_Element_Parse::instance()->replace_char_to_char_from_string(temp_str, "%s", quality_str.data());

        sprintf(txt, "%s %d / %d",temp_str.data(),(int)ele_cont.get_count(), (int)ele_cont.get_count_require());
        return 0;
    }
    //DICTIONARY_CONFIG_MGR::instance()->get_string_by_id();
    return -1;
}
UI_Mission_Layer* UI_Mission_Layer::get_instance()
{
	return instance_;
}

void UI_Mission_Layer::showInfoCallback( Ref* pSender ,Widget::TouchEventType type)
{
cocos2d::ui::ImageView* curImg;
int base_id;
Game_Data::Item_Config* item_config;
    int quality = 0;
    int level = 1;
    Item_Config* config = NULL;

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	curImg = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
	base_id =curImg->getTag();

    item_config = ITEM_CONFIG_MGR::instance()->get_item_config(base_id);
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

    if(config->type == IT_BOOK)
    {
        m_pLayerIconInfo->showButton(config->base_id, config->icon,config->name,level,quality,
            TIPS_STYLE_OK | TIPS_STYLE_BOOK_ATTR | TIPS_STYLE_LEVEL);
    }
    else if (config->type == IT_EQUIPMENT)
    {
        m_pLayerIconInfo->showButton(config->base_id, config->icon,config->name,level,quality,
            TIPS_STYLE_OK | TIPS_STYLE_EQUIPMENT_ATTR | TIPS_STYLE_LEVEL);
    }
    else
    {
        m_pLayerIconInfo->showButton(config->base_id, config->icon,config->name,level,quality,TIPS_STYLE_OK);
    }

	m_pLayerIconInfo->setVisible(true);

	break;
    default:
	break;
}

}
