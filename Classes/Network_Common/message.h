// -*- C++ -*-


#ifndef MESSAGE_H_
#define MESSAGE_H_

// client message recogn
enum
{
    CLIENT_AUTH_SESSION = 100000,
    CLIENT_CREATE_ROLE,
    CLIENT_DELETE_ROLE,
    CLIENT_START_GAME,
    CLIENT_STOP_GAME,
    CLIENT_ENTER_SCENE,
};

#define CLIENT_SAVE_PLAYER               100008
#define CLIENT_LOAD_INFO                100009
#define CLIENT_LIFE_INIT                100010
#define CLIENT_INVITE_PROBE             100105
#define CLIENT_RESPOND_PROBE            100106
#define CLIENT_ROLE_RELIVE              100107

#define CLIENT_ON_HOOK_SET              101301
#define CLIENT_ON_HOOK_START            101302
#define CLIENT_ON_HOOK_STOP             101303
#define CLIENT_ON_HOOK_INFO             101304

//Instance system
#define CLIENT_INSTANCE_REQUIRE         101400
#define CLIENT_INSTANCE_RESULT          101401
#define CLIENT_INSTANCE_FINISHI         101402
#define CLIENT_REQUIRE_STAGE_INSTANCE_STATE 101403
#define CLIENT_REQUIRE_STAGE            101404
#define CLIENT_BEGIN_INSTANCE_TIMER     101405
#define CLIENT_INSTANCE_PLAYER_DIE      101406
#define CLIENT_INSTANCE_SWEEP           101407
#define CLIENT_REQUIRE_STAGE_ALL		101408
#define CLIENT_INSTANCE_NEXT			101409

//Quest System
#define CLIENT_QUEST_ACCEPT_QUEST       101500
#define CLIENT_QUEST_SUBMIT_QUEST       101501
#define CLIENT_QUEST_GIVEUP_QUEST       101502
#define CLIENT_REQUIRE_NPC_QUEST_LIST   101503
#define CLIENT_QUEST_SEARCH             101504
#define CLIENT_QUEST_NPC_CHALLENGE      101505
#define CLIENT_QUEST_NPC_DIALOGTO       101506
#define CLIENT_QUEST_GIVE_ITEM_TO_NPC   101507
#define CLIENT_REQUIRE_QUEST_LIST       101508

//monster system
#define CLIENT_MONSTER_KILL             101509

// player
enum 
{
    C2S_GET_MAIN_CITY_PLAYER = 101601,
	C2S_PLAYER_INTO_MAIN_CITY,
    C2S_PLAYER_MOVE,
    C2S_GET_PLAYER_INFO,
    C2S_PLAYER_CHAT,
    C2S_GM_COMMAND,
    C2S_PLAYER_REVIVE,
    C2S_PLAYER_BUY_ENERGY,
	C2S_PLAYER_QUALITY_UP,
	C2S_COLLIDED_SOMETHING,
	C2S_USEITEM_SOMETHING,
};

// item
enum 
{
    C2S_LOAD_ITEM = 101701,
    C2S_LOAD_MATERIAL_FRAGMENT,
    C2S_LOAD_BOOK_FRAGMENT,
    C2S_TIDY_ITEM,
    C2S_EQUIP_EQUIPMENT,
    C2S_TAKE_OFF_EQUIPMENT,
    C2S_EQUIP_BOOK,
    C2S_TAKE_OFF_BOOK,
    C2S_EQUIPMENT_LEVEL_UP,
    C2S_EQUIPMENT_QUALITY_UP,
    C2S_BOOK_LEVEL_UP,
    C2S_BOOK_QUALITY_UP,
    C2S_SELL_ITEM,
    C2S_COMPOUND_MATERIAL_FRAGMENT,
    C2S_COMPOUND_BOOK_FRAGMENT,
    C2S_USE_ITEM,
    C2S_SET_ON_GEM,
    C2S_SET_OFF_GEM,
    C2S_GEM_LEVEL_UP,
};

// item_container
enum 
{
    C2S_LOAD_ITEM_CONTAINER = 101801,
    C2S_ADD_ITEM_CONTAINER,
};

// skill
enum 
{
    CS_UPLEVEL_SKILL = 101901,
    CS_LOAD_SKILL,
	CS_CHANGE_SELECT_SKILL,
};

