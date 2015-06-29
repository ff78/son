
#include "Network_Common/NetManager.h"
#include "Network_Common/message.h"
#include "Network_Common/message_coder.h"
#include "Network_Common/message_stream.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Relation_Msg_Proc.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Common/GameDefine.h"
#include "Item_System/Item_Config_Mgr.h"
#include "Item_System/Item_Config_Data.h"
#include "UI_Interface/UI_MainMenu_Layer.h"
#include "UI_Interface/UI_ModalDialogue_Layer.h"
#include "Relation_System/Relation_Mgr.h"
#include "UI_Interface/CocoStu_UI_Scene_Interface.h"

Relation_Msg_Proc* Relation_Msg_Proc::instance_ = 0;
Relation_Msg_Proc::Relation_Msg_Proc()
	:localTimeRecord(0)
{

}

Relation_Msg_Proc::~Relation_Msg_Proc()
{

}

Relation_Msg_Proc* Relation_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Relation_Msg_Proc;

    return instance_;
}

bool Relation_Msg_Proc::send_add_friend(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	if( para.size() < 1)
	{
		return false;
	}

	::string stranger_name = gm_interface.get_keyword();

	char body[256] = {0};
	message_stream body_ms(body, sizeof(body));
	body_ms << CS_ADD_FRIEND;
	body_ms << stranger_name.c_str();

    CNetManager::GetMe()->send_msg( body_ms );
	return true;
}

bool Relation_Msg_Proc::send_del_friend(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	if( para.size() < 1)
	{
		return false;
	}

	int relation_id = (int)para[0];

	char body[256] = {0};
	message_stream body_ms(body, sizeof(body));
	body_ms << CS_DEL_FRIEND;
	body_ms << relation_id;

    CNetManager::GetMe()->send_msg( body_ms );
	return true;
}

bool Relation_Msg_Proc::send_ask_friend_info(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	if( para.size() < 1)
	{
		return false;
	}

	::string stranger_name = gm_interface.get_keyword();

	char body[256] = {0};
	message_stream body_ms(body, sizeof(body));
	body_ms << CS_ASK_FRIEND_INFO;
	body_ms << stranger_name.c_str();;

    CNetManager::GetMe()->send_msg( body_ms );
	return true;
}

bool Relation_Msg_Proc::send_ask_friend_list(Game_Logic::Game_Interface& gm_interface)
{
	long curTime = Relation_Msg_Proc::instance()->getCurrentTime();
	long localTimeRecord = Relation_Msg_Proc::instance()->getLocalTimeRecord();
	if( (curTime - localTimeRecord ) < 5000 && 0 != localTimeRecord)
	{
		return false;
	}

	Relation_Msg_Proc::instance()->setLocalTimeRecord(curTime);
	char body[256] = {0};
	message_stream body_ms(body, sizeof(body));
	body_ms << CS_ASK_FRIEND_LIST;

    CNetManager::GetMe()->send_msg( body_ms );

	const char* loadFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(MODEL_LOADING_FONT);
	CocoStu_UI_Scene_Interface::get_instance()->lockScreen("",loadFont);
	return true;
}


bool Relation_Msg_Proc::on_add_friend_from_apply(Game_Logic::Game_Interface& gm_interface)
{
	/************************************************************************/
	// 从服务器接收消息添加申请好友 
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	int nResult = 0;
	body_ms >> nResult;

	if (nResult == 1)
	{
		Relation_Manager::instance()->AddFriendFromApplyToOwn();
	}
	return true;
}


