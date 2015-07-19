#include "UI_NpcDialogue_Layer.h"

#include "Common/GameMacro.h"
#include "UI/City_Scene.h"

#include "Item_System/Item_Config_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Character_System/CommonNpc_Config_Mgr.h"
#include "Character_System/CommonNpc.h"
#include "Character_System/Player_Logic_Cl.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/CommonNpc.h"

#include "game_play_controler/game_play_controler_data/gameplay_ctrl_data_mgr.h"
#include "Game_Interface/game_data_exchange_client.h"

#include "Character_System/Player.h"
#include "Play_System/Instance_Data_Mgr.h"
#include "Play_System/Formula_Function_Instance.h"
//#include "UI_Interface/UI_Instance_Layer.h"

#include "UI_Icon_Info_Layer.h"
#include "Joiner_Guidance.h"
#include "Function_Open_System/Function_Open_Logic.h"
#include "Common/Game_Utils.h"
#ifdef GAME_CLIENT
#include "cocos2d.h"
#endif

#include "quest_system/quest_data/quest_data_mgr.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/Game_Element_Parse.h"
//#include "AI_System/Game_Utils.h"


using namespace std;
using namespace Game_Data;
using namespace UI;

static const char* szIcon[] =
{
	"dialogue_icon_shop.png",
	"dialogue_icon_cmp.png",
	"dialogue_icon_acc.png",
	"dialogue_icon_uncmp.png"
};

UI_NpcDialogue_Layer::UI_NpcDialogue_Layer(void)
	:m_pWidget(NULL),
	m_pBtnClose(NULL),
	m_pTxtDialogue(NULL),
	m_pAwardPanel(NULL),
	m_pExperience(NULL),
	m_pMoneyNum(NULL),
	m_pImgOfAwardGoods(NULL),
	m_pScrollView(NULL),
	awardGoodId_(0),
    awardGoodCount_(0),
	juniorGuide(NULL)
{
	memset(m_pMissionName, 0 , sizeof(m_pMissionName));
	memset(m_pMissionState, 0 , sizeof(m_pMissionState));
	memset(m_pMissionButton, 0 , sizeof(m_pMissionButton));
}

UI_NpcDialogue_Layer::~UI_NpcDialogue_Layer(void)
{
}

bool UI_NpcDialogue_Layer::init()
{
	if( !Layer::init() )
		return false;

	m_pWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/talk.json");
	addChild(m_pWidget);

	// 关闭按钮
	m_pBtnClose = (cocos2d::ui::Button*)cocos2d::ui::Helper::seekWidgetByName(m_pWidget,"btn_close");
	m_pBtnClose->addTouchEventListener(this,toucheventselector(UI_NpcDialogue_Layer::btnCallback_Close));

	// 滑动层
	m_pScrollView = dynamic_cast<cocos2d::ui::ScrollView*>(Helper::seekWidgetByName(m_pWidget,"scr_scrollView"));

	// 任务描述
	m_pTxtDialogue = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"tea_info"));

	// 奖励层
	m_pAwardPanel = dynamic_cast<cocos2d::ui::Layout*>(Helper::seekWidgetByName(m_pWidget,"pan_award_info"));

	// award experience num
	m_pExperience = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_experience_num"));

	// award money num
	m_pMoneyNum = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_money_num"));

	// award goods icon back
	m_pImgIconBack = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget,"img_frame_goods"));
	m_pImgIconBack->addTouchEventListener(this, toucheventselector(UI_NpcDialogue_Layer::showIconInfo));	

	// award goods icon 
	m_pImgOfAwardGoods = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget,"img_award_icon"));

	// award goods number
	m_pLabOfAwardGoodsNum = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_goods_num"));
	m_pLabOfAwardGoodsNum->setVisible(false);

	for (int i = 0; i < NPC_DIALOGUE_OPTION; i++)
	{
		char szName[32] = { 0 };
		SPRINTF(szName, "btn_mission_back_%d", i + 1);

		m_pMissionButton[i] = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, szName));
		m_pMissionButton[i]->setVisible(false);
		m_pMissionButton[i]->setTouchEnabled(false);
		m_pMissionButton[i]->addTouchEventListener(this, toucheventselector(UI_NpcDialogue_Layer::btnCallback_SelectOption));

		SPRINTF(szName, "lab_mission_info_%d", i + 1);
		m_pMissionName[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget, szName));

		SPRINTF(szName, "img_mission_type_%d", i + 1);
		m_pMissionState[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, szName));
	}
	auto headImg = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "image_mission_type_1") );
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	auto player = (Game_Data::Player*)CHARACTER_MGR::instance()->get_character(role_id);
	int job = player->get_job();
	if (job >= 3)
		job = 3;
	Value pre("img/headIcon/job_");
	Value suff(job);
	Value path(pre.asString() + suff.asString() + ".png");
	headImg->loadTexture(path.asString());

	m_pLayerIconInfo = UI_Icon_Info_Layer::create();
	this->addChild(m_pLayerIconInfo,THISLAYERZORDERE,THISLAYERTAG);
	m_pLayerIconInfo->setVisible(false);

	return true;
}

