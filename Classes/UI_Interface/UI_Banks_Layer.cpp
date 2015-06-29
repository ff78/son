#include "UI_Banks_Layer.h"
#include "Network_Common/global_macros.h"
#include "Game_Interface/game_content_interface.h"
#include "Banks_System/Banks_Logic_Mgr.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Common/GameMacro.h"
using namespace ui;
UI_Banks_Layer::UI_Banks_Layer(void)
	:banks_widget_(NULL)
	,banks_close_btn_(NULL)
	,banks_exchange_commit_btn_(NULL)
	,banks_token_value_(NULL)
	,banks_money_value_(NULL)
	,banks_count_value_(NULL)
{
}


UI_Banks_Layer::~UI_Banks_Layer(void)
{
}

bool UI_Banks_Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());

		banks_widget_ = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Banks_Layer/Banks_Layer.ExportJson");
		this->addChild(banks_widget_);
		this->initAndBindCloseBtnEvent();
		this->initAndBindExchangeBtnEvent();
		this->initLabels();
		this->refresh();
		bRet = true;
	} while (0);

	return bRet;
}

void UI_Banks_Layer::closeReleaseCallback( Ref* pSender,Widget::TouchEventType type )
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

void UI_Banks_Layer::exchangeReleaseCallback( Ref* pSender,Widget::TouchEventType type )
{
vector<uint64> para;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_exchange_token_to_gold",para);
	break;
    default:
	break;
}
}

void UI_Banks_Layer::setVisible( bool visible )
{
	cocos2d::Layer::setVisible(visible);
	if (banks_close_btn_)
	{
		banks_close_btn_->setTouchEnabled(visible);
	}
	if (banks_exchange_commit_btn_)
	{
		banks_exchange_commit_btn_->setTouchEnabled(visible);
	}

    if (visible)
    {
        update();
    }
}

void UI_Banks_Layer::initAndBindCloseBtnEvent()
{
	banks_close_btn_ = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(banks_widget_,"Banks_Close_Btn"));
	if (banks_close_btn_)
	{
		banks_close_btn_->addTouchEventListener( this, toucheventselector( UI_Banks_Layer::closeReleaseCallback ) );
	}
}

void UI_Banks_Layer::initAndBindExchangeBtnEvent()
{
	banks_exchange_commit_btn_ = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(banks_widget_,"Banks_Exchange_BTN"));
	if (banks_exchange_commit_btn_)
	{
		banks_exchange_commit_btn_->addTouchEventListener( this, toucheventselector( UI_Banks_Layer::exchangeReleaseCallback ) );
	}
}

void UI_Banks_Layer::update( void )
{
	this->refresh();
}

void UI_Banks_Layer::initLabels()
{
	banks_token_value_ = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(banks_widget_,"Banks_Cost_Content_Label"));

	banks_money_value_ = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(banks_widget_,"Banks_Pay_Content_Lable"));

	banks_count_value_ = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(banks_widget_,"Banks_Count_Content_Label"));
}

void UI_Banks_Layer::refresh()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	int count = player->get_banks_exchange_count();
	int level = player->get_character_level();

	int cost_token = Banks_Logic_Mgr::instance()->calculate_cost(count);
	int money_get = Banks_Logic_Mgr::instance()->calculate_exchanged_cold_by_token(level, count+1);

	if (banks_token_value_)
	{
		banks_token_value_->setString(intToString(cost_token).c_str());
	}

	if (banks_money_value_)
	{
		banks_money_value_->setString(intToString(money_get).c_str());
	}

	std::string count_str = intToString(count) + "/" + "20";

	if (banks_count_value_)
	{
		banks_count_value_->setString(count_str.c_str());
	}
}

std::string UI_Banks_Layer::intToString( int a)
{
	char str[32] = {0};

	SPRINTF(str, "%d", a);

	return std::string(str); 
}
