
#include "UI_Interface/UI_Interface.h"
#include "Game_Interface/common.h"
#include "Game_Interface/game_content_interface.h"
#include "UI_Config.h"
#include "UI_Config_Data_Mgr.h"
#include "cocos2d.h"
#include "UI/Main_City_Scene.h"
using namespace ui;
UI_Interface* UI_Interface::instance_p_ = 0;
UI_Interface::UI_Interface()
{

}

UI_Interface::~UI_Interface()
{

}

UI_Interface* UI_Interface::instance()
{
	if (!instance_p_)
		instance_p_ = new UI_Interface;
	return instance_p_;
}

void UI_Interface::click_event(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
	cocos2d::ui::Widget* pWidget;
	int nId;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		pWidget = (cocos2d::ui::Widget*)pSender;
		nId = pWidget->getTag();

		do_test(nId);
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}


void UI_Interface::event_register(int id)
{
	Game_Data::UI_Config* uiconf = Game_Data::UI_Config_Data_Mgr::instance()->get_ui_config_list_by_id(id);
	if (NULL == uiconf)
		return;

	cocos2d::ui::Widget* pWidRoot = NULL;

	cocos2d::ui::Widget* pLayer = UI::Main_City_Actor_Layer::get_instance()->getUILayerWidget();
	const char* szName = uiconf->get_ui_name();
	cocos2d::ui::Widget* pWidget = (cocos2d::ui::Widget*)(Helper::seekWidgetByName(pLayer, szName));
	if (!pWidget)
		return;

	pWidget->setTag(id);
	pWidget->addTouchEventListener(pWidget, toucheventselector(UI_Interface::click_event));

}

void UI_Interface::do_test(int nId)
{
	vector<uint64> para;
	para.push_back(nId);
	Game_Logic::Game_Content_Interface::instance()->exec_interface("execUI", para, "");
}