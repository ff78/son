#ifndef _UI_INSTANCE_LAYER_
#define _UI_INSTANCE_LAYER_
//#include "cocos-ext.h"
#include "cocos2d.h"
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
#include "Common/Utils.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;
class Joiner_Guidance;
class UI_Instance_Layer : public cocos2d::Layer
{
public:
	UI_Instance_Layer(void);
	~UI_Instance_Layer(void);

	virtual bool init();
	CREATE_FUNC(UI_Instance_Layer);

	virtual void setVisible( bool visible );
	void bagCloseCallback( Ref* pSender,Widget::TouchEventType type );

	void button_clicked_area( Ref* pSender ,Widget::TouchEventType type);
	void backCallback( Ref* pSender ,Widget::TouchEventType type);
    void update(void);

    static void clicked_area(int area_id);
	static void show_npc_dialog(int sprite_id);

private:
	cocos2d::ui::Button*			m_btn_pic_mountain[5];
	cocos2d::ui::Button*			m_btn_button[5];
	cocos2d::ui::Text*			m_lab_mountain_name[5];
	cocos2d::ui::Text*			m_lab_level_limit[5];

	Joiner_Guidance*			juniorGuide;
};

#endif //_UI_INSTANCE_LAYER_