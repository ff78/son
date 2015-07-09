
#ifndef __PLAYER_LOGIC_H__
#define __PLAYER_LOGIC_H__

#include "Game_Interface/game_element.h"

#include "cocos2d.h"
USING_NS_CC;

namespace Game_Data
{
    class Player;
    class Player_Logic : public Node
    {
    public:
        Player_Logic();
        virtual ~Player_Logic();

        static Player_Logic* instance();

        virtual void update(float delta);
        void start_update();

    public:
        void get_main_city_player();
        void player_move();
        void get_player_info();
        void send_chat_msg(const char* chat);
		void send_chat_msg(int channel, const char* receiver_name, const char* chat);
		/************************* dely *************************/
		void send_chat_msg_all(int channel, const char* receiver_name, const char* chat);
		void send_chat_msg_faction(int channel, const char* receiver_name, const char* chat);
		void send_chat_msg_world(int channel, const char* receiver_name, const char* chat);
		void send_chat_msg_friend(int channel, const char* receiver_name, const char* chat);
		void send_chat_msg_team(int channel, const char* receiver_name, const char* chat);
		void send_chat_msg_private(int channel, const char* receiver_name, const char* chat);
		/************************* dely *************************/
        void player_buy_energy();
//        void player_callup_deputy_general(int character_id);
        void player_quality_up(int character_id);

        bool check_bag_room(int player_id,game_element_list_t& ele_list);
        bool check_bag_room(int player_id,int item_base_id,int count);

//        bool check_can_use(int player_id,game_element_list_t& ele_list);

    private:
        void calc_need_bag_room(Player* player,int item_base_id,int count,int& need_bag_count);
        
    private:
        static Player_Logic*         instance_;

        int check_x;
        int check_y;
    };
}

typedef Game_Data::Player_Logic PLAYER_LOGIC;


#endif /* __PLAYER_LOGIC_H__ */
