#ifndef _UI_BUTTON_LAYER_
#define _UI_BUTTON_LAYER_

#include "cocos2d.h"
#include "Game_Interface/event_define.h"
#include "UI_AllSetting_Layer.h"
#include "Character_System/Player_Config_Data.h"
#include "Function_Open_System/Function_Open_Config_Data.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
#include "Common/Game_Utils.h"
#include "ClientLogic/Actor/City_NPC.h"
/*========================================= dely =====================================*/
#include "../ClientLogic/SneakyJoy/SneakyJoystick.h"
#include "../ClientLogic/SneakyJoy/SneakyJoystickSkinnedBase.h"
#include "./UI_Equipment_Strength_Layer/UI_Equipment_Strengthen_Layer.h"
#include "./UI_Equipment_StarUp_Layer/UI_Equipment_StarUp_Layer.h"
/*========================================= dely =====================================*/
#include "ClientLogic/GameScene/SelectBattleLayer.h"

USING_NS_CC;

namespace Game_Logic
{
	struct Game_Event;
}

enum OperateType
{
    OP_CLICK = 1,
    OP_MOVE = 2,
    OP_DRAG = 3
};
struct GuideData
{
    int tableId;
    int level;
    int nextStepId;
    std::string armStr;
    float offX;
    float offY;
    float scaleX;
    float scaleY;
    float moveX;
    float moveY;
    std::string itemName;
    std::string destItmeName;
    std::string tipStr;
    int operateType;
};


//一级界面
//class UI_Role_Info_Layer;
class Game_Utils;
class City_NPC;
class UI_Bag_Info_Layer;
//class UI_Instance_Layer;
class UI_Skill_Layer;
//class UI_Instance_Describe_Layer;
//class UI_HeartMethod_Layer;
class UI_Mission_Layer;
class UI_ChatBoard_Layer;
class UI_NpcDialogue_Layer;
class UI_MissionDialogue_Layer;
class UI_Social_Activity_Layer;
class UI_Arena_Layer;
class UI_Material_Fragment_Layer;
class UI_Fate_Layer;
class UI_Public_Announcement;
class UI_Exchange_Code_Layer;
class UI_Banks_Layer;
class UI_Ranking_List_Layer;
class UI_Login_Award_Layer;
class UI_Shop_Center_Layer;
class UI_Activity_Layer;

//二级界面
//class UI_HeartMethod_Combine_Layer;
//class UI_HeartMethod_Quality_Up_Layer;
//class UI_Secondary_Instance_Layer;
//class UI_Role_Quality_Up;
class UI_Daily_Mission;
//class UI_Item_Combine_Layer;
//class UI_Residual_Page_Layer;
//class UI_Skill_Icon_Info_Layer;
class UI_New_Function_Open;
//class UI_Sweep_Desc_Layer;
class UI_Trade_Layer;
class UI_Activity_Six_Sect_Layer;

class Joiner_Guidance;
class UI_MainMenu_Layer : public cocos2d::Layer
{
public:
	enum 
	{
		TAG_MENU = 50,
		ROLE_LAYER,
		BAG_LAYER,
		SOCIAL_LAYER,
		SKILL_LAYER,
		EQUIPMENT_LAYER,
		CHAT_LAYER,
		MISSION_LAYER,
		INSTANCE_LAYER,
		SETTLEMENT_LAYER,
		DIALOGUE_LAYER,
		SHOP_LAYER,
		ALL_SETTING,
		RANK_LIST_LAYER,
		ARENA_LAYER,
		FRAGMENT_LAYER,
		FATE_LAYER,
		EXCHANGE_LAYER,
		BANKS_LAYER,
		LOGIN_AWARD_LAYER,
		MISSION_DIALOGUE_LAYER,
		MAX_LAYER,
	};
	enum FunctionalType
	{
		FT_SystemSetting=0,
		//FT_Billboard,
//		FT_Relationship,
		FT_Skill,
		FT_Bag,
		FT_Property,
//		FT_Fate,
//		FT_Refine,
		FT_Pet,
		FT_God,
//		FT_Pan,
		FT_Num
	};
	
