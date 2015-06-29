
#ifndef __LOTTERY_CONFIG_MGR_H__
#define __LOTTERY_CONFIG_MGR_H__

#include "Game_Interface/common.h"
#include "Lottery_Data_Common.h"

namespace Game_Data
{
    class Lottery_Config_Mgr
    {
    public:
        Lottery_Config_Mgr();
        virtual ~Lottery_Config_Mgr();

        static Lottery_Config_Mgr* instance();

        int initialize(void);
        int release(void);

    private:

		int load_lottery_category_config_data();

        void proc_string(const string& content_str, item_content &ic);

    private:
        static Lottery_Config_Mgr*         instance_;

		LotteryCategory_Map				map_lottery_category_config_;


    };
}


typedef Game_Data::Lottery_Config_Mgr Lottery_Config_Mgr;


#endif /* __LOTTERY_CONFIG_MGR_H__ */
