#ifndef GLOBAL_MACROS_H_
#define GLOBAL_MACROS_H_

#define JIE_JI_INT_MAX     0x7FFFFFFF

#define MAX_EPOLL_PARA     3000

#ifdef YN_WINDOWS
#pragma warning(disable:4251) 
#pragma warning(disable:4819)
#pragma warning(disable:4996)
typedef signed  __int8  sint8;
typedef unsigned __int8  uint8;
typedef signed  __int16  sint16;
typedef unsigned __int16  uint16;
typedef signed  __int32  sint32;
typedef unsigned __int32  uint32;
typedef signed  __int64  sint64;
typedef unsigned __int64  uint64;

typedef    int   sint;   // at least 32bits (depend of processor)
typedef unsigned int   uint;   // at least 32bits (depend of processor)

#define I64 "I64"
#endif

#ifdef YN_LINUX
typedef long long int sint64;
typedef unsigned long long int uint64;
typedef int sint;
typedef unsigned int uint;
#define I64 \
    "ll"
#endif

#ifdef YN_LINUX
#define SPRINTF_STR snprintf
#else
#define SPRINTF_STR sprintf_s
#endif

#ifdef YN_LINUX
#define STRTOK_STR strtok_r
#else
#define STRTOK_STR strtok_s
#endif

#ifdef YN_LINUX
#define ATOLL_STR atoll
#else
#define ATOLL_STR atol
#endif

#define MIN_SERVICE_SN                    1
#define MAX_SERVICE_SN                    1999
#define ROLE_ID_RANGE                     1000000
#define MIN_ROLE_ID                       1000
#define MAX_ROLE_ID                       ((MAX_SERVICE_SN+1)*ROLE_ID_RANGE-1)
#define IS_ROLE(ID)                       ((ID)<=MAX_ROLE_ID&&(ID)>=MIN_ROLE_ID)
#define MAX_ROLE_COUNT                    3
#define FACTION_ID_BASE                   100000
#define TEAM_ID_BASE                      10000000

#define MONSTER_ID_BASE                   2001000000
#define IS_MONSTER(ID)                    ((ID)/1000000*1000000==MONSTER_ID_BASE)
#define BEAST_ID_BASE                     2002000000
#define IS_BEAST(ID)                      ((ID)/1000000*1000000==BEAST_ID_BASE)
#define SPAWN_MONSTER_ID_BASE             2003000000
#define IS_SPAWN_MONSTER(ID)              ((ID)/1000000*1000000==SPAWN_MONSTER_ID_BASE)
#define ITEM_ID_BASE                      2004000000
//#define IS_ITEM(ID)                       ((ID)/1000000*1000000==ITEM_ID_BASE)
#define MOUNT_ID_BASE                     2004000000
#define IS_MOUNT(ID)                      ((ID)/1000000*1000000==MOUNT_ID_BASE)
#define NPC_ID_BASE                       2005000000
#define IS_NPC(ID)                        ((ID)/1000000*1000000==NPC_ID_BASE)
#define EFFECT_EVNET_ID_BASE              2006000000

#define IP_ADDR_LEN                       16
#define NEWBIE_CARD_KEY_LEN               16
#define MAX_FILE_NAME                     255
#define MAX_NAME_LEN                      16
#define MAX_ACCOUNT_LEN                   64
#define MAX_NOTICE_CONTENT_LEN            255
#define KEEP_ALIVE_TIMEOUT                25
#define NEW_ROLE_LEVEL                    1
#define MAX_SCENE_RECORD_LEN              100    // "1001,1002" (20 scenes)
#define MAX_MSG_BODY_LEN                  4096
#define MAX_ENCODE_BODY_LEN               20480
#define MAX_PKG_COUNT                     147
#define MAX_STORAGE_COUNT                 147
#define MAX_GE_AUTH_KEY_LEN               32
#define MAX_TIMER_INIT                    100000
#define MAX_BUFFER_PATH_LENGTH            5
#define SCAN_SNAP_INTERVAL                200
#define SNAP_SIGHT_RADIUS                 17
#define ITEM_UNBIND                       0     // 未绑定
#define ITEM_USED_BIND                    1     // 使用后绑定
#define ITEM_ALREADY_BIND                 2     // 始终绑定
#define ITEM_GOT_BIND                     3     // 获得后绑定

