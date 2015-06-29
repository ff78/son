#include "quest_json_config.h"
#include "Play_System/Container_Mgr.h"
#ifdef GAME_CLIENT
#include "json/json_header.h"
#include "cocos2d.h"
#else
#include "json/json.h"
#endif
#include <fstream>

#ifdef GAME_CLIENT
#define QUEST_CFG_PATH "game_data/quest_data/quest_config.json"
#else
#define QUEST_CFG_PATH "../config/quest_data/quest_config.json"
#endif

namespace Game_Data
{
	game_content_parse* game_content_parse::instance_ = 0;
	game_content_parse::game_content_parse( void )
	{
	}

	game_content_parse::~game_content_parse( void )
	{
        if(instance_)
            delete instance_;
	}

	game_content_parse* game_content_parse::instance()
	{
		if( NULL == instance_ )
		{
			instance_ = new game_content_parse;
		}
		
		return instance_;
	}
	int game_content_parse::game_element_parse_cmd( const string& cmd_str, game_command_element_vec_t& game_cmd_vec )
	{
		game_cmd_vec.clear();
		string stringproc_str = cmd_str;

#ifdef YN_LINUX
		stringproc_str = trim( stringproc_str );
#endif
#ifdef YN_WINDOWS
		stringproc_str.erase( remove_if( stringproc_str.begin( ), stringproc_str.end( ), ptr_fun( isspace ) ), stringproc_str.end( ) );
#endif
		game_element_list_t game_element_vec;
		game_element_vec.clear();
		Game_Command_Element gce;
		//find command
		int fst_idx = 0; int scd_idx = 0;
		
		fst_idx = stringproc_str.find("[");
		if( fst_idx > (int)stringproc_str.size() || fst_idx < 0 )
		  return -1;
		    
		scd_idx = stringproc_str.find("]");
		string fsttmp_str;fsttmp_str.clear();
		do
		{
			if( (unsigned int)scd_idx > stringproc_str.size() )
				break;
			fsttmp_str.clear();
			fsttmp_str= stringproc_str.substr(fst_idx + 1, scd_idx - fst_idx - 1 );
			stringproc_str = stringproc_str.substr( scd_idx+1, stringproc_str.size() - 1 );

			game_element_parse_cell( fsttmp_str, game_element_vec );

			gce.set_game_element_data(game_element_vec);
			game_cmd_vec.push_back(gce);	

			fst_idx = 0; scd_idx = 0;
			fst_idx = stringproc_str.find("[");
			
			scd_idx = stringproc_str.find("]");
		} while( !0 );

		return 0;
	}

	int game_content_parse::game_element_parse_cell( const string& cell_str, game_element_list_t &game_element_vec )
	{
		game_element_vec.clear();
		string stringproc_str = cell_str;

		//find element
		int fst_idx = 0; int scd_idx = 0;
		fst_idx = stringproc_str.find("(");
		scd_idx = stringproc_str.find(")");
		string fsttmp_str;fsttmp_str.clear();
		string cmd_str; cmd_str.clear();
		do
		{
			if( (unsigned int)scd_idx > stringproc_str.size() )
				break;

			fsttmp_str.clear();
			cmd_str = stringproc_str.substr(0,fst_idx);
			fsttmp_str= stringproc_str.substr(fst_idx , scd_idx - fst_idx + 1);
			stringproc_str = stringproc_str.substr( scd_idx+1, stringproc_str.size() - 1 );
			list<string> string_vec;
			getContentListFromString(string_vec, fsttmp_str.data());

			Game_Element ge;
			ge.set_command(cmd_str.data());
			ge.set_para_str_list(string_vec);

			list<unsigned int> data_vec; data_vec.clear();
			list<string>::iterator its = string_vec.begin();

			for(  ;its != string_vec.end(); ++its)
			{
				data_vec.push_back( atoi((*its).data()));
			}
			ge.set_para_list(data_vec);

			game_element_vec.push_back(ge);

			fst_idx = 0; scd_idx = 0;
			fst_idx = stringproc_str.find("(");
			
			scd_idx = stringproc_str.find(")");

		} while( !0 );

		return 0;
	}

