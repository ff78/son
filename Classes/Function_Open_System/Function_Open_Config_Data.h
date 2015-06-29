#ifndef __FUNCTION_OPEN_CONFIG_DATA_H__
#define __FUNCTION_OPEN_CONFIG_DATA_H__

#include <map>
using namespace std;

namespace Game_Data
{
	enum IconOpen
	{
		ICON_NONE = 0,
		ICON_BAG_TAG,			//bag button

		//ICON_EQUIP_TAG,			//equipment button (main)
		//ICON_AUTO_FIGHT_BTN,	//hosting button
		ICON_BAG_SELL_BTN,		//bag sell button

		//ICON_XINFA_TAG,			//xin fa (main)
		//ICON_XINFA_EQUIP_BTN,	//xin fa equipment button
		//ICON_BAG_COMBINE_BTN,	//combine button in bag
		//ICON_EQUIP_QUA_UP_BTN,	//equipment quality up

		ICON_SKILL_TAG,			//skill button (main)
		//ICON_XINFA_COMBINE_BTN,	//xin fa combine button

		//ICON_ARENA_TAG,			//arena button (main)
		//ICON_ROLE_QUA_BTN,		//role role quality
		//ICON_ARENA_GET_BTN,		//arena gain button
		//ICON_LIEU_FIGHT_BTN,	//lieutenant fihgting button

		//ICON_FATE_TAG,			//fate button (main)
		//ICON_XINFA_QUA_BTN,		//xin fa quality button
		ICON_SUM,
	};

    struct function_open_config
    {
       int				index_;
	   int				quest_id_;
    };


	typedef map<int, function_open_config*>				function_open_config_map;
	typedef function_open_config_map::iterator			function_open_config_map_iter;
}

#endif /* __FUNCTION_OPEN_CONFIG_DATA_H__ */

