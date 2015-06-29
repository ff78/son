#ifndef __H_SHIELD_MANAGER_H__
#define __H_SHIELD_MANAGER_H__
#include <string>
#include <vector>
#include "cocos2d.h"
#include "json/json_header.h"
USING_NS_CC;
using namespace std;
class ShieldManager
{
public:
	static ShieldManager* instance_;
	set<string> data;
public:
	ShieldManager();
	~ShieldManager();
	static ShieldManager* sharedShieldManager();
	void init();
	bool isNameContainShield(const string& name);
	string transferChatMessage(const string& message);
};
#endif //__H_SHIELD_MANAGER_H__
