#ifndef __GAME_DEFINE_H__
#define __GAME_DEFINE_H__

#define PROFILE_KEY_FIRST_ENTERGAME				"firstentergame"
#define PROFILE_KEY_FIRST_USERNAME				"username"
#define PROFILE_KEY_FIRST_PASSWORD				"password"

#define EACH_SCROLL_PANEL			4			//ÿ�����������4��������ʾ����
#if 1//yypp
#define NPC_DIALOGUE_OPTION			4			//npc�Ի�������ѡ����
#else
#define NPC_DIALOGUE_OPTION			8			//npc�Ի�������ѡ����
#endif
#define UI_HEARTMETHOD_LAYER_EQUIP_INFO  4		//��ʾװ��������

#define UI_HEAD_SUM_NUM		3
#define ENDLESS_TOWER_STATE_ID 5000				// �޾����½�ID
#define ENDLESS_TOWER_LAST_FLOOR 50009			// �޾������һ�صĹؿ�ID

enum NpcServiceType								//npc�������ͣ���ʾ��ʱ��Ҳ������Ⱥ�˳��
{
	NS_Shop = 0,						// �̵�
	NS_Mission_Compeleted,				// ��ɵ�û�ύ������
	NS_Mission_CanBeAccepted,			// �ɽ�����
	NS_Mission_Uncompelted,				// û����ɵ�����

	NS_Num
};

enum UI_Desc                            //������̶�������ʾ��Ϣ����
{
	UI_FATE = 90013,//����
	UI_RANKING = 90018,//���а�
	UI_SOCIAL = 90017,//�罻
	UI_SYSTEM = 90016,//ϵͳ
	UI_ASSISTANT = 90020,//����
	UI_ACTIVITY = 90019,//�
	UI_GIFT_BAG = 90021,//���

	//role UI
	ROLE_TITLE = 90008,//����
	ROLE_INFO = 90024,//��������
	ROLE_INTERDUCE = 90088,//�������
	ROLE_FONT = 90285, //����
	//lieutenant UI
	LIEUTENANT_TITLE = 90009,//����

	//bag UI
	BAG_TITLE = 90010,//����

	//skill UI
	SKILL_TITLE = 90014,//��ʽ

	//heart method UI
	HEART_METHOD_TITLE = 90011,//�ķ�
	HEART_METHOD_COMBINE = 90042,//�ķ��ϳ�
	HEART_METHOD_QUALITY_UP_TITLE = 90074,//�ķ���Ʒ

	//equipment UI
	EQUIPMENT_TITLE = 90501,//װ��
	COMMON_EXP_FONT = 90506,//����

	//equipment quality up UI
	EQUIPMENT_QUALITY_UP_TITLE = 90047,//װ����Ʒ
	EQUIPMENT_INTENSIFY = 90037,//ǿ��

	//store
	STORE_TITLE = 90038,//�̵�

	//mission UI
	MISSION_TITLE = 90012,//����
	MISSION_TITLE_ACCEPT = 90030,//�ѽ�����
	MISSION_TITLE_ABLE_ACCEPT = 90029,//�ɽ�����
	MISSION_TITLE_DAILY = 90031,//ÿ������
	MISSION_GO = 90032,//����ǰ��
	MISSION_PAGE_UP = 90033,//��һҳ
	MISSION_PAGE_DOWN = 90034,//��һҳ
	MISSION_QUIT = 90036,//��������

	//common attr
	COMMON_ROLE = 90023,//��ɫ
	COMMOM_COMBINE = 90027,//�ϳ�
	COMMON_PURCHASE = 90039,//����
	COMMON_SELL = 90041,//����
	COMMON_TAKE_OFF = 90040,//ж��
	COMMON_EQUIP = 90015,//װ��
	COMMON_LEVEL_UP = 90026,//����
	COMMON_QUALITY_UP = 90028,//��Ʒ
	COMMON_ASTART = 90160,//Ѱ·
	COMMON_EQUIP_EQUIPMENT = 90161,//װ��װ��
	COMMON_EQUIMENT_STRENGTHENING = 90162,//װ��ǿ��
	COMMON_XINFA_EQUIP = 90163,//װ���ķ�
	COMMON_EQUIPMENT_QUALITY_UP = 90164,//װ����Ʒ
	COMMON_SKILL_UP = 90165,//��ʽ����
	COMMON_LIEUTENANT_FIGHT = 90166,//������ս
	COMMON_XINFA_COMBINE = 90167,//�ķ��ϳ�
	COMMON_XINFA_QUALITY_UP = 90168,//�ķ���Ʒ
	COMMON_ROLE_QUALITY_UP = 90169,//������Ʒ
	COMMON_ROLE_QUALITY_UP_TITLE = 90170,//��ɫ��Ʒ
	COMMON_FATE_LEVEL_UP = 90620,//��������

