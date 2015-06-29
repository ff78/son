

#ifndef __LOGIN_REWARD_H__
#define __LOGIN_REWARD_H__

#include <map>

#include "Network_Common/global_macros.h"

#ifdef YN_LINUX
#include <string.h>
#endif

using namespace std;
namespace Game_Data
{
    struct Login_Reward
    {
        Login_Reward()
        {
            reset();
        }

        ~Login_Reward()
        {
            reset();
        }

        void reset()
        {
            role_id_ = 0;                       
            is_continuous_ = 0;
            continuous_count_ = 0;
            memset(got_flag_,0,sizeof(got_flag_));
        }

        int                     role_id_;                   // ��ɫID
        int                     is_continuous_;              // �Ƿ���������¼
        int                     continuous_count_;          // ������¼����
        int			            got_flag_[WEEK_DAY];         // ��ȡ�������
    };

    typedef map<int, Login_Reward*>         Login_Reward_Map;
    typedef Login_Reward_Map::iterator	    Login_Reward_Map_Iter;
}

#endif /* __LOGIN_REWARD_H__ */

