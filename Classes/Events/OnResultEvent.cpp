#include "OnResultEvent.h"

const char* OnResultEvent::_TYPE = "OnResultEvent";

OnResultEvent::OnResultEvent(bool bWin)
:cocos2d::EventCustom(_TYPE),
m_bWin(bWin)
{

}