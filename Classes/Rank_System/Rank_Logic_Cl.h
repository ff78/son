
#ifndef __RANK_LOGIC_H__
#define __RANK_LOGIC_H__

#include "Rank_Data.h"

using namespace std;
namespace Game_Data
{
    class Rank_Logic
    {
    public:
        Rank_Logic();
        virtual ~Rank_Logic();

        static Rank_Logic* instance();

    public:
        void load_rank();
        void load_rank_role_level();
        void load_rank_role_fighting_capacity();
        void load_rank_role_have_gold();

    private:
        static Rank_Logic*      instance_;
        
    };
}

typedef Game_Data::Rank_Logic RANK_LOGIC;


#endif /* __RANK_LOGIC_H__ */
