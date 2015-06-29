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
	// ��ʼ��Relation_Manager
	// 1. �����������������������ڴ�
	m_pRelationData = new Relation_Data[MAX_OWN_FRIEND_COUNT + MAX_APPLY_FRIEND_COUNT];

	// 2. �洢���еĺ�����������
	for (int nIndex = 0; nIndex < MAX_OWN_FRIEND_COUNT + MAX_APPLY_FRIEND_COUNT; ++nIndex)
	{
		m_pFreeRelationDataIndexList.push_back(nIndex);
	}
	return 0;
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// ����߼�����
void Relation_Manager::AddFriendToList(const FRIEND_LIST_TYPE eType, Relation_Data * pData)
{
	/************************************************************************/
	// ��Ӻ��ѵ������б���
	// 1. �ж������Ƿ��쳣
	if (pData == NULL)
		return;

	int nFriendID = pData->friend_role_id_;
	std::map<int , int>::const_iterator own_friend_iter;
	std::map<int , int>::const_iterator apply_friend_iter;
	// 2_1. �жϸú����Ƿ�����������б��У��������Ӻ�����ô�˺��ѿ϶������������б��У�
	if (eType == FRIEND_LIST_TYPE_OWN)
	{
		apply_friend_iter = m_pApplyFriendMap.find(nFriendID);
		if (apply_friend_iter == m_pApplyFriendMap.end())
			return;

		own_friend_iter = m_pOwnFriendMap.find(nFriendID);
		if (own_friend_iter != m_pOwnFriendMap.end())
			return;
	}
	// 2_1. �жϸú����Ƿ�����������б���
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

	// 3. �жϺ��Ѹ����Ƿ�ﵽ����
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
	
	// 4. �жϿ��еĺ������������б��Ƿ�ﵽ����
	if (m_pFreeRelationDataIndexList.size() == 0)
		return;
	
	// 5. ��ȡ�������ж��Ƿ��쳣
	int nIndex = m_pFreeRelationDataIndexList.front();
	if (nIndex < 0 || nIndex >= MAX_OWN_FRIEND_COUNT + MAX_APPLY_FRIEND_COUNT)
		return;

	/************************************************************************/
	// ��������,���˺��ѵ�������ӵ��б���
	// 1. ���������Ӣ���б���(�������Ӻ��ѣ���ôҪ��һ�������ǽ��˺��Ѵ������б����Ƴ�)
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

	// 2. �ӿ��еĺ������������б����Ƴ�Ŀ������
	m_pFreeRelationDataIndexList.pop_front();

	// 3. ���ú��ѵ����ݸ��Ƶ�Ŀ��ṹ����
	memset(&m_pRelationData[nIndex] , 0 , sizeof(Relation_Data));
	memcpy(&m_pRelationData[nIndex], pData, sizeof(Relation_Data));

	// 4. �������к����б�״̬
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
	// �Ӻ����б����Ƴ�����
	int nIndex = 0;
	std::map<int, int>::const_iterator friend_iter;
	// 1. �����������������Ӣ���б�
	if (eType == FRIEND_LIST_TYPE_OWN)
	{
		// 1_1. ��������Ӣ���б�,Ѱ��ID��nRoleIDһ�µĺ���
		friend_iter = m_pOwnFriendMap.find(nRoleID);
		if (friend_iter == m_pOwnFriendMap.end())
			return;

		// 1_2. ��ȡ���������������뵽���еĺ�������������
		nIndex = friend_iter->second;
		m_pFreeRelationDataIndexList.push_front(nIndex);

		m_pOwnFriendMap.erase(nRoleID);

		// 1_3. �������к����б�״̬
		m_bOwnListChange = true;
	}
	// 2. �����������������Ӣ���б�
	else if (eType == FRIEND_LIST_TYPE_APPLY)
	{
		// 2_1. ��������Ӣ���б�,Ѱ��ID��nRoleIDһ�µĺ���,
		friend_iter = m_pApplyFriendMap.find(nRoleID);
		if (friend_iter == m_pApplyFriendMap.end())
			return;

		// 2_2. ��ȡ���������������뵽���еĺ�������������
		nIndex = friend_iter->second;
		m_pFreeRelationDataIndexList.push_front(nIndex);

		m_pApplyFriendMap.erase(nRoleID);

		// 2_3. �������к����б�״̬
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
	// �������б���Ӻ��ѵ����к����б���
	int nIndex = 0;
	// 1. �жϴ˺����Ƿ�����������б���
	std::map<int, int>::const_iterator apply_friend_iter;
	apply_friend_iter = m_pApplyFriendMap.find(m_nCurrentRoleID);
	if (apply_friend_iter == m_pApplyFriendMap.end())
		return;

	nIndex = apply_friend_iter->second;
	// 2. �жϸú����Ƿ�����������б���
	std::map<int, int>::const_iterator own_friend_iter;
	own_friend_iter = m_pOwnFriendMap.find(m_nCurrentRoleID);
	if (own_friend_iter != m_pOwnFriendMap.end())
		return;

	/************************************************************************/
	// ����������Ӻ���
	// 1. ���к������б���в���
	m_pApplyFriendMap.erase(m_nCurrentRoleID);
	m_pOwnFriendMap.insert(make_pair(m_nCurrentRoleID, nIndex));

	// 2. ���ID
	m_nCurrentRoleID	= 0;

	// 3. �������к����б�״̬
	m_bOwnListChange	= true;
	m_bApplyListChange	= true;
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// ����ʾ��Ľ���
int Relation_Manager::UIRequestCellCount()
{
	/************************************************************************/
	// ��ʾ��򿪺��ѽ���������Ѹ���
	// 1. �����ǰ���������к��ѽ���
	if (m_eCurrentLayerState == CURRENT_FRIEND_LAYER_STATE_OWN)
	{
		return GetOwnFriendCount();
	}
	// 2. �����ǰ������������ѽ���
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
	// ��ʾ���������ID
	// 1. �жϵ�ǰ�ĺ��ѽ���״̬�Ƿ��쳣
	if (m_eCurrentLayerState < CURRENT_FRIEND_LAYER_STATE_OWN || m_eCurrentLayerState > CURRENT_FRIEND_LAYER_STATE_APPLY)
		return false;

	// 2. �жϺ��ѵĸ����Ƿ��쳣
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
	// ��������
	// 1. �����б�
	pList->clear();

	// 2. ��ȡÿ�����ѵ�RoleID
	int nFriendRoleID = 0;
	std::map<int, int>::const_iterator friend_iter;
	// 1. �����������������Ӣ���б�
	if (m_eCurrentLayerState == FRIEND_LIST_TYPE_OWN)
	{
		friend_iter = m_pOwnFriendMap.begin();
		for (friend_iter; friend_iter != m_pOwnFriendMap.end(); ++friend_iter)
		{
			nFriendRoleID = friend_iter->first;
			pList->push_back(nFriendRoleID);
		}
		
	}
	// 2. �����������������Ӣ���б�
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
	// ��ʾ��������ѵ���ʾ��Ϣ
	int nIndex = 0;
	std::map<int, int>::const_iterator friend_iter;
	// 1. �����������������Ӣ���б�
	if (m_eCurrentLayerState == FRIEND_LIST_TYPE_OWN)
	{
		// 1_1. ��������Ӣ���б�,Ѱ��ID��nRoleIDһ�µĺ���
		friend_iter = m_pOwnFriendMap.find(nID);
		if (friend_iter == m_pOwnFriendMap.end())
			return false;

		// 1_2. ��ȡ����
		nIndex = friend_iter->second;
	}
	// 2. �����������������Ӣ���б�
	else if (m_eCurrentLayerState == FRIEND_LIST_TYPE_APPLY)
	{
		// 2_1. ��������Ӣ���б�,Ѱ��ID��nRoleIDһ�µĺ���,
		friend_iter = m_pApplyFriendMap.find(nID);
		if (friend_iter == m_pApplyFriendMap.end())
			return false;

		// 2_2. ��ȡ����
		nIndex = friend_iter->second;
	}
	else
	{
		return false;
	}
	// 3. �ж������Ƿ��쳣
	if (nIndex < 0 || nIndex > MAX_OWN_FRIEND_COUNT + MAX_APPLY_FRIEND_COUNT)
		return false;

	/************************************************************************/
	// ��������,�Խṹ����и�ֵ
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
	// ��ʾ���������Ŀ�����״̬
	// 1. �ж������ҳ��״̬�Ƿ��쳣
	if (eState == CURRENT_FRIEND_LAYER_STATE_ERROR)
		return false;
	
	// 2. ����������������еĺ��ѽ���
	if (eState == CURRENT_FRIEND_LAYER_STATE_OWN)
	{
		// 2_1. ��¼��ǰ��ҳ��״̬
		m_eCurrentLayerState = eState;

		// 2_2. �ж��Ƿ��ȡ�����к����б�
		if (m_bOwnListIsGot)
			return true;

		// 2_3. ���û�л�ȡ�����еĺ����б������������������б�����
		SendMsgRequestOwnFriendList();
	}
	// 3. �����������������ĺ��ѽ���
	else if (eState == CURRENT_FRIEND_LAYER_STATE_APPLY)
	{
		// 3_1. ��¼��ǰ��ҳ��״̬
		m_eCurrentLayerState = eState;

		// 3_2. �ж��Ƿ��ȡ����������б�
		if (m_bApplyListIsGot)
			return true;

		// 3_3. ���û�л�ȡ������ĺ����б������������������б�����
		SendMsgRequestApplyFriendList();
	}
	// 4. �����ҳ��״̬
	else
	{
		return false;
	}
	return true;
}


void Relation_Manager::UIRequestAddFriend(std::string strName)
{
	/************************************************************************/
	// ��ʾ��������Ӻ���
	SendMsgRequestAddFriend(strName);
}

void Relation_Manager::UIRequestDeleteFriend(int nRoleID)
{
	/************************************************************************/
	// ��ʾ������ɾ������
	std::map<int, int>::const_iterator friend_iter;
	// 1. �����ǰ�������к����б����
	if (m_eCurrentLayerState == CURRENT_FRIEND_LAYER_STATE_OWN)
	{
		// 1_1. �ж�Ŀ������Ƿ������к����б���
		friend_iter = m_pOwnFriendMap.find(nRoleID);
		if (friend_iter == m_pOwnFriendMap.end())
			return;

		// 1_2. ������Ϣ����ɾ������
		SendMsgRequestDeleteFriendFromOwnList(nRoleID);

	}
	// 2. �����ǰ��������ĺ����б����,
	else if (m_eCurrentLayerState == CURRENT_FRIEND_LAYER_STATE_APPLY)
	{
		// 2_1. �ж�Ŀ������Ƿ�����������б���
		friend_iter = m_pApplyFriendMap.find(nRoleID);
		if (friend_iter == m_pApplyFriendMap.end())
			return;

		// 2_2. ������Ϣ����ɾ������
		SendMsgRequestDeleteFriendFromApplyList(nRoleID);
	}
	// 3. �����ҳ��״̬
	else
	{
	}
}


void Relation_Manager::UIRequestAddFriendFromApply(int nRoleID)
{
	/************************************************************************/
	// ��ʾ������������б���Ӻ���
	// 1. �жϵ�ǰ��ҳ��״̬�Ƿ��쳣
	if (m_eCurrentLayerState != CURRENT_FRIEND_LAYER_STATE_APPLY)
		return;

	// 2. �ж�Ŀ������Ƿ�����������б���
	std::map<int, int>::const_iterator own_friend_iter;
	own_friend_iter = m_pOwnFriendMap.find(nRoleID);
	if (own_friend_iter != m_pOwnFriendMap.end())
		return;

	// 3. �ж�Ŀ������Ƿ�����������б���
	std::map<int, int>::const_iterator apply_friend_iter;
	apply_friend_iter = m_pApplyFriendMap.find(nRoleID);
	if (apply_friend_iter == m_pApplyFriendMap.end())
		return;

	// 4. ��¼����ID
	m_nCurrentRoleID	= nRoleID;

	/************************************************************************/
	// �������㷢����Ϣ��������
	SendMsgRequestAddFriendFromApplyList(nRoleID);
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// ��������Ľ���
void Relation_Manager::SendMsgRequestOwnFriendList()
{
	/************************************************************************/
	// ������Ϣ��������б�
	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));
	body_ms << CS_ASK_FRIEND_LIST;

	CNetManager::GetMe()->send_msg(body_ms);
}

void Relation_Manager::SendMsgRequestApplyFriendList()
{
	/************************************************************************/
	// ������Ϣ������������б�

	// ���Դ���
	// �˽ܣ�02.06��
	SetApplyFriendListGetState(true);
}

void Relation_Manager::SendMsgRequestAddFriend(std::string strName)
{
	/************************************************************************/
	// ������Ϣ������Ӻ���
	// 1. ��ȡ���ID
	int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();

	// 2. ������Ϣ
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
	// ������Ϣ��������к����б�ɾ������
	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));
	body_ms << CS_DEL_FRIEND;
	body_ms << nRoleID;

	CNetManager::GetMe()->send_msg(body_ms);
}

void Relation_Manager::SendMsgRequestDeleteFriendFromApplyList(const int nRoleID)
{
	/************************************************************************/
	// ������Ϣ�������������б�ɾ������
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
	// ������Ϣ�������������б���Ӻ���
	// 1. ��ȡ���ID
	int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();

	// 2. ������Ϣ
	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));
	body_ms << CS_ADD_FRIEND;
	body_ms << nPlayerID;
	body_ms << nRoleID;

	CNetManager::GetMe()->send_msg(body_ms);
}
