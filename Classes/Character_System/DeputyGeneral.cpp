#ifdef YN_LINUX
#include <string.h>

#endif
#ifdef GAME_SERVER
#include "log_common_defines.h"
#include "logger.h"
extern cute::logger *role_money_die;
#endif // GAME_SERVER

#include <assert.h>
#include "Common/Tool.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
#include "Skill_System/Impact/Impact_Common.h"
#include "quest_system/quest_data/quest_data_mgr.h"
#include "Acupoint_System/Acupoint_Config_Mgr.h"
#include "Player_Config_Mgr.h"
#include "Player.h"
#include "DeputyGeneral.h"


#include "Network_Common/message_stream.h"

#ifdef GAME_CLIENT
//#include "Game_Utils.h"
#include <ctime>
#include "Item_System/Item_Mgr_Cl.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#else
#include "Item_System/Item_Mgr_Sv.h"
#include "Common/date_time.h"
#endif

namespace Game_Data
{
	DeputyGeneral::DeputyGeneral(void)
		:m_nComboNum(0)
        ,m_sex(0)
        ,m_exp(0)
	{
        m_coord_x = 400;
        m_coord_y = 200;
		m_ComboCountDownTime = 0.0f;
		m_base_attr_p_ = NULL;
		m_level_attr_p_ = NULL;
		memset(m_name, 0, MAX_NAME_LEN);
		m_owner = NULL;
		m_character_quality = 0;
        memset(&m_array_equipment_bar,0,sizeof(m_array_equipment_bar));
        memset(&m_array_book_bar,0,sizeof(m_array_book_bar));
	}

	DeputyGeneral::~DeputyGeneral(void)
	{
	}

	void DeputyGeneral::set_base_attr_config_data(Player_Base_Attr_Config_Data* base_attr)
	{
	    m_base_attr_p_ = base_attr;
	}

	void DeputyGeneral::set_level_attr_config_data(Player_Level_Attr_Config_Data* level_attr)
	{
	    m_level_attr_p_ = level_attr;
	}

	void DeputyGeneral::init_attr_data(int static_id, int level)
	{
        set_static_character_id(static_id);
        set_character_level(level);
		Player_Base_Attr_Config_Data* base_attr = PLAYER_MGR::instance()->get_player_base_attr(static_id);
#ifdef GAME_CLIENT
		CC_ASSERT(base_attr);
#else
        assert(base_attr);
#endif
		set_base_attr_config_data(base_attr);
        update_level_date();
	}

	int DeputyGeneral::get_character_max_hp( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_max_hp();
		}
        get_equipment_attr(EAT_HEALTH,nTotalValue);
        get_book_attr(EAT_HEALTH,nTotalValue);
        get_acupoint_attr(EAT_HEALTH,nTotalValue);
        if (m_owner && m_owner->get_fight_general_id() == m_database_id)
        {
            m_owner->get_player_addition_attr(EAT_HEALTH,nTotalValue);
        }
        
