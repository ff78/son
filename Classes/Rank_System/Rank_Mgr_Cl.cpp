#include "Network_Common/NetManager.h"
#include "Network_Common/message.h"
#include "Network_Common/message_coder.h"
#include "Network_Common/message_stream.h"

#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Player_Account/Account_Data_Mgr.h"

#include "../DataModule/Little.h"

#include "Rank_System/Rank_Data.h"
#include "Rank_Mgr_Cl.h"

USING_NS_CC;

Rank_Manager* Rank_Manager::g_pRankManager = 0;

Rank_Manager::Rank_Manager()
{
	m_bPVPRankTypeListIsGet				= false;
	m_bLevelRankTypeListIsGet			= false;
	m_bFightingPowerRankTypeListIsGet	= false;
	m_bMoneyRankTypeListIsGet			= false;
	m_bRenownRankTypeListIsGet			= false;

	m_bCurrentRankTypeListIsChange		= false;

	m_pPVPRankingDataList				= NULL;
	m_pLevelRankingDataList				= NULL;
	m_pFightingPowerRankingDataList		= NULL;
	m_pMoneyRankingDataList				= NULL;	
	m_pRenownRankingDataList			= NULL;

	m_eCurrentRankType					= Rank_Type_Error;

	m_pMyRankingMap.clear();
	m_pRankingListCountMap.clear();
}


Rank_Manager::~Rank_Manager()
{
	SAFE_DELETE_ARRAY(m_pPVPRankingDataList);
	SAFE_DELETE_ARRAY(m_pLevelRankingDataList);
	SAFE_DELETE_ARRAY(m_pFightingPowerRankingDataList);
	SAFE_DELETE_ARRAY(m_pMoneyRankingDataList);
	SAFE_DELETE_ARRAY(m_pRenownRankingDataList);
}

Rank_Manager * Rank_Manager::instance()
{
	if (NULL == g_pRankManager)
		g_pRankManager = new Rank_Manager;

	return g_pRankManager;
}

