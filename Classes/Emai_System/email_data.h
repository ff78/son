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
	int				type;								// �ʼ�����(ϵͳ�����)
	int				role_id;							// ������ID
	int				target_id;							// �ռ���ID
	char			target_name[MAX_NAME_LEN + 1];		// �ռ�������
	bool			is_on_read;							// �Ƿ��Ķ�
	std::string		msg;								// ����
	int				item_id;							// ��ƷID
	char			send_time_[TIME_LEN + 1];			// ���͵�ʱ��
};

typedef std::map<int,std::vector<email_data*>>	Email_map;
typedef std::map<int, email_data*>				Email_map_by_database;
typedef Email_map::iterator         Email_Map_Iter;
typedef Email_map_by_database::iterator Email_Database_Iter;

#endif