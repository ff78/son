//
//  MissionDialog.h
//  son
//
//  Created by ff on 15-6-6.
//
//

#ifndef __son__MissionDialog__
#define __son__MissionDialog__

#include "cocos2d.h"
#include "Common/GameDefine.h"

namespace Game_Data
{
    struct quest_data;
}


enum DialogueState
{
    DS_NpcDialogue = 0,
    DS_Mission,
    
    DS_Num
};


enum guide_step
{
    JUNIOR_GUIDE_STEP_2 = 2,
    JUNIOR_GUIDE_STEP_3 = 3,
    JUNIOR_GUIDE_STEP_4 = 4,
    JUNIOR_GUIDE_STEP_13 = 13,
    JUNIOR_GUIDE_STEP_14 = 14,
    JUNIOR_GUIDE_STEP_15 = 15,
};


struct ServiceData
{
    ServiceData(NpcServiceType Type, int ID, const char* Caption)
    :nType(Type)
    , nID(ID)
    , strCaption(Caption)
    {
    }
    NpcServiceType nType;
    int nID;
    std::string strCaption;
    
};


struct Compare
{
    bool operator ()(const ServiceData& a, const ServiceData& b)
    {
        return a.nType<b.nType;
    }
};

class MissionDialog
{
public:
    void nextPage();
    void showDialogueWithNpcTypeID(int npcId);
private:
    void updateDetail();
    void executeTask(int index);
    
private:
    ServiceData m_vecServiceData;
    int m_nNpcID;
    
    DialogueState m_State;

};

#endif /* defined(__son__MissionDialog__) */
