
#include "Skill_System/Impact/Impact_Common.h"
#include "FightNpc_Config_Mgr.h"
#include "FightNpc_Config_Data.h"
#include "FightNpc.h"

namespace Game_Data
{
	FightNpc::FightNpc(void)
	{
		m_base_attr_p_  = NULL;
		m_level_attr_p_ = NULL;
	}

	FightNpc::~FightNpc(void)
	{
	}

	void FightNpc::set_base_attr_config_data(FightNpc_Base_Attr_Config_Data*  m_base_attr_p_)
	{
		this->m_base_attr_p_ = m_base_attr_p_;
	}

	void FightNpc::set_level_attr_config_data(FightNpc_Level_Attr_Config_Data* m_level_attr_p_)
	{
		this->m_level_attr_p_ = m_level_attr_p_;
	}

	void FightNpc::init_attr_data(int static_id, int level)
	{
		set_static_character_id(static_id);
		set_character_level( level );
		FightNpc_Base_Attr_Config_Data* base_attr = FIGHTNPC_MGR::instance()->get_base_attr_config_data(static_id);
		set_base_attr_config_data( base_attr );

		FightNpc_Level_Attr_Config_Data* level_attr = FIGHTNPC_MGR::instance()->get_level_attr_config_data(static_id, base_attr->get_fightnpc_level_id(), this->m_level);
		set_level_attr_config_data( level_attr );

		set_character_cur_hp( get_character_max_hp() );
		set_character_cur_mp( get_character_max_mp() );
		set_character_cur_gp( get_character_max_gp() );

		std::list<int> skill_list;
		std::list<int>::iterator it;
		Character_Skill skill;
		std::vector<Character_Skill> skill_vector;
		for (int i = 0; i < FightNpc_Max_Skill_Count; i++)
		{
			skill.skill_id = base_attr->get_fightnpc_skill_id(i);
			//skill.skill_level = base_attr->get_fightnpc_skill_level(i);
			skill_vector.push_back( skill );
		}
		insert_skill_list( skill_vector );
	}

	int FightNpc::get_character_max_hp( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_fightnpc_max_hp();
		}

		nTotalValue += get_buff_attr(CA_MAX_HP, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_MAX_HP, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightNpc::get_character_max_mp( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_fightnpc_max_mp();
		}

		nTotalValue += get_buff_attr(CA_MAX_MP, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_MAX_MP, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightNpc::get_character_max_gp( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_fightnpc_max_gp();
		}

		nTotalValue += get_buff_attr(CA_MAX_GP, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_MAX_GP, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightNpc::get_character_gp_reduce_hurt( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_fightnpc_gp_reduce_hurt();
		}

		nTotalValue += get_buff_attr(CA_GP_REDUCE_HURT, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_GP_REDUCE_HURT, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightNpc::get_character_attack( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_fightnpc_attack();
		}

		nTotalValue += get_buff_attr(CA_ATTACK, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_ATTACK, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightNpc::get_character_define( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_fightnpc_define();
		}

		nTotalValue += get_buff_attr(CA_DEFINE, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_DEFINE, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightNpc::get_character_hit_ratio( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_fightnpc_hit_ratio();
		}

		nTotalValue += get_buff_attr(CA_HIT_RATIO, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_HIT_RATIO, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightNpc::get_character_avoidance( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_fightnpc_avoidance();
		}

		nTotalValue += get_buff_attr(CA_AVOIDANCE, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_AVOIDANCE, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightNpc::get_character_crit_rate( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_fightnpc_crit_rate();
		}

		nTotalValue += get_buff_attr(CA_CRIT_RATE, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_CRIT_RATE, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightNpc::get_character_tenacity( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_fightnpc_tenacity();
		}

		nTotalValue += get_buff_attr(CA_TENACITY, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_TENACITY, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightNpc::get_character_crit( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_fightnpc_crit();
		}

		nTotalValue += get_buff_attr(CA_CRIT, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_CRIT, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightNpc::get_skill_level(int skillid)
	{
		vector<Character_Skill>::iterator it = m_skill_vector.begin();
		for (; it != m_skill_vector.end(); it++)
		{
			if ( skillid == (*it).skill_id )
			{
				//return (*it).skill_level;
			}
		}

		return 0;
	}

	int FightNpc::get_skill_quality(int /*skillid*/)
	{
		return 0;
	}

	int FightNpc::get_character_invincible( void )
	{
		int nTotalValue = get_buff_attr(CA_INVINCIBLE, MT_MODFITY_TYPE3);

		return nTotalValue;
	}

	float FightNpc::get_character_move_speed_rate( void )
	{
		int nTotalValue = 1;
		nTotalValue += get_buff_attr(CA_MOVE_SPEED_RATE, MT_MODFITY_TYPE1);

		return (float)nTotalValue;
	}

	void FightNpc::set_skill_level(int skillid, int level)
	{
		vector<Character_Skill>::iterator it = m_skill_vector.begin();
		for (; it != m_skill_vector.end(); it++)
		{
			if ( skillid == (*it).skill_id )
			{
				//(*it).skill_level = level;
			}
		}
	}

    int FightNpc::get_face_mode_id()
    {
        if (m_base_attr_p_)
        {
            return  m_base_attr_p_->get_fightnpc_face_mode_id();
        } 
        else
        {
            return  0;
        }
    }

    int FightNpc::get_model()
    {
        if (m_base_attr_p_)
        {
            return  m_base_attr_p_->get_fightnpc_model();
        } 
        else
        {
            return  0;
        }
    }
}