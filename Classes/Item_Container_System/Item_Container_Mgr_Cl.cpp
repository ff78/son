
#include "Item_Container_Mgr_Cl.h"

#include "Network_Common/message_stream.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Item_System/Item_Mgr_Cl.h"

#include "Game_Interface/game_event_response.h"

#ifdef YN_LINUX
#include <string.h>
#endif

namespace Game_Data
{
    Item_Container_Mgr* Item_Container_Mgr::instance_ = NULL;
    Item_Container_Mgr::Item_Container_Mgr()
    :m_is_load(false)
    {

    }

    Item_Container_Mgr::~Item_Container_Mgr()
    {

    }

    Item_Container_Mgr* Item_Container_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Item_Container_Mgr;
        }

        return instance_;
    }

    void Item_Container_Mgr::release()
    {
        Item_Container* container = NULL;
        Item_Container_Map_Iter iter = m_map_item_container.begin();
        for (;iter != m_map_item_container.end();++iter)
        {
            container = iter->second;
            if (container)
            {
                delete container;
            }
        }

        m_map_item_container.clear();
        m_is_load = false;
    }

    void Item_Container_Mgr::load_item_container(Player* player,message_stream& ms)
    {
        m_is_load = true;
        int container_count = 0;
        ms >> container_count;

        Item_Container* container = NULL;
        for (int i = 0; i < container_count; ++i)
        {
            Item_Container* container = new Item_Container;
            memset(container,0,sizeof(Item_Container));
            ms >> container->id;
            ms >> container->character_id;
            ms >> container->type;
            ms >> container->index;
            ms >> container->is_num_type;
            ms >> container->item_id;
            ms >> container->item_count;
            ms >> container->destroy;

            m_map_item_container.insert(make_pair(container->id,container));
            player->insert_item_container(container);
            player->load_item_container(container);
        }

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
    }

    void Item_Container_Mgr::update_item_container(Player* player,message_stream& ms)
    {
        uint64 container_id = 0;
        int item_count = 0;
        ms >> container_id;
        ms >> item_count;

        Item_Container* container = ITEM_CONTAINER_MGR::instance()->get_item_container(container_id);
        if (!container)
        {
            return;
        }
        
        container->item_count = item_count;
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

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
    }

    void Item_Container_Mgr::create_item_container(Player* player,message_stream& ms)
    {
        if (!m_is_load)
        {
            return;
        }
        
        Item_Container* container = new Item_Container;
        memset(container,0,sizeof(Item_Container));
        ms >> container->id;
        ms >> container->character_id;
        ms >> container->type;
        ms >> container->index;
        ms >> container->is_num_type;
        ms >> container->item_id;
        ms >> container->item_count;
        ms >> container->destroy;

        m_map_item_container.insert(make_pair(container->id,container));
        player->insert_item_container(container);
        player->load_item_container(container);

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
    }

    void Item_Container_Mgr::tidy_item_container(Player* player,message_stream& ms)
    {
        int container_count = 0;
        ms >> container_count;

        uint64 container_id = 0;
        Item_Container* container = NULL;
        for (int i = 0; i < container_count; ++i)
        {
            ms >> container_id;
            Item_Container* container = get_item_container(container_id);
            if (!container)
            {
                continue;
            }

            ms >> container->character_id;
            ms >> container->type;
            ms >> container->index;
            ms >> container->is_num_type;
            ms >> container->item_id;
            ms >> container->item_count;
            ms >> container->destroy;
        }

        Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
    }

    void Item_Container_Mgr::insert_item_container(Item_Container* container)
    {
        if (container)
        {
            m_map_item_container.insert(make_pair(container->id, container));
        }
    }

    void Item_Container_Mgr::remove_item_container(int id)
    {
        Item_Container_Map_Iter iter = m_map_item_container.find(id);
        if (iter != m_map_item_container.end())
        {
            m_map_item_container.erase(iter);
        }
    }

    Item_Container* Item_Container_Mgr::get_item_container(uint64 id)
    {
        Item_Container* container = NULL;
        Item_Container_Map_Iter iter = m_map_item_container.find(id);
        if (iter != m_map_item_container.end())
        {
            container = iter->second;
        }

        return container;
    }
}

