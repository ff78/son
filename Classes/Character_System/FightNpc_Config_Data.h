

#ifndef __FightNpc_DATA_H__
#define __FightNpc_DATA_H__

#include <list>

#define  FightNpc_Max_Skill_Count    10         // 怪物配置技能的个数  

namespace Game_Data
{
    struct Game_Element;
    
    struct FightNpc_Base_Attr_Config_Data
    {
    public:
        FightNpc_Base_Attr_Config_Data(){ reset();}
        virtual ~FightNpc_Base_Attr_Config_Data(){}

        int reset( void )
        {
			id						= 0;  
			level_id				= 0;                                                      
			model					= 0;                             
			scale_rate				= 0;                        
			face_mode_id			= 0;
			camp                    = 0;
			ai                      = 0;
			binding_grain_effect_id = 0;           
			move_speed              = 0;
			moveback_speed          = 0;
			behit_effect            = 0;						
			behit_sound             = 0;
			max_level               = 0;	
			dead_drop_id			= 0;
			relive_time_interval    = 0;
			relive_max_count	    = 0;
			king_skill_id			= 0;
			king_skill_level		= 0;

			for (int i = 0; i < FightNpc_Max_Skill_Count; i++)
			{
				skill_id[i]    = 0;
				skill_level[i] = 0;
			}

            return 0;
        }
    public:
        int get_fightnpc_id( void ) {return id ;}
        void set_fightnpc_id(int id){this->id = id;}

		int get_fightnpc_level_id( void ){return level_id;}
		void set_fightnpc_level_id(int levelid){this->level_id = levelid;}
        
        int get_fightnpc_model( void ){return model;}
        void set_fightnpc_model(int model){this->model = model;}

        int get_fightnpc_scale_rate( void ){return scale_rate;}
        void set_fightnpc_scale_rate(int scale_rate){this->scale_rate = scale_rate;}

        int get_fightnpc_face_mode_id( void ){return face_mode_id;}
        void set_fightnpc_face_mode_id(int face_mode_id){this->face_mode_id = face_mode_id;}

		int get_fightnpc_camp( void ) {return camp ;}
        void set_fightnpc_camp(int camp){this->camp = camp;}

		int get_fightnpc_ai( void ) {return ai ;}
        void set_fightnpc_ai(int ai){this->ai = ai;}

        int get_fightnpc_binding_grain_effect_id( void ){return binding_grain_effect_id;}
        void set_fightnpc_binding_grain_effect_id(int binding_grain_effect_id){this->binding_grain_effect_id = binding_grain_effect_id;}

        int get_fightnpc_move_speed( void ){return move_speed;}
        void set_fightnpc_move_speed(int move_speed){this->move_speed = move_speed;}

		int get_fightnpc_moveback_speed( void ){return moveback_speed;}
        void set_fightnpc_moveback_speed(int moveback_speed){this->moveback_speed = moveback_speed;}

        int get_fightnpc_behit_effect( void ){return behit_effect;}
        void set_fightnpc_behit_effect(int behit_effect){this->behit_effect = behit_effect;}

        int get_fightnpc_behit_sound( void ){return behit_sound;}
        void set_fightnpc_behit_sound(int behit_sound){this->behit_sound = behit_sound;}

        int get_fightnpc_max_level( void ){return max_level;}
        void set_fightnpc_max_level(int max_level){this->max_level = max_level;}

		int get_fightnpc_dead_drop_id( void ) {return dead_drop_id ;}
        void set_fightnpc_dead_drop_id(int dead_drop_id){this->dead_drop_id = dead_drop_id;}

		int get_fightnpc_relive_time_interval( void ) {return relive_time_interval ;}
        void set_fightnpc_relive_time_interval(int relive_time_interval){this->relive_time_interval = relive_time_interval;}

		int get_fightnpc_relive_max_count( void ) {return relive_max_count ;}
        void set_fightnpc_relive_max_count(int relive_max_count){this->relive_max_count = relive_max_count;}

		int get_fightnpc_skill_id(int index) 
		{
			if( 0 > index || index >=  FightNpc_Max_Skill_Count ) 
				return -1; 
			return skill_id[index];
		}
        void set_fightnpc_skill_id(int index, int skillid)
		{
			if ( 0 > index || index >=  FightNpc_Max_Skill_Count ) 
				return;
			skill_id[index] = skillid;
		}

		int get_fightnpc_skill_level(int index) 
		{
			if( 0 > index || index >=  FightNpc_Max_Skill_Count ) 
				return -1; 
			return skill_level[index];
		}
        void set_fightnpc_skill_level(int index, int skilllevel)
		{
			if ( 0 > index || index >=  FightNpc_Max_Skill_Count ) 
				return; 
			skill_level[index] = skilllevel;
		}

		int get_fightnpc_king_skill_id( void ) {return king_skill_id ;}
        void set_fightnpc_king_skill_id(int king_skill_id){this->king_skill_id = king_skill_id;}

