#include "SendResultEvent.h"

const char* SendResultEvent::_TYPE = "SendResultEvent";

SendResultEvent::SendResultEvent(bool bWin)
:cocos2d::EventCustom(_TYPE),
m_bWin(bWin)
{

}