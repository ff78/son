#include "Network_Common/NetManager.h"
#include "Network_Common/message.h"
#include "Network_Common/message_coder.h"
#include "Network_Common/message_stream.h"

#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Player_Account/Account_Data_Mgr.h"

#include "../DataModule/Little.h"

#include "Relation_Common.h"
#include "Relation_Mgr.h"

USING_NS_CC;


Relation_Manager* Relation_Manager::g_pRelationManager = 0;

Relation_Manager::Relation_Manager()
{
	m_nCurrentRoleID			= 0;

	m_bOwnListIsGot				= false;
	m_bApplyListIsGot			= false;
	m_bOwnListChange			= false;
	m_bApplyListChange			= false;

	m_pRelationData				= NULL;

	m_eCurrentLayerState		= CURRENT_FRIEND_LAYER_STATE_ERROR;

	m_pOwnFriendMap.clear();
	m_pApplyFriendMap.clear();
	m_pFreeRelationDataIndexList.clear();
}


Relation_Manager::~Relation_Manager()
{

}

Relation_Manager * Relation_Manager::instance()
{
	if (NULL == g_pRelationManager)
		g_pRelationManager = new Relation_Manager;

	return g_pRelationManager;
}

int Relation_Manager::initialize()
{
	/************************************************************************/
	// 初始化Relation_Manager
	// 1. 根据最大数量申请好友数据内存
	m_pRelationData = new Relation_Data[MAX_OWN_FRIEND_COUNT + MAX_APPLY_FRIEND_COUNT];

	// 2. 存储空闲的好友数据索引
	for (int nIndex = 0; nIndex < MAX_OWN_FRIEND_COUNT + MAX_APPLY_FRIEND_COUNT; ++nIndex)
	{
		m_pFreeRelationDataIndexList.push_back(nIndex);
	}
	return 0;
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 相关逻辑处理
void Relation_Manager::AddFriendToList(const FRIEND_LIST_TYPE eType, Relation_Data * pData)
{
	/************************************************************************/
	// 添加好友到好友列表中
	// 1. 判断数据是否异常
	if (pData == NULL)
		return;

	int nFriendID = pData->friend_role_id_;
	std::map<int , int>::const_iterator own_friend_iter;
	std::map<int , int>::const_iterator apply_friend_iter;
	// 2_1. 判断该好友是否存在于已有列表中（如果是添加好友那么此好友肯定存在于申请列表中）
	if (eType == FRIEND_LIST_TYPE_OWN)
	{
		apply_friend_iter = m_pApplyFriendMap.find(nFriendID);
		if (apply_friend_iter == m_pApplyFriendMap.end())
			return;

		own_friend_iter = m_pOwnFriendMap.find(nFriendID);
		if (own_friend_iter != m_pOwnFriendMap.end())
			return;
	}
	// 2_1. 判断该好友是否存在于已有列表中
	else if (eType == FRIEND_LIST_TYPE_APPLY)
	{
		apply_friend_iter = m_pApplyFriendMap.find(nFriendID);
		if (apply_friend_iter != m_pApplyFriendMap.end())
			return;
	}
	else
	{
		return;
	}

	// 3. 判断好友个数是否达到上限
	int nFriendCount = 0;
	if (eType == FRIEND_LIST_TYPE_OWN)
	{
		nFriendCount = m_pOwnFriendMap.size();
		if (nFriendCount > MAX_OWN_FRIEND_COUNT)
			return;
	}
	else if (eType == FRIEND_LIST_TYPE_APPLY)
	{
		nFriendCount = m_pApplyFriendMap.size();
		if (nFriendCount > MAX_APPLY_FRIEND_COUNT)
			return;
	}
	else
	{
		return;
	}
	
	// 4. 判断空闲的好友数据索引列表是否达到上限
	if (m_pFreeRelationDataIndexList.size() == 0)
		return;
	
	// 5. 获取索引并判断是否异常
	int nIndex = m_pFreeRelationDataIndexList.front();
	if (nIndex < 0 || nIndex >= MAX_OWN_FRIEND_COUNT + MAX_APPLY_FRIEND_COUNT)
		return;

	/************************************************************************/
	// 条件满足,将此好友的数据添加到列表中
	// 1. 添加索引到英雄列表中(如果是添加好友，那么要多一步操作是将此好友从申请列表中移除)
	if (eType == FRIEND_LIST_TYPE_OWN)
	{
		m_pApplyFriendMap.erase(nFriendID);
		m_pOwnFriendMap.insert(make_pair(nFriendID, nIndex));
	}
	else if (eType == FRIEND_LIST_TYPE_APPLY)
	{
		m_pApplyFriendMap.insert(make_pair(nFriendID, nIndex));
	}
	else
	{
		return;
	}

	// 2. 从空闲的好友数据索引列表中移除目标索引
	m_pFreeRelationDataIndexList.pop_front();

	// 3. 将该好友的数据复制到目标结构体中
	memset(&m_pRelationData[nIndex] , 0 , sizeof(Relation_Data));
	memcpy(&m_pRelationData[nIndex], pData, sizeof(Relation_Data));

	// 4. 更改已有好友列表状态
	if (eType == FRIEND_LIST_TYPE_OWN)
	{
		m_bOwnListChange = true;
	}
	else if (eType == FRIEND_LIST_TYPE_APPLY)
	{
		m_bApplyListChange = true;
	}
	else
	{
		return;
	}
	
}


void Relation_Manager::RemoveFriendFromList(const FRIEND_LIST_TYPE eType, const int nRoleID)
{
	/************************************************************************/
	// 从好友列表中移除好友
	int nIndex = 0;
	std::map<int, int>::const_iterator friend_iter;
	// 1. 如果操作对象是已有英雄列表
	if (eType == FRIEND_LIST_TYPE_OWN)
	{
		// 1_1. 遍历已有英雄列表,寻找ID与nRoleID一致的好友
		friend_iter = m_pOwnFriendMap.find(nRoleID);
		if (friend_iter == m_pOwnFriendMap.end())
			return;

		// 1_2. 获取该数据索引并塞入到空闲的好友数据索引中
		nIndex = friend_iter->second;
		m_pFreeRelationDataIndexList.push_front(nIndex);

		m_pOwnFriendMap.erase(nRoleID);

		// 1_3. 更改已有好友列表状态
		m_bOwnListChange = true;
	}
	// 2. 如果操作对象是申请英雄列表
	else if (eType == FRIEND_LIST_TYPE_APPLY)
	{
		// 2_1. 遍历申请英雄列表,寻找ID与nRoleID一致的好友,
		friend_iter = m_pApplyFriendMap.find(nRoleID);
		if (friend_iter == m_pApplyFriendMap.end())
			return;

		// 2_2. 获取该数据索引并塞入到空闲的好友数据索引中
		nIndex = friend_iter->second;
		m_pFreeRelationDataIndexList.push_front(nIndex);

		m_pApplyFriendMap.erase(nRoleID);

		// 2_3. 更改已有好友列表状态
		m_bApplyListChange = true;
	}
	else
	{
		return;
	}
}


void Relation_Manager::AddFriendFromApplyToOwn()
{
	/************************************************************************/
	// 从申请列表添加好友到已有好友列表中
	int nIndex = 0;
	// 1. 判断此好友是否存在于申请列表中
	std::map<int, int>::const_iterator apply_friend_iter;
	apply_friend_iter = m_pApplyFriendMap.find(m_nCurrentRoleID);
	if (apply_friend_iter == m_pApplyFriendMap.end())
		return;

	nIndex = apply_friend_iter->second;
	// 2. 判断该好友是否存在于已有列表中
	std::map<int, int>::const_iterator own_friend_iter;
	own_friend_iter = m_pOwnFriendMap.find(m_nCurrentRoleID);
	if (own_friend_iter != m_pOwnFriendMap.end())
		return;

	/************************************************************************/
	// 条件满足添加好友
	// 1. 已有和申请列表进行操作
	m_pApplyFriendMap.erase(m_nCurrentRoleID);
	m_pOwnFriendMap.insert(make_pair(m_nCurrentRoleID, nIndex));

	// 2. 清除ID
	m_nCurrentRoleID	= 0;

	// 3. 更改已有好友列表状态
	m_bOwnListChange	= true;
	m_bApplyListChange	= true;
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 与显示层的交互
int Relation_Manager::UIRequestCellCount()
{
	/************************************************************************/
	// 显示层打开好友界面请求好友个数
	// 1. 如果当前界面是已有好友界面
	if (m_eCurrentLayerState == CURRENT_FRIEND_LAYER_STATE_OWN)
	{
		return GetOwnFriendCount();
	}
	// 2. 如果当前界面是申请好友界面
	else if (m_eCurrentLayerState == CURRENT_FRIEND_LAYER_STATE_APPLY)
	{
		return GetApplyFriendCount();
	}
	else
	{
		return -1;
	}	
}

bool Relation_Manager::UIRequestFriendRoleID(std::list<int> * pList)
{
	/************************************************************************/
	// 显示层请求好友ID
	// 1. 判断当前的好友界面状态是否异常
	if (m_eCurrentLayerState < CURRENT_FRIEND_LAYER_STATE_OWN || m_eCurrentLayerState > CURRENT_FRIEND_LAYER_STATE_APPLY)
		return false;

	// 2. 判断好友的个数是否异常
	int nFriendCount = 0;
	if (m_eCurrentLayerState == CURRENT_FRIEND_LAYER_STATE_OWN)
	{
		nFriendCount =  GetOwnFriendCount();
	}
	if (m_eCurrentLayerState == CURRENT_FRIEND_LAYER_STATE_APPLY)
	{
		nFriendCount =  GetApplyFriendCount();
	}
	if (nFriendCount <= 0)
		return false;

	/************************************************************************/
	// 条件满足
	// 1. 清理列表
	pList->clear();

	// 2. 获取每个好友的RoleID
	int nFriendRoleID = 0;
	std::map<int, int>::const_iterator friend_iter;
	// 1. 如果操作对象是已有英雄列表
	if (m_eCurrentLayerState == FRIEND_LIST_TYPE_OWN)
	{
		friend_iter = m_pOwnFriendMap.begin();
		for (friend_iter; friend_iter != m_pOwnFriendMap.end(); ++friend_iter)
		{
			nFriendRoleID = friend_iter->first;
			pList->push_back(nFriendRoleID);
		}
		
	}
	// 2. 如果操作对象是申请英雄列表
	if (m_eCurrentLayerState == FRIEND_LIST_TYPE_APPLY)
	{
		friend_iter = m_pApplyFriendMap.begin();
		for (friend_iter; friend_iter != m_pApplyFriendMap.end(); ++friend_iter)
		{
			nFriendRoleID = friend_iter->first;
			pList->push_back(nFriendRoleID);
		}
	}
	return true;
}

bool Relation_Manager::UIRequestFriendShowInfo(const int nID, TARGET_FRIEND_INFO_FOR_SHOW * pData)
{
	/************************************************************************/
	// 显示层请求好友的显示信息
	int nIndex = 0;
	std::map<int, int>::const_iterator friend_iter;
	// 1. 如果操作对象是已有英雄列表
	if (m_eCurrentLayerState == FRIEND_LIST_TYPE_OWN)
	{
		// 1_1. 遍历已有英雄列表,寻找ID与nRoleID一致的好友
		friend_iter = m_pOwnFriendMap.find(nID);
		if (friend_iter == m_pOwnFriendMap.end())
			return false;

		// 1_2. 获取索引
		nIndex = friend_iter->second;
	}
	// 2. 如果操作对象是申请英雄列表
	else if (m_eCurrentLayerState == FRIEND_LIST_TYPE_APPLY)
	{
		// 2_1. 遍历申请英雄列表,寻找ID与nRoleID一致的好友,
		friend_iter = m_pApplyFriendMap.find(nID);
		if (friend_iter == m_pApplyFriendMap.end())
			return false;

		// 2_2. 获取索引
		nIndex = friend_iter->second;
	}
	else
	{
		return false;
	}
	// 3. 判断索引是否异常
	if (nIndex < 0 || nIndex > MAX_OWN_FRIEND_COUNT + MAX_APPLY_FRIEND_COUNT)
		return false;

	/************************************************************************/
	// 条件满足,对结构体进行赋值
	memset(pData , 0 , sizeof(TARGET_FRIEND_INFO_FOR_SHOW));
	pData->nFriendLevel				= m_pRelationData[nIndex].level_;
	pData->nFriendFighttingPower	= m_pRelationData[nIndex].zhanli_;
	pData->szFriendName = m_pRelationData[nIndex].name_;
	pData->szFriendJobName = Little::jobs[m_pRelationData[nIndex].nJob].name;
	return true;
}


bool Relation_Manager::UIRequestEnterTargetLayerState(CURRENT_FRIEND_LAYER_STATE eState)
{
	/************************************************************************/
	// 显示层请求进入目标界面状态
	// 1. 判断申请的页面状态是否异常
	if (eState == CURRENT_FRIEND_LAYER_STATE_ERROR)
		return false;
	
	// 2. 如果请求进入的是已有的好友界面
	if (eState == CURRENT_FRIEND_LAYER_STATE_OWN)
	{
		// 2_1. 记录当前的页面状态
		m_eCurrentLayerState = eState;

		// 2_2. 判断是否获取到已有好友列表
		if (m_bOwnListIsGot)
			return true;

		// 2_3. 如果没有获取到已有的好友列表，则向服务器请求好友列表数据
		SendMsgRequestOwnFriendList();
	}
	// 3. 如果请求进入的是申请的好友界面
	else if (eState == CURRENT_FRIEND_LAYER_STATE_APPLY)
	{
		// 3_1. 记录当前的页面状态
		m_eCurrentLayerState = eState;

		// 3_2. 判断是否获取到申请好友列表
		if (m_bApplyListIsGot)
			return true;

		// 3_3. 如果没有获取到申请的好友列表，则向服务器请求好友列表数据
		SendMsgRequestApplyFriendList();
	}
	// 4. 错误的页面状态
	else
	{
		return false;
	}
	return true;
}


void Relation_Manager::UIRequestAddFriend(std::string strName)
{
	/************************************************************************/
	// 显示层请求添加好友
	SendMsgRequestAddFriend(strName);
}

void Relation_Manager::UIRequestDeleteFriend(int nRoleID)
{
	/************************************************************************/
	// 显示层请求删除好友
	std::map<int, int>::const_iterator friend_iter;
	// 1. 如果当前处于已有好友列表界面
	if (m_eCurrentLayerState == CURRENT_FRIEND_LAYER_STATE_OWN)
	{
		// 1_1. 判断目标玩家是否处于已有好友列表中
		friend_iter = m_pOwnFriendMap.find(nRoleID);
		if (friend_iter == m_pOwnFriendMap.end())
			return;

		// 1_2. 发送消息请求删除好友
		SendMsgRequestDeleteFriendFromOwnList(nRoleID);

	}
	// 2. 如果当前处于申请的好友列表界面,
	else if (m_eCurrentLayerState == CURRENT_FRIEND_LAYER_STATE_APPLY)
	{
		// 2_1. 判断目标玩家是否处于申请好友列表中
		friend_iter = m_pApplyFriendMap.find(nRoleID);
		if (friend_iter == m_pApplyFriendMap.end())
			return;

		// 2_2. 发送消息请求删除好友
		SendMsgRequestDeleteFriendFromApplyList(nRoleID);
	}
	// 3. 错误的页面状态
	else
	{
	}
}


void Relation_Manager::UIRequestAddFriendFromApply(int nRoleID)
{
	/************************************************************************/
	// 显示层请求从申请列表添加好友
	// 1. 判断当前的页面状态是否异常
	if (m_eCurrentLayerState != CURRENT_FRIEND_LAYER_STATE_APPLY)
		return;

	// 2. 判断目标好友是否存在于已有列表中
	std::map<int, int>::const_iterator own_friend_iter;
	own_friend_iter = m_pOwnFriendMap.find(nRoleID);
	if (own_friend_iter != m_pOwnFriendMap.end())
		return;

	// 3. 判断目标好友是否存在于申请列表中
	std::map<int, int>::const_iterator apply_friend_iter;
	apply_friend_iter = m_pApplyFriendMap.find(nRoleID);
	if (apply_friend_iter == m_pApplyFriendMap.end())
		return;

	// 4. 记录申请ID
	m_nCurrentRoleID	= nRoleID;

	/************************************************************************/
	// 条件满足发送消息到服务器
	SendMsgRequestAddFriendFromApplyList(nRoleID);
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 与服务器的交互
void Relation_Manager::SendMsgRequestOwnFriendList()
{
	/************************************************************************/
	// 发送消息请求好友列表
	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));
	body_ms << CS_ASK_FRIEND_LIST;

	CNetManager::GetMe()->send_msg(body_ms);
}

void Relation_Manager::SendMsgRequestApplyFriendList()
{
	/************************************************************************/
	// 发送消息请求申请好友列表

	// 测试代码
	// 潘杰（02.06）
	SetApplyFriendListGetState(true);
}

void Relation_Manager::SendMsgRequestAddFriend(std::string strName)
{
	/************************************************************************/
	// 发送消息请求添加好友
	// 1. 获取玩家ID
	int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();

	// 2. 发送消息
	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));
	body_ms << CS_APPLY_FRIEND;
	body_ms << nPlayerID;
	body_ms << strName;

	CNetManager::GetMe()->send_msg(body_ms);
}


void Relation_Manager::SendMsgRequestDeleteFriendFromOwnList(const int nRoleID)
{
	/************************************************************************/
	// 发送消息请求从已有好友列表删除好友
	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));
	body_ms << CS_DEL_FRIEND;
	body_ms << nRoleID;

	CNetManager::GetMe()->send_msg(body_ms);
}

void Relation_Manager::SendMsgRequestDeleteFriendFromApplyList(const int nRoleID)
{
	/************************************************************************/
	// 发送消息请求从申请好友列表删除好友
	//char body[256] = { 0 };
	//message_stream body_ms(body, sizeof(body));
	//body_ms << CS_DEL_FRIEND;
	//body_ms << nRoleID;
	//
	//CNetManager::GetMe()->send_msg(body_ms);
}

void Relation_Manager::SendMsgRequestAddFriendFromApplyList(const int nRoleID)
{
	/************************************************************************/
	// 发送消息请求从申请好友列表添加好友
	// 1. 获取玩家ID
	int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();

	// 2. 发送消息
	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));
	body_ms << CS_ADD_FRIEND;
	body_ms << nPlayerID;
	body_ms << nRoleID;

	CNetManager::GetMe()->send_msg(body_ms);
}
