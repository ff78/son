#include "SimpleAudioEngine.h"
#include "Actor_Layer.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/FightNpc.h"
#include "Character_System/Player.h"
#include "Common/Utils.h"
#include <fstream>
#include "Play_System/Formula_Function_Instance_Client.h"
//#include "AI_Controller.h"
//#include "NPC_Cfg_Data_Mgr.h"
//#include "Monster_Cfg_Data_Mgr.h"
//#include "Monster_Wave_Cfg_Data_Mgr.h"
#include "Play_System/Instance_Data_Mgr.h"
#include "Game_Interface/game_event_mgr.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
//#include "Skill_System/Skill/Skill_Logic.h"
//#include "Runtime.h"
#include "Player_Account/Account_Data_Mgr.h"
//#include "Active_Area_Delegate.h"
#include "UI/City_Scene.h"
#include "UI_Interface/UI_MainMenu_Layer.h"
#include "Game_Interface/game_event_response.h"
#include "Character_System/CommonNpc.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player_Logic_Cl.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
//#include "Fight_System/Offline_Fight_Mgr_Cl.h"
#include "UI_Interface/UI_Tips_Layer.h"
//#include "Hit_Test_Manager.h"
//#include "GameUI_Layer.h"
//#include "Effect_Cfg_Data_Mgr.h"
#include "Game/Audio_Manager.h"
#include "Common/Utils.h"
//#include "Unique_Skill.h"
//#include "Enter_Game_Flash_Layer.h"
//#include "Common/Utils.h"

//#include "Real_Time_Operator.h"
using namespace std;
using namespace Game_Data;



namespace UI
{
	bool Actor_Layer::is_played_flash_ = false;

	Actor_Layer::Actor_Layer():
		//delegate_(NULL),
		//background_delegate_(NULL),
		//primary_actor_(NULL),
		//pet_(NULL),
		//opponent_(NULL),
		is_in_portal_(false),
		current_wave_(-1),
		monster_waves_(-1),
		//active_area_delegate_(NULL),
		pre_locked_screen_(false),
		is_auto_moving_(false),
		need_pre_locked_screen_moving_(false),
		pre_locked_finish_call_back_(NULL),
		real_time_operator_(NULL)
	{
		//scene_type_ = Runtime::instance()->get_scene_type();
	}

	Actor_Layer::~Actor_Layer()
	{
		if(real_time_operator_){
			//delete real_time_operator_;
			//real_time_operator_ = NULL;
		}
	}

	bool Actor_Layer::init()
	{
		//if(get_is_in_city_scene()){
			char file_name[80];
//			Runtime::instance()->get_scene_config_file(file_name);
			Utils::get_value_by_file(file_name, scene_config );


			if(! scene_config){
				CCLOG ("error:load config file %s \n", file_name);
			}
			init_primay_actor();
			pre_init_npc();
			init_npc();
			init_portal(scene_config);
			this->scheduleUpdate();
			return true;
		//}
		#if 0
		else if(get_is_in_instance_scene()){
			init_primay_actor();
			init_pet();
			pre_init_monster();
			this->scheduleUpdate();
			return true;
		}
		else if(get_is_in_offline_pk_scene()){
			init_primay_actor();
			init_asynchronous_battle_opponent();
			locked_screen(true, 1);

			//pre_to_start_asynchronous_battle();
			return true;
		}
		else if(get_is_in_real_time_pk_scene()){
			active_area_delegate_->set_Active_screen((float)0 , Director::getInstance()->getWinSize().width);
			init_primay_actor();
			init_real_time_pk_opponent();
#if 0
			if(Runtime::instance()->get_primary_actor_born_in_the_right_side()){
				float primary_actor_x, primary_actor_y, opponent_x, opponent_y;
				primary_actor_->get_logic_postion(primary_actor_x, primary_actor_y);
				opponent_->get_logic_postion(opponent_x, opponent_y);
				primary_actor_->set_logic_postion(opponent_x, opponent_y);
				opponent_->set_logic_postion(primary_actor_x, primary_actor_y);
				primary_actor_->set_direction(Dynamic_Sprite::LEFT);
				opponent_->set_direction(Dynamic_Sprite::RIGHT);
			}
#endif			
			schedule(schedule_selector(Actor_Layer::update_real_time_operator));
			return true;
		}
#endif
		return false;
	}

	void Actor_Layer::pre_init_monster()
	{
		std::list<Game_Data::Game_Command_Element>  monster_waves_list;
		//if(!Runtime::instance()->is_in_city_scene())
		//	Game_Utils::instance()->load_current_monster_wave_data( monster_waves_list );
#if 0
		vector<uint> para;
		std::list<Game_Data::Game_Command_Element>::iterator itc;
		std::list<Game_Data::Game_Element>::iterator ite;
		std::list<Game_Data::Game_Element> tmp_monster_list;
		int i = 0;
		for (itc= monster_waves_list.begin(); itc != monster_waves_list.end(); ++ itc ) // total wave
		{
			CCLOG("monster_waves_list[%d]\n",i);
			std::vector<int> mon_lst;
			(*itc).get_game_element_data(tmp_monster_list);
			for( ite = tmp_monster_list.begin(); ite != tmp_monster_list.end(); ++ite )
			{
				para.clear();
				(*ite).get_para_list_in_vector( para );
				if( para.size() < 6 )
					continue;
				int monster_id = para[0];//monster id
				int center_x = para[1];//x pos
				int center_y = para[2];//y pos
				int radius = para[3]; //radius of monster birth area
				int monster_counts = para[4]; //monster counts
				para[5]; //interval time

				//monster_config* config = Monster_Cfg_Data_Mgr::instance()->get_monster_config(monster_id);
				int sprite_prototype_id = config->sprite_prototype_id_;
				int ai_type_id = config->ai_type_id_;
				int attribute_id = config->attribute_id_;
				int attribute_lv = config->attribute_lv_;
				int string_id = config->monster_name_;
				const char * monster_name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(string_id);
				string_id = config->title_;
				const char * title = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(string_id);
				int sprite_id;
				float born_point_x;
				float born_point_y;
				CCLOG("\t create monster(%d,%d,%d,%d,%d)\n",monster_id,center_x,center_y,radius,monster_counts);
				for(int j = 0; j < monster_counts; j++){
					get_born_position(born_point_x, born_point_y, center_x, center_y, radius);
					Monster* monster = Monster::create(sprite_prototype_id, sprite_id , born_point_x, born_point_y);
					monster->set_name(monster_name);
					monster->set_static_id(monster_id);
					monster->set_hit_test_delegate(this);
					monster->set_ai_type_id(ai_type_id);
					monster->set_attribute_id(attribute_id);
					monster->set_attribute_lv(attribute_lv);
					this->addChild(monster,0, sprite_id);
					monster->set_logic_postion(born_point_x, born_point_y);
					monster->setVisible(false);
					mon_lst.push_back(sprite_id);
				}
			}
			monster_wave_map_.insert(std::pair < int, std::vector < int > >(i, mon_lst));
			i++;
		}
		monster_waves_ = i;
#endif
	}

