

#ifdef YN_LINUX
#include <string.h>
#endif

#include "Instance_Data_Mgr.h"
#include <fstream>
#include <algorithm>

#include "Common/GameDefine.h"
#include "Container_Mgr.h"
#include "Game_Interface/Game_Element_Parse.h"
#include "Game_Interface/game_content_interface.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Play_System/Formula_Function_Instance.h"
#include "Common/Utils.h"
#ifdef GAME_CLIENT
    #include "json/json_header.h"
    #include "cocos2d.h"

    #define AREA_UI_CONFIG_FILE_PATH "game_data/Play_System/area_ui_config.json"
    #define INSTANCE_UI_CONFIG_FILE_PATH "game_data/Play_System/scene_ui_config.json"
    #define INSTANCE_DIALOG_FILE_PATH "game_data/Play_System/instance_dialog.json"
#else
    #include "json/json.h"

    #define AREA_UI_CONFIG_FILE_PATH "../config/play_system/instance_system/area_ui_config.json"
    #define INSTANCE_UI_CONFIG_FILE_PATH "../config/play_system/instance_system/instance_ui_config.json"
#endif
#ifdef GAME_CLIENT
    #include "cocostudio/CocoStudio.h"

    USING_NS_CC;
    using namespace cocostudio;
#endif

Instance_Data_Mgr* Instance_Data_Mgr::instance_ = 0;
Instance_Data_Mgr::Instance_Data_Mgr()
{
    m_map_area_ui_config.clear();
    m_map_instance_ui_config.clear();
#ifdef YN_LINUX		
        pthread_mutex_init(&instance_mutex_,NULL);
#endif
}

Instance_Data_Mgr::~Instance_Data_Mgr()
{
#ifdef YN_LINUX			
        pthread_mutex_destroy(&instance_mutex_);
#endif
}

Instance_Data_Mgr* Instance_Data_Mgr::instance()
{
    if( NULL == instance_ )
        instance_ = new Instance_Data_Mgr;

    return instance_;

}

int Instance_Data_Mgr::initialize( void )
{
    instance_state_ = 0;
    current_instance_id_ = 0;
    current_insance_stage_id_ = 0;
    current_prompt_instance_id_ = 0;
    current_prompt_type_ = 0;
    current_instance_type_ = 0;

    current_player_instance_data_.clear();
    player_instance_list_.clear();
    current_player_stage_instance_data_.clear();
    current_stage_state_lst_.clear();
    clear_current_dialog();
    instance_dialog_data_.clear();

    load_area_ui_config_data();
    load_instance_ui_config_data();
    load_instance_dialog_config_data();

    return 0;
}

void Instance_Data_Mgr::release( void )
{
    instance_state_ = 0;
    current_instance_id_ = 0;
    current_insance_stage_id_ = 0;
    current_prompt_instance_id_ = 0;
    current_prompt_type_ = 0;
    current_instance_type_ = 0;

    current_player_instance_data_.clear();
    player_instance_list_.clear();
    current_player_stage_instance_data_.clear();
    current_stage_state_lst_.clear();
    clear_current_dialog();
    instance_dialog_data_.clear();
}

int Instance_Data_Mgr::load_area_ui_config_data()
{
#ifdef GAME_CLIENT
    Json::Value root_value;
    if( -1 == Game_Data::Container_Mgr::instance()->get_json_value_by_file_name(root_value, AREA_UI_CONFIG_FILE_PATH))
        return -1;
#else
    std::ifstream fin(AREA_UI_CONFIG_FILE_PATH);
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

    //Area_UI_Config* config = NULL;
	for (Json::Value::iterator iter = root_value.begin();iter != root_value.end();++iter)
	{
        Area_UI_Config config;
        config.area_id = 0;
        config.name_id = 0;
        config.iconName = "";
        config.level_id = 0;
        config.list_instance_id.clear();

		Json::Value &v = (*iter)["area_id"];
		if (!v.empty())
		{
            config.area_id = v.asInt();
		}

		v = (*iter)["name_id"];
		if (!v.empty())
		{
            config.name_id = v.asInt();
		}
        v = (*iter)["icon"];
        if (!v.empty())
        {
            config.iconName = v.asString();
        }

        v = (*iter)["level_id"];
        if (!v.empty())
        {
            config.level_id = v.asInt();
        }

        v = (*iter)["open_id"];
        if (!v.empty())
        {
            config.open_id = v.asInt();
        }

        m_map_area_ui_config.insert(make_pair(config.area_id, config));
	}

    return 0;
}

