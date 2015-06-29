#include "cocos2d.h"
#include "ClientLogic/Utils/GameReader.h"

#include "ClientLogic/Actor/Actor.h"
#include "ClientLogic/Actor/FightActor.h"

#include "Buff_Common.h"
#include "Buff_Logic.h"
#include "Buff_Mgr.h"

USING_NS_CC;
using namespace cocostudio;

Buff_Manager* Buff_Manager::g_pBuffManager = 0;

Buff_Manager::Buff_Manager()
{
	m_pAllBuffCount					= 0;

	m_pBuffLogicData				= NULL;
	m_pAllBuffData					= NULL;
	g_pBuffManager					= NULL;

	m_pFightActorMap.clear();
	m_pFreeLogicTagID.clear();
}


Buff_Manager::~Buff_Manager()
{
}

Buff_Manager * Buff_Manager::instance()
{
	if (NULL == g_pBuffManager)
		g_pBuffManager = new Buff_Manager;

	return g_pBuffManager;
}

int Buff_Manager::initialize()
{
	// ��ʼ��BuffManager����
	if (!InitializeBuffData())
		return -1;

	// ��ʼ������Buff�Ĺ�����
	if (!InitializeBuffLogic())
		return -1;
	
	return 0;
}


bool Buff_Manager::InitializeBuffData()
{
	/************************************************************************/
	// ��ʼ��BuffManager����
	// 1. ��ȡ���ñ�,�ж϶�ȡ�����ñ��Ƿ��쳣
	rapidjson::Document * pDocument = GameReader::getDocInstance("game_data/Buff_System/Buff_Config.json");
	if (pDocument == NULL)
		return false;

	if (!pDocument->IsArray())
		return false;

	m_pAllBuffCount = pDocument->Size();
	if (m_pAllBuffCount <= 0)
		return false;

	m_pAllBuffData = new BUFF_DATA[m_pAllBuffCount];
	if (m_pAllBuffData == NULL)
		return false;

	// 2. ��ȡ���ñ��е�����
	int nTemp = 0;
	const char *szTemp = NULL;
	for (int i = 0; i < m_pAllBuffCount; ++i)
	{
		const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*pDocument), i);

		// ����ID
		nTemp = DICTOOL->getIntValue_json(dic, "Index_ID");
		m_pAllBuffData[i].byIndexID					= nTemp;

		// Buff��ͼ��ID
		nTemp = DICTOOL->getIntValue_json(dic, "Buff_Icon_ID");
		m_pAllBuffData[i].nBuffIconID				= nTemp;

		// Buff����Ч��������
		nTemp = DICTOOL->getIntValue_json(dic, "Buff_All_Effect_Type");
		if (nTemp >= BUFF_ALL_EFFECT_TYPE_ERROR || nTemp < 0)
			return false;

		m_pAllBuffData[i].eBuffAllEffectType		= (BUFF_ALL_EFFECT_TYPE)nTemp;

		// Buff��Чʱ��
		szTemp = DICTOOL->getStringValue_json(dic, "Buff_Effective_Time");
		nTemp = DealWithIntervalTimeAndTotalTime(szTemp);
		if (nTemp < 0)
			return false;

		m_pAllBuffData[i].nBuffEffectiveTime		= nTemp;

		// Buff���ʱ��
		szTemp = DICTOOL->getStringValue_json(dic, "Buff_Interval_Time");
		nTemp = DealWithIntervalTimeAndTotalTime(szTemp);
		if (nTemp < 0)
			return false;

		m_pAllBuffData[i].nBuffIntervalTime			= nTemp;

		// Buff�ܳ���ʱ��
		szTemp = DICTOOL->getStringValue_json(dic, "Buff_Last_Total_Time");
		nTemp = DealWithIntervalTimeAndTotalTime(szTemp);
		if (nTemp <= 0)
			return false;

		m_pAllBuffData[i].nBuffLastTotalTime		= nTemp;

		// Buff������
		szTemp = DICTOOL->getStringValue_json(dic, "Buff_Describe");
		sprintf(m_pAllBuffData[i].szBuffDescribe, szTemp, nullptr);
		m_pAllBuffData[i].szBuffDescribe[sizeof(m_pAllBuffData[i].szBuffDescribe) - 1] = '\0';

		// Buff������
		nTemp = DICTOOL->getIntValue_json(dic, "Buff_Type");
		if (nTemp >= BUFF_TYPE_MAX || nTemp < 0)
			return false;

		m_pAllBuffData[i].eBuffType					= (BUFF_TYPE)nTemp;

		// Buff�Ƿ���Ա��滻
		nTemp = DICTOOL->getIntValue_json(dic, "Buff_Replace_Type");
		if (nTemp >= BUFF_REPLACE_TYPE_ERROR || nTemp < 0)
			return false;

		m_pAllBuffData[i].eBuffRepalceType			= (BUFF_REPLACE_TYPE)nTemp;

		// Buff��Ч������
		szTemp = DICTOOL->getStringValue_json(dic, "Buff_Effect_Attribute_Type");
		int n_1 = DealWithBuffEffectData(szTemp, DEAL_BUFF_EFFECT_ATTRIBUTE_TYPE, m_pAllBuffData[i].strBuffEffectData);
		if (n_1 <= 0)
			return false;

		// ����Buff����ֵ������
		szTemp = DICTOOL->getStringValue_json(dic, "Buff_Effect_Attribute_Value_Type");
		int n_2 = DealWithBuffEffectData(szTemp, DEAL_BUFF_EFFECT_ATTRIBUTE_VALUE_TYPE, m_pAllBuffData[i].strBuffEffectData);
		if (n_2 <= 0 || n_2 != n_1)
			return false;

		// ����Buff����ֵ
		szTemp = DICTOOL->getStringValue_json(dic, "Buff_Effect_Attribute_Value");
		int n_3 = DealWithBuffEffectData(szTemp, DEAL_BUFF_EFFECT_ATTRIBUTE_VALUE, m_pAllBuffData[i].strBuffEffectData);
		if (n_3 <= 0 || n_3 != n_2)
			return false;
	}
	return true;
}