void UI_NpcDialogue_Layer::setVisible( bool visible )
{
	cocos2d::Layer::setVisible(visible);
	if(visible)
	{
		showGuide();
	}
	else
	{
		m_pLayerIconInfo->setVisible(false);
	}
}

void UI_NpcDialogue_Layer::showGuide()
{
	m_pBtnClose->setTouchEnabled(true);

	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if(player == nullptr) 
		return;
;
	if( JUNIOR_GUIDE_STEP_2 == player->get_guide_id() || JUNIOR_GUIDE_STEP_13 == player->get_guide_id() )
	{
		if (JUNIOR_GUIDE_STEP_2 == player->get_guide_id())
		{
			Joiner_Guidance::receiveCurPosWidget(m_pMissionButton[0]);
		}	
		else
		{
			Joiner_Guidance::receiveCurPosWidget(m_pMissionButton[0]);
		}		
	}
	else if (JUNIOR_GUIDE_STEP_3 == player->get_guide_id() || JUNIOR_GUIDE_STEP_14 == player->get_guide_id())
	{
		Joiner_Guidance::receiveCurPosWidget(m_pMissionButton[0]);
	}
}

void UI_NpcDialogue_Layer::btnCallback_Close( Ref* pSender ,Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;

    int role_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
    if (player == nullptr)
		return;
    
	setVisible(false);
	if (JUNIOR_GUIDE_STEP_2 == player->get_guide_id() || JUNIOR_GUIDE_STEP_13 == player->get_guide_id())
	{
		player->change_guide_id(player->get_guide_id() - 1);
		UI_MainMenu_Layer::get_instance()->showGuide();
	}
	if (JUNIOR_GUIDE_STEP_3 == player->get_guide_id())
	{
		player->change_guide_id(player->get_guide_id() - 2);
		UI_MainMenu_Layer::get_instance()->showGuide();
	}
}


void UI_NpcDialogue_Layer::showDialogueWithNpcTypeID( int nTypeID )
{
	// 1. 记录当前与玩家互动的NpcID
	m_nNpcID = nTypeID;

	// 2. 切换当前的状态为对话状态
	m_State = DS_NpcDialogue;

	// 3. 初始化记录的Npc上的数据
	m_vecServiceData.clear();

	// 4. 设置Npc的名字
	ui::Text* pName = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_role_name"));

	City_NPC* npc = Game_Utils::instance()->get_npc_by_id(m_nNpcID);
	if (npc)
	{
		pName->setString(npc->getCityActor()->getName());
	}

	// 5. 刷新界面
	updateDetail();
}