int Instance_Data_Mgr::load_instance_ui_config_data()
{
    rapidjson::Document doc;
    std::string contentStr = FileUtils::getInstance()->getStringFromFile(INSTANCE_UI_CONFIG_FILE_PATH);
    
    doc.Parse < 0 > (contentStr.c_str());
    if (doc.HasParseError()) {
        return -1;
    }
    
    if (!doc.IsArray()){
        return -1;
    }
    
    Area_UI_Config* area_ui_config = NULL;
    int size = doc.Size();
    for (int i = 0; i<size; i++) {
        Instance_UI_Config config;
        memset(&config,0,sizeof(Instance_UI_Config));
        config.instance_id = DICTOOL->getIntValue_json(doc[i], "instance_id");
        config.area_id = DICTOOL->getIntValue_json(doc[i], "area_id");
        config.type = DICTOOL->getIntValue_json(doc[i], "type");
        config.x = DICTOOL->getIntValue_json(doc[i], "x");
        config.y = DICTOOL->getIntValue_json(doc[i], "y");
        config.open_id = DICTOOL->getIntValue_json(doc[i], "open_id");
        config.iconName = DICTOOL->getStringValue_json(doc[i], "icon");
        
        m_map_instance_ui_config.insert(make_pair(config.instance_id, config));
        area_ui_config = get_area_ui_config(config.area_id);
        if (area_ui_config)
        {
            area_ui_config->list_instance_id.push_back(config.instance_id);
        }
    }
    
//    Json::Value root_value;
//    if( -1 == Game_Data::Container_Mgr::instance()->get_json_value_by_file_name(root_value, INSTANCE_UI_CONFIG_FILE_PATH))
//        return -1;
//
//    Area_UI_Config* area_ui_config = NULL;
//    for (Json::Value::iterator iter = root_value.begin();
//        iter != root_value.end();
//        ++iter)
//    {
//        Instance_UI_Config config;
//        memset(&config,0,sizeof(Instance_UI_Config));
//
//        Json::Value &v = (*iter)["instance_id"];
//        if (!v.empty())
//        {
//            config.instance_id = v.asInt();
//
//        }
//
//        v = (*iter)["area_id"];
//        if (!v.empty())
//        {
//            config.area_id = v.asInt();
//        }
//
//        v = (*iter)["type"];
//        if (!v.empty())
//        {
//            config.type = v.asInt();
//        }
//
//        v = (*iter)["x"];
//        if (!v.empty())
//        {
//            config.x = v.asInt();
//        }
//
//        v = (*iter)["y"];
//        if (!v.empty())
//        {
//            config.y = v.asInt();
//        }
//
//        v = (*iter)["open_id"];
//        if (!v.empty())
//        {
//            config.open_id = v.asInt();
//        }
////        v = (*iter)["icon"];
////        if (!v.empty())
////        {
////            config.iconName = v.asString();
////        }
//
//        m_map_instance_ui_config.insert(make_pair(config.instance_id, config));
//
//        area_ui_config = get_area_ui_config(config.area_id);
//        if (area_ui_config)
//        {
//            area_ui_config->list_instance_id.push_back(config.instance_id);
//        }
//    }

    return 0;
}

int Instance_Data_Mgr::load_instance_dialog_config_data()
{

#ifdef GAME_CLIENT
	Json::Value root_value;
    Game_Data::Container_Mgr::instance()->get_json_value_by_file_name(root_value, INSTANCE_DIALOG_FILE_PATH );

    instance_dialog id_data;
    string str_cmd;
    std::list<Game_Data::Game_Command_Element> ge_cmd_lst;
    for (Json::Value::iterator iter = root_value.begin();
		iter != root_value.end();
		++iter)
	{
        id_data.reset();
		Json::Value &v = (*iter)["id"];
		if (!v.empty())
		{
            id_data.set_instance_dialog_id( v.asInt());
        }

		v = (*iter)["dialog_content"];
		if (!v.empty())
		{
            ge_cmd_lst.clear();
            str_cmd = v.asString();
            Game_Data::Game_Element_Parse::instance()->game_element_parse_cmd(str_cmd.data(),ge_cmd_lst,"cell");
            id_data.add_command_element_list(ge_cmd_lst);
        }

        instance_dialog_data_.insert( make_pair( id_data.get_instance_dialog_id(), id_data ) );
    }
#endif
    return 0;
}
Area_UI_Config* Instance_Data_Mgr::get_area_ui_config(int area_id)
{
    Area_UI_Config* config = NULL;
    Map_Area_UI_Config_Iter iter = m_map_area_ui_config.find(area_id);
    if (iter != m_map_area_ui_config.end())
    {
        config = &(iter->second);
		return  config;
    }
	return NULL;
}

