#ifndef __GAME_DEFINE_H__
#define __GAME_DEFINE_H__

#define PROFILE_KEY_FIRST_ENTERGAME				"firstentergame"
#define PROFILE_KEY_FIRST_USERNAME				"username"
#define PROFILE_KEY_FIRST_PASSWORD				"password"

#define EACH_SCROLL_PANEL			4			//每个滑动层放置4个任务显示区域
#if 1//yypp
#define NPC_DIALOGUE_OPTION			4			//npc对话框最大的选项数
#else
#define NPC_DIALOGUE_OPTION			8			//npc对话框最大的选项数
#endif
#define UI_HEARTMETHOD_LAYER_EQUIP_INFO  4		//显示装备的属性

#define UI_HEAD_SUM_NUM		3
#define ENDLESS_TOWER_STATE_ID 5000				// 无尽塔章节ID
#define ENDLESS_TOWER_LAST_FLOOR 50009			// 无尽塔最后一关的关卡ID

enum NpcServiceType								//npc服务类型，显示的时候也按这个先后顺序
{
	NS_Shop = 0,						// 商店
	NS_Mission_Compeleted,				// 完成但没提交的任务
	NS_Mission_CanBeAccepted,			// 可接任务
	NS_Mission_Uncompelted,				// 没有完成的任务

	NS_Num
};

enum UI_Desc                            //各界面固定文字显示信息配置
{
	UI_FATE = 90013,//天命
	UI_RANKING = 90018,//排行榜
	UI_SOCIAL = 90017,//社交
	UI_SYSTEM = 90016,//系统
	UI_ASSISTANT = 90020,//助手
	UI_ACTIVITY = 90019,//活动
	UI_GIFT_BAG = 90021,//礼包

	//role UI
	ROLE_TITLE = 90008,//主将
	ROLE_INFO = 90024,//人物属性
	ROLE_INTERDUCE = 90088,//人物介绍
	ROLE_FONT = 90285, //主角
	//lieutenant UI
	LIEUTENANT_TITLE = 90009,//副将

	//bag UI
	BAG_TITLE = 90010,//背包

	//skill UI
	SKILL_TITLE = 90014,//招式

	//heart method UI
	HEART_METHOD_TITLE = 90011,//心法
	HEART_METHOD_COMBINE = 90042,//心法合成
	HEART_METHOD_QUALITY_UP_TITLE = 90074,//心法升品

	//equipment UI
	EQUIPMENT_TITLE = 90501,//装备
	COMMON_EXP_FONT = 90506,//经验

	//equipment quality up UI
	EQUIPMENT_QUALITY_UP_TITLE = 90047,//装备升品
	EQUIPMENT_INTENSIFY = 90037,//强化

	//store
	STORE_TITLE = 90038,//商店

	//mission UI
	MISSION_TITLE = 90012,//任务
	MISSION_TITLE_ACCEPT = 90030,//已接任务
	MISSION_TITLE_ABLE_ACCEPT = 90029,//可接任务
	MISSION_TITLE_DAILY = 90031,//每日任务
	MISSION_GO = 90032,//立刻前往
	MISSION_PAGE_UP = 90033,//上一页
	MISSION_PAGE_DOWN = 90034,//下一页
	MISSION_QUIT = 90036,//放弃任务

	//common attr
	COMMON_ROLE = 90023,//角色
	COMMOM_COMBINE = 90027,//合成
	COMMON_PURCHASE = 90039,//购买
	COMMON_SELL = 90041,//出售
	COMMON_TAKE_OFF = 90040,//卸下
	COMMON_EQUIP = 90015,//装备
	COMMON_LEVEL_UP = 90026,//升级
	COMMON_QUALITY_UP = 90028,//升品
	COMMON_ASTART = 90160,//寻路
	COMMON_EQUIP_EQUIPMENT = 90161,//装配装备
	COMMON_EQUIMENT_STRENGTHENING = 90162,//装备强化
	COMMON_XINFA_EQUIP = 90163,//装配心法
	COMMON_EQUIPMENT_QUALITY_UP = 90164,//装备升品
	COMMON_SKILL_UP = 90165,//招式升级
	COMMON_LIEUTENANT_FIGHT = 90166,//副将出战
	COMMON_XINFA_COMBINE = 90167,//心法合成
	COMMON_XINFA_QUALITY_UP = 90168,//心法升品
	COMMON_ROLE_QUALITY_UP = 90169,//人物升品
	COMMON_ROLE_QUALITY_UP_TITLE = 90170,//角色升品
	COMMON_FATE_LEVEL_UP = 90620,//天命升级

