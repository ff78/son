#include "cocos2d.h"

//#include "UI_Interface/UI_Dialogue_Layer/UI_Dialogue_Layer.h"

#include "Network_Common/message_stream.h"
#include "RadiateSystem/Radiate_Msg_Proc.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
#include "Game_Interface/event_define.h"

#include "UI/Message_Layer.h"

Radiate_Msg_Proc* Radiate_Msg_Proc::instance_ = 0;

Radiate_Msg_Proc::Radiate_Msg_Proc()
{

}

Radiate_Msg_Proc::~Radiate_Msg_Proc()
{

}


Radiate_Msg_Proc* Radiate_Msg_Proc::instance()
{
	if(!instance_)
		instance_ = new Radiate_Msg_Proc;

	return instance_;
}

bool Radiate_Msg_Proc::PlaySystemMsgForUI(Game_Logic::Game_Interface& gm_interface)
{
	/************************************************************************/
	// 播放从服务器得到的广播信息(系统触发)
	// 1. 解析消息
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	std::string _msg;
	body_ms >> _msg;

	// 2. 通知客户端显示
	if (!UIPlayMsg(_msg))
		return false;

	return true;
}

bool Radiate_Msg_Proc::PlayPlayerMsgForUI(Game_Logic::Game_Interface& gm_interface)
{
	/************************************************************************/
	// 播放从服务器得到的广播信息(玩家行为触发)
	// 1. 解析消息
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	std::string _msg;
	body_ms >> _msg;

	// 2. 通知客户端显示
	if (!UIPlayMsg(_msg))
		return false;

	return true;
}

bool Radiate_Msg_Proc::UIPlayMsg(std::string strMsg)
{
	/************************************************************************/
	// 显示层播放消息
	// 1. 获取当前场景
	Scene* pScene = Director::getInstance()->getRunningScene();
	if (pScene == nullptr)
		return false;
	
	// 2. 获取消息页面
	UI::Message_Layer * pMsgLayer = dynamic_cast<UI::Message_Layer *>(pScene->getActionByTag(999));
	if (pMsgLayer == nullptr)
	{
		pMsgLayer = UI::Message_Layer::create();
		pMsgLayer->setTag(999);
		pMsgLayer->setZOrder(9001);
		pScene->addChild(pMsgLayer);
	}
	pMsgLayer->add_message(strMsg.c_str());
}
