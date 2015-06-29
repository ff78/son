
#include "Game_Element_Parse.h"

namespace Game_Data
{
Game_Element_Parse* Game_Element_Parse::instance_ = 0;
Game_Element_Parse::Game_Element_Parse( void )
{
#ifdef YN_LINUX		
		pthread_mutex_init(&game_element_mutex_,NULL);  
#endif	
}

Game_Element_Parse::~Game_Element_Parse( void )
{
#ifdef YN_LINUX				
		pthread_mutex_destroy(&game_element_mutex_);
#endif	
}

Game_Element_Parse* Game_Element_Parse::instance()
{
	if( NULL == instance_ )
	{
		instance_ = new Game_Element_Parse;
	}

	return instance_;
}
int Game_Element_Parse::game_element_parse_cmd( const string& cmd_str, game_command_element_vec_t& game_cmd_list ,const char* data_type)
{
	game_cmd_list.clear();
	string stringproc_str = cmd_str;

#ifdef YN_LINUX
	//stringproc_str = trim( stringproc_str );
#endif
#ifdef YN_WINDOWS
	//stringproc_str.erase( remove_if( stringproc_str.begin( ), stringproc_str.end( ), ptr_fun( isspace ) ), stringproc_str.end( ) );
#endif
	game_element_list_t Game_Element_vec;
	Game_Element_vec.clear();
	Game_Command_Element gce;
	//find command
	size_t fst_idx = 0, scd_idx = 0;
	fst_idx = (size_t)stringproc_str.find("[");
	scd_idx = (size_t)stringproc_str.find("]");
	string fsttmp_str;fsttmp_str.clear();
	do
	{
		if( (unsigned int)scd_idx > stringproc_str.size() )
			break;
		fsttmp_str.clear();
		fsttmp_str= stringproc_str.substr(fst_idx + 1, scd_idx - fst_idx - 1 );
		stringproc_str = stringproc_str.substr( scd_idx+1, stringproc_str.size() - 1 );

		game_element_parse_cell( fsttmp_str, Game_Element_vec );

		gce.set_game_element_data(Game_Element_vec);
        gce.set_data_type(data_type);
		game_cmd_list.push_back(gce);	

		fst_idx = 0; scd_idx = 0;
		fst_idx = stringproc_str.find("[");

		scd_idx = stringproc_str.find("]");
	} while( !0 );

	return 0;
}

int Game_Element_Parse::game_element_parse_cell( const string& cell_str, game_element_list_t &Game_Element_list, const char* data_type )
{

	Game_Element_list.clear();
	string stringproc_str = cell_str;
	replace_char_to_char_from_string(stringproc_str, "),", ")");
	//find element
	size_t fst_idx = 0,scd_idx = 0;
	fst_idx = (size_t)stringproc_str.find("(");
	scd_idx = (size_t)stringproc_str.find(")");
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
		ge.set_data_type(data_type);

		Game_Element_list.push_back(ge);

		fst_idx = 0; scd_idx = 0;
		fst_idx = (size_t)stringproc_str.find("(");

		scd_idx = (size_t)stringproc_str.find(")");

	} while( !0 );

	return 0;
}