	COMMON_UI_QUALITY_UP = 90028,//升品
	COMMON_USE = 90337,//使用
	COMMON_ALL_GREEN_QUA_EQUIP = 90194,//一身绿装
	COMMON_TIDY_BAG = 90500,//整理背包
	COMMON_REPUTATION_FONT = 90514,//声望值：
	COMMON_PINZHUANG_XINFA = 90516,//拼装心法
	COMMON_EAT_MATERIAL = 90622,//吞噬
	COMMON_SELECT_EAT_BOOK_NUM = 90623,//选择被吞噬的心法：%d本
	COMMON_GAIN_EXP = 90624,//获得经验
	COMMON_NEED_GOLD = 90625,//消耗银两
	CONTAIN_SHIELD = 90629,//文字内含有屏蔽字符
	SURE_TO_EXIT_GAME = 90075,//确定退出游戏吗？
	SURE_EXIT = 90076,//确定
	CANCEL_EXIT = 90077,//取消
	COMMON_BACK = 90078,//返回
	COMMON_QUIT = 90087,//退出
	TASKUNCOMPLETE = 90098,//只是躲在这里可是什么事也办不了的！
	SYSTEM_SETTING = 90099,//系统设置
	ACCOUNT_MANAGE = 90100,//账号管理
	GOBACK_TO_LOGIN = 90101,//返回登录
	STRATEGY_GUIDE = 90102,//攻略指引
	GAME_NOTICE = 90103,//游戏公告
	UIMUSIC_SETTING = 90104,//音乐
	UIEFFECT_SETTING = 90105,//音效
	UISHIELD_SETTING = 90106,//屏蔽玩家模型
	SYSTEM_FUNCTION = 90115,//系统功能
	COMMON_SELL_GAIN_MONEY = 90252,//出售获得银两
	COMMON_WHEATHER_SELL = 90253,//是否出售？
	COMMON_BUY_NEED_GOLD = 90254,//购买需要银两
	COMMON_WEATHER_BUY = 90255,//是否购买？
	VERSION_BOT_SAME = 90179,//版本不一致，请您更新客户端。
	GAME_SERVER_FOR_CLIENT = 90184,//客服
	UI_LOGIN_TEXT = 90627,//登录
	SERVER_ERROR = 90367,//服务器错误
	CHANGE_ACCOUNT = 90368,//更换账号
	ENTER_GAME = 90369,//进入游戏
	SEE_ALL_SERVER = 90370,//查看全部服务器
	CURRENT_SERVER = 90001,//当前服务器
	LOGIN_SUCCEED_CHECKING_UPDATE = 90376,//登录成功，正在检查更新
	GETTING_SERVER_INFO = 90377,//正在获取服务器信息
	UPDATE_TIPS = 90378,//您当前网络环境非WIFI会使用移动数据流量，是否继续更新？
	UPDATE_NOT_NOW = 90379,//暂不更新
	UPDATE_CONTINUE = 90380,//继续更新
	DOWNLODING = 90381,//正在下载
	UPDATE_PROGRESS = 90382,//更新进度
	DOWNLOAD_SUCCEED_INSTALL = 90383,//下载成功，请安装更新
	DOWNLOAD_SUCCEED_RESTART = 90384,//下载成功，请重启游戏
	NETWORK_FAILED = 90385,//连接网络失败
	CREATE_FILE_FAILED = 90386,//创建文件失败
	READING_RESOURCES_INFO = 90387,//正在或许需要下载的资源信息
	MAX_PLAYER = 90613,//服务器人数已满，请稍候重试。
	INSTANCE_WILL_END = 90616,//副本即将结束
	FUNCTION_WITHOUT = 90628,//功能未开启

	//副本结算界面
	COMMON_GO_BACK_MAIN_CITY = 90392,//回城
};

enum UI_Tips
{
	//活动界面信息
	UA_LEVEL_FONT = 92009, //【等级】
	UA_LEVEL_LIMIT = 92010,// %d级以上
	UA_INTR_FONT = 92035, //【说明】
	UA_AWARD_FONT = 92036, //【奖励】
	UA_TIME_FONT = 92037, //【时间】
	UA_ENTER_FONT = 92018, //进入
	UA_PASS_AWARD = 92025, //通关奖励：
	UA_OPEN_LEVEL = 92027, //开启等级：
	UA_NEED_ENERGY = 92029, //消耗体力：
	UA_OPEN_TIME = 92031, //开放时间：
	UA_ENTER_TIMES = 92034, //进入次数：
	UA_LEVEL = 92028, //%d级
	UA_ENERGY = 92030, //%d点

	UA_TIME_OUT = 92006, //不在活动时间，无法进入！



	//商店界面信息
	SP_CENTER_SIVER = 5902, //银两
	SP_CENTER_GOLD_INGOLT = 5903,	//元宝
	SP_CENTER_SPECIAL_SELLING = 5904,	//特卖
	SP_CENTER_GAIN_SILVER = 5905,	//获取银两
	SP_CENTER_GAIN_GOLD = 5907,	//获取元宝
	SP_CENTER_GAIN_FONT = 90630,//获得：
	SP_CENTER_SELL_NUM = 90631,//出售数量
	SHOP_PURCHASE_INFO = 5906, //是否花费%d元宝购买%d个%s？


