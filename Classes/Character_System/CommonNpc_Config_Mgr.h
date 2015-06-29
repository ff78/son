

#ifndef __CommonNpc_MGR_H__
#define __CommonNpc_MGR_H__

#include <list>

#include "Game_Interface/game_element.h"
#include "CommonNpc_Config_Data.h"
namespace Game_Data
{
	class CommonNpcConfig;
	class CommonNpc_Config_Mgr
	{
	public:
		CommonNpc_Config_Mgr();
		virtual ~CommonNpc_Config_Mgr();

        static CommonNpc_Config_Mgr* instance();

		int initialize( void );
	public:
		CommonNpcConfig* get_commomnpc_by_id(int id);
	private:
		int load_CommonNpc_Attr_Config_Data(void);
    private:
        static CommonNpc_Config_Mgr*                        instance_;
		std::list<CommonNpcConfig>						 CommonNpc_attr_data_list_;
	};
}


typedef Game_Data::CommonNpc_Config_Mgr CommonNpc_Config_MGR;


#endif /* __CommonNpc_MGR_H__ */
