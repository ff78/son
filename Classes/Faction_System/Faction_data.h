#ifndef __Faction_CONFIG_DATA_H__
#define __Faction_CONFIG_DATA_H__

#define CREATE_TIME_LEN    64
#define FACTION_MEMBER_MAX    30
#define FACTION_FIGHT_MAX 10
#define FACTION_TOTEMS_MAX 9

#include <map>
#include <vector>
#include "Network_Common/global_macros.h"
#include "Game_Interface/common.h"

enum
{
	FACTION_EMPTY = 0,			// û�й���
	FACTION_MEMBER,				// ��Ա
	FACTION_DEPUTY_LEADER,		// ������
	FACTION_LEADER				// ����
};

enum
{
	FACTION_JOIN_OK = 1,					// �ɹ�
	FACTION_JOIN_FAILURE_BY_FIGHT_NUM,		// ʧ��(ս����)
	FACTION_JOIN_FAILURE_BY_NO_FACTION,		// ʧ��(û���������)
	FACTION_JOIN_FAILURE_BY_SELF,			// ʧ��(���ܼ����Լ��Ĺ���)
	FACTION_JOIN_FAILURE_MAX				// ʧ��(�����Ա����)
};

enum
{
	TOTMES_LIFE = 0,		// ����ͼ��
	TOTMES_ATTACK,			// ����ͼ��
	TOTMES_DEFENSE,			// ����ͼ��
	TOTMES_ICE,				// ��ͼ��
	TOTMES_FIRE,			// ��ͼ��
	TOTMES_THUNDER,			// ��ͼ��
	TOTMES_WIND,			// ��ͼ��
	TOTMES_LIGHR,			// ��ͼ��
	TOTMES_DARK				// ��ͼ��
};


struct faction_member_data
{
	int lv;					// �ȼ�
	int player_id;			// ���ID
	int job;				// ְλ
	int fighting_capacity;	// ս����
	//char name[MAX_NAME_LEN + 1];// ����
	std::string name;
};

struct faction_data_common	// ��������
{
	int  lv;					// ���ᵱǰ�ȼ�
	int  buy_num;				// �����Ա�������
	int  digging_num;			// ÿ���ڿ����
	int  digging_values;		// ÿ���ڿ��õĹ��׶�
	int  digging_active_num;	// ÿ���ڿ��õĻ�Ծ��
	int  worship_num;			// �����ԱĤ�ݴ���
	int  worship_values;		// ÿ��Ĥ�ݻ�õĹ��׶�
	int  worship_active_num;	// Ĥ�ݻ�õĻ�Ծ��
	int  boss_id;				// boss ��ID
	int  boss_num;				// BOSS��ս����
	int  boss_kill;				// BOSS��ɱ����(��ǿ��)
	int  kill_boss_active_num;	// ��ɱBOSS��õĻ�Ծ��
	int  kill_boss_values;		// ��ɱBOSS��õĹ��׶�
	int  level_exp;				// ������������
	int  totems_max;			// ͼ����ߵȼ�

	int totems_lv[FACTION_TOTEMS_MAX];		// ͼ����������	
	int totoems_num[FACTION_TOTEMS_MAX];	// ͼ�ڸ��ӵ���ֵ
	/*
	int  totems_life_lv;		// ����ͼ����������	
	int  totems_life_num;		// ����ͼ�ڸ��ӵ���ֵ
	int  totems_attack_lv;      // ����ͼ����������	
	int  totems_attack_num;		// ����ͼ�ڸ��ӵ���ֵ
	int  totems_defense_lv;		// ����ͼ����������	
	int  totems_defense_num;	// ����ͼ�ڸ��ӵ���ֵ
	int  totems_ice_lv;			// ��ͼ����������
	int  totems_ice_num;		// ��ͼ�ڸ��ӵ���ֵ
	int  totems_fire_lv;		// ��ͼ����������
	int  totems_fire_num;		// ��ͼ�ڸ��ӵ���ֵ
	int  totems_thunder_lv;		// ��ͼ����������
	int  totems_thunder_num;	// ��ͼ�ڸ��ӵ���ֵ
	int  totems_wind_lv;		// ��ͼ����������
	int  totems_wind_num;		// ��ͼ�ڸ��ӵ���ֵ
	int  totems_light_lv;		// ��ͼ����������
	int  totems_light_num;		// ��ͼ�ڸ��ӵ���ֵ
	int  totems_dark_lv;		// ��ͼ����������
	int  totems_dark_num;		// ��ͼ�ڸ��ӵ���ֵ*/
};

struct create_faction	// ������������
{
	int  level;		// �ȼ�
	int  gold;		// ��Ǯ
	int  token;		// Ԫ��
};

struct faction_data_DB
{
	faction_data_DB()
	{
		reset();
	}

	~faction_data_DB(){}

	void reset()
	{
		faction_level = 1;
		curr_exp = 0;
		faction_name.clear();
		msg_board.clear();
		notice.clear();
		join_fighting_capacity = 0;
		member_list.clear();
		boss_id = 0;
		active_num = 0;
		boss_kill_num = 0;
		owner_id = 0;
		::memset(curr_totems_lv, 0, sizeof(curr_totems_lv));
	}

	int id;												// ����ID
	int faction_level;									// ����ȼ�
	int curr_exp;										// ��ǰ���ᾭ��
	std::string faction_name;							// ��������
	std::string msg_board;								// ���԰�
	std::string notice;									// ���ṫ��
	int join_fighting_capacity;							// ���빤��ս����(����)
	vector<faction_member_data*>		member_list;	// ��Ա�б�
	int boss_id;										// ��ǰBOSS��id
	int active_num;										// �����Ծ��
	int boss_kill_num;									// ��ǰBOSS����ɱ����
	int owner_id;										// ӵ����ID(����)

	int curr_totems_lv[FACTION_TOTEMS_MAX];		// ͼ�ڵȼ�

	/*
	int curr_totems_life;		// ����ͼ�ڵȼ�
	int curr_totems_attack;		// ����ͼ�ڵȼ�
	int curr_totems_defense;	// ����ͼ�ڵȼ�
	int curr_totems_ice;		// ��ͼ�ڵȼ�
	int curr_totems_fire;		// ��ͼ�ڵȼ�
	int curr_totems_thunder;	// ��ͼ�ڵȼ�
	int curr_totems_wind;		// ��ͼ�ڵȼ�
	int curr_totems_light;		// ��ͼ�ڵȼ�
	int curr_totems_dark;		// ��ͼ�ڵȼ�*/
};

typedef map<int, faction_data_common*>	faction_config_map;

typedef map<int, faction_data_DB*>		faction_Mgr_map_by_id;

typedef map<std::string, faction_data_DB*> faction_Mgr_map_by_name;

typedef map<int, std::vector<faction_data_DB*>>	faction_fight_mgr_by_id;

#endif