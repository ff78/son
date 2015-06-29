
#ifndef __RADIATE_MSG_PROC_H__
#define __RADIATE_MSG_PROC_H__

#include "Game_Interface/common.h"

namespace Game_Logic
{
	struct Game_Interface;
}

class Radiate_Msg_Proc
{
public:
	Radiate_Msg_Proc();
	virtual  ~Radiate_Msg_Proc();

	static Radiate_Msg_Proc* instance();

public:
	static bool PlaySystemMsgForUI(Game_Logic::Game_Interface& gm_interface);	// ���Ŵӷ������õ��Ĺ㲥��Ϣ(ϵͳ����)
	static bool PlayPlayerMsgForUI(Game_Logic::Game_Interface& gm_interface);	// ���Ŵӷ������õ��Ĺ㲥��Ϣ(�����Ϊ����)

private:
	static bool UIPlayMsg(std::string strMsg);									// ��ʾ�㲥����Ϣ

private:
	static Radiate_Msg_Proc* instance_;

};

#endif // __RADIATE_MSG_PROC_H__