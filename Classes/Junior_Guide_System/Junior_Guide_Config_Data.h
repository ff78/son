
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

	int                     base_id_;                           // 任务id
	int                     desc_;                              // 任务步骤描述
	int                     pos_x_;                             // 任务提示 x 坐标
	int                     pos_y_;                             // 任务提示 y 坐标
	int						img_index_;							// 镜像与否
};


#endif /* __JUNIOR_GUIDE_CONFIG_DATA_H__ */