// shop
enum 
{
    CS_LOAD_SHOPING_RECORD = 102001,
    CS_BUY_ITEM,
};

// deputy_general
enum
{
	CS_LOAD_DEPUTY_GENERAL   = 102101,
	CS_DEPUTY_GENERAL_FIGHT,
	CS_DEPUTY_GENERAL_CANCEL_FIGHT,
};

// relation
enum
{
	CS_APPLY_FRIEND = 102201,
    CS_ADD_FRIEND ,
    CS_DEL_FRIEND,
	CS_DEL_APPLY_FRIEND,
    CS_ASK_FRIEND_INFO,
    CS_ASK_FRIEND_LIST,
	CS_ON_LOAD_DATA,
};

// offline_fight
enum 
{
    C2S_LOAD_OFFLINE_FIGHT = 102301,
    C2S_OFFLINE_FIGHT_START,
    C2S_OFFLINE_FIGHT_FINISH,
    C2S_PLAYER_BUY_OFFLINE_FIGHT_COUNT,
    C2S_GET_OFFLINE_FIGHT_RANK_REWARD,
};

// acupoint
enum 
{
    C2S_LOAD_ACUPOINT = 102401,
    C2S_OPEN_ACUPOINT,
};

//public annoucement
enum 
{
	C2S_ASK_PUBLIC_ANNOUCEMENT = 102501,
};

// cool_time
enum 
{
    C2S_LOAD_COOL_TIME = 102601,
    C2S_CLEAN_COOL_TIME,
};

// Partition server list
enum
{
	C2S_ASK_PARTITION_SERVER_LIST = 102701,
};

// Reward system
enum
{
	C2S_ASK_EXCHANGE_CODE_REWARD = 102801,
};

// Reward system
enum
{
	C2S_EXCHANGE_TOKEN_TO_GOLD = 102901,
};

// Online system
enum
{
	C2S_LOAD_ONLINE_FIGHT = 103001,
	C2S_ONLINE_FIGHT_START,
	C2S_ONLINE_FIGHT_FINISH,
	C2S_ONLINE_FIGHT_MOVE,
	C2S_ONLINE_FIGHT_USE_SKILL,
	C2S_ONLINE_FIGHT_RESULT,
};

// rank
enum 
{
    C2S_LOAD_RANK = 103101,
    C2S_LOAD_RANK_ROLE_LEVEL,
    C2S_LOAD_RANK_ROLE_FIGHTING_CAPACITY,
    C2S_LOAD_RANK_ROLE_HAVE_GOLD,
	C2S_LOAD_RANK_ROLE_PRESTIGE,
	C2S_LOAD_RANK_ROLE_ARENA,
};

// rank
enum 
{
    C2S_LOAD_LOGIN_REWARD = 103201,
    C2S_GET_LOGIN_REWARD,
};

// all server radiate
enum 
{
	INNER_RADIATE_SYSTEM = 103301,		// 系统触发的广播
	INNER_RADIATE_PLAYER,				// 玩家行为触发的广播
};

// activity
enum 
{
    C2S_LOAD_ACTIVITY_RECORD = 103401,
    C2S_ACTIVITY_SIX_SECT,
};
  
// daily_task
enum 
{
    C2S_LOAD_DAILY_TASK = 103501,
    C2S_DROP_DAILY_TASK,
    C2S_SUBMIT_DAILY_TASK,
    C2S_REFRESH_DAILY_TASK_STAR_LEVEL,
    C2S_SET_DAILY_TASK_STAR_LEVEL_MAX,
    C2S_TOKEN_COMPLETE_DAILY_TASK,
    C2S_GET_DAILY_TASK_GIFT_ONE,
    C2S_GET_DAILY_TASK_GIFT_TWO,
    C2S_GET_DAILY_TASK_GIFT_THREE,
};

//  chat system
enum
{
	C2S_CHAT_AREA_MSG = 104001,		// 区域聊天
	C2S_CHAT_PRIVATE_MSG,			// 私聊
	C2S_CHAT_TEAM_MSG ,				// 组队聊天
	C2S_CHAT_FRIEND_MSG,			// 好友聊天
	C2S_CHAT_FACTION_MSG,			// 工会（帮派）聊天
	C2S_CHAT_WORLD_MSG,				// 世界聊天
};