#define HIT_SHOW_OFFSET      7950
#define CRIT_SHOW_OFFSET     1380

#define PRE_ROLE_NAME_PREFIX              "jjjh_"

#if __WORDSIZE == 64
# define INT64_FMT "%ld"
#else
# define INT64_FMT "%lld"
#endif
/**
* The actual class id is composed of 8-bit integer values, 
* the high four-bit identify the type,
* the lower four-bit identify serial number.
* e.g. 11000001(task id) / 10000000 = a task
* e.g. 11000001(task id) % 10000 = the first task
*/
#define CLASS_ID_SERIAL_NO_RANGE          10000000

#define CLASS_ID_1_BASE                   10000000
#define CLASS_ID_2_BASE                   1000000
#define CLASS_ID_3_BASE                   10000
#define CLASS_ID_GEM_BASE                 100000

//add by brucexu
#define CLASS_ID_MOUNT_BASE               100000
#define MOUNT_ITEM_TYPE                   6

// = MPT FILE
#define MAX_UNZIP_MPT_SIZE                (1024*1024)

// = DB CONFIG
#define DB_CFG_PATH                       "db.json"

// = GATE CONFIG
#define GATE_CFG_PATH                     "gate.json"

#define VERSION_CFG_PATH				"version.json"

// = ENGINE CONFIG
#define ENGINE_CFG_PATH                   "engine.json"

// = SYSTEM CONFIG
#define SYSTEM_CFG_PATH                   "system.json"

// = ITEM DESC CONFIG
#define ITEM_DESC_CFG_PATH                "item_system/item_desc_config.json"

// = SERVER ID CONFIG
#define SERVER_ID_PATH					"game_server_id.json"

// = PARTITION CONFIG
#define  PARTITION_CFG_PATH				"partition.json"

// = GM CONFIG
#define  GM_CFG_PATH				     "gm_server.json"

// = RADIATE CONFIG
#define  RADIATE_SYSTEM_CFG_PATH		"radiate_system.json"

// = RADIATE PLAYER CONFIG
#define  RADIATE_PLAYER_CFG_PATH		"radiate_player.json"

// = TIMER
#define ROLE_INFO_CHECK_INTERVAL          10

// = COUNTRY
#define COUNTRY_YANLIU                    1
#define COUNTRY_LIANG                     2
#define COUNTRY_WU                        3
#define COUNTRY_ZHONG                     4
#define COUNTRY_COUNT                     5
#define CHECK_COUNTRY_ID(N)              ((N)==COUNTRY_YANLIU||(N)==COUNTRY_LIANG||(N)==COUNTRY_WU)

#define SCENE_ID_COUNTRY_YANLIU           1002
#define SCENE_ID_BORDER_YANLIU            1004
#define SCENE_ID_COUNTRY_LIANG            2002
#define SCENE_ID_BORDER_LIANG             2004
#define SCENE_ID_COUNTRY_WU               3002
#define SCENE_ID_BORDER_WU                3004
#define SCENE_ID_RED_COUNTRY              4002

// = SCENE CONFIG
#define SCENE_PATH                        "scene"
#define SCENE_CFG_PATH                    "scene/scene.json"
#define SCENE_LIMIT_CFG_PATH              "scene/scene_limit.json"
#define SCENE_ID_SERIAL_NO_RANGE          10000
#define UNMOVEABLE_POINT                  1
#define SCENE_SERIAL_ID(N)                ((N) % SCENE_ID_SERIAL_NO_RANGE)

