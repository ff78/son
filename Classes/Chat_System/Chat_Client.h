#ifndef __CHAT_MSG_PROC_H__
#define __CHAT_MSG_PROC_H__
#include <string>

namespace Game_Logic
{
	struct Game_Interface;
};

class Chat_Msg_Proc
{
public:
	Chat_Msg_Proc();
	virtual ~Chat_Msg_Proc();
	static Chat_Msg_Proc* getInstance();

	static bool send_chat_all_msg(int channel, const char* receiver_name, const char* chat);      //区域
	static bool send_chat_private_msg(int channel, const char* receiver_name, const char* chat);  //私密
	static bool send_chat_team_msg(int channel, const char* receiver_name, const char* chat);     //组队
	static bool send_chat_friend_msg(int channel, const char* receiver_name, const char* chat);   //好友
	static bool send_chat_faction_msg(int channel, const char* receiver_name, const char* chat);  //工会
	static bool send_chat_world_msg(int channel, const char* receiver_name, const char* chat);    //世界
	static bool send_chat_area_msg(int channel, const char* receiver_name, const char* chat);

	static bool on_chat_all_msg(Game_Logic::Game_Interface& gm_interface);                        //综合
	static bool on_chat_private_msg(Game_Logic::Game_Interface& gm_interface);                    //私密
	static bool on_chat_team_msg(Game_Logic::Game_Interface& gm_interface);                       //组队
	static bool on_chat_friend_msg(Game_Logic::Game_Interface& gm_interface);                     //好友
	static bool on_chat_faction_msg(Game_Logic::Game_Interface& gm_interface);                    //工会
	static bool on_chat_world_msg(Game_Logic::Game_Interface& gm_interface);                      //世界
	static bool on_chat_area_msg(Game_Logic::Game_Interface& gm_interface);                       //区域

private:
	static Chat_Msg_Proc* instance_;

};

namespace Game_Data
{
	class Chat_Logic
	{
	private:
		int mChannel;
		static Chat_Logic* _instance;
	public :
		static Chat_Logic* getInstance();
		int get_channel(){ return mChannel; }
		void set_channel(int para){ mChannel = para; }

		std::string mMessageSend;
		std::string get_msg_send(){ return mMessageReceived; }
		void set_msg_send(std::string para){ mMessageSend = para; }

		std::string mMessageReceived;
		std::string get_msg_received(){ return mMessageReceived; }
		void set_msg_received(std::string para){ mMessageReceived = para; }

		void clear_msg(){ mChannel = 0; mMessageSend.clear(); mMessageReceived.clear(); }

		void send_chat_msg_all(int channel, const char* receiver_name, const char* chat);
		void send_chat_msg_faction(int channel, const char* receiver_name, const char* chat);
		void send_chat_msg_world(int channel, const char* receiver_name, const char* chat);
		void send_chat_msg_friend(int channel, const char* receiver_name, const char* chat);
		void send_chat_msg_team(int channel, const char* receiver_name, const char* chat);
		void send_chat_msg_private(int channel, const char* receiver_name, const char* chat);
		void send_chat_msg_area(int channel, const char* receiver_name, const char* chat);
	};

}

typedef Game_Data::Chat_Logic CHAT_LOGIC;

#endif