Instance_UI_Config* Instance_Data_Mgr::get_instance_ui_config(int instance_id)
{
    Instance_UI_Config* config = NULL;
    Map_Instance_UI_Config_Iter iter = m_map_instance_ui_config.find(instance_id);
    if (iter != m_map_instance_ui_config.end())
    {
        config = &(iter->second);
    }

    return config;
}
int Instance_Data_Mgr::add_player_instance( int player_id,current_instance_data& cid)
{
#ifdef YN_LINUX		
        Game_Logic::map_mutex m(&instance_mutex_);
#endif
    map<int, current_instance_data>::iterator itc;
    itc = current_player_instance_data_.find(player_id);
    if( itc == current_player_instance_data_.end())
    {
        current_player_instance_data_.insert( make_pair(player_id, cid));
    }
    return 0;
}

int Instance_Data_Mgr::add_player_instance( int player_id, int instance_id, int scene_id, int monster_wave)
{
	/************************************************************************/
	// 添加玩家副本的数据
#ifdef YN_LINUX		
        Game_Logic::map_mutex m(&instance_mutex_);
#endif
    map<int, current_instance_data>::iterator itc;
    itc = current_player_instance_data_.find(player_id);
    if( itc == current_player_instance_data_.end())
    {
        current_instance_data cid;
        cid.reset();
        cid.set_player_id( player_id );
        cid.set_instance_id( instance_id);
        cid.set_monster_wave_require(monster_wave);
        cid.set_current_scene( scene_id );
        current_player_instance_data_.insert( make_pair(player_id, cid));
        return 0;
    }

    return -1;
}

int Instance_Data_Mgr::modi_player_instance( int player_id, current_instance_data& cid)
{
#ifdef YN_LINUX		
        Game_Logic::map_mutex m(&instance_mutex_);
#endif
    map<int, current_instance_data>::iterator itc;
    itc = current_player_instance_data_.find(player_id);
    if( itc != current_player_instance_data_.end())
    {
        itc->second = cid;
        return 0;
    }
    return -1;
}
int Instance_Data_Mgr::get_player_instance( int player_id, current_instance_data& cid)
{
#ifdef YN_LINUX		
  //      Game_Logic::map_mutex m(&instance_mutex_);
#endif
    map<int, current_instance_data>::iterator itc;
    itc = current_player_instance_data_.find(player_id);
    if( itc != current_player_instance_data_.end())
    {
        cid = itc->second;
        return 0;
    }
    return -1;
}
int Instance_Data_Mgr::remove_player_instance_data( int player_id )
{
	/************************************************************************/
	// 清除玩家副本数据
#ifdef YN_LINUX		
        Game_Logic::map_mutex m(&instance_mutex_);
#endif
    current_instance_id_ = 0;
    current_prompt_instance_id_ = 0;
    map<int, current_instance_data>::iterator itc;
    itc = current_player_instance_data_.find(player_id);
    if( itc != current_player_instance_data_.end())
    {
        current_player_instance_data_.erase(itc);
        return 0;
    }
    return -1;
}

int Instance_Data_Mgr::add_player_instance_lst( int player_id,current_instance_data& cid)
{
#ifdef YN_LINUX		
        Game_Logic::map_mutex m(&instance_mutex_);
#endif
    map< int, list < current_instance_data > >::iterator itc;
    itc = player_instance_list_.find( player_id );
    if( itc != player_instance_list_.end() )
    {
		list < current_instance_data >::iterator itqv;
		
	    itqv = find_if( itc->second.begin(), itc->second.end(), bind2nd( equal_to<current_instance_data>(), cid ));

		if( itqv == itc->second.end())
        {
				itc->second.push_back(cid);
                return 0;
        }
    }
    else
    {
        list < current_instance_data > instance_lst;
        instance_lst.push_back( cid );
        player_instance_list_.insert( make_pair ( player_id, instance_lst));
        return 0;
    }
    return -1;
}

int Instance_Data_Mgr::remove_player_instance_list( int player_id )
{
#ifdef YN_LINUX		
        Game_Logic::map_mutex m(&instance_mutex_);
#endif
    map< int, list < current_instance_data > >::iterator itc;
    itc = player_instance_list_.find( player_id );
    if( itc != player_instance_list_.end() )
    {
        player_instance_list_.erase( itc );
        return 0;
    }
    return -1;
}

