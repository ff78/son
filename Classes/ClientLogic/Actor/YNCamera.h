#pragma once

#include "cocos2d.h"

class YNCamera : public cocos2d::Node
{
public:

    static YNCamera *getInstance();
    
    bool init();
    
	CREATE_FUNC(YNCamera);

	void setCameraCenter(cocos2d::Point pos);
    
    float vShake();
    
    static bool bShake;
    static int shakeDuration;
    static float shakeRange;
    static int flashCount;
    
//    void scheduleShake();
    
    void stopShake();
    
    bool isOutWindow(cocos2d::Point p);
    
private:
    static YNCamera *inc;

};