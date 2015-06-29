//
//  SkillManager.h
//  son
//
//  Created by ff on 15-4-25.
//
//

#ifndef __son__SkillManager__
#define __son__SkillManager__

#include "cocos2d.h"
#include "SkillDefine.h"
#include "LogicSkill.h"
#include "ClientLogic/Utils/GameUtil.h"

class SkillManager : public Singleton<SkillManager>
{
public:
    SkillManager();
    ~SkillManager();
    
    bool canUpgrade(int skillId);
    int upgradeSkill(int skillId);
    void upgradeSkillResult(int originSkillId, int newSkillId);
    bool swapSelSkill(int posA, int posB);
    bool changeSkill(int posA, int skillId);
    
    std::vector<LogicSkill> getAllSkills();
    std::vector<LogicSkill> getSelSkills();
    LogicSkill getSPSkill();
    
    void readShowSkillFromFile(int skillId);
    void readSelSkillFromFile(int skillId);
    
    void postChanges2Server();
    bool GetCharacterBattleSkillData(TARGET_CHARACTER_BATTLE_SKILL_DATA * pData);
//    void reqInitData(); not used, server notified skillData, when you first enter city.
private:
    
    LogicSkill SPSkill;
    std::map<int, LogicSkill> allSkills;
    std::map<int, LogicSkill> selSkills;
    CC_SYNTHESIZE(bool, waitForPack, WaitForPack);
    std::vector<LogicSkill> showSkills;
    std::vector<LogicSkill> showSelSkills;
};

#endif /* defined(__son__SkillManager__) */
