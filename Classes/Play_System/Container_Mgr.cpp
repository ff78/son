
 
#include "Container_Mgr.h"

#include <fstream>

#ifdef GAME_CLIENT
#include "json/json_header.h"
#include "cocos2d.h"
#else
#include "json/json.h"
#endif

#include "Container_Data.h"
#ifdef GAME_CLIENT
#define CONTAINER_FILE_NAME "game_data/Play_System/container_config.json"
#define STATIC_CONTAINER_FILE_NAME "game_data/Play_System/static_container_data_config.json"
#else
#define CONTAINER_FILE_NAME "../config/play_system/container_config.json"
#define STATIC_CONTAINER_FILE_NAME "../config/play_system/static_container_data_config.json"
#endif
namespace Game_Data
{
Container_Mgr* Container_Mgr::instance_ = 0;
Container_Mgr::Container_Mgr()
{

}

Container_Mgr::~Container_Mgr()
{

}
Container_Mgr* Container_Mgr::instance()
{
    if( NULL == instance_ )
    {
        instance_ = new Container_Mgr;
    }

    return instance_;
}
int Container_Mgr::initialize( void )
{
	container_config_lst_.clear();
	container_attribute_config_lst_.clear();
	load_container_config_data( CONTAINER_FILE_NAME, container_config_lst_);
	proc_all_container_data();
	proc_all_container_attribute_cell_data();

	return 0;
}
int Container_Mgr::get_json_value_by_file_name( Json::Value& root_value, const char* file_name)
{
#ifdef GAME_CLIENT
      //unsigned long size = 0;
	  ssize_t size = 0;
      unsigned char* pData = 0;

      CCLOG("Container_Mgr::get_json value by file_name %s", file_name);
      pData = cocos2d::FileUtils::getInstance()->getFileData
        (file_name, "rb", &size);

      cocos2d::CCFileData data(file_name, "rb");
      unsigned long nBufSize = data.getSize();
      char* pBuffer = (char*) data.getBuffer();	 

      Json::Reader j_reader;
      if (!j_reader.parse((const char*) pData,(const char*) (pData+size), root_value))
      {	
        CCLOG( "parse failed! %s", j_reader.getFormattedErrorMessages().c_str());
        //  exit(0);
        CC_SAFE_DELETE_ARRAY(pData);   
        return -1;
      }
#else
    std::ifstream fin(file_name);
	if (!fin)
	{
		return -1;
	}
	Json::Reader j_reader;
	if (!j_reader.parse(fin, root_value))
	{
		printf("/n%s/n", j_reader.getFormatedErrorMessages().c_str());
		return -1;
	}
#endif
    return 0;
}
int Container_Mgr::load_container_config_data( const char* file_name, std::list<Container_Config>& container_lst )
{

	Json::Value root_value;
    get_json_value_by_file_name(root_value, file_name );

	Container_Config con_cfg;

	for (Json::Value::iterator iter = root_value.begin();
		iter != root_value.end();
		++iter)
	{
		con_cfg.reset();
		Json::Value &v = (*iter)["container_key"];
		if (!v.empty())
		{
			con_cfg.set_container_key(v.asString().data());
		}
		v = (*iter)["container_json_file"];
		if (!v.empty())
		{
			con_cfg.set_container_json_file(v.asString().data());
		}
		
		container_lst.push_back(con_cfg);
	}

	return 0;
}


int Container_Mgr::proc_all_container_data( void )
{
	std::list<Container_Config>::iterator itc;
	Container_Data cd;
	for (itc = container_config_lst_.begin(); itc != container_config_lst_.end(); ++ itc )
	{
		cd.reset();
		load_container_data((*itc).get_container_json_file(), cd);
		container_attribute_config_lst_.insert(make_pair(cd.get_container_key(),cd));
	}

	return 0;
}

int Container_Mgr::proc_all_container_attribute_cell_data( void )
{

	std::map<string, Game_Element> cell_list;
	std::list<uint> id_lst;
	std::map<std::string, Container_Data>::iterator itc;
	for( itc = container_attribute_config_lst_.begin(); itc != container_attribute_config_lst_.end(); ++ itc )
	{
		cell_list.clear();
		id_lst.clear();
		itc->second.get_cell_id_list(id_lst);
		load_container_atttribut_data( itc->second.get_container_json_file(),id_lst, cell_list);
		itc->second.set_cell_list(cell_list);
	}
	return 0;
}

int Container_Mgr::load_container_atttribut_data(const char* file_name, std::list<uint>& id_lst, std::map<string, Game_Element>& cell_lst )
{

	Json::Value root_value;
    get_json_value_by_file_name(root_value, file_name );


	cell_lst.clear();
	id_lst.clear();
	Game_Element ge;
	for (Json::Value::iterator iter = root_value.begin();
		iter != root_value.end();
		++iter)
	{
		ge.reset();
		Json::Value &v = (*iter)["element_id"];
		if (!v.empty())
		{
			ge.set_cell_id(v.asInt());
		}
		v = (*iter)["element_key"];
		if (!v.empty())
		{
			ge.set_command(v.asString().data());
		}
		v = (*iter)["element_data_type"];
		if (!v.empty())
		{
			ge.set_data_type(v.asString().data());
		}
		v = (*iter)["db_save"];
		if (!v.empty())
		{
			ge.set_db_save(v.asInt());
		}
		id_lst.push_back(ge.get_cell_id());
		cell_lst.insert(make_pair(ge.get_command(), ge));
	}

	return 0;
}
int Container_Mgr::load_container_data(const char* file_name, Container_Data& cd )
{


	Json::Value root_value;
    get_json_value_by_file_name(root_value, file_name );


	cd.reset();
	for (Json::Value::iterator iter = root_value.begin();
		iter != root_value.end();
		++iter)
	{

		Json::Value &v = (*iter)["container_key"];
		if (!v.empty())
		{
			cd.set_container_key(v.asString().data());
		}
		v = (*iter)["container_id"];
		if (!v.empty())
		{
			cd.set_container_id(v.asInt());
		}
		v = (*iter)["container_json_file"];
		if (!v.empty())
		{
			cd.set_contianer_json_file(v.asString().data());
		}
		v = (*iter)["container_element_list"];
		for(Json::Value::iterator itj = v.begin(); itj != v.end(); ++ itj)
		{
			cd.add_cell_id_list((*itj).asUInt());
		}
		container_attribute_config_lst_.insert(make_pair(cd.get_container_key(), cd));
	}

 	return 0;
}

int Container_Mgr::get_container_attribute_data_by_key(const char* key,
													   std::map<string, Game_Element>& attribute_list)
{
	attribute_list.clear();
	std::map<std::string, Container_Data>::iterator itc;
	itc = container_attribute_config_lst_.find(key);
	if( itc != container_attribute_config_lst_.end())
	{
		itc->second.get_cell_list(attribute_list);
	}
	return 0;
}

}

