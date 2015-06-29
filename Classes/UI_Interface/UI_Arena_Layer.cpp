#include "UI_Arena_Layer.h"
#include "UI_ModalDialogue_Layer.h"
#include "UI_MainMenu_Layer.h"

//#include "Fight_System/Fight_Config_Mgr.h"
//#include "Fight_System/Offline_Fight_Mgr_Cl.h"
//#include "Fight_System/Offline_Fight_Record_Mgr_Cl.h"
//#include "Fight_System/Offline_Fight_Logic_Cl.h"
//#include "Game_Interface/game_content_interface.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player_Config_Mgr.h"
#include "Character_System/Player_Logic_Cl.h"

#include "Item_System/Item_Desc_Config_Mgr.h"

#include "Game_Interface/game_event_mgr.h"
#include "Game_Interface/Game_Element_Parse.h"
#include "Game_Interface/game_content_interface.h"
#include "Function_Open_System/Function_Open_Config_Data.h"

#include "Joiner_Guidance.h"

using namespace Game_Data;
using namespace ui;
UI_Arena_Layer*	UI_Arena_Layer::m_pInstance = NULL;
UI_Arena_Layer::UI_Arena_Layer(void):
	m_pRootWidget(NULL),
	m_pBtnCloseCurLayer(NULL),
	m_pLabMyName(NULL),
	m_pImgMyHeadPhoto(NULL),
    m_pImgMyHeadPhotoBack(NULL),
	m_pLabMyLevel(NULL),
	m_pLabMyRankNum(NULL),
	m_pLabMyReputationNum(NULL),
	m_pLabCountdown(NULL),
	m_pLabGetOrNotFont(NULL),
	m_pBtnGetOrNot(NULL),
	m_pLabTodayChallengeInfoFont(NULL),
	m_pLabRankAwardFont(NULL),
	m_pLabAwardIcon(NULL),
	m_pImgAwardInfoBack(NULL),
	m_pLabLevelInfo(NULL),
	m_pLabFirstAwardInfo(NULL),
	m_pLabSecondAwardInfo(NULL)
{
	memset(m_pImgPlayerFatherNodeBack, 0, sizeof(m_pImgPlayerFatherNodeBack));
	memset(m_pImgOffLinePlayerHeadPhotoBack, 0 , sizeof(m_pImgOffLinePlayerHeadPhotoBack));
	memset(m_pImgOffLinePlayerHeadPhoto, 0 , sizeof(m_pImgOffLinePlayerHeadPhoto));
	memset(m_pLabOffLinePlayerRankNun, 0 , sizeof(m_pLabOffLinePlayerRankNun));
	memset(m_pLabOffLinePlayerName, 0 , sizeof(m_pLabOffLinePlayerName));
	memset(m_pLabOffLinePlayerLevel, 0 , sizeof(m_pLabOffLinePlayerLevel));
	memset(m_pLabRecord, 0, sizeof(m_pLabRecord));
	memset(m_pImgAttackMark, 0, sizeof(m_pImgAttackMark));
	memset(m_pImgDefenceMark, 0, sizeof(m_pImgDefenceMark));
	memset(m_pLabAwardContext, 0, sizeof(m_pLabAwardContext));
}


UI_Arena_Layer::~UI_Arena_Layer(void)
{
    
}


bool UI_Arena_Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());

		m_pRootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Competition/Competition.ExportJson");
		this->addChild(m_pRootWidget);

		m_pBtnCloseCurLayer = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pRootWidget,"btn_close"));
		m_pBtnCloseCurLayer->addTouchEventListener(this,toucheventselector(UI_Arena_Layer::buttonCloseCallback));

		initNotChangePart();
		initChangePart();

		reset_ui();
		update();

		bRet = true;
	} while (0);

	m_pInstance = this;
	return bRet;

}

void UI_Arena_Layer::reset_ui()
{
	for(int i=0; i<OFFLINEPLAYERNUM; ++i)
	{
		m_pImgPlayerFatherNodeBack[i]->setVisible(false);
		m_pImgAttackMark[i]->setVisible(false);
		m_pImgDefenceMark[i]->setVisible(false);
		m_pLabRecord[i]->setVisible(false);
	}
}