	void game_content_parse::getContentListFromString(list<string>& vecTempStrLst,  const char* contentList)
	{
		vecTempStrLst.clear();

		string				tempStrLst,tempStrLstleft;
		tempStrLst.clear();
		tempStrLstleft.clear();

		tempStrLst				= contentList;

    string	tempRnd		= "";

		string::size_type	fstIdx = 0, secIdx = 0;

		fstIdx						= tempStrLst.find("(");
		if ( fstIdx > tempStrLst.size() ) {
			return;
		}
		
		tempStrLst				= tempStrLst.substr(fstIdx + 1, tempStrLst.size());
		secIdx						= tempStrLst.find(",");
		
		if( secIdx > tempStrLst.size() )
			secIdx =  tempStrLst.find(")");
		
		while(!0) {

			tempStrLstleft	= tempStrLst.substr(fstIdx , secIdx);

			tempStrLst			= tempStrLst.substr(secIdx + 1, tempStrLst.size());

			tempRnd					= tempStrLstleft;

			vecTempStrLst.push_back(tempRnd);

			secIdx					= tempStrLst.find(",");

			if ( secIdx > tempStrLst.size() ) 
			{
				secIdx =  tempStrLst.find(")");
				if( secIdx > tempStrLst.size() )
					break;
			}
			fstIdx = 0;
		}
	}

	quest_config* quest_config::instance_ = 0;

	quest_config* quest_config::instance()
	{
		if( NULL == instance_ )
		{
			instance_ = new quest_config;
		}
		
		return instance_;
	}

	int quest_config::load_config(quest_data::quest_one_data_map_t &qdm, const char* /*root*/)
	{
		qdm.clear();
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, QUEST_CFG_PATH);

		for (Json::Value::iterator iter = root_value.begin();
		   iter != root_value.end();
		   ++iter)
		{
            quest_data* qd = new quest_data;
            qd->reset();
			Json::Value &v = (*iter)["quest_id"];
		    if (!v.empty())
		    {
                qd->set_quest_id(v.asInt());
            }
		    v = (*iter)["quest_name"];
		    if (!v.empty())
		    {
                qd->set_quest_name_id(v.asInt());
            }
		    v = (*iter)["quest_info"];
		    if (!v.empty())
		    {
                qd->set_quest_info_id( v.asInt());			
		    }
            v = (*iter)["quest_exec_dialog"];
            if (!v.empty())
		    {

                qd->set_quest_exec_dialog_id(v.asInt());			
		    }
		    game_quest_content gqc;
		    v = (*iter)["quest_exec_command"];
		    if (!v.empty())
		    {
			    string command_str = v.asString();
			    game_command_element_vec_t game_cmd_vec;		
			    game_content_parse::instance()->game_element_parse_cmd(command_str, game_cmd_vec);
			    gqc.set_quest_command_element(game_cmd_vec);
		    }
		    v = (*iter)["quest_exec_cell"];
		    if (!v.empty())
		    {
			    string cell_str = v.asString();
			    proc_string( cell_str,gqc);
		    }
		    qd->set_quest_content(gqc);


		    v = (*iter)["quest_complet_content"];
		    if (!v.empty())
		    {
			    string cell_str = v.asString();
			    proc_string( cell_str,gqc);
		    }
            qd->set_quest_complete(gqc);

		    v = (*iter)["quest_complet_dialog"];
		    if (!v.empty())
		    {

                qd->set_quest_submit_dialog_id(v.asInt());			
		    }
		    v= (*iter)["quest_award"];
		    if (!v.empty())
		    {
			    game_quest_content gqcc;
			    string cell_str = v.asString();
			    qd->set_quest_award_str( cell_str.data() );
			    proc_string( cell_str,gqcc);
			    qd->set_quest_award(gqcc);			
		    }
		
		    v = (*iter)["quest_accept_content"];
		    if (!v.empty())
		    {
			    game_quest_content gqcc;
			    string cell_str = v.asString();
			    proc_string( cell_str,gqcc);
			    qd->set_quest_accept(gqcc);
		    }

		    // precondition
		    v = (*iter)["pre_quest_id"];
		    if (!v.empty())
		    {
                qd->push_pre_cond(v.asInt());
            }

		    // postcondition
		    v = (*iter)["post_quest_id"];
		    if (!v.empty())
		    {
                qd->push_post_cond(v.asInt());
            }
		
            qdm.insert(make_pair(qd->get_quest_id(),*qd));
		}

		cout << "load quest data over----------------" << endl;
		return 0;
	}

	void quest_config::proc_string(const string& content_str, game_quest_content &gqc )
	{
		game_element_list_t game_element_vec;
		game_content_parse::instance()->game_element_parse_cell( content_str, game_element_vec );
		gqc.set_quest_element(game_element_vec);
	}

}
