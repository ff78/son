/* -------------------------------------------------------------------------
//	�ļ���		��	BuffCommon.h
//	��������	��	���ڴ��Buff�Ĺ�������
// -----------------------------------------------------------------------*/

#ifndef _BUFF_COMMON_H
#define _BUFF_COMMON_H

#include "../../Game_Interface/common.h"

#define	 MAX_BUFF_LOGIC_COUNT		10	
#define  MAX_BUFF_COUNT_ON_PALYER	10		// �佫�������BUFF��
#define  MAX_EFFECT_COUNT			4		// һ��BUFF���ӵ�е�Ч������
#define  MAX_BUFF_DESCRIBE_SIZE		126		// BUFF�����ĳ���

/************************************************************************/
// Buff����Ч������ض���
// BuffЧ�����Ե�����
enum BUFF_EFFECT_ATTRIBUTE_TYPE
{
    BUFF_EFFECT_ATTRIBUTE_TYPE_MAX_HP						= 1,								// ��Ѫ����
    BUFF_EFFECT_ATTRIBUTE_TYPE_CUR_HP						= 2,								// ��ǰ��Ѫ
    BUFF_EFFECT_ATTRIBUTE_TYPE_HP_RECOVER_SPEED				= 3,								// ��Ѫ�ظ��ٶ�
    BUFF_EFFECT_ATTRIBUTE_TYPE_MAX_MP						= 4,								// ħ������
    BUFF_EFFECT_ATTRIBUTE_TYPE_CUR_MP						= 5,								// ��ǰħ��
    BUFF_EFFECT_ATTRIBUTE_TYPE_MP_RECOVER_SPEED				= 6,								// ħ���ظ��ٶ�
    BUFF_EFFECT_ATTRIBUTE_TYPE_MAX_AP						= 7,								// ŭ������
    BUFF_EFFECT_ATTRIBUTE_TYPE_CUR_AP						= 8,								// ��ǰŭ��
    BUFF_EFFECT_ATTRIBUTE_TYPE_AP_RECOVER_SPEED				= 9,								// ŭ���ָ��ٶ�
    BUFF_EFFECT_ATTRIBUTE_TYPE_ATTACK						= 10,								// ������
    BUFF_EFFECT_ATTRIBUTE_TYPE_DEFINE						= 11,								// ������
    BUFF_EFFECT_ATTRIBUTE_TYPE_HIT_RATIO					= 12,								// ����ֵ
    BUFF_EFFECT_ATTRIBUTE_TYPE_AVOIDANCE					= 13,								// �ر�ֵ
    BUFF_EFFECT_ATTRIBUTE_TYPE_CRIT_RATE					= 14,								// ����ֵ
    BUFF_EFFECT_ATTRIBUTE_TYPE_TENACITY						= 15,								// ����ֵ
    BUFF_EFFECT_ATTRIBUTE_TYPE_MOVE_SPEED_RATE				= 16,								// �ƶ�����
    BUFF_EFFECT_ATTRIBUTE_TYPE_FLOAT						= 17,								// ������ֵ
    BUFF_EFFECT_ATTRIBUTE_TYPE_HIT_DOWN                     = 18,								// ������ֵ
    BUFF_EFFECT_ATTRIBUTE_TYPE_FAINT                        = 19,								// ѣ��״̬
    BUFF_EFFECT_ATTRIBUTE_TYPE_FIX							= 20,								// ����״̬
    BUFF_EFFECT_ATTRIBUTE_TYPE_FROZEN						= 21,								// ����״̬
    BUFF_EFFECT_ATTRIBUTE_TYPE_ICE_RESIST					= 22,								// ����
    BUFF_EFFECT_ATTRIBUTE_TYPE_FIRE_RESIST					= 23,								// ��
    BUFF_EFFECT_ATTRIBUTE_TYPE_THUNDER_RESIST				= 24,								// �׿�
    BUFF_EFFECT_ATTRIBUTE_TYPE_WIND_RESIST					= 25,								// �翹
    BUFF_EFFECT_ATTRIBUTE_TYPE_LIGHT_RESIST					= 26,								// �⿹
    BUFF_EFFECT_ATTRIBUTE_TYPE_DARK_RESIST					= 27,								// ����
    BUFF_EFFECT_ATTRIBUTE_TYPE_IMMU_ALL						= 28,								// �������м���״̬
    BUFF_EFFECT_ATTRIBUTE_TYPE_IMMU_DEBUFF					= 29,								// ����ָ������״̬
    BUFF_EFFECT_ATTRIBUTE_TYPE_IMMU_FIX						= 30,								// ���߶���
    BUFF_EFFECT_ATTRIBUTE_TYPE_IMMU_FROZEN					= 31,								// ���߱���
    BUFF_EFFECT_ATTRIBUTE_TYPE_1							= 32,								// ����Buff_1
    BUFF_EFFECT_ATTRIBUTE_TYPE_2							= 33,								// ����Buff_2
    BUFF_EFFECT_ATTRIBUTE_TYPE_3                            = 34,								// ����Buff_3
    BUFF_EFFECT_ATTRIBUTE_TYPE_4                            = 35,								// ����Buff_4
    BUFF_EFFECT_ATTRIBUTE_TYPE_5                            = 36,								// ����Buff_5
    BUFF_EFFECT_ATTRIBUTE_TYPE_6                            = 37,								// ����Buff_6
    BUFF_EFFECT_ATTRIBUTE_TYPE_7                            = 38,								// ����Buff_7
    BUFF_EFFECT_ATTRIBUTE_TYPE_8                            = 39,								// ����Buff_8
    BUFF_EFFECT_ATTRIBUTE_TYPE_MAX
};																							  
																							  
