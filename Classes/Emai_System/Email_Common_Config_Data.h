#ifndef _Email_Common_Config_Data_H_
#define _Email_Common_Config_Data_H_

#include <map>
#include "Network_Common/global_macros.h"
#include "email_data.h"

#define	MAX_EMAIL_COUNT					20									// 邮件的最大个数

// 当前邮件界面状态
enum Current_Email_Layer_State
{
	Current_Email_Layer_State_All		= 0,								// 当前邮件界面状态处于所有邮件状态
	Current_Email_Layer_State_Send		= 1,								// 当前邮件界面状态处于发送邮件状态
	Current_Email_Layer_State_Receive	= 2,								// 当前邮件界面状态处于接收邮件状态
	Current_Email_Layer_State_Error
};

// 邮件来源类型
enum Email_Source_Type
{
	Email_Source_Type_Official			= 0,								// 邮件来源于官方
	Email_Source_Type_Personal			= 1,								// 邮件来源于个人
	Email_Source_Type_Error
};

// 邮件数据
typedef struct __Email_Data
{
	int									_id;
	int									nItemID;							// 物品ID
	int									nSenderID;							// 发件人ID
	int									nReceiverID;						// 收件人ID

	//char								szSenderName[MAX_NAME_LEN];			// 发件人名字
	//char								szReceiverName[MAX_NAME_LEN];		// 收件人名字
	//char								szCreatTime[MAX_NAME_LEN];			// 发送的时间

	std::string							szSenderName;						// 发件人名字
	std::string							szReceiverName;						// 收件人名字
	std::string							szCreatTime;			// 发送的时间

	bool								bEmailIsRead;						// 邮件是否被阅读过

	std::string							strEmailContent;					// 邮件内容

	Email_Source_Type					eEmailSourceType;					// 邮件来源类型
}Email_Data;

// 邮件简单显示数据
typedef struct __Email_Data_For_Show
{
	int									_id;
	bool								bIsOfficialEmail;					// 是否为官方邮件
	bool								bIsRead;							// 是否阅读

	//char								szSenderName[MAX_NAME_LEN];			// 发件人名字
	std::string							szSenderName;		// 发件人名字
	std::string							szTitle;			// 标题
	std::string							szCreatTime;	// 发送的时间
}Email_Simple_Data_For_Show;

// 邮件详细显示数据
typedef struct __Email_Detail_Data_For_Show
{
	int									_id;
	int									nItemID;							// 物品ID

	//char								szSenderName[MAX_NAME_LEN];			// 发件人名字
	//char								szContent[MAX_NAME_LEN];			// 标题
	std::string 						szSenderName;						// 发件人名字
	std::string							szContent;							// 标题

}Email_Detail_Data_For_Show;

#endif