#ifndef _EVENT_SYSTEM_DATA_MGR_H__
#define _EVENT_SYSTEM_DATA_MGR_H__
#include <map>
#include <list>
#include <string>
#include "Event_Data.h"
using namespace std;
class event_system_data_mgr
{
public:
	static event_system_data_mgr* sharedInstance();
	int init();
	void getEventDataMap(map<int,Event_Data> &map_t);
	void getEventDataById(int id,Event_Data& event_data);
private:
	event_system_data_mgr();
	static event_system_data_mgr* instance_;
	void load_data(const char* filename);
	map<int,Event_Data> event_data_map_t;
};
#endif //_EVENT_SYSTEM_DATA_MGR_H__