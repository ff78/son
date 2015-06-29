#include "Name_Random_Mgr.h"

#ifdef GAME_CLIENT
#include "json/json_header.h"
#include "cocos2d.h"
#else
#include "json.h"
#endif

#define NAME_CONFIG_FILE_PATH "game_data/Play_System/random_name_config.json"

Name_Random_Mgr* Name_Random_Mgr::instance_ = NULL;
Name_Random_Mgr::Name_Random_Mgr(void)
{
}


Name_Random_Mgr::~Name_Random_Mgr(void)
{
}

int Name_Random_Mgr::initialize( void )
{
	load_name_desc_date();

	return 0;
}


int Name_Random_Mgr::load_name_desc_date()
{
	m_map_name_container.clear();
#ifdef GAME_CLIENT
	//unsigned long size = 0;
	ssize_t size = 0;
	unsigned char* pData = 0;

	pData = cocos2d::FileUtils::getInstance()->getFileData(NAME_CONFIG_FILE_PATH, "rb", &size);

	Json::Reader j_reader;
	Json::Value root_value;
	if(!j_reader.parse((const char*)pData, (const char*)(pData+size), root_value))
	{
		cout<<"parse failed!"<<j_reader.getFormattedErrorMessages().c_str()<<endl;
		CC_SAFE_DELETE_ARRAY(pData);

		return -1;
	}
#else
	std::ifstream fin(EQUIPMENT_CONFIG_FILE_PATH);
	if (!fin)
	{
		return -1;
	}
	Json::Reader j_reader;
	Json::Value root_value;
	if (!j_reader.parse(fin, root_value))
	{
		printf("/n%s/n", j_reader.getFormatedErrorMessages().c_str());
		return -1;

	}
#endif // GAME_CLIENT

	int id = 0;
	for (Json::Value::iterator iter = root_value.begin(); iter!=root_value.end(); ++iter)
	{
		Json::Value &v = (*iter)["base_id"];
		if(!v.empty())
		{
			id = v.asInt();
		}

		string str;
		v = (*iter)["desc"];
		if(!v.empty())
		{
			str = v.asString();
		}

		m_map_name_container.insert(make_pair(id, str));
	}

	return 0;
}

const char* Name_Random_Mgr::get_name_by_id(int id)
{
	if( -1 == id)
		return "id == -1";

	map<int, string>::iterator iter = m_map_name_container.find(id);
	if(iter != m_map_name_container.end() )
		return (iter->second.data());

	return "id is not find";
}

Name_Random_Mgr* Name_Random_Mgr::get_instance()
{
	if(!instance_)
	{
		instance_ = new Name_Random_Mgr();
	}
	return instance_;
}