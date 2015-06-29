
#ifndef __COOL_TIME_H__
#define __COOL_TIME_H__

#include <list>
#include <map>

#include "Network_Common/global_macros.h"
#include "Game_Interface/common.h"
#include "Cool_Time_Config_Data.h"
#include "Cool_Time_Config_Mgr.h"

#ifdef YN_LINUX
#include <string.h>
#endif

using namespace std;
namespace Game_Data
{
    struct Cool_Time
    {
        Cool_Time()
        {
            reset();
        }

        ~Cool_Time()
        {
            reset();
        }

        void reset()
        {
            id_ = 0;                       
            config_ = NULL;
            cool_ = 0;                        
            check_ = 0;                     
            length_ = 0;
        }

        uint64			    id_;			// 数据库ID
        int			        role_id_;	    // 角色ID
        cool_time_config*	config_;        // 表数据
        int			        cool_;		    // 是否冷却(1为冷却中)
        int			        check_;		    // 检测时间点(秒)
        int			        length_;	    // 时间累加长度(秒)
    };

    typedef map<uint64, Cool_Time*>         Cool_Time_Map;
    typedef Cool_Time_Map::iterator	        Cool_Time_Map_Iter;

    typedef list<Cool_Time*>                 Cool_Time_List;
    typedef Cool_Time_List::iterator         Cool_Time_List_Iter;
}

#endif /* __COOL_TIME_H__ */

