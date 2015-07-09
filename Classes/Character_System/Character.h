#pragma once

#include <string>
#include <vector>
#include <map>

#ifdef GAME_CLIENT
//#include "AI_System/Game_Utils.h"
#endif
#include "Game_Interface/common.h"
//#include "Skill_System/Buff/Buff_Logic.h"
//#include "Skill_System/Skill/Skill_Common.h"

namespace Game_Data
{
    class  Player;
    struct Game_Element;
    struct Master_Skill_List;
    struct Item;
    struct Player_Base_Attr_Config_Data;
    enum Character_Attribute
    {
        CA_ID,         //
        CA_LEVEL,      //
        CA_CUR_HP,
        CA_CUR_MP,
        CA_CUR_GP,
        CA_MAX_HP,
        CA_MAX_MP,
        CA_MAX_GP,
        CA_HP_RECOVER_SPEED,
        CA_GP_REDUCE_HURT,
        CA_BEHIT_TIME,
        CA_GP_RECOVER_SPEED,
        CA_ATTACK,
        CA_DEFINE,
        CA_HIT_RATIO,
        CA_AVOIDANCE,
        CA_CRIT_RATE,
        CA_TENACITY,
        CA_CRIT,
        CA_INVINCIBLE,
		CA_MOVE_SPEED_RATE,
		CA_CANNOT_MOVE,
        CB_MAX_COUNT
    };

    struct Character_Skill
    {
        uint64 database_id;         //  ˝æ›ø‚ID
        int skill_id;               // ººƒ‹ID
        //int skill_level;            // ººƒ‹µ»º∂
    };

	struct Player_Faction_Data
	{
		uint64 faction_id;		// π§ª·ID
		int _faction_job;		// π§ª·÷∞Œª(√ª”–π§ª·:0,≥…‘±:1,∏±∞Ô÷˜:2,∞Ô÷˜:3)
		char	_name[16 + 1];	// π§ª·√˚≥∆
		int contribute_num;			// π±œ◊∂»
		int curr_digging_num;		// µ±ÃÏÕ⁄øÛµƒ¥Œ ˝
		int curr_worship_num;		// µ±ÃÏƒ§∞›µƒ¥Œ ˝
		int curr_boss_num;			// µ±ÃÏÃÙ’ΩBOSS¥Œ ˝
	};

