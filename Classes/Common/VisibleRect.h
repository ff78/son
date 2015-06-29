#ifndef __VISIBLERECT_H__
#define __VISIBLERECT_H__
#pragma warning(disable:4251) 
#include "cocos2d.h"
USING_NS_CC;

class VisibleRect
{
public:
    static CCRect getVisibleRect();

    static Point left();
    static Point right();
    static Point top();
    static Point bottom();
    static Point center();
    static Point leftTop();
    static Point rightTop();
    static Point leftBottom();
    static Point rightBottom();
	static float  cutLength();
private:
    static void lazyInit();
    static CCRect s_visibleRect;
};

#endif /* __VISIBLERECT_H__ */
