#include "Common/Tool.h"
#ifdef GAME_CLIENT
#include "Common/GameMacro.h"
//#include "AI_System/Game_Utils.h"
#endif
//#include "Skill_System/Buff/Buff_Mgr.h"
#include "Skill_System/Impact/Impact_Common.h"
#include "Character.h"
#include <stdio.h>

namespace Game_Data
{
	Character::Character(void)
	{

		cleanup();

	}

	Character::~Character(void)
	{

		cleanup();

	}

	void Character::cleanup(void)
	{
        m_scene_id              = 0;
		m_database_id			= 0;
		m_static_id				= 0;
		m_type					= 0;
		m_level					= 1;                              
		m_cur_hp				= 0;                           
		m_cur_mp				= 0;						     
		m_cur_gp				= 0;						    
		m_max_hp				= 0;                            
		m_max_mp				= 0;						    
		m_max_gp				= 0;						     
		m_hp_recover_speed		= 0;		          
		m_gp_reduce_hurt		= 0;					
		m_gp_behit_time			= 0;						
		m_gp_recover_speed		= 0;				     
		m_attack				= 0;							
		m_define				= 0;							
		m_hit_ratio				= 0;							 
		m_avoidance				= 0;							 
		m_crit_rate				= 0;							 
		m_tenacity				= 0;							
		m_crit					= 0;		
		m_dead					= 0;
		m_invincible			= 0;
		m_move_speed_rate       = 0;
		m_Ice_Resist			= 0;
		m_Fire_Resist			= 0;
		m_Thunder_Resist		= 0;
		m_Wind_Resist			= 0;
		m_Light_Resist			= 0;
		m_Dark_Resist			= 0;

#ifdef GAME_CLIENT
		//m_ai_state				= MISS_STATE;
#endif
		m_no_hurt_time          = GetCurTime(0);
//		m_buff_vector.clear();                            
#if 1//yypp
		m_job_skill_list.clear();
		m_select_job_skill_list.clear();
#endif
	}

	int Character::get_buff_attr(int attr_index, int type)
	{
		int nTotalValue = 0;
		/*vector<Buff_Logic>::iterator it = m_buff_vector.begin();
		for (; it != m_buff_vector.end(); it++)
		{
			(*it).GetIntPropertyRefix(attr_index, type, nTotalValue);
		}
*/
		return nTotalValue;
	}

//	int Character::have_this_buff(int buffid)
//	{
		/*vector<Buff_Logic>::iterator it = m_buff_vector.begin();
		for (; it != m_buff_vector.end(); it++)
		{
			if ( (uint32)buffid == (*it).GetBuffData(CBA_ID) )
			{
				return 1;
			}
		}*/
//
//		return 0;
//	}

//	Buff_Logic* Character::get_buff_logic(int buffid)
//	{
		/*vector<Buff_Logic>::iterator it = m_buff_vector.begin();
		for (; it != m_buff_vector.end(); it++)
		{
			if ( (uint32)buffid == (*it).GetBuffData(CBA_ID) )
			{
				return &(*it);
			}
		}
*/
//		return NULL;
//	}

//	int Character::insert_buff(Buff_Logic* buff_logic)
//	{
//		if ( NULL == buff_logic )
//			return 1;
//
//		int target_effect_id = buff_logic->GetBuffInfo()->m_Attr[BA_TARGET_EFFECT];
//		if ( target_effect_id > 0 )
//		{
//			int out_effect_id = 0;
//#ifdef GAME_CLIENT
//			char szTemp[64];
//			memset(szTemp, 0, sizeof(szTemp));
//			::SPRINTF(szTemp,"%d",target_effect_id);
//			//Game_Utils::instance()->play_continued_effect(get_database_character_id(), szTemp, out_effect_id);
//#endif
//			buff_logic->SetBuffData(CBA_EFFECT_ID, out_effect_id);
//		}
//		
//		m_buff_vector.push_back(*buff_logic);
//
//
//#ifdef GAME_CLIENT
//		/*Game_Utils::instance()->srpite_set_is_stunning(get_database_character_id(), (get_buff_attr(CA_CANNOT_MOVE, MT_MODFITY_TYPE1) != 0));
//		Game_Utils::instance()->sprite_set_move_scale(get_database_character_id(), get_character_move_speed_rate());*/
//#endif
//
//		return 0;
//	}

//	int Character::remove_buff(int buffid)
//	{
//		vector<Buff_Logic>::iterator it = m_buff_vector.begin();
//		for (; it != m_buff_vector.end(); it++)
//		{
//			if ( (uint32)buffid == (*it).GetBuffData(CBA_ID) )
//			{
//#ifdef GAME_CLIENT
//				/*Game_Utils::instance()->remove_continued_effect(get_database_character_id(), (*it).GetBuffData(CBA_EFFECT_ID));
//				m_buff_vector.erase(it);
//				Game_Utils::instance()->srpite_set_is_stunning(get_database_character_id(), (get_buff_attr(CA_CANNOT_MOVE, MT_MODFITY_TYPE1) != 0));
//				Game_Utils::instance()->sprite_set_move_scale(get_database_character_id(), get_character_move_speed_rate());*/
//#endif
//				return 0;
//			}
//		}
//
//		return 1;
//	}

//	int Character::remove_all_buff()
//	{
//		vector<Buff_Logic>::iterator it = m_buff_vector.begin();
//		for (; it != m_buff_vector.end(); it++)
//		{
//		
//#ifdef GAME_CLIENT
//			int effect_id = (*it).GetBuffData(CBA_EFFECT_ID);
//			/*if ( effect_id > 0 )
//			{
//				Game_Utils::instance()->remove_continued_effect(get_database_character_id(), effect_id);
//			}
//			Game_Utils::instance()->srpite_set_is_stunning(get_database_character_id(), 0);
//			Game_Utils::instance()->sprite_set_move_scale(get_database_character_id(), 1);*/
//#endif
//		}
//
//		m_buff_vector.clear();
//
//		return 0;
//	}

//	int Character::remove_all_fight_buff()
//	{
//		vector<Buff_Logic>::iterator it = m_buff_vector.begin();
//		for (; it != m_buff_vector.end(); it++)
//		{
//
//#ifdef GAME_CLIENT
//			int buff_id = (*it).GetBuffData(CBA_ID);
//			if ( buff_id > 0 )
//			{
//				Buff_Data* newDataPtr = BUFF_MGR::instance()->GetBuffData(buff_id);
//				if( NULL == newDataPtr && newDataPtr->m_Attr[BA_LEAVECOPY_DISAPPEAR] > 0 )
//				{
//					remove_buff(buff_id);
//				}
//			}
//#endif
//		}
//
//		m_buff_vector.clear();
//		/*
//#ifdef GAME_CLIENT
//		Game_Utils::instance()->srpite_set_is_stunning(get_database_character_id(), 0);
//		Game_Utils::instance()->sprite_set_move_scale(get_database_character_id(), 1);
//#endif*/
//
//		return 0;
//	}

//	Buff_Logic* Character::get_buff_logic_by_index(int index)
//	{
//		if ( index > (int)m_buff_vector.size() )
//			return NULL;
//
//		return &m_buff_vector.at(index);
//	}
//	
//	int Character::get_buff_size()
//	{
//		return m_buff_vector.size();
//	}

