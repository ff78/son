#ifndef __PROFILE_H__
#define __PROFILE_H__

#define PROFILE_KEY_USER_NAME "username"
#define PROFILE_KEY_PASSWORD "password"
#define PROFILE_KEY_REMEMBER_PWD "rememberpwd"

#include <string>

class Profile
{

public:
    static bool    getBoolForKey(const char* pKey);
    static bool    getBoolForKey(const char* pKey, bool defaultValue);

    static int     getIntegerForKey(const char* pKey);
    static int     getIntegerForKey(const char* pKey, int defaultValue);

    static float    getFloatForKey(const char* pKey);
    static float    getFloatForKey(const char* pKey, float defaultValue);

    static double  getDoubleForKey(const char* pKey);
    static double  getDoubleForKey(const char* pKey, double defaultValue);

    static std::string getStringForKey(const char* pKey);
    static std::string getStringForKey(const char* pKey, const std::string & defaultValue);

    static void    setBoolForKey(const char* pKey, bool value);
    static void    setIntegerForKey(const char* pKey, int value);
    static void    setFloatForKey(const char* pKey, float value);
    static void    setDoubleForKey(const char* pKey, double value);
    static void    setStringForKey(const char* pKey, const std::string & value);

    static void    flush();

};
#endif // !defined(__PROFILE_H__)
