//
//  WarWorld.h
//  cocosGame
//
//  Created by ff on 14-11-25.
//
//

#ifndef __cocosGame__WarWorld__
#define __cocosGame__WarWorld__

#include "cocos2d.h"
#include "ClientLogic/Utils/GameUtil.h"
#include "WarZone.h"

class WarWorld : public Singleton<WarWorld>
{
public:
    void getWarZone(int zoneId);
    
    std::map<int, WarZone *> getZoneMap(){return zoneMap;};
    
    bool loadFromFile();
    
private:
    std::map<int, WarZone *> zoneMap;
    std::map<int, bool> zoneHasOpen;
};

#endif /* defined(__cocosGame__WarWorld__) */