	//int Character::get_buff_replace_index(Buff_Data* buffInfoPtr)
	//{
	//	int  index = -1;
	//	if ( 0 == buffInfoPtr )
	//	{
	//		return index;
	//	}

	//	vector<Buff_Logic>::iterator it = m_buff_vector.begin();
	//	for (; it != m_buff_vector.end(); it++)
	//	{
	//		if ( buffInfoPtr->m_Attr[BA_REPLACE_ID] == (*it).GetBuffInfo()->m_Attr[BA_REPLACE_ID] )
	//		{
	//			index++;
	//			break;
	//		}
	//	}

	//	return index;
	//}

	void Character::insert_skill_list(std::vector<Character_Skill> &skill_list)
	{
		for (int i = 0; i < (int)skill_list.size(); i++)
		{
			m_skill_vector.push_back(skill_list[i]);
		}
	}

	void Character::insert_skill(Character_Skill & skill)
	{
		m_skill_vector.push_back(skill);
	}

    void Character::set_character_cur_hp(int cur_hp)
    {
        this->m_cur_hp = cur_hp;
        if ( this->m_cur_hp <= 0 )
		{/*
#ifdef GAME_CLIENT
            m_dead = 1; Game_Utils::instance()->dead(get_database_character_id(), get_character_type(), 0);
			this->m_cur_hp = 0;
#endif*/
			set_dead(1);
        }
    }

	Character_Skill* Character::get_skill_by_id(int skill_id)
	{
		vector<Character_Skill>::iterator it = m_skill_vector.begin();
		for (; it != m_skill_vector.end(); it++)
		{
			if ( it->skill_id == skill_id )
			{
				return &(*it);
			}
		}

		return NULL;
	}

	Character_Skill* Character::get_skill_by_index(int index)
	{
		if ( index < (int)m_skill_vector.size() )
		{
			return &(m_skill_vector.at(index));
		}

		return NULL;
	}

	void Character::set_skill_level(int skillid, int level)
	{
		vector<Character_Skill>::iterator it = m_skill_vector.begin();
		for (; it != m_skill_vector.end(); it++)
		{
			if ( it->skill_id == skillid )
			{
				//it->skill_level = level;
				break;
			}
		}
	}

	int Character::get_skill_id_by_database_id(uint64 database_id)
	{
		vector<Character_Skill>::iterator it = m_skill_vector.begin();
		for (; it != m_skill_vector.end(); it++)
		{
			if ( it->database_id == database_id )
			{
				return it->skill_id;
			}
		}

		return 0;
	}

