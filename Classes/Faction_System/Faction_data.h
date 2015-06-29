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
	FACTION_EMPTY = 0,			// 没有工会
	FACTION_MEMBER,				// 成员
	FACTION_DEPUTY_LEADER,		// 副帮主
	FACTION_LEADER				// 帮主
};

enum
{
	FACTION_JOIN_OK = 1,					// 成功
	FACTION_JOIN_FAILURE_BY_FIGHT_NUM,		// 失败(战斗力)
	FACTION_JOIN_FAILURE_BY_NO_FACTION,		// 失败(没有这个工会)
	FACTION_JOIN_FAILURE_BY_SELF,			// 失败(不能加入自己的工会)
	FACTION_JOIN_FAILURE_MAX				// 失败(工会成员已满)
};

enum
{
	TOTMES_LIFE = 0,		// 生命图腾
	TOTMES_ATTACK,			// 攻击图腾
	TOTMES_DEFENSE,			// 防御图腾
	TOTMES_ICE,				// 冰图腾
	TOTMES_FIRE,			// 火图腾
	TOTMES_THUNDER,			// 雷图腾
	TOTMES_WIND,			// 风图腾
	TOTMES_LIGHR,			// 光图腾
	TOTMES_DARK				// 暗图腾
};


struct faction_member_data
{
	int lv;					// 等级
	int player_id;			// 玩家ID
	int job;				// 职位
	int fighting_capacity;	// 战斗力
	//char name[MAX_NAME_LEN + 1];// 名字
	std::string name;
};

struct faction_data_common	// 工会数据
{
	int  lv;					// 工会当前等级
	int  buy_num;				// 工会成员购买次数
	int  digging_num;			// 每日挖矿次数
	int  digging_values;		// 每次挖矿获得的贡献度
	int  digging_active_num;	// 每次挖矿获得的活跃度
	int  worship_num;			// 工会成员膜拜次数
	int  worship_values;		// 每次膜拜获得的贡献度
	int  worship_active_num;	// 膜拜获得的活跃度
	int  boss_id;				// boss 的ID
	int  boss_num;				// BOSS挑战次数
	int  boss_kill;				// BOSS击杀次数(被强化)
	int  kill_boss_active_num;	// 击杀BOSS获得的活跃度
	int  kill_boss_values;		// 击杀BOSS获得的贡献度
	int  level_exp;				// 工会升级经验
	int  totems_max;			// 图腾最高等级

	int totems_lv[FACTION_TOTEMS_MAX];		// 图腾升级消耗	
	int totoems_num[FACTION_TOTEMS_MAX];	// 图腾附加的数值
	/*
	int  totems_life_lv;		// 生命图腾升级消耗	
	int  totems_life_num;		// 生命图腾附加的数值
	int  totems_attack_lv;      // 攻击图腾升级消耗	
	int  totems_attack_num;		// 攻击图腾附加的数值
	int  totems_defense_lv;		// 防御图腾升级消耗	
	int  totems_defense_num;	// 防御图腾附加的数值
	int  totems_ice_lv;			// 冰图腾升级消耗
	int  totems_ice_num;		// 冰图腾附加的数值
	int  totems_fire_lv;		// 火图腾升级消耗
	int  totems_fire_num;		// 火图腾附加的数值
	int  totems_thunder_lv;		// 雷图腾升级消耗
	int  totems_thunder_num;	// 雷图腾附加的数值
	int  totems_wind_lv;		// 风图腾升级消耗
	int  totems_wind_num;		// 风图腾附加的数值
	int  totems_light_lv;		// 光图腾升级消耗
	int  totems_light_num;		// 光图腾附加的数值
	int  totems_dark_lv;		// 暗图腾升级消耗
	int  totems_dark_num;		// 暗图腾附加的数值*/
};

struct create_faction	// 创建工会条件
{
	int  level;		// 等级
	int  gold;		// 金钱
	int  token;		// 元宝
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

	int id;												// 工会ID
	int faction_level;									// 工会等级
	int curr_exp;										// 当前工会经验
	std::string faction_name;							// 工会名称
	std::string msg_board;								// 留言板
	std::string notice;									// 工会公告
	int join_fighting_capacity;							// 加入工会战斗力(限制)
	vector<faction_member_data*>		member_list;	// 成员列表
	int boss_id;										// 当前BOSS的id
	int active_num;										// 工会活跃度
	int boss_kill_num;									// 当前BOSS被击杀次数
	int owner_id;										// 拥有者ID(帮主)

	int curr_totems_lv[FACTION_TOTEMS_MAX];		// 图腾等级

	/*
	int curr_totems_life;		// 生命图腾等级
	int curr_totems_attack;		// 攻击图腾等级
	int curr_totems_defense;	// 防御图腾等级
	int curr_totems_ice;		// 冰图腾等级
	int curr_totems_fire;		// 火图腾等级
	int curr_totems_thunder;	// 雷图腾等级
	int curr_totems_wind;		// 风图腾等级
	int curr_totems_light;		// 光图腾等级
	int curr_totems_dark;		// 暗图腾等级*/
};

typedef map<int, faction_data_common*>	faction_config_map;

typedef map<int, faction_data_DB*>		faction_Mgr_map_by_id;

typedef map<std::string, faction_data_DB*> faction_Mgr_map_by_name;

typedef map<int, std::vector<faction_data_DB*>>	faction_fight_mgr_by_id;

#endif