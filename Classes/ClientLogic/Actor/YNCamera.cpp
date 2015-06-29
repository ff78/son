#include "YNCamera.h"
#include "../FightDefine.h"
USING_NS_CC;

bool YNCamera::bShake = false;
int YNCamera::shakeDuration = 0;
float YNCamera::shakeRange = 0;
int YNCamera::flashCount = 0;
YNCamera *YNCamera::inc;

bool YNCamera::init()
{
    if (!Node::init()) {
        return false;
    }
    inc = this;
    
    return true;
}

YNCamera *YNCamera::getInstance()
{
    return inc;
}

void YNCamera::setCameraCenter(cocos2d::Point pos)
{
	float posX = pos.x;
	posX = MIN(MAP_AREA_RIGHT, posX);
	posX = MAX(MAP_AREA_LEFT, posX);

	setPosition(Point(posX, pos.y));
}

float YNCamera::vShake()
{
    if (shakeDuration >= 6) {
        stopShake();
        return 0;
    }
    shakeDuration++;
    if(shakeDuration%2 == 1)
    {
        return shakeRange;
    } else {
        shakeRange /= 2;
        return 0;
    }
}

void YNCamera::stopShake()
{
    bShake = false;
    shakeDuration = -1;
}

bool YNCamera::isOutWindow(Point p)
{
    if(p.x == MAP_AREA_RIGHT){
        log("catch it");
        return true;
    }
    if (p.x == MAP_AREA_LEFT) {
        return true;
    }
    auto winSize = Director::getInstance()->getWinSize();
    if (getPositionX() <= MAP_AREA_LEFT + winSize.width/2) {
        if (p.x<getPositionX()) {
            return p.x <= MAP_AREA_LEFT;
        } else {
            return p.x > winSize.width;
        }
    } else if (getPositionX() >= MAP_AREA_RIGHT - winSize.width/2) {
        if (p.x > getPositionX()) {
            return p.x >= MAP_AREA_RIGHT;
        } else {
            return p.x < MAP_AREA_WIDTH - winSize.width;
        }
    } else {
        return abs(p.x-getPositionX()) > winSize.width/2;
    }
}

//void YNCamera::scheduleShake()
//{
//    if (shakeDuration > 0 || !bShake) {
//        return;
//    }
//}
