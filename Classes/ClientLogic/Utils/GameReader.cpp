//
//  GameReader.cpp
//  soul
//
//  Created by ff on 14-9-11.
//
//

#include "GameReader.h"

USING_NS_CC;
using namespace rapidjson;
using namespace cocostudio;

std::map<std::string, rapidjson::Document*> GameReader::docPool;
std::map<std::string, rapidjson::Document> GameReader::filePool;

bool GameReader::readData(std::string filePath,rapidjson::Document* _doc)
{
    bool ret = false;
    
    std::string contentStr = FileUtils::getInstance()->getStringFromFile(filePath);
    
    _doc->Parse < 0 > (contentStr.c_str());
    ret = !_doc->HasParseError();
    
    return ret;
}

rapidjson::Document* GameReader::getDocInstance(std::string filePath)
{
    auto dataItr = docPool.find(filePath);
    if(dataItr == docPool.end())
    {
        rapidjson::Document* _doc = new rapidjson::Document();
        
        if(readData(filePath, _doc))
        {
            docPool.insert(std::make_pair(filePath, _doc));
            return docPool[filePath];
        }else{
            return NULL;
        }
    }else{
        return (dataItr->second);
    }
}

//bool GameReader::getWriteDocInstance(std::string filePath,rapidjson::Document &_doc)
//{
//    auto dataItr = filePool.find(filePath);
//    if(dataItr == filePool.end())
//    {
//        if(readSavedData(filePath, _doc))
//        {
//            filePool.insert(std::make_pair(filePath, _doc));
////            filePool.insert(std::make_pair(filePath, _doc));
//            return true;
//        }else{
//            return false;
//        }
//    }else{
//        ((*dataItr).second);
////        _doc = dataItr.second;
//        return true;
//    }
//    return false;
//}

bool GameReader::readSavedData(std::string filePath,rapidjson::Document &_doc)
{
    bool ret = false;
    
    std::string path(FileUtils::getInstance()->getWritablePath());
    path += filePath;
    std::string contentStr = FileUtils::getInstance()->getStringFromFile(path);
    
    _doc.Parse < 0 > (contentStr.c_str());
    ret = !_doc.HasParseError();
    
    return ret;
}

int GameReader::getFileSize(std::string fileName)
{
    auto path = FileUtils::getInstance()->getWritablePath();
    path += fileName;
    
    if (!FileUtils::getInstance()->isFileExist(path)) {
        return 0;
    }
    rapidjson::Document doc;
    if(!readSavedData(path, doc))
    {
        return 0;
    }

    return doc.Size();
}