// = ROLES INFO
#define SEX_MALE                          1
#define SEX_FEMALE                        2
#define SEX_ADAPTE_TO_DB(N)               ((N) == SEX_MALE ? 'M' : 'F')
#define SEX_ADAPTE_FROM_DB(N)             ((N) == 'M' ? SEX_MALE : SEX_FEMALE) 
#define CHECK_SEX_ID(N)                   ((N) == SEX_MALE||(N) == SEX_FEMALE)
#define CAREER_WARRIOR                    1   // 武者
#define WARRIOR_LVL_1_HP                  19
#define WARRIOR_LVL_1_MP                  15
#define CAREER_RABBI                      2   // 游侠
#define RABBI_LVL_1_HP                    16
#define RABBI_LVL_1_MP                    18
#define CAREER_TAOIST                     3   // 羽士
#define TAOIST_LVL_1_HP                   17
#define TAOIST_LVL_1_MP                   13
#define CAREER_COUNT                      4   // 
//#define CHECK_CAREER_NO(ID)               ((ID) > 0 && (ID) < CAREER_COUNT)
#define CHECK_CAREER_ID(T)                ((T)==CAREER_WARRIOR||(T)==CAREER_RABBI||(T)==CAREER_TAOIST)
#define ROLE_INIT_CFG_PATH                "role/init.json"
#define ROLE_BIRTH_CFG_PATH               "role/birth.json"
#define ROLE_BASIC_SPEED                  100
#define MAX_LEVEL                         40

// = TASK CONFIG
#define TASK_TYPE                         1   // 
#define TRUNK_TASK_TYPE                   1   // 主线任务
#define BRANCH_TASK_TYPE                  2   // 支线任务
#define DAILY_TASK_TYPE                   3   // 日常任务
#define NEWBIE_TASK_TYPE                  4   // 新手任务
#define TASK_CFG_PATH                     "task/task.json"
#define TASK_SERIAL_ID(N)                 ((N) % CLASS_ID_SERIAL_NO_RANGE)
// task status
#define TASK_STATUS_NULL                  0
#define TASK_STATUS_UN_ACCEPTABLE         1
#define TASK_STATUS_ACCEPTABLE            2
#define TASK_STATUS_ACCEPTED              3
#define TASK_STATUS_REFERABLE             4
#define TASK_STATUS_COMPLETE              5
#define TASK_STATUS_DONE                  6
#define MAX_QUEST_COUNTER                  200

// = PET CONFIG
#define PET_CLASS_CFG_PATH                "pet/pet.json"
#define PET_SKILL_CFG_PATH                "pet/petskill.json"
#define PET_SERIAL_ID(N)                  ((N) % CLASS_ID_SERIAL_NO_RANGE)
#define PET_BOOK_SERIAL_ID(N)             ((N) % CLASS_ID_SERIAL_NO_RANGE)
#define PET_MAX_SKILLS                    4


// = ITEM CONFIG
#define ITEM_TYPE                         2   // 
#define EQUIP_ITEM_TYPE                   1   // 装备物品
#define CONSUME_ITEM_TYPE                 2   // 消耗品
#define TASK_ITEM_TYPE                    3   // 任务物品
//add by brucexu
//#define MOUNT_ITEM_TYPE                 4   // 坐骑(也属于物品)
#define ITEM_MAX_HOLE_COUNT               3
#define MAX_ITEM_EFFECT_COUNT             5
#define BASE_INDEX_EQUIP                  10000
#define BASE_INDEX_PACKAGE                20000
#define BASE_INDEX_STORAGE                30000
#define BASE_INDEX_DROPPED                40000
#define BASE_INDEX_BUYBACK                50000
#define BASE_INDEX_TRADE                  60000
#define BASE_INDEX_TRADED                 65000
#define BASE_INDEX_MAILGOODS              70000
#define EQUIP_CLOTHES_PART                1
#define EQUIP_WEAPONS_PART                2
#define EQUIP_ARMET_PART                  3
#define EQUIP_CESTUS_PART                 4
#define EQUIP_BOOT_PART                   6
#define EQUIP_NECKLACE_PART               8
#define EQUIP_ITEM_CFG_PATH               "item/equip.json"
#define TASK_ITEM_CFG_PATH                "item/task_item.json"
#define CONSUME_ITEM_CFG_PATH             "item/consume.json"
#define ITEM_SERIAL_ID(N)                 ((N) % CLASS_ID_SERIAL_NO_RANGE)
#define MAX_DROP_ITEM_AMOUNT              48
//
#if 0
#define PACK_GOODS_SOURCE_DEFAULT         0
#define PACK_GOODS_SOURCE_BUY             10
#define PACK_GOODS_SOURCE_COMBINE         21
#define PACK_GOODS_SOURCE_REMOVE          22
#define PACK_GOODS_SOURCE_PICK            30
#define PACK_GOODS_SOURCE_GIFT            40
#define PACK_GOODS_SOURCE_EMAIL           50
#define PACK_GOODS_SOURCE_TASK            60
#define PACK_GOODS_SOURCE_TRADE           70
#define PACK_GOODS_DELETE_BY_KILL         80
#define PACK_INSERT_GOOD                  110
#define PACK_DELETE_GOOD                  111
#define PACK_UPDATE_GOOD                  112
#endif