void UI_NpcDialogue_Layer::updateDetail()
{
	for (int i = 0; i < NPC_DIALOGUE_OPTION; i++)
	{
		m_pMissionButton[i]->setVisible(false);
		m_pMissionButton[i]->setTouchEnabled(false);
	}

#ifdef YN_WINDOWS
	static_assert(sizeof(szIcon)/sizeof(szIcon[0])==NS_Num,"the number of szIcon should be equal with NS_Num");
#endif

	//m_pScrollView->scrollToTop();

	if (DS_NpcDialogue==m_State)
	{
		m_pAwardPanel->setVisible(false);
		m_pImgIconBack->setTouchEnabled(false);

		m_vecServiceData.clear();

		//quest
		proc_quest_select_list();

		// 设置任务描述
		City_NPC* npc = Game_Utils::instance()->get_npc_by_id(m_nNpcID);
		if (npc)
		{
			
			m_pTxtDialogue->setText(get_string(npc->getCityActor()->getDialogID()));
		}		

		int nOptionNum = MIN(NPC_DIALOGUE_OPTION,m_vecServiceData.size());

		if (nOptionNum>0)
		{
			std::sort(m_vecServiceData.begin(),m_vecServiceData.end(),Compare());
		}

		for (int i = 0; i < NPC_DIALOGUE_OPTION; ++i)
		{
			if (i>=nOptionNum)
				break;
			m_pMissionButton[i]->setVisible(true);
			m_pMissionButton[i]->setTouchEnabled(true);
			m_pMissionButton[i]->setTag(i);
			m_pMissionButton[i]->addTouchEventListener(this,toucheventselector(UI_NpcDialogue_Layer::btnCallback_SelectOption));
			const char* missionDesc = m_vecServiceData[i].strCaption.c_str();
			m_pMissionName[i]->setString( missionDesc );  
		}


	}
	else if (DS_Mission==m_State)
	{
		proc_quest_selected();

	}
	else
	{
		CC_ASSERT(false && "m_State ERROR!!" );
	}
}

const char* UI_NpcDialogue_Layer::get_quest_dialog_txt(Game_Data::quest_data& qd, int type)
{
	if(type==NS_Mission_Uncompelted)
	{
		return get_string(TASKUNCOMPLETE);
	}
	if(type==NS_Mission_CanBeAccepted)
	{
		int value=qd.get_quest_exec_dialog_id();
		return get_string(value);
	}
	if(type==NS_Mission_Compeleted)
	{
		return get_string(qd.get_quest_submit_dialog_id());
	}

	return "";
}

int UI_NpcDialogue_Layer::proc_quest_selected( void )
{
	m_pAwardPanel->setVisible(true);

	CC_ASSERT( m_nCurrSelectID>=0 && m_nCurrSelectID<(int)m_vecServiceData.size() );
	const ServiceData& refData = m_vecServiceData[m_nCurrSelectID];

	Game_Data::quest_data* qd = Game_Data::quest_data_mgr::instance()->get_org_quest_data( refData.nID );
	if( NULL == qd )
	{
		return -1;
	}

	m_pTxtDialogue->setText(get_quest_dialog_txt(*qd,refData.nType ));
	displayer_quest_award(*qd);

	display_npc_dialog( *qd, refData );
	return 0;
}
int UI_NpcDialogue_Layer::displayer_quest_award(Game_Data::quest_data& qd)
{
	Game_Data::game_quest_content award_cont;

	qd.get_quest_award(award_cont);
	Game_Data::game_element_list_t award_list;
	award_cont.get_quest_element(award_list);
	vector<uint> para;
	Game_Element_Parse::instance()->get_para_from_require_element( "awardexp", award_list, para);
	char txt[256];
	if( para.size() > 0)
	{	
		sprintf( txt, "%d", para[0]);
		m_pExperience->setString(txt);
	}
	para.clear();

	Game_Element_Parse::instance()->get_para_from_require_element( "awardmoney", award_list, para);
	if( para.size() > 0)
	{
		sprintf( txt, "%d", para[0]);
		m_pMoneyNum->setString(txt);
	}

	//道具奖励
	para.clear();
	Game_Element_Parse::instance()->get_para_from_require_element( "awarditem", award_list, para);
	if( para.size() > 1 )
	{
		m_pImgIconBack->setVisible(true);
		m_pImgIconBack->setTouchEnabled(true);

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

        Item_Config_Mgr::instance()->load_icon_config_data();
		const char* iconName = ITEM_CONFIG_MGR::instance()->get_icon_path(config->icon);
        std::string p("icon/");
        p+=iconName;
		m_pImgOfAwardGoods->loadTexture(p.c_str());

		if( para[1] > 1 )
		{
			m_pLabOfAwardGoodsNum->setString(CCString::createWithFormat("%d",para[1])->getCString());
			m_pLabOfAwardGoodsNum->setVisible(true);
		}
		else
		{
			m_pLabOfAwardGoodsNum->setVisible(false);
		}
		

		awardGoodId_ = para[0];
        awardGoodCount_ = para[1];
	m_pImgIconBack->setTag(para[0]);
		m_pImgIconBack->setVisible(true);
		m_pImgIconBack->setTouchEnabled(true);
	}
	else
	{
		awardGoodId_ = 0;
        awardGoodCount_ = 0;
		m_pImgIconBack->setTag(0);
		m_pImgIconBack->setVisible(false);
		m_pImgIconBack->setTouchEnabled(false);
	}
	return 0;
}
int UI_NpcDialogue_Layer::display_npc_dialog( Game_Data::quest_data& qd, const ServiceData& refData )
{
	for (int i = 0; i < NPC_DIALOGUE_OPTION; i++)
	{
		m_pMissionButton[i]->setVisible(false);
		m_pMissionButton[i]->setTouchEnabled(false);
	}
	for (int i = 0; i < NPC_DIALOGUE_OPTION; i++)
	{
		if(0!=i)
		{ 
			m_pMissionButton[i]->setVisible(false);
			m_pMissionButton[i]->setTouchEnabled(false);
			continue;
		}
		m_pMissionButton[i]->setVisible(true);
		m_pMissionButton[i]->setTouchEnabled(true);

//		m_pMissionState[i]->loadTexture(szIcon[refData.nType],UI_TEX_TYPE_PLIST);

		char txt[1024];
		if (NS_Mission_Compeleted==refData.nType)
		{
			//设置提示信息内容
			get_npc_dialog_quest_state_txt(qd, MISSION_OVER, txt);
			m_pMissionName[i]->setString(txt);
		}
		else if (NS_Mission_CanBeAccepted==refData.nType)
		{
			//设置提示信息内容
			get_npc_dialog_quest_state_txt(qd, MISSION_ACCEPT, txt);
			m_pMissionName[i]->setString(txt);
			CCLog("open new icon !!!");
		}
		else if (NS_Mission_Uncompelted==refData.nType)
		{
			//设置提示信息内容
			get_npc_dialog_quest_state_txt(qd, MISSION_DOITNOW, txt);
			m_pMissionName[i]->setString(txt);
		}
		else
		{
			CC_ASSERT(false);
		}

	}
	return 0;
}
int UI_NpcDialogue_Layer::get_npc_dialog_quest_state_txt(Game_Data::quest_data& qd, int type, char* txt)
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	const char* accepttext=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(type);
	char count[256];
	if( 0 ==  game_data_exchange_client::instance()->get_quest_act_txt(player_id, qd.get_quest_id(), count) )
	{
		sprintf( txt, "%s%s",accepttext,count);
	}
	else
	{
		sprintf( txt, "%s",accepttext);
	}
	return 0;
}

