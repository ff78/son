#include "Game_Utils.h"
//#include "Monster.h"
//#include "Game_Scene.h"
#include "UI/City_Scene.h"
#include "UI/Actor_Layer.h"
//#include "GameUI_Layer.h"
//#include "Game_Scene_Operator_Layer.h"
//#include "Unique_Skill.h"
#include "UI/Message_Layer.h"
#include "cocos2d.h"
#include "Game_Interface/event_define.h"
//#include "Dynamic_Sprite.h"
//#include "Attack_Cfg_Data_Mgr.h"
#include "Game/Hurt_Utils.h"
#include "Game_Interface/game_event_mgr.h"
#include "Game_Interface/game_event_response.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_element.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Play_System/Instance_Data_Mgr.h"
//#include "Fight_System/Offline_Fight_Logic_Cl.h"
//#include "Fight_System/Offline_Fight_Mgr_Cl.h"
//#include "Fight_System/Fight_Config_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"

//#include "Game/Monster_Wave_Cfg_Data_Mgr.h"

#include "Character_System/Character_Mgr.h"
#include "Character_System/Character.h"
#include "Character_System/Player.h"
#include "Character_System/Player_Config_Mgr.h"
//#include "Skill_System/Skill/Skill_Logic.h"
#include "UI_Interface/UI_MainMenu_Layer.h"
//#include "Runtime.h"

//#include "Unique_Skill.h"

//#include "Effect_Cfg_Data_Mgr.h"
//#include "Projectile_Sprite.h"

//#include "cocos-ext.h"

USING_NS_CC;
//USING_NS_CC_EXT;

Game_Utils*  Game_Utils::instance_ = 0;
Game_Utils*  Game_Utils::instance()
{
    if( NULL == instance_ )
        instance_ = new Game_Utils;

    return instance_;
}
#if 1
City_NPC * Game_Utils::get_npc_by_id(int id)
{
	CityLayer* al = get_actor_layer();
	if (NULL == al)
	{
		return nullptr;
	}
	return al->getNPCbyId(id);

}
int Game_Utils::get_npc_list(std::map<int, int>& list)
{
	CityLayer* al = get_actor_layer();
	if (NULL == al)
	{
		return -1;
	}
	std::vector<int> tmp_lst = al->getNpcIds();
	
	
	list.clear();
	std::vector<int>::iterator iti;
	for ( iti = tmp_lst.begin(); iti != tmp_lst.end(); ++ iti )
	{
		list.insert(make_pair(get_npc_static_id((*iti)),(*iti)));
	}

	return 0;
}
void Game_Utils::set_sprite_info(int npcId, const char * img_path, bool use_plist)
{
	CityLayer* al = get_actor_layer();
	if (NULL == al)
	{
		return ;
	}
	al->setNpcTipSprite(npcId,img_path,false);
}
void Game_Utils::add_effect_to_scene(const std::string& effect_id)
{
	//cocos2d::Sprite *effect = cocos2d::Sprite::create();
	//Effect_Cfg_Data_Mgr::instance()->get_effect(effect, effect_id);
	//effect->setPosition(pos);
	//Director::getInstance()->getRunningScene()->addChild(effect, 30);
}
CityLayer* Game_Utils::get_actor_layer()
{
	Scene*  scene = Director::getInstance()->getRunningScene();
	if ( 0 == scene)
		return NULL;
	Node*  node = scene->getChildByTag(UI::TAG_ACT);
	if( NULL == node )
		return NULL;
	return dynamic_cast< CityLayer*> (node);
}
int Game_Utils::get_npc_static_id( int id )
{
#if 1
	return id;
#else
	Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(id);
	if ( NULL == character )
		return -1;
	return character->get_static_character_id();
#endif
}

void Game_Utils::quest_auto_move(int npcId, CallBackFun func, int param)
{
	CityLayer* al = get_actor_layer();
	if (al)
	{	
		//al->autoMove2NPC(x, y, func, param);
		al->autoMove2NPC(npcId, func, param);
	}
}
void Game_Utils::clicked_area(int area_id)
{

    UI_MainMenu_Layer::get_instance()->visibleSecondaryInstance(area_id);
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    vector<uint64> para;
    para.push_back( player_id );
    para.push_back( 1000 );//area_id
//    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendrequirestagestate", para);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendrequireallstage", para);

    //INSTANCE_DATA_MGR::instance()->set_current_instance_stage_id( area_id );
}

void Game_Utils::show_npc_dialog(int sprite_id)
{
	Scene* pScene = Director::getInstance()->getRunningScene();
	CC_ASSERT(pScene);
	UI_MainMenu_Layer* pLayer = dynamic_cast<UI_MainMenu_Layer*>(pScene->getChildByTag(UI::TAG_BTN_UI));
	if (pLayer)
	{
		pLayer->showNpcDialogue(sprite_id);
	}
	else
	{
		CCLOG("NPC_Clicked pLayer=NULL");
	}

}

