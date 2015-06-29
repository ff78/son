#include "UI_Settlement_Layer.h"
#include "Game_Interface/game_content_interface.h"
#include "Character_System/Player_Logic_Cl.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Character.h"
#include "Character_System/Player_Config_Mgr.h"
#include "Character_System/FightNpc_Config_Mgr.h"
#include "Character_System/Player.h"
#include "Item_System/Item_Logic_Cl.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Play_System/Instance_Data_Mgr.h"
//#include "Game_Utils.h"
#include "Game_Interface/game_event_mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"

#include "Play_System/Formula_Function_Instance.h"
#include "Play_System/Instance_Data_Mgr.h"

//#include "UI/Unique_Skill.h"
#include "UI_Icon_Info_Layer.h"
#include "Joiner_Guidance.h"
#include "Common/GameDefine.h"
using namespace Game_Data;
using namespace ui;

UI_Settlement_Layer::UI_Settlement_Layer(void):
	m_pSettlementWidget_(NULL),
	m_pImgWinOrLose(NULL), 
	m_pLabExp_1(NULL),  
	m_pLabLieuExpNum(NULL),  
	m_pLabMoneyAward(NULL),
	m_pLabTimeScore(NULL),
	m_pLabDeadScore(NULL),
	m_pLabVIPScore(NULL),
	m_pLabFinalScore(NULL),
	m_pImgHeadPhoto_1(NULL),
	m_pImgHeadPhoto_2(NULL),
	isGainOrNot(false),
	m_star_count(0)
{
	memset(cocoIconGoods, 0, sizeof(cocoIconGoods));
	memset(cocoIconGoods_Texture, 0, sizeof(cocoIconGoods_Texture));
	memset(cocoIconGoods_Num, 0, sizeof(cocoIconGoods_Num));
	memset(m_pImgStartsForLevel, 0, sizeof(m_pImgStartsForLevel));
}


UI_Settlement_Layer::~UI_Settlement_Layer(void)
{
}

bool UI_Settlement_Layer::init()
{
	if( !cocos2d::Layer::init() )
	{
		return false;
	}

	const char* gain = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_U_GAIN);
	std::string strTemp(gain);
	m_getGainAwardInfo = strTemp;   //您获得了（+两个空格）  

	m_pSettlementWidget_ = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Result/Result.ExportJson");
	m_pSettlementWidget_->setVisible(true);
	addChild(m_pSettlementWidget_);

	closeButton = (cocos2d::ui::Button*)Helper::seekWidgetByName(m_pSettlementWidget_,"btn_Close");
	closeButton->addTouchEventListener(this,toucheventselector(UI_Settlement_Layer::settlementCloseCallback));
	
	m_lab_close_btn_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pSettlementWidget_,"lab_hc"));
	m_lab_close_btn_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_GO_BACK_MAIN_CITY));

	//创建物品信息显示框 function init()
	m_pLayerIconInfo = UI_Icon_Info_Layer::create();
	this->addChild(m_pLayerIconInfo,THISLAYERZORDERE,THISLAYERTAG);
	m_pLayerIconInfo->setVisible(false);

	settlementConfig();

	return true;
}

int  UI_Settlement_Layer::proc_instance_result(void)
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();

	current_instance_data cid;
	if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
	{
		return -1;
	}
	if( current_instance_data::INSTANCE_STATE_SUC != cid.get_instance_state())
		return -1;
	cout << "----------send finish instance---------------------" << endl;
	vector<uint64> para;
	para.clear();
	para.push_back(player_id);
	para.push_back(instance_id);
	para.push_back(0);
	Game_Logic::Game_Content_Interface::instance()->exec_interface("sendfinishinstance", para);

	para.clear();
	Game_Logic::Game_Content_Interface::instance()->exec_interface("remvoeinstancedata", para);

	return 0;
}


void UI_Settlement_Layer::setVisible( bool visible )
{
	cocos2d::Layer::setVisible(visible);
	if(visible)
	{
		//UI::Unique_Skill::get_instance()->setTouchEvent(false);
		/* 显示获取物品及物品数量的信息
		if(isGainOrNot)
			DICTIONARY_CONFIG_MGR::instance()->show_alert(m_getGainAwardInfo.c_str());
		*/
		showGuide();
	}
	else
	{
		m_pLayerIconInfo->setVisible(false);
	}
	
}

