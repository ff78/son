
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
	static bool PlaySystemMsgForUI(Game_Logic::Game_Interface& gm_interface);	// 播放从服务器得到的广播信息(系统触发)
	static bool PlayPlayerMsgForUI(Game_Logic::Game_Interface& gm_interface);	// 播放从服务器得到的广播信息(玩家行为触发)

private:
	static bool UIPlayMsg(std::string strMsg);									// 显示层播放消息

private:
	static Radiate_Msg_Proc* instance_;

};

#endif // __RADIATE_MSG_PROC_H__