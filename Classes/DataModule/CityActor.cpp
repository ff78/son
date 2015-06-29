//
//  CityActor.cpp
//  cocosGame
//
//  Created by ff on 14-11-7.
//
//

#include "CityActor.h"
#include "cocostudio/CocoStudio.h"
#include "../ClientLogic/Utils/GameReader.h"

USING_NS_CC;
using namespace cocostudio;

std::map<int, int> CityActor::idTable;

CityActor::CityActor()
{
    
}

CityActor::~CityActor()
{
    
}
void CityActor::initIdTable(rapidjson::Document &_doc){
    if (_doc.IsArray()){
        int size = _doc.Size();
        int objId;
        for (int i = 0; i<size; i++) {
            objId =DICTOOL->getIntValue_json(_doc[i], "static_character_id");
            idTable.insert(std::make_pair(objId, i));
        }
    }
}

bool CityActor::initData(int idx, rapidjson::Document& _doc) {
    int index = idTable.find(idx)->second;
    
    const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(_doc, index);
    if (dic.IsNull()) {
        return false;
    }
    
    
    actorId =DICTOOL->getIntValue_json(dic, "static_character_id");
    iconId = DICTOOL->getIntValue_json(dic, "face_mode_id");
    appearCondition = DICTOOL->getIntValue_json(dic, "appear_condition");
    npcType = DICTOOL->getIntValue_json(dic, "npc_type");
    dialogId = DICTOOL->getIntValue_json(dic, "dialog_id");
    triggerRule = DICTOOL->getIntValue_json(dic, "trigger_rule");
    waitAction = DICTOOL->getIntValue_json(dic, "wait_action");
    shopId1 = DICTOOL->getIntValue_json(dic, "shop_id1");
    shopId2 = DICTOOL->getIntValue_json(dic, "shop_id2");
    shopId3 = DICTOOL->getIntValue_json(dic, "shop_id3");
    
    name = DICTOOL->getStringValue_json(dic, "name");
    resName = DICTOOL->getStringValue_json(dic, "armature");
    scaleRate = DICTOOL->getFloatValue_json(dic, "scaleFactor");
    stateMachineFile = DICTOOL->getStringValue_json(dic, "StateMachine");
    return true;
}

void CityActor::readFile(int idx, std::string filename)
{
    auto doc = GameReader::getDocInstance(filename);
    if(CityActor::idTable.empty())
    {
        CityActor::initIdTable(*doc);
    }
    initData(idx, *doc);
}