	//天命界面显示信息
	FATE_ACUPOINT_NAME = 2809,	//穴位名:
	FATE_ACUPOINT_SUC_RATE = 2810,	//成功率:
	FATE_ACUPOINT_ADD_ATTR = 2811,	//加成属性:
	FATE_ACUPOINT_NOW_GAIN = 2812,	//现已获得:
	FATE_ACUPOINT_ALL_GIFT = 2813,	//全通赠送:
	FATE_ACUPOINT_XIU_NUM = 2814,	//修炼重数:
	FATE_ACUPOINT_HAS_REP = 2815,	//拥有声望:
	FATE_ACUPOINT_NEED_REP = 2816,	//消耗声望:
	FATE_ACUPOINT_HAS_MON = 2817,	//拥有银两:
	FATE_ACUPOINT_NEED_MON = 2818,	//消耗银两:
	FATE_ACUPOINT_COOL_TIME = 2819,	//冷却时间:

	BAG_FULL_TIPS = 90200, //背包已满
	LACK_GOLD_COIN = 90201, //银两不足
	LACK_GOLD_INGOT = 90202, //元宝不足
	LACK_POWER = 90320, //功力不足
	MATERIAL_INSTANCE_NOT_OPEN = 90203, //材料产出副本尚未开启
	LACK_MATERIAL = 90204, //材料不足
	LEVEL_UP_SUCCESS = 90205, //升级成功
	QUALITY_UP_SUCCESS = 90206, //升品成功
	ROLE_REACH_LEVEL_LIMIT = 90207, //角色达到等级上限
	INPUT_RIGHT_EMAIL = 90208, //账号请输入正确邮箱格式
	INPUT_ACCOUNT = 90209, //请输入您的账号
	INPUT_PASSWORD = 90210, //请输入您的密码
	SKILL_REACH_MAX_LEVEL = 90211, //招式已达到当前品质可提升最大等级，请您先提升角色品质
	METEMPSYCHOSIS_SUCCESS = 90212, //转生成功
	LACK_EQUIPMENT_GRID = 90213, //装备栏无空位
	ASSEMBLE_SUCCESS = 90214, //拼装成功
	COMBINE_SUCCESS = 90215, //合成成功
	QUEUE_ALREADY_FULL = 90216, //队列已满
	HEART_METHOD_REACH_CUR_MAX_LEVEL = 90217, //心法已达到当前品质的最大强化等级，请您升品 
	HEART_METHOD_REACH_LEVEL_LIMIT = 90218, //心法已达等级上限
	EQUIPMENT_INTENSIFY_LESS_PROTAGONIST_LEVEL = 90219, //装备强化等级不能超过主角等级，请您提升主角等级
	EQUIPMENT_INTENSIFY_SUCCESS = 90220, //强化成功
	EQUIPMENT_REACH_CUR_MAX_LEVEL = 90221, //装备已达到当前品质的最大强化等级，请您升品
	EQUIPMENT_REACH_LEVEL_LIMIT = 90222, //装备已达等级上限
	CURRENT_INSTANCE_NOT_CHANGE_ROLE = 90223, //当前副本不能换人
	NONE_USEABLE_ROLE = 90224, //没有可用角色
	ROLE_ALREADY_DEAD = 90225, //角色已经死亡
	COOLING_TIME_RUNNING = 90226, //冷却时间未结束
	BAG_FULL_FOR_AWARD_FAIL = 90227, //背包已满，获取奖励失败
	MISSION_ACCEPT_REACH_LIMIT = 90228, //已接任务达到上限
	PASS_KONGFU_SUCCESS = 90229, //传功成功
	EFFICIENT_PASS_KONGFU_SUCCESS = 90230, //高效传功成功
	LACK_KONGFU_MEDICINE = 90231, //传功丹不足
	LIEUTENANT_LEVEL_LESS_PLAYER = 90232, //副将等级不能超过主角等级，请您先提升主角
	INPTU_KONGFU_ROLE_REACH_MAX_LEVEL = 90233, //放进的传功角色已足够使目标角色达到最大等级
	LACK_PASS_KONGFU_OBJECT = 90234, //传功栏未放置角色
	LACK_MISS_KONGFU_OBJECT = 90235, //散功栏未放置角色
	EVERY_TIME_ACCETT_MISSION_ONCE = 90236, //一次只能接取一个每日任务
	NONE_SEARCH_THIS_PERSON = 90237, //查无此人
	// 238 == 208 == 242
	ERROR_INPUT_PASSWORD = 90239, //密码输入错误
	WAIT_FOR_UPDATE = 90240, //正在更新，请稍后
	EMAIL_NOT_BE_REGISTER = 90241, //此邮箱未被注册
	PASSWORD_INPUT_TYPE_TIPS = 90243, //密码请输入6-12位的字母、数字、符合的组合，字母分大小写
	TWICE_PASSWORD_DISMATCH = 90244, //密码不一致
	INPUT_CONFIRM_PASSWORD = 90245, //请输入您的确认密码
	EMAIL_ALREADY_REGISTER = 90246, //此邮箱已被注册
	NAME_ALREADY_EXIST = 90247, //该昵称已存在
	NAME_INPUT_TYPE_TIPS = 90248, //昵称请输入2-16个字符，可以是字母、数字、汉字的组合
	INPUT_YOUR_NAME = 90249, //请输入您的昵称
	// 90250 90240 
	SERVER_DISCONNECT = 90251,//服务器连接已断，请您稍后尝试登录
	BUY_SUCCEED = 90261,//购买成功
	NET_DISCONNECT = 90262,//网络以断，请您稍后尝试登录

