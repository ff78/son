#ifndef ACTOR_LAYER_H
#define ACTOR_LAYER_H
#pragma warning(disable:4251) 
//#include "cocos-ext.h"
#include "cocos2d.h"
//#include "Actor.h"
//#include "Pet.h"
//#include "Monster.h"
//#include "NPC.h"
//#include "Treasure_Box_Sprite.h"
//#include "Trigger_Sprite.h"
#include <list>
#include <vector>
#include <map>
//#include "Dynamic_Sprite.h"
//#include "Operator_Delegate.h"
//#include "Adjust_Delegate.h"
//#include "Hit_Test_Delegate.h"
//#include "Background_Delegate.h"
//#include "NPC_Delegate.h"
#include "json/json_header.h"
#include "Common/GameDefine.h"
//#include "Scene_Utils.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;
#define TIME_SCALE_SHOW_WIN 0.2f
#define SHOW_WIN_DELAY 2.f

#define TIME_SCALE_PRIMAY_ACTOR_DEAD 0.2f
#define SHOW_PRIMAY_ACTOR_DEAD_DELAY 0.4f

namespace UI{
//class Active_Area_Delegate;
};

class Real_Time_Operator;

typedef std::list<int> Sprite_List;
USING_NS_CC;

namespace UI
{
// typedef std::map<int, NPC *> NPC_Map;
 //typedef std::pair<int, NPC *> NPC_Pair;

  //, public Operator_Delegate, public Adjust_Delegate//, public Hit_Test_Delegate, public NPC_Delegate
  class Actor_Layer : public Layer
  {
  public:
    Actor_Layer();
	virtual ~Actor_Layer();
    virtual bool init();
    virtual void onExit();
	virtual void onEnter();
    virtual void update(float dt);
    bool init_primay_actor();
	bool init_pet();
	bool init_asynchronous_battle_opponent();
	bool init_real_time_pk_opponent();
    bool init_monster();
	bool init_npc();
	bool init_portal(Json::Value &json_value);

	void pre_init_monster();
	void pre_init_npc();
    CREATE_FUNC(Actor_Layer);

	void init_monster_wave();
	void clean_monster(Node *node);
	std::map<int , int >& get_monster_prototype_map();
  public:
    virtual void on_move_began();
    virtual void on_move_ended();
    virtual void on_moving(float x, float y, float dt);
    virtual void on_attack_began(int n);
    virtual void on_attack_ended(int n);

	//void set_adjust_delegate(Adjust_Delegate * delegate);
    void adjust_backgroud(float& x, float& y);
	virtual void auto_move_adjust_backgroud(float& x);
	void set_is_auto_moving(bool is_auto_move);
    void show_effect(int n,float x,float y);

	//virtual void NPC_Clicked(int sprite_id);
    //{for testing
    #if 0
    cocos2d::extension::CCSkeleton* get_enemy_skeletion (int id);
    cocos2d::extension::CCSkeleton* get_self_skeletion ();
#endif
//    Monster*         get_monstor(int id);
	//Actor*        get_primary_actor();
	//Pet *		  get_pet();
	//NPC *			get_npc(int id);
	//Dynamic_Sprite * get_sprite_by_id(int id);
    int             get_npc_list( std::vector<int>& list );
	Sprite_List * get_monster_list_ptr();


   // virtual void             hit_test(int sprite_id, int skill_id, bool center_blow );
	//virtual void monster_hit_test( int sprite_id, int skill_id, bool center_blow );//add by LiaoPengfei 20130617,怪物攻击
	//virtual void projectile_hit_test( int sprite_id, int owner_sprite_id, int skill_id, bool center_blow , bool hit_remove );
	//virtual void monster_hurt_finished(int spriteID);//怪物受创结束
//	virtual void monster_is_stunning(int spriteID, bool is_stunning);
//	virtual void update_monster_attack_status(int sprite_id,bool is_attacking);//更新怪物攻击状态


	//void check_position(float &x, float &y);//修正精灵位置，防止越界
	void check_position_x(float &x);//修正精灵位置，防止越界
	void check_position_y(float &y);//修正精灵位置，防止越界

