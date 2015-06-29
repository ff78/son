//
//  BaseUtils.h
//  ssoul
//
//  Created by ff on 14-9-23.
//
//

#ifndef __ssoul__BaseUtils__
#define __ssoul__BaseUtils__

#include "cocos2d.h"

template <class T>
std::string Convert2String(T value) {
    std::stringstream ss;
    ss<<value;
    return ss.str();
}

class YNBaseUtil {
    
public:
    static std::vector<std::string> splitString(std::string str, std::string pattern);
	static std::string randomNameBySexId(int sex);//sex == 0 为女性名 1为男性名称
    
    static cocos2d::Size WinSize;
};

#endif /* defined(__ssoul__BaseUtils__) */
