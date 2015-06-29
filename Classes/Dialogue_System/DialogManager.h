//
//  DialogManager.h
//  son
//
//  Created by ff on 15-6-1.
//
//

#ifndef __son__DialogManager__
#define __son__DialogManager__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ClientLogic/Utils/GameUtil.h"
#include "DialogGroup.h"

class DialogManager : public Singleton<DialogManager>
{
public:
    bool loadDialog();
    bool nextPage();
    void skipDialog();
    DialogGroup *getCurrGroup();
private:
    int currDialogId = -1;
    int currDialogGroupId = -1;
    CC_SYNTHESIZE_READONLY(bool, dialogOver, DialogOver);
    DialogGroup *currGroup;
    CC_SYNTHESIZE(int, toDialogId, DialogId);
    CC_SYNTHESIZE(int, toGroupId, GroupId);
};

#endif /* defined(__son__DialogManager__) */
