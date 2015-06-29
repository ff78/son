//
//  BlackActor.cpp
//  ssoul
//
//  Created by ff on 14-10-14.
//
//

#include "BlackActor.h"
#include "cocostudio/CocoStudio.h"
#include "ClientLogic/Utils/GameReader.h"
/****************************************** dely ***************************************/
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player.h"
/****************************************** dely ***************************************/
#include "ClientLogic/FightDefine.h"
//#include "Job_Skill_System/Job_Skill_Config_Mgr.h"
#include "TouchSkill/SkillManager.h"
#include "BlackColossus.h"

USING_NS_CC;
using namespace cocostudio;

std::map<int, int> BlackActor::idTable;

BlackActor::BlackActor()
{
    av = 0;
    ap = 0;
    selSkills.clear();
    selSkillTags.clear();
}

BlackActor::~BlackActor()
{
    selSkills.clear();
    selSkillTags.clear();
}

void BlackActor::initIdTable(rapidjson::Document &_doc){
    if (_doc.IsArray()){
        int size = _doc.Size();
        int objId;
        for (int i = 0; i<size; i++) {
            objId =DICTOOL->getIntValue_json(_doc[i], "ID");
            idTable.insert(std::make_pair(objId, i));
        }
    }
}

bool BlackActor::initData(int idx, rapidjson::Document& _doc) {
    int index = idTable.find(idx)->second;
    
    const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(_doc, index);
    if (dic.IsNull()) {
        return false;
    }
    
    
    actorId =DICTOOL->getIntValue_json(dic, "ID");
    name = DICTOOL->getStringValue_json(dic, "name");
    resName = DICTOOL->getStringValue_json(dic, "armature");
    scaleRate = DICTOOL->getFloatValue_json(dic, "scaleFactor");
    moveSpeed = DICTOOL->getIntValue_json(dic, "moveSpeed");
    rushSpeed = DICTOOL->getFloatValue_json(dic, "rushSpeed");
    maxHp = hp = DICTOOL->getFloatValue_json(dic, "hp");
    maxMp = mp = DICTOOL->getFloatValue_json(dic, "mp");
    attack = DICTOOL->getFloatValue_json(dic, "attack");
    defence = DICTOOL->getFloatValue_json(dic, "defence");
    hitRatio = DICTOOL->getFloatValue_json(dic, "hitRatio");
    dodgeRatio = DICTOOL->getFloatValue_json(dic, "dodgeRatio");
    critRatio = DICTOOL->getFloatValue_json(dic, "critRatio");
    tenacity = DICTOOL->getFloatValue_json(dic, "tenacity");
    iceResist = DICTOOL->getFloatValue_json(dic, "iceResist");
    fireResist = DICTOOL->getFloatValue_json(dic, "fireResist");
    thunderResist = DICTOOL->getFloatValue_json(dic, "thunderResist");
    windResist = DICTOOL->getFloatValue_json(dic, "windResist");
    lightResist = DICTOOL->getFloatValue_json(dic, "lightResist");
    darkResist = DICTOOL->getFloatValue_json(dic, "darkResist");
    
    level = DICTOOL->getFloatValue_json(dic, "level");
    stateMachineFile = DICTOOL->getStringValue_json(dic, "StateMachine");
    deHitDownVal = DICTOOL->getFloatValue_json(dic, "deHitDown");
    
    atk1skillId = DICTOOL->getFloatValue_json(dic, "atk1");
    atkskillId = atk1skillId;
    
    atk2skillId = DICTOOL->getIntValue_json(dic, "atk2");
    atk3skillId = DICTOOL->getFloatValue_json(dic, "atk3");
    atk4skillId = DICTOOL->getFloatValue_json(dic, "atk4");
    
    skillAId = DICTOOL->getIntValue_json(dic, "currSkill1");
    skillBId = DICTOOL->getIntValue_json(dic, "currSkill2");
    skillCId = DICTOOL->getIntValue_json(dic, "currSkill3");
    skillDId = DICTOOL->getIntValue_json(dic, "currSkill4");
    
    skillSPId = DICTOOL->getIntValue_json(dic, "SPSkill");
    runAttack1ID = DICTOOL->getIntValue_json(dic, "RunAtk1");
    runAttack2ID = DICTOOL->getIntValue_json(dic, "RunAtk2");
    runAttackID = runAttack1ID;

    de2AirRate = DICTOOL->getIntValue_json(dic, "body");
    deDownRate = DICTOOL->getIntValue_json(dic, "balance");
    immuBuffRate = DICTOOL->getIntValue_json(dic, "immuBuff");
    
    atkAThreshold = DICTOOL->getIntValue_json(dic, "atkAThreshold");
    hurtAThreshold = DICTOOL->getIntValue_json(dic, "hurtAThreshold");
    maxAV = DICTOOL->getIntValue_json(dic, "MaxAV");
    maxAp = DICTOOL->getIntValue_json(dic, "MaxAP");
    mpRecover = DICTOOL->getFloatValue_json(dic, "MpRecover");
    ghost = maxGhost = 100;
    return true;
}

void BlackActor::readFile(int idx, std::string filename)
{
    auto doc = GameReader::getDocInstance(filename);
    if(BlackActor::idTable.empty())
    {
        BlackActor::initIdTable(*doc);
    }
    initData(idx, *doc);
}

