#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "../Game_Interface/game_content_interface.h"

#include "Faction_data.h"

USING_NS_CC;

//model
namespace Game_Model
{
	class Faction_Data
	{
	private:
		//main page
		bool											   m_bIsJoined = false;
		//bool											   m_bIsJoined = true;

		bool											   m_bIsSignedToday = false;
		//bool											   m_bIsSignedToday = true;

		std::string										   m_sName = "default";
		int												   m_nNum = 0;
		int												   m_nLevel = 0;
		int												   m_nExp = 0;
		std::string										   m_sNotice = "Pay attention please!";


		int												   m_nLevelLimit = 0;
		int												   m_nCoin = 0;
		int												   m_nToken = 0;

		//totem page
		int												   m_nActiveNum = 0;

		int												   m_nLife = 0;
		int												   m_nAttack = 0;
		int												   m_nDefense = 0;
		int												   m_nWind = 0;
		int												   m_nFire = 0;
		int												   m_nThunder = 0;
		int												   m_nCurTotemType = 0;

		std::vector<faction_member_data>				   m_vMembers;
		int												   m_nOwnerId;
		int												   m_nPowerLimit;
		
		int												   m_nJob;
		int												   m_nCurSelectJobId = -1;
		int												   m_nCurSelectMemberId = -1;
		int												   m_nCurSelectDonateId = -1;

		int												   m_nDigCurTimes = 0;
		int												   m_nDigTotalTimes = 0;
		int												   m_nWorshipCurTimes = 0;
		int												   m_nWorshipTotalTimes = 0;
	public:
		faction_data_DB faction_db;
		bool init();

		static Faction_Data* getInstance();

		inline bool			 isJoined()					     { return m_bIsJoined; };
		inline void			 setJoined(bool bJoined)         { m_bIsJoined = bJoined; };

		inline bool			 isSignedToday()			     { return m_bIsSignedToday; };
		inline void			 setSignedToday(bool bSigned)    { m_bIsSignedToday = bSigned; };

		inline std::string	 getName()					     { return m_sName; };
		inline void			 setName(std::string sName)      { m_sName = sName; };

		inline int			 getNum()					     { return m_nNum; };
		inline void			 setNum(int nNum)			     { m_nNum = nNum; };

		inline int			 getLevel()					     { return m_nLevel; };
		inline void			 setLevel(int nLevel)		     { m_nLevel = nLevel; };

		inline int			 getExp()					     { return m_nExp; };
		inline void			 setExp(int nExp)				 { m_nExp = nExp; };

		inline std::string	 getNotice()				     { return m_sNotice; };
		inline void			 setNotice(std::string sNotice)  { m_sNotice = sNotice; };

		inline int			 getLevelLimit()				 { return m_nLevelLimit; };
		inline void			 setLevelLimit(int nLevel)		 { m_nLevelLimit = nLevel; };

		inline int			 getCoin()						 { return m_nCoin; };
		inline void			 setCoin(int nCoin)				 { m_nCoin = nCoin; };

		inline int			 getToken()						 { return m_nToken; };
		inline void			 setToken(int nToken)			 { m_nToken = nToken; };

		inline int			 getActive()					 { return m_nActiveNum; };
		inline void			 setActive(int nActive)			 { m_nActiveNum = nActive; };
		
		inline void			 setLife(int nLife)				 { m_nLife = nLife; };
		inline int			 getLife()						 { return m_nLife; };

		inline void			 setAttack(int nAttack)			 { m_nAttack = nAttack; };
		inline int			 getAttack()					 { return m_nAttack; };

		inline void			 setDefense(int nDefense)		 { m_nDefense = nDefense; };
		inline int			 getDefense()					 { return m_nDefense; };

		inline void			 setWind(int nWind)				 { m_nWind = nWind; };
		inline int			 getWind()						 { return m_nWind; };

		inline void			 setFire(int nFire)				 { m_nFire = nFire; };
		inline int			 getFire()						 { return m_nFire; };

		inline void			 setThunder(int nThunder)		 { m_nThunder = nThunder; };
		inline int			 getThunder()					 { return m_nThunder; };

		inline void			 setCurTotemType(int nType)		 { m_nCurTotemType = nType; };
		inline int			 getCurTotemType()				 { return m_nCurTotemType; };

