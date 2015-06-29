#include <fstream>	
#include "Item_Logic_Cl.h"
#include "Item_System/Item_Mgr_Cl.h"
#include "Item_Container_System/Item_Container_Mgr_Cl.h"

#include "Game_Interface/game_content_interface.h"

#include "Game_Interface/Game_Element_Parse.h"
#include "UI_Interface/CocoStu_UI_Scene_Interface.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
#include "Game_Interface/event_define.h"

#include "Event_System/event_system_data_mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Player_Logic_Cl.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Shop_System/Shop_Config_Mgr.h"

#include "Common/GameDefine.h"

#include "UI_Interface/UI_ModalDialogue_Layer.h"

namespace Game_Data
{
    Item_Logic* Item_Logic::instance_ = NULL;
    Item_Logic::Item_Logic()
    {

    }

    Item_Logic::~Item_Logic()
    {

    }

    Item_Logic* Item_Logic::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Item_Logic;
        }

        return instance_;
    }

    void Item_Logic::load_item()
    {
        if (ITEM_MGR::instance()->is_load_item())
        {
            return;
        }
        
        std::vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_item", para);
    }

    void Item_Logic::load_material_fragment()
    {
        if (ITEM_MGR::instance()->is_load_material_fragment())
        {
            return;
        }

        std::vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_material_fragment", para);
    }

    void Item_Logic::load_book_fragment()
    {
        if (ITEM_MGR::instance()->is_load_book_fragment())
        {
            return;
        }

        std::vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_book_fragment", para);
    }

    void Item_Logic::tidy_item()
    {
        int role_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
        if (!player)
        {
            return;
        }

        if (ITEM_MGR::instance()->is_need_tidy_item(player) == false)
        {
            cout << "do not need tidy!----------------------------------"<< endl;
            return;
        }

        int cur_time = (int)time(NULL);
        if (cur_time - player->get_last_tidy_item_time() < TIDY_ITEM_TIME)
        {
            cout << "to fast!----------------------------------"<< endl;
            return;
        }

        player->set_last_tidy_item_time(cur_time);

        vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_tidy_item", para);
    }

    bool Item_Logic::equip_equipment(int character_id,uint64 container_id)
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return false;
        }

        Character* character = CHARACTER_MGR::instance()->get_character(character_id);
        if (!character)
        {
            return false;
        } 

        Item_Container* container = ITEM_CONTAINER_MGR::instance()->get_item_container(container_id);
        if (!container)
        {
            return false;
        }

        Game_Data::Item*item = ITEM_MGR::instance()->get_item(container->item_id);
        if (item == NULL || character->get_character_level() < item->level)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(EQUIP_ITEM_LEVEL_LIMIT);
            return false;
        }

        std::vector<uint64> para;
        para.push_back(character_id);
        para.push_back(container->index);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_equip_equipment", para);

        return true;
    }

    void Item_Logic::take_off_equipmen(int character_id,uint64 item_id)
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        Character* character = CHARACTER_MGR::instance()->get_character(character_id);
        if (!character)
        {
            return;
        }

        Item* item = ITEM_MGR::instance()->get_item(item_id);
        if (!item)
        {
            return;
        }

        Item_Container* empty_container = player->get_empty_bag_container();
        if (empty_container == NULL)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(BAG_FULL_TIPS);
            return;
        }

        std::vector<uint64> para;
        para.push_back(character_id);
        para.push_back(item->bar_pos);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_take_off_equipmen", para);
    }

    bool Item_Logic::equip_book(int character_id,uint64 container_id)
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return false;
        }

        Character* character = CHARACTER_MGR::instance()->get_character(character_id);
        if (!character)
        {
            return false;
        } 

        Item_Container* container = ITEM_CONTAINER_MGR::instance()->get_item_container(container_id);
        if (!container)
        {
            return false;
        }

        Game_Data::Item*item = ITEM_MGR::instance()->get_item(container->item_id);
        if (!item)
        {
            return false;
        }

        Game_Data::Book_Config* config = reinterpret_cast<Game_Data::Book_Config*>(item->config);
        if (!config)
        {
            return false;
        }

        if (character->get_power() < (config->need_power + character->get_used_power()))
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_POWER);
            return false;
        }

        int pos = character->get_empty_book_bar();
        if (pos == -1)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_POWER);
            return false;
        }
        
        std::vector<uint64> para;
        para.push_back(character_id);
        para.push_back(container->index);
        para.push_back(pos);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_equip_book", para);

        return true;
    }

    void Item_Logic::take_off_book(int character_id,uint64 item_id)
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        Character* character = CHARACTER_MGR::instance()->get_character(character_id);
        if (!character)
        {
            return;
        }

        Item* item = ITEM_MGR::instance()->get_item(item_id);
        if (!item)
        {
            return;
        }

        Item_Container* empty_container = player->get_empty_bag_container();
        if (empty_container == NULL)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(BAG_FULL_TIPS);
            return;
        }

        std::vector<uint64> para;
        para.push_back(character_id);
        para.push_back(item->bar_pos);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_take_off_book", para);
    }

    bool Item_Logic::equipment_level_up(uint64 item_id)
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return false;
        }

        Item* item = ITEM_MGR::instance()->get_item(item_id);
        if (!item)
        {
            return false;
        }

        if (item->config->type != IT_EQUIPMENT)
        {
            return false;
        }

        if (item->general_id > 0)
        {
            Character* character = CHARACTER_MGR::instance()->get_character(item->general_id);
            if (!character)
            {
                return false;
            }

            if (item->level >= character->get_character_level())
            {
                DICTIONARY_CONFIG_MGR::instance()->show_alert(EQUIPMENT_INTENSIFY_LESS_ROLE_LEVEL);
                return false;
            }
        }
        else
        {
            if (item->level >= player->get_character_level())
            {
                DICTIONARY_CONFIG_MGR::instance()->show_alert(EQUIPMENT_INTENSIFY_LESS_PROTAGONIST_LEVEL);
                return false;
            }
        }

        int cost = ITEM_CONFIG_MGR::instance()->get_equipment_level_up_cost(item->config->base_id,item->level);
        if (player->get_gold() < cost)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_GOLD_COIN);
            return false;
        }
        
        std::vector<uint64> para;
        para.push_back(item_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_equipment_level_up", para);

        return true;
    }

    void Item_Logic::equipment_quality_up(uint64 item_id)
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        Item* item = ITEM_MGR::instance()->get_item(item_id);
        if (!item)
        {
            return;
        }

        if (item->config->type != IT_EQUIPMENT)
        {
            return;
        }    

        if(item->current_quality >= Game_Data::QT_ORANGE)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(QUALITY_MAX_LIMIT);
            return;
        }

        //if (ITEM_MGR::instance()->check_quality_upgrade_need_material(player,Game_Data::QMT_EQUIPMENT,item->current_quality) == false)
        //{
        //    DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_MATERIAL);
        //    return;
        //}

        std::vector<uint64> para;
        para.push_back(item_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_equipment_quality_up", para);
    }

    bool Item_Logic::book_level_up(uint64 item_id,std::list<uint64>* list_item_id)
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return false;
        }

        Item* item = ITEM_MGR::instance()->get_item(item_id);
        if (!item)
        {
            return false;
        }

        if (item->config->type != IT_BOOK)
        {
            return false;
        }

        int item_max_level = ITEM_CONFIG_MGR::instance()->get_book_max_level(item->config->base_id,item->current_quality);
        if (item->level >= item_max_level)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(EQUIPMENT_INTENSIFY_LESS_PROTAGONIST_LEVEL);
            return false;
        }

        std::vector<uint64> para;
        para.push_back(item_id);
        
        item = NULL;
        std::list<uint64>::iterator item_iter = list_item_id->begin();
        for (;item_iter != list_item_id->end();++item_iter)
        {
            item = ITEM_MGR::instance()->get_item(*item_iter);
            if (!item || item->config->type != IT_BOOK)
            {
                return false;
            }

            para.push_back(item->id);
        }

        if (para.size() < 2)
        {
            return false;
        }
    
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_book_level_up", para);

        return true;
    }

    void Item_Logic::book_quality_up(uint64 item_id)
    {
        int character_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
        if (!player)
        {
            return;
        }

        Item* item = ITEM_MGR::instance()->get_item(item_id);
        if (!item)
        {
            return;
        }

        if (item->config->type != IT_BOOK)
        {
            return;
        } 

        if(item->current_quality >= Game_Data::QT_ORANGE)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(QUALITY_MAX_LIMIT);
            return;
        }

        int item_max_level = ITEM_CONFIG_MGR::instance()->get_book_max_level(item->config->base_id,item->current_quality);
        if (item_max_level != item->level)
        {
            return;
        }

        if (ITEM_MGR::instance()->check_quality_upgrade_need_material(player,Game_Data::QMT_BOOK,item->current_quality) == false)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_MATERIAL);
            return;
        }

        std::vector<uint64> para;
        para.push_back(item_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_book_quality_up", para);
    }

    void Item_Logic::sell_item(uint64 container_id,int count)
    {
        int character_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
        if (!player)
        {
            return;
        }

        Item_Container* container = ITEM_CONTAINER_MGR::instance()->get_item_container(container_id);
        if (!container)
        {
            return;
        }

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

        if (config == NULL || config->can_sell == 0)
        {
            return;
        }

        // check item is locked

        std::vector<uint64> para;
        para.push_back(container->id);
        para.push_back(count);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_sell_item", para);
    }

    void Item_Logic::use_item(uint64 container_id)
    {
        int role_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
        if (!player)
        {
            return;
        }

        Item_Container* container = ITEM_CONTAINER_MGR::instance()->get_item_container(container_id);
        if (!container)
        {
            return;
        }

        Item_Config* config = NULL; 
        if (container->is_num_type == 0)
        {
            Item* item = ITEM_MGR::instance()->get_item(container->item_id);
            if (item)
            {
                if (item->count <= 0)
                {
                    return;
                }

                config = item->config;
            }
        } 
        else
        {
            if (container->item_count <= 0)
            {
                return;
            }

            config = ITEM_CONFIG_MGR::instance()->get_item_config((int)container->item_id);
        }

        if (config == NULL || (config->type != IT_USABLE_ITEM && config->type != IT_GIFT_ITEM))
        {
            return;
        }

        Usable_Item_Config* usable_config = reinterpret_cast<Usable_Item_Config*>(config);
        if (!usable_config)
        {
            return;
        }

        int level_down = 0;
        int level_up = 0;
        ITEM_CONFIG_MGR::instance()->get_item_use_level(config->base_id,level_down,level_up);
        if (level_down == 0 || level_up == 0)
        {
            return;
        }

        if (level_down > player->get_character_level())
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_ROLE_LEVEL);
            return;
        }

        if (level_up < player->get_character_level())
        {
            return;
        }

        if (config->type == IT_GIFT_ITEM)
        {
            Event_Data event_data;
            event_system_data_mgr::sharedInstance()->getEventDataById(usable_config->event_id,event_data);
            if(event_data.getId()==0)
            {
                return;
            }

            Game_Data::game_element_list_t ele_list;
            event_data.getFunction(ele_list);
            if (PLAYER_LOGIC::instance()->check_bag_room(role_id,ele_list) == false)
            {
                DICTIONARY_CONFIG_MGR::instance()->show_alert(UG_BAG_FULL);
                return;
            }
        }
        else if (config->type == IT_USABLE_ITEM)
        {
            Event_Data event_data;
            event_system_data_mgr::sharedInstance()->getEventDataById(usable_config->event_id,event_data);
            if(event_data.getId()==0)
            {
                return;
            }

            Game_Data::game_element_list_t ele_list;
            event_data.getFunction(ele_list);
            if (PLAYER_LOGIC::instance()->check_can_use(role_id,ele_list) == false)
            {
                return;
            }
        }

        // check item is locked

        std::vector<uint64> para;
        para.push_back(container->id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_use_item", para);
    }

    void Item_Logic::compound_material_fragment(int item_base_id,int compound_count)
    {
        if (compound_count <= 0)
        {
            return;
        }

        int character_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
        if (!player)
        {
            return;
        }

        Item_Container* empty = player->get_empty_bag_container();
        if (!empty)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(BAG_FULL_TIPS);
            return;
        }

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
        
        if (config->need_count * compound_count > fragment->count)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_MATERIAL);
            return;
        }

        std::vector<uint64> para;
        para.push_back(item_base_id);
        para.push_back(compound_count);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_compound_material_fragment", para);
    }

    void Item_Logic::compound_book_fragment(int item_base_id,int compound_count)
    {
        if (compound_count <= 0)
        {
            return;
        }

        int character_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
        if (!player)
        {
            return;
        }

        Item_Container* empty = player->get_empty_bag_container();
        if (!empty)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(BAG_FULL_TIPS);
            return;
        }

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

        if (config->need_count * compound_count > fragment->count)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_MATERIAL);
            return;
        }

        std::vector<uint64> para;
        para.push_back(item_base_id);
        para.push_back(compound_count);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_compound_book_fragment", para);
    }

    void Item_Logic::set_on_gem(int character_id,uint64 container_id)
    {
		/************************************************************************/
		// 镶嵌宝石
		// 1. 获取当前玩家ID
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(character_id);
        if (!character)
        {
            return;
        }

        Game_Data::Item_Container* container = ITEM_CONTAINER_MGR::instance()->get_item_container(container_id);
        if (!container)
        {
            return;
        }

        if (container->is_num_type == 0)
        {
            return;
        }

        Game_Data::Gem_Config* config = ITEM_CONFIG_MGR::instance()->get_gem_config((int)container->item_id);
        if (!config)
        {
            return;
        }

        Game_Data::Item* equipment = character->get_item_from_equipment_bar(config->set_equipment_pos);
        if (!equipment)
        {
            return;
        }

        int gem_pos = ITEM_MGR::instance()->get_can_set_gem_pos(equipment);
        if (gem_pos == -1)
        {
            if (equipment->current_quality == Game_Data::QT_ORANGE)
            {
                DICTIONARY_CONFIG_MGR::instance()->show_alert(GEM_INLAY_FULL_FONT);
            } 
            else
            {
                DICTIONARY_CONFIG_MGR::instance()->show_alert(GEM_INLAY_FULL_TIP);
            }
            return;
        }

        std::vector<uint64> para;
        para.push_back(character_id);
        para.push_back(container_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_set_on_gem", para);
    }
	
	int Item_Logic::GetTargetGemEquipPos (const int nCharacterID, const uint64 container_id)
	{
		/************************************************************************/
		// 获取目标宝石的镶嵌位置
		// 1. 判断目标材料是否为宝石
		if (!JudgeTargetItemIsGem(nCharacterID, container_id))
			return -1;

		// 2. 获取宝石的镶嵌位置
		Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(nCharacterID);
		if (!character)
		{
			return -1;
		}

		Game_Data::Item_Container* container = ITEM_CONTAINER_MGR::instance()->get_item_container(container_id);
		if (!container)
		{
			return -1;
		}

		if (container->is_num_type == 0)
		{
			return -1;
		}

		Game_Data::Gem_Config* config = ITEM_CONFIG_MGR::instance()->get_gem_config((int)container->item_id);
		if (!config)
		{
			return -1;
		}

		return config->set_equipment_pos;
	}


	bool Item_Logic::JudgeMaterialIsExist(const int nCharacterID, const uint64 container_id)
	{
		/************************************************************************/
		// 判断目标材料是否存在
		// 1. 判断目标玩家的目标角色是否存在
		int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();
		Game_Data::Player* pPlayer = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(nPlayerID));
		if (pPlayer == NULL)
			return false;

		Game_Data::Character* pCharacter = CHARACTER_MGR::instance()->get_character(nCharacterID);
		if (pCharacter == NULL)
			return false;

		// 2. 判断目标材料是否存在
		Game_Data::Item_Container* pContainer = ITEM_CONTAINER_MGR::instance()->get_item_container(container_id);
		if (pContainer == NULL)
			return false;

		// 3. 判断目标材料的个数是不是为0
		if (pContainer->item_count <= 0)
		{
			return false;
		}

		// 4. 判断目标材料是否是计数型道具
		if (pContainer->is_num_type == 0)
			return false;

		return true;
	}


	bool Item_Logic::JudgeTargetItemIsGem(const int nCharacterID, const uint64 container_id)
	{
		/************************************************************************/
		// 判断目标物品是否为宝石
		// 1. 判断目标玩家的目标角色是否存在
		int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();
		Game_Data::Player* pPlayer = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(nPlayerID));
		if (pPlayer == NULL)
			return false;

		Game_Data::Character* pCharacter = CHARACTER_MGR::instance()->get_character(nCharacterID);
		if (pCharacter == NULL)
			return false;

		// 2. 判断目标材料是否存在
		if (!JudgeMaterialIsExist(nCharacterID , container_id))
			return false;
		
		// 3. 判断堆叠类型
		Game_Data::Item_Container* container = ITEM_CONTAINER_MGR::instance()->get_item_container(container_id);
		if (!container)
			return false;

		if (container->is_num_type == 0)
			return false;

		// 4. 获取配置信息判断类型
		Game_Data::Gem_Config* pItemConfig = ITEM_CONFIG_MGR::instance()->get_gem_config((int)container->item_id);
		if (pItemConfig == NULL)
			return false;

		int nType = pItemConfig->type;
		if (nType != 9)
		{
			return false;
		}
		return true;
	}

	bool Item_Logic::JudgeTargetPosIsOnEquip(const int nCharacterID, const int nEquipPos)
	{
		/************************************************************************/
		// 判断位置是否有穿戴装备
		// 1. 判断目标玩家的目标角色是否存在
		int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();
		Game_Data::Player* pPlayer = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(nPlayerID));
		if (pPlayer == NULL)
			return false;

		Game_Data::Character* pCharacter = CHARACTER_MGR::instance()->get_character(nCharacterID);
		if (pCharacter == NULL)
			return false;

		// 2. 判断当前位置是否有穿戴装备
		Game_Data::Item* pEquipment = pCharacter->get_item_from_equipment_bar(nEquipPos);
		if (pEquipment == NULL)
		{
			return false;
		}
		return true;
	}


	bool Item_Logic::JudgeTargetPosEquipCanFillInGem(const int nCharacterID, const int nEquipPos)
	{
		/************************************************************************/
		// 判断目标位置的装备是否可以镶嵌宝石
		// 1. 判断判断位置是否有穿戴装备
		if (!JudgeTargetPosIsOnEquip(nCharacterID , nEquipPos))
		{
			return false;
		}

		// 2. 判断目标装备是否还留有孔位
		Game_Data::Character* pCharacter = CHARACTER_MGR::instance()->get_character(nCharacterID);
		if (pCharacter == NULL)
			return false;

		Game_Data::Item* pEquipment = pCharacter->get_item_from_equipment_bar(nEquipPos);
		if (pEquipment == NULL)
		{
			return false;
		}
		
		int gem_pos = ITEM_MGR::instance()->get_can_set_gem_pos(pEquipment);
		if (gem_pos == -1)
		{
			return false;
		}
		return true;
	}


	bool Item_Logic::JudgeTargetGemCanCompound(const int nCharacterID, const uint64 nContainerID)
	{
		/************************************************************************/
		// 判断目标宝石是够可以合成
		// 1. 判断玩家的数据是否异常
		int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();
		Game_Data::Player* pPlayer = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(nPlayerID));
		if (pPlayer == NULL)
			return false;

		// 2. 判断目标材料是否为宝石
		if (!JudgeTargetItemIsGem(nCharacterID, nContainerID))
			return false;

		// 3. 获取宝石的Config文件
		Game_Data::Item_Container* container = ITEM_CONTAINER_MGR::instance()->get_item_container(nContainerID);
		if (!container)
			return false;

		// 4. 获取宝石ID
		int nGemID = container->item_id;
		Game_Data::Gem_Config* pGemConfig = ITEM_CONFIG_MGR::instance()->get_gem_config(nGemID);
		if (!pGemConfig)
			return false;

		// 4. 判断宝石的提升等级是不是已经到了最高级
		if (pGemConfig->compound_id == 0)
		{
			DICTIONARY_CONFIG_MGR::instance()->show_alert(GEM_COMBINE_LEVEL_LIMIT);
			return false;
		}

		// 5. 判断宝石的数量是否足够合成
		int nGemCount = pPlayer->get_bag_same_item_count(nGemID);
		if (nGemCount < GEM_LEVEL_UP_NEED_COUNT)
		{
			DICTIONARY_CONFIG_MGR::instance()->show_alert(GEM_COMBINE_LACK_COUNT);
			return false;
		}

		// 6. 判断当前玩家拥有的金钱是否足够升级
		int nNeedGold = pGemConfig->upgrade_cost;
		int nHaveGold = pPlayer->get_gold();
		if (nNeedGold < 0 || nNeedGold > nHaveGold)
			return false;

		return true;
	}

	bool Item_Logic::JudgeMaterialCanFillInTargetEquip(const int nCharacterID, const uint64 container_id, const int nEquipPos)
	{
		/************************************************************************/
		// 判断目标材料是否可以镶嵌到指定装备上
		// 1. 判断目标材料是否为宝石
		if (!JudgeTargetItemIsGem(nCharacterID, container_id))
			return false;
		
		// 2. 判断位置是否有穿戴装备
		if (!JudgeTargetPosIsOnEquip(nCharacterID, nEquipPos))
			return false;

		// 3. 判断宝石的镶嵌位置是否与装备的位置一样
		int nGemPos = GetTargetGemEquipPos(nCharacterID, container_id);
		if (nGemPos < 0 || nGemPos != nEquipPos)
			return false;
		
		// 4. 判断该装备是否还留有孔位
		if (!JudgeTargetPosEquipCanFillInGem(nCharacterID, nEquipPos))
			return false;

		return true;
	}

    void Item_Logic::set_off_gem(uint64 item_id,int gem_pos)
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        if (gem_pos < 0 || gem_pos >= SET_GEM_COUNT)
        {
            return;
        }

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
        if (!container)
        {
            container = player->get_empty_bag_container();
            if (!container)
            {
                DICTIONARY_CONFIG_MGR::instance()->show_alert(BAG_FULL_TIPS);
                return;
            }
        }

        std::vector<uint64> para;
        para.push_back(item_id);
        para.push_back(gem_pos);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_set_off_gem", para);
    }
}

