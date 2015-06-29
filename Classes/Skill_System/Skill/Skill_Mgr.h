
#pragma once

#include <map>
#include "Skill_Common.h"

enum SKILL_ATTRIBUTE
{
	SA_ID,							//
	SA_TARGET_TYPE,					// ��Ч����
	SA_HURT_RESULT,					// ���б���
	SA_HURT_ROAD_X_MOVE,            // ���е����ɫˮƽ�ܴ�λ��
	SA_HURT_ROAD_Y_MOVE,            // ���е����ɫ��ֱ�ܴ�λ��
	SA_HURT_SKY_X_MOVE,             // ���п��н�ɫˮƽ�ܴ�λ��
	SA_HURT_SKY_Y_MOVE,             // ���п��н�ɫ��ֱ�ܴ�λ��
	SA_HURT_CNTER_MOVE,				// ���ݹ��������ܴ�λ�Ʒ���
	SA_HURT_LEVEL,					// �ܴ���������
	SA_YINGZHI_TIME,				// Ӳֱʱ��
	SA_TARGET_RATE,                 // Ŀ����BUFF�ĸ���
	SA_TARGET_BUFF_ID,              // Ŀ���Buff��ID
	SA_HURT_CHANGE_COLOR,			// �ܴ��߱�ɫ
	SA_GET_MP,						// ���ŭ��
	SA_SHAKE_ID,					// ��Id
	
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
