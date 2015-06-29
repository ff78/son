/* -------------------------------------------------------------------------
//	文件名		：	SkillLogic.h
//	功能描述	：	所有的技能逻辑类
// -----------------------------------------------------------------------*/

#pragma once

#include "Skill_Common.h"

namespace Game_Logic
{
	struct Game_Interface;
}

struct Skill_Data;
class message_stream;
class Skill_Logic
{
public:
	Skill_Logic(void);
	~Skill_Logic(void);
    static Skill_Logic* instance();
public:
	uint32 CanUseSkill(Character* self, Character* target, Skill_Data* skill) const;
	// HitTimes:连击次数
	uint32 UseSkill(Skill_Use & skilluse) const;
	uint32 AddBuff(Character* self, Character* target, BuffID_t nBuffId, bool is_in_air = false, int nBuffLevel = 1) const;
	uint32 AddBuff(Character* self, Character* target, SkillID_t nSkillID, BuffID_t nBuffId, int movePos = 0, int hurtPos = 0, bool is_in_air =false, int bCritical = 0) const;
	uint32 CalculateTargetList(Character & rMe, OBJLIST& rTargets) const;
	uint32 HitThisTarget(Character& rMe, Character& rTar) const;
	uint32 EffectOnUnitOnce(Character& rMe, Character& rTar, BYTE HitTimes, BOOL bCriticalFlag=false) const;
	int CriticalHitThisTarget(Character* self, Character* target) const;
	uint32 GetHurtType(int pos, int hurtPos, int skillId);
	int   save_skill(int player_id);
public:
#ifdef GAME_CLIENT
	void load_skill(int character_id);
#endif
	bool fill_skill_message_stream(int player_id, message_stream& ms);
    bool fill_create_deputy_general_skill_message_stream(int deputy_general_id, message_stream& ms);
	uint32 uplevel_skill(int player_id,int character_id, int skill_id, int & skill_level_out);

private:
    static Skill_Logic*    instance_;
};

typedef Skill_Logic SKILL_LOGIC;