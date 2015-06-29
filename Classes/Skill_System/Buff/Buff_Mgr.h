/* -------------------------------------------------------------------------
//	文件名		：	Buff.h
//	功能描述	：	BUFF类，用于所有BUFF的数据。
// -----------------------------------------------------------------------*/
#ifndef _Buff_Manager_H_
#define _Buff_Manager_H_
#include "Buff_Common.h"

class FightActor;
class Buff_Logic;

// 处理Buff类型
enum DEAL_BUFF_TYPE
{
	DEAL_BUFF_EFFECT_ATTRIBUTE_TYPE,							  // 处理Buff的效果类型
	DEAL_BUFF_EFFECT_ATTRIBUTE_VALUE_TYPE,						  // 处理Buff的数值的类型
	DEAL_BUFF_EFFECT_ATTRIBUTE_VALUE,							  // 处理Buff的数值
	DEAL_BUFF_EFFECT_MAX
};

class Buff_Manager
{
public:
	Buff_Manager();
	~Buff_Manager();
	int  initialize();																															// 初始化BuffManager
	bool InitializeBuffData();																													// 初始化所有Buff的数据(读取配置表)
	bool InitializeBuffLogic();																													// 初始化BuffLogic

	static Buff_Manager * instance();

private:
	//---成员变量---//
	int										m_pAllBuffCount;																					 // 所有Buff的个数

	std::list<int>							m_pFreeLogicTagID;																					 // 空余的Logic标识ID列表
	std::map<FightActor * , int>			m_pFightActorMap;																					 // FightActor列表

	Buff_Logic*								m_pBuffLogicData;																					 // 单个Buff的管理类

	BUFF_DATA*								m_pAllBuffData;																						 // 所有Buff的数据

private:
	//---数据处理的相关方法---//
	int										DealWithIntervalTimeAndTotalTime(string strTemp);													// 处理配置表中关于时间的字段的数据
	int										DealWithBuffEffectData(string strTemp, const DEAL_BUFF_TYPE eType, BUFF_EFFECT_DATA * pData);		// 处理配置表中关于Buff效果的字段的数据

public:
	//---相关逻辑处理---//
	bool									FightActorAddBuff(FightActor * pFightActor , int nBuffID);											// 目标对象添加Buff

	void									RemoveTargetFightActor(FightActor * pFightActor);													// 清除目标FightActor

public:
	//--获取与设置成员变量---//
	inline  BUFF_DATA *						GetTargetBuffData(const int nTargetID)																// 获取指定ID的Buff数据
	{
		if (nTargetID < 0 || nTargetID > m_pAllBuffCount - 1)
			return NULL;

		return &m_pAllBuffData[nTargetID];
	}
	

private:
	static Buff_Manager * g_pBuffManager;
};


#endif // !_Buff_Manager_H_