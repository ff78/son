#include "UI_Exchange_Code_Layer.h"
#include "Common/GameDefine.h"
#include "Game_Interface/game_content_interface.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "UI_MainMenu_Layer.h"
#include <cctype>
#include <algorithm>

USING_NS_CC;
//USING_NS_CC_EXT;
using namespace ui;
UI_Exchange_Code_Layer::UI_Exchange_Code_Layer()
	:exchange_code_layer_widget_(NULL)
	,exchange_code_("")
{

}

UI_Exchange_Code_Layer::~UI_Exchange_Code_Layer()
{
}

bool UI_Exchange_Code_Layer::init()
{
	bool result = false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());
		
		exchange_code_layer_widget_ = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Exchange_Layer/Exchange_Layer.ExportJson");
		addChild(exchange_code_layer_widget_);
		this->closeBtnEventBlind();
		this->commitBtnEventBlind();
		this->initTabButtons();
		cocos2d::Size sz=Director::getInstance()->getWinSize();
		inputPos=this->getPosition();
		inputUpPos=Vec2(this->getPosition().x,this->getPosition().y+sz.height*0.25);
		cocos2d::ui::TextField *code_field = dynamic_cast<cocos2d::ui::TextField*>( Helper::seekWidgetByName(exchange_code_layer_widget_,"EC_Input"));
		code_field->addEventListenerTextField(this,textfieldeventselector(UI_Exchange_Code_Layer::textFieldEvent));
		login_award_ = dynamic_cast<cocos2d::ui::Button*>( Helper::seekWidgetByName(exchange_code_layer_widget_,"Button_Daily") );
		if (login_award_)
		{
			login_award_->addTouchEventListener(this,toucheventselector(UI_Exchange_Code_Layer::dailyAwardCallback));
		}
		

		result = true;
	} while (0);

	return result;
}
void UI_Exchange_Code_Layer::textFieldEvent(Ref* pSender, cocos2d::ui::TextFiledEventType type)
{
#if 1
	switch (type)
	{
	case TEXTFIELD_EVENT_ATTACH_WITH_IME:
		{
#if(CC_PLATFORM_IOS==CC_TARGET_PLATFORM)
			ActionInterval* moveup=CCMoveTo::create(0.05f,inputUpPos);
			this->runAction(moveup);
#endif
		}
		break;

	case TEXTFIELD_EVENT_DETACH_WITH_IME:
		{
#if(CC_PLATFORM_IOS==CC_TARGET_PLATFORM)
			ActionInterval* movedown=CCMoveTo::create(0.05f,inputPos);
			this->runAction(movedown);
#endif
		}
		break;
	default:
		break;
	}
#endif
}

void UI_Exchange_Code_Layer::closeBtnEventBlind()
{
	cocos2d::ui::Button* close_btn = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(exchange_code_layer_widget_,"EL_Close_Btn"));
	if (!close_btn)
	{
		return;
	}
	close_btn->addTouchEventListener(this,toucheventselector(UI_Exchange_Code_Layer::closeReleaseCallback));
}

void UI_Exchange_Code_Layer::closeReleaseCallback( Ref* pSender,cocos2d::ui::Widget::TouchEventType type )
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	this->setVisible(false);

	break;
    default:
	break;
}
}

void UI_Exchange_Code_Layer::commitBtnEventBlind()
{
	cocos2d::ui::Button *commit_btn = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(exchange_code_layer_widget_,"EC_Commit_Btn"));
	if (!commit_btn)
	{
		return;
	}
	commit_btn->addTouchEventListener( this,toucheventselector( UI_Exchange_Code_Layer::commitCallback ) );
}

void UI_Exchange_Code_Layer::commitCallback( Ref* pSender ,cocos2d::ui::Widget::TouchEventType type)
{
cocos2d::ui::TextField *code_field ;
	vector<uint64> para;

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	code_field = dynamic_cast<cocos2d::ui::TextField*>( Helper::seekWidgetByName(exchange_code_layer_widget_,"EC_Input") );
	exchange_code_ = code_field->getStringValue();
	if (exchange_code_.empty())
	{
		DICTIONARY_CONFIG_MGR::instance()->show_alert(ECR_PLEASE_INPUT);
		return;
	}

	if (exchange_code_.size() > MAX_EXCHANGE_CODE_LEN)
	{
		CCLOG("TOO LONG CODE \n");
		return;
	}

	this->exchangecode_tolower();

	para.clear();
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_ask_exchange_code_info",para,exchange_code_.c_str());

	code_field->setText("");

	break;
    default:
	break;
}
	
}

void UI_Exchange_Code_Layer::exchangecode_tolower( void )
{
	std::transform(exchange_code_.begin(),exchange_code_.end(), exchange_code_.begin(), ::tolower);
}

void UI_Exchange_Code_Layer::initTabButtons()
{
	cocos2d::ui::Button *ex_btn = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(exchange_code_layer_widget_,"Button_EL"));
	if (!ex_btn)
	{
		return;
	}
	ex_btn->loadTextureNormal("pic_tab_s_actived.png");
}

void UI_Exchange_Code_Layer::dailyAwardCallback( Ref* pSender ,cocos2d::ui::Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(false);
	UI_MainMenu_Layer::get_instance()->visibleLoginAward();

	break;
    default:
	break;
}
}