void Game_Element_Parse::getContentListFromString(list<string>& vecTempStrLst,  const char* contentList)
{
#ifdef YN_LINUX
  // Game_Logic::map_mutex m(&game_element_mutex_);
#endif
	vecTempStrLst.clear();

	string				tempStrLst,tempStrLstleft;
	tempStrLst.clear();
	tempStrLstleft.clear();

	tempStrLst				= contentList;

	string	tempRnd		= "";

	size_t	fstIdx = 0, secIdx = 0;

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

int Game_Element_Parse::replace_char_to_char_from_string( string& temp_str, const char* src_char, const char* des_char )
{
#ifdef YN_LINUX
  // Game_Logic::map_mutex m(&game_element_mutex_);
#endif
	string src_str =src_char;
	size_t src_size = src_str.size();
	if(src_size - 1 < 1)
		return -1;
	while(!0)
	{
		size_t idx = temp_str.find(src_char);
		if(idx >temp_str.size())
			break;
		temp_str.replace(idx,src_size, des_char );
	}
	return 0;
}

int Game_Element_Parse::push_msg_para( const int msgid,const char* msg, vector<uint64>& para_vec)
{
#ifdef YN_LINUX
  // Game_Logic::map_mutex m(&game_element_mutex_);
#endif
	vector<string> str_vec;
	get_content_from_string(str_vec, msg, "|" );

	bool find = false;
	vector<string>::iterator its;
	for( its = str_vec.begin(); its != str_vec.end(); ++ its )
	{
		if( find )
			para_vec.push_back(atoi((*its).data()));

		if( !find && atoi((*its).data()) == msgid )
		{
			find = true;
			if( its != str_vec.end()) ++its;

			if(its == str_vec.end()) break;
		}
	}

    return 0;
}
int Game_Element_Parse::get_content_from_string(vector<string>& str_vec, const char* content, const char* key )
{
#ifdef YN_LINUX
   Game_Logic::map_mutex m(&game_element_mutex_);
#endif
	string tempStrLst,tempStrLstleft,tempRnd;
	tempStrLst.clear();
	tempStrLstleft.clear();
	tempRnd.clear();

	tempStrLst = content;
	string::size_type	fstIdx = 0, secIdx = 0;

	secIdx = tempStrLst.find(key);
	if ( secIdx > tempStrLst.size() ) 
	{
		str_vec.push_back( tempStrLst);
		return 0;
	}

	str_vec.clear();
	while(!0) {
		tempStrLstleft	= tempStrLst.substr(fstIdx , secIdx);

		tempStrLst		= tempStrLst.substr(secIdx + 1, tempStrLst.size());

		tempRnd			= tempStrLstleft;

		str_vec.push_back(tempRnd);

		secIdx			= tempStrLst.find(key);

		if ( secIdx > tempStrLst.size() ) 
		{
			if(tempStrLst.compare(""))
				str_vec.push_back( tempStrLst);
			break;
		}
	}
    return 0;
}

int Game_Element_Parse::get_para_from_require_element( const char* key, game_element_list_t& Game_Element_list, vector<uint>& para_vec)
{
#ifdef YN_LINUX
  Game_Logic::map_mutex m(&game_element_mutex_);
#endif
    string comp_key = key;
    game_element_list_t::iterator itg;

    for( itg = Game_Element_list.begin(); itg != Game_Element_list.end(); ++ itg)
    {
        if(!comp_key.compare((*itg).get_command()))
        {
            (*itg).get_para_list_in_vector( para_vec);
            if(  0 == para_vec.size())
            {
                list<string> para_str = (*itg).get_para_str_list();
                list<string>::iterator itr;
                for ( itr = para_str.begin(); itr != para_str.end(); ++ itr )
                {
                    para_vec.push_back(atoi((*itr).data()));
                }

            }
            return 0;
        }
    }

    return -1;
}

int Game_Element_Parse::get_string_para_from_require_element( const char* key, game_element_list_t& Game_Element_list, vector<string>& para_vec)
{
#ifdef YN_LINUX
   Game_Logic::map_mutex m(&game_element_mutex_);
#endif
    string comp_key = key;
    game_element_list_t::iterator itg;

    for( itg = Game_Element_list.begin(); itg != Game_Element_list.end(); ++ itg)
    {
        if(!comp_key.compare((*itg).get_command()))
        {


            list<string> para_str = (*itg).get_para_str_list();
            list<string>::iterator itr;
            for ( itr = para_str.begin(); itr != para_str.end(); ++ itr )
            {
                 para_vec.push_back((*itr).data());
            }

            return 0;
        }
    }

    return -1;
}

}

