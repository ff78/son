
#ifndef __ACUPOINT_CONFIG_DATA_H__
#define __ACUPOINT_CONFIG_DATA_H__

#define VEIN_LEVEL_MAX                  6
#define ACUPOINT_POS_MAX                25
#define VEIN_COUNT_MAX                  8

#include <string>

using namespace std;
namespace Game_Data
{
    // 穴位层级数据
    struct acupoint_level_data
    {
        acupoint_level_data()
        {
            reset();
        }

        ~acupoint_level_data()
        {
            reset();
        }

        void reset()
        {
            cur_attr_ = 0;
            total_attr_ = 0;
            prestige_cost_ = 0;
            gold_cost_ = 0;
        }

        int                     cur_attr_;              // 当前增加属性
        int                     total_attr_;             // 累计增加属性
        int                     prestige_cost_;         // 消耗的声望
        int                     gold_cost_;             // 消耗的金币
        int                     suc_rate_;               // 成功率
    };

    // 穴位配置
    struct acupoint_config
    {
        acupoint_config()
        {
            reset();
        }

        ~acupoint_config()
        {
            reset();
        }

        void reset()
        {
            base_id_ = 0;
            type_ = 0;
            pos_ = 0;
            pos_x_ = 0;
            pos_y_ = 0;
            name_x_ = 0;
            name_y_ = 0;
            name_ = 0;
            attr_type_ = 0;
            level_data_->reset();
        }

        int                     base_id_;                           // 表ID
        int                     type_;                              // 脉络类型
        int                     pos_;                               // 穴位
        int                     pos_x_;                             // 点亮图标X坐标
        int                     pos_y_;                             // 点亮图标Y坐标
        int                     name_x_;                            // 名字X坐标
        int                     name_y_;                            // 名字Y坐标
        int                     name_;                              // 穴位名字
        int                     attr_type_;                         // 属性类型
        acupoint_level_data     level_data_[VEIN_LEVEL_MAX];        // 层级数据
    };

    // 脉络层级数据 
    struct vein_level_data
    {
        vein_level_data()
        {
            reset();
        }

        ~vein_level_data()
        {
            reset();
        }

        void reset()
        {
            open_level_ = 0;
            attr_type_ = 0;
            attr_ = 0;
        }

        int                     open_level_;                        // 开放等级
        int                     attr_type_;                         // 属性类型
        int                     attr_;                              // 增加属性
    };

    // 脉络配置
    struct vein_config
    {
        vein_config()
        {
            reset();
        }

        ~vein_config()
        {
            reset();
        }

        void reset()
        {
            base_id_ = 0;
            type_ = 0;
            name_ = 0;
            for (int i = 0;i < VEIN_LEVEL_MAX;++i)
            {
                level_data_[i].reset();
            }
        }

        int                     base_id_;                           // 表ID
        int                     type_;                              // 脉络类型
        int                     name_;                              // 脉络名字
        vein_level_data         level_data_[VEIN_LEVEL_MAX];        // 层级数据
    };
}

#endif /* __ACUPOINT_CONFIG_DATA_H__ */