		int get_fightnpc_king_skill_level( void ) {return king_skill_level ;}
        void set_fightnpc_king_skill_level(int king_skill_level){this->king_skill_level = king_skill_level;}

private:
        int                      id;                                 // ID
		int                      level_id;                           // 等级Id
		int                      model;                              // 形象
		int                      scale_rate;                         // 缩放率
		int				         face_mode_id;		                 // 头像图标
		int				         camp;				                 // 阵营
		int				         ai;					             // ai
		int                      binding_grain_effect_id;            // 绑定粒子
		int					     move_speed;                         // 前进速度
		int					     moveback_speed;                     // 后退速度
		int					     behit_effect;						 // 受创特效
		int					     behit_sound;						 // 受创音效
		int					     max_level;							 // 最大等级
		int					     dead_drop_id;                       // 死亡掉落包
		int					     relive_time_interval;               // 重生间隔时间
		int					     relive_max_count;                   // 重生最大次数
		int                      skill_id[FightNpc_Max_Skill_Count]; // 技能Id
		int                      skill_level[FightNpc_Max_Skill_Count]; // 技能等级
		int                      king_skill_id;                      // 必杀技
		int                      king_skill_level;                   // 必杀技等级
    };

	struct FightNpc_Level_Attr_Config_Data
	{
	public:
		FightNpc_Level_Attr_Config_Data(){ reset();}
		virtual ~FightNpc_Level_Attr_Config_Data(){}

		int reset( void )
		{
			id						= 0;                                                
			level					= 0;                                                       
			max_hp				    = 0;                        	                
			max_mp					= 0;                              
			max_gp					= 0;           
			gp_reduce_hurt          = 0;                        
			gp_behit_time_interval  = 0;						
			gp_recover_speed        = 0;
			attack                  = 0;	
			define					= 0;                              
			hit_ratio				= 0;           
			avoidance               = 0;                        
			crit_rate               = 0;						
			tenacity                = 0;
			crit                    = 0;	

			return 0;
		}

		int get_fightnpc_id( void ){return id;}
		void set_fightnpc_id(int id){this->id = id;}

		int get_fightnpc_level( void ){return level;}
		void set_fightnpc_level(int level){this->level = level;}

		int get_fightnpc_max_hp( void ){return max_hp;}
		void set_fightnpc_max_hp(int max_hp){this->max_hp = max_hp;}

		int get_fightnpc_max_mp( void ){return max_mp;}
		void set_fightnpc_max_mp(int max_mp){this->max_mp = max_mp;}

		int get_fightnpc_max_gp( void ){return max_gp;}
		void set_fightnpc_max_gp(int max_gp){this->max_gp = max_gp;}

		int get_fightnpc_gp_reduce_hurt( void ){return gp_reduce_hurt;}
		void set_fightnpc_gp_reduce_hurt(int gp_reduce_hurt){this->gp_reduce_hurt = gp_reduce_hurt;}

		int get_fightnpc_gp_behit_time_interval( void ){return gp_behit_time_interval;}
		void set_fightnpc_gp_behit_time_interval(int gp_behit_time_interval){this->gp_behit_time_interval = gp_behit_time_interval;}

		int get_fightnpc_gp_recover_speede( void ){return gp_recover_speed;}
		void set_fightnpc_gp_recover_speed(int gp_recover_speed){this->gp_recover_speed = gp_recover_speed;}

		int get_fightnpc_attack( void ){return attack;}
		void set_fightnpc_attack(int attack){this->attack = attack;}

		int get_fightnpc_define( void ){return define;}
		void set_fightnpc_define(int define){this->define = define;}

		int get_fightnpc_hit_ratio( void ){return hit_ratio;}
		void set_fightnpc_hit_ratio(int hit_ratio){this->hit_ratio = hit_ratio;}

		int get_fightnpc_avoidance( void ){return avoidance;}
		void set_fightnpc_avoidance(int avoidance){this->avoidance = avoidance;}

		int get_fightnpc_crit_rate( void ){return crit_rate;}
		void set_fightnpc_crit_rate(int crit_rate){this->crit_rate = crit_rate;}

		int get_fightnpc_tenacity( void ){return tenacity;}
		void set_fightnpc_tenacity(int tenacity){this->tenacity = tenacity;}

		int get_fightnpc_crit( void ){return crit;}
		void set_fightnpc_crit(int crit){this->crit = crit;}
	private:
		int                      id;                                 // ID
		int                      level;                              // 等级
		int                      max_hp;                             // 气血上限
		int                      max_mp;						     // 怒气上限
		int                      max_gp;						     // 罡气上限
		int                      gp_reduce_hurt;					 // 罡气减伤率
		int                      gp_behit_time_interval;			 // 罡气受伤后恢复间隔
		int                      gp_recover_speed;				     // 罡气恢复速度
		int                      attack;							 // 攻击力
		int                      define;							 // 防御力
		int                      hit_ratio;							 // 命中值
		int                      avoidance;							 // 回避值
		int                      crit_rate;							 // 暴击值
		int                      tenacity;							 // 坚韧值
		int                      crit;								 // 暴击伤害加成
	};
}

#endif /* __FightNpc_DATA_H__ */