#define T_MONEY_BIND_COPPER               1 
#define T_MONEY_COPPER                    2
#define T_MONEY_GOLD                      3
#define MAX_BUY_MALL_GOODS                20
#define MAX_UNBIND_COPPER                 999999999
#define MAX_BIND_COPPER                   999999999
#define MAX_GOLD_COIN                     999999999

// = SKILL CONFIG
#define SKILL_TYPE                        3   // 
#define WARRIOR_SKILL_TYPE                1   // 武者
#define RABBI_SKILL_TYPE                  2   // 游侠
#define TAOIST_SKILL_TYPE                 3   // 羽士
#define PET_SKILL_TYPE                    4   // 宠物
#define MAX_SKILL_LEVEL                   4
#define SKILL_CFG_PATH                    "skill/skill.json"
#define SKILL_SERIAL_ID(N)                ((N) % CLASS_ID_SERIAL_NO_RANGE)

#define SKILL_ID_RANGE                    1000000
#define IS_NORMAL_SKILL(N)                   (((N) % SKILL_ID_RANGE) == 1)

// = NPC CONFIG
#define NPC_TYPE                          4   // 
#define FUNC_NPC_TYPE                     1   // 功能型NPC
#define TASK_NPC_TYPE                     2   // 任务型NPC
#define NPC_SERIAL_ID(N)                  ((N) % CLASS_ID_SERIAL_NO_RANGE)

// = MONSTER CONFIG
#define MONSTER_TYPE                      5   // 
#define MONSTER_TYPE_NORMAL               1   // 普通怪物
#define MONSTER_TYPE_COLLECT              2   // 采集怪物
#define MONSTER_TYPE_UNDEAD               3   // 不死系怪物
#define MONSTER_TYPE_NOTATTACK            4   // 不反击怪物
#define MONSTER_TYPE_RED_KILLER           5   // 红名克星
#define ATT_TYPE_ACTIVE                   1   // 主动攻击
#define ATT_TYPE_INACTIVE                 2   // 被动攻击
#define ORD_MONSTER_TYPE                  1   // 普通怪
#define ELITE_MONSTER_TYPE                2   // 精英怪
#define BOSS_MONSTER_TYPE                 3   // BOSS怪
#define MONSTER_TYPE_PET                  6   // PET
#define MONSTER_ROBOT_CFG_PATH            "monster/robot.json"
#define MONSTER_DROP_CFG_PATH             "monster/drop.json"
#define MONSTER_SERIAL_ID(N)              ((N) % CLASS_ID_SERIAL_NO_RANGE)
#define MONSTER_CORPSE_REAMIND_TIME       10

// = TEAM
#define TEAM_ASSIGN_MODE_FREE             1
#define TEAMER_QUIT_ACTIVE                0
#define TEAMER_QUIT_KICKED                1
#define MAX_TEAMER_COUNT                  5
#define ASSIGN_PROFIT_RANGE               20

// = SHOP CONFIG
#define SHOP_CFG_PATH                     "item/shop.json"

// = MARKET CONFIG
#define MARKET_CFG_PATH                   "item/market.json"

// = GIFT CONFIG
#define GIFT_CFG_PATH                     "item/gift.json"

// = GIFT CONFIG
#define ONLINE_GIFT_CFG_PATH              "item/onlinegift.json"

// = EXP CONFIG
#define EXP_CFG_PATH                      "role/exp.json"

// = FRIENDLY_CLUE CONFIG
#define FRIENDLY_CLUE_CFG_PATH            "role/friendly_clue.json"

