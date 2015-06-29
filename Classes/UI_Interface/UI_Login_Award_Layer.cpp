#include "UI_Login_Award_Layer.h"
#include "Common/GameDefine.h"
#include "Network_Common/global_macros.h"
#include "Game_Interface/game_content_interface.h"
#include "UI_MainMenu_Layer.h"
#include "Common/GameResource.h"
#include "Login_Reward_System/Login_Reward_Mgr_Cl.h"
#include "Login_Reward_System/Login_Reward_Config_Mgr.h"
#include "Character_System/Player_Logic_Cl.h"
#include "Player_Account/Account_Data_Mgr.h"
#include <cctype>
#include <algorithm>
using namespace ui;
USING_NS_CC;
//USING_NS_CC_EXT;

const int g_row_nums = 4;
const int g_gap_vertical = 270;
const int g_gap_horizontal = 245;

#define GIFT_TYPE "gift_type_"

UI_Login_Award_Layer::UI_Login_Award_Layer()
	:login_award_layer_wiget_(NULL)
	,exchange_btn_(NULL)
	
{
	daily_award_board_map.clear();
}

UI_Login_Award_Layer::~UI_Login_Award_Layer()
{
}

bool UI_Login_Award_Layer::init()
{
	bool result = false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());
		
		login_award_layer_wiget_ = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Daily_Award/Daily_Award.ExportJson");
		addChild(login_award_layer_wiget_);

		this->closeBtnEventBlind();

		exchange_btn_ = dynamic_cast<cocos2d::ui::Button*>( Helper::seekWidgetByName(login_award_layer_wiget_,"btn_exchange") );
		if (exchange_btn_)
		{
			exchange_btn_->addTouchEventListener(this,toucheventselector(UI_Login_Award_Layer::exchangeViewCallback));
		}

		this->initAwardCells(WEEK_DAY);
		this->refresh();

		result = true;
	} while (0);

	return result;
}

void UI_Login_Award_Layer::exchangeViewCallback( Ref* pSender,cocos2d::ui::Widget::TouchEventType type )
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(false);
	UI_MainMenu_Layer::get_instance()->visibleExchange();

	break;
    default:
	break;
}
}

void UI_Login_Award_Layer::closeReleaseCallback( Ref* pSender ,cocos2d::ui::Widget::TouchEventType type)
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

void UI_Login_Award_Layer::closeBtnEventBlind()
{
cocos2d::ui::Button* close_btn;

	close_btn = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(login_award_layer_wiget_,"btn_close"));
	if (!close_btn)
	{
		return;
	}
	close_btn->addTouchEventListener(this,toucheventselector(UI_Login_Award_Layer::closeReleaseCallback));


}

void UI_Login_Award_Layer::initAwardCells( int nums )
{

	cocos2d::ui::ImageView* bg = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(login_award_layer_wiget_,"first_back"));

	int x = -400;
	int y = 90;

	//测试

	const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(LOGIN_AWARD_NORMAL_TITLE);

	for (int i = 0; i < nums; ++i)
	{
		CCString * str = CCString::createWithFormat(szString, (i+1) );
		Daily_Award_Single_Frame* award_frame = Daily_Award_Single_Frame::create();
		int x_tmp = x + g_gap_vertical * ( i % g_row_nums );
		int y_tmp = y - g_gap_horizontal * ( i / g_row_nums );
		award_frame->setPosition(Vec2(x_tmp,y_tmp));
		bg->addChild(award_frame);
		award_frame->setTheType(i);
		award_frame->addTouchEventListener(this,toucheventselector(UI_Login_Award_Layer::commitCallback));
		award_frame->setTitle(str->getCString());
		daily_award_board_map.insert(make_pair(i,award_frame));
	}
}

void UI_Login_Award_Layer::refresh()
{

	Game_Data::Login_Reward login_reward = Game_Data::Login_Reward_Mgr::instance()->get_login_reward();
	if (login_reward.is_continuous_)
	{
	}

	int continuous_count = login_reward.continuous_count_;
	int nums = WEEK_DAY;

	for (int i = 0; i < nums ; ++i)
	{
		Daily_Award_Single_Frame* award_frame_tmp = daily_award_board_map[i];
		if (1 <= continuous_count)
		{
			award_frame_tmp->setState(ACS_CAN_RECEIVE);
			if (login_reward.got_flag_[i])
			{
				award_frame_tmp->setState(ACS_RECEIVED);
			}
			continuous_count--;
		}else
		{
			award_frame_tmp->setState(ACS_CAN_NOT_RECEIVE);
		}
	}

}

void UI_Login_Award_Layer::commitCallback( Ref* pSender,cocos2d::ui::Widget::TouchEventType type )
{
	cocos2d::ui::Button* commit_btn = dynamic_cast<cocos2d::ui::Button*>(pSender);

	cocos2d::ui::Text* cell_type_label = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(commit_btn,GIFT_TYPE));
	int award_cell_type =atoi( cell_type_label->getStringValue().c_str() );

    Game_Data::login_reward_config* config = LOGIN_REWARD_CONFIG_MGR::instance()->get_login_reward_config(award_cell_type);
    if (!config)
    {   
        return;
    }

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    if (PLAYER_LOGIC::instance()->check_bag_room(player_id,config->reward_id_,1) == false)
    {
        DICTIONARY_CONFIG_MGR::instance()->show_alert(BAG_FULL_TIPS);
        return;
    }

	std::vector<uint64> para;
	para.push_back(award_cell_type);
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_get_login_reward", para);

}