// BuffЧ������ֵ������																	  
enum BUFF_EFFECT_ATTRIBUTE_VALUE_TYPE														  
{																							  
	BUFF_EFFECT_ATTRIBUTE_VALUE_TYPE_PERCENT			= 0,									// �ٷ���
	BUFF_EFFECT_ATTRIBUTE_VALUE_TYPE_INTEGER			= 1,									// ����
	BUFF_EFFECT_ATTRIBUTE_VALUE_TYPE_ERROR
};

// Buff����Ч��������
typedef struct __BUFF_EFFECT_DATA
{
	int													nEffectValue;							// BuffЧ��ֵ

	BUFF_EFFECT_ATTRIBUTE_TYPE							eEffectAttributeType;					// BuffЧ������������
	BUFF_EFFECT_ATTRIBUTE_VALUE_TYPE					eEffectAttributeValueType;				// BuffЧ������ֵ������
}BUFF_EFFECT_DATA;

/************************************************************************/
// ����Buff����ض���
// Buff��Ч������
enum BUFF_TYPE
{
	BUFF_TYPE_MAX_HP									= 1,									// ��Ѫ����
	BUFF_TYPE_CUR_HP									= 2,									// ��ǰ��Ѫ
	BUFF_TYPE_HP_RECOVER_SPEED							= 3,									// ��Ѫ�ظ��ٶ�
	BUFF_TYPE_MAX_MP									= 4,									// ħ������
	BUFF_TYPE_CUR_MP									= 5,									// ��ǰħ��
	BUFF_TYPE_MP_RECOVER_SPEED							= 6,									// ħ���ظ��ٶ�
	BUFF_TYPE_MAX_AP									= 7,									// ŭ������
	BUFF_TYPE_CUR_AP									= 8,									// ��ǰŭ��
	BUFF_TYPE_AP_RECOVER_SPEED							= 9,									// ŭ���ָ��ٶ�
	BUFF_TYPE_ATTACK									= 10,									// ������
	BUFF_TYPE_DEFINE									= 11,									// ������
	BUFF_TYPE_HIT_RATIO									= 12,									// ����ֵ
	BUFF_TYPE_AVOIDANCE									= 13,									// �ر�ֵ
	BUFF_TYPE_CRIT_RATE									= 14,									// ����ֵ
	BUFF_TYPE_TENACITY									= 15,									// ����ֵ
	BUFF_TYPE_MOVE_SPEED_RATE							= 16,									// �ƶ�����
	BUFF_TYPE_FLOAT										= 17,									// ������ֵ
	BUFF_TYPE_HIT_DOWN                                  = 18,									// ������ֵ
	BUFF_TYPE_FAINT                                     = 19,									// ѣ��״̬
	BUFF_TYPE_FIX										= 20,									// ����״̬
	BUFF_TYPE_FROZEN									= 21,									// ����״̬
	BUFF_TYPE_ICE_RESIST								= 22,									// ����
	BUFF_TYPE_FIRE_RESIST								= 23,									// ��
	BUFF_TYPE_THUNDER_RESIST							= 24,									// �׿�
	BUFF_TYPE_WIND_RESIST								= 25,									// �翹
	BUFF_TYPE_LIGHT_RESIST								= 26,									// �⿹
	BUFF_TYPE_DARK_RESIST								= 27,									// ����
	BUFF_TYPE_IMMU_ALL									= 28,									// �������м���״̬
	BUFF_TYPE_IMMU_DEBUFF								= 29,									// ����ָ������״̬
	BUFF_TYPE_IMMU_FIX									= 30,									// ���߶���
	BUFF_TYPE_IMMU_FROZEN								= 31,									// ���߱���
	BUFF_TYPE_INVINCIBLE								= 32,									// �޵�״̬
	BUFF_TYPE_PA										= 33,									// ����״̬
	BUFF_TYPE_3                                         = 34,									// ����Buff_3
	BUFF_TYPE_4                                         = 35,									// ����Buff_4
	BUFF_TYPE_5                                         = 36,									// ����Buff_5
	BUFF_TYPE_6                                         = 37,									// ����Buff_6
	BUFF_TYPE_7                                         = 38,									// ����Buff_7
	BUFF_TYPE_8                                         = 39,									// ����Buff_8
	BUFF_TYPE_MAX															  
};

