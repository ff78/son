#ifndef _UI_Equipment_Strengthen_Layer_
#define _UI_Equipment_Strengthen_Layer_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../../Game_Interface/common.h"

#define attr_num 2

USING_NS_CC;

using namespace ui;

class UI_Equipment_Strengthen_Layer :public cocos2d::Layer
{
private:
	uint64								mItemId;
	//---按钮方法回调---//	
	void								OnBtnCloseCallBack(Ref* pSender, Widget::TouchEventType type);					// 关闭按钮方法回调
	void								OnBtnStrengthenTextCallBack(Ref* pSender, Widget::TouchEventType type);			// 强化按钮方法回调
	void								OnBtnStarUpTextCallBack(Ref* pSender, Widget::TouchEventType type);				// 升星按钮方法回调
	void								OnBtnGemCallBack(Ref* pSender, Widget::TouchEventType type);					// 宝石按钮方法回调
	void								onWashCallBack(Ref* pSender, Widget::TouchEventType type);
	void                                strengthenCallback(Ref* pSender, Widget::TouchEventType type);

private:
	//---接收消息---//

private:
	//---发送消息---//

private:
	//---Cocostudio文件---//
	ui::Button*							m_pEquipStrengthenText;					// 强化文本
	ui::Button*							m_pEquipStarUpText;						// 升星文本
	ui::Button*							m_pEquipGemText;						// 宝石文本
	ui::Button*							m_pEquipWashText;						// 洗炼文本
	ui::Button*							_washButton;					

	ui::Button*							m_pCloseBtn;						// 关闭按钮
	CC_SYNTHESIZE(ui::Widget*,root,Root);

	CC_SYNTHESIZE(ui::ImageView*, curEquip, CurEquip);
	CC_SYNTHESIZE(ui::Text*, curName, CurName);
	CC_SYNTHESIZE(ui::Text*, levelNeeded, LevelNeeded);
	CC_SYNTHESIZE(ui::Text*, levelCur, LevelCur);
	CC_SYNTHESIZE(ui::Text*, levelAfter, LevelAfter);
	ui::Text* mCurAttrs[attr_num];
	ui::Text* mAfterAttrs[attr_num];
	CC_SYNTHESIZE(ui::Text*, powerTxt, PowerTxt);
	CC_SYNTHESIZE(ui::Text*, moneyNeeded, MoneyNeeded);
	CC_SYNTHESIZE(ui::Text*, nextMoneyNeeded, NextMoneyNeeded);
	CC_SYNTHESIZE(ui::Button*, strengthenBtn, StrengthenBtn);

	static Value sGold;
	static Value sToken;
	bool initData();

	CC_SYNTHESIZE(cocos2d::ui::TextAtlas*, retainToken, RetainToken);
	CC_SYNTHESIZE(cocos2d::ui::TextAtlas*, retainGold, RetainGold);

	void update();

	inline void setItemId(const uint64 itemId){ mItemId = itemId; };

	UI_Equipment_Strengthen_Layer();
	~UI_Equipment_Strengthen_Layer();
	CREATE_FUNC(UI_Equipment_Strengthen_Layer);

	virtual bool init() override;
	virtual void onExit() override;
	virtual void onEnter() override;
	virtual void setVisible(bool visible) override;

};

#endif