void Game_Utils::show_alert( const char *msg )
{
	UI::Message_Layer * msg_layer = get_Message_Layer();
	if(msg_layer){
		msg_layer->show_alert(msg);
	}
}
UI::Message_Layer * Game_Utils::get_Message_Layer()
{
	Scene*  scene = Director::getInstance()->getRunningScene();
	if (!scene)
		return NULL;

	Node*  node = scene->getChildByTag(UI::TAG_MSG);
	if( !node )
		return NULL;
	return dynamic_cast< UI::Message_Layer *> (node);
}
#else
UI::Actor_Layer* Game_Utils::get_actor_layer()
{
	Scene*  scene = Director::getInstance()->getRunningScene();
	if ( 0 == scene)
		return NULL;

	Node*  node = scene->getChildByTag(UI::TAG_ACT);
	if( NULL == node )
		return NULL;
	return dynamic_cast< UI::Actor_Layer*> (node);

}

UI::Game_UI_Delegate * Game_Utils::get_Game_UI_layer()
{
	Scene*  scene = Director::getInstance()->getRunningScene();
	if (!scene)
		return NULL;

	Node*  node = scene->getChildByTag(UI::TAG_UI);
	if( !node )
		return NULL;
	return dynamic_cast< UI::Game_UI_Delegate*> (node);
}

UI::Message_Layer * Game_Utils::get_Message_Layer()
{
	Scene*  scene = Director::getInstance()->getRunningScene();
	if (!scene)
		return NULL;

	Node*  node = scene->getChildByTag(UI::TAG_MSG);
	if( !node )
		return NULL;
	return dynamic_cast< UI::Message_Layer *> (node);
}

UI::Game_Scene_Operator_Layer * Game_Utils::get_Game_Scene_Operator_Layer()
{
	Scene*  scene = Director::getInstance()->getRunningScene();
	if (!scene)
		return NULL;

	Node*  node = scene->getChildByTag(UI::TAG_OPT);
	if( !node )
		return NULL;
	return dynamic_cast< UI::Game_Scene_Operator_Layer *> (node);
}

UI::Unique_Skill* Game_Utils::get_Unique_layer()
{
	Scene*  scene = Director::getInstance()->getRunningScene();
	if (!scene)
		return NULL;

	Node*  node = scene->getChildByTag(UI::TAG_UNS);
	if( !node )
		return NULL;
	return dynamic_cast< UI::Unique_Skill*> (node);
}

UI::Monster * Game_Utils::get_monster_by_id(int id){

	 UI::Actor_Layer* al = get_actor_layer();
	if (al == 0)
	 {
		return NULL;
	 }
	return al->get_monstor(id);
}

UI::NPC * Game_Utils::get_npc_by_id( int id )
{
	UI::Actor_Layer* al = get_actor_layer();
	if (al == 0)
	{
		return NULL;
	}
	return al->get_npc(id);
}

FSM::Monster * Game_Utils::get_fsm_monster_by_id(int id){

	UI::Actor_Layer* al = get_actor_layer();
	if (al == 0 || !al->get_monstor(id))
	{
		return NULL;
	}
	return al->get_monstor(id)->logic_processor();
}

int Game_Utils::get_primary_actor_id( void )
{
	 UI::Actor_Layer* al = get_actor_layer();
	if (al == 0)
	 {
		return -1;
	 }
    return al->get_primary_actor()->sprite_id();
}



int Game_Utils::get_pet_id( void )
{
	UI::Dynamic_Sprite* pet = get_pet();
	if(pet && !pet->get_is_dead()){
		return pet->sprite_id();
	}
	return -1;
}


UI::Actor*  Game_Utils::get_player_by_id(int id){

	 UI::Actor_Layer* al = get_actor_layer();
	if (al == 0)
	 {
		return NULL;
	 }

	if(id == al->get_primary_actor()->sprite_id()){ //todo 当前副本场景中午其他玩家，先写死主角
		return al->get_primary_actor();
	}
	else if(al->get_opponent() && id == al->get_opponent()->sprite_id()){
		return al->get_opponent();
	}
	else if(id == get_pet_id()){
		return al->get_pet();
	}
	return NULL;
}

Sprite_List *  Game_Utils::get_monster_list(){

	 UI::Actor_Layer* al = get_actor_layer();
	 if (al == 0)
	 {
		return NULL;
	}

	return  al->get_monster_list_ptr();
}

void Game_Utils::add_actor(UI::Actor* actor,float x, float y)
{
    UI::Actor_Layer* layer = get_actor_layer();
	actor->set_logic_postion(x,y);
    if (layer)
    {
        layer->addChild(actor);
    }
}

void Game_Utils::remove_actor(UI::Actor* actor)
{
    actor->removeFromParent();
}

