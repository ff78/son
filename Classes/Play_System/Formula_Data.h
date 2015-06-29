

#if !defined(EA_90C3EFE3_7EED_4519_84A9_EE2B5C9313FA__INCLUDED_)
#define EA_90C3EFE3_7EED_4519_84A9_EE2B5C9313FA__INCLUDED_

#include <string>
#include <list>
#include <map>

namespace Game_Data
{
struct Game_Element;
struct Game_Command_Element;
struct Formula_Data
{

	Formula_Data():formula_id_(0), formula_key_("")
	{
		formula_element_org_string_list_.clear();
		formula_element_data_list_.clear();
	}
	~Formula_Data() {}

	void reset( void )
	{
		formula_id_ = 0;
		formula_key_ = "";
		formula_element_org_string_list_.clear();
		formula_element_data_list_.clear();
	}

	void set_formula_id(int id) { formula_id_ = id; }
	int get_formula_id() {return formula_id_; }

	void set_formula_key( const char* key ) {formula_key_ = key;}
	const char* get_formula_key( void ) const { return formula_key_.data(); }

	void reset_formula_element_list(void) { formula_element_data_list_.clear();}
	int  add_formula_element_list( const char* key, std::list<Game_Element>& ele_lst )
	{
		formula_element_data_list_.insert(make_pair(key, ele_lst));
		return 0;
	}
	int get_formula_element_list_by_key(const char* key, std::list<Game_Element>& ele_lst)
	{
		std::map<std::string, std::list< Game_Element > >::iterator itg;
		itg = formula_element_data_list_.find(key);
		if( itg != formula_element_data_list_.end())
		{
			ele_lst = itg->second;
			return 0;
		}
		
		return -1;
	}

	void reset_formula_command_element_list(void) { formula_command_element_data_list_.clear();}
	int  add_formula_command_element_list( const char* key, std::list<Game_Command_Element>& ele_lst )
	{
		formula_command_element_data_list_.insert(make_pair(key, ele_lst));
		return 0;
	}
	int get_formula_command_element_list_by_key(const char* key, std::list<Game_Command_Element>& ele_lst)
	{
		std::map<std::string, std::list< Game_Command_Element > >::iterator itg;
		itg = formula_command_element_data_list_.find(key);
		if( itg != formula_command_element_data_list_.end())
		{
			ele_lst = itg->second;
			return 0;
		}
		
		return -1;
	}

private:
	int formula_id_;
	std::string formula_key_;

	std::map<std::string, std::string> formula_element_org_string_list_;
	std::map<std::string, std::list< Game_Element > > formula_element_data_list_; //key and process content such as : "[plot(1000,1)monster_wave(10000,1)][plot(10001,2)monster_wave(10001,2)][plot(10002,3)monster_wave(10002,3)]"
    std::map<std::string, std::list< Game_Command_Element> > formula_command_element_data_list_; 
};

struct Play_System_Formula
{
	Play_System_Formula(): id_(0), key_(""){ exec_lst_.clear();}
	~Play_System_Formula() {}

	void reset( void ) 
	{
		id_ = 0;
		key_ = "";
		exec_lst_.clear();
	}

	void set_id( int id ) { id_ = id; }
	int get_id( void ) { return id_; }

	void set_key( const char* key ) { key_ = key; }
	const char* get_key( void ) { return key_.data(); }

	int exec_list_clear( void ) { exec_lst_.clear(); return 0; }
	int add_cell_to_exec_list( Game_Element& ge ) { exec_lst_.push_back(ge); return 0; }
	int set_exec_list( std::list<Game_Element>& ge_lst) { exec_lst_ = ge_lst; return 0; }
	int get_exec_list( std::list<Game_Element>& ge_lst ) { ge_lst = exec_lst_; return 0; }
private:
	int id_;
	std::string key_;
	std::list<Game_Element> exec_lst_;
};
}
#endif // !defined(EA_90C3EFE3_7EED_4519_84A9_EE2B5C9313FA__INCLUDED_)
