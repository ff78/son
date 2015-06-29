
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
	//---������Ϣ---//
    static bool send_add_friend(Game_Logic::Game_Interface& gm_interface);
	static bool send_del_friend(Game_Logic::Game_Interface& gm_interface);
	static bool send_ask_friend_info(Game_Logic::Game_Interface& gm_interface);
	static bool send_ask_friend_list(Game_Logic::Game_Interface& gm_interface);

public:
	//---������Ϣ---//
	static bool on_add_friend(Game_Logic::Game_Interface& gm_interface);				   // �ӷ�����������Ϣ��Ӻ��� 
	static bool on_del_friend(Game_Logic::Game_Interface& gm_interface);				   // �ӷ���������ɾ��Ŀ�����
	static bool on_ask_friend_info(Game_Logic::Game_Interface& gm_interface);
	static bool on_ask_friend_list(Game_Logic::Game_Interface& gm_interface);			   // �ӷ�������ȡ�����б�
	static bool on_add_friend_from_apply(Game_Logic::Game_Interface& gm_interface);		   // �ӷ�����������Ϣ���������� 


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

