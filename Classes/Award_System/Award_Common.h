/* -------------------------------------------------------------------------
//	�ļ���		��	Award_Common.h
//	��������	��	���ڴ��Award�Ĺ�������
// -----------------------------------------------------------------------*/

#ifndef _AWARD_COMMON_H_
#define _AWARD_COMMON_H_

#include "Network_Common/global_macros.h"
#include <string>
#include <list>

enum Exchange_Ask_Result
{
	EAR_NOT_EXIST = 0,
	EAR_BEEN_EXCHANGED = -3,
	EAR_SUCCESS = 1,
	EAR_BAG_FULL = 2,
};

#endif // _AWARD_COMMON_H_