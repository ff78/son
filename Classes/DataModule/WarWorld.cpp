//
//  WarWorld.cpp
//  cocosGame
//
//  Created by ff on 14-11-25.
//
//

#include "WarWorld.h"
#include "ClientLogic/FightDefine.h"


bool loadFromFile()
{
    WarZone::readFile(WARZONE_CONFIG_FILE);
    
    return true;
}