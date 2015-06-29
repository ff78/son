

#if !defined(EA_30A2F955_0E9E_4490_929D_7FAA9CFFD045__INCLUDED_)
#define EA_30A2F955_0E9E_4490_929D_7FAA9CFFD045__INCLUDED_

#include "Game_Interface/common.h"
#include "Game_Interface/game_element.h"
#include <queue>

#ifdef GAME_SERVER
#include <ace/ACE.h>
#include <ace/Time_Value.h>
#endif

enum Instance_Type
{
	IT_NORMAL = 1,
	IT_ELITE
};

enum Instance_State
{
	IS_GOING = 0,    // 进行中
	IS_COMPLETE,                // 完成
};

enum Prompt_Type
{
	PT_QUEST = 1,    // 任务
	PT_MATERIAL,                // 材料
};

struct Area_UI_Config
{
	int         area_id;
	int         name_id;
	std::string iconName;
	int         level_id;
	int         open_id;
	list<int>   list_instance_id;
};

struct Instance_UI_Config
{
	int         instance_id;
	int         area_id;
	int         type;
	int         x;
	int         y;
	int         score;
	int         open_id;
    std::string iconName;
};

typedef map<int, Area_UI_Config>                Map_Area_UI_Config;
typedef map<int, Area_UI_Config>                Map_Endless_Tower_Config;
typedef Map_Area_UI_Config::iterator            Map_Area_UI_Config_Iter;
typedef Map_Endless_Tower_Config::iterator      Map_Endless_Tower_Config_Iter;
typedef map<int, Instance_UI_Config>            Map_Instance_UI_Config;
typedef Map_Instance_UI_Config::iterator        Map_Instance_UI_Config_Iter;

struct instance_dialog
{
	instance_dialog() : instance_dialog_id_(0)
	{
		dialog_content_lst_.clear();
	}
	~instance_dialog() {}

	void reset()
	{
		instance_dialog_id_ = 0;
		dialog_content_lst_.clear();
	}

	void set_instance_dialog_id(int id) { instance_dialog_id_ = id; }
	int get_instance_dialog_id(void) { return instance_dialog_id_; }

	void reset_command_element_list(void) { dialog_content_lst_.clear(); }
	void add_command_element_list(std::list<Game_Data::Game_Command_Element>& gce_lst) { dialog_content_lst_ = gce_lst; }
	void get_command_element_list(std::list< Game_Data::Game_Command_Element>& gce_list)
	{
		gce_list = dialog_content_lst_;
	}

private:
	int instance_dialog_id_;
	std::list< Game_Data::Game_Command_Element> dialog_content_lst_;
};

struct current_instance_data
{
	enum INSTANCE_STATE {
		INSTANCT_STATE_PROC = 1,
		INSTANCE_STATE_FAILE,
		INSTANCE_STATE_SUC,
		INSTANCE_SAVED,
		INSTANCE_FIRST,
		INSTANCE_STATE_FAILE_OVER_TIME,
		INSTANCE_STATE_SUC_KEEP_ALIVE,
		INSTANCE_TYPE_ELITE
	};
	current_instance_data() :player_id_(0),
		instance_id_(0),
		monster_wave_(0),
		monster_wave_require_(0),
		current_scene_(0),
		instance_current_time_limit_(0),
		instance_score_(0),
		instance_state_(0),
		current_lock_scene_id_(0),
		total_monster_kill_(0),
		total_hurt_data_(0),
		total_combo_hit_(0),
		total_player_die_(0),
#ifdef GAME_SERVER
		instance_check_time_(0),
#endif
		time_grad_(0),
		saved_instance_(0),
		elite_instance_(0)

	{
		monster_counter_lst_.clear();
		monster_wave_id_lst_.clear();
		scene_config_list_.clear();
		item_award_list_.clear();
	}
	~current_instance_data() {}