		nTotalValue += get_buff_attr(CA_MAX_HP, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_MAX_HP, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int DeputyGeneral::get_character_max_mp( void )
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

	void DeputyGeneral::character_quality_up()
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
        if( NULL != m_owner)
        {
            Game_Logic::Game_Event_Response::instance()->on_gerneral_qa_up(m_owner->get_database_character_id());
        }

        // save db
        vector<uint64> para;
        para.push_back(m_database_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_deputy_general_quality_up",para);
	}

	int DeputyGeneral::get_character_max_gp( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_max_gp();
		}
        get_equipment_attr(EAT_MAGIC,nTotalValue);
        get_book_attr(EAT_MAGIC,nTotalValue);
        get_acupoint_attr(EAT_MAGIC,nTotalValue);
        if (m_owner && m_owner->get_fight_general_id() == m_database_id)
        {
            m_owner->get_player_addition_attr(EAT_MAGIC,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_MAX_GP, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_MAX_GP, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int DeputyGeneral::get_character_hp_recover_speed( void )
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

	int DeputyGeneral::get_character_gp_reduce_hurt( void )
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

	int DeputyGeneral::get_character_gp_behit_time( void )
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

	int DeputyGeneral::get_character_gp_recover_speed( void )
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

	int DeputyGeneral::get_character_attack( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_attack();
		}
        get_equipment_attr(EAT_ATTACK,nTotalValue);
        get_book_attr(EAT_ATTACK,nTotalValue);
        get_acupoint_attr(EAT_ATTACK,nTotalValue);
        if (m_owner && m_owner->get_fight_general_id() == m_database_id)
        {
            m_owner->get_player_addition_attr(EAT_ATTACK,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_ATTACK, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_ATTACK, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int DeputyGeneral::get_character_define( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_define();
		}
        get_equipment_attr(EAT_DEFENSE,nTotalValue);
        get_book_attr(EAT_DEFENSE,nTotalValue);
        get_acupoint_attr(EAT_DEFENSE,nTotalValue);
        if (m_owner && m_owner->get_fight_general_id() == m_database_id)
        {
            m_owner->get_player_addition_attr(EAT_DEFENSE,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_DEFINE, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_DEFINE, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int DeputyGeneral::get_character_hit_ratio( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_hit_ratio();
		}
        get_equipment_attr(EAT_HIT,nTotalValue);
        get_book_attr(EAT_HIT,nTotalValue);
        get_acupoint_attr(EAT_HIT,nTotalValue);
        if (m_owner && m_owner->get_fight_general_id() == m_database_id)
        {
            m_owner->get_player_addition_attr(EAT_HIT,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_HIT_RATIO, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_HIT_RATIO, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int DeputyGeneral::get_character_avoidance( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_avoidance();
		}
        get_equipment_attr(EAT_DODGE,nTotalValue);
        get_book_attr(EAT_DODGE,nTotalValue);
        get_acupoint_attr(EAT_DODGE,nTotalValue);
        if (m_owner && m_owner->get_fight_general_id() == m_database_id)
        {
            m_owner->get_player_addition_attr(EAT_DODGE,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_AVOIDANCE, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_AVOIDANCE, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int DeputyGeneral::get_character_crit_rate( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_crit_rate();
		}
        get_equipment_attr(EAT_CRIT,nTotalValue);
        get_book_attr(EAT_CRIT,nTotalValue);
        get_acupoint_attr(EAT_CRIT,nTotalValue);
        if (m_owner && m_owner->get_fight_general_id() == m_database_id)
        {
            m_owner->get_player_addition_attr(EAT_CRIT,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_CRIT_RATE, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_CRIT_RATE, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int DeputyGeneral::get_character_tenacity( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_tenacity();
		}
        get_equipment_attr(EAT_TENACITY,nTotalValue);
        get_book_attr(EAT_TENACITY,nTotalValue);
        get_acupoint_attr(EAT_TENACITY,nTotalValue);
        if (m_owner && m_owner->get_fight_general_id() == m_database_id)
        {
            m_owner->get_player_addition_attr(EAT_TENACITY,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_TENACITY, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_TENACITY, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int DeputyGeneral::get_character_crit( void )
	{
		int nTotalValue = 0;
		if ( NULL != m_level_attr_p_ )
		{
			nTotalValue = m_level_attr_p_->get_player_crit();
		}
        get_equipment_attr(EAT_HURT,nTotalValue);
        get_book_attr(EAT_HURT,nTotalValue);
        if (m_owner && m_owner->get_fight_general_id() == m_database_id)
        {
            m_owner->get_player_addition_attr(EAT_HURT,nTotalValue);
        }

		nTotalValue += get_buff_attr(CA_CRIT, MT_MODFITY_TYPE1);
		nTotalValue *= (PER_RATIO + get_buff_attr(CA_CRIT, MT_MODFITY_TYPE2))/PER_RATIO;

		return nTotalValue;
	}

	int DeputyGeneral::get_character_invincible( void )
	{
		int nTotalValue = 0;
		nTotalValue += get_buff_attr(CA_INVINCIBLE, MT_MODFITY_TYPE1);
		nTotalValue += get_buff_attr(CA_INVINCIBLE, MT_MODFITY_TYPE3);

		return nTotalValue;
	}

	float DeputyGeneral::get_character_move_speed_rate( void )
	{
		int nTotalValue = 1;
		nTotalValue += get_buff_attr(CA_MOVE_SPEED_RATE, MT_MODFITY_TYPE1);

		return (float)nTotalValue;
	}

	int DeputyGeneral::get_skill_level(int skillid)
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

	int DeputyGeneral::get_skill_quality(int /*skillid*/)
	{
        return m_character_quality;
	}

	void DeputyGeneral::set_skill_level(int skillid, int level)
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

	void DeputyGeneral::update(float /*delta*/)
	{
		if (m_nComboNum>0)
		{
			m_ComboCountDownTime--;
			if (m_ComboCountDownTime<=0)
			{
				m_nComboNum = 0;
#ifdef GAME_CLIENT
				//Game_Utils::instance()->update_combo(get_database_character_id(),get_character_type(), get_character_combo());
#endif
			}
		}
	}

	const char* DeputyGeneral::get_character_name()
	{
       const char* name = "";
#ifdef GAME_CLIENT
       if (m_base_attr_p_)
       {
           name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(m_base_attr_p_->get_player_name());
       }
#endif
		return name;
	}

	void  DeputyGeneral::set_character_name(const char* name)
	{
		memcpy(m_name, name, MAX_NAME_LEN);
	}

	void DeputyGeneral::update_gangqi(float /*delta*/)
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

	void DeputyGeneral::set_character_combo( int nComboNum )
	{
		m_nComboNum = nComboNum;
		m_ComboCountDownTime = 20;
	}

	int DeputyGeneral::get_power()
	{
		if ( NULL == m_level_attr_p_ )
		{
			return 0;
		}
		
		return m_level_attr_p_->get_player_power();
	}

    int DeputyGeneral::get_used_power()
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

    int DeputyGeneral::get_fighting_capacity()
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

	Player* DeputyGeneral::get_owner()
	{
		return m_owner;
	}

    int DeputyGeneral::get_owner_id()
    {
        if (m_owner)
        {
            return m_owner->get_database_character_id();
        }
       
        return 0;
    }

	void DeputyGeneral::set_owner(Player* player)
	{
		m_owner = player;
	}

    void DeputyGeneral::set_bar_item(Item* item)
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

    void DeputyGeneral::clear_bar_item(int item_type,int pos)
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

    int DeputyGeneral::get_empty_book_bar()
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

    Item* DeputyGeneral::get_item_from_equipment_bar(int pos)
    {
        return m_array_equipment_bar[pos];
    }

    Item* DeputyGeneral::get_item_from_book_bar(int pos)
    {
        return m_array_book_bar[pos];
    }

    void DeputyGeneral::get_general_addition_attr(int attr_type,int& op_val)
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

    void DeputyGeneral::get_equipment_attr(int attr_type,int& op_val)
    {
        int val = 0;
        Item* item = NULL;
        for (int i = 0;i < EP_MAX;++i)
        {
            item = m_array_equipment_bar[i];
            if (item)
            {
                val += ITEM_CONFIG_MGR::instance()->get_equipment_attr(item->config->base_id,item->level,item->current_quality,attr_type);
            }
        }

        op_val += val;
    }

    void DeputyGeneral::get_book_attr(int attr_type,int& op_val)
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

    void DeputyGeneral::get_acupoint_attr(int attr_type,int& op_val)
    {
        int val = 0;
        if (m_owner)
        {
            Acupoint* acupoint = m_owner->get_acupoint(attr_type);
            if (acupoint)
            {
                val += ACUPOINT_CONFIG_MGR::instance()->get_acupoint_attr(attr_type,acupoint->pos_,acupoint->level_);
                val += ACUPOINT_CONFIG_MGR::instance()->get_vein_attr(attr_type,acupoint->pos_,acupoint->level_);
            }
        }

        op_val += val;
    }

    int DeputyGeneral::get_player_levelup_exp()
    {
		if ( NULL == m_level_attr_p_ )
		{
			return 0;
		}
		
        return m_level_attr_p_->get_player_levelup_exp();
    }

    void DeputyGeneral::update_level_date()
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

    void DeputyGeneral::change_exp(int change)
    {
        if (change > 0 && m_level >= MAX_LEVEL)
        {
            return;
        }

        m_exp += change;

        bool is_level_up = false;
        int levelup_exp = get_player_levelup_exp();
        while (m_exp >= levelup_exp && m_level < MAX_LEVEL)
        {
            is_level_up = true;

            m_exp -= levelup_exp;
            ++m_level;

            update_level_date();
            levelup_exp = get_player_levelup_exp();
        }

#ifdef GAME_SERVER
        // update to client
        vector<uint64> para;
        para.push_back(get_owner_id());
        para.push_back(m_database_id);
        para.push_back(change);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_change_exp",para);

        // save db
        para.clear();
        para.push_back(m_database_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_deputy_general_exp",para);
        if (is_level_up)
        {
            // save db
            Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_deputy_general_level",para);
        }
#else
        if (is_level_up)
        {
            int out = 0;
            //Game_Utils::instance()->play_continued_effect(m_database_id,"3003",out);//副将升级 由于特效是一次性的变量out不用处理
//			AI_UTils::instance()->add_effect_to_scene("2016");//by liaopengfei 20131123 策划做成了一个场景特效
        }
#endif
    }

    int DeputyGeneral::get_face_mode_id()
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

    int DeputyGeneral::get_model()
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