    class Character
    {
    public:
        Character(void);
        ~Character(void);
        void cleanup(void);
        virtual void init_attr_data(int /*static_id*/, int /*level*/) {}
    public:
        virtual int get_database_character_id( void ){return m_database_id;}
        virtual void set_database_character_id(int id){this->m_database_id = id;}
        virtual int get_static_character_id( void ){return m_static_id;}
        virtual void set_static_character_id(int id){this->m_static_id = id;}
        virtual int get_character_type( void ){return m_type;}
        virtual void set_character_type(int type){this->m_type = type;}
        virtual int get_character_level( void ){return m_level;}
        virtual void set_character_level(int level){this->m_level = level;}
        virtual int get_character_cur_hp( void ){return m_cur_hp;}
        virtual void set_character_cur_hp(int cur_hp);
        virtual int get_character_cur_mp( void ){return m_cur_mp;}
        virtual void set_character_cur_mp(int cur_mp){this->m_cur_mp = cur_mp;}
        virtual int get_character_cur_gp( void ){return m_cur_gp;}
        virtual void set_character_cur_gp(int cur_gp){this->m_cur_gp = cur_gp; if ( this->m_cur_gp < 0 ) this->m_cur_gp = 0;}
        virtual int get_character_max_hp( void ){return m_max_hp;}
		virtual void set_character_max_hp(int max_hp){ m_max_hp = max_hp;}
        virtual int get_character_max_mp( void ){return m_max_mp;}
		virtual void set_character_max_mp(int max_mp){ m_max_mp = max_mp;}
        virtual int get_character_max_gp( void ){return m_max_gp;}
		virtual void set_character_max_gp(int max_gp){ m_max_gp = max_gp;}
        virtual int get_character_hp_recover_speed( void ){return 0;}
        virtual int get_character_gp_reduce_hurt( void ){return 0;}
        virtual int get_character_gp_behit_time( void ){return 0;}
        virtual int get_character_gp_recover_speed( void ){return 0;}
        virtual int get_character_attack( void ){return m_attack;}
		virtual void set_character_attack(int attack){this->m_attack = attack;}
        virtual int get_character_define( void ){return m_define;}
		virtual void set_character_define(int define){this->m_define = define;}
        virtual int get_character_hit_ratio( void ){return m_hit_ratio;}
		virtual void set_character_hit_ratio(int hit_ratio){this->m_hit_ratio = hit_ratio;}
        virtual int get_character_avoidance( void ){return m_avoidance;}
		virtual void set_character_avoidance(int avoidance){this->m_avoidance = avoidance;}
        virtual int get_character_crit_rate( void ){return m_crit_rate;}
		virtual void set_character_crit_rate(int crit_rate){this->m_crit_rate = crit_rate;}
        virtual int get_character_tenacity( void ){return m_tenacity;}
		virtual void set_character_tenacity(int tenacity){this->m_tenacity = tenacity;}
        virtual int get_character_crit( void ){return m_crit;}
		virtual void set_character_crit(int crit){this->m_crit = crit;}
        virtual int get_buff_attr(int attr_index, int type);
        virtual int get_character_invincible( void ) {return 0;}
        virtual int get_power() {return 0;}
        virtual int get_used_power() {return 0;}
        virtual int get_player_levelup_exp() {return 0;}
        virtual int get_fighting_capacity() {return 0;}
		virtual float get_character_move_speed_rate() {return 0;}

		virtual void set_Ice_Resist(int _val){ m_Ice_Resist = _val; }
		virtual int get_Ice_Resist(){ return m_Ice_Resist; }
		virtual void set_Fire_Resist(int _val){ m_Fire_Resist = _val; }
		virtual int get_Fire_Resist(){ return m_Fire_Resist; }
		virtual void set_Thunder_Resist(int _val){ m_Thunder_Resist = _val; }
		virtual int get_Thunder_Resist(){ return m_Thunder_Resist; }
		virtual void set_Wind_Resist(int _val){ m_Wind_Resist = _val; }
		virtual int get_Wind_Resist(){ return m_Wind_Resist; }
		virtual void set_Light_Resist(int _val){ m_Light_Resist = _val; }
		virtual int get_Light_Resist(){ return m_Light_Resist; }
		virtual void set_Dark_Resist(int _val){ m_Dark_Resist = _val; }
		virtual int get_Dark_Resist(){ return m_Dark_Resist; }

//        virtual int have_this_buff(int buffid);
//        virtual Buff_Logic* get_buff_logic(int buffid);
//        virtual int insert_buff(Buff_Logic* buff_logic);
//        virtual int remove_buff(int buffid);
//        virtual int remove_all_buff();
//		virtual int remove_all_fight_buff();
//        virtual Buff_Logic* get_buff_logic_by_index(int index);
//        virtual int get_buff_size();
        //virtual int get_buff_replace_index(Buff_Data* buffInfoPtr);
        virtual void insert_skill_list(std::vector<Character_Skill> &skill_list);
        virtual void insert_skill(Character_Skill & skill);
        virtual int get_skill_level(int /*skillid*/) { return 0;}
        virtual int get_skill_quality(int /*skillid*/) { return 0;}
        virtual int get_skill_id_by_database_id(uint64 database_id);
        virtual uint64 get_skill_database_id_by_id(int skill_id);
        virtual int get_skill_level_by_database_id(uint64 database_id);
        virtual void set_skill_level(int skillid, int level);
        virtual vector<Character_Skill>& get_skill_vector(){return m_skill_vector;}
        virtual Character_Skill* get_skill_by_id(int skill_id);
        virtual Character_Skill* get_skill_by_index(int index);
        virtual int get_skill_size();
#if 1//yypp
		void update_job_skill(int _skill_id, int _skill_up_id);
#endif
        virtual void character_quality_up(){}
        virtual void set_character_quality(int quality){this->m_character_quality=quality;}
        virtual int get_character_quality(){return this->m_character_quality;}
#ifdef GAME_CLIENT
        /*virtual Charcter_AI_State get_ai_state() {return this->m_ai_state;}
        virtual void set_ai_state(Charcter_AI_State ai_state);
        virtual void clean_ai_state() {this->m_ai_state = MISS_STATE;}*/
#endif
        virtual int get_character_combo( void ){return 0;}
        virtual void set_character_combo( int /*nComboNum*/ ){}