	//role dead tips
	TIPS_ROLE_DEAD = 90256, //大侠出师不利，被敌人打倒在地
	TIPS_TIME_COUNT = 90257, //秒后副本失败
	TIPS_CHANGE_ROLE = 90258, //换人
	TIPS_RECOVERY = 90259, //复活
	TIPS_GIVE_UP = 90260, //放弃
	TIPS_EXPEND = 90263,//花费
	TIPS_YUANBAO = 90264,//元宝
	TIPS_FIGHT_AGAIN = 90265,//再战江湖
	TIPS_LEFT_TIME = 90266,//还剩
	TIPS_SECOND = 90267,//秒

	ROLE_AMOUNT_FULL = 90269, //您的创建角色空位已满
	CREATE_ROLE_FAILED = 90270, //创建角色失败，请重试
	QUIT_INSTANCE = 90271, //副本尚未完成，是否确定退出？
	QUEST_COMPLETE = 90272, //任务完成！
	BUY_ENERGY_COUNT_LIMIT = 90273, //今天您的体力购买次数已用完
	LACK_ENERGY = 90274, //您的体力不足
	LACK_ROLE_LEVEL = 90275, //您的等级不足
	LEVEL_NOT_REACH = 90276, //未达到等级需求
	QUALITY_MAX_LIMIT = 90277, //已达到最高品级
	EQUIP_ITEM_LEVEL_LIMIT = 90278, //物品等级大于人物等级，不可装备该物品
	EQUIPMENT_INTENSIFY_LESS_ROLE_LEVEL = 90279, //装备强化等级不能超过穿戴者等级，请您提升穿戴者等级
	TODAY_MISSION_TIMES_OVER = 90280, //当日任务次数已用尽
	TODAY_CHALLENGE_TIMES_OVER = 90281, //当日挑战次数已用尽
	TODAY_PURCHASE_TIMES_OVER = 90282, //当日购买次数已用尽
	TODAY_GOT_OFFLINE_FIGHT_RANK_REWARD = 90283, //您已领取当日奖励。
	GOT_OFFLINE_FIGHT_RANK_REWARD = 90284, //获得%d银两%d声望。。

	ARENA_NOT_OPEN = 90290, //竞技场未开启
	MATERIAL_NOT_OPEN = 90291, //材料未开放
	EXCHANGE_COUNT = 90292, //兑换(%d)
	ASSEMBLE_COUNT = 90293, //拼装(%d)
	EXCHANGE_SUCCESS = 90294, //兑换成功
	ARENA_OPEN_LEVEL = 90388, //竞技场%d级开放

	//添加好友反馈提示
	ADD_FRIEND_SUCCESS = 90125, //添加好友成功!
	ADD_FRIEND_NOT_ONLINE = 90118, //%s不在线。
	ADD_FRIEND_FULL = 90117, //你的好友已满。
	ADD_FRIEND_ALREADY_IS = 90126, //%s已在您的好友列表里。
	ADD_FRIEND_BLACK_LIST = 90127, //%s在您的黑名单里。
	ADD_FRIEND_ADD_SELF = 90116, //不能添加自己为好友。

	//添加删除好友提示
	ADD_FRIEND_CONFIRM = 90128, //是否添加%s为好友？
	DELETE_FRIEND_CONFIRM = 90129, //是否删除%s好友？
	SEND_MESSAGE_TO_SB = 90130, //你对【%s】说
	RECEIVE_MESSAGE_FROM_SB = 90131, //【%s】对你说

	//钱庄兑换提示
	BANK_SUCCEED = 90389, //获得银两%d
	BANK_NOT_ENOUGH_TOKEN = 90390, //元宝不足，无法兑换！
	BANK_HAVE_NO_CHANCE = 90391, //兑换次数已达上限


