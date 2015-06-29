
#ifndef __COOL_TIME_CONFIG_DATA_H__
#define __COOL_TIME_CONFIG_DATA_H__


enum Cool_Time_Type
{
    CTT_OPEN_ACUPOINT = 0,

    CTT_MAX,
};

namespace Game_Data
{
    // 冷却时间配置
    struct cool_time_config
    {
        cool_time_config()
        {
            reset();
        }

        ~cool_time_config()
        {
            reset();
        }

        void reset()
        {
            base_id_ = 0;
            type_ = 0;
            over_ = 0;
            add_time_ = 0;
            unit_cost_ = 0;
            interval_ = 0;
        }

        int                     base_id_;                           // 表ID
        int                     type_;                              // 类型
        int                     over_;		                        // 时间冷却阀值，累计超过该值就开始冷却(秒)
        int                     add_time_;		                    // 单位间隔增加的时间(秒)
        int                     unit_cost_;	                        // 单位间隔时间清除花费(代币)
        int                     interval_;	                        // 清除时间花费的计算间隔(秒)
    };
}

#endif /* __COOL_TIME_CONFIG_DATA_H__ */

