#include "Network_Common/NetManager.h"
#include "Network_Common/message.h"
#include "Network_Common/message_coder.h"
#include "Network_Common/message_stream.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "UI/Main_City_Scene.h"
#include "Partition_Msg_Proc_Cl.h"
#include "Platform_Dependence/Dependence.h"
#include "Common/GameDefine.h"
#include "UI/Login_Scene.h"
#include "Common/Utils.h"
USING_NS_CC;

Partition_Msg_Proc_Cl* Partition_Msg_Proc_Cl::instance_ = 0;
Partition_Msg_Proc_Cl::Partition_Msg_Proc_Cl()
{

}

Partition_Msg_Proc_Cl::~Partition_Msg_Proc_Cl()
{

}

Partition_Msg_Proc_Cl* Partition_Msg_Proc_Cl::instance()
{
    if(NULL == instance_)
        instance_ = new Partition_Msg_Proc_Cl;

    return instance_;
}

bool Partition_Msg_Proc_Cl::on_ask_partition_info( Game_Logic::Game_Interface& gm_interface )
{

	CCLog("-------------------------------on_ask_partition_info");
	std::string partition_server_list;

	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	body_ms >> partition_server_list;

	vector<uint64> para;
	Game_Logic::Game_Content_Interface::instance()->exec_interface("closeserver", para, "partition");

	Account_Data_Mgr::instance()->load_server_list_from_str(partition_server_list.c_str(), partition_server_list.size());
	Director* pDirector = Director::getInstance();
	if (!pDirector)
	{
		return false;
	}
	if (pDirector->getRunningScene() == 0)
	{
		pDirector->runWithScene(UI::Main_City_Scene::scene());
	}
	else
	{
		pDirector->replaceScene(UI::Main_City_Scene::scene());
	}
	return true;
}

bool Partition_Msg_Proc_Cl::send_ask_partition_info( Game_Logic::Game_Interface& gm_interface )
{
	std::string ip = Account_Data_Mgr::instance()->partition_server_ip();
	int port = Account_Data_Mgr::instance()->partition_server_port();

	vector<uint64> para;
	para.push_back(port);
	if(!Game_Logic::Game_Content_Interface::instance()->exec_interface("connecttogame", para, ip.data()))
	{
		Login_Scene* ls=Login_Scene::sharedInstance();
		if(ls)
		{
			ls->sendMessage(Login_Scene::EVENT_TYPE_GOT_SERVER_FAILED);
		}
	}
	vector<uint64> para2;
	gm_interface.get_para(para2);
	if( para2.size() < 0)
	{
		return false;
	}

	char body[256] = {0};
	message_stream body_ms(body, sizeof(body));
	body_ms << C2S_ASK_PARTITION_SERVER_LIST;

	CNetManager::GetMe()->send_msg( body_ms );
	return true;
}


