#ifndef _UI_SETTLEMENT_LAYER_
#define _UI_SETTLEMENT_LAYER_

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
#define AWARD_INFO_NUM	3

//USING_NS_CC;
//USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;
class UI_Icon_Info_Layer;
class UI_Settlement_Layer : public cocos2d::Layer
{
public:
	UI_Settlement_Layer(void);
	virtual ~UI_Settlement_Layer(void);

public:
	virtual bool init();
	CREATE_FUNC(UI_Settlement_Layer);
	virtual void setVisible( bool visible );
	void showGuide();

	void settlementCloseCallback( cocos2d::Ref* pSender ,Widget::TouchEventType type);
	void showIconInfo(cocos2d::Ref* pSender,Widget::TouchEventType type);

	void settlementConfig();
	void update();
	void setStarsVisible();

private:
    int proc_instance_result(void);
	int m_star_count;
	cocos2d::ui::Widget*			m_pSettlementWidget_;	//UI根节点

	cocos2d::ui::ImageView*		cocoIconGoods[AWARD_INFO_NUM];		//物品奖励背景 
	cocos2d::ui::ImageView*		cocoIconGoods_Texture[AWARD_INFO_NUM];//物品奖励图片
	cocos2d::ui::Text*			cocoIconGoods_Num[AWARD_INFO_NUM];

	cocos2d::ui::ImageView*		m_pImgWinOrLose;		//设置胜利 失败的图片显示信息
	cocos2d::ui::Text*			m_pLabExp_1;			//设置 上方的 EXP 经验值 数值
	cocos2d::ui::Text*			m_pLabMoneyAward;		//设置 金钱奖励 数值

	cocos2d::ui::Text*			m_pLabTimeScore;		//数值 时间得分
	cocos2d::ui::Text*			m_pLabDeadScore;		//数值 死亡扣分
	cocos2d::ui::Text*			m_pLabVIPScore;			//数值 VIP补正
	cocos2d::ui::Text*			m_pLabFinalScore;		//数值 最终得分

	cocos2d::ui::ImageView*		m_pImgStartsForLevel[3];//星星 获得
	cocos2d::ui::ImageView*		m_pImgHeadPhoto_1;		//设置头像 1 图片
	cocos2d::ui::ImageView*		m_pImgHeadPhoto_2;		//设置头像 2 图片


	//副将显示信息 区域
	cocos2d::ui::ImageView*		m_pImgLieuHeadBack;
	cocos2d::ui::Text*			m_pLabLieuEXP;
	cocos2d::ui::ImageView*		m_pImgLieuVIP;
	cocos2d::ui::Text*			m_pLabLieuExpNum;			//设置 下方的 EXP 经验值 数值
	cocos2d::ui::Text*			m_pLabLieuVIPNum;


	//Icon 信息显示框
	UI_Icon_Info_Layer*			m_pLayerIconInfo;


	//显示 奖励获得信息
	std::string					m_getGainAwardInfo;
	bool						isGainOrNot;
	
	cocos2d::ui::Button*					closeButton;
	cocos2d::ui::Text*					m_lab_close_btn_font;
private:
	enum guide_step
	{
		JUNIOR_GUIDE_STEP_11 = 11,
	};
};

#endif //_UI_SETTLEMENT_LAYER_