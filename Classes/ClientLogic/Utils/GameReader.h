//
//  GameReader.h
//  soul
//
//  Created by ff on 14-9-11.
//
//

#ifndef __soul__GameReader__
#define __soul__GameReader__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "../cocos2d/external/json/document.h"
#include "../cocos2d/external/json/writer.h"
#include "../cocos2d/external/json/stringbuffer.h"

struct ACCOUNT_DOC_INFO {
    int roleId;
    int baseId;
    int level;
    int sex;
    const char* roleName;
    const char* account;
};

//template <class T>
//std::string Convert2String(T value) {
//    std::stringstream ss;
//    ss<<value;
//    return ss.str();
//}

class GameReader {
public:
    static std::map<std::string, rapidjson::Document*> docPool;
    
    static std::map<std::string, rapidjson::Document> filePool;
    
public:
    static bool readData(std::string filePath, rapidjson::Document* doc);
    
    static rapidjson::Document* getDocInstance(std::string filePath);
    
    static bool readSavedData(std::string filePath,rapidjson::Document &_doc);
//    static bool getWriteDocInstance(std::string filePath,rapidjson::Document &_doc);
    static void savePlayerSkill(std::string fileName, rapidjson::Value &value, cocos2d::Value &key, const char* keyName);
    static void saveInstanceScore(std::string fileName, rapidjson::Value &value, cocos2d::Value &key, const char* keyName);
    static void saveDoc2File(std::string fileName, rapidjson::Document &doc);
    
    static void saveToFile(std::string fileName, std::map<std::string, cocos2d::Value> &values, cocos2d::Value &key, const char* keyName);
    static void saveToFile(std::string fileName, ACCOUNT_DOC_INFO &info, cocos2d::Value &key, const char* keyName);
    static bool isExistInFile(std::string fileName, cocos2d::Value &key, rapidjson::Document& doc, rapidjson::Value& root, const char* keyName);
    static int getFileSize(std::string fileName);
};

#endif /* defined(__soul__GameReader__) */