		inline void			 setMembers(std::vector<faction_member_data> para){ m_vMembers = para; };
		inline std::vector<faction_member_data>getMembers()				   { return m_vMembers; };

		inline void			 setOwnerId(int nOwnerId)		 { m_nOwnerId = nOwnerId; };
		inline int			 getOwnerId()					 { return m_nOwnerId; };

		inline void			 setPowerLimit(int nPowerLimit)  { m_nPowerLimit = nPowerLimit; };
		inline int			 getPowerLimit()			     { return m_nPowerLimit; };

		inline void			 setJob(int nJob)				 { m_nJob = nJob; };
		inline int			 getJob()						 { return m_nJob; };

		inline void			 setCurSelectMemberId(int nId)	 { m_nCurSelectMemberId = nId; };
		inline int			 getCurSelectMemberId()			 { return m_nCurSelectMemberId; };
		
		inline void			 setCurSelectJobId(int nId)		 { m_nCurSelectJobId = nId; };
		inline int			 getCurSelectJobId()			 { return m_nCurSelectJobId; };
		
		inline void			 setCurSelectDonateId(int nId)	 { m_nCurSelectDonateId = nId; };
		inline int			 getCurSelectDonateId()			 { return m_nCurSelectDonateId; };
		
		inline void			 setDigCurTime(int nTime)	 { m_nDigCurTimes = nTime; };
		inline int			 getDigCurTime()			 { return m_nDigCurTimes; };

		inline void			 setDigTotalTime(int nTime)	 { m_nDigTotalTimes = nTime; };
		inline int			 getDigTotalTime()			 { return m_nDigTotalTimes; };

		inline void			 setWorshipCurTime(int nTime)	 { m_nWorshipCurTimes = nTime; };
		inline int			 getWorshipCurTime()			 { return m_nWorshipCurTimes; };

		inline void			 setWorshipTotalTime(int nTime)	 { m_nWorshipTotalTimes = nTime; };
		inline int			 getWorshipTotalTime()			 { return m_nWorshipTotalTimes; };

	};

	struct Faction_Create_Needed
	{
		//condition needed
		int												   m_nLevelLimit = 0;
		int												   m_nCoin  = 0;
		int												   m_nToken = 0;

		inline int			 getLevel()			 { return m_nLevelLimit; };
		inline void			 setLevel(int nLevel){ m_nLevelLimit = nLevel; };

		inline int			 getCoin()			 { return m_nCoin; };
		inline void			 setCoin(int nCoin)  { m_nCoin = nCoin; };

		inline int			 getToken()			 { return m_nToken; };
		inline void			 setToken(int nToken){ m_nToken = nToken; };

	};

	struct Faction_Boss_Data
	{
	private:
		int					m_nBossId = 1;

		int					m_nOneLevel = 1;
		int					m_nOneValue = 0;//贡献度

		int					m_nTwoLevel = 1;
		int					m_nTwoValue = 0;//贡献度

		int					m_nThreeLevel = 1;
		int					m_nThreeValue = 0;//贡献度

		int					m_nFourLevel = 1;
		int					m_nFourValue = 0;//贡献度

		int					m_nBuffId = 1;
		int					m_nBuffConsum = 0;
		int					m_nCurTimes = 0;
		int					m_nTotalTimes = 0;
		int					m_nActive = 0;
		int					m_nContribute = 0;
	public:

		static Faction_Boss_Data* getInstance();

		inline int			 getBossId()			   { return m_nBossId; };
		inline void			 setBossId(int nBossId)	   { m_nBossId = nBossId; };

		inline int			 getOneLevel()			   { return m_nOneLevel; };
		inline void			 setOneLevel(int nOneLevel){ m_nOneLevel = nOneLevel; };

		inline int			 getOneValue()			   { return m_nOneValue; };
		inline void			 setOneValue(int nOneValue){ m_nOneValue = nOneValue; };

		inline int			 getTwoLevel()			   { return m_nTwoLevel; };
		inline void			 setTwoLevel(int nTwoLevel){ m_nTwoLevel = nTwoLevel; };

		inline int			 getTwoValue()			   { return m_nTwoValue; };
		inline void			 setTwoValue(int nTwoValue){ m_nTwoValue = nTwoValue; };