bool GameReader::isExistInFile(std::string fileName, cocos2d::Value &key, rapidjson::Document& doc, rapidjson::Value& root, const char* keyName)
{
//    root = NULL;
    auto path = FileUtils::getInstance()->getWritablePath();
    path += fileName;
    
    if (!FileUtils::getInstance()->isFileExist(path)) {
        return false;
    }
    
    
    if(!readSavedData(fileName, doc))
    {
        return false;
    }
    
    bool found = false;
    auto keyType = key.getType();
    for (int i=0; i<doc.Size(); i++) {
        switch (keyType) {
            case cocos2d::Value::Type::STRING:
            {
                std::string tempKey = DICTOOL->getStringValue_json(doc[i], keyName);
                if (tempKey == key.asString()) {
                    found = true;
                }
            }
                break;
            case cocos2d::Value::Type::INTEGER:
            {
                int tempKey = DICTOOL->getIntValue_json(doc[i], keyName);
                if (tempKey == key.asInt()) {
                    found = true;
                }
            }
                break;
            default:
                break;
        }
        
        if (found) {
            root = doc[i];
            return true;
        }
    }
    return false;
}
void GameReader::savePlayerSkill(std::string fileName, rapidjson::Value &value, cocos2d::Value &key, const char* keyName)
{
    auto path = FileUtils::getInstance()->getWritablePath();
    path += fileName;
    
    rapidjson::Document doc;
    
    if(FileUtils::getInstance()->isFileExist(path)){
        if(!readSavedData(fileName, doc))
        {
            return;
        }
    }else{
        doc.SetArray();
    }
    
    bool found = false;
    int index = -1;
    auto keyType = key.getType();
    
    for (int i=0; i<doc.Size(); i++) {
        switch (keyType) {
            case cocos2d::Value::Type::STRING:
            {
                std::string tempKey = DICTOOL->getStringValue_json(doc[i], keyName);
                if (tempKey == key.asString()) {
                    found = true;
                }
            }
                break;
            case cocos2d::Value::Type::INTEGER:
            {
                int tempKey = DICTOOL->getIntValue_json(doc[i], keyName);
                if (tempKey == key.asInt()) {
                    found = true;
                }
            }
                break;
            default:
                break;
        }
        
        if (found) {
            index = i;
            break;
        }
    }
    
    rapidjson::Document::AllocatorType& allocator= doc.GetAllocator();

    if (found) {
        doc[index]["roleId"] = DICTOOL->getIntValue_json(value, "roleId");
        rapidjson::Value &defaultSkill = doc[index]["default_skill"];
        int size = defaultSkill.Size();
        for (int i = 0; i<size; i++) {
            defaultSkill.PopBack();
        }
        size = value["default_skill"].Size();
        for (int i = 0; i<size; i++) {
            rapidjson::Value skill;
            skill.SetObject();
            skill.AddMember("skillid", DICTOOL->getIntValue_json(value["default_skill"][i], "skillid"), allocator);
            defaultSkill.PushBack(skill, allocator);
        }
        rapidjson::Value &selSkill = doc[index]["select_skill"];
        size = selSkill.Size();
        for (int i = 0; i<size; i++) {
            selSkill.PopBack();
        }
        size = value["select_skill"].Size();
        for (int i = 0; i<size; i++) {
            rapidjson::Value skill;
            skill.SetObject();
            skill.AddMember("skillid", DICTOOL->getIntValue_json(value["select_skill"][i], "skillid"), allocator);
            selSkill.PushBack(skill, allocator);
        }
    }else{
        doc.PushBack(value, allocator);
    }
    
    StringBuffer buff;
    rapidjson::Writer<StringBuffer> writer(buff);
    doc.Accept(writer);
    
    
    std::string s = StringUtils::format("%s", buff.GetString());
    log("%s", s.c_str());
    FILE* pFile = fopen(path.c_str(),"wb");
    if (pFile)
    {
        fputs(buff.GetString(),pFile);
        fclose(pFile);
    }else
    {
        CCLOG("UserManage::SaveUserToFile error! can not open %s",path.c_str());
    }

}

