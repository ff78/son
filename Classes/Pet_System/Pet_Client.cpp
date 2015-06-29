#include "Pet_Client.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "json/document.h"

#include "../Network_Common/NetManager.h"
#include "../Network_Common/message.h"

#include "../Player_Account/Account_Data_Mgr.h"
#include "../Character_System/Character_Mgr.h"
#include "../Character_System/Player.h"

void Game_Model::PetData::load()
{
	_petConfigMap.clear();
	_petAttrMap.clear();

	rapidjson::Document doc;
	rapidjson::Document doc1;
	auto str = FileUtils::getInstance()->getStringFromFile("game_data/guard_beast_system/guard_beast_data.json");
	auto str1 = FileUtils::getInstance()->getStringFromFile("game_data/guard_beast_system/guard_beast_att.json");
	
	doc.Parse<0>(str.c_str());
	if (doc.IsArray())
	{
		for (int i = 0; i < doc.Size(); i++)
		{
			PetConfig* config = new PetConfig;

			const rapidjson::Value& v = doc[i];
			int id = cocostudio::DICTOOL->getIntValue_json(doc[i], "id");
			int star = cocostudio::DICTOOL->getIntValue_json(doc[i], "star");
			int quality = cocostudio::DICTOOL->getIntValue_json(doc[i], "Quality");
			int consume = cocostudio::DICTOOL->getIntValue_json(doc[i], "expend_gold");
			std::string name = cocostudio::DICTOOL->getStringValue_json(doc[i], "name");
			int attr = cocostudio::DICTOOL->getIntValue_json(doc[i], "att_id");
			config->attrId = attr;
			config->id = id;
			config->star = star;
			config->quality = quality;
			config->consume = consume;
			config->name = name;

			_petConfigMap.insert( std::make_pair(id, config) );

		}

	}

	doc1.Parse<0>(str1.c_str());
	if (doc1.IsArray())
	{
		for (int i = 0; i < doc1.Size(); i++)
		{
			PetAttr* attr = new PetAttr;

			const rapidjson::Value& v = doc1[i];
			int id = cocostudio::DICTOOL->getIntValue_json(doc1[i], "id");
			int health = cocostudio::DICTOOL->getIntValue_json(doc1[i], "health");
			int magic = cocostudio::DICTOOL->getIntValue_json(doc1[i], "magic");
			int attack = cocostudio::DICTOOL->getIntValue_json(doc1[i], "attack");
			int defense = cocostudio::DICTOOL->getIntValue_json(doc1[i], "defense"); 
			int hit = cocostudio::DICTOOL->getIntValue_json(doc1[i], "hit");
			int dodge = cocostudio::DICTOOL->getIntValue_json(doc1[i], "dodge");
			int crit = cocostudio::DICTOOL->getIntValue_json(doc1[i], "crit");
			int tenacity = cocostudio::DICTOOL->getIntValue_json(doc1[i], "tenacity");
			attr->id = id;
			attr->health = health;
			attr->magic = magic;
			attr->attack = attack;
			attr->defense = defense;
			attr->hit = hit;
			attr->dodge = dodge;
			attr->crit = crit;
			attr->tenacity = tenacity;

			_petAttrMap.insert(std::make_pair(id, attr));

		}

	}
}

void PET_MODEL::eventChangeData()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH, nullptr);
}