int atkIdx;
void BlackActor::initSelSkill()
{
    atkIdx = 1;
//    readRelativeSkill(atkskillId);
    equipSkills[ATK_KEY] = atk1skillId;
    equipSkills[SKILLA_KEY] = skillAId;
    equipSkills[SKILLB_KEY] = skillBId;
    equipSkills[SKILLC_KEY] = skillCId;
    equipSkills[SKILLD_KEY] = skillDId;
    equipSkills[SKILLS_KEY] = skillSPId;
    equipSkills[RUN_ATK_KEY] = runAttack1ID;
    
    readRelativeSkill(atk1skillId);
    readRelativeSkill(runAttack1ID);
    readRelativeSkill(runAttack2ID);
    readRelativeSkill(skillAId);
    readRelativeSkill(skillBId);
    readRelativeSkill(skillCId);
    readRelativeSkill(skillDId);
    readRelativeSkill(skillSPId);
}

void BlackActor::initClsSelSkill(BlackColossus *cls)
{
    auto skillMap = cls->clsSkills;
    int skillId = skillMap.begin()->second.getSkillId();
    equipSkills[SKILLA_KEY] = skillId;
    atk1skillId = 0;
    for (auto skill : skillMap) {
        int skillId = skill.second.getSkillId();
        readRelativeSkill(skillId);
    }
}

void BlackActor::readRelativeSkill(int skillId)
{
    if (skillId <= 0) {
        return;
    }
    auto tSkill = new Skill;
    tSkill->readFile(skillId, SKILL_FIGHT_FILE);
    selSkills[skillId] = tSkill;
    
    
    int linkId = tSkill->getLinkID();
    if (linkId > 0) {
        if(tSkill->getBaseSkillID() == atk1skillId)
        {
            switch (atkIdx) {
                case 1:
                    atk2skillId = linkId;
                    break;
                case 2:
                    atk3skillId = linkId;
                    break;
                case 3:
                    atk4skillId = linkId;
                    break;
                default:
                    break;
            }
            atkIdx++;
        }
        readRelativeSkill(linkId);
    }
    
    int xuliId = tSkill->getXuliId();
    if (xuliId > 0) {
        readRelativeSkill(xuliId);
    }
    
}

void BlackActor::initSelSkillTag()
{
    auto doc = GameReader::getDocInstance(SKILLTAG_FIGHT_FILE);
    if(SkillTag::idTable.empty())
    {
        SkillTag::initIdTable(*doc);
    }
    
    for (auto skill : selSkills) {
        int skillId = skill.first;
        readRelativeSkillTag(skillId);
    }
}

void BlackActor::readRelativeSkillTag(int skillId)
{
    int skillTagId = skillId * 100 + 1;
    while (SkillTag::idTable.find(skillTagId) != SkillTag::idTable.end() && skillTagId < skillId*100 +100) {
        auto skillTag = new SkillTag;
        skillTag->readFile(skillTagId, SKILLTAG_FIGHT_FILE);
        selSkillTags[skillTagId] = skillTag;
        skillTagId++;
    }
}

void BlackActor::initPlayerData()
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    Value tmpLevel(player->get_character_level());
    level = tmpLevel.asInt();
    
//    maxHp = player->get_character_max_hp();
    maxMp = player->get_character_max_mp();
//    hp = player->get_character_cur_hp();
    mp = player->get_character_cur_mp();
//    maxAp = player->get_character_max_gp();
//    ap = player->get_character_cur_gp();
    attack = player->get_character_attack();
    defence = player->get_character_define();
    
    hitRatio = player->get_character_hit_ratio();
    dodgeRatio = player->get_character_avoidance();
    critRatio = player->get_character_crit_rate();
    tenacity = player->get_character_tenacity();
    
    iceResist = player->get_Ice_Resist();
    fireResist = player->get_Fire_Resist();
    thunderResist = player->get_Thunder_Resist();
    windResist = player->get_Wind_Resist();
    lightResist = player->get_Light_Resist();
    darkResist = player->get_Dark_Resist();
    playerName = player->get_character_name();
    
    colossusId = player->get_cur_god_id();
    guardId = player->get_cur_pet_id();
//    colossusId = 100002;
//    guardId = 100001;
    
    TARGET_CHARACTER_BATTLE_SKILL_DATA skillData;
    if(!SkillManager::instance()->GetCharacterBattleSkillData(&skillData))
    {
        return;
    }
    
//    int job = player->get_job();
//    auto skillVec = player->get_select_job_skill_list();
//    for (auto skill : skillVec) {
//        Skill::readySkillFromData(job, skill);
//    }
//    runAttack1ID = skillData.nRunSkill[0];
//    runAttack2ID = skillData.nRunSkill[1];
    if(runAttack2ID == 0)
    {
        runAttack2ID = runAttack1ID;
    }
    runAttackID = runAttack1ID;
    skillAId = skillData.nSelectedSkill[0];
    skillBId = skillData.nSelectedSkill[1];
    skillCId = skillData.nSelectedSkill[2];
    skillDId = skillData.nSelectedSkill[3];
    
//    atk1skillId = skillData.nGeneralSkillID;
//    atkskillId = skillData.nGeneralSkillID;
    skillSPId = skillData.nSpSkillID;
    
    initSelSkill();
    initSelSkillTag();
}

void BlackActor::addAv()
{
    av++;
    if (av >= maxAV) {
        av = 0;
        ap++;
        ap = MIN(ap, maxAp);
    }
}