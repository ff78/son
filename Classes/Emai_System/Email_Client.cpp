#include "cocos2d.h"
#include "../ClientLogic/Utils/GameReader.h"

#include "Network_Common/NetManager.h"
#include "Network_Common/message.h"
#include "Network_Common/message_coder.h"
#include "Network_Common/message_stream.h"

#include "Email_Common_Config_Data.h"
#include "Email_Client.h"
#include "../Player_Account/Account_Data_Mgr.h"
#include "../Character_System/Character_Mgr.h"
#include "../Character_System/Player.h"

USING_NS_CC;
using namespace cocostudio;
using namespace Game_Model;


EMAIL_MODEL* EMAIL_MODEL::g_pEmailManager = 0;

EMAIL_MODEL::Email_Manager()
{
	m_nCurrentDealEmailIndex	= 0;

	m_bEmailListIsChange		= false;

	m_pAllEmailData.clear();

	m_eCurrentState				= Current_Email_Layer_State_Error;

	m_pFreeEmailDataIndexList.clear();
}

EMAIL_MODEL::~Email_Manager()
{
	//SAFE_DELETE_ARRAY(m_pAllEmailData);
}

EMAIL_MODEL * EMAIL_MODEL::instance()
{
	if (NULL == g_pEmailManager)
		g_pEmailManager = new EMAIL_MODEL;

	return g_pEmailManager;
}