void UI_Settlement_Layer::showGuide()
{
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if(!player) return;
	if( JUNIOR_GUIDE_STEP_11 == player->get_guide_id() )
	{
		Point worldPoint = closeButton->getWorldPosition();
		Joiner_Guidance::receiveCurPosWidget(closeButton);
	}
}

void UI_Settlement_Layer::settlementCloseCallback( cocos2d::Ref* pSender,Widget::TouchEventType type )
{
int role_id;
Game_Data::Player* player;
	vector<uint64> para;

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:

	setVisible(false);

	role_id = Account_Data_Mgr::instance()->get_current_role_id();
	player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if(!player) return;
	if( JUNIOR_GUIDE_STEP_11 == player->get_guide_id() )
	{
		Joiner_Guidance::hideGuide();
		player->change_guide_id(player->get_guide_id()+1);
	}

	//将角色的怒气值清零
//	UI::Unique_Skill::get_instance()->clearAngryGas();

	para.clear();
	Game_Logic::Game_Content_Interface::instance()->exec_interface("remvoeinstancedata", para);
	para.clear();
	para.push_back(1);
	Game_Logic::Game_Content_Interface::instance()->exec_interface("enterscene", para);
	//Game_Utils::instance()->show_win_finished();

	//Game_Utils::instance()->reset_role_actor();

	break;
    default:
	break;
}
}

void UI_Settlement_Layer::settlementConfig()
{

	//设置胜利 失败的图片显示信息
	cocos2d::ui::ImageView* img_WinOrLose = (cocos2d::ui::ImageView*)Helper::seekWidgetByName(m_pSettlementWidget_,"img_WinOrLose");

	m_pImgWinOrLose = (cocos2d::ui::ImageView*)Helper::seekWidgetByName(m_pSettlementWidget_,"img_WinOrLose");

	//设置 上方的 EXP 经验值 数值
	m_pLabExp_1 = (cocos2d::ui::Text*)Helper::seekWidgetByName(m_pSettlementWidget_,"lab_EXP_Num1");

	m_pLabMoneyAward = (cocos2d::ui::Text*)Helper::seekWidgetByName(m_pSettlementWidget_,"lab_MoneyReawrd_Num");
	m_pLabTimeScore = (cocos2d::ui::Text*)Helper::seekWidgetByName(m_pSettlementWidget_,"lab_Combo_Score");
	m_pLabDeadScore = (cocos2d::ui::Text*)Helper::seekWidgetByName(m_pSettlementWidget_,"lab_TimeConsuming_Score");
	m_pLabVIPScore = (cocos2d::ui::Text*)Helper::seekWidgetByName(m_pSettlementWidget_,"lab_BeHit_Score");
	m_pLabFinalScore = (cocos2d::ui::Text*)Helper::seekWidgetByName(m_pSettlementWidget_,"lab_KillEnemy_Score");

	//星星 获得 
	char starskey[32] = {0};
	for( int i=0; i<3; ++i)
	{
		memset(starskey, 0, sizeof(starskey));
		sprintf(starskey, "img_Star_%d", i+1);
		m_pImgStartsForLevel[i] = (cocos2d::ui::ImageView*)Helper::seekWidgetByName(m_pSettlementWidget_,starskey);
		m_pImgStartsForLevel[i]->setScale(1.0f);
		m_pImgStartsForLevel[i]->setVisible(false);
	}

	//设置头像 1 图片
	cocos2d::ui::ImageView* imgHead_1 = (cocos2d::ui::ImageView*)Helper::seekWidgetByName(m_pSettlementWidget_,"img_head1");
	m_pImgHeadPhoto_1 = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pSettlementWidget_,"img_PlayerHead_1"));

	//副将 头像 2 图片
	m_pImgLieuHeadBack = (cocos2d::ui::ImageView*)Helper::seekWidgetByName(m_pSettlementWidget_,"img_head2");
	m_pImgHeadPhoto_2 = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pSettlementWidget_,"img_PlayerHead_2"));


	//副将 EXP 数值
	m_pLabLieuExpNum = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pSettlementWidget_,"lab_EXP_Num2"));
	//副将 EXP 图片
	m_pLabLieuEXP = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pSettlementWidget_,"lab_EXP_2"));
	//副将 VIP 图片
	m_pImgLieuVIP = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pSettlementWidget_,"img_VIP_2"));
	//副将 VIP 数值
	m_pLabLieuVIPNum = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pSettlementWidget_,"lab_VIP_Num2"));

	//设置副本奖励 图标
	char key[32] = {0};
	for( int i=0 ; i<3 ; ++i )
	{
		//奖励图片背景
		memset(key, 0, sizeof(key));
		sprintf(key, "img_AwardItem_%d", i+1);
		cocoIconGoods[i] = (cocos2d::ui::ImageView*)(Helper::seekWidgetByName(m_pSettlementWidget_,key));
		cocoIconGoods[i]->addTouchEventListener(this, toucheventselector(UI_Settlement_Layer::showIconInfo));

		//奖励显示的图片
		memset(key, 0, sizeof(key));
		sprintf(key, "img_IconTexture_%d", i+1);
		cocoIconGoods_Texture[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pSettlementWidget_,key));

		memset(key, 0, sizeof(key));
		sprintf(key, "lab_num_%d", i+1);
		cocoIconGoods_Num[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pSettlementWidget_,key));
		cocoIconGoods_Num[i]->setVisible(false);
	}

	update();
}

