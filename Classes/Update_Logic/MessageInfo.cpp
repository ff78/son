#include "MessageInfo.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#else
MessageInfo::MessageInfo()
{
	what=0;
	obj=0;
}
#endif