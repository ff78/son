#pragma once

//#include "cocos-ext.h"
#include "cocos2d.h"
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
#include "cocostudio/CocoStudio.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;
//USING_NS_CC_EXT;

class UI_Banks_Layer : public cocos2d::Layer
{
public:
	UI_Banks_Layer(void);
	~UI_Banks_Layer(void);
	virtual bool init();
	virtual void setVisible(bool visible);
	CREATE_FUNC(UI_Banks_Layer);

public:
	void update(void);

private://callback functions
	void closeReleaseCallback( Ref* pSender,Widget::TouchEventType type );
	void exchangeReleaseCallback( Ref* pSender ,Widget::TouchEventType type);

private://init and binding
	void refresh();
	void initLabels();

	void initAndBindCloseBtnEvent();
	void initAndBindExchangeBtnEvent();

	std::string intToString( int );


private:
	cocos2d::ui::Widget*	banks_widget_;
	cocos2d::ui::Button*   banks_close_btn_;			//?????
	cocos2d::ui::Button*	banks_exchange_commit_btn_;	//??????
	cocos2d::ui::Text*	banks_token_value_;
	cocos2d::ui::Text*	banks_money_value_;
	cocos2d::ui::Text*	banks_count_value_;

};