int EMAIL_MODEL::initialize()
{
	/************************************************************************/
	// 初始化EMAIL_MODEL
	// 1. 申明内存空间存储所有的邮件数据
	//m_pAllEmailData			= new Email_Data[MAX_EMAIL_COUNT];

	// 2. 存储空余的邮件索引
	for (int nIndex = 0; nIndex < MAX_EMAIL_COUNT; ++nIndex)
	{
		m_pFreeEmailDataIndexList.push_back(nIndex);
	}
	

	return 0;
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 数据处理的相关方法

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 相关逻辑处理
void EMAIL_MODEL::DeleteTargetEmail(const int nIndex)
{
	/************************************************************************/
	// 删除目标邮件
	// 判断索引是否异常
	if (!JudgeTargetIndexIsError(nIndex))
		return;
	
	/************************************************************************/
	// 条件满足
	// 1. 清除目标邮件数据
	memset(&m_pAllEmailData[nIndex], 0, sizeof(Email_Data));

	// 2. 索引添加到列表中
	m_pFreeEmailDataIndexList.push_front(nIndex);

	// 3. 设置邮件列表是否发生改变的状态
	m_bEmailListIsChange = true;

	// 4. 清除当前记录的操作单元索引
	m_nCurrentDealEmailIndex = -1;
}


bool EMAIL_MODEL::JudgeTargetIndexIsError(const int nIndex)
{
	/************************************************************************/
	// 判断目标索引是否异常
	// 1. 获取玩家所有的邮件的个数
	int nCount	= GetPlayerAllEmailsCount();
	if (nCount < 0 || nIndex > MAX_EMAIL_COUNT)
		return false;

	// 2. 判断索引是否异常
	if (nIndex < 0 || nIndex >= nCount)
		return false;
	
	return true;
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 与显示层的交互
int EMAIL_MODEL::GetPlayerAllEmailsCount()
{
	/************************************************************************/
	// 获取玩家所有的邮件的个数
	int nEmailCount = 0;
	// 1. 如果邮件个数是否异常，则清除邮件里面的所有数据
	//if (nEmailCount < 0 || nEmailCount > MAX_EMAIL_COUNT)
	//{
	//	m_pFreeEmailDataIndexList.clear();

	//	for (int nIndex = 0; nIndex < MAX_EMAIL_COUNT; ++nIndex)
	//	{
	//		m_pFreeEmailDataIndexList.push_back(nIndex);
	//	}
	//	
	//	//memset(m_pAllEmailData, 0, sizeof(Email_Data)* MAX_EMAIL_COUNT);

	//	nEmailCount = 0;
	//}

	
	nEmailCount = m_pAllEmailData.size();

	
	//nEmailCount = MAX_EMAIL_COUNT - m_pFreeEmailDataIndexList.size();
	// 2. 返回正确的邮件个数
	return nEmailCount;
	//return 3;
}

bool EMAIL_MODEL::UIRequestTargetIndexShowInfo(const int nIndex)
{
	/************************************************************************/
	// 显示层请求目标索引的显示信息
	// 判断目标索引是否异常
	if (!JudgeTargetIndexIsError(nIndex))
		return false;
	return true;

}

bool EMAIL_MODEL::UIRequestTargetIndexDetailShowInfo(const int nIndex, Email_Detail_Data_For_Show *pInfo)
{
	/************************************************************************/
	// 显示层请求目标索引的详细显示信息
	// 判断目标索引是否异常
	if (!JudgeTargetIndexIsError(nIndex))
		return false;
	m_nCurrentDealEmailIndex = nIndex;
	return true;
	/************************************************************************/
	// 条件满足
	// 1. 对目标结构体进行赋值
	//memset(pInfo, 0, sizeof(Email_Detail_Data_For_Show));
	//const char * szContent	= m_pAllEmailData[nIndex]->strEmailContent.c_str();
	//pInfo->nItemID			= m_pAllEmailData[nIndex]->nItemID;

	//pInfo->szSenderName = m_pAllEmailData[nIndex]->szSenderName;
	//pInfo->szContent = szContent;

	//snprintf(pInfo->szSenderName, sizeof(pInfo->szSenderName), m_pAllEmailData[nIndex]->szSenderName);
	//pInfo->szSenderName[sizeof(pInfo->szSenderName) - 1] = '\0';

	//snprintf(pInfo->szContent, sizeof(pInfo->szContent), szContent);
	//pInfo->szContent[sizeof(pInfo->szContent) - 1] = '\0';

	// 2. 记录当前操作的邮件索引

	return true;
}


void EMAIL_MODEL::UIRequestDeleteTargetIndexEmail(const int nIndex)
{
	/************************************************************************/
	// 显示层请求删除目标索引的邮件
	// 1. 判断索引是否异常
	if (!JudgeTargetIndexIsError(nIndex))
		return ;

	// 2. 记录当前处理的邮件索引
	m_nCurrentDealEmailIndex = nIndex;

	// 3 .给服务器发消息请求删除目标邮件
	SendMsgRequestDeleteTargetIndexEmail(nIndex);
}


void EMAIL_MODEL::UIRequestReceiveTargetIndexEmailPresent()
{
	/************************************************************************/
	// 显示层请求接收目标邮件的附属物品
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 与服务器的交互
void EMAIL_MODEL::SendMsgRequestDeleteTargetIndexEmail(const int nIndex)
{
	/************************************************************************/
	// 发送消息请求删除目标邮件
	// ...
}

using namespace Game_Net;
Email_Msg* Email_Msg::getInstance()
{

	static Email_Msg _instance;
	return &_instance;

}

bool Email_Msg::init()
{
	return true;
}

bool Email_Msg::send_load_email(Game_Logic::Game_Interface& gm_interface)
{
	auto player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;
	auto player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	body_ms << C2S_ON_LOAD_EMAIL;
	body_ms << player_id;

	CNetManager::GetMe()->send_msg(body_ms);
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_DIG, nullptr);
	return true;

}

bool Email_Msg::on_load_email(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	std::vector<email_data> emails;
	int			count;
	body_ms >> count;
	for (int i = 0; i < count;i++)
	{
		int id;
		int type;
		int role_id;
		int target_id;
		std::string target_name;
		int is_on_read;
		std::string msg;
		int item_id;
		std::string send_time;
		body_ms >> id;
		body_ms >> type;
		body_ms >> role_id;
		body_ms >> target_id;
		body_ms >> target_name;
		body_ms >> is_on_read;
		body_ms >> msg;
		body_ms >> item_id;
		body_ms >> send_time;

		email_data data;
		data.id = id;
		data.type = type;
		data.role_id = role_id;
		data.target_id = target_id;
		//strcpy(data.target_name, target_name.c_str());
		sprintf(data.target_name, "%s", target_name.c_str());

		data.is_on_read = is_on_read;
		data.msg = msg;
		//strcpy(data.send_time_, send_time.c_str());
		sprintf(data.send_time_, "%s", send_time.c_str());
		emails.push_back(data);
	}
	static int x;
	email_data tmp_data;
	tmp_data.id = 100+x++;
	tmp_data.type = 1;
	tmp_data.role_id = 10000002;
	tmp_data.is_on_read = false;
	tmp_data.item_id = 0;
	tmp_data.msg = "msg_to_show";
	auto player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;
	auto player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	//tmp_data.target_id = player_id;
	//sprintf(tmp_data.target_name, "%s%d", "JulyRoberts",x);
	//log("test_name:%s",tmp_data.target_name);
	//sprintf(tmp_data.send_time_, "%s", "2015/04/01");
	//log("test_time:%s", tmp_data.send_time_);
	//emails.push_back(tmp_data);
	//EMAIL_MODEL::instance()->SetCurrentEmailListIsChangeState(true);

	for (auto it = emails.begin(); it != emails.end(); it++)
	{
		Email_Data data;
		data._id = (*it).id;
		data.bEmailIsRead = (*it).is_on_read;
		data.nItemID = (*it).item_id;
		data.strEmailContent = (*it).msg;
		data.nSenderID = (*it).role_id;
		//sprintf(data.szSenderName, (*it).target_name);
		data.szSenderName = (*it).target_name;
		data.nReceiverID = (*it).target_id;
		//sprintf(data.szReceiverName, "%s", player->get_character_name());
		data.szReceiverName = player->get_character_name();
		//sprintf(data.szCreatTime,"%s", (*it).send_time_);
		data.szCreatTime = (*it).send_time_;
		//strcpy(data.szCreatTime, (*it).send_time_);

		if ((*it).type == RT_EMAIL_SYSTEM)
			data.eEmailSourceType = Email_Source_Type_Official;
		else if ((*it).type == RT_EMAIL_PLAYER)
			data.eEmailSourceType = Email_Source_Type_Personal;
		else
			data.eEmailSourceType = Email_Source_Type_Error;
		auto allDatas = EMAIL_MODEL::instance()->getAllData();
		allDatas.push_back(data);
		EMAIL_MODEL::instance()->setAllData(allDatas);

		Email_Simple_Data_For_Show simpleData;
		simpleData._id = data._id;
		simpleData.bIsOfficialEmail = data.eEmailSourceType == Email_Source_Type_Official;
		simpleData.bIsRead = data.bEmailIsRead;
		simpleData.szSenderName = data.szSenderName;
		simpleData.szTitle = data.strEmailContent;
		simpleData.szCreatTime = data.szCreatTime;
		auto simpleDatas = EMAIL_MODEL::instance()->getSimpleData();
		simpleDatas.push_back(simpleData);
		EMAIL_MODEL::instance()->setSimpleData(simpleDatas);

		Email_Detail_Data_For_Show detailData;
		detailData._id = detailData._id;
		detailData.nItemID = data.nItemID;
		detailData.szContent = data.strEmailContent;
		detailData.szSenderName = data.szSenderName;
		auto detailDatas = EMAIL_MODEL::instance()->getDetailData();
		detailDatas.push_back(detailData);
		EMAIL_MODEL::instance()->setDetailData(detailDatas);

	}
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_DIG, nullptr);

	return true;

}

bool Email_Msg::send_send_email(Game_Logic::Game_Interface& gm_interface)
{
	auto player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;
	auto player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;
	std::string me( player->get_character_name() );
	auto target_name = EMAIL_MODEL::instance()->getTargetNameToSend();
	auto content = EMAIL_MODEL::instance()->getMsgToSend();
	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));
	
	body_ms << C2S_SEND_EMAIL;
	body_ms << player_id;
	body_ms << content;
	body_ms << me;
	body_ms << target_name;
	CNetManager::GetMe()->send_msg(body_ms);
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_DIG, nullptr);
	return true;

}

