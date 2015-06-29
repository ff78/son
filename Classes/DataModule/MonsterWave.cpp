//
//  MonsterWave.cpp
//  cocosGame
//
//  Created by ff on 14-11-30.
//
//

#include "MonsterWave.h"
#include "cocostudio/CocoStudio.h"
#include "../ClientLogic/Utils/GameReader.h"
//#include "../Dialogue_System/Dialogue_Common.h"
//#include "../Dialogue_System/DialogueManager.h"

USING_NS_CC;
using namespace cocostudio;

std::map<int, int> MonsterWave::idTable;

MonsterWave::MonsterWave():
waveId(0),
surviveCount(0),
nextWaveId(0),
startTeamId(0),
teamCount(0),
tiledMap(nullptr),
sendTeamOver(true)
{
	m_pDialogueIDList.clear();
}

MonsterWave::~MonsterWave()
{
    waveId = 0;
    surviveCount = 0;
    nextWaveId = 0;
    startTeamId = 0;
    teamCount = 0;
    tiledMap = nullptr;
    teams.clear();
	m_pDialogueIDList.clear();
}

MonsterTeam *MonsterWave::getTeam(int teamId)
{
    if(teams.find(teamId) == teams.end())
    {
        return nullptr;
    }
    
    return teams[teamId];
}

bool MonsterWave::sendTeam(int teamId)
{
    if (!sendTeamOver) {
        return false;
    }
    
    auto monTeam = new MonsterTeam();
    if(!monTeam->readFile(teamId, "GameData/scene_team.json"))
    {
        return false;
    }
    teams[monTeam->getTeamId()] = monTeam;

//	int nDialogueID = monTeam->getBeginDialogueID();
//	if (DialogueManager::instance()->JudgeTargetDialogueIDIslegal(nDialogueID))
//	{
//		m_pDialogueIDList.push_back(monTeam->getBeginDialogueID());
//	}
	
    monTeam->sendMonster();
    auto waitSend = monTeam->getMons();
    for (auto waitMon : waitSend)
    {
        waitSendMons.push_back(waitMon);
    }
    

    if (monTeam->getNextTeamId() != 0) {
        if (monTeam->getTeamInterval() == 0) {
            sendTeam(monTeam->getNextTeamId());
        }else{
            EventCustom event("delayNextTeam");
            event.setUserData(monTeam);
            Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
            sendTeamOver = false;
        }
    }
    return true;
}
void MonsterWave::sendWaitOver()
{
    sendTeamOver = true;
    waitSendMons.clear();
}

bool MonsterWave::isAllTeamOut()
{
    return false;
}

bool MonsterWave::isWaveOver()
{
    return true;
}

bool MonsterWave::someOneDead(int teamIdx)
{
    auto team = teams[teamIdx];
    if(team->someOneDead())
    {
        teamCount--;
		if (teamCount == 0)
		{
//			int nDialogueID = team->getEndDialogueID();
//			if (DialogueManager::instance()->JudgeTargetDialogueIDIslegal(nDialogueID))
//			{
//				m_pDialogueIDList.push_back(team->getEndDialogueID());
//			}
			return true;
		}
        if (team->getDieTeamId() == 0) 
		{
            return false;
        }
        
        EventCustom event("arrangeDieTeam");
        event.setUserData(team);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }
    
    return false;
}

bool MonsterWave::readWave(int idx, rapidjson::Document& _doc)
{
    int index = idTable.find(idx)->second;
    
    const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(_doc, index);
    if (dic.IsNull()) {
        return false;
    }
    
    waveId = DICTOOL->getIntValue_json(dic, "ID");
    nextWaveId = DICTOOL->getIntValue_json(dic, "nextWaveId");
    startTeamId = DICTOOL->getIntValue_json(dic, "startTeamId");
    teamCount = DICTOOL->getIntValue_json(dic, "teamCount");
    
    return true;
}

void MonsterWave::initIdTable(rapidjson::Document &_doc)
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

bool MonsterWave::readFile(int idx, std::string filename)
{
    auto doc = GameReader::getDocInstance(filename);
    if(MonsterWave::idTable.empty())
    {
        MonsterWave::initIdTable(*doc);
    }
    return readWave(idx, *doc);
}

bool MonsterWave::startWave()
{
    teams.clear();
    return sendTeam(startTeamId);
}