#ifndef _SELECT_SERVER_CLASS_
#define _SELECT_SERVER_CLASS_
#include "Game_Interface/common.h"
#include "cocos2d.h"
//#include "cocos-ext.h"
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include "ui/UITextField.h"
#include "ui/UILoadingBar.h"
#include "ui/UILayout.h"
#include "ui/UISlider.h"
#include "ui/UICheckBox.h"
#include "ui/UIWidget.h"
#include "ui/UIScrollView.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
//#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;
namespace Game_Logic
{
    struct Game_Interface;
}
class Select_Server_UI : public cocos2d::ui::Button
{
private:
	Select_Server_UI(void);
public:
	virtual ~Select_Server_UI(void);

	static Select_Server_UI* get_instance();

    int do_create_button_list( vector<uint64>& para );

	void set_name(int id, const char* name);
	const char* get_name(int id);

    static bool create_button_list(Game_Logic::Game_Interface& gm_interface);
    static bool set_button_name(Game_Logic::Game_Interface& gm_interface);
    static bool show_next_ui(Game_Logic::Game_Interface& gm_interface);

    void set_total_num( int num ) {sum_num_ = num;}
    int get_total_num( void ) { return sum_num_; }

private:
	void current_server(Ref* pSender,Widget::TouchEventType);
	void reset();

private:
	int sum_num_;
	static Select_Server_UI* instance_;

	map<int,string> m_for_name_;
	cocos2d::ui::Layout* panel;
};


#endif //_SELECT_SERVER_CLASS_