	void Actor_Layer::pre_init_npc()
	{
#if 0
		Json::Value npcs = NPC_Cfg_Data_Mgr::shared_instance()->get_cfg_data();
		int current_scene_id = Runtime::instance()->get_scene_id();
		int size = npcs.size();
		int sprite_prototype_id;
		int sprite_id;
		float born_point_x;
		float born_point_y;
		int touch_width;
		int touch_height;
		int scene_id;

		Json::Value::Members members = npcs.getMemberNames();  
		for (Json::Value::Members::iterator it = members.begin();  
			it != members.end(); ++it) {  
				std::string member_name = *it;  
				Json::Value &npc_config = npcs[member_name.c_str()];
				scene_id = npc_config["scene_id"].asInt();
				if(scene_id != current_scene_id){
					continue;
				}
				sprite_prototype_id = npc_config["sprite_prototype_id"].asInt();
				born_point_x = npc_config["x"].asFloat();
				born_point_y = npc_config["y"].asFloat();
				touch_width = npc_config["touch_width"].asInt();
				touch_height = npc_config["touch_height"].asInt();
				int string_id = npc_config["name"].asInt();
				const char * name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(string_id);
				string_id = npc_config["title"].asInt();
				const char * title = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(string_id);
				const char * info_path =  npc_config["info_path"].asCString();
				NPC* npc = NPC::create(sprite_prototype_id, sprite_id , born_point_x, born_point_y);
				npc->set_npc_delegate(this);
				npc->set_backgroud_delegate(background_delegate_);
				npc->set_name(name);
				npc->set_title(title);
				npc->set_info(info_path);
				npc->set_touch_args(touch_width, touch_height);
				this->addChild(npc,0, sprite_id);
				npc_map_.insert(NPC_Pair(sprite_id, npc));
				npc->setVisible(false);


				//to do.  场景配置中的id、lv，动态生成的sID for NPC System�?				int id = npc_config["id"].asInt();
				int lv = npc_config["level"].asInt();
				int sID = sprite_id;

				CommonNpc* pCharacter = new CommonNpc;
				pCharacter->set_database_character_id(sprite_id);
				pCharacter->set_character_type(Game_Logic::Game_Event::EVENT_TYPE_NPC);
				pCharacter->init_attr_data(id, lv);
				CHARACTER_MGR::instance()->insert_character(pCharacter);
		}
#endif
	}

	bool Actor_Layer::init_monster()
	{
#if 0
		map< int, vector < int > >::iterator iter;
		iter = monster_wave_map_.find(current_wave_);
		vector<int> mon_lst;
		if(iter != monster_wave_map_.end()){
			mon_lst =iter->second;
		}
		else{
			CCLOG("monster_wave_map_ can not find current_wave_:%d",current_wave_);
			return false;
		}
		int size = mon_lst.size();

		int sprite_prototype_id;
		int ai_type_id;
		//	  int sprite_id;
		float born_point_x;
		float born_point_y;
		//add for 属�?		int attribute_id;
		int attribute_lv;

		vector<uint64> para;
		monster_prototype_map_.clear();
		for(int i = 0; i < size; i++){
			int sprite_id = mon_lst[i];
			Monster* monster = get_monstor(sprite_id);
			sprite_prototype_id = monster->sprite_prototype_id();
			ai_type_id = monster->get_ai_type_id();
			monster->setVisible(true);
			monster_list_.push_back(sprite_id);
			monster->set_adjust_delegate(this);
			monster->get_logic_postion(born_point_x,born_point_y);
			AI_Controller::instance()->add_child(ai_type_id, sprite_id, born_point_x, born_point_y);

			//add for 属�?			attribute_id = monster->get_attribute_id();
			attribute_lv = monster->get_attribute_lv();

			//todo: here need change, invalide way to config
			FightNpc* pCharacter = new FightNpc;
			pCharacter->set_database_character_id(sprite_id);
			pCharacter->set_character_type(Game_Logic::Game_Event::EVENT_TYPE_MONSTER);
			pCharacter->init_attr_data(attribute_id, attribute_lv);
			CHARACTER_MGR::instance()->insert_character(pCharacter);

			//记录怪物信息
			AI_Controller::instance()->set_max_hp(sprite_id, pCharacter->get_character_max_hp());
			AI_Controller::instance()->set_cur_hp(sprite_id, pCharacter->get_character_cur_hp());
			int sprite_static_id = monster->get_static_id_();
			map<int, int>::iterator iter;
			iter = monster_prototype_map_.find(sprite_static_id);
			if(iter != monster_prototype_map_.end()){
				iter->second +=1;
			}
			else{
				monster_prototype_map_.insert(std::pair<int ,int>(sprite_static_id, 1));
			}
		}
		para.clear();
		Game_Logic::Game_Content_Interface::instance()->exec_interface("finishmonstercreate", para);
#endif
		return true;
	}

	bool Actor_Layer::init_npc()
	{
#if 0
		NPC_Map::iterator it;
		for( it = npc_map_.begin(); it != npc_map_.end(); it++){
			NPC * npc = it->second;
			Point bornPoint = npc->get_birth_place();
			npc->set_logic_postion(bornPoint.x, bornPoint.y);
			npc->setVisible(true);
		}
#endif
		return true;
	}

	bool Actor_Layer::init_portal( Json::Value &json_value )
	{
#if 0
		Json::Value &portals = json_value["portals"];
		int size = portals.size();
		for(int i = 0; i < size; i++){
			Json::Value &portal_config = portals[i];
			int portal_x = portal_config["x"].asInt();
			int portal_y = portal_config["y"].asInt();
			int portal_id = portal_config["id"].asInt();
			int radius = portal_config["radius"].asInt();

			cocos2d::Sprite *portal = cocos2d::Sprite::create();
			Effect_Cfg_Data_Mgr::instance()->get_effect(portal, "2010");
			portal->setPosition(Vec2(portal_x,portal_y-50));
			portal->setZOrder(720 - portal_y);
			portal->setScale(5.f);
			portal->setAnchorPoint(Vec2(0.5, 0));
			addChild(portal);
		}
#endif
		return true;
	}

