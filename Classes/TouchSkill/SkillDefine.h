//
//  SkillDefine.h
//  son
//
//  Created by ff on 15-4-25.
//
//

#ifndef son_SkillDefine_h
#define son_SkillDefine_h

#include "cocos2d.h"

#define SKILL_DATA_FILE "game_data/skill/skill_data.json"
#define  MAX_SELECT_SKILL_COUNT			4
#define  MAX_RUN_SKILL_COUNT            2
#define SKILL_UPGRADE_DONE "SKILL_UPGRADE_DONE"

enum SKILL_FIGHT_TYPE
{
    TARGET_SKILL_TYPE_LINK				= 0,
    TARGET_SKILL_TYPE_SELECT			= 1,
    TARGET_SKILL_TYPE_SP				= 2,
    TARGET_SKILL_TYPE_GENERAL           = 3,
    TARGET_SKILL_TYPE_RUN_1             = 4,
    TARGET_SKILL_TYPE_RUN_2             = 5,
    TARGET_SKILL_TYPE_RUN_3             = 6,
    TARGET_SKILL_TYPE_ERROR
};

enum SKILL_UPGRADE_RESULT
{
    SKILL_UPGRADE_SUCCESS = 0,
    SKILL_UPGRADE_MAX_LEVEL = 1,
    SKILL_UPGRADE_REQUIRE_PLAYER_LV = 2,
    SKILL_UPGRADE_MONEY_NOTENOUGH = 3,
    SKILL_UPGRADE_NEXT_SKILL_ERROR = 4,
    SKILL_UPGRADE_WAIT_RESPONSE = 5,
    SKILL_UPGRADE_OTHER_ERROR,

};

typedef struct _TARGET_CHARACTER_BATTLE_SKILL_DATA
{
    int								nSpSkillID;
    int								nGeneralSkillID;
    
    int								nRunSkill[MAX_RUN_SKILL_COUNT];
    int								nSelectedSkill[MAX_SELECT_SKILL_COUNT];
}TARGET_CHARACTER_BATTLE_SKILL_DATA;

#endif
