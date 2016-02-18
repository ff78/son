//
//  SkillMsgProc.cpp
//  son
//
//  Created by ff on 15-4-25.
//
//

#include "SkillMsgProc.h"
#include "Network_Common/NetManager.h"
#include "Network_Common/message.h"
#include "Network_Common/message_stream.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "SkillManager.h"
#include "SkillDefine.h"
#include "ClientLogic/Utils/GameReader.h"

#define PLAYER_SKILL_FILE "player_skill.json"
#define DEFAULT_SKILL_FILE "GameData/skill_default.json"

using namespace cocostudio;

bool SkillMsgProc::on_load_skill(Game_Logic::Game_Interface &gm_interface)
{
    SkillManager::instance()->setWaitForPack(true);
//    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
//    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (player == NULL)
        return false;
    
    if (player->get_job_skill_size() > 0)
        return false;
    
    int nSkillID			= 0;
    int nSkillCount			= 0;
    int nCharacterID		= 0;
    
    int nSelectSkillID		= 0;
    int nSelectSkillCount	= 0;
    
//    std::string path(FileUtils::getInstance()->getWritablePath());
//    path += "/";
//    path += PLAYER_SKILL_FILE;
//    remove(path.c_str());
    cocos2d::Value key(player_id);
    rapidjson::Value dic;
    rapidjson::Document doc;
    if(!GameReader::isExistInFile(PLAYER_SKILL_FILE, key, doc, dic, "roleId"))
    {
        auto defaultDoc = GameReader::getDocInstance(DEFAULT_SKILL_FILE);
        rapidjson::Document::AllocatorType& allocator= defaultDoc->GetAllocator();
        rapidjson::Value value;
        value.SetObject();
        value.AddMember("roleId", player_id, allocator);
        
        for (int i = 0; i<defaultDoc->Size(); i++) {
            const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*defaultDoc), i);
            if (dic.IsNull()) {
                return false;
            }
            if (DICTOOL->getIntValue_json(dic, "job") == player->get_job()) {
                rapidjson::Value defaultSkill;
                defaultSkill.SetArray();
                const rapidjson::Value &defaultRoot = DICTOOL->getSubDictionary_json(dic, "default_skill");
                nSkillCount = defaultRoot.Size();
                for (int j = 0; j<nSkillCount; j++) {
                    nSkillID = DICTOOL->getIntValue_json(defaultRoot[j], "skillid");
                    rapidjson::Value item;
                    item.SetObject();
                    item.AddMember("skillid", nSkillID, allocator);
                    defaultSkill.PushBack(item, allocator);
                    SkillManager::instance()->readShowSkillFromFile(nSkillID);
                }
                value.AddMember("default_skill", defaultSkill, allocator);
                
                rapidjson::Value selSkill;
                selSkill.SetArray();
                const rapidjson::Value &selectRoot = DICTOOL->getSubDictionary_json(dic, "select_skill");
                nSelectSkillCount = selectRoot.Size();
                for (int j = 0; j<nSelectSkillCount; j++) {
                    nSelectSkillID = DICTOOL->getIntValue_json(selectRoot[j], "skillid");
                    rapidjson::Value item;
                    item.SetObject();
                    item.AddMember("skillid", nSelectSkillID, allocator);
                    selSkill.PushBack(item, allocator);
                    SkillManager::instance()->readSelSkillFromFile(nSelectSkillID);
                }
                value.AddMember("select_skill", selSkill, allocator);
                break;
            }
        }
        
        cocos2d::Value key(player_id);
        
        GameReader::savePlayerSkill(PLAYER_SKILL_FILE, value, key, "roleId");
    }else{
        const rapidjson::Value &defaultRoot = DICTOOL->getSubDictionary_json(dic, "default_skill");
        nSkillCount = defaultRoot.Size();
        for (int j = 0; j<nSkillCount; j++) {
            nSkillID = DICTOOL->getIntValue_json(defaultRoot[j], "skillid");
            SkillManager::instance()->readShowSkillFromFile(nSkillID);
        }
        
        const rapidjson::Value &selectRoot = DICTOOL->getSubDictionary_json(dic, "select_skill");
        nSelectSkillCount = selectRoot.Size();
        for (int j = 0; j<nSelectSkillCount; j++) {
            nSelectSkillID = DICTOOL->getIntValue_json(selectRoot[j], "skillid");
            SkillManager::instance()->readSelSkillFromFile(nSelectSkillID);
        }
    }
    
//    body_ms >> nSkillCount;
//    
//    for (int i = 0; i < nSkillCount; ++i)
//    {
//        body_ms >> nCharacterID;
//        body_ms >> nSkillID;
//        
//        SkillManager::instance()->readShowSkillFromFile(nSkillID);
//    }
//    
//    body_ms >> nSelectSkillCount;
//    
//    for (int i = 0; i < nSelectSkillCount; ++i)
//    {
//        body_ms >> nCharacterID;
//        body_ms >> nSelectSkillID;
//        
//        SkillManager::instance()->readSelSkillFromFile(nSelectSkillID);
//    }

    SkillManager::instance()->setWaitForPack(false);
    return true;
}

