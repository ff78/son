/* -------------------------------------------------------------------------
//	�ļ���		��	ImpactCommon.h
//	��������	��	���ڴ��Impact�Ĺ�������
// -----------------------------------------------------------------------*/

#ifndef _IMPACT_COMMON_H
#define _IMPACT_COMMON_H

#include "Game_Interface/common.h"

#define PER_RATIO           10000  // ս������ϵ������

enum ImpactLogicID
{
	IL_BASE = -1,
	IL_IMPACT1 = 1,   // �޸�Ŀ���һ��������
	IL_IMPACT2,       // ����Ŀ����˺����Լ�����������һ������
	IL_IMPACT3,       // ����Ŀ������Զ�Ŀ���һ������Ч��
	IL_IMPACT4,       // ����Ŀ������Զ������һ������Ч��
	IL_IMPACT5,       // �Ƴ�BUFF
	IL_IMPACT6,       // ������������Զ������һ������Ч��
	IL_MAX_COUNT,
};

enum MODFITY_TYPE
{
	MT_MODFITY_TYPE1 = 1,  // ��ֵ
	MT_MODFITY_TYPE2 = 2,  // ����
	MT_MODFITY_TYPE3 = 3,  // ����
};


#endif // _IMPACT_COMMON_H