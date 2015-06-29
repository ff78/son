#ifndef __UI_ARENA_LAYER__
#define __UI_ARENA_LAYER__

#include "cocos2d.h"
//#include "cocos-ext.h"
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include "ui/UITextField.h"
#include "ui/UILoadingBar.h"
#include "ui/UILayout.h"
#include "ui/UISlider.h"
#include "ui/UICheckBox.h"
#include "ui/UIWidget.h"
#include "ui/UIScrollView.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;
USING_NS_CC;
//USING_NS_CC_EXT;

#ifndef OFFLINEPLAYERNUM
#define OFFLINEPLAYERNUM 5
#endif //OFFLINEPLAYERNUM

#define AWARDGOODSNUM 6
#define OFFLINERESULTITEM 5

class UI_Arena_Layer : public cocos2d::Layer
{
public:
	UI_Arena_Layer(void);
	~UI_Arena_Layer(void);

	virtual bool init();
	virtual void setVisible(bool visible);
	CREATE_FUNC(UI_Arena_Layer);

    void update();
    void update_time(int time);

	static UI_Arena_Layer*		m_pInstance;
public:
	void setTime(int second);
	//UI_Arena_Layer* get_instance();

private:
	void initNotChangePart();   //初始化不变的部分（主要是字体设置）
	void initChangePart();		//初始化可变的部分
	
	void reset_ui();
	
	void buttonCloseCallback(Ref* pSender,Widget::TouchEventType type);
	void buttonIncreaceCallback(Ref* pSender,Widget::TouchEventType type);
	void fightStart(Ref* pSender,Widget::TouchEventType type);
	void buttonGetOrNot(Ref* pSender,Widget::TouchEventType type);

	void buttonOpenOrNot();
	void seeGainRewardInfo( Ref* pSender ,Widget::TouchEventType type);
	//void showContext(Game_Data::game_element_list_t ele_list);
private:
	//UI_Arena_Layer*			m_pInstance;
	cocos2d::ui::Widget*				m_pRootWidget;
	cocos2d::ui::Button*				m_pBtnCloseCurLayer;

	// 左侧角色信息栏（昵称 头像 等级 排名 声望 排名奖励 倒计时 领取与否按钮）
	cocos2d::ui::Text*				m_pLabMyName;
	cocos2d::ui::ImageView*			m_pImgMyHeadPhoto;
    cocos2d::ui::ImageView*		    m_pImgMyHeadPhotoBack;
	cocos2d::ui::Text*				m_pLabMyLevel;
	cocos2d::ui::Text*				m_pLabMyRankNum;
	cocos2d::ui::Text*				m_pLabMyReputationNum;
	cocos2d::ui::Text*				m_pLabCountdown;
	cocos2d::ui::Text*				m_pLabGetOrNotFont;
	cocos2d::ui::Button*				m_pBtnGetOrNot;

	//右上侧 信息栏
	cocos2d::ui::ImageView*			m_pImgPlayerFatherNodeBack[OFFLINEPLAYERNUM];
	cocos2d::ui::ImageView*			m_pImgOffLinePlayerHeadPhotoBack[OFFLINEPLAYERNUM];
	cocos2d::ui::ImageView*			m_pImgOffLinePlayerHeadPhoto[OFFLINEPLAYERNUM];
	cocos2d::ui::Text*				m_pLabOffLinePlayerRankNun[OFFLINEPLAYERNUM];
	cocos2d::ui::Text*				m_pLabOffLinePlayerName[OFFLINEPLAYERNUM];
	cocos2d::ui::Text*				m_pLabOffLinePlayerLevel[OFFLINEPLAYERNUM];

	cocos2d::ui::Text*				m_pLabTodayChallengeInfoFont;//%s


	cocos2d::ui::Text*				m_pLabLatestRankNum;

	cocos2d::ui::Text*				m_pLabRankAwardFont;

	cocos2d::ui::ImageView*			m_pLabAwardIcon; //gift icon
	cocos2d::ui::ImageView*			m_pImgAwardInfoBack;
	cocos2d::ui::Text*				m_pLabLevelInfo;
	cocos2d::ui::Text*				m_pLabFirstAwardInfo;
	cocos2d::ui::Text*				m_pLabSecondAwardInfo;
	cocos2d::ui::Text*				m_pLabAwardContext[AWARDGOODSNUM];   //动态显示内容

	//结果显示信息
	cocos2d::ui::Text*				m_pLabRecord[OFFLINERESULTITEM];  
	cocos2d::ui::ImageView*			m_pImgAttackMark[OFFLINERESULTITEM];
	cocos2d::ui::ImageView*			m_pImgDefenceMark[OFFLINERESULTITEM];

	cocos2d::ui::Text*				labYesterdayRankFont;

	//以下 private 为引导内容区
private:
	enum guide_index
	{
		GUIDE_ARENA_STEP_0 = 180,  //keep the order
		GUIDE_ARENA_STEP_1,
		GUIDE_ARENA_STEP_2,
	};
	void showGuide();
};

#endif //__UI_ARENA_LAYER__