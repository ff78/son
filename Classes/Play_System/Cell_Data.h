

#if !defined(EA_30FD9692_C55D_4b54_81AE_B274A885587E__INCLUDED_)
#define EA_30FD9692_C55D_4b54_81AE_B274A885587E__INCLUDED_

#include <string>
#include <list>
struct Cell_Data
{

	Cell_Data();
	virtual ~Cell_Data();

private:
	int count_require_;
	int counter_;
	std::string key_data_;
	std::list<std::string> para_value_list_;
	std::list<double> para_value_num_list_;
	int operation_bind_id_;

};
#endif // !defined(EA_30FD9692_C55D_4b54_81AE_B274A885587E__INCLUDED_)

