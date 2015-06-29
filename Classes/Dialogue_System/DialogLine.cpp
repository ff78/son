//
//  DialogLine.cpp
//  son
//
//  Created by ff on 15-6-1.
//
//

#include "DialogLine.h"
#include "ClientLogic/Utils/GameReader.h"

std::map<int, int> DialogLine::idTable;

using namespace cocostudio;

void DialogLine::initIdTable(rapidjson::Document &_doc){
    if (_doc.IsArray()){
        int size = _doc.Size();
        int objId;
        for (int i = 0; i < size; i++) {
            objId = DICTOOL->getIntValue_json(_doc[i], "lineId");
            idTable.insert(std::make_pair(objId, i));
        }
    }
}

bool DialogLine::initData(int idx, rapidjson::Document& _doc)
{
    int index = idTable.find(idx)->second;
    
    const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(_doc, index);
    if (dic.IsNull()) {
        return false;
    }
    
    lineId = DICTOOL->getIntValue_json(dic, "lineId");
    content = DICTOOL->getStringValue_json(dic, "content");
    return true;
}

bool DialogLine::loadLine(std::string fileName, int idx)
{
    auto doc = GameReader::getDocInstance(fileName + "_line.json");
    
    if (DialogLine::idTable.empty()) {
        DialogLine::initIdTable(*doc);
    }
    
    if(!initData(idx, *doc))
    {
        return false;
    }
    
    return true;
}

void DialogLine::clearIdTable()
{
    idTable.clear();
}
