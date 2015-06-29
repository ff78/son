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
#include "json/document.h"

//template <class T>
//std::string Convert2String(T value) {
//    std::stringstream ss;
//    ss<<value;
//    return ss.str();
//}

class GameReader {
public:
    static std::map<std::string, rapidjson::Document*> docPool;
    
public:
    static bool readData(std::string filePath, rapidjson::Document* doc);
    
    static rapidjson::Document* getDocInstance(std::string filePath);

};

#endif /* defined(__soul__GameReader__) */