void Item_Logic::gem_level_up(int gem_id,int time)
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return;
    }

    Game_Data::Gem_Config* gem_config = ITEM_CONFIG_MGR::instance()->get_gem_config(gem_id);
    if (!gem_config)
    {
        return;
    }

    if (gem_config->compound_id == 0)
    {
        DICTIONARY_CONFIG_MGR::instance()->show_alert(GEM_COMBINE_LEVEL_LIMIT);
        return;
    }

    int gem_count = player->get_bag_same_item_count(gem_id);
    if (gem_count < GEM_LEVEL_UP_NEED_COUNT)
    {
        DICTIONARY_CONFIG_MGR::instance()->show_alert(GEM_COMBINE_LACK_COUNT);
        return;
    }

    int op_time = 1;
    if (time == 0)
    {
        op_time = gem_count / GEM_LEVEL_UP_NEED_COUNT;
    }

    int need_gold = op_time * gem_config->upgrade_cost;
    int have_gold = player->get_gold();
    if (need_gold > have_gold)
    {
        op_time = have_gold / gem_config->upgrade_cost;
        need_gold = op_time * gem_config->upgrade_cost;
    } 

    if (op_time == 0)
    {
        DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_GOLD_COIN);
        return;
    }

    Game_Data::Item_Container* container = player->get_empty_bag_container();
    if (!container)
    {
        DICTIONARY_CONFIG_MGR::instance()->show_alert(BAG_FULL_TIPS);
        return;
    }

    std::vector<uint64> para;
    para.push_back(gem_id);
    para.push_back(time);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("send_gem_level_up", para);
}

