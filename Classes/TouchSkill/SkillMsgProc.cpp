//
//  SkillMsgProc.cpp
//  son
//
//  Created by ff on 15-4-25.
//
//

#include "SkillMsgProc.h"
#include "Network_Common/NetManager.h"
#include "Network_Common/message.h"
#include "Network_Common/message_stream.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "SkillManager.h"
#include "SkillDefine.h"

bool SkillMsgProc::on_load_skill(Game_Logic::Game_Interface &gm_interface)
{
    SkillManager::instance()->setWaitForPack(true);
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (player == NULL)
        return false;
    
    if (player->get_job_skill_size() > 0)
        return false;
    
    int nSkillID			= 0;
    int nSkillCount			= 0;
    int nCharacterID		= 0;
    body_ms >> nSkillCount;
    
    for (int i = 0; i < nSkillCount; ++i)
    {
        body_ms >> nCharacterID;
        body_ms >> nSkillID;
        
        SkillManager::instance()->readShowSkillFromFile(nSkillID);
    }
    
    int nSelectSkillID		= 0;
    int nSelectSkillCount	= 0;
    body_ms >> nSelectSkillCount;
    
    for (int i = 0; i < nSelectSkillCount; ++i)
    {
        body_ms >> nCharacterID;
        body_ms >> nSelectSkillID;
        
        SkillManager::instance()->readSelSkillFromFile(nSelectSkillID);
    }

    SkillManager::instance()->setWaitForPack(false);
    return true;
}

bool SkillMsgProc::on_uplevel_skill(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));
    
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* pPlayer = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (pPlayer == NULL)
        return false;
    
    int skill_id		= 0;
    int skill_up_id		= 0;
    int character_id	= 0;
    body_ms >> skill_id;
    body_ms >> skill_up_id;
    body_ms >> character_id;
    
    SkillManager::instance()->upgradeSkillResult(skill_id, skill_up_id);
    
    return true;
}

bool SkillMsgProc::send_select_changes(std::vector<LogicSkill> &selSkill)
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    char msg_buf[1024] = { 0 };
    message_stream body_ms(msg_buf, sizeof(msg_buf));
    body_ms << CS_CHANGE_SELECT_SKILL;
    body_ms << player_id;
    
    for (int nIndex = 0; nIndex < MAX_SELECT_SKILL_COUNT; ++nIndex)
    {
        if (nIndex >= selSkill.size()) {
            body_ms << 0;
            continue;
        }
        body_ms << selSkill[nIndex].getId();
    }
    CNetManager::GetMe()->send_msg(body_ms);
    return true;
}

bool SkillMsgProc::send_uplevel_skill(int skillId)
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << CS_UPLEVEL_SKILL << skillId << player_id;
    
    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}
