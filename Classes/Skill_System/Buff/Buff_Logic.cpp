/************************************************************************/
// Buff�滻����
// 1. ����Ѱ��FightActor��Buff�б�Ѱ���Ƿ�����Ŀ��Buff����һ�µ�Buff
// 2. ����еĻ����ж��Ƿ���ڿ��滻����
// 3. ������ڿ��滻���͵Ļ�,��ֱ���滻������Buff,�����������ֱ�ӽ���Buff���뵽FightActor��Buff�б���
// 4. ���û����Ŀ��Buff����һ�µ�Buff,��ֱ�ӽ���Buff���뵽FightActor��Buff�б���
// 5. ����Buff��FightActor��Buff�б���ʱ,���û�ﵽ����,��ֱ�Ӳ���
// 6. ����ﵽ����,���滻FightActor�е�һ�������滻��Buff,������е�Buff�������滻,���Buff��Ϊ�����滻���е�Buff�б��е�Buff
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
	// ��ʼ��
	if (pFightActor == NULL)
		return false;

	// 1. ���õ�ǰ��FightActor
	m_pCurrentFightActor	= pFightActor;

	// 2. ������ʱ��
	m_bUpdataIsOpen = true;
	schedule(schedule_selector(Buff_Logic::OnActive), 1.0f);
	return true;
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// ����߼�����
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
	// ���Buff
	// 1. ��ȡ��Ŀ��Buff����һ����Buff�б�
	std::list<int> same_type_buff_list;
	same_type_buff_list.clear();
	int nCount = GetSameTypeBuffListToTargetSkill(nBuffID, &same_type_buff_list);

	// 2. ���û����Ŀ��Buff����һ����Buff�б�,���¼Ŀ��Buff��Map��
	if (nCount == 0)
	{
		RecordTargetBuffToMap(nBuffID);
	}
	// 3. ���������Ŀ��Buff����һ����Buff�б��Ҹ�������
	else if (nCount > 0 && nCount <= MAX_BUFF_COUNT_ON_PALYER)
	{
		bool bValue = false;
		// 3_1. �����б�Ѱ���Ƿ���ڿ��滻���͵�Buff,���������ֱ���滻����Buff
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
		// 3_2. �����б�Ѱ���Ƿ���ڿ��滻���͵�Buff,������������¼Ŀ��Buff��Map��
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
	// ����Ƿ�����Ӧ�Լ��Ƴ�ʱ��
	// 1. �ж϶�ʱ���Ŀ���״̬
	if (!m_bUpdataIsOpen)
	{
		unschedule(schedule_selector(Buff_Logic::OnActive));
		return;
	}
	
	// 2. ��ȡ����Buff����Ӧʱ����Ƴ�ʱ�䲢�����ж�
	int nBuffID								= -1;
	UINT uRespondTime						= 0;
	UINT uRemoveTime						= 0;
	BUFF_CURRENT_TIME_TYPE eCurrentTimeType = BUFF_CURRENT_TIME_TYPE_ERROR;

	std::map<int, int>::const_iterator BuffMapItor = m_pFightActorBuffMap.begin();
	for (; BuffMapItor != m_pFightActorBuffMap.end(); ++BuffMapItor)
	{
		nBuffID		= BuffMapItor->first;
		// 2_1. �ж�ʱ���Ƿ��˽���ʱ��,������˽���ʱ��ֱ���Ƴ�Buff
		int nIndex = BuffMapItor->second;
		if (nIndex < 0 || nIndex >= MAX_BUFF_COUNT_ON_PALYER)
			continue;
		
		uRemoveTime = m_strAllBuffTimeData[nIndex].uBuffRemoveTime;
		if (uRemoveTime <= m_uUpdataCurrentTime)
		{
			RemoveTargetBuff(nBuffID);
			continue;
		}
		
		// 2_2. �ж�ʱ���Ƿ�����Ӧʱ��,���������Ӧʱ������ݵ�ǰ��Buffʱ������ִ����Ӧ������������Ӧʱ��
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
			
			// ������һ�ε���Ӧʱ��
			ChangeTargetBuffNextRespondTime(nBuffID);
		}
	}
	++m_uUpdataCurrentTime;
}


void Buff_Logic::RemoveTargetBuff(const int nBuffID)
{
	/************************************************************************/
	// �Ƴ�Ŀ��Buff
	// 1. �ж�Ŀ��BuffID�Ƿ��쳣
	BUFF_DATA * pData = Buff_Manager::instance()->GetTargetBuffData(nBuffID);
	if (pData == NULL)
		return;

	std::map<int, int>::iterator BuffMapItor = m_pFightActorBuffMap.find(nBuffID);
	if (BuffMapItor == m_pFightActorBuffMap.end())
		return;

	// 2. ��ȡ�Ƴ�ʱ��,���ж��Ƴ�ʱ���Ƿ��쳣
	int nIndex = BuffMapItor->second;
	if (nIndex < 0 || nIndex >= MAX_BUFF_COUNT_ON_PALYER)
		return;

	UINT uBuffRemoveTime = m_strAllBuffTimeData[nIndex].uBuffRemoveTime;
	if (uBuffRemoveTime > m_uUpdataCurrentTime)
		return;

	// 3. ���������Map���Ƴ�Ŀ��Buff
	m_pFightActorBuffMap.erase(nBuffID);
	m_pFreeBuffTimeDataIndexList.push_front(nIndex);

	// 4. �жϵ�ǰ��FightActor�Ƿ���Buff
	JudgeCurrentFightActorHaveBuff();
}


