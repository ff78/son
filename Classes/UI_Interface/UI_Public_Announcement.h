#ifndef _UI_PUBLIC_ANNOUNCEMENT_H_
#define _UI_PUBLIC_ANNOUNCEMENT_H_


#include "cocos2d.h"
//#include "cocos-ext.h"
#include "ui/UIScrollView.h"
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
#include "cocostudio/CocoStudio.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
#define FONT_SIZE 25
#define TITLE_SIZE 30
#define GAP 5
USING_NS_CC;
using namespace ui;
class UI_Public_Announcement:public cocos2d::Layer
{
public:
	static UI_Public_Announcement* instance();
public:
	UI_Public_Announcement();
	~UI_Public_Announcement();
	bool init();
	CREATE_FUNC(UI_Public_Announcement);

public:
	void update();

private:// init functions
	void initTableView();
	void closeBtnEventBlind();
	void refreshContent();
	void resetScrollList();

private://callback functions
	void closeReleaseCallback( Ref* pSender ,Widget::TouchEventType type);
	cocos2d::ui::Widget* createPA( const char* title, int title_font_size , const char* content, int content_font_size, bool separated = true );
	int calculateNeededLinesNums(const char* content, int display_width, int font_size = FONT_SIZE);

private:
	cocos2d::ui::Widget* public_announcement_widget_;
	cocos2d::ui::ScrollView* pal_scroll_view_;
	cocos2d::Size display_area_size_;
	cocos2d::Size content_area_size_;
	std::list<cocos2d::ui::ImageView*> pa_list;
	static UI_Public_Announcement *instance_;

};
#endif //_UI_PUBLIC_ANNOUNCEMENT_H_
