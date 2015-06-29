

#ifndef __LOGIN_REWARD_CONFIG_MGR_H__
#define __LOGIN_REWARD_CONFIG_MGR_H__

#include "Game_Interface/common.h"
#include "Login_Reward_Config_Data.h"

namespace Game_Data
{
    class Login_Reward_Config_Mgr
    {
    public:
        Login_Reward_Config_Mgr();
        virtual ~Login_Reward_Config_Mgr();

        static Login_Reward_Config_Mgr* instance();

        int initialize();
        int release();

        login_reward_config* get_login_reward_config(int type);

    private:
        int load_login_reward_config();

    private:
        static Login_Reward_Config_Mgr*         instance_;

        login_reward_config_map                 login_reward_config_map_;
    };
}


typedef Game_Data::Login_Reward_Config_Mgr LOGIN_REWARD_CONFIG_MGR;


#endif /* __LOGIN_REWARD_CONFIG_MGR_H__ */