int Instance_Data_Mgr::remove_player_instance_from_list( int player_id, int instance_id )
{
#ifdef YN_LINUX		
        Game_Logic::map_mutex m(&instance_mutex_);
#endif
    map< int, list < current_instance_data > >::iterator itc;
    itc = player_instance_list_.find( player_id );
    if( itc != player_instance_list_.end() )
    {
        current_instance_data cid;
        cid.set_instance_id( instance_id );
		list < current_instance_data >::iterator itqv;
	    itqv = find_if( itc->second.begin(), itc->second.end(), bind2nd( equal_to<current_instance_data>(), cid ));

		if( itqv == itc->second.end())
        {
				itc->second.erase(itqv);
                return 0;
        }
    }
    return -1;
}

int Instance_Data_Mgr::modi_player_instance_list( int player_id,current_instance_data& cid)
{
#ifdef YN_LINUX		
        Game_Logic::map_mutex m(&instance_mutex_);
#endif
    map< int, list < current_instance_data > >::iterator itc;
    itc = player_instance_list_.find( player_id );
    if( itc != player_instance_list_.end() )
    {
		list < current_instance_data >::iterator itqv;
	    itqv = find_if( itc->second.begin(), itc->second.end(), bind2nd( equal_to<current_instance_data>(), cid ));

		if( itqv != itc->second.end())
        {
				*itqv = cid;
                return 0;
        }
    }
    return -1;
}

int Instance_Data_Mgr::get_player_instance_from_list( int player_id,current_instance_data& cid)
{
#ifdef YN_LINUX		
  //    Game_Logic::map_mutex m(&instance_mutex_);
#endif
    map< int, list < current_instance_data > >::iterator itc;
    itc = player_instance_list_.find( player_id );
    if( itc != player_instance_list_.end() )
    {
		list < current_instance_data >::iterator itqv;
	    itqv = find_if( itc->second.begin(), itc->second.end(), bind2nd( equal_to<current_instance_data>(), cid ));

		if( itqv != itc->second.end())
        {
            cid = *itqv;
            return 0;
        }
    }
    return -1;
}

int Instance_Data_Mgr::analysis_stage_instance_data( int player_id )
{
#ifdef YN_LINUX		
    Game_Logic::map_mutex m(&instance_mutex_);
#endif
  //printf(" analysis_stage_instance_data config size %d\n", (int)m_map_instance_ui_config.size());
    Map_Instance_UI_Config::iterator itm;
    for( itm = m_map_instance_ui_config.begin(); itm != m_map_instance_ui_config.end(); ++ itm )
    {
        current_instance_data cid;
        cid.reset();
        cid.set_instance_id((itm->second).instance_id);
        if( -1 == get_player_instance_from_list( player_id, cid) )
        {
            (itm->second).score = -1;
            continue;
        }

        (itm->second).score = cid.get_instance_score();

    }
    return 0;
}

#if 1//MISSION_DIALOG
int Instance_Data_Mgr::get_player_instance_from_list2(int player_id, current_instance_data& cid)
{
#ifdef YN_LINUX		
	//    Game_Logic::map_mutex m(&instance_mutex_);
#endif
	map< int, list < current_instance_data > >::iterator itc;
	itc = player_instance_list_.find(player_id);
	if (itc != player_instance_list_.end())
	{
		list < current_instance_data >::iterator itqv;
		for (itqv = itc->second.begin(); itqv != itc->second.end(); ++itqv)
		{
			if (itqv->get_instance_id() == cid.get_instance_id() && itqv->get_instance_state() == current_instance_data::INSTANCE_STATE_SUC)
			{
				return 0;
			}
		}
	}
	return -1;
}