bool Game_Utils::check_position(float &x, float &y){
	UI::Actor_Layer* al = get_actor_layer();
	if(!al){
		return false;
	}
	al->check_position(x,y);
	return true;
}

bool Game_Utils::check_position_x(float &x){
	UI::Actor_Layer* al = get_actor_layer();
	if(!al){
		return false;
	}
	al->check_position_x(x);
	return true;
}

bool Game_Utils::check_position_y(float &y){
	UI::Actor_Layer* al = get_actor_layer();
	if(!al){
		return false;
	}
	al->check_position_y(y);
	return true;
}

void Game_Utils::dead( int id, int type, int dead_type )
{
	UI::Actor_Layer* al = get_actor_layer();
	if(!al){
		return ;
	}
    //add die event
	UI::Dynamic_Sprite * sprite = al->get_sprite(id, type);
	if(!sprite){
		CCLOG("Can not find sprite %d",id);
		return;
	}
    Game_Logic::Game_Event_Response::instance()->on_character_die(sprite->get_static_id_(), type,sprite->getPositionX(),sprite->getPositionY());

	al->sprite_dead(id, type, dead_type);
}

void Game_Utils::update_combo(int id, int type, int combo)
{
	 UI::Game_UI_Delegate* gl = get_Game_UI_layer();
	if(gl && get_primary_actor_id() == id)
	{
		gl->update_combo(combo);
	}
}

void Game_Utils::hurt( Hurt_Args & hurt_args )
{
	UI::Actor_Layer* al = get_actor_layer();
	if(!al){
		return ;
	}
	al->sprite_hurt(hurt_args.hurt_sprite_id_, hurt_args.hurt_sprite_type_, hurt_args.attcker_id_,(Hurt_Type)hurt_args.hurt_type_, hurt_args.hurt_value_, hurt_args.hurting_vellovity_, hurt_args.hurting_v_h_vellovity_, hurt_args.yinzhi_time_/1000.f);

	UI::Game_UI_Delegate* gl = get_Game_UI_layer();
	if(gl)
	{
		update_combo(hurt_args.hurt_sprite_id_, hurt_args.hurt_sprite_type_, 0);
		gl->update_hp(hurt_args.hurt_sprite_id_, hurt_args.hurt_sprite_type_,(Hurt_Type)hurt_args.hurt_type_, hurt_args.hurt_value_);
	}
}

void Game_Utils::stop()
{
	UI::Actor *actor = Runtime::instance()->get_primary_actor();
	if (actor)
	{
		actor->set_is_moving(false);
	}
}

Charcter_AI_State	 Game_Utils::get_ai_state(int character_id)
{
	Character* character = CHARACTER_MGR::instance()->get_character(character_id);
	if (character )
	{
		return character->get_ai_state();
	}

	return MISS_STATE;
}

void Game_Utils::start_ai_state(int character_id)
{
	Character* character = CHARACTER_MGR::instance()->get_character(character_id);
	if (character )
	{
		character->clean_ai_state();
	}
}

void Game_Utils::show_top(Show_Top_Args & show_top_args)
{
	UI::Actor_Layer* al = get_actor_layer();
	if(!al){
		return ;
	}
	UI::Dynamic_Sprite * sprite = al->get_sprite(show_top_args.hurt_sprite_id_, show_top_args.hurt_sprite_type_);
	if(sprite && !sprite->get_is_dead()){
		sprite->show_top(show_top_args.image_name_.c_str());
	}
}

void Game_Utils::get_actor_attack_list( int prototype_id, std::list<int> & list )
{
	Attack_Cfg_Data_Mgr::shared_instance()->get_actor_attack_list(prototype_id, &list);
}

void Game_Utils::init_monser_wave( void )
{
    UI::Actor_Layer* al = get_actor_layer();
	if(al){
        al->init_monster_wave();
    }
}

void Game_Utils::get_monster_prototype_map( std::map<int,int>& mst_lst)
{
    UI::Actor_Layer* al = get_actor_layer();
	if(al){
        mst_lst = al->get_monster_prototype_map();
    }
}

void Game_Utils::quest_auto_move(int x,int y,CallBackFun fun,int param)
{
    UI::Actor_Layer* al = get_actor_layer();
    if(al)
    {
        al->quest_auto_move(x,y,fun,param);
    }
}

UI::Actor * Game_Utils::get_primary_actor()
{
	UI::Actor_Layer* al = get_actor_layer();
	if(al){
		return al->get_primary_actor();
	}

    return NULL;
}

UI::Pet * Game_Utils::get_pet()
{
	UI::Actor_Layer* al = get_actor_layer();
	if(al){
		return al->get_pet();
	}

	return NULL;
}

UI::Dynamic_Sprite * Game_Utils::get_primary_sprite_by_type(int type)
{
	UI::Actor_Layer* al = get_actor_layer();
	if(al){
		if(Game_Logic::Game_Event::EVENT_TYPE_PLAYER == type){
			return al->get_primary_actor();

		}
		else if(Game_Logic::Game_Event::EVENT_TYPE_DEPUTY_GENERAL == type){
			return al->get_pet();
		}
	}
	return NULL;
}

