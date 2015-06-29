
#ifndef __RELATION_MSG_PROC_H__
#define __RELATION_MSG_PROC_H__

#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"
#include "Relation_System/Relation_Common.h"

class message_stream;
class Relation_Msg_Proc
{

public:
    Relation_Msg_Proc();
    virtual ~Relation_Msg_Proc();
    static Relation_Msg_Proc* instance();

public:
	//---发送消息---//
    static bool send_add_friend(Game_Logic::Game_Interface& gm_interface);
	static bool send_del_friend(Game_Logic::Game_Interface& gm_interface);
	static bool send_ask_friend_info(Game_Logic::Game_Interface& gm_interface);
	static bool send_ask_friend_list(Game_Logic::Game_Interface& gm_interface);

public:
	//---接收消息---//
	static bool on_add_friend(Game_Logic::Game_Interface& gm_interface);				   // 从服务器接收消息添加好友 
	static bool on_del_friend(Game_Logic::Game_Interface& gm_interface);				   // 从服务器接收删除目标好友
	static bool on_ask_friend_info(Game_Logic::Game_Interface& gm_interface);
	static bool on_ask_friend_list(Game_Logic::Game_Interface& gm_interface);			   // 从服务器获取好友列表
	static bool on_add_friend_from_apply(Game_Logic::Game_Interface& gm_interface);		   // 从服务器接收消息添加申请好友 


public:
	long getLocalTimeRecord();
	void setLocalTimeRecord(long t);

private:
	long getCurrentTime();

private:
    static Relation_Msg_Proc* instance_;
	long		localTimeRecord;
};
#endif // __RELATION_MSG_PROC_H__