	enum Campaign
	{
		cEndless = 0,
		//cRob,
//		cBoss,
		cNum
	};

	enum Sports
	{
		sArena = 0,
		//sParty,
		sNum
	};
public:
/*========================================= dely =====================================*/
	CC_SYNTHESIZE_READONLY(cocos2d::ui::Widget*,root,Root);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, propertyBtn, PropertyBtn);
	cocos2d::ui::Button* bagBtn;
	cocos2d::ui::Button* missionBtn;
	//SneakyJoystick *joyStick;
	CC_SYNTHESIZE_READONLY(SneakyJoystick*, joyStick, JoyStick);
	void onClickTitleCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onClickBossCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onClickFateCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onClickArenaCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onClickPropertyCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onClickTaskCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onClickPetCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onClickRobCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onClickStarCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

/*========================================= dely =====================================*/
	UI_MainMenu_Layer(void);
	~UI_MainMenu_Layer(void);

	virtual bool init();
	void onEnter()override;
	CREATE_FUNC(UI_MainMenu_Layer);


	void showGuide();
	void setToggleState(int state);
	int getToggleState();

public:
	void HideAllWindow();
	void showNpcDialogue( int nNpcID );
	void openPropertyCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);
	void buttonMainRoleInfo( Ref* pSender ,Widget::TouchEventType type);
	void buttonBagInfo( Ref* pSender ,Widget::TouchEventType type);
	void buttonSkillInfo( Ref* pSender ,Widget::TouchEventType type);
	void buttonHeartMethod( Ref* pSender ,Widget::TouchEventType type);
	void buttonMission( Ref* pSender ,Widget::TouchEventType type);
	void buttonEquipment( Ref* pSender ,Widget::TouchEventType type);
	void buttonSetting( Ref* pSender ,Widget::TouchEventType type);
	void buttonRankingList(Ref* pSender, Widget::TouchEventType type);
	void buttonAssist(Ref* pSender, Widget::TouchEventType type);
	void buttonReward(Ref* pSender, Widget::TouchEventType type);
	void buttonSign(Ref* pSender, Widget::TouchEventType type);

	void buttonSocialActivity( Ref* pSender,Widget::TouchEventType type );					// 点击社交按钮回调
	void buttonCompetition( Ref* pSender,Widget::TouchEventType type );
	void buttonFragment( Ref* pSender ,Widget::TouchEventType type);
	void buttonFate( Ref* pSender ,Widget::TouchEventType type);
	void buttonExchangeCode( Ref* pSender ,Widget::TouchEventType type);
	void buttonBanks( Ref* pSender ,Widget::TouchEventType type);
	void btnShoppingCenter( Ref* pSender,Widget::TouchEventType type );
	void btnPayMoneyCallback( Ref* pSender ,Widget::TouchEventType type);
	void btnActivityCallback(Ref* pSender, Widget::TouchEventType type);

//	virtual void keyBackClicked(void);
	void buttonPathFinding( Ref* pSender,Widget::TouchEventType type );
	void refreshFindWay();
	void buttonChatBoard( Ref* pSender ,Widget::TouchEventType type);

	void caculateOpenNumFunc();
	void openToggleGuide( float dt );
	void closeToggleGuide();
	void toggleFunctionalBtns(Ref* pSender, Widget::TouchEventType type);
	void campaignToggle(Ref* pSender, Widget::TouchEventType type);
	void sportsToggle(Ref* pSender, Widget::TouchEventType type);
	void addGoldCallback( Ref* pSender ,Widget::TouchEventType type);
	void addStrengthCallback( Ref* pSender ,Widget::TouchEventType type);

	void buttonAreaInstance();
	void buttonInstanceDes(int instance_id);

    static bool update_main_ui_info(const Game_Logic::Game_Event& gm_evt);
    static bool update_item_ui_info(const Game_Logic::Game_Event& gm_evt);
    static bool update_skill(const Game_Logic::Game_Event& gm_evt);
    static bool update_instance_stage(const Game_Logic::Game_Event& gm_evt);
    static bool update_stage(const Game_Logic::Game_Event& gm_evt);
	static bool update_mission_dialog(const Game_Logic::Game_Event& gm_evt);
    static bool update_stage_all(const Game_Logic::Game_Event& gm_evt);
    static bool update_friend_list(const Game_Logic::Game_Event& gm_evt);
    static bool update_friend_detail(const Game_Logic::Game_Event& gm_evt);
    static bool update_arena(const Game_Logic::Game_Event& gm_evt);
    static bool update_count_down_time(const Game_Logic::Game_Event& gm_evt);
    static bool update_npc_dialog(const Game_Logic::Game_Event& gm_evt);
