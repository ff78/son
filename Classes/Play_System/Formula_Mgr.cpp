

#include "Formula_Mgr.h"
#include "Formula_Data.h"

#ifdef GAME_CLIENT
#include "json/json_header.h"
#include "cocos2d.h"
#else
#include "json/json.h"
#endif

#include <fstream>

#include "Game_Interface/Game_Element_Parse.h"

#include "Container_Data.h"
#include "Container_Mgr.h"
#include "Instance_Data_Mgr.h"
#ifdef GAME_CLIENT
#define STATIC_CONTAINER_FILE_NAME "game_data/Play_System/static_container_data_config.json"
#define GAME_PLAY_CONFIG_FILE_NAME "game_data/Play_System/game_play_formula.json"
#include "cocos2d.h"
#else
#define STATIC_CONTAINER_FILE_NAME "../config/play_system/static_container_data_config.json"
#define GAME_PLAY_CONFIG_FILE_NAME "../config/play_system/game_play_formula/game_play_formula.json"
#endif
namespace Game_Data
{
Formula_Mgr* Formula_Mgr::instance_ = 0;
Formula_Mgr::Formula_Mgr()
{
#ifdef YN_LINUX		
        pthread_mutex_init(&formula_mutex_,NULL);
#endif
}

Formula_Mgr::~Formula_Mgr()
{
#ifdef YN_LINUX			
        pthread_mutex_destroy(&formula_mutex_);
#endif
}
Formula_Mgr* Formula_Mgr::instance()
{

    if( NULL == instance_ )
    {
        instance_ = new Formula_Mgr;
    }
    return instance_;
}
int Formula_Mgr::initialize( void )
{
	play_system_formula_data_lst_.clear();
	static_container_config_lst_.clear();
	static_container_data_list_.clear();

	play_system_fomula_list_.clear();
	load_static_formula_data();
	load_game_play_data();
	return 0;
}
int Formula_Mgr::load_game_play_data()
{
    Json::Value root_value;
    Container_Mgr::instance()->get_json_value_by_file_name(root_value,GAME_PLAY_CONFIG_FILE_NAME);

    return 0;
	Play_System_Formula psf;
	std::list<Game_Element> ge_lst;
	for (Json::Value::iterator iter = root_value.begin();
		iter != root_value.end();
		++iter)
	{
		psf.reset();

		Json::Value &v = (*iter)["id"];
		if (!v.empty())
		{
			psf.set_id(v.asInt());
		}
		v = (*iter)["key"];
		if (!v.empty())
		{
			psf.set_key(v.asString().data());
		}
		v = (*iter)["exec"];
		if (!v.empty())
		{
			string exec_str = v.asString();
			Game_Element_Parse::instance()->game_element_parse_cell(exec_str.data(), ge_lst, "cell");
			psf.set_exec_list(ge_lst);
		}
		play_system_fomula_list_.insert(make_pair(psf.get_id(), psf));
	}

	return 0;
}
int Formula_Mgr::load_static_formula_data()
{
	Container_Mgr::instance()->load_container_config_data(STATIC_CONTAINER_FILE_NAME,static_container_config_lst_);
	std::list<Container_Config>::iterator itc;
	std::map<string, Game_Element> attribute_list;
	std::map<int, Formula_Data> fd_lst;
	for (itc = static_container_config_lst_.begin(); itc != static_container_config_lst_.end(); ++ itc )
	{
		fd_lst.clear();

		Container_Mgr::instance()->get_container_attribute_data_by_key((*itc).get_container_key(),  attribute_list);
		load_static_formula_element_data((*itc).get_container_key(), 
			(*itc).get_container_json_file(),attribute_list, fd_lst);

		play_system_formula_data_lst_.insert(make_pair( (*itc).get_container_key(), fd_lst));
	}

	return 0;

}

int Formula_Mgr::load_static_formula_element_data(const char* /*container_key*/, const char* file_name, 
													  std::map<string, Game_Element>& attibute_list,
													  std::map<int, Formula_Data>& fd)
{

    Json::Value root_value;
    Container_Mgr::instance()->get_json_value_by_file_name(root_value,file_name);

	std::map<string, Game_Element>::iterator itg;
	std::list<Game_Element> ge_lst;
	std::list<Game_Command_Element> ge_cmd_lst;
	ge_lst.clear();
	Formula_Data fdata;
    vector<uint> para_vec;
	for (Json::Value::iterator iter = root_value.begin();
		iter != root_value.end();
		++iter)
	{
		fdata.reset();
		int id = atoi(iter.key().asString().data());
		fdata.set_formula_id(id);
		for( itg = attibute_list.begin(); itg != attibute_list.end(); ++ itg )
		{

			Json::Value &v = (*iter)[itg->second.get_command()];
			if (!v.empty())
			{
				proce_formula_element_data(ge_lst,ge_cmd_lst, itg->second, v.asString().data());
				fdata.add_formula_element_list(itg->second.get_command(),ge_lst);
                fdata.add_formula_command_element_list(itg->second.get_command(),ge_cmd_lst);
			}
		}
        ge_lst.clear();
        fdata.get_formula_element_list_by_key("id", ge_lst);
        para_vec.clear();    
        Game_Element_Parse::instance()->get_para_from_require_element( "id", ge_lst, para_vec);
        if( para_vec.size() > 0 )
            id = para_vec[0];
        fdata.set_formula_id(id);
		fd.insert(make_pair(id, fdata));
	}
	return 0;
}

int Formula_Mgr::proce_formula_element_data( std::list<Game_Element>& ge_lst,
                                            std::list<Game_Command_Element>& ge_cmd_lst, 
                                            Game_Element& ge_config, const char* value )
{

	std::string value_type = ge_config.get_data_type();
	Game_Element ge = ge_config;
	if( !value_type.compare("content") )
	{ 
		std::string content = value;
		ge_lst.clear();
		Game_Data::Game_Element_Parse::instance()->game_element_parse_cell(content.data(),ge_lst,"cell"); 
        Game_Data::Game_Element_Parse::instance()->game_element_parse_cmd(content.data(),ge_cmd_lst,"cell"); 

		return 0;
	}
	else if(!value_type.compare("value"))
	{
		list<uint> para;
		para.clear();
		para.push_back(atoi(value));
		ge.set_para_list(para);
		ge_lst.push_back(ge);
		return 0;
	}
	else if( !value_type.compare("string"))
	{
		list<std::string> para;
		para.clear();
		para.push_back(value);
		ge.set_para_str_list(para);
		ge_lst.push_back(ge);
		return 0;
	}
	else
	{
		ge.set_text(value);
		ge_lst.push_back(ge);
		return 0;
	}
	return -1;
}

int Formula_Mgr::get_play_system_formula_by_id( int id, Play_System_Formula& psf )
{
  #ifdef YN_LINUX		
  // Game_Logic::map_mutex m(&formula_mutex_);
#endif
	std::map<int, Play_System_Formula>::iterator itp;
	itp = play_system_fomula_list_.find( id);
	if( itp != play_system_fomula_list_.end())
	{
		psf = itp->second;
		return 0;
	}
	return -1;
}

int Formula_Mgr::get_formula_data(const char* key, int id, Formula_Data& fd )
{
#ifdef YN_LINUX		
  //  Game_Logic::map_mutex m(&formula_mutex_);
#endif
	std::map<std::string, std::map< int, Formula_Data > >::iterator itall;
	itall = play_system_formula_data_lst_.find(key);
	if( itall == play_system_formula_data_lst_.end())
		return -1;

	std::map<int, Formula_Data>::iterator itf;
	itf = itall->second.find(id);
	if( itf != itall->second.end() )
	{

		fd = itf->second;
		return 0;
	}

	return -1;
}

int Formula_Mgr::get_instance_dialog_id(  int /*player_id*/, int instance_id, int instance_finish )
{
	Game_Data::Formula_Data fd;
	if( -1 == get_formula_data("instance_attribute", instance_id, fd ))
		return -1;

    list<Game_Data::Game_Element> ge_lst;
    ge_lst.clear();
    
    if( instance_finish )
    {
        fd.get_formula_element_list_by_key("result_content", ge_lst);
    }
    else
    {
	    fd.get_formula_element_list_by_key("began_content", ge_lst);
    }

    vector<uint> para_u;
    Game_Data::Game_Element_Parse::instance()->get_para_from_require_element("dialog",ge_lst, para_u);
    if(para_u.size() < 1 )
        return -1;
   
    return (int)para_u[0];
}

int Formula_Mgr::get_time_limit( int instance_id, int& type )
{
    type = 0;
	Game_Data::Formula_Data fd;
	if( -1 == get_formula_data("instance_attribute", instance_id, fd ))
		return 0;

    list<Game_Data::Game_Element> ge_lst;
    ge_lst.clear();
	fd.get_formula_element_list_by_key("began_content", ge_lst);

    //get time limit
    int time_limit = 0;

   vector<uint> para_u;
   para_u.clear();
   Game_Data::Game_Element_Parse::instance()->get_para_from_require_element("instance_time_limit",ge_lst, para_u);
   if(para_u.size() > 0 )
   {
       time_limit = para_u[0];
       type = current_instance_data::INSTANCE_STATE_FAILE_OVER_TIME;
       return time_limit;
   }
   para_u.clear();
   Game_Data::Game_Element_Parse::instance()->get_para_from_require_element("keep_alive_time",ge_lst, para_u);
   if(para_u.size() > 0 )
   {
       time_limit = para_u[0];
       type = current_instance_data::INSTANCE_STATE_SUC_KEEP_ALIVE;
       return time_limit;
   }

    return time_limit;
}


}

