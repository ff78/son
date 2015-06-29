#include "Profile.h"
#include "cocos2d.h"

USING_NS_CC;


 bool Profile::getBoolForKey(const char* pKey)
 {
     return UserDefault::getInstance()->getBoolForKey(pKey, false);
 }

bool Profile::getBoolForKey(const char* pKey, bool defaultValue)
{
	return UserDefault::getInstance()->getBoolForKey(pKey,defaultValue);
}

int Profile::getIntegerForKey(const char* pKey)
{
    return UserDefault::getInstance()->getIntegerForKey(pKey, 0);
}

int Profile::getIntegerForKey(const char* pKey, int defaultValue)
{
	return UserDefault::getInstance()->getIntegerForKey(pKey, defaultValue);
}

float Profile::getFloatForKey(const char* pKey)
{
    return UserDefault::getInstance()->getFloatForKey(pKey, 0.0f);
}

float Profile::getFloatForKey(const char* pKey, float defaultValue)
{
    return UserDefault::getInstance()->getFloatForKey(pKey, defaultValue);
}

double  Profile::getDoubleForKey(const char* pKey)
{
    return  UserDefault::getInstance()->getDoubleForKey(pKey, 0.0);
}

double Profile::getDoubleForKey(const char* pKey, double defaultValue)
{
	return  UserDefault::getInstance()->getDoubleForKey(pKey, defaultValue);
}

std::string Profile::getStringForKey(const char* pKey)
{
    return  UserDefault::getInstance()->getStringForKey(pKey, "");
}

std::string Profile::getStringForKey(const char* pKey, const std::string & defaultValue)
{
	return  UserDefault::getInstance()->getStringForKey(pKey, defaultValue);
}

void Profile::setBoolForKey(const char* pKey, bool value)
{
	UserDefault::getInstance()->setBoolForKey(pKey, value);
}

void Profile::setIntegerForKey(const char* pKey, int value)
{
	UserDefault::getInstance()->setIntegerForKey(pKey, value);
}

void Profile::setFloatForKey(const char* pKey, float value)
{
    UserDefault::getInstance()->setFloatForKey(pKey, value);
}

void Profile::setDoubleForKey(const char* pKey, double value)
{
    UserDefault::getInstance()->setDoubleForKey(pKey, value);
}

void Profile::setStringForKey(const char* pKey, const std::string & value)
{
	UserDefault::getInstance()->setStringForKey(pKey,value);
}
void Profile::flush()
{
	UserDefault::getInstance()->flush();
}