void GameReader::saveInstanceScore(std::string fileName, rapidjson::Value &value, cocos2d::Value &key, const char* keyName)
{
    auto path = FileUtils::getInstance()->getWritablePath();
    path += fileName;

    rapidjson::Document doc;
    
    if(FileUtils::getInstance()->isFileExist(path)){
        if(!readSavedData(fileName, doc))
        {
            return;
        }
    }else{
        doc.SetArray();
    }
    
    bool found = false;
    int index = -1;
    auto keyType = key.getType();
    
    for (int i=0; i<doc.Size(); i++) {
        switch (keyType) {
            case cocos2d::Value::Type::STRING:
            {
                std::string tempKey = DICTOOL->getStringValue_json(doc[i], keyName);
                if (tempKey == key.asString()) {
                    found = true;
                }
            }
                break;
            case cocos2d::Value::Type::INTEGER:
            {
                int tempKey = DICTOOL->getIntValue_json(doc[i], keyName);
                if (tempKey == key.asInt()) {
                    found = true;
                }
            }
                break;
            default:
                break;
        }
        
        if (found) {
            index = i;
            break;
        }
    }
    
    rapidjson::Document::AllocatorType& allocator= doc.GetAllocator();
    
    if (found) {
        int size = doc[index]["stage_result"].Size();
        for (int i = 0; i<size; i++) {
            int passVal = DICTOOL->getIntValue_json(value["stage_result"][i], "pass");
            doc[index]["stage_result"][i]["pass"] = passVal;
            const rapidjson::Value& instanceResult = DICTOOL->getSubDictionary_json(value["stage_result"][i], "instance_result");
            int instanceCount = doc[index]["stage_result"][i]["instance_result"].Size();
            for (int j = 0; j<instanceCount; j++) {
                int scoreVal = DICTOOL->getIntValue_json(instanceResult[j], "instance_score");
                doc[index]["stage_result"][i]["instance_result"][j]["instance_score"] = scoreVal;
            }
        }
//        doc[index]["roleId"] = DICTOOL->getIntValue_json(value, "roleId");
//        rapidjson::Value &defaultSkill = doc[index]["default_skill"];
//        int size = defaultSkill.Size();
//        for (int i = 0; i<size; i++) {
//            defaultSkill.PopBack();
//        }
//        size = value["default_skill"].Size();
//        for (int i = 0; i<size; i++) {
//            rapidjson::Value skill;
//            skill.SetObject();
//            skill.AddMember("skillid", DICTOOL->getIntValue_json(value["default_skill"][i], "skillid"), allocator);
//            defaultSkill.PushBack(skill, allocator);
//        }
//        rapidjson::Value &selSkill = doc[index]["select_skill"];
//        size = selSkill.Size();
//        for (int i = 0; i<size; i++) {
//            selSkill.PopBack();
//        }
//        size = value["select_skill"].Size();
//        for (int i = 0; i<size; i++) {
//            rapidjson::Value skill;
//            skill.SetObject();
//            skill.AddMember("skillid", DICTOOL->getIntValue_json(value["select_skill"][i], "skillid"), allocator);
//            selSkill.PushBack(skill, allocator);
//        }
    }else{
        doc.PushBack(value, allocator);
    }
    
//    StringBuffer buff;
//    rapidjson::Writer<StringBuffer> writer(buff);
//    doc.Accept(writer);
    
    
    saveDoc2File(fileName, doc);
    
}
void GameReader::saveDoc2File(std::string fileName, rapidjson::Document &doc)
{
    auto path = FileUtils::getInstance()->getWritablePath();
    path += fileName;

    StringBuffer buff;
    rapidjson::Writer<StringBuffer> writer(buff);
    doc.Accept(writer);
    
    
    std::string s = StringUtils::format("%s", buff.GetString());
    log("%s", s.c_str());
    FILE* pFile = fopen(path.c_str(),"wb");
    if (pFile)
    {
        fputs(buff.GetString(),pFile);
        fclose(pFile);
    }else
    {
        CCLOG("UserManage::SaveUserToFile error! can not open %s",path.c_str());
    }

}

