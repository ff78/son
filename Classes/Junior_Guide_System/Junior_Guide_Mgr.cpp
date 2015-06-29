#include "Junior_Guide_Mgr.h"
#ifdef GAME_CLIENT
#include "json/json_header.h"
#include "cocos2d.h"
#else
#include "json.h"
#endif

#define GUIDE_CONFIG_PATH "game_data/junior_guide_data/junior_guide_config.json"

Junior_Guide_Mgr* Junior_Guide_Mgr::instance_ = NULL;
Junior_Guide_Mgr::Junior_Guide_Mgr(void)
{
}


Junior_Guide_Mgr::~Junior_Guide_Mgr(void)
{
}



int Junior_Guide_Mgr::initialize( void )
{
	load_guide_desc_date();
	return 0;
}



int Junior_Guide_Mgr::load_guide_desc_date()
{
	m_map_guide_info_container.clear();

	//unsigned long size = 0;
	ssize_t size = 0;
	unsigned char* pData = 0;

	pData = cocos2d::FileUtils::getInstance()->getFileData(GUIDE_CONFIG_PATH, "rb", &size);

	Json::Reader j_reader;
	Json::Value root_value;
	if(!j_reader.parse((const char*)pData, (const char*)(pData+size), root_value))
	{
		cout<<"parse failed!"<<j_reader.getFormattedErrorMessages().c_str()<<endl;
		CC_SAFE_DELETE_ARRAY(pData);

		return -1;
	}

	junior_guide_config* config = NULL;
	for (Json::Value::iterator iter = root_value.begin(); iter!=root_value.end(); ++iter)
	{
		config = new junior_guide_config;
		memset(config, 0, sizeof(config));

		Json::Value &v = (*iter)["base_id"];
		if(!v.empty())
		{
			config->base_id_ = v.asInt();
		}

		v = (*iter)["desc"];
		if(!v.empty())
		{
			config->desc_ = v.asInt();
		}

		v = (*iter)["pos_x"];
		if(!v.empty())
		{
			config->pos_x_ = v.asInt();
		}

		v = (*iter)["pos_y"];
		if(!v.empty())
		{
			config->pos_y_ = v.asInt();
		}

		v = (*iter)["img_index"];
		if(!v.empty())
		{
			config->img_index_ = v.asInt();
		}

		m_map_guide_info_container.insert(make_pair(config->base_id_,config));
	}

	return 0;
}

junior_guide_config* Junior_Guide_Mgr::get_config_by_id( int base_id )
{
	if(-1 == base_id)
		return NULL;

	map<int, junior_guide_config*>::iterator iter = m_map_guide_info_container.find(base_id);
	if(iter != m_map_guide_info_container.end())
		return (iter->second);
	return NULL;
}

Junior_Guide_Mgr* Junior_Guide_Mgr::get_instance()
{
	if(!instance_)
		instance_ = new Junior_Guide_Mgr();
	return instance_;
}