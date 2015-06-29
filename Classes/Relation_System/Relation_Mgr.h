#ifndef _RELATION_MGR_H_
#define _RELATION_MGR_H_

#include "Relation_System/Relation_Common.h"

class Relation_Manager
{
public:
	Relation_Manager();
	~Relation_Manager();

	int								initialize();																// ��ʼ��Relation_Manager
	static Relation_Manager*		instance();

private:
	//---��Ա����---//
	int								m_nCurrentRoleID;															// ��ǰ��ɫID

	bool							m_bOwnListIsGot;															// ���еĺ����б��Ƿ��ȡ��
	bool							m_bApplyListIsGot;															// ������ĺ����б��Ƿ��ȡ��
	bool							m_bOwnListChange;															// ���еĺ����б����ı����Ϣ�Ƿ񷵻�
	bool							m_bApplyListChange;															// ������ĺ����б����ı����Ϣ�Ƿ񷵻�

	Relation_Data*					m_pRelationData;															// ���еĺ������ݣ��������к����룩

	std::list<int>					m_pFreeRelationDataIndexList;												// ���еĺ������������б�

	std::map<int , int>				m_pOwnFriendMap;															// ���еĺ����б�Key��RoleID,Value��������
	std::map<int , int>				m_pApplyFriendMap;															// ����ĺ����б�Key��RoleID,Value��������

	CURRENT_FRIEND_LAYER_STATE		m_eCurrentLayerState;														// ��ǰ��ҳ��״̬
public:
	//---����߼�����---//
	void							AddFriendToList(const FRIEND_LIST_TYPE eType , Relation_Data * pData);		// ��Ӻ��ѵ������б���
	void							RemoveFriendFromList(const FRIEND_LIST_TYPE eType, const int nRoleID);		// �Ӻ����б����Ƴ�����
	void							AddFriendFromApplyToOwn();													// �������б���Ӻ��ѵ����к����б���

public:
	//---��ɫ���ܵ���ز���---//	

public:
	//---����ʾ��Ľ���---//		
	int								UIRequestCellCount();														// ��ʾ��򿪺��ѽ���������Ѹ���
	
	bool							UIRequestFriendRoleID(std::list<int> * pList);								// ��ʾ���������ID
	bool							UIRequestFriendShowInfo(const int nID, TARGET_FRIEND_INFO_FOR_SHOW * pData);// ��ʾ��������ѵ���ʾ��Ϣ
	bool							UIRequestEnterTargetLayerState(CURRENT_FRIEND_LAYER_STATE eState);			// ��ʾ���������Ŀ�����״̬

	void							UIRequestAddFriend(std::string strName);									// ��ʾ��������Ӻ���
	void							UIRequestDeleteFriend(int nRoleID);											// ��ʾ������ɾ������
	void							UIRequestAddFriendFromApply(int nRoleID);									// ��ʾ������������б���Ӻ���
public:
	//---��������Ľ���---//	
	// 1. ��������������Ϣ
	void							SendMsgRequestOwnFriendList();												// ������Ϣ��������б�
	void							SendMsgRequestApplyFriendList();											// ������Ϣ������������б�
	void							SendMsgRequestAddFriend(std::string strName);								// ������Ϣ������Ӻ���
	void							SendMsgRequestDeleteFriendFromOwnList(const int nRoleID);					// ������Ϣ��������к����б�ɾ������
	void							SendMsgRequestDeleteFriendFromApplyList(const int nRoleID);					// ������Ϣ�������������б�ɾ������
	void							SendMsgRequestAddFriendFromApplyList(const int nRoleID);					// ������Ϣ�������������б���Ӻ���

	// 2. �ӷ�����������Ϣ

public:
	//--��ȡ�����ó�Ա����---//
	// ��ȡ���к��ѵ�����
	inline int						GetOwnFriendCount()
	{
		int nCount = m_pOwnFriendMap.size();
		if (nCount > MAX_OWN_FRIEND_COUNT)
			return 0;
		
		return nCount;
	}

	// ��ȡ����ĺ��ѵ�����
	inline int						GetApplyFriendCount()
	{
		int nCount = m_pApplyFriendMap.size();
		if (nCount > MAX_APPLY_FRIEND_COUNT)
			return 0;

		return nCount;
	}

	// �������еĺ����б��Ƿ��ȡ״̬
	inline void						SetOwnFriendListGetState(const bool bValue = false)
	{
		m_bOwnListIsGot = bValue;
	}

	// ���ñ�����ĺ����б��Ƿ��ȡ״̬
	inline void						SetApplyFriendListGetState(const bool bValue = false)
	{
		m_bApplyListIsGot = bValue;
	}

	// ��ȡ���еĺ����б��Ƿ��ȡ״̬
	inline bool						GetOwnFriendListGetState()
	{
		return m_bOwnListIsGot;
	}

	// ��ȡ����ĺ����б��Ƿ��ȡ״̬
	inline bool						GetApplyFriendListGetState()
	{
		return m_bApplyListIsGot;
	}

	// �������еĺ����б��Ƿ�ı��״̬
	inline void						SetOwnFriendListChangeMsgBackState(const bool bValue = false)
	{
		m_bOwnListChange = bValue;
	}

	// ���ñ�����ĺ����б��Ƿ�ı�״̬
	inline void						SetApplyFriendListChangeState(const bool bValue = false)
	{
		m_bApplyListChange = bValue;
	}

	// ��ȡ���еĺ����б��Ƿ�ı��״̬
	inline bool						GetOwnFriendListChangeState()
	{
		return m_bOwnListChange;
	}

	// ��ȡ����ĺ����б��Ƿ�ı��״̬
	inline bool						GetApplyFriendListChangeState()
	{
		return m_bApplyListChange;
	}

private:
	static Relation_Manager*    g_pRelationManager;
};
#endif //_RELATION_MGR_H_
