
#ifndef _PARTITION_COMMON_H_
#define _PARTITION_COMMON_H_

#include "Network_Common/global_macros.h"
#include <string>
#include <list>

namespace Game_Data
{
	typedef struct Partition_Common_Data
	{
		std::string title;
		std::string content;
		void reset()
		{
			title.clear();              
			content.clear();	
		}
	} PartitionData ;

	typedef std::list<PartitionData>    PartitionData_List;
	typedef PartitionData_List::iterator PartitionData_Iter;
}

#endif // _PARTITION_COMMON_H_