void Buff_Logic::ChangeTargetBuffNextRespondTime(const int nBuffID)
{
	/************************************************************************/
	// ����Ŀ��Buff����һ����Ӧʱ��
	// 1. �ж�Ŀ��BuffID�Ƿ��쳣
	BUFF_DATA * pData = Buff_Manager::instance()->GetTargetBuffData(nBuffID);
	if (pData == NULL)
		return;
	
	std::map<int, int>::iterator BuffMapItor = m_pFightActorBuffMap.find(nBuffID);
	if (BuffMapItor == m_pFightActorBuffMap.end())
		return;

	int nIndex = BuffMapItor->second;
	if (nIndex < 0 || nIndex >= MAX_BUFF_COUNT_ON_PALYER)
		return;

	// 2. ��ȡ��ǰ����һ����սʱ��
	UINT uNextRespondTime = m_strAllBuffTimeData[nIndex].uNextRespondTime;
	if (uNextRespondTime > m_uUpdataCurrentTime)
		return;

	// 3. ���ݵ�ǰ��Buffʱ�����͸�����һ�ε���Ӧʱ��
	BUFF_CURRENT_TIME_TYPE eCurrentTimeType = m_strAllBuffTimeData[nIndex].eBuffTimeType;
	// 3_1. �����ǰ����Buff��Чʱ��,���޸���һ�ε���Ӧʱ��,ͬʱ����ǰ��Buffʱ�����͸�ΪBuff���ʱ��
	// ��һ�ε���Ӧʱ�� = ��ǰʱ�� + ���ʱ��
	if (eCurrentTimeType = BUFF_CURRENT_TIME_TYPE_EFFECTIVE_TIME)
	{
		uNextRespondTime = pData->nBuffIntervalTime + uNextRespondTime;
		m_strAllBuffTimeData[nIndex].eBuffTimeType = BUFF_CURRENT_TIME_INTERVAL_TIME;
	}
	// 3_2. �����ǰ����Buff���ʱ��,���޸���һ�ε���Ӧʱ��,ͬʱ����ǰ��Buffʱ�����͸�ΪBuff��Чʱ��
	// ��һ�ε���Ӧʱ�� = ��ǰʱ�� + ��Чʱ��
	else if (eCurrentTimeType = BUFF_CURRENT_TIME_INTERVAL_TIME)
	{
		uNextRespondTime = pData->nBuffEffectiveTime + uNextRespondTime;
		m_strAllBuffTimeData[nIndex].eBuffTimeType = BUFF_CURRENT_TIME_TYPE_EFFECTIVE_TIME;
	}
	// 3_3. �����ʱ������
	else
	{
		return;
	}
	
	m_strAllBuffTimeData[nIndex].uNextRespondTime = uNextRespondTime;
}


void Buff_Logic::JudgeCurrentFightActorHaveBuff()
{
	/************************************************************************/
	// �жϵ�ǰ��FightActor�Ƿ���Buff
	// 1. �����ǰ��FightActor����Buff,�򲻽����κβ���
	if (m_pFightActorBuffMap.size() > 0)
		return;

	// 2. ���û��Buff,��֪ͨBuffManager���Ŀ��
	Buff_Manager::instance()->RemoveTargetFightActor(m_pCurrentFightActor);
} 


