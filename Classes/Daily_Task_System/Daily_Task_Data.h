
#ifndef __DAILY_TASK_DATA_H__
#define __DAILY_TASK_DATA_H__

#define DAILY_TASK_GIFT_COUNT       3

#include <string>
#include <map>

using namespace std;
namespace Game_Data
{
    enum Daily_Task_Gift_Type
    {
        DTGT_ONE,
        DTGT_TWO,
        DTGT_THREE,
    };

    struct daily_task
    {
        daily_task()
        {
            reset();
        }

        ~daily_task()
        {
            reset();
        }

        void reset()
        {
            role_id_ = 0;       
            task_base_id_ = 0;
            star_level_ = 0;
            progress_ = 0;
            complete_count_ = 0;
            exec_count_ = 0;
            got_time_ = 0;
            memset(got_flag_,0,sizeof(got_flag_));
        }

        int                     role_id_;                               //
        int                     task_base_id_;                          // ��ǰ����ı�ID
        int                     star_level_;                            // ��ǰ�Ǽ�
        int                     progress_;                              // ��ǰ��������Ĵ���
        int                     complete_count_;                        // ��������ճ�����Ĵ���
        int                     exec_count_;                            // ִ���ճ�����Ĵ���(���������Ĵ���)
        int                     got_time_;                              //
        int                     got_flag_[DAILY_TASK_GIFT_COUNT];       // �Ƿ��ȡ����ɽ���
    };

    typedef map<int,daily_task*>                    daily_task_map;
    typedef daily_task_map::iterator	            daily_task_map_iter;
}

#endif /* __DAILY_TASK_DATA_H__ */

