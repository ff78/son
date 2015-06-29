

#ifndef __SHOPING_RECORD_DATA_H__
#define __SHOPING_RECORD_DATA_H__


#include <string>
#include <map>

using namespace std;
namespace Game_Data
{
    struct shoping_record
    {
        shoping_record()
        {
            reset();
        }

        ~shoping_record()
        {
            reset();
        }

        void reset()
        {
            goods_id_ = 0;
            buy_count_ = 0;
            check_point_ = 0;
        }

        int                     goods_id_;      //
        int                     buy_count_;     //
        int                     check_point_;   //
    };

    typedef map<int,shoping_record*>                shoping_record_map;
    typedef shoping_record_map::iterator	        shoping_record_map_iter;
}

#endif /* __SHOPING_RECORD_DATA_H__ */

