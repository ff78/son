
#ifndef __ACTIVITY_RECORD_MGR_H__
#define __ACTIVITY_RECORD_MGR_H__

#include "Game_Interface/common.h"
#include "Activity_Record_Data.h"

class message_stream;
namespace Game_Data
{
    class Player;
    class Activity_Record_Mgr
    {
    public:
        Activity_Record_Mgr();
        virtual ~Activity_Record_Mgr();

        static Activity_Record_Mgr* instance();

        void release();

        void load_activity_record(message_stream& ms);
        activity_record& get_activity_record(){return activity_record_;}
        
        int get_six_sect_join_count(int type);

    private:
        static Activity_Record_Mgr*     instance_;

        activity_record                 activity_record_;
    };
}


typedef Game_Data::Activity_Record_Mgr ACTIVITY_RECORD_MGR;


#endif /* __ACTIVITY_RECORD_MGR_H__ */