	COMMON_UI_QUALITY_UP = 90028,//��Ʒ
	COMMON_USE = 90337,//ʹ��
	COMMON_ALL_GREEN_QUA_EQUIP = 90194,//һ����װ
	COMMON_TIDY_BAG = 90500,//������
	COMMON_REPUTATION_FONT = 90514,//����ֵ��
	COMMON_PINZHUANG_XINFA = 90516,//ƴװ�ķ�
	COMMON_EAT_MATERIAL = 90622,//����
	COMMON_SELECT_EAT_BOOK_NUM = 90623,//ѡ�����ɵ��ķ���%d��
	COMMON_GAIN_EXP = 90624,//��þ���
	COMMON_NEED_GOLD = 90625,//��������
	CONTAIN_SHIELD = 90629,//�����ں��������ַ�
	SURE_TO_EXIT_GAME = 90075,//ȷ���˳���Ϸ��
	SURE_EXIT = 90076,//ȷ��
	CANCEL_EXIT = 90077,//ȡ��
	COMMON_BACK = 90078,//����
	COMMON_QUIT = 90087,//�˳�
	TASKUNCOMPLETE = 90098,//ֻ�Ƕ����������ʲô��Ҳ�첻�˵ģ�
	SYSTEM_SETTING = 90099,//ϵͳ����
	ACCOUNT_MANAGE = 90100,//�˺Ź���
	GOBACK_TO_LOGIN = 90101,//���ص�¼
	STRATEGY_GUIDE = 90102,//����ָ��
	GAME_NOTICE = 90103,//��Ϸ����
	UIMUSIC_SETTING = 90104,//����
	UIEFFECT_SETTING = 90105,//��Ч
	UISHIELD_SETTING = 90106,//�������ģ��
	SYSTEM_FUNCTION = 90115,//ϵͳ����
	COMMON_SELL_GAIN_MONEY = 90252,//���ۻ������
	COMMON_WHEATHER_SELL = 90253,//�Ƿ���ۣ�
	COMMON_BUY_NEED_GOLD = 90254,//������Ҫ����
	COMMON_WEATHER_BUY = 90255,//�Ƿ���
	VERSION_BOT_SAME = 90179,//�汾��һ�£��������¿ͻ��ˡ�
	GAME_SERVER_FOR_CLIENT = 90184,//�ͷ�
	UI_LOGIN_TEXT = 90627,//��¼
	SERVER_ERROR = 90367,//����������
	CHANGE_ACCOUNT = 90368,//�����˺�
	ENTER_GAME = 90369,//������Ϸ
	SEE_ALL_SERVER = 90370,//�鿴ȫ��������
	CURRENT_SERVER = 90001,//��ǰ������
	LOGIN_SUCCEED_CHECKING_UPDATE = 90376,//��¼�ɹ������ڼ�����
	GETTING_SERVER_INFO = 90377,//���ڻ�ȡ��������Ϣ
	UPDATE_TIPS = 90378,//����ǰ���绷����WIFI��ʹ���ƶ������������Ƿ�������£�
	UPDATE_NOT_NOW = 90379,//�ݲ�����
	UPDATE_CONTINUE = 90380,//��������
	DOWNLODING = 90381,//��������
	UPDATE_PROGRESS = 90382,//���½���
	DOWNLOAD_SUCCEED_INSTALL = 90383,//���سɹ����밲װ����
	DOWNLOAD_SUCCEED_RESTART = 90384,//���سɹ�����������Ϸ
	NETWORK_FAILED = 90385,//��������ʧ��
	CREATE_FILE_FAILED = 90386,//�����ļ�ʧ��
	READING_RESOURCES_INFO = 90387,//���ڻ�����Ҫ���ص���Դ��Ϣ
	MAX_PLAYER = 90613,//�������������������Ժ����ԡ�
	INSTANCE_WILL_END = 90616,//������������
	FUNCTION_WITHOUT = 90628,//����δ����

	//�����������
	COMMON_GO_BACK_MAIN_CITY = 90392,//�س�
};

enum UI_Tips
{
	//�������Ϣ
	UA_LEVEL_FONT = 92009, //���ȼ���
	UA_LEVEL_LIMIT = 92010,// %d������
	UA_INTR_FONT = 92035, //��˵����
	UA_AWARD_FONT = 92036, //��������
	UA_TIME_FONT = 92037, //��ʱ�䡿
	UA_ENTER_FONT = 92018, //����
	UA_PASS_AWARD = 92025, //ͨ�ؽ�����
	UA_OPEN_LEVEL = 92027, //�����ȼ���
	UA_NEED_ENERGY = 92029, //����������
	UA_OPEN_TIME = 92031, //����ʱ�䣺
	UA_ENTER_TIMES = 92034, //���������
	UA_LEVEL = 92028, //%d��
	UA_ENERGY = 92030, //%d��

	UA_TIME_OUT = 92006, //���ڻʱ�䣬�޷����룡



	//�̵������Ϣ
	SP_CENTER_SIVER = 5902, //����
	SP_CENTER_GOLD_INGOLT = 5903,	//Ԫ��
	SP_CENTER_SPECIAL_SELLING = 5904,	//����
	SP_CENTER_GAIN_SILVER = 5905,	//��ȡ����
	SP_CENTER_GAIN_GOLD = 5907,	//��ȡԪ��
	SP_CENTER_GAIN_FONT = 90630,//��ã�
	SP_CENTER_SELL_NUM = 90631,//��������
	SHOP_PURCHASE_INFO = 5906, //�Ƿ񻨷�%dԪ������%d��%s��


