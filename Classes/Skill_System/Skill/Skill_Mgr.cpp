
#include <fstream>
#include "Skill_Mgr.h"

#ifdef GAME_CLIENT
#include "json/json_header.h"
#include "cocos2d.h"
#else
#include "json/json.h"
#endif

#define SKILL_FILE_NAME "game_data/skill/skill_config.json"

Skill_Mgr* Skill_Mgr::instance_ = 0;
Skill_Mgr::Skill_Mgr()
{
	m_is_load = false;
}

Skill_Mgr::~Skill_Mgr()
{
}
Skill_Mgr* Skill_Mgr::instance()
{
    if( NULL == instance_ )
        instance_ = new Skill_Mgr;

    return instance_;
}
void Skill_Mgr::cleanup()
{
	m_mapSkill.clear();
    m_is_load = false;
}

int Skill_Mgr::load_skill_data()
{
#ifdef GAME_CLIENT
    ssize_t size = 0;
    unsigned char* pData = 0;

    pData = cocos2d::FileUtils::getInstance()->getFileData
        (SKILL_FILE_NAME, "rb", &size);

    //         cocos2d::CCFileData data(SKILL_FILE_NAME, "rb");
    //         unsigned long nBufSize = data.getSize();
    //         char* pBuffer = (char*) data.getBuffer();	 

    Json::Reader j_reader;
    Json::Value root_value;
    if (!j_reader.parse((const char*) pData,(const char*) (pData+size), root_value))
    {	
        //cout << "parse failed!" << j_reader.getFormatedErrorMessages().c_str() << endl;
        //  exit(0);
		CCLOG("Skill_Mgr::load_skill_data parse error!!!");
        CC_SAFE_DELETE_ARRAY(pData);   
        return -1;
    }
#else
    std::ifstream fin(SKILL_FILE_NAME);
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
#endif

	Skill_Data con_cfg;
	memset(&con_cfg, 0, sizeof(Skill_Data));

	for (Json::Value::iterator iter = root_value.begin();
		iter != root_value.end();
		++iter)
	{
		int Id = 0;
		Json::Value &v = (*iter)["SA_ID"];
		if (!v.empty())
		{
			con_cfg.m_Attr[SA_ID] = v.asInt();
			Id = v.asInt();
		}
		v = (*iter)["SA_TARGET_TYPE"];
		if (!v.empty())
		{
			con_cfg.m_Attr[SA_TARGET_TYPE] = v.asInt();
		}
		v = (*iter)["SA_HURT_RESULT"];
		if (!v.empty())
		{
			con_cfg.m_Attr[SA_HURT_RESULT] = v.asInt();
		}
		v = (*iter)["SA_HURT_ROAD_X_MOVE"];
		if (!v.empty())
		{
			con_cfg.m_Attr[SA_HURT_ROAD_X_MOVE] = v.asInt();
		}
		v = (*iter)["SA_HURT_ROAD_Y_MOVE"];
		if (!v.empty())
		{
			con_cfg.m_Attr[SA_HURT_ROAD_Y_MOVE] = v.asInt();
		}
		v = (*iter)["SA_HURT_SKY_X_MOVE"];
		if (!v.empty())
		{
			con_cfg.m_Attr[SA_HURT_SKY_X_MOVE] = v.asInt();
		}
		v = (*iter)["SA_HURT_SKY_Y_MOVE"];
		if (!v.empty())
		{
			con_cfg.m_Attr[SA_HURT_SKY_Y_MOVE] = v.asInt();
		}
		v = (*iter)["SA_HURT_CNTER_MOVE"];
		if (!v.empty())
		{
			con_cfg.m_Attr[SA_HURT_CNTER_MOVE] = v.asInt();
		}
		v = (*iter)["SA_HURT_LEVEL"];
		if (!v.empty())
		{
			con_cfg.m_Attr[SA_HURT_LEVEL] = v.asInt();
		}
		v = (*iter)["SA_YINGZHI_TIME"];
		if (!v.empty())
		{
			con_cfg.m_Attr[SA_YINGZHI_TIME] = v.asInt();
		}

		v = (*iter)["SA_TARGET_RATE"];
		if (!v.empty())
		{
			con_cfg.m_Attr[SA_TARGET_RATE] = v.asInt();
		}
		v = (*iter)["SA_TARGET_BUFF_ID"];
		if (!v.empty())
		{
			con_cfg.m_Attr[SA_TARGET_BUFF_ID] = v.asInt();
		}
		v = (*iter)["SA_HURT_CHANGE_COLOR"];
		if (!v.empty())
		{
			con_cfg.m_Attr[SA_HURT_CHANGE_COLOR] = v.asInt();
		}
		v = (*iter)["SA_GET_MP"];
		if (!v.empty())
		{
			con_cfg.m_Attr[SA_GET_MP] = v.asInt();
		}
		v = (*iter)["SHAKE_ID"];
		if (!v.empty())
		{
			con_cfg.m_Attr[SA_SHAKE_ID] = v.asInt();
		}
		
		v = (*iter)["SA_SKILL_LEVEL_BUFF"];
		if (!v.empty())
		{
			int count = 0;
			for (Json::Value::iterator e_iter = v.begin();
				e_iter != v.end(); e_iter ++)
			{
				con_cfg.level_buff[count++] = (*e_iter).asInt();
			} 
		}

		m_mapSkill.insert(make_pair(Id, con_cfg));
	}

	return 0;
}

int Skill_Mgr::initialize()
{
	m_mapSkill.clear();

	load_skill_data();
        
	return 0;
}

Skill_Data* Skill_Mgr::GetSkillData(uint32 skillId)
{
	map<uint32, Skill_Data>::iterator it = m_mapSkill.find(skillId);
	if ( it == m_mapSkill.end() )
		return NULL;

	return &(*it).second;
}

bool Skill_Mgr::is_load()
{
	return m_is_load;
}