int UI_NpcDialogue_Layer::proc_quest_select_list( void )
{
	// 
	// 1. 获取玩家ID
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();

	// 2. 获取NpcID
	int npc_static_id = Game_Utils::instance()->get_npc_static_id( m_nNpcID );

	// 3. 获取该Npc身上所有的请求数据列表
	Game_Data::npc_bind_quest::npc_bind_quest_vec_t npc_quest_lst;
	Game_Data::quest_data_mgr::instance()->get_player_npc_quest_bind_data( player_id, npc_quest_lst );

	// 4. 遍历请求数据列表,然后分类并进行存储
	std::vector<uint32> vecQuest;
	Game_Data::npc_bind_quest::npc_bind_quest_vec_t::iterator itn;
	for( itn = npc_quest_lst.begin(); itn != npc_quest_lst.end(); ++ itn )
	{
		if( (*itn).get_npc_id() != npc_static_id )
			continue;

		// 4_1. 获取可接任务的数据
		vecQuest.clear();
		(*itn).get_accept_quest_list(vecQuest);
		if (vecQuest.size() != 0)
		{
			proc_quest_select(NS_Mission_CanBeAccepted, vecQuest);
		}

		// 4_2. 获取完成但没提交的任务数据
		vecQuest.clear();
		(*itn).get_submit_quest_list(vecQuest);
		if (vecQuest.size() != 0)
		{
			proc_quest_select(NS_Mission_Compeleted, vecQuest);
		}
		
		// 4_3. 获取没有完成的任务数据
		vecQuest.clear();
		(*itn).get_inprocess_quest_list(vecQuest);
		if (vecQuest.size() != 0)
		{
			proc_quest_select(NS_Mission_Uncompelted, vecQuest);
		}
		break;
	}

	return 0;
}