UI::Dynamic_Sprite * Game_Utils::get_primary_sprite_by_id(int id)
{
	UI::Actor_Layer* al = get_actor_layer();
	if(al){
		if( al->get_primary_actor() &&al->get_primary_actor()->sprite_id() == id){
			return al->get_primary_actor();

		}
		else if(al->get_pet() &&al->get_pet()->sprite_id() == id){
			return al->get_pet();
		}
	}
	return NULL;
}

UI::Actor * Game_Utils::get_opponent()
{
	UI::Actor_Layer* al = get_actor_layer();
	if(al){
		return al->get_opponent();
	}

	return NULL;
}

bool Game_Utils::is_in_city()
{
	return Runtime::instance()->is_in_city_scene();
}

bool Game_Utils::gas_full_ro_not(int spreite_id)
{
	return UI::Unique_Skill::get_instance()->judge_gas_full_ro_not(spreite_id);
}

void Game_Utils::set_sprite_name( UI::Base_Sprite *sprite ,const char * name )
{
	if(sprite){
		sprite->set_name(name);
	}
}

void Game_Utils::set_sprite_title( UI::Base_Sprite *sprite ,const char * title )
{
	if(sprite){
		sprite->set_title(title);
	}
}

void Game_Utils::set_sprite_info( UI::Base_Sprite *sprite ,const char * img_path, bool use_plist )
{
	if(sprite){
		sprite->set_info(img_path, use_plist);
	}
}
void Game_Utils::createShake(int id)
{
	Shake_Manager::createShake(id);
}
int Game_Utils::get_npc_list( std::map<int, int>& list )
{
	UI::Actor_Layer* al = get_actor_layer();
	if (NULL == al)
	{
		return -1;
	}
    std::vector<int> tmp_lst;

    al->get_npc_list( tmp_lst );

    list.clear();
    std::vector<int>::iterator iti;
    for ( iti = tmp_lst.begin(); iti != tmp_lst.end(); ++ iti )
    {
        list.insert(make_pair(get_npc_static_id((*iti)),(*iti)));
    }

    return 0;
}

int Game_Utils::get_npc_static_id( int id )
{
    Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(id);
    if ( NULL == character )
        return -1;

     return character->get_static_character_id();
}

void Game_Utils::locked_screen( bool locked, int screen_num )
{
	UI::Actor_Layer* al = get_actor_layer();
	if(al){
		al->locked_screen(locked, screen_num);
	}
}

void Game_Utils::show_sign( bool bShow )
{
	UI::Game_UI_Delegate* gl = get_Game_UI_layer();
	if(gl){
		gl->show_sign(bShow);
	}
}

void Game_Utils::pre_locked_screen( bool locked, int screen_num,  call_back_handler_t pre_locked_finish_call_back )
{
	UI::Actor_Layer* al = get_actor_layer();
	if(al){
		al->pre_locked_screen(locked, screen_num, pre_locked_finish_call_back);
	}
}

int Game_Utils::load_current_monster_wave_data( list<Game_Data::Game_Command_Element> &total_monster_list )
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();

    current_instance_data cid;

    if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
    {
        CCLOG( "Error load current instance_data" );

        return false;
    }

    vector<int> monster_wave_lst;
    cid.get_monster_wave_id_list( monster_wave_lst );
//    list<Game_Data::Game_Command_Element> total_monster_list;
    list<Game_Data::Game_Command_Element> gce_lst;
    list<Game_Data::Game_Command_Element>::iterator itc;
    list<Game_Data::Game_Element>::iterator ite;
    vector<int>::iterator iti;
    for( iti = monster_wave_lst.begin(); iti != monster_wave_lst.end(); ++ iti )
    {
       Monster_Wave_Config* mwc_data = Monster_Wave_Cfg_Data_Mgr::shared_instance()->get_monster_wave_data_by_id(*iti);
       if( NULL == mwc_data )
           continue;

       gce_lst.clear();
       mwc_data->get_command_element_list(gce_lst);
       for( itc = gce_lst.begin(); itc != gce_lst.end(); ++ itc )
       {
           total_monster_list.push_back(*itc);
           
       }

    }
    return 0;
}

void Game_Utils::add_msg(const char *msg )
{
	UI::Message_Layer * msg_layer = get_Message_Layer();
	if(msg_layer){
		msg_layer->add_message(msg);
	}
}

void Game_Utils::show_alert( const char *msg )
{
	UI::Message_Layer * msg_layer = get_Message_Layer();
	if(msg_layer){
		msg_layer->show_alert(msg);
	}
}

void Game_Utils::move_to_position( float &x, float &y )
{
	UI::Actor_Layer* al = get_actor_layer();
	if(al){
		check_position(x, y);
		al->move_to(x,y);
	}
}