	bool Actor_Layer::init_primay_actor()
	{
#if 0
		Runtime::instance()->create_primary_actor();
		primary_actor_ = Runtime::instance()->get_primary_actor();
		primary_actor_->set_direction(Dynamic_Sprite::RIGHT);
		primary_actor_->set_hit_test_delegate(this);
		primary_actor_->set_adjust_delegate(this);
//		primary_actor_->clean_status();
		this->addChild(primary_actor_,1, primary_actor_->sprite_id());
		primary_actor_->set_logic_postion(400.f,200.f);
#endif
		return true;
	}


	bool Actor_Layer::init_pet()
	{
#if 0
		int character_id = Game_Utils::instance()->get_lieutenant_id();
		Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(character_id);
		if (!character)
		{
			return false;
		}

		Game_Data::Player_Base_Attr_Config_Data* config = character->get_base_attr_config_data();
		if (!config)
		{
			return false;
		}

		pet_ = UI::Pet::create(config->get_player_model(), character_id, primary_actor_);
		Game_Utils::instance()->set_sprite_name(pet_,character->get_character_name());
		this->addChild(pet_,1, pet_->sprite_id());
		pet_->set_logic_postion(600.f,200.f);
		pet_->set_hit_test_delegate(this);
		pet_->set_is_hosting(true);
#endif
		return true;
	}


	bool Actor_Layer::init_asynchronous_battle_opponent()
	{
#if 0
		opponent_ = Actor::create(Runtime::instance()->get_opponent_prototype_id(), Runtime::instance()->get_opponent_sprite_id());
		opponent_->set_direction(Dynamic_Sprite::LEFT);
		opponent_->set_hit_test_delegate(this);
		opponent_->set_adjust_delegate(this);
		opponent_->clean_status();
		this->addChild(opponent_,1, opponent_->sprite_id());
		opponent_->set_logic_postion(1000.f,200.f);

		Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(Runtime::instance()->get_opponent_sprite_id());
		if (character)
		{
			opponent_->set_name(character->get_character_name());
		}
#endif
		return true;
	}

	bool Actor_Layer::init_real_time_pk_opponent()
	{
#if 0
		opponent_ = Actor::create(Runtime::instance()->get_opponent_prototype_id(), Runtime::instance()->get_opponent_sprite_id());
		opponent_->set_direction(Dynamic_Sprite::LEFT);
		opponent_->set_hit_test_delegate(this);
		opponent_->set_adjust_delegate(this);
		opponent_->clean_status();
		this->addChild(opponent_,1, opponent_->sprite_id());
		opponent_->set_logic_postion(1000.f,200.f);

		Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(Runtime::instance()->get_opponent_sprite_id());
		if (character)
		{
			opponent_->set_name(character->get_character_name());
		}

		real_time_operator_ = new Real_Time_Operator(opponent_);
#endif
		return true;
	}


	void Actor_Layer::on_move_began()
	{
#if 0
		if(primary_actor_->get_is_dead()){
			return;
		}
		primary_actor_->set_is_auto_moving(false);
		primary_actor_->set_is_moving(true);
		primary_actor_->logic_processor()->process_event(FSM::Event::Actor_Running());
#endif
	}

	void Actor_Layer::on_move_ended()
	{
#if 0
		if(primary_actor_->get_is_dead()){
			return;
		}
		primary_actor_->set_is_moving(false);
		primary_actor_->logic_processor()->process_event(FSM::Event::Actor_Standby());
#endif
	}

	void Actor_Layer::on_moving( float x, float y, float dt )
	{
#if 0
		if(primary_actor_->get_is_dead()  || primary_actor_->get_is_hurting() || primary_actor_->get_is_attacking()){
			return;
		}
		primary_actor_->set_is_auto_moving(false);
		primary_actor_->move_delta(x, y, dt);
#endif
	}

	void Actor_Layer::on_attack_began(int n)
	{
#if 0
		if(primary_actor_->get_is_dead() || primary_actor_->get_is_hurting()){
			return;
		}
		primary_actor_->set_is_auto_moving(false);
		FSM::Actor* fsm = primary_actor_->logic_processor(); 
		switch (n)
		{
		case 1:
			fsm->process_event(FSM::Event::Key_Pressed_A());//A
			break;
		case 2:
			fsm->process_event(FSM::Event::Key_Pressed_B());//B
			break;
		case 3:
			fsm->process_event(FSM::Event::Key_Pressed_C());//C
		default:
			break;
		}
#endif
	}

	void Actor_Layer::on_attack_ended(int n)
	{
#if 0
		if(primary_actor_->get_is_dead()){
			return;
		}
#endif
	}

	void Actor_Layer::adjust_backgroud( float& x, float& y )
	{
#if 0
		Json::Value &portals = scene_config["portals"];
		int size = portals.size();
		int i;
		for( i = 0; i < size; i++){
			Json::Value &portal_config = portals[i];
			int portal_x = portal_config["x"].asInt();
			int portal_y = portal_config["y"].asInt();
			int portal_id = portal_config["id"].asInt();
			int radius = portal_config["radius"].asInt();
			if(x >= portal_x - radius && x <= portal_x + radius && y >= portal_y - radius && y <= portal_y + radius)
			{
				if(is_in_portal_ == true)
				{
					break;
				}

				is_in_portal_ = true;
				if (!primary_actor_->get_is_auto_moving())
				{
					vector<uint64> para;
					Game_Logic::Game_Content_Interface::instance()->exec_interface("enterinstance",para);

					primary_actor_->set_is_moving(false);
					primary_actor_->set_is_auto_moving(false);
					primary_actor_->standby();
				}

				break;
			}
		}

		if(i == size)
		{
			is_in_portal_ = false;
		}

		if(pre_locked_screen_){
			if(x >= locked_min_x_){
				current_pos_x_ = x;
				set_is_auto_moving(true);
				pre_locked_screen_ = false;
				if(pre_locked_finish_call_back_){
					(*pre_locked_finish_call_back_)();
					pre_locked_finish_call_back_ = NULL;
				}
			}
		}

		for( Sprite_List::iterator it = trigger_sprite_list_ .begin(); it != trigger_sprite_list_ .end(); it++){
			Trigger_Sprite *sprite = get_trigger_sprite(*it);
			if(sprite && !sprite->get_is_dead() && sprite->check_pos_in_area(x,y)){
				do_trigger_sprite_event(*it);
				FiniteTimeAction* action = CCSequence::create
					(
					CCFadeOut::create(0.5f),
 					CallFuncN::create(this, callfuncN_selector(Actor_Layer::clean_monster)),
					NULL);
				sprite->runAction(action);
				sprite->dead(0);
			}
		}

		if(is_auto_moving_)
		{
			if(x > move_to_pos_x_)
			{
				set_is_auto_moving(false);
			}
			else
			{
				return;
			} 
		}
		if(need_pre_locked_screen_moving_){
			return;
		}

		if(delegate_){
			delegate_->adjust_backgroud(x,y);
		}
#endif
	}


