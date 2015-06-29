

#if !defined(EA_547C0CC7_1236_447d_BAB5_5C48BA1D2FDD__INCLUDED_)
#define EA_547C0CC7_1236_447d_BAB5_5C48BA1D2FDD__INCLUDED_

#include "Game_Interface/common.h"
#include "Game_Interface/game_element.h"

#include <list>
#include <map>

namespace Game_Data
{
struct Container_Config;
struct Container_Data;
struct Formula_Data;
struct Play_System_Formula;
class Formula_Mgr
{

public:
	Formula_Mgr();
	virtual ~Formula_Mgr();

	int initialize( void );
	typedef std::map<uint, Container_Data> container_data_list_t;  //id and cell data list
	typedef std::map<string, container_data_list_t> contianer_static_data_list_t; // type(player, instance, quest) and static data 

	int get_play_system_formula_by_id( int id, Play_System_Formula& psf );
	int get_formula_data(const char* key, int id, Formula_Data& fd );

    static Formula_Mgr* instance();


    int get_instance_dialog_id(  int player_id, int instance_id, int instance_finish = 0 ); 
    int get_time_limit( int instance_id, int& type );
private:
	int load_game_play_data();

	//load
	int load_static_formula_data();
	int load_static_formula_element_data(const char* container_key, const char* file_name,
		std::map<string, Game_Element>& attibute_list, 
		std::map<int, Formula_Data>& fd_lst);
	int proce_formula_element_data( std::list<Game_Element>& ge_lst,std::list<Game_Command_Element>& ge_cmd_lst,
        Game_Element& ge_config, const char* value );

	// static formula data
// ----instance config data
// ----player config data
	std::map<std::string, std::map<int, Formula_Data > > play_system_formula_data_lst_;

	std::list<Container_Config> static_container_config_lst_;
	contianer_static_data_list_t static_container_data_list_;

	// play system---- game exec 
	std::map<int, Play_System_Formula> play_system_fomula_list_;

    static Formula_Mgr* instance_;
#ifdef YN_LINUX		
        pthread_mutex_t                     formula_mutex_;
#endif
};
}

#endif // !defined(EA_547C0CC7_1236_447d_BAB5_5C48BA1D2FDD__INCLUDED_)