bool Buff_Manager::InitializeBuffLogic()
{
	/************************************************************************/
	// ��ʼ��BuffLogic
	m_pBuffLogicData = new Buff_Logic[MAX_BUFF_LOGIC_COUNT];
	if (m_pBuffLogicData == NULL)
		return false;

	for (int nIndex = 0; nIndex < MAX_BUFF_LOGIC_COUNT; nIndex++)
	{
		m_pBuffLogicData[nIndex].SetCurrentLogicTagID(nIndex);
		m_pFreeLogicTagID.push_back(nIndex);
	}
	return true;
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// ���ݴ������ط���
int Buff_Manager::DealWithIntervalTimeAndTotalTime(string strTemp)
{
	/************************************************************************/
	// �������ñ��й���ʱ����ֶε�����
	// ע������ʱ���ʽΪ0h0m0s������
	// 1. �жϹ���ʱ����ַ����б�ʾ�룬���Ӻ�Сʱ�ַ��Ƿ����
	int nSize = 0;
	// 1_1. �ж����Ƿ����,���ڵĻ����滻's'Ϊ' '
	string::size_type idx = strTemp.find('s');
	bool bSecondExist = false;
	bSecondExist = idx != string::npos;
	if (bSecondExist)
	{
		replace(strTemp.begin(), strTemp.end(), 's', ' ');
		++nSize;
	}

	// 1_2. �жϷ����Ƿ����,���ڵĻ����滻'm'Ϊ' '
	idx = strTemp.find('m');
	bool bMinuteExist = false;
	bMinuteExist = idx != string::npos;
	if (bMinuteExist)
	{
		replace(strTemp.begin(), strTemp.end(), 'm', ' ');
		++nSize;
	}
	
	// 1_3. �ж�Сʱ�Ƿ����,���ڵĻ����滻'h'Ϊ' '
	idx = strTemp.find('h');
	bool bHourExist = false;
	bHourExist = idx != string::npos;
	if (bHourExist)
	{
		replace(strTemp.begin(), strTemp.end(), 'h', ' ');
		++nSize;
	}

	// 2. ���ʱ��
	int nTime = 0;
	int nTemp[3] = {0};
	istringstream stream(strTemp);
	for (int nIndex = 0; nIndex < nSize; ++nIndex)
	{
		stream >> nTemp[nIndex];
	}

	// 3. ͨ���㷨��ʱ�任�����
	// ���￼������û����΢�򵥵���㷨
	// ...
	if (nSize == 3)
	{
		nTime = nTemp[0] * 60 * 60 + nTemp[1] * 60 + nTemp[2];
	}
	else if (nSize == 2)
	{
		if (bHourExist)
		{
			if (bMinuteExist)
			{
				nTime = nTemp[0] * 60 * 60 + nTemp[1] * 60;
			}
			else
			{
				nTime = nTemp[0] * 60 * 60 + nTemp[1];
			}
		}
		else
		{
			nTime = nTemp[0] * 60 + nTemp[1];
		}
	}
	else if (nSize == 1)
	{
		if (bHourExist && !bMinuteExist && !bSecondExist)
		{
			nTime = nTemp[0] * 60 * 60;
		}
		else if (!bHourExist && bMinuteExist && !bSecondExist)
		{
			nTime = nTemp[0] * 60;
		}
		else if (!bHourExist && !bMinuteExist && bSecondExist)
		{
			nTime = nTemp[0];
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
	return nTime;
}


int Buff_Manager::DealWithBuffEffectData(string strTemp, const DEAL_BUFF_TYPE eType, BUFF_EFFECT_DATA * pData)
{
	/************************************************************************/
	// �������ñ��й���ʱ����ֶε�����
	// ע��BuffЧ���ĸ�ʽ�����ַ�"|"�ָ���
	// 1. ��ȡ��Buff��Ч���ĸ���
	int nSize = static_cast<int>(count(strTemp.begin() , strTemp.end() , '|'));
	if (nSize > MAX_EFFECT_COUNT)
		return -1;

	replace(strTemp.begin(), strTemp.end(), '|', ' ');
	istringstream stream(strTemp);

	// 2. ����Ч��������,���������������ݸ�ֵ���ṹ����
	int nTemp = -1;
	// 2_1. �����������BuffЧ������������
	if (eType == DEAL_BUFF_EFFECT_ATTRIBUTE_TYPE)
	{
		for (int nIndex = 0; nIndex < nSize; ++nIndex)
		{
			stream >> nTemp;
			if (nTemp >= BUFF_EFFECT_ATTRIBUTE_TYPE_MAX || nTemp < 0)
				return -1;
			
			pData[nIndex].eEffectAttributeType		= (BUFF_EFFECT_ATTRIBUTE_TYPE)nTemp;
		}
	}
	// 2_2. �����������BuffЧ����������ֵ����
	else if (eType == DEAL_BUFF_EFFECT_ATTRIBUTE_VALUE_TYPE)
	{
		for (int nIndex = 0; nIndex < nSize; ++nIndex)
		{
			stream >> nTemp;
			if (nTemp >= BUFF_EFFECT_ATTRIBUTE_VALUE_TYPE_ERROR || nTemp < 0)
				return -1;

			pData[nIndex].eEffectAttributeValueType	= (BUFF_EFFECT_ATTRIBUTE_VALUE_TYPE)nTemp;
		}
	}
	// 2_3. �����������BuffЧ������ֵ����
	else if (eType == DEAL_BUFF_EFFECT_ATTRIBUTE_VALUE)
	{
		for (int nIndex = 0; nIndex < nSize; ++nIndex)
		{
			stream >> nTemp;

			pData[nIndex].nEffectValue				= (BUFF_EFFECT_ATTRIBUTE_VALUE_TYPE)nTemp;
		}
	}
	// 2_4. ����Ľ�������
	else
	{
		return -1;
	}
	return nSize;
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// ����߼�����
bool Buff_Manager::FightActorAddBuff(FightActor * pFightActor , int nBuffID)
{
	/************************************************************************/
	// Ŀ��������Buff
	// 1. �ж�Ŀ��ID��Buff�Ƿ����
	BUFF_DATA * pBuffData = GetTargetBuffData(nBuffID);
	if (pBuffData == NULL)
		return false;
	
	// 2. �ж�Ŀ��FightActor֮ǰ�Ƿ��д��ڼ�¼
	int nTagID										= -1;
	std::list<int>::iterator list_itor				= m_pFreeLogicTagID.begin();
	std::map<FightActor *, int>::iterator map_itor	= m_pFightActorMap.find(pFightActor);
	// 2_1. ���֮ǰ�м�¼,�����BuffLogic�������Buff
	if (map_itor != m_pFightActorMap.end())
	{
		nTagID = map_itor->second;
		if (nTagID < 0 || nTagID >= MAX_BUFF_LOGIC_COUNT)
			return false;

		m_pBuffLogicData[nTagID].AddBuff(nBuffID);
	}
	// 2_2. ���֮ǰû�м�¼,���¼��FightActor
	else
	{
		nTagID = *list_itor;
		if (nTagID < 0 || nTagID >= MAX_BUFF_LOGIC_COUNT)
			return false;

		if (!m_pBuffLogicData[nTagID].InitData(pFightActor))
			return false;

		m_pFightActorMap[pFightActor] = nTagID;
		m_pFreeLogicTagID.pop_front();

		m_pBuffLogicData[nTagID].AddBuff(nBuffID);
	}
	return true;
}


void Buff_Manager::RemoveTargetFightActor(FightActor * pFightActor)
{
	/************************************************************************/
	// ���Ŀ��FightActor
	// 1. �ж�Ŀ��FightActor�Ƿ��쳣
	if (pFightActor == NULL)
		return;
	
	std::map<FightActor *, int>::iterator map_itor = m_pFightActorMap.find(pFightActor);
	if (map_itor == m_pFightActorMap.end())
		return;

	int nTagID = -1;
	nTagID = map_itor->second;
	if (nTagID < 0 || nTagID >= MAX_BUFF_LOGIC_COUNT)
		return;
	
	std::list<int>::iterator list_itor = m_pFreeLogicTagID.begin();
	for (; list_itor != m_pFreeLogicTagID.end(); ++list_itor)
	{
		if (*list_itor == nTagID)
			return;
	}

	// 2. ��������,���Ŀ��BuffLogic����
	m_pFreeLogicTagID.push_front(nTagID);
	m_pFightActorMap.erase(pFightActor);

	m_pBuffLogicData[nTagID].Clear();
}
