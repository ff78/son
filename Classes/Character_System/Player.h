#pragma once


#include "Character.h"
//#include "Fight_System/Offline_Fight_Record.h"
#include "Item_System/Item_Data.h"
#include "Shop_System/Shoping_Record_Data.h"
#include "Acupoint_System/Acupoint_Data.h"
#include "Cool_Time_System/Cool_Time_Data.h"
#include "Item_Container_System/Item_Container_Data.h"
//#include "DeputyGeneral.h"
#include "Relation_System/Relation_Common.h"
#include "Network_Common/global_macros.h"

class message_stream;
namespace Game_Data
{
    enum Role_Sex
    {
        RS_FEMALE = 0,
        RS_MALE,
    };

	struct Player_Base_Attr_Config_Data;
	struct Player_Level_Attr_Config_Data;
	class Player : public Character
	{
	public:
		Player(void);
		~Player(void);
	public:
		virtual void init_attr_data(int static_id, int level);
		void set_base_attr_config_data(Player_Base_Attr_Config_Data* base_attr);
        Player_Base_Attr_Config_Data* get_base_attr_config_data(){return  m_base_attr_p_;};
		void set_level_attr_config_data(Player_Level_Attr_Config_Data* level_attr);
	public:
		virtual int get_character_max_hp( void );
		virtual int get_character_max_mp( void );
		virtual int get_character_max_gp( void );
		virtual int get_character_hp_recover_speed( void );
		virtual int get_character_gp_reduce_hurt( void );
		virtual int get_character_gp_behit_time( void );
		virtual int get_character_gp_recover_speed( void );
		virtual int get_character_attack( void );
		virtual int get_character_define( void );
		virtual int get_character_hit_ratio( void );
		virtual int get_character_avoidance( void );
		virtual int get_character_crit_rate( void );
		virtual int get_character_tenacity( void );
		virtual int get_character_crit( void );
		virtual int get_character_invincible( void );
		virtual float get_character_move_speed_rate();
		virtual int get_skill_level(int skillid);
		virtual int get_skill_quality(int skillid);
		virtual void set_skill_level(int skillid, int level);
		virtual int get_character_combo( void ){return m_nComboNum;}
		virtual void set_character_combo( int nComboNum );
		virtual int get_power();
//        virtual int get_used_power();
        virtual int get_fighting_capacity();
		virtual void set_character_quality(int quality){this->m_character_quality=quality;}
		virtual int get_character_quality(){return this->m_character_quality;}
		virtual void character_quality_up();
        virtual int get_face_mode_id();
        virtual int get_model();
		virtual void update(float delta);
		virtual const char* get_character_name();
		void    set_character_name(const char* name);
		void    update_gangqi(float delta);

    public:
		/***************************** dely ******************************/
		int									m_nTitle;
		void set_title(int nTitle){ m_nTitle = nTitle; };
		int get_title(){ return m_nTitle; };

		std::string								_titleName;
		void set_title_name(std::string name){ _titleName = name; };
		std::string get_title_name(){ return _titleName; };

		std::string                         m_chat_send;
		void set_chat_send(std::string& send){ m_chat_send = send; }
		std::string get_chat_send(){ return m_chat_send; }

		std::string                         m_chat_received;
		void set_chat_received(std::string& rece){ m_chat_received = rece; }
		std::string get_chat_received(){ return m_chat_received; }

		int m_nChannel;
		void set_channel(int nChannel){ m_nChannel = nChannel; }
		int get_channel(){ return m_nChannel; }

		void clear_chat(){ m_chat_send.clear(); m_chat_received.clear(); }
		/***************************** dely ******************************/
        int get_player_levelup_exp();

        void set_logout_time(int time){m_logout_time = time;}

        void set_energy(int energy){m_energy = energy;}
        void set_buy_energy_count(int count){m_buy_energy_count = count;}
        void set_prestige(int prestige){m_prestige = prestige;}
        void set_offline_fight_count(int count){m_offline_fight_count = count;}
        void set_buy_offline_fight_count(int count){m_buy_offline_fight_count = count;}
        void set_offline_fight_rank_reward_count(int count){m_offline_fight_rank_reward_count = count;}
		void set_banks_exchange_count(int count){m_banks_exchange_count = count;}

        void set_sex(int sex){m_sex = sex;} 
        void set_present_token(int present_token){m_present_token = present_token;}
		void set_recharge_token(int recharge_token){m_recharge_token = recharge_token;}
        void set_gold(int gold){m_gold = gold;}
        void set_exp(int exp){m_exp = exp;}
        void set_guide_id(int id){m_guide_id = id;}
        void set_function_open_id(int id){m_function_open_id = id;}
		void set_main_city_scene_id(int _id){ m_main_city_scene_id = _id; }
	
		void set_camp_tag(int _tag){ m_camp_tag = _tag; }
		void set_job(int _job){ m_job = _job; }

