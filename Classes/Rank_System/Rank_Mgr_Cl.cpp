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
	// 初始化Rank_Manager
	// 1.申明内存空间
	m_pPVPRankingDataList				= new TARGET_RANKING_DATA[MAX_RANK_COUNT];
	m_pLevelRankingDataList				= new TARGET_RANKING_DATA[MAX_RANK_COUNT];
	m_pFightingPowerRankingDataList		= new TARGET_RANKING_DATA[MAX_RANK_COUNT];
	m_pMoneyRankingDataList				= new TARGET_RANKING_DATA[MAX_RANK_COUNT];
	m_pRenownRankingDataList			= new TARGET_RANKING_DATA[MAX_RANK_COUNT];

	// 2. 初始化排行榜列表的个数
	for (int nIndex = 0 ; nIndex < Rank_Type_Error ; ++nIndex)
	{
		m_pMyRankingMap.insert(make_pair((Rank_Type)nIndex, 0));
		m_pRankingListCountMap.insert(make_pair((Rank_Type)nIndex, 0));
	}
	
	return 0;
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 相关逻辑处理
int Rank_Manager::GetMyRankingInTargetRankType(const Rank_Type eType)
{
	/************************************************************************/
	// 获取我在目标排行榜类型中的排名
	// 1. 判断排行榜类型是否异常
	if (eType >= Rank_Type_Error)
		return -1;

	// 2. 获取排名
	int nRanking = -1;
	std::map<Rank_Type, int>::const_iterator my_ranking_iter = m_pMyRankingMap.find(m_eCurrentRankType);
	if (my_ranking_iter == m_pMyRankingMap.end())
		return -1;
	
	nRanking = my_ranking_iter->second;

	// 3. 判断排名是否异常(排名是index + 1)
	if (!JudgeTargetIndexIsError(nRanking - 1))
		return -1;
	
	/************************************************************************/
	// 条件满足
	return nRanking;
}


void Rank_Manager::RequestTargetRankTypeList()
{
	/************************************************************************/
	// 获取当前的排行榜列表
	// 1. 判断当前类型排行榜列表数据是否获取到
	if (JudgeCurrentRankTypeListIsGet())
		return;
	
	// 2. 发送消息请求数据
	SendMsgRequestTargetTypeRankingList(m_eCurrentRankType);
}


bool Rank_Manager::JudgeTargetIndexIsError(const int nIndex)
{
	/************************************************************************/
	// 判断目标索引是否异常
	// 1. 判断当前的排行榜类型是否异常
	if (m_eCurrentRankType >= Rank_Type_Error)
		return false;

	// 2. 获取目标排行榜类型的排行个数
	int nCount = -1;
	std::map<Rank_Type, int>::const_iterator rank_type_count_iter = m_pRankingListCountMap.find(m_eCurrentRankType);
	if (rank_type_count_iter == m_pRankingListCountMap.end())
		return false;

	nCount = rank_type_count_iter->second;

	// 3. 判断目标排行榜类型的排行个数是否异常
	if (nCount <= 0 || nCount > MAX_RANK_COUNT)
		return false;

	// 4. 索引与排行榜个数相比较
	if (nIndex < 0 || nIndex >= nCount)
		return false;
	
	return true;
}