bool Relation_Msg_Proc::on_add_friend(Game_Logic::Game_Interface& gm_interface)
{
	/************************************************************************/
	// 从服务器接收消息添加好友 
	// 1. 获取相应的好友数据
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	// 2. 解析数据
	string m_name;
	int nFriendType = 0;
	Relation_Data strData;
	memset(&strData, 0, sizeof(Relation_Data));
	body_ms >> strData.friend_role_id_;
	body_ms >> m_name;
	body_ms >> strData.level_;
	body_ms >> nFriendType;
	body_ms >> strData.nJob;
	body_ms >> strData.nVipLevel;
	body_ms >> strData.zhanli_;
	body_ms >> strData.is_online_;
	strcpy(strData.name_, m_name.c_str());
	strData.eFriendType = (RELATION_TYPE)nFriendType;

	// 3. 根据好友类型插入到不同列表中
	if (strData.eFriendType == RT_FRIEND)
	{
		Relation_Manager::instance()->AddFriendToList(FRIEND_LIST_TYPE_OWN, &strData);

	}
	else if (strData.eFriendType == RT_APPLY)
	{
		Relation_Manager::instance()->AddFriendToList(FRIEND_LIST_TYPE_APPLY, &strData);
	}
	else
	{
		return false;
	}
	return true;

								/*-----------以下代码为测试代码-----------*/
	//			// 1. 获取相应的好友数据
	//			message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	//			body_ms.set_rd_ptr(sizeof(int));
	//			
	//			string m_name;
	//			int player_id = 0;
	//			int result = 0;
	//			int friend_db_id = 0;
	//			int level = 0;
	//			int menpai_id = 0;
	//			int fujiang_id = 0;
	//			int type = 0;
	//			int is_online = 0;
	//			int zhanli = 0;
	//			
	//			body_ms >> player_id;
	//			body_ms >> result;
	//			body_ms >> friend_db_id;
	//			body_ms >> m_name;
	//			body_ms >> level;
	//			body_ms >> menpai_id;
	//			body_ms >> fujiang_id;
	//			body_ms >> type;
	//			body_ms >> is_online;
    //			body_ms >> zhanli;
	//			
	//			CCString* note_text = NULL;
	//			
	//			// 2. 根据添加好友是否成功提示不同的信息
	//			if(ART_NOT_ONLINE == result)
	//			{
	//				const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ADD_FRIEND_NOT_ONLINE);
	//				note_text = CCString::createWithFormat(szString,m_name.c_str());
	//			}
	//			else if(ART_ADD_SELF == result)
	//			{
	//				const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ADD_FRIEND_ADD_SELF);
	//				note_text = CCString::createWithFormat("%s",szString);
	//			}
	//			
	//			else if(ART_LIST_FULL == result)
	//			{
	//				const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ADD_FRIEND_FULL);
	//				note_text = CCString::createWithFormat("%s",szString);
	//			}
	//			else if(ART_ALREADY_FRIENDS == result)
	//			{
	//				const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ADD_FRIEND_ALREADY_IS);
	//				note_text = CCString::createWithFormat(szString,m_name.c_str());	
	//			}
	//			else if(ART_IN_BLACK_LIST == result)
	//			{
	//				const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ADD_FRIEND_BLACK_LIST);
	//				note_text = CCString::createWithFormat(szString,m_name.c_str());	
	//			}
	//			
	//			else if(ART_SUCCESS == result)
	//			{
	//				Relation_Data strData;
	//				memset(&strData, 0, sizeof(Relation_Data));
	//				strData.friend_role_id_	= friend_db_id;
	//				strData.general_id_		= fujiang_id;
	//				strData.level_			= level;
	//				strData.menpai_id_		= menpai_id;
	//				strData.type_			= type;
	//				strData.is_online_		= is_online;
	//				strData.zhanli_			= zhanli;
	//				strcpy(strData.name_, m_name.c_str());
	//			
	//				Relation_Manager::instance()->AddFriendToList(FRIEND_LIST_TYPE_OWN, &strData);
	//			
	//				const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ADD_FRIEND_SUCCESS);
	//				note_text = CCString::createWithFormat("%s",szString);	
	//			}
	//			
	//			//Game_Utils::instance()->show_alert(note_text->getCString());
	//			return true;

									/*-----------以上代码为测试代码-----------*/
}

bool Relation_Msg_Proc::on_del_friend(Game_Logic::Game_Interface& gm_interface)
{
	/************************************************************************/
	// 从服务器接收删除目标好友
	// 1. 获取好友ID
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	
	int success = 0;
	int friend_db_id = 0;

	body_ms >> success;
	body_ms >> friend_db_id;

	if(!success)
	{
		return false;	
	}
	// 2. 调用RelationManager中的移除好友方法
	Relation_Manager::instance()->RemoveFriendFromList(FRIEND_LIST_TYPE_OWN, friend_db_id);
	return true;
}

bool Relation_Msg_Proc::on_ask_friend_info(Game_Logic::Game_Interface& gm_interface)
{
	return true;
	//Game_Data::Friend_Detail_Data new_friend;
	//new_friend.reset();
	//
	//std::string m_name	= "";
	//
	//message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	//body_ms.set_rd_ptr(sizeof(int));
	//
	//body_ms >> new_friend.m_database_id;
	//body_ms >> m_name;
	//body_ms >> new_friend.m_level;
	//body_ms >> new_friend.m_menpai_id;
	//body_ms >> new_friend.m_fujiang_id;
	//body_ms >> new_friend.m_fujiang_level;
	//body_ms >> new_friend.m_sex;
    //body_ms >> new_friend.m_zhanli;
	//
	//strncpy(new_friend.m_name, m_name.c_str(), MAX_NAME_LEN + 1);
	//
	//int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    //Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    //if (!player)
    //{
    //    return false;
    //}
	//
	//Game_Data::Relation_Mgr::instance()->set_last_asked_friend_info(new_friend);
	//
	//Game_Logic::Game_Event_Response::instance()->on_update_selected_relation_spine(player_id);
	//
	//return true;
}

bool Relation_Msg_Proc::on_ask_friend_list(Game_Logic::Game_Interface& gm_interface)
{
	/************************************************************************/
	// 从服务器获取好友列表
	// 1. 获取好友个数
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	int friend_count = 0;
	body_ms >> friend_count;

	// 2. 获取每个好友的有关信息,并存储到RelationManager中
	string m_name;
	Relation_Data strData;
	for (int i=0; i<friend_count; i++)
	{
		memset(&strData, 0, sizeof(Relation_Data));

		body_ms >> m_name;
		body_ms >> strData.friend_role_id_;
		body_ms >> strData.level_;
		body_ms >> strData.menpai_id_;
		body_ms >> strData.general_id_;
		body_ms >> strData.type_;
		body_ms >> strData.is_online_;
		body_ms >> strData.zhanli_;

		strncpy(strData.name_, m_name.c_str(), MAX_NAME_LEN + 1);

		Relation_Manager::instance()->AddFriendToList(FRIEND_LIST_TYPE_OWN, &strData);
	}

	// 3. 设置已有的好友列表是否被获取到的状态
	Relation_Manager::instance()->SetOwnFriendListGetState(true);
	return true;
}

long Relation_Msg_Proc::getCurrentTime()
{
	struct timeval tv;     
 //yypp   Time::gettimeofdayCocos2d(&tv, NULL);  
    return tv.tv_sec * 1000 + tv.tv_usec / 1000; 
	return 0;
}

long Relation_Msg_Proc::getLocalTimeRecord()
{
	return localTimeRecord;
}

void Relation_Msg_Proc::setLocalTimeRecord(long t)
{
	localTimeRecord = t;
}