// friend system
enum
{
	C2S_ON_LOAD_FRIEND = 104501,		// 获得好友信息
	C2S_APPLY_ADD_FRIEND,				// 申请添加好友
	C2S_ADD_FRIEND_OK,					// 添加好友成功
	C2S_ADD_FRIEND_REFUSE,				// 添加好友失败(拒绝)
	C2S_DEL_FRIEND,						// 删除好友
	C2S_ADD_BLACK_LIST,					// 添加黑名单数据
	C2S_DEL_BLACK_LIST,					// 删除黑名单数据
};

// faction system
enum
{
	C2S_CREATE_FACTION = 104701,		// 创建工会
	C2S_JOIN_FACTION,					// 加入工会
	C2S_SET_JOB_FACTION,				// 设置工会职位
	C2S_KICK_MEMBER_FACTION,			// 踢人
	C2S_TOTEMS_UP_FACTION,				// 图腾升级
	C2S_SET_MSG_BOARD_FACTION,			// 设置留言板
	C2S_FACTION_DIGGIN,					// 挖矿
	C2S_FACTION_WORSHIP,				// 膜拜
	C2S_FACTION_DEKARON_BOSS,			// 挑战工会BOSS
	C2S_FACTION_KILL_BOSS,				// 击杀工会BOSS
	C2S_FACTION_FIND_BY_NAME,			// 搜索帮派(名称)
	C2S_GET_FACTION_DATA,				// 申请获得帮派数据
	
};

// email system
enum
{
	C2S_ON_LOAD_EMAIL = 104801,			// 获得当前的邮件数据(玩家自身)
	C2S_SEND_EMAIL,						// 发送邮件
	C2S_RECEIVE_EMAIL_ITEM,				// 获得邮件里的道具
	C2S_OPEN_EMAIL,						// 打开邮件
	C2S_DELETE_EMAIL,					// 删除邮件
};

// guard_beast
enum
{
	C2S_GUARD_BEAST_LV_UP = 104901,		// 守护兽升级
	C2S_GUARD_BEAST_CHANGE_STATE,		// 守护兽改变状态
};

// god weapon
enum
{
	C2S_GOD_WEAPON_LEVEL_UP = 105001,	// 神兵升级
};

// inner server msg
#define INNER_ENGINE_LOGIN              200000
#define INNER_AUTH_GE_KEY               200001
#define INNER_PLAYER_LOGIN              200002
#define INNER_PLAYER_LOGOUT             200003  // engine notify gate role exit world
#define GATE_TO_GM_GATEID               200004  // geta serverID(GM服务器用于区分)
#define PT_PLAYER_LOGOUT                1
#define PT_PLAYER_CROSS_SVC             2
#define INNER_KICK_OUT_PLAYER           200004  // gate notify engine to kick out player
#define MESSAGE_FORWARD_FROM_GT         200005  // 
#define GE_GT_TRANSFER_MSG              200006  // 
#define INNER_LOAD_TEAM_INFO            200020
#define INNER_CREATE_TEAM               200021
#define INNER_CHANGE_AC_SETTING         200022
#define INNER_LOAD_BEAST_INFO           200023
#define INNER_UPDATE_BEAST_INFO         200024  // add by sheldon 
#define INNER_PUBLISH_TIPS				200025  // 发布公告
#define INNER_QUERY_TIPS				200026  // 查询公告
#define INNER_CHANGE_TIPS				200027	// 修改公告
#define INNER_PLAYER_ENTER_BATTLE       200028
#define INNER_PLAYER_LEAVE_BATTLE       200029
#define INNER_REFRESH_DAILY_DATA        200030  // 零点刷新
#define INNER_UPDATE_GAME_SERVER_PLAYER_LIST 200031 //when reconnect to gate server send player id list to gate
#define INNER_PAYMENT_MONEY				200032

#define UPDATE_MONEY                    200100  // 
#define UPDATE_ITEMS                    200101  // 
#define ADDICTED_OFFLINE                200102
#define PLAYER_MODIFY_EXP               200104
#define PLAYER_MODIFY_PERSONAL_EXP      200105
#define AUTO_INSERT_DROPPED_ITEM        200106
#define PLAYER_KILL_MONSTER             200107
#define PLAYER_DEAD                     200108
#define NOTIFY_PLAYER_REMOVE_ITEM		200109
#define PLAYER_COLLECT				    200110
#define NOTIFY_PLAYER_REMOVE_ITEM_WITHOUT_AMOUNT 200111

