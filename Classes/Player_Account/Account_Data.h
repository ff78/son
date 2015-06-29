// -*- C++ -*-

#ifndef ACCOUNT_ATT_H_
#define ACCOUNT_ATT_H_

#include <stdio.h>
#include <stdlib.h>

#include "Game_Interface/common.h"
#include "Network_Common/global_macros.h"
#include <string.h>

#define ID_CARD_LENGTH     20

// table name in database 
const char db_tb_account_att[] = "account_att";

enum
{
  S_AC_CREATE               = 0,
  S_AC_LOADED               = 1,
  S_AC_CREATE_ROLE          = 2,
  S_AC_SELECT_ROLE          = 3,
  S_AC_ENTER_GAME           = 4,
  S_CLT_LOAD_SCENE_OK       = 5
};
enum
{
  S_AC_UNADDICTED           = 1L << 0,
  S_AC_UNVERITY             = 1L << 1,
  S_AC_MINOR_VERITY_OK      = 1L << 2,   // 未成年认证通过
  S_AC_MAJOR_VERITY_OK      = 1L << 3,   // 成年人认证OK
  S_AC_ADDICTED_1           = 1L << 4,
  S_AC_ADDICTED_2           = 1L << 5
};
/**
 * @class account_att
 * 
 * @brief
 */

struct Account_Data
{

    enum   // For column index.
    {
        IDX_ACCOUNT = 0, IDX_TRACK_STATUS, IDX_STATUS, 
        IDX_ONLINE_TIME, IDX_CREATE_TIME,
        IDX_LOGIN_TIME, IDX_LOGOUT_TIME, IDX_IP_ADDR, 
        IDX_R_NAME, IDX_ID_CARD, IDX_IS_MINOR,
        IDX_END
    };

    Account_Data()
    { 
        reset(); 
    
    }

    ~Account_Data() {}

    void reset()   // For reuse
    {
      this->is_minor_     = 1;
      this->track_status_ = S_AC_CREATE;
      this->status_       = S_AC_UNADDICTED;
      this->online_time_  = 0;
      this->create_time_  = 0;
      this->login_time_   = 0;
      this->logout_time_  = 0;
      this->account_      = "";
      this->r_name_       = "";
      this->id_card_      = "";
      this->ip_addr_      = "";
    }
    void set_account_id ( uint64 id ) {account_id_ = id;}
    uint64 get_account_id(void) {return account_id_;}
    void set_is_minor(char data) {is_minor_ = data;}
    char get_is_minor( void ) {return is_minor_; }
    void set_track_status( int status ) { track_status_ = status;}
    int get_track_status( void ) {return track_status_;}
    void set_status( int status ) {status_ = status;}
    int get_status( void ) { return status_;}
    void set_account( const char* account) {account_ = account;}
    const char* get_account( void ) {return account_.data();}
    void set_ip_addr( const char* addr ) { ip_addr_ = addr; }
    const char* get_ip_addr( void ) {return ip_addr_.data();}
    int add_role_id ( int id ) 
    { 
        vector<int>::iterator iti; 
        iti = find( role_list_.begin(), role_list_.end(), id); 
        if ( iti == role_list_.end() )
        {
            role_list_.push_back(id);
            return 0;
        }

        return -1;
    }

    int get_role_list( vector<int>& list )
    {
        list = role_list_;
    }

    int is_role_exist( int id )
    {
        vector<int>::iterator iti; 
        iti = find( role_list_.begin(), role_list_.end(), id); 
        return iti != role_list_.end() ? 0:-1;
    }
private:
    uint64 account_id_;
    char is_minor_;
    int  track_status_;
    int  status_;
    int  online_time_;
    int  create_time_;
    int  login_time_;                         // 
    int  logout_time_;                        // 
    string account_;          // login account
    string r_name_;           // 
    string id_card_;        // 
    string ip_addr_;
    vector<int> role_list_;
};

struct Server_List_Data
{
    Server_List_Data():id_(0),server_name_(""), server_ip_(""),server_port_(0),server_state_(-1) {}
    ~Server_List_Data() {}
	enum STATE
	{
		STATE_HOT,
		STATE_RECOMEND,
	};
    void reset( void )
    {
        id_ = 0;
        server_name_ = "";
        server_ip_ = "";
        server_port_ = 0;
		server_state_=-1;

    }

    void set_id( int id ) {id_ = id;}
    int get_id( void ) {return id_;}

	void set_state(int state){server_state_=state ;}
	int get_state(){return server_state_;}

    void set_server_name( const char* name ) {server_name_ = name;}
    const char* get_server_name( void) {return server_name_.c_str();}

    void set_server_ip( const char* ip) {server_ip_ = ip;}
    const char* get_server_ip( void ) {return server_ip_.data();}

    void set_server_port( int port) {server_port_ = port;}
    int get_server_port(void) {return server_port_;}

    void set_next_ui( int ui) { next_ui_ = ui;}
    int get_next_ui( void ) {return next_ui_;}
private:
    int id_;
    std::string server_name_;
    std::string server_ip_;
    int server_port_;
    int next_ui_;
	int server_state_;
};

#endif // ACCOUNT_ATT_H_