void Game_Utils::reset_role_actor()
{
	UI::Actor *actor = Runtime::instance()->get_primary_actor();
    if (actor)
    {
        actor->set_is_dead(false);
        reset_character(actor->sprite_id());
    }

    int general_id = get_lieutenant_id();
    if (general_id > 0)
    {
        actor = Runtime::instance()->get_actor(general_id);
        if (actor)
        {
            actor->set_is_dead(false);
            reset_character(actor->sprite_id());
        }
    }

    //reset instance data
    vector<uint64> para;
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
    para.push_back(player_id);
    para.push_back(instance_id);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("playerinstancebackhome", para);
}

void Game_Utils::reset_character(int character_id)
{
    Character* character = CHARACTER_MGR::instance()->get_character(character_id);
    if (character )
    {
        character->set_dead(0);
        character->set_character_cur_hp(character->get_character_max_hp());
        character->set_character_cur_mp(0);
        character->set_character_cur_gp(character->get_character_cur_gp());
    }
}

void Game_Utils::close_UI_Tips_Layer()
{
	Scene*  scene = Director::getInstance()->getRunningScene();
	if (!scene){
		return ;
	}
	scene->removeChildByTag(UI::TAG_TIP);
}

void Game_Utils::show_win()
{
    //to do disable exit instance button
    UI::GameUI_Layer::get_instance()->setEnableTouchEvent(false);
    Game_Utils::instance()->set_operator_is_disable(true);

	UI::Actor_Layer * al = get_actor_layer();
	if(al){
		al->show_win();
	}
	lock_hp(true);
}
void Game_Utils::instance_dialog_after_fight(int player_id,int instance_id,int instance_state)
{
	UI::Actor_Layer * al = get_actor_layer();
	if(al){
		al->instance_dialog_after_fight(player_id,instance_id,instance_state);
	}
}

void Game_Utils::show_win_finished()
{
	lock_hp(false);
}

void Game_Utils::lock_hp( bool locked )
{
	//to do 写相应逻辑
	if(locked){

	}
	else{

	}
}

void Game_Utils::add_buff( int spriteID, int buff_id )
{
	Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(spriteID);
	if ( NULL == character )
		return;
	SKILL_LOGIC::instance()->AddBuff(character, character, buff_id);
}

void Game_Utils::start_update_cd( float cd_time )
{
	UI::Game_UI_Delegate* gl = get_Game_UI_layer();
	if(gl){
		gl->start_update_cd(cd_time);
	}
}

void Game_Utils::stop_update_cd()
{
	UI::Game_UI_Delegate* gl = get_Game_UI_layer();
	if(gl){
		gl->stop_update_cd();
	}
}

bool Game_Utils::can_change_primary_actor( int sprite_id )
{
	if(false)
    {//副本是否允许使用副将
		DICTIONARY_CONFIG_MGR::instance()->show_alert(CAN_NOT_CHANGE_ROLE_INSTANCE);
		return false;
	}

	if(get_lieutenant_id() == -1)
    {//是否有休息角色
        DICTIONARY_CONFIG_MGR::instance()->show_alert(CAN_NOT_CHANGE_ROLE_NOT_STAY);
		return false;
	}

    Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(sprite_id);
	if(character == NULL || character->get_dead() == 1)
    {//休息角色是否生存
        DICTIONARY_CONFIG_MGR::instance()->show_alert(CAN_NOT_CHANGE_ROLE_DEATH);
		return false;
	}
	return true;
}

void Game_Utils::change_primary_actor( int sprite_id )
{
    Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(sprite_id);
    if (character)
    {
        Player_Base_Attr_Config_Data* config = character->get_base_attr_config_data();
        if (config)
        {
        }
		start_update_cd(10.f);
    }
    
	UI::Actor_Layer * al = get_actor_layer();
	if(al)
    {
		al->change_primary_actor(sprite_id);
	}
}

int Game_Utils::get_lieutenant_id()
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (player && player->get_fight_general_id() > 0)
    {
        return player->get_fight_general_id();
    }

	return -1;
}

void Game_Utils::update_actor_hp( int sprite_id ,int percent )
{
	UI::Game_UI_Delegate* gl = get_Game_UI_layer();
	if(gl){
		gl->update_actor_hp( sprite_id , percent );
	}
}

cocos2d::ui::Widget* Game_Utils::ShowCharAvatar(int character_id)
{
    cocos2d::ui::Widget* pNode = NULL;
    UI::Actor* actor = Runtime::instance()->get_actor(character_id);
    if (actor)
    {
    #if 0//yypp
        cocos2d::extension::CCSkeletonAnimation* pAvatar = 
            cocos2d::extension::CCSkeletonAnimation::createWithData(actor->implentation()->skeleton->data);
        pAvatar->addAnimationState();
        pAvatar->setScale(0.4f);
        pAvatar->timeScale = 1.0f;
        pAvatar->setPosition(Vec2(0,-50));
        pAvatar->setAnimation(ACTION_STD,true);

        pNode = UINodeContainer::create();
        pNode->addChild(pAvatar);
#endif		
    }

    return pNode;
}

