

#include "Game_Interface/game_content_interface.h"
#include "Character.h"
#include "FightNpc.h"
#include "Player.h"
#include "CommonNpc.h"
#include "Character_Mgr.h"
#include "Skill_System/Skill/Technical_Mgr.h"
#include "Character_Mgr.h"
#include "DeputyGeneral.h"
#include "Character_Logic.h"

using namespace Game_Data;

Character_Logic* Character_Logic::instance_ = NULL;
Character_Logic::Character_Logic()
{

}

Character_Logic::~Character_Logic()
{

}

Character_Logic* Character_Logic::instance()
{
    if(instance_ == NULL)
    {
        instance_ = new Character_Logic;
    }

    return instance_;
}

int Character_Logic::init_Character_system( void )
{
	Character_function_call_list_.clear();

	
	return 0;
}

int Character_Logic::exec_Character_interface(const char* cmd, std::vector<uint64> para, const char* key)
{
     return Game_Logic::Game_Content_Interface::instance()->exec_interface(cmd, para, key ) ? 0 : -1;
}

int Character_Logic::exec_Character_function(const char* cmd, vector<uint64> para, const char* key )
{
    return Game_Logic::Game_Content_Interface::instance()->exec_function(cmd, para,Character_function_call_list_, key ) ? 0 : -1;

}

//different Character need different process logic

int Character_Logic::exec_element_function_list( int player_id, std::list<Game_Data::Game_Element>& ge_lst, const char* /*key*/ )
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
	}

    return 0;
}


int Character_Logic::reg_Character_function(){

	return 0;
}


void Character_Logic::exec_Character_function(){

}

bool Character_Logic::init_character_skill_list(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
    gm_interface.get_para( para );
    if( para.size() < 1 )
        return false;

	int character_id        = (int)para[0];

	return init_skill_list( character_id );
}

bool Character_Logic::init_skill_list(int character_id)
{
	Character* self = CHARACTER_MGR::instance()->get_character( character_id );
	if ( NULL == self )
		return false;

	std::list<int> skill_list;
	std::list<int>::iterator it;
	TECHNICAL_MGR::instance()->get_character_technical_list(self->get_character_type(), &skill_list);

	Character_Skill skill;
	std::vector<Character_Skill> skill_vector;
	for (it = skill_list.begin(); it != skill_list.end(); it++)
	{
		skill.skill_id = *it;
		//skill.skill_level = 1;
		skill_vector.push_back( skill );
	}
	self->insert_skill_list( skill_vector );

	return true;
}
