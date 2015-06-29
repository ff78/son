/* -------------------------------------------------------------------------
//	文件名		：	Rank_Data.h
//	功能描述	：	用于存放Rank的公共数据
// -----------------------------------------------------------------------*/

#ifndef _RANK_DATA_H
#define _RANK_DATA_H

#include <map>
#include <string>
#include "Network_Common/global_macros.h"

#define		MAX_RANK_COUNT			100													// 最大排名个数
#define		NO_PRESENT_RANKING		500													// 没有奖励的排名

// 排行榜类型
enum Rank_Type
{
	Rank_Type_PVP				=	0,													// 排行榜类型为竞技场类型
	Rank_Type_Level				=	1,													// 排行榜类型为等级类型
	Rank_Type_Fighting_Power	=	2,													// 排行榜类型为战斗力类型
	Rank_Type_Money				=	3,													// 排行榜类型为金钱类型
	Rank_Type_Renown			=	4,													// 排行榜类型为声望类型
	Rank_Type_Error
};

// 目标排名的数据
typedef struct __TARGET_RANKING_DATA
{
	int								nRoleID;											// 角色ID
	int								nRoleBaseID;										// 角色形象ID
	int								nRanking;											// 排名
	int								nJobID;												// 职业ID
	int								nAttributeValue;									// 属性值

    std::string						szName;                                             // 昵称
}TARGET_RANKING_DATA;

// 目标索引的显示信息
typedef struct __TARGET_INDEX_INFO_FOR_SHOW
{
	int								nRanking;											// 排名
	int								nAttributeValue;									// 属性值

    std::string						szTargetPlayerName;					// 目标玩家的名字
    std::string						szTargetPlayerJobName;				// 目标玩家职业的名字
}TARGET_INDEX_INFO_FOR_SHOW;


// 目标索引的简单显示信息
typedef struct __TARGET_INDEX_SIMPLE_INFO_FOR_SHOW
{
	int								nRanking;											// 排名
	int 							nIconID;											// 物品ID

	bool							bPresentVisible;									// 礼物是否可见
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
//#define ON_RANK_ROLE_LEVEL_LIMIT                    15      // 上榜最小等级
//#define ON_RANK_ROLE_FIGHTING_CAPACITY_LIMIT        2000    // 上榜最小战力
//#define ON_RANK_ROLE_HAVE_GOLD_LIMIT                10000   // 上榜最小持有银两
//
//using namespace std;
//namespace Game_Data
//{
//    // 排行榜类型
//    enum Rank_Type
//    {
//        RT_ROLE_LEVEL = 0,              // 玩家等级排行榜
//        RT_ROLE_FIGHTING_CAPACITY,      // 玩家战力排行榜
//        RT_ROLE_HAVE_GOLD,              // 玩家银两排行榜
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
//        int                     id_;                                // 数据库ID
//        int                     role_id_;                           // 角色ID
//        int                     role_base_id_;                      // 角色形象ID
//        char			        name_[MAX_NAME_LEN + 1];            // 昵称
//        int                     rank_attr_;                         // 排序属性
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