	//Secondary UI font  副本描述界面显示内容
	MISSION_NEED_POWER = 90079, //需要体力
	MISSION_AWARD_EXP = 90080, //经验奖励
	MISSION_AWARD_MONEY = 90081, //银两奖励
	MISSION_SUGGEST_LEVEL = 90082, //建议等级
	MISSION_DAY_TIMES = 90083, //今日次数
	MISSION_PASS_CONDITION = 90084, //通关条件
	BUTTON_FONT_ENTER = 90085, //进入副本
	MISSION_MAYBE_GAIN = 90086, //可能获得

	//任务界面配置字典
	MISSION_INTRODUCE = 90089,//任务说明
	MISSION_REWORD = 90090,//任务奖励
	MISSION_PUBLISH_NPC = 90091,//发布npc
	MISSION_OVER_NPC = 90092,//完成NPC
	MISSION_EXPERIENCE = 90093,//经验:
	MISSION_GOLD = 90094,//银两:
	MISSION_ACCEPT = 90095,//接收任务
	MISSION_DOITNOW = 90096,//马上前去
	MISSION_OVER = 90097,//完成任务

	//招式界面配置字典表
	SKILL_NEED_LEVEL = 90132, //等级需求：%s级
	SKILL_LEVEL_EQUAL_TO_ROLE_LEVEL = 90133, //招式品级与角色品级一致
	SKILL_NEED_MONEY_FOR_LEVEL_UP = 90134, //升级费用：%s 银两
	SKILL_DAMAGE_NUM = 90135, //招式伤害
	SKILL_LEVEL_UP_BEFORE = 90136, //升级前
	SKILL_LEVEL_UP_AFTER = 90137, //升级后
	SKILL_NOT_REACH_REQUIRE = 90276, //未达到等级需求
	SKILL_WAIT_FOR_OPEN = 90138, //未开放
	SKILL_CURRENT_NAME = 90360, //招式名称：
	SKILL_CURRENT_LEVEL = 90361, //当前等级：
	SKILL_CURRENT_DESC = 90362, //招式说明：
	SKILL_RELEASE_METHOD = 90363, //出招方式：
	SKILL_RELEASE_PROMPT = 90364, //依次点击以下按钮
	SKILL_LEVEL = 90365, //等级：
	SKILL_CURRENT_HARM = 90366, //伤害：

	//人物属性 界面
	LIEUTENANT_FIGHTING_FONT = 90140, //人物出战
	LIEUTENANT_QUIT_FIGHTING_FONT = 90141, //放弃出战
	LIEUTENANT_DISMISS_FONT = 90142, //遣散

	//Ranking list Layer
	RANKING_LIST_FONT = 90601, //排行榜
	//RANKING_LIST_ROLE					= 90602, //主角
	RANKING_LIST_LEVEL = 90603, //等级
	RANKING_LIST_FIGHT = 90604, //战力
	RANKING_LIST_GOLD = 90605, //银两
	RANKING_LIST_RANK = 90606, //名次
	RANKING_LIST_NAME = 90607, //名称
	RANKING_LIST_GUILD = 90608, //帮派
	RANKING_LIST_U_RANK = 90609, //你的排名
	RANKING_LIST_NOT_RANK = 90610, //您未上榜，请继续努力
	FIGHT_FAIL_TIPS = 90611, //搜集更强的装备与心法等来强化自己
	FIGHT_EXIT_INSTANCE = 90612, //退出副本

	//竞技场界面
	ARENA_TODAY_CHALLENGE_TIMES = 90143, //今日可挑战%d次
	ARENA_RECEIVE = 90144, //领取
	ARENA_ALREADY_RECEIVE = 90145, //已领取
	ARENA_RANGKING = 90146, //排名
	ARENA_REPUTATION = 90147, //声望
	ARENA_ARENE_TITLE = 90148, //竞技场
	ARENA_RANKING_AWARD = 90149, //排名奖励:
	ARENA_YESTERDAY_RANKING = 90150, //昨日排名:
	ARENA_CURRENT_RANKING = 90151, //当前排名:
	ARENA_TOMORROW_AWARD = 90154, //明日奖励:
	ARENA_INCREACE = 90152, //增加
	ARENA_GOLD = 90155, //银两
	ARENA_CUR_REPUTATION = 90617, //当前声望：
	ARENA_TODAY_RANKING = 90618, //今日排名：
	ARENA_AWARD_COUNTDOWN = 90619, //领取倒计时：

	//竞技场 竞技结果显示内容
	ARENA_CHALLENGE_WIN_FALL = 90286, //你对【%s】发起挑战，你战败了！当前排名为第【%d】位。
	ARENA_CHALLENGE_WIN_RAISE = 90287, //你对【%s】发起挑战，你获胜了！当前排名为第【%d】位。
	ARENA_BE_CHALLENGED_WIN_FALL = 90288, //【%s】对你发起挑战，你战败了！当前排名为第【%d】位。
	ARENA_BE_CHALLENGED_WIN_RAISE = 90289, //【%s】对你发起挑战，你战胜了！当前排名为第【%d】位。

