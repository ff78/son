

#include "Function_Open_Logic.h"
#include "Function_Open_System/Function_Open_Config_Mgr.h"

#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"

#ifdef GAME_CLIENT
#include "UI_Interface/UI_MainMenu_Layer.h"
#endif

namespace Game_Data
{
    Function_Open_Logic* Function_Open_Logic::instance_ = NULL;
    Function_Open_Logic::Function_Open_Logic()
    {
		memset(open_icon_array, 0, sizeof(open_icon_array));

		for ( int i=0; i<(int)Game_Data::ICON_SUM; ++i )
		{
			int quest_id = FUNCTION_OPEN_CONFIG_MGR::instance()->get_cur_index_point_quest_id(i);
			open_icon_array[i] = quest_id;
		}
    }

    Function_Open_Logic::~Function_Open_Logic()
    {

    }

    Function_Open_Logic* Function_Open_Logic::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Function_Open_Logic;
        }

        return instance_;
    }

	void Function_Open_Logic::submit_quest_open(int player_id,int quest_id)
	{
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

		if ( //quest_id == open_icon_array[Game_Data::ICON_AUTO_FIGHT_BTN] || 
			quest_id == open_icon_array[Game_Data::ICON_BAG_SELL_BTN])
		{
			player->add_function_open_id();
		}

#ifdef GAME_CLIENT
		if ( quest_id == open_icon_array[Game_Data::ICON_BAG_SELL_BTN] )
		{
			CCLog("Here open sell button of bag");
			UI_MainMenu_Layer::get_instance()->visibleFuncOpen(COMMON_SELL, ICON_BAG_SELL_BTN);
		}

		//if ( quest_id == open_icon_array[Game_Data::ICON_AUTO_FIGHT_BTN] )
		//{
		//	CCLog("Here open TuoGuan button");
			//UI_MainMenu_Layer::get_instance()->visibleFuncOpen();
		//}
#endif

	}

	void Function_Open_Logic::accept_quest_open(int player_id,int quest_id)
	{
		return; //yypp
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

		for ( int i=(int)Game_Data::ICON_NONE; i<(int)Game_Data::ICON_SUM; ++i )
		{
			if( quest_id == open_icon_array[i] && 
				(quest_id != open_icon_array[Game_Data::ICON_BAG_SELL_BTN]))//(quest_id != open_icon_array[Game_Data::ICON_AUTO_FIGHT_BTN]) && 
			{
				player->add_function_open_id();
			}
		}

#ifdef GAME_CLIENT
		//open bag
		if( quest_id == open_icon_array[Game_Data::ICON_BAG_TAG] )
		{
			//setIconNum(getIconNum()+1); //设置开启数量
			//Here add notice information and icon function
			UI_MainMenu_Layer::get_instance()->visibleFuncOpen(BAG_TITLE, ICON_BAG_TAG);
		}
		//open equipment
		//else if ( quest_id == open_icon_array[Game_Data::ICON_EQUIP_TAG] )
		//{
		//	UI_MainMenu_Layer::get_instance()->visibleFuncOpen(EQUIPMENT_TITLE, ICON_EQUIP_TAG);
		//}
		//open xin fa
		//else if ( quest_id == open_icon_array[Game_Data::ICON_XINFA_TAG] )
		//{
		//	UI_MainMenu_Layer::get_instance()->visibleFuncOpen(HEART_METHOD_TITLE, ICON_XINFA_TAG);
		//}
		//open skill
		else if ( quest_id == open_icon_array[Game_Data::ICON_SKILL_TAG] )
		{
			UI_MainMenu_Layer::get_instance()->visibleFuncOpen(SKILL_TITLE, ICON_SKILL_TAG);
		}
		//open fate
		//else if ( quest_id == open_icon_array[Game_Data::ICON_ARENA_TAG] )
		//{
		//	UI_MainMenu_Layer::get_instance()->visibleFuncOpen(ARENA_ARENE_TITLE, ICON_ARENA_TAG);
		//}
		//open arena
		//else if ( quest_id == open_icon_array[Game_Data::ICON_FATE_TAG] )
		//{
		//	UI_MainMenu_Layer::get_instance()->visibleFuncOpen(UI_FATE, ICON_FATE_TAG);
		//}
#endif

	}
    
}

