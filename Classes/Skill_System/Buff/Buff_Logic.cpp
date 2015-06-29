/************************************************************************/
// Buff替换规则
// 1. 首先寻找FightActor的Buff列表寻找是否有与目标Buff类型一致的Buff
// 2. 如果有的话再判断是否存在可替换类型
// 3. 如果存在可替换类型的话,则直接替换这两个Buff,如果不存在则直接将此Buff插入到FightActor的Buff列表中
// 4. 如果没有与目标Buff类型一致的Buff,则直接将此Buff插入到FightActor的Buff列表中
// 5. 插入Buff到FightActor的Buff列表中时,如果没达到上限,则直接插入
// 6. 如果达到上限,则替换FightActor中第一个可以替换的Buff,如果所有的Buff都不能替换,则此Buff认为不能替换现有的Buff列表中的Buff
/************************************************************************/
#include "ClientLogic/Actor/Actor.h"
#include "ClientLogic/Actor/FightActor.h"

#include "Buff_Common.h"
#include "Buff_Logic.h"
#include "Buff_Mgr.h"

Buff_Logic::Buff_Logic(void)
{
	Clear();
}

Buff_Logic::~Buff_Logic(void)
{

}

bool Buff_Logic::InitData(FightActor * pFightActor)
{
	/************************************************************************/
	// 初始化
	if (pFightActor == NULL)
		return false;

	// 1. 设置当前的FightActor
	m_pCurrentFightActor	= pFightActor;

	// 2. 开启定时器
	m_bUpdataIsOpen = true;
	schedule(schedule_selector(Buff_Logic::OnActive), 1.0f);
	return true;
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// 相关逻辑处理
void Buff_Logic::Clear()
{
	m_uUpdataCurrentTime	= 0;

	m_bUpdataIsOpen			= false;

	m_pCurrentFightActor	= NULL;

	m_pFightActorBuffMap.clear();

	memset(m_strAllBuffTimeData, 0, sizeof(BUFF_TIME_DATA)* MAX_BUFF_COUNT_ON_PALYER);

	for (int nIndex = 0; nIndex < MAX_BUFF_COUNT_ON_PALYER;++nIndex)
	{
		m_pFreeBuffTimeDataIndexList.push_back(nIndex);
	}
}


void Buff_Logic::AddBuff(const int nBuffID)
{
	/************************************************************************/
	// 添加Buff
	// 1. 获取与目标Buff类型一样的Buff列表
	std::list<int> same_type_buff_list;
	same_type_buff_list.clear();
	int nCount = GetSameTypeBuffListToTargetSkill(nBuffID, &same_type_buff_list);

	// 2. 如果没有与目标Buff类型一样的Buff列表,则记录目标Buff到Map中
	if (nCount == 0)
	{
		RecordTargetBuffToMap(nBuffID);
	}
	// 3. 如果存在与目标Buff类型一样的Buff列表，且个数正常
	else if (nCount > 0 && nCount <= MAX_BUFF_COUNT_ON_PALYER)
	{
		bool bValue = false;
		// 3_1. 遍历列表寻找是否存在可替换类型的Buff,如果存在则直接替换两个Buff
		std::list<int>::const_iterator same_type_buff_iter = same_type_buff_list.begin();
		for (same_type_buff_iter; same_type_buff_iter != same_type_buff_list.end(); ++same_type_buff_iter)
		{
			int nTempID = *same_type_buff_iter;
			BUFF_DATA * pTempData = Buff_Manager::instance()->GetTargetBuffData(nTempID);
			if (pTempData == NULL)
				continue;

			if (pTempData->eBuffRepalceType != BUFF_REPLACE_TYPE_YES)
				continue;

			if (!ReplaceNewBuffToOld(nTempID, nBuffID))
				continue;
			
			bValue = true;
			break;
		}
		// 3_2. 遍历列表寻找是否存在可替换类型的Buff,如果不存在则记录目标Buff到Map中
		if (bValue)
		{
			RecordTargetBuffToMap(nBuffID);
		}
	}
	else
	{
		return;
	}
}


void Buff_Logic::OnActive(float dt)
{
	/************************************************************************/
	// 检查是否到了响应以及移除时间
	// 1. 判断定时器的开关状态
	if (!m_bUpdataIsOpen)
	{
		unschedule(schedule_selector(Buff_Logic::OnActive));
		return;
	}
	
	// 2. 获取所有Buff的响应时间和移除时间并进行判断
	int nBuffID								= -1;
	UINT uRespondTime						= 0;
	UINT uRemoveTime						= 0;
	BUFF_CURRENT_TIME_TYPE eCurrentTimeType = BUFF_CURRENT_TIME_TYPE_ERROR;

	std::map<int, int>::const_iterator BuffMapItor = m_pFightActorBuffMap.begin();
	for (; BuffMapItor != m_pFightActorBuffMap.end(); ++BuffMapItor)
	{
		nBuffID		= BuffMapItor->first;
		// 2_1. 判断时间是否到了结束时间,如果到了结束时间直接移除Buff
		int nIndex = BuffMapItor->second;
		if (nIndex < 0 || nIndex >= MAX_BUFF_COUNT_ON_PALYER)
			continue;
		
		uRemoveTime = m_strAllBuffTimeData[nIndex].uBuffRemoveTime;
		if (uRemoveTime <= m_uUpdataCurrentTime)
		{
			RemoveTargetBuff(nBuffID);
			continue;
		}
		
		// 2_2. 判断时间是否到了响应时间,如果到了响应时间则根据当前的Buff时间类型执行响应操作并更换响应时间
		uRespondTime		= m_strAllBuffTimeData[nIndex].uNextRespondTime;
		eCurrentTimeType	= m_strAllBuffTimeData[nIndex].eBuffTimeType;
		if (uRespondTime <= m_uUpdataCurrentTime)
		{
			if (eCurrentTimeType = BUFF_CURRENT_TIME_TYPE_EFFECTIVE_TIME)
			{
				// ...
			}
			else if (eCurrentTimeType = BUFF_CURRENT_TIME_INTERVAL_TIME)
			{
				// ...
			}
			else
			{
				continue;
			}
			
			// 更换下一次的响应时间
			ChangeTargetBuffNextRespondTime(nBuffID);
		}
	}
	++m_uUpdataCurrentTime;
}


void Buff_Logic::RemoveTargetBuff(const int nBuffID)
{
	/************************************************************************/
	// 移除目标Buff
	// 1. 判断目标BuffID是否异常
	BUFF_DATA * pData = Buff_Manager::instance()->GetTargetBuffData(nBuffID);
	if (pData == NULL)
		return;

	std::map<int, int>::iterator BuffMapItor = m_pFightActorBuffMap.find(nBuffID);
	if (BuffMapItor == m_pFightActorBuffMap.end())
		return;

	// 2. 获取移除时间,并判断移除时间是否异常
	int nIndex = BuffMapItor->second;
	if (nIndex < 0 || nIndex >= MAX_BUFF_COUNT_ON_PALYER)
		return;

	UINT uBuffRemoveTime = m_strAllBuffTimeData[nIndex].uBuffRemoveTime;
	if (uBuffRemoveTime > m_uUpdataCurrentTime)
		return;

	// 3. 条件满足从Map中移除目标Buff
	m_pFightActorBuffMap.erase(nBuffID);
	m_pFreeBuffTimeDataIndexList.push_front(nIndex);

	// 4. 判断当前的FightActor是否有Buff
	JudgeCurrentFightActorHaveBuff();
}


void Buff_Logic::ChangeTargetBuffNextRespondTime(const int nBuffID)
{
	/************************************************************************/
	// 更换目标Buff的下一次响应时间
	// 1. 判断目标BuffID是否异常
	BUFF_DATA * pData = Buff_Manager::instance()->GetTargetBuffData(nBuffID);
	if (pData == NULL)
		return;
	
	std::map<int, int>::iterator BuffMapItor = m_pFightActorBuffMap.find(nBuffID);
	if (BuffMapItor == m_pFightActorBuffMap.end())
		return;

	int nIndex = BuffMapItor->second;
	if (nIndex < 0 || nIndex >= MAX_BUFF_COUNT_ON_PALYER)
		return;

	// 2. 获取当前的下一次挑战时间
	UINT uNextRespondTime = m_strAllBuffTimeData[nIndex].uNextRespondTime;
	if (uNextRespondTime > m_uUpdataCurrentTime)
		return;

	// 3. 根据当前的Buff时间类型更换下一次的响应时间
	BUFF_CURRENT_TIME_TYPE eCurrentTimeType = m_strAllBuffTimeData[nIndex].eBuffTimeType;
	// 3_1. 如果当前处于Buff有效时间,则修改下一次的响应时间,同时将当前的Buff时间类型改为Buff间隔时间
	// 下一次的响应时间 = 当前时间 + 间隔时间
	if (eCurrentTimeType = BUFF_CURRENT_TIME_TYPE_EFFECTIVE_TIME)
	{
		uNextRespondTime = pData->nBuffIntervalTime + uNextRespondTime;
		m_strAllBuffTimeData[nIndex].eBuffTimeType = BUFF_CURRENT_TIME_INTERVAL_TIME;
	}
	// 3_2. 如果当前处于Buff间隔时间,则修改下一次的响应时间,同时将当前的Buff时间类型改为Buff有效时间
	// 下一次的响应时间 = 当前时间 + 有效时间
	else if (eCurrentTimeType = BUFF_CURRENT_TIME_INTERVAL_TIME)
	{
		uNextRespondTime = pData->nBuffEffectiveTime + uNextRespondTime;
		m_strAllBuffTimeData[nIndex].eBuffTimeType = BUFF_CURRENT_TIME_TYPE_EFFECTIVE_TIME;
	}
	// 3_3. 错误的时间类型
	else
	{
		return;
	}
	
	m_strAllBuffTimeData[nIndex].uNextRespondTime = uNextRespondTime;
}


void Buff_Logic::JudgeCurrentFightActorHaveBuff()
{
	/************************************************************************/
	// 判断当前的FightActor是否有Buff
	// 1. 如果当前的FightActor还有Buff,则不进行任何操作
	if (m_pFightActorBuffMap.size() > 0)
		return;

	// 2. 如果没有Buff,则通知BuffManager清除目标
	Buff_Manager::instance()->RemoveTargetFightActor(m_pCurrentFightActor);
} 


void Buff_Logic::RecordTargetBuffToMap(const int nBuffID)
{
	/************************************************************************/
	// 记录目标Buff到Map中
	// 1. 判断Buff的个数是否达到上限
	int nCount = m_pFightActorBuffMap.size();

	// 2. 如果个数没有达到上限,则直接将目标Buff插入到Map中
	if (nCount < MAX_BUFF_COUNT_ON_PALYER && nCount >= 0)
	{
		// 2_1. 获取空闲的BuffTimeData的个数,并判断个数是否异常
		int nFreeBuffTimeDataCount = m_pFreeBuffTimeDataIndexList.size();
		if (nFreeBuffTimeDataCount <= 0 || nFreeBuffTimeDataCount > MAX_BUFF_COUNT_ON_PALYER)
			return;

		// 2_2. 获取空闲的BuffTimeData列表的第一个索引,并判断是否异常
		int nIndex = m_pFreeBuffTimeDataIndexList.front();
		if (nIndex < 0 || nIndex > MAX_BUFF_COUNT_ON_PALYER)
			return;
		
		// 2_3. 获取目标Buff的数据,并判断是否异常
		BUFF_DATA * pData = Buff_Manager::instance()->GetTargetBuffData(nBuffID);
		if (pData == NULL)
			return;

		// 2_4. 条件满足,从空闲的BuffTimeData删除第一个元素,并给目标Buff的时间结构体赋值最后插入到FightActor的记录BuffID的Map中
		m_pFreeBuffTimeDataIndexList.pop_front();
		memset(&m_strAllBuffTimeData[nIndex], 0, sizeof(BUFF_TIME_DATA));
		m_strAllBuffTimeData[nIndex].eBuffTimeType		= BUFF_CURRENT_TIME_TYPE_EFFECTIVE_TIME;
		m_strAllBuffTimeData[nIndex].uNextRespondTime	= pData->nBuffEffectiveTime + m_uUpdataCurrentTime;
		m_strAllBuffTimeData[nIndex].uBuffRemoveTime	= pData->nBuffLastTotalTime + m_uUpdataCurrentTime;
		m_pFightActorBuffMap.insert(make_pair(nBuffID, nIndex));
	}
	// 3. 如果FightActor的Buff个数达到上限
	else if (nCount == MAX_BUFF_COUNT_ON_PALYER)
	{
		// 3_1. 遍历FightActor的所有Buff列表,寻找类型为可替换类型的Buff
		std::map<int, int>::const_iterator actor_buff_map_iter = m_pFightActorBuffMap.begin();
		for (actor_buff_map_iter; actor_buff_map_iter != m_pFightActorBuffMap.end(); ++actor_buff_map_iter)
		{
			int nTempBuffID = actor_buff_map_iter->first;
			BUFF_DATA * pData = Buff_Manager::instance()->GetTargetBuffData(nTempBuffID);
			if (pData == NULL)
				continue;

			// 3_2. 如果Buff类型不是可替换类型Buff,则继续寻找直到找到可替换类型的Buff,如果没有的话,则不添加Buff
			if (pData->eBuffRepalceType != BUFF_REPLACE_TYPE_YES)
				continue;

			// 3_3. 条件满足则替换之前的Buff数据
			if (!ReplaceNewBuffToOld(nTempBuffID , nBuffID))
				continue;
	
			break;
		}
	}
	// 4. 错误的FightActor的Buff个数,不进行任何操作
	else
	{
		return;
	}
}


bool Buff_Logic::ReplaceNewBuffToOld(const int nOldID, const int nNewID)
{
	/************************************************************************/
	// 替换两个Buff
	// 注：这里的替换由于包括同类型的顶替以及FightActor身上的Buff个数满了,强行顶替,因此这里的替换可以是不同类型替换
	// 1. 判断两个BuffID是否异常
	BUFF_DATA * pOldBuffData = Buff_Manager::instance()->GetTargetBuffData(nOldID);
	if (pOldBuffData == NULL)
		return false;

	BUFF_DATA * pNewBuffData = Buff_Manager::instance()->GetTargetBuffData(nNewID);
	if (pNewBuffData == NULL)
		return false;

	// 2. 判断原来的Buff是否存在于FightActor身上,并判断Buff时间数据的索引是否异常
	std::map<int, int>::iterator fight_actor_buff_iter = m_pFightActorBuffMap.find(nOldID);
	if (fight_actor_buff_iter == m_pFightActorBuffMap.end())
		return false;

	int nIndex = fight_actor_buff_iter->second;
	if (nIndex < 0 || nIndex >= MAX_BUFF_COUNT_ON_PALYER)
		return false;

	// 3. 判断原来的Buff的类型是否为可替换的类型
	if (pOldBuffData->eBuffRepalceType != BUFF_REPLACE_TYPE_YES)
		return false;
	
	/************************************************************************/
	// 条件满足,替换新的Buff数据
	memset(&m_strAllBuffTimeData[nIndex], 0, sizeof(BUFF_TIME_DATA));
	m_strAllBuffTimeData[nIndex].eBuffTimeType		= BUFF_CURRENT_TIME_TYPE_EFFECTIVE_TIME;
	m_strAllBuffTimeData[nIndex].uNextRespondTime	= pNewBuffData->nBuffEffectiveTime + m_uUpdataCurrentTime;
	m_strAllBuffTimeData[nIndex].uBuffRemoveTime	= pNewBuffData->nBuffLastTotalTime + m_uUpdataCurrentTime;

	m_pFightActorBuffMap.erase(nOldID);
	m_pFightActorBuffMap.insert(make_pair(nNewID, nIndex));
	return true;
}


int Buff_Logic::GetSameTypeBuffListToTargetSkill(const int nTargetBuffID, std::list<int> * pList)
{
	/************************************************************************/
	// 获取与目标Buff类型一样的Buff列表
	// 1. 判断目标BuffID是否异常
	BUFF_DATA * pTargetBuffData = Buff_Manager::instance()->GetTargetBuffData(nTargetBuffID);
	if (pTargetBuffData == NULL)
		return -1;

	// 2. 获取目标Buff的Buff类型
	BUFF_TYPE eType = pTargetBuffData->eBuffType;
	if (eType >= BUFF_TYPE_MAX)
		return -1;
	
	// 3. 判断目标身上的Buff个数是否异常
	if (m_pFightActorBuffMap.size() > MAX_BUFF_COUNT_ON_PALYER)
		return -1;
	
	// 4. 遍历目标身上的Buff寻找与目标Buff类型一致的BuffID
	pList->clear();
	std::map<int, int>::const_iterator map_buff_data_iter = m_pFightActorBuffMap.begin();
	for (map_buff_data_iter; map_buff_data_iter != m_pFightActorBuffMap.end(); ++map_buff_data_iter)
	{
		int nBuffID = map_buff_data_iter->first;
		BUFF_DATA * pData = Buff_Manager::instance()->GetTargetBuffData(nBuffID);
		if (pData == NULL)
			continue;

		if (pData->eBuffType != eType)
			continue;

		pList->push_back(nBuffID);
	}

	// 5. 返回与目标Buff类型一致的Buff的个数
	return pList->size();
}