	//模态框 文字信息 显示
	MODEL_LOADING_FONT = 90153, //加载中……
	MODEL_PURCHASE_ENERGY_FONT = 90157, //购买20体力需要%d元宝。
	MODEL_PURCHASE_CHALLENGE_FONT = 90158, //使用%d元宝增加一次挑战次数

	//show_alert  提示信息显示 文字
	ALERT_U_GAIN = 90308, //您获得了
	ALERT_GAIN_INFO = 90309, //[%s]x%d
	TIPS_LACK_REPUTATION = 90310, //声望不足
	TIPS_CHONG_FIRST = 90311, //第一重
	TIPS_CHONG_SECOND = 90312, //第二重
	TIPS_CHONG_THIRD = 90313, //第三重
	TIPS_CHONG_FOURTH = 90314, //第四重
	TIPS_CHONG_FIFTH = 90315, //第五重
	TIPS_CHONG_SIXTH = 90316, //第六重
	TIPS_OPEN_FOR_LEVEL = 90317, //%d级开启
	TIPS_OPEN_NEXT_LEVEL = 90318, //下一重%d级开启
	TIPS_OPEN_ACUPOINT_FAILED = 90319, //冲穴失败
	TIPS_OPEN_ACUPOINT = 90324, //冲穴
	TIPS_RESET = 90325, //重置
	TIPS_COOL_TIME = 90326, //冷却时间
	TIPS_CLEAN_COST = 90327, //使用%d元宝消除冷却时间

	//残页 碎片提示信息Residual_Page
	FRAGMENT_CURRENT_NO = 90306, //尚未获得碎片，请努力收集吧
	RESIDUAL_PAGE_CURRENT_NO = 90307, //尚未获得残页，请努力收集吧
	CAN_NOT_CHANGE_ROLE_INSTANCE = 90321, //当前副本不能使用副将
	CAN_NOT_CHANGE_ROLE_DEATH = 90322, //角色已阵亡，切换失败
	CAN_NOT_CHANGE_ROLE_NOT_STAY = 90323, //没有副将处在出战状态
	//剧情信息
	PLOT_FIRST_SENTENCE = 90185, //前朝末年，群雄割据，
	PLOT_SECOND_SENTENCE = 90186, //内忧外患，民不聊生。
	PLOT_THIRD_SENTENCE = 90187, //天降英杰，功盖华宇，
	PLOT_FORTH_SENTENCE = 90188, //统一中原，后称武帝。
	PLOT_FIFTH_SENTENCE = 90189, //武帝在位间，国泰民安。然武帝前往华山论剑途中被害，
	PLOT_SIXTH_SENTENCE = 90190, //而太子年幼尚不能理事，以至战乱不断，草寇猖獗……
	PLOT_SEVENTH_SENTENCE = 90191, //十余年后的华山深处，故事由此展开……

	COMMON_CLICK_SCREEN_CONTINUE = 90183, //点击屏幕继续

	//*------------------------------------<<新手指引内容>>------------------------------------------------*//
	//初次进入游戏
	JUNIOR_GUIDE_STORY = 9900, //天下大乱，谁主沉浮。初登江湖，英雄大显身手！
	//寻路功能引导
	JUNIOR_GUIDE_ASTAR = 9901, //寻路功能按键可直接将您引到目标地点

