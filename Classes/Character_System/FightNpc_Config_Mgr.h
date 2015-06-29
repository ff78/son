

#ifndef __FightNpc_MGR_H__
#define __FightNpc_MGR_H__

#include <list>

#include "Game_Interface/game_element.h"
#include "FightNpc_Config_Data.h"
namespace Game_Data
{
	struct FightNpc_Base_Attr_Config_Data;
	struct FightNpc_Level_Attr_Config_Data;
	
	class FightNpc_Mgr
	{
	public:
		FightNpc_Mgr();
		virtual ~FightNpc_Mgr();

        static FightNpc_Mgr* instance();

		int initialize( void );
	public:
		FightNpc_Base_Attr_Config_Data* get_base_attr_config_data(int id);
		FightNpc_Level_Attr_Config_Data* get_level_attr_config_data(int id, int level_id, int level);

	private:

		int load_FightNpc_Base_Attr_Config_Data(void);
		int load_FightNpc_Level_Attr_Config_Data(void);

    private:
        static FightNpc_Mgr*                        instance_;

        std::list<FightNpc_Base_Attr_Config_Data>   FightNpc_base_attr_data_list_;
		std::list<FightNpc_Level_Attr_Config_Data>  FightNpc_level_attr_data_list_;
	};
}


typedef Game_Data::FightNpc_Mgr FIGHTNPC_MGR;


#endif /* __FightNpc_MGR_H__ */