void GameReader::saveToFile(std::string fileName, std::map<std::string, cocos2d::Value> &values, cocos2d::Value &key, const char* keyName)
{
    auto path = FileUtils::getInstance()->getWritablePath();
    path += fileName;
    
    rapidjson::Document doc;

    if(FileUtils::getInstance()->isFileExist(path)){
        if(!readSavedData(fileName, doc))
        {
            return;
        }
    }else{
        doc.SetArray();
    }

    bool found = false;
    int index = -1;
    auto keyType = key.getType();
    
    for (int i=0; i<doc.Size(); i++) {
        switch (keyType) {
            case cocos2d::Value::Type::STRING:
            {
                std::string tempKey = DICTOOL->getStringValue_json(doc[i], keyName);
                if (tempKey == key.asString()) {
                    found = true;
                }
            }
                break;
            case cocos2d::Value::Type::INTEGER:
            {
                int tempKey = DICTOOL->getIntValue_json(doc[i], keyName);
                if (tempKey == key.asInt()) {
                    found = true;
                }
            }
                break;
            default:
                break;
        }
        
        if (found) {
            index = i;
            break;
        }
    }
    
    rapidjson::Document::AllocatorType& allocator= doc.GetAllocator();

    rapidjson::Value uList;
    uList.SetObject();
    std::map<std::string, cocos2d::Value>::iterator it;

    for(it=values.begin();it!=values.end();it++)
    {
        auto valType = it->second.getType();
        switch (valType) {
            case cocos2d::Value::Type::STRING:
                if (found) {
                    doc[index][(it->first).c_str()] = it->second.asString().c_str();
                }else{
                    uList.AddMember((it->first).c_str(), it->second.asString().c_str(), allocator);
                }
                break;
            case cocos2d::Value::Type::INTEGER:
                if (found) {
                    doc[index][(it->first).c_str()] = it->second.asInt();
                }else{
                    uList.AddMember((it->first).c_str(), it->second.asInt(), allocator);
                }
                break;
            case cocos2d::Value::Type::FLOAT:
                if (found) {
                    doc[index][(it->first).c_str()] = it->second.asFloat();
                }else{
                    uList.AddMember((it->first).c_str(), it->second.asFloat(), allocator);
                }
            default:
                break;
        }
    }
    if (!found) {
        doc.PushBack(uList, allocator);
    }
    StringBuffer buff;
    rapidjson::Writer<StringBuffer> writer(buff);
    doc.Accept(writer);
    
    
    std::string s = StringUtils::format("%s", buff.GetString());
    log("%s", s.c_str());
    FILE* pFile = fopen(path.c_str(),"wb");
    if (pFile)
    {
        fputs(buff.GetString(),pFile);
        fclose(pFile);
    }else
    {
        CCLOG("UserManage::SaveUserToFile error! can not open %s",path.c_str());
    }
}

void GameReader::saveToFile(std::string fileName, ACCOUNT_DOC_INFO &info, cocos2d::Value &key, const char* keyName)
{
    auto path = FileUtils::getInstance()->getWritablePath();
    path += fileName;
    
    rapidjson::Document doc;
    
    if(FileUtils::getInstance()->isFileExist(path)){
        if(!readSavedData(fileName, doc))
        {
            return;
        }
    }else{
        doc.SetArray();
    }
    
    bool found = false;
    int index = -1;
    auto keyType = key.getType();
    
    for (int i=0; i<doc.Size(); i++) {

        switch (keyType) {
            case cocos2d::Value::Type::STRING:
            {
                std::string tempKey = DICTOOL->getStringValue_json(doc[i], keyName);
                if (tempKey == key.asString()) {
                    found = true;
                }
            }
                break;
            case cocos2d::Value::Type::INTEGER:
            {
                int tempKey = DICTOOL->getIntValue_json(doc[i], keyName);
                if (tempKey == key.asInt()) {
                    found = true;
                }
            }
                break;
            default:
                break;
        }
        
        if (found) {
            index = i;
            break;
        }
    }
    
    rapidjson::Document::AllocatorType& allocator= doc.GetAllocator();
    
    rapidjson::Value uList;
    uList.SetObject();
    std::map<std::string, cocos2d::Value>::iterator it;

    uList.AddMember("roleId", info.roleId, allocator);
    uList.AddMember("baseId", info.baseId, allocator);
    uList.AddMember("level", info.level, allocator);
    uList.AddMember("sex", info.sex, allocator);
    uList.AddMember("roleName", info.roleName, allocator);
    uList.AddMember("account", info.account, allocator);

    if (!found) {
        doc.PushBack(uList, allocator);
    }
    StringBuffer buff;
    rapidjson::Writer<StringBuffer> writer(buff);
    doc.Accept(writer);
    
    
    std::string s = StringUtils::format("%s", buff.GetString());
    log("%s", s.c_str());
    FILE* pFile = fopen(path.c_str(),"wx");
    if (pFile)
    {
        fputs(buff.GetString(),pFile);
        fclose(pFile);
    }else
    {
        CCLOG("UserManage::SaveUserToFile error! can not open %s",path.c_str());
    }
}