void PET_VIEW::refresh()
{
	_upgradeButton->setTouchEnabled(true),
	_upgradeButton->setBright(true); 

	loadScrollView();

	int petId = PET_MODEL::getInstance()->getSelectedPetId();
	if (petId > 0)
	{
		auto pet = PET_MODEL::getInstance()->_petConfigMap[petId];
		_petName->setString(pet->name);
		Value consume(pet->consume);
		_petConsume->setString(consume.asString());

		int attrId = pet->attrId;
		auto attr = PET_MODEL::getInstance()->_petAttrMap[attrId];

		float petPower = 0;
		int health = attr->health;
		int magic = attr->magic;
		int attack = attr->attack;
		int defense = attr->defense;
		int hit = attr->hit /*- HIT_SHOW_OFFSET*/;
		int dodge = attr->dodge;
		int crit = attr->crit /*- CRIT_SHOW_OFFSET*/;
		int tenacity = attr->tenacity;
		petPower = (0.1f*health) + (0.08f*magic) + (1.2f*attack) + (1.5f*defense) + (0.6f*hit) + (0.6f*dodge) + (0.6f*crit) + (0.6f*tenacity);
		Value petPowerV(petPower);
		_petPower->setString( petPowerV.asString() );

		int role_id = Account_Data_Mgr::instance()->get_current_role_id();
		auto player = CHARACTER_MGR::instance()->get_character(role_id);
		auto mePower = player->get_fighting_capacity();
		Value mePowerV(mePower);
		_mePower->setString( mePowerV.asString() );

		std::string preQuality("Txt_Quality_0_");
		for (int i = 0; i < QUALITY_NUM; i++)
		{
			int q = pet->quality;
			preQuality += i;
			if (i == q-1)
				_qualities[i]->setVisible(true);
			else
				_qualities[i]->setVisible(false);

		}

		std::string preStar("Image_85_");
		for (int i = 0; i < STAR_NUM; i++)
		{
			preStar += i;
			int s = pet->star;

			if (i <= s)
				_stars[i]->setVisible(true);
			else
				_stars[i]->setVisible(false);
		}

	}

}

void PET_VIEW::loadScrollView()
{

	if (_rootWidget == nullptr)return;
	_petsScrollView = dynamic_cast<cocos2d::ui::ScrollView*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Scr_Pets"));
	_petsScrollView->removeAllChildren();

	auto cell = dynamic_cast<cocos2d::ui::Layout*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Pnl_Cell"));
	auto pets = PET_MODEL::getInstance()->getPets();
	int current_pet_id = PET_MODEL::getInstance()->getCurrentPetId();

	std::vector<Game_Model::Pet>::iterator it = pets->begin();
	int index = 0;
	for (; it != pets->end();it++)
	{
		auto cellClone = cell->clone();
		auto unready = (cocos2d::ui::ImageView*)( cellClone->getChildByName("Img_Unready") );
		auto ready = (cocos2d::ui::ImageView*)( cellClone->getChildByName("Img_Ready") );
		if ((*it).id == current_pet_id){ ready->setVisible(true); }else { ready->setVisible(false); }

		cellClone->setPosition(Vec2(index*110,0) );cellClone->addTouchEventListener( CC_CALLBACK_2(PET_VIEW::onClickCellCallback, this) );
		_petsScrollView->addChild(cellClone, index, (*it).id);
		index++;

	}

}

