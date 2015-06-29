
#define  CLIENT_VERSION_PATH_INFO "game_data/version.json"
#define  PARTITION_SERVER_LIST "game_data/Player_Account/partition_server_config.json"
#include "Player_Account/Account_Data.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "cocos2d.h"
#include "json/json_header.h"
USING_NS_CC;
Account_Data_Mgr* Account_Data_Mgr::instance_ = 0;
Account_Data_Mgr::Account_Data_Mgr():
    next_ui_config_id_(0),
    self_account_(""),
    avatar_id_(0),
    current_role_id_(0),
	m_nCurrentSelectIndex(-1),
    m_is_show_all_stage(0),
    m_is_first_login(0),
	m_version("")
{

}


Account_Data_Mgr::~Account_Data_Mgr()
{

}

Account_Data_Mgr* Account_Data_Mgr::instance()
{
    if( NULL == instance_ )
        instance_ = new Account_Data_Mgr;

    return instance_;
}

int Account_Data_Mgr::init(void)
{
    account_list_.clear();
    server_list_.clear();
    load_server_list("game_data/Player_Account/server_config.json");
	load_partition_server_info(PARTITION_SERVER_LIST);
    return 0;
}
int Account_Data_Mgr::load_server_list( const char* pzPath )
{


	/*
	Json::Value &version = root_value["version"];
	if (!version.empty())
	{
		m_version = version.asCString();
	}*/
	//unsigned long int sizev=0;
	ssize_t sizev = 0;
	unsigned char*	datav=0;
	//CCLog("load----------------------%s",(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(CLIENT_VERSION_PATH_INFO)).c_str());
	datav=cocos2d::FileUtils::getInstance()->getFileData(CLIENT_VERSION_PATH_INFO,"rb",&sizev);
	Json::Reader reader;
	Json::Value  versionvalue;
	if(!reader.parse((const char*)datav,(const char*)(datav+sizev),versionvalue))
	{
		printf("/n%s/n", reader.getFormattedErrorMessages().c_str());
		CC_SAFE_DELETE_ARRAY(datav);   
		return -1;
	}
	if(!versionvalue.empty())
	{
		m_version=versionvalue["version"].asCString();
	}



	server_list_.clear();
    //unsigned long size = 0;
	ssize_t size = 0;
    unsigned char* pData = 0;

    pData = cocos2d::FileUtils::getInstance()->getFileData(pzPath, "rb", &size);

	Json::Reader j_reader;
	Json::Value root_value;
	if (!j_reader.parse((const char*) pData,(const char*) (pData+size), root_value))
	{
		printf("/n%s/n", j_reader.getFormattedErrorMessages().c_str());
		CC_SAFE_DELETE_ARRAY(pData);   
		return -1;
	}
    Server_List_Data sld;

	

	Json::Value &server_list = root_value["server_list"];
	for (Json::Value::iterator iter = server_list.begin();
		iter != server_list.end();
		++iter)
	{

		sld.reset();
		Json::Value &v = (*iter)["id"];
		if (!v.empty())
		{
            sld.set_id(v.asInt());
		}
        v = (*iter)["server_name"];
		if (!v.empty())
		{
            sld.set_server_name(v.asString().c_str());
		}
		v = (*iter)["server_ip"];
		if (!v.empty())
		{
            sld.set_server_ip( v.asString().data());
		}
		v = (*iter)["server_port"];
		if (!v.empty())
		{
            sld.set_server_port(v.asInt());
		}
		v = (*iter)["next_ui"];
		if (!v.empty())
		{
            sld.set_next_ui(v.asInt());
		}

        server_list_.insert(make_pair(sld.get_id(), sld));
	}
    CC_SAFE_DELETE_ARRAY(pData);   
	return 0; 
}


int Account_Data_Mgr::load_partition_server_info( const char* pzPath )
{
	//unsigned long size = 0;
	ssize_t size = 0;
	unsigned char* pData = 0;
	pData = cocos2d::FileUtils::getInstance()->getFileData(pzPath, "rb", &size);

	Json::Reader j_reader;
	Json::Value root_value;
	if (!j_reader.parse((const char*) pData,(const char*) (pData+size), root_value))
	{
		printf("/n%s/n", j_reader.getFormattedErrorMessages().c_str());
		CC_SAFE_DELETE_ARRAY(pData);   
		return -1;
	}
	Json::Value &partition_server_ip = root_value["partition_server_ip"];
	if (!partition_server_ip.empty())
	{
		partition_server_ip_  = partition_server_ip.asString();
	}
	Json::Value &partition_server_port = root_value["partition_server_port"];
	if (!partition_server_port.empty())
	{
		partition_server_port_  = partition_server_port.asInt();
	}

	CC_SAFE_DELETE_ARRAY(pData);

	return 0;
}

