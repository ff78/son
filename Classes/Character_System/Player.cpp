#ifdef YN_LINUX
#include <string.h>
#endif
#include <assert.h>

#ifdef GAME_CLIENT
//#include "Game_Utils.h"
#include <ctime>
#include "Item_System/Item_Mgr_Cl.h"
#else
#include "Character_Mgr.h"
#include "Item_System/Item_Mgr_Sv.h"
#include "Item_System/Item_Logic.h"
#include "Item_Container_System/Item_Container_Mgr_Sv.h"
#include "Acupoint_System/Acupoint_Mgr_Sv.h"
#include "Cool_Time_System/Cool_Time_Mgr_Sv.h"
#include "Fight_System/Fight_Config_Mgr.h"
#include "Fight_System/Offline_Fight_Record_Mgr_Sv.h"
#include "Login_Reward_System/Login_Reward_Mgr_Sv.h"
#include "Activity_System/Activity_Record_Mgr_Sv.h"
#include "Daily_Task_System/Daily_Task_Mgr_Sv.h"
#include "Common/date_time.h"
#include "LoggerFacade.h"
#endif

#include "Common/Tool.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
#include "Skill_System/Impact/Impact_Common.h"
#include "quest_system/quest_data/quest_data_mgr.h"
#include "Acupoint_System/Acupoint_Config_Mgr.h"
#include "Daily_Task_System/Daily_Task_Config_Mgr.h"
#include "Player_Config_Mgr.h"
#include "Player.h"
#include "Network_Common/message_stream.h"
#include "Relation_System/Relation_Mgr.h"

namespace Game_Data
{
	Player::Player(void)
		:m_nComboNum(0)
        ,m_logout_time(0)
        ,m_energy(0)
        ,m_buy_energy_count(0)
        ,m_prestige(0)
        ,m_offline_fight_count(0)
        ,m_buy_offline_fight_count(1)
        ,m_offline_fight_rank_reward_count(0)
        ,m_sex(0)
        ,m_present_token(0)
		,m_recharge_token(0)
        ,m_gold(0)
        ,m_exp(0)
        ,m_guide_id(-1)
        ,m_function_open_id(0)
		,m_fight_general_id(0)
        ,m_last_tidy_item_time(0)
		,m_pk_player_id(0)
		,m_login_level(0)
		,m_banks_exchange_count(0)
        ,m_last_role_fighting_capacity(0)
        ,m_last_role_have_gold(0)
		
	{
        m_coord_x = 400;
        m_coord_y = 200;
        
		m_ComboCountDownTime = 0.0f;
		m_base_attr_p_  = NULL;
		m_level_attr_p_ = NULL;
		memset(m_name, 0, MAX_NAME_LEN);

        m_login_time = (int)::time(NULL);
		m_character_quality = 0;
        m_map_item.clear();
        m_map_material_fragment.clear();
        m_map_book_fragment.clear();
        m_map_shoping_record.clear();
        m_map_acupoint.clear();
        m_map_cool_time.clear();
        m_map_deputy_general.clear();

        memset(&m_array_equipment_bar,0,sizeof(m_array_equipment_bar));
        memset(&m_array_book_bar,0,sizeof(m_array_book_bar));
        m_map_bag_item.clear();     
        m_map_store_item.clear();  
	}

	Player::~Player(void)
	{
	}

	void Player::set_base_attr_config_data(Player_Base_Attr_Config_Data*  base_attr)
	{
		m_base_attr_p_ = base_attr;
	}

	void Player::set_level_attr_config_data(Player_Level_Attr_Config_Data* level_attr)
	{
	    m_level_attr_p_ = level_attr;
	}

	void Player::init_attr_data(int static_id, int level)
	{   
        set_static_character_id(static_id);
        set_character_level(level);
		Player_Base_Attr_Config_Data* base_attr = PLAYER_MGR::instance()->get_player_base_attr(static_id);
#ifdef GAME_CLIENT
		CC_ASSERT(base_attr);
#else
        assert(base_attr);
#endif
		set_base_attr_config_data( base_attr );
        update_level_date();
		this->m_login_level = level;
	}