	void reset(void)
	{
		player_id_ = 0;
		instance_id_ = 0;
		monster_wave_ = 0;
		monster_wave_require_ = 0;
		current_scene_ = 0;
		instance_current_time_limit_ = 0;
		instance_score_ = 0;
		instance_state_ = 0;
		monster_counter_lst_.clear();
		monster_wave_id_lst_.clear();
		item_award_list_.clear();
		scene_config_list_.clear();
		saved_instance_ = 0;
#ifdef GAME_SERVER
		instance_check_time_ = 0;

#endif
		current_lock_scene_id_ = 0;
		total_monster_kill_ = 0;
		total_hurt_data_ = 0;
		total_combo_hit_ = 0;
		time_grad_ = 0;
		total_player_die_ = 0;
		elite_instance_ = 0;
	}

	bool operator==(const current_instance_data& cid)const
	{
		return (cid.get_instance_id() == instance_id_);
	}


	void set_player_id(int id) { player_id_ = id; }
	int get_player_id(void) { return player_id_; }

	void set_instance_id(int id) { instance_id_ = id; }
	int get_instance_id(void) const { return instance_id_; }

	void clear_monster_counter_lst()
	{
		monster_counter_lst_.clear();
	}
	int instert_monster_counter_lst(Game_Data::Game_Element& ge)
	{
		vector< Game_Data::Game_Element>::iterator itg;
		itg = find_if(monster_counter_lst_.begin(), monster_counter_lst_.end(), bind2nd(equal_to<Game_Data::Game_Element>(), ge));
		if (itg != monster_counter_lst_.end())
			return -1;

		monster_counter_lst_.push_back(ge);
		return 0;
	}
	int clear_monster_counter(void)
	{
		monster_counter_lst_.clear();
		return 0;
	}
	int add_monster_counter(int monster_id)
	{
		vector< Game_Data::Game_Element>::iterator itg;
		for (itg = monster_counter_lst_.begin(); itg != monster_counter_lst_.end(); ++itg)
		{
			if (monster_id == (*itg).get_cell_id())
			{
				if ((*itg).get_count() < (*itg).get_count_require())
				{
					(*itg).count_add();
					return (*itg).get_count() < (*itg).get_count_require() ? -1 : 0;
				}
				else
					return 0;

			}
		}

		return -1;
	}
	int get_monster_lst(vector< Game_Data::Game_Element>& lst)
	{
		lst = monster_counter_lst_;
		return 0;
	}

	int is_couter_full(void)
	{
		if (0 == monster_counter_lst_.size())
		{
			return -1;
		}
		vector< Game_Data::Game_Element>::iterator itg;
		int rst = 0;
		for (itg = monster_counter_lst_.begin(); itg != monster_counter_lst_.end(); ++itg)
		{
			if ((*itg).get_count() < (*itg).get_count_require())
			{
				rst = -1;
				break;
			}
		}
		return rst;
	}
	void add_monster_wave(void) { monster_wave_++; }
	int get_monster_wave(void) { return monster_wave_; }

	void set_monster_wave_require(int req) { monster_wave_require_ = req; }
	int get_monster_wave_require(void) { return monster_wave_require_; }

	void set_instance_score(int score)  { instance_score_ = score; }
	int get_instance_score(void) { return instance_score_; }

	void set_instance_state(int state) { instance_state_ = state; }
	int get_instance_state(void) { return instance_state_; }

	void clear_monster_wave_id_list(void) { monster_wave_id_lst_.clear(); }
	void add_monster_wave_id(int id) { monster_wave_id_lst_.push_back(id); }
	void set_monster_wave_id_list(vector<int>& lst) { monster_wave_id_lst_ = lst; }
	void get_monster_wave_id_list(vector<int>& lst) { lst = monster_wave_id_lst_; }
	void set_scene_config(int scene_id, int monster_wave_count) { scene_config_list_.insert(make_pair(scene_id, monster_wave_count)); }
	int get_scene_config(int scene_id)
	{
		map<int, int>::iterator iti;
		iti = scene_config_list_.find(scene_id);
		return iti != scene_config_list_.end() ? iti->second : -1;
	}
	void get_scene_config_list(map<int, int>& scene_list) { scene_list = scene_config_list_; }
	void set_current_scene(int scene)
	{
		current_scene_ = scene;
	}