void Buff_Logic::RecordTargetBuffToMap(const int nBuffID)
{
	/************************************************************************/
	// ��¼Ŀ��Buff��Map��
	// 1. �ж�Buff�ĸ����Ƿ�ﵽ����
	int nCount = m_pFightActorBuffMap.size();

	// 2. �������û�дﵽ����,��ֱ�ӽ�Ŀ��Buff���뵽Map��
	if (nCount < MAX_BUFF_COUNT_ON_PALYER && nCount >= 0)
	{
		// 2_1. ��ȡ���е�BuffTimeData�ĸ���,���жϸ����Ƿ��쳣
		int nFreeBuffTimeDataCount = m_pFreeBuffTimeDataIndexList.size();
		if (nFreeBuffTimeDataCount <= 0 || nFreeBuffTimeDataCount > MAX_BUFF_COUNT_ON_PALYER)
			return;

		// 2_2. ��ȡ���е�BuffTimeData�б�ĵ�һ������,���ж��Ƿ��쳣
		int nIndex = m_pFreeBuffTimeDataIndexList.front();
		if (nIndex < 0 || nIndex > MAX_BUFF_COUNT_ON_PALYER)
			return;
		
		// 2_3. ��ȡĿ��Buff������,���ж��Ƿ��쳣
		BUFF_DATA * pData = Buff_Manager::instance()->GetTargetBuffData(nBuffID);
		if (pData == NULL)
			return;

		// 2_4. ��������,�ӿ��е�BuffTimeDataɾ����һ��Ԫ��,����Ŀ��Buff��ʱ��ṹ�帳ֵ�����뵽FightActor�ļ�¼BuffID��Map��
		m_pFreeBuffTimeDataIndexList.pop_front();
		memset(&m_strAllBuffTimeData[nIndex], 0, sizeof(BUFF_TIME_DATA));
		m_strAllBuffTimeData[nIndex].eBuffTimeType		= BUFF_CURRENT_TIME_TYPE_EFFECTIVE_TIME;
		m_strAllBuffTimeData[nIndex].uNextRespondTime	= pData->nBuffEffectiveTime + m_uUpdataCurrentTime;
		m_strAllBuffTimeData[nIndex].uBuffRemoveTime	= pData->nBuffLastTotalTime + m_uUpdataCurrentTime;
		m_pFightActorBuffMap.insert(make_pair(nBuffID, nIndex));
	}
	// 3. ���FightActor��Buff�����ﵽ����
	else if (nCount == MAX_BUFF_COUNT_ON_PALYER)
	{
		// 3_1. ����FightActor������Buff�б�,Ѱ������Ϊ���滻���͵�Buff
		std::map<int, int>::const_iterator actor_buff_map_iter = m_pFightActorBuffMap.begin();
		for (actor_buff_map_iter; actor_buff_map_iter != m_pFightActorBuffMap.end(); ++actor_buff_map_iter)
		{
			int nTempBuffID = actor_buff_map_iter->first;
			BUFF_DATA * pData = Buff_Manager::instance()->GetTargetBuffData(nTempBuffID);
			if (pData == NULL)
				continue;

			// 3_2. ���Buff���Ͳ��ǿ��滻����Buff,�����Ѱ��ֱ���ҵ����滻���͵�Buff,���û�еĻ�,�����Buff
			if (pData->eBuffRepalceType != BUFF_REPLACE_TYPE_YES)
				continue;

			// 3_3. �����������滻֮ǰ��Buff����
			if (!ReplaceNewBuffToOld(nTempBuffID , nBuffID))
				continue;
	
			break;
		}
	}
	// 4. �����FightActor��Buff����,�������κβ���
	else
	{
		return;
	}
}


bool Buff_Logic::ReplaceNewBuffToOld(const int nOldID, const int nNewID)
{
	/************************************************************************/
	// �滻����Buff
	// ע��������滻���ڰ���ͬ���͵Ķ����Լ�FightActor���ϵ�Buff��������,ǿ�ж���,���������滻�����ǲ�ͬ�����滻
	// 1. �ж�����BuffID�Ƿ��쳣
	BUFF_DATA * pOldBuffData = Buff_Manager::instance()->GetTargetBuffData(nOldID);
	if (pOldBuffData == NULL)
		return false;

	BUFF_DATA * pNewBuffData = Buff_Manager::instance()->GetTargetBuffData(nNewID);
	if (pNewBuffData == NULL)
		return false;

	// 2. �ж�ԭ����Buff�Ƿ������FightActor����,���ж�Buffʱ�����ݵ������Ƿ��쳣
	std::map<int, int>::iterator fight_actor_buff_iter = m_pFightActorBuffMap.find(nOldID);
	if (fight_actor_buff_iter == m_pFightActorBuffMap.end())
		return false;

	int nIndex = fight_actor_buff_iter->second;
	if (nIndex < 0 || nIndex >= MAX_BUFF_COUNT_ON_PALYER)
		return false;

	// 3. �ж�ԭ����Buff�������Ƿ�Ϊ���滻������
	if (pOldBuffData->eBuffRepalceType != BUFF_REPLACE_TYPE_YES)
		return false;
	
	/************************************************************************/
	// ��������,�滻�µ�Buff����
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
	// ��ȡ��Ŀ��Buff����һ����Buff�б�
	// 1. �ж�Ŀ��BuffID�Ƿ��쳣
	BUFF_DATA * pTargetBuffData = Buff_Manager::instance()->GetTargetBuffData(nTargetBuffID);
	if (pTargetBuffData == NULL)
		return -1;

	// 2. ��ȡĿ��Buff��Buff����
	BUFF_TYPE eType = pTargetBuffData->eBuffType;
	if (eType >= BUFF_TYPE_MAX)
		return -1;
	
	// 3. �ж�Ŀ�����ϵ�Buff�����Ƿ��쳣
	if (m_pFightActorBuffMap.size() > MAX_BUFF_COUNT_ON_PALYER)
		return -1;
	
	// 4. ����Ŀ�����ϵ�BuffѰ����Ŀ��Buff����һ�µ�BuffID
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

	// 5. ������Ŀ��Buff����һ�µ�Buff�ĸ���
	return pList->size();
}

