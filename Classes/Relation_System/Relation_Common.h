/* -------------------------------------------------------------------------
//	文件名		：	Relation_Common.h
//	功能描述	：	用于存放Relation的公共数据
// -----------------------------------------------------------------------*/

#ifndef _RELATION_COMMON_H
#define _RELATION_COMMON_H

#include <map>
#include "Network_Common/global_macros.h"

#define  MAX_OWN_FRIEND_COUNT		30         // 最大的已有好友个数
#define  MAX_APPLY_FRIEND_COUNT		30		   // 最大的被申请的好友个数

// 请求添加返回类型
enum ADD_RETURN_TYPE
{
	ART_FAILD			= 0,
	ART_SUCCESS			= 1,
	ART_NOT_ONLINE		= 2,
	ART_LIST_FULL		= 3,
	ART_ALREADY_FRIENDS = 4,
	ART_IN_BLACK_LIST	= 5,
	ART_ADD_SELF		= 6,
};

// 朋友列表类型
enum FRIEND_LIST_TYPE
{
	FRIEND_LIST_TYPE_OWN	= 0,			   // 已有的朋友列表
	FRIEND_LIST_TYPE_APPLY	= 1,			   // 被申请的朋友列表
	FRIEND_LIST_TYPE_ERROR
};

// 当前的好友界面类型
enum CURRENT_FRIEND_LAYER_STATE
{
	CURRENT_FRIEND_LAYER_STATE_OWN		= 0,	// 当前是界面状态是已有的好友界面状态
	CURRENT_FRIEND_LAYER_STATE_APPLY	= 1,	// 当前是界面状态是申请的好友界面状态
	CURRENT_FRIEND_LAYER_STATE_ERROR
};

// 关系类型
enum RELATION_TYPE
{
	RT_NONE								= 0,	// 错误类型
	RT_FRIEND							= 1,	// 好友列表
	RT_APPLY							= 2		// 申请列表
};

struct Relation_Data
{
	uint64				db_id_;					// 数据库主键
	int					role_id_;				// 角色ID
	int					friend_role_id_;		// 好友角色Id
	char				name_[MAX_NAME_LEN + 1];// 角色名字
	int					level_;					// 等级
	int					menpai_id_;				// 门派
	int					general_id_;			// 副将Id()
	int					type_;					// 关系(1好友 2黑名单)
	int					is_online_;				// 是否在线(0 不在线 1在线)
	int					sex_;					// 角色性别
	int					zhanli_;				// 战斗力
	int					nVipLevel;				// Vip等级
	int					nJob;					// 职业


	RELATION_TYPE	   eFriendType;				// 好友类型
};

// 目标好友的显示信息
typedef struct _TARGET_FRIEND_INFO_FOR_SHOW
{
	int								nFriendLevel;															// 好友等级
	int								nFriendFighttingPower;													// 好友战斗力

    std::string						szFriendName;                                                           // 好友名字
    std::string						szFriendJobName;                                                        // 好友职业名字
}TARGET_FRIEND_INFO_FOR_SHOW;
#endif // _RELATION_COMMON_H