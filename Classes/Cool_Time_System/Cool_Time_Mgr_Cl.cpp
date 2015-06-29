
#include "Cool_Time_Mgr_Cl.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Network_Common/message_stream.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"

#include "Game_Interface/game_event_response.h"

#ifdef YN_LINUX
#include <string.h>
#endif


namespace Game_Data
{
    Cool_Time_Mgr* Cool_Time_Mgr::instance_ = NULL;
    Cool_Time_Mgr::Cool_Time_Mgr()
    {
        _scheduler->scheduleSelector(schedule_selector(Cool_Time_Mgr::update_count_down), this, 1, kRepeatForever, 0, false);
    }

    Cool_Time_Mgr::~Cool_Time_Mgr()
    {

    }

    Cool_Time_Mgr* Cool_Time_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Cool_Time_Mgr;
        }

        return instance_;
    }

    void Cool_Time_Mgr::release()
    {
        Cool_Time* cool_time = NULL;
        Cool_Time_Map_Iter iter = cool_time_map_.begin();
        for (;iter != cool_time_map_.end();++iter)
        {
            cool_time = iter->second;
            if (cool_time)
            {
                delete cool_time;
            }
        }
        
        cool_time_map_.clear();
    }

    void Cool_Time_Mgr::load_cool_time(Player* player,message_stream& ms)
    {
        int count = 0;
        ms >> count;

        Cool_Time* cool_time = NULL;
        int type = 0;
        for (int i = 0; i < count; ++i)
        {
            cool_time = new Cool_Time;
            ms >> cool_time->id_;
            ms >> cool_time->role_id_;
            ms >> type;
            ms >> cool_time->cool_;
            ms >> cool_time->check_;
            ms >> cool_time->length_;

            cool_time->config_ = COOL_TIME_CONFIG_MGR::instance()->get_cool_time_config(type);

            insert_cool_time(cool_time);
            //player->insert_cool_time(cool_time);
        }
    }

    void Cool_Time_Mgr::create_cool_time(Player* player,message_stream& ms)
    {
        int type = 0;
        Cool_Time* cool_time = new Cool_Time;
        ms >> cool_time->id_;
        ms >> cool_time->role_id_;
        ms >> type;
        ms >> cool_time->cool_;
        ms >> cool_time->check_;
        ms >> cool_time->length_;

        cool_time->config_ = COOL_TIME_CONFIG_MGR::instance()->get_cool_time_config(type);

        insert_cool_time(cool_time);
        //player->insert_cool_time(cool_time);
    }

    void Cool_Time_Mgr::insert_cool_time(Cool_Time* cool_time)
    {
        if (cool_time)
        {
            cool_time_map_.insert(make_pair(cool_time->config_->type_,cool_time));
        }
    }

    void Cool_Time_Mgr::remove_cool_time(int type)
    {
        Cool_Time_Map_Iter iter = cool_time_map_.find(type);
        if (iter != cool_time_map_.end())
        {
            cool_time_map_.erase(iter);
        }
    }

    Cool_Time* Cool_Time_Mgr::get_cool_time(int type)
    {
        Cool_Time* cool_time = NULL;
        Cool_Time_Map_Iter iter = cool_time_map_.find(type);
        if (iter != cool_time_map_.end())
        {
            cool_time = iter->second;
        }

        return cool_time;
    }

    bool Cool_Time_Mgr::is_cool(Cool_Time* cool_time)
    {
        if (cool_time->cool_ == 0)
        {
            return false;
        }

        return true;
    }

    bool Cool_Time_Mgr::is_need_clean(Cool_Time* cool_time)
    {
        if (cool_time->length_ == 0)
        {
            return false;
        }

        return true;
    }

    void Cool_Time_Mgr::add_length(Cool_Time* cool_time)
    {
        if (!cool_time->config_)
        {
            return;
        }

        if(cool_time->length_ == 0)
        {
            cool_time->check_ = (int)time(NULL);
        }

        cool_time->length_ += cool_time->config_->add_time_;
        if(cool_time->length_ >= cool_time->config_->over_)
        {
            cool_time->cool_ = 1;
        }

    }

    void Cool_Time_Mgr::change_length(Cool_Time* cool_time,int len)
    {
        int old_length = cool_time->length_;
        if (len > 0)
        {
            if ((JIE_JI_INT_MAX-len) <= old_length)
            {
                len = JIE_JI_INT_MAX - old_length;
            }
        }
        else if (len < 0)
        {
            if (old_length < (-len))
            {
                len = -old_length;
            }
        }
        else
        {
            return;
        }

        if(cool_time->length_ == 0)
        {
            cool_time->check_ = (int)time(NULL);
        }

        cool_time->length_ = old_length+len;
        if (cool_time->length_ == 0)
        {
            cool_time->cool_ = 0;
        }
        else
        {
            if(cool_time->length_ >= cool_time->config_->over_)
            {
                cool_time->cool_ = 1;
            }
        }
    }

    void Cool_Time_Mgr::clean_cool_time(Cool_Time* cool_time)
    {
        cool_time->cool_ = 0;
        cool_time->check_ = 0;
        cool_time->length_ = 0;
    }

    int Cool_Time_Mgr::get_clean_cool_time_cost(Cool_Time* cool_time)
    {
        int dest = (cool_time->length_%cool_time->config_->interval_ == 0)?0:1;
        int cost = (cool_time->length_/cool_time->config_->interval_+dest)*cool_time->config_->unit_cost_;

        return cost;
    }

    void Cool_Time_Mgr::update_count_down(float dt)
    {
        Cool_Time* cool_time = NULL;
        Cool_Time_Map_Iter iter = cool_time_map_.begin();
        for (;iter != cool_time_map_.end();++iter)
        {
            cool_time = iter->second;
            if (!cool_time)
            {
                continue;
            }

            if (cool_time->length_ > 0)
            {
                --(cool_time->length_);
                int role_id = Account_Data_Mgr::instance()->get_current_role_id();
                Game_Logic::Game_Event_Response::instance()->on_update_count_down_time(role_id,cool_time->length_);
                if (cool_time->length_ == 0)
                {
                    cool_time->cool_ = 0;
                    cool_time->check_ = 0;
                }
            }
        }
    }
}

