//
//  DialogManager.cpp
//  son
//
//  Created by ff on 15-6-1.
//
//

#include "DialogManager.h"
#include "Common/GameResource.h"
#include "ClientLogic/Utils/BaseUtils.h"

using namespace cocostudio;

bool DialogManager::loadDialog()
{
    dialogOver = false;
    if (currDialogId == toDialogId && currDialogGroupId == toGroupId) {
        return false;
    }
    
    
    std::string fileName(DIALOG_FILE);
    fileName += Convert2String(toDialogId);
    
    currGroup = new DialogGroup();
    if (currDialogId != toDialogId) {
        currGroup->clearIdTable();
    }
    
    if(!currGroup->loadGroup(fileName, toGroupId))
    {
        currGroup = nullptr;
        return false;
    }
    
    currDialogId = toDialogId;
    currDialogGroupId = toGroupId;
    return true;
}

bool DialogManager::nextPage()
{
    if (currGroup == nullptr) {
        dialogOver = true;
        return false;
    }
    
    if(!currGroup->nextPage())
    {
        dialogOver = true;
        currGroup = nullptr;
        return false;
    }
    
    return true;
}

void DialogManager::skipDialog()
{
    dialogOver = true;
    currGroup = nullptr;
}

DialogGroup* DialogManager::getCurrGroup()
{
    return currGroup;
}
