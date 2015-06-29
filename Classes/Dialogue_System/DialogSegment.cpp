//
//  DialogSegment.cpp
//  son
//
//  Created by ff on 15-6-1.
//
//

#include "DialogSegment.h"
#include "ClientLogic/Utils/GameReader.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player.h"
#include "ClientLogic/Utils/BaseUtils.h"

std::map<int, int> DialogSegment::idTable;

using namespace cocostudio;

bool DialogSegment::loadSegment(std::string fileName, int idx)
{
    auto doc = GameReader::getDocInstance(fileName + "_seg.json");
    
    if (DialogSegment::idTable.empty()) {
        DialogSegment::initIdTable(*doc);
    }
    
    if(!initData(idx, *doc))
    {
        return false;
    }
    
    lineVec.clear();
    segOver = false;
    for (int i = 0; i < lineCount; i++) {
        auto line = new DialogLine();
        line->loadLine(fileName, startLineId+i);
        lineVec.push_back(line);
    }
    currLine = lineVec[0];
    currLineIndex = 0;
    if (lineCount == 1) {
        segOver = true;
    }
    return true;
}

void DialogSegment::initIdTable(rapidjson::Document &_doc){
    if (_doc.IsArray()){
        int size = _doc.Size();
        int objId;
        for (int i = 0; i < size; i++) {
            objId = DICTOOL->getIntValue_json(_doc[i], "segId");
            idTable.insert(std::make_pair(objId, i));
        }
    }
}

bool DialogSegment::initData(int idx, rapidjson::Document& _doc)
{
    int index = idTable.find(idx)->second;
    
    const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(_doc, index);
    if (dic.IsNull()) {
        return false;
    }
    
    segId = DICTOOL->getIntValue_json(dic, "segId");
    startLineId = DICTOOL->getIntValue_json(dic, "startLine");
    lineCount = DICTOOL->getIntValue_json(dic, "lineCount");
//    dialogType = DICTOOL->getIntValue_json(dic, "dialogType");
    dir = atoi(DICTOOL->getStringValue_json(dic, "direct"));
    
    faceIcon = DICTOOL->getStringValue_json(dic, "face");
    faceName = DICTOOL->getStringValue_json(dic, "dialogName");
    if (faceName == "#") {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        
        faceName = player->get_character_name();
    }
    if (faceIcon == "#") {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        
        faceIcon = "job_" + Convert2String(player->get_job()-1);
    }
    return true;
}

void DialogSegment::clearIdTable()
{
    idTable.clear();
    
}

void DialogSegment::nextPage()
{
    if (segOver) {
        return;
    }
    
    currLineIndex++;
    currLine = lineVec[currLineIndex];
    if (currLineIndex >= lineCount-1) {
        segOver = true;
    }
}

DialogLine *DialogSegment::getCurrLine()
{
    return currLine;
}
