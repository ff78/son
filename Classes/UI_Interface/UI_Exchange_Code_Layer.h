#ifndef _UI_EXCHANGE_CODE_LAYER_H_
#define _UI_EXCHANGE_CODE_LAYER_H_


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
//USING_NS_CC_EXT;
USING_NS_CC;
#define MAX_EXCHANGE_CODE_LEN 16
using namespace ui;
class UI_Exchange_Code_Layer:public cocos2d::Layer
{
public:
	UI_Exchange_Code_Layer();
	~UI_Exchange_Code_Layer();
	bool init();
	CREATE_FUNC(UI_Exchange_Code_Layer);

private:
	// init functions
	void closeBtnEventBlind();
	void commitBtnEventBlind();
	void initTabButtons();

private:
	//callback functions
	void closeReleaseCallback( Ref* pSender ,Widget::TouchEventType type);
	void commitCallback( Ref* pSender,Widget::TouchEventType type );
	void dailyAwardCallback( Ref* pSender ,Widget::TouchEventType type);
	//helper
	void exchangecode_tolower( void );
	void textFieldEvent(Ref* pSender, cocos2d::ui::TextFiledEventType type);
private:
	cocos2d::ui::Widget* exchange_code_layer_widget_;
	std::string exchange_code_;
	Point					inputPos;
	Point					inputUpPos;
	cocos2d::ui::Button* login_award_;

};
#endif //_UI_EXCHANGE_CODE_LAYER_H_