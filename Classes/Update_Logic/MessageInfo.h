#ifndef __MESSAGEINFO_H__
#define __MESSAGEINFO_H__
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#else
#include <string>
using namespace std;
class MessageInfo
{
public:
	enum MsgType
	{
		START_MESSION,
		DELETE_SOMETHING,
		CREATE_FILE_FAILED,
		UNCOMPRESS_FAILED,
		NET_WORK_ERROR,
		START_GETMESSAGE,
		STARTDOWNLOAD,
		DOWNLOAD_PROGRESS,
		DOWNLOAD_SUCCEED,
		UNCOMPRESS_SUCCEED,
		ONE_SUCCEED,
		ALL_SUCCEED,
	};
	unsigned int what;
	unsigned int arg1;
	unsigned int arg2;
	unsigned int arg3;
	string filename;
	string md5;
	string respath;
	void* obj;
	MessageInfo();
};
#endif // CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#endif //__MESSAGEINFO_H__