        virtual int get_character_coord_x( void ){return m_coord_x;}
        virtual void set_character_coord_x( int coord_x){this->m_coord_x = coord_x;}

        virtual int get_character_coord_y( void ){return m_coord_y;}
        virtual void set_character_coord_y( int coord_y){this->m_coord_y = coord_y;}

        virtual int get_character_scene_id( void ){return m_scene_id;}
        virtual void set_character_scene_id( int scene_id){this->m_scene_id = scene_id;}

        virtual int get_character_no_hurt_time( void ){return m_no_hurt_time;}
        virtual void set_character_no_hurt_time( int no_hurt_time){this->m_no_hurt_time = no_hurt_time;}

        virtual int get_exp(){return 0;}
        virtual void update(float /*delta*/){}
        virtual void update_gangqi(float /*delta*/) {}

        virtual void set_owner(Player* /*player*/) {}

        virtual Player* get_owner() {return NULL;}

        virtual void set_bar_item(Item* /*item*/){}
        virtual void clear_bar_item(int /*item_type*/,int /*pos*/){}

        virtual int get_empty_book_bar(){return -1;}
        virtual Item* get_item_from_equipment_bar(int/* pos*/){return NULL;}
        virtual Item* get_item_from_book_bar(int/* pos*/){return NULL;}
        virtual Item** get_equipment_array(){return NULL;}
        virtual Item** get_book_array(){return NULL;}

        virtual Player_Base_Attr_Config_Data* get_base_attr_config_data(){return  NULL;}
        virtual int get_face_mode_id(){return  0;}
        virtual int get_model(){return  0;}
        virtual const char* get_character_name(){return NULL;}
        virtual void change_exp(int /*change*/){}
        virtual void set_dead(int dead);
        virtual int get_dead(){return m_dead;}

		virtual void set_job_skill_list(vector<int> _job_skill_list){ this->m_job_skill_list = _job_skill_list; }
		virtual bool delete_job_skill(int _skill_id);
		virtual bool insert_job_skill(int _skill_id);
#if 1//yypp
		int get_job_skill_by_index(int index);
		int get_skill_index_by_skill_id(int _skill_id);
#endif
		virtual vector<int>& get_job_skill_list(){ return m_job_skill_list; }
		virtual int get_job_skill_size(){ return m_job_skill_list.size(); }

		virtual void set_select_job_skill(vector<int> _job_skill_list){ this->m_select_job_skill_list = _job_skill_list; }
		virtual bool insert_select_skill(int _select_skill_id);
		virtual vector<int>& get_select_job_skill_list(){ return m_select_job_skill_list; }

		void set_job(int _job){ m_job = _job; }
		int get_job(){ return m_job; }

		inline int get_cur_god_id(){return m_cur_god_id;};
		inline void set_cur_god_id(int id){m_cur_god_id=id;};
		
		inline int get_cur_pet_id(){return m_cur_pet_id;};
		//inline void set_cur_pet_id(int id){m_cur_god_id=id;};

		void set_cur_pet_id(int id);
		void change_one_pet_of_list_by_id(int old_id,int new_id);
		void add_pet(uint64 database_id, int id);
		void reset_pet(uint64 database_id, int id);

#if 1//yypp
		int get_player_select_skill_by_index(int index);
		std::vector<int>& get_player_select_skills();
		void set_player_temp_select_skills(std::vector<int>&temp);
		void update_player_select_skills();
#endif