	//接任务引导
	JUNIOR_GUIDE_MISSION_ONE = 9902, //任务交接界面显示任务的相关信息
	JUNIOR_GUIDE_MISSION_TWO = 9903, //点击按键可以接受任务
	//完成任务引导
	JUNIOR_GUIDE_MISSION_THR = 9904, //点击按键可以完成任务
	//副本流程引导
	JUNIOR_GUIDE_INS_ONE = 9905, //有任务副本图标的表示该副本是当前任务所属副本 
	JUNIOR_GUIDE_INS_TWO = 9906, //在进入副本界面可查看此副本的相关信息
	JUNIOR_GUIDE_INS_THR = 9907, //点击退出副本回到主城
	//战斗操作引导
	JUNIOR_GUIDE_FIG_ONE = 9908, //方向键可控制角色的移动
	JUNIOR_GUIDE_FIG_TWO = 9909, //攻击键连续点击或持续按住可触发角色使用连续技
	JUNIOR_GUIDE_FIG_THR = 9910, //招式按键可单独进行点击或与攻击键进行组合按键触发不同的招式
	JUNIOR_GUIDE_FIG_FOR = 9911, //攻击和被攻击都会增加怒气值，怒气值满时点击可触发必杀技
	//展开工具栏引导
	JUNIOR_GUIDE_OPEN = 9912, //请点击展开功能栏
	//穿装备引导
	JUNIOR_GUIDE_EQUIP_ONE = 9913, //点击背包打开背包页面
	JUNIOR_GUIDE_EQUIP_TWO = 9914, //点击选择装备
	JUNIOR_GUIDE_EQUIP_THR = 9915, //点击装备按键可将道具装备到角色身上
	JUNIOR_GUIDE_EQUIP_FOR = 9916, //点击可关闭当前界面
	JUNIOR_GUIDE_EQUIP_FIF = 9917, //点击身上装备，可弹出卸下装备的选项
	//装备强化引导
	JUNIOR_GUIDE_EQUIP_QUA_ONE = 9918, //点击进入装备强化的页面
	JUNIOR_GUIDE_EQUIP_QUA_TWO = 9919, //点击选择穿在身上的装备
	JUNIOR_GUIDE_EQUIP_QUA_THR = 9920, //点击可对选择的装备进行强化
	JUNIOR_GUIDE_EQUIP_QUA_FOR = 9921, //点击可关闭当前界面
	//心法装备引导
	JUNIOR_GUIDE_XINFA_ONE = 9922, //点击进入心法的页面
	JUNIOR_GUIDE_XINFA_TWO = 9923, //点击选择心法
	JUNIOR_GUIDE_XINFA_THR = 9924, //点击装备按键可将心法装备到角色身上
	//招式升级引导
	JUNIOR_GUIDE_SKILL_UP_ONE = 9925, //点击进入招式强化的页面
	JUNIOR_GUIDE_SKILL_UP_TWO = 9926, //可对您要升级的招式进行选择
	JUNIOR_GUIDE_SKILL_UP_THR = 9927, //点击可对选择的招式进行升级
	//副将出战引导
	JUNIOR_GUIDE_LIE_FIG_ONE = 9928, //点击进入角色的页面
	JUNIOR_GUIDE_LIE_FIG_TWO = 9929, //点击可对副将进行选择
	JUNIOR_GUIDE_LIE_FIG_THR = 9930, //点击可使选中的副将出战，一次只能有一名副将出战
	JUNIOR_GUIDE_LIE_FIG_FOR = 9931, //点击副将头像可进行人物切换
	//心法合成引导
	JUNIOR_GUIDE_HMCOM_ONE = 9932, //点击进入心法的页面
	JUNIOR_GUIDE_HMCOM_TWO = 9933, //点击后进入心法合成页面
	JUNIOR_GUIDE_HMCOM_THR = 9934, //第一次点击的会被移到合成框中
	JUNIOR_GUIDE_HMCOM_FOR = 9935, //后面依次点击都会被合成掉
	JUNIOR_GUIDE_HMCOM_FIF = 9936, //点击按键进行合成
	//人物升品引导
	JUNIOR_GUIDE_ROLE_QUA_ONE = 9937, //点击进入人物升品页面
	JUNIOR_GUIDE_ROLE_QUA_TWO = 9938, //选择要升品的角色
	JUNIOR_GUIDE_ROLE_QUA_THR = 9939, //点击按键进行升品
	//装备升品引导
	JUNIOR_GUIDE_EQU_QUA_ONE = 9940, //选择需要升品的装备
	JUNIOR_GUIDE_EQU_QUA_TWO = 9941, //点击进入升品的页面
	JUNIOR_GUIDE_EQU_QUA_THR = 9942, //点击按键进行升品
	//心法拼装引导
	JUNIOR_GUIDE_HMPZ_ONE = 9943, //点击进入心法拼装页面
	JUNIOR_GUIDE_HMPZ_TWO = 9944, //点击拼装
	//心法升品引导
	JUNIOR_GUIDE_HMQUA_ONE = 9945, //满级心法图标左上角有升品提醒
	JUNIOR_GUIDE_HMQUA_TWO = 9946, //合成按钮变化为升品按钮
	//*------------------------------------<<新手指引内容>>------------------------------------------------*//


	//instance describe
	COPY_TYPE = 5476, //类型
	COPY_HARD_LEVEL = 5477, //难度
	COPY_SWEEP = 5478, //扫荡
	COPY_SWEEP_TIMES = 5479, //扫荡轮数
	COPY_SWEEP_RECORD = 5480, //扫荡记录
	COPY_CURRENT_ENERGY = 5481, //当前体力
	COPY_SWEEP_NEED_ENERGY = 5482, //扫荡%d轮需要%d点体力 
	COPY_SWEEP_PER_TIMES = 5483, //扫荡%d轮
	COPY_ALL_ENERGY_SWEEP = 5484, //全体力扫荡
	COPY_CURRENT_TIMES = 5485, //当前轮数：
	COPY_SWEEP_TIMES_NUM = 5486, //第%d次扫荡：
	COPY_AWARD = 5487, //副本奖励：
	COPY_DROP_GOODS = 5488, //掉落道具：
	COPY_BAG_NOT_ENOUGH = 5489, //背包空间不足，已自动停止扫荡
	COPY_PASS_CONDITION_TIME = 90304, //限时
	COPY_PASS_CONDITION_SURVIVE = 90305, //生存
	COPY_WIN_CONDITION = 90268, //通关

