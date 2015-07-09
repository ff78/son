#include "God_Client.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "../Network_Common/NetManager.h"
#include "../Network_Common/message.h"

#include "../Player_Account/Account_Data_Mgr.h"
#include "../Character_System/Character_Mgr.h"
#include "../Character_System/Player.h"
#include "God_Weapon_Config_Mgr.h"
#include "ClientLogic/Utils/BaseUtils.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

void GOD_MODEL::load()
{
    blackColossus->readColossus(getCurrentGodId(), "GameData/data_ClsSkill.json");
}

std::map<int, ClsSkill>& Game_Model::GodData::getSkills()
{
	return blackColossus->clsSkills;
}

void GOD_VIEW::eventOnUpdate()
{
	if (_upgradeButton != nullptr)
	{
		_upgradeButton->setTouchEnabled(true);
		_upgradeButton->setBright(true);
	}
    GOD_MODEL::getInstance()->blackColossus->readColossus(GOD_MODEL::getInstance()->getCurrentGodId(), "GameData/data_ClsSkill.json");
	int godId = GOD_MODEL::getInstance()->getCurrentGodId();

	auto config = GOD_WEAPON_CONFIG_MGR::instance()->get_god_weapon_config_data(godId);
	if (config == NULL)return;

	_level = config->level;
	_consume = config->up_money;
	auto path = config->anim_path;
	std::string str("armature/");
	str += path;
	str += ".ExportJson";
	loadData(_level, _consume);
}

void GOD_VIEW::loadData(int level, int consume)
{
	Value vLevel(level);
	Value vConsume(consume);

	if (_levelText!=nullptr)_levelText->setString( vLevel.asString() );
	if(_consumeText!=nullptr)_consumeText->setString( vConsume.asString() );
}

void GOD_VIEW::update(float dt)
{

}

