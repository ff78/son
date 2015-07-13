#include "UI_LoginLayer.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Platform_Dependence/Dependence.h"
#include "Common/GameDefine.h"
#include "Game_Interface/game_content_interface.h"
#include "Update_Logic/MessageInfo.h"
#include "Update_Logic/UpdateHelper.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Common/VisibleRect.h"
using namespace ui;
bool UI_LoginLayer::init()
{
	bool ret=false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());

		// 创建版本信息
		std::string str_version = Account_Data_Mgr::instance()->get_version();
		LabelTTF *lable_version = LabelTTF::create(str_version.c_str(),"Thonburi",30.f);
		//lable_version->setVisible(true);
		lable_version->setAnchorPoint( Vec2(0,1) );
		this->addChild(lable_version);
		lable_version->setPosition(VisibleRect::leftTop());
		cocos2d::Size sz=Director::getInstance()->getVisibleSize();


		/*
		cocos2d::Size sz=Director::getInstance()->getVisibleSize();
		cocos2d::Sprite *bg=cocos2d::Sprite::create("ui/Loading/background.jpg");
		bg->setPosition(Vec2(sz.width/2,sz.height/2));
		addChild(bg,0);

		MenuItemImage *item=MenuItemImage::create("pic_tab_s_normal.png","pic_tab_s_actived.png",this,menu_selector(UI_LoginLayer::btnCallBack));
		item->setPosition(Vec2(sz.width/2,sz.height/2));
		CCMenu* menu=CCMenu::create(item,NULL);
		menu->setPosition(CCPointZero);
		addChild(menu,1);

		LabelTTF* tipsLabel=LabelTTF::create("","Arial",32);
		tipsLabel->setPosition(Vec2(sz.width/2,sz.height/4));
		addChild(tipsLabel,2,TAG_LABEL_TEXT);
		*/
		m_pWidget=cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/UI_Login_Layer/UI_Login_Layer.ExportJson");
		this->addChild(m_pWidget);

		//登录的汉字
		cocos2d::ui::Text* logintxt=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget, "lab_login"));
		const char* textlogin=DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UI_LOGIN_TEXT);
		if (logintxt)
			logintxt->setString(textlogin);
		//登录按钮
		m_btnLogin=dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, "btn_login"));
		m_btnLogin->addTouchEventListener(this,toucheventselector(UI_LoginLayer::btnCallBack));
		m_btnLogin->setTitleText(textlogin);
		//提示文字
		m_labTips=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget, "lab_tips"));
		m_labTips->setTag(TAG_LABEL_TEXT);
		//对话框
		m_imgDialog=dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget, "img_update_dialog"));
		m_imgDialog->setVisible(false);
		m_btnClose=dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, "btn_close_dialog"));
		m_btnClose->addTouchEventListener(this,toucheventselector(UI_LoginLayer::closeDialogCallBack));
		//更新的提示
		m_teaUpdateTips=dynamic_cast<cocos2d::ui::TextField*>(Helper::seekWidgetByName(m_pWidget, "tea_update_tips"));
		const char* update_tips = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UPDATE_TIPS);
		if (m_teaUpdateTips)
		m_teaUpdateTips->setText(update_tips);

		//暂不更新按钮
		m_tbnNotNow=dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, "tbn_not_now"));
		if (m_tbnNotNow)
		m_tbnNotNow->addTouchEventListener(this,toucheventselector(UI_LoginLayer::notNowCallBack));
		const char* txt_not_now = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UPDATE_NOT_NOW);
		m_labNotNow=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget, "lab_not_now"));
		if (m_labNotNow)
		m_labNotNow->setString(txt_not_now);
		//继续更新
		m_tbnContinue=dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget, "tbn_continue"));
		if (m_tbnContinue)
		m_tbnContinue->addTouchEventListener(this,toucheventselector(UI_LoginLayer::continueCallBack));
		m_labContinue=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget, "lab_continue"));
		const char* txt_update_continue = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(UPDATE_CONTINUE);
		if (m_labContinue)
		m_labContinue->setString(txt_update_continue);		
		ret=true;
	} while (0);
	return ret;
}
void UI_LoginLayer::btnCallBack(Ref* pSender,Widget::TouchEventType type)
{
	//点击按钮，弹出SDK出来的界面
#if  0//(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//	Dependence::showLogin();
#endif
}
void UI_LoginLayer::closeDialogCallBack(Ref* pSender,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	m_imgDialog->setVisible(false);

	break;
    default:
	break;
}
}
void UI_LoginLayer::notNowCallBack(Ref* pSender,Widget::TouchEventType type)
{
	vector<uint64> para2;
const char* getting_info ;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	m_imgDialog->setVisible(false);
	getting_info = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(GETTING_SERVER_INFO);
	m_labTips->setString(getting_info);
	
	para2.clear();
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_ask_partition_info",para2);

	break;
    default:
	break;
}
}
void UI_LoginLayer::continueCallBack(Ref* pSender,Widget::TouchEventType type)
{
#if 0//(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	m_imgDialog->setVisible(false);
	m_labTips->setString("");
	MessageInfo *msg=new MessageInfo();
	msg->what=MessageInfo::START_MESSION;
	UpdateHelper::sharedInstance()->sendMessage(msg);
#endif
}



