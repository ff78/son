
#ifndef __JUNIOR_GUIDE_CONFIG_DATA_H__
#define __JUNIOR_GUIDE_CONFIG_DATA_H__

#include <string>
using namespace std;

struct junior_guide_config
{
	junior_guide_config()
	{
		reset();
	}

	~junior_guide_config()
	{
		reset();
	}

	void reset()
	{
		base_id_ = 0;
		desc_ = 0;
		pos_x_ = 0;
		pos_y_ = 0;
		img_index_ = 0;
	}

	int                     base_id_;                           // ����id
	int                     desc_;                              // ����������
	int                     pos_x_;                             // ������ʾ x ����
	int                     pos_y_;                             // ������ʾ y ����
	int						img_index_;							// �������
};


#endif /* __JUNIOR_GUIDE_CONFIG_DATA_H__ */

