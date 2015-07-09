#include "Endless_Client.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "../Player_Account/Account_Data_Mgr.h"
#include "../Character_System/Character_Mgr.h"
#include "../Character_System/Player.h"
#include "EndlessPrayLayer.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

ENDLESSDATA_MODEL* ENDLESSDATA_MODEL::getInstance()
{
	static ENDLESSDATA_MODEL instance_;
	return &instance_;

}

void ENDLESS_VIEW::onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
		return;
	auto spawnAction = cocos2d::Spawn::createWithTwoActions(cocos2d::DelayTime::create(0.01), cocos2d::CallFunc::create(CC_CALLBACK_0(ENDLESS_VIEW::removeFromParent, this)));
	this->runAction(spawnAction);

}

void ENDLESS_VIEW::onEnter()
{
	Layer::onEnter();
}

void ENDLESS_VIEW::onExit()
{
	Layer::onExit();
}

bool ENDLESS_VIEW::init()
{
	if( !Layer::init() )
		return false;
	
	_rootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/endlesstower.json");
	if( _rootWidget == nullptr )
		return false;
	addChild(_rootWidget);

	_closeButton  = dynamic_cast<cocos2d::ui::Button*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Button_9_0_0") );
	_closeButton->setVisible(true);
	_closeButton->setTouchEnabled(true);
	_closeButton->addTouchEventListener(CC_CALLBACK_2(ENDLESS_VIEW::onCloseCallback, this));

	_goButton = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Button_19"));
	_goButton->setVisible(true);
	_goButton->setTouchEnabled(true);
	_goButton->addTouchEventListener(CC_CALLBACK_2(ENDLESS_VIEW::onGoCallback, this));
	
    prayButton = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Button_20"));
    prayButton->addTouchEventListener(CC_CALLBACK_2(ENDLESS_VIEW::onPrayCallback, this));
    
    auto nameLabel = dynamic_cast<Text *>(Helper::seekWidgetByName(_rootWidget, "Label_26"));
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    nameLabel->setString(player->get_character_name());
    
    auto head = dynamic_cast<ImageView*>(Helper::seekWidgetByName(_rootWidget, "Image_25"));
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

void Game_View::EndlessLayer::onGoCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
		return;
	auto spawnAction = cocos2d::Spawn::createWithTwoActions(cocos2d::DelayTime::create(0.1), cocos2d::CallFunc::create(CC_CALLBACK_0(ENDLESS_VIEW::removeFromParent, this)));
	this->runAction(spawnAction);

	vector<uint64> para;
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	para.push_back(player_id);
	para.push_back(5000);

	Game_Logic::Game_Content_Interface::instance()->exec_interface("sendrequireallstage", para);
}
void Game_View::EndlessLayer::onPrayCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
        return;
    auto prayLayer = EndlessPrayLayer::create();
    addChild(prayLayer);
}
