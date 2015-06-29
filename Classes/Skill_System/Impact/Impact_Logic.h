/* -------------------------------------------------------------------------
//	文件名		：	ImpactLogic.h
//	功能描述	：	所有的效果逻辑类
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

// 修改目标的一二级属性
class ImpactLogic1 : public ImpactLogic_T
{
public:
	enum
	{
		ID = IL_IMPACT1,
	};
	enum
	{
		PARAM1 = 3, // 作用索引
		PARAM2 = 4, // 作用类型
		PARAM3 = 5, // 概率
		PARAM4 = 6, // 作用值
	};
	ImpactLogic1()  {}
	~ImpactLogic1() {}
public:            
	virtual void     OnActive(Buff_Logic* buffPtr, uint32 index) const;
	virtual void     GetIntPropertyRefix(Buff_Logic* buffPtr, uint32 propertyIndex, uint32 impactIndex, uint32 type, sint32 &valueOut) const;
};

// 对目标的一次伤害
class ImpactLogic2 : public ImpactLogic_T
{
public:
	enum
	{
		ID = IL_IMPACT2,
	}; 
	enum
	{
		PARAM1 = 3, // 作用索引
		PARAM2 = 4, // 作用类型
		PARAM3 = 5, // 比例
		PARAM4 = 6, // 上限
	};
	ImpactLogic2()  {}
	~ImpactLogic2() {}
public:             
	virtual void     OnActive(Buff_Logic* buffPtr, uint32 index) const;
};

// 按照目标的属性对目标的一次作用效果
class ImpactLogic3 : public ImpactLogic_T
{
public:
	enum
	{
		ID = IL_IMPACT3,
	};
	enum
	{
		PARAM1 = 3, // 作用索引
		PARAM2 = 4, // 作用类型
		PARAM3 = 5, // 属性索引
		PARAM4 = 6, // 作用值
	};
	ImpactLogic3()  {}
	~ImpactLogic3() {}
public:             
	virtual void     OnActive(Buff_Logic* buffPtr, uint32 index) const;
};

// 4.	按照目标的属性对自身的一次作用效果
class ImpactLogic4 : public ImpactLogic_T
{
public:
	enum
	{
		ID = IL_IMPACT4,
	};
	enum
	{
		PARAM1 = 3, // 作用索引
		PARAM3 = 4, // 作用类型
		PARAM2 = 5, // 属性索引
		PARAM4 = 6, // 作用值
	};
	ImpactLogic4()  {}
	~ImpactLogic4() {}
public:     
	virtual void     OnActive(Buff_Logic* buffPtr, uint32 index) const;
};

// 5.	移除BUFF
class ImpactLogic5 : public ImpactLogic_T
{
public:
	enum
	{
		ID = IL_IMPACT5,
	};
	enum
	{
		PARAM1 = 3, // BUFF正负面类型
		PARAM3 = 4, // 移除BUFF个数
	};
	ImpactLogic5()  {}
	~ImpactLogic5() {}
public:           
	virtual void     OnActive(Buff_Logic* buffPtr, uint32 index) const;
};

// 按照自身的属性对自身的一次作用效果
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
