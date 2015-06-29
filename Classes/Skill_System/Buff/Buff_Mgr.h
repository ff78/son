/* -------------------------------------------------------------------------
//	�ļ���		��	Buff.h
//	��������	��	BUFF�࣬��������BUFF�����ݡ�
// -----------------------------------------------------------------------*/
#ifndef _Buff_Manager_H_
#define _Buff_Manager_H_
#include "Buff_Common.h"

class FightActor;
class Buff_Logic;

// ����Buff����
enum DEAL_BUFF_TYPE
{
	DEAL_BUFF_EFFECT_ATTRIBUTE_TYPE,							  // ����Buff��Ч������
	DEAL_BUFF_EFFECT_ATTRIBUTE_VALUE_TYPE,						  // ����Buff����ֵ������
	DEAL_BUFF_EFFECT_ATTRIBUTE_VALUE,							  // ����Buff����ֵ
	DEAL_BUFF_EFFECT_MAX
};

class Buff_Manager
{
public:
	Buff_Manager();
	~Buff_Manager();
	int  initialize();																															// ��ʼ��BuffManager
	bool InitializeBuffData();																													// ��ʼ������Buff������(��ȡ���ñ�)
	bool InitializeBuffLogic();																													// ��ʼ��BuffLogic

	static Buff_Manager * instance();

private:
	//---��Ա����---//
	int										m_pAllBuffCount;																					 // ����Buff�ĸ���

	std::list<int>							m_pFreeLogicTagID;																					 // �����Logic��ʶID�б�
	std::map<FightActor * , int>			m_pFightActorMap;																					 // FightActor�б�

	Buff_Logic*								m_pBuffLogicData;																					 // ����Buff�Ĺ�����

	BUFF_DATA*								m_pAllBuffData;																						 // ����Buff������

private:
	//---���ݴ������ط���---//
	int										DealWithIntervalTimeAndTotalTime(string strTemp);													// �������ñ��й���ʱ����ֶε�����
	int										DealWithBuffEffectData(string strTemp, const DEAL_BUFF_TYPE eType, BUFF_EFFECT_DATA * pData);		// �������ñ��й���BuffЧ�����ֶε�����

public:
	//---����߼�����---//
	bool									FightActorAddBuff(FightActor * pFightActor , int nBuffID);											// Ŀ��������Buff

	void									RemoveTargetFightActor(FightActor * pFightActor);													// ���Ŀ��FightActor

public:
	//--��ȡ�����ó�Ա����---//
	inline  BUFF_DATA *						GetTargetBuffData(const int nTargetID)																// ��ȡָ��ID��Buff����
	{
		if (nTargetID < 0 || nTargetID > m_pAllBuffCount - 1)
			return NULL;

		return &m_pAllBuffData[nTargetID];
	}
	

private:
	static Buff_Manager * g_pBuffManager;
};


#endif // !_Buff_Manager_H_