//    static bool update_role_quality_up(const Game_Logic::Game_Event& gm_evt);
//    static bool update_compound_fragment(const Game_Logic::Game_Event& gm_evt);
    static bool update_fate(const Game_Logic::Game_Event& gm_evt);
    static bool update_banks(const Game_Logic::Game_Event& gm_evt);
    static bool update_rank(const Game_Logic::Game_Event& gm_evt);
    static bool update_login_award(const Game_Logic::Game_Event& gm_evt);
    static bool update_instance_sweep(const Game_Logic::Game_Event& gm_evt);
    static bool update_gem_inlay(const Game_Logic::Game_Event& gm_evt);
    static bool update_operate_gem(const Game_Logic::Game_Event& gm_evt);
    static bool update_gem_level_up(const Game_Logic::Game_Event& gm_evt);
    static bool update_shop(const Game_Logic::Game_Event& gm_evt);
    static bool update_daily_task(const Game_Logic::Game_Event& gm_evt);
	/************************ dely *********************/
	static bool update_chat(const Game_Logic::Game_Event& gm_evt);	
	/************************ dely *********************/
	void RefreshMainUIInfo();														  // 刷新主界面上UI信息

	//二级界面显示函数
	void visibleHeartMethodCombine(int character_id);   //心法合成界面
	void visibleHeartMethodQualityUp(uint64 item_id);  //心法升品界面
	void visibleEquipmentQualityUp(uint64 item_id);    //装备升品界面
	void visibleSecondaryInstance(int area_id);		//副本小地图界面
	void visibleRoleQualityUp();
	void visibleExchange();
	void visibleLoginAward();
	void visibleDailyMission();			//每日任务界面
//	void visibleFragmentCombine();		//碎片合成界面
//	void visibleResidualPage();			//残页界面
	void visibleSkillUpLayer( bool visible, int skillId = 0, int characterId=0 );			//招式升级界面
	void visibleFuncOpen( int iconNameId, int iconOpenId  );
	void visibleSweepDescLayer(int ui_instance_elite);
	void visibleEquipmentInlayLayer();
	void visibleEquipmentGemCombine();
	void visibleTradeLayer( uint64 goods_id, int style );
	void visibleActivityEnterLayer( Ref* pSender,Widget::TouchEventType type );

	void addChatContent(const char* szChatContent, int channel=CHAT_CHANNEL_WORLD, const char* sender="", const char* receiver="");
	void privateChatFromRelationList(const char* receiver);

	static UI_MainMenu_Layer* get_instance();

	void quest_show_bag(int item_base_id);
	void quest_show_skill(int skill_base_id);
	void quest_show_equipment(int item_base_id);
	void quest_show_book_bag(int item_base_id);
	void show_arena();
	
private:
	void move_to_accept_quest_npc();
	void move_to_quest_npc();

public:
	void refresh_accept_quest_show();
	void refresh_quest_show();

	void SendAllSubmitableQuest();
private:
	void reg_event_update_ui(const char* cmd,const Game_Logic::game_event_handler_t handle,unsigned int owner_type);
	void remove_event_update_ui(unsigned int owner_type);

private:
	cocos2d::ui::ImageView*		m_pRoleHeadBkg;
	cocos2d::ui::ImageView*		_headImg;
	cocos2d::ui::Widget*		_rootWidget;
	cocos2d::ui::ImageView*		_titleImg;
	//cocos2d::ui::Button*		_bossBtn;
	//cocos2d::ui::Button*		_fateBtn;
	//cocos2d::ui::Button*		_arenaBtn;
	//cocos2d::ui::Button*		_propertyBtn;
	cocos2d::ui::Button*		_tryonceBtn;
