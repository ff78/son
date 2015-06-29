#ifndef _Game_Element_H
#define	_Game_Element_H

#include "common.h"
#include <fstream>

namespace Game_Data
{

	struct Game_Element
	{
		Game_Element(void):command_str_(""), count_(0),count_require_(0), text_str_(""),dirty_write_(0),db_save_(0),cell_id_(0),data_type_("") {para_vec_.clear();}
		~Game_Element(void) {}
		Game_Element(const string& cmd_str, const list<uint> cmd_lst):command_str_(cmd_str), count_(0), text_str_(""),dirty_write_(0), db_save_(0),cell_id_(0),data_type_("")
		{
			para_vec_.clear();
			para_vec_ = cmd_lst;
		}
		
		/*Game_Element( const Game_Element& ge )
		{
			command_str_ 	= ge.get_command();
			count_ 			= ge.get_count();
			dirty_write_    = 0;
			db_save_		= 0;
			cell_id_		= 0;
			data_type_		= "";
			para_str_vec_.clear();
			para_str_vec_ = ge.get_para_str_list();
			para_vec_.clear();
			para_vec_ 		= ge.get_para_list();
			text_str_ 		= "";
			text_str_ 		= ge.get_text();
			data_type_		= ge.get_data_type();
			cell_id_		= ge.get_cell_id();
			db_save_		= ge.get_db_save();
			dirty_write_    = ge.get_dirty_write();
            count_require_  = ge.get_count_require();
		}
		
		Game_Element& operator = ( const Game_Element& ge )
		{
			command_str_ 	= ge.get_command();
			count_ 			= ge.get_count();
			para_str_vec_.clear();
			para_str_vec_ = ge.get_para_str_list();
			para_vec_.clear();
			para_vec_ 		= ge.get_para_list();
			text_str_ 		= "";
			text_str_ 		= ge.get_text();
			data_type_		= ge.get_data_type();
			cell_id_		= ge.get_cell_id();
			db_save_		= ge.get_db_save();
			dirty_write_	= ge.get_dirty_write();
            count_require_  = ge.get_count_require();
			return *this;
		}*/

        bool operator==(const Game_Element& ge)const
		{
            return cell_id_ == ge.get_cell_id();
        }

		int reset()
		{
			command_str_ 	= "";
			count_ 			= 0;
			count_require_  = 0;
			dirty_write_    = 0;
			db_save_		= 0;
			cell_id_		= 0;
			para_str_vec_.clear();
			para_vec_.clear();
			text_str_ 		= "";
			data_type_		= "";
			return 0;

		}

		const list<uint>& get_para_list( void )const { return para_vec_; }

		void get_para_list_in_vector( vector<uint>& lst)
		{
			list<uint>::iterator itu;
			for( itu = para_vec_.begin(); itu != para_vec_.end(); ++itu )
			{
				lst.push_back((*itu));
			}
		}

		void set_para_list( list<uint> para ) { para_vec_.clear(); para_vec_ = para;  }

		const list<string> get_para_str_list( void ) const { return para_str_vec_; }
		void set_para_str_list( list<string> para ) { para_str_vec_.clear(); para_str_vec_ = para;  }
		void get_para_str_list_in_vector( vector<string>& lst)
		{
			list<string>::iterator itu;
			for( itu = para_str_vec_.begin(); itu != para_str_vec_.end(); ++itu )
			{
				lst.push_back((*itu));
			}
		}

		void count_add( void ) { count_++; }
		uint get_count( void ) const { return count_; }
		void set_count( uint count ) { count_ = count; }

		void set_command( const char* cmd ) 
		{ 
			command_str_ = cmd;
#ifdef YN_LINUX
		//command_str_ = trim( command_str_ );
#endif
#ifdef YN_WINDOWS
		//command_str_.erase( remove_if( command_str_.begin( ), command_str_.end( ), ptr_fun( isspace ) ), command_str_.end( ) );
#endif		
		}
		const char* get_command( void ) const { return command_str_.data(); }

		void set_text( const char* txt ) { text_str_ = txt; }
		const char* get_text( void ) const { return text_str_.data(); }

		void set_count_require( uint req ) { count_require_ = req; }
		uint get_count_require( void )const { return count_require_; }

		void set_dirty_write( int dirty ) {dirty_write_ = dirty; }
		int get_dirty_write( void )const { return dirty_write_; }

		void set_db_save( int dbsave ) {db_save_ = dbsave;}
		int get_db_save(void ) const{ return db_save_; }

		void set_cell_id ( int id ) {cell_id_ = id;}
		int get_cell_id( void  )const {return cell_id_;}

		void set_data_type( const char* type ){ data_type_ = type;}
		const char* get_data_type ( void ) const {return data_type_.data();}
	private:
		string command_str_;
		list<uint> para_vec_;
		list<string> para_str_vec_;

		uint count_;  // for count
		uint count_require_;
		string text_str_; // for text detail
		int dirty_write_;
		int db_save_;
		int cell_id_;
		string data_type_;
	};

	typedef list<Game_Element> game_element_list_t;
	struct Game_Command_Element
	{
        Game_Command_Element( void ):data_type_("") { game_element_data_list_.clear(); }
		~Game_Command_Element( void ) {}
		
		Game_Command_Element( const Game_Command_Element& gce ):data_type_("") 
		{
			game_element_data_list_.clear();
			game_element_data_list_ = gce.get_element_data();
		}
		
		Game_Command_Element& operator = ( const Game_Command_Element& gce )
		{
			game_element_data_list_.clear();
			game_element_data_list_ = gce.get_element_data();
			return *this;
		}
		const game_element_list_t& get_element_data() const { return game_element_data_list_; }
		void set_game_element_data( const game_element_list_t& ge ) { game_element_data_list_.clear(); game_element_data_list_ = ge; }
		void get_game_element_data( game_element_list_t& ge ) { ge.clear(); ge = game_element_data_list_ ; }
		void set_data_type( const char* type ){ data_type_ = type;}
		const char* get_data_type ( void ) const {return data_type_.data();}
	private:
		game_element_list_t game_element_data_list_;
        string data_type_;
	};

	typedef list<Game_Command_Element> game_command_element_vec_t;

}

#endif

