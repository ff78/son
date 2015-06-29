/* -------------------------------------------------------------------------
//	�ļ���		��	Relation_Common.h
//	��������	��	���ڴ��Relation�Ĺ�������
// -----------------------------------------------------------------------*/

#ifndef _RELATION_COMMON_H
#define _RELATION_COMMON_H

#include <map>
#include "Network_Common/global_macros.h"

#define  MAX_OWN_FRIEND_COUNT		30         // �������к��Ѹ���
#define  MAX_APPLY_FRIEND_COUNT		30		   // ���ı�����ĺ��Ѹ���

// ������ӷ�������
enum ADD_RETURN_TYPE
{
	ART_FAILD			= 0,
	ART_SUCCESS			= 1,
	ART_NOT_ONLINE		= 2,
	ART_LIST_FULL		= 3,
	ART_ALREADY_FRIENDS = 4,
	ART_IN_BLACK_LIST	= 5,
	ART_ADD_SELF		= 6,
};

// �����б�����
enum FRIEND_LIST_TYPE
{
	FRIEND_LIST_TYPE_OWN	= 0,			   // ���е������б�
	FRIEND_LIST_TYPE_APPLY	= 1,			   // ������������б�
	FRIEND_LIST_TYPE_ERROR
};

// ��ǰ�ĺ��ѽ�������
enum CURRENT_FRIEND_LAYER_STATE
{
	CURRENT_FRIEND_LAYER_STATE_OWN		= 0,	// ��ǰ�ǽ���״̬�����еĺ��ѽ���״̬
	CURRENT_FRIEND_LAYER_STATE_APPLY	= 1,	// ��ǰ�ǽ���״̬������ĺ��ѽ���״̬
	CURRENT_FRIEND_LAYER_STATE_ERROR
};

// ��ϵ����
enum RELATION_TYPE
{
	RT_NONE								= 0,	// ��������
	RT_FRIEND							= 1,	// �����б�
	RT_APPLY							= 2		// �����б�
};

struct Relation_Data
{
	uint64				db_id_;					// ���ݿ�����
	int					role_id_;				// ��ɫID
	int					friend_role_id_;		// ���ѽ�ɫId
	char				name_[MAX_NAME_LEN + 1];// ��ɫ����
	int					level_;					// �ȼ�
	int					menpai_id_;				// ����
	int					general_id_;			// ����Id()
	int					type_;					// ��ϵ(1���� 2������)
	int					is_online_;				// �Ƿ�����(0 ������ 1����)
	int					sex_;					// ��ɫ�Ա�
	int					zhanli_;				// ս����
	int					nVipLevel;				// Vip�ȼ�
	int					nJob;					// ְҵ


	RELATION_TYPE	   eFriendType;				// ��������
};

// Ŀ����ѵ���ʾ��Ϣ
typedef struct _TARGET_FRIEND_INFO_FOR_SHOW
{
	int								nFriendLevel;															// ���ѵȼ�
	int								nFriendFighttingPower;													// ����ս����

    std::string						szFriendName;                                                           // ��������
    std::string						szFriendJobName;                                                        // ����ְҵ����
}TARGET_FRIEND_INFO_FOR_SHOW;
#endif // _RELATION_COMMON_H