	//����������ʾ��Ϣ
	FATE_ACUPOINT_NAME = 2809,	//Ѩλ��:
	FATE_ACUPOINT_SUC_RATE = 2810,	//�ɹ���:
	FATE_ACUPOINT_ADD_ATTR = 2811,	//�ӳ�����:
	FATE_ACUPOINT_NOW_GAIN = 2812,	//���ѻ��:
	FATE_ACUPOINT_ALL_GIFT = 2813,	//ȫͨ����:
	FATE_ACUPOINT_XIU_NUM = 2814,	//��������:
	FATE_ACUPOINT_HAS_REP = 2815,	//ӵ������:
	FATE_ACUPOINT_NEED_REP = 2816,	//��������:
	FATE_ACUPOINT_HAS_MON = 2817,	//ӵ������:
	FATE_ACUPOINT_NEED_MON = 2818,	//��������:
	FATE_ACUPOINT_COOL_TIME = 2819,	//��ȴʱ��:

	BAG_FULL_TIPS = 90200, //��������
	LACK_GOLD_COIN = 90201, //��������
	LACK_GOLD_INGOT = 90202, //Ԫ������
	LACK_POWER = 90320, //��������
	MATERIAL_INSTANCE_NOT_OPEN = 90203, //���ϲ���������δ����
	LACK_MATERIAL = 90204, //���ϲ���
	LEVEL_UP_SUCCESS = 90205, //�����ɹ�
	QUALITY_UP_SUCCESS = 90206, //��Ʒ�ɹ�
	ROLE_REACH_LEVEL_LIMIT = 90207, //��ɫ�ﵽ�ȼ�����
	INPUT_RIGHT_EMAIL = 90208, //�˺���������ȷ�����ʽ
	INPUT_ACCOUNT = 90209, //�����������˺�
	INPUT_PASSWORD = 90210, //��������������
	SKILL_REACH_MAX_LEVEL = 90211, //��ʽ�Ѵﵽ��ǰƷ�ʿ��������ȼ���������������ɫƷ��
	METEMPSYCHOSIS_SUCCESS = 90212, //ת���ɹ�
	LACK_EQUIPMENT_GRID = 90213, //װ�����޿�λ
	ASSEMBLE_SUCCESS = 90214, //ƴװ�ɹ�
	COMBINE_SUCCESS = 90215, //�ϳɳɹ�
	QUEUE_ALREADY_FULL = 90216, //��������
	HEART_METHOD_REACH_CUR_MAX_LEVEL = 90217, //�ķ��Ѵﵽ��ǰƷ�ʵ����ǿ���ȼ���������Ʒ 
	HEART_METHOD_REACH_LEVEL_LIMIT = 90218, //�ķ��Ѵ�ȼ�����
	EQUIPMENT_INTENSIFY_LESS_PROTAGONIST_LEVEL = 90219, //װ��ǿ���ȼ����ܳ������ǵȼ��������������ǵȼ�
	EQUIPMENT_INTENSIFY_SUCCESS = 90220, //ǿ���ɹ�
	EQUIPMENT_REACH_CUR_MAX_LEVEL = 90221, //װ���Ѵﵽ��ǰƷ�ʵ����ǿ���ȼ���������Ʒ
	EQUIPMENT_REACH_LEVEL_LIMIT = 90222, //װ���Ѵ�ȼ�����
	CURRENT_INSTANCE_NOT_CHANGE_ROLE = 90223, //��ǰ�������ܻ���
	NONE_USEABLE_ROLE = 90224, //û�п��ý�ɫ
	ROLE_ALREADY_DEAD = 90225, //��ɫ�Ѿ�����
	COOLING_TIME_RUNNING = 90226, //��ȴʱ��δ����
	BAG_FULL_FOR_AWARD_FAIL = 90227, //������������ȡ����ʧ��
	MISSION_ACCEPT_REACH_LIMIT = 90228, //�ѽ�����ﵽ����
	PASS_KONGFU_SUCCESS = 90229, //�����ɹ�
	EFFICIENT_PASS_KONGFU_SUCCESS = 90230, //��Ч�����ɹ�
	LACK_KONGFU_MEDICINE = 90231, //����������
	LIEUTENANT_LEVEL_LESS_PLAYER = 90232, //�����ȼ����ܳ������ǵȼ�����������������
	INPTU_KONGFU_ROLE_REACH_MAX_LEVEL = 90233, //�Ž��Ĵ�����ɫ���㹻ʹĿ���ɫ�ﵽ���ȼ�
	LACK_PASS_KONGFU_OBJECT = 90234, //������δ���ý�ɫ
	LACK_MISS_KONGFU_OBJECT = 90235, //ɢ����δ���ý�ɫ
	EVERY_TIME_ACCETT_MISSION_ONCE = 90236, //һ��ֻ�ܽ�ȡһ��ÿ������
	NONE_SEARCH_THIS_PERSON = 90237, //���޴���
	// 238 == 208 == 242
	ERROR_INPUT_PASSWORD = 90239, //�����������
	WAIT_FOR_UPDATE = 90240, //���ڸ��£����Ժ�
	EMAIL_NOT_BE_REGISTER = 90241, //������δ��ע��
	PASSWORD_INPUT_TYPE_TIPS = 90243, //����������6-12λ����ĸ�����֡����ϵ���ϣ���ĸ�ִ�Сд
	TWICE_PASSWORD_DISMATCH = 90244, //���벻һ��
	INPUT_CONFIRM_PASSWORD = 90245, //����������ȷ������
	EMAIL_ALREADY_REGISTER = 90246, //�������ѱ�ע��
	NAME_ALREADY_EXIST = 90247, //���ǳ��Ѵ���
	NAME_INPUT_TYPE_TIPS = 90248, //�ǳ�������2-16���ַ�����������ĸ�����֡����ֵ����
	INPUT_YOUR_NAME = 90249, //�����������ǳ�
	// 90250 90240 
	SERVER_DISCONNECT = 90251,//�����������Ѷϣ������Ժ��Ե�¼
	BUY_SUCCEED = 90261,//����ɹ�
	NET_DISCONNECT = 90262,//�����Զϣ������Ժ��Ե�¼

