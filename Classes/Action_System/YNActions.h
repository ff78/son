#ifndef _YNACTIONS_H_
#define _YNACTIONS_H_

#include "cocos2d.h"
USING_NS_CC;

class Actions
{
public:
	static Actions* getInstance();

	ScaleTo* getActionScaleSmall();
	ScaleTo* getActionScaleBig();

	DelayTime* getActionDelay();

private:

};


#endif