int Rank_Manager::initialize()
{
	/************************************************************************/
	// ��ʼ��Rank_Manager
	// 1.�����ڴ�ռ�
	m_pPVPRankingDataList				= new TARGET_RANKING_DATA[MAX_RANK_COUNT];
	m_pLevelRankingDataList				= new TARGET_RANKING_DATA[MAX_RANK_COUNT];
	m_pFightingPowerRankingDataList		= new TARGET_RANKING_DATA[MAX_RANK_COUNT];
	m_pMoneyRankingDataList				= new TARGET_RANKING_DATA[MAX_RANK_COUNT];
	m_pRenownRankingDataList			= new TARGET_RANKING_DATA[MAX_RANK_COUNT];

	// 2. ��ʼ�����а��б�ĸ���
	for (int nIndex = 0 ; nIndex < Rank_Type_Error ; ++nIndex)
	{
		m_pMyRankingMap.insert(make_pair((Rank_Type)nIndex, 0));
		m_pRankingListCountMap.insert(make_pair((Rank_Type)nIndex, 0));
	}
	
	return 0;
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// ����߼�����
int Rank_Manager::GetMyRankingInTargetRankType(const Rank_Type eType)
{
	/************************************************************************/
	// ��ȡ����Ŀ�����а������е�����
	// 1. �ж����а������Ƿ��쳣
	if (eType >= Rank_Type_Error)
		return -1;

	// 2. ��ȡ����
	int nRanking = -1;
	std::map<Rank_Type, int>::const_iterator my_ranking_iter = m_pMyRankingMap.find(m_eCurrentRankType);
	if (my_ranking_iter == m_pMyRankingMap.end())
		return -1;
	
	nRanking = my_ranking_iter->second;

	// 3. �ж������Ƿ��쳣(������index + 1)
	if (!JudgeTargetIndexIsError(nRanking - 1))
		return -1;
	
	/************************************************************************/
	// ��������
	return nRanking;
}


void Rank_Manager::RequestTargetRankTypeList()
{
	/************************************************************************/
	// ��ȡ��ǰ�����а��б�
	// 1. �жϵ�ǰ�������а��б������Ƿ��ȡ��
	if (JudgeCurrentRankTypeListIsGet())
		return;
	
	// 2. ������Ϣ��������
	SendMsgRequestTargetTypeRankingList(m_eCurrentRankType);
}


bool Rank_Manager::JudgeTargetIndexIsError(const int nIndex)
{
	/************************************************************************/
	// �ж�Ŀ�������Ƿ��쳣
	// 1. �жϵ�ǰ�����а������Ƿ��쳣
	if (m_eCurrentRankType >= Rank_Type_Error)
		return false;

	// 2. ��ȡĿ�����а����͵����и���
	int nCount = -1;
	std::map<Rank_Type, int>::const_iterator rank_type_count_iter = m_pRankingListCountMap.find(m_eCurrentRankType);
	if (rank_type_count_iter == m_pRankingListCountMap.end())
		return false;

	nCount = rank_type_count_iter->second;

	// 3. �ж�Ŀ�����а����͵����и����Ƿ��쳣
	if (nCount <= 0 || nCount > MAX_RANK_COUNT)
		return false;

	// 4. ���������а������Ƚ�
	if (nIndex < 0 || nIndex >= nCount)
		return false;
	
	return true;
}


bool Rank_Manager::JudgeCurrentRankTypeListIsGet()
{
	/************************************************************************/
	// �жϵ�ǰ�����а��б��Ƿ��ȡ
	if (m_eCurrentRankType == Rank_Type_PVP)
	{
		return m_bPVPRankTypeListIsGet;
	}
	else if (m_eCurrentRankType == Rank_Type_Level)
	{
		return m_bLevelRankTypeListIsGet;
	}
	else if (m_eCurrentRankType == Rank_Type_Fighting_Power)
	{
		return m_bFightingPowerRankTypeListIsGet;
	}
	else if (m_eCurrentRankType == Rank_Type_Money)
	{
		return m_bMoneyRankTypeListIsGet;
	}
	else if (m_eCurrentRankType == Rank_Type_Renown)
	{
		return m_bRenownRankTypeListIsGet;
	}
	else
	{
		return true;
	}
}




TARGET_RANKING_DATA * Rank_Manager::GetTargetIndexRankingData(const int nIndex)
{
	/************************************************************************/
	// ��ȡĿ�����������а�����
	// 1.�ж�Ŀ�������Ƿ��쳣
	if (!JudgeTargetIndexIsError(nIndex))
		return NULL;

	// 2. �������ͻ�ȡ���а�����
	if (m_eCurrentRankType == Rank_Type_PVP)
	{
		return &m_pPVPRankingDataList[nIndex];
	}
	else if (m_eCurrentRankType == Rank_Type_Level)
	{
		return &m_pLevelRankingDataList[nIndex];
	}
	else if (m_eCurrentRankType == Rank_Type_Fighting_Power)
	{
		return &m_pFightingPowerRankingDataList[nIndex];
	}
	else if (m_eCurrentRankType == Rank_Type_Money)
	{
		return &m_pMoneyRankingDataList[nIndex];
	}
	else if (m_eCurrentRankType == Rank_Type_Renown)
	{
		return &m_pRenownRankingDataList[nIndex];
	}
	else
	{
		return NULL;
	}

}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// ����ʾ��Ľ���
bool Rank_Manager::UIRequestEnterTargetRankLayer(const Rank_Type eType)
{
	/************************************************************************/
	// ��ʾ���������Ŀ�����а����
	// 1. �ж�Ŀ�����а�������Ƿ��쳣
	if (eType >= Rank_Type_Error)
		return false;

	// 2. �жϵ�ǰ�����а�������Ƿ���Ҫ���һ��
	if (m_eCurrentRankType == eType)
		return false;

	/************************************************************************/
	// ��������
	// 1. ��¼��ǰ��ҳ��״̬
	m_eCurrentRankType	= eType;
	
	return true;
}

int Rank_Manager::UIRequestCurrentRankTypeCount()
{
	/************************************************************************/
	// ��ʾ������ǰ���а����͵����а����
	// 1. �ж�Ŀ�����а�������Ƿ��쳣
	if (m_eCurrentRankType >= Rank_Type_Error)
		return -1;

	// 2. ��Map�л�ȡĿ�����а�����и���
	int nCount = -1;
	std::map<Rank_Type , int>::const_iterator rank_type_count_iter = m_pRankingListCountMap.find(m_eCurrentRankType);
	if (rank_type_count_iter == m_pRankingListCountMap.end())
		return -1;

	nCount	= rank_type_count_iter->second;
	
	// 3. �жϸ����Ƿ��쳣
	if (nCount > MAX_RANK_COUNT)
		return -1;
	
	return nCount;
}

bool Rank_Manager::UIRequestTargetIndexShowInfo(const int nIndex, TARGET_INDEX_INFO_FOR_SHOW *pInfo)
{
	/************************************************************************/
	// ��ʾ������Ŀ����������ʾ��Ϣ
	// 1.�ж�Ŀ�������Ƿ��쳣
	if (!JudgeTargetIndexIsError(nIndex))
		return false;

	// 2. �ж�Ŀ���������������Ƿ����
	TARGET_RANKING_DATA * pData = GetTargetIndexRankingData(nIndex);
	if (pData == NULL)
		return false;
	
	/************************************************************************/
	// ��������,��Ŀ��ṹ����и�ֵ
	memset(pInfo , 0 , sizeof(TARGET_INDEX_INFO_FOR_SHOW));
	pInfo->nRanking			= pData->nRanking;
	pInfo->nAttributeValue	= pData->nAttributeValue;

	pInfo->szTargetPlayerName = pData->szName;
	pInfo->szTargetPlayerJobName = Little::jobs[pData->nJobID].name;

	return true;
}

bool Rank_Manager::UIRequestTargetIndexSimpleShowInfo(const int nIndex, TARGET_INDEX_SIMPLE_INFO_FOR_SHOW *pInfo)
{
	/************************************************************************/
	// ��ʾ������Ŀ�������򵥵���ʾ��Ϣ
	// 1.�ж�Ŀ�������Ƿ��쳣
	if (!JudgeTargetIndexIsError(nIndex))
		return false;

	// 2. �ж�Ŀ���������������Ƿ����
	TARGET_RANKING_DATA * pData = GetTargetIndexRankingData(nIndex);
	if (pData == NULL)
		return false;

	/************************************************************************/
	// ��������,��Ŀ��ṹ����и�ֵ
	memset(pInfo, 0, sizeof(TARGET_INDEX_SIMPLE_INFO_FOR_SHOW));
	pInfo->nRanking = pData->nRanking;
	// ���Դ���
	// ...
	pInfo->nIconID	= 0;

	return true;
}

bool Rank_Manager::UIRequestPlayerRankingSimpleShowInfo(TARGET_INDEX_SIMPLE_INFO_FOR_SHOW *pInfo)
{
	/************************************************************************/
	// ��ʾ��������ұ���򵥵���ʾ��Ϣ
	// 1. ��ȡ����Լ���Ŀ�����а������е�����
	memset(pInfo, 0, sizeof(TARGET_INDEX_SIMPLE_INFO_FOR_SHOW));
	int nRanking	= -1;
	nRanking		= GetMyRankingInTargetRankType(m_eCurrentRankType);
	
	// 2. �ж������Ƿ��쳣
	if (nRanking <= 0)
		return false;
	
	/************************************************************************/
	// ��������
	// 1. ���ݲ߻�������������ĳ��������û�н���
	if (nRanking < 1 || nRanking > NO_PRESENT_RANKING)
	{
		pInfo->bPresentVisible = false;
	}
	else
	{
		pInfo->bPresentVisible = true;
	}
	
	// 2. �������ʾ��Ϣ��ֵ
	pInfo->nRanking		= nRanking;
	// ���Դ���
	// ...
	pInfo->nIconID		= 0;

	return true;
}


void Rank_Manager::UIRequestCloseRankingListLayer()
{
	/************************************************************************/
	// ��ʾ������ر����а����
	// ��ԭ��ǰ�����а�ҳ��״̬
	m_eCurrentRankType = Rank_Type_Error;
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// ��������Ľ���(����Ϣ)
void Rank_Manager::SendMsgRequestTargetTypeRankingList(const Rank_Type eType)
{
	/************************************************************************/
	// ������Ϣ����Ŀ���������а������б�
	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));
	if (eType == Rank_Type_PVP)
	{
		return;
	}
	else if (eType == Rank_Type_Level)
	{
		body_ms << C2S_LOAD_RANK_ROLE_LEVEL;
	}
	else if (eType == Rank_Type_Fighting_Power)
	{
		body_ms << C2S_LOAD_RANK_ROLE_FIGHTING_CAPACITY;
	}
	else if (eType == Rank_Type_Money)
	{
		body_ms << C2S_LOAD_RANK_ROLE_HAVE_GOLD;
	}
	else if (eType == Rank_Type_Renown)
	{
		return;
	}
	else
	{
		return;
	}
	CNetManager::GetMe()->send_msg(body_ms);
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// ��������Ľ���(����Ϣ)
void Rank_Manager::LoadPVPRankingDataList(message_stream& ms)
{
	/************************************************************************/
	// ���վ������������а������б�
	// 1. ��ȡ���ID
	int nMyRanking	= -1;
	int nPlayerID	= Account_Data_Mgr::instance()->get_current_role_id();

	// 2. �洢����
	memset(m_pPVPRankingDataList , 0 , sizeof(TARGET_RANKING_DATA) * MAX_RANK_COUNT);
	std::string strName;
	int nCount = 0;
	ms >> nCount;
	int nMinCount = nCount > MAX_RANK_COUNT ? MAX_RANK_COUNT : nCount;
	for (int nIndex = 0; nIndex < nMinCount; ++nIndex)
	{
		ms >> m_pPVPRankingDataList[nIndex].nRoleID;
		ms >> m_pPVPRankingDataList[nIndex].nRoleBaseID;
		ms >> strName;
		ms >> m_pPVPRankingDataList[nIndex].nAttributeValue;
		ms >> m_pPVPRankingDataList[nIndex].nJobID;
        m_pPVPRankingDataList[nIndex].szName = strName;

		m_pPVPRankingDataList[nIndex].nRanking = nIndex + 1;

		if (m_pPVPRankingDataList[nIndex].nRoleID == nPlayerID)
		{
			nMyRanking = nIndex + 1;
		}
	}

	// 3. �洢����
	std::map<Rank_Type, int>::iterator rank_type_count_iter = m_pRankingListCountMap.find(Rank_Type_PVP);
	if (rank_type_count_iter == m_pRankingListCountMap.end())
		return ;

	rank_type_count_iter->second = nCount;

	// 4. �洢��ҵ�����
	std::map<Rank_Type, int>::iterator my_ranking_iter = m_pMyRankingMap.find(Rank_Type_PVP);
	if (my_ranking_iter == m_pMyRankingMap.end())
		return;

	my_ranking_iter->second = nMyRanking;

	// 5. ����ҳ��״̬
	if (m_eCurrentRankType == Rank_Type_PVP)
	{
		m_bCurrentRankTypeListIsChange = true;
	}

	// 6. ���������Ƿ���յ���״̬
	m_bPVPRankTypeListIsGet = true;
}

void Rank_Manager::LoadLevelRankingDataList(message_stream& ms)
{
	/************************************************************************/
	// ���յȼ��������а������б�
	// 1. ��ȡ���ID
	int nMyRanking	= -1;
	int nPlayerID	= Account_Data_Mgr::instance()->get_current_role_id();

	// 2. �洢����
	memset(m_pLevelRankingDataList, 0, sizeof(TARGET_RANKING_DATA)* MAX_RANK_COUNT);
	std::string strName;
	int nCount = 0;
	ms >> nCount;
	int nMinCount = nCount > MAX_RANK_COUNT ? MAX_RANK_COUNT : nCount;
	for (int nIndex = 0; nIndex < nMinCount; ++nIndex)
	{
		ms >> m_pLevelRankingDataList[nIndex].nRoleID;
		ms >> m_pLevelRankingDataList[nIndex].nRoleBaseID;
		ms >> strName;
		ms >> m_pLevelRankingDataList[nIndex].nAttributeValue;
		ms >> m_pLevelRankingDataList[nIndex].nJobID;
        m_pLevelRankingDataList[nIndex].szName = strName;

		m_pLevelRankingDataList[nIndex].nRanking = nIndex + 1;

		if (m_pLevelRankingDataList[nIndex].nRoleID == nPlayerID)
		{
			nMyRanking = nIndex + 1;
		}
	}

	// 3. �洢����
	std::map<Rank_Type, int>::iterator rank_type_count_iter = m_pRankingListCountMap.find(Rank_Type_Level);
	if (rank_type_count_iter == m_pRankingListCountMap.end())
		return;

	rank_type_count_iter->second = nCount;

	// 4. �洢��ҵ�����
	std::map<Rank_Type, int>::iterator my_ranking_iter = m_pMyRankingMap.find(Rank_Type_Level);
	if (my_ranking_iter == m_pMyRankingMap.end())
		return;
	my_ranking_iter->second = nMyRanking;

	// 5. ����ҳ��״̬
	if (m_eCurrentRankType == Rank_Type_Level)
	{
		m_bCurrentRankTypeListIsChange = true;
	}

	// 6. ���������Ƿ���յ���״̬
	m_bLevelRankTypeListIsGet = true;
}

void Rank_Manager::LoadFightingPowerRankingDataList(message_stream& ms)
{
	/************************************************************************/
	// ����ս�����������а������б�
	// 1. ��ȡ���ID
	int nMyRanking	= -1;
	int nPlayerID	= Account_Data_Mgr::instance()->get_current_role_id();

	// 2. �洢����
	memset(m_pFightingPowerRankingDataList, 0, sizeof(TARGET_RANKING_DATA)* MAX_RANK_COUNT);
	std::string strName;
	int nCount = 0;
	ms >> nCount;
	int nMinCount = nCount > MAX_RANK_COUNT ? MAX_RANK_COUNT : nCount;
	for (int nIndex = 0; nIndex < nMinCount; ++nIndex)
	{
		ms >> m_pFightingPowerRankingDataList[nIndex].nRoleID;
		ms >> m_pFightingPowerRankingDataList[nIndex].nRoleBaseID;
		ms >> strName;
		ms >> m_pFightingPowerRankingDataList[nIndex].nAttributeValue;
		ms >> m_pFightingPowerRankingDataList[nIndex].nJobID;
        m_pFightingPowerRankingDataList[nIndex].szName = strName;

		m_pFightingPowerRankingDataList[nIndex].nRanking = nIndex + 1;

		if (m_pFightingPowerRankingDataList[nIndex].nRoleID == nPlayerID)
		{
			nMyRanking = nIndex + 1;
		}
	}

	// 3. �洢����
	std::map<Rank_Type, int>::iterator rank_type_count_iter = m_pRankingListCountMap.find(Rank_Type_Fighting_Power);
	if (rank_type_count_iter == m_pRankingListCountMap.end())
		return;

	rank_type_count_iter->second = nCount;

	// 4. �洢��ҵ�����
	std::map<Rank_Type, int>::iterator my_ranking_iter = m_pMyRankingMap.find(Rank_Type_Fighting_Power);
	if (my_ranking_iter == m_pMyRankingMap.end())
		return;

	my_ranking_iter->second = nMyRanking;

	// 5. ����ҳ��״̬
	if (m_eCurrentRankType == Rank_Type_Fighting_Power)
	{
		m_bCurrentRankTypeListIsChange = true;
	}

	// 6. ���������Ƿ���յ���״̬
	m_bFightingPowerRankTypeListIsGet = true;
}

void Rank_Manager::LoadMoneyRankingDataList(message_stream& ms)
{
	/************************************************************************/
	// ���ս�Ǯ�������а������б�
	// 1. ��ȡ���ID
	int nMyRanking	= -1;
	int nPlayerID	= Account_Data_Mgr::instance()->get_current_role_id();

	// 2. �洢����
	memset(m_pMoneyRankingDataList, 0, sizeof(TARGET_RANKING_DATA)* MAX_RANK_COUNT);
	std::string strName;
	int nCount = 0;
	ms >> nCount;
	int nMinCount = nCount > MAX_RANK_COUNT ? MAX_RANK_COUNT : nCount;
	for (int nIndex = 0; nIndex < nMinCount; ++nIndex)
	{
		ms >> m_pMoneyRankingDataList[nIndex].nRoleID;
		ms >> m_pMoneyRankingDataList[nIndex].nRoleBaseID;
		ms >> m_pMoneyRankingDataList[nIndex].szName;
		ms >> m_pMoneyRankingDataList[nIndex].nAttributeValue;
		ms >> m_pMoneyRankingDataList[nIndex].nJobID;


		m_pMoneyRankingDataList[nIndex].nRanking = nIndex + 1;

		if (m_pMoneyRankingDataList[nIndex].nRoleID == nPlayerID)
		{
			nMyRanking = nIndex + 1;
		}
	}

	// 3. �洢����
	std::map<Rank_Type, int>::iterator rank_type_count_iter = m_pRankingListCountMap.find(Rank_Type_Money);
	if (rank_type_count_iter == m_pRankingListCountMap.end())
		return;

	rank_type_count_iter->second = nCount;

	// 4. �洢��ҵ�����
	std::map<Rank_Type, int>::iterator my_ranking_iter = m_pMyRankingMap.find(Rank_Type_Money);
	if (my_ranking_iter == m_pMyRankingMap.end())
		return;

	my_ranking_iter->second = nMyRanking;

	// 5. ����ҳ��״̬
	if (m_eCurrentRankType == Rank_Type_Money)
	{
		m_bCurrentRankTypeListIsChange = true;
	}

	// 6. ���������Ƿ���յ���״̬
	m_bMoneyRankTypeListIsGet = true;
}

void Rank_Manager::LoadRenownRankingDataList(message_stream& ms)
{
	/************************************************************************/
	// ���������������а������б�
	// 1. ��ȡ���ID
	int nMyRanking	= -1;
	int nPlayerID	= Account_Data_Mgr::instance()->get_current_role_id();

	// 2. �洢����
	memset(m_pRenownRankingDataList, 0, sizeof(TARGET_RANKING_DATA)* MAX_RANK_COUNT);
	std::string strName;
	int nCount = 0;
	ms >> nCount;
	int nMinCount = nCount > MAX_RANK_COUNT ? MAX_RANK_COUNT : nCount;
	for (int nIndex = 0; nIndex < nMinCount; ++nIndex)
	{
		ms >> m_pRenownRankingDataList[nIndex].nRoleID;
		ms >> m_pRenownRankingDataList[nIndex].nRoleBaseID;
		ms >> m_pRenownRankingDataList[nIndex].szName;
		ms >> m_pRenownRankingDataList[nIndex].nAttributeValue;
		ms >> m_pRenownRankingDataList[nIndex].nJobID;

		m_pRenownRankingDataList[nIndex].nRanking = nIndex + 1;

		if (m_pRenownRankingDataList[nIndex].nRoleID == nPlayerID)
		{
			nMyRanking = nIndex + 1;
		}
	}

	// 3. �洢����
	std::map<Rank_Type, int>::iterator rank_type_count_iter = m_pRankingListCountMap.find(Rank_Type_Renown);
	if (rank_type_count_iter == m_pRankingListCountMap.end())
		return;

	rank_type_count_iter->second = nCount;

	// 4. �洢��ҵ�����
	std::map<Rank_Type, int>::iterator my_ranking_iter = m_pMyRankingMap.find(Rank_Type_Renown);
	if (my_ranking_iter == m_pMyRankingMap.end())
		return;

	rank_type_count_iter->second = nMyRanking;

	// 5. ����ҳ��״̬
	if (m_eCurrentRankType == Rank_Type_Renown)
	{
		m_bCurrentRankTypeListIsChange = true;
	}

	// 6. ���������Ƿ���յ���״̬
	m_bRenownRankTypeListIsGet = true;
}


//#include "Rank_Mgr_Cl.h"
//
//#include "Character_System/Player.h"
//#include "Player_Account/Account_Data_Mgr.h"
//#include "Character_System/Character_Mgr.h"
//#include "Network_Common/message_stream.h"
////#include "UI/Actor_Mgr.h"
//
//#include "Game_Interface/event_define.h"
//#include "Game_Interface/game_event_response.h"
//
//#ifdef YN_LINUX
//#include <string.h>
//#endif
//
//
//namespace Game_Data
//{
//    Rank_Mgr* Rank_Mgr::instance_ = NULL;
//    Rank_Mgr::Rank_Mgr()
//    {
//        memset(rank_role_level_array_,0,sizeof(rank_role_level_array_));
//        memset(rank_role_fighting_capacity_array_,0,sizeof(rank_role_fighting_capacity_array_));
//        memset(rank_role_have_gold_array_,0,sizeof(rank_role_have_gold_array_));
//    }
//
//    Rank_Mgr::~Rank_Mgr()
//    {
//        memset(rank_role_level_array_,0,sizeof(rank_role_level_array_));
//        memset(rank_role_fighting_capacity_array_,0,sizeof(rank_role_fighting_capacity_array_));
//        memset(rank_role_have_gold_array_,0,sizeof(rank_role_have_gold_array_));
//    }
//
//    Rank_Mgr* Rank_Mgr::instance()
//    {
//        if(instance_ == NULL)
//        {
//            instance_ = new Rank_Mgr;
//        }
//
//        return instance_;
//    }
//
//    void Rank_Mgr::release()
//    {
//        memset(rank_role_level_array_,0,sizeof(rank_role_level_array_));
//        memset(rank_role_fighting_capacity_array_,0,sizeof(rank_role_fighting_capacity_array_));
//        memset(rank_role_have_gold_array_,0,sizeof(rank_role_have_gold_array_));
//    }
//
//    void Rank_Mgr::load_rank(message_stream& ms)
//    {
//        memset(rank_role_level_array_,0,sizeof(rank_role_level_array_));
//        int count = 0;
//        ms >> count;
//        for (int i = 0; i < count && i < RANK_MAX; ++i)
//        {
//            Rank& rank = rank_role_level_array_[i];
//            std::string name;
//            ms >> rank.role_id_;
//            ms >> rank.role_base_id_;
//            ms >> name;
//            ms >> rank.rank_attr_;
//            strncpy(rank.name_,name.c_str(), name.length());
//        }
//    }
//
//    void Rank_Mgr::load_rank_role_level(message_stream& ms)
//    {
//        memset(rank_role_level_array_,0,sizeof(rank_role_level_array_));
//        int count = 0;
//        ms >> count;
//        for (int i = 0; i < count; ++i)
//        {
//            Rank& rank = rank_role_level_array_[i];
//            std::string name;
//            ms >> rank.role_id_;
//            ms >> rank.role_base_id_;
//            ms >> name;
//            ms >> rank.rank_attr_;
//            strncpy(rank.name_,name.c_str(), name.length());
//        }
//    }
//
//    void Rank_Mgr::load_rank_role_fighting_capacity(message_stream& ms)
//    {
//        memset(rank_role_fighting_capacity_array_,0,sizeof(rank_role_fighting_capacity_array_));
//        int count = 0;
//        ms >> count;
//        for (int i = 0; i < count; ++i)
//        {
//            Rank& rank = rank_role_fighting_capacity_array_[i];
//            std::string name;
//            ms >> rank.role_id_;
//            ms >> rank.role_base_id_;
//            ms >> name;
//            ms >> rank.rank_attr_;
//            strncpy(rank.name_,name.c_str(), name.length());
//        }
//    }
//
//    void Rank_Mgr::load_rank_role_have_gold(message_stream& ms)
//    {
//        memset(rank_role_have_gold_array_,0,sizeof(rank_role_have_gold_array_));
//        int count = 0;
//        ms >> count;
//        for (int i = 0; i < count; ++i)
//        {
//            Rank& rank = rank_role_have_gold_array_[i];
//            std::string name;
//            ms >> rank.role_id_;
//            ms >> rank.role_base_id_;
//            ms >> name;
//            ms >> rank.rank_attr_;
//            strncpy(rank.name_,name.c_str(), name.length());
//        }
//    }
//
//    int Rank_Mgr::get_rank_role_level_list(Rank_List& list)
//    {
//        list.clear();
//        int count = 0;
//        Rank* rank = NULL;
//        for (int i = 0;i < RANK_MAX;++i)
//        {
//            rank = &(rank_role_level_array_[i]);
//            if (rank->role_id_ > 0)
//            {
//                list.push_back(rank);
//                ++count;
//            }
//            else
//            {
//                break;
//            }
//        }
//
//        return count;
//    }
//
//    int Rank_Mgr::get_rank_role_fighting_capacity_list(Rank_List& list)
//    {
//        list.clear();
//        int count = 0;
//        Rank* rank = NULL;
//        for (int i = 0;i < RANK_MAX;++i)
//        {
//            rank = &(rank_role_fighting_capacity_array_[i]);
//            if (rank->role_id_ > 0)
//            {
//                list.push_back(rank);
//                ++count;
//            }
//            else
//            {
//                break;
//            }
//        }
//
//        return count;
//    }
//
//    int Rank_Mgr::get_rank_role_have_gold_list(Rank_List& list)
//    {
//        list.clear();
//        int count = 0;
//        Rank* rank = NULL;
//        for (int i = 0;i < RANK_MAX;++i)
//        {
//            rank = &(rank_role_have_gold_array_[i]);
//            if (rank->role_id_ > 0)
//            {
//                list.push_back(rank);
//                ++count;
//            }
//            else
//            {
//                break;
//            }
//        }
//
//        return count;
//    }
//}

