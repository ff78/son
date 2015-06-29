//
//  FightDefine.h
//  cocosGame
//
//  战斗中使用的常量和枚举
//
//  Created by ff on 14-11-6.
//
//

#ifndef cocosGame_FightDefine_h
#define cocosGame_FightDefine_h

/*
 *  地图边界，协定所有地图为1920宽。地图上下边界有可能会有变化，等
 *  需要改变时再从文件读取。目前先放到这里做一致定义。
 *  左右两边各留20像素，不让角色进入，避免一半身体出地图。
 */
#define MAP_AREA_TOP 240
#define MAP_AREA_BOTTOM 50
#define MAP_AREA_LEFT 60
#define MAP_AREA_RIGHT 1860
#define MAP_AREA_WIDTH 1920

//放战斗角色数据，包括玩家与怪物和NPC。玩家数据会在读取文件后，再由实时数据重写相关字段
#define ACTOR_FILE "GameData/data_actor.json"
//放城镇地图数据
#define CITY_FILE "GameData/scene_city.json"
//放城镇NPC角色数据
#define NPC_FILE "GameData/scene_npc.json"
//战斗场景数据
#define FIGHT_SCENE_FILE "GameData/scene_fight.json"
//战区数据，暂时没用，用的是之前工程的那套
#define WARZONE_CONFIG_FILE "GameData/scene_warzone.json"
//技能数据，战斗显示相关的部分
#define SKILL_FIGHT_FILE "GameData/data_skill.json"
//技能段tag数据
#define SKILLTAG_FIGHT_FILE "GameData/data_skillTag.json"
//神兵技能数据
#define CLS_SKILLT_FIGHT_FILE "GameData/data_ClsSkill.json"

#define SHADOW_FILE "img/scene/shadow.png"
#define STATE_MACHINE_DIR "GameData/statemachine/"
#define ARM_DIR "armature/"

//与伤害相关的自定义事件名称
//主角被击事件标签，由击中主角的对象发出。需要在userData中配置攻击方与防御方
#define HERO_HURT_TAG "hero_parse_hurt"
//怪物重置动作时，让主角将其从案犯记录（造成过伤害的怪物的列表）中删掉
#define MONSTER_RESET_PUNCH "monster_reset_punchtag"
//怪物被击事件标签，与主角被击事件标签作用类似
#define MONSTER_HURT_TAG "monster_parse_hurt"
//主角重置动作标签，与怪物重置动作标签作用类似
#define HERO_RESET_PUNCH "hero_reset_punchtag"

//关卡选择数据到达标签
#define ENTER_FIGHT_NETOVER "enter_fight_network_over"

#define FIGHT_RESUTLT_NETOVER "fight_result_network_over"


#define XULI_EFFECT_TAG 100
#define ATTACK_EFFECT_TAG 101

#define MOVE_ACTION_TAG 1001
#define READY_RUSH_TAG 1002
#define READY_RUSHATK_TAG 1003
#define COMBOBOOM_TAG 1004

#define XULI_ENOUGH_TAG 10000
#define SKILLA_LINK_TIMEOUT_TAG 10001
#define SKILLB_LINK_TIMEOUT_TAG 10002
#define SKILLC_LINK_TIMEOUT_TAG 10003
#define SKILLD_LINK_TIMEOUT_TAG 10004
#define IDLE_TIMEOUT_TAG 10005
#define WAIT_TIMEOUT_TAG 10006
#define TIP_TIMEOUT_TAG 10007
#define GHOST_BAR_CHANGE_TAG 10008

#define SKILLA_BTN 20000
#define SKILLB_BTN 20001
#define SKILLC_BTN 20002
#define SKILLD_BTN 20003
#define SKILLA_LBG 20004
#define SKILLB_LBG 20005
#define SKILLC_LBG 20006
#define SKILLD_LBG 20007
#define SKILLA_PRO 20008
#define SKILLB_PRO 20009
#define SKILLC_PRO 20010
#define SKILLD_PRO 20011
#define SKILLA_PROACTION 20012
#define SKILLB_PROACTION 20013
#define SKILLC_PROACTION 20014
#define SKILLD_PROACTION 20015
#define SKILLA_TEXT 20016
#define SKILLB_TEXT 20017
#define SKILLC_TEXT 20018
#define SKILLD_TEXT 20019
#define SKILLY_BTN 20020