bool Rank_Manager::JudgeCurrentRankTypeListIsGet()
{
	/************************************************************************/
	// 判断当前的排行榜列表是否获取
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
	// 获取目标索引的排行榜数据
	// 1.判断目标索引是否异常
	if (!JudgeTargetIndexIsError(nIndex))
		return NULL;

	// 2. 根据类型获取排行榜数据
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
// 与显示层的交互
bool Rank_Manager::UIRequestEnterTargetRankLayer(const Rank_Type eType)
{
	/************************************************************************/
	// 显示层请求进入目标排行榜界面
	// 1. 判断目标排行榜的类型是否异常
	if (eType >= Rank_Type_Error)
		return false;

	// 2. 判断当前的排行榜的类型是否与要求的一致
	if (m_eCurrentRankType == eType)
		return false;

	/************************************************************************/
	// 条件满足
	// 1. 记录当前的页面状态
	m_eCurrentRankType	= eType;
	
	return true;
}

int Rank_Manager::UIRequestCurrentRankTypeCount()
{
	/************************************************************************/
	// 显示层请求当前排行榜类型的排行榜个数
	// 1. 判断目标排行榜的类型是否异常
	if (m_eCurrentRankType >= Rank_Type_Error)
		return -1;

	// 2. 从Map中获取目标排行榜的排行个数
	int nCount = -1;
	std::map<Rank_Type , int>::const_iterator rank_type_count_iter = m_pRankingListCountMap.find(m_eCurrentRankType);
	if (rank_type_count_iter == m_pRankingListCountMap.end())
		return -1;

	nCount	= rank_type_count_iter->second;
	
	// 3. 判断个数是否异常
	if (nCount > MAX_RANK_COUNT)
		return -1;
	
	return nCount;
}

bool Rank_Manager::UIRequestTargetIndexShowInfo(const int nIndex, TARGET_INDEX_INFO_FOR_SHOW *pInfo)
{
	/************************************************************************/
	// 显示层请求目标索引的显示信息
	// 1.判断目标索引是否异常
	if (!JudgeTargetIndexIsError(nIndex))
		return false;

	// 2. 判断目标类型排名数据是否存在
	TARGET_RANKING_DATA * pData = GetTargetIndexRankingData(nIndex);
	if (pData == NULL)
		return false;
	
	/************************************************************************/
	// 条件满足,对目标结构体进行赋值
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
	// 显示层请求目标索引简单的显示信息
	// 1.判断目标索引是否异常
	if (!JudgeTargetIndexIsError(nIndex))
		return false;

	// 2. 判断目标类型排名数据是否存在
	TARGET_RANKING_DATA * pData = GetTargetIndexRankingData(nIndex);
	if (pData == NULL)
		return false;

	/************************************************************************/
	// 条件满足,对目标结构体进行赋值
	memset(pInfo, 0, sizeof(TARGET_INDEX_SIMPLE_INFO_FOR_SHOW));
	pInfo->nRanking = pData->nRanking;
	// 测试代码
	// ...
	pInfo->nIconID	= 0;

	return true;
}

bool Rank_Manager::UIRequestPlayerRankingSimpleShowInfo(TARGET_INDEX_SIMPLE_INFO_FOR_SHOW *pInfo)
{
	/************************************************************************/
	// 显示层请求玩家本身简单的显示信息
	// 1. 获取玩家自己在目标排行榜类型中的排名
	memset(pInfo, 0, sizeof(TARGET_INDEX_SIMPLE_INFO_FOR_SHOW));
	int nRanking	= -1;
	nRanking		= GetMyRankingInTargetRankType(m_eCurrentRankType);
	
	// 2. 判断排名是否异常
	if (nRanking <= 0)
		return false;
	
	/************************************************************************/
	// 条件满足
	// 1. 根据策划需求排名大于某个名次是没有奖励
	if (nRanking < 1 || nRanking > NO_PRESENT_RANKING)
	{
		pInfo->bPresentVisible = false;
	}
	else
	{
		pInfo->bPresentVisible = true;
	}
	
	// 2. 其余的显示信息赋值
	pInfo->nRanking		= nRanking;
	// 测试代码
	// ...
	pInfo->nIconID		= 0;

	return true;
}


void Rank_Manager::UIRequestCloseRankingListLayer()
{
	/************************************************************************/
	// 显示层请求关闭排行榜界面
	// 还原当前的排行榜页面状态
	m_eCurrentRankType = Rank_Type_Error;
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 与服务器的交互(发消息)
void Rank_Manager::SendMsgRequestTargetTypeRankingList(const Rank_Type eType)
{
	/************************************************************************/
	// 发送消息请求目标类型排行榜数据列表
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
// 与服务器的交互(接消息)
void Rank_Manager::LoadPVPRankingDataList(message_stream& ms)
{
	/************************************************************************/
	// 接收竞技场类型排行榜数据列表
	// 1. 获取玩家ID
	int nMyRanking	= -1;
	int nPlayerID	= Account_Data_Mgr::instance()->get_current_role_id();

	// 2. 存储数据
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

	// 3. 存储个数
	std::map<Rank_Type, int>::iterator rank_type_count_iter = m_pRankingListCountMap.find(Rank_Type_PVP);
	if (rank_type_count_iter == m_pRankingListCountMap.end())
		return ;

	rank_type_count_iter->second = nCount;

	// 4. 存储玩家的排名
	std::map<Rank_Type, int>::iterator my_ranking_iter = m_pMyRankingMap.find(Rank_Type_PVP);
	if (my_ranking_iter == m_pMyRankingMap.end())
		return;

	my_ranking_iter->second = nMyRanking;

	// 5. 更改页面状态
	if (m_eCurrentRankType == Rank_Type_PVP)
	{
		m_bCurrentRankTypeListIsChange = true;
	}

	// 6. 更改数据是否接收到的状态
	m_bPVPRankTypeListIsGet = true;
}

void Rank_Manager::LoadLevelRankingDataList(message_stream& ms)
{
	/************************************************************************/
	// 接收等级类型排行榜数据列表
	// 1. 获取玩家ID
	int nMyRanking	= -1;
	int nPlayerID	= Account_Data_Mgr::instance()->get_current_role_id();

	// 2. 存储数据
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

	// 3. 存储个数
	std::map<Rank_Type, int>::iterator rank_type_count_iter = m_pRankingListCountMap.find(Rank_Type_Level);
	if (rank_type_count_iter == m_pRankingListCountMap.end())
		return;

	rank_type_count_iter->second = nCount;

	// 4. 存储玩家的排名
	std::map<Rank_Type, int>::iterator my_ranking_iter = m_pMyRankingMap.find(Rank_Type_Level);
	if (my_ranking_iter == m_pMyRankingMap.end())
		return;
	my_ranking_iter->second = nMyRanking;

	// 5. 更改页面状态
	if (m_eCurrentRankType == Rank_Type_Level)
	{
		m_bCurrentRankTypeListIsChange = true;
	}

	// 6. 更改数据是否接收到的状态
	m_bLevelRankTypeListIsGet = true;
}

void Rank_Manager::LoadFightingPowerRankingDataList(message_stream& ms)
{
	/************************************************************************/
	// 接收战斗力类型排行榜数据列表
	// 1. 获取玩家ID
	int nMyRanking	= -1;
	int nPlayerID	= Account_Data_Mgr::instance()->get_current_role_id();

	// 2. 存储数据
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

	// 3. 存储个数
	std::map<Rank_Type, int>::iterator rank_type_count_iter = m_pRankingListCountMap.find(Rank_Type_Fighting_Power);
	if (rank_type_count_iter == m_pRankingListCountMap.end())
		return;

	rank_type_count_iter->second = nCount;

	// 4. 存储玩家的排名
	std::map<Rank_Type, int>::iterator my_ranking_iter = m_pMyRankingMap.find(Rank_Type_Fighting_Power);
	if (my_ranking_iter == m_pMyRankingMap.end())
		return;

	my_ranking_iter->second = nMyRanking;

	// 5. 更改页面状态
	if (m_eCurrentRankType == Rank_Type_Fighting_Power)
	{
		m_bCurrentRankTypeListIsChange = true;
	}

	// 6. 更改数据是否接收到的状态
	m_bFightingPowerRankTypeListIsGet = true;
}

void Rank_Manager::LoadMoneyRankingDataList(message_stream& ms)
{
	/************************************************************************/
	// 接收金钱类型排行榜数据列表
	// 1. 获取玩家ID
	int nMyRanking	= -1;
	int nPlayerID	= Account_Data_Mgr::instance()->get_current_role_id();

	// 2. 存储数据
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

	// 3. 存储个数
	std::map<Rank_Type, int>::iterator rank_type_count_iter = m_pRankingListCountMap.find(Rank_Type_Money);
	if (rank_type_count_iter == m_pRankingListCountMap.end())
		return;

	rank_type_count_iter->second = nCount;

	// 4. 存储玩家的排名
	std::map<Rank_Type, int>::iterator my_ranking_iter = m_pMyRankingMap.find(Rank_Type_Money);
	if (my_ranking_iter == m_pMyRankingMap.end())
		return;

	my_ranking_iter->second = nMyRanking;

	// 5. 更改页面状态
	if (m_eCurrentRankType == Rank_Type_Money)
	{
		m_bCurrentRankTypeListIsChange = true;
	}

	// 6. 更改数据是否接收到的状态
	m_bMoneyRankTypeListIsGet = true;
}

void Rank_Manager::LoadRenownRankingDataList(message_stream& ms)
{
	/************************************************************************/
	// 接收声望类型排行榜数据列表
	// 1. 获取玩家ID
	int nMyRanking	= -1;
	int nPlayerID	= Account_Data_Mgr::instance()->get_current_role_id();

	// 2. 存储数据
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

	// 3. 存储个数
	std::map<Rank_Type, int>::iterator rank_type_count_iter = m_pRankingListCountMap.find(Rank_Type_Renown);
	if (rank_type_count_iter == m_pRankingListCountMap.end())
		return;

	rank_type_count_iter->second = nCount;

	// 4. 存储玩家的排名
	std::map<Rank_Type, int>::iterator my_ranking_iter = m_pMyRankingMap.find(Rank_Type_Renown);
	if (my_ranking_iter == m_pMyRankingMap.end())
		return;

	rank_type_count_iter->second = nMyRanking;

	// 5. 更改页面状态
	if (m_eCurrentRankType == Rank_Type_Renown)
	{
		m_bCurrentRankTypeListIsChange = true;
	}

	// 6. 更改数据是否接收到的状态
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

