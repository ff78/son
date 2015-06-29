/* -------------------------------------------------------------------------
//	�ļ���		��	Pubilc_Annoucement_Common.h
//	��������	��	���ڴ��Public_Annoucement�Ĺ�������
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
		uint64 id;		// ���������Ψһ��ʶ
		int	effect;		// 0:δ��Ч��1����Ч
		std::string title;	//����ı���
		std::string content;//���������
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