// = HAN_TARGET CONFIG
#define HAN_TARGET_CFG_PATH               "role/han_target.json"

// = RELIVE CONFIG
#define RELIVE_CFG_PATH                   "scene/relive.json"

// = BUF_CONFIG
#define BUF_CFG_PATH                      "skill/state.json"

// = TELEPORT_CONFIG
#define TRANSPORT_CFG_PATH                "scene/transport.json"

// = IU_CONFIG
#define IU_SERIAL_ID(N)                   ((N) % CLASS_ID_SERIAL_NO_RANGE)
#define GEM_MAX_LEVEL                     5
#define POLISH_MAX_LEVEL                  5
#define GEM_ITEM_TYPE                     3
#define GEM_COMBINE_CFG_PATH              "iu/combine.json"
#define EQUIP_PUNCH_CFG_PATH              "iu/punch.json"
#define GEM_INLAY_CFG_PATH                "iu/inlay.json"
#define GEM_REMOVE_CFG_PATH               "iu/remove.json"
#define GEM_STRENGTHEN_CFG_PATH           "iu/strengthen.json"
#define EQUIP_UPGRADE_CFG_PATH            "iu/equip_upgrade.json"

// = SUIT_CONFIG
#define SUIT_CFG_PATH                     "iu/suit.json"
#define SUIT_ITEM_TYPE                    5

// PK_MODE
#define PK_MODE_PEACE                     1
#define PK_MODE_ALL                       2
#define PK_MODE_TEAM                      3
#define PK_MODE_FACTION                   4
#define PK_MODE_COUNTRY                   5

// PK_STATE
#define PK_STATE_NORMAL                   1
#define PK_STATE_GRAY                     2

// WHITE_COLOR
#define PK_WHITE_COLOR                    2

// RED_COLOR
#define PK_RED_COLOR                      4

// PK_MAX_SIN_VALUE
#define PK_MAX_SIN_VALUE                  30 

// 装备保护符
#define ITEM_EQUIP_PROTECT                22050023
// 浮云
#define ITEM_CLOUD_DRIFT                  22050037
// 喇叭
#define ITEM_BUGLE                        22050004

// 耐久度最小值
#define EQUIP_DURABILITY_LOWEST           5

// 召唤兽
#define BEAST_MAX_LEVEL                   8
#define BEAST_MAX_EXP                     840

// VIP 类型
#define VIP_TYPE_NORMAL                   0
#define VIP_TYPE_WEEK                     1
#define VIP_TYPE_MONTH                    2
#define VIP_TYPE_SEASON                   3
#define VIP_TYPE_HALF_YEAR                4

// 大汉目标
#define HAN_TARGET_STATUS_CLOSE   0
#define HAN_TARGET_STATUS_OPEN    1
#define HAN_TARGET_STATUS_FINISH  2
#define HAN_TARGET_STATUS_AWARD   3

// 任务的字节个数
#define MAX_QUEST_BYTES           400

// item
#define MAX_ATTR_COUNT                              9           // 玩家属性个数
#define SET_GEM_COUNT                               5           // 宝石镶嵌个数
#define GEM_LEVEL_UP_NEED_COUNT                     3           // 宝石升级需要个数

// skill
#define  MAX_SKILL_COUNT                10          // 玩家配置技能的个数

// offline_fight
#define OFFLINE_FIGHT_PLAYER_MAX_COUNT              5   // 玩家挑战列表个数

// item_container
#define CREATE_BAG_CONTAINER_COUNT                  24

// Login_Reward
#define WEEK_DAY                    7

// struct tm *gmtime_r(const time_t *timep, struct tm *result)
// {
// 	   struct tm *p = gmtime(timep);
// 	    memset(result, 0, sizeof(*result));
// 	    if (p) {
// 		        *result = *p;
// 		        p = result;
// 		    }
// 	    return p;
// 	}
// 
// struct tm *localtime_r(const time_t *timep, struct tm *result)
// {
// 	    struct tm *p = localtime(timep);
// 	    memset(result, 0, sizeof(*result));
// 	    if (p) {
// 		        *result = *p;
// 		        p = result;
// 		    }
// 	    return p;
// }


#endif

