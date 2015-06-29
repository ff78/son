
//#include <fstream>
#ifdef YN_LINUX
#include <string.h>
#endif

#include "Shoping_Record_Mgr_Cl.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Network_Common/message_stream.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"

namespace Game_Data
{
    Shoping_Record_Mgr* Shoping_Record_Mgr::instance_ = NULL;
    Shoping_Record_Mgr::Shoping_Record_Mgr()
    {

    }

    Shoping_Record_Mgr::~Shoping_Record_Mgr()
    {

    }

    Shoping_Record_Mgr* Shoping_Record_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Shoping_Record_Mgr;
        }

        return instance_;
    }

    int Shoping_Record_Mgr::release()
    {
        shoping_record* record = NULL;
        shoping_record_map_iter iter = shoping_record_map_.begin();
        for (;iter != shoping_record_map_.end();++iter)
        {
            record = iter->second;
            if (record)
            {
                delete record;
            }
        }

        shoping_record_map_.clear();
        return 0;
    }

    shoping_record* Shoping_Record_Mgr::get_shoping_record(int goods_id)
    {
        shoping_record* record = NULL;
        shoping_record_map_iter iter = shoping_record_map_.find(goods_id);
        if (iter != shoping_record_map_.end())
        {
            record = iter->second;
        }

        return record;
    }

    void Shoping_Record_Mgr::load_shoping_record(Player* player,message_stream& ms)
    {
        int record_count = 0;
        ms >> record_count;

        shoping_record* record = NULL;
        int base_id = 0;
        for (int i = 0; i < record_count; ++i)
        {
            record = new shoping_record;
            ms >> record->goods_id_;
            ms >> record->buy_count_;
           
            shoping_record_map_.insert(make_pair(record->goods_id_,record));
            player->insert_shoping_record(record);
        }
    }

    void Shoping_Record_Mgr::create_shoping_record(Player* player,int goods_id,int count)
    {
        shoping_record* record = new shoping_record;
        record->goods_id_ = goods_id;
        record->buy_count_ = count;

        shoping_record_map_.insert(make_pair(record->goods_id_,record));
        player->insert_shoping_record(record);
    }
}