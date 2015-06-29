

#ifndef __PLAYER_DATA_H__
#define __PLAYER_DATA_H__

#include <string>
#include <list>
#include "Network_Common/global_macros.h"
 
#define  PLAYER_MAX_ENERGY              120         // ����������
#define  PLAYER_BUY_ENERGY_MAX_COUNT    20          // ��ҹ�������������
#define  PLAYER_BUY_ENERGY_VALUE        20          // ��ҹ���һ������������
#define  PLAYER_REVIVE_COST             50          // ��Ҹ���Ԫ������
#define  PLAYER_UP_LEVEL_RECOVER_ENERGY 30          // ��������ָ�����


enum CHAT_CHANNEL_TYPE
{
	CHAT_CHANNEL_ALL = 0,
	CHAT_CHANNEL_WORLD,
	CHAT_CHANNEL_MENPAI,
	CHAT_CHANNEL_TEAM,
	CHAT_CHANNEL_FRIEND,
	CHAT_CHANNEL_PRIVATE,
	CHAT_CHANNEL_SYSTEM,
};

namespace Game_Data
{
    struct Game_Element;
    
    struct Player_Base_Attr_Config_Data
    {
    public:
        Player_Base_Attr_Config_Data(){ reset();}
        virtual ~Player_Base_Attr_Config_Data(){}

        int reset( void )
        {
			id						= 0;   
			level_id				= 0;
            name				    = 0;
			prefession.clear();                        
			title.clear();                             
			quality					= 0;
            addition			    = 0;
			model					= 0;                             
			scale_rate				= 0;                        
			face_mode_id			= 0;		                
			sex					    = 0;                              
			binding_grain_effect_id = 0;           
			move_speed              = 0;                        
			behit_effect            = 0;						
			behit_sound             = 0;
			max_level               = 0;
			king_skill_id			= 0;

			for (int i = 0; i < MAX_SKILL_COUNT; i++)
			{
				skill_id[i] = 0;
			}

            return 0;
        }
    public:
        int get_player_id( void ) {return id ;}
        void set_player_id(int id){this->id = id;}

		int get_player_level_id( void ){return level_id;}
		void set_player_level_id(int levelid){this->level_id = levelid;}

        int get_player_name( void ){return name;}
        void set_player_name(int name){this->name = name;}

		std::string get_player_prefession( void ){return prefession;}
        void set_player_prefession(std::string prefession){this->prefession = prefession;}

        std::string get_player_title( void ){return title;}
        void set_player_title(std::string title){this->title = title;}

        int get_player_quality( void ){return quality;}
        void set_player_quality(int quality){this->quality = quality;}

        int get_player_addition( void ){return addition;}
        void set_player_addition(int addition){this->addition = addition;}
        
        int get_player_model( void ){return model;}
        void set_player_model(int model){this->model = model;}

        int get_player_scale_rate( void ){return scale_rate;}
        void set_player_scale_rate(int scale_rate){this->scale_rate = scale_rate;}

        int get_player_face_mode_id( void ){return face_mode_id;}
        void set_player_face_mode_id(int face_mode_id){this->face_mode_id = face_mode_id;}

        int get_player_sex( void ){return sex;}
        void set_player_sex(int sex){this->sex = sex;}

        int get_player_binding_grain_effect_id( void ){return binding_grain_effect_id;}
        void set_player_binding_grain_effect_id(int binding_grain_effect_id){this->binding_grain_effect_id = binding_grain_effect_id;}

        int get_player_move_speed( void ){return move_speed;}
        void set_player_move_speed(int move_speed){this->move_speed = move_speed;}

        int get_player_behit_effect( void ){return behit_effect;}
        void set_player_behit_effect(int behit_effect){this->behit_effect = behit_effect;}

        int get_player_behit_sound( void ){return behit_sound;}
        void set_player_behit_sound(int behit_sound){this->behit_sound = behit_sound;}

        int get_player_max_level( void ){return max_level;}
        void set_player_max_level(int max_level){this->max_level = max_level;}

		int get_player_skill_id( int index )
		{
			if ( 0 > index || index >= MAX_SKILL_COUNT) 
				return -1;
			return skill_id[index];
		}
        void set_player_skill_id(int index, int skillid)
		{
			if ( 0 > index || index >= MAX_SKILL_COUNT) 
				return;
			skill_id[index] = skillid;
		}

