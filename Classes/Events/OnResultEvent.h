#ifndef _ON_RESULT_H__
#define _ON_RESULT_H__

#include "cocos2d.h"

class OnResultEvent:public cocos2d::EventCustom
{
private:
	bool m_bWin = false;
public:
	static const char* _TYPE;

	OnResultEvent(bool bWin);

};
#endif //_EVENT_DATA_H__