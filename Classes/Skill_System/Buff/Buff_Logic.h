/* -------------------------------------------------------------------------
//	文件名		：	Buff.h
//	功能描述	：	BUFF类，用于处理玩家身上BUFF的数据。
// -----------------------------------------------------------------------*/

#ifndef _BUFF_H
#define _BUFF_H

#include "cocos2d.h"
#include "Buff_Common.h"

USING_NS_CC;

// Buff关于时间的数据
typedef struct __BUFF_TIME_DATA
{
	UINT									uNextRespondTime;										// 下一次的响应时间
	UINT									uBuffRemoveTime;										// Buff移除时间

	BUFF_CURRENT_TIME_TYPE					eBuffTimeType;											// Buff当前是处于有效时间还是处于间隔时间内
}BUFF_TIME_DATA;

class FightActor;

class Buff_Logic : public CCNode
{
public:
	Buff_Logic(void);
	~Buff_Logic(void);
	bool  InitData(FightActor * pFightActor);														// 初始化BuffLogic


private:
	//---成员变量---//
	int										m_nCurrentLogicTagID;									// 当前Logic标识ID

	bool									m_bUpdataIsOpen;										// 定时器是否开启

	UINT									m_uUpdataCurrentTime;									// 定时器当前时间

	FightActor*								m_pCurrentFightActor;									// 当前的FightActor

	BUFF_TIME_DATA							m_strAllBuffTimeData[MAX_BUFF_COUNT_ON_PALYER];			// FightActor所有的Buff时间数据

	std::map<int, int>						m_pFightActorBuffMap;									// FightActor的所有Buff

	std::list<int>							m_pFreeBuffTimeDataIndexList;							// 空闲的Buff时间数据列表	

public:
	//---相关逻辑处理---//
	void									Clear();
	void									AddBuff(const int nBuffID);								// 添加Buff
	void									OnActive(float dt);										// 检查是否到了响应以及移除时间

	void									RemoveTargetBuff(const int nBuffID);					// 移除目标Buff
	void									ChangeTargetBuffNextRespondTime(const int nBuffID);		// 更换目标Buff的下一次响应时间

	void									JudgeCurrentFightActorHaveBuff();						// 判断当前的FightActor是否有Buff

	void									RecordTargetBuffToMap(const int nBuffID);				// 记录目标Buff到Map中

	bool									ReplaceNewBuffToOld(const int nOldID, const int nNewID);// 替换两个Buff

	int										GetSameTypeBuffListToTargetSkill(const int nBuffID, std::list<int> * pList); // 获取与目标Buff类型一样的Buff列表
public:
	//---获取与设置成员变量---//
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