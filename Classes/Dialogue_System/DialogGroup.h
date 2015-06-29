//
//  DialogGroup.h
//  son
//
//  Created by ff on 15-6-1.
//
//

#ifndef __son__DialogGroup__
#define __son__DialogGroup__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "DialogSegment.h"

class DialogGroup
{
public:
    bool loadGroup(std::string fileName, int idx);
    
    static void initIdTable(rapidjson::Document &_doc);
    
    bool initData(int idx, rapidjson::Document& _doc);
    
    void clearIdTable();
    
    bool nextPage();
    static std::map<int, int> idTable;
    DialogSegment* getCurrSeg();
private:
    CC_SYNTHESIZE_READONLY(int, groupId, GroupId);
    CC_SYNTHESIZE_READONLY(int, segCount, SegCount);
    CC_SYNTHESIZE_READONLY(int, startSegId, StartSegId);
    std::vector<DialogSegment *> segVec;
    DialogSegment *currSeg;
};

#endif /* defined(__son__DialogGroup__) */
