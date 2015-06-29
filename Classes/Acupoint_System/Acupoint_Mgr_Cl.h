
#ifndef __ACUPOINT_MGR_H__
#define __ACUPOINT_MGR_H__

#include "Acupoint_Data.h"

class message_stream;
namespace Game_Data
{
    class Player;
    class Acupoint_Mgr
    {
    public:
        Acupoint_Mgr();
        virtual ~Acupoint_Mgr();

        static Acupoint_Mgr* instance();

        void release();

    public:
        void load_acupoint(Player* player,message_stream& ms);
        void open_acupoint(Player* player,message_stream& ms);

        void create_acupoint(Player* player,message_stream& ms);

        void insert_acupoint(Acupoint* acupoint);
        void remove_acupoint(int type);
        Acupoint* get_acupoint(int type);
        Acupoint_Map* get_acupoint_map(){return &acupoint_map_;}

    private:
        static Acupoint_Mgr*        instance_;

        Acupoint_Map                acupoint_map_;
    };
}

typedef Game_Data::Acupoint_Mgr ACUPOINT_MGR;


#endif /* __ACUPOINT_MGR_H__ */
