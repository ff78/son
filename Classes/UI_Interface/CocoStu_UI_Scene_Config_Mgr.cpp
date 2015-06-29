#include "CocoStu_UI_Scene_Config_Mgr.h"
#include "cocos2d.h"
//#include "cocos-ext.h"
#include "CocoStu_UI_Scene_Config.h"
#include "json/json_header.h"

namespace CocoStudio
{
	CocoStu_UI_Scene_Config_Mgr* CocoStu_UI_Scene_Config_Mgr::instance_ = 0;

	CocoStu_UI_Scene_Config_Mgr::CocoStu_UI_Scene_Config_Mgr(void)
	{
	}


	CocoStu_UI_Scene_Config_Mgr::~CocoStu_UI_Scene_Config_Mgr(void)
	{
	}

	void CocoStu_UI_Scene_Config_Mgr::init()
	{
		ui_json_config_map_.clear();
		load_ui_json_config();
	}

	int CocoStu_UI_Scene_Config_Mgr::get_ui_json_config_by_id( int id, CocoStu_UI_Scene_Config& UJC )
	{
		std::map<int, CocoStu_UI_Scene_Config>::iterator iter;

		iter = ui_json_config_map_.find(id);
		if( iter != ui_json_config_map_.end() )
			UJC = iter->second;
		return 0;
	}
	
	void CocoStu_UI_Scene_Config_Mgr::load_ui_json_config()
	{
		ssize_t size = 0;
		unsigned char* pData = 0;

		pData = cocos2d::FileUtils::getInstance()->getFileData("game_data/UI/read_ui_json.json", "rb", &size);

		Json::Reader j_reader;
		Json::Value j_value;
		if ( !j_reader.parse((const char*) pData , (const char*)(pData+size), j_value))
		{
			printf("/n%s/n", j_reader.getFormattedErrorMessages().c_str());
			CC_SAFE_DELETE_ARRAY(pData);
			return;
		}

		CocoStudio::CocoStu_UI_Scene_Config UJC;
		//std::list<Game_Element> gm_list;

		for ( Json::Value::iterator iter = j_value.begin(); iter != j_value.end(); ++iter )
		{
			UJC.reset();
			Json::Value &v = (*iter)["id"];
			if ( !v.empty() )
			{
				UJC.set_json_id( v.asInt() );
			}

			v = (*iter)["name"];
			if ( !v.empty() )
			{
				UJC.set_json_name( v.asString().data() );
			}

			v = (*iter)["type"];
			if( !v.empty() )
			{
				UJC.set_json_type( v.asInt() );
			}

			v = (*iter)["enableAdapt"];
			if( !v.empty() )
			{
				UJC.set_enableAdapt( v.asBool() );
			}

			v = (*iter)["scaleAdapt"];
			if( !v.empty() )
			{
				UJC.set_scaleAdapt( v.asBool() );
			}

			v = (*iter)["equalProportions"];
			if( !v.empty() )
			{
				UJC.set_equalProportions( v.asBool() );
			}

			v = (*iter)["widget_id"];
			if ( !v.empty() )
			{
				for ( Json::Value::iterator e_iter = v.begin(); e_iter != v.end(); e_iter++ )
				{
					UJC.set_widget_id( (*e_iter).asInt() );
				}
			}

			ui_json_config_map_.insert(make_pair(UJC.get_json_id(),UJC));
		}
		CC_SAFE_DELETE_ARRAY(pData);
	}

	int CocoStu_UI_Scene_Config_Mgr::get_ui_json_config_map( map<int,CocoStu_UI_Scene_Config>& i_ujc_map )
	{
		i_ujc_map = ui_json_config_map_;
		return 0;
	}

	CocoStu_UI_Scene_Config_Mgr* CocoStudio::CocoStu_UI_Scene_Config_Mgr::get_instance()
	{
		if( !instance_ )
			instance_ = new CocoStu_UI_Scene_Config_Mgr();
		return instance_;
	}
}



