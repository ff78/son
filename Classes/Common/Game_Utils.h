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
	int hurt_sprite_id_;	//���˾���id
	int hurt_sprite_type_;	//���˾�������
	int hurt_type_;			//��������
	int hurt_value_;		//����ֵ
	int attcker_id_;		//������id
	int yinzhi_time_;       //Ӳֱʱ��
	float hurting_vellovity_;	//�ܴ��˶������ٶȡ�ˮƽ����
	float hurting_v_h_vellovity_; //�ܴ��˶��ٶȣ���ֱ����

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
	int hurt_sprite_id_;	//���˾���id
	int hurt_sprite_type_;	//���˾�������
	std::string image_name_; //ͼ������
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
	MISS_STATE,   // ������Χ��û�и����κοɹ�������
	GUARD_STATE,  // �������е��ˡ���������������ԣ�������޵С����ܣ���Ч�����
	NOMAL_STATE,  // �������е��ˡ���������ܴ�������������������������
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
	void set_sprite_info(int npcId, const char * img_path, bool use_plist = false);//���þ������ϢͼƬ��ͷ���Ƕ�������ʾ����AI_UTils::instance()->set_sprite_info(AI_UTils::instance()->get_npc_by_id(1001), "buttonA_2.png");
	void add_effect_to_scene(const std::string& effect_id);
	int get_npc_static_id(int id);
	static Game_Utils* instance();
	void quest_auto_move(int npcId, CallBackFun func, int param);
	static void clicked_area(int area_id);	
	static void show_npc_dialog(int sprite_id);
    void show_alert( const char *msg );	
