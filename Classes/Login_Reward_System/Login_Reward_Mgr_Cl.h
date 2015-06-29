
#ifndef __LOGIN_REWARD_MGR_H__
#define __LOGIN_REWARD_MGR_H__

#include "Login_Reward_Config_Data.h"
#include "Login_Reward_Data.h"

class message_stream;
namespace Game_Data
{
    class Login_Reward_Mgr
    {
    public:
        Login_Reward_Mgr();
        virtual ~Login_Reward_Mgr();

        static Login_Reward_Mgr* instance();

        void release();

    public:
        void load_login_reward(message_stream& ms);
        Login_Reward& get_login_reward(){return login_reward_;}

        bool is_can_get_login_reward();

    private:
        static Login_Reward_Mgr*        instance_;

        Login_Reward                    login_reward_;
    };
}

typedef Game_Data::Login_Reward_Mgr LOGIN_REWARD_MGR;


#endif /* __LOGIN_REWARD_MGR_H__ */
