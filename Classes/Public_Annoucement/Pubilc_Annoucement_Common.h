/* -------------------------------------------------------------------------
//	文件名		：	Pubilc_Annoucement_Common.h
//	功能描述	：	用于存放Public_Annoucement的公共数据
// -----------------------------------------------------------------------*/

#ifndef _PUBILC_ANNOUCEMENT_COMMON_H_
#define _PUBILC_ANNOUCEMENT_COMMON_H_

#include "Network_Common/global_macros.h"
#include <string>
#include <map>

namespace Game_Data
{
	typedef struct Pubic_Annoucement_Date
	{
		uint64 id;		// 该条公告的唯一标识
		int	effect;		// 0:未生效，1：生效
		std::string title;	//公告的标题
		std::string content;//公告的内容
		void reset()
		{
			id = 0;
			effect = 1;
			title.clear();              
			content.clear();	
		}
	} PAD ;

	typedef std::map<uint64, PAD*>   PAD_Map;
	typedef PAD_Map::iterator PAD_Iter;
}

#endif // _PUBILC_ANNOUCEMENT_COMMON_H_