	//role dead tips
	TIPS_ROLE_DEAD = 90256, //������ʦ�����������˴��ڵ�
	TIPS_TIME_COUNT = 90257, //��󸱱�ʧ��
	TIPS_CHANGE_ROLE = 90258, //����
	TIPS_RECOVERY = 90259, //����
	TIPS_GIVE_UP = 90260, //����
	TIPS_EXPEND = 90263,//����
	TIPS_YUANBAO = 90264,//Ԫ��
	TIPS_FIGHT_AGAIN = 90265,//��ս����
	TIPS_LEFT_TIME = 90266,//��ʣ
	TIPS_SECOND = 90267,//��

	ROLE_AMOUNT_FULL = 90269, //���Ĵ�����ɫ��λ����
	CREATE_ROLE_FAILED = 90270, //������ɫʧ�ܣ�������
	QUIT_INSTANCE = 90271, //������δ��ɣ��Ƿ�ȷ���˳���
	QUEST_COMPLETE = 90272, //������ɣ�
	BUY_ENERGY_COUNT_LIMIT = 90273, //�������������������������
	LACK_ENERGY = 90274, //������������
	LACK_ROLE_LEVEL = 90275, //���ĵȼ�����
	LEVEL_NOT_REACH = 90276, //δ�ﵽ�ȼ�����
	QUALITY_MAX_LIMIT = 90277, //�Ѵﵽ���Ʒ��
	EQUIP_ITEM_LEVEL_LIMIT = 90278, //��Ʒ�ȼ���������ȼ�������װ������Ʒ
	EQUIPMENT_INTENSIFY_LESS_ROLE_LEVEL = 90279, //װ��ǿ���ȼ����ܳ��������ߵȼ����������������ߵȼ�
	TODAY_MISSION_TIMES_OVER = 90280, //��������������þ�
	TODAY_CHALLENGE_TIMES_OVER = 90281, //������ս�������þ�
	TODAY_PURCHASE_TIMES_OVER = 90282, //���չ���������þ�
	TODAY_GOT_OFFLINE_FIGHT_RANK_REWARD = 90283, //������ȡ���ս�����
	GOT_OFFLINE_FIGHT_RANK_REWARD = 90284, //���%d����%d��������

	ARENA_NOT_OPEN = 90290, //������δ����
	MATERIAL_NOT_OPEN = 90291, //����δ����
	EXCHANGE_COUNT = 90292, //�һ�(%d)
	ASSEMBLE_COUNT = 90293, //ƴװ(%d)
	EXCHANGE_SUCCESS = 90294, //�һ��ɹ�
	ARENA_OPEN_LEVEL = 90388, //������%d������

	//��Ӻ��ѷ�����ʾ
	ADD_FRIEND_SUCCESS = 90125, //��Ӻ��ѳɹ�!
	ADD_FRIEND_NOT_ONLINE = 90118, //%s�����ߡ�
	ADD_FRIEND_FULL = 90117, //��ĺ���������
	ADD_FRIEND_ALREADY_IS = 90126, //%s�������ĺ����б��
	ADD_FRIEND_BLACK_LIST = 90127, //%s�����ĺ������
	ADD_FRIEND_ADD_SELF = 90116, //��������Լ�Ϊ���ѡ�

	//���ɾ��������ʾ
	ADD_FRIEND_CONFIRM = 90128, //�Ƿ����%sΪ���ѣ�
	DELETE_FRIEND_CONFIRM = 90129, //�Ƿ�ɾ��%s���ѣ�
	SEND_MESSAGE_TO_SB = 90130, //��ԡ�%s��˵
	RECEIVE_MESSAGE_FROM_SB = 90131, //��%s������˵

	//Ǯׯ�һ���ʾ
	BANK_SUCCEED = 90389, //�������%d
	BANK_NOT_ENOUGH_TOKEN = 90390, //Ԫ�����㣬�޷��һ���
	BANK_HAVE_NO_CHANCE = 90391, //�һ������Ѵ�����


