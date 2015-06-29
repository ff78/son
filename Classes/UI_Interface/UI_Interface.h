
#if !defined(EA_BE58D2EA_155C_4d53_9DB1_3BD1119C4021__INCLUDED_)
#define EA_BE58D2EA_155C_4d53_9DB1_3BD1119C4021__INCLUDED_
#pragma warning(disable:4251) 

#include "ui/CocosGUI.h"

#include "cocos2d.h"
#include "ui/UIWidget.h"
USING_NS_CC;
using namespace ui;
class UI_Interface
{

public:
	UI_Interface();
	virtual ~UI_Interface();
	
	static UI_Interface* instance();
	
	void event_register(int id);
	void click_event(cocos2d::Ref* pSender,Widget::TouchEventType type);

	void do_test(int nId);

private:
	static UI_Interface* instance_p_;

};
#endif // !defined(EA_BE58D2EA_155C_4d53_9DB1_3BD1119C4021__INCLUDED_)
