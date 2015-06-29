#ifndef __RANK_MGR_H__
#define __RANK_MGR_H__

#include "Rank_System/Rank_Data.h"

class message_stream;

class Rank_Manager
{
public:
	Rank_Manager();
	~Rank_Manager();

	int											initialize();																					// 初始化Rank_Manager
	static Rank_Manager*						instance();

private:
	//---成员变量---//
	bool										m_bPVPRankTypeListIsGet;																		// 竞技场类型排行榜数据列表是否改变
	bool										m_bLevelRankTypeListIsGet;																		// 等级类型排行榜数据列表是否改变
	bool										m_bFightingPowerRankTypeListIsGet;																// 战斗力类型排行榜数据列表是否改变
	bool										m_bMoneyRankTypeListIsGet;																		// 金钱类型排行榜数据列表是否改变
	bool										m_bRenownRankTypeListIsGet;																		// 声望类型排行榜数据列表是否改变

	bool										m_bCurrentRankTypeListIsChange;																	// 当前排行榜类型的数据是否改变

	Rank_Type									m_eCurrentRankType;																				// 当前的排行榜类型

	TARGET_RANKING_DATA *						m_pPVPRankingDataList;																			// 竞技场类型排行榜数据列表
	TARGET_RANKING_DATA *						m_pLevelRankingDataList;																		// 等级类型排行榜数据列表
	TARGET_RANKING_DATA *						m_pFightingPowerRankingDataList;																// 战斗力类型排行榜数据列表
	TARGET_RANKING_DATA *						m_pMoneyRankingDataList;																		// 金钱类型排行榜数据列表
	TARGET_RANKING_DATA *						m_pRenownRankingDataList;																		// 声望类型排行榜数据列表

	std::map<Rank_Type, int>					m_pRankingListCountMap;																			// 各种类型排行榜列表个数
	std::map<Rank_Type, int>					m_pMyRankingMap;																				// 各种类型排行榜列表玩家的名次

public:
	//---相关逻辑处理---//
	int											GetMyRankingInTargetRankType(const Rank_Type eType);											// 获取我在目标排行榜类型中的排名

	bool										JudgeCurrentRankTypeListIsGet();																// 判断当前的排行榜列表是否获取
	bool										JudgeTargetIndexIsError(const int nIndex);														// 判断目标索引是否异常

	void										RequestTargetRankTypeList();																	// 获取当前的排行榜列表

	TARGET_RANKING_DATA *						GetTargetIndexRankingData(const int nIndex);													// 获取目标索引的排行榜数据

public:
	//---角色技能的相关操作---//	

public:
	//---与显示层的交互---//		
	int											UIRequestCurrentRankTypeCount();																// 显示层请求当前排行榜类型的排行榜个数

	bool										UIRequestEnterTargetRankLayer(const Rank_Type eType);											// 显示层请求进入目标排行榜界面
	bool										UIRequestTargetIndexShowInfo(const int nIndex, TARGET_INDEX_INFO_FOR_SHOW *pInfo);				// 显示层请求目标索引的显示信息
	bool										UIRequestTargetIndexSimpleShowInfo(const int nIndex, TARGET_INDEX_SIMPLE_INFO_FOR_SHOW *pInfo);	// 显示层请求目标索引简单的显示信息
	bool										UIRequestPlayerRankingSimpleShowInfo(TARGET_INDEX_SIMPLE_INFO_FOR_SHOW *pInfo);					// 显示层请求玩家本身简单的显示信息

	void										UIRequestCloseRankingListLayer();																// 显示层请求关闭排行榜界面

public:
	//---与服务器的交互---//	
	// 1. 发送消息到服务器
	void										SendMsgRequestTargetTypeRankingList(const Rank_Type eType);										// 发送消息请求目标类型排行榜数据列表

	// 2. 从服务器接收消息
	void										LoadPVPRankingDataList(message_stream& ms);														// 接收竞技场类型排行榜数据列表
	void										LoadLevelRankingDataList(message_stream& ms);													// 接收等级类型排行榜数据列表
	void										LoadFightingPowerRankingDataList(message_stream& ms);											// 接收战斗力类型排行榜数据列表
	void										LoadMoneyRankingDataList(message_stream& ms);													// 接收金钱类型排行榜数据列表
	void										LoadRenownRankingDataList(message_stream& ms);													// 接收声望类型排行榜数据列表

public:
	//--获取与设置成员变量---//
	inline bool									GetCurrentRankTypeIsChangeState()
	{
		return m_bCurrentRankTypeListIsChange;
	}

	inline void									SetCurrentRankTypeIsChangeState(const bool bValue = false)
	{
		m_bCurrentRankTypeListIsChange = bValue;
	}

private:
	static Rank_Manager*						g_pRankManager;
};
#endif //__RANK_MGR_H__




//#ifndef __RANK_MGR_H__
//#define __RANK_MGR_H__
//
//#include "Rank_Data.h"
//
//class message_stream;
//namespace Game_Data
//{
//    class Rank_Mgr
//    {
//    public:
//        Rank_Mgr();
//        virtual ~Rank_Mgr();
//        static Rank_Mgr* instance();
//        void release();
//
//    public:
//        void load_rank(message_stream& ms);
//        void load_rank_role_level(message_stream& ms);
//        void load_rank_role_fighting_capacity(message_stream& ms);
//        void load_rank_role_have_gold(message_stream& ms);
//
//        int get_rank_role_level_list(Rank_List& list);
//        int get_rank_role_fighting_capacity_list(Rank_List& list);
//        int get_rank_role_have_gold_list(Rank_List& list);
//
//    private:
//        static Rank_Mgr*                instance_;
//
//        Rank                            rank_role_level_array_[RANK_MAX];
//        Rank                            rank_role_fighting_capacity_array_[RANK_MAX];
//        Rank                            rank_role_have_gold_array_[RANK_MAX];
//    };
//}
//
//typedef Game_Data::Rank_Mgr RANK_MGR;
//
//
//#endif /* __RANK_MGR_H__ */
