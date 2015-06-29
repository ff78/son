/* -------------------------------------------------------------------------
//	文件名		：	General.h
//	功能描述	：	通用的逻辑管理器
// -----------------------------------------------------------------------*/

#pragma once

#include "../Impact/Impact_Logic.h"
#include "LogicManagerCommon.h"
#include <assert.h>

template <typename T, uint32 nSize>
class LogicManager_T
{
public:
	LogicManager_T();
	~LogicManager_T();
	bool Init();
	T const* GetLogicById(uint32 const nId);
	void RegisterLogic(uint32 nID, T* pLogic);
private:
	bool m_bReady;
	T* m_apLogics[nSize];
};

template <typename T, uint32 nSize>
LogicManager_T<T, nSize>::LogicManager_T()
{
	memset((void*)m_apLogics, 0, sizeof(m_apLogics));
	m_bReady = Init();				
};

template <typename T, uint32 nSize>
inline bool LogicManager_T<T, nSize>::Init()
{
	return false;
};

template <typename T, uint32 nSize>
inline LogicManager_T<T, nSize>::~LogicManager_T()
{
	m_bReady = false;
	for(uint32 i=0;nSize>i;++i)
	{
		if(NULL != m_apLogics[i])
		{
			delete m_apLogics[i];
			m_apLogics[i] = NULL;
		}
	};		
};

template<typename T, uint32 nSize>
inline T const* LogicManager_T<T, nSize>::GetLogicById(uint32 const nId)
{
	if(/*0<=nId &&*/ nSize>nId && true==m_bReady)
	{
		return m_apLogics[nId];
	}
	return NULL;
}

template<typename T, uint32 nSize>
inline void LogicManager_T<T, nSize>::RegisterLogic(uint32 nID, T* pLogic)
{
	assert(m_apLogics[nID]==NULL);
	m_apLogics[nID]=pLogic;
}
#define REGISTER_LOGIC(LOGIC) {RegisterLogic(LOGIC::ID, (new (LOGIC)));}


template<>
inline bool LogicManager_T<ImpactLogic_T, IL_MAX_COUNT>::Init()
{

	REGISTER_LOGIC(ImpactLogic1);
	REGISTER_LOGIC(ImpactLogic2);
	REGISTER_LOGIC(ImpactLogic3);
	REGISTER_LOGIC(ImpactLogic4);
	REGISTER_LOGIC(ImpactLogic5);
	REGISTER_LOGIC(ImpactLogic6);

	m_bReady = true;
	return true;
};


typedef class LogicManager_T<ImpactLogic_T, IL_MAX_COUNT> ImpactLogicManager_T;
extern ImpactLogicManager_T g_ImpactLogicList;