        int get_vip_lv(){ return m_vip_level = 0; }
        void set_vip_lv(int lv){ m_vip_level = lv; }
    protected:
        int				            m_database_id;                      //  ˝æ›ø‚ID
        int                         m_static_id;                        // æ≤Ã¨ ˝æ›ID
        int                         m_type;                             // ¿‡–Õ    EVENT_TYPE_PLAYERÕÊº“  EVENT_TYPE_MONSTERπ÷ŒÔ EVENT_TYPE_NPC(NPC)
        int                         m_level;                            // µ»º∂
        int                         m_cur_hp;                           // µ±«∞∆¯—™
        int                         m_cur_mp;						    // µ±«∞≈≠∆¯
        int                         m_cur_gp;						    // µ±«∞Ó∏∆¯
        int				    	    m_coord_x;                          // x◊¯±Í
        int				    	    m_coord_y;						    // y◊¯±Í
        int				    	    m_scene_id;						    // ≥°æ∞id
        int                         m_max_hp;                           // ∆¯—™…œœﬁ
        int                         m_max_mp;						    // ≈≠∆¯…œœﬁ
        int                         m_max_gp;						    // Ó∏∆¯…œœﬁ
        int                         m_hp_recover_speed;		            // ∆¯—™ªÿ∏¥ÀŸ∂»
        int                         m_gp_reduce_hurt;				    // Ó∏∆¯ºı…À¬ 
        int                         m_gp_behit_time;				    // Ó∏∆¯ ‹…À∫Ûª÷∏¥º‰∏Ù
        int                         m_gp_recover_speed;				    // Ó∏∆¯ª÷∏¥ÀŸ∂»
        int                         m_attack;						    // π•ª˜¡¶
        int                         m_define;						    // ∑¿”˘¡¶
        int                         m_hit_ratio;					    // √¸÷–÷µ
        int                         m_avoidance;					    // ªÿ±‹÷µ
        int                         m_crit_rate;					    // ±©ª˜÷µ
        int                         m_tenacity;						    // º·»Õ÷µ
        int                         m_crit;							    // ±©ª˜…À∫¶º”≥…
        int                         m_dead;                             // À¿Õˆ
        int				    	    m_invincible;					    // Œﬁµ–
        int				    	    m_no_hurt_time;					    // Œ¥ ‹µΩπ•ª˜µƒ ±º‰
        int				    	    m_character_quality;			    // »ÀŒÔµƒ∆∑÷ 
		int                         m_move_speed_rate;                  // “∆∂ØÀŸ¬   

		//   Ù–‘øπ–‘
		int							m_Ice_Resist;						// ±˘øπ
		int							m_Fire_Resist;						// ªøπ
		int							m_Thunder_Resist;					// ¿◊øπ
		int							m_Wind_Resist;						// ∑Áøπ
		int							m_Light_Resist;						// π‚øπ
		int							m_Dark_Resist;						// ∞µøπ

		int							m_job;								// ÷∞“µ

		/*
#ifdef GAME_CLIENT
        Charcter_AI_State        m_ai_state;						   // AI◊¥Ã¨
#endif*/
//        vector<Buff_Logic>       m_buff_vector;                        // buff¡–±Ì
        vector<Character_Skill>  m_skill_vector;                       // list¡–±Ì

		vector<int>				m_job_skill_list;						// ººƒ‹¡–±Ì(ÕÊº“µ±«∞—ßœ∞µƒ)
		vector<int>				m_select_job_skill_list;				// ÕÊº“—°‘Òµƒººƒ‹ID
#if 1//yypp
		vector<int>				m_temp_job_skill_list;
#endif
		map<uint64, int>		m_pet_list;
		int						m_cur_pet_id;

		int						m_cur_god_id;
        
        int	 m_vip_level;		// VIP等级
    };
}
