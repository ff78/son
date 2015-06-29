#include "Message_Layer.h"
#include "Common/GameResource.h"
#include "Common/Utils.h"
UI::Message_Layer::Message_Layer()
	:message_label_(NULL),
	alert_label_(NULL)
{

}

bool UI::Message_Layer::init()
{
	bool retval = Layer::init();
	if(retval){


		cocos2d::Size winSize = Director::getInstance()->getWinSize();
		//±³¾°Í¼Æ¬
		backgroundimage=cocos2d::Sprite::create(NOTICE_MESSAGE_BACK_PIC);
		backgroundimage->setPosition(Vec2(winSize.width/2, winSize.height/2));
		backgroundimage->setAnchorPoint(Vec2(0.5,0.5));
		backgroundimage->setOpacity(0);
		addChild(backgroundimage);

		m_pubulic_notice_back = cocos2d::Sprite::create(NOTICE_MESSAGE_BACK_PIC);
		m_pubulic_notice_back->setVisible(false);
		m_pubulic_notice_back->setPosition(Vec2(winSize.width/2, winSize.height/2 + 200));
		addChild(m_pubulic_notice_back);

		message_label_ = LabelTTF::create("","MarkerFelt-Thin", MSG_FONT_SIZE);
		message_label_->setColor(MSG_LABEL_COLOR);
		message_label_->setPosition(Vec2(winSize.width/2, winSize.height/2 + 200));
		addChild(message_label_);

		alert_label_ = LabelTTF::create("","KaiTi", ALERT_FONT_SIZE);
		alert_label_->setColor(ALERT_LABEL_COLOR);
		alert_label_->setAnchorPoint(Vec2(0.5,0.5));
		alert_label_->setPosition(Vec2(winSize.width/2, winSize.height/2));
		alert_label_->setOpacity(0);
		addChild(alert_label_);
	}
	return retval;
}

UI::Message_Layer::~Message_Layer()
{

}

void UI::Message_Layer::add_message(const char *msg )
{
	message_queue_.push(msg);
	if(message_queue_.size() == 1)
	{
		show_message();
		//¼Ó±³¾°
		m_pubulic_notice_back->setVisible(true);
	}
}

void UI::Message_Layer::show_message()
{
	std::string message = message_queue_.front();
	message_label_->setVisible(false);
	message_label_->setString(message.c_str());

	float win_width = Director::getInstance()->getWinSize().width;
	float label_width =120;//message_label_->getBoundingBox().size().width;
	float pos_x = win_width + label_width/2;

	float to_pos_x = -label_width/2;
	float pos_y = message_label_->getPositionY();

	message_label_->setPosition(Vec2(pos_x, pos_y));
	message_label_->setVisible(true);
	

	message_label_->runAction(CCSequence::create(
		CCMoveTo::create((pos_x -to_pos_x)/MOVE_SPEED, Vec2(to_pos_x, pos_y)),
		CallFunc::create(this, callfunc_selector(Message_Layer::do_next))
		,NULL));
}

void UI::Message_Layer::do_next()
{
	message_queue_.pop();
	if(message_queue_.size() > 0){
		show_message();
	}
	else if( 0 == message_queue_.size())
	{
		//ÒÆ³ý
		m_pubulic_notice_back->setVisible(false);
	}
}

void UI::Message_Layer::show_alert( const char *msg )
{
	alert_label_->stopAllActions();
	backgroundimage->stopAllActions();

	alert_label_->setString(msg);

	alert_label_->runAction(CCSequence::create(CCFadeIn::create(SHOW_ALERT_FADE_IN_TIME),CCDelayTime::create(SHOW_ALERT_DELAY_TIME),CCFadeOut::create(SHOW_ALERT_TIME),NULL));
	backgroundimage->runAction(CCSequence::create(CCFadeIn::create(SHOW_ALERT_FADE_IN_TIME),CCDelayTime::create(SHOW_ALERT_DELAY_TIME),CCFadeOut::create(SHOW_ALERT_TIME),NULL));
}