int UI_NpcDialogue_Layer::proc_quest_select(NpcServiceType Type,std::vector<uint32> vecQuest)
{
	/************************************************************************/
	// 根据Npc服务类型进行存储
	std::vector<uint32>::iterator it = vecQuest.begin();

	// 遍历列表获取请求的名字,并将结构体数据存储
	for ( it ; it!=vecQuest.end(); it++)
	{
		Game_Data::quest_data* qd = Game_Data::quest_data_mgr::instance()->get_org_quest_data( (*it));
		if( NULL == qd )
			continue;

		char txt[128] = {0};
		get_quest_name(*qd, txt);
		m_vecServiceData.push_back(ServiceData(Type, qd->get_quest_id(),txt));
	}
	return 0;
}
int UI_NpcDialogue_Layer::get_quest_name( Game_Data::quest_data& qd, char* txt )
{
	/************************************************************************/
	// 获取请求的名字
	// 1. 获取玩家ID
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();

	// 2. 获取请求的名字
	char count[256] = {0};
	if (game_data_exchange_client::instance()->get_quest_act_txt(player_id, qd.get_quest_id(), count) == 0)
	{
		sprintf(txt, "%s%s", get_string(qd.get_quest_name_id()),count );
	}
	else
	{
		sprintf(txt, "%s", get_string(qd.get_quest_name_id()));
	}
	return 0;
}

const char* UI_NpcDialogue_Layer::get_string( int id )
{
	return DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(id);
}

