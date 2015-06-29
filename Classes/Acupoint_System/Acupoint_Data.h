
#ifndef __ACUPOINT_H__
#define __ACUPOINT_H__

#include <list>
#include <map>

#include "Network_Common/global_macros.h"
#include "Game_Interface/common.h"

#ifdef YN_LINUX
#include <string.h>
#endif

using namespace std;
namespace Game_Data
{
    struct Acupoint
    {
        Acupoint()
        {
            reset();
        }

        ~Acupoint()
        {
            reset();
        }

        void reset()
        {
            id_ = 0;                       
            role_id_ = 0;
            type_ = 0;                        
            level_ = 0;                     
            pos_ = 0;
            rate_ = 0;
        }

        uint64                  id_;                            // 数据库ID
        int                     role_id_;                       // 角色ID
        int                     type_;                          // 脉络类型
        int                     level_;                         // 层级
        int                     pos_;                           // 当前穴位
        int                     rate_;                          // 额外成功率
    };

    typedef map<uint64, Acupoint*>          Acupoint_Map;
    typedef Acupoint_Map::iterator	        Acupoint_Map_Iter;

    typedef list<Acupoint*>                 Acupoint_List;
    typedef Acupoint_List::iterator         Acupoint_List_Iter;
}

#endif /* __ACUPOINT_H__ */

