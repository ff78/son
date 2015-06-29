/* -------------------------------------------------------------------------
//	�ļ���		��	SkillCommon.h
//	��������	��	���ڴ��Skill�Ĺ�������
// -----------------------------------------------------------------------*/

#ifndef _SKILL_COMMON_H
#define _SKILL_COMMON_H

#include "Game_Interface/common.h"
#include "Character_System/Character.h"

using namespace Game_Data;

#define SKILL_MAX_LEVEL  100             // �������ȼ�

enum SKILL_TARGET_TYPE
{
	STT_ENEMY = 1,              // �з�
	STT_FRIEND,                 // �ѷ�
	STT_SELF,                   // �Լ�
};

#ifdef GAME_CLIENT

#else
typedef enum{
	LIGHT_HIT,
	HEAVY_HIT,
	BACK_LIGHT_HIT,
	BACK_HEAVY_HIT,
	HIT_FLY,
	BACK_HIT_FLY
}Hurt_Type;

#endif // CLIENT

typedef struct _OBJLIST
{
	enum
	{
		MAX_OBJ_LIST_SIZE = 255,
	};
	Character*		m_aObj[MAX_OBJ_LIST_SIZE];
	BYTE		m_Count;
	VOID CleanUp(VOID)
	{
		memset((VOID*)m_aObj, 0, sizeof(m_aObj));
		m_Count = 0;
	}
	_OBJLIST( )
	{
		CleanUp();
	};
} OBJLIST;

struct Skill_Use
{
	int nSelfID;
	int nTargetID;
	int nSkillID;
	int nLevel;            // ���ܵȼ�
	int nMovePos;          // �ƶ�����
	bool nHurtPos;          // ������λ

	bool is_in_the_air_;//�Ƿ��ڿ���
	Skill_Use(int nSelfID, int nTargetID, int nSkillID, int nLevel, int nMovePos, bool nHurtPos, bool is_in_the_air)
	{
		this->nSelfID   = nSelfID;
		this->nTargetID = nTargetID;
		this->nSkillID  = nSkillID;
		this->nLevel    = nLevel;
		this->nMovePos  = nMovePos;
		this->nHurtPos  = nHurtPos;

		this->is_in_the_air_ = is_in_the_air;
	}
	VOID CleanUp(VOID)
	{
		nSelfID    = 0;
		nTargetID  = 0;
		nSkillID   = 0;
		nLevel     = 0;
		nMovePos   = 0;
		nHurtPos   = 0;
	}
};

#endif // _SKILL_COMMON_H