//
//  DialogLine.h
//  son
//
//  Created by ff on 15-6-1.
//
//

#ifndef __son__DialogLine__
#define __son__DialogLine__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class DialogLine
{
public:
    bool loadLine(std::string fileName, int idx);
    
    static void initIdTable(rapidjson::Document &_doc);
    
    bool initData(int idx, rapidjson::Document& _doc);
    
    static std::map<int, int> idTable;
    static void clearIdTable();
private:
    CC_SYNTHESIZE_READONLY(std::string, content, Content);
    CC_SYNTHESIZE_READONLY(int, lineId, LineId);
    
};

#endif /* defined(__son__DialogLine__) */
