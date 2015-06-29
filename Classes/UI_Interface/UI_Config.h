
#if !defined(EA_2D61E99D_C682_495d_8F70_732E042A2015__INCLUDED_)
#define EA_2D61E99D_C682_495d_8F70_732E042A2015__INCLUDED_

#include "Game_Interface/common.h"

namespace Game_Data
{
struct UI_Config
{
	UI_Config() : id_(0),
		ui_name_(""),
		type_("")
	{
		func_lst_.clear();
	}

	void reset()
	{
		id_ = 0;
		ui_name_ = "";
		type_ = "";
		func_lst_.clear();
	}
	void set_id(int id)
	{
		id_ = id;
	}
	int get_id()
	{
		return id_;
	}
	void set_ui_name(const char* name)
	{
		ui_name_ = name;
	}
	const char* get_ui_name()
	{
		return ui_name_.data();
	}
	void set_type(const char* type)
	{
		type_ = type;
	}
	const char* get_type()
	{
		return type_.data();
	}
	int set_func_list( std::list<Game_Element>& gm_lst)
	{
		func_lst_ = gm_lst;
		return 0;
	}
	int get_func_list( std::list<Game_Element>& gm_lst)
	{
		gm_lst = func_lst_;
		return 0;
	}

	typedef map<int, UI_Config> UI_Config_t;
private:
	int id_;
	string ui_name_;
	string type_;
	std::list<Game_Element> func_lst_;
};
}
#endif // !defined(EA_2D61E99D_C682_495d_8F70_732E042A2015__INCLUDED_)