void UI_Arena_Layer::buttonIncreaceCallback(Ref* pSender,Widget::TouchEventType type)
{
int role_id;
Player* player;
const char* szString;
const char* purchaseInfo;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    role_id = Account_Data_Mgr::instance()->get_current_role_id();
    player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
    if (!player)
    {
        return;
    }

	szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MODEL_PURCHASE_CHALLENGE_FONT);
	purchaseInfo = CCString::createWithFormat(szString,player->get_buy_offline_fight_count_cost())->getCString();
	UI_ModalDialogue_Layer::DoModal("",purchaseInfo,UI_ModalDialogue_Layer::DT_YES_NO,[]()
	{
		//OFFLINE_FIGHT_LOGIC::instance()->player_buy_offline_fight_count();
	}
	);

	break;
    default:
	break;
}
}

void UI_Arena_Layer::initNotChangePart()
{
	const char* szFont = NULL; 

	m_pLabAwardIcon = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pRootWidget,"img_award_icon"));
	m_pLabAwardIcon->addTouchEventListener(this, toucheventselector(UI_Arena_Layer::seeGainRewardInfo));
	//排名
	cocos2d::ui::Text* labMyRankFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_my_rank_font"));
	szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_CURRENT_RANKING);
	labMyRankFont->setString(szFont);
	//声望
	cocos2d::ui::Text* labMyReputationFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_my_reputation_font"));
	szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_CUR_REPUTATION);
	labMyReputationFont->setString(szFont);
	//昨日排名
	labYesterdayRankFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_latest_rank_font"));
	szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_YESTERDAY_RANKING);
	labYesterdayRankFont->setString(szFont);
	//排名奖励：
	cocos2d::ui::Text* labRankAwardInfoFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_rank_award_right"));
	szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_RANKING_AWARD);
	labRankAwardInfoFont->setString(szFont);
	//排名奖励（左侧）
	m_pLabRankAwardFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_rank_award_font"));
	szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_AWARD_COUNTDOWN);
	m_pLabRankAwardFont->setString(szFont);
	m_pLabRankAwardFont->setVisible(false);

	//金币
	cocos2d::ui::Text* labGoldCoinFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_gold_coin_font"));
// 	szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MISSION_GOLD);
// 	labGoldCoinFont->setString(szFont);

	//增加
	cocos2d::ui::Text* labIncreaceFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_increase_font"));
	szFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_INCREACE);
	labIncreaceFont->setString(szFont);

	cocos2d::ui::Button* btnIncreace = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pRootWidget,"btn_increase"));
	btnIncreace->addTouchEventListener(this, toucheventselector(UI_Arena_Layer::buttonIncreaceCallback));

	char szName[64] = {0};
	for (int i=0; i<OFFLINERESULTITEM; ++i)
	{
		memset(szName, 0, sizeof(szName));
		sprintf(szName, "img_result_mark_%d", i);
		m_pImgAttackMark[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pRootWidget,szName));
		m_pImgAttackMark[i]->setVisible(false);

		memset(szName, 0, sizeof(szName));
		sprintf(szName, "img_defence_mark_%d", i);
		m_pImgDefenceMark[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pRootWidget,szName));
		m_pImgDefenceMark[i]->setVisible(false);

		memset(szName, 0, sizeof(szName));
		sprintf(szName, "lab_finght_result_font_%d", i);
		m_pLabRecord[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,szName));
	}
};

