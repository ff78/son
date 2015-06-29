#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "MyPageView.h"
#include "../../Play_System/Instance_Data_Mgr.h"
#include "../../DataModule/BattleField.h"

class SelectBattleLayer : public cocos2d::Layer,public MyPageViewDelegate
{
public:
    bool init();
    
    CREATE_FUNC(SelectBattleLayer);
	SelectBattleLayer(void);
	~SelectBattleLayer(void);
    
	void onEnter() override;
    void onExit();
    
    bool initRoot(); 
	void closeStageCallBack(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void clickStageCallBack(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void removeStage();

	void pageViewEvent(cocos2d::Ref*pSender, cocos2d::ui::PageView::EventType type);
    int show_item_icon(std::vector<uint>& para, int item_count);
    void selectedEvent(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);

    void resetInstanceDetail(int instanceId);
    
    void pressStart(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    
    void updateData();
	void updateBig();
	void updateSmall(int bigId);
	void RefreshLayer(const int nStateID);
	void enterFight();
private:
	cocos2d::ui::Button* closeBtn;
	cocos2d::ui::PageView* pageV;
	cocos2d::ui::Widget* root;
	cocos2d::ui::ImageView* itembg[3];
	cocos2d::ui::CheckBox* difficultBox[2];
	cocos2d::ui::Button* startBtn;
public :
	Layer* getContainer();
	virtual Size sizeForPerPage();
	virtual void pageViewDidScroll(MyPageView* pageView);
	virtual void myPageViewTurned();
private:
	int _bigId;
	int mIndex;
	MyPageView* pageView;
	void addPages();
	BattleField* _battle;
    
    int currScore;
};