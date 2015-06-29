#ifndef __EMAIL_DATA_H__
#define __EMAIL_DATA_H__

#define TIME_LEN    64
#define EMAIL_MAX   30

#include "Network_Common/global_macros.h"
#include "Game_Interface/common.h"
#include <string>
#include <vector>

enum
{
	RT_EMAIL_SYSTEM = 1,
	RT_EMAIL_PLAYER,
};

struct  email_data
{
	int		        id;									// ID
	int				type;								// 邮件类型(系统，玩家)
	int				role_id;							// 发件人ID
	int				target_id;							// 收件人ID
	char			target_name[MAX_NAME_LEN + 1];		// 收件人名字
	bool			is_on_read;							// 是否阅读
	std::string		msg;								// 内容
	int				item_id;							// 物品ID
	char			send_time_[TIME_LEN + 1];			// 发送的时间
};

typedef std::map<int,std::vector<email_data*>>	Email_map;
typedef std::map<int, email_data*>				Email_map_by_database;
typedef Email_map::iterator         Email_Map_Iter;
typedef Email_map_by_database::iterator Email_Database_Iter;

#endif