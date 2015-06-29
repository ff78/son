
#include "Instance_Sweep_Data_Mgr.h"
#include "Instance_Data_Mgr.h"

#include "Character_System/Player.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Network_Common/message_stream.h"
#include "Play_System/Formula_Function_Instance.h"
#include "Item_System/Item_Desc_Config_Mgr.h"

#include "Common/GameDefine.h"

#include "UI_Interface/UI_ModalDialogue_Layer.h"
#include "Game_Interface/event_define.h"
#include "Game_Interface/game_event_response.h"
#include "Game_Interface/game_content_interface.h"

#ifdef YN_LINUX
#include <string.h>
#endif


namespace Game_Data
{
    Instance_Sweep_Data_Mgr* Instance_Sweep_Data_Mgr::instance_ = NULL;
    Instance_Sweep_Data_Mgr::Instance_Sweep_Data_Mgr()
    {
        reset();
    }

    Instance_Sweep_Data_Mgr::~Instance_Sweep_Data_Mgr()
    {
        reset();
    }

    Instance_Sweep_Data_Mgr* Instance_Sweep_Data_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Instance_Sweep_Data_Mgr;
        }

        return instance_;
    }

    void Instance_Sweep_Data_Mgr::reset()
    {
        is_elite_instance_ = 0;
        all_sweep_count_ = 0;
        cur_sweep_count_ = 0;
        is_keep_sweep_ = false;
        for (int i = 0;i < 3;++i)
        {
            instance_sweep_data_[i].reset();
        }
    }

    bool Instance_Sweep_Data_Mgr::is_have_enough_energy()
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return false;
        }

        int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
        vector<uint> para;
        Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute","began_content","energyconsume",para);
        if ( para.size() <= 0)
        {
            return false;
        }

        if (player->get_energy() < (int)para[0])
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_ENERGY);
            return false;
        }

        return true;
    }

    bool Instance_Sweep_Data_Mgr::is_have_enough_bag_room()
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return false;
        }

        if (player->get_bag_empty_count() == 0)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(COPY_BAG_NOT_ENOUGH);
            return false;
        }

        return true;
    }

    void Instance_Sweep_Data_Mgr::set_award(message_stream& ms)
    {
        int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
        if (is_elite_instance_ == 1)
        {
            instance_id = Formula_Function_Instance::instance()->get_elite_instance_id(instance_id);
        }

        vector<uint> para;
        Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute","result_content","award_exp_compute",para);
        if ( para.size() > 0)
        {
            instance_sweep_data_[cur_sweep_count_].award_exp_ = (int)para[0];
        }

        para.clear();
        Formula_Function_Instance::instance()->get_para_list_from_instance_data(instance_id, "instance_attribute","result_content","award_money",para);
        if ( para.size() > 0)
        {
            instance_sweep_data_[cur_sweep_count_].award_gold_ = (int)para[0];
        }

        int item_type_count = 0;
        int item_id = 0;
        int item_count = 0;
        ms >> item_type_count;
        for (int i = 0;i < item_type_count; ++i)
        {
            ms >> item_id;
            ms >> item_count;
            instance_sweep_data_[cur_sweep_count_].set_award_item(item_id,item_count);
        }

        instance_sweep_data_[cur_sweep_count_].flag_ = 1;

        ++cur_sweep_count_;
        if (cur_sweep_count_ >= all_sweep_count_)
        {
            is_keep_sweep_ = false;
        }
    }

    void Instance_Sweep_Data_Mgr::start_sweep(int count,int is_elite_instance)
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        if (is_have_enough_energy() == false)
        {
            return;
        }

        if (is_keep_sweep_)
        {
            return;
        }

        //check bag room
        
        reset();
        is_elite_instance_ = is_elite_instance;
        all_sweep_count_ = count;
        is_keep_sweep_ = true;

        int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
        if (player->get_bag_empty_count() == 0)
        {
            const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SWEEP_INSTANCE_BAG_FULL);
            UI_ModalDialogue_Layer::DoModal("",szString,UI_ModalDialogue_Layer::DT_YES_NO,[=]()
            {
                vector<uint64> param;
                param.push_back(instance_id);
                param.push_back(is_elite_instance_);
                Game_Logic::Game_Content_Interface::instance()->exec_interface("send_instance_sweep", param);            
            }
            );
        }
        else
        {
            vector<uint64> param;
            param.push_back(instance_id);
            param.push_back(is_elite_instance_);
            Game_Logic::Game_Content_Interface::instance()->exec_interface("send_instance_sweep", param);
        }
    }
}