		inline int			 getThreeLevel()			   { return m_nThreeLevel; };
		inline void			 setThreeLevel(int nThreeLevel){ m_nThreeLevel = nThreeLevel; };

		inline int			 getThreeValue()			   { return m_nThreeValue; };
		inline void			 setThreeValue(int nThreeValue){ m_nThreeValue = nThreeValue; };

		inline int			 getFourLevel()			     { return m_nFourLevel; };
		inline void			 setFourLevel(int nFourLevel){ m_nFourLevel = nFourLevel; };

		inline int			 getFourValue()			     { return m_nFourValue; };
		inline void			 setFourValue(int nFourValue){ m_nFourValue = nFourValue; };


		inline int			 getBuffId()			     { return m_nBuffId; };
		inline void			 setBuffId(int nBuffId)		 { m_nBuffId = nBuffId; };

		inline int			 getBuffConsum()			 { return m_nBuffConsum; };
		inline void			 setBuffConsum(int nConsum)	 { m_nBuffConsum = nConsum; };

		inline int			 getCurTimes()			     { return m_nCurTimes; };
		inline void			 setCurTimes(int nTime)		 { m_nCurTimes = nTime; };

		inline int			 getTotalTimes()			     { return m_nTotalTimes; };
		inline void			 setTotalTimes(int nTime)		 { m_nTotalTimes = nTime; };

		inline int			 getActive()					 { return m_nActive; };
		inline void			 setActive(int nActive)			 { m_nActive = nActive; };

		inline int			 getContribute()			     { return m_nContribute; };
		inline void			 setContribute(int nContribute)	 { m_nContribute = nContribute; };

	};

};
typedef Game_Model::Faction_Data FACTION_MODEL;
typedef Game_Model::Faction_Create_Needed FACTION_CONDITION_MODEL;
typedef Game_Model::Faction_Boss_Data FACTION_BOSS_MODEL;

//view
#define EVENT_FACTION_CREATE_SUCCESS "event_faction_create_success"

#define EVENT_FACTION_CREATE_FAILED "event_faction_create_failed"

#define EVENT_REOPEN_FACTION "event_reopen_faction"

#define EVENT_REFRESH_FACTION "event_refresh_faction"

#define EVENT_REFRESH_BOSS "event_refresh_boss"

#define EVENT_REFRESH_WORSHIP "event_refresh_worship"

#define EVENT_REFRESH_DIG "event_refresh_dig"

#define EVENT_REFRESH_BOARD "event_refresh_board"



namespace Game_View
{
	class FactionLayer : public cocos2d::Layer
	{
	private:
		//cocos2d::ui::Widget*							   m_pRoot;

	public:

		void											   eventReopen(EventCustom* evt);
		void											   event_create_faction_success(EventCustom* evt);

		void											   onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

		virtual void									   onEnter() override;
		virtual void									   onExit()  override;
		virtual bool									   init()    override;

		CREATE_FUNC(FactionLayer);

	};

	class FactionMainLayer : public cocos2d::Layer
	{
	private:
		cocos2d::ui::Widget*							   m_pRoot;

		cocos2d::ui::Widget*							   m_pBossRoot;

		cocos2d::ui::Widget*							   m_pWorshipRoot;

		cocos2d::ui::Widget*							   m_pMemberRoot;
		cocos2d::ui::Widget*							   m_pRejobRoot;
		cocos2d::ui::Widget*							   m_pDonateRoot;

		cocos2d::ui::Widget*							   m_pMineRoot;

