/* -------------------------------------------------------------------------
//	文件名		：	Banks_Common.h
//	功能描述	：	用于存放Banks的公共数据
// -----------------------------------------------------------------------*/

#ifndef _BANKS_COMMON_H_
#define _BANKS_COMMON_H_

#include "Network_Common/global_macros.h"
#include <string>
#include <list>

#define MAX_BANKS_EXCHANGE_TIMES 20
#define MAX_EXCHANGE_TOKEN_NUMS 50
#define EXCHANGE_TOKEN_UNIT_NUMS 2

enum BANKS_EXCHANGE_RESULT
{
	BER_SUCCEED,
	BER_FAILED,
	BER_NOT_ENOUGH_TOKEN,
	BER_HAVE_NO_CHANCE,
};



#endif // _BANKS_COMMON_H_