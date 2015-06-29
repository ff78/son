#ifndef _EMAIL_MODEL_H_
#define _EMAIL_MODEL_H_

#include "Email_Common_Config_Data.h"
#include "../Game_Interface/game_content_interface.h"

namespace Game_Model
{
	class Email_Manager
	{
	public:
		Email_Manager();
		~Email_Manager();

		int												 initialize();
		static Email_Manager*							 instance();

		inline std::vector<Email_Data>&					 getAllData(){ return  m_pAllEmailData; };
		inline void										 setAllData(const std::vector<Email_Data>& all){ m_pAllEmailData = all; };

		inline std::vector<Email_Simple_Data_For_Show>&  getSimpleData(){ return m_pSimpleEmailData; };
		inline void										 setSimpleData(const std::vector<Email_Simple_Data_For_Show>& simple){ m_pSimpleEmailData = simple; };

		inline std::vector<Email_Detail_Data_For_Show>&  getDetailData(){ return m_pDetailEmailData; };
		inline void										 setDetailData(const std::vector<Email_Detail_Data_For_Show>& detail){ m_pDetailEmailData = detail; };

		inline int  getCurrentIndex()			{ return m_nCurrentDealEmailIndex; };
		inline void	setCurrentIndex(int index)  { m_nCurrentDealEmailIndex = index; };

		inline int  getCurrentEmailId()			{ return _currentEmailId; };
		inline void	setCurrentEmailId(int id)   { _currentEmailId = id; };
	private:
		std::vector<Email_Data>					 m_pAllEmailData;																	
		std::vector<Email_Simple_Data_For_Show>	 m_pSimpleEmailData;																		
		std::vector<Email_Detail_Data_For_Show>	 m_pDetailEmailData;	

		std::string									_msgToSend;
		std::string									_targetNameToSend;
		int											_currentEmailId;
		int											m_nCurrentDealEmailIndex;																// 当前处理的邮件索引

		bool										m_bEmailListIsChange;																	// 邮件列表是否发生改变
		
		Current_Email_Layer_State			m_eCurrentState;																		// 当前显示层的邮件页面状态

		std::list<int>						m_pFreeEmailDataIndexList;	
		// 空闲的Buff时间数据列表							
		std::vector<email_data>				_emails;
	private:
		//---数据处理的相关方法---//

	public:
		//---相关逻辑处理---//
		void								DeleteTargetEmail(const int nIndex);													// 删除目标邮件

		bool								JudgeTargetIndexIsError(const int nIndex);												// 判断目标索引是否异常


	public:
		//---与显示层的交互---//	
		int									GetPlayerAllEmailsCount();																// 获取玩家所有的邮件的个数

		bool								UIRequestTargetIndexShowInfo(const int nIndex);		// 显示层请求目标索引的显示信息
		bool								UIRequestTargetIndexDetailShowInfo(const int nIndex, Email_Detail_Data_For_Show *pInfo);// 显示层请求目标索引的详细显示信息

		void								UIRequestDeleteTargetIndexEmail(const int nIndex);										// 显示层请求删除目标索引的邮件
		void								UIRequestReceiveTargetIndexEmailPresent();												// 显示层请求接收目标邮件的附属物品

	public:
		// 1. 发送消息到服务器
		void								SendMsgRequestDeleteTargetIndexEmail(const int nIndex);									// 发送消息请求删除目标邮件

		// 2. 从服务器接收消息

	public:
		//--获取与设置成员变量---//
		inline void setEmails(std::vector<email_data> emails)
		{
			_emails = emails;
		}
		inline std::vector<email_data> getEmails()
		{
			return _emails;
		}

		inline	void						SetCurrentEmailLayerState(const Current_Email_Layer_State eState)						// 设置当前显示层的邮件页面状态
		{
			m_eCurrentState = eState;
		}

		inline	Current_Email_Layer_State	GetCurrentEmailLayerState()																// 获取当前显示层的邮件页面状态
		{
			return m_eCurrentState;
		}

		inline void							SetCurrentEmailListIsChangeState(const bool bValue = false)
		{
			m_bEmailListIsChange = bValue;
		}

		inline bool							GetCurrentEmailListIsChangeState()
		{
			return m_bEmailListIsChange;
		}

		inline void							setMsgToSend(std::string msg)
		{
			_msgToSend = msg;
		}

		inline std::string					getMsgToSend()
		{
			return _msgToSend;
		}

		inline void							setTargetNameToSend(std::string name)
		{
			_targetNameToSend = name;
		}

		inline std::string					getTargetNameToSend()
		{
			return _targetNameToSend;
		}

	private:
		static Email_Manager*    g_pEmailManager;
	};
}
typedef Game_Model::Email_Manager EMAIL_MODEL;
//net
#define EVENT_EMAIL_SEND_LOAD "event_email_send_load"
#define EVENT_EMAIL_ON_LOAD "event_email_on_load"

#define EVENT_EMAIL_SEND_SEND "event_email_send_send"
#define EVENT_EMAIL_ON_SEND "event_email_on_send"

#define EVENT_EMAIL_ON_RECIEVE "event_email_on_recieve"
#define EVENT_EMAIL_ON_RECIEVE_SYSTEM "event_email_on_recieve_system"

#define EVENT_EMAIL_SEND_OPEN "event_email_send_open"
#define EVENT_EMAIL_ON_OPEN "event_email_on_open"

#define EVENT_EMAIL_SEND_DELETE "event_email_send_delete"
#define EVENT_EMAIL_ON_DELETE "event_email_on_delete"

//show
#define  EVENT_EMAIL_SHOW_OPEN "event_email_show_open"
#define  EVENT_EMAIL_SHOW_DELETE "event_email_show_delete"

namespace Game_Net
{
	class Email_Msg
	{
	public:
		bool init();
		static Email_Msg* getInstance();

		static bool send_load_email(Game_Logic::Game_Interface& gm_interface);
		static bool on_load_email(Game_Logic::Game_Interface& gm_interface);

		static bool send_send_email(Game_Logic::Game_Interface& gm_interface);
		static bool on_send_email(Game_Logic::Game_Interface& gm_interface);

		static bool on_recieve_email(Game_Logic::Game_Interface& gm_interface);
		static bool on_recieve_system_email(Game_Logic::Game_Interface& gm_interface);

		static bool send_open_email(Game_Logic::Game_Interface& gm_interface);
		static bool on_open_email(Game_Logic::Game_Interface& gm_interface);


		static bool send_delete_email(Game_Logic::Game_Interface& gm_interface);
		static bool on_delete_email(Game_Logic::Game_Interface& gm_interface);

	};
}
typedef Game_Net::Email_Msg EMAIL_NET;
#endif