//战斗界面layout标签
#define BATTLE_LAYOUT 90000

//原是走松开后，连接跑的极限时间定义
//现在城镇中，已取消冲刺跑
//现在战斗中，用于跑攻1和跑攻2的时间分界点
#define RUSH_LINK_TIME 0.3
//定义蓄力满的时间
#define XULI_DUR 0.2

//定义走、跑速度。玩家的速度会从blackActor中拿
#define WALK_SPEED 8
#define RUSH_SPEED 16

//方向定义，可位操作查看叠加方向信息
enum DIRECT
{
    NONE = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 4,
    LEFT = 8
};

//角色状态列表，所有角色涉及的所有状态。各状态机表格需要与它保持一致。
enum ACTORSTATE
{
    ANY = -2,
    UNDEFINED = -1,
    IDLE = 0,
    MOVE,
    RUSH,
    ATTACK,
    SKILL,
    SKILL4, //5
    RUNATTACK,
    JUMP,
    JUMPATTACK,
    HURT,
    FELLDOWN, //10
    XULI,
    INAIR,
    SPSKILL,
    DIE,
    BLINK, //15
    PATROL,
    CHASE,
    RETURN,
    WAIT,
    LINGERS, //20
    BACK,
    AUTOMOVE,
    INIT,
    BOUNDGROUND,
    BOUNDWALL, //25
    SNEAK,
    SNEAKRUSH,
    FAINT,
    FIX,
    FORZEN  //30
};

//原为所有角色所用的动作名表，但现在动作的顺序已不再需要遵循。
//再使用这个会是比较危险的。
//todo 需要将所有用这个的地方再检查一遍。能不使用就替换掉。
enum HEROACTION
{
    STAND = 0,
    GETUP,
    HEADHIT,
    WAISTHIT,
    WALK,
    RUN, //5
    JUMP_UP,
    JUMP_DOWN,
    LANDGROUND,
    JUMPATTACK1,
    JUMPATTACK2, //10
    HEADFELLDOWN,
    WAISTFELLDOWN,
    AIRHITUP,
    AIRHITDOWN,
    AIRHIT, //15
    ATTACKPART1,
    ATTACKPART2,
    ATTACKPART3,
    ATTACKPART4,
    ATTACKPART5, //20
    ATTACKPART6,
    ATTACKPART7,
    ATTACKPART8,
    ATTACKPART9,
    SKILLATK1, //25
    SKILLATK2,
    SKILLATK3,
    SKILLATK4,
    SKILLATK5,
    SKILLATK6, //30
    SKILLATK7,
    SKILLATK8,
    SKILLATK9,
    RUNATTACK1,
    RUNATTACK2, //35
    RUNATTACK3,
    RUNATTACK4,
    RUNATTACK5,
    RUNATTACK6,
    RUNATTACK7, //40
    RUNATTACK8,
    RUNATTACK9,
    ATTACKCACHE,
    LIE,
    LIESHOCK, //45
    BOUND2G,
    BOUNDUP,
    BOUND2W,
    BOUNDBACK
};

//按键解码结果列表，目前只用到前三个。
enum KEYCOMMAND
{
    CMD_STOPMOVE = 0,
    CMD_WALK,
    CMD_RUSH,
    CMD_RUSHATK1,
    CMD_RUSHATK2,
    CMD_ATTACK,
    CMD_SKILLA,
    CMD_SKILLB,
    CMD_SKILLC,
    CMD_SKILLD
};
enum GAMEKEY
{
    BUTTON_A = 1,
    BUTTON_S1 = 2,
    BUTTON_S2 = 3,
    BUTTON_S3 = 4,
    BUTTON_J = 5,
    BUTTON_S1_E = 6,
    BUTTON_S2_E = 7,
    BUTTON_S3_E = 8,
    BUTTON_SP = 9,
    BUTTON_Y = 10
};

enum Game_Scene_State
{
    Game_Scene_State_Loading		= 0,			  // Loading状态
    Game_Scene_State_Normal			= 1,			  // 正常状态(也就是正常的战斗状态)
    Game_Scene_State_Result			= 2,			  // 战斗结束状态(弹胜利失败界面)
    Game_Scene_State_Dialogue		= 3,			  // 对话状态
    Game_Scene_State_Max
};
#endif