int Account_Data_Mgr::load_server_list_from_str( const char* server_list_in_string , int size )
{
	std::string pData_str = server_list_in_string;

	Json::Reader j_reader;
	Json::Value root_value;

	const char* pData = pData_str.c_str();

	if (!j_reader.parse((const char*) pData,(const char*) (pData+size), root_value))
	{
		printf("/n%s/n", j_reader.getFormattedErrorMessages().c_str());
		CC_SAFE_DELETE_ARRAY(pData);   
		return -1;
	}
	Server_List_Data sld;

	server_list_.clear();

	Json::Value &server_list = root_value["server_list"];
	for (Json::Value::iterator iter = server_list.begin();
		iter != server_list.end();
		++iter)
	{

		sld.reset();
		Json::Value &v = (*iter)["id"];
		if (!v.empty())
		{
			sld.set_id(v.asInt());
		}
		v = (*iter)["server_name"];
		if (!v.empty())
		{
			sld.set_server_name(v.asString().c_str());
		}
		v = (*iter)["server_ip"];
		if (!v.empty())
		{
			sld.set_server_ip( v.asString().data());
		}
		v = (*iter)["server_port"];
		if (!v.empty())
		{
			sld.set_server_port(v.asInt());
		}
		v = (*iter)["next_ui"];
		if (!v.empty())
		{
			sld.set_next_ui(v.asInt());
		}
		v=(*iter)["server_state"];
		if(!v.empty())
		{
			sld.set_state(v.asInt());
		}
		server_list_.insert(make_pair(sld.get_id(), sld));
	} 
	return 0; 
}


int Account_Data_Mgr::get_server_list(map<int, Server_List_Data>& svr_lst)
{
    svr_lst.clear();
    svr_lst = server_list_;
    return 0;
}

int Account_Data_Mgr::get_server_list_by_id( int id, Server_List_Data& sld )
{
    map<int, Server_List_Data>::iterator its;
    sld.reset();
    its = server_list_.find( id);
    if( its != server_list_.end())
    {
        sld = its->second;
        return 0;
    }
    return -1;
}

int Account_Data_Mgr::add_acount( Account_Data& ad)
{
    map<string, Account_Data>::iterator ita;
    ita = account_list_.find( ad.get_account());
    if( ita == account_list_.end() )
    {
        account_list_.insert(make_pair(ad.get_account(), ad));
        return 0;
    }
    return -1;
}
int Account_Data_Mgr::get_account_by_name(const char* name, Account_Data& ad )
{
    map<string, Account_Data>::iterator ita;
    ita = account_list_.find( name );
    if( ita != account_list_.end() )
    {
        ad = ita->second;
        return 0;
    }
    return -1;
}
int Account_Data_Mgr::get_account_by_id( int id, Account_Data& ad )
{
    return 0;
}
int Account_Data_Mgr::modi_account_data_by_name(const char* name, Account_Data& ad)
{
    map<string, Account_Data>::iterator ita;
    ita = account_list_.find( name );
    if( ita != account_list_.end() )
    {
        ita->second = ad;
        return 0;
    }
    return -1;

}
int Account_Data_Mgr::modi_account_by_id( int id, Account_Data& ad )
{
    return 0;
}
int Account_Data_Mgr::get_self_account( Account_Data& ad )
{
    map<string, Account_Data>::iterator ita;
    ita = account_list_.find( get_self_account() );
    if( ita != account_list_.end() )
    {
        ad = ita->second;
        return 0;
    }
    return -1;

}

void Account_Data_Mgr::set_avatar_id ( int sex ) 
{ 
    if (sex == 1)
    {
        avatar_id_ = 1;
    } 
    else
    {
        avatar_id_ = 2 ;
    } 
}

const Account_Data_Mgr::SRoleData* Account_Data_Mgr::get_current_select ( void )
{
	if (m_nCurrentSelectIndex>=0 && m_nCurrentSelectIndex<m_nRoleNum && m_nCurrentSelectIndex<MAX_ROLE_COUNT)
	{
		return &m_RoleData[m_nCurrentSelectIndex];
	}
	return 0;
}
