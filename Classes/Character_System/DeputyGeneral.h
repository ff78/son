#pragma once

#include "cocos2d.h"
#include "Character.h"
#include "Item_System/Item_Data.h"
#include "Item_Container_System/Item_Container_Data.h"
#include "Network_Common/global_macros.h"

#define  MAX_DEPUTY_GENERAL_COUNT  6     // 副将最大个数

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class message_stream;
namespace Game_Data
{
	class Player;
	struct Player_Base_Attr_Config_Data;
	struct Player_Level_Attr_Config_Data;
	class DeputyGeneral : public Character,public cocos2d::Layer
	{
	public:
		DeputyGeneral(void);
		~DeputyGeneral(void);
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
		virtual int get_skill_level(int skillid);
		virtual int get_skill_quality(int skillid);
		virtual void set_skill_level(int skillid, int level);
		virtual int get_character_combo( void ){return m_nComboNum;}
		virtual void set_character_combo( int nComboNum );
		virtual float get_character_move_speed_rate();
		virtual int get_power();
        virtual int get_used_power();
        virtual int get_fighting_capacity();
		virtual void update(float delta);
		virtual void set_character_quality(int quality){this->m_character_quality=quality;}
		virtual int get_character_quality(){return this->m_character_quality;}
		virtual void character_quality_up();
        virtual int get_face_mode_id();
        virtual int get_model();
		virtual const char* get_character_name();
		void    set_character_name(const char* name);
		void    update_gangqi(float delta);
    public:
        int get_player_levelup_exp();

        void set_sex(int sex){m_sex = sex;} 
        void set_exp(int exp){m_exp = exp;}

        int get_sex(){return m_sex;}
        int get_exp(){return m_exp;}

        void set_x(int x){m_coord_x = x;}
        void set_y(int y){m_coord_y = y;}
        int get_x(){return m_coord_x;}
        int get_y(){return m_coord_y;}

        void update_level_date();
        void change_exp(int change);


		void set_owner(Player* player);
		Player* get_owner();
        int get_owner_id();

        void set_bar_item(Item* item);
        void clear_bar_item(int item_type,int pos);

        int get_empty_book_bar();
        Item* get_item_from_equipment_bar(int pos);
        Item* get_item_from_book_bar(int pos);
        Item** get_equipment_array(){return m_array_equipment_bar;}
        Item** get_book_array(){return m_array_book_bar;}

        void get_general_addition_attr(int attr_type,int& op_val);

    private:
        void get_equipment_attr(int attr_type,int& op_val);
        void get_book_attr(int attr_type,int& op_val);
        void get_acupoint_attr(int attr_type,int& op_val);

	private: 
		Player_Base_Attr_Config_Data*       m_base_attr_p_;
		Player_Level_Attr_Config_Data*      m_level_attr_p_;
		int                                 m_nComboNum;
		float                               m_ComboCountDownTime;

        int                                 m_sex;
        int                                 m_exp;
		char								m_name[MAX_NAME_LEN+1];

		Player*								m_owner;

        Item*                               m_array_equipment_bar[EP_MAX];  // 主角装备栏
        Item*                               m_array_book_bar[BP_MAX];       // 主角心法书籍栏
	};

    typedef map<int, DeputyGeneral*>        Deputy_General_Map;
    typedef Deputy_General_Map::iterator	Deputy_General_Map_Iter;
}