#else
	UI::Actor *			get_primary_actor();//��ȡ����
	UI::Pet *			get_pet();//��ȡ����
	UI::Dynamic_Sprite *			get_primary_sprite_by_type(int type);//ͨ�����ͻ�ȡ���ǻ����
	UI::Dynamic_Sprite *			get_primary_sprite_by_id(int id);//ͨ��id��ȡ���ǻ����
	UI::Actor *			get_opponent();
    UI::Actor*          get_player_by_id(int id);
    UI::Monster *       get_monster_by_id(int id);
	UI::NPC *			get_npc_by_id(int id);
    std::list<int> *    get_monster_list();
	FSM::Monster *		get_fsm_monster_by_id(int id);//��ȡ����״̬��
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

	//�ж�ŭ���Ƿ�����
	bool gas_full_ro_not(int spreite_id);

    int  get_npc_list( std::map<int, int>& list );

	void set_sprite_name(UI::Base_Sprite *sprite ,const char * name);//���þ�������֡�spriteͨ�� get_primay_actor()��get_monster_by_id(int id)��get_npc_by_id(int id)�ֱ��ȡ
	void set_sprite_title(UI::Base_Sprite *sprite ,const char * title);//���þ���ĳƺ�
	void set_sprite_info(UI::Base_Sprite *sprite ,const char * img_path, bool use_plist = false);//���þ������ϢͼƬ��ͷ���Ƕ�������ʾ����AI_UTils::instance()->set_sprite_info(AI_UTils::instance()->get_npc_by_id(1001), "buttonA_2.png");

	void locked_screen( bool locked, int screen_num );//�����п�����locked�����������screen_num�����ڼ�����Ļ��1-4����
	void pre_locked_screen( bool locked, int screen_num, call_back_handler_t pre_locked_finish_call_back = NULL);//Ԥ����������ͣ���ڵ�ǰ��Ļ��׼��������screen_num��������ʾ�����ǰ�ܶ�
	void show_sign(bool bShow);

    //for monster wave interface

    int load_current_monster_wave_data( std::list<Game_Data::Game_Command_Element> &total_monster_list );

    int get_npc_static_id( int id );

	void add_msg(const char *msg);//���ϵͳ��Ϣ��ʾ����AI_UTils::instance()->add_msg(msg);
	void show_alert(const char *msg);//�����ʾ��Ϣ��ʾ����AI_UTils::instance()->show_alert(msg);

	void reset_role_actor();//�ָ���ɫ(�������ս����)
    void reset_character(int character_id);//�����޸Ľ�ɫ����(���� ŭ�� ���)

	void close_UI_Tips_Layer();
	void show_win();
	void show_win_finished();
	void lock_hp(bool locked);//����Ѫ������֤����
	void add_buff(int spriteID, int buff_id);//����Buff
    //-------------------------
	// for cd
	void start_update_cd(float cd_time);//��ʼ�����л�cd
	void stop_update_cd();//ֹͣ�����л�cd
	bool can_change_primary_actor(int sprite_id);//�Ƿ�����л�
	void change_primary_actor( int sprite_id );//�л�
	int get_lieutenant_id();//��ȡ����id
	void update_actor_hp(int sprite_id ,int percent);//ˢ��ս���н�ɫѪ��
	//-------------------------
	// for �й� and �첽PK
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
	// for ����
	UI::Trigger_Sprite*  get_trigger_sprite(int sprite_id); //��ȡһ��ҩƷ�ྫ�顣����sprite_idΪ����ʱ��̬�����Ψһ��ʾ��
	UI::Treasure_Box_Sprite*  get_treasure_box_sprite(int sprite_id); //��ȡһ�������ྫ�顣����sprite_idΪ����ʱ��̬�����Ψһ��ʾ��
	void create_trigger_sprite (int sprite_prototype_id,int &sprite_id, float born_point_x, float born_point_y);//����һ��ҩƷ�ྫ��. ����ʧ�ܣ�sprite_id = -1
	void create_treasure_box_sprite (int sprite_prototype_id,int &sprite_id, float born_point_x, float born_point_y);//����һ�������ྫ��. ����ʧ�ܣ�sprite_id = -1
	void do_trigger_sprite_event(int sprite_id);//��ӦҩƷ�ྫ���¼�
	void do_treasure_box_sprite_event(int sprite_id);//��Ӧ�����ྫ���¼�
	//-------------------
	//-------------------------
	// for ���е���
	void add_effect_to_actor_layer(const char *effect_id, float bass_x, float base_y, float base_z, int ZOrder, bool bflip);
	void add_projectile_to_actor_layer(int projectile_id,int &sprite_id, int owner_sprite_id, float born_point_x, float born_point_y, float born_point_z, bool bflip, int ZOrder);
	//-------------------
	//-------------------------
	// for ������ӳ�������Ч
	void play_continued_effect(int sprite_id, const std::string& effect_id, int &effect_tag);//������Ч������Ч��effect_tagΪ����Ч�ھ����е�Ψһ��ʶ����ʧ��ʱΪ -1��
	void remove_continued_effect(int sprite_id, int effect_tag);//�Ƴ�ĳ������Ч
	//-------------------

	// for ����������Ч
	void add_effect_to_scene(const std::string& effect_id);
    void add_effect_to_scene(const std::string& effect_id,const cocos2d::Point& pos);
	// for ��������ͼƬЧ��
	void add_image_to_scene(const std::string iamgepath,float time);
	//��ʱ��ʾ��������ʱ��dialog
	void instance_dialog_after_fight(int player_id,int instance_id,int instance_state);

	//-------------------

	// for ���٣�ѣ��
	bool srpite_get_is_stunning(int sprite_id); //��ȡ�����ѣ��״̬�����鲻����ʱ������true
	void srpite_set_is_stunning(int sprite_id, bool is_stunning);//���þ����ѣ��״̬
	void sprite_set_move_scale(int sprite_id, float move_scale);//���þ����ƶ��ٶȱ��ʡ������ٶ�Ϊ1.0f
	//-------------------

	// for ��ʱPK
	Real_Time_Operator* get_real_time_operator();//��ȡ��ʱPK�����߼�
	void start_Real_Time_PK();//��ʼ��ʱPK
	void Real_Time_PK_win();//Ӯ
	void Real_Time_PK_fail();//��
	void Real_Time_PK_reset_data();//������ʱPK���ָ�����

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

	//��Ļ��
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