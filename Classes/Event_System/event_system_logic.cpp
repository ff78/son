#include "event_system_logic.h"
#include "Event_Data.h"
#include "event_system_data_mgr.h"
#include "Event_Function_Instance.h"
#include "Game_Interface/event_define.h"
#include "Game_Interface/game_element.h"
#include "Game_Interface/game_content_interface.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "event_system_data_mgr.h"
#include "Game_Interface/game_condition.h"
using namespace Game_Logic;
event_system_logic::event_system_logic()
{

}
event_system_logic* event_system_logic::instance_= 0;
event_system_logic* event_system_logic::sharedInstance()
{
	if(instance_==0)
	{
		instance_=new event_system_logic();
	}
	return instance_;
}
bool event_system_logic::load_event_data(Game_Logic::Game_Interface& /*gm_interface*/)
{
	event_system_data_mgr::sharedInstance()->init();

    sharedInstance()->reg_function();

	return true;
}

int event_system_logic::reg_function()
{
	event_function_call_map_.clear();
#ifdef GAME_CLIENT
	Game_Logic::Game_Content_Interface::instance()->reg_function_callback("awardgold",Event_Function_Instance::awardgold, event_function_call_map_);
	Game_Logic::Game_Content_Interface::instance()->reg_function_callback("awardhp",Event_Function_Instance::awardhp, event_function_call_map_);
	Game_Logic::Game_Content_Interface::instance()->reg_function_callback("awardmp",Event_Function_Instance::awardmp, event_function_call_map_);
    Game_Logic::Game_Content_Interface::instance()->reg_function_callback("dropsomething",Event_Function_Instance::dropsomething, event_function_call_map_);
#endif

    Game_Logic::Game_Content_Interface::instance()->reg_function_callback("awarditem",Event_Function_Instance::awarditem, event_function_call_map_);
	Game_Logic::Game_Content_Interface::instance()->reg_function_callback("random_award_one_bag",Event_Function_Instance::randomawardone, event_function_call_map_);
	Game_Logic::Game_Content_Interface::instance()->reg_function_callback("random_award_one_book_bag",Event_Function_Instance::randomawardone, event_function_call_map_);
    
    Game_Logic::Game_Content_Interface::instance()->reg_function_callback("award_gold",Event_Function_Instance::award_gold, event_function_call_map_);
    Game_Logic::Game_Content_Interface::instance()->reg_function_callback("award_token",Event_Function_Instance::award_token, event_function_call_map_);
    Game_Logic::Game_Content_Interface::instance()->reg_function_callback("award_prestige",Event_Function_Instance::award_prestige, event_function_call_map_);
    Game_Logic::Game_Content_Interface::instance()->reg_function_callback("award_feat",Event_Function_Instance::award_feat, event_function_call_map_);
    Game_Logic::Game_Content_Interface::instance()->reg_function_callback("award_energy",Event_Function_Instance::award_energy, event_function_call_map_);
    Game_Logic::Game_Content_Interface::instance()->reg_function_callback("award_general_exp",Event_Function_Instance::award_general_exp, event_function_call_map_);
    Game_Logic::Game_Content_Interface::instance()->reg_function_callback("award_deputy_general",Event_Function_Instance::award_deputy_general, event_function_call_map_);

    Game_Logic::Game_Content_Interface::instance()->reg_function_callback("collided_something",Event_Function_Instance::collided_something, event_function_call_map_);

	Game_Logic::Game_Content_Interface::instance()->reg_function_callback("useitem",Event_Function_Instance::useitem, event_function_call_map_);
	Game_Logic::Game_Content_Interface::instance()->reg_function_callback("monster_die",Event_Function_Instance::monster_die, event_function_call_map_);

    return 0;
}
int event_system_logic::init_event_system(int player_id)
{

	//注册触发事件
	map<int,Event_Data> map_t;
	list<Game_Element> ge_lst;
	event_system_data_mgr::sharedInstance()->getEventDataMap(map_t);
	for(map<int,Event_Data>::iterator iter=map_t.begin();iter!=map_t.end();++iter)
	{
		Event_Data ed=iter->second;
		ed.getTrigger(ge_lst);
		vector<uint64> v;
		v.push_back(player_id);
		exec_element_function_list( iter->first, ge_lst, "",v);

	}
	
	return 0;
}

int event_system_logic::exec_element_function_list( int event_id, std::list<Game_Data::Game_Element>& ge_lst, const char* /*key*/,vector<uint64> para)
{

	std::list<Game_Data::Game_Element>::iterator itr;
	vector<uint> para_u;
	vector<uint64> para_lst;
	vector<uint>::iterator itu;
	for( itr = ge_lst.begin(); itr != ge_lst.end(); ++ itr )
	{
		para_u.clear();
		para_lst.clear();
		para_lst.push_back(event_id);

		(*itr).get_para_list_in_vector(para_u);
		for( itu = para_u.begin(); itu != para_u.end(); ++itu)
        {
			para_lst.push_back(*itu);
        }

        for(uint i=0;i<para.size();i++)
        {
            para_lst.push_back(para[i]);
        }

		Game_Logic::Game_Content_Interface::instance()->exec_function((*itr).get_command(), para_lst,event_function_call_map_, "" );
	}

	return 0;
}
bool event_system_logic::proc_monster_die_envent(const Game_Event& gm_evt )
{

	int event_id = gm_evt.get_event_owner_id();
	Event_Data ed;
	list<Game_Element> condition_lst;
	event_system_data_mgr::sharedInstance()->getEventDataById(event_id,ed);
	if(ed.getId()==0)
	{
		return false;
	}
	ed.getCondition(condition_lst);

	
	int player_id =gm_evt.get_char_id();

	if(!Game_Condition::instance()->analysis_game_condition( player_id, condition_lst))
	{
		return false;

	}

	list<Game_Element> function_lst;
	ed.getFunction(function_lst);
	vector<uint64> ivc;
	gm_evt.get_para(ivc);
	event_system_logic::sharedInstance()->exec_element_function_list( event_id, function_lst, "",ivc);

	return true;
}
bool event_system_logic::proc_useitem_event( const Game_Logic::Game_Event& gm_evt )
{
	int event_id = gm_evt.get_event_owner_id();

	Event_Data ed;
	list<Game_Element> condition_lst;
	event_system_data_mgr::sharedInstance()->getEventDataById(event_id,ed);
	if(ed.getId()==0)
	{
		return false;
	}
	ed.getCondition(condition_lst);


	int player_id =gm_evt.get_char_id();

	if(!Game_Condition::instance()->analysis_game_condition( player_id, condition_lst))
	{
		return false;

	}

#ifdef GAME_SERVER
	list<Game_Element> function_lst;
	ed.getFunction(function_lst);
	vector<uint64> ivc;
	gm_evt.get_para(ivc);
	event_system_logic::sharedInstance()->exec_element_function_list( event_id, function_lst, "",ivc);
#endif

#ifdef GAME_CLIENT
	int activate_id=gm_evt.get_event_active_id();
	//发送消息到服务器
	std::vector<uint64> paras;
	paras.push_back(activate_id);
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_player_useitem_something", paras);
#endif




	return true;
}