	void get_born_position(float &born_x, float &born_y, int center_x, int center_y, int radius);

	//Dynamic_Sprite * get_sprite(int id, int type);

	void sprite_dead(int id, int type, int dead_type);
//	void  sprite_hurt(int id, int type, int attcker_id, Hurt_Type hurt_type, int value, float hurting_vellovity, float hurting_v_h_vellovity, float hurt_time = 0.5f);

	void kill_all_monster();
	void show_win();
	void instance_dialog_after_fight(int player_id,int instance_id,int instance_state);
	static int palyer_dialog_id;
	static int instance_dialog_id;
	static int instance_dialog_state;
	void instance_dialog_callback();
	void show_win_callback();
	void play_win_effect();
	void do_primay_actor_callback();

	// for 异步PK
	//Actor* get_opponent();
	Real_Time_Operator* get_real_time_operator();
	void update_real_time_operator(float dt);
//	void pre_to_start_asynchronous_battle();
	void start_asynchronous_battle();
	//-------------------

	// for 场景
//	bool get_is_in_city_scene();
	//bool get_is_in_instance_scene();
	//bool get_is_in_offline_pk_scene();
	//bool get_is_in_real_time_pk_scene();

	bool get_is_in_pk_scene();
	//-------------------

	// for 掉落
//	Trigger_Sprite*  get_trigger_sprite(int id);
//	Treasure_Box_Sprite*  get_treasure_box_sprite(int id);
	void create_trigger_sprite (int sprite_prototype_id,int &sprite_id, float born_point_x, float born_point_y);
	void create_treasure_box_sprite (int sprite_prototype_id,int &sprite_id, float born_point_x, float born_point_y);
	void do_trigger_sprite_event(int sprite_id);
	void do_treasure_box_sprite_event(int sprite_id);
	//-------------------
  public:
	  void move_to(float x, float y);
	  //void move_to_portal(int id);
//      void quest_auto_move(int x,int y,CallBackFun fun,int param);

	  void change_primary_actor( int sprite_id );

  public:
	  //Background_Delegate * get_background_delegate();
	  //void set_background_delegate(Background_Delegate * background_delegate);
	 // void set_active_area_delegate(Active_Area_Delegate * active_area_delegate);
	  //void locked_screen( bool locked, int screen_num = 1 );
	  void pre_locked_screen( bool locked, int screen_num , call_back_handler_t pre_locked_finish_call_back = NULL);
	  void show_sign(bool bShow = true);
	  void start_pre_locked();
  public:
	  //virtual void addChild(Node * child);
	  //virtual void addChild(Node * child, int zOrder);
	 // virtual void addChild(Node* child, int zOrder, int tag);
	  Node * getChildByTag(int tag);

      static void show_npc_dialogue(int sprite_id);

  private:
  //  Actor*         primary_actor_;//玩家
	//Pet*			pet_;//宠物
//	Actor*		   opponent_;//对手
    Sprite_List		monster_list_;//怪物
	Sprite_List		trigger_sprite_list_;
	Sprite_List		treasure_box_list_;
	//NPC_Map npc_map_;

	//Adjust_Delegate * delegate_;

	Json::Value scene_config;
	int monster_waves_;
	int current_wave_;
	std::map< int , int > monster_prototype_map_; //每波怪物的详细详细 map<原型, 数量>
	std::map< int ,std::vector < int > > monster_wave_map_;//所有怪物波信息 map<波数， vector<怪物ID>>

    bool is_in_portal_;

	//Background_Delegate * background_delegate_;
	//Active_Area_Delegate * active_area_delegate_;

	bool pre_locked_screen_;
	bool need_pre_locked_screen_moving_;
	bool is_auto_moving_;
	int screen_num_;
	float locked_min_x_;
	float current_pos_x_;
	float move_to_pos_x_;
	call_back_handler_t pre_locked_finish_call_back_;

	Real_Time_Operator * real_time_operator_;//即时战斗的操控逻辑类

//	SCENE_TYPE scene_type_;
	static	bool is_played_flash_;

  };
};



#endif /* ACTOR_LAYER_H */