#define DEMISE_LEADER_TO_ME             200200
#define DEMISE_LEADER_OK                200201

#define NOTIFY_PLAYER_SEND_ITEM_CONTAINER 200300
#define NOTIFY_PLAYER_SEND_SKILL_LIST   200301
#define NOTIFY_PLAYER_SEND_INSTANCE_RESULT 200302

#define INNER_ACTIVE_CLOSE              200900

// GM COMMAND
#define CLIENT_GM_COMMAND               300000

// server return recogn
#define RETURN_AUTH_SESSION             500000
#define RETURN_ENTER_GAME               500001
#define RETURN_CREATE_ROLE              500002
#define RETURN_DELETE_ROLE              500003
#define RETURN_START_GAME               500004
#define RETURN_STOP_GAME                500005
#define RETURN_ENTER_SCENE              500006
#define RETURN_LINE_DETAIL              500031
#define RETURN_SELECT_LINE              500032
#define RETURN_MOVE_ACTION              500101
#define RETURN_MAP_TRANSFER             500102
#define RETURN_INVITE_PROBE             500105
#define RETURN_RESPOND_PROBE            500106
#define RETURN_ROLE_RELIVE              500107
#define RETURN_POST_LIST                500131
#define RETURN_POST_SCENE               500132
#define RETURN_SCENE_INFO_O             500133
#define RETURN_PUBLISH_TIPS				500151
#define RETURN_DROP_PACKAGE             500190
#define RETURN_ROLE_DETAILS             500201
#define RETURN_ROLE_PROPERTY_M          500202
#define RETURN_ROLE_LABELS              500203
#define RETURN_ROLE_LABEL_C             500204
#define RETURN_ROLE_INTRO_M             500205
#define RETURN_ROLE_PK_C                500206
#define RETURN_ROLE_SKILLS              500207
#define RETURN_PROMOTE_SKILL            500208
#define RETURN_OTHER_ROLE_INFO          500240
#define RETURN_OTHER_ROLE_DETAIL        500241
#define RETURN_TAKEDOWN_EQUIP           500251
#define RETURN_REPLACE_EQUIP            500252
#define RETURN_SET_SYSTEM_SETTINGS      500253
#define RETURN_GET_SYSTEM_SETTINGS      500254

//error msg
#define RETURN_ERROR_MESSAGE            500300

//instance 
#define RETURN_INSTANCE_REQ             500400
#define RETURN_INSTANCE_RESULT          500401
#define RETURN_INSTANCE_MONSTER         500402
#define RETURN_INSTANCE_SCENE           500403
#define RETURN_INSTANCE_FINISH          500404
#define RETURN_REQUIRE_STAGE_INSTANCE_STATE 500405
#define RETURN_INSTANCE_PROGRESS        500406
#define RETURN_INSTANCE_SWEEP           500407

#define RETURN_REQUIRE_STAGE            500546
#define RETURN_REQUIRE_STAGE_ALL        500547
#define RETURN_INSTANCE_NEXT			500548

//quest
#define RETURN_QUEST_UPDATE             500500
#define RETURN_NPC_QUEST_BIND_LIST      500501
#define RETURN_QUEST_SUBMIT_RESULT      500502


// player
enum 
{

    S2C_GET_MAIN_CITY_PLAYER = 500601,
    S2C_PLAYER_MOVE,
    S2C_LOAD_PLAYER_RES,
    S2C_GET_PLAYER_INFO,
    S2C_PLAYER_CHAT,
    S2C_GM_COMMAND,
    S2C_PLAYER_REVIVE,
    S2C_PLAYER_BUY_ENERGY,
	S2C_PLAYER_QUALITY_UP,
	S2C_COLLIDED_SOMETHING,

    S2C_PLAYER_INTO_MAIN_CITY = 500651,
    S2C_PLAYER_QUIT_MAIN_CITY,
    S2C_CHANGE_GOLD,
    S2C_CHANGE_EXP,
    S2C_CHANGE_ENERGY,
    S2C_CHANGE_TOKEN,
    S2C_ADD_RECHARGE_TOKEN,
    S2C_CHANGE_PRESTIGE,
};

