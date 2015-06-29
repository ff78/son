//
//  BattleField.cpp
//  cocosGame
//
//  Created by ff on 14-11-24.
//
//

#include "BattleField.h"
#include "../ClientLogic/Utils/GameReader.h"
#include "../ClientLogic/Utils/BaseUtils.h"
#include "Play_System/Formula_Function_Instance_Client.h"
#include "Player_Account/Account_Data_Mgr.h"

/***************** dely ******************/
#include "../Events/SendResultEvent.h"
/***************** dely ******************/
USING_NS_CC;
using namespace cocostudio;

std::map<int, int> BattleField::idTable;

BattleField::BattleField():
sceneId(0),secondLimit(0),
waveSheetId(0),waveCount(0),
tiledMapName(""),currSecondLeft(0),
currWaveId(0),currWaveCount(0),gameFail(false),
startDialogId(-1),startGroupId(-1),
winDialogId(-1), winGroupId(-1),
loseDialogId(-1), loseGroupId(-1)
{
	m_bFightResult		= false;
	m_bCanSendResult	= false;
}

BattleField::~BattleField()
{
    sceneId = 0;
    secondLimit = 0;
    waveSheetId= 0;
    waveCount = 0;
    tiledMapName = "";
    currSecondLeft = 0;
    currWaveId = 0;
    currWaveCount = 0;
    gameFail = false;
}
void BattleField::initIdTable(rapidjson::Document &_doc)
{
    if (_doc.IsArray()){
        int size = _doc.Size();
        int objId;
        for (int i = 0; i<size; i++) {
            objId =DICTOOL->getIntValue_json(_doc[i], "instance_id");
            idTable.insert(std::make_pair(objId, i));
        }
    }
}

bool BattleField::readBattle(int idx, rapidjson::Document& _doc)
{
    int index = idTable.find(idx)->second;
    log("battle :%d>>>%d", idx, index);
    
    const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(_doc, index);
    if (dic.IsNull()) {
        return false;
    }
    
    sceneId = DICTOOL->getIntValue_json(dic, "instance_id");
    tiledMapName = DICTOOL->getStringValue_json(dic, "tiledMap");
    waveSheetId = DICTOOL->getIntValue_json(dic, "waveSheetID");
    waveCount = DICTOOL->getIntValue_json(dic, "waveCount");
    secondLimit = DICTOOL->getIntValue_json(dic, "secondLimit");
    bgImgName = DICTOOL->getStringValue_json(dic, "backImg");
    midImgName = DICTOOL->getStringValue_json(dic, "midImg");
    frontImgName = DICTOOL->getStringValue_json(dic, "frontImg");
	/************************** dely *****************************/
	condition = DICTOOL->getIntValue_json(dic, "condition");
	_hp = DICTOOL->getIntValue_json(dic, "hp");
	_time = DICTOOL->getIntValue_json(dic, "time");
	_count = DICTOOL->getIntValue_json(dic, "count");
	/************************** dely *****************************/
    
    log("battle dialog");
    std::string s = DICTOOL->getStringValue_json(dic, "startDialog");
    if (s != "null") {
        auto startVec = YNBaseUtil::splitString(s, ";");
        startDialogId = atoi(startVec[0].c_str());
        startGroupId = atoi(startVec[1].c_str());
    }else{
        startDialogId = -1;
        startGroupId = -1;
    }
    
    log("battle win dialog");
    s = DICTOOL->getStringValue_json(dic, "winDialog");
    if (s != "null") {
        auto winVec = YNBaseUtil::splitString(s, ";");
        winDialogId = atoi(winVec[0].c_str());
        winGroupId = atoi(winVec[1].c_str());
    }else{
        winDialogId = -1;
        winGroupId = -1;
    }
    
    log("battle lose dialog");
    s = DICTOOL->getStringValue_json(dic, "loseDialog");
    if (s != "null") {
        auto loseVec = YNBaseUtil::splitString(s, ";");
        loseDialogId = atoi(loseVec[0].c_str());
        loseGroupId = atoi(loseVec[1].c_str());
    }else{
        loseDialogId = -1;
        loseGroupId = -1;
    }
    
    gameFail = false;
    waveOver = false;
    
    log("battle finish");
//    std::string tiledDir("scene/");
//    tiledMap = experimental::TMXTiledMap::create(tiledDir + tiledMapName);
    return true;
}

void BattleField::readFile(std::string filename)
{
    auto doc = GameReader::getDocInstance(filename);
    if(BattleField::idTable.empty())
    {
        BattleField::initIdTable(*doc);
    }
    readBattle(sceneId, *doc);
}

bool BattleField::start1stWave()
{
    currWaveId = waveSheetId;
    currWaveCount = 1;
    
    if (currWaveId<=0) {
        return false;
    }
    
    if(!readCurrWave())
    {
        return false;
    }
    
    return currMonsterWave->startWave();
}

bool BattleField::readCurrWave()
{
    if (currWaveId <= 0) {
        return false;
    }
    currMonsterWave = MonsterWave::instance();
    return currMonsterWave->readFile(currWaveId, "GameData/scene_wave.json");
    
}

bool BattleField::change2NextWave()
{
    if (currWaveCount == waveCount) {
        //win
        waveOver=true;
//		NotifyServerResult(true);
//		SendResultEvent evt(true);
//		Director::getInstance()->getEventDispatcher()->dispatchEvent(&evt);
//		Director::getInstance()->getActionManager()->pauseAllRunningActions();

        return false;
    }
    currWaveCount++;
    int nextWaveId = currMonsterWave->getNextWaveId();
    if (nextWaveId == 0) {
        //win
        waveOver = true;
//		NotifyServerResult(true);
//		SendResultEvent evt(true);
//		Director::getInstance()->getEventDispatcher()->dispatchEvent(&evt);
//		Director::getInstance()->getActionManager()->pauseAllRunningActions();

        return false;
    }
    
    currWaveId = nextWaveId;
    if(!readCurrWave())
    {
        return false;
    }
    
    return currMonsterWave->startWave();
}

void BattleField::notifyServerTime()
{
//    Formula_Function_Instance_Client::instance()->notifyServerTime();
}

void BattleField::waitPacket()
{
    Formula_Function_Instance_Client::instance()->waitPacket();
}

void BattleField::NotifyServerResult(const bool bValue /*= false*/)
{
//	m_bFightResult = bValue;
	m_bCanSendResult = true;

//	if (!m_bFightResult)
    SendServerFightResult();
	
}

void BattleField::SendServerFightResult()
{
	if (m_bFightResult)
	{
		Formula_Function_Instance_Client::instance()->notifyServerWin();
	}
	else
	{
		gameFail = true;
		Formula_Function_Instance_Client::instance()->notifyServerLose();
	}

	m_bCanSendResult = false;
}



//void BattleField::onClickNext()
//{
//    Formula_Function_Instance_Client::instance()->requireSelStage();
//}
//
//bool BattleField::onReceiveNext(const Game_Logic::Game_Event& gm_evt)
//{
//    EventCustom event("popSelStage");
//    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
//    return true;
//}
//
