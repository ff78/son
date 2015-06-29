
#pragma once

#include <map>
#include "Skill_Common.h"

enum SKILL_ATTRIBUTE
{
	SA_ID,							//
	SA_TARGET_TYPE,					// 有效对象
	SA_HURT_RESULT,					// 击中表现
	SA_HURT_ROAD_X_MOVE,            // 击中地面角色水平受创位移
	SA_HURT_ROAD_Y_MOVE,            // 击中地面角色垂直受创位移
	SA_HURT_SKY_X_MOVE,             // 击中空中角色水平受创位移
	SA_HURT_SKY_Y_MOVE,             // 击中空中角色垂直受创位移
	SA_HURT_CNTER_MOVE,				// 根据攻击中心受创位移反向
	SA_HURT_LEVEL,					// 受创动作级别
	SA_YINGZHI_TIME,				// 硬直时间
	SA_TARGET_RATE,                 // 目标上BUFF的概率
	SA_TARGET_BUFF_ID,              // 目标的Buff的ID
	SA_HURT_CHANGE_COLOR,			// 受创者变色
	SA_GET_MP,						// 获得怒气
	SA_SHAKE_ID,					// 震动Id
	
	SA_MAX_COUNT
};

struct Skill_Data
{
	uint32  m_Attr[SA_MAX_COUNT];
	uint32  level_buff[SKILL_MAX_LEVEL];
};

class Skill_Mgr
{
public:
	Skill_Mgr();
	~Skill_Mgr();
	void cleanup();
	int  initialize();
public:
	int  load_skill_data();
    static Skill_Mgr* instance();
public:
	bool is_load();
	Skill_Data* GetSkillData(uint32 skillId);
private:
	map<uint32, Skill_Data>			m_mapSkill;
    static Skill_Mgr* instance_;
	bool                m_is_load;
};

typedef Skill_Mgr SKILL_MGR;