//	UI_Role_Info_Layer*					m_pRoleInfo;
	UI_Bag_Info_Layer*					m_pBagInfo;
	UI_Skill_Layer*						m_pSkillInfo;
//	UI_Instance_Layer*					m_pAreaInstance;
//	UI_HeartMethod_Layer*				m_pHeartMethod;
	UI_Mission_Layer*					m_pMission;
	UI_Arena_Layer*						m_pArena;
	UI_Material_Fragment_Layer*		    m_pMaterialFragment;
	UI_Fate_Layer*						m_pFateLayer;

	//UI_Instance_Describe_Layer*			m_pInstanceDes;
	/***************************** dely *****************************/
public:
	UI_Equipment_Strengthen_Layer*      m_pEquipmentStrenthen;
	UI_Equipment_StarUp_Layer*		    m_pEquipmentStarUp;

private:
	/***************************** dely *****************************/
	UI_ChatBoard_Layer*					m_pChatBoard;
	UI_NpcDialogue_Layer*				m_pNpcDialogue;
	#if 1
	UI_MissionDialogue_Layer*			m_pMissionDialogue;
	#endif
	UI_AllSetting_Layer*				m_pAllSetting;
	//UI_Ranking_List_Layer*				m_pRankingList;
	//UI_Social_Activity_Layer*			m_pSocialActivity;
	UI_Public_Announcement*				m_pPublicAnnouncement;
	UI_Exchange_Code_Layer*				m_pExchangeCodeLayer;
	UI_Banks_Layer*						m_pBancksLayer;
	UI_Login_Award_Layer*				m_pLoginAwardLayer;
	UI_Shop_Center_Layer*				m_pShopCenterLayer;
//	UI_Activity_Layer*					m_activity_layer;

	//二级界面
//	UI_HeartMethod_Combine_Layer*		m_pHeartMethodCombineLayer;
//	UI_HeartMethod_Quality_Up_Layer*	m_pHeartMethodQualityUpLayer;
//	UI_Secondary_Instance_Layer*		m_pSecondaryInstanceLayer;
//	UI_Role_Quality_Up*					m_pRoleQualityUpLayer;
	UI_Daily_Mission*					m_pDailyMissionLayer;
//	UI_Item_Combine_Layer*			    m_pItemCombineLayer;
//	UI_Residual_Page_Layer*				m_pResidualPageLayer;
//	UI_Skill_Icon_Info_Layer*			m_pSkillDescLayer;
	UI_New_Function_Open*				m_pFuncOpenLayer;
//	UI_Sweep_Desc_Layer*				m_pSweepDescLayer;
	UI_Trade_Layer*						m_trade_layer;
//	UI_Activity_Six_Sect_Layer*			m_activity_six_sect_layer;
    
    SelectBattleLayer * selBattleLayer;

    
	static UI_MainMenu_Layer*			m_instance_;

	//界面可运动的12个按钮
	cocos2d::ui::Button*					_sports[sNum];
	Vec2									_sportsPosition[sNum];
	Vec2									_sportsDestination;

	cocos2d::ui::Button*					_campaign[cNum];
	Vec2									_campaignPosition[cNum];
	Vec2									_campaignDestination;


	cocos2d::ui::Button*					m_pFunctionalBtn[FT_Num];
	Vec2									m_ptBtnOrigenPos[FT_Num];
	Vec2									m_ptDestinyPos;
	int m_bt_state;							
	int _campaignState = 1;						
	int _sportsState = 1;						

	/**********************************退出对话框 的 确定按钮*************************************************/
	void btnCallBackExit();
	/**********************************************************************************************/

	
	LabelAtlas*				vip_level_label_;
//	ProgressTimer*			m_pPercentVisible;	//经验条
	//cocos2d::Sprite*					m_effect_login_reward;  //特效
    //cocos2d::Sprite*					m_effect_activity;		//特效

	/*******************  指引图标  ********************/
	Joiner_Guidance*			juniorGuide;

	//float					pointPosArray[7][2];	//记录坐标点
	int						m_nOpenActNum;

public:
	//bool						arr[Game_Data::ICON_SUM];				//set button close-or-open state
	int							recordNum;