	int get_current_scene(void) { return current_scene_; }

	void set_current_lock_scene_id(int id) { current_lock_scene_id_ = id; }
	int get_current_lock_scene_id(void) { return current_lock_scene_id_; }

	void set_instance_current_time_limit(int time) { instance_current_time_limit_ = time; }
	int get_instance_current_time_limit(void) { return instance_current_time_limit_; }

	void set_saved_instance(int state) { saved_instance_ = state; }
	int get_saved_instance(void) { return saved_instance_; }


	void set_elite_instance(int state) { elite_instance_ = state; }
	int get_elite_instance(void) { return elite_instance_; }
	/************************************* dely ************************************/
	int get_item_award_size(){ return item_award_id_que.size(); };
	void set_item_award_id_que(uint64 item_id){ item_award_id_que.push_back(item_id); };
	uint64 get_item_award_id_que()
	{
		if (item_award_id_que.size() > 0)
		{
			uint64 ret = item_award_id_que.front();
			item_award_id_que.pop_front();
			return ret;
		}
		else
			return 0;
	}

	void set_item_award_count_que(int item_count){ item_award_count_que.push_back(item_count); };
	int get_item_award_count_que(int item_id)
	{
		int ret = item_award_count_que.front();
		return ret;
	}
	/************************************* dely ************************************/
	void set_item_award_list(int item_id, int item_count) { item_award_list_.insert(make_pair(item_id, item_count)); }
	int get_item_award_list(int item_id)
	{
		map<int, int>::iterator iti;
		iti = item_award_list_.find(item_id);
		return iti != item_award_list_.end() ? iti->second : -1;
	}
	void get_item_award_list(map<int, int>& item_list) { item_list = item_award_list_; }

	void add_total_monster_kill(void)  { total_monster_kill_++; }
	int get_total_monster_kill(void) { return total_monster_kill_; }

	void add_total_hurt_data(int value)  { total_hurt_data_ += value; }
	int get_total_hurt_data(void) { return total_hurt_data_; }

	void add_total_combo_hit(void)  { total_combo_hit_++; }
	int get_total_combo_hit(void) { return total_combo_hit_; }

	void add_total_player_die(void)  { total_player_die_++; }
	void set_total_player_die(int count)  { total_player_die_ = count; }
	int get_total_player_die(void) { return total_player_die_; }

	void set_time_grad(int grad) { time_grad_ = grad; }
	int get_time_grad(void) { return time_grad_; }

#ifdef GAME_SERVER
	void set_instace_check_time(ACE_Time_Value& now) { instance_check_time_ = now; }
	ACE_Time_Value& get_instace_check_time(void) { return instance_check_time_; }
	int do_time_check(ACE_Time_Value& now)
	{
		if ((now - instance_check_time_).sec() > instance_current_time_limit_)
		{
			return 0;
		}

		return -1;
	}
#endif

private:
	int player_id_;
	int instance_id_;
	int monster_wave_;
	int monster_wave_require_;
	int current_scene_;
	int instance_current_time_limit_;
	int instance_score_;
	int instance_state_;
	int current_lock_scene_id_;
	int total_monster_kill_;
	int total_hurt_data_;
	int total_combo_hit_;
	int total_player_die_;
#ifdef GAME_SERVER
	ACE_Time_Value instance_check_time_;
#endif
	int time_grad_;
	vector< Game_Data::Game_Element> monster_counter_lst_;
	vector< int > monster_wave_id_lst_;
	map<int, int> scene_config_list_;
	map<int, int> item_award_list_;
	int saved_instance_;
	int elite_instance_;
	/************************************* dely ************************************/
	deque<uint64> item_award_id_que;
	deque<int> item_award_count_que;
	/************************************* dely ************************************/

};

class Instance_Data_Mgr
{

public:
	Instance_Data_Mgr();
	virtual ~Instance_Data_Mgr();

