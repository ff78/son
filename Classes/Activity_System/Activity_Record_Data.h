
#ifndef __ACTIVITY_RECORD_DATA_H__
#define __ACTIVITY_RECORD_DATA_H__

#define SIX_SECT_COUNT  6

#include <string>
#include <map>

using namespace std;
namespace Game_Data
{
    struct activity_record
    {
        activity_record()
        {
            reset();
        }

        ~activity_record()
        {
            reset();
        }

        void reset()
        {
            role_id_ = 0;
            memset(six_sect_record_,0,sizeof(six_sect_record_));
        }

        int                     role_id_;                            //
        int                     six_sect_record_[SIX_SECT_COUNT];    //
    };

    typedef map<int,activity_record*>               activity_record_map;
    typedef activity_record_map::iterator	        activity_record_map_iter;
}

#endif /* __ACTIVITY_RECORD_DATA_H__ */

