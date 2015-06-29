#include "YNActions.h"

Actions* Actions::getInstance()
{
	static Actions _instance;
	return &_instance;
}

ScaleTo* Actions::getActionScaleSmall()
{
	auto scale = ScaleTo::create(0.5, 0.2);
	return scale;
}

ScaleTo* Actions::getActionScaleBig()
{
	auto scale = ScaleTo::create(0.5, 1);
	return scale;
}

DelayTime* Actions::getActionDelay()
{
	auto delay = DelayTime::create(0.5);
	return delay;
}