UI::Dynamic_Sprite* Game_Utils::get_enemy_by_id(int sprite_id ,int enemy_id)
{
	UI::Actor_Layer* al = get_actor_layer();
	if (al == 0)
	{
		return NULL;
	}
	if(al->get_is_in_pk_scene()){
		if(sprite_id == al->get_primary_actor()->sprite_id()){
			return al->get_opponent();
		}
		else{
			return al->get_primary_actor();
		}
	}
	else{
		return al->get_monstor(enemy_id);
	}
}

void Game_Utils::set_is_hosting( bool is_hosting )
{
	UI::Actor_Layer * al = get_actor_layer();
	if(al){
		al->get_primary_actor()->set_is_hosting(is_hosting);
		set_operator_is_disable(is_hosting);
	}
}

void Game_Utils::set_operator_is_disable( bool is_disable )
{
	UI::Game_Scene_Operator_Layer * ol = get_Game_Scene_Operator_Layer();
	if(ol){
		ol->set_is_disable(is_disable);
	}
	UI::Unique_Skill*ul = get_Unique_layer();
	if(ul){
		ul->set_is_hosting(is_disable);
	}
}

void Game_Utils::release_Unique_Skill()
{
	UI::Unique_Skill*ul = get_Unique_layer();
	if(ul){
		ul->releaseUniqueSkill(NULL);//,Widget::TouchEventType::ENDED
	}
}

void Game_Utils::do_Pressed_Key_C()
{
	UI::Actor_Layer * al = get_actor_layer();
	if(al){
		al->get_primary_actor()->logic_processor()->process_event(FSM::Event::Key_Pressed_C());
		if(Runtime::instance()->is_in_real_time_pk_scene()){
					send_Real_Time_pk_press_key(3);
		}
	}
}

UI::Dynamic_Sprite* Game_Utils::get_asynchronous_battle_opponent( int sprite_id )
{
	UI::Actor_Layer* al = get_actor_layer();
	if (al == 0)
	{
		return NULL;
	}
	if(al->get_is_in_pk_scene()){
		if(sprite_id == al->get_primary_actor()->sprite_id()){
			return al->get_opponent();
		}
		else{
			return al->get_primary_actor();
		}
	}
	return NULL;
}

void Game_Utils::asynchronous_battle_win()
{
	set_operator_is_disable(true);
    int cur_rank = OFFLINE_FIGHT_MGR::instance()->get_self_cur_rank();
    Game_Data::offline_fight_challenge_reward_config* config = FIGHT_CONFIG_MGR::instance()->get_offline_fight_challenge_reward_config(cur_rank);
    if (config)
    {
		UI::Game_UI_Delegate * gl = get_Game_UI_layer();
		if(gl){
			gl->showResult(true, config->win_gold_, config->win_prestige_);
		}
    }
    
    OFFLINE_FIGHT_LOGIC::instance()->offline_fight_finish(get_opponent()->sprite_id(),1);
}

void Game_Utils::asynchronous_battle_fail()
{
	set_operator_is_disable(true);
    int cur_rank = OFFLINE_FIGHT_MGR::instance()->get_self_cur_rank();
    Game_Data::offline_fight_challenge_reward_config* config = FIGHT_CONFIG_MGR::instance()->get_offline_fight_challenge_reward_config(cur_rank);
    if (config)
    {
		UI::Game_UI_Delegate * gl = get_Game_UI_layer();
		if(gl){
			gl->showResult(false, config->lose_gold_, config->lose_prestige_);
		}
    }

    OFFLINE_FIGHT_LOGIC::instance()->offline_fight_finish(get_opponent()->sprite_id(),0);
}

void Game_Utils::asynchronous_battle_reset_data()
{
	UI::Actor* actor = get_primary_actor();
	actor->set_is_dead(false);
	reset_character(actor->sprite_id());
	actor = get_opponent();
	actor->set_is_dead(false);
	reset_character(actor->sprite_id());
}

void Game_Utils::start_asynchronous_battle()
{
	get_opponent()->set_is_hosting(true);
	set_operator_is_disable(false);
	UI::Game_UI_Delegate * gl = get_Game_UI_layer();
	if(gl){
		gl->updateCountdownCallback();
	}
}

UI::Trigger_Sprite* Game_Utils::get_trigger_sprite( int sprite_id )
{
	UI::Actor_Layer * al = get_actor_layer();
	if(al){
		return al->get_trigger_sprite(sprite_id);
	}
	return NULL;
}

UI::Treasure_Box_Sprite* Game_Utils::get_treasure_box_sprite( int sprite_id )
{
	UI::Actor_Layer * al = get_actor_layer();
	if(al){
		al->get_treasure_box_sprite(sprite_id);
	}
	return NULL;
}

