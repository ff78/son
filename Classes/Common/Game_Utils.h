#ifndef GAME_UTLIS
#define GAME_UTLIS

#include <list>
#include <map>
#include <string>
#include <vector>
#include "Common/GameDefine.h"
//#include "Shake_System/Shake_Manager.h"
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include "ui/UITextField.h"
#include "ui/UILoadingBar.h"
#include "ui/UILayout.h"
#include "ui/UISlider.h"
#include "ui/UICheckBox.h"
#include "ui/UIWidget.h"
#if 0
#include "CocoStudio/GUI/UIWidgets/Compatible/CompatibleClasses.h"
#endif
//#include "Real_Time_Operator.h"
#if 1
class Actor;
class CityLayer;
class City_NPC;
typedef void(*CallBackFun)(int);
namespace UI
{
	class Message_Layer;
}

#else
namespace UI
{
    class Actor;
    class Monster;
    class Actor_Layer;
	class NPC;
	class Pet;
	class Trigger_Sprite;
	class Treasure_Box_Sprite;
	class Base_Sprite;
	class Game_UI_Delegate;
	class Message_Layer;
	class Dynamic_Sprite;
	class Game_Scene_Operator_Layer;
	class Unique_Skill;
}

namespace FSM{
	class Monster;
}

struct Hurt_Args{
	int hurt_sprite_id_;	//受伤精灵id
	int hurt_sprite_type_;	//受伤精灵类型
	int hurt_type_;			//受伤类型
	int hurt_value_;		//受伤值
	int attcker_id_;		//攻击者id
	int yinzhi_time_;       //硬直时间
	float hurting_vellovity_;	//受创运动方向速度。水平方向
	float hurting_v_h_vellovity_; //受创运动速度，垂直方向

	Hurt_Args(int hurt_sprite_id , int hurt_sprite_type, int hurt_type, int hurt_value, int attcker_id, int yinzhi_time, float hurting_vellovity = 0.f, float hurting_v_h_vellovity = 0.f){
		hurt_sprite_id_ = hurt_sprite_id;
		hurt_sprite_type_ = hurt_sprite_type;
		hurt_type_ = hurt_type;
		hurt_value_ = hurt_value;
		attcker_id_ = attcker_id;
		yinzhi_time_ = yinzhi_time;
		hurting_vellovity_ = hurting_vellovity;
		hurting_v_h_vellovity_ = hurting_v_h_vellovity;
	}
};

struct Show_Top_Args
{
	int hurt_sprite_id_;	//受伤精灵id
	int hurt_sprite_type_;	//受伤精灵类型
	std::string image_name_; //图像名字
	Show_Top_Args(int hurt_sprite_id, int hurt_sprite_type, std::string image_name)
	{
		hurt_sprite_id_   = hurt_sprite_id;
		hurt_sprite_type_ = hurt_sprite_type;
		image_name_       = image_name;
	}
};

typedef void(*CallBackFun)(int);

namespace Game_Data
{
    struct Game_Command_Element;
}

// namespace cocos2d 
// {
//     namespace extension 
//     {
//         class cocos2d::ui::Widget;
//     }
// }

enum Charcter_AI_State
{
	MISS_STATE,   // 攻击范围内没有覆盖任何可攻击对象
	GUARD_STATE,  // 正常击中敌人、但有任意防御属性（罡气、无敌、闪避）生效的情况
	NOMAL_STATE,  // 正常击中敌人、造成正常受创动作（包括击破罡气的情况）
};
#endif
class Game_Utils
{
public:
    Game_Utils() {}
    ~Game_Utils() {}
#if 1
	City_NPC * get_npc_by_id(int id);
	int  get_npc_list(std::map<int, int>& list);
	void set_sprite_info(int npcId, const char * img_path, bool use_plist = false);//设置精灵的消息图片（头顶那东西）。示例：AI_UTils::instance()->set_sprite_info(AI_UTils::instance()->get_npc_by_id(1001), "buttonA_2.png");
	void add_effect_to_scene(const std::string& effect_id);
	int get_npc_static_id(int id);
	static Game_Utils* instance();
	void quest_auto_move(int npcId, CallBackFun func, int param);
	static void clicked_area(int area_id);	
	static void show_npc_dialog(int sprite_id);
    void show_alert( const char *msg );	
#else
	UI::Actor *			get_primary_actor();//获取主角
	UI::Pet *			get_pet();//获取宠物
	UI::Dynamic_Sprite *			get_primary_sprite_by_type(int type);//通过类型获取主角或宠物
	UI::Dynamic_Sprite *			get_primary_sprite_by_id(int id);//通过id获取主角或宠物
	UI::Actor *			get_opponent();
    UI::Actor*          get_player_by_id(int id);
    UI::Monster *       get_monster_by_id(int id);
	UI::NPC *			get_npc_by_id(int id);
    std::list<int> *    get_monster_list();
	FSM::Monster *		get_fsm_monster_by_id(int id);//获取怪物状态机
	bool check_position(float &x, float &y);
	bool check_position_x(float &x);
	bool check_position_y(float &y);
	void                dead(int id, int type, int dead_type);
	void				update_combo(int id, int type, int combo);