	void Actor_Layer::auto_move_adjust_backgroud( float& x )
	{
	#if 0
		if(delegate_){
			delegate_->auto_move_adjust_backgroud(x);
		}
		#endif
	}


	void Actor_Layer::set_is_auto_moving( bool is_auto_move )
	{
	#if 0
		is_auto_moving_ = is_auto_move;
		if(!is_auto_move){
			show_sign(false);
		}
		#endif
	}

	void Actor_Layer::onExit()
	{
	#if 0
		Layer::onExit();
		AI_Controller::instance()->remove_all_child();
		Director::getInstance()->getScheduler()->setTimeScale(1.f);
		if(get_is_in_city_scene()){

		}
		else if(get_is_in_instance_scene()){

		}
		else if(get_is_in_offline_pk_scene()){
			Game_Utils::instance()->asynchronous_battle_reset_data();
		}
		else if(get_is_in_real_time_pk_scene()){
			Game_Utils::instance()->Real_Time_PK_reset_data();
		}
		#endif
	}


	void Actor_Layer::onEnter()
	{
	#if 0
		Layer::onEnter();

        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
		Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
		if ( NULL == player)
		{
			CCLOG("player id(%d) is wrong!!!\n", Account_Data_Mgr::instance()->get_current_role_id());
			return;
		}

        // 连击清零
		player->set_character_combo(0);
        Game_Utils::instance()->reset_character(player_id);
        Game_Utils::instance()->reset_character(player->get_fight_general_id());

		//to do scene load finish
		cout << "=======================scene load finish===========================" << endl;
		if (Game_Utils::instance()->is_in_city())
		{
            //////////////////////////////////////////////////////////////////////////
            std::vector<uint64> para;
            Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_item_container", para);

            para.push_back(Account_Data_Mgr::instance()->get_current_role_id());
            Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_skill", para);
            //////////////////////////////////////////////////////////////////////////

			PLAYER_LOGIC::instance()->get_main_city_player();
			UI_MainMenu_Layer::get_instance()->refreshFindWay();

#ifdef HIDE_FLASH
#else
			if ( (Account_Data_Mgr::instance()->get_is_first_login() == 1 ) && (is_played_flash_ == false) )
			{
				is_played_flash_ = true;
				Director::getInstance()->getRunningScene()->addChild(Enter_Game_Flash_Layer::create(),0xffff,0xffff);
				Enter_Game_Flash_Layer::get_instance()->startPictureFlash();
			}
#endif // SHOW_FLASH

			if (OFFLINE_FIGHT_MGR::instance()->is_in_arena())
			{
				UI_MainMenu_Layer::get_instance()->show_arena();
				OFFLINE_FIGHT_MGR::instance()->set_in_arena(false);
			}
		}
		Game_Logic::Game_Event_Response::instance()->on_finish_scene_load();
		#endif
	}

	void Actor_Layer::update( float dt )
	{
	#if 0
		if(is_auto_moving_){
			current_pos_x_ += AUTO_MOVE_SPEED * dt;
			if(current_pos_x_ > move_to_pos_x_){
				current_pos_x_ = move_to_pos_x_;
				set_is_auto_moving(false);
			}
			if(delegate_){
				delegate_->auto_move_adjust_backgroud(current_pos_x_);
			}
		}
		else if(need_pre_locked_screen_moving_){
			current_pos_x_ += AUTO_MOVE_SPEED * dt;
			if(current_pos_x_ > primary_actor_->get_logic_x()){
				current_pos_x_ = primary_actor_->get_logic_x();
				need_pre_locked_screen_moving_ = false;
				return;
			}
			if(delegate_){
				delegate_->auto_move_adjust_backgroud(current_pos_x_);
			}
		}
		#endif
	}


	void Actor_Layer::update_real_time_operator( float dt )
	{
	#if 0
		if(real_time_operator_){
			real_time_operator_->update(dt);
		}
		#endif
	}

	void Actor_Layer::show_effect( int n,float x,float y )
	{

	}
#if 0
	cocos2d::extension::CCSkeleton*  Actor_Layer::get_enemy_skeletion( int id )
	{
		Node*  e = (Node*) this->getChildByTag(id);
		if (e)
		{
			Monster* a =   dynamic_cast<Monster*>(e);
			return  dynamic_cast<cocos2d::extension::CCSkeleton*> (a->implentation());
		}
		else
		{
			return 0;
		}
	}

	cocos2d::extension::CCSkeleton* Actor_Layer::get_self_skeletion()
	{
		if (this->primary_actor_)
		{
			return  dynamic_cast<cocos2d::extension::CCSkeleton*> ( this->primary_actor_->implentation());
		}
		else
		{
			return 0;
		}
	}
#endif
#if 0
	Monster* Actor_Layer::get_monstor( int id )
	{
		Node*  node = (Node*) this->getChildByTag(id);
		if (node)
		{
			Monster* sprite =   dynamic_cast<Monster*>(node);
			return sprite;
		}

		return NULL;
	}

	Trigger_Sprite* Actor_Layer::get_trigger_sprite( int id )
	{
		Node*  node = (Node*) this->getChildByTag(id);
		if (node)
		{
			Trigger_Sprite* sprite =   dynamic_cast<Trigger_Sprite*>(node);
			return sprite;
		}

		return NULL;
	}

	Treasure_Box_Sprite* Actor_Layer::get_treasure_box_sprite( int id )
	{
		Node*  node = (Node*) this->getChildByTag(id);
		if (node)
		{
			Treasure_Box_Sprite* sprite =   dynamic_cast<Treasure_Box_Sprite*>(node);
			return sprite;
		}

		return NULL;
	}

	NPC * Actor_Layer::get_npc( int id )
	{
		NPC * npc = NULL;
		NPC_Map::iterator it = npc_map_.find(id);
		if(it != npc_map_.end()){
			npc = it->second;
		}
		return npc;
	}

	Dynamic_Sprite * Actor_Layer::get_sprite_by_id( int id )
	{
		Node*  node = (Node*) this->getChildByTag(id);
		if (node)
		{
			Dynamic_Sprite* sprite =   dynamic_cast<Dynamic_Sprite*>(node);
			return sprite;
		}

		return NULL;
	}

	int   Actor_Layer::get_npc_list( std::vector<int>& list )
	{
		list.clear();
		NPC_Map::iterator itn;
		for( itn = npc_map_.begin(); itn != npc_map_.end(); ++ itn )
		{
			list.push_back( itn->first );
		}

		return 0;
	}