void UI_Settlement_Layer::update()
{
	//设置 win or lose
	//img_WinOrLose->loadTexture("",UI_TEX_TYPE_PLIST);

	int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
	vector<uint> para;

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	current_instance_data cid;
	if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
	{
		return;
	}

	m_pLabExp_1->setString("0");
	para.clear();
	Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute","result_content","award_exp_compute",para);
	if ( para.size() >= 1)
	{
		char txt[256];
		sprintf( txt, "%d", para[0]);
		m_pLabExp_1 = (cocos2d::ui::Text*)Helper::seekWidgetByName(m_pSettlementWidget_,"lab_EXP_Num1");
		m_pLabExp_1->setString(txt);
		m_pLabLieuExpNum->setString(txt);
	}

	m_pLabMoneyAward->setString("0");
	para.clear();
	Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute","result_content","award_money",para);
	if ( para.size() >= 1)
	{
		char txt[256];
		sprintf( txt, "%d", para[0]);
		m_pLabMoneyAward = (cocos2d::ui::Text*)Helper::seekWidgetByName(m_pSettlementWidget_,"lab_MoneyReawrd_Num");
		m_pLabMoneyAward->setString(txt);
	}

	m_pLabTimeScore->setString("0");
	para.clear();
	Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute","result_content","time_envalue",para);
	if ( para.size() > 1)
	{
		int time_value_100 = para[0]; int time_value_0 = para[1];
		int score = 0;
		if( time_value_0 - time_value_100 != 0 )
			score =100 - (cid.get_time_grad() - time_value_100)/(time_value_0 - time_value_100)*100;
		if(score < 0) score = 0;
		char txt[256];
		sprintf( txt, "%d", score);
		m_pLabTimeScore->setString(txt);
	}

	m_pLabDeadScore->setString("0");
	para.clear();
	Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute","result_content","player_die_envalue",para);
	if ( para.size() > 0)
	{
		int player_die_envalue = para[0];
		int score = cid.get_total_player_die()*player_die_envalue;
		if(score < 0) score = 0;
		char txt[256];
		sprintf( txt, "%d", score);
		m_pLabDeadScore->setString(txt);
	}


	m_pLabVIPScore->setString("0");

	if( cid.get_total_monster_kill() > 0)
	{
		char txt[256];
		sprintf( txt, "%d", cid.get_instance_score());
		m_pLabFinalScore->setString(txt);
	}
	else
	{
		m_pLabFinalScore->setString("0");
	}

	//设置主角头像
	Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	CC_ASSERT(player);
	const char* picRoleHead = ITEM_CONFIG_MGR::instance()->get_icon_path(player->get_face_mode_id());
	m_pImgHeadPhoto_1->loadTexture(picRoleHead,UI_TEX_TYPE_PLIST);

	//设置副将头像
	DeputyGeneral* general = player->get_fight_general();
	if(general)
	{
		m_pImgLieuHeadBack->setVisible(true);
		m_pLabLieuEXP->setVisible(true);
		m_pImgLieuVIP->setVisible(true);
		m_pLabLieuExpNum->setVisible(true);
		m_pLabLieuVIPNum->setVisible(true);

		const char* picRoleHead = ITEM_CONFIG_MGR::instance()->get_icon_path(general->get_face_mode_id());
		m_pImgHeadPhoto_2->loadTexture(picRoleHead, UI_TEX_TYPE_PLIST);
	}
	else
	{
		m_pImgLieuHeadBack->setVisible(true);
		m_pLabLieuEXP->setVisible(true);
		m_pImgLieuVIP->setVisible(true);

		m_pLabLieuExpNum->setVisible(true);
		m_pLabLieuExpNum->setString("0");
		m_pLabLieuVIPNum->setVisible(true);
	}

	int visibelStarsNum = 0;//	分数线的划分85含85以上为三星、45分不含45分以下为1星，其余情况为二星
	int score = cid.get_instance_score();
	if(score >= 85)
	{
		visibelStarsNum = 3;
	}
	else if(score < 85 && score >= 45 )
	{
		visibelStarsNum = 2;
	}
	else if(score > 0 )
	{
		visibelStarsNum = 1;
	}

	float fDelayTime = 1.5f;
	static const float fScale1 = 0.05f;
	static const float fScale2 = 0.3f;
	static const float fDelay = 0.2f;
	m_star_count = 0;
	for( int i=0; i<visibelStarsNum && visibelStarsNum<=3; ++i)
	{
		CCSequence* pSeq = CCSequence::create(CCDelayTime::create(fDelayTime),
			CCShow::create(),
			CCScaleTo::create(fScale1,5.0f),
			CCScaleTo::create(fScale2,1.5f),
			CCDelayTime::create(fDelay),
			NULL);
		fDelayTime += fScale1+fScale2+fDelay;
		CallFunc* callFunc = CallFunc::create(this, callfunc_selector(UI_Settlement_Layer::setStarsVisible));
		m_pImgStartsForLevel[i]->runAction(CCSequence::create(pSeq, callFunc, NULL));
	}


	//设置副本奖励 图标
	map<int,int> item_list;
	map<int,int>::iterator itm;
	cid.get_item_award_list(item_list);

	int item_count = 0;
	for( itm =item_list.begin(); itm != item_list.end(); ++ itm)
	{
		int item_base_id = itm->first;
		int count = itm->second;
		cocoIconGoods[item_count]->setVisible(true);	
		cocoIconGoods_Texture[item_count]->setVisible(true);

		Game_Data::Item_Config* item_config = ITEM_CONFIG_MGR::instance()->get_item_config(item_base_id);
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
		cocoIconGoods_Texture[item_count]->loadTexture(szTexture,UI_TEX_TYPE_PLIST);
		if( count > 1 )
		{
			cocoIconGoods_Num[item_count]->setString(CCString::createWithFormat("%d",count)->getCString());
			cocoIconGoods_Num[item_count]->setVisible(true);
		}
		else
		{
			cocoIconGoods_Num[item_count]->setVisible(false);
		}
		cocoIconGoods[item_count]->setTag(item_base_id);
		item_count ++;

		const char* iconName = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(config->name);
		const char* gainInfo = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_GAIN_INFO);
		const char* getGainInfo = CCString::createWithFormat(gainInfo,iconName,count)->getCString();
		string str(getGainInfo);
		m_getGainAwardInfo += (str+"  ");
		isGainOrNot = true;

#if 0
		CCSequence* pSeq2 = CCSequence::create(CCDelayTime::create(fDelayTime),CCShow::create(),CCScaleTo::create(fScale1,5.0f),CCScaleTo::create(fScale2,2.0f),CCDelayTime::create(fDelay),NULL);
		fDelayTime += fScale1+fScale2+fDelay;
		cocoIconGoods_Texture[item_count]->runAction(pSeq2);
#endif
	}

}

void UI_Settlement_Layer::setStarsVisible()
{
	m_pImgStartsForLevel[m_star_count]->setVisible(true);
	m_star_count++;
}

void UI_Settlement_Layer::showIconInfo( cocos2d::Ref* pSender ,Widget::TouchEventType type)
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
	if( NULL == item_config )
		return;
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
	else if(config->type == IT_EQUIPMENT)
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
