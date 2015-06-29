#ifndef _UI_JSON_LOGIC_MGR_CLASS_
#define _UI_JSON_LOGIC_MGR_CLASS_

#include "Game_Interface/event_define.h"
#include "Game_Interface/game_element.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include "ui/UITextField.h"
#include "ui/UILoadingBar.h"
#include "ui/UILayout.h"
#include "ui/UISlider.h"
#include "ui/UICheckBox.h"
#include "ui/UIWidget.h"
#include "ui/UIScrollView.h"
#include "ui/UIDeprecated.h"
#include "ui/UIHelper.h"
#include "ui/UIPageView.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;

class CocoStu_UI_Scene_Logic
{
public:
	CocoStu_UI_Scene_Logic(void);
	virtual ~CocoStu_UI_Scene_Logic(void);

	static CocoStu_UI_Scene_Logic* get_instance();

	int init_UI_Scene_system();
	int excu_UI_Scene_fun(const char* cmd, std::vector<uint64> para/*, const char* key*/);
	static bool exec_UI_Scene(Game_Logic::Game_Interface& gm_interface);

private:
	static CocoStu_UI_Scene_Logic* instance_;
	Game_Logic::game_interface_handler_map_t UI_Json_fun_call_list_;
};

#endif //_UI_JSON_LOGIC_MGR_CLASS_