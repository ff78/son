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
	// Ԫ���һ�������ʽ �����̻������=1000+INT(���ǵȼ�/5+��ǰ�������/4+1)*400
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