void UI_Arena_Layer::initChangePart()
{
	m_pLabMyName = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_my_name_font"));

	m_pImgMyHeadPhoto = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pRootWidget,"img_my_head_texture"));
    m_pImgMyHeadPhotoBack = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pRootWidget,"img_my_head_photo_back"));

	m_pLabMyLevel = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_my_level_font"));

	m_pLabMyRankNum = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_my_rank_num"));

	m_pLabMyReputationNum = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_my_reputation_num"));

	m_pLabCountdown = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_countdown"));
	m_pLabCountdown->setString("00:00:00");
	m_pLabCountdown->setVisible(false);

	m_pLabGetOrNotFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_get_or_not_font"));
	m_pLabGetOrNotFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_RECEIVE));

	m_pBtnGetOrNot = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pRootWidget,"btn_get_or_not"));
	m_pBtnGetOrNot->addTouchEventListener(this, toucheventselector(UI_Arena_Layer::buttonGetOrNot));

	m_pLabLatestRankNum = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_latest_rank_num"));

	char key[32] = {0};
	for (int i=0; i<OFFLINEPLAYERNUM; ++i)
	{
		memset(key, 0, sizeof(key));
		sprintf(key,"img_player_back_%d", i);
		m_pImgPlayerFatherNodeBack[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pRootWidget,key));

		memset(key, 0, sizeof(key));
		sprintf(key, "img_player_head_back_%d", i);
		m_pImgOffLinePlayerHeadPhotoBack[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pRootWidget,key));

		memset(key, 0, sizeof(key));
		sprintf(key, "img_head_texture_%d", i);
		m_pImgOffLinePlayerHeadPhoto[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pRootWidget,key));
		m_pImgOffLinePlayerHeadPhoto[i]->setTouchEnabled(true);
		m_pImgOffLinePlayerHeadPhoto[i]->addTouchEventListener(this,toucheventselector(UI_Arena_Layer::fightStart));
m_pImgOffLinePlayerHeadPhoto[i]->setTag(0);

		memset(key, 0, sizeof(key));
		sprintf(key, "lab_rank_num_%d", i);
		m_pLabOffLinePlayerRankNun[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,key));
		m_pLabOffLinePlayerRankNun[i]->setString("8");

		memset(key, 0, sizeof(key));
		sprintf(key, "lab_player_name_%d", i);
		m_pLabOffLinePlayerName[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,key));
		m_pLabOffLinePlayerName[i]->setString("9");

		memset(key, 0, sizeof(key));
		sprintf(key, "lab_cur_player_level_%d", i);
		m_pLabOffLinePlayerLevel[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,key));
		m_pLabOffLinePlayerLevel[i]->setString("10");

	}

	m_pLabTodayChallengeInfoFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_today_challenge_font_num"));//%s

	m_pImgAwardInfoBack = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pRootWidget,"img_award_goods_info_back"));
	m_pImgAwardInfoBack->setVisible(false);
	m_pLabLevelInfo = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_dang_info"));
	m_pLabFirstAwardInfo = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_award_first_goods"));
	m_pLabSecondAwardInfo = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_award_second_goods"));

};

void UI_Arena_Layer::setVisible(bool visible)
{
	cocos2d::Layer::setVisible(visible);
	if (visible)
	{
		Joiner_Guidance::hideGuide();
//		OFFLINE_FIGHT_LOGIC::instance()->load_offline_fight();
		showGuide();
	} 
	else
	{
//		UI_MainMenu_Layer::get_instance()->showGuide();

		Joiner_Guidance::hideGuide();
	}
}

void UI_Arena_Layer::buttonCloseCallback(Ref* pSender,Widget::TouchEventType type )
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(false);

	break;
    default:
	break;
}
}

