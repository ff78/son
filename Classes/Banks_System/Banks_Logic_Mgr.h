#pragma once
class Banks_Logic_Mgr
{
public:
	Banks_Logic_Mgr(void);
	~Banks_Logic_Mgr(void);
	static Banks_Logic_Mgr* instance();

public:
	int calculate_cost( int count );
	int calculate_exchanged_cold_by_token( int level, int cur_count );

private:
	static Banks_Logic_Mgr* instance_;

};

