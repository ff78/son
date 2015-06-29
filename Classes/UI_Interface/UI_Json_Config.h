#ifndef _UI_JSON_CONFIG_CLASS_
#define _UI_JSON_CONFIG_CLASS_

#include "Game_Interface/common.h"

class UI_Json_Config
{
public:
	UI_Json_Config() : id_(0) , name_("") {}

	void reset( void ) { id_=0; name_="";}

	void set_json_id( int id ) { id_ = id; }
	const int get_json_id( void ) { return id_; }

	void set_json_name( const char* name ) { name_ = name; }
	const char* get_json_name( void ) { return name_.data(); }

private:
	int id_;
	string name_;
};

#endif //_UI_JSON_CONFIG_CLASS_