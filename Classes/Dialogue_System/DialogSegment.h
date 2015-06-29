//
//  DialogSegment.h
//  son
//
//  Created by ff on 15-6-1.
//
//

#ifndef __son__DialogSegment__
#define __son__DialogSegment__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "DialogLine.h"

class DialogSegment
{
public:
    bool loadSegment(std::string fileName, int idx);
    
    static void initIdTable(rapidjson::Document &_doc);
    
    bool initData(int idx, rapidjson::Document& _doc);
    
    void nextPage();
    static std::map<int, int> idTable;
    
    static void clearIdTable();
    DialogLine *getCurrLine();
private:
    CC_SYNTHESIZE_READONLY(int, segId, SegId);
    CC_SYNTHESIZE_READONLY(int, startLineId, startLineId);
    CC_SYNTHESIZE_READONLY(int, lineCount, lineCount);
//    CC_SYNTHESIZE_READONLY(int, dialogType, DialogType);
    CC_SYNTHESIZE_READONLY(int, dir, Dir);
    CC_SYNTHESIZE_READONLY(std::string, faceIcon, FaceIcon);
    CC_SYNTHESIZE_READONLY(std::string, faceName, FaceName);
    CC_SYNTHESIZE_READONLY(bool, segOver, SegOver);
    std::vector<DialogLine *> lineVec;
    DialogLine *currLine;
    CC_SYNTHESIZE_READONLY(int, currLineIndex, CurrLineIdx);
};

#endif /* defined(__son__DialogSegment__) */
