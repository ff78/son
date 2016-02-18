#ifndef __JUNIOR_GUIDE_MGR__
#define __JUNIOR_GUIDE_MGR__

#include <map>
#include <string>
using namespace std;

#include "Junior_Guide_Config_Data.h"
class Junior_Guide_Mgr
{
public:
	Junior_Guide_Mgr(void);
	~Junior_Guide_Mgr(void);

public:
	static Junior_Guide_Mgr* get_instance();
	int initialize(void);

	junior_guide_config* get_config_by_id(int base_id);

private:
	int load_guide_desc_date();    //解析随机姓名 一个ID 对应一个junior_guide_config*

private:
	static Junior_Guide_Mgr*			instance_;
	map<int, junior_guide_config*>		m_map_guide_info_container;
};

#endif //__JUNIOR_GUIDE_MGR__