	void				hurt(Hurt_Args & hurt_args);
	void                stop();
	Charcter_AI_State	get_ai_state(int character_id);
	void				start_ai_state(int character_id);

	void				show_top(Show_Top_Args & show_top_args);

	void				get_actor_attack_list(int prototype_id, std::list<int> & list);

    void                init_monser_wave( void );
    void                get_monster_prototype_map( std::map<int,int>& mst_lst);
    int                 get_primary_actor_id( void );
	int                 get_pet_id( void );

	//void move_to_portal(int id);
    void quest_auto_move(int x,int y,CallBackFun fun,int param);
	void move_to_position(float &x, float &y);

    void add_actor(UI::Actor* actor, float x, float y);
    void remove_actor(UI::Actor* actor);
	bool is_in_city();

	//判断怒气是否已满
	bool gas_full_ro_not(int spreite_id);

    int  get_npc_list( std::map<int, int>& list );

	void set_sprite_name(UI::Base_Sprite *sprite ,const char * name);//设置精灵的名字。sprite通过 get_primay_actor()，get_monster_by_id(int id)，get_npc_by_id(int id)分别获取
	void set_sprite_title(UI::Base_Sprite *sprite ,const char * title);//设置精灵的称号
	void set_sprite_info(UI::Base_Sprite *sprite ,const char * img_path, bool use_plist = false);//设置精灵的消息图片（头顶那东西）。示例：AI_UTils::instance()->set_sprite_info(AI_UTils::instance()->get_npc_by_id(1001), "buttonA_2.png");

	void locked_screen( bool locked, int screen_num );//副本中卡屏，locked加锁或解锁，screen_num锁到第几个屏幕（1-4）；
	void pre_locked_screen( bool locked, int screen_num, call_back_handler_t pre_locked_finish_call_back = NULL);//预卡屏。界面停留在当前屏幕，准备卡到第screen_num屏，并提示玩家向前跑动
	void show_sign(bool bShow);

    //for monster wave interface

    int load_current_monster_wave_data( std::list<Game_Data::Game_Command_Element> &total_monster_list );

    int get_npc_static_id( int id );

	void add_msg(const char *msg);//添加系统消息。示例：AI_UTils::instance()->add_msg(msg);
	void show_alert(const char *msg);//添加提示消息。示例：AI_UTils::instance()->show_alert(msg);

	void reset_role_actor();//恢复角色(主角与出战副将)
    void reset_character(int character_id);//重新修改角色数据(生命 怒气 罡气)

	void close_UI_Tips_Layer();
	void show_win();
	void show_win_finished();
	void lock_hp(bool locked);//锁定血条，保证不死
	void add_buff(int spriteID, int buff_id);//增加Buff
    //-------------------------
	// for cd
	void start_update_cd(float cd_time);//开始副将切换cd
	void stop_update_cd();//停止副将切换cd
	bool can_change_primary_actor(int sprite_id);//是否可以切换
	void change_primary_actor( int sprite_id );//切换
	int get_lieutenant_id();//获取副将id
	void update_actor_hp(int sprite_id ,int percent);//刷新战斗中角色血量
	//-------------------------
	// for 托管 and 异步PK
	UI::Dynamic_Sprite*  get_enemy_by_id(int sprite_id ,int enemy_id);
	void set_is_hosting(bool is_hosting);
	void release_Unique_Skill();
	void do_Pressed_Key_C();

