/* -------------------------------------------------------------------------
//	�ļ���		��	ImpactLogic.h
//	��������	��	���е�Ч���߼���
// -----------------------------------------------------------------------*/

#pragma once

#include "Impact_Common.h"

class Buff_Logic;

class ImpactLogic_T
{
public:
	enum
	{
		ID = IL_BASE,
	};
	ImpactLogic_T()  {}
	~ImpactLogic_T() {}
public:            
	virtual void     OnActive(Buff_Logic* buffPtr, uint32 index) const;
	virtual void     GetIntPropertyRefix(Buff_Logic* buffPtr, uint32 propertyIndex, uint32 impactIndex, uint32 type, sint32 &valueOut) const;
	void  GetValueByModifyType(Buff_Logic* buffPtr, uint32 modifyType, sint32 &valueOut, uint32 index =0) const;
};

ImpactLogic_T const* Impact_GetLogic(uint32 impactId);

// �޸�Ŀ���һ��������
class ImpactLogic1 : public ImpactLogic_T
{
public:
	enum
	{
		ID = IL_IMPACT1,
	};
	enum
	{
		PARAM1 = 3, // ��������
		PARAM2 = 4, // ��������
		PARAM3 = 5, // ����
		PARAM4 = 6, // ����ֵ
	};
	ImpactLogic1()  {}
	~ImpactLogic1() {}
public:            
	virtual void     OnActive(Buff_Logic* buffPtr, uint32 index) const;
	virtual void     GetIntPropertyRefix(Buff_Logic* buffPtr, uint32 propertyIndex, uint32 impactIndex, uint32 type, sint32 &valueOut) const;
};

// ��Ŀ���һ���˺�
class ImpactLogic2 : public ImpactLogic_T
{
public:
	enum
	{
		ID = IL_IMPACT2,
	}; 
	enum
	{
		PARAM1 = 3, // ��������
		PARAM2 = 4, // ��������
		PARAM3 = 5, // ����
		PARAM4 = 6, // ����
	};
	ImpactLogic2()  {}
	~ImpactLogic2() {}
public:             
	virtual void     OnActive(Buff_Logic* buffPtr, uint32 index) const;
};

// ����Ŀ������Զ�Ŀ���һ������Ч��
class ImpactLogic3 : public ImpactLogic_T
{
public:
	enum
	{
		ID = IL_IMPACT3,
	};
	enum
	{
		PARAM1 = 3, // ��������
		PARAM2 = 4, // ��������
		PARAM3 = 5, // ��������
		PARAM4 = 6, // ����ֵ
	};
	ImpactLogic3()  {}
	~ImpactLogic3() {}
public:             
	virtual void     OnActive(Buff_Logic* buffPtr, uint32 index) const;
};

// 4.	����Ŀ������Զ������һ������Ч��
class ImpactLogic4 : public ImpactLogic_T
{
public:
	enum
	{
		ID = IL_IMPACT4,
	};
	enum
	{
		PARAM1 = 3, // ��������
		PARAM3 = 4, // ��������
		PARAM2 = 5, // ��������
		PARAM4 = 6, // ����ֵ
	};
	ImpactLogic4()  {}
	~ImpactLogic4() {}
public:     
	virtual void     OnActive(Buff_Logic* buffPtr, uint32 index) const;
};

// 5.	�Ƴ�BUFF
class ImpactLogic5 : public ImpactLogic_T
{
public:
	enum
	{
		ID = IL_IMPACT5,
	};
	enum
	{
		PARAM1 = 3, // BUFF����������
		PARAM3 = 4, // �Ƴ�BUFF����
	};
	ImpactLogic5()  {}
	~ImpactLogic5() {}
public:           
	virtual void     OnActive(Buff_Logic* buffPtr, uint32 index) const;
};

// ������������Զ������һ������Ч��
class ImpactLogic6 : public ImpactLogic_T
{
public:
	enum
	{
		ID = IL_IMPACT6,
	};
	ImpactLogic6()  {}
	~ImpactLogic6() {}
public:           
	virtual void     OnActive(Buff_Logic* buffPtr, uint32 index) const;
};
