

#include "Formula_Logic.h"
#include "Game_Interface/game_content_interface.h"

#include "Formula_Data.h"
#include "Formula_Mgr.h"

#include "Formula_Function_Instance.h"

Formula_Logic* Formula_Logic::instance_ = 0;
Formula_Logic::Formula_Logic()
{

}

Formula_Logic::~Formula_Logic()
{

}

Formula_Logic* Formula_Logic::instance()
{
    if( NULL == instance_ )
        instance_ = new Formula_Logic;

    return instance_;
}

int Formula_Logic::init_formula_system( void )
{
	formula_function_call_list_.clear();

	//cell function call
#ifdef GAME_SERVER
    Game_Logic::Game_Content_Interface::instance()->reg_function_callback("give_item",Formula_Function_Instance::give_item, formula_function_call_list_);
	Game_Logic::Game_Content_Interface::instance()->reg_function_callback("award_money",Formula_Function_Instance::award_money, formula_function_call_list_);
	Game_Logic::Game_Content_Interface::instance()->reg_function_callback("award_item",Formula_Function_Instance::award_item, formula_function_call_list_);
    Game_Logic::Game_Content_Interface::instance()->reg_function_callback("award_general",Formula_Function_Instance::award_general, formula_function_call_list_);
    Game_Logic::Game_Content_Interface::instance()->reg_function_callback("award_exp_compute",Formula_Function_Instance::award_exp_compute, formula_function_call_list_);
    Game_Logic::Game_Content_Interface::instance()->reg_function_callback("remove_item",Formula_Function_Instance::remove_item, formula_function_call_list_);
    Game_Logic::Game_Content_Interface::instance()->reg_function_callback("energyconsume",Formula_Function_Instance::instance_energy_consume, formula_function_call_list_);
#endif
    return 0;
}

bool Formula_Logic::load_formula_data(Game_Logic::Game_Interface& /*gm_interface*/)
{
    Game_Data::Formula_Mgr::instance()->initialize();
	return true;
}

int Formula_Logic::exec_formula_function_list(int player_id, list<Game_Data::Game_Element>& ge_lst )
{
    Formula_Logic::instance()->exec_element_function_list( player_id, ge_lst, "");
	return 0;
}

int Formula_Logic::exec_formula_interface(const char* cmd, std::vector<uint64> para, const char* key)
{
     return Game_Logic::Game_Content_Interface::instance()->exec_interface(cmd, para, key ) ? 0 : -1;
}

int Formula_Logic::exec_formula_function(const char* cmd, vector<uint64> para, const char* key )
{
    return Game_Logic::Game_Content_Interface::instance()->exec_function(cmd, para,formula_function_call_list_, key ) ? 0 : -1;

}

//different formula need different process logic

bool Formula_Logic::exec_formula(Game_Logic::Game_Interface& gm_interface) 
{
	vector<uint64>  para;
	gm_interface.get_para(para);
	if( para.size() < 1)
		return false;
    uint32 player_id = (uint)para[0];
	uint32 formula_id = (uint)para[1];

	Game_Data::Play_System_Formula psf;
	psf.reset();
	if (-1 == Game_Data::Formula_Mgr::instance()->get_play_system_formula_by_id( formula_id, psf ))
		return false;


	std::list<Game_Data::Game_Element> ge_lst;
	psf.get_exec_list(ge_lst);

    Formula_Logic::instance()->exec_element_function_list( player_id, ge_lst, psf.get_key());

	return true;
}

int Formula_Logic::exec_element_function_list( int player_id, std::list<Game_Data::Game_Element>& ge_lst, const char* key )
{

	std::list<Game_Data::Game_Element>::iterator itr;
	vector<uint> para_u;
	vector<uint64> para_lst;
	vector<uint>::iterator itu;
	for( itr = ge_lst.begin(); itr != ge_lst.end(); ++ itr )
	{
		para_u.clear();
		para_lst.clear();
        para_lst.push_back(player_id);
		(*itr).get_para_list_in_vector(para_u);
		for( itu = para_u.begin(); itu != para_u.end(); ++itu)
			para_lst.push_back(*itu);
		Formula_Logic::instance()->exec_formula_interface((*itr).get_command(),  para_lst, key);
	}

    return 0;
}


