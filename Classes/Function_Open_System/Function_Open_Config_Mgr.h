

#ifndef __FUNCTION_OPEN_CONFIG_MGR_H__
#define __FUNCTION_OPEN_CONFIG_MGR_H__

#include "Function_Open_Config_Data.h"

namespace Game_Data
{
    class function_open_config_mgr
    {
    public:
        function_open_config_mgr();
        virtual ~function_open_config_mgr();
        static function_open_config_mgr* instance();

        int initialize();
		int get_map_size();
		int get_cur_index_point_quest_id( int index );
		function_open_config* get_cur_index_point_config( int index );

    private:
        int load_function_open_config_data();

    private:
        static function_open_config_mgr*		instance_;
		function_open_config_map				function_open_config_map_;
    };
}


typedef Game_Data::function_open_config_mgr FUNCTION_OPEN_CONFIG_MGR;


#endif /* __FUNCTION_OPEN_CONFIG_MGR_H__ */
