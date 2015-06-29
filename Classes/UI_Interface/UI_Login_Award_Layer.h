#ifndef _UI_LOGIN_AWARD_LAYER_H_
#define _UI_LOGIN_AWARD_LAYER_H_

#include "cocos2d.h"
//#include "cocos-ext.h"
#include <map>
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include "ui/UITextField.h"
#include "ui/UILoadingBar.h"
#include "ui/UILayout.h"
#include "ui/UISlider.h"
#include "ui/UICheckBox.h"
#include "ui/UIWidget.h"
#include "ui/UIScrollView.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;
enum AWARD_CELL_STATE
{
	ACS_CAN_RECEIVE,
	ACS_CAN_NOT_RECEIVE,
	ACS_RECEIVED,
};


class Daily_Award_Single_Frame: public cocos2d::ui::ImageView
{
public:
	Daily_Award_Single_Frame();
	~Daily_Award_Single_Frame();
	bool init();
	CREATE_FUNC(Daily_Award_Single_Frame);

public:
	void setState( AWARD_CELL_STATE new_state );
	int getState(){ return this->award_cell_state_;};

	void setTheType( int type );
	int getTheType( void ){ return this->type_; };

	void setTitle(const char* title);
	const char* getTitle( void );

	void setGiftImage(const char* image);
	void setButtonText( const char* text );
	//void addTouchEventListener(Ref* target, cocos2d::ui::SEL_ReleaseEvent selector);

private:
	cocos2d::ui::ImageView* title_bg_;
	cocos2d::ui::Text* title_;
	cocos2d::ui::Button* commit_btn_;
	cocos2d::ui::ImageView* gift_show_;
	cocos2d::ui::ImageView* gift_bg_;
	cocos2d::ui::Text* gift_type_;
	int type_;
	int award_cell_state_;
};


class UI_Login_Award_Layer: public cocos2d::Layer
{
public:
	UI_Login_Award_Layer();
	~UI_Login_Award_Layer();
	bool init();
	CREATE_FUNC(UI_Login_Award_Layer);

public:
	void refresh();
	virtual void setVisible(bool visible);

private:
	// init functions
	void closeBtnEventBlind();
	void commitBtnEventBlind();

	void initTabButtons();
	void initAwardCells( int nums );

private:
	//callback functions
	void closeReleaseCallback( Ref* pSender ,Widget::TouchEventType type);
	void commitCallback( Ref* pSender,Widget::TouchEventType type );
	void exchangeViewCallback( Ref* pSender ,Widget::TouchEventType type);

private:
	cocos2d::ui::Widget* login_award_layer_wiget_;
	cocos2d::ui::Button* exchange_btn_;
	std::map<int, Daily_Award_Single_Frame*> daily_award_board_map;
};
#endif //_UI_LOGIN_AWARD_LAYER_H_
