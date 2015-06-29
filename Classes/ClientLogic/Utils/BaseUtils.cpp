//
//  BaseUtils.cpp
//  ssoul
//
//  Created by ff on 14-9-23.
//
//

#include "BaseUtils.h"

#include "../../Random_System/Name_Random_Mgr.h"
cocos2d::Size YNBaseUtil::WinSize;

std::vector<std::string> YNBaseUtil::splitString(std::string str, std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;
    std::string::size_type size = str.size();
    
    for (std::string::size_type i = 0; i < size; i++) {
        pos = str.find(pattern, i);
        if (pos < size) {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}

std::string YNBaseUtil::randomNameBySexId(int sex)
{
	std::string retName;
	int family_name_id;
	const char* name_front;
	//cocos2d::ui::TextField* pEditBox;
	char name_f[32] = { 0 };
	int family_name_called_id = 0;
	char name_r[64] = { 0 };
	const char* name_rear;
	std::string family_name_called;
	std::string family_name;
	CCLOG(" random role name ");
	srand((unsigned)time(NULL));
	family_name_id = rand() % 264 + 1;
	CCLOG("family_name_id = %d", family_name_id);
	name_front = Name_Random_Mgr::get_instance()->get_name_by_id(family_name_id);

	memcpy(name_f, name_front, strlen(name_front) - 1);
	family_name = name_f;


	if (0 == sex) //随机女性名称
		family_name_called_id = rand() % (1808 - 1500) + 1501;
	if (1 == sex) //随机男性名称
		family_name_called_id = rand() % (956 - 500) + 501;

	CCLOG("family_name_called_id = %d", family_name_called_id);
	name_rear = Name_Random_Mgr::get_instance()->get_name_by_id(family_name_called_id);

	memcpy(name_r, name_rear, strlen(name_rear) - 1);
	family_name_called = name_r;

	retName = family_name + family_name_called;
	CCLOG("name = %s", retName.c_str());
	return retName;
}
