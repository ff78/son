#ifndef _UI_SECONDARY_INSTANCE_LAYER_
#define _UI_SECONDARY_INSTANCE_LAYER_

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
#include "Common/Utils.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
//USING_NS_CC_EXT;
#include <list>
USING_NS_CC;
using namespace ui;
#define INSTANCE_SUM_NUM		15
#define EACH_ICON_OWN_STARS		3

enum Star_Icon
{

};

using namespace std;

class Joiner_Guidance;
class UI_Secondary_Instance_Layer : public cocos2d::Layer
{
public:
	UI_Secondary_Instance_Layer(void);
	~UI_Secondary_Instance_Layer(void);

	virtual bool init();
	CREATE_FUNC(UI_Secondary_Instance_Layer);
	virtual void setVisible(bool visible);
	void showGuide();

	void buttonBackCallback( Ref* pSender ,Widget::TouchEventType type);
    void button_clicked_instance( Ref* pSender ,Widget::TouchEventType type);
	void openDescUI();
	void buttonPushDownCallback(Ref* pSender,Widget::TouchEventType type);
	void buttonCancelCallback(Ref* pSender,Widget::TouchEventType type);
	void imgBackClickCallBack(Ref* pSender,Widget::TouchEventType type);

    void init_instance_date(int area_id);
    void update();

private:
    const char* get_instance_icon_by_type(int type);

private:
	cocos2d::ui::ImageView*			m_img_star[INSTANCE_SUM_NUM][EACH_ICON_OWN_STARS];
	cocos2d::ui::Button*				m_btn_mission[INSTANCE_SUM_NUM];
	cocos2d::ui::ImageView*								line[INSTANCE_SUM_NUM];
    cocos2d::ui::Text*                m_lab_title_font;
	cocos2d::ui::ImageView*			m_img_cur_instance;
	cocos2d::ui::ImageView*			m_img_cur_instance_effect;
	cocos2d::ui::ImageView*			m_img_cur_material;
	cocos2d::ui::Button*				m_pBtnBack;

	int							instance_id;

	Joiner_Guidance*			juniorGuide;

private:
	enum guide_step
	{
		JUNIOR_GUIDE_STEP_5 = 5,
	};
};

#endif //_UI_SECONDARY_INSTANCE_LAYER_