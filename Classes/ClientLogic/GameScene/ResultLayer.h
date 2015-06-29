#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Game_Interface/common.h"

#define CARD_NUM 4

USING_NS_CC;

namespace Game_Logic
{
	struct Game_Interface;
	struct Game_Event;
}

class ResultLayer : public cocos2d :: Layer
{
public:
	/** ==================================== Datas ==================================== */
	/*static std::map<int,int> sItemMap;
	static std::map<int,int> sCountMap;
	static std::vector<int> sItemVec;
	static std::vector<int> sCountVec;*/
	static int sCurInstanceId;
	static int sMoney;
	static int sExp;
	static int sUpWhere;
	static int sDownWhere;
	static int sTemp;

	static int sClickTimes;
	static Value sWinOrLose;
	static Value sName;
	static Value sPower;

	static Value sHP;
	static Value sAtk;
	static Value sGuard;
	static Value sMP;
	static Value sLevel;
	static Value sJob;
	static Value sJobStrings[];
	/** ==================================== Datas ==================================== */

	/** ==================================== members ==================================== */
	CC_SYNTHESIZE_READONLY(cocos2d::ui::Text*, nameTxt, NameTxt);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, powerAtlas, PowerAtlas);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, hpAtlas, HpAtlas);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, atkAtlas, AtkAtlas);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, guardAtlas, GuardAtlas);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, mpAtlas, MpAtlas);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, levelAtlas, LevelAtlas);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::Text*, jobTxt, JobTxt);

	CC_SYNTHESIZE_READONLY(cocos2d::ui::Widget*,root,Root);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, closeBtn, CloseBtn);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, nextBtn, NextBtn);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, backBtn, BackBtn);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, expAts, ExpAts);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::ImageView*, money_icon, Money_icon);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, money, Money);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::ImageView*, money_icon1, Money_icon1);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, money1, Money1);
	CC_SYNTHESIZE_READONLY(cocos2d::ui::TextAtlas*, times, Times);
   
    CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, againBtn, AgainBtn);
    CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, back2CityBtn, Back2CityBtn);
	
	cocos2d::ui::Layout* _adapterLayout;
	cocos2d::ui::Button* upCards[CARD_NUM];
	cocos2d::ui::Button* downCards[CARD_NUM];
	cocos2d::Sprite*     _upSprites[CARD_NUM];
	cocos2d::Sprite*     _downSprites[CARD_NUM];
	Sequence*			 _effectUpSequences[CARD_NUM];
	Sequence*			 _effectDownSequences[CARD_NUM];

	vector<uint64> itemIds;
	/** ==================================== members ==================================== */

	/** ==================================== Callbacks ==================================== */
	void eventBackMainCity();

	void upCardsCallback2(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);

	void nextCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);

	void backCallback(cocos2d::Ref*pSender, cocos2d::ui::Widget::TouchEventType type);

	void hideEffect( int index);

	static bool waiting(Game_Logic::Game_Interface& gm_interface);

    void popResult();

	static bool sendNext();//send get awards packet after click next button 

//	static bool onReceivedNext(Game_Logic::Game_Interface& gm_interface);//on received get awards packet

	static bool	NextInstanceDataBeenReceived(Game_Logic::Game_Interface& gm_interface);							// 下一个副本数据已经被接收

	virtual void onExit();

	bool initUpCards();

	bool initData();

	bool initRoot();

	virtual bool init();

	CREATE_FUNC(ResultLayer);

    LayerColor *waitLayer;
};

