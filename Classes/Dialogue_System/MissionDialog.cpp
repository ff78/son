//
//  MissionDialog.cpp
//  son
//
//  Created by ff on 15-6-6.
//
//

#include "MissionDialog.h"

void MissionDialog::showDialogueWithNpcTypeID(int npcId)
{
    m_nNpcID = npcId;
    m_State = DS_NpcDialogue;
    memset(&m_vecServiceData, 0, sizeof(m_vecServiceData));
    
    updateDetail();
}

void MissionDialog::updateDetail()
{
    
}