void UI_NpcDialogue_Layer::btnCallback_SelectOption( Ref* pSender ,Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
		return;

    cocos2d::ui::Button* pBtn ;
    int buttonTag ;
    int role_id;
    Game_Data::Player* player;
    pBtn = dynamic_cast<cocos2d::ui::Button*>(pSender);
    buttonTag = pBtn->getTag();
    //CCLOG("current button Tag = %d", buttonTag);
    CC_ASSERT(pBtn);

    role_id = Account_Data_Mgr::instance()->get_current_role_id();
    player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
    if (!player) return;
    if (JUNIOR_GUIDE_STEP_2 == player->get_guide_id() || JUNIOR_GUIDE_STEP_3 == player->get_guide_id() || JUNIOR_GUIDE_STEP_13 == player->get_guide_id() || JUNIOR_GUIDE_STEP_14 == player->get_guide_id())
    {
        Joiner_Guidance::hideGuide();
        player->change_guide_id(player->get_guide_id() + 1);
        showGuide();
        if (JUNIOR_GUIDE_STEP_4 == player->get_guide_id() || JUNIOR_GUIDE_STEP_15 == player->get_guide_id())
        {
            UI_MainMenu_Layer::get_instance()->showGuide();
        }
    }

if (DS_NpcDialogue == m_State)
{
	m_State = DS_Mission;
	m_nCurrSelectID = pBtn->getTag();

	CC_ASSERT(m_nCurrSelectID >= 0 && m_nCurrSelectID < (int)m_vecServiceData.size());

	const ServiceData& refData = m_vecServiceData[m_nCurrSelectID];
	switch (refData.nType)
	{
	case NS_Shop:
	{
					UI_MainMenu_Layer* pMenu = dynamic_cast<UI_MainMenu_Layer*>(getParent());
					CC_ASSERT(pMenu);
					//pMenu->showShop(refData.nID);
					setVisible(false);
	}
		break;
	case NS_Mission_Compeleted: //完成任务
	{
									//m_pScrollView->getInnerContainer()->setSize(Size(600,50*4));
									//m_pScrollView->getInnerContainer()->setPosition(Vec2(0,0));
									updateDetail();
	}
		break;
	case NS_Mission_CanBeAccepted: //接受任务
	case NS_Mission_Uncompelted: //未完成（马上前去）
	{
									 //m_pScrollView->getInnerContainer()->setSize(Size(600,50*4));
									 //m_pScrollView->getInnerContainer()->setPosition(Vec2(0,0));
									 updateDetail();
	}
		break;
	default:
		CC_ASSERT(false);
	}

}
else if (DS_Mission == m_State)
{
	//m_pScrollView->getInnerContainer()->setSize(Size(600,50*4));
	//if (0==pBtn->getTag())
	{//accept mission

		CC_ASSERT(m_nCurrSelectID >= 0 && m_nCurrSelectID < (int)m_vecServiceData.size());

		const ServiceData& refData = m_vecServiceData[m_nCurrSelectID];
		switch (refData.nType)
		{
		case NS_Mission_Compeleted:
		{
									  Game_Data::quest_data* quest_data = Game_Data::quest_data_mgr::instance()->get_quest_data(role_id, refData.nID);
									  if (!quest_data)
									  {
										  return;
									  }

									  game_quest_content ele_cont;
									  quest_data->get_quest_award(ele_cont);

									  Game_Data::game_element_list_t ele_list;
									  ele_cont.get_quest_element(ele_list);
									  if (PLAYER_LOGIC::instance()->check_bag_room(role_id, ele_list) == false)
									  {
										  DICTIONARY_CONFIG_MGR::instance()->show_alert(UG_BAG_FULL);
										  return;
									  }

									  vector<uint64> para;
									  para.push_back(role_id);
									  para.push_back(refData.nID);
									  Game_Logic::Game_Content_Interface::instance()->exec_interface("sendsubmitquest", para);
									  CCLog("mission success, congratulations!!!");

									  FUNCTION_OPEN_LOGIC::instance()->submit_quest_open(role_id, refData.nID);

									  if (awardGoodId_ != 0)
									  {//显示 获得信息的提示	
										  const char* gain = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_U_GAIN);
										  std::string strGain(gain);
										  const char* gainCont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_GAIN_INFO);

										  Game_Data::Item_Config* item_config = ITEM_CONFIG_MGR::instance()->get_item_config(awardGoodId_);
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

										  const char* iconName = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(config->name);
										  const char* getGainInfo = CCString::createWithFormat(gainCont, iconName, awardGoodCount_)->getCString();
										  std::string strGainCont(getGainInfo);
										  DICTIONARY_CONFIG_MGR::instance()->show_alert((strGain + strGainCont).c_str());
									  }

		}
			break;
		case NS_Mission_CanBeAccepted:
		{
										 vector<uint64> para;
										 para.push_back(Account_Data_Mgr::instance()->get_current_role_id());
										 para.push_back(refData.nID);
										 Game_Logic::Game_Content_Interface::instance()->exec_interface("sendacceptquest", para);

										 FUNCTION_OPEN_LOGIC::instance()->accept_quest_open(role_id, refData.nID);

		}
			break;
		case NS_Mission_Uncompelted:
		{
									   //					vector<uint64> para;
									   //					para.push_back(Account_Data_Mgr::instance()->get_current_role_id());
									   //					para.push_back(refData.nID);
									   ////					Game_Logic::Game_Content_Interface::instance()->exec_interface("sendrequirestagestate", para);
									   //                    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendrequirestageall", para);

									   CCLog("refData.nID = %d", refData.nID);
									   executeTask(refData.nID);
		}
			break;
		case NS_Shop:
		default:
			CC_ASSERT(false);
		}
	}
	setVisible(false);
}
else
{
	CC_ASSERT(false && "m_State ERROR!!");
}

}

void UI_NpcDialogue_Layer::executeTask(int missionId)
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (player == NULL)
	{
		return;
	}

	const quest_data::quest_data_vec_t vecData = quest_data_mgr::instance()->get_quest_data_list(player_id);
	quest_data* qd = Game_Data::quest_data_mgr::instance()->get_quest_data(player_id, missionId);
	if (!qd)
	{
		return;
	}

	game_quest_content ele_cont;
	qd->get_quest_content(ele_cont);

	Game_Data::game_element_list_t ele_list;
	ele_cont.get_quest_element(ele_list);

	Game_Data::game_element_list_t::iterator itg;

	vector<uint> para;
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
				Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
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
				Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
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

void UI_NpcDialogue_Layer::showIconInfo( Ref* pSender,Widget::TouchEventType type )
{
cocos2d::ui::ImageView* curImg;
int base_id;
Game_Data::Item_Config* item_config;
	int quality = 0;
	int level = 1;
	Item_Config* config = NULL;
	Equipment_Depot_Config* equipment_depot_config;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	curImg = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
	base_id =curImg->getTag();

	item_config = ITEM_CONFIG_MGR::instance()->get_item_config(base_id);
	if (item_config->type == IT_EQUIPMENT_DEPOT)
	{
		equipment_depot_config = reinterpret_cast<Equipment_Depot_Config*>(item_config);
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