	void Actor_Layer::hit_test(int sprite_id, int skill_id, bool center_blow )
	{
		if(get_is_in_offline_pk_scene() || get_is_in_real_time_pk_scene()){
			Actor * attacker = NULL;
			Actor * attcked = NULL;
			if(sprite_id == primary_actor_->sprite_id()){
				attacker = primary_actor_;
				attcked = opponent_;
			}
			else{
				attacker = opponent_;
				attcked = primary_actor_;
			}
			if(!attcked || attcked->get_is_dead() || attacker->atk_set_contains_spr(attcked)){
				return;
			}
			Hit_Test_Result result;
			if(Hit_Test_Manager::instance()->hit_test(attacker, attcked, center_blow, result))
			{
				attacker->add_atk_spr(attcked);				
				Skill_Use skilluse(result.attacker_id_, result.attacked_sprite_id_, skill_id, 1, result.symbol_, result.b_hit_front_, result.is_in_the_air_);
				SKILL_LOGIC::instance()->UseSkill(skilluse);
				Unique_Skill::get_instance()->calculateAngryNum(Unique_Skill::gainType::HIT_ENEMY,attacker->sprite_id(),1,skill_id);
			}

		}
		else if(get_is_in_instance_scene()){
			Actor * attacker = NULL;
			if(sprite_id == primary_actor_->sprite_id()){
				attacker = primary_actor_;
			}
			else if(sprite_id == pet_->sprite_id()){
				attacker = pet_;
			}
//			attacker =primary_actor_;
			for(Sprite_List::iterator it = this->monster_list_.begin(); it != this->monster_list_.end(); ++it)
			{
				int id = *it;
				Monster* monster = this->get_monstor(id);
				if(!monster || monster->get_is_dead() || attacker->atk_set_contains_spr(monster)){
					continue;
				}
				Hit_Test_Result result;
				if(Hit_Test_Manager::instance()->hit_test(attacker, monster, center_blow, result))
				{
					attacker->add_atk_spr(monster);				
					Skill_Use skilluse(result.attacker_id_, result.attacked_sprite_id_, skill_id, 1, result.symbol_, result.b_hit_front_, result.is_in_the_air_);
					SKILL_LOGIC::instance()->UseSkill(skilluse);
					Unique_Skill::get_instance()->calculateAngryNum(Unique_Skill::gainType::HIT_ENEMY,attacker->sprite_id(),1,skill_id);
				}
			}

			for( Sprite_List::iterator it = treasure_box_list_.begin(); it != treasure_box_list_.end(); it++){
				int id = *it;
				Treasure_Box_Sprite* monster = this->get_treasure_box_sprite(id);
				if(!monster || monster->get_is_dead() || attacker->atk_set_contains_spr(monster)){
					continue;
				}
				Hit_Test_Result result;
				if(Hit_Test_Manager::instance()->hit_test(attacker, monster, center_blow, result))
				{
					attacker->add_atk_spr(monster);				
					Skill_Use skilluse(result.attacker_id_, result.attacked_sprite_id_, skill_id, 1, result.symbol_, result.b_hit_front_, result.is_in_the_air_);
					SKILL_LOGIC::instance()->UseSkill(skilluse);
					Unique_Skill::get_instance()->calculateAngryNum(Unique_Skill::gainType::HIT_ENEMY,attacker->sprite_id(),1,skill_id);
				}
			}
		}
	}

	void Actor_Layer::monster_hit_test( int sprite_id, int skill_id, bool center_blow )
	{
		Monster *monster = get_monstor(sprite_id);
		if(monster->get_is_dead()){
			return;
		}
		if(!monster->atk_set_contains_spr(primary_actor_)){
			Hit_Test_Result result;
			if(Hit_Test_Manager::instance()->hit_test( monster, primary_actor_, center_blow, result))
			{
				monster->add_atk_spr(primary_actor_);
				Skill_Use skilluse(result.attacker_id_, result.attacked_sprite_id_, skill_id, 1, result.symbol_, result.b_hit_front_, result.is_in_the_air_);
				SKILL_LOGIC::instance()->UseSkill(skilluse);
			}
		}
		if(pet_ && !monster->atk_set_contains_spr(pet_)){
			Hit_Test_Result result;
			if(Hit_Test_Manager::instance()->hit_test( monster, pet_, center_blow, result))
			{
				monster->add_atk_spr(pet_);
				Skill_Use skilluse(result.attacker_id_, result.attacked_sprite_id_, skill_id, 1, result.symbol_, result.b_hit_front_, result.is_in_the_air_);
				SKILL_LOGIC::instance()->UseSkill(skilluse);
			}
		}
	}

	void Actor_Layer::projectile_hit_test( int sprite_id, int owner_sprite_id, int skill_id, bool center_blow , bool hit_remove )
	{
		Dynamic_Sprite * attacker = get_sprite_by_id(sprite_id);
		if(!attacker){
			return;
		}
		if(get_is_in_offline_pk_scene() || get_is_in_real_time_pk_scene()){
			Dynamic_Sprite * attcked = NULL;
			if(owner_sprite_id == primary_actor_->sprite_id()){
				attcked = opponent_;
			}
			else{
				attcked = primary_actor_;
			}
			if(!attcked || attcked->get_is_dead() || attacker->atk_set_contains_spr(attcked)){
				return;
			}
			Hit_Test_Result result;
			if(Hit_Test_Manager::instance()->hit_test(attacker, attcked, center_blow, result))
			{
				attacker->add_atk_spr(attcked);				
				Skill_Use skilluse(owner_sprite_id, result.attacked_sprite_id_, skill_id, 1, result.symbol_, result.b_hit_front_, result.is_in_the_air_);
				SKILL_LOGIC::instance()->UseSkill(skilluse);
				Unique_Skill::get_instance()->calculateAngryNum(Unique_Skill::gainType::HIT_ENEMY,owner_sprite_id,1,skill_id);
				if(hit_remove){
					attacker->dead(0);
					return;
				}
			}
		}
		else if(get_is_in_instance_scene()){
			if(owner_sprite_id == primary_actor_->sprite_id() || (pet_ && owner_sprite_id == pet_->sprite_id())){
				for(Sprite_List::iterator it = this->monster_list_.begin(); it != this->monster_list_.end(); ++it)
				{
					int id = *it;
					Monster* monster = this->get_monstor(id);
					if(!monster || monster->get_is_dead() || attacker->atk_set_contains_spr(monster)){
						continue;
					}
					Hit_Test_Result result;
					if(Hit_Test_Manager::instance()->hit_test(attacker, monster, center_blow, result))
					{
						attacker->add_atk_spr(monster);				
						Skill_Use skilluse(owner_sprite_id, result.attacked_sprite_id_, skill_id, 1, result.symbol_, result.b_hit_front_, result.is_in_the_air_);
						SKILL_LOGIC::instance()->UseSkill(skilluse);
						Unique_Skill::get_instance()->calculateAngryNum(Unique_Skill::gainType::HIT_ENEMY,owner_sprite_id,1,skill_id);
						if(hit_remove){
							attacker->dead(0);
							return;
						}
					}
				}
			}
			else{
				if(attacker->atk_set_contains_spr(primary_actor_)){
					return;
				}

				Hit_Test_Result result;
				if(Hit_Test_Manager::instance()->hit_test( attacker, primary_actor_, center_blow, result))
				{
					attacker->add_atk_spr(primary_actor_);
					Skill_Use skilluse(owner_sprite_id, result.attacked_sprite_id_, skill_id, 1, result.symbol_, result.b_hit_front_, result.is_in_the_air_);
					SKILL_LOGIC::instance()->UseSkill(skilluse);
					if(hit_remove){
						attacker->dead(0);
						return;
					}
				}
			}
		}
	}

