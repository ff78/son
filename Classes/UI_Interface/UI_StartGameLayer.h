#ifndef _H_H_UI_STARTGAMELAYER_H__
#define _H_H_UI_STARTGAMELAYER_H__
#include "cocos2d.h"
//#include "cocos-ext.h"
#include "Player_Account/Account_Data.h"
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
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;
using namespace std;
//USING_NS_CC;
//USING_NS_CC_EXT;
class UI_StartGameLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(UI_StartGameLayer);

//    void keyBackClicked();
	void btnCallBackExit();

private:
	cocos2d::ui::Widget*   m_pWidgetStartGame;

	cocos2d::ui::Text*		m_labserverName;
	cocos2d::ui::ImageView*		m_img_hot;
	cocos2d::ui::ImageView*		m_img_recomend;
	cocos2d::ui::ImageView*		m_img_hot_red;
	cocos2d::ui::ImageView*		m_img_recomend_green;


	cocos2d::ui::Button*		m_btnStartGame;
	cocos2d::ui::Button*		m_btnChangeAccount;
	cocos2d::ui::Text*		m_btnSeeAllServer;
	cocos2d::ui::Button*		m_btnExit;

private:
	void startGame(Ref* pSender,Widget::TouchEventType type);
	void changeAccount(Ref* pSender,Widget::TouchEventType type);
	void seeAllServer(Ref* pSender,Widget::TouchEventType type);
	void goExit(Ref* pSender,Widget::TouchEventType type);
	void setServerStateUI(Server_List_Data sld);
};
#endif //_H_H_UI_STARTGAMELAYER_H__
