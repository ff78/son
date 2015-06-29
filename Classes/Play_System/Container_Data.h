

#if !defined(EA_99933960_EED0_4bf4_87FA_159825928564__INCLUDED_)
#define EA_99933960_EED0_4bf4_87FA_159825928564__INCLUDED_

#include <string>
#include <list>
namespace Game_Data
{
struct Game_Element;
struct Container_Data
{

	Container_Data(): container_id_(0), container_key_(""){ cell_list_.clear(); cell_id_lst_.clear();}
	~Container_Data(){}

	int reset( void )
	{
		container_id_ = 0;
		container_key_ = "";
		cell_id_lst_.clear();
		cell_list_.clear();
		return 0;
	}

	void set_container_id( int id )	{	container_id_ = id;	}

	int get_container_id ( void ) { return container_id_; }

	void set_container_key( const char* key ) { container_key_ = key; }
	const char* get_container_key( void ) { return container_key_.data(); }

	void set_contianer_json_file( const char* file_name ) {container_json_file_ = file_name; }
	const char* get_container_json_file( void ) { return container_json_file_.data(); }
 
	int reset_cell_list(void) {cell_list_.clear(); return 0;}
	int insert_to_cell_list(Game_Element& ge) { cell_list_.insert(make_pair(ge.get_command(), ge)); return 0; }
	int get_cell_list( std::map<string, Game_Element>& cell_lst ){cell_lst.clear(); cell_lst = cell_list_; return 0;}
	int set_cell_list( std::map<string, Game_Element>& cell_lst ) {cell_list_ = cell_lst; return 0;}

	int reset_cell_id_list( void ) { cell_id_lst_.clear(); return 0; }
	int add_cell_id_list( uint id ) { cell_id_lst_.push_back(id); return 0; }
	int get_cell_id_list( std::list<uint>& lst ) { lst = cell_id_lst_; return  0;}
private:
	int container_id_;
	std::string container_key_;
	std::string container_json_file_;
	std::list<uint> cell_id_lst_;
	std::map<string, Game_Element> cell_list_;

};

struct Container_Config
{
	Container_Config():container_key_(""), containner_json_file_("") {}
	~Container_Config() {}

	int reset( void ) { container_key_ = ""; containner_json_file_ = ""; return 0;}

	void set_container_key( const char* key ) {container_key_ = key;}
	const char* get_container_key( void ) { return container_key_.data(); }

	void set_container_json_file( const char* name ) { containner_json_file_ = name; }
	const char* get_container_json_file( void ) { return containner_json_file_.data(); }

private:
	std::string container_key_;
	std::string containner_json_file_;
};
}
#endif // !defined(EA_99933960_EED0_4bf4_87FA_159825928564__INCLUDED_)