bool SkillMsgProc::on_uplevel_skill(Game_Logic::Game_Interface& gm_interface)
{
//    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
//    body_ms.set_rd_ptr(sizeof(int));
    
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* pPlayer = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (pPlayer == NULL)
        return false;
    
    int skill_id		= 0;
    int skill_up_id		= 0;
    int character_id	= 0;
    vector<uint64> param = gm_interface.get_para();
    skill_id = (int)param[0];
    skill_up_id = (int)param[1];
    
//    body_ms >> skill_id;
//    body_ms >> skill_up_id;
//    body_ms >> character_id;
    cocos2d::Value key(player_id);
    rapidjson::Value dic;
    
//    if (GameReader::isExistInFile(PLAYER_SKILL_FILE, key, dic, "roleId")) {
//        int size = dic["default_skill"].Size();
//        for (int i = 0; i<size; i++) {
//            int skillId = DICTOOL->getIntValue_json(dic["default_skill"][i], "skillid");
//            if (skillId == skill_id) {
//                dic["default_skill"][i]["skillid"] = skill_up_id;
//                break;
//            }
//        }
//        
//        size = dic["select_skill"].Size();
//        for (int i = 0; i<size; i++) {
//            int skillId = DICTOOL->getIntValue_json(dic["select_skill"][i], "skillid");
//            if (skillId == skill_id) {
//                dic["select_skill"][i]["skillid"] = skill_up_id;
//                break;
//            }
//        }
//        
//        GameReader::savePlayerSkill(PLAYER_SKILL_FILE, dic, key, "roleId");
//    }
    
    SkillManager::instance()->upgradeSkillResult(skill_id, skill_up_id);
    
    return true;
}

bool SkillMsgProc::send_select_changes(std::vector<LogicSkill> &selSkill, std::vector<LogicSkill> &showSkill)
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    
    
//    char msg_buf[1024] = { 0 };
//    message_stream body_ms(msg_buf, sizeof(msg_buf));
//    body_ms << CS_CHANGE_SELECT_SKILL;
//    body_ms << player_id;
//    
//    for (int nIndex = 0; nIndex < MAX_SELECT_SKILL_COUNT; ++nIndex)
//    {
//        if (nIndex >= selSkill.size()) {
//            body_ms << 0;
//            continue;
//        }
//        body_ms << selSkill[nIndex].getId();
//    }
//    CNetManager::GetMe()->send_msg(body_ms);
    Game_Data::Player* pPlayer = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (pPlayer == NULL)
        return false;
    
    int nSkillID			= 0;
    int nSkillCount			= 0;
    int nCharacterID		= 0;
    
    int nSelectSkillID		= 0;
    int nSelectSkillCount	= 0;
    
    auto defaultDoc = GameReader::getDocInstance(DEFAULT_SKILL_FILE);
    rapidjson::Document::AllocatorType& allocator= defaultDoc->GetAllocator();
    rapidjson::Value value;
    value.SetObject();
    value.AddMember("roleId", player_id, allocator);
    
    for (int i = 0; i<defaultDoc->Size(); i++) {
        const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*defaultDoc), i);
        if (dic.IsNull()) {
            return false;
        }
        if (DICTOOL->getIntValue_json(dic, "job") == pPlayer->get_job()) {
            rapidjson::Value defaultSkill;
            defaultSkill.SetArray();
//            const rapidjson::Value &defaultRoot = DICTOOL->getSubDictionary_json(dic, "default_skill");
            nSkillCount = showSkill.size();
            for (int j = 0; j<nSkillCount; j++) {
//                nSkillID = DICTOOL->getIntValue_json(defaultRoot[j], "skillid");
                nSkillID = showSkill[j].getId();
                rapidjson::Value item;
                item.SetObject();
                item.AddMember("skillid", nSkillID, allocator);
                defaultSkill.PushBack(item, allocator);
                SkillManager::instance()->readShowSkillFromFile(nSkillID);
            }
            value.AddMember("default_skill", defaultSkill, allocator);
            
            rapidjson::Value sel_Skill;
            sel_Skill.SetArray();
//            const rapidjson::Value &selectRoot = DICTOOL->getSubDictionary_json(dic, "select_skill");
            nSelectSkillCount = selSkill.size();
            for (int j = 0; j<nSelectSkillCount; j++) {
                nSelectSkillID = selSkill[j].getId();
                rapidjson::Value item;
                item.SetObject();
                item.AddMember("skillid", nSelectSkillID, allocator);
                sel_Skill.PushBack(item, allocator);
                SkillManager::instance()->readSelSkillFromFile(nSelectSkillID);
            }
            value.AddMember("select_skill", sel_Skill, allocator);
            break;
        }
    }
    
    cocos2d::Value key(player_id);
    
    GameReader::savePlayerSkill(PLAYER_SKILL_FILE, value, key, "roleId");
    return true;
}

bool SkillMsgProc::send_uplevel_skill(int skillId, int nextSkillId)
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();

    Game_Logic::Game_Interface temp;
    vector<uint64> para;
    
    para.clear();
    para.push_back(skillId);//new
    para.push_back(nextSkillId);
    temp.set_para(para);
    on_uplevel_skill(temp);
//    char body[256] = {0};
//    message_stream body_ms(body, sizeof(body));
//    body_ms << CS_UPLEVEL_SKILL << skillId << player_id;
//    
//    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}