	UI::Actor* Actor_Layer::get_primary_actor()
	{
		//return this->primary_actor_;
	}

	Pet * Actor_Layer::get_pet()
	{
		return pet_;
	}

	Actor* Actor_Layer::get_opponent()
	{
		return opponent_;
	}

	Real_Time_Operator* Actor_Layer::get_real_time_operator()
	{
		return real_time_operator_;
	}

	Sprite_List * Actor_Layer::get_monster_list_ptr()
	{
		return &(this->monster_list_);
	}

	void Actor_Layer::monster_is_stunning( int spriteID, bool is_stunning )
	{
		AI_Controller::instance()->monster_is_stunning(spriteID, is_stunning);
	}

	void Actor_Layer::monster_hurt_finished(int spriteID){
		AI_Controller::instance()->hurt_finished(spriteID);
	}

	void Actor_Layer::update_monster_attack_status(int spriteID,bool is_attacking){
		AI_Controller::instance()->update_attack_status(spriteID, is_attacking);
	}

	void Actor_Layer::check_position_y(float &y){
		if( !active_area_delegate_ ){
			return;
		}
		if(y >active_area_delegate_->get_max_y()){
			y = active_area_delegate_->get_max_y();
		}
		else if(y < active_area_delegate_->get_min_y()){
			y = active_area_delegate_->get_min_y();
		}

	}

	void Actor_Layer::check_position_x(float &x){
		if( !active_area_delegate_ ){
			return;
		}
		if(x >active_area_delegate_->get_max_x()){
			x = active_area_delegate_->get_max_x();
		}
		else if(x < active_area_delegate_->get_min_x()){
			x = active_area_delegate_->get_min_x();
		}

	}

	void Actor_Layer::check_position(float &x, float &y){
		check_position_x(x);
		check_position_y(y);
	}

	Dynamic_Sprite * Actor_Layer::get_sprite( int id, int type )
	{
		Dynamic_Sprite * sprite = NULL;
		if(type == Game_Logic::Game_Event::EVENT_TYPE_PLAYER){
			sprite = primary_actor_;
		}
		else if( type == Game_Logic::Game_Event::EVENT_TYPE_DEPUTY_GENERAL){
			sprite = pet_;
		}
		else if( type == Game_Logic::Game_Event::EVENT_TYPE_MONSTER){
			sprite = get_monstor(id);
		}
		else if ( type == Game_Logic::Game_Event::EVENT_TYPE_FIGHT_PLAYER )
		{
			sprite = opponent_;
		}
		
		return sprite;
	}

	void Actor_Layer::sprite_dead( int id, int type, int dead_type)
	{
		Dynamic_Sprite * sprite = NULL;
		if(type == Game_Logic::Game_Event::EVENT_TYPE_PLAYER || type == Game_Logic::Game_Event::EVENT_TYPE_FIGHT_PLAYER){
			if(get_is_in_offline_pk_scene()){
				if(id == primary_actor_->sprite_id()){
					sprite = primary_actor_;
					Game_Utils::instance()->asynchronous_battle_fail();
				}
				else{
					sprite = opponent_;
					Game_Utils::instance()->asynchronous_battle_win();
				}
			}
			else if(get_is_in_real_time_pk_scene()){
				if(id == primary_actor_->sprite_id()){
					Game_Utils::instance()->send_Real_Time_PK_result(false);
					return;
				}
				else{
					Game_Utils::instance()->send_Real_Time_PK_result(true);
					return;
				}
			}
			else if(get_is_in_instance_scene()){
				sprite = primary_actor_;
				Game_Utils::instance()->stop_update_cd();

				Director::getInstance()->getScheduler()->setTimeScale(TIME_SCALE_PRIMAY_ACTOR_DEAD);
				runAction(CCSequence::create(CCDelayTime::create(SHOW_PRIMAY_ACTOR_DEAD_DELAY), CallFunc::create(this, callfunc_selector(Actor_Layer::do_primay_actor_callback)), NULL));
				
				AI_Controller::instance()->sprite_dead(primary_actor_->sprite_id());
				if(pet_ && !pet_->get_is_dead()){
					pet_->dead();
					Game_Utils::instance()->update_actor_hp( pet_->sprite_id(), 0 );
					Character* character = CHARACTER_MGR::instance()->get_character(pet_->sprite_id());
					if (character )
					{
						character->set_dead(1);
						character->set_character_cur_hp(0);
					}
				}
			}
		}
		else if( type == Game_Logic::Game_Event::EVENT_TYPE_DEPUTY_GENERAL){
			sprite = pet_;
		}
		else if( type == Game_Logic::Game_Event::EVENT_TYPE_MONSTER){
			sprite = get_monstor(id);	
			AI_Controller::instance()->remove_child(id);
			FiniteTimeAction* action = CCSequence::create
				(
				CCDelayTime::create(5.f),
				CallFuncN::create(this, callfuncN_selector(Actor_Layer::clean_monster)),
				NULL);
			sprite->runAction(action);
		}
		else{
			sprite = get_treasure_box_sprite(id);
			FiniteTimeAction* action = CCSequence::create
				(
				CCFadeOut::create(3.5f),
				CallFuncN::create(this, callfuncN_selector(Actor_Layer::clean_monster)),
				NULL);
			sprite->runAction(action);
			do_treasure_box_sprite_event(id);
		}
		if(sprite){
			sprite->dead(dead_type);
		}
		else{
			CCLOG("Can not find dead sprite %d", id);
		}
	}