public:
	//---CoCostudio控件---//
	cocos2d::ui::ImageView*			m_pImgFindWay;		//自动寻路图标
	ui::Text*						m_pLabFindWayFont;					// 自动寻路 

	ui::ImageView*					m_pImgFontShadow;					// 文字阴影
																		   
	ui::Button*						m_pBtnFindPath;						// 自动寻路
	ui::Button*						m_pBtnChatBoard;					// 聊天按钮
	ui::Button*						_emailButton;					// 聊天按钮
	ui::Button*						m_pBtnGiftBag;						// 商城按钮
																		   															   
	ui::TextAtlas*					m_lab_fighting_capacity;			// 战力
																		   
	ui::CheckBox*					m_pBtnToggle;						// 展开图标按钮
	ui::CheckBox*					_sportsDestinationCbx;				// 展开图标按钮
	ui::CheckBox*					_campaignDestinationCbx;			// 展开图标按钮

private:
	enum guide_step
	{
		JUNIOR_GUIDE_STEP_1 = 1,		//clear
		JUNIOR_GUIDE_STEP_4 = 4,
		JUNIOR_GUIDE_STEP_5 = 5,
		JUNIOR_GUIDE_STEP_12 = 12,

		BAG_GUIDE_STEP_0 = 20,			//clear
		BAG_GUIDE_STEP_1 = 21,

		EQUIP_GUIDE_STEP_0 = 40,		//clear
		EQUIP_GUIDE_STEP_1 = 41,

		XF_ASSEMBLE_STEP_0 = 60,		//clear
		XF_ASSEMBLE_STEP_1 = 61,

		XF_EQUIP_GUIDE_STEP_0 = 80,		//clear
		XF_EQUIP_GUIDE_STEP_1 = 81,

		FRAGEMENT_COMB_STEP_0 = 100,	//clear
		FRAGEMENT_COMB_STEP_1 = 101,

		EQUIP_QUA_UP_STEP_0	= 120,		//clear no test
		EQUIP_QUA_UP_STEP_1	= 121,

		SKILL_LEVEL_UP_STEP_0 = 140,	//clear
		SKILL_LEVEL_UP_STEP_1 = 141,

		XF_COMBINE_STEP_0 = 160,		//--(\)no no no
		XF_COMBINE_STEP_1 = 161,

		ARENA_FIGHT_STEP_0 = 180,		// clear no test
		ARENA_FIGHT_STEP_1 = 181,

		ROLE_QUA_UP_STEP_0 = 200,		// clear no test
		ROLE_QUA_UP_STEP_1 = 201,

		ARENA_GET_REWARD_STEP_0 = 220,	// NO
		ARENA_GET_REWARD_STEP_1 = 221,

		LIEUTENANT_FIGHT_STEP_0 = 240,  // ??  --lieutenant fighting
		LIEUTENANT_FIGHT_STEP_1 = 241,

		USE_LIEU_FIGHT_STEP_0 = 260,	// NO  --use lieutenant fighting
		USE_LIEU_FIGHT_STEP_1 = 261,

		FATE_LEVEL_UP_STEP_0 = 280,		// clear no test
		FATE_LEVEL_UP_STEP_1 = 281,

		XF_QUA_UP_STEP_0 = 300,			// clear no test
		XF_QUA_UP_STEP_1 = 301,
	};
public:
    static std::map<int, std::map<std::string, GuideData>> levelGuide;
    static int oldLevel;
    static bool showMissionFinish;
    cocos2d::Sprite *tipBg;
    cocos2d::Label *tipLabel;
    void hidePop();
    void popTip(std::string content);
	/*====================================   dely   ====================================*/
private:
	void initJoystick();
public:
	void hideCampaign(int index);
	void hideButtons(int index);
	void hideSports(int index);
	//---无尽塔相关方法---//
	void btnEndlessTowerCallback(Ref* pSender, Widget::TouchEventType type);								// 无尽塔按钮点击回调
	void SendMsgRequestChallengeEndlessTower();																// 发送消息请求挑战无尽塔
};
#endif //_UI_BUTTON_LAYER_
