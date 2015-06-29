#ifndef __DAILY_MISSION__
#define __DAILY_MISSION__

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
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;
USING_NS_CC;
//USING_NS_CC_EXT;

#define DAILY_MISSION_GAIN_NUM 3
#define STARTS_ALL_NUM			5

class UI_Daily_Mission : public cocos2d::Layer
{
public:
	UI_Daily_Mission(void);
	~UI_Daily_Mission(void);

	virtual bool init();
	virtual void setVisible(bool visible);
	CREATE_FUNC(UI_Daily_Mission);

    void update();
    void reset_ui();

private:
	void tokenFinishCallback( Ref* pSender ,Widget::TouchEventType type);			//元宝完成
	void oneKeyGainAllStarsCallback( Ref* pSender ,Widget::TouchEventType type);	//一键满星
	void opMissionCallback( Ref* pSender,Widget::TouchEventType type );		//放弃任务
	void refreshStarsLevelUpCallback( Ref* pSender,Widget::TouchEventType type );	//刷星升级
	void btnGiftGainOrNotCallback( Ref* pSender,Widget::TouchEventType type );		//领取

	void initComponent();
	void btnAlreadyAcpCallback( Ref* pSender,Widget::TouchEventType type );		//已接任务
	void btnNoAcpCallback( Ref* pSender,Widget::TouchEventType type );				//未接任务
	void btnCloseCallback( Ref* pSender,Widget::TouchEventType type );				//关闭
	
private:
	cocos2d::ui::Widget*			m_prRotWidget;

	//切换界面区
	cocos2d::ui::Button*			m_btn_already_acp_mis;
	cocos2d::ui::Button*			m_btn_no_acp_mis;
	cocos2d::ui::Button*			m_btn_close;

	//任务区
	cocos2d::ui::ImageView*		m_img_stars_back_texture[STARTS_ALL_NUM];
	cocos2d::ui::ImageView*		m_img_stars_texture[STARTS_ALL_NUM];
	cocos2d::ui::Text*			m_lab_mission_process_font;
	cocos2d::ui::Text*			m_lab_mission_process_percent;
	cocos2d::ui::Text*			m_lab_vip_times_font;
	cocos2d::ui::Text*			m_lab_vip_times_percent;

	cocos2d::ui::Text*			m_lab_mission_name;
	cocos2d::ui::Text*			m_lab_mission_cur_state;
	cocos2d::ui::Text*			m_lab_mission_require;
	cocos2d::ui::Text*			m_lab_mission_require_info;
	cocos2d::ui::Text*			m_lab_mission_award_font;
	cocos2d::ui::Text*			m_lab_mission_award_exp;
	cocos2d::ui::Text*			m_lab_mission_award_exp_num;
	cocos2d::ui::Text*			m_lab_mission_award_exp_times_num;
	cocos2d::ui::Text*			m_lab_mission_award_silver;
	cocos2d::ui::Text*			m_lab_mission_award_silver_num;
	cocos2d::ui::Text*			m_lab_mission_award_silver_times_num;

	cocos2d::ui::Button*			m_btn_first;
	cocos2d::ui::Text*			m_btn_first_font;
	cocos2d::ui::Button*			m_btn_second;
	cocos2d::ui::Text*			m_lab_second_font;
	cocos2d::ui::Button*			m_btn_third;
	cocos2d::ui::Text*			m_lab_third_font;
	cocos2d::ui::Button*			m_btn_fourth;
	cocos2d::ui::Text*			m_lab_fourth_font;

	//礼包领取区
	cocos2d::ui::ImageView*		m_img_gift_texture[DAILY_MISSION_GAIN_NUM];
	cocos2d::ui::Text*			m_lab_gift_daily_mis_compelete[DAILY_MISSION_GAIN_NUM];
	cocos2d::ui::Text*			m_lab_gift_daily_mis_percent[DAILY_MISSION_GAIN_NUM];
	cocos2d::ui::Button*			m_btn_gift_gain_or_not[DAILY_MISSION_GAIN_NUM];
	cocos2d::ui::Text*			m_lab_gift_gain_or_not[DAILY_MISSION_GAIN_NUM];

};

#endif //__DAILY_MISSION__