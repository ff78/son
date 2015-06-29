
#ifndef __ACUPOINT_LOGIC_H__
#define __ACUPOINT_LOGIC_H__

#include "Acupoint_Data.h"

using namespace std;
namespace Game_Data
{
    class Acupoint_Logic
    {
    public:
        Acupoint_Logic();
        virtual ~Acupoint_Logic();

        static Acupoint_Logic* instance();

    public:
        void load_acupoint();
        bool open_acupoint(int type);

    private:
        static Acupoint_Logic*          instance_;
        
    };
}

typedef Game_Data::Acupoint_Logic ACUPOINT_LOGIC;


#endif /* __ACUPOINT_LOGIC_H__ */
