#ifndef _SEND_RESULT_H__
#define _SEND_RESULT_H__

#include "cocos2d.h"

class SendResultEvent:public cocos2d::EventCustom
{
private:
public:
	bool m_bWin = false;

	static const char* _TYPE;

	SendResultEvent(bool bWin);

};
#endif //_EVENT_DATA_H__