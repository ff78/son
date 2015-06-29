
#ifndef __LOGIN_REWARD_CONFIG_DATA_H__
#define __LOGIN_REWARD_CONFIG_DATA_H__


#include <string>
#include <map>

using namespace std;
namespace Game_Data
{
    struct login_reward_config
    {
        login_reward_config()
        {
            reset();
        }

        ~login_reward_config()
        {
            reset();
        }

        void reset()
        {
            base_id_ = 0;
            reward_id_ = 0;
        }

        int                     base_id_;               // 
        int                     reward_id_;             // 
    };

    typedef map<int,login_reward_config*>                   login_reward_config_map;
    typedef login_reward_config_map::iterator	            login_reward_config_map_iter;
}

#endif /* __LOGIN_REWARD_CONFIG_DATA_H__ */

