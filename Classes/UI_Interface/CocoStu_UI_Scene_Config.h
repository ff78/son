#ifndef _UI_JSON_READ_CONFIG_CLASS_
#define _UI_JSON_READ_CONFIG_CLASS_

#include "Game_Interface/common.h"
#include "Game_Interface/game_element.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;
namespace CocoStudio
{
	struct CocoStu_UI_Scene_Config
	{
		CocoStu_UI_Scene_Config() : json_id_(0),json_name_(""),json_type_(0),enableAdapt_(0),scaleAdapt_(0),equalProportions_(0) { widget_id_list_.clear(); }

		void reset(){ json_id_ = 0; json_name_ = ""; json_type_ = 0; enableAdapt_ = 0; scaleAdapt_ = 0; equalProportions_ = 0; widget_id_list_.clear();}

		void set_json_id( int json_id ) {json_id_ = json_id; }
		const int get_json_id( void ) { return json_id_; }

		void set_json_name( const char* json_name ) { json_name_ = json_name; }
		const char* get_json_name( void ) { return json_name_.data();}

		void set_json_type( int json_type) { json_type_ = json_type; }
		const int get_json_type( void ) { return json_type_; }

		void set_enableAdapt( bool enable_adapt ) { enableAdapt_ = enable_adapt; }
		const bool get_enableAdapt( void ) { return enableAdapt_; }

		void set_scaleAdapt( bool scale_adapt ) { scaleAdapt_ = scale_adapt; }
		const bool get_scaleAdapt( void ) { return scaleAdapt_; }

		void set_equalProportions( bool equal_proportions ) { equalProportions_ = equal_proportions; }
		const bool get_equalProportions( void ) { return equalProportions_; }

		void set_widget_id( int widget_id ) { widget_id_list_.push_back(widget_id); }
		void get_widget_id_list ( list<int>& id_list ) { id_list = widget_id_list_; }

		int set_fun_list( std::list<Game_Data::Game_Element>& gm_list) { func_list_ = gm_list; return 0; }
		int get_fun_list( std::list<Game_Data::Game_Element>& gm_list) { gm_list = func_list_; return 0; }


	private:
		int json_id_;
		string json_name_;
		int json_type_;
		bool enableAdapt_;
		bool scaleAdapt_;
		bool equalProportions_;
		list<int> widget_id_list_;

		std::list<Game_Data::Game_Element> func_list_;
	};
}
#endif //_UI_JSON_READ_CONFIG_CLASS_
