//
//  SkillMsgProc.h
//  son
//
//  Created by ff on 15-4-25.
//
//

#ifndef __son__SkillMsgProc__
#define __son__SkillMsgProc__

#include "ClientLogic/Utils/GameUtil.h"
#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"
#include "LogicSkill.h"

class SkillMsgProc : public Singleton<SkillMsgProc>
{
    
public:
    static bool send_uplevel_skill(int skillId);
    static bool send_select_changes(std::vector<LogicSkill> &selSkill);
    
    static bool on_load_skill(Game_Logic::Game_Interface& gm_interface);
    static bool on_uplevel_skill(Game_Logic::Game_Interface& gm_interface);
};

#endif /* defined(__son__SkillMsgProc__) */