bool GOD_VIEW::init()
{
	if( !Layer::init() )return false;

	Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_ON_UPDATE_SUCCESS, CC_CALLBACK_0(GOD_VIEW::eventOnUpdate, this) );

	_rootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/godweapon.json");
	if( _rootWidget == nullptr )return false;
	addChild(_rootWidget);

	_closeButton  = dynamic_cast<cocos2d::ui::Button*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Button_9_0") );
	_closeButton->setVisible(true);_closeButton->setTouchEnabled(true);
	_closeButton->addTouchEventListener(CC_CALLBACK_2(GOD_VIEW::onCloseCallback, this));
	
	_upgradeButton = dynamic_cast<cocos2d::ui::Button*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Button_119") );
	_upgradeButton->setVisible(false);_upgradeButton->setTouchEnabled(false);
	_upgradeButton->addTouchEventListener(CC_CALLBACK_2(GOD_VIEW::onUpgradeCallback, this));

	_levelText = dynamic_cast<cocos2d::ui::Text*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Label_5_0") );
	_consumeText = dynamic_cast<cocos2d::ui::Text*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Label_120_1") );
    
    _skillScroll = dynamic_cast<cocos2d::ui::ScrollView*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "ScrollView_41"));
    _skillScroll->getInnerContainer()->setAnchorPoint(Vec2(0, 1));
    _skillScroll->getInnerContainer()->removeAllChildren();
	
	int godId = GOD_MODEL::getInstance()->getCurrentGodId();
	if (godId <= 0)
	{
//		loadData(0, 0);
        _levelText->setVisible(false);
        _consumeText->setVisible(false);
        
        
		_upgradeButton->setBright(false);
        _upgradeButton->setEnabled(false);
        _upgradeButton->setTouchEnabled(false);
        
        int role_id = Account_Data_Mgr::instance()->get_current_role_id();
        auto player = CHARACTER_MGR::instance()->get_character(role_id);
        std::string name(player->get_character_name());
        auto upGradeDesc = dynamic_cast<cocos2d::ui::Text*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Label_120") );
        upGradeDesc->setColor(Color3B::RED);
        upGradeDesc->setString(name + "等级提升到3级可获得天降神兵！");
        auto skillName = dynamic_cast<cocos2d::ui::Text*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Label_73") );
        skillName->setColor(Color3B::RED);
        skillName->setString("3级获得");
        auto skillDes = dynamic_cast<cocos2d::ui::Text*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Label_73_0") );
        skillDes->setVisible(false);
        auto la5 = dynamic_cast<cocos2d::ui::Text*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Label_5") );
        la5->setVisible(false);
        auto coinIcon = dynamic_cast<cocos2d::ui::ImageView*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Image_125"));
        coinIcon->setVisible(false);
        
        cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/wdj_quantao.ExportJson");
        _armatureRepeat = cocostudio::Armature::create("wdj_quantao");
        _armatureRepeat->setScale(1.5);
        _armatureRepeat->getAnimation()->playWithIndex(0);
        _armatureRepeat->setPosition( Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2-260) );
        this->addChild(_armatureRepeat,999);
        _armatureRepeat->setColor(Color3B::GRAY);
		return true;
	}

	auto config = GOD_WEAPON_CONFIG_MGR::instance()->get_god_weapon_config_data(godId);
	if (config == NULL)return true;
	_level = config->level;
	_consume = config->up_money;
	auto path = config->anim_path;
	std::string str("armature/");
	str += path;
	str += ".ExportJson";
	loadData(_level, _consume);
	
	if (_level >= 3)_upgradeButton->setBright(false);

	cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo(str);
	_armatureRepeat = cocostudio::Armature::create(path);
    _armatureRepeat->setScale(1.5);
	_armatureRepeat->getAnimation()->play("stand");
	_armatureRepeat->setPosition( Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2-260) );
    _armatureRepeat->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(GodLayer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	this->addChild(_armatureRepeat,999);

    auto skills = GOD_MODEL::getInstance()->blackColossus->clsSkills;
    int i = 0;
    auto tempBtn = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Selected_Skill_4th_Btn_0"));
    auto btnSize = tempBtn->getContentSize();
    _skillScroll->setInnerContainerSize(Size(_skillScroll->getContentSize().width,skills.size()*0.8*btnSize.height));
    auto scrollSize = _skillScroll->getInnerContainerSize();
    for (auto skill : skills) {
        auto skillBtn = tempBtn->clone();
        skillBtn->setPosition(Vec2(scrollSize.width/2, scrollSize.height-btnSize.height*0.8/2-i*(btnSize.height*0.8)));
        skillBtn->setEnabled(true);
        skillBtn->setVisible(true);
        skillBtn->setTag(i);
        skillBtn->addTouchEventListener(CC_CALLBACK_2(GOD_VIEW::onClickSkillCell, this));
        auto img = dynamic_cast<ImageView*>(skillBtn->getChildByName("Image_42"));
        img->loadTexture("img/joystick/"+skill.second.getIcon()+".png");
        i++;
        _skillScroll->getInnerContainer()->addChild(skillBtn);
    }
    _skillScroll->jumpToBottom();
    
//	_skillButton1 = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Selected_Skill_4th_Btn_0"));
//	_skillButton1->setTag(1);
//	_skillButton1->addTouchEventListener(CC_CALLBACK_2(GOD_VIEW::onClickSkillCell, this));
//
//	_skillButton2 = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Selected_Skill_4th_Btn_0_1"));
//	_skillButton2->setTag(2);
//	_skillButton2->addTouchEventListener(CC_CALLBACK_2(GOD_VIEW::onClickSkillCell, this));
//
//	_skillButton3 = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Selected_Skill_4th_Btn_0_2"));
//	_skillButton3->setTag(3);
//	_skillButton3->addTouchEventListener(CC_CALLBACK_2(GOD_VIEW::onClickSkillCell, this));
//
//	_skillButton4 = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Selected_Skill_4th_Btn_0_3"));
//	_skillButton4->setTag(4);
//	_skillButton4->addTouchEventListener(CC_CALLBACK_2(GOD_VIEW::onClickSkillCell, this));

	_descText = dynamic_cast<cocos2d::ui::Text*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Label_73_0"));

	return true;

}