	void Actor_Layer::sprite_hurt( int id, int type, int attcker_id, Hurt_Type hurt_type, int value, float hurting_vellovity, float hurting_v_h_vellovity, float hurt_time /*= 0.5f*/ )
	{
		Dynamic_Sprite * sprite = NULL;
		if(type == Game_Logic::Game_Event::EVENT_TYPE_PLAYER  || type == Game_Logic::Game_Event::EVENT_TYPE_FIGHT_PLAYER){
			if(id == primary_actor_->sprite_id()){
				sprite = primary_actor_;
			}
			else{
				sprite = opponent_;
			}
		}
		else if( type == Game_Logic::Game_Event::EVENT_TYPE_DEPUTY_GENERAL){
			sprite = pet_;
		}
		else if( type == Game_Logic::Game_Event::EVENT_TYPE_MONSTER){
			sprite = get_monstor(id);
			if(hurt_type > -1)
				AI_Controller::instance()->sprite_attack_AI(attcker_id ,id);
			AI_Controller::instance()->hp_change(id, value);
		}
		else{
			sprite = get_treasure_box_sprite(id);
		}
		if(sprite){
			sprite->hurt(hurt_type, value, hurting_vellovity, hurting_v_h_vellovity, hurt_time);
		}
		else{
			CCLOG("Can not find hurted sprite %d", id);
		}
	}

	void Actor_Layer::set_adjust_delegate( Adjust_Delegate * delegate )
	{
		delegate_ = delegate;
	}

	void Actor_Layer::init_monster_wave()
	{
		//monster_waves_; 怪物波数
		//current_wave_;现在是第几波，从0开�?		if(monster_waves_ <= 0 ||current_wave_ > monster_waves_ - 2){
			return;
		}
		current_wave_ ++;

