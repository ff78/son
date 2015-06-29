//
//  BlackCity.cpp
//  cocosGame
//
//  Created by ff on 14-11-5.
//
//

#include "BlackCity.h"
#include "../ClientLogic/Utils/GameReader.h"
#include "Game_Interface/game_content_interface.h"
#include "Player_Account/Account_Data_Mgr.h"

USING_NS_CC;
using namespace cocostudio;

std::map<int, int> BlackCity::idTable;


void BlackCity::readFile(int idx, std::string filename)
{
    auto doc = GameReader::getDocInstance(filename);
    if(BlackCity::idTable.empty())
    {
        BlackCity::initIdTable(*doc);
    }
    initData(idx, *doc);
}

void BlackCity::initIdTable(rapidjson::Document &_doc){
    if (_doc.IsArray()){
        int size = _doc.Size();
        int objId;
        for (int i = 0; i<size; i++) {
            objId =DICTOOL->getIntValue_json(_doc[i], "ID");
            idTable.insert(std::make_pair(objId, i));
        }
    }
}

bool BlackCity::initData(int idx, rapidjson::Document& _doc) {
    int index = idTable.find(idx)->second;
    log("load index:%d>>>>%d", idx, index);
    const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(_doc, index);
    if (dic.IsNull()) {
        return false;
    }
    
    sceneId = DICTOOL->getIntValue_json(dic, "ID");
    tiledMapPath = DICTOOL->getStringValue_json(dic, "tiledMap");
    name = DICTOOL->getStringValue_json(dic, "name");
    permissionLvl = DICTOOL->getIntValue_json(dic, "permissionLevel");
    campId = DICTOOL->getIntValue_json(dic, "campID");
    bgPath = DICTOOL->getStringValue_json(dic, "bgRes");
    midPath = DICTOOL->getStringValue_json(dic, "midRes");
    frontPath = DICTOOL->getStringValue_json(dic, "frontRes");
    log("load tiled:%s", tiledMapPath.c_str());
    return true;

}

bool BlackCity::canEnter(int level, int campId)
{
    return (level >= permissionLvl && this->campId == campId);
}

void BlackCity::onCollideDoor()
{
    vector<uint64> para;
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    para.push_back( player_id );
    para.push_back(1000);
    
    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendrequireallstage", para);
}

