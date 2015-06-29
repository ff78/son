
#include "Character_System/Player_Config_Mgr.h"
#include "Skill_System/Impact/Impact_Common.h"
#include "FightPlayer.h"

namespace Game_Data
{
	FightPlayer::FightPlayer(void)
	{
		memset(m_name, 0, MAX_NAME_LEN);
	}

	FightPlayer::~FightPlayer(void)
	{
	}

	void FightPlayer::init_attr_data(int static_id, int level)
	{
		set_static_character_id(static_id);
		set_character_level( level );
		Player_Base_Attr_Config_Data* base_attr = PLAYER_MGR::instance()->get_player_base_attr(static_id);
#ifdef GAME_CLIENT
		CC_ASSERT(base_attr);
#else
		assert(base_attr);
#endif
		set_base_attr_config_data( base_attr );

		Player_Level_Attr_Config_Data* level_attr = PLAYER_MGR::instance()->get_player_level_attr(base_attr->get_player_level_id(), level);
#ifdef GAME_CLIENT
		CC_ASSERT(level_attr);
#else
		assert(level_attr);
#endif

		set_level_attr_config_data(level_attr);
	}

	void FightPlayer::set_base_attr_config_data(Player_Base_Attr_Config_Data*  m_base_attr_p_)
	{
		this->m_base_attr_p_ = m_base_attr_p_;
	}

	void FightPlayer::set_level_attr_config_data(Player_Level_Attr_Config_Data* m_level_attr_p_)
	{
		this->m_level_attr_p_ = m_level_attr_p_;
	}

	int FightPlayer::get_character_max_hp( void )
	{
		int nTotalValue = Character::get_character_max_hp();

		nTotalValue += get_buff_attr(CA_MAX_HP, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_MAX_HP, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightPlayer::get_character_max_mp( void )
	{
		int nTotalValue = Character::get_character_max_mp();

		nTotalValue += get_buff_attr(CA_MAX_MP, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_MAX_MP, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightPlayer::get_character_max_gp( void )
	{
		int nTotalValue = Character::get_character_max_gp();

		nTotalValue += get_buff_attr(CA_MAX_GP, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_MAX_GP, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightPlayer::get_character_gp_reduce_hurt( void )
	{
		int nTotalValue = Character::get_character_gp_reduce_hurt();

		nTotalValue += get_buff_attr(CA_GP_REDUCE_HURT, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_GP_REDUCE_HURT, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightPlayer::get_character_attack( void )
	{
		int nTotalValue = Character::get_character_attack();

		nTotalValue += get_buff_attr(CA_ATTACK, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_ATTACK, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightPlayer::get_character_define( void )
	{
		int nTotalValue = Character::get_character_define();

		nTotalValue += get_buff_attr(CA_DEFINE, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_DEFINE, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightPlayer::get_character_hit_ratio( void )
	{
		int nTotalValue = Character::get_character_hit_ratio();

		nTotalValue += get_buff_attr(CA_HIT_RATIO, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_HIT_RATIO, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightPlayer::get_character_avoidance( void )
	{
		int nTotalValue = Character::get_character_avoidance();

		nTotalValue += get_buff_attr(CA_AVOIDANCE, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_AVOIDANCE, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightPlayer::get_character_crit_rate( void )
	{
		int nTotalValue = Character::get_character_crit_rate();

		nTotalValue += get_buff_attr(CA_CRIT_RATE, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_CRIT_RATE, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightPlayer::get_character_tenacity( void )
	{
		int nTotalValue = Character::get_character_tenacity();

		nTotalValue += get_buff_attr(CA_TENACITY, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_TENACITY, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightPlayer::get_character_crit( void )
	{
		int nTotalValue = Character::get_character_crit();

		nTotalValue += get_buff_attr(CA_CRIT, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_CRIT, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int FightPlayer::get_skill_level(int skillid)
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

	int FightPlayer::get_skill_quality(int skillid)
	{
		return 0;
	}

	int FightPlayer::get_character_invincible( void )
	{
		int nTotalValue = get_buff_attr(CA_INVINCIBLE, MT_MODFITY_TYPE3);

		return nTotalValue;
	}

	float FightPlayer::get_character_move_speed_rate( void )
	{
		int nTotalValue = 1;
		nTotalValue += get_buff_attr(CA_MOVE_SPEED_RATE, MT_MODFITY_TYPE1);

		return (float)nTotalValue;
	}

	void FightPlayer::set_skill_level(int skillid, int level)
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

	int FightPlayer::get_model()
	{
		if (m_base_attr_p_)
		{
			return  m_base_attr_p_->get_player_model();
		} 
		else
		{
			return  0;
		}
	}
}