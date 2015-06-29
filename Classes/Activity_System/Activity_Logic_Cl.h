

#ifndef __ACTIVITY_LOGIC_H__
#define __ACTIVITY_LOGIC_H__

namespace Game_Data
{
    class Activity_Logic
    {
    public:
        Activity_Logic();
        virtual ~Activity_Logic();

        static Activity_Logic* instance();

    public:
        void activity_six_sect(int base_id);


        bool check_activity(int activity_type);

    private:
        static Activity_Logic*      instance_;
        
    };
}

typedef Game_Data::Activity_Logic ACTIVITY_LOGIC;


#endif /* __ACTIVITY_LOGIC_H__ */