void UI_Arena_Layer::update()
{   
#if 0
	reset_ui();
	
	buttonOpenOrNot();

	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character( role_id ));
	if (!player)
	{
        return;
	}

	//setPlayerName
	m_pLabMyName->setString(player->get_character_name());
	//setPlayerPhoto
	const char* picRoleHead = ITEM_CONFIG_MGR::instance()->get_icon_path(player->get_face_mode_id());
	m_pImgMyHeadPhoto->loadTexture(picRoleHead, UI_TEX_TYPE_PLIST);
    const char* quality_back = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(player->get_character_quality());
    m_pImgMyHeadPhotoBack->loadTexture(quality_back, UI_TEX_TYPE_PLIST);
	//setPlayerLevel
	m_pLabMyLevel->setString(CCString::createWithFormat("LV.%d",player->get_character_level())->getCString());
	m_pLabMyReputationNum->setString(CCString::createWithFormat("%d",player->get_prestige())->getCString());
	//setPlayerRanking
	int cur_rank = OFFLINE_FIGHT_MGR::instance()->get_self_cur_rank();
	m_pLabMyRankNum->setString(CCString::createWithFormat("%d",cur_rank)->getCString());

	int yesterdayRank = OFFLINE_FIGHT_MGR::instance()->get_self_last_rank();
	m_pLabLatestRankNum->setString(CCString::createWithFormat("%d",yesterdayRank)->getCString());

	const char* format = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_TODAY_CHALLENGE_TIMES);
	m_pLabTodayChallengeInfoFont->setString(CCString::createWithFormat(format,player->get_offline_fight_count())->getCString());

	if (player->get_offline_fight_rank_reward_count() > 0)
	{
		m_pLabGetOrNotFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_RECEIVE));
		m_pBtnGetOrNot->setVisible(true);
		m_pBtnGetOrNot->setTouchEnabled(true);

		m_pLabRankAwardFont->setVisible(false);
        m_pLabCountdown->setVisible(false);
	}
	else
	{
		m_pLabGetOrNotFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_ALREADY_RECEIVE));
		m_pBtnGetOrNot->setVisible(false);
		m_pBtnGetOrNot->setTouchEnabled(false);

		labYesterdayRankFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_TODAY_RANKING));

		m_pLabRankAwardFont->setVisible(true);
        m_pLabCountdown->setVisible(true);
	}

	Game_Data::Offline_Fight* offline_fight_array = OFFLINE_FIGHT_MGR::instance()->get_offline_fight_array();
	for (int i = 0;i < OFFLINEPLAYERNUM; ++i)
	{
		Game_Data::Offline_Fight& fight = offline_fight_array[i];
		if (fight.role_id_ == 0)
		{
			break;
		}

		m_pLabOffLinePlayerName[i]->setString(fight.name_);
		m_pLabOffLinePlayerLevel[i]->setString(CCString::createWithFormat("LV.%d",fight.level_)->getCString());
		m_pLabOffLinePlayerRankNun[i]->setString(CCString::createWithFormat("NO.%d",fight.cur_rank_)->getCString());

		Player_Base_Attr_Config_Data* roleData = PLAYER_MGR::instance()->get_player_base_attr(fight.role_base_id_);
		if (roleData)
		{
			picRoleHead = ITEM_CONFIG_MGR::instance()->get_icon_path(roleData->get_player_face_mode_id());
			m_pImgOffLinePlayerHeadPhoto[i]->loadTexture(picRoleHead, UI_TEX_TYPE_PLIST);
		}

        quality_back = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(fight.quality_);
        m_pImgOffLinePlayerHeadPhotoBack[i]->loadTexture(quality_back, UI_TEX_TYPE_PLIST);

m_pImgOffLinePlayerHeadPhoto[i]->setTag(fight.role_id_);
		m_pImgPlayerFatherNodeBack[i]->setVisible(true);
	}

	Game_Data::Offline_Fight_Record* offline_fight_record_array = OFFLINE_FIGHT_RECORD_MGR::instance()->get_offline_fight_record_array();
	for (int i = 0;i < OFFLINEPLAYERNUM; ++i)
	{
		Game_Data::Offline_Fight_Record& record = offline_fight_record_array[i];
		if (record.record_id_ == 0)
		{
			break;
		}

		if (record.challenger_id_ == role_id)
		{
			const char* record_text = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_CHALLENGE_WIN_FALL);
			if (record.challenger_win_ == 1)
			{
				record_text = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_CHALLENGE_WIN_RAISE);
			} 

			m_pLabRecord[i]->setString(CCString::createWithFormat(record_text,record.target_name_,record.challenger_rank_)->getCString());
			m_pImgAttackMark[i]->setVisible(true);
		} 
		else
		{
			const char* record_text = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_BE_CHALLENGED_WIN_RAISE);
			if (record.challenger_win_ == 1)
			{
				record_text = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_BE_CHALLENGED_WIN_FALL);
			}

			m_pLabRecord[i]->setString(CCString::createWithFormat(record_text,record.challenger_name_,record.target_rank_)->getCString());
			m_pImgDefenceMark[i]->setVisible(true);
		}
		
		m_pLabRecord[i]->setVisible(true);
	}
#endif
}