		init_monster();
	}

	void Actor_Layer::clean_monster( Node *node )
	{
		node->removeFromParentAndCleanup(true);
	}

	std::map<int , int >& Actor_Layer::get_monster_prototype_map()
	{
		return monster_prototype_map_;
	}

	void Actor_Layer::move_to( float x, float y )
	{
		primary_actor_->auto_move_to(x, y);
	}

	void Actor_Layer::quest_auto_move(int x,int y,CallBackFun fun,int param)
	{
		primary_actor_->auto_move_to_call_back((float)x, (float)y,fun,param);
	}

	Background_Delegate * Actor_Layer::get_background_delegate()
	{
		return background_delegate_;
	}

	void Actor_Layer::set_background_delegate( Background_Delegate * background_delegate )
	{
		background_delegate_ = background_delegate;
	}

	void Actor_Layer::NPC_Clicked( int sprite_id )
	{
		//to do. NPC Clicked
		show_npc_dialogue(sprite_id);
	}

	void Actor_Layer::show_npc_dialogue(int sprite_id)
	{
	
		CCLOG("NPC(%d) Clicked\n", sprite_id);
		Scene* pScene = Director::getInstance()->getRunningScene();
		CC_ASSERT( pScene );
		UI_MainMenu_Layer* pLayer =dynamic_cast<UI_MainMenu_Layer*>(pScene->getChildByTag(TAG_BTN_UI));
		if (pLayer)
		{
			pLayer->showNpcDialogue(sprite_id);
		}
		else
		{
			CCLOG("NPC_Clicked pLayer=NULL");
		}
	}

	void Actor_Layer::set_active_area_delegate( Active_Area_Delegate * active_area_delegate )
	{
		active_area_delegate_ = active_area_delegate;
	}

	void Actor_Layer::addChild( Node * child )
	{
		if(background_delegate_){
			background_delegate_->add_child(child);
		}
	}

	void Actor_Layer::addChild( Node * child, int zOrder )
	{
		if(background_delegate_){
			background_delegate_->add_child(child, zOrder);
		}
	}

	void Actor_Layer::addChild( Node* child, int zOrder, int tag )
	{
		if(background_delegate_){
			background_delegate_->add_child(child, zOrder, tag);
		}
	}

	Node * Actor_Layer::getChildByTag( int tag )
	{
		if(background_delegate_){
			return background_delegate_->get_child_by_tag(tag);
		}
		return NULL;
	}

	void Actor_Layer::locked_screen( bool locked, int screen_num )
	{
		if(locked){
			active_area_delegate_->set_Active_screen((float)LOCK_SCENE_WIDTH *(screen_num - 1), (float)LOCK_SCENE_WIDTH *screen_num);
		}
		else{
			active_area_delegate_->set_Active_screen((float)0 ,(float)active_area_delegate_->get_scene_width());
		}
	}

	void Actor_Layer::get_born_position( float &born_x, float &born_y, int center_x, int center_y, int radius )
	{
		born_x = (float)(center_x + (int)rand()%(radius * 2) - radius);
		born_y = (float)(center_y + (int)rand()%(radius * 2) - radius);
		check_position_y(born_y);
	}

	void Actor_Layer::show_sign( bool bShow /*= true*/ )
	{
		Game_Utils::instance()->show_sign(bShow);
	}

	void Actor_Layer::pre_locked_screen( bool locked, int screen_num , call_back_handler_t pre_locked_finish_call_back)
	{
		#if 0
		if(!locked){
			locked_screen(false);
		}
		else{
			show_sign();
			pre_locked_finish_call_back_ = pre_locked_finish_call_back;
			screen_num_ = screen_num;
			start_pre_locked();
		}
		#endif
	}

	void Actor_Layer::start_pre_locked()
	{
		#if 0
		pre_locked_screen_ = true;
		need_pre_locked_screen_moving_ = true;
		active_area_delegate_->set_Active_screen((float)active_area_delegate_->get_min_x(), (float)LOCK_SCENE_WIDTH *screen_num_);
		locked_min_x_ = (float)LOCK_SCENE_WIDTH * (screen_num_ - 1);
		move_to_pos_x_ = locked_min_x_+ Director::getInstance()->getWinSize().width/2;
		current_pos_x_ = locked_min_x_- Director::getInstance()->getWinSize().width/2;
		primary_actor_->set_pre_lock_screen(locked_min_x_);
		#endif
	}

	void Actor_Layer::kill_all_monster()
	{
		for(Sprite_List::iterator it = this->monster_list_.begin(); it != this->monster_list_.end(); ++it)
		{
			int id = *it;
			Monster* monster = this->get_monstor(id);
			if(monster && !monster->get_is_dead()){
				AI_Controller::instance()->remove_child(id);
				monster->dead();
			}
		}
	}
	int Actor_Layer::palyer_dialog_id=0;
	int Actor_Layer::instance_dialog_id=0;
	int Actor_Layer::instance_dialog_state=0;
	void Actor_Layer::instance_dialog_after_fight(int player_id,int instance_id,int instance_state)
	{
		#if 0
		palyer_dialog_id=player_id;
		instance_dialog_id=instance_id;
		instance_dialog_state=instance_state;
		Audio_Manager::shared_Audio_Manager()->play_effect("audio/finish.mp3");
		runAction(CCSequence::create(CCDelayTime::create(SHOW_WIN_DELAY), CallFunc::create(this, callfunc_selector(Actor_Layer::instance_dialog_callback)), NULL));
		#endif
	}
	void Actor_Layer::instance_dialog_callback()
	{
	#if 0
		//if(UI_FuBenDialog::sharedUI_FuBenDialog()->get_is_show() || Formula_Function_Instance_Client::instance()->process_instance_dialog( palyer_dialog_id, instance_dialog_id, 1 ) )
		//{
		//	return ;
		//}
		current_instance_data cid;
		if(0 == INSTANCE_DATA_MGR::instance()->get_player_instance( palyer_dialog_id, cid) )
		{
			cid.set_instance_state(instance_dialog_state);
			INSTANCE_DATA_MGR::instance()->modi_player_instance( palyer_dialog_id, cid );
		}

		if(current_instance_data::INSTANCE_STATE_SUC == instance_dialog_state )
			Game_Utils::instance()->show_win();

		Game_Logic::Game_Event_Response::instance()->on_update_game_ui_child_info(palyer_dialog_id);
		#endif
	}
	void Actor_Layer::show_win()
	{
		#if 0
		Director::getInstance()->getScheduler()->setTimeScale(TIME_SCALE_SHOW_WIN);
		kill_all_monster();
		
		runAction(CCSequence::create(/*CCDelayTime::create(TIME_SCALE_SHOW_WIN * SHOW_WIN_DELAY),*/ CallFunc::create(this, callfunc_selector(Actor_Layer::show_win_callback)), NULL));
		Audio_Manager::shared_Audio_Manager()->stopAllEffects();
		Audio_Manager::shared_Audio_Manager()->stopBackgroundMusic();
		Audio_Manager::shared_Audio_Manager()->play_background_music("finish.mp3");
		#endif
	}

	void Actor_Layer::show_win_callback()
	{
		Director::getInstance()->getScheduler()->setTimeScale(1.f);
//		UI::GameUI_Layer::get_instance()->buttonSettlement();
	}

	void Actor_Layer::play_win_effect()
	{
	//	Game_Utils::instance()->add_effect_to_scene("1000");
	}

	void Actor_Layer::do_primay_actor_callback()
	{
		#if 0
		Director::getInstance()->getScheduler()->setTimeScale(1.f);
		UI_Tips_Layer* tips_layer = UI_Tips_Layer::create();
		Director::getInstance()->getRunningScene()->addChild(tips_layer,30,TAG_TIP);
		tips_layer->show();
		#endif
	}

	void Actor_Layer::change_primary_actor( int sprite_id )
	{
		#if 0
		return;
		float x, y;
		Dynamic_Sprite::Direction direction = primary_actor_->get_direction();
		bool is_hosting = primary_actor_->get_is_hosting();
		primary_actor_->get_logic_postion(x, y);
		primary_actor_->removeFromParent(); 
		if(Runtime::instance()->get_primary_actor()->sprite_id() == sprite_id){
			primary_actor_ = Runtime::instance()->get_primary_actor();
			primary_actor_->clean_status();
		}
		else{
			primary_actor_ = Runtime::instance()->get_actor(sprite_id);
			primary_actor_->set_hit_test_delegate(this);
			primary_actor_->set_adjust_delegate(this);
			primary_actor_->clean_status();
		}
		this->addChild(primary_actor_,1,sprite_id);
		primary_actor_->set_direction(direction);
		primary_actor_->set_logic_postion(x,y);
		primary_actor_->set_is_hosting(is_hosting);
		primary_actor_->set_pre_lock_screen(locked_min_x_);
		primary_actor_->logic_processor()->process_event(FSM::Event::Exchange_Fighter());
		#endif
	}

	bool Actor_Layer::get_is_in_city_scene()
	{
		return scene_type_ == CITY_SCENE;
	}

	bool Actor_Layer::get_is_in_instance_scene()
	{
		return scene_type_ == INSTANCE_SCENE;
	}

	bool Actor_Layer::get_is_in_real_time_pk_scene()
	{
		return scene_type_ == REAL_TIME_PK_SCENE;
	}

	bool Actor_Layer::get_is_in_offline_pk_scene()
	{
		return scene_type_ == OFFLINE_PK_SCENE;
	}

	bool Actor_Layer::get_is_in_pk_scene()
	{
		return scene_type_ == OFFLINE_PK_SCENE || scene_type_ == REAL_TIME_PK_SCENE;
	}

	void Actor_Layer::pre_to_start_asynchronous_battle()
	{
	#if 0
		Game_Utils::instance()->set_operator_is_disable(true);
		Game_Utils::instance()->add_effect_to_scene("2015");
		FiniteTimeAction* action = CCSequence::create
			(
			CCDelayTime::create(3.5f),
			CallFunc::create(this, callfunc_selector(Actor_Layer::start_asynchronous_battle)),
			NULL);
		runAction(action);
		#endif
	}

	void Actor_Layer::start_asynchronous_battle()
	{
		//Game_Utils::instance()->start_asynchronous_battle();
	}

	void Actor_Layer::create_trigger_sprite( int sprite_prototype_id,int &sprite_id, float born_point_x, float born_point_y )
	{
		//Trigger_Sprite* sprite = Trigger_Sprite::create(sprite_prototype_id, sprite_id , born_point_x, born_point_y);
		//this->addChild(sprite,0, sprite_id);
		//trigger_sprite_list_.push_back(sprite_id);
	}

	void Actor_Layer::create_treasure_box_sprite( int sprite_prototype_id,int &sprite_id, float born_point_x, float born_point_y )
	{
		//Treasure_Box_Sprite* sprite = Treasure_Box_Sprite::create(sprite_prototype_id, sprite_id , born_point_x, born_point_y);
		//this->addChild(sprite,0, sprite_id);
		//treasure_box_list_.push_back(sprite_id);
	}

	void Actor_Layer::do_trigger_sprite_event( int sprite_id )
	{
	//	Game_Utils::instance()->do_trigger_sprite_event(sprite_id);
	}

	void Actor_Layer::do_treasure_box_sprite_event( int sprite_id )
	{
		//Game_Utils::instance()->do_treasure_box_sprite_event(sprite_id);
	}

#endif
};