		int get_logout_time(){return m_logout_time;}
		int get_login_time(){return m_login_time;}
		int get_login_level(){return m_login_level;}

        int get_energy(){return m_energy;}
        int get_buy_energy_count(){return m_buy_energy_count;}
        int get_prestige(){return m_prestige;}
        int get_offline_fight_count(){return m_offline_fight_count;}
        int get_buy_offline_fight_count(){return m_buy_offline_fight_count;}
        int get_offline_fight_rank_reward_count(){return m_offline_fight_rank_reward_count;}
		int get_banks_exchange_count(){return m_banks_exchange_count;}

        int get_sex(){return m_sex;}
        int get_token();
        int get_present_token(){return m_present_token;}
		int get_recharge_token(){return m_recharge_token;} 
        int get_gold(){return m_gold;}
        int get_exp(){return m_exp;}
        int get_guide_id(){return m_guide_id;}
        int get_function_open_id(){return m_function_open_id;}

        int get_buy_energy_cost();
        int get_buy_offline_fight_count_cost();

		int get_main_city_scene_id(){ return m_main_city_scene_id; }
		int get_camp_tag(){ return m_camp_tag; }
		int get_job(){ return m_job; }

        void set_x(int x){m_coord_x = x;}
        void set_y(int y){m_coord_y = y;}
        int get_x(){return m_coord_x;}
        int get_y(){return m_coord_y;}
        int get_scene_id( void ){return m_scene_id; }
        void set_scene_id( int id ) { m_scene_id = id; } 

        bool is_fighting_capacity_changed();
		bool is_fighting_capacity_getting_big();
        bool is_havegold_changed();

        void update_level_date();

        void change_token(int change);
		void add_recharge_token(uint add);
        void change_energy(int change);
        void change_prestige(int change);
        void change_gold(int change);
        void change_exp(int change);
        void change_guide_id(int id);
        void add_function_open_id();

        void insert_item(Item* item);
        void remove_item(int id);
        
        void insert_material_fragment(Item* item);
        void remove_material_fragment(int base_id);

        void insert_book_fragment(Item* item);

        void insert_shoping_record(shoping_record* record);
        void remove_shoping_record(int goods_id);
        
        void insert_acupoint(Acupoint* acupoint);
        void remove_acupoint(int type);
        
        void insert_cool_time(Cool_Time* cool_time);
        void remove_cool_time(int type);

        int insert_item_container(Item_Container* container);
        int remove_item_container(int id);

//		int insert_deputy_general(DeputyGeneral* deputy_general);
//		int remove_deputy_general(int id);
		
		//int insert_relation(Relation_Data* relation);
		//int remove_relation(int friend_role_id);

        //void load_offline_fight_record(Offline_Fight_Record* record);
        //void insert_offline_fight_record(Offline_Fight_Record* record);
        
        Item_Container_Map& get_bag_item_container_map(){return m_map_bag_item;}
        Item_Container_Map& get_store_item_container_map(){return m_map_store_item;}

        Item_Container* get_bag_can_pile_item_container(Item_Config* config_data);
        Item_Container* get_empty_bag_container();
        Item_Container* get_container_from_bag(int index);
        void load_item_container(Item_Container* container);
        int get_bag_item_container_count(){return m_map_bag_item.size();};
        
        void set_bar_item(Item* item);
        void clear_bar_item(int item_type,int pos);
        int get_empty_book_bar();
        Item** get_equipment_array(){return m_array_equipment_bar;}
        Item** get_book_array(){return m_array_book_bar;}
        Item* get_item_from_equipment_bar(int pos);
        Item* get_item_from_book_bar(int pos);

        Item_Map& get_item_map(){return m_map_item;}
        Item_Map& get_material_fragment_map(){return m_map_material_fragment;}
        Item_Map& get_book_fragment_map(){return m_map_book_fragment;}
        shoping_record_map& get_shoping_record_map(){return m_map_shoping_record;}
        Acupoint_Map& get_acupoint_map(){return m_map_acupoint;} 
        Cool_Time_Map& get_cool_time_map(){return m_map_cool_time;}
        Item_Container_Map& get_player_item_container_map(){return m_map_item_container;}
//		Deputy_General_Map& get_deputy_general() {return m_map_deputy_general;}

        Item* get_item(uint64 item_id);
        Item* get_material_fragment(int item_base_id);
        Item* get_book_fragment(int item_base_id);
        shoping_record* get_shoping_record(int goods_id);
        Acupoint* get_acupoint(int type); 
        Cool_Time* get_cool_time(int type);
        //Relation_Data* get_relation(int friend_role_id);
        Item_Container* get_item_container(uint64 container_id);
//		DeputyGeneral* get_deputy_general(int deputy_general_id);
//		DeputyGeneral* get_deputy_general_by_index(int index);

