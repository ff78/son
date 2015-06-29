
#if !defined(EA_C4C17382_C702_49e1_8635_D1437A6651BD__INCLUDED_)
#define EA_C4C17382_C702_49e1_8635_D1437A6651BD__INCLUDED_

#include "Game_Interface/common.h"
#include "Game_Interface/game_element.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;
namespace cs
{
	class CocoWidget;
};
namespace Game_Data
{
struct UI_Config;
class UI_Config_Data_Mgr
{

public:
	UI_Config_Data_Mgr();
	virtual ~UI_Config_Data_Mgr();

	static UI_Config_Data_Mgr* instance();
	void init();

	int get_ui_config_data_by_id(int id, UI_Config& UIc);

	void load_ui_config_data();

	int get_ui_config_list(map<int, UI_Config>& list);

    UI_Config* get_ui_config_list_by_id( int id );

private:
	static UI_Config_Data_Mgr* instance_p_;
	map<int, UI_Config> ui_config_list_;
};
}
#endif // !defined(EA_C4C17382_C702_49e1_8635_D1437A6651BD__INCLUDED_)
