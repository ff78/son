

#ifndef __DAILY_TASK_CONFIG_DATA_H__
#define __DAILY_TASK_CONFIG_DATA_H__

#define STAR_LEVEL_MAX              5
#define DAILY_TASK_COUNT_MAX        10

#define REFRESH_DAILY_TASK_STAR_LEVEL_COST      5
#define SET_DAILY_TASK_STAR_LEVEL_MAX_COST      100
#define TOKEN_COMPLETE_DAILY_TASK_COST          100

#define GET_DAILY_TASK_GIFT_ONE_NEED_COMPLETE_COUNT         3
#define GET_DAILY_TASK_GIFT_TWO_NEED_COMPLETE_COUNT         6
#define GET_DAILY_TASK_GIFT_THREE_NEED_COMPLETE_COUNT       10

#define DAILY_TASK_GIFT_ONE_ITEM_ID         81200   
#define DAILY_TASK_GIFT_TWO_ITEM_ID         81201
#define DAILY_TASK_GIFT_THREE_ITEM_ID       81202

#include <string>
#include <map>
#include <list>

using namespace std;
namespace Game_Data
{
    enum Daily_Task_Type
    {
        DTT_COST_TOKEN = 1,         // 花费元宝
        DTT_UPGRADE_EQUIPMENT,      // 强化装备
        DTT_OFFLINE_FIGHT,          // 竞技场
        DTT_INSTANCE,               // 副本
        DTT_UPGRADE_SKILL,          // 强化技能
    };

    struct daily_task_config
    {
        daily_task_config()
        {
            reset();
        }

        ~daily_task_config() {}

        void reset()
        {
            base_id_ = 0;
            type_ = 0;
            count_ = 0;
            exp_ = 0;
            money_ = 0;
            name_ = 0;
            icon_ = 0;
            desc_ = 0;
        }

        int base_id_;
        int type_;          // 任务条件类型
        int count_;         // 需要达成条件的次数
        int exp_;
        int money_;
        int name_;
        int icon_;
        int desc_;
    };

    typedef map<int, daily_task_config*>                daily_task_config_map;
    typedef daily_task_config_map::iterator		        daily_task_config_map_iter;
}

#endif /* __DAILY_TASK_CONFIG_DATA_H__ */

