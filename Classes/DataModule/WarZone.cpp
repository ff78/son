//
//  WarZone.cpp
//  cocosGame
//
//  Created by ff on 14-11-25.
//
//

#include "WarZone.h"
#include "../ClientLogic/Utils/GameReader.h"

USING_NS_CC;
using namespace cocostudio;

std::map<int, WarZone> WarZone::zoneMap;
std::vector<int> WarZone::zoneIdVec;

void WarZone::readFile(std::string filename)
{
    auto doc = GameReader::getDocInstance(filename);
    if (doc->IsArray()){
        int size = doc->Size();
        
        for (int i = 0; i<size; i++) {
            const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
            WarZone zone;
            zone.zoneId = DICTOOL->getIntValue_json(dic, "ID");
            zone.zoneName = DICTOOL->getStringValue_json(dic, "name");
            zone.fieldCount = DICTOOL->getIntValue_json(dic, "fieldCount");
            zone.hasOpen = (DICTOOL->getIntValue_json(dic, "hasOpen") == 0?false:true);
            zone.nextZone = DICTOOL->getIntValue_json(dic, "nextZone");
            
            zoneMap[zone.zoneId] = zone;
            zoneIdVec.push_back(zone.zoneId);
        }
    }
}

//std::map<int, int> WarZone::idTable;

//void WarZone::initIdTable(rapidjson::Document &_doc){
//    if (_doc.IsArray()){
//        int size = _doc.Size();
//        int objId;
//        for (int i = 0; i<size; i++) {
//            objId =DICTOOL->getIntValue_json(_doc[i], "ID");
//            idTable.insert(std::make_pair(objId, i));
//        }
//    }
//}
//
//bool WarZone::initData(int idx, rapidjson::Document& _doc) {
//    int index = idTable.find(idx)->second;
//    
//    const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(_doc, index);
//    if (dic.IsNull()) {
//        return false;
//    }
//    
//    zoneId = DICTOOL->getIntValue_json(dic, "ID");
//    zoneName = DICTOOL->getStringValue_json(dic, "name");
//    fieldCount = DICTOOL->getIntValue_json(dic, "fieldCount");
//    hasOpen = (DICTOOL->getIntValue_json(dic, "hasOpen") == 0?false:true);
//    nextZone = DICTOOL->getIntValue_json(dic, "nextZone");
//
//    return true;
//    
//}
//
//void WarZone::readZoneFromFile(int zoneIdx, std::string filename)
//{
//    auto doc = GameReader::getDocInstance(filename);
//    if(WarZone::idTable.empty())
//    {
//        WarZone::initIdTable(*doc);
//    }
//    initData(zoneIdx, *doc);
//
//}
