//
//  MonsterWave.cpp
//  cocosGame
//
//  Created by ff on 14-11-24.
//
//

#include "MonsterTeam.h"

#include "cocostudio/CocoStudio.h"
#include "../ClientLogic/Utils/GameReader.h"
#include "../ClientLogic/Utils/BaseUtils.h"
#include "BattleField.h"

USING_NS_CC;
using namespace cocostudio;

std::map<int, int> MonsterTeam::idTable;

MonsterTeam::MonsterTeam():
teamId(0),
monsterId(0),
monsterCount(0),
displayPos(0),
nextTeamId(0),
teamInterval(0),
tiledMap(nullptr),
surviveCount(0),
hasSend(false)
{
    
}

MonsterTeam::~MonsterTeam()
{
    teamId = 0;
    monsterId = 0;
    monsterCount = 0;
    displayPos = 0;
    nextTeamId = 0;
    teamInterval = 0;
    tiledMap = nullptr;
    surviveCount = 0;
    
}

bool MonsterTeam::readTeam(int idx, rapidjson::Document& _doc)
{
    int index = idTable.find(idx)->second;
    
    const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(_doc, index);
    if (dic.IsNull()) {
        return false;
    }
    
    teamId = DICTOOL->getIntValue_json(dic, "ID");
    monsterId = DICTOOL->getIntValue_json(dic, "monID");
    monsterCount = DICTOOL->getIntValue_json(dic, "count");
    displayPos = DICTOOL->getIntValue_json(dic, "pos");
    nextTeamId = DICTOOL->getIntValue_json(dic, "nextTeam");
    teamInterval = DICTOOL->getFloatValue_json(dic, "interval");
    fromTmx = ((DICTOOL->getIntValue_json(dic, "fromTmx") == 1)?true:false);
    dieTeamId = DICTOOL->getIntValue_json(dic, "dieTeam");
    waveId = DICTOOL->getIntValue_json(dic, "waveId");

    std::string s = DICTOOL->getStringValue_json(dic, "BeginDialogueID");
    if (s != "null") {
        auto startVec = YNBaseUtil::splitString(s, ",");
        BeginDialogueID = atoi(startVec[0].c_str());
        beginGroupId = atoi(startVec[1].c_str());
    }else{
        BeginDialogueID = -1;
        beginGroupId = -1;
    }
    
    s = DICTOOL->getStringValue_json(dic, "EndDialogueID");
    if (s != "null") {
        auto startVec = YNBaseUtil::splitString(s, ",");
        EndDialogueID = atoi(startVec[0].c_str());
        endGroupID = atoi(startVec[1].c_str());
    }else{
        EndDialogueID = -1;
        endGroupID = -1;
    }
    
    surviveCount = monsterCount;
    return true;
}

void MonsterTeam::initIdTable(rapidjson::Document &_doc)
{
    if (_doc.IsArray()){
        int size = _doc.Size();
        int objId;
        for (int i = 0; i<size; i++) {
            objId =DICTOOL->getIntValue_json(_doc[i], "ID");
            idTable.insert(std::make_pair(objId, i));
        }
    }
}

bool MonsterTeam::readFile(int idx, std::string filename)
{
    auto doc = GameReader::getDocInstance(filename);
    if(MonsterTeam::idTable.empty())
    {
        MonsterTeam::initIdTable(*doc);
    }
    return readTeam(idx, *doc);
}

void MonsterTeam::sendMonster()
{
    mons.clear();
    
    if (fromTmx) {
        std::string path("scene/");
        auto fileName = BattleField::instance()->getTiledMapName();
        tiledMap = experimental::TMXTiledMap::create(path + fileName);
        auto groups = tiledMap->getObjectGroups();
        for (auto group : groups) {
            if(group->getGroupName() != ("wave"+Convert2String(waveId)))
            {
                continue;
            }
            auto objs = group->getObjects();
            for (auto obj : objs)
            {
                if (obj.asValueMap()["teamId"].asInt() != teamId) {
                    continue;
                }
                surviveCount++;
                mon mon1;
                mon1.monId = obj.asValueMap()["monId"].asInt();
                mon1.teamId = obj.asValueMap()["teamId"].asInt();
                mon1.posType = 4;
                mon1.fromTmx = fromTmx;
                mon1.x = obj.asValueMap()["x"].asFloat();
                mon1.y = obj.asValueMap()["y"].asFloat();
                mons.push_back(mon1);
            }
            break;
        }
    }else{
        for (int i = 0; i<monsterCount; i++)
        {
            mon mon1;
            mon1.monId = monsterId;
            mon1.teamId = teamId;
            mon1.posType = displayPos;
            mon1.fromTmx = fromTmx;
            mons.push_back(mon1);
        }
    }
    hasSend = true;
}

bool MonsterTeam::someOneDead()
{
    if (surviveCount == 0) {
        return false;
    }
    
    surviveCount--;
    if (surviveCount == 0) {
        return true;
    }
	return false;
}
