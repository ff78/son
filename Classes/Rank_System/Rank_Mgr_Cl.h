#ifndef __RANK_MGR_H__
#define __RANK_MGR_H__

#include "Rank_System/Rank_Data.h"

class message_stream;

class Rank_Manager
{
public:
	Rank_Manager();
	~Rank_Manager();

	int											initialize();																					// ��ʼ��Rank_Manager
	static Rank_Manager*						instance();

private:
	//---��Ա����---//
	bool										m_bPVPRankTypeListIsGet;																		// �������������а������б��Ƿ�ı�
	bool										m_bLevelRankTypeListIsGet;																		// �ȼ��������а������б��Ƿ�ı�
	bool										m_bFightingPowerRankTypeListIsGet;																// ս�����������а������б��Ƿ�ı�
	bool										m_bMoneyRankTypeListIsGet;																		// ��Ǯ�������а������б��Ƿ�ı�
	bool										m_bRenownRankTypeListIsGet;																		// �����������а������б��Ƿ�ı�

	bool										m_bCurrentRankTypeListIsChange;																	// ��ǰ���а����͵������Ƿ�ı�

	Rank_Type									m_eCurrentRankType;																				// ��ǰ�����а�����

	TARGET_RANKING_DATA *						m_pPVPRankingDataList;																			// �������������а������б�
	TARGET_RANKING_DATA *						m_pLevelRankingDataList;																		// �ȼ��������а������б�
	TARGET_RANKING_DATA *						m_pFightingPowerRankingDataList;																// ս�����������а������б�
	TARGET_RANKING_DATA *						m_pMoneyRankingDataList;																		// ��Ǯ�������а������б�
	TARGET_RANKING_DATA *						m_pRenownRankingDataList;																		// �����������а������б�

	std::map<Rank_Type, int>					m_pRankingListCountMap;																			// �����������а��б����
	std::map<Rank_Type, int>					m_pMyRankingMap;																				// �����������а��б���ҵ�����

public:
	//---����߼�����---//
	int											GetMyRankingInTargetRankType(const Rank_Type eType);											// ��ȡ����Ŀ�����а������е�����

	bool										JudgeCurrentRankTypeListIsGet();																// �жϵ�ǰ�����а��б��Ƿ��ȡ
	bool										JudgeTargetIndexIsError(const int nIndex);														// �ж�Ŀ�������Ƿ��쳣

	void										RequestTargetRankTypeList();																	// ��ȡ��ǰ�����а��б�

	TARGET_RANKING_DATA *						GetTargetIndexRankingData(const int nIndex);													// ��ȡĿ�����������а�����

public:
	//---��ɫ���ܵ���ز���---//	

public:
	//---����ʾ��Ľ���---//		
	int											UIRequestCurrentRankTypeCount();																// ��ʾ������ǰ���а����͵����а����

	bool										UIRequestEnterTargetRankLayer(const Rank_Type eType);											// ��ʾ���������Ŀ�����а����
	bool										UIRequestTargetIndexShowInfo(const int nIndex, TARGET_INDEX_INFO_FOR_SHOW *pInfo);				// ��ʾ������Ŀ����������ʾ��Ϣ
	bool										UIRequestTargetIndexSimpleShowInfo(const int nIndex, TARGET_INDEX_SIMPLE_INFO_FOR_SHOW *pInfo);	// ��ʾ������Ŀ�������򵥵���ʾ��Ϣ
	bool										UIRequestPlayerRankingSimpleShowInfo(TARGET_INDEX_SIMPLE_INFO_FOR_SHOW *pInfo);					// ��ʾ��������ұ���򵥵���ʾ��Ϣ

	void										UIRequestCloseRankingListLayer();																// ��ʾ������ر����а����

public:
	//---��������Ľ���---//	
	// 1. ������Ϣ��������
	void										SendMsgRequestTargetTypeRankingList(const Rank_Type eType);										// ������Ϣ����Ŀ���������а������б�

	// 2. �ӷ�����������Ϣ
	void										LoadPVPRankingDataList(message_stream& ms);														// ���վ������������а������б�
	void										LoadLevelRankingDataList(message_stream& ms);													// ���յȼ��������а������б�
	void										LoadFightingPowerRankingDataList(message_stream& ms);											// ����ս�����������а������б�
	void										LoadMoneyRankingDataList(message_stream& ms);													// ���ս�Ǯ�������а������б�
	void										LoadRenownRankingDataList(message_stream& ms);													// ���������������а������б�

public:
	//--��ȡ�����ó�Ա����---//
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