	public:
		void onClickRenotice(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

		void onClickSign(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickConfirmSign(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

		void onClickBoss(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickOne(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickTwo(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickThree(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickFour(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickBuff1(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickBuff2(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickBuff3(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickBuff4(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickWish(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickChallenge(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void eventRefreshBoss(EventCustom* evt);
		void delayRefreshBoss(float dt);
		void onCloseBoss(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

		void onClickWorship(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickWorshipCell(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickMemberWorship(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);	
		void eventRefreshWorship(EventCustom* evt);
		void delayRefreshWorship(float dt);
		void onCloseWorship(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

		void onClickDig(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickConfirmDig(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void eventRefressDig(EventCustom* evt);
		void delayRefreshDig(float dt);
		void onCloseDig(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

		void onClickTotem(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickAttackUp(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickDefenceUp(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickLifeUp(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickWindUp(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickFireUp(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickThunderUp(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onCloseTotem(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

		void onClickMember(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickCell(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickRejob(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onSelectHead(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);
		void onSelectAssist(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);
		void onSelectMember(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);
		void onClickConfirmRejob(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickDonate(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onSelectOne(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);
		void onSelectTwo(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);
		void onSelectFive(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);
		void onClickConfirmDonate(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickExit(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onClickKick(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onCloseFrame(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void onCloseMember(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

		virtual void									  onEnter() override;
		virtual void									  onExit()  override;
		virtual bool									  init()    override;
		FactionMainLayer();
		~FactionMainLayer();
		CREATE_FUNC(FactionMainLayer);

		void											   eventRefresh(EventCustom* evt);
		void											   eventRefreshBoard(EventCustom* evt);

	};

	class FactionApplyLayer : public cocos2d::Layer
	{
	private:
		cocos2d::ui::Widget*							  m_pApplyRoot;
		cocos2d::ui::Widget*							  m_pFrame;
	public:

		//void on_create_faction_failed(EventCustom* evt);

		void onClickButtonJoin(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

		void onClickButtonSearch(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

		void onClickButtonOpenFrame(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

		void onClickButtonCloseFrame(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

		void onClickButtonConditionConfirm(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

		void onClickButtonConditionCancel(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

		void onClickButtonRenameConfirm(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

		void											  eventCallback() ;
		virtual void									  onEnter() override;
		virtual void									  onExit()  override;
		virtual bool									  init()    override;

		CREATE_FUNC(FactionApplyLayer);

	};

};
typedef Game_View::FactionLayer	     FACTION_VIEW;
typedef Game_View::FactionMainLayer  FACTION_MAIN_VIEW;
typedef Game_View::FactionApplyLayer FACTION_APPLY_VIEW;

//controller
namespace Game_Controller
{
	class FactionLogic
	{
	public:	
		bool init();
		static FactionLogic* getInstance();

		inline bool isJoined()			   { return FACTION_MODEL::getInstance()->isJoined(); };
		inline void setJoined(bool bJoined){ FACTION_MODEL::getInstance()->setJoined(bJoined); };

		inline bool isSigned()			   { return FACTION_MODEL::getInstance()->isSignedToday(); };
		inline void setSigned(bool bSigned){ FACTION_MODEL::getInstance()->setSignedToday(bSigned); };

		bool        isCanCreate();

		FACTION_CONDITION_MODEL getCurrentCondition();
		FACTION_CONDITION_MODEL getNeededCondition();

	};

};
typedef Game_Controller::FactionLogic FACTION_CONTROLLER;

//net
#define EVENT_FACTION_SEND_GET_DATA "event_faction_send_get_data"
#define EVENT_FACTION_ON_GET_DATA "event_faction_on_get_data"

#define EVENT_FACTION_SEND_SEARCH "event_faction_send_search"
#define EVENT_FACTION_ON_SEARCH "event_faction_on_search"

#define EVENT_FACTION_SEND_LIMIT "event_faction_send_limit"
#define EVENT_FACTION_ON_LIMIT "event_faction_on_limit"

#define EVENT_FACTION_SEND_CREATE "event_faction_send_create"
#define EVENT_FACTION_ON_CREATE "event_faction_on_create"

#define EVENT_FACTION_SEND_JOIN "event_faction_send_join"
#define EVENT_FACTION_ON_JOIN "event_faction_on_join"

#define EVENT_FACTION_SEND_RENOTICE "event_faction_send_renotice"
#define EVENT_FACTION_ON_RENOTICE "event_faction_on_renotice"

#define EVENT_FACTION_SEND_WISH "event_faction_send_wish"
#define EVENT_FACTION_ON_WISH "event_faction_on_wish"

#define EVENT_FACTION_SEND_CHALLENGE "event_faction_send_challenge"
#define EVENT_FACTION_ON_CHALLENGE "event_faction_on_challenge"

#define EVENT_FACTION_SEND_REJOB "event_faction_send_rejob"
#define EVENT_FACTION_ON_REJOB "event_faction_on_rejob"

#define EVENT_FACTION_SEND_DONATE "event_faction_send_donate"
#define EVENT_FACTION_ON_DONATE "event_faction_on_donate"

#define EVENT_FACTION_SEND_KICK "event_faction_send_kick"
#define EVENT_FACTION_ON_KICK "event_faction_on_kick"

#define EVENT_FACTION_SEND_DIG "event_faction_send_dig"
#define EVENT_FACTION_ON_DIG "event_faction_on_dig"

#define EVENT_FACTION_SEND_TOTEMUP "event_faction_send_totemup"
#define EVENT_FACTION_ON_TOTEMUP "event_faction_on_totemup"

#define EVENT_FACTION_SEND_WORSHIP "event_faction_send_worship"
#define EVENT_FACTION_ON_WORSHIP "event_faction_on_worship"

namespace Game_Net
{
	class FactionMsg
	{
	public:
		bool init();
		static FactionMsg* getInstance();

		static bool send_get_faction_data(Game_Logic::Game_Interface& gm_interface);			// 按名称搜索工会(帮派)
		static bool on_get_faction_data(Game_Logic::Game_Interface& gm_interface);				// 按名称搜索工会(帮派)

		static bool send_faction_search(Game_Logic::Game_Interface& gm_interface);				// 按名称搜索工会(帮派)
		static bool on_faction_search(Game_Logic::Game_Interface& gm_interface);				// 按名称搜索工会(帮派)

		static bool send_faction_join_limit(Game_Logic::Game_Interface& gm_interface);			// 设置加入帮派条件
		static bool on_faction_join_limit(Game_Logic::Game_Interface& gm_interface);			// 设置加入帮派条件

		static bool send_faction_create(Game_Logic::Game_Interface& gm_interface);				// 创建工会(帮派)
		static bool on_faction_create(Game_Logic::Game_Interface& gm_interface);				// 创建工会(帮派)

		static bool send_faction_join(Game_Logic::Game_Interface& gm_interface);				// 加入工会(帮派)
		static bool on_faction_join(Game_Logic::Game_Interface& gm_interface);					// 加入工会(帮派)

		static bool send_faction_set_notice(Game_Logic::Game_Interface& gm_interface);			// 设置帮派公告
		static bool on_faction_set_notice(Game_Logic::Game_Interface& gm_interface);			// 设置帮派公告

		static bool send_faction_kick_member(Game_Logic::Game_Interface& gm_interface);			// 踢人工会(帮派)
		static bool on_faction_kick_member(Game_Logic::Game_Interface& gm_interface);			// 踢人工会(帮派)

		static bool send_faction_set_job(Game_Logic::Game_Interface& gm_interface);				// 设置职位
		static bool on_faction_set_job(Game_Logic::Game_Interface& gm_interface);				// 设置职位

		static bool send_faction_totems_up(Game_Logic::Game_Interface& gm_interface);			// 帮派图腾升级
		static bool on_faction_totems_up(Game_Logic::Game_Interface& gm_interface);			// 帮派图腾升级

		static bool send_faction_member_donation(Game_Logic::Game_Interface& gm_interface);		// 帮派成员捐献

		static bool send_faction_set_msg_board(Game_Logic::Game_Interface& gm_interface);		// 设置留言板

		static bool send_faction_member_digging(Game_Logic::Game_Interface& gm_interface);		// 帮派成员挖矿
		static bool on_faction_member_digging(Game_Logic::Game_Interface& gm_interface);		// 帮派成员挖矿
		// 帮派成员逻辑
		static bool send_faction_member_worship(Game_Logic::Game_Interface& gm_interface);		// 帮派成员膜拜
		static bool on_faction_member_worship(Game_Logic::Game_Interface& gm_interface);		// 帮派成员膜拜

		static bool send_faction_member_dekaron_boos(Game_Logic::Game_Interface& gm_interface);	// 帮派成员挑战BOSS
		static bool on_faction_member_dekaron_boos(Game_Logic::Game_Interface& gm_interface);	// 帮派成员挑战BOSS
		
		static bool send_faction_member_kill_boos(Game_Logic::Game_Interface& gm_interface);	// 帮派成员击杀BOSS
		static bool on_faction_member_kill_boos(Game_Logic::Game_Interface& gm_interface);	// 帮派成员击杀BOSS

		static bool send_faction_member_buy_item(Game_Logic::Game_Interface& gm_interface);		// 帮派成员购买物品
	};

}
typedef Game_Net::FactionMsg FACTION_NET;