void Game_Utils::create_trigger_sprite( int sprite_prototype_id,int &sprite_id, float born_point_x, float born_point_y )
{
	sprite_id = -1;
	UI::Actor_Layer * al = get_actor_layer();
	if(al){
		al->create_trigger_sprite(sprite_prototype_id, sprite_id, born_point_x, born_point_y);
	}
}

void Game_Utils::create_treasure_box_sprite( int sprite_prototype_id,int &sprite_id, float born_point_x, float born_point_y )
{
	sprite_id = -1;
	UI::Actor_Layer * al = get_actor_layer();
	if(al){
		al->create_treasure_box_sprite(sprite_prototype_id, sprite_id, born_point_x, born_point_y);
	}
}

void Game_Utils::do_trigger_sprite_event( int sprite_id )
{
	UI::Trigger_Sprite* ts=get_trigger_sprite(sprite_id);
	int static_id=ts->get_static_id_();

	//客户端自己的事情
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	vector<uint64> para;
	para.push_back(sprite_id);

	Game_Logic::Game_Event ge;
	ge.reset();
	ge.set_char_id(player_id);
	ge.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
	ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_COLLIDED_SOMETHING);
	ge.set_event_active_id(static_id);
	//ge.set_para(para);
	Game_Logic::Game_Event_Mgr::instance()->proc_event(player_id,"collided_something",ge);
	//////////////////////////////////////////////////////////////////////////////////////////
	//发送消息到服务器



	//发送碰到物品的消息
	std::vector<uint64> paras;
	paras.push_back(static_id);
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_player_instance_collided_something", paras);
	


	printf("do_trigger_sprite_event with sprite(%d)\n", sprite_id);
}

void Game_Utils::do_treasure_box_sprite_event( int sprite_id )
{
	printf("do_treasure_box_sprite_event with sprite(%d)\n", sprite_id);
}

void Game_Utils::add_effect_to_actor_layer( const char *effect_id, float bass_x, float base_y, float base_z, int ZOrder, bool bflip)
{
	UI::Actor_Layer * al = get_actor_layer();
	if(al){
		cocos2d::Sprite *effect = cocos2d::Sprite::create();
		if(Effect_Cfg_Data_Mgr::instance()->get_effect(effect, effect_id) == 0){
			effect->setVisible(false);
			effect->setPosition(Vec2(effect->getPositionX() + bass_x, effect->getPositionY() + base_y + base_z));
			effect->setFlipX(bflip);
			al->addChild(effect,ZOrder);
		}
	}
}

void Game_Utils::add_projectile_to_actor_layer( int projectile_id,int &sprite_id, int owner_sprite_id, float born_point_x, float born_point_y, float born_point_z, bool bflip, int ZOrder )
{
	sprite_id = -1;
	UI::Dynamic_Sprite::Direction direction = bflip ? UI::Dynamic_Sprite::LEFT : UI::Dynamic_Sprite::RIGHT;
	UI::Actor_Layer * al = get_actor_layer();
	if(al){
		UI::Projectile_Sprite* projectile_sprite = UI::Projectile_Sprite::create(projectile_id, sprite_id, owner_sprite_id, born_point_x, born_point_y, born_point_z, direction);
		al->addChild(projectile_sprite, ZOrder, sprite_id);
		projectile_sprite->set_hit_test_delegate(al);
	}
}

void Game_Utils::play_continued_effect( int sprite_id, const std::string& effect_id, int &effect_tag )
{
	effect_tag = -1;
	UI::Actor_Layer * al = get_actor_layer();
	if(al){
		UI::Dynamic_Sprite* sprite = al->get_sprite_by_id(sprite_id);
		if(sprite){
			sprite->play_continued_effect(effect_id, effect_tag);
		}
	}
}

void Game_Utils::remove_continued_effect( int sprite_id, int effect_tag )
{
	UI::Actor_Layer * al = get_actor_layer();
	if(al){
		UI::Dynamic_Sprite* sprite = al->get_sprite_by_id(sprite_id);
		if(sprite)
			sprite->remove_continued_effect(effect_tag);
	}
}

void Game_Utils::add_effect_to_scene( const std::string& effect_id )
{
	cocos2d::Sprite *effect = cocos2d::Sprite::create();
	Effect_Cfg_Data_Mgr::instance()->get_effect(effect, effect_id);
	Director::getInstance()->getRunningScene()->addChild(effect, 30);
}

void Game_Utils::add_effect_to_scene( const std::string& effect_id ,const cocos2d::Point &pos)
{
    cocos2d::Sprite *effect = cocos2d::Sprite::create();
    Effect_Cfg_Data_Mgr::instance()->get_effect(effect, effect_id);
    effect->setPosition(pos);
    Director::getInstance()->getRunningScene()->addChild(effect, 30);
}

