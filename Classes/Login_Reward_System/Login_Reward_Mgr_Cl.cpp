
#include "Login_Reward_Mgr_Cl.h"

#include "Character_System/Player.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Network_Common/message_stream.h"

#include "Game_Interface/event_define.h"
#include "Game_Interface/game_event_response.h"

#ifdef YN_LINUX
#include <string.h>
#endif


namespace Game_Data
{
    Login_Reward_Mgr* Login_Reward_Mgr::instance_ = NULL;
    Login_Reward_Mgr::Login_Reward_Mgr()
    {
        login_reward_.reset();
    }

    Login_Reward_Mgr::~Login_Reward_Mgr()
    {
        login_reward_.reset();
    }

    Login_Reward_Mgr* Login_Reward_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Login_Reward_Mgr;
        }

        return instance_;
    }

    void Login_Reward_Mgr::release()
    {
        login_reward_.reset();
    }

    void Login_Reward_Mgr::load_login_reward(message_stream& ms)
    {
        login_reward_.reset();

        ms >> login_reward_.role_id_;
        ms >> login_reward_.is_continuous_;
        ms >> login_reward_.continuous_count_;
        for (int i = 0;i < WEEK_DAY;++i)
        {
            ms >> login_reward_.got_flag_[i];
        }
    }

    bool Login_Reward_Mgr::is_can_get_login_reward()
    {
        for (int i = 0; i < login_reward_.continuous_count_ ; ++i)
        {
            if (login_reward_.got_flag_[i] == 0)
            {
                return true;
            }
        }

        return false;
    }
}

