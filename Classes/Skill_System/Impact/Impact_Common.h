/* -------------------------------------------------------------------------
//	文件名		：	ImpactCommon.h
//	功能描述	：	用于存放Impact的公共数据
// -----------------------------------------------------------------------*/

#ifndef _IMPACT_COMMON_H
#define _IMPACT_COMMON_H

#include "Game_Interface/common.h"

#define PER_RATIO           10000  // 战斗属性系数调节

enum ImpactLogicID
{
	IL_BASE = -1,
	IL_IMPACT1 = 1,   // 修改目标的一二级属性
	IL_IMPACT2,       // 按照目标的伤害对自己的生命进行一次作用
	IL_IMPACT3,       // 按照目标的属性对目标的一次作用效果
	IL_IMPACT4,       // 按照目标的属性对自身的一次作用效果
	IL_IMPACT5,       // 移除BUFF
	IL_IMPACT6,       // 按照自身的属性对自身的一次作用效果
	IL_MAX_COUNT,
};

enum MODFITY_TYPE
{
	MT_MODFITY_TYPE1 = 1,  // 数值
	MT_MODFITY_TYPE2 = 2,  // 比例
	MT_MODFITY_TYPE3 = 3,  // 覆盖
};


#endif // _IMPACT_COMMON_H