	//Secondary UI font  ��������������ʾ����
	MISSION_NEED_POWER = 90079, //��Ҫ����
	MISSION_AWARD_EXP = 90080, //���齱��
	MISSION_AWARD_MONEY = 90081, //��������
	MISSION_SUGGEST_LEVEL = 90082, //����ȼ�
	MISSION_DAY_TIMES = 90083, //���մ���
	MISSION_PASS_CONDITION = 90084, //ͨ������
	BUTTON_FONT_ENTER = 90085, //���븱��
	MISSION_MAYBE_GAIN = 90086, //���ܻ��

	//������������ֵ�
	MISSION_INTRODUCE = 90089,//����˵��
	MISSION_REWORD = 90090,//������
	MISSION_PUBLISH_NPC = 90091,//����npc
	MISSION_OVER_NPC = 90092,//���NPC
	MISSION_EXPERIENCE = 90093,//����:
	MISSION_GOLD = 90094,//����:
	MISSION_ACCEPT = 90095,//��������
	MISSION_DOITNOW = 90096,//����ǰȥ
	MISSION_OVER = 90097,//�������

	//��ʽ���������ֵ��
	SKILL_NEED_LEVEL = 90132, //�ȼ�����%s��
	SKILL_LEVEL_EQUAL_TO_ROLE_LEVEL = 90133, //��ʽƷ�����ɫƷ��һ��
	SKILL_NEED_MONEY_FOR_LEVEL_UP = 90134, //�������ã�%s ����
	SKILL_DAMAGE_NUM = 90135, //��ʽ�˺�
	SKILL_LEVEL_UP_BEFORE = 90136, //����ǰ
	SKILL_LEVEL_UP_AFTER = 90137, //������
	SKILL_NOT_REACH_REQUIRE = 90276, //δ�ﵽ�ȼ�����
	SKILL_WAIT_FOR_OPEN = 90138, //δ����
	SKILL_CURRENT_NAME = 90360, //��ʽ���ƣ�
	SKILL_CURRENT_LEVEL = 90361, //��ǰ�ȼ���
	SKILL_CURRENT_DESC = 90362, //��ʽ˵����
	SKILL_RELEASE_METHOD = 90363, //���з�ʽ��
	SKILL_RELEASE_PROMPT = 90364, //���ε�����°�ť
	SKILL_LEVEL = 90365, //�ȼ���
	SKILL_CURRENT_HARM = 90366, //�˺���

	//�������� ����
	LIEUTENANT_FIGHTING_FONT = 90140, //�����ս
	LIEUTENANT_QUIT_FIGHTING_FONT = 90141, //������ս
	LIEUTENANT_DISMISS_FONT = 90142, //ǲɢ

	//Ranking list Layer
	RANKING_LIST_FONT = 90601, //���а�
	//RANKING_LIST_ROLE					= 90602, //����
	RANKING_LIST_LEVEL = 90603, //�ȼ�
	RANKING_LIST_FIGHT = 90604, //ս��
	RANKING_LIST_GOLD = 90605, //����
	RANKING_LIST_RANK = 90606, //����
	RANKING_LIST_NAME = 90607, //����
	RANKING_LIST_GUILD = 90608, //����
	RANKING_LIST_U_RANK = 90609, //�������
	RANKING_LIST_NOT_RANK = 90610, //��δ�ϰ������Ŭ��
	FIGHT_FAIL_TIPS = 90611, //�Ѽ���ǿ��װ�����ķ�����ǿ���Լ�
	FIGHT_EXIT_INSTANCE = 90612, //�˳�����

	//����������
	ARENA_TODAY_CHALLENGE_TIMES = 90143, //���տ���ս%d��
	ARENA_RECEIVE = 90144, //��ȡ
	ARENA_ALREADY_RECEIVE = 90145, //����ȡ
	ARENA_RANGKING = 90146, //����
	ARENA_REPUTATION = 90147, //����
	ARENA_ARENE_TITLE = 90148, //������
	ARENA_RANKING_AWARD = 90149, //��������:
	ARENA_YESTERDAY_RANKING = 90150, //��������:
	ARENA_CURRENT_RANKING = 90151, //��ǰ����:
	ARENA_TOMORROW_AWARD = 90154, //���ս���:
	ARENA_INCREACE = 90152, //����
	ARENA_GOLD = 90155, //����
	ARENA_CUR_REPUTATION = 90617, //��ǰ������
	ARENA_TODAY_RANKING = 90618, //����������
	ARENA_AWARD_COUNTDOWN = 90619, //��ȡ����ʱ��

	//������ ���������ʾ����
	ARENA_CHALLENGE_WIN_FALL = 90286, //��ԡ�%s��������ս����ս���ˣ���ǰ����Ϊ�ڡ�%d��λ��
	ARENA_CHALLENGE_WIN_RAISE = 90287, //��ԡ�%s��������ս�����ʤ�ˣ���ǰ����Ϊ�ڡ�%d��λ��
	ARENA_BE_CHALLENGED_WIN_FALL = 90288, //��%s�����㷢����ս����ս���ˣ���ǰ����Ϊ�ڡ�%d��λ��
	ARENA_BE_CHALLENGED_WIN_RAISE = 90289, //��%s�����㷢����ս����սʤ�ˣ���ǰ����Ϊ�ڡ�%d��λ��

	//ģ̬�� ������Ϣ ��ʾ
	MODEL_LOADING_FONT = 90153, //�����С���
	MODEL_PURCHASE_ENERGY_FONT = 90157, //����20������Ҫ%dԪ����
	MODEL_PURCHASE_CHALLENGE_FONT = 90158, //ʹ��%dԪ������һ����ս����

	//show_alert  ��ʾ��Ϣ��ʾ ����
	ALERT_U_GAIN = 90308, //�������
	ALERT_GAIN_INFO = 90309, //[%s]x%d
	TIPS_LACK_REPUTATION = 90310, //��������
	TIPS_CHONG_FIRST = 90311, //��һ��
	TIPS_CHONG_SECOND = 90312, //�ڶ���
	TIPS_CHONG_THIRD = 90313, //������
	TIPS_CHONG_FOURTH = 90314, //������
	TIPS_CHONG_FIFTH = 90315, //������
	TIPS_CHONG_SIXTH = 90316, //������
	TIPS_OPEN_FOR_LEVEL = 90317, //%d������
	TIPS_OPEN_NEXT_LEVEL = 90318, //��һ��%d������
	TIPS_OPEN_ACUPOINT_FAILED = 90319, //��Ѩʧ��
	TIPS_OPEN_ACUPOINT = 90324, //��Ѩ
	TIPS_RESET = 90325, //����
	TIPS_COOL_TIME = 90326, //��ȴʱ��
	TIPS_CLEAN_COST = 90327, //ʹ��%dԪ��������ȴʱ��

	//��ҳ ��Ƭ��ʾ��ϢResidual_Page
	FRAGMENT_CURRENT_NO = 90306, //��δ�����Ƭ����Ŭ���ռ���
	RESIDUAL_PAGE_CURRENT_NO = 90307, //��δ��ò�ҳ����Ŭ���ռ���
	CAN_NOT_CHANGE_ROLE_INSTANCE = 90321, //��ǰ��������ʹ�ø���
	CAN_NOT_CHANGE_ROLE_DEATH = 90322, //��ɫ���������л�ʧ��
	CAN_NOT_CHANGE_ROLE_NOT_STAY = 90323, //û�и������ڳ�ս״̬
	//������Ϣ
	PLOT_FIRST_SENTENCE = 90185, //ǰ��ĩ�꣬Ⱥ�۸�ݣ�
	PLOT_SECOND_SENTENCE = 90186, //�����⻼����������
	PLOT_THIRD_SENTENCE = 90187, //�콵Ӣ�ܣ����ǻ��
	PLOT_FORTH_SENTENCE = 90188, //ͳһ��ԭ�������ۡ�
	PLOT_FIFTH_SENTENCE = 90189, //�����λ�䣬��̩�񰲡�Ȼ���ǰ����ɽ�۽�;�б�����
	PLOT_SIXTH_SENTENCE = 90190, //��̫�������в������£�����ս�Ҳ��ϣ��ݿܲ�ⱡ���
	PLOT_SEVENTH_SENTENCE = 90191, //ʮ�����Ļ�ɽ��������ɴ�չ������

	COMMON_CLICK_SCREEN_CONTINUE = 90183, //�����Ļ����

	//*------------------------------------<<����ָ������>>------------------------------------------------*//
	//���ν�����Ϸ
	JUNIOR_GUIDE_STORY = 9900, //���´��ң�˭�����������ǽ�����Ӣ�۴������֣�
	//Ѱ·��������
	JUNIOR_GUIDE_ASTAR = 9901, //Ѱ·���ܰ�����ֱ�ӽ�������Ŀ��ص�

	//����������
	JUNIOR_GUIDE_MISSION_ONE = 9902, //���񽻽ӽ�����ʾ����������Ϣ
	JUNIOR_GUIDE_MISSION_TWO = 9903, //����������Խ�������
	//�����������
	JUNIOR_GUIDE_MISSION_THR = 9904, //������������������
	//������������
	JUNIOR_GUIDE_INS_ONE = 9905, //�����񸱱�ͼ��ı�ʾ�ø����ǵ�ǰ������������ 
	JUNIOR_GUIDE_INS_TWO = 9906, //�ڽ��븱������ɲ鿴�˸����������Ϣ
	JUNIOR_GUIDE_INS_THR = 9907, //����˳������ص�����
	//ս����������
	JUNIOR_GUIDE_FIG_ONE = 9908, //������ɿ��ƽ�ɫ���ƶ�
	JUNIOR_GUIDE_FIG_TWO = 9909, //��������������������ס�ɴ�����ɫʹ��������
	JUNIOR_GUIDE_FIG_THR = 9910, //��ʽ�����ɵ������е�����빥����������ϰ���������ͬ����ʽ
	JUNIOR_GUIDE_FIG_FOR = 9911, //�����ͱ�������������ŭ��ֵ��ŭ��ֵ��ʱ����ɴ�����ɱ��
	//չ������������
	JUNIOR_GUIDE_OPEN = 9912, //����չ��������
	//��װ������
	JUNIOR_GUIDE_EQUIP_ONE = 9913, //��������򿪱���ҳ��
	JUNIOR_GUIDE_EQUIP_TWO = 9914, //���ѡ��װ��
	JUNIOR_GUIDE_EQUIP_THR = 9915, //���װ�������ɽ�����װ������ɫ����
	JUNIOR_GUIDE_EQUIP_FOR = 9916, //����ɹرյ�ǰ����
	JUNIOR_GUIDE_EQUIP_FIF = 9917, //�������װ�����ɵ���ж��װ����ѡ��
	//װ��ǿ������
	JUNIOR_GUIDE_EQUIP_QUA_ONE = 9918, //�������װ��ǿ����ҳ��
	JUNIOR_GUIDE_EQUIP_QUA_TWO = 9919, //���ѡ�������ϵ�װ��
	JUNIOR_GUIDE_EQUIP_QUA_THR = 9920, //����ɶ�ѡ���װ������ǿ��
	JUNIOR_GUIDE_EQUIP_QUA_FOR = 9921, //����ɹرյ�ǰ����
	//�ķ�װ������
	JUNIOR_GUIDE_XINFA_ONE = 9922, //��������ķ���ҳ��
	JUNIOR_GUIDE_XINFA_TWO = 9923, //���ѡ���ķ�
	JUNIOR_GUIDE_XINFA_THR = 9924, //���װ�������ɽ��ķ�װ������ɫ����
	//��ʽ��������
	JUNIOR_GUIDE_SKILL_UP_ONE = 9925, //���������ʽǿ����ҳ��
	JUNIOR_GUIDE_SKILL_UP_TWO = 9926, //�ɶ���Ҫ��������ʽ����ѡ��
	JUNIOR_GUIDE_SKILL_UP_THR = 9927, //����ɶ�ѡ�����ʽ��������
	//������ս����
	JUNIOR_GUIDE_LIE_FIG_ONE = 9928, //��������ɫ��ҳ��
	JUNIOR_GUIDE_LIE_FIG_TWO = 9929, //����ɶԸ�������ѡ��
	JUNIOR_GUIDE_LIE_FIG_THR = 9930, //�����ʹѡ�еĸ�����ս��һ��ֻ����һ��������ս
	JUNIOR_GUIDE_LIE_FIG_FOR = 9931, //�������ͷ��ɽ��������л�
	//�ķ��ϳ�����
	JUNIOR_GUIDE_HMCOM_ONE = 9932, //��������ķ���ҳ��
	JUNIOR_GUIDE_HMCOM_TWO = 9933, //���������ķ��ϳ�ҳ��
	JUNIOR_GUIDE_HMCOM_THR = 9934, //��һ�ε���Ļᱻ�Ƶ��ϳɿ���
	JUNIOR_GUIDE_HMCOM_FOR = 9935, //�������ε�����ᱻ�ϳɵ�
	JUNIOR_GUIDE_HMCOM_FIF = 9936, //����������кϳ�
	//������Ʒ����
	JUNIOR_GUIDE_ROLE_QUA_ONE = 9937, //�������������Ʒҳ��
	JUNIOR_GUIDE_ROLE_QUA_TWO = 9938, //ѡ��Ҫ��Ʒ�Ľ�ɫ
	JUNIOR_GUIDE_ROLE_QUA_THR = 9939, //�������������Ʒ
	//װ����Ʒ����
	JUNIOR_GUIDE_EQU_QUA_ONE = 9940, //ѡ����Ҫ��Ʒ��װ��
	JUNIOR_GUIDE_EQU_QUA_TWO = 9941, //���������Ʒ��ҳ��
	JUNIOR_GUIDE_EQU_QUA_THR = 9942, //�������������Ʒ
	//�ķ�ƴװ����
	JUNIOR_GUIDE_HMPZ_ONE = 9943, //��������ķ�ƴװҳ��
	JUNIOR_GUIDE_HMPZ_TWO = 9944, //���ƴװ
	//�ķ���Ʒ����
	JUNIOR_GUIDE_HMQUA_ONE = 9945, //�����ķ�ͼ�����Ͻ�����Ʒ����
	JUNIOR_GUIDE_HMQUA_TWO = 9946, //�ϳɰ�ť�仯Ϊ��Ʒ��ť
	//*------------------------------------<<����ָ������>>------------------------------------------------*//


	//instance describe
	COPY_TYPE = 5476, //����
	COPY_HARD_LEVEL = 5477, //�Ѷ�
	COPY_SWEEP = 5478, //ɨ��
	COPY_SWEEP_TIMES = 5479, //ɨ������
	COPY_SWEEP_RECORD = 5480, //ɨ����¼
	COPY_CURRENT_ENERGY = 5481, //��ǰ����
	COPY_SWEEP_NEED_ENERGY = 5482, //ɨ��%d����Ҫ%d������ 
	COPY_SWEEP_PER_TIMES = 5483, //ɨ��%d��
	COPY_ALL_ENERGY_SWEEP = 5484, //ȫ����ɨ��
	COPY_CURRENT_TIMES = 5485, //��ǰ������
	COPY_SWEEP_TIMES_NUM = 5486, //��%d��ɨ����
	COPY_AWARD = 5487, //����������
	COPY_DROP_GOODS = 5488, //������ߣ�
	COPY_BAG_NOT_ENOUGH = 5489, //�����ռ䲻�㣬���Զ�ֹͣɨ��
	COPY_PASS_CONDITION_TIME = 90304, //��ʱ
	COPY_PASS_CONDITION_SURVIVE = 90305, //����
	COPY_WIN_CONDITION = 90268, //ͨ��

	//exchange_code_result
	ECR_WRONG_CODE = 90338,//����Ķһ��룬���������룡
	ECR_EXCHENGED = 90339,//�˶һ�����ʹ�ù� 
	ECR_PLEASE_INPUT = 90340,//������һ���
	ECR_SUCCESS = 90341,//�һ��ɹ����뵽�����鿴��
	ECR_BAG_FULL = 90342,//������������ȡ���ʧ�ܡ�

	UG_BAG_FULL = 90343,//������λ���㡣

	//friends details
	FRIENDS_DETAIL_FUJIANG_NAME_NULL = 90192,//���޸���
	FRIENDS_DETAIL_MENPAI_NULL = 90193,//��������

	//loading scence
	LOADING_RESOUCES = 90345, // ��Դ������
	SELECT_ROLE_FIRST = 90359, //��ѡ��һ����ɫ

	INTO_INSTANCE_BAG_FULL = 90346, // ���ı�������������������ȡ�õ��ߣ��Ƿ���븱����
	SWEEP_INSTANCE_BAG_FULL = 91056, //��ǰ���������������ܻ�õ��ߣ��Ƿ����ɨ����
	OPEN_ITEM_CONTAINER = 90348, // �Ƿ񻨷�%dԪ��������һ��λ
	SHOW_ENERGY = 90353, // ����

	//login award
	LOGIN_AWARD_CAN_RECEIVE = 90144, // ��ȡ
	LOGIN_AWARD_RECEIVED = 90145, // ����ȡ
	LOGIN_AWARD_NORMAL_TITLE = 19067, //�ۼ�%d��

	//��ʯ��Ƕ��
	GEM_INLAY_SUCCESS = 23001,	//��Ƕ�ɹ�
	GEM_SETOFF_SUCCESS = 23002,	//ж�³ɹ�
	GEM_INLAY_FULL_TIP = 23003,	//��λ����������װ��Ʒ�ʿɿ��������λ��
	GEM_INLAY_FULL_FONT = 23004,	//��λ����
	GEM_OPEN_MORE_HOLE = 23005,	//����װ��Ʒ�ʿɿ��������λ
	GEM_FONT = 23006,	//��ʯ
	GEM_SETOFF_TIP = 23007,	//��ʯ��ж�ɹ�
	GEM_INLAY_HOLE = 23008,	//��Ƕ��λ
	GEM_INLAY_FONT = 23009,	//��Ƕ
	GEM_GREEN_QUA_OPEN = 23012,	//��ɫƷ�ʿ���
	GEM_BLUE_QUA_OPEN = 23013,	//��ɫƷ�ʿ���
	GEM_PURSE_QUA_OPEN = 23014,	//��ɫƷ�ʿ���
	GEM_ORANGE_QUA_OPEN = 23015,	//��ɫƷ�ʿ���

	GEM_COMBINE_NEED_MAT_FONT = 23010,    //��Ҫ����
	GEM_COM_OUTPUT_MAT_FONT = 23011,    //��������
	GEM_COMBINE_ALL_FONT = 23016,    //ȫ���ϳ�
	GEM_COMBINE_LACK_COUNT = 23017,    //��ʯ���㣬�޷��ϳɣ�
	GEM_COMBINE_LEVEL_LIMIT = 23018,	//��ǰ��ʯ�ȼ���Ϊ��߼���
	GEM_NOT_INLAY = 23019,    // δ��Ƕ

	// ����
	GENERAL_USE_EXP_ITEM = 15031,    //ʹ��ʧ�ܣ���ǰ�޳�ս������
	GENERAL_FULL = 15032,    //������������
	GENERAL_GET_EXP = 90632,	//%s�����%d����
};

enum Instance_Icon
{
	II_ELITE_ENABLE = 5126,
	II_ELITE_DISABLE = 5127,
	II_NORMAL_ENABLE = 5128,
	II_NORMAL_DISABLE = 5129,
	II_STAR_SOLID = 5130,
	II_STAR_HOLLOW = 5131,

	II_REQUEST_1 = 5117, // ������ɫ
	II_REQUEST_2 = 5118, // ��ɫ��
	II_REQUEST_3 = 5120, // ��
};

enum ChatBoard_UI
{
	CHAT_UI_BTN_ALL_TAG = 90107,	//ȫ��	
	CHAT_UI_BTN_WORLD_TAG = 90108,	//����
	CHAT_UI_BTN_UNITED_TAG = 90109,	//����
	CHAT_UI_BTN_SECRET_CHAT_TAG = 90110,	//����(˽�ģ�
	CHAT_UI_BTN_GUILD_TAG = 90111,	//ϵͳ����
	CHAT_UI_BTN_EXPRESSION = 90112,	//��Ʒ/����

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