// item
enum 
{
    S2C_LOAD_ITEM = 500701,
    S2C_LOAD_MATERIAL_FRAGMENT,
    S2C_LOAD_BOOK_FRAGMENT,
    S2C_TIDY_ITEM,
    S2C_EQUIP_EQUIPMENT,
    S2C_TAKE_OFF_EQUIPMENT,
    S2C_EQUIP_BOOK,
    S2C_TAKE_OFF_BOOK,
    S2C_EQUIPMENT_LEVEL_UP,
    S2C_EQUIPMENT_QUALITY_UP,
    S2C_BOOK_LEVEL_UP,
    S2C_BOOK_QUALITY_UP,
    S2C_SELL_ITEM,
    S2C_COMPOUND_MATERIAL_FRAGMENT,
    S2C_COMPOUND_BOOK_FRAGMENT,
    S2C_USE_ITEM,
    S2C_SET_ON_GEM,
    S2C_SET_OFF_GEM,
    S2C_GEM_LEVEL_UP,

    S2C_CREATE_ITEM = 500751,
    S2C_CREATE_MATERIAL_FRAGMENT,
    S2C_CREATE_BOOK_FRAGMENT,
    S2C_ITEM_CLIENT_SHOW,
};

// item_container
enum 
{
    S2C_LOAD_ITEM_CONTAINER = 500801,
    S2C_ADD_ITEM_CONTAINER,

    S2C_UPDATE_ITEM_CONTAINER = 500851,
};

// skill
enum 
{
    SC_UPLEVEL_SKILL = 500901,
    SC_LOAD_SKILL,
	SC_CHANGE_SELECT_SKILL,

    SC_CREATE_SKILL = 500951,
};

// shop
enum 
{
    SC_LOAD_SHOPING_RECORD = 501001,
    SC_BUY_ITEM,
};

// deputy_general
enum
{
	SC_LOAD_DEPUTY_GENERAL = 501101,
	SC_DEPUTY_GENERAL_FIGHT,
	SC_DEPUTY_GENERAL_CANCEL_FIGHT,

    SC_CREATE_DEPUTY_GENERAL = 501151,
};

// relation
enum
{
	SC_ADD_FRIEND = 501201,
	SC_ALLPY_FRIEND_DATA,
	SC_DEL_FRIEND,
	SC_DEL_APPLY_FRIEND,
	SC_ASK_FRIEND_INFO,
	SC_ASK_FRIEND_LIST,
	SC_ON_LOAD_RELATION_DATA,
};

// offline_fight
enum 
{
    S2C_LOAD_OFFLINE_FIGHT = 501301,
    S2C_OFFLINE_FIGHT_START,
    S2C_OFFLINE_FIGHT_FINISH,
    S2C_PLAYER_BUY_OFFLINE_FIGHT_COUNT,
    S2C_GET_OFFLINE_FIGHT_RANK_REWARD,

    S2C_GET_OFFLINE_FIGHT_RANK_REWARD_REMAINING_TIME = 501351,
};

// offline_fight
enum 
{
	S2C_LOAD_ONLINE_FIGHT = 501361,
	S2C_ONLINE_FIGHT_START,
	S2C_ONLINE_FIGHT_FINISH,
	S2C_ONLINE_FIGHT_MOVE,
	S2C_ONLINE_FIGHT_USE_SKILL,
	S2C_ONLINE_FIGHT_RESULT,
};

// acupoint
enum 
{
    S2C_LOAD_ACUPOINT = 501401,
    S2C_OPEN_ACUPOINT,

    S2C_CREATE_ACUPOINT = 501451,
};

// public annoucement
enum
{
	S2C_ASK_PUBLIC_ANNOUCEMENT = 501501,
};

// acupoint
enum 
{
    S2C_LOAD_COOL_TIME = 501601,
    S2C_CLEAN_COOL_TIME,

    S2C_CREATE_COOL_TIME = 501651,
};

// Partition server list
enum
{
	S2C_ASK_PARTITION_SERVER_LIST = 501701,
};

// Exchange code
enum
{
	S2C_ASK_EXCHANGE_CODE_INFO = 501801,
};

// Banks system
enum
{
	S2C_EXCHANGE_TOKEN_TO_GOLD = 501901,
};