	static Instance_Data_Mgr* instance();

	int initialize(void);
	void release(void);

	Map_Area_UI_Config &get_area_ui_config_map(){ return m_map_area_ui_config; }
	Area_UI_Config* get_area_ui_config(int area_id);
	Area_UI_Config* get_endless_tower_config(int area_id);
	Instance_UI_Config* get_instance_ui_config(int instance_id);

	int analysis_stage_instance_data(int player_id);

	void set_current_instance_id(int id) { current_instance_id_ = id; }
	int get_current_instance_id(void)  { return current_instance_id_; }

	void set_current_prompt_instance_id(int type, int id, int instance_type = 0) { current_prompt_type_ = type; current_prompt_instance_id_ = id; current_instance_type_ = instance_type; }
	int get_current_prompt_instance_id(void)  { return current_prompt_instance_id_; }
	int get_current_prompt_type(void)  { return current_prompt_type_; }
	int get_current_instance_type(void)  { return current_instance_type_; }

	int add_player_instance(int player_id, current_instance_data& cid);
	int add_player_instance(int player_id, int instance_id, int scene_id, int monster_wave);
	int modi_player_instance(int player_id, current_instance_data& cid);
	int get_player_instance(int player_id, current_instance_data& cid);
	int remove_player_instance_data(int player_id);

	int add_player_instance_lst(int player_id, current_instance_data& cid);
	int remove_player_instance_list(int player_id);
	int remove_player_instance_from_list(int player_id, int instance_id);
	int modi_player_instance_list(int player_id, current_instance_data& cid);
	int get_player_instance_from_list(int player_id, current_instance_data& cid);

	int get_current_instance_stage_id(void) { return current_insance_stage_id_; }
	void set_current_instance_stage_id(int id) { current_insance_stage_id_ = id; }
#if 1//MISSION_DIALOG
	int get_player_instance_from_list2(int player_id, current_instance_data& cid);
	int get_quest_instance_state(int player_id, int instance_id);
#endif
	int add_stage_data(int stage, int pass);
	int clear_stage_data(void);
	int get_stage_data(map<int, int>& stage_lst);

	void set_instance_state(int state){ instance_state_ = state; }
	int get_instance_state(){ return instance_state_; }

	int get_instance_dialog_data_by_id(int id, instance_dialog& id_data);

	int clear_current_dialog(void);
	int push_current_dialog(Game_Data::Game_Element& ge);
	int pop_current_dialog(Game_Data::Game_Element& ge);
	int is_current_dialog_empty(void);


	bool RequestChallengeNextInstance();															// 请求挑战下一个关卡
	bool JudgeInstanceBelongTargetState(const int nInstanceID, const int nStateID);					// 判断当前关卡是否属于目标章节		

	void SendMsgRequestInstanceNext(const int nCurrentInstanceID);									// 发送消息请求挑战下一关

private:
	static Instance_Data_Mgr* instance_;

	int load_area_ui_config_data();
	int load_instance_ui_config_data();
	int load_instance_dialog_config_data();

	int instance_state_;
	int current_instance_id_;
	int current_insance_stage_id_;
	int current_prompt_instance_id_;
	int current_prompt_type_;
	int current_instance_type_;

	Map_Area_UI_Config                      m_map_area_ui_config;
	Map_Instance_UI_Config                  m_map_instance_ui_config;

	map< int, current_instance_data >       current_player_instance_data_;
	map< int, list < current_instance_data > > player_instance_list_;
	map< int, Map_Instance_UI_Config >      current_player_stage_instance_data_;
	map< int, int > current_stage_state_lst_;
	map< int, instance_dialog > instance_dialog_data_;
	std::queue< Game_Data::Game_Element > current_instance_dialog_list_;

#ifdef YN_LINUX		
	pthread_mutex_t                     instance_mutex_;
#endif
};

typedef Instance_Data_Mgr INSTANCE_DATA_MGR;
#endif // !defined(EA_30A2F955_0E9E_4490_929D_7FAA9CFFD045__INCLUDED_)