void Game_Utils::add_image_to_scene(const std::string iamgepath,float time)
{
	cocos2d::Sprite *image=cocos2d::Sprite::create();
	Effect_Cfg_Data_Mgr::instance()->get_image(image,iamgepath.c_str(),time);
	Director::getInstance()->getRunningScene()->addChild(image, 30);
}

bool Game_Utils::srpite_get_is_stunning( int sprite_id )
{
	UI::Actor_Layer * al = get_actor_layer();
	if(al){
		UI::Dynamic_Sprite* sprite = al->get_sprite_by_id(sprite_id);
		if(sprite)
			return sprite->get_is_stunning();
	}
	return true;
}

void Game_Utils::srpite_set_is_stunning(int sprite_id, bool is_stunning)
{
	UI::Actor_Layer * al = get_actor_layer();
	if(al){
		UI::Dynamic_Sprite* sprite = al->get_sprite_by_id(sprite_id);
		if(sprite)
			sprite->set_is_stunning(is_stunning);
	}
}

void Game_Utils::sprite_set_move_scale(int sprite_id, float move_scale)
{
	UI::Actor_Layer * al = get_actor_layer();
	if(al){
		UI::Dynamic_Sprite* sprite = al->get_sprite_by_id(sprite_id);
		if(sprite)
			sprite->set_move_scale(move_scale);
	}
}

void Game_Utils::start_Real_Time_PK()
{
	CCLOG("start_Real_Time_PK");
}

void Game_Utils::Real_Time_PK_win()
{
	CCLOG("Real_Time_PK_win");
	//? for test
	UI::Game_UI_Delegate * gl = get_Game_UI_layer();
	if(gl){
		gl->showResult(true, 0, 0);
	}
	//?
}

void Game_Utils::Real_Time_PK_fail()
{
	CCLOG("Real_Time_PK_fail");
	//? for test
	UI::Game_UI_Delegate * gl = get_Game_UI_layer();
	if(gl){
		gl->showResult(false, 0, 0);
	}
	//?
}

void Game_Utils::Real_Time_PK_reset_data()
{
	CCLOG("Real_Time_PK_reset_data");
	reset_character(get_primary_actor_id());
	reset_character(get_opponent()->sprite_id());
}

Real_Time_Operator* Game_Utils::get_real_time_operator()
{
	UI::Actor_Layer * al = get_actor_layer();
	if(al){
		return al->get_real_time_operator();
	}
	return NULL;
}

bool Game_Utils::on_Real_Time_pk_joystick_velocity( int x, int y )
{
	Real_Time_Operator * real_time_operator = get_real_time_operator();
	if(!real_time_operator){
		return false;
	}
	real_time_operator->set_joystick_velocity((float)x, (float)y);
	return true;
}

bool Game_Utils::on_Real_Time_pk_press_key( int key )
{
//	CCLOG("Game_Utils::on_Real_Time_pk_press_key( int key = %d )",key);
	Real_Time_Operator * real_time_operator = get_real_time_operator();
	if(!real_time_operator){
		return false;
	}
	real_time_operator->on_attack_began(key);
	return true;
}

void Game_Utils::send_Real_Time_pk_joystick_velocity( int x, int y )
{
	int target_id = get_opponent()->sprite_id();
	vector<uint64> para;
	para.push_back(target_id);
	para.push_back(x);
	para.push_back(y);
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_online_fight_move",para);
}

void Game_Utils::send_Real_Time_pk_press_key( int key )
{
//	CCLOG("Game_Utils::send_Real_Time_pk_press_key( int key = %d )",key);
	int target_id = get_opponent()->sprite_id();
	vector<uint64> para;
	para.push_back(target_id);
	para.push_back(key);
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_online_fight_use_skill",para);
}

void Game_Utils::send_Real_Time_PK_result( bool bWin )
{
	CCLOG("send Real Time PK Result %s", bWin?"win":"fail");

	int target_id = get_opponent()->sprite_id();
	vector<uint64> para;
	para.push_back(target_id);
	para.push_back(bWin);
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_online_fight_result",para);
}

void Game_Utils::on_Real_Time_PK_result( bool bWin )
{
	CCLOG("on Real Time PK Result %s", bWin?"win":"fail");
	UI::Actor_Layer * al = get_actor_layer();
	if(!al){
		return;
	}
	if(bWin){
		al->get_opponent()->dead(0);
		update_actor_hp(al->get_opponent()->sprite_id(), 0);
		Real_Time_PK_win();
	}
	else{
		al->get_primary_actor()->dead(0);
		update_actor_hp(al->get_primary_actor()->sprite_id(), 0);
		Real_Time_PK_fail();
	}
}

void Game_Utils::kill_all_monster()
{
    UI::Actor_Layer * al = get_actor_layer();
    if(!al){
        return;
    }
    
    al->kill_all_monster();
}
#endif