void UI_Login_Award_Layer::setVisible( bool visible )
{
	cocos2d::Layer::setVisible(visible);
	if (visible)
	{
			this->refresh();
	}
}











Daily_Award_Single_Frame::Daily_Award_Single_Frame()
	:title_bg_(NULL)
	,title_(NULL)
	,commit_btn_(NULL)
	,gift_show_(NULL)
	,gift_bg_(NULL)
	,type_(0)
	,award_cell_state_(1)
{

}

Daily_Award_Single_Frame::~Daily_Award_Single_Frame()
{

}

bool Daily_Award_Single_Frame::init()
{
	bool result = false;
	do 
	{
		CC_BREAK_IF(!cocos2d::ui::ImageView::init());

		//登录奖励 每一个小单元 的背景图
		this->loadTexture(PAGE_VIEW_BG_LXD);
this->setScale9Enabled(true);
		this->setCapInsets(CCRect(40,40,40,40));
this->setSize(Size(190,236));

		//小单元 标题的背景图
		title_bg_ = cocos2d::ui::ImageView::create();
		title_bg_->loadTexture(GIFT_FRAME_TITLE_BG);
title_bg_->setScale9Enabled(true);
		title_bg_->setCapInsets(CCRect(5,5,5,5));
title_bg_->setSize(Size(196,37));
		title_bg_->setPosition(Vec2(2,98));
		this->addChild(title_bg_);

		//标题
		title_ = cocos2d::ui::Text::create();
//		title_->setFontSize(25);
		title_->setString("Test");
		title_bg_->addChild(title_);

		//礼物图片背景框
		gift_bg_ = cocos2d::ui::ImageView::create();
		gift_bg_->loadTexture(GIFT_BG_FRAME);
		gift_bg_->setPosition(Vec2(0,10));
		this->addChild(gift_bg_);

		//礼物图片
		gift_show_ = cocos2d::ui::ImageView::create();
		gift_show_->loadTexture(PIC_LIBAO_PUTONG);
		gift_bg_->addChild(gift_show_);

		//领取按钮
		commit_btn_ = cocos2d::ui::Button::create();
		commit_btn_->loadTextures(TIDY_BUTTON_NORMAL, TIDY_BUTTON_PRESSED, TIDY_BUTTON_DISABLED);
		commit_btn_->setPosition(Vec2(0,-75));
		commit_btn_->setTouchEnabled(true);
		this->addChild(commit_btn_);

		//用uilabel 来给记录当前是累计多少天的，给回调函数用做给服务器发消息的ID
		gift_type_ = cocos2d::ui::Text::create();
		gift_type_->setVisible(false);
		gift_type_->setName(GIFT_TYPE);
		commit_btn_->addChild(gift_type_);

		result = true;
	} while (0);

	return result;
}

void Daily_Award_Single_Frame::setTitle( const char* title )
{
	if (NULL != title)
	{
		this->title_->setString(title);
	}
}

void Daily_Award_Single_Frame::setGiftImage( const char* image )
{
	if (NULL != image)
	{
		this->gift_show_->loadTexture(image);
	}
}
#if 0
void Daily_Award_Single_Frame::addTouchEventListener( Ref* target, cocos2d::extension::SEL_ReleaseEvent selector )
{
	if (this->commit_btn_)
	{
		commit_btn_->addTouchEventListener(target,selector);
	}
	
}
#endif
void Daily_Award_Single_Frame::setState( AWARD_CELL_STATE new_state )
{
	this->award_cell_state_ = new_state;

	switch (new_state)
	{
	case ACS_CAN_RECEIVE:
		{
			this->commit_btn_->setTitleText("ACS_CAN_RECEIVE");
			this->commit_btn_->setTouchEnabled(true);
			this->commit_btn_->loadTextureNormal(TIDY_BUTTON_NORMAL);
			const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(LOGIN_AWARD_CAN_RECEIVE);
			this->commit_btn_->setTitleText(szString);
			this->commit_btn_->setTitleFontSize(25);
		}
		break;
	case ACS_CAN_NOT_RECEIVE:
		{
			this->commit_btn_->setTitleText("ACS_CAN_NOT_RECEIVE");
			this->commit_btn_->setTouchEnabled(false);
			this->commit_btn_->loadTextureNormal(TIDY_BUTTON_DISABLED);
			const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(LOGIN_AWARD_CAN_RECEIVE);
			this->commit_btn_->setTitleText(szString);
			this->commit_btn_->setTitleFontSize(25);
		}
		break;
	case ACS_RECEIVED:
		{
			this->commit_btn_->setTitleText("ACS_RECEIVED");
			this->commit_btn_->setTouchEnabled(false);
			this->commit_btn_->loadTextureNormal(TIDY_BUTTON_DISABLED);
			const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(LOGIN_AWARD_RECEIVED);
			this->commit_btn_->setTitleText(szString);
			this->commit_btn_->setTitleFontSize(25);
		}
		break;
	default:
		break;
	}

	//update ui;
	
}

void Daily_Award_Single_Frame::setTheType( int type )
{
	this->type_ = type; 
	CCString* str = CCString::createWithFormat("%d", type);
	gift_type_->setString(str->getCString());
}