	int Player::get_character_max_hp( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_max_hp();
		}
        get_equipment_attr(EAT_HEALTH,nTotalValue);
        get_book_attr(EAT_HEALTH,nTotalValue);
        get_acupoint_attr(EAT_HEALTH,nTotalValue);
        DeputyGeneral* general = get_fight_general();
        if (general)
        {
            general->get_general_addition_attr(EAT_HEALTH,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_MAX_HP, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_MAX_HP, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int Player::get_character_max_mp( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_max_mp();
		}

		nTotalValue += get_buff_attr(CA_MAX_MP, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_MAX_MP, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int Player::get_character_max_gp( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_max_gp();
		}
        get_equipment_attr(EAT_MAGIC,nTotalValue);
        get_book_attr(EAT_MAGIC,nTotalValue);
        get_acupoint_attr(EAT_MAGIC,nTotalValue);
        DeputyGeneral* general = get_fight_general();
        if (general)
        {
            general->get_general_addition_attr(EAT_MAGIC,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_MAX_GP, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_MAX_GP, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int Player::get_character_hp_recover_speed( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_hp_recover_speed();
		}

		nTotalValue += get_buff_attr(CA_HP_RECOVER_SPEED, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_HP_RECOVER_SPEED, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int Player::get_character_gp_reduce_hurt( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_gp_reduce_hurt();
		}

		nTotalValue += get_buff_attr(CA_GP_REDUCE_HURT, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_GP_REDUCE_HURT, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int Player::get_character_gp_behit_time( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_gp_behit_time();
		}

		nTotalValue += get_buff_attr(CA_BEHIT_TIME, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_BEHIT_TIME, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int Player::get_character_gp_recover_speed( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_gp_recover_speed();
		}

		nTotalValue += get_buff_attr(CA_GP_RECOVER_SPEED, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_GP_RECOVER_SPEED, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int Player::get_character_attack( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_attack();
		}
        get_equipment_attr(EAT_ATTACK,nTotalValue);
        get_book_attr(EAT_ATTACK,nTotalValue);
        get_acupoint_attr(EAT_ATTACK,nTotalValue);
        DeputyGeneral* general = get_fight_general();
        if (general)
        {
            general->get_general_addition_attr(EAT_ATTACK,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_ATTACK, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_ATTACK, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int Player::get_character_define( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_define();
		}
        get_equipment_attr(EAT_DEFENSE,nTotalValue);
        get_book_attr(EAT_DEFENSE,nTotalValue);
        get_acupoint_attr(EAT_DEFENSE,nTotalValue);
        DeputyGeneral* general = get_fight_general();
        if (general)
        {
            general->get_general_addition_attr(EAT_DEFENSE,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_DEFINE, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_DEFINE, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int Player::get_character_hit_ratio( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_hit_ratio();
		}
        get_equipment_attr(EAT_HIT,nTotalValue);
        get_book_attr(EAT_HIT,nTotalValue);
        get_acupoint_attr(EAT_HIT,nTotalValue);
        DeputyGeneral* general = get_fight_general();
        if (general)
        {
            general->get_general_addition_attr(EAT_HIT,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_HIT_RATIO, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_HIT_RATIO, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int Player::get_character_avoidance( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_avoidance();
		}
        get_equipment_attr(EAT_DODGE,nTotalValue);
        get_book_attr(EAT_DODGE,nTotalValue);
        get_acupoint_attr(EAT_DODGE,nTotalValue);
        DeputyGeneral* general = get_fight_general();
        if (general)
        {
            general->get_general_addition_attr(EAT_DODGE,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_AVOIDANCE, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_AVOIDANCE, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int Player::get_character_crit_rate( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_crit_rate();
		}
        get_equipment_attr(EAT_CRIT,nTotalValue);
        get_book_attr(EAT_CRIT,nTotalValue);
        get_acupoint_attr(EAT_CRIT,nTotalValue);
        DeputyGeneral* general = get_fight_general();
        if (general)
        {
            general->get_general_addition_attr(EAT_CRIT,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_CRIT_RATE, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_CRIT_RATE, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int Player::get_character_tenacity( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_tenacity();
		}
        get_equipment_attr(EAT_TENACITY,nTotalValue);
        get_book_attr(EAT_TENACITY,nTotalValue);
        get_acupoint_attr(EAT_TENACITY,nTotalValue);
        DeputyGeneral* general = get_fight_general();
        if (general)
        {
            general->get_general_addition_attr(EAT_TENACITY,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_TENACITY, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_TENACITY, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int Player::get_character_crit( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_crit();
		}
        get_equipment_attr(EAT_HURT,nTotalValue);
        get_book_attr(EAT_HURT,nTotalValue);
        DeputyGeneral* general = get_fight_general();
        if (general)
        {
            general->get_general_addition_attr(EAT_HURT,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_CRIT, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_CRIT, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int Player::get_character_invincible( void )
	{
		int nTotalValue = 0;
		nTotalValue += get_buff_attr(CA_INVINCIBLE, MT_MODFITY_TYPE1);
		nTotalValue += get_buff_attr(CA_INVINCIBLE, MT_MODFITY_TYPE3);

		return nTotalValue;
	}

	float Player::get_character_move_speed_rate( void )
	{
		int nTotalValue = 1;
		nTotalValue += get_buff_attr(CA_MOVE_SPEED_RATE, MT_MODFITY_TYPE1);

		return (float)nTotalValue;
	}

	int Player::get_skill_level(int skillid)
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

	int Player::get_skill_quality(int /*skillid*/)
	{
        return m_character_quality;
	}

	void Player::set_skill_level(int skillid, int level)
	{
		vector<Character_Skill>::iterator it = m_skill_vector.begin();
		for (; it != m_skill_vector.end(); it++)
		{
			if ( skillid == (*it).skill_id )
			{
				//(*it).skill_level = level;
				return;
			}
		}
	}

	void Player::update(float /*delta*/)
	{
		if (m_nComboNum>0)
		{
			m_ComboCountDownTime--;
			if (m_ComboCountDownTime<=0)
			{
				m_nComboNum = 0;
#ifdef GAME_CLIENT
			//	Game_Utils::instance()->update_combo(get_database_character_id(),get_character_type(), get_character_combo());
#endif
			}
		}
	}

	const char* Player::get_character_name()
	{
		return m_name;
	}

	void  Player::set_character_name(const char* name)
	{
		memcpy(m_name, name, MAX_NAME_LEN);
	}

	void Player::update_gangqi(float /*delta*/)
	{
		if ( GetCurTime() - get_character_no_hurt_time() >= get_character_gp_behit_time() )
		{
			int add_gp = get_character_gp_recover_speed();
			if ( get_character_cur_gp() + add_gp > get_character_max_gp() )
			{
				add_gp = get_character_max_gp() - get_character_cur_gp();
			}
			
			set_character_cur_gp(get_character_cur_gp() + add_gp);
		}
	}

	void Player::set_character_combo( int nComboNum )
	{
		m_nComboNum = nComboNum;
		m_ComboCountDownTime = 9999999999.f;
	}

	int Player::get_power()
	{
		if ( NULL == m_level_attr_p_ )
		{
			return 0;
		}
		
		return m_level_attr_p_->get_player_power();
	}

    int Player::get_used_power()
    {
        int power = 0;
        Game_Data::Item* item = NULL;
        Game_Data::Book_Config* config = NULL;
        for (int i = 0;i < BP_MAX;++i)
        {
            item = m_array_book_bar[i];
            if (!item)
            {
                continue;
            }

            config = reinterpret_cast<Game_Data::Book_Config*>(item->config);
            if (!config)
            {
                continue;
            }

            power += config->need_power;
        }

        return power;
    }

    int Player::get_fighting_capacity()
    {
        float capacity = 0;
        int health = get_character_max_hp();
        int magic = get_character_max_gp();
        int attack = get_character_attack();
        int defense = get_character_define();
        int hit = get_character_hit_ratio() - HIT_SHOW_OFFSET;
        int dodge = get_character_avoidance();
        int crit = get_character_crit_rate() - CRIT_SHOW_OFFSET;
        int tenacity = get_character_tenacity();
        capacity = (0.1f*health) + (0.08f*magic) + (1.2f*attack) + (1.5f*defense) + (0.6f*hit) + (0.6f*dodge) + (0.6f*crit) + (0.6f*tenacity);

        return (int)capacity;
    }

    void Player::insert_item(Item* item)
    {
        if (item)
        {
            m_map_item.insert(make_pair(item->id,item));
        }
    }

    void Player::remove_item(int id)
    {
        Item_Map_Iter iter = m_map_item.find(id);
        if (iter != m_map_item.end())
        {
            m_map_item.erase(iter);
        }
    }

    void Player::insert_material_fragment(Item* item)
    {
        if (item)
        {
            m_map_material_fragment.insert(make_pair(item->config->base_id,item));
        }
    }

    void Player::remove_material_fragment(int base_id)
    {
        Item_Map_Iter iter = m_map_material_fragment.find(base_id);
        if (iter != m_map_material_fragment.end())
        {
            m_map_material_fragment.erase(iter);
        }
    }
    
    void Player::insert_book_fragment(Item* item)
    {
        if (item)
        {
            m_map_book_fragment.insert(make_pair(item->config->base_id,item));
        }
    }

    void Player::insert_shoping_record(shoping_record* record)
    {
        if (record)
        {
            m_map_shoping_record.insert(make_pair(record->goods_id_,record));
        }
    }

    void Player::remove_shoping_record(int goods_id)
    {
        shoping_record_map_iter iter = m_map_shoping_record.find(goods_id);
        if (iter != m_map_shoping_record.end())
        {
            m_map_shoping_record.erase(iter);
        }
    }

    void Player::insert_acupoint(Acupoint* acupoint)
    {
        if (acupoint)
        {
            m_map_acupoint.insert(make_pair(acupoint->type_,acupoint));
        }
    }

    void Player::remove_acupoint(int type)
    {
        Acupoint_Map_Iter iter = m_map_acupoint.find(type);
        if (iter != m_map_acupoint.end())
        {
            m_map_acupoint.erase(iter);
        }
    }
    
    void Player::insert_cool_time(Cool_Time* cool_time)
    {
        if (cool_time)
        {
            m_map_cool_time.insert(make_pair(cool_time->config_->type_,cool_time));
        }
    }

    void Player::remove_cool_time(int type)
    {
        Cool_Time_Map_Iter iter = m_map_cool_time.find(type);
        if (iter != m_map_cool_time.end())
        {
            m_map_cool_time.erase(iter);
        }
    }

    int Player::insert_item_container(Item_Container* container)
    {
        if (!container)
        {
            return -1;
        }

        m_map_item_container.insert(make_pair(container->id,container));

        return 0;
    }

    int Player::remove_item_container(int id)
    {
        Item_Container_Map_Iter iter = m_map_item_container.find(id);
        if (iter == m_map_item_container.end())
        {
            return -1;
        }

        m_map_item_container.erase(iter);

        return 0;
    }

	int Player::insert_deputy_general(DeputyGeneral* deputy_general)
	{
		if (!deputy_general)
		{
			return -1;
		}

		m_map_deputy_general.insert(make_pair(deputy_general->get_database_character_id(), deputy_general));

		return 0;
	}

	int Player::remove_deputy_general(int id)
	{
		Deputy_General_Map_Iter iter = m_map_deputy_general.find(id);
		if (iter == m_map_deputy_general.end())
		{
			return -1;
		}

		m_map_deputy_general.erase(iter);

		return 0;
	}
	
	/*int Player::insert_relation(Relation_Data* relation)
    {
        if (!relation)
        {
            return -1;
        }

		m_map_relation.insert(make_pair(relation->friend_role_id_,relation));

        return 0;
    }

    int Player::remove_relation(int friend_role_id)
    {
        Relation_Map_Iter iter = m_map_relation.find(friend_role_id);
        if (iter == m_map_relation.end())
        {
            return -1;
        }
  
        m_map_relation.erase(iter);

        return 0;
    }*/

    /*void Player::load_offline_fight_record(Offline_Fight_Record* record)
    {
#ifdef GAME_SERVER
        if (!record)
        {
            return;
        }

        if (m_list_offline_fight_record.size() < OFFLINE_FIGHT_RECORD_MAX_COUNT)
        {
            m_list_offline_fight_record.push_back(record);
        }
#endif
    }

    void Player::insert_offline_fight_record(Offline_Fight_Record* new_record)
    {
#ifdef GAME_SERVER
        if (!new_record)
        {
            return;
        }

        if (m_list_offline_fight_record.size() == OFFLINE_FIGHT_RECORD_MAX_COUNT)
        {
            Offline_Fight_Record* old_record = m_list_offline_fight_record.back();
            if (old_record)
            {
                if (old_record->challenger_id_ == m_database_id)
                {
                    old_record->challenger_flag_ = 0;
                }
                else if (old_record->target_id_ == m_database_id)
                {
                    old_record->target_flag_ = 0;
                }

                if (old_record->challenger_flag_ == 0 && old_record->target_flag_ == 0)
                {
                    OFFLINE_FIGHT_RECORD_MGR::instance()->remove_offline_fight_record(old_record);
                }
            }

            m_list_offline_fight_record.pop_back();
        }

        m_list_offline_fight_record.push_front(new_record);
#endif
    }*/

    void Player::load_item_container(Item_Container* container)
    {
        switch (container->type)
        {
        case ICT_STORE:
            {
                m_map_store_item.insert(make_pair(container->index, container));
            }

            break;

        case ICT_BAG:
            {
                m_map_bag_item.insert(make_pair(container->index, container));
            }

            break;

        default:
            break;
        }
    }

    void Player::set_bar_item(Item* item)
    {
        if (item->config->type == IT_EQUIPMENT)
        {
            m_array_equipment_bar[item->bar_pos] = item;
        }
        else if (item->config->type == IT_BOOK)
        {
            m_array_book_bar[item->bar_pos] = item;
        }
    }

    void Player::clear_bar_item(int item_type,int pos)
    {
        if (item_type == IT_EQUIPMENT)
        {
            m_array_equipment_bar[pos] = NULL;
        }
        else if (item_type == IT_BOOK)
        {
            m_array_book_bar[pos] = NULL;
        }
    }

    Item_Container* Player::get_bag_can_pile_item_container(Item_Config* config)
    {
        Item_Container* container = NULL;
        Item_Container_Map_Iter iter = m_map_bag_item.begin();
        for (;iter != m_map_bag_item.end();++iter)
        {
            container = iter->second;
            if (container && container->is_num_type == 1 && container->item_id == (uint64)config->base_id && container->item_count < config->pile_count)
            {
                return container;
            }
        }

        return NULL;
    }

    Item_Container* Player::get_empty_bag_container()
    {
        Item_Container* container = NULL;
        Item_Container_Map_Iter iter = m_map_bag_item.begin();
        for (;iter != m_map_bag_item.end();++iter)
        {
            container = iter->second;
            if (container->item_id == 0)
            {
                return container;
            }
        }

        return NULL;
    }

    int Player::get_empty_book_bar()
    {
        for (int i = 0;i < BP_MAX;++i)
        {
            if (m_array_book_bar[i] == NULL)
            {
                return i;
            }
        }

        return -1;
    }

    Item_Container* Player::get_container_from_bag(int index)
    {
        Item_Container* container = NULL;
        Item_Container_Map_Iter iter = m_map_bag_item.find(index);
        if (iter != m_map_bag_item.end())
        {
            container = iter->second;
        }

        return container;
    }

    Item* Player::get_item_from_equipment_bar(int pos)
    {
        return m_array_equipment_bar[pos];
    }

    Item* Player::get_item_from_book_bar(int pos)
    {
        return m_array_book_bar[pos];
    }

    Item* Player::get_item(uint64 item_id)
    {
        Item* item = NULL;
        Item_Map_Iter iter = m_map_item.find(item_id);
        if (iter != m_map_item.end())
        {
            item = iter->second;
        }

        return item;
    }

    Item* Player::get_material_fragment(int item_base_id)
    {
        Item* item = NULL;
        Item_Map_Iter iter = m_map_material_fragment.find(item_base_id);
        if (iter != m_map_material_fragment.end())
        {
            item = iter->second;
        }

        return item;
    }
    
    Item* Player::get_book_fragment(int item_base_id)
    {
        Item* item = NULL;
        Item_Map_Iter iter = m_map_book_fragment.find(item_base_id);
        if (iter != m_map_book_fragment.end())
        {
            item = iter->second;
        }

        return item;
    }

    shoping_record* Player::get_shoping_record(int goods_id)
    {
        shoping_record* record = NULL;
        shoping_record_map_iter iter = m_map_shoping_record.find(goods_id);
        if (iter != m_map_shoping_record.end())
        {
            record = iter->second;
        }

        return record;
    }
    
    Acupoint* Player::get_acupoint(int type)
    {
        Acupoint* acupoint = NULL;
        Acupoint_Map_Iter iter = m_map_acupoint.find(type);
        if (iter != m_map_acupoint.end())
        {
            acupoint = iter->second;
        }

        return acupoint;
    }
    
    Cool_Time* Player::get_cool_time(int type)
    {
        Cool_Time* cool_time = NULL;
        Cool_Time_Map_Iter iter = m_map_cool_time.find(type);
        if (iter != m_map_cool_time.end())
        {
            cool_time = iter->second;
        }

        return cool_time;
    }

    Item_Container* Player::get_item_container(uint64 container_id)
    {
        Item_Container* container = NULL;
        Item_Container_Map_Iter iter = m_map_item_container.find(container_id);
        if (iter != m_map_item_container.end())
        {
            container = iter->second;
        }

        return container;
    }

	DeputyGeneral* Player::get_deputy_general(int deputy_general_id)
	{
		DeputyGeneral* deputy_general = NULL;
		Deputy_General_Map_Iter iter = m_map_deputy_general.find(deputy_general_id);
		if ( iter != m_map_deputy_general.end() )
		{
			deputy_general = iter->second;
		}
		
		return deputy_general;
	}

	DeputyGeneral* Player::get_deputy_general_by_index(int index)
	{
		if ( index >= get_deputy_general_count() || index < 0 )
		{
			return NULL;
		}

		Deputy_General_Map_Iter iter = m_map_deputy_general.begin();
		for (int i = 0; i < index; i++)
		{
			iter++;
		}
		
		return iter->second;
	}

    bool Player::fill_item_message_stream(message_stream& ms)
    {
        int item_count = (int)m_map_item.size();
        ms << item_count;

        int count = 0;
        Item* item = NULL;
        Item_Map_Iter iter = m_map_item.begin();
        for (;iter != m_map_item.end();++iter)
        {
            item = iter->second;
            if (item)
            {
                ms << item->id;
                ms << item->container_id;
                ms << item->character_id;
                ms << item->general_id;
                ms << item->config->base_id;
                ms << item->is_bind;
                ms << item->bar_pos;
                ms << item->level;
                ms << item->exp;
                ms << item->current_quality;
                ms << item->count;
                ms << item->get_time_point;
                ms << item->use_time_point;
                ms << item->create_way;
                ms << item->destroy_way;
                for (int i = 0;i < SET_GEM_COUNT;++i)
                {
                    ms << item->gem_id[i];
                }

                ++count;
            }

        }

        if (count != item_count)
        {
            return false;
        }

        return true;
    }

    bool Player::fill_material_fragment_message_stream(message_stream& ms)
    {
        int fragment_type_count = (int)m_map_material_fragment.size();
        ms << fragment_type_count;

        int type_count = 0;
        Item* item = NULL;
        Item_Map_Iter iter = m_map_material_fragment.begin();
        for (;iter != m_map_material_fragment.end();++iter)
        {
            item = iter->second;
            if (item)
            {
                ms << item->id;
                ms << item->container_id;
                ms << item->character_id;
                ms << item->general_id;
                ms << item->config->base_id;
                ms << item->is_bind;
                ms << item->bar_pos;
                ms << item->level;
                ms << item->exp;
                ms << item->current_quality;
                ms << item->count;
                ms << item->get_time_point;
                ms << item->use_time_point;
                ms << item->create_way;
                ms << item->destroy_way;

                ++type_count;
            }

        }

        if (type_count != fragment_type_count)
        {
            return false;
        }

        return true;
    }
    
    bool Player::fill_book_fragment_message_stream(message_stream& ms)
    {
        int fragment_type_count = (int)m_map_book_fragment.size();
        ms << fragment_type_count;

        int type_count = 0;
        Item* item = NULL;
        Item_Map_Iter iter = m_map_book_fragment.begin();
        for (;iter != m_map_book_fragment.end();++iter)
        {
            item = iter->second;
            if (item)
            {
                ms << item->id;
                ms << item->container_id;
                ms << item->character_id;
                ms << item->general_id;
                ms << item->config->base_id;
                ms << item->is_bind;
                ms << item->bar_pos;
                ms << item->level;
                ms << item->exp;
                ms << item->current_quality;
                ms << item->count;
                ms << item->get_time_point;
                ms << item->use_time_point;
                ms << item->create_way;
                ms << item->destroy_way;

                ++type_count;
            }

        }

        if (type_count != fragment_type_count)
        {
            return false;
        }

        return true;
    }

    bool Player::fill_shoping_record_message_stream(message_stream& ms)
    {
        int record_count = (int)m_map_shoping_record.size();
        ms << record_count;

        int count = 0;
        shoping_record* record = NULL;
        shoping_record_map_iter iter = m_map_shoping_record.begin();
        for (;iter != m_map_shoping_record.end();++iter)
        {
            record = iter->second;
            if (record)
            {
                ms << record->goods_id_;
                ms << record->buy_count_;
                ++count;
            }
        }

        if (count != record_count)
        {
            return false;
        }

        return true;
    }

    bool Player::fill_acupoint_message_stream(message_stream& ms)
    {
        int acupoint_type_count = (int)m_map_acupoint.size();
        ms << acupoint_type_count;

        int type_count = 0;
        Acupoint* acupoint = NULL;
        Acupoint_Map_Iter iter = m_map_acupoint.begin();
        for (;iter != m_map_acupoint.end();++iter)
        {
            acupoint = iter->second;
            if (acupoint)
            {
                ms << acupoint->id_;
                ms << acupoint->role_id_;
                ms << acupoint->type_;
                ms << acupoint->level_;
                ms << acupoint->pos_;
                ms << acupoint->rate_;

                ++type_count;
            }

        }

        if (type_count != acupoint_type_count)
        {
            return false;
        }

        return true;
    }

    bool Player::fill_cool_time_message_stream(message_stream& ms)
    {
        int cool_time_type_count = (int)m_map_cool_time.size();
        ms << cool_time_type_count;

        int type_count = 0;
        Cool_Time* cool_time = NULL;
        Cool_Time_Map_Iter iter = m_map_cool_time.begin();
        for (;iter != m_map_cool_time.end();++iter)
        {
            cool_time = iter->second;
            if (cool_time)
            {
                ms << cool_time->id_;
                ms << cool_time->role_id_;
                ms << cool_time->config_->type_;
                ms << cool_time->cool_;
                ms << cool_time->check_;
                ms << cool_time->length_;

                ++type_count;
            }

        }

        if (type_count != cool_time_type_count)
        {
            return false;
        }

        return true;
    }

    bool Player::fill_item_container_message_stream(message_stream& ms)
    {
        int container_count = (int)m_map_item_container.size();
        ms << container_count;

        int count = 0;
        Item_Container* container = NULL;
        Item_Container_Map_Iter iter = m_map_item_container.begin();
        for (;iter != m_map_item_container.end();++iter)
        {
            container = iter->second;
            if (container)
            {
                ms << container->id;
                ms << container->character_id;
                ms << container->type;
                ms << container->index;
                ms << container->is_num_type;
                ms << container->item_id;
                ms << container->item_count;
                ms << container->destroy;
                
                ++count;
            }

        }

        if (count != container_count)
        {
            return false;
        }

        return true;
    }

	bool Player::fill_deputy_general_message_stream(message_stream& ms)
	{
		int deputy_general_count = (int)m_map_deputy_general.size();
		ms << deputy_general_count;

		int count = 0;
		DeputyGeneral* deputy_general = NULL;
		Deputy_General_Map_Iter iter = m_map_deputy_general.begin();
		for (;iter != m_map_deputy_general.end();++iter)
		{
			deputy_general = iter->second;
			if (deputy_general)
			{
				ms << deputy_general->get_database_character_id();
				ms << deputy_general->get_static_character_id();
				ms << deputy_general->get_character_level();
                ms << deputy_general->get_character_quality();
				ms << deputy_general->get_exp();

				++count;
			}

		}

		if (count != deputy_general_count)
		{
			return false;
		}

		return true;
	}

    bool Player::fill_offline_fight_record_message_stream(message_stream& ms)
    {
        /*int record_count = (int)m_list_offline_fight_record.size();
        ms << record_count;

        int count = 0;
        Offline_Fight_Record* record = NULL;
        Offline_Fight_Record_List_Iter iter = m_list_offline_fight_record.begin();
        for (;iter != m_list_offline_fight_record.end();++iter)
        {
            record = *iter;
            if (record)
            {
                ms << record->record_id_;
                ms << record->challenger_id_;
                ms << record->target_id_;
                ms << record->challenger_name_;
                ms << record->target_name_;
                ms << record->challenger_rank_;
                ms << record->target_rank_;
                ms << record->challenger_win_;
                ms << record->rank_change_;

                ++count;
            }

        }

        if (count != record_count)
        {
            return false;
        }*/

        return true;
    }

	void Player::db_save(int player_id)
	{
		save_role_attr(player_id);
		save_role_info(player_id);
	} 

	void Player::save_role_attr(int player_id)
	{
		vector<uint64> para;
		para.push_back(player_id);
		Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_attr", para);
	}

	void Player::save_role_info(int player_id)
	{
		vector<uint64> para;
		para.push_back(player_id);
		Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_info", para);
	}

    void Player::save_login(int player_id)
    {
        vector<uint64> para;
        para.push_back(player_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_login", para);
    }

    void Player::save_logout(int player_id)
    {
        vector<uint64> para;
        para.push_back(player_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_logout", para);
    }

    void Player::save_energy(int player_id)
    {
        vector<uint64> para;
        para.push_back(player_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_energy", para);
    }

    void Player::save_daily_refresh_data(int player_id)
    {
        vector<uint64> para;
        para.push_back(player_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_daily_data", para);
    }	

	void Player::release_item()
	{
#ifdef GAME_SERVER
		Item* item = NULL;
		Item_Map_Iter iter = m_map_item.begin();
		for (;iter != m_map_item.end();++iter)
		{
			item = iter->second;
			if (item)
			{
                ITEM_MGR::instance()->remove_item(item);
			}
		}
#endif
	}

    void Player::release_material_fragment()
	{
#ifdef GAME_SERVER
		Item* item = NULL;
        Item_Map_Iter iter = m_map_material_fragment.begin();
		for (;iter != m_map_material_fragment.end();++iter)
		{
			item = iter->second;
			if (item)
			{
                ITEM_MGR::instance()->remove_item(item);
			}
		}
#endif
    }
    
    void Player::release_book_fragment()
    {
#ifdef GAME_SERVER
        Item* item = NULL;
        Item_Map_Iter iter = m_map_book_fragment.begin();
        for (;iter != m_map_book_fragment.end();++iter)
        {
            item = iter->second;
            if (item)
            {
                ITEM_MGR::instance()->remove_item(item);
            }
        }
#endif
    }

    void Player::release_shoping_record()
    {
#ifdef GAME_SERVER
        shoping_record* record = NULL;
        shoping_record_map_iter iter = m_map_shoping_record.begin();
        for (;iter != m_map_shoping_record.end();++iter)
        {
            record = iter->second;
            if (record)
            {
                delete record;
            }
        }

        m_map_shoping_record.clear();
#endif
    }

    void Player::release_acupoint()
    {
#ifdef GAME_SERVER
        Acupoint* acupoint = NULL;
        Acupoint_Map_Iter iter = m_map_acupoint.begin();
        for (;iter != m_map_acupoint.end();++iter)
        {
            acupoint = iter->second;
            if (acupoint)
            {
                ACUPOINT_MGR::instance()->remove_acupoint(acupoint);
            }
        }
#endif
    }

    void Player::release_cool_time()
    {
#ifdef GAME_SERVER
        Cool_Time* cool_time = NULL;
        Cool_Time_Map_Iter iter = m_map_cool_time.begin();
        for (;iter != m_map_cool_time.end();++iter)
        {
            cool_time = iter->second;
            if (cool_time)
            {
                COOL_TIME_MGR::instance()->remove_cool_time(cool_time);
            }
        }
#endif
    }

    void Player::release_item_container()
    {
#ifdef GAME_SERVER
        Item_Container* container = NULL;
        Item_Container_Map_Iter iter = m_map_item_container.begin();
        for (;iter != m_map_item_container.end();++iter)
        {
            container = iter->second;
            if (container)
            {
                ITEM_CONTAINER_MGR::instance()->remove_item_container(container);
            }
        }
#endif
    }

	void Player::release_deputy_general()
	{
#ifdef GAME_SERVER
		DeputyGeneral* deputy_general = NULL;
		Deputy_General_Map_Iter iter = m_map_deputy_general.begin();
		for (;iter != m_map_deputy_general.end();++iter)
		{
			deputy_general = iter->second;
			if (deputy_general)
			{
                CHARACTER_MGR::instance()->remove_character_from_list(deputy_general->get_database_character_id());
                
			}
		}
#endif
	}

    void Player::release_offline_fight_record()
    {
#ifdef GAME_SERVER
        Offline_Fight_Record* record = NULL;
        Offline_Fight_Record_List_Iter iter = m_list_offline_fight_record.begin();
        for (;iter != m_list_offline_fight_record.end();++iter)
        {
            record = *iter;
            if (record)
            {
                if (record->challenger_id_ == m_database_id)
                {
                    record->challenger_flag_ = 0;
                }
                else if (record->target_id_ == m_database_id)
                {
                    record->target_flag_ = 0;
                }

                if (record->challenger_flag_ == 0 && record->target_flag_ == 0)
                {
                    OFFLINE_FIGHT_RECORD_MGR::instance()->remove_offline_fight_record(record);
                }
            }
        }
#endif
    }

	void Player::release_relation()
	{
#ifdef GAME_SERVER
		Relation_Data *relation = NULL;
		Relation_Map_Iter iter = m_map_relation.begin();
		for (; iter != m_map_relation.end(); ++iter)
		{
			relation = iter->second;
			Relation_Mgr::instance()->remove_relation(relation);
		}
		
#endif // GAME_SERVER

	}

    void Player::get_player_addition_attr(int attr_type,int& op_val)
    {
		if ( NULL == m_level_attr_p_ || NULL == m_base_attr_p_ )
		{
			return;
		}
		
        int val = 0;
        switch (attr_type)
        {
        case EAT_HEALTH:
            {
                val = m_level_attr_p_->get_player_max_hp();
            }

            break;

        case EAT_MAGIC:
            {
                val = m_level_attr_p_->get_player_max_gp();
            }

            break;

        case EAT_ATTACK:
            {
                val = m_level_attr_p_->get_player_max_gp();
            }

            break;

        case EAT_DEFENSE:
            {
                val = m_level_attr_p_->get_player_max_gp();
            }

            break;

        case EAT_HIT:
            {
                val = m_level_attr_p_->get_player_max_gp();
            }

            break;

        case EAT_DODGE:
            {
                val = m_level_attr_p_->get_player_max_gp();
            }

            break;

        case EAT_CRIT:
            {
                val = m_level_attr_p_->get_player_max_gp();
            }

            break;

        case EAT_TENACITY:
            {
                val = m_level_attr_p_->get_player_max_gp();
            }

            break;

        case EAT_HURT:
            {
                val = m_level_attr_p_->get_player_crit();
            }

            break;

        default:
            break;
        }

        get_equipment_attr(attr_type,val);
        get_book_attr(attr_type,val);
        if (attr_type != EAT_HURT)
        {
            get_acupoint_attr(attr_type,val);
        }

        val = int(val * m_base_attr_p_->get_player_addition() / 100.0f);
        op_val += val;
    }

    void Player::get_equipment_attr(int attr_type,int& op_val)
    {
        int val = 0;
        Item* item = NULL;
        for (int i = 0;i < EP_MAX;++i)
        {
            item = m_array_equipment_bar[i];
            if (item)
            {
                val += ITEM_MGR::instance()->get_equipment_attr(item,attr_type);
                val += ITEM_MGR::instance()->get_equipment_gem_attr(item,attr_type);
            }
        }

        op_val += val;
    }

    void Player::get_book_attr(int attr_type,int& op_val)
    {
        int val = 0;
        Item* item = NULL;
        for (int i = 0;i < BP_MAX;++i)
        {
            item = m_array_book_bar[i];
            if (item)
            {
                val += ITEM_CONFIG_MGR::instance()->get_book_attr(item->config->base_id,item->level,item->current_quality,attr_type);
            }
        }

        op_val += val;
    }

    void Player::get_acupoint_attr(int attr_type,int& op_val)
    {
        int val = 0;
        Acupoint* acupoint = get_acupoint(attr_type);
        if (acupoint)
        {
            val += ACUPOINT_CONFIG_MGR::instance()->get_acupoint_attr(attr_type,acupoint->pos_,acupoint->level_);
            val += ACUPOINT_CONFIG_MGR::instance()->get_vein_attr(attr_type,acupoint->pos_,acupoint->level_);
        }
        
        op_val += val;
    }

    int Player::get_player_levelup_exp()
    {
		if ( NULL == m_level_attr_p_ )
		{
			return 0;
		}
		
        return m_level_attr_p_->get_player_levelup_exp();
    }

    void Player::update_level_date()
    {
		if ( NULL == m_base_attr_p_ )
		{
			return;
		}
		
        Player_Level_Attr_Config_Data* level_attr = PLAYER_MGR::instance()->get_player_level_attr(m_base_attr_p_->get_player_level_id(),m_level);
#ifdef GAME_CLIENT
        CC_ASSERT(level_attr);
#else
        assert(level_attr);
#endif

        set_level_attr_config_data(level_attr);
        set_character_cur_hp(get_character_max_hp());
        set_character_cur_mp(get_character_max_mp());
        set_character_cur_gp(get_character_max_gp());
    }

    int Player::get_token()
    {
        return (m_present_token + m_recharge_token);
    }

    int Player::get_buy_energy_cost()
    {
        int cost = 20;
        if (m_buy_energy_count >= 5 && m_buy_energy_count < 10)
        {
            cost = 40;
        }
        else if (m_buy_energy_count >= 10)
        {
            cost = 80;
        }

        return cost;
    }

    int Player::get_buy_offline_fight_count_cost()
    {
        int cost = m_buy_offline_fight_count * 2;
        return cost;
    }

	void Player::add_recharge_token(uint add)
	{
        m_recharge_token += add;
#ifdef GAME_SERVER
        // update to client
        vector<uint64> para;
        para.push_back(m_database_id);
        para.push_back(add);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_add_recharge_token",para);

        // save db
        para.clear();
        para.push_back(m_database_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_recharge_token",para);
#endif
	}

    void Player::change_token(int change)
    {
        if (change > 0)
        {
            m_present_token += change;
        } 
        else
        {
            int cost = - change;
            if (m_present_token >= cost)
            {
                m_present_token -= cost;
            } 
            else
            {
                int last = cost - m_present_token;
                m_present_token = 0;
                m_recharge_token -= last;
                if (m_recharge_token < 0)
                {
                    m_recharge_token = 0;
                }
            }

#ifdef GAME_SERVER
            DAILY_TASK_MGR::instance()->update_daily_task_progress(m_database_id,DTT_COST_TOKEN);
#endif
        }

#ifdef GAME_SERVER
        // update to client
        vector<uint64> para;
        para.push_back(m_database_id);
        para.push_back(change);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_change_token",para);
        if( change < 0)
        {
            Game_Logic::Game_Event_Response::instance()->on_cost_gold(m_database_id);
        }
#endif
    }

    void Player::change_energy(int change)
    {
        m_energy += change;
        if (m_energy < 0)
        {
            m_energy = 0;
        }

#ifdef GAME_SERVER
        // update to client
        vector<uint64> para;
        para.push_back(m_database_id);
        para.push_back(change);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_change_energy",para);
#endif
    }

    void Player::change_prestige(int change)
    {
        m_prestige += change;
        if (m_prestige < 0)
        {
            m_prestige = 0;
        }

#ifdef GAME_SERVER
        // update to client
        vector<uint64> para;
        para.push_back(m_database_id);
        para.push_back(change);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_change_prestige",para);
#endif
    }

    void Player::change_gold(int change)
    {
        m_gold += change;
        if (m_gold < 0)
        {
            m_gold = 0;
        }

#ifdef GAME_SERVER
        // update to client
        vector<uint64> para;
        para.push_back(m_database_id);
        para.push_back(change);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_change_gold",para);

        Game_Logic::Game_Event_Response::instance()->on_add_money(m_database_id);
       
#endif
    }

    void Player::change_exp(int change)
    {
        if (change > 0 && m_level >= MAX_LEVEL)
        {
            return;
        }

        m_exp += change;
        if (m_exp < 0)
        {
            m_exp = 0;
        }

        bool is_level_up = false;
        int levelup_exp = get_player_levelup_exp();
        while (m_exp >= levelup_exp && m_level < MAX_LEVEL)
        {
            is_level_up = true;

            m_exp -= levelup_exp;
            ++m_level;
#ifdef GAME_SERVER
			LoggerFacade::instance()->facade_role_level(this->m_database_id,m_name,m_sex,(m_level-1),1,m_level,0,0);
#endif 
            update_level_date();
            levelup_exp = get_player_levelup_exp();

            //
			/*int recover_energy = m_energy+PLAYER_UP_LEVEL_RECOVER_ENERGY;
            if (recover_energy > PLAYER_MAX_ENERGY)
            {
                recover_energy = PLAYER_MAX_ENERGY;
            }
            
            m_energy = recover_energy;*/
        }

#ifdef GAME_SERVER
        // update to client
        vector<uint64> para;
        para.push_back(m_database_id);
        para.push_back(m_database_id);
        para.push_back(change);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_change_exp",para);

        // save db
        para.clear();
        para.push_back(m_database_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_exp",para);
        if (is_level_up)
        {
            Game_Logic::Game_Content_Interface::instance()->exec_interface("on_role_level_changed",para);

            // save db
            //Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_energy",para);
            // save db
            Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_level",para);
        }
#else
        if (is_level_up)
        {
            int out = 0;
            //Game_Utils::instance()->play_continued_effect(m_database_id,"3003",out);//
//			AI_UTils::instance()->add_effect_to_scene("2016");//
		}
        
#endif
    }

    void Player::change_guide_id(int id)
    {
        m_guide_id = id;
    }

    void Player::add_function_open_id()
    {
        ++m_function_open_id;

#ifdef GAME_SERVER
        // save db
        vector<uint64> para;
        para.push_back(m_database_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_function_open_id",para);
#endif
    }

    void Player::login_refresh_data(int player_id)
    {
#ifdef GAME_SERVER
        cute::date_time logoutTime(m_logout_time);
        cute::date_time curTime;
        int refreshPoint = 0;//hour
        bool dailyRefresh = false;
        bool newDayRefresh = false;
        if (logoutTime.year() == curTime.year() && logoutTime.month() == curTime.month() && 
            logoutTime.mday() == curTime.mday())
        {
            if (curTime.hour() >= refreshPoint)
            {
                if (logoutTime.hour() < refreshPoint)
                {
                    dailyRefresh = true;
                }
            }
        }
        else
        {
            newDayRefresh = true;
            if (curTime.hour() >= refreshPoint)
            {
                dailyRefresh = true;
            }
        }

        // ¡„µ„À¢–�?        if (newDayRefresh == true)
        {
            m_buy_energy_count = 0;
            m_offline_fight_count = PLAYER_DAILY_OFFLINE_FIGHT_COUNT;
            m_buy_offline_fight_count = 1;
            m_offline_fight_rank_reward_count = 1;
			m_banks_exchange_count = 0;

            LOGIN_REWARD_MGR::instance()->login_refresh_data((curTime.wday() == 1),player_id);
            DAILY_TASK_MGR::instance()->login_refresh_data(player_id);
            ACTIVITY_RECORD_MGR::instance()->login_refresh_data(player_id);

            save_daily_refresh_data(player_id);
        }

        // À¢–¬ ±º‰µ„À¢–�?refreshPoint)
        if (dailyRefresh == true)
        {
            
        }

        login_update_energy(player_id);

        save_login(player_id);
#endif
    }

    void Player::login_update_energy(int player_id)
    {
#ifdef GAME_SERVER
        if (m_energy < PLAYER_MAX_ENERGY)
        {
            cute::date_time logoutTime(m_logout_time);
            cute::date_time curTime;

            int year = curTime.year()-logoutTime.year();
            int month = curTime.month()-logoutTime.month();
            if (year == 0 && month == 0)
            {
                m_energy += ((((curTime.mday()-logoutTime.mday())*24+curTime.hour()-logoutTime.hour()))*60+curTime.minute()-logoutTime.minute())/5;
                if (m_energy > PLAYER_MAX_ENERGY)
                {
                    m_energy = PLAYER_MAX_ENERGY;
                }
            }
            else
            {
                m_energy = PLAYER_MAX_ENERGY;
            }

            save_energy(player_id);
        }
#endif
    }

	int  Player::get_fight_general_id()
	{
		return m_fight_general_id;
	}

    DeputyGeneral* Player::get_fight_general()
    {
        DeputyGeneral* general = get_deputy_general(m_fight_general_id);
        return general;
    }

	void  Player::set_fight_general_id(int fight_general_id)
	{
		m_fight_general_id = fight_general_id;
	}

	void Player::character_quality_up()
	{
		++m_character_quality;
        ++m_static_id;
        Player_Base_Attr_Config_Data* base_attr = PLAYER_MGR::instance()->get_player_base_attr(m_static_id);
#ifdef GAME_CLIENT
        CC_ASSERT(base_attr);
#else
        assert(base_attr);
#endif
        set_base_attr_config_data(base_attr);
        update_level_date();

        Game_Logic::Game_Event_Response::instance()->on_player_quality_up(m_database_id);

        // save db
        vector<uint64> para;
        para.push_back(m_database_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_quality_up",para);
	}

    void Player::load_deputy_general_skill()
    {
        DeputyGeneral* general = NULL;
        Deputy_General_Map_Iter iter = m_map_deputy_general.begin();
        for (;iter != m_map_deputy_general.end();++iter)
        {
            general = iter->second;
            if (general)
            {
                vector<uint64>  para;
                para.push_back(get_database_character_id());
                para.push_back(general->get_database_character_id());
                Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_select_skill", para);
            }
        }
    }

    int Player::get_deputy_general_skill_count()
    {
        int count = 0;
        DeputyGeneral* general = NULL;
        Deputy_General_Map_Iter iter = m_map_deputy_general.begin();
        for (;iter != m_map_deputy_general.end();++iter)
        {
            general = iter->second;
            if (general)
            {
                count += general->get_skill_size();
            }
        }

        return count;
    }

    int Player::get_bag_same_item_count(int item_base_id)
    {
        int count = 0;
        Item_Container* container = NULL;
        Item_Container_Map_Iter iter = m_map_bag_item.begin();
        for (;iter != m_map_bag_item.end();++iter)
        {
            container = iter->second;
            if (!container)
            {
                continue;
            }

            if (container->is_num_type == 1)
            {
                if (container->item_id == (uint64)item_base_id)
                {
                    count += container->item_count;
                }
			}
            else
            {
                Item* item = ITEM_MGR::instance()->get_item(container->item_id);
                if (item && item->config && item->config->base_id == item_base_id)
                {
                    count += container->item_count;
                }
            }
        }

        return count;
    }

   
	int Player::get_bag_empty_count()
    {
        int count = 0;
        Item_Container* container = NULL;
        Item_Container_Map_Iter iter = m_map_bag_item.begin();
        for (;iter != m_map_bag_item.end();++iter)
        {
            container = iter->second;
            if (!container)
            {
                continue;
            }

            if (container->item_id == 0)
            {
                ++count;
            }
        }

        return count;
    }

    int Player::get_face_mode_id()
    {
        if (m_base_attr_p_)
        {
            return  m_base_attr_p_->get_player_face_mode_id();
        } 
        else
        {
            return  0;
        }
    }

    int Player::get_model()
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

    bool Player::player_all_equipment_reach_quality(int quality)
    {
        Item* item = NULL;
        for (int i = 0;i < EP_FASHION;++i)
        {
            item = m_array_equipment_bar[i];
            if (!item)
            {
                return false;
            }

            if (item->current_quality < quality)
            {
                return false;
            }
        }

        return true;
    }

    bool Player::player_equip_book_count(int& count, int quality)
    {
        int equip_count = 0;
        Item* item = NULL;
        for (int i = 0;i < BP_MAX;++i)
        {
            item = m_array_book_bar[i];
            if (!item)
            {
                continue;
            }

            if( item->current_quality < quality)
            {
                continue;
            }

            ++equip_count;
        }

        if(equip_count >= count)
        {
            count = equip_count;
            return true;
        }
        else
        {
            count = equip_count;
        }
        return false;
    }

    bool Player::player_have_skill(int& count,int level)
    {
        int skill_count = 0;
        vector<Character_Skill>& skill_vector = get_skill_vector();
        vector<Character_Skill>::iterator iter = skill_vector.begin();
        for (;iter != skill_vector.end();++iter)
        {
            Character_Skill& skill = *iter;
            /*if (skill.skill_level < level)
            {
                continue;
            }*/

            ++skill_count;
        }

        if(skill_count >= count)
        {
            count = skill_count;
            return true;
        }
        else
        {
            count = skill_count;
        }
        return false;
    }

    bool Player::player_have_general(int& count,int quality)
    {
        int general_count = 0;
        DeputyGeneral* general = NULL;
        Deputy_General_Map_Iter iter = m_map_deputy_general.begin();
        for (;iter != m_map_deputy_general.end();++iter)
        {
            general = iter->second;
            if (general->get_character_quality() < quality)
            {
                continue;
            }

            ++general_count;
        }

        if (general_count >= count)
        {
            count = general_count;
            return true;
        }
        else
        {
            count = general_count;
        }
        return false;
    }

    bool Player::is_fighting_capacity_changed()
    {
        int fighting_capacity = get_fighting_capacity();
        if (fighting_capacity != m_last_role_fighting_capacity)
        {
            m_last_role_fighting_capacity = fighting_capacity;
            return true;
        }
        
        return false;
    }
	bool Player::is_fighting_capacity_getting_big()
	{
		int fighting_capacity = get_fighting_capacity();
		if (fighting_capacity >m_last_role_fighting_capacity)
		{
			m_last_role_fighting_capacity = fighting_capacity;

			return true;
		}else
		{
			m_last_role_fighting_capacity = fighting_capacity;
		}

		return false;
	}

    bool Player::is_havegold_changed()
    {
        if (m_gold != m_last_role_have_gold)
        {
            m_last_role_have_gold = m_gold;
            return true;
        }

        return false;
    }

    void Player::refresh_shop_record()
    {
        shoping_record* record = NULL;
        shoping_record_map_iter iter = m_map_shoping_record.begin();
        for (;iter != m_map_shoping_record.end();++iter)
        {
            record = iter->second;
            if (record)
            {
                record->buy_count_ = 0;
                record->check_point_ = (int)time(NULL);
            }
        }
    }
}