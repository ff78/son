
#include "quest_logic_client.h"
#include "quest_system/quest_data/quest_data_mgr.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/Game_Element_Parse.h"
quest_logic_client* quest_logic_client::instance_ = 0;
quest_logic_client::quest_logic_client(){

}


quest_logic_client::~quest_logic_client(){

}

quest_logic_client* quest_logic_client::instance()
{
    if( NULL == instance_ )
        instance_ = new quest_logic_client;

    return instance_;
}

bool quest_logic_client::proc_update_quest(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 5 )
        return false;

    string couter_str = gm_interface.get_keyword();

    int player_id = (int)para[0];
    int quest_id = (int)para[1];
    int quest_state = (int)para[2];
    int act_count = (int)para[3];
    int act_total_count = (int)para[4];

    if( Game_Data::quest_data::QUEST_STATE_REMOVE == quest_state )
     {
        instance()->proc_remove_complete_quest( player_id, quest_id );
        para.clear();
        para.push_back(player_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sendreqnpcquest", para);
        return 0;
    }

    Game_Data::quest_data tmp_qd;

    Game_Data::quest_data* qd = Game_Data::quest_data_mgr::instance()->get_quest_data( player_id, quest_id );
    if( NULL == qd )
    {

        Game_Data::quest_data* org_qd = Game_Data::quest_data_mgr::instance()->get_org_quest_data(quest_id);
        if( NULL == org_qd )
            return false;

        tmp_qd = *org_qd;
        tmp_qd.set_quest_state( quest_state );

        Game_Data::quest_data_mgr::instance()->addquest(player_id, tmp_qd );
        para.clear();
        para.push_back(player_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sendreqnpcquest", para);
    }
    else
    {
        tmp_qd = *qd;

    }

	//get quest content
	Game_Data::game_quest_content gqc;
	tmp_qd.get_quest_content( gqc );

	//get content element list
	Game_Data::game_element_list_t ge_vec;
	gqc.get_quest_element( ge_vec );	

    vector< int > counter_vec;
    vector< string > counter_str;
    counter_str.clear(); counter_vec.clear();
    Game_Data::Game_Element_Parse::instance()->get_content_from_string(counter_str, couter_str.data(), "|");
    vector< string >::iterator its;
    for(its = counter_str.begin(); its != counter_str.end(); ++its )
    {
        counter_vec.push_back(atoi((*its).data()));
    }
	
	if( ge_vec.size() == counter_vec.size()/2)
    {	

	    Game_Data::game_element_list_t::iterator itgv;
	    unsigned int i = 0;
	    for( itgv = ge_vec.begin(); itgv != ge_vec.end(); ++ itgv )
	    {
		    (*itgv).set_count(counter_vec[i]); i ++;
            (*itgv).set_count_require(counter_vec[i]); i++;
        }
    }

    tmp_qd.set_quest_state( quest_state );
    gqc.set_quest_element(ge_vec);
    tmp_qd.set_quest_content(gqc);

    Game_Data::quest_data_mgr::instance()->modi_quest_data( player_id, tmp_qd );

    return true;
}

int quest_logic_client::proc_remove_complete_quest( int player_id, int quest_id )
{

    Game_Data::quest_data_mgr::instance()->removequest(player_id, quest_id );
    return 0;
}

bool quest_logic_client::is_quest_done(Game_Logic::Game_Interface& gm_interface)
{
    return false;
}