int Instance_Data_Mgr::get_quest_instance_state( int player_id ,int instance_id)
{
#ifdef YN_LINUX		
		Game_Logic::map_mutex m(&instance_mutex_);
#endif
	current_instance_data cid;
	cid.reset();
	cid.set_instance_id(instance_id);
	if ((-1 == INSTANCE_DATA_MGR::instance()->get_player_instance_from_list2(player_id, cid)))
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
#endif


int Instance_Data_Mgr::add_stage_data( int stage, int pass )
{
#ifdef YN_LINUX		
      Game_Logic::map_mutex m(&instance_mutex_);
#endif
    map<int, int>::iterator itm;
    itm = current_stage_state_lst_.find( stage );
    if( itm != current_stage_state_lst_.end())
    {
        itm->second = pass;
    }
    else
    {
        current_stage_state_lst_.insert( make_pair( stage, pass ) );
    }
    return 0;
}
int Instance_Data_Mgr::clear_stage_data( void )
{
#ifdef YN_LINUX		
        Game_Logic::map_mutex m(&instance_mutex_);
#endif
    current_stage_state_lst_.clear();
    return 0;
}
int Instance_Data_Mgr::get_stage_data( map<int,int>& stage_lst )
{
#ifdef YN_LINUX		
        Game_Logic::map_mutex m(&instance_mutex_);
#endif
    stage_lst = current_stage_state_lst_;
    return 0;
}

int Instance_Data_Mgr::get_instance_dialog_data_by_id( int id, instance_dialog& id_data)
{
    map< int, instance_dialog >::iterator iti;
    
    iti = instance_dialog_data_.find(id);
    if( iti != instance_dialog_data_.end())
    {
        id_data = iti->second;
        return 0;
    }
    return -1;
}


int Instance_Data_Mgr::clear_current_dialog( void )
{
    while (!current_instance_dialog_list_.empty())
        current_instance_dialog_list_.pop();

    return 0;
}

int Instance_Data_Mgr::push_current_dialog( Game_Data::Game_Element& ge )
{
    current_instance_dialog_list_.push(ge);
    return 0;
}
int Instance_Data_Mgr::pop_current_dialog( Game_Data::Game_Element& ge )
{
    if( current_instance_dialog_list_.empty())
        return -1;
    ge = current_instance_dialog_list_.front();
    current_instance_dialog_list_.pop();
    return 0;
}
int Instance_Data_Mgr::is_current_dialog_empty( void )
{
    return current_instance_dialog_list_.empty() ? 0 : -1 ;
}

#include <fstream>
bool Instance_Data_Mgr::RequestChallengeNextInstance()
{
	/************************************************************************/
	// 请求挑战下一个关卡
	
	// 1. 判断条件是否满足挑战下一关（体力是否足够等相关条件）
	// 潘杰（12.05）
	// ...


	// 2. 判断当前关卡是否属于当前章节
	if (!JudgeInstanceBelongTargetState(current_instance_id_, current_insance_stage_id_))
		return false;
	
	// 3. 根据下一关ID,判断下一步操作
	vector<uint> param;
	Formula_Function_Instance::instance()->get_para_list_from_instance_data(current_instance_id_, "instance_attribute", "result_content", "next_instance", param);
	if (param.size() <= 0)
		return false;

	int nNextInstanceID = -9999;
	nNextInstanceID		= param[0];
	// 3_1. 如果下一关的InstanceID是0（普通关卡）
	bool bValue = false;
	if (nNextInstanceID == 0)
	{
		// 普通关卡的下一关暂时不做任何处理
		// ...
		return false;
	}
	// 3_2. 如果下一关的InstanceID是-1（当前关卡是无尽塔的最后一层）
	else if (nNextInstanceID == -1)
	{
		// 根据需求,看以后是否需要提示玩家是不是最后一层
		// ...
		return false;
	}
	// 3_3. 如果下一关的InstanceID大于0（无尽塔的非最后一层）
	else if (nNextInstanceID > 0)
	{

	}
	else
	{
		return false;
	}

	/************************************************************************/
	// 条件满足,给服务器发送消息挑战下一关
	SendMsgRequestInstanceNext(current_instance_id_);
	return true;
}

bool Instance_Data_Mgr::JudgeInstanceBelongTargetState(const int nInstanceID, const int nStateID)
{
	/************************************************************************/
	// 判断当前关卡是否属于目标章节	
	// 1. 根据StateID获取不同的配置文件
	Area_UI_Config* pTargetStateConfig = NULL;
	pTargetStateConfig = INSTANCE_DATA_MGR::instance()->get_area_ui_config(nStateID);
	if (pTargetStateConfig == NULL)
		return false;

	// 2. 判断当前关卡是否属于目标章节	
	list<int>::iterator iter = pTargetStateConfig->list_instance_id.begin();
	for (; iter != pTargetStateConfig->list_instance_id.end(); ++iter)
	{
		if (nInstanceID == *iter)
		{
			return true;
		}
	}
	return false;
}


void Instance_Data_Mgr::SendMsgRequestInstanceNext(const int nCurrentInstanceID)
{
	/************************************************************************/
	// 判断当前关卡是否属于目标章节	
	vector<uint64> para;
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	para.push_back(player_id);
	para.push_back(nCurrentInstanceID);

	Game_Logic::Game_Content_Interface::instance()->exec_interface("sendrequirechallengenext", para);
}