bool PET_VIEW::init()
{
	if( !Layer::init() )return false;

	Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_REFRESH, CC_CALLBACK_0(PET_VIEW::refresh, this));


	_rootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/pet/pet.ExportJson");
	if( _rootWidget == nullptr )return false;
	addChild(_rootWidget);

	_closeButton  = dynamic_cast<cocos2d::ui::Button*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Btn_Close") );
	_closeButton->setVisible(true);_closeButton->setTouchEnabled(true);
	_closeButton->addTouchEventListener( CC_CALLBACK_2(PET_VIEW::onCloseCallback, this) );
	
	_upgradeButton = dynamic_cast<cocos2d::ui::Button*>( cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Btn_Upgrade") );
	_upgradeButton->setVisible(true);/*_upgradeButton->setTouchEnabled(true);*/
	_upgradeButton->addTouchEventListener( CC_CALLBACK_2(PET_VIEW::onUpgradeCallback, this) );

	_goButton = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Button_Go"));
	_goButton->setVisible(true); _goButton->setTouchEnabled(true);
	_goButton->addTouchEventListener( CC_CALLBACK_2(PET_VIEW::onGoCallback, this) );

	_petPower = dynamic_cast<cocos2d::ui::Text*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Label_95_0"));
	_mePower = dynamic_cast<cocos2d::ui::Text*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Label_95_0_4_5"));

	
	std::string preQuality("Txt_Quality_0_");
	for (int i = 0; i < QUALITY_NUM; i++)
	{
		Value iInt(i);
		std::string iStr( iInt.asString() );
		_qualities[i] = dynamic_cast<cocos2d::ui::Text*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, preQuality + iStr));
	}

	std::string preStar("Image_85_");
	for (int i = 0; i < STAR_NUM; i++)
	{
		Value iInt(i);
		std::string iStr(iInt.asString());
		_stars[i] = dynamic_cast<cocos2d::ui::ImageView*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, preStar + iStr));
	}
	//_starImage1 = dynamic_cast<cocos2d::ui::ImageView*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Image_85_0"));
	//_starImage1->setVisible(true);

	//_starImage2 = dynamic_cast<cocos2d::ui::ImageView*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Image_85_1"));
	//_starImage2->setVisible(false);

	//_starImage3 = dynamic_cast<cocos2d::ui::ImageView*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Image_85_2"));
	//_starImage3->setVisible(false);

	//_starImage4 = dynamic_cast<cocos2d::ui::ImageView*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Image_85_3"));
	//_starImage4->setVisible(false);

	//_starImage5 = dynamic_cast<cocos2d::ui::ImageView*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Image_85_4"));
	//_starImage5->setVisible(false);
	_petName = dynamic_cast<cocos2d::ui::Text*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Label_81"));
	_petConsume = dynamic_cast<cocos2d::ui::Text*>(cocos2d::ui::Helper::seekWidgetByName(_rootWidget, "Label_120_1"));
	int petId = PET_MODEL::getInstance()->getCurrentPetId();
	if (petId > 0)
	{
		auto pet = PET_MODEL::getInstance()->_petConfigMap[petId];
		_petName->setString(pet->name);
		Value consume(pet->consume);
		_petConsume->setString(consume.asString());


		int attrId = pet->attrId;
		auto attr = PET_MODEL::getInstance()->_petAttrMap[attrId];

		float petPower = 0;
		int health = attr->health;
		int magic = attr->magic;
		int attack = attr->attack;
		int defense = attr->defense;
		int hit = attr->hit/* - HIT_SHOW_OFFSET*/;
		int dodge = attr->dodge;
		int crit = attr->crit/* - CRIT_SHOW_OFFSET*/;
		int tenacity = attr->tenacity;
		petPower = (0.1f*health) + (0.08f*magic) + (1.2f*attack) + (1.5f*defense) + (0.6f*hit) + (0.6f*dodge) + (0.6f*crit) + (0.6f*tenacity);
		Value petPowerV(petPower);
		_petPower->setString(petPowerV.asString());

		int role_id = Account_Data_Mgr::instance()->get_current_role_id();
		auto player = CHARACTER_MGR::instance()->get_character(role_id);
		auto mePower = player->get_fighting_capacity();
		Value mePowerV(mePower);
		_mePower->setString(mePowerV.asString());


		std::string preQuality("Txt_Quality_0_");
		for (int i = 0; i < QUALITY_NUM; i++)
		{
			int q = pet->quality;
			preQuality += i;
			if (i==q-1)
				_qualities[i]->setVisible(true);
			else
				_qualities[i]->setVisible(false);

		}

		std::string preStar("Image_85_");
		for (int i = 0; i < STAR_NUM; i++)
		{
			preStar += i;
			int s = pet->star;

			if (i <= s)
				_stars[i]->setVisible(true);
			else
				_stars[i]->setVisible(false);
		}
	}

	loadScrollView();

    return true;

}

void PET_VIEW::onEnter()
{
	Layer::onEnter();
}

void PET_VIEW::onExit()
{
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_REFRESH);
}

void PET_VIEW::onUpgradeCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type != cocos2d::ui::Widget::TouchEventType::ENDED)return;

	_upgradeButton->setTouchEnabled(false), _upgradeButton->setBright(false);
    std::vector<uint64> para;Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_PET_SEND_UPGRADE, para);

}

void PET_VIEW::onGoCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)return;

	std::vector<uint64> para; Game_Logic::Game_Content_Interface::instance()->exec_interface(EVENT_PET_SEND_CHANGE, para);


}

void PET_VIEW::onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)return;

	auto spawnAction = cocos2d::Spawn::createWithTwoActions(cocos2d::DelayTime::create(0.1), cocos2d::CallFunc::create(CC_CALLBACK_0(PET_VIEW::removeFromParent, this)));
	this->runAction(spawnAction);
}