// rank
enum 
{
    S2C_LOAD_RANK = 502001,
    S2C_LOAD_RANK_ROLE_LEVEL,
    S2C_LOAD_RANK_ROLE_FIGHTING_CAPACITY,
    S2C_LOAD_RANK_ROLE_HAVE_GOLD,
	S2C_LOAD_RANK_ROLE_PRESTIGE,
	S2C_LOAD_RANK_ROLE_ARENA,
};

// rank
enum 
{
    S2C_LOAD_LOGIN_REWARD = 502101,
    S2C_GET_LOGIN_REWARD,
};

// radiate
enum 
{
	S2C_RADIATE_SYSTEM = 502201,
	S2C_RADIATE_PLAYER,
};

// activity
enum 
{
    S2C_LOAD_ACTIVITY_RECORD = 502301,
    S2C_ACTIVITY_SIX_SECT,
};

// daily_task
enum 
{
    S2C_LOAD_DAILY_TASK = 502401,
    S2C_DROP_DAILY_TASK,
    S2C_SUBMIT_DAILY_TASK,
    S2C_REFRESH_DAILY_TASK_STAR_LEVEL,
    S2C_SET_DAILY_TASK_STAR_LEVEL_MAX,
    S2C_TOKEN_COMPLETE_DAILY_TASK,
    S2C_GET_DAILY_TASK_GIFT_ONE,
    S2C_GET_DAILY_TASK_GIFT_TWO,
    S2C_GET_DAILY_TASK_GIFT_THREE,

    S2C_UPDATE_DAILY_TASK_PROGRESS = 502451,
};

//  chat system
enum
{
	S2C_CHAT_AREA_MSG = 502601,		// 区域聊天
	S2C_CHAT_PRIVATE_MSG,			// 私聊
	S2C_CHAT_TEAM_MSG,				// 组队聊天
	S2C_CHAT_FRIEND_MSG,			// 好友聊天
	S2C_CHAT_FACTION_MSG,			// 工会（帮派）聊天
	S2C_CHAT_WORLD_MSG,				// 世界聊天
};

// friend system
enum
{
	S2C_ON_LOAD_FRIEND = 502801,		// 获得好友信息
	S2C_APPLY_ADD_FRIEND,				// 申请添加好友
	S2C_ADD_FRIEND_OK,					// 添加好友成功
	S2C_ADD_FRIEND_REFUSE,				// 添加好友失败(拒绝)
	S2C_DEL_FRIEND,						// 删除好友
	S2C_ADD_BLACK_LIST,					// 添加黑名单数据
	S2C_DEL_BLACK_LIST,					// 删除黑名单数据
};

// faction system
enum
{
	S2C_CREATE_FACTION = 502901,		// 创建工会
	S2C_JOIN_FACTION,					// 加入工会
	S2C_SET_JOB_FACTION,				// 设置工会职位
	S2C_SET_NOTICE_FACTION,				// 设置工会公告
	S2C_SET_JOIN_LINMIT_FACTION,		// 设置工会加入条件(战斗力)
	S2C_SET_TOTEMS_UP_FACTION,			// 升级工会图腾等级
	S2C_KICK_MEMBER_FACTION,			// 踢人
	S2C_SET_MSG_BOARD_FACTION,			// 设置留言板
	S2C_FACTION_DIGGIN,					// 挖矿
	S2C_FACTION_WORSHIP,				// 膜拜
	S2C_FACTION_DEKARON_BOSS,			// 挑战工会BOSS
	S2C_FACTION_KILL_BOSS,				// 击杀工会BOSS
	S2C_FACTION_FIND_BY_NAME,			// 查找帮派
	S2C_GET_FACTION_DATA,				// 获得帮派数据
};

// email
enum
{
	S2C_ON_LOAD_EMAIL = 503001,			// 获得当前的邮件数据
	S2C_SEND_EMAIL_BY_SELF,				// 玩家主动发送邮件（是否成功）
	S2C_SEND_EMAIL_BY_TARGET,			// 玩家收到邮件（收件人，被动触发，由服务器主动发送）
	S2C_SEND_RECEIVE_EMAIL_ITEM,		// 获得邮件里的道具
	S2C_SEND_OPEN_EMAIL,				// 打开邮件
	S2C_SEND_DELETE_EMAIL,				// 删除邮件
};

