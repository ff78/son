
#include "Item_Mgr_Cl.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Network_Common/message_stream.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player_Config_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Item_Container_System/Item_Container_Mgr_Cl.h"
#include "Play_System/Instance_Data_Mgr.h"
#include "Event_System/event_system_data_mgr.h"

//#include "UI_Interface/UI_Instance_Layer.h"
#include "UI_Interface/UI_MainMenu_Layer.h"

#include "Common/GameDefine.h"

#include "Game_Interface/game_event_response.h"

#ifdef YN_LINUX
#include <string.h>
#endif


namespace Game_Data
{
    Item_Mgr* Item_Mgr::instance_ = NULL;
    Item_Mgr::Item_Mgr()
    :m_is_load_item(false),
    m_is_load_material_fragment(false),
    m_is_load_book_fragment(false)
    {

    }

    Item_Mgr::~Item_Mgr()
    {

    }

    Item_Mgr* Item_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Item_Mgr;
        }

        return instance_;
    }

    void Item_Mgr::release()
    {
        Item* item = NULL;
        Item_Map_Iter iter = m_map_item.begin();
        for (;iter != m_map_item.end();++iter)
        {
            item = iter->second;
            if (item)
            {
                delete item;
            }
        }

        item = NULL;
        iter = m_map_material_fragment.begin();
        for (;iter != m_map_material_fragment.end();++iter)
        {
            item = iter->second;
            if (item)
            {
                delete item;
            }
        }

        item = NULL;
        iter = m_map_book_fragment.begin();
        for (;iter != m_map_book_fragment.end();++iter)
        {
            item = iter->second;
            if (item)
            {
                delete item;
            }
        }

        m_map_item.clear();
        m_map_material_fragment.clear();
        m_map_book_fragment.clear();
        m_is_load_item = false;
        m_is_load_material_fragment = false;
        m_is_load_book_fragment = false;
    }

    void Item_Mgr::load_item(Player* player,message_stream& ms)
    {
        m_is_load_item = true;
        int item_count = 0;
        ms >> item_count;

        Item* item = NULL;
        int base_id = 0;
        for (int i = 0; i < item_count; ++i)
        {
            item = new Item;
            memset(item,0,sizeof(Item));
            ms >> item->id;
            ms >> item->container_id;
            ms >> item->character_id;
            ms >> item->general_id;
            ms >> base_id;
            ms >> item->is_bind;
            ms >> item->bar_pos;
            ms >> item->level;
            ms >> item->exp;
            ms >> item->current_quality;
            ms >> item->count;
            ms >> item->get_time_point;
            ms >> item->use_time_point;
            ms >> item->create_way;
            ms >> item->destroy_way;
            for (int i = 0;i < SET_GEM_COUNT;++i)
            {
                ms >> item->gem_id[i];
            }

            item->config = ITEM_CONFIG_MGR::instance()->get_item_config(base_id);

            m_map_item.insert(make_pair(item->id,item));
            player->insert_item(item);
            if (item->general_id > 0)
            {
                Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(item->general_id);
                if (character)
                {
                    character->set_bar_item(item);
                }
            }
        }

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
    }

    void Item_Mgr::load_material_fragment(Player* player,message_stream& ms)
    {
        m_is_load_material_fragment = true;
        int fragment_count = 0;
        ms >> fragment_count;

        Item* item = NULL;
        int base_id = 0;
        for (int i = 0; i < fragment_count; ++i)
        {
            item = new Item;
            memset(item,0,sizeof(Item));
            ms >> item->id;
            ms >> item->container_id;
            ms >> item->character_id;
            ms >> item->general_id;
            ms >> base_id;
            ms >> item->is_bind;
            ms >> item->bar_pos;
            ms >> item->level;
            ms >> item->exp;
            ms >> item->current_quality;
            ms >> item->count;
            ms >> item->get_time_point;
            ms >> item->use_time_point;
            ms >> item->create_way;
            ms >> item->destroy_way;

            item->config = ITEM_CONFIG_MGR::instance()->get_item_config(base_id);

            m_map_material_fragment.insert(make_pair(item->config->base_id,item));
            player->insert_material_fragment(item);
        }

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
    }

    void Item_Mgr::load_book_fragment(Player* player,message_stream& ms)
    {
        m_is_load_book_fragment = true;
        int fragment_count = 0;
        ms >> fragment_count;

        Item* item = NULL;
        int base_id = 0;
        for (int i = 0; i < fragment_count; ++i)
        {
            item = new Item;
            memset(item,0,sizeof(Item));
            ms >> item->id;
            ms >> item->container_id;
            ms >> item->character_id;
            ms >> item->general_id;
            ms >> base_id;
            ms >> item->is_bind;
            ms >> item->bar_pos;
            ms >> item->level;
            ms >> item->exp;
            ms >> item->current_quality;
            ms >> item->count;
            ms >> item->get_time_point;
            ms >> item->use_time_point;
            ms >> item->create_way;
            ms >> item->destroy_way;

            item->config = ITEM_CONFIG_MGR::instance()->get_item_config(base_id);

            m_map_book_fragment.insert(make_pair(item->config->base_id,item));
            player->insert_book_fragment(item);
        }

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
    }

    void Item_Mgr::equip_equipment(Player* player,message_stream& ms)
    {
        int character_id = 0;
        int index = 0;
        ms >> character_id;
        ms >> index;

        Character* character = CHARACTER_MGR::instance()->get_character(character_id);
        if (!character)
        {
            return;
        }

        Item_Container* container = player->get_container_from_bag(index);
        if (!container)
        {
            return;
        }

        Item* item = get_item(container->item_id);
        if (!item)
        {
            return;
        }

        container->is_num_type = 0;
        container->item_id = 0;
        container->item_count = 0;

        Equipment_Config* config = reinterpret_cast<Equipment_Config*>(item->config);
        int pos = config->pos;
        Item* equipped = character->get_item_from_equipment_bar(pos);
        if (equipped)
        {
            container->is_num_type = 0;
            container->item_id = equipped->id;
            container->item_count = 1;

            equipped->bar_pos = 0;
            equipped->general_id = 0;
            equipped->container_id = container->id;
        } 

        item->bar_pos = pos;
        item->general_id = character->get_database_character_id();
        item->container_id = 0;
        character->set_bar_item(item);
        if (config->bind == IBS_USED_BIND)
        {
            item->is_bind = 1;
        }

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
        Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());
    }

    void Item_Mgr::take_off_equipmen(Player* player,message_stream& ms)
    {
        int character_id = 0;
        int index = 0;
        ms >> character_id;
        ms >> index;

        Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(character_id);
        if (!character)
        {
            return ;
        }

        Item* equipped = character->get_item_from_equipment_bar(index);
        if (!equipped)
        {
            return;
        }

        Game_Data::Item_Container* empty = player->get_empty_bag_container();
        if (!empty)
        {
            return;
        }

        empty->is_num_type = 0;
        empty->item_id = equipped->id;
        empty->item_count = 1;

        character->clear_bar_item(IT_EQUIPMENT,equipped->bar_pos);
        equipped->bar_pos = 0;
        equipped->general_id = 0;
        equipped->container_id = empty->id;

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
        Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());
    }

    void Item_Mgr::equip_book(Player* player,message_stream& ms)
    {
        int character_id = 0;
        int index = 0;
        int pos = 0;
        ms >> character_id;
        ms >> index;
        ms >> pos;

        Character* character = CHARACTER_MGR::instance()->get_character(character_id);
        if (!character)
        {
            return;
        }

        Item_Container* container = player->get_container_from_bag(index);
        if (!container)
        {
            return;
        }

        Item* item = get_item(container->item_id);
        if (!item)
        {
            return;
        }

        container->is_num_type = 0;
        container->item_id = 0;
        container->item_count = 0;

        Item* equipped = character->get_item_from_book_bar(pos);
        if (equipped)
        {
            container->is_num_type = 0;
            container->item_id = equipped->id;
            container->item_count = 1;

            equipped->bar_pos = 0;
            equipped->general_id = 0;
            equipped->container_id = container->id;
        } 

        item->bar_pos = pos;
        item->general_id = character->get_database_character_id();
        item->container_id = 0;
        character->set_bar_item(item);
        if (item->config->bind == IBS_USED_BIND)
        {
            item->is_bind = 1;
        }

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
        Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());
    }

    void Item_Mgr::take_off_book(Player* player,message_stream& ms)
    {
        int character_id = 0;
        int index = 0;
        ms >> character_id;
        ms >> index;

        Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(character_id);
        if (!character)
        {
            return ;
        }

        Item* equipped = character->get_item_from_book_bar(index);
        if (!equipped)
        {
            return;
        }

        Game_Data::Item_Container* empty = player->get_empty_bag_container();
        if (!empty)
        {
            return;
        }

        empty->is_num_type = 0;
        empty->item_id = equipped->id;
        empty->item_count = 1;

        character->clear_bar_item(IT_BOOK,equipped->bar_pos);
        equipped->bar_pos = 0;
        equipped->general_id = 0;
        equipped->container_id = empty->id;

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
        Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());
    }

    void Item_Mgr::equipment_level_up(Player* player,message_stream& ms)
    {
        uint64 item_id = 0;
        ms >> item_id;
        Item* item = get_item(item_id);
        if (!item)
        {
            return;
        }

        int up_level = 0;
        ms >> up_level;
        item->level += up_level;

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
        Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());

        //DICTIONARY_CONFIG_MGR::instance()->show_alert(EQUIPMENT_INTENSIFY_SUCCESS);

        //Game_Utils::instance()->add_effect_to_scene("2018");//装备强化
    }

    void Item_Mgr::equipment_quality_up(Player* player,message_stream& ms)
    {
        uint64 item_id = 0;
        ms >> item_id;
        Item* item = get_item(item_id);
        if (!item)
        {
            return;
        }

        remove_quality_upgrade_need_material(player,Game_Data::QMT_EQUIPMENT,item->current_quality);

        item->current_quality++;

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
        Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());

        DICTIONARY_CONFIG_MGR::instance()->show_alert(QUALITY_UP_SUCCESS);

        //Game_Utils::instance()->add_effect_to_scene("2019");//装备升品
    }

    void Item_Mgr::book_level_up(Player* player,message_stream& ms)
    {
        uint64 up_item_id = 0;
        int up_level = 0;
        int surplus_exp = 0;
        ms >> up_item_id;
        ms >> up_level;
        ms >> surplus_exp;
        Item* item = get_item(up_item_id);
        if (item)
        {
            item->level += up_level;
            item->exp = surplus_exp;
        }

        int count = 0;
        ms >> count;
        uint64 item_id = 0;
        for (int i = 0;i < count;++i)
        {
            ms >> item_id;
            item = ITEM_MGR::instance()->get_item(item_id);
            if (item)
            {
                if (item->general_id > 0)
                {
                    Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(item->general_id);
                    if (character)
                    {
                        character->clear_bar_item(IT_BOOK,item->bar_pos);
                        item->general_id = 0;
                        item->bar_pos = 0;
                    }
                }
                else
                {
                    if (item->container_id > 0)
                    {
                        Item_Container* container = player->get_item_container(item->container_id);
                        if (container)
                        {
                            container->is_num_type = 0;
                            container->item_id = 0;
                            container->item_count = 0;
                        }
                    }
                }

                item->destroy_way = IDW_MAKE;
                // delete
            }
        }

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
        Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());

        DICTIONARY_CONFIG_MGR::instance()->show_alert(COMBINE_SUCCESS);

        //Game_Utils::instance()->add_effect_to_scene("2017");//心法合成
    }

    void Item_Mgr::book_quality_up(Player* player,message_stream& ms)
    {
        uint64 item_id = 0;
        ms >> item_id;
        Item* item = get_item(item_id);
        if (!item)
        {
            return;
        }

        remove_quality_upgrade_need_material(player,Game_Data::QMT_BOOK,item->current_quality);

        item->current_quality ++;
        item->level = 1;

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
        Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());

        DICTIONARY_CONFIG_MGR::instance()->show_alert(QUALITY_UP_SUCCESS);

        //Game_Utils::instance()->add_effect_to_scene("2019");//心法升品
    }

    void Item_Mgr::sell_item(Player* player,message_stream& ms)
    {
        uint64 container_id = 0;
        int sell_count = 0;
        ms >> container_id;
        ms >> sell_count;

        Item_Container* container = ITEM_CONTAINER_MGR::instance()->get_item_container(container_id);
        if (!container)
        {
            return;
        }

        if (container->is_num_type == 0)
        {
            Item* item = ITEM_MGR::instance()->get_item(container->item_id);
            if (item)
            {
                item->destroy_way = IDW_SELL;
                // delete
            }
        }
        
        container->item_count -= sell_count;
        if (container->item_count == 0)
        {
            container->is_num_type = 0;
            container->item_id = 0;
        }

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
    }

    void Item_Mgr::use_item(Player* player,message_stream& ms)
    {
        uint64 container_id = 0;
        int item_base_id = 0;
        ms >> container_id;

        Item_Container* container = ITEM_CONTAINER_MGR::instance()->get_item_container(container_id);
        if (!container)
        {
            return;
        }

        if (container->is_num_type == 0)
        {
            Item* item = ITEM_MGR::instance()->get_item(container->item_id);
            if (item)
            {
                item_base_id = item->config->base_id;
                item->count -= 1;
                if (item->count == 0)
                {
                    container->item_id = 0;
                    item->destroy_way = IDW_USED;
                    // delete
                }
            }
        }
        else
        {
            item_base_id = (int)container->item_id;
            container->item_count -= 1;
            if (container->item_count == 0)
            {
                container->is_num_type = 0;
                container->item_id = 0;
            }
        }

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());

        Item_Config*config = ITEM_CONFIG_MGR::instance()->get_item_config(item_base_id);
        if (config == NULL || (config->type != IT_USABLE_ITEM && config->type != IT_GIFT_ITEM))
        {
            return;
        }

        Usable_Item_Config* usable_config = reinterpret_cast<Usable_Item_Config*>(config);
        if (!usable_config)
        {
            return;
        }

        if (usable_config->type == IT_GIFT_ITEM)
        {
            int gift_type = ITEM_CONFIG_MGR::instance()->get_gift_type(item_base_id);
            if (gift_type == 0)
            {
                return;
            }

            if (gift_type == GT_ALL)
            {
                Event_Data event_data;
                event_system_data_mgr::sharedInstance()->getEventDataById(usable_config->event_id,event_data);
                if(event_data.getId()==0)
                {
                    return;
                }

                std::string reward = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_U_GAIN);
                Game_Data::game_element_list_t ele_list;
                event_data.getFunction(ele_list);
                Game_Data::game_element_list_t::iterator itg;
                for( itg = ele_list.begin(); itg != ele_list.end(); ++ itg)
                {
                    Game_Data::Game_Element& element = (*itg);
                    if(strcmp(element.get_command(),"awarditem") == 0)
                    {
                        vector<uint> para;
                        element.get_para_list_in_vector( para);
                        if(para.size() > 1)
                        {
                            int item_base_id = para[0];
                            int item_count = para[1];

                            Game_Data::Item_Config* config = ITEM_CONFIG_MGR::instance()->get_item_config(item_base_id);
                            Item_Config* item_config = NULL;
                            if (config->type == IT_EQUIPMENT_DEPOT)
                            {
                                Equipment_Depot_Config* equipment_depot_config = reinterpret_cast<Equipment_Depot_Config*>(config);
                                item_config = ITEM_CONFIG_MGR::instance()->get_item_config(equipment_depot_config->item_base_id);
                            }
                            else
                            {
                                item_config = config;
                            }

                            if (item_config)
                            {
                                const char* format = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_GAIN_INFO);
                                const char* item_name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(item_config->name);
                                reward += CCString::createWithFormat(format,item_name,item_count)->getCString();
                            }
                        }
                    }
                }

                //Game_Utils::instance()->show_alert(reward.c_str());
            }
        }
        else
        {
            Event_Data event_data;
            event_system_data_mgr::sharedInstance()->getEventDataById(usable_config->event_id,event_data);
            if(event_data.getId()==0)
            {
                return;
            }

            std::string reward;
            Game_Data::game_element_list_t ele_list;
            event_data.getFunction(ele_list);
            Game_Data::game_element_list_t::iterator itg;
            for( itg = ele_list.begin(); itg != ele_list.end(); ++ itg)
            {
                Game_Data::Game_Element& element = (*itg);
                if(strcmp(element.get_command(),"award_gold") == 0)
                {
                    reward = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_U_GAIN);
                    vector<uint> para;
                    element.get_para_list_in_vector( para);
                    if(para.size() > 0)
                    {
                        int value = para[0];
                        const char* show = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_GOLD);
                        reward += CCString::createWithFormat("%d%s",value,show)->getCString();
                    }
                }
                else if(strcmp(element.get_command(),"award_token") == 0)
                {
                    reward = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_U_GAIN);
                    vector<uint> para;
                    element.get_para_list_in_vector( para);
                    if(para.size() > 0)
                    {
                        int value = para[0];
                        const char* show = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_YUANBAO);
                        reward += CCString::createWithFormat("%d%s",value,show)->getCString();
                    }
                }
                else if(strcmp(element.get_command(),"award_prestige") == 0)
                {
                    reward = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_U_GAIN);
                    vector<uint> para;
                    element.get_para_list_in_vector( para);
                    if(para.size() > 0)
                    {
                        int value = para[0];
                        const char* show = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ARENA_REPUTATION);
                        reward += CCString::createWithFormat("%d%s",value,show)->getCString();
                    }
                }
                else if(strcmp(element.get_command(),"award_feat") == 0)
                {
                    reward = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_U_GAIN);
                    vector<uint> para;
                    element.get_para_list_in_vector( para);
                    if(para.size() > 0)
                    {
                        int value = para[0];
                        const char* show = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SHOW_ENERGY);
                        reward += CCString::createWithFormat("%d%s",value,show)->getCString();
                    }
                }
                else if(strcmp(element.get_command(),"award_energy") == 0)
                {
                    reward = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_U_GAIN);
                    vector<uint> para;
                    element.get_para_list_in_vector( para);
                    if(para.size() > 0)
                    {
                        int value = para[0];
                        const char* show = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SHOW_ENERGY);
                        reward += CCString::createWithFormat("%d%s",value,show)->getCString();
                    }
                }
                else if(strcmp(element.get_command(),"award_general_exp") == 0)
                {
//                    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
//                    Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
//                    if (player)
//                    {
//                        DeputyGeneral* general = player->get_fight_general();
//                        if (general)
//                        {
//                            vector<uint> para;
//                            element.get_para_list_in_vector( para);
//                            if(para.size() > 0)
//                            {
//                                int value = para[0];
//                                const char* show = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(GENERAL_GET_EXP);
//                                reward = CCString::createWithFormat(show,general->get_character_name(),value)->getCString();
//                            }
//                        }
//                    }                    
                }
                else if(strcmp(element.get_command(),"award_deputy_general") == 0)
                {
                    reward = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_U_GAIN);
                    vector<uint> para;
                    element.get_para_list_in_vector( para);
                    if(para.size() > 0)
                    {
                        int value = para[0];
                        int name = PLAYER_MGR::instance()->get_name_id(value);
                        reward += DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(name);
                    }
                }
            }

           //Game_Utils::instance()->show_alert(reward.c_str());
        }
    }

    void Item_Mgr::compound_material_fragment(Player* player,message_stream& ms)
    {
        int item_base_id = 0;
        int compound_count = 0;
        ms >> item_base_id;
        ms >> compound_count;

        Item* fragment = ITEM_MGR::instance()->get_material_fragment(item_base_id);
        if (!fragment)
        {
            return;
        }

        Item_Fragment_Config* config = reinterpret_cast<Item_Fragment_Config*>(fragment->config);
        if (!config)
        {
            return;
        }

        int need = config->need_count * compound_count;
        if (fragment->count >= need)
        {
            fragment->count -= need;
        } 
        else
        {
            fragment->count = 0;
        }

        int change = 0;
        if (fragment->count == 0)
        {
            change = 1;
        }

//        Game_Logic::Game_Event_Response::instance()->on_update_compound_fragment(player->get_database_character_id(),change);
        DICTIONARY_CONFIG_MGR::instance()->show_alert(EXCHANGE_SUCCESS);

        //Game_Utils::instance()->add_effect_to_scene("");//材料合成
    }

    void Item_Mgr::compound_book_fragment(Player* player,message_stream& ms)
    {
        int item_base_id = 0;
        int compound_count = 0;
        ms >> item_base_id;
        ms >> compound_count;

        Item* fragment = ITEM_MGR::instance()->get_book_fragment(item_base_id);
        if (!fragment)
        {
            return;
        }

        Item_Fragment_Config* config = reinterpret_cast<Item_Fragment_Config*>(fragment->config);
        if (!config)
        {
            return;
        }

        int need = config->need_count * compound_count;
        if (fragment->count >= need)
        {
            fragment->count -= need;
        } 
        else
        {
            fragment->count = 0;
        }

        int change = 0;
        if (fragment->count == 0)
        {
            change = 1;
        }

//        Game_Logic::Game_Event_Response::instance()->on_update_compound_fragment(player->get_database_character_id(),change);
        DICTIONARY_CONFIG_MGR::instance()->show_alert(ASSEMBLE_SUCCESS);

        //Game_Utils::instance()->add_effect_to_scene("");//心法拼装
    }

    void Item_Mgr::set_on_gem(Player* player,message_stream& ms)
    {
        uint64 container_id = 0;
        uint64 item_id = 0;
        int gem_pos = 0;
        ms >> container_id;
        ms >> item_id;
        ms >> gem_pos;

        Game_Data::Item_Container* container = player->get_item_container(container_id);
        if (!container)
        {
            return;
        }

        Game_Data::Item* item = ITEM_MGR::instance()->get_item(item_id);
        if (!item)
        {
            return;
        }

        item->gem_id[gem_pos] = (int)container->item_id;
        container->item_count -= 1;
        if (container->item_count == 0)
        {
            container->is_num_type = 0;
            container->item_id = 0;
        }

        Game_Logic::Game_Event_Response::instance()->on_update_gem_inlay(player->get_database_character_id(),gem_pos);

        DICTIONARY_CONFIG_MGR::instance()->show_alert(GEM_INLAY_SUCCESS);
    }

    void Item_Mgr::set_off_gem(Player* player,message_stream& ms)
    {
        uint64 item_id = 0;
        int gem_pos = 0;
        ms >> item_id;
        ms >> gem_pos;

        Game_Data::Item* item = ITEM_MGR::instance()->get_item(item_id);
        if (!item)
        {
            return;
        }

        int gem_id = item->gem_id[gem_pos];
        Game_Data::Item_Config* gem_config = ITEM_CONFIG_MGR::instance()->get_item_config(gem_id);
        if (!gem_config)
        {
            return;
        }

        Game_Data::Item_Container* container = player->get_bag_can_pile_item_container(gem_config);
        if (container)
        {
            container->item_count += 1;
        }
        else
        {
            container = player->get_empty_bag_container();
            if (container)
            {
                container->is_num_type = 1;
                container->item_id = gem_id; 
                container->item_count = 1;
            }
        }

        item->gem_id[gem_pos] = 0;

        Game_Logic::Game_Event_Response::instance()->on_update_gem_inlay(player->get_database_character_id(),-1);

        DICTIONARY_CONFIG_MGR::instance()->show_alert(GEM_SETOFF_SUCCESS);
    }

    void Item_Mgr::create_item(Player* player,message_stream& ms)
    {
        if (!m_is_load_item)
        {
            return;
        }

        uint64 container_id = 0;
        ms >> container_id;
        Item_Container* container = ITEM_CONTAINER_MGR::instance()->get_item_container(container_id);
        if (!container)
        {
            return;
        }

        ms >> container->is_num_type;
        ms >> container->item_id;
        ms >> container->item_count;

        Item* item = NULL;
        if (container->is_num_type == 0)
        {
            int base_id = 0;
            item = new Item;
            memset(item,0,sizeof(Item));
            ms >> item->id;
            ms >> item->container_id;
            ms >> item->character_id;
            ms >> item->general_id;
            ms >> base_id;
            ms >> item->is_bind;
            ms >> item->bar_pos;
            ms >> item->level;
            ms >> item->exp;
            ms >> item->current_quality;
            ms >> item->count;
            ms >> item->get_time_point;
            ms >> item->use_time_point;
            ms >> item->create_way;
            ms >> item->destroy_way;

            item->config = ITEM_CONFIG_MGR::instance()->get_item_config(base_id);

            m_map_item.insert(make_pair(item->id,item));
            player->insert_item(item);
        }

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
    }

    void Item_Mgr::create_material_fragment(Player* player,message_stream& ms)
    {
        if (!m_is_load_material_fragment)
        {
            return;
        }

        int base_id = 0;
        ms >> base_id;
        Item* item = get_material_fragment(base_id);
        if (item == NULL)
        { 
            item = new Item;
            memset(item,0,sizeof(Item));
            item->config = ITEM_CONFIG_MGR::instance()->get_item_config(base_id);

            m_map_material_fragment.insert(make_pair(item->config->base_id,item));
            player->insert_material_fragment(item);
        }

        ms >> item->id;
        ms >> item->container_id;
        ms >> item->character_id;
        ms >> item->general_id;
        ms >> item->is_bind;
        ms >> item->bar_pos;
        ms >> item->level;
        ms >> item->exp;
        ms >> item->current_quality;
        ms >> item->count;
        ms >> item->get_time_point;
        ms >> item->use_time_point;
        ms >> item->create_way;
        ms >> item->destroy_way;

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
    }

    void Item_Mgr::create_book_fragment(Player* player,message_stream& ms)
    {
        if (!m_is_load_book_fragment)
        {
            return;
        }

        int base_id = 0;
        ms >> base_id;
        Item* item = get_book_fragment(base_id);
        if (item == NULL)
        { 
            item = new Item;
            memset(item,0,sizeof(Item));
            item->config = ITEM_CONFIG_MGR::instance()->get_item_config(base_id);

            m_map_book_fragment.insert(make_pair(item->config->base_id,item));
            player->insert_book_fragment(item);
        }

        ms >> item->id;
        ms >> item->container_id;
        ms >> item->character_id;
        ms >> item->general_id;
        ms >> item->is_bind;
        ms >> item->bar_pos;
        ms >> item->level;
        ms >> item->exp;
        ms >> item->current_quality;
        ms >> item->count;
        ms >> item->get_time_point;
        ms >> item->use_time_point;
        ms >> item->create_way;
        ms >> item->destroy_way;

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
    }

    void Item_Mgr::item_client_show(Player* player,message_stream& ms)
    {
        int item_base_id = 0;
        int item_count = 0;
        ms >> item_base_id;
        ms >> item_count;

        Game_Data::Item_Config* config = ITEM_CONFIG_MGR::instance()->get_item_config(item_base_id);
        Item_Config* item_config = NULL;
        if (config->type == IT_EQUIPMENT_DEPOT)
        {
            Equipment_Depot_Config* equipment_depot_config = reinterpret_cast<Equipment_Depot_Config*>(config);
            item_config = ITEM_CONFIG_MGR::instance()->get_item_config(equipment_depot_config->item_base_id);
        }
        else
        {
            item_config = config;
        }

        if (item_config)
        {
            
            const char* format = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_GAIN_INFO);
            const char* name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(item_config->name);
            const char* item = CCString::createWithFormat(format,name,item_count)->getCString();
            const char* head = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_U_GAIN);
            //Game_Utils::instance()->show_alert(CCString::createWithFormat("%s%s",head,item)->getCString());
        }
    }

    void Item_Mgr::show_book_level_up(Item* up_item,Item_List* list_item,int& up_level,int& surplus_exp)
    {
        Item* item = NULL;
        Item_List_Iter iter = list_item->begin();
        for (;iter != list_item->end();++iter)
        {
            item = *iter;
            if (item)
            {
                surplus_exp += ITEM_CONFIG_MGR::instance()->get_book_offer_exp(item->config->base_id,item->level,item->current_quality);
                surplus_exp += item->exp;
            }
        }

        int level_up_need_exp = ITEM_CONFIG_MGR::instance()->get_book_level_up_need_exp(up_item->config->base_id,up_item->level,up_item->current_quality);
        while (surplus_exp >= level_up_need_exp)
        {
            ++up_level;
            surplus_exp -= level_up_need_exp;
            level_up_need_exp = ITEM_CONFIG_MGR::instance()->get_book_level_up_need_exp(up_item->config->base_id,up_item->level + up_level,up_item->current_quality);
        }
    }

    bool Item_Mgr::check_quality_upgrade_need_material(Player* player,int module_type,int cur_quality)
    {
        Game_Data::game_element_list_t ele_list;
        ITEM_CONFIG_MGR::instance()->get_quality_upgrade_need_material(module_type,cur_quality,ele_list);
        Game_Data::game_element_list_t::iterator itg;
        for( itg = ele_list.begin(); itg != ele_list.end(); ++ itg)
        {
            Game_Data::Game_Element& element = (*itg);
            if(strcmp(element.get_command(),"instance") == 0 || strcmp(element.get_command(),"arena") == 0)
            {
                vector<uint> para;
                element.get_para_list_in_vector( para);
                if(para.size() > 1)
                {
                    int item_base_id = para[0];
                    int need_count = para[1];
                    
                    int have_count = player->get_bag_same_item_count(item_base_id);
                    if (have_count < need_count)
                    {
                        return false;
                    }
                }
            }
        }
        
        return true;
    }

    void Item_Mgr::remove_quality_upgrade_need_material(Player* player,int module_type,int cur_quality)
    {
        Game_Data::game_element_list_t ele_list;
        ITEM_CONFIG_MGR::instance()->get_quality_upgrade_need_material(module_type,cur_quality,ele_list);
        Game_Data::game_element_list_t::iterator itg;
        for( itg = ele_list.begin(); itg != ele_list.end(); ++ itg)
        {
            Game_Data::Game_Element& element = (*itg);
            if(strcmp(element.get_command(),"instance") == 0 || strcmp(element.get_command(),"arena") == 0)
            {
                vector<uint> para;
                element.get_para_list_in_vector( para);
                if(para.size() > 1)
                {
                    int item_base_id = para[0];
                    int need_count = para[1];

                    Item_Container_Map& bag_item_map = player->get_bag_item_container_map();

                    Item_Container* container = NULL;
                    Item_Container_Map_Iter iter = bag_item_map.begin();
                    for (;iter != bag_item_map.end();++iter)
                    {
                        container = iter->second;
                        if (!container)
                        {
                            continue;
                        }

                        bool is_same = false;
                        if (container->is_num_type == 1)
                        {
                            if (container->item_id == item_base_id)
                            {
                                is_same = true;
                            }
                        } 
                        else
                        {
                            Item* item = ITEM_MGR::instance()->get_item(container->item_id);;
                            if (item && item->config && item->config->base_id == item_base_id)
                            {
                                is_same = true;
                            }
                        }

                        if (is_same)
                        {
                            if (container->item_count >= need_count)
                            {
                                container->item_count -= need_count;
                                need_count = 0;
                            }
                            else
                            {
                                need_count -= container->item_count;
                                container->item_count = 0;
                            }

                            if (container->item_count == 0)
                            {
                                if (container->is_num_type == 0)
                                {
                                    Item* item = ITEM_MGR::instance()->get_item(container->item_id);
                                    if (item)
                                    {
                                        item->destroy_way = IDW_QUEST;
                                        // delete
                                    }
                                }

                                container->is_num_type = 0;
                                container->item_id = 0;
                            }
                        }
                        else
                        {
                            continue;
                        }

                        if (need_count == 0)
                        {
                            break;
                        }
                    }

                    if (need_count > 0)
                    {
                        // error
                    }
                }
            }
        }
    }

    void Item_Mgr::pathfinding_quality_upgrade_need_material(int module_type,int cur_quality,int item_base_id)
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::game_element_list_t ele_list;
        ITEM_CONFIG_MGR::instance()->get_quality_upgrade_need_material(module_type,cur_quality,ele_list);
        Game_Data::game_element_list_t::iterator itg;
        for( itg = ele_list.begin(); itg != ele_list.end(); ++ itg)
        {
            Game_Data::Game_Element& element = (*itg);
            if(strcmp(element.get_command(),"instance") == 0)
            {
                vector<uint> para;
                element.get_para_list_in_vector( para);
                if(para.size() > 2)
                {
                    int base_id = para[0];
                    if (item_base_id == base_id)
                    {
                        int instance_id = 0;
                        int instance_count = para[3];
                        if (instance_count == 0)
                        {
                            DICTIONARY_CONFIG_MGR::instance()->show_alert(MATERIAL_NOT_OPEN);
                            return;
                        }

                        int is_elite = para[2];
                        for (int i = 0;i < instance_count;++i)
                        {
                            instance_id = para[i + 4];
                            current_instance_data cid;
                            cid.reset();
                            cid.set_instance_id(instance_id);
                            if (-1 == INSTANCE_DATA_MGR::instance()->get_player_instance_from_list(player_id, cid))
                            {
                                cid.reset();
                                if (is_elite == 0)
                                {
                                    cid.set_instance_id(instance_id - 1);
                                } 
                                else
                                {
                                    cid.set_instance_id(instance_id);
                                }
                                
                                if (-1 == INSTANCE_DATA_MGR::instance()->get_player_instance_from_list(player_id, cid))
                                {
                                    continue;
                                }
                            }

                            Instance_UI_Config* instance_config = INSTANCE_DATA_MGR::instance()->get_instance_ui_config(instance_id);
                            INSTANCE_DATA_MGR::instance()->set_current_prompt_instance_id(PT_MATERIAL,instance_id,is_elite);

							Game_Utils::instance()->quest_auto_move(1011, Game_Utils::clicked_area, instance_config->area_id);
                            return;
                        }
                        
                        DICTIONARY_CONFIG_MGR::instance()->show_alert(MATERIAL_INSTANCE_NOT_OPEN);
                        return;
                    }
                }
            }
            else if (strcmp(element.get_command(),"arena") == 0)
            {
                vector<uint> para;
                element.get_para_list_in_vector( para);
                if(para.size() > 0)
                {
                    //UI_MainMenu_Layer::get_instance()->show_arena();
                    return;
                }

                DICTIONARY_CONFIG_MGR::instance()->show_alert(ARENA_NOT_OPEN);
                return;
            }
        }
    }

    void Item_Mgr::insert_item(Item* item)
    {
        if (item)
        {
            m_map_item.insert(std::make_pair(item->id, item));
        }
    }

    void Item_Mgr::remove_item(int id)
    {
        Item_Map_Iter iter = m_map_item.find(id);
        if (iter != m_map_item.end())
        {
            m_map_item.erase(iter);
        }
    }

    Item* Item_Mgr::get_item(uint64 id)
    {
        Item* item = NULL;
        Item_Map_Iter iter = m_map_item.find(id);
        if (iter != m_map_item.end())
        {
            item = iter->second;
        }

        return item;
    }

    void Item_Mgr::insert_material_fragment(Item* item)
    {
        if (item)
        {
            m_map_material_fragment.insert(std::make_pair(item->config->base_id, item));
        }
    }

    void Item_Mgr::remove_material_fragment(int base_id)
    {
        Item_Map_Iter iter = m_map_material_fragment.find(base_id);
        if (iter != m_map_material_fragment.end())
        {
            m_map_material_fragment.erase(iter);
        }
    }

    void Item_Mgr::insert_book_fragment(Item* item)
    {
        if (item)
        {
            m_map_book_fragment.insert(std::make_pair(item->config->base_id, item));
        }
    }

    void Item_Mgr::remove_book_fragment(int base_id)
    {
        Item_Map_Iter iter = m_map_book_fragment.find(base_id);
        if (iter != m_map_book_fragment.end())
        {
            m_map_book_fragment.erase(iter);
        }
    }

    Item* Item_Mgr::get_material_fragment(int base_id)
    {
        Item* item = NULL;
        Item_Map_Iter iter = m_map_material_fragment.find(base_id);
        if (iter != m_map_material_fragment.end())
        {
            item = iter->second;
        }

        return item;
    }

    Item* Item_Mgr::get_book_fragment(int base_id)
    {
        Item* item = NULL;
        Item_Map_Iter iter = m_map_book_fragment.find(base_id);
        if (iter != m_map_book_fragment.end())
        {
            item = iter->second;
        }

        return item;
    }

    int Item_Mgr::get_all_material_fragment(Item_List& list)
    {
        list.clear();
        int count = 0;
        Item* item = NULL;
        Item_Map_Iter iter = m_map_material_fragment.begin();
        for (;iter != m_map_material_fragment.end();++iter)
        {
            item = iter->second;
            if (item && item->count > 0)
            {
                list.push_back(item);
                ++count;
            }
        }

        return count;
    }

    int Item_Mgr::get_all_book_fragment(Item_List& list)
    {
        list.clear();
        int count = 0;
        Item* item = NULL;
        Item_Map_Iter iter = m_map_book_fragment.begin();
        for (;iter != m_map_book_fragment.end();++iter)
        {
            item = iter->second;
            if (item && item->count > 0)
            {
                list.push_back(item);
                ++count;
            }
        }

        return count;
    }

    bool Item_Mgr::is_need_tidy_item(Player* player)
    {
        Item_Container_Map& bag_item_map = player->get_bag_item_container_map();
        if (check_pile_item(bag_item_map))
        {
            return true;
        }
        
        if (check_sort_item(bag_item_map))
        {
            return true;
        }
        
        return false;
    }

    Item_Config* Item_Mgr::get_item_config_from_container(Item_Container* container)
    {
        Item_Config* config = NULL;
        if (container->is_num_type == 0)
        {
            Item* item = ITEM_MGR::instance()->get_item(container->item_id);
            if (item)
            {
                config = item->config;
            }
        } 
        else
        {
            config = ITEM_CONFIG_MGR::instance()->get_item_config((int)container->item_id);
        }

        return config;
    }

    int Item_Mgr::get_can_set_gem_pos(Item* item)
    {
		for (int i = 0; i < SET_GEM_COUNT; ++i)
        {
            if (item->gem_id[i] == 0)
            {
                return i;
            }
        } 

        return -1;
    }

    int Item_Mgr::get_equipment_attr(Item* item,int attr_type)
    {
        int attr = ITEM_CONFIG_MGR::instance()->get_equipment_attr(item->config->base_id,item->level,item->current_quality,attr_type);
        return attr;
    }

    int Item_Mgr::get_equipment_gem_attr(Item* item,int attr_type)
    {
        int attr = 0;
        Gem_Config* config = NULL;
        for (int i = 0;i < SET_GEM_COUNT;++i)
        {
            config = ITEM_CONFIG_MGR::instance()->get_gem_config(item->gem_id[i]);
            if (config && config->attr_type == attr_type)
            {
                attr += config->attr_value;
            }
        }

        return attr;
    }

    bool Item_Mgr::check_pile_item(Item_Container_Map& bag_item_map)
    {
        Item_Config* config = NULL;
        Item_Container* container_1 = NULL;
        Item_Container* container_2 = NULL;
        int container_count = (int)bag_item_map.size();
        for (int i = 0;i < container_count;++i)
        {
            container_1 = bag_item_map.at(i);
            if (!container_1 || container_1->is_num_type == 0)
            {
                continue;
            }

            config = ITEM_CONFIG_MGR::instance()->get_item_config((int)container_1->item_id);
            if (!config || config->can_pile == 0 || container_1->item_count >= config->pile_count)
            {
                continue;
            }

            for (int j = i+1;j < container_count;++j)
            {
                container_2 = bag_item_map.at(j);
                if (!container_2 || container_2->is_num_type == 0 
                    || container_2->item_id != container_1->item_id)
                {
                    continue;
                }

                return true;
            }
        }

        return false;
    }

    bool Item_Mgr::check_sort_item(Item_Container_Map& bag_item_map)
    {
        Item_Config* config = NULL;
        Item_Container* container_1 = NULL;
        Item_Container* container_2 = NULL;
        int is_num_type = 0;
        uint64 item_id = 0;
        int item_count = 0;
        int container_count = (int)bag_item_map.size();
        for (int i = 0;i < container_count;++i)
        {
            container_1 = bag_item_map.at(i);
            if (!container_1)
            {
                continue;
            }

            for (int j = i+1;j < container_count;++j)
            {
                container_2 = bag_item_map.at(j);
                if (!container_2)
                {
                    continue;
                }

                if (is_change(container_1,container_2))
                {
                    return true;
                }
            }
        }

        return false;
    }

    bool Item_Mgr::is_change(Item_Container* container_1,Item_Container* container_2)
    {
        if (container_1->item_id == 0)
        {
            if (container_2->item_id == 0)
            {
                return false;
            }
            else 
            {
                return true;
            }
        }
        else if (container_2->item_id == 0)
        {
            return false;
        }

        Item_Config* config_1 = get_item_config_from_container(container_1);
        Item_Config* config_2 = get_item_config_from_container(container_2);
        if (!config_1 || !config_2)
        {
            return false;
        }

        if (config_1->type == IT_GIFT_ITEM && config_2->type != IT_GIFT_ITEM)
        {
            return false;
        }

        if (config_1->type != IT_GIFT_ITEM && config_2->type == IT_GIFT_ITEM)
        {
            return true;
        }

        if (container_1->is_num_type > container_2->is_num_type)
        {
            return true;
        } 
        else if (container_1->is_num_type == container_2->is_num_type)
        {
            if (config_1->sort > config_2->sort)
            {
                return true;
            } 
            else if (config_1->sort == config_2->sort)
            {
                if (config_1->base_id < config_2->base_id)
                {
                    return true;
                } 
                else if (config_1->base_id == config_2->base_id)
                {
                    if (container_1->is_num_type == 0)
                    {
                        Item* item_1 = ITEM_MGR::instance()->get_item(container_1->item_id);
                        Item* item_2 = ITEM_MGR::instance()->get_item(container_2->item_id);
                        if (!item_1 || !item_2)
                        {
                            return false;
                        }

                        if (item_1->level < item_2->level)
                        {
                            return true;
                        } 
                        else if (item_1->level == item_2->level)
                        {
                            if (item_1->current_quality < item_2->current_quality)
                            {
                                return true;
                            }
                        }
                    } 
                    else if (container_1->item_count < container_2->item_count)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }
}