void PET_VIEW::onClickCellCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type!=cocos2d::ui::Widget::TouchEventType::ENDED)return;

	auto cell = (cocos2d::ui::Layout*)pSender;
	PET_MODEL::getInstance()->setSelectedPetId(cell->getTag());
	int selected_pet_id = PET_MODEL::getInstance()->getSelectedPetId();
	if (PET_MODEL::getInstance()->getCurrentPetId() == selected_pet_id)
	{
		_upgradeButton->setTouchEnabled(false),_upgradeButton->setBright(false);
	}
	else
	{
		_upgradeButton->setTouchEnabled(true), _upgradeButton->setBright(true);
	}
	auto children = _petsScrollView->getInnerContainer()->getChildren();
	for (auto& child:children)
	{
		auto c = child->getChildByName("Img_Cursor");
		c->setVisible(false);
	}
	auto cursor = (cocos2d::ui::ImageView*)( cell->getChildByName("Img_Cursor") );
	cursor->setVisible(true);
}

bool PET_NET::on_load(Game_Logic::Game_Interface& gm_interface)
{
	char body[256] = { 0 };
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int			player_id;
	int			pet_id;
	uint64		pet_guid;
	body_ms >> player_id;
	body_ms >> pet_id;
	body_ms >> pet_guid;

	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	auto player = CHARACTER_MGR::instance()->get_character(role_id);
	player->add_pet(pet_guid,pet_id);
	auto pets = PET_MODEL::getInstance()->getPets();
	Game_Model::Pet pet;
	pet.guid = pet_guid;
	pet.id = pet_id;
	pets->push_back(pet);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_CHANGE_DATA, nullptr);

	return true;
}

bool PET_NET::send_upgrade(Game_Logic::Game_Interface& gm_interface)
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();

	int pet_id = PET_MODEL::getInstance()->getSelectedPetId();
	auto pets = PET_MODEL::getInstance()->getPets();
	std::vector<Game_Model::Pet>::iterator it = pets->begin();
	uint64 guid;
	for (; it != pets->end();it++)
	{
		if ((*it).id == pet_id)
		{
			guid = (*it).guid;
		}
	}
	char body[256] = { 0 };
	message_stream body_ms( body, sizeof(body) );
	body_ms << C2S_GUARD_BEAST_LV_UP;
	body_ms << player_id;
	body_ms << guid;

	CNetManager::GetMe()->send_msg(body_ms);

	return true;

}

bool PET_NET::on_upgrade(Game_Logic::Game_Interface& gm_interface)
{
	char body[256] = { 0 };
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int player_id;
	int old_pet_id;
	int new_pet_id;
	int exp;
	body_ms >> player_id;
	body_ms >> old_pet_id;
	body_ms >> new_pet_id;
	body_ms >> exp;

	if ( !new_pet_id||(old_pet_id == new_pet_id) )return false;

	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	auto player = CHARACTER_MGR::instance()->get_character(role_id);
	player->change_one_pet_of_list_by_id(old_pet_id,new_pet_id);

	auto pets = PET_MODEL::getInstance()->getPets();

	std::vector<Game_Model::Pet>::iterator it = pets->begin();
	for (; it != pets->end();it++)
	{
		if( (*it).id == old_pet_id ){ (*it).id = new_pet_id; break; }
	}

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_CHANGE_DATA, nullptr);

	return true;

}

bool PET_NET::send_change_state(Game_Logic::Game_Interface& gm_interface)
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();

	int pet_id = PET_MODEL::getInstance()->getSelectedPetId();
	auto pets = PET_MODEL::getInstance()->getPets();
	std::vector<Game_Model::Pet>::iterator it = pets->begin();
	uint64 guid;
	for (; it != pets->end(); it++)
	{
		if ((*it).id == pet_id)
		{
			guid = (*it).guid;
		}
	}
	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));
	body_ms << C2S_GUARD_BEAST_CHANGE_STATE;
	body_ms << player_id;
	body_ms << guid;

	CNetManager::GetMe()->send_msg(body_ms);

	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_CHANGE_DATA, nullptr);

	return true;
}

bool PET_NET::on_change_state(Game_Logic::Game_Interface& gm_interface)
{
	char body[256] = { 0 };
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int			player_id;
	int			result;

	body_ms >> player_id;
	body_ms >> result;

	if (result)
	{
		int selected_id = PET_MODEL::getInstance()->getSelectedPetId();
		PET_MODEL::getInstance()->setCurrentPetId(selected_id);
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        player->set_cur_pet_id(selected_id);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_CHANGE_DATA, nullptr);
	}
	else
	{

		return false;
	}

	return true;

}