        bool fill_item_message_stream(message_stream& ms);
        bool fill_material_fragment_message_stream(message_stream& ms);
        bool fill_book_fragment_message_stream(message_stream& ms);
        bool fill_shoping_record_message_stream(message_stream& ms);
        bool fill_acupoint_message_stream(message_stream& ms); 
        bool fill_cool_time_message_stream(message_stream& ms);
        bool fill_item_container_message_stream(message_stream& ms);
//		bool fill_deputy_general_message_stream(message_stream& ms);
        bool fill_offline_fight_record_message_stream(message_stream& ms);

		void db_save(int player_id);  
		void save_role_attr(int player_id);
		void save_role_info(int player_id);

        void save_login(int player_id);
        void save_logout(int player_id);
        void save_energy(int player_id);
        void save_daily_refresh_data(int player_id);

		void release_item();
        void release_material_fragment();
        void release_book_fragment();
        void release_shoping_record();
        void release_acupoint();
        void release_cool_time();
        void release_item_container();
//		void release_deputy_general();
        void release_offline_fight_record();
		void release_relation();

        int get_material_fragment_type_count(){return m_map_material_fragment.size();}
        int get_book_fragment_type_count(){return m_map_book_fragment.size();}
        int get_item_container_count(){return m_map_item_container.size();}
//		int get_deputy_general_count() {return m_map_deputy_general.size();}
		//int get_relation_count(){return m_map_relation.size();}
        //int get_offline_fight_record_count(){return m_list_offline_fight_record.size();}

        void login_refresh_data(int player_id);
        void login_update_energy(int player_id);

//		int get_fight_general_id();
//        DeputyGeneral* get_fight_general();
//		void set_fight_general_id(int fight_general_id);
//
//        void load_deputy_general_skill();
//        int get_deputy_general_skill_count();

        int get_bag_same_item_count(int item_base_id);

        int get_bag_empty_count();

        bool player_all_equipment_reach_quality(int quality);
        bool player_equip_book_count(int& count, int quality);
        bool player_have_skill(int& count,int level);
        bool player_have_general(int& count,int quality);

        void set_last_tidy_item_time(int time){m_last_tidy_item_time = time;}
        int get_last_tidy_item_time(){return m_last_tidy_item_time;}

		void set_pk_player_id(int pk_player_id){m_pk_player_id = pk_player_id;}
		int get_pk_player_id(){return m_pk_player_id;}

        void get_player_addition_attr(int attr_type,int& op_val);

        void refresh_shop_record();

    private:
        void get_equipment_attr(int attr_type,int& op_val);
        void get_book_attr(int attr_type,int& op_val);
        void get_acupoint_attr(int attr_type,int& op_val);

	private: 
		Player_Base_Attr_Config_Data*       m_base_attr_p_;
		Player_Level_Attr_Config_Data*      m_level_attr_p_;

		int                                 m_nComboNum;
		float                               m_ComboCountDownTime;

        int                                 m_login_time;                       // role login time
        int                                 m_logout_time;                      // role logout time

		int                                 m_login_level;                      // role login level							

        int                                 m_energy;
        int                                 m_buy_energy_count;

        int                                 m_prestige;
        int                                 m_offline_fight_count;
        int                                 m_buy_offline_fight_count;
        int                                 m_offline_fight_rank_reward_count;

		int									m_banks_exchange_count;			// 元宝兑换银两 计数

        int                                 m_sex;
        int                                 m_present_token;                // 游戏内赠送的元宝
		int                                 m_recharge_token;				// 充值元宝
        int                                 m_gold;
        int                                 m_exp;
		char								m_name[MAX_NAME_LEN+1];

        Item_Container_Map                  m_map_bag_item;                 // 背包
        Item_Container_Map                  m_map_store_item;               // 仓库
        Item*                               m_array_equipment_bar[EP_MAX];  // 主角装备栏
        Item*                               m_array_book_bar[BP_MAX];       // 主角心法书籍栏

        Item_Map                            m_map_item;
        Item_Map                            m_map_material_fragment;
        Item_Map                            m_map_book_fragment;
        shoping_record_map                  m_map_shoping_record;
        Acupoint_Map                        m_map_acupoint;
        Cool_Time_Map                       m_map_cool_time;
        Item_Container_Map                  m_map_item_container;
//		Deputy_General_Map                  m_map_deputy_general;
       // Offline_Fight_Record_List           m_list_offline_fight_record;

		int								    m_fight_general_id;    // 出战的副将Id
        int                                 m_guide_id;
        int                                 m_function_open_id;
        int                                 m_last_tidy_item_time;
		int                                 m_pk_player_id;

        int                                 m_last_role_fighting_capacity;
        int                                 m_last_role_have_gold;

		int									m_main_city_scene_id;		// 主城场景ID
		int									m_camp_tag;					// 阵营标记

	};

    typedef map<int, Player*>               Player_Map;
    typedef Player_Map::iterator		    Player_Map_Iter;
}