	//exchange_code_result
	ECR_WRONG_CODE = 90338,//错误的兑换码，请重新输入！
	ECR_EXCHENGED = 90339,//此兑换码已使用过 
	ECR_PLEASE_INPUT = 90340,//请输入兑换码
	ECR_SUCCESS = 90341,//兑换成功，请到背包查看！
	ECR_BAG_FULL = 90342,//背包已满，获取礼包失败。

	UG_BAG_FULL = 90343,//背包空位不足。

	//friends details
	FRIENDS_DETAIL_FUJIANG_NAME_NULL = 90192,//暂无副将
	FRIENDS_DETAIL_MENPAI_NULL = 90193,//暂无门派

	//loading scence
	LOADING_RESOUCES = 90345, // 资源加载中
	SELECT_ROLE_FIRST = 90359, //请选择一个角色

	INTO_INSTANCE_BAG_FULL = 90346, // 您的背包容量已满，将不会取得道具，是否进入副本？
	SWEEP_INSTANCE_BAG_FULL = 91056, //当前背包已满，将不能获得道具，是否进行扫荡？
	OPEN_ITEM_CONTAINER = 90348, // 是否花费%d元宝开启下一栏位
	SHOW_ENERGY = 90353, // 体力

	//login award
	LOGIN_AWARD_CAN_RECEIVE = 90144, // 领取
	LOGIN_AWARD_RECEIVED = 90145, // 已领取
	LOGIN_AWARD_NORMAL_TITLE = 19067, //累计%d天

	//宝石镶嵌区
	GEM_INLAY_SUCCESS = 23001,	//镶嵌成功
	GEM_SETOFF_SUCCESS = 23002,	//卸下成功
	GEM_INLAY_FULL_TIP = 23003,	//孔位已满，提升装备品质可开启更多孔位！
	GEM_INLAY_FULL_FONT = 23004,	//孔位已满
	GEM_OPEN_MORE_HOLE = 23005,	//提升装备品质可开启更多孔位
	GEM_FONT = 23006,	//宝石
	GEM_SETOFF_TIP = 23007,	//宝石拆卸成功
	GEM_INLAY_HOLE = 23008,	//镶嵌孔位
	GEM_INLAY_FONT = 23009,	//镶嵌
	GEM_GREEN_QUA_OPEN = 23012,	//绿色品质开启
	GEM_BLUE_QUA_OPEN = 23013,	//蓝色品质开启
	GEM_PURSE_QUA_OPEN = 23014,	//紫色品质开启
	GEM_ORANGE_QUA_OPEN = 23015,	//橙色品质开启

	GEM_COMBINE_NEED_MAT_FONT = 23010,    //需要道具
	GEM_COM_OUTPUT_MAT_FONT = 23011,    //产出道具
	GEM_COMBINE_ALL_FONT = 23016,    //全部合成
	GEM_COMBINE_LACK_COUNT = 23017,    //宝石不足，无法合成！
	GEM_COMBINE_LEVEL_LIMIT = 23018,	//当前宝石等级已为最高级！
	GEM_NOT_INLAY = 23019,    // 未镶嵌

	// 副将
	GENERAL_USE_EXP_ITEM = 15031,    //使用失败，当前无出战副将！
	GENERAL_FULL = 15032,    //副将栏已满！
	GENERAL_GET_EXP = 90632,	//%s获得了%d经验
};

enum Instance_Icon
{
	II_ELITE_ENABLE = 5126,
	II_ELITE_DISABLE = 5127,
	II_NORMAL_ENABLE = 5128,
	II_NORMAL_DISABLE = 5129,
	II_STAR_SOLID = 5130,
	II_STAR_HOLLOW = 5131,

	II_REQUEST_1 = 5117, // 正常颜色
	II_REQUEST_2 = 5118, // 灰色的
	II_REQUEST_3 = 5120, // 卷
};

enum ChatBoard_UI
{
	CHAT_UI_BTN_ALL_TAG = 90107,	//全部	
	CHAT_UI_BTN_WORLD_TAG = 90108,	//世界
	CHAT_UI_BTN_UNITED_TAG = 90109,	//门派
	CHAT_UI_BTN_SECRET_CHAT_TAG = 90110,	//密语(私聊）
	CHAT_UI_BTN_GUILD_TAG = 90111,	//系统公告
	CHAT_UI_BTN_EXPRESSION = 90112,	//物品/表情

};

typedef void(*call_back_handler_t)(void);
typedef struct Hit_Box
{
	int f_x_;
	int	b_x_;
	int	y_;
	int	max_z_;
	int	min_z_;
}Hit_Box;

typedef struct Attack_Box
{
	Hit_Box hit_box_;
	int add_x_;
	int add_z_;
}Attack_Box;

#endif /* __GAME_DEFINE_H__ */
