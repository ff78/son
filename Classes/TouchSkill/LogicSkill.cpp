//
//  LogicSkill.cpp
//  son
//
//  Created by ff on 15-4-25.
//
//
#include "SkillDefine.h"
#include "LogicSkill.h"

using namespace cocostudio;

std::map<int, int> LogicSkill::idTable;

LogicSkill::LogicSkill()
{
}

LogicSkill::~LogicSkill()
{
    nextSkill = nullptr;
}
bool LogicSkill::initWithId(int skillId)
{
    auto doc = GameReader::getDocInstance(SKILL_DATA_FILE);
    if(LogicSkill::idTable.empty())
    {
        LogicSkill::initIdTable(*doc);
    }
    return readData(skillId, *doc);
}

void LogicSkill::initIdTable(rapidjson::Document &doc)
{
    if (doc.IsArray()){
        int size = doc.Size();
        int objId;
        for (int i = 0; i<size; i++) {
            objId =DICTOOL->getIntValue_json(doc[i], "skillid");
            idTable.insert(std::make_pair(objId, i));
        }
    }
}

bool LogicSkill::readData(int skillId, rapidjson::Document &doc)
{
    int index = idTable.find(skillId)->second;
    
    const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(doc, index);
    if (dic.IsNull()) {
        return false;
    }

    this->skillId = skillId;
    name = DICTOOL->getStringValue_json(dic, "name");
    attackRate = DICTOOL->getIntValue_json(dic, "attack");
    level = DICTOOL->getIntValue_json(dic, "curr_lv");
    upgradeMoney = DICTOOL->getIntValue_json(dic, "lv_up_money");
    upgradeId = DICTOOL->getIntValue_json(dic, "lv_up_skill_id");
    requierPlayerLevel = DICTOOL->getIntValue_json(dic, "player_lv");
    desc = DICTOOL->getStringValue_json(dic, "Skill_Describe");
    icon = DICTOOL->getStringValue_json(dic, "icon");
    pressKeys = DICTOOL->getStringValue_json(dic, "pressKey");
	type = DICTOOL->getIntValue_json(dic, "Skill_Type");
	action = DICTOOL->getStringValue_json(dic, "action_name");
    frontEff = DICTOOL->getStringValue_json(dic, "frontEffect");
    frontScale = DICTOOL->getStringValue_json(dic, "frontScale");
    backScale = DICTOOL->getStringValue_json(dic, "backScale");
    backEff = DICTOOL->getStringValue_json(dic, "backEffect");
//    backEff2 = DICTOOL->getStringValue_json(dic, "backEffect2");
//    backEff3 = DICTOOL->getStringValue_json(dic, "backEffect3");
    if (upgradeId == 0) {
        nextSkill = nullptr;
    }else{
		nextSkill = new LogicSkill();
        readNextSkill(upgradeId, doc);
    }
    return true;
}

bool LogicSkill::readNextSkill(int nextSkillId, rapidjson::Document &doc)
{
    int index = idTable.find(nextSkillId)->second;
    
    const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(doc, index);
    if (dic.IsNull()) {
        return false;
    }
    nextSkill->name = DICTOOL->getStringValue_json(dic, "name");
    nextSkill->level = DICTOOL->getIntValue_json(dic, "curr_lv");
    nextSkill->desc = DICTOOL->getStringValue_json(dic, "Skill_Describe");
    return true;
}

LogicSkill* LogicSkill::getNextSkill()
{
    return nextSkill;
}