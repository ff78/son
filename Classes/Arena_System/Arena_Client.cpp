#include "Arena_Client.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "../Player_Account/Account_Data_Mgr.h"
#include "../Character_System/Character_Mgr.h"
#include "../Character_System/Player.h"

ARENA_MODEL* ARENA_MODEL::getInstance()
{
	static ARENA_MODEL instance_;
	return &instance_;

}

void ARENA_VIEW::onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
		return;
	auto spawnAction = cocos2d::Spawn::createWithTwoActions(cocos2d::DelayTime::create(0.1), cocos2d::CallFunc::create(CC_CALLBACK_0(ARENA_VIEW::removeFromParent, this)));
	this->runAction(spawnAction);

}

void ARENA_VIEW::onEnter()
{
	Layer::onEnter();
}

void ARENA_VIEW::onExit()
{
	Layer::onExit();
}

bool ARENA_VIEW::init()
{
	if( !Layer::init() )
		return false;
	
	_rootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/arena/arena.ExportJson");
	if( _rootWidget == nullptr )
		return false;
	addChild(_rootWidget);

	_closeButton  = dynamic_cast<cocos2d::ui::Button*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Button_9_0_1") );
	_closeButton->setVisible(true);
	_closeButton->setTouchEnabled(true);
	_closeButton->addTouchEventListener(CC_CALLBACK_2(ARENA_VIEW::onCloseCallback, this));

	auto head = dynamic_cast<cocos2d::ui::ImageView*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Image_64") );
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	auto player = (Game_Data::Player*)CHARACTER_MGR::instance()->get_character(role_id);
	int job = player->get_job();
	if (job >= 3)
		job = 3;
	cocos2d::Value pre("img/headIcon/job_");
	cocos2d::Value suff(job);
	cocos2d::Value path(pre.asString() + suff.asString() + ".png");
	head->loadTexture(path.asString());

	return true;

}

bool Game_Net::send_on_load(Game_Logic::Game_Interface& gm_interface)
{
	return false;
}