void GOD_VIEW::onEnter(){ Layer::onEnter(); }

void GOD_VIEW::onExit()
{
	//_rootWidget = nullptr; _closeButton = nullptr; _upgradeButton = nullptr;
	//_levelText = nullptr; _consumeText = nullptr; _armatureRepeat = nullptr;
	Layer::onExit();
    getEventDispatcher()->removeCustomEventListeners(EVENT_ON_UPDATE_SUCCESS);
}

void GOD_VIEW::onClickSkillCell(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)return;
	int index = ( (cocos2d::ui::Button*)pSender )->getTag();
	auto skills = GOD_MODEL::getInstance()->blackColossus->clsSkills;
	ClsSkill skill;
    int i = 0;
    for (auto s : skills) {
        if (i==index) {
            skill = s.second;
            break;
        }
        i++;
    }
    if (i>=skills.size()) {
        return;
    }
    
    for (auto obj : _skillScroll->getInnerContainer()->getChildren()) {
        auto btn = dynamic_cast<Button *>(obj);
        btn->setBrightStyle(ui::Widget::BrightStyle::NORMAL);
    }
    dynamic_cast<Button *>(pSender)->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
    
	auto name = skill.getActionName();
    auto names = YNBaseUtil::splitString(name, ";");
	auto desc = skill.getDesc();
//	std::vector<std::string> actionNames;
//	actionNames.push_back(name);

	if (_armatureRepeat != nullptr)
		_armatureRepeat->getAnimation()->playWithNames(names);
	if (_descText != nullptr)
		_descText->setString(desc);

}

void GOD_VIEW::onUpgradeCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type != cocos2d::ui::Widget::TouchEventType::ENDED)return;

	_upgradeButton->setTouchEnabled(false);
	_upgradeButton->setBright(false);
    std::vector<uint64> para;Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_GOD_SEND_UPGRADE, para);

}

void GOD_VIEW::onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)return;

	auto spawnAction = cocos2d::Spawn::createWithTwoActions( cocos2d::DelayTime::create(0.1), cocos2d::CallFunc::create( CC_CALLBACK_0( GOD_VIEW::removeFromParent, this ) ) );
	this->runAction(spawnAction);
}
void GOD_VIEW::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if (movementType == MovementEventType::COMPLETE)
    {
        if (movementID != "stand") {
            armature->getAnimation()->play("stand");
        }
    }
}

bool GOD_NET::on_load(Game_Logic::Game_Interface& gm_interface)
{
	char body[256] = { 0 };
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int			player_id;
	int			god_id;
	body_ms >> player_id;
	body_ms >> god_id;
	if (god_id > 0)
	{
		GOD_MODEL::getInstance()->setCurrentGodId(god_id);
		int role_id = Account_Data_Mgr::instance()->get_current_role_id();
		auto player = CHARACTER_MGR::instance()->get_character(role_id);
		player->set_cur_god_id(god_id);

	}
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_ON_UPDATE_SUCCESS, nullptr);

	return true;
}

bool GOD_NET::send_upgrade(Game_Logic::Game_Interface& gm_interface)
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();

	char body[256] = { 0 };
	message_stream body_ms( body, sizeof(body) );
	body_ms << C2S_GOD_WEAPON_LEVEL_UP;
	body_ms << player_id;

	CNetManager::GetMe()->send_msg(body_ms);

	return true;

}

bool GOD_NET::on_upgrade(Game_Logic::Game_Interface& gm_interface)
{
	char body[256] = { 0 };
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	int		 player_id;
	int		 god_id;
	body_ms>>player_id;
	body_ms>>god_id;

	GOD_MODEL::getInstance()->setCurrentGodId(god_id);
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	auto player = CHARACTER_MGR::instance()->get_character(role_id);
	player->set_cur_god_id(god_id);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_ON_UPDATE_SUCCESS, nullptr);
    
	return true;

}