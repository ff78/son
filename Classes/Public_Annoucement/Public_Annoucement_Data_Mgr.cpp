#include "Public_Annoucement/Public_Annoucement_Data_Mgr.h"
#ifdef GAME_SERVER
#include "Public_Annoucement/Public_Annoucement_Config.h"
#endif // GAME_SERVER

using namespace std;

namespace Game_Data
{
	Public_Annoucement_Data_Mgr* Public_Annoucement_Data_Mgr::instance_ = 0;
	Public_Annoucement_Data_Mgr::Public_Annoucement_Data_Mgr()
	{
		cleanup();
	}

	Public_Annoucement_Data_Mgr::~Public_Annoucement_Data_Mgr()
	{
	}

	Public_Annoucement_Data_Mgr* Public_Annoucement_Data_Mgr::instance()
	{
		if( NULL == instance_ )
			instance_ = new Public_Annoucement_Data_Mgr;

		return instance_;
	}
	void Public_Annoucement_Data_Mgr::cleanup()
	{
		pad_map.clear();
	}



	int Public_Annoucement_Data_Mgr::initialize()
	{

		return 0;
	}

	int Public_Annoucement_Data_Mgr::add_pad( const PAD &pad )
	{
		PAD* pad_tmp = new PAD;
		pad_tmp->id = pad.id;
		pad_tmp->title = pad.title;
		pad_tmp->content = pad.content;

		this->pad_map.insert( make_pair( pad_tmp->id, pad_tmp ) );

#ifdef GAME_SERVER
		Public_Annoucement_Config::instance()->persistence(false,true);
#endif // GAME_SERVER		

		return 0;
	}

	PAD_Map Public_Annoucement_Data_Mgr::get_pad_map( void )
	{
		return pad_map;
	}

	PAD* Public_Annoucement_Data_Mgr::find_pad_by_id( uint64 id )
	{
		PAD* result = NULL;	
		PAD_Iter tmp = this->pad_map.find(id);
		if( tmp != this->pad_map.end() )
		{
			result = tmp->second;
		}
		return result;
	}

	int Public_Annoucement_Data_Mgr::update_pad( uint64 id, const char* title, const char* content )
	{
		PAD* tmp = NULL;
		tmp = this->find_pad_by_id( id );
		if( NULL == tmp )
		{
			return -1;
		}
		tmp->title = title;
		tmp->content = content;

#ifdef GAME_SERVER
		Public_Annoucement_Config::instance()->persistence(false,true);
#endif // GAME_SERVER
		return 0;
	}

	int Public_Annoucement_Data_Mgr::update_or_add_pad( const PAD &pad )
	{
		int result = -1;
		if ( 0 != this->update_pad(pad.id, pad.title.c_str(), pad.content.c_str()) )
		{
			result = this->add_pad(pad);
		}
		return result;
	}


}