// guard_beast
enum
{
	S2C_ADD_GUARD_BEAST = 504001,		// 添加新的守护兽
	S2C_GUARD_BEAST_LV_UP,				// 守护兽升级
	S2C_GUARD_BEAST_STATE_CHANGE,				// 守护兽状态改变
};

// god weapon
enum
{
	S2C_ADD_GOD_WEAPON = 504101,		// 添加神兵
	S2C_GOD_WEAPON_LEVEL_UP,
};

// inner server respond
#define INNER_RET_GE_LOGIN              700000
#define INNER_RET_AUTH_GE_KEY           700001
#define INNER_RET_PLAYER_LOGIN          700002
#define INNER_RET_KICK_OUT_PLAYER       700004  // 
#define INNER_RET_LOAD_TEAM_INFO        700020
#define INNER_RET_BEAST_INFO            700023

#define INNER_RET_SOCIAL_LIST           700308

#define INNER_RELATION_APPLY_FRIEND		700401
#define INNER_RELATION_ASK_FRIEND_LIST	700402

#define INNER_RELATION_IS_ON_LINE		700403

// offline fight---------begin
#define INNER_LOAD_OFFLINE_FIGHT		        700501
#define INNER_OFFLINE_FIGHT_START		        700502
#define INNER_OFFLINE_FIGHT_FINISH		        700503
#define INNER_OFFLINE_FIGHT_GET_RANK_REWARD		700504
#define INNER_OFFLINE_FIGHT_GET_REMAINING_TIME  700505
#define INNER_SEND_TARGET_OFFLINE_FIGHT_RECORD  700506

#define INNER_CREATE_DEFAULT_OFFLINE_FIGHT      700551
#define INNER_OFFLINE_FIGHT_SAVE		        700552
// offline fight-----------end

// rank---------begin
#define INNER_LOAD_RANK 		                700601
#define INNER_LOAD_RANK_ROLE_LEVEL 		        700602
#define INNER_LOAD_RANK_ROLE_FIGHTING_CAPACITY  700603
#define INNER_LOAD_RANK_ROLE_HAVE_GOLD          700604
#define INNER_LOAD_RANK_ROLE_PRESTIGE           700605
#define INNER_LOAD_RANK_ROLE_ARENA              700606
#define INNER_ROLE_LEVEL_CHANGED		        700611
#define INNER_ROLE_FIGHTING_CAPACITY_CHANGED    700612
#define INNER_ROLE_HAVE_GOLD_CHANGED            700613
// rank-----------end

// email-----------begin
#define INNER_EMAIL_LOAD						700651
#define INNER_EMAIL_SEND			            700652
#define INNER_EMAIL_RECEIVE_ITEM	            700653
#define INNER_EMAIL_OPEN			            700654
#define INNER_EMAIL_DELETE			            700655
// email-----------end


// faction -------- begin
#define INNER_CREATE_FACTION		            700681
#define INNER_JOIN_FACTION						700682
#define INNER_KICK_MEMBR_FACTION				700683
#define INNER_SET_JOB_FACTION					700684
#define INNER_SET_NOTICE_FACTION				700685
#define INNER_SET_JOIN_LINMIT_FACTION			700686
#define INNER_SET_TOTEMS_UP_FACTION				700687
#define INNER_SET_MSG_BOARD_FACTION				700688

// faction member begin
#define INNER_FACTION_MEMBER_DIGGING			700689
#define INNER_FACTION_MEMBER_WORSHIP			700690
#define INNER_FACTION_MEMBER_DEKARON_BOSS		700691
#define INNER_FACTION_MEMBER_KILL_BOSS			700692

#define INNER_GET_FACTION_DATA					700693

// faction member end 

// faction -------- end

// gm command---------begin
#define INNER_GM_COMMMAND_SHOW_PLAYER		    700701
// offline fight-----------end

#define ACTIVE_ADDICTED_NOTIFY          800602
#define ACTIVE_POST_NOTICE              800610

#define ADDICTED_LOGIN_NOTIFY_REG       1
#define ADDICTED_WARNING_1_HOUR         2
#define ADDICTED_WARNING_2_HOUR         3
#define ADDICTED_LAST_WARNING           4
#define ADDICTED_NOTIFY_OFFLINE         5
#define ADDICTED_LOGIN_NOTIFY_FORCE_REG 6

