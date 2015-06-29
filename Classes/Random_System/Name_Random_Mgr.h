#ifndef __NAME_RANDOM_MGR__
#define __NAME_RANDOM_MGR__

#include <map>
#include <string>
using namespace std;


class Name_Random_Mgr
{
public:
	Name_Random_Mgr(void);
	~Name_Random_Mgr(void);

public:
	static Name_Random_Mgr* get_instance();
	int initialize(void);

	const char* get_name_by_id(int id);

private:
	int load_name_desc_date();    //����������� һ��ID ��Ӧһ���ַ���

private:
	static Name_Random_Mgr*			instance_;
	map<int, string>				m_map_name_container;
};

#endif //__NAME_RANDOM_MGR__
