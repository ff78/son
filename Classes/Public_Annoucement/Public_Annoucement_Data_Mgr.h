
#ifndef _PUBLIC_ANNOUCEMENT_DATA_MGR_H_
#define _PUBLIC_ANNOUCEMENT_DATA_MGR_H_

#include <string>
#include <list>

#include "Public_Annoucement/Pubilc_Annoucement_Common.h"

namespace Game_Data
{

	class Public_Annoucement_Data_Mgr
	{

	public:
		Public_Annoucement_Data_Mgr();
		virtual ~Public_Annoucement_Data_Mgr();
		static Public_Annoucement_Data_Mgr* instance();
		int initialize();
		void cleanup();

	public:
		PAD* find_pad_by_id( uint64 id );
		int update_or_add_pad( const PAD &pad);
		int update_pad( uint64 id, const char* title, const char* content );
		int add_pad( const PAD &pad );
		PAD_Map get_pad_map( void );

	private:
		static Public_Annoucement_Data_Mgr*    instance_;
		PAD_Map pad_map;

	};

}


#endif //_PUBLIC_ANNOUCEMENT_DATA_MGR_H_