	uint64 Character::get_skill_database_id_by_id(int skill_id)
	{
		vector<Character_Skill>::iterator it = m_skill_vector.begin();
		for (; it != m_skill_vector.end(); it++)
		{
			if ( it->skill_id == skill_id )
			{
				return it->database_id;
			}
		}

		return 0;
	}

	int Character::get_skill_level_by_database_id(uint64 database_id)
	{
		vector<Character_Skill>::iterator it = m_skill_vector.begin();
		for (; it != m_skill_vector.end(); it++)
		{
			if ( it->database_id == database_id )
			{
				//return it->skill_level;
			}
		}

		return 0;
	}

	int Character::get_skill_size()
	{
		return m_skill_vector.size();
	}


	void Character::update_job_skill(int _skill_id,int _skill_up_id)
	{
		int size = m_job_skill_list.size();
		for (int i = 0; i < size; i++)
		{
			if (m_job_skill_list[i] == _skill_id)
			{
				m_job_skill_list[i] = _skill_up_id;
				return;
			}
		}

		return ;
	}


	bool Character::delete_job_skill(int _skill_id)
	{
		vector<int>::iterator _iter = m_job_skill_list.begin();
		for (_iter; _iter < m_job_skill_list.end(); ++_iter)
		{
			if ((*_iter) == _skill_id)
			{
				m_job_skill_list.erase(_iter);
				return true;
			}
		}

		return false;
	}

	bool Character::insert_select_skill(int _select_skill_id)
	{
		vector<int>::iterator _iter = m_select_job_skill_list.begin();
		for (_iter; _iter < m_select_job_skill_list.end(); ++_iter)
		{
			if ((*_iter) == _select_skill_id)
			{
				return false;
			}
		}
		m_select_job_skill_list.push_back(_select_skill_id);
		return true;
	}

	bool Character::insert_job_skill(int _skill_id)
	{
		vector<int>::iterator _iter = m_job_skill_list.begin();
		for (_iter; _iter < m_job_skill_list.end(); ++_iter)
		{
			if ((*_iter) == _skill_id)
			{
				return false;
			}
		}
		m_job_skill_list.push_back(_skill_id);
		return true;
	}
#if 1//yypp
	int Character::get_job_skill_by_index(int index)
	{
		if (index < (int)m_job_skill_list.size() && index>=0)
		{
			return m_job_skill_list.at(index);
		}

		return -1;
	}

	int  Character::get_skill_index_by_skill_id(int _skill_id)
	{
		int index=0;
		vector<int>::iterator _iter = m_job_skill_list.begin();
		for (; _iter != m_job_skill_list.end(); _iter++)
		{
			if ((*_iter) == _skill_id)
			{
				return index;
			}
			index++;
		}
		return -1;
	}
	#endif
	void Character::set_dead(int dead)
	{ 
		m_dead = dead;
//		if ( 0 != m_dead )
//		{
//			remove_all_buff();
//		}
	}
#if 1//yypp
	int Character::get_player_select_skill_by_index(int index)
	{
		if (index < m_select_job_skill_list.size())
			return m_select_job_skill_list[index];
		else
			return -1;
	}
	std::vector<int>& Character::get_player_select_skills()
	{
		//if (m_select_job_skill_list.size()>0)
		return m_select_job_skill_list;
	}
	void Character::set_player_temp_select_skills(std::vector<int>&temp)
	{
		m_temp_job_skill_list.clear();
		m_temp_job_skill_list=temp;
	}
	void Character::update_player_select_skills()
	{
		m_select_job_skill_list = m_temp_job_skill_list;
	}
#endif	

	void Character::set_cur_pet_id(int id)
	{
        m_cur_pet_id = 0;
		map<uint64, int>::iterator _iter = m_pet_list.begin();
		for (_iter; _iter != m_pet_list.end(); ++_iter)
		{
			if ((*_iter).second == id)
			{
				m_cur_pet_id = id;
			}

		}

	}

	void Character::add_pet(uint64 database_id, int id)
	{
		int _size = (int)m_pet_list.size();
		if (_size >= 20)
		{
			return;
		}
		m_pet_list.insert( std::pair<uint64, int>(database_id, id) );
	}

	void Character::reset_pet(uint64 database_id, int id)
	{
		map<uint64, int>::iterator _iter = m_pet_list.find(database_id);
		if (_iter != m_pet_list.end())
		{
			m_pet_list[database_id] = id;
		}

	}

	void Character::change_one_pet_of_list_by_id(int old_id, int new_id)
	{
		map<uint64, int>::iterator _iter = m_pet_list.begin();
		for (_iter; _iter != m_pet_list.end(); ++_iter)
		{
			if ((*_iter).second == old_id)
			{
				(*_iter).second = new_id;
			}

		}

	}


/*
#ifdef GAME_CLIENT
	void Character::set_ai_state(Charcter_AI_State ai_state)
	{
		if ( ai_state > m_ai_state )
		{
			m_ai_state = ai_state;
		}
	}
#endif*/
}