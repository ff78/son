/* -------------------------------------------------------------------------
//	�ļ���		��	Buff.h
//	��������	��	BUFF�࣬���ڴ����������BUFF�����ݡ�
// -----------------------------------------------------------------------*/

#ifndef _BUFF_H
#define _BUFF_H

#include "cocos2d.h"
#include "Buff_Common.h"

USING_NS_CC;

// Buff����ʱ�������
typedef struct __BUFF_TIME_DATA
{
	UINT									uNextRespondTime;										// ��һ�ε���Ӧʱ��
	UINT									uBuffRemoveTime;										// Buff�Ƴ�ʱ��

	BUFF_CURRENT_TIME_TYPE					eBuffTimeType;											// Buff��ǰ�Ǵ�����Чʱ�仹�Ǵ��ڼ��ʱ����
}BUFF_TIME_DATA;

class FightActor;

class Buff_Logic : public CCNode
{
public:
	Buff_Logic(void);
	~Buff_Logic(void);
	bool  InitData(FightActor * pFightActor);														// ��ʼ��BuffLogic


private:
	//---��Ա����---//
	int										m_nCurrentLogicTagID;									// ��ǰLogic��ʶID

	bool									m_bUpdataIsOpen;										// ��ʱ���Ƿ���

	UINT									m_uUpdataCurrentTime;									// ��ʱ����ǰʱ��

	FightActor*								m_pCurrentFightActor;									// ��ǰ��FightActor

	BUFF_TIME_DATA							m_strAllBuffTimeData[MAX_BUFF_COUNT_ON_PALYER];			// FightActor���е�Buffʱ������

	std::map<int, int>						m_pFightActorBuffMap;									// FightActor������Buff

	std::list<int>							m_pFreeBuffTimeDataIndexList;							// ���е�Buffʱ�������б�	

public:
	//---����߼�����---//
	void									Clear();
	void									AddBuff(const int nBuffID);								// ���Buff
	void									OnActive(float dt);										// ����Ƿ�����Ӧ�Լ��Ƴ�ʱ��

	void									RemoveTargetBuff(const int nBuffID);					// �Ƴ�Ŀ��Buff
	void									ChangeTargetBuffNextRespondTime(const int nBuffID);		// ����Ŀ��Buff����һ����Ӧʱ��

	void									JudgeCurrentFightActorHaveBuff();						// �жϵ�ǰ��FightActor�Ƿ���Buff

	void									RecordTargetBuffToMap(const int nBuffID);				// ��¼Ŀ��Buff��Map��

	bool									ReplaceNewBuffToOld(const int nOldID, const int nNewID);// �滻����Buff

	int										GetSameTypeBuffListToTargetSkill(const int nBuffID, std::list<int> * pList); // ��ȡ��Ŀ��Buff����һ����Buff�б�
public:
	//---��ȡ�����ó�Ա����---//
	inline	void							SetCurrentLogicTagID(const int nTagID)
	{
		m_nCurrentLogicTagID = nTagID;
	}

	inline	int								GetCurrentFightActorBuffCount()
	{
		return m_pFightActorBuffMap.size();
	}

};

#endif // _BUFF_H