bool Email_Msg::on_send_email(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	char body[256] = { 0 };
	int			result;

	body_ms >> result;
	if (result != 0)
		return false;
	else
		;
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_DIG, nullptr);

	return true;

}

bool Email_Msg::on_recieve_email(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	char body[256] = { 0 };
	int			result;

	body_ms >> result;
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_DIG, nullptr);

	return true;
}

bool Email_Msg::on_recieve_system_email(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	char body[256] = { 0 };
	int			result;

	body_ms >> result;
	if (result != 0)
		return false;
	else
		;
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_DIG, nullptr);

	return true;
}



bool Email_Msg::send_open_email(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	auto player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;
	auto player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	body_ms << C2S_OPEN_EMAIL;
	body_ms << player_id;
	body_ms << para[0];
	CNetManager::GetMe()->send_msg(body_ms);
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_DIG, nullptr);
	return true;
}

bool Email_Msg::on_open_email(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	char body[256] = { 0 };
	int			result;

	body_ms >> result;
	if (result != 0)
		return false;
	else
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_EMAIL_SHOW_OPEN, nullptr);
	//{
	//	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_EMAIL_SHOW_DELETE, nullptr);

	//}

	return true;
}

bool EMAIL_NET::send_delete_email(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	auto player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;
	auto player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	body_ms << C2S_DELETE_EMAIL;
	body_ms << player_id;
	body_ms << para[0];
	CNetManager::GetMe()->send_msg(body_ms);
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_REFRESH_DIG, nullptr);
	return true;

}

bool EMAIL_NET::on_delete_email(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	int			result;

	body_ms >> result;
	if (result!=0)
		return false;
	else
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_EMAIL_SHOW_DELETE, nullptr);

	return true;

}