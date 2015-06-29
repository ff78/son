/* -------------------------------------------------------------------------
//	�ļ���		��	Rank_Data.h
//	��������	��	���ڴ��Rank�Ĺ�������
// -----------------------------------------------------------------------*/

#ifndef _RANK_DATA_H
#define _RANK_DATA_H

#include <map>
#include <string>
#include "Network_Common/global_macros.h"

#define		MAX_RANK_COUNT			100													// �����������
#define		NO_PRESENT_RANKING		500													// û�н���������

// ���а�����
enum Rank_Type
{
	Rank_Type_PVP				=	0,													// ���а�����Ϊ����������
	Rank_Type_Level				=	1,													// ���а�����Ϊ�ȼ�����
	Rank_Type_Fighting_Power	=	2,													// ���а�����Ϊս��������
	Rank_Type_Money				=	3,													// ���а�����Ϊ��Ǯ����
	Rank_Type_Renown			=	4,													// ���а�����Ϊ��������
	Rank_Type_Error
};

// Ŀ������������
typedef struct __TARGET_RANKING_DATA
{
	int								nRoleID;											// ��ɫID
	int								nRoleBaseID;										// ��ɫ����ID
	int								nRanking;											// ����
	int								nJobID;												// ְҵID
	int								nAttributeValue;									// ����ֵ

    std::string						szName;                                             // �ǳ�
}TARGET_RANKING_DATA;

// Ŀ����������ʾ��Ϣ
typedef struct __TARGET_INDEX_INFO_FOR_SHOW
{
	int								nRanking;											// ����
	int								nAttributeValue;									// ����ֵ

    std::string						szTargetPlayerName;					// Ŀ����ҵ�����
    std::string						szTargetPlayerJobName;				// Ŀ�����ְҵ������
}TARGET_INDEX_INFO_FOR_SHOW;


// Ŀ�������ļ���ʾ��Ϣ
typedef struct __TARGET_INDEX_SIMPLE_INFO_FOR_SHOW
{
	int								nRanking;											// ����
	int 							nIconID;											// ��ƷID

	bool							bPresentVisible;									// �����Ƿ�ɼ�
}TARGET_INDEX_SIMPLE_INFO_FOR_SHOW;


#endif // _RANK_DATA_H







//#ifndef __RANK_H__
//#define __RANK_H__
//
//#include <list>
//#include <map>
//
//#include "Network_Common/global_macros.h"
//
//#ifdef YN_LINUX
//#include <string.h>
//#endif
//
//#define RANK_MAX                                    30
//
//#define ON_RANK_ROLE_LEVEL_LIMIT                    15      // �ϰ���С�ȼ�
//#define ON_RANK_ROLE_FIGHTING_CAPACITY_LIMIT        2000    // �ϰ���Сս��
//#define ON_RANK_ROLE_HAVE_GOLD_LIMIT                10000   // �ϰ���С��������
//
//using namespace std;
//namespace Game_Data
//{
//    // ���а�����
//    enum Rank_Type
//    {
//        RT_ROLE_LEVEL = 0,              // ��ҵȼ����а�
//        RT_ROLE_FIGHTING_CAPACITY,      // ���ս�����а�
//        RT_ROLE_HAVE_GOLD,              // ����������а�
//    };
//
//    struct Rank
//    {
//        Rank()
//        {
//            reset();
//        }
//
//        ~Rank()
//        {
//            reset();
//        }
//
//        void reset()
//        {
//            role_id_ = 0;                       
//            role_base_id_ = 0;
//            memset(name_,0,sizeof(name_));
//        }
//
//        int                     id_;                                // ���ݿ�ID
//        int                     role_id_;                           // ��ɫID
//        int                     role_base_id_;                      // ��ɫ����ID
//        char			        name_[MAX_NAME_LEN + 1];            // �ǳ�
//        int                     rank_attr_;                         // ��������
//    };
//
//    class Rank_Role_Level_Sort
//    {
//    public:
//        bool operator () (Rank* rank_1,Rank* rank_2) const  
//        {  
//            return rank_1->rank_attr_ > rank_2->rank_attr_;  
//        };
//    };
//
//    class Rank_Role_fighting_capacity_Sort
//    {
//    public:
//        bool operator () (Rank* rank_1,Rank* rank_2) const  
//        {  
//            return rank_1->rank_attr_ > rank_2->rank_attr_;  
//        };
//    };
//
//    class Rank_Role_have_gold_Sort
//    {
//    public:
//        bool operator () (Rank* rank_1,Rank* rank_2) const  
//        {  
//            return rank_1->rank_attr_ > rank_2->rank_attr_;  
//        };
//    };
//
//    typedef list<Rank*>                         Rank_List;
//    typedef Rank_List::iterator                 Rank_List_Iter;
//    typedef map<int,Rank*>                      Rank_Map;
//    typedef Rank_Map::iterator                  Rank_Map_Iter;
//}
//
//#endif /* __RANK_H__ */
//
