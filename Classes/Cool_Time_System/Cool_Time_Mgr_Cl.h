
#ifndef __COOL_TIME_MGR_H__
#define __COOL_TIME_MGR_H__

#include "Cool_Time_Data.h"

#include "cocos2d.h"

USING_NS_CC;

class message_stream;
namespace Game_Data
{
    class Player;
    class Cool_Time_Mgr : public Node
    {
    public:
        Cool_Time_Mgr();
        virtual ~Cool_Time_Mgr();

        static Cool_Time_Mgr* instance();

        void release();

    public:
        void load_cool_time(Player* player,message_stream& ms);
        void create_cool_time(Player* player,message_stream& ms);

        void insert_cool_time(Cool_Time* acupoint);
        void remove_cool_time(int type);
        Cool_Time* get_cool_time(int type);
        Cool_Time_Map* get_acupoint_map(){return &cool_time_map_;}

        bool is_cool(Cool_Time* cool_time);
        bool is_need_clean(Cool_Time* cool_time);
        void add_length(Cool_Time* cool_time);
        void change_length(Cool_Time* cool_time,int len);
        void clean_cool_time(Cool_Time* cool_time);
        int get_clean_cool_time_cost(Cool_Time* cool_time);

    private:
        void update_count_down(float dt);

    private:
        static Cool_Time_Mgr*       instance_;

        Cool_Time_Map               cool_time_map_;
    };
}

typedef Game_Data::Cool_Time_Mgr COOL_TIME_MGR;


#endif /* __COOL_TIME_MGR_H__ */
