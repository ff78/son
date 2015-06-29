#ifndef _EVENT_DATA_H__
#define _EVENT_DATA_H__
#include "Game_Interface/game_element.h"
using namespace Game_Data;
using namespace std;
class Event_Data
{
public:
	Event_Data();
	~Event_Data();
	Event_Data(int id,list<Game_Element> condition,list<Game_Element> trigger,list< Game_Element >  function);
	void setId(int id);
	int getId();
	void setCondition(list<Game_Element> &condition);
	void getCondition(list<Game_Element> &condition);

	void setTrigger(list<Game_Element> &trigger);
	void getTrigger(list<Game_Element> &trigger);

	void setFunction(list<Game_Element> &function);
	void getFunction(list<Game_Element>& ge_lst);
private:
	int id;
	list< Game_Element >  condition_element_data_list_;
	list< Game_Element >  trigger_element_data_list_;
	list< Game_Element >  function_element_data_list_;
};
#endif //_EVENT_DATA_H__