#define ACTIVE_NOTIFY_ERROR             800999
#define ACTIVE_SNAP_INFO                888888

#define SERVER_KEEP_ALIVE               999999

// INNER asynch msg
#define AUTH_ENGINE_KEY_OK              101
#define AUTH_ENGINE_KEY_ERROR           102
#define KICK_OUT_PLAYER_OK              103
#define KICK_OUT_PLAYER_FAILED          104

// backend msg queue
#define WEB_RECHARGE_YUAN_BAO           1021
#define WEB_GIFT_YUAN_BAO               1022
#define WEB_KICK_PLAYER                 1023
#define WEB_FORBID_TALK                 1024
#define WEB_FORBID_ROLE_LOGIN           1025
#define WEB_FORBID_AC_LOGIN             1026
#define WEB_FORBID_IP_LOGIN             1027
#define WEB_REMOVE_GM_CTRL              1028
#define WEB_EXTRAT_NEWBIE_CARD          1029
#define WEB_INSERT_ITEM                 1101
#define WEB_REMOVE_ITEM                 1102
#define WEB_ADD_EXP                     1103
#define WEB_ADD_RELATION_ONLINE			1201
#define WEB_ASK_RELATION_LIST_ONLINE	1202
#define WEB_PULISH_TIPS					1203
#define WEB_RECHARGE_TOKEN				1204
#define WEB_RECHARGE_TOKEN_RESULT		1205
#define WEB_RELATION_IS_ONLINE			1206
#define WEB_ADD_RELATION_NOT_ONLINE		1207

// offline fight---------begin
#define WEB_LOAD_OFFLINE_FIGHT			        1301
#define WEB_OFFLINE_FIGHT_START			        1302
#define WEB_OFFLINE_FIGHT_FINISH	            1303
#define WEB_OFFLINE_FIGHT_GET_RANK_REWARD	    1304
#define WEB_OFFLINE_FIGHT_GET_REMAINING_TIME    1305
#define WEB_SEND_TARGET_OFFLINE_FIGHT_RECORD    1306

#define WEB_CREATE_DEFAULT_OFFLINE_FIGHT	    1351
// offline fight-----------end

// rank---------begin
#define WEB_LOAD_RANK			                1401
#define WEB_LOAD_RANK_ROLE_LEVEL			    1402
#define WEB_LOAD_RANK_ROLE_FIGHTING_CAPACITY    1403
#define WEB_LOAD_RANK_ROLE_HAVE_GOLD            1404
#define WEB_LOAD_RANK_ROLE_PRESTIGE             1405
#define WEB_LOAD_RANK_ROLE_ARENA                1406

//#define WEB_CREATE_DEFAULT_RANK	    1451
// rank-----------end


// faction---------begin
#define WEB_CREATE_FACTION		                1451
#define WEB_JOIN_FACTION		                1452
#define WEB_KICK_MEMBER_FACTION		            1453
#define WEB_KICK_MEMBER_OF_MEMBER_FACTION	    1454
#define WEB_SET_JOB_FACTION					    1455
#define WEB_SET_JOB_FOR_MEMBER_FACTION		    1456
#define WEB_SET_NOTICE_FACTION					1457
#define WEB_SET_JOIN_LINMIT_FACTION				1458
#define WEB_SET_TOTEMS_UP_FACTION				1459
#define WEB_SET_MSG_BOARD_FACTION				1460
// faction member begin
#define WEB_FACTION_MEMBER_DIGGING				1461
#define WEB_FACTION_MEMBER_WORSHIP				1462
#define WEB_FACTION_MEMBER_DEKARON_BOSS			1463
#define WEB_FACTION_MEMBER_KILL_BOSS			1464
#define WEB_GET_FACTION_DATA					1465
// faction member end

// faction---------end

// email--------begin
#define WEB_LOAD_EMAIL_DATA						1481
#define WEB_SEND_EMAIL_BY_SELF					1482
#define WEB_SEND_EMAIL_BY_TARGET				1483
#define WEB_RECEIVE_EMAIL_ITEM					1484
#define WEB_OPEND_EMAIL							1485
#define WEB_DELETE_EMAIL						1486
// email--------end

// gm commmand---------begin
#define WEB_GM_COMMMAND_SHOW_PLAYER			    1501
// gm commmand-----------end

#endif

