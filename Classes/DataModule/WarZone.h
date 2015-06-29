//
//  WarZone.h
//  cocosGame
//
//  Created by ff on 14-11-25.
//
//

#ifndef __cocosGame__WarZone__
#define __cocosGame__WarZone__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class WarZone
{
public:
//    void initIdTable(rapidjson::Document &_doc);
//    
//    bool initData(int idx, rapidjson::Document& _doc);
//    
//    void readZoneFromFile(int zoneIdx, std::string filename);
    
    static void readFile(std::string filename);
private:
    CC_SYNTHESIZE_READONLY(int, zoneId, ZoneId);
    CC_SYNTHESIZE_READONLY(std::string, zoneName, zoneName);
    CC_SYNTHESIZE_READONLY(int, fieldCount, FieldCount);
    CC_SYNTHESIZE(bool, hasOpen, HasOpen);
    CC_SYNTHESIZE_READONLY(int, nextZone, nextZone);
    
//public:
//    static std::map<int, int> idTable;
public:
    static std::map<int, WarZone> zoneMap;
    static std::vector<int> zoneIdVec;
};

#endif /* defined(__cocosGame__WarZone__) */
