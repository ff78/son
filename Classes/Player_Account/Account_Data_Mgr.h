
#if !defined(EA_1FBE462B_0C7A_4fee_8DD6_E52E0E0335B7__INCLUDED_)
#define EA_1FBE462B_0C7A_4fee_8DD6_E52E0E0335B7__INCLUDED_

#include "Game_Interface/common.h"

#ifndef MAX_ROLE_COUNT
#define MAX_ROLE_COUNT 3
#endif

struct Server_List_Data;
struct Account_Data;
class Account_Data_Mgr
{

public:
	
	struct SRoleData
	{
		int m_nRoleID;
		int m_nBaseID;
		int m_nLevel;
        int m_nSex;
		std::string m_strName;
	}m_RoleData[MAX_ROLE_COUNT];

	Account_Data_Mgr();
	virtual ~Account_Data_Mgr();
    int init(void);
    static Account_Data_Mgr* instance();
    void set_next_ui_config_id( int id) {next_ui_config_id_ = id;}
    int get_next_ui_config_id( void )  {return next_ui_config_id_;}

    int load_server_list( const char* pzPath );
    int get_server_list(map<int, Server_List_Data>& svr_lst);
    int get_server_list_by_id( int id, Server_List_Data& sld );

	int load_partition_server_info( const char* pzPath );

	int load_server_list_from_str( const char* server_list_in_string , int size );

    int add_acount( Account_Data& ad);
    int get_account_by_name(const char* name, Account_Data& ad );
    int get_account_by_id( int id, Account_Data& ad );
    int modi_account_data_by_name(const char* name, Account_Data& ad);
    int modi_account_by_id( int id, Account_Data& ad );

    void set_self_account( const char* account ) {self_account_ = account;}
    const char* get_self_account( void ) {return self_account_.data(); }
    int get_self_account( Account_Data& ad );

    void set_avatar_id ( int sex );
    int get_avatar_id ( void ) { return avatar_id_; }

    void set_current_role_id ( int role_id ) { current_role_id_ = role_id; }
    int get_current_role_id ( void ) { return current_role_id_; }

    void set_role_num( int role_num ) { m_nRoleNum = role_num; }
    int get_role_num ( void ) { return m_nRoleNum; }

	void set_current_select( int index ) { m_nCurrentSelectIndex = index; }
    const SRoleData* get_current_select ( void );

    void set_is_show_all_stage ( int is ) { m_is_show_all_stage = is; }
    int get_is_show_all_stage ( void ) { return m_is_show_all_stage; }

    void set_is_first_login ( int is ) { m_is_first_login = is; }
    int get_is_first_login ( void ) { return m_is_first_login; }

	std::string get_version( void ){ return m_version; }

	std::string partition_server_ip( void ) { return partition_server_ip_; }

	int partition_server_port( void ) { return partition_server_port_; }
    int getJob() { return select_job; }
    void setJob(int job) {
        select_job = job;
    }
private:
   static Account_Data_Mgr* instance_;

   map<int, Server_List_Data> server_list_;
   map<string, Account_Data> account_list_; 

    int select_job;
   int next_ui_config_id_;
   string self_account_;
   int avatar_id_;
   int current_role_id_;
   int m_nRoleNum;
   int m_nCurrentSelectIndex;

   int m_is_show_all_stage;
   int m_is_first_login;

   std::string partition_server_ip_;
   int partition_server_port_;

   std::string m_version; //客户端版本信息
};
#endif // !defined(EA_1FBE462B_0C7A_4fee_8DD6_E52E0E0335B7__INCLUDED_)
