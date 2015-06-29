
#include "Instance_Sweep_Data.h"

#ifndef __INSTANCE_SWEEP_DATA_MGR_H__
#define __INSTANCE_SWEEP_DATA_MGR_H__

class message_stream;
namespace Game_Data
{
    class Instance_Sweep_Data_Mgr
    {
    public:
        Instance_Sweep_Data_Mgr();
        virtual ~Instance_Sweep_Data_Mgr();

        static Instance_Sweep_Data_Mgr* instance();

        void reset();

    public:
        void set_award(message_stream& ms);
        void start_sweep(int count,int is_elite_instance);

        int get_is_elite_instance(){return is_elite_instance_;}
        int get_all_sweep_count(){return all_sweep_count_;}
        int get_cur_sweep_count(){return cur_sweep_count_;}
        bool is_keep_sweep(){return is_keep_sweep_;}
        bool is_have_enough_energy();
        bool is_have_enough_bag_room();
        Instance_Sweep_Data* get_instance_sweep_data(){return instance_sweep_data_;}

    private:
        static Instance_Sweep_Data_Mgr*     instance_;

        int                                 is_elite_instance_;
        int                                 all_sweep_count_;    // 总扫荡次数
        int                                 cur_sweep_count_;    // 当前扫荡次数
        bool                                is_keep_sweep_;
        Instance_Sweep_Data                 instance_sweep_data_[3];
    };
}

typedef Game_Data::Instance_Sweep_Data_Mgr INSTANCE_SWEEP_DATA_MGR;


#endif /* __INSTANCE_SWEEP_DATA_MGR_H__ */
