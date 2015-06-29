
#ifndef __COOL_TIME_LOGIC_H__
#define __COOL_TIME_LOGIC_H__

#include "Cool_Time_Data.h"

using namespace std;
namespace Game_Data
{
    class Cool_Time_Logic
    {
    public:
        Cool_Time_Logic();
        virtual ~Cool_Time_Logic();

        static Cool_Time_Logic* instance();

    public:
        void load_cool_time();
        bool clean_cool_time(int type);

    private:
        static Cool_Time_Logic*     instance_;
        
    };
}

typedef Game_Data::Cool_Time_Logic COOL_TIME_LOGIC;


#endif /* __COOL_TIME_LOGIC_H__ */
