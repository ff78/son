
#ifndef __LOTTERY_DATA_COMMON_H__
#define __LOTTERY_DATA_COMMON_H__

#include <list>
#include <map>
#include "Game_Interface/common.h"
#include "Game_Interface/game_element.h"

#ifdef YN_LINUX
#include <string.h>
#endif

namespace Game_Data
{
	struct LotteryCategory
	{
		int category_id;
		int category_des_id;
		int category_icon_id;
		int category_quality_des_id;
		int free_cold_down_time;
		int free_count;
		int token_cost;
		int first_blood;
		int coupon_floor;
		int coupon_ceiling;
		int award_items_pool_id;
	};

	struct AwardItem
	{
		int item_id;
		int item_nums;
		int weights_floor;
		int weights_ceiling;
	};

	struct CouponItem
	{
		int index;
		int item_id;
		int cost;
		int exchange_nums;	
	};

	struct item_content
	{		
		item_content() 
		{
			item_element_vec_.clear();
		}

		~item_content() {}

		void reset()
		{
			item_element_vec_.clear();
		}

		item_content(const item_content& ic) 
		{
			item_element_vec_.clear();
			item_element_vec_ = ic.get_element();
		}

		item_content & operator = (const item_content& ic)
		{
			item_element_vec_.clear();
			item_element_vec_ = ic.get_element();
			return *this;
		}	
		void set_element(const game_element_list_t& gev) {item_element_vec_.clear(); item_element_vec_ = gev;}
		void get_element(game_element_list_t& gev) {gev.clear(); gev = item_element_vec_;}
		const game_element_list_t get_element() const {return item_element_vec_;}

	private:
		game_element_list_t item_element_vec_;
	};


	typedef map<uint64, AwardItem*>				AwardItem_Map;
	typedef AwardItem_Map::iterator				AwardItem_Map_Iter;

	typedef list<AwardItem*>			AwardItem_List;
	typedef AwardItem_List::iterator	AwardItem_List_Iter;

	typedef map<uint64, AwardItem_List>		AwardItemPool;

	typedef map<uint64, LotteryCategory*>		LotteryCategory_Map;
	typedef LotteryCategory_Map::iterator		LotteryCategory_Map_Iter;

	typedef list<LotteryCategory*>              LotteryCategory_List;
	typedef LotteryCategory_List::iterator		LotteryCategory_List_Iter;

	typedef vector<LotteryCategory*>            LotteryCategory_Vector;
	typedef LotteryCategory_Vector::iterator	LotteryCategory_Vector_Iter;
}

#endif /* __LOTTERY_DATA_COMMON_H__ */

