
//#include <fstream>
#ifdef YN_LINUX
#include <string.h>
#endif

#include "Activity_Record_Mgr_Cl.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Network_Common/message_stream.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Activity_System/Activity_Config_Mgr.h"

namespace Game_Data
{
    Activity_Record_Mgr* Activity_Record_Mgr::instance_ = NULL;
    Activity_Record_Mgr::Activity_Record_Mgr()
    {

    }

    Activity_Record_Mgr::~Activity_Record_Mgr()
    {

    }

    Activity_Record_Mgr* Activity_Record_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Activity_Record_Mgr;
        }

        return instance_;
    }

    void Activity_Record_Mgr::release()
    {
        activity_record_.reset();
    }

    void Activity_Record_Mgr::load_activity_record(message_stream& ms)
    {
        activity_record_.reset();

        ms >> activity_record_.role_id_;
        for (int i = 0;i < SIX_SECT_COUNT;++i)
        {
            ms >> activity_record_.six_sect_record_[i];
        }
    }

    int Activity_Record_Mgr::get_six_sect_join_count(int type)
    {
        return activity_record_.six_sect_record_[type];
    }
}