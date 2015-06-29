
#ifndef __ACUPOINT_CONFIG_DATA_H__
#define __ACUPOINT_CONFIG_DATA_H__

#define VEIN_LEVEL_MAX                  6
#define ACUPOINT_POS_MAX                25
#define VEIN_COUNT_MAX                  8

#include <string>

using namespace std;
namespace Game_Data
{
    // Ѩλ�㼶����
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

        int                     cur_attr_;              // ��ǰ��������
        int                     total_attr_;             // �ۼ���������
        int                     prestige_cost_;         // ���ĵ�����
        int                     gold_cost_;             // ���ĵĽ��
        int                     suc_rate_;               // �ɹ���
    };

    // Ѩλ����
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

        int                     base_id_;                           // ��ID
        int                     type_;                              // ��������
        int                     pos_;                               // Ѩλ
        int                     pos_x_;                             // ����ͼ��X����
        int                     pos_y_;                             // ����ͼ��Y����
        int                     name_x_;                            // ����X����
        int                     name_y_;                            // ����Y����
        int                     name_;                              // Ѩλ����
        int                     attr_type_;                         // ��������
        acupoint_level_data     level_data_[VEIN_LEVEL_MAX];        // �㼶����
    };

    // ����㼶���� 
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

        int                     open_level_;                        // ���ŵȼ�
        int                     attr_type_;                         // ��������
        int                     attr_;                              // ��������
    };

    // ��������
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

        int                     base_id_;                           // ��ID
        int                     type_;                              // ��������
        int                     name_;                              // ��������
        vein_level_data         level_data_[VEIN_LEVEL_MAX];        // �㼶����
    };
}

#endif /* __ACUPOINT_CONFIG_DATA_H__ */

