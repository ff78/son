//
//  DialogGroup.cpp
//  son
//
//  Created by ff on 15-6-1.
//
//

#include "DialogGroup.h"
#include "ClientLogic/Utils/GameReader.h"

std::map<int, int> DialogGroup::idTable;

using namespace cocostudio;

bool DialogGroup::loadGroup(std::string fileName, int idx)
{
    auto doc = GameReader::getDocInstance(fileName + "_group.json");
    
    if (DialogGroup::idTable.empty()) {
        DialogGroup::initIdTable(*doc);
    }
    
    if(!initData(idx, *doc))
    {
        return false;
    }
    
    segVec.clear();
    for (int i = 0; i < segCount; i++) {
        auto seg = new DialogSegment();
        if(!seg->loadSegment(fileName, startSegId+i))
        {
            return false;
        }
        
        segVec.push_back(seg);
    }
    
    currSeg = segVec[0];
    return true;
}

void DialogGroup::initIdTable(rapidjson::Document &_doc){
    if (_doc.IsArray()){
        int size = _doc.Size();
        int objId;
        for (int i = 0; i < size; i++) {
            objId = DICTOOL->getIntValue_json(_doc[i], "dialogId");
            idTable.insert(std::make_pair(objId, i));
        }
    }
}

bool DialogGroup::initData(int idx, rapidjson::Document& _doc)
{
    int index = idTable.find(idx)->second;
    
    const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(_doc, index);
    if (dic.IsNull()) {
        return false;
    }
    
    groupId = DICTOOL->getIntValue_json(dic, "dialogId");
    startSegId = DICTOOL->getIntValue_json(dic, "startSeg");
    segCount = DICTOOL->getIntValue_json(dic, "segCount");
    return true;
}

void DialogGroup::clearIdTable()
{
    idTable.clear();
    DialogSegment::clearIdTable();
    DialogLine::clearIdTable();
}

bool DialogGroup::nextPage()
{
    if (currSeg->getSegOver()) {
        return false;
    }
    currSeg->nextPage();
    
    return true;
}

DialogSegment* DialogGroup::getCurrSeg()
{
    return currSeg;
}