#include "Event_Data.h"
Event_Data::Event_Data()
{
	
}
Event_Data::~Event_Data()
{
	this->condition_element_data_list_.clear();
	this->trigger_element_data_list_.clear();
	this->function_element_data_list_.clear();
}
Event_Data::Event_Data(int id,list<Game_Element> condition,list<Game_Element> trigger,list< Game_Element >  function)
{
	this->id=id;
	this->condition_element_data_list_=condition;
	this->trigger_element_data_list_=trigger;
	this->function_element_data_list_=function;
}
void Event_Data::setId(int id)
{
	this->id=id;
}
int Event_Data::getId()
{
	return this->id;
}
void Event_Data::setCondition(list<Game_Element> &condition)
{

	this->condition_element_data_list_=condition;
}
void Event_Data::getCondition(list<Game_Element> &condition)
{
	condition=this->condition_element_data_list_;
}

void Event_Data::setTrigger(list<Game_Element> &trigger)
{
	this->trigger_element_data_list_=trigger;
}
void Event_Data::getTrigger(list<Game_Element> &trigger)
{
	trigger=this->trigger_element_data_list_;
}

void Event_Data::setFunction(list<Game_Element> &function)
{
	this->function_element_data_list_=function;
}
void Event_Data::getFunction(list<Game_Element> &function)
{
	function=this->function_element_data_list_;
}
