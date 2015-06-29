
#include "Acupoint_Mgr_Cl.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Network_Common/message_stream.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"

#include "Game_Interface/game_event_response.h"

#include "Common/GameDefine.h"

#ifdef YN_LINUX
#include <string.h>
#endif


namespace Game_Data
{
    Acupoint_Mgr* Acupoint_Mgr::instance_ = NULL;
    Acupoint_Mgr::Acupoint_Mgr()
    {

    }

    Acupoint_Mgr::~Acupoint_Mgr()
    {

    }

    Acupoint_Mgr* Acupoint_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Acupoint_Mgr;
        }

        return instance_;
    }

    void Acupoint_Mgr::release()
    {
        Acupoint* acupoint = NULL;
        Acupoint_Map_Iter iter = acupoint_map_.begin();
        for (;iter != acupoint_map_.end();++iter)
        {
            acupoint = iter->second;
            if (acupoint)
            {
                delete acupoint;
            }
        }
        
        acupoint_map_.clear();
    }

    void Acupoint_Mgr::load_acupoint(Player* player,message_stream& ms)
    {
        int count = 0;
        ms >> count;

        Acupoint* acupoint = NULL;
        for (int i = 0; i < count; ++i)
        {
            acupoint = new Acupoint;
            ms >> acupoint->id_;
            ms >> acupoint->role_id_;
            ms >> acupoint->type_;
            ms >> acupoint->level_;
            ms >> acupoint->pos_;
            ms >> acupoint->rate_;

            insert_acupoint(acupoint);
            player->insert_acupoint(acupoint);
        }
    }

    void Acupoint_Mgr::open_acupoint(Player* player,message_stream& ms)
    {
        int type = 0;
        int level = 0;
        int pos = 0;
        int rate = 0;
        ms >> type;
        ms >> level;
        ms >> pos;
        ms >> rate;

        Acupoint* acupoint = get_acupoint(type);
        if (acupoint)
        {
            acupoint->level_ = level;
            acupoint->pos_ = pos;
            acupoint->rate_ = rate;
            if (rate > 0)
            {
                DICTIONARY_CONFIG_MGR::instance()->show_alert(TIPS_OPEN_ACUPOINT_FAILED);
            }
        }
    }

    void Acupoint_Mgr::create_acupoint(Player* player,message_stream& ms)
    {
        Acupoint* acupoint = new Acupoint;
        ms >> acupoint->id_;
        ms >> acupoint->role_id_;
        ms >> acupoint->type_;
        ms >> acupoint->level_;
        ms >> acupoint->pos_;
        ms >> acupoint->rate_;

        insert_acupoint(acupoint);
        player->insert_acupoint(acupoint);
    }

    void Acupoint_Mgr::insert_acupoint(Acupoint* acupoint)
    {
        if (acupoint)
        {
            acupoint_map_.insert(make_pair(acupoint->type_,acupoint));
        }
    }

    void Acupoint_Mgr::remove_acupoint(int type)
    {
        Acupoint_Map_Iter iter = acupoint_map_.find(type);
        if (iter != acupoint_map_.end())
        {
            acupoint_map_.erase(iter);
        }
    }

    Acupoint* Acupoint_Mgr::get_acupoint(int type)
    {
        Acupoint* acupoint = NULL;
        Acupoint_Map_Iter iter = acupoint_map_.find(type);
        if (iter != acupoint_map_.end())
        {
            acupoint = iter->second;
        }

        return acupoint;
    }
}

