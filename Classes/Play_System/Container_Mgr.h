

#if !defined(EA_28E35EE7_1229_4970_9CDF_93DEAAAE94C8__INCLUDED_)
#define EA_28E35EE7_1229_4970_9CDF_93DEAAAE94C8__INCLUDED_


#include <list>
#include <map>

#include "Game_Interface/game_element.h"
#include "json/json_header.h"

namespace Game_Data
{
struct Container_Config;
struct Container_Data;
class Container_Mgr
{

public:
	Container_Mgr();
	virtual ~Container_Mgr();

	int initialize( void );

	int load_container_config_data( const char* file_name, std::list<Container_Config>& container_lst );
	
	int get_container_attribute_data_by_key(const char* key, 
		std::map<string, Game_Element>& attribute_list);

    int get_json_value_by_file_name( Json::Value& root_value, const char* file_name);

    static Container_Mgr* instance();
private:

	int proc_all_container_data(void);
	int load_container_data(const char* file_name, Container_Data& cd );
	int proc_all_container_attribute_cell_data( void );
	int load_container_atttribut_data(const char* file_name, std::list<uint>& id_lst,
		std::map<string, Game_Element>& cell_lst );


	//load
	int load_static_container_data();
	int load_static_container_element_data(const char* container_key, const char* file_name,
		std::map<string, Game_Element>& attibute_list, std::map<string, std::list < Game_Element > > & element_lst );
	int proce_container_element_data( std::list<Game_Element>& ge, Game_Element& ge_config, const char* value );
	// container config
	std::list<Container_Config> container_config_lst_;
	std::map<std::string, Container_Data> container_attribute_config_lst_;

    static Container_Mgr* instance_;


// game container data
// ---------- player list
// ---------- instance list
// ---------- stage list
// ---------- quest list


};
}

#endif // !defined(EA_28E35EE7_1229_4970_9CDF_93DEAAAE94C8__INCLUDED_)


