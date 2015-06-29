
#ifndef __COOL_TIME_CONFIG_DATA_H__
#define __COOL_TIME_CONFIG_DATA_H__


enum Cool_Time_Type
{
    CTT_OPEN_ACUPOINT = 0,

    CTT_MAX,
};

namespace Game_Data
{
    // ��ȴʱ������
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

        int                     base_id_;                           // ��ID
        int                     type_;                              // ����
        int                     over_;		                        // ʱ����ȴ��ֵ���ۼƳ�����ֵ�Ϳ�ʼ��ȴ(��)
        int                     add_time_;		                    // ��λ������ӵ�ʱ��(��)
        int                     unit_cost_;	                        // ��λ���ʱ���������(����)
        int                     interval_;	                        // ���ʱ�仨�ѵļ�����(��)
    };
}

#endif /* __COOL_TIME_CONFIG_DATA_H__ */