// Buff����Ч��������
enum BUFF_ALL_EFFECT_TYPE
{
	BUFF_ALL_EFFECT_TYPE_BUFF							= 0,									// ����Buff
	BUFF_ALL_EFFECT_TYPE_DEBUFF							= 1,									// ������Buff
	BUFF_ALL_EFFECT_TYPE_ERROR
};


// Buff�Ƿ���Ա��滻
enum BUFF_REPLACE_TYPE
{
	BUFF_REPLACE_TYPE_YES								= 0,									// Buff���Ա��滻
	BUFF_REPLACE_TYPE_NO								= 1,									// Buff�����Ա��滻
	BUFF_REPLACE_TYPE_ERROR
};

// Buff������������Ƿ����ʧ
enum BUFF_PLAYER_DIE_DISAPPEA_TYPE
{
	BUFF_PLAYER_DIE_DISAPPEA_TYPE_YES					= 0,									// Buff��������������ʧ
	BUFF_PLAYER_DIE_DISAPPEA_TYPE_NO					= 1,									// Buff����������󲻻���ʧ
	BUFF_PLAYER_DIE_DISAPPEA_TYPE_ERROR
};

// Buff��ǰ��ʱ������
enum BUFF_CURRENT_TIME_TYPE
{
	BUFF_CURRENT_TIME_TYPE_EFFECTIVE_TIME				= 0,									// BUFF��ǰ�Ĵ�����Чʱ����
	BUFF_CURRENT_TIME_INTERVAL_TIME						= 1,									// BUFF��ǰ�Ĵ��ڼ��ʱ����
	BUFF_CURRENT_TIME_TYPE_ERROR
};

enum BUFF_TARGET
{
    BUFF_AT_ME                                          = 1,                                    //���Լ���buff
    BUFF_AT_ENIMY                                       = 2,                                    //�Եз���buff
    BUFF_AT_FRIENDS                                     = 3,                                    //���ѷ������Լ�
    BUFF_AT_ERROR
};

// Buff��������
typedef struct __BUFF_DATA
{
	int													nBuffIconID;							// Buff��ͼ��ID
	int													nBuffEffectiveTime;						// Buff��Чʱ��
	int													nBuffIntervalTime;						// Buff���ʱ��
	int													nBuffLastTotalTime;						// Buff�ܳ���ʱ��
	
	char												szBuffDescribe[MAX_BUFF_DESCRIBE_SIZE];	// Buff������

	USHORT												byIndexID;								// ����ID

	BUFF_TYPE											eBuffType;								// Buff������
	BUFF_REPLACE_TYPE									eBuffRepalceType;						// Buff�Ƿ���Ա��滻
	BUFF_ALL_EFFECT_TYPE								eBuffAllEffectType;						// Buff����Ч��������

    int                                                 nEffectCount;                           // Ч������
	BUFF_EFFECT_DATA									strBuffEffectData[MAX_EFFECT_COUNT];	// Buff����Ч��������
}BUFF_DATA;
#endif // _BUFF_COMMON_H