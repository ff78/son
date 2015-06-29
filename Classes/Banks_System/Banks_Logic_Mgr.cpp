#include "Banks_Logic_Mgr.h"
#include "Banks_Common.h"

Banks_Logic_Mgr* Banks_Logic_Mgr::instance_ = 0;

Banks_Logic_Mgr::Banks_Logic_Mgr(void)
{
}


Banks_Logic_Mgr::~Banks_Logic_Mgr(void)
{
}

int Banks_Logic_Mgr::calculate_cost( int count )
{
	int cost = ( (count + 1) * EXCHANGE_TOKEN_UNIT_NUMS  );
	if ( MAX_EXCHANGE_TOKEN_NUMS < cost )
	{
		cost = MAX_EXCHANGE_TOKEN_NUMS;
	}
	return cost;
}

int Banks_Logic_Mgr::calculate_exchanged_cold_by_token( int level, int cur_count )
{
	// 元宝兑换银两公式 ：银铺获得银币=1000+INT(主角等级/5+当前购买次数/4+1)*400
	int gold = 1000 + ( int(level/5 + cur_count/4 + 1) )*400;
	return gold;
}

Banks_Logic_Mgr* Banks_Logic_Mgr::instance()
{
	if (!instance_)
	{
		instance_ = new Banks_Logic_Mgr;
	}
	return instance_;
}
