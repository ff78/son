#ifndef _RELATION_MGR_H_
#define _RELATION_MGR_H_

#include "Relation_System/Relation_Common.h"

class Relation_Manager
{
public:
	Relation_Manager();
	~Relation_Manager();

	int								initialize();																// 初始化Relation_Manager
	static Relation_Manager*		instance();

private:
	//---成员变量---//
	int								m_nCurrentRoleID;															// 当前角色ID

	bool							m_bOwnListIsGot;															// 已有的好友列表是否获取到
	bool							m_bApplyListIsGot;															// 被申请的好友列表是否获取到
	bool							m_bOwnListChange;															// 已有的好友列表发生改变的消息是否返回
	bool							m_bApplyListChange;															// 被申请的好友列表发生改变的消息是否返回

	Relation_Data*					m_pRelationData;															// 所有的好友数据（包括已有和申请）

	std::list<int>					m_pFreeRelationDataIndexList;												// 空闲的好友数据索引列表

	std::map<int , int>				m_pOwnFriendMap;															// 已有的好友列表（Key是RoleID,Value是索引）
	std::map<int , int>				m_pApplyFriendMap;															// 申请的好友列表（Key是RoleID,Value是索引）

	CURRENT_FRIEND_LAYER_STATE		m_eCurrentLayerState;														// 当前的页面状态
public:
	//---相关逻辑处理---//
	void							AddFriendToList(const FRIEND_LIST_TYPE eType , Relation_Data * pData);		// 添加好友到好友列表中
	void							RemoveFriendFromList(const FRIEND_LIST_TYPE eType, const int nRoleID);		// 从好友列表中移除好友
	void							AddFriendFromApplyToOwn();													// 从申请列表添加好友到已有好友列表中

public:
	//---角色技能的相关操作---//	

public:
	//---与显示层的交互---//		
	int								UIRequestCellCount();														// 显示层打开好友界面请求好友个数
	
	bool							UIRequestFriendRoleID(std::list<int> * pList);								// 显示层请求好友ID
	bool							UIRequestFriendShowInfo(const int nID, TARGET_FRIEND_INFO_FOR_SHOW * pData);// 显示层请求好友的显示信息
	bool							UIRequestEnterTargetLayerState(CURRENT_FRIEND_LAYER_STATE eState);			// 显示层请求进入目标界面状态

	void							UIRequestAddFriend(std::string strName);									// 显示层请求添加好友
	void							UIRequestDeleteFriend(int nRoleID);											// 显示层请求删除好友
	void							UIRequestAddFriendFromApply(int nRoleID);									// 显示层请求从申请列表添加好友
public:
	//---与服务器的交互---//	
	// 1. 给服务器发送消息
	void							SendMsgRequestOwnFriendList();												// 发送消息请求好友列表
	void							SendMsgRequestApplyFriendList();											// 发送消息请求申请好友列表
	void							SendMsgRequestAddFriend(std::string strName);								// 发送消息请求添加好友
	void							SendMsgRequestDeleteFriendFromOwnList(const int nRoleID);					// 发送消息请求从已有好友列表删除好友
	void							SendMsgRequestDeleteFriendFromApplyList(const int nRoleID);					// 发送消息请求从申请好友列表删除好友
	void							SendMsgRequestAddFriendFromApplyList(const int nRoleID);					// 发送消息请求从申请好友列表添加好友

	// 2. 从服务器接收消息

public:
	//--获取与设置成员变量---//
	// 获取已有好友的数量
	inline int						GetOwnFriendCount()
	{
		int nCount = m_pOwnFriendMap.size();
		if (nCount > MAX_OWN_FRIEND_COUNT)
			return 0;
		
		return nCount;
	}

	// 获取申请的好友的数量
	inline int						GetApplyFriendCount()
	{
		int nCount = m_pApplyFriendMap.size();
		if (nCount > MAX_APPLY_FRIEND_COUNT)
			return 0;

		return nCount;
	}

	// 设置已有的好友列表是否获取状态
	inline void						SetOwnFriendListGetState(const bool bValue = false)
	{
		m_bOwnListIsGot = bValue;
	}

	// 设置被申请的好友列表是否获取状态
	inline void						SetApplyFriendListGetState(const bool bValue = false)
	{
		m_bApplyListIsGot = bValue;
	}

	// 获取已有的好友列表是否获取状态
	inline bool						GetOwnFriendListGetState()
	{
		return m_bOwnListIsGot;
	}

	// 获取申请的好友列表是否获取状态
	inline bool						GetApplyFriendListGetState()
	{
		return m_bApplyListIsGot;
	}

	// 设置已有的好友列表是否改变的状态
	inline void						SetOwnFriendListChangeMsgBackState(const bool bValue = false)
	{
		m_bOwnListChange = bValue;
	}

	// 设置被申请的好友列表是否改变状态
	inline void						SetApplyFriendListChangeState(const bool bValue = false)
	{
		m_bApplyListChange = bValue;
	}

	// 获取已有的好友列表是否改变的状态
	inline bool						GetOwnFriendListChangeState()
	{
		return m_bOwnListChange;
	}

	// 获取申请的好友列表是否改变的状态
	inline bool						GetApplyFriendListChangeState()
	{
		return m_bApplyListChange;
	}

private:
	static Relation_Manager*    g_pRelationManager;
};
#endif //_RELATION_MGR_H_