void UI_Arena_Layer::update_time(int time)
{
    int hour = time/3600;
    int minute = time%3600/60;
    int second = time%3600%60;

    const char* str_hour = "";
    if (hour >= 0 && hour < 10)
    {
        str_hour = CCString::createWithFormat("0%d",hour)->getCString();
    }
    else
    {
        str_hour = CCString::createWithFormat("%d",hour)->getCString();
    }

    const char* str_minute = "";
    if (minute >= 0 && minute < 10)
    {
        str_minute = CCString::createWithFormat("0%d",minute)->getCString();
    }
    else
    {
        str_minute = CCString::createWithFormat("%d",minute)->getCString();
    }

    const char* str_second = "";
    if (second >= 0 && second < 10)
    {
        str_second = CCString::createWithFormat("0%d",second)->getCString();
    }
    else
    {
        str_second = CCString::createWithFormat("%d",second)->getCString();
    }

    const char* text_time = CCString::createWithFormat("%s:%s:%s",str_hour,str_minute,str_second)->getCString();
    m_pLabCountdown->setString(text_time);
}

void UI_Arena_Layer::fightStart(Ref* pSender,Widget::TouchEventType type)
{
int player_id;
Game_Data::Player* player;
cocos2d::ui::ImageView* imageView;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	player_id = Account_Data_Mgr::instance()->get_current_role_id();
	player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	imageView = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
	if (imageView)
	{
//		OFFLINE_FIGHT_LOGIC::instance()->offline_fight_start(imageView->getTag());
		player->change_guide_id(player->get_guide_id()+1);
	}
	break;
    default:
	break;
}

}

void UI_Arena_Layer::buttonGetOrNot( Ref* pSender ,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
#if 0
	if (OFFLINE_FIGHT_LOGIC::instance()->get_offline_fight_rank_reward())
	{
		m_pBtnGetOrNot->setVisible(false);
		m_pBtnGetOrNot->setTouchEnabled(false);
        m_pLabCountdown->setVisible(true);

		labYesterdayRankFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_TODAY_RANKING));
	}
#endif
	break;
    default:
	break;
}
}

void UI_Arena_Layer::buttonOpenOrNot()
{
//	m_pBtnGetOrNot->setVisible(UI_MainMenu_Layer::get_instance()->arr[Game_Data::ICON_ARENA_GET_BTN]);
//	m_pBtnGetOrNot->setTouchEnabled(UI_MainMenu_Layer::get_instance()->arr[Game_Data::ICON_ARENA_GET_BTN]);
}

void UI_Arena_Layer::seeGainRewardInfo( Ref* pSender ,Widget::TouchEventType type)
{
// 	m_pLabLevelInfo->setString("");
// 	m_pLabFirstAwardInfo->setString("");
// 	m_pLabSecondAwardInfo->setString("");
// 
// 	m_pImgAwardInfoBack->setVisible(true);
// 	m_pImgAwardInfoBack->runAction(
// 		CCSequence::create(CCFadeOut::create(5.0f),NULL)
// 		);

}

// void UI_Arena_Layer::showContext(Game_Data::game_element_list_t ele_list)
// {
// 	unsigned int size = ele_list.size();
// 	m_pLabAwardIcon->setSize(Size(260,120));
// 
// 	int index = 0;
// 	Game_Data::game_element_list_t::iterator itg;
// 	for( itg = ele_list.begin(); itg != ele_list.end(); ++ itg)
// 	{
// 		Game_Data::Game_Element& element = (*itg);
// 		if(strcmp(element.get_command(),"item") == 0)
// 		{
// 			vector<uint> para;
// 			element.get_para_list_in_vector(para);
// 			if(para.size() > 1)
// 			{
// 				int item_base_id = para[0];
// 				int item_count = para[1];
// 				Game_Data::Item_Config* item_config = ITEM_CONFIG_MGR::instance()->get_item_config(item_base_id);
// 				if (item_config)
// 				{
// 					const char* format = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_GAIN_INFO);
// 					const char* item_name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(item_config->name);
// 
// 					m_pLabAwardContext[index]->setString(CCString::createWithFormat(format,item_name,item_count)->getCString());
// 				}
// 				index++;
// 			}
// 		}
// 	}
// }


void UI_Arena_Layer::showGuide()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}
	if( GUIDE_ARENA_STEP_2 == player->get_guide_id() )
	{
		Joiner_Guidance::receiveCurPosWidget(m_pImgPlayerFatherNodeBack[2]);
	}
}