void Item_Logic::buy_item(int goods_id,int count)
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return;
    }

    Game_Data::shop_config* shop_config = SHOP_CONFIG_MGR::instance()->get_shop_config(goods_id);
    if (!shop_config)
    {
        return;
    }

    if (shop_config->buy_count_ > 0)
    {
        Game_Data::shoping_record* record = player->get_shoping_record(goods_id);
        if (record && (record->buy_count_ + count) > shop_config->buy_count_)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(TODAY_PURCHASE_TIMES_OVER);
            return;
        }
    }

    Item_Config* item_config = ITEM_CONFIG_MGR::instance()->get_item_config(shop_config->item_base_id_);
    if (!item_config)
    {
        return;
    }

    if (PLAYER_LOGIC::instance()->check_bag_room(player_id,item_config->base_id,count) == false)
    {
        DICTIONARY_CONFIG_MGR::instance()->show_alert(BAG_FULL_TIPS);
        return;
    }

    int cost = shop_config->cost_ * shop_config->discount_ / 10000 * count;
    if (shop_config->money_type_ == MT_GOLD_MONEY)
    {
        if (player->get_gold() < cost)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_GOLD_COIN);
            return;
        }

        std::vector<uint64> para;
        para.push_back(goods_id);
        para.push_back(count);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_buy_item", para);
    }
    else
    {
        if (player->get_token() < cost)
        {   
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_GOLD_INGOT);
            return;
        }

        const char* format = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SHOP_PURCHASE_INFO);
        const char* name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(item_config->name);
        const char* purchaseInfo = CCString::createWithFormat(format,cost,count,name)->getCString();
        UI_ModalDialogue_Layer::DoModal("",purchaseInfo,UI_ModalDialogue_Layer::DT_YES_NO,[=]()
        {
            std::vector<uint64> para;
            para.push_back(goods_id);
            para.push_back(count);
            Game_Logic::Game_Content_Interface::instance()->exec_interface("send_buy_item", para);            
        }
        );
    }
}
#include <fstream>
uint64 Item_Logic::GetTargetPosEquipItemID(const int nCharacterID, const int nEquipPos)
{
	/************************************************************************/
	// 判断目标角色的目标位置是否存在装备
	// 1. 判断目标玩家的目标角色是否存在
	int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* pPlayer = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(nPlayerID));
	if (pPlayer == NULL)
		return 0;

	Game_Data::Character* pCharacter = CHARACTER_MGR::instance()->get_character(nCharacterID);
	if (pCharacter == NULL)
		return 0;

	// 2. 判断该角色的目标装备位置是否存在装备
	Game_Data::Item* pEquipment = pCharacter->get_item_from_equipment_bar(nEquipPos);
	if (pEquipment == NULL)
		return 0;

	/************************************************************************/
	// 目标角色的目标位置存在装备,则返回该装备的ItemID
	return pEquipment->id;	
}
