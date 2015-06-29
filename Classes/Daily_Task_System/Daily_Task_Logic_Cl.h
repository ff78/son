
#ifndef __DAILY_TASK_LOGIC_H__
#define __DAILY_TASK_LOGIC_H__

namespace Game_Data
{
    class Daily_Task_Logic
    {
    public:
        Daily_Task_Logic();
        virtual ~Daily_Task_Logic();

        static Daily_Task_Logic* instance();

    public:
        void load_daily_task();
        void op_daily_task();
        void refresh_daily_task_star_level();
        void set_daily_task_star_level_max();
        void token_complete_daily_task();
        void get_daily_task_gift_one();
        void get_daily_task_gift_two();
        void get_daily_task_gift_three();

    private:
        void drop_daily_task();
        void submit_daily_task();

    private:
        static Daily_Task_Logic*        instance_;
        
    };
}

typedef Game_Data::Daily_Task_Logic DAILY_TASK_LOGIC;


#endif /* __DAILY_TASK_LOGIC_H__ */
