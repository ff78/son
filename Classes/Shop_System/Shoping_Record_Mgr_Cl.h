
#ifndef __SHOPING_RECORD_MGR_H__
#define __SHOPING_RECORD_MGR_H__

#include "Game_Interface/common.h"
#include "Shoping_Record_Data.h"

class message_stream;
namespace Game_Data
{
    class Player;
    class Shoping_Record_Mgr
    {
    public:
        Shoping_Record_Mgr();
        virtual ~Shoping_Record_Mgr();

        static Shoping_Record_Mgr* instance();

        int release();

        shoping_record* get_shoping_record(int goods_id);

        void load_shoping_record(Player* player,message_stream& ms);
        void create_shoping_record(Player* player,int goods_id,int count);

    private:
        static Shoping_Record_Mgr*         instance_;

        shoping_record_map                 shoping_record_map_;
    };
}


typedef Game_Data::Shoping_Record_Mgr SHOPING_RECORD_MGR;


#endif /* __SHOPING_RECORD_MGR_H__ */