	void set_operator_is_disable(bool is_disable);

	UI::Dynamic_Sprite*   get_asynchronous_battle_opponent(int sprite_id);
	void start_asynchronous_battle();
	void asynchronous_battle_win();
	void asynchronous_battle_fail();
	void asynchronous_battle_reset_data();
	//-------------------------
	// for 掉落
	UI::Trigger_Sprite*  get_trigger_sprite(int sprite_id); //获取一个药品类精灵。其中sprite_id为创建时动态分配的唯一标示符
	UI::Treasure_Box_Sprite*  get_treasure_box_sprite(int sprite_id); //获取一个宝箱类精灵。其中sprite_id为创建时动态分配的唯一标示符
	void create_trigger_sprite (int sprite_prototype_id,int &sprite_id, float born_point_x, float born_point_y);//创建一个药品类精灵. 创建失败，sprite_id = -1
	void create_treasure_box_sprite (int sprite_prototype_id,int &sprite_id, float born_point_x, float born_point_y);//创建一个宝箱类精灵. 创建失败，sprite_id = -1
	void do_trigger_sprite_event(int sprite_id);//响应药品类精灵事件
	void do_treasure_box_sprite_event(int sprite_id);//响应宝箱类精灵事件
	//-------------------
	//-------------------------
	// for 飞行道具
	void add_effect_to_actor_layer(const char *effect_id, float bass_x, float base_y, float base_z, int ZOrder, bool bflip);
	void add_projectile_to_actor_layer(int projectile_id,int &sprite_id, int owner_sprite_id, float born_point_x, float born_point_y, float born_point_z, bool bflip, int ZOrder);
	//-------------------
	//-------------------------
	// for 给精灵加持续性特效
	void play_continued_effect(int sprite_id, const std::string& effect_id, int &effect_tag);//创建特效持续特效。effect_tag为该特效在精灵中的唯一标识符，失败时为 -1；
	void remove_continued_effect(int sprite_id, int effect_tag);//移除某持续特效
	//-------------------

	// for 给场景加特效
	void add_effect_to_scene(const std::string& effect_id);
    void add_effect_to_scene(const std::string& effect_id,const cocos2d::Point& pos);
	// for 给场景加图片效果
	void add_image_to_scene(const std::string iamgepath,float time);
	//延时显示副本结束时的dialog
	void instance_dialog_after_fight(int player_id,int instance_id,int instance_state);

	//-------------------

	// for 减速，眩晕
	bool srpite_get_is_stunning(int sprite_id); //获取精灵的眩晕状态。精灵不存在时，返回true
	void srpite_set_is_stunning(int sprite_id, bool is_stunning);//设置精灵的眩晕状态
	void sprite_set_move_scale(int sprite_id, float move_scale);//设置精灵移动速度倍率。正常速度为1.0f
	//-------------------

	// for 即时PK
	Real_Time_Operator* get_real_time_operator();//获取即时PK操纵逻辑
	void start_Real_Time_PK();//开始即时PK
	void Real_Time_PK_win();//赢
	void Real_Time_PK_fail();//输
	void Real_Time_PK_reset_data();//结束即时PK，恢复数据

	void send_Real_Time_PK_result(bool bWin);
	void on_Real_Time_PK_result(bool bWin);

	void send_Real_Time_pk_joystick_velocity(int x, int y);
	void send_Real_Time_pk_press_key(int key);
	bool on_Real_Time_pk_joystick_velocity(int x, int y);
	bool on_Real_Time_pk_press_key(int key);

    void kill_all_monster();
	//-------------------------
    cocos2d::ui::Widget* ShowCharAvatar(int character_id);

    static Game_Utils* instance();

	//屏幕震动
	static void createShake(int id);
#endif
private:
#if 1
	CityLayer* get_actor_layer();
	UI::Message_Layer *  get_Message_Layer();
#else
	UI::Actor_Layer*    get_actor_layer();
	UI::Game_UI_Delegate *  get_Game_UI_layer();
	UI::Message_Layer *  get_Message_Layer();
	UI::Game_Scene_Operator_Layer * get_Game_Scene_Operator_Layer();
	UI::Unique_Skill*			get_Unique_layer();
#endif
    static Game_Utils* instance_;
};

#endif