#ifndef _COCOSTUDIO_INTERFACE_CLASS_
#define _COCOSTUDIO_INTERFACE_CLASS_

#include "ui/CocosGUI.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;

class CocoStu_UI_Scene_Interface
{
public:
	CocoStu_UI_Scene_Interface(void);
	virtual ~CocoStu_UI_Scene_Interface(void);

	static CocoStu_UI_Scene_Interface* get_instance();
	void run_test( int id );
	void lockScreen(const char* szTitle,const char* szContent="");
	void unlockScreen();

private:
	static CocoStu_UI_Scene_Interface* instance_point_;

};

#endif //_COCOSTUDIO_INTERFACE_CLASS_