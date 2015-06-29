#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "../FightDefine.h"
#include "../Actor/Hero.h"
#include "../SneakyJoy/SneakyJoyStick.h"
#include "../Actor/YNCamera.h"
#include "ActorLayer.h"
#include "ui/CocosGUI.h"
#include "../LoadScene/LoadScene.h"
#include "DataModule/BattleField.h"
#include "SelectBattleLayer.h"
#include "Dialogue_System/Dialogue_Client.h"

#include "ResultLayer.h"

class GameScene : public cocos2d::Scene
{
public:
	~GameScene();
	bool init();
    void onExit();
    
	CREATE_FUNC(GameScene);

	void update(float delta);

	/**
     *	@brief	根据camera位置，设定各层的位移，实现镜头定位
     *
     */
    void setViewWindow();

    void touchAttackEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchSkill1Event(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchSkill2Event(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchSkill3Event(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchSPEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchJumpEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchExitButton(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchSkillYEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
 
    int decodeJoyStick(float delta);
//    bool skillDown(cocos2d::Touch*, cocos2d::Event*);
//    void skillUp(cocos2d::Touch*, cocos2d::Event*);
//    void skillCancel(cocos2d::Touch*, cocos2d::Event*);
	/**
     *	@brief	按下攻击键的响应
     *
     *	@param 	cocos2d::Touch*
     *	@param 	cocos2d::Event*
     *
     *	@return	bool
     */
    bool attackDown(cocos2d::Touch*, cocos2d::Event*);

	//void attackMove(cocos2d::Touch*, cocos2d::Event*);
    
	/**
     *	@brief	抬起攻击键的响应
     *
     *	@param 	cocos2d::Touch*
     *	@param 	cocos2d::Event*
     */
    void attackUp(cocos2d::Touch*, cocos2d::Event*);

	/**
     *	@brief	取消攻击键的响应
     *
     *	@param 	cocos2d::Touch*
     *	@param 	cocos2d::Event*
     */
    void attackCancel(cocos2d::Touch*, cocos2d::Event*);
    
    void load(float dt);
    void enterGame();
    
    void sendMonster2Scene(std::vector<mon> mons);
    void getNextTeam(cocos2d::EventCustom* event);
    void getDeadTeam(cocos2d::EventCustom* event);
    void sendTeam2Scene(MonsterTeam *team);
    void monsterLogicDie(cocos2d::EventCustom* event);
    
    void popSelStage();
    
    static void updateHp(int curHp,int maxHp);
    static void updateMp(int curMp,int maxMp);
    static void updateAp(int currAp, int currAv, int maxAv);
    static void addAp(int val, int currAp);
    static void updateGhost(int currGhost, int maxGhost);
    
    void showMonster();
    
    void addSceneEffect(std::string groupName, Node *parent, bool alignTop);
    
    void showLinkBar(int btnTag, std::string iconName, float duration);
    void hideLinkBar(int btnTag, std::string iconName, float cd);
    static void changeCombo();
    
    FightActor * m_pCurrentMonster;
    bool m_bTestValue;
    void initWithHpShow();								 // 初始化血量展示的成员变量
    void showMonsterHp(FightActor * pMonster);			 // 显示当前怪物的Hp

    
    void skillACDClock(float dt);
//    void skillBCDClock(float dt);
//    void skillCCDClock(float dt);
//    void skillDCDClock(float dt);
    
    void runOut(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    
    void popTip(std::string content);
    void hidePop();
    
    void resetGameMode(int nextMode);
    bool enterGameMode(int next);
    void exitGameMode(int currMode);
    static int gameMode;
    static int cacheGameMode;
private:
    
    
    SelectBattleLayer *selBattleLayer;
    LoadScene *loadLayer;
    ResultLayer *resultLayer;
    int loadCount;
	CC_SYNTHESIZE_READONLY(cocos2d::Layer*, backLayer, BackLayer);
	CC_SYNTHESIZE_READONLY(cocos2d::Layer*, midLayer, MidLayer);
	CC_SYNTHESIZE_READONLY(ActorLayer*, actorLayer, ActorLayer);
	CC_SYNTHESIZE_READONLY(cocos2d::Layer*, frontLayer, FrontLayer);
    CC_SYNTHESIZE_READONLY(cocos2d::Layer*, weather, WeatherLayer);
	CC_SYNTHESIZE_READONLY(cocos2d::Layer*, uiLayer, UiLayer);
    CC_SYNTHESIZE_READONLY(cocos2d::LayerColor *, flashLayer, FlashLayer);
    CC_SYNTHESIZE_READONLY(cocos2d::Layer *, scrFrtLayer, scrFrtLayer);
    CC_SYNTHESIZE_READONLY(cocos2d::Layer *, goalLayer, goalLayer);

    CC_SYNTHESIZE(bool, firstPass, FirstPass);
    cocos2d::ui::Button *attackBtn_A;
    cocos2d::ui::Button *skillBtn_A;
    cocos2d::Sprite *skillALinkBg;
    cocos2d::ui::Button *skillBtn_B;
    cocos2d::Sprite *skillBLinkBg;
    cocos2d::ui::Button *skillBtn_C;
    cocos2d::Sprite *skillCLinkBg;
    cocos2d::ui::Button *spSkillBtn;
    cocos2d::ui::Button *jumpBtn;
    cocos2d::Sprite *skillDLinkBg;
    cocos2d::ui::Button *exitBtn;
	cocos2d::Sprite *attckBtn;
    cocos2d::Sprite *attckBtnB;
    cocos2d::LabelAtlas *comboNum;
    static cocos2d::LabelAtlas *comboNum1;
    cocos2d::Sprite *comboBack;
    cocos2d::Sprite *comboLabel;
    cocos2d::ui::LoadingBar* monsterHpBar;
    cocos2d::ui::LoadingBar* monsterHpBGBar;
    cocos2d::ui::ImageView* monsterHpBg;
    cocos2d::ui::Button *skillBtn_Y;
//    cocos2d::ui::LoadingBar *angryProg;
//    cocos2d::ui::ImageView *apBoard[4];
    
    float        _time0, _time1, _time2, _time3, _time4;
//    cocos2d::ProgressTimer *timeLeft;
    cocos2d::ui::TextAtlas *skillAClock;
    cocos2d::ui::TextAtlas *skillBClock;
    cocos2d::ui::TextAtlas *skillCClock;
    cocos2d::ui::TextAtlas *skillDClock;
    
	//HRocker *joyStick;
	SneakyJoystick *joyStick;
    bool pressJoy;
    bool pressJoy1;
    int lastDir;
    float pressDur[2];
    float releaseDur;
    int rushPart;
    int rushCmd;
    int lastRushCmd;
    
    
	Hero *hero;
	YNCamera *camera;
	cocos2d::Sprite *bgSpt;
    BattleField *battle;
    cocos2d::EventListenerCustom *nextTeamListener;
    cocos2d::EventListenerCustom *monsterDyingListener;
    cocos2d::EventListenerCustom *deadTeamListener;
//    cocos2d::EventListenerCustom *selStageListener;
    
    int joyDir[8];
	/* ================================= dely =====================================*/
	cocos2d::Layer* backDialogue;
	CC_SYNTHESIZE_READONLY(cocos2d::Layer*, rstLayer, RstLayer);
    
    //void refreshHpAndMp(float dt);
//    static float myHp;
//    static float myMp;
    static cocos2d::ui::Text* hp_num;
    static cocos2d::ui::Text* mp_num;
    static cocos2d::ui::LoadingBar* hpBar;
    static cocos2d::ui::LoadingBar* hpBGBar;
    static cocos2d::ui::LoadingBar* mpBar;
//    static cocos2d::ui::LoadingBar* avBar;
    static cocos2d::ui::ImageView* apBg[4];
    static cocostudio::Armature* apFire[4];
//    static cocos2d::ui::ImageView *ghostProg;
    static cocos2d::ProgressTimer* ghostProg;
    enum SendType
    {
        normal, guard,suvival, count, hp, boss
    };
    int _sendType = normal;
    
    bool updateSendByType(int type, float delta);
    
    long _firstTime;
    float _currentTime;
    long _lastTime;
    int	 _limitTime;
    cocos2d::ui::TextAtlas* _showTimeRed = nullptr;
    cocos2d::ui::TextAtlas* _showTimeGreen = nullptr;
    
    int _currentCount;
    int _limitCount;
    cocos2d::ui::TextAtlas* _showCountRed = nullptr;
    cocos2d::ui::TextAtlas* _showCountGreen = nullptr;
    
    int _limitHp;
    cocos2d::ui::Text* _showPreRed = nullptr;
    cocos2d::ui::TextAtlas* _showHpRed = nullptr;
    cocos2d::ui::Text* _showSuffRed = nullptr;
    
    void showOrHideDialogue(bool showOrHide);
    std::vector<Game_Model::Line> _lines;
    bool _isFirst = true;
    bool _changeShowState = false;
    bool _showOrHide = false;
    DIALOGUE_VIEW*          _rootDialogue;
    cocos2d::ui::ImageView* _leftHeadImage;
    cocos2d::ui::ImageView* _rightHeadImage;
    cocos2d::ui::Text*      _contentText;
    /* ================================= dely =====================================*/
    
    cocos2d::Sprite *tipBg;
    cocos2d::Label *tipLabel;
};