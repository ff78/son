//
//  SkillManager.cpp
//  son
//
//  Created by ff on 15-4-25.
//
//

#include "SkillManager.h"


#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "SkillMsgProc.h"

SkillManager::SkillManager()
{
    waitForPack = false;
//    SPSkill = nullptr;
    allSkills.clear();
    selSkills.clear();
    showSkills.clear();
    showSelSkills.clear();
}

SkillManager::~SkillManager()
{
    waitForPack = false;
//    SPSkill = nullptr;
    allSkills.clear();
    selSkills.clear();
    showSkills.clear();
    showSelSkills.clear();
}

void SkillManager::readSelSkillFromFile(int skillId)
{
    if (selSkills.find(skillId) != selSkills.end())
    {
        return;
    }
    
    if (allSkills.find(skillId) == allSkills.end()) {
        return;
    }
    
    LogicSkill skill = allSkills[skillId];
//    if (skill.getType() == TARGET_SKILL_TYPE_SP) {
//        SPSkill = &skill;
//    }else {
    selSkills[skillId] = skill;
    showSelSkills.push_back(skill);
//    }
    
}

void SkillManager::readShowSkillFromFile(int skillId)
{
    if (allSkills.find(skillId) != allSkills.end())
    {
        return;
    }
    
    LogicSkill skill;
    if(skill.initWithId(skillId))
    {
        if (skill.getType() == TARGET_SKILL_TYPE_SP) {
            SPSkill = skill;
        }
        allSkills[skillId] = skill;
        showSkills.push_back(skill);
    }
}

bool SkillManager::canUpgrade(int skillId)
{
    if (allSkills[skillId].getUpgradeId() <= 0)
    {
        return false;
    }
    
    int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* pPlayer = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(nPlayerID));
    if (pPlayer == NULL)
    {
        return false;
    }
    
    int nPlayerGold = pPlayer->get_gold();
    if (nPlayerGold < allSkills[skillId].getUpgradeMoney())
    {
        return false;
    }
    
    LogicSkill skill;
    if (!skill.initWithId(skillId)) {
        return false;
    }
    
    if (pPlayer->get_character_level() < skill.getReqPlayerLv()) {
        return false;
    }

    return true;
}

int SkillManager::upgradeSkill(int skillId)
{
    if (allSkills[skillId].getUpgradeId() <= 0)
    {
        return SKILL_UPGRADE_MAX_LEVEL;
    }
    
    int nPlayerID = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* pPlayer = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(nPlayerID));
    if (pPlayer == NULL)
    {
        return SKILL_UPGRADE_OTHER_ERROR;
    }
    
    int nPlayerGold = pPlayer->get_gold();
    if (nPlayerGold < allSkills[skillId].getUpgradeMoney())
    {
        return SKILL_UPGRADE_MONEY_NOTENOUGH;
    }
    
    LogicSkill skill;
    if (!skill.initWithId(allSkills[skillId].getUpgradeId())) {
        return SKILL_UPGRADE_NEXT_SKILL_ERROR;
    }
    
    if (pPlayer->get_character_level() < skill.getReqPlayerLv()) {
        return SKILL_UPGRADE_REQUIRE_PLAYER_LV;
    }

    SkillMsgProc::send_uplevel_skill(skillId);
    return SKILL_UPGRADE_WAIT_RESPONSE;
}

void SkillManager::upgradeSkillResult(int originSkillId, int newSkillId)
{
    
    EventCustom event(SKILL_UPGRADE_DONE);
    LogicSkill skill;
    if (!skill.initWithId(newSkillId)) {
        event.setUserData(nullptr);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
        return;
    }
    if (originSkillId == SPSkill.getId()) {
        if (skill.getType() != TARGET_SKILL_TYPE_SP) {
            event.setUserData(nullptr);
            Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
            return;
        }
        
        SPSkill = skill;
    }
    
    //replace origin skill with new skill in allSkills map
    if (allSkills.find(originSkillId) != allSkills.end()) {
        //find origin skill pos in showSkills vector, replace it with new skill
        auto itr = showSkills.begin();
        for (; itr != showSkills.end(); itr++) {
            if(itr->getId() == originSkillId)
            {
                break;
            }
        }
        if (itr != showSkills.end()) {
            itr = showSkills.erase(itr);
            showSkills.insert(itr, skill);
        }
        allSkills.erase(allSkills.find(originSkillId));
    }
    allSkills[skill.getId()] = skill;
    
    //replace origin skill with new skill in selSkills map
    if (selSkills.find(originSkillId) != selSkills.end()) {
        //find origin skill pos in showSelSkills vector, replace it with new skill
        auto itr = showSkills.begin();
        for (; itr != showSkills.end(); itr++) {
            if(itr->getId() == originSkillId)
            {
                break;
            }
        }
        if (itr != showSelSkills.end()) {
            itr = showSelSkills.erase(itr);
            showSelSkills.insert(itr, skill);
        }
        selSkills.erase(allSkills.find(originSkillId));
        selSkills[newSkillId] = skill;
    }
    
    event.setUserData(&skill);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

bool SkillManager::swapSelSkill(int posA, int posB)
{
    if (posA == posB) {
        return false;
    }
    
    if (posA < 0 || posB < 0 || posA >= showSelSkills.size() || posB >= showSelSkills.size()) {
        return false;
    }
    
    swap(showSelSkills[posA], showSelSkills[posB]);
    return true;
}

bool SkillManager::changeSkill(int posA, int skillId)
{
    if (posA < 0 || posA >= showSelSkills.size()) {
        return false;
    }
    
    if (allSkills.find(skillId) == allSkills.end()) {
        return false;
    }
    
    if (allSkills.find(skillId)->second.getType() != TARGET_SKILL_TYPE_SELECT) {
        return false;
    }
    
    showSelSkills[posA] = allSkills.find(skillId)->second;
    return true;
}

void SkillManager::postChanges2Server()
{
    SkillMsgProc::send_select_changes(showSelSkills);
}

std::vector<LogicSkill> SkillManager::getAllSkills()
{
    return showSkills;
}

std::vector<LogicSkill> SkillManager::getSelSkills()
{
    return showSelSkills;
}

LogicSkill SkillManager::getSPSkill()
{
    return SPSkill;
}

bool SkillManager::GetCharacterBattleSkillData(TARGET_CHARACTER_BATTLE_SKILL_DATA * pData)
{
    for (auto skill : allSkills) {
        switch (skill.second.getType()) {
            case TARGET_SKILL_TYPE_GENERAL:
                pData->nGeneralSkillID = skill.second.getId();
                break;
            case TARGET_SKILL_TYPE_SP:
                pData->nSpSkillID = skill.second.getId();
                break;
            case TARGET_SKILL_TYPE_RUN_1:
                pData->nRunSkill[0] = skill.second.getId();
                break;
            case TARGET_SKILL_TYPE_RUN_2:
                pData->nRunSkill[1] = skill.second.getId();
                break;
            default:
                break;
        }
    }
    
    for (int i = 0; i<MAX_SELECT_SKILL_COUNT;i++) {
        if (i >= showSelSkills.size()) {
            pData->nSelectedSkill[i] = 0;
            continue;
        }
        pData->nSelectedSkill[i] = showSelSkills[i].getId();
    }
    return true;
}