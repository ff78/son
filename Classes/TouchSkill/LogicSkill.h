//
//  LogicSkill.h
//  son
//
//  Created by ff on 15-4-25.
//
//

#ifndef __son__LogicSkill__
#define __son__LogicSkill__

#include "cocos2d.h"
#include "ClientLogic/Utils/GameReader.h"

class LogicSkill
{
public:
    LogicSkill();
    ~LogicSkill();
    
    bool initWithId(int skillId);
    void initIdTable(rapidjson::Document &doc);
    bool readData(int skillId, rapidjson::Document &doc);
    bool readNextSkill(int nextSkillId, rapidjson::Document &doc);
    LogicSkill *getNextSkill();
private:
    static std::map<int, int> idTable;
    CC_SYNTHESIZE_READONLY(int, skillId, Id);
    CC_SYNTHESIZE_READONLY(std::string, name, Name);
    CC_SYNTHESIZE_READONLY(std::string, desc, Descript);
    CC_SYNTHESIZE_READONLY(std::string, icon, Icon);
    CC_SYNTHESIZE_READONLY(std::string, pressKeys, PressKeys);
    CC_SYNTHESIZE_READONLY(float, attackRate, AttackRate);
    CC_SYNTHESIZE_READONLY(int, level, Level);
    CC_SYNTHESIZE_READONLY(int, upgradeMoney, UpgradeMoney);
    CC_SYNTHESIZE_READONLY(int, upgradeId, UpgradeId);
    CC_SYNTHESIZE_READONLY(int, requierPlayerLevel, ReqPlayerLv);
	CC_SYNTHESIZE_READONLY(int, type, Type);
	CC_SYNTHESIZE_READONLY(std::string,action,Action);
    CC_SYNTHESIZE_READONLY(std::string, frontEff, FrontEff);
    CC_SYNTHESIZE_READONLY(std::string, backEff, BackEff);
    CC_SYNTHESIZE_READONLY(std::string, backScale, BackScale);
    CC_SYNTHESIZE_READONLY(std::string, frontScale, FrontScale);

    LogicSkill *nextSkill;
};

#endif /* defined(__son__LogicSkill__) */
