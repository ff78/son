#ifndef _UI_Equipment_StarUp_Layer_
#define _UI_Equipment_StarUp_Layer_
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "../../Game_Interface/common.h"

#define attr_num 2

USING_NS_CC;

using namespace ui;

class UI_Equipment_StarUp_Layer :public cocos2d::Layer
{
private:
	ui::Button*							m_pEquipStrengthenText;					// 强化文本
	ui::Button*							m_pEquipStarUpText;						// 升星文本
	ui::Button*							m_pEquipGemText;						// 宝石文本
	ui::Button*							m_pEquipWashText;						// 洗炼文本

	ui::Button*							m_pCloseBtn;						// 关闭按钮

	void								onCloseCallBack(Ref* pSender, Widget::TouchEventType type);					// 关闭按钮方法回调
	void								onStrengthenTextCallBack(Ref* pSender, Widget::TouchEventType type);			// 强化按钮方法回调
	void								onStarUpTextCallBack(Ref* pSender, Widget::TouchEventType type);				// 升星按钮方法回调
	void								onGemCallBack(Ref* pSender, Widget::TouchEventType type);					// 宝石按钮方法回调
	void								onWashCallBack(Ref* pSender, Widget::TouchEventType type);				    // 洗炼按钮方法回调
	void                                starupCallback(Ref* pSender, Widget::TouchEventType type);
	void                                starupTenCallback(Ref* pSender, Widget::TouchEventType type);

	CC_SYNTHESIZE(ui::Widget*, root, Root);

	CC_SYNTHESIZE(ui::ImageView*, curEquip, CurEquip);
	CC_SYNTHESIZE(ui::Text*, curName, CurName);
	CC_SYNTHESIZE(ui::Text*, levelNeeded, LevelNeeded);
	CC_SYNTHESIZE(ui::Text*, starsLeft, StarsLeft);
	CC_SYNTHESIZE(ui::Text*, starsRight, StarsRight);

	static Value sGold;
	static Value sToken;
	bool initData();

	CC_SYNTHESIZE(cocos2d::ui::TextAtlas*, retainToken, RetainToken);
	CC_SYNTHESIZE(cocos2d::ui::TextAtlas*, retainGold, RetainGold);

	/*CC_SYNTHESIZE(ui::Text*, starsCur, StarsCur);
	CC_SYNTHESIZE(ui::Text*, starsAfter, StarsAfter);*/
	int mStarsCur;
	int mStarsAfter;
	ui::Text* mCurAttrs[attr_num];
	ui::Text* mAfterAttrs[attr_num];
	CC_SYNTHESIZE(ui::Text*, powerTxt, PowerTxt);
	CC_SYNTHESIZE(ui::Text*, moneyNeeded, MoneyNeeded);
	CC_SYNTHESIZE(ui::Text*, nextMoneyNeeded, NextMoneyNeeded);
	CC_SYNTHESIZE(ui::Button*, starupBtn, StarupBtn);
	ui::ImageView* stars[9];
	ui::ImageView* starsAfter[9];
	ui::Text* starLevelTxt[9];


	UI_Equipment_StarUp_Layer();
	~UI_Equipment_StarUp_Layer();

	int curCost;

	void update();
	uint64 mItemId;
	void setItemId(const uint64 itemId){ mItemId = itemId; };

	//virtual void setVisible(bool visible) override;
	virtual bool init() override;
	virtual void onExit() override;
	virtual void onEnter() override;
	virtual void setVisible(bool visible) override;
	CREATE_FUNC(UI_Equipment_StarUp_Layer);
};

#endif