		int get_player_king_skill_id( void ){return king_skill_id;}
        void set_player_king_skill_id(int king_skill_id){this->king_skill_id = king_skill_id;}

private:
        int                      id;                                 // ID
		int                      level_id;                           // �ȼ�Id
        int                      name;                               // ����
		std::string              prefession;                         // ְҵ����
		std::string				 title;                              // �ƺ�
		int                      quality;                            // Ʒ��
        int                      addition;                           // �ӳ�
		int                      model;                              // ����
		int                      scale_rate;                         // ������
		int				         face_mode_id;		                 // ͷ��ͼ��
		int                      sex;                                // �Ա�
		int                      binding_grain_effect_id;            // ������
		int					     move_speed;                         // ǰ���ٶ�
		int					     behit_effect;						 // �ܴ���Ч
		int					     behit_sound;						 // �ܴ���Ч
		int					     max_level;							 // ���ȼ�
		int                      skill_id[MAX_SKILL_COUNT];          // ����Id
		int                      king_skill_id;                      // ��ɱ��                     
    };

	struct Player_Level_Attr_Config_Data
	{
	public:
		Player_Level_Attr_Config_Data(){ reset();}
		virtual ~Player_Level_Attr_Config_Data(){}

		int reset( void )
		{
			id						= 0;                                                
			level					= 0;                          
			levelup_exp				= 0;                             
			max_hp				    = 0;                        
			hp_recover_speed	    = 0;		                
			max_mp					= 0;                              
			max_gp					= 0;           
			gp_reduce_hurt          = 0;                        
			gp_behit_time           = 0;						
			gp_recover_speed        = 0;
			attack                  = 0;	
			define					= 0;                              
			hit_ratio				= 0;           
			avoidance               = 0;                        
			crit_rate               = 0;						
			tenacity                = 0;
			crit                    = 0;	
			power					= 0;

			return 0;
		}

		int get_player_id( void ){return id;}
		void set_player_id(int id){this->id = id;}

		int get_player_level( void ){return level;}
		void set_player_level(int level){this->level = level;}

		int get_player_levelup_exp( void ){return levelup_exp;}
		void set_player_levelup_exp(int levelup_exp){this->levelup_exp = levelup_exp;}

		int get_player_max_hp( void ){return max_hp;}
		void set_player_max_hp(int max_hp){this->max_hp = max_hp;}

		int get_player_hp_recover_speed( void ){return hp_recover_speed;}
		void set_player_hp_recover_speed(int hp_recover_speed){this->hp_recover_speed = hp_recover_speed;}

		int get_player_max_mp( void ){return max_mp;}
		void set_player_max_mp(int max_mp){this->max_mp = max_mp;}

		int get_player_max_gp( void ){return max_gp;}
		void set_player_max_gp(int max_gp){this->max_gp = max_gp;}

		int get_player_gp_reduce_hurt( void ){return gp_reduce_hurt;}
		void set_player_gp_reduce_hurt(int gp_reduce_hurt){this->gp_reduce_hurt = gp_reduce_hurt;}

		int get_player_gp_behit_time( void ){return gp_behit_time;}
		void set_player_gp_behit_time(int gp_behit_time){this->gp_behit_time = gp_behit_time;}

		int get_player_gp_recover_speed( void ){return gp_recover_speed;}
		void set_player_gp_recover_speed(int gp_recover_speed){this->gp_recover_speed = gp_recover_speed;}

		int get_player_attack( void ){return attack;}
		void set_player_attack(int attack){this->attack = attack;}

		int get_player_define( void ){return define;}
		void set_player_define(int define){this->define = define;}

		int get_player_hit_ratio( void ){return hit_ratio;}
		void set_player_hit_ratio(int hit_ratio){this->hit_ratio = hit_ratio;}

		int get_player_avoidance( void ){return avoidance;}
		void set_player_avoidance(int avoidance){this->avoidance = avoidance;}

		int get_player_crit_rate( void ){return crit_rate;}
		void set_player_crit_rate(int crit_rate){this->crit_rate = crit_rate;}

		int get_player_tenacity( void ){return tenacity;}
		void set_player_tenacity(int tenacity){this->tenacity = tenacity;}

		int get_player_crit( void ){return crit;}
		void set_player_crit(int crit){this->crit = crit;}

		int get_player_power( void ){return power;}
		void set_player_power(int power){this->power = power;}
	private:
		int                      id;                                 // ID
		int                      level;                              // �ȼ�
		int                      levelup_exp;                        // ��������
		int                      max_hp;                             // ��Ѫ����
		int                      hp_recover_speed;		             // ��Ѫ�ظ��ٶ�
		int                      max_mp;						     // ŭ������
		int                      max_gp;							 // �������
		int                      gp_reduce_hurt;					 // ���������
		int                      gp_behit_time;						 // ������˺�ָ����
		int                      gp_recover_speed;				     // ����ָ��ٶ�
		int                      attack;							 // ������
		int                      define;							 // ������
		int                      hit_ratio;							 // ����ֵ
		int                      avoidance;							 // �ر�ֵ
		int                      crit_rate;							 // ����ֵ
		int                      tenacity;							 // ����ֵ
		int                      crit;								 // �����˺��ӳ�
		int						 power;							     // ����
	};
}

#endif /* __PLAYER_DATA_H__ */

