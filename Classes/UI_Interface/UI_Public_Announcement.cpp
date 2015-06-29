#include "UI_Public_Announcement.h"

#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Public_Annoucement/Public_Annoucement_Data_Mgr.h"
#include "Common/GameDefine.h"
#include "Common/GameResource.h"

USING_NS_CC;
using namespace ui;
UI_Public_Announcement *UI_Public_Announcement::instance_ = NULL;
UI_Public_Announcement::UI_Public_Announcement()
	:public_announcement_widget_(NULL)
	,pal_scroll_view_(NULL)
{
	display_area_size_ = CCSizeZero;
	content_area_size_ = CCSizeZero;
	pa_list.clear();
}

UI_Public_Announcement::~UI_Public_Announcement()
{
	instance_ = NULL;
}

bool UI_Public_Announcement::init()
{
	bool result = false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());
		
		public_announcement_widget_ = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Public_Announcement_Layer/Public_Announcement_Layer.ExportJson");
		addChild(public_announcement_widget_);
		pal_scroll_view_ = dynamic_cast<cocos2d::ui::ScrollView*>(Helper::seekWidgetByName(public_announcement_widget_,"PAL_SCROLL_VIEW"));
		if (pal_scroll_view_)
		{
			this->display_area_size_ = pal_scroll_view_->getSize();
		}
		this->closeBtnEventBlind();
		this->refreshContent();
		result = true;
	} while (0);

	return result;
}

void UI_Public_Announcement::refreshContent()
{
	this->resetScrollList();

	Game_Data::PAD_Map annoucement_list = Game_Data::Public_Annoucement_Data_Mgr::instance()->get_pad_map() ;

	for (Game_Data::PAD_Iter iter = annoucement_list.begin(); iter != annoucement_list.end(); ++iter)
	{
		bool separated = true;
		if (iter == annoucement_list.begin())
		{
			separated = false;
		}
		std::string title	= iter->second->title;
		std::string content = iter->second->content;
		cocos2d::ui::ImageView* pa = dynamic_cast<cocos2d::ui::ImageView*>(this->createPA(title.c_str(),TITLE_SIZE,content.c_str(),FONT_SIZE,separated));
		content_area_size_.width = pa->getSize().width;
		content_area_size_.height = content_area_size_.height + pa->getSize().height;
		pa_list.push_back(pa);
	}
	
	if (content_area_size_.height <= display_area_size_.height) // 如果滚动层的内部容器层的高小于滚动层的高，则将内部容器层的高设置为与滚动层的高相等。
	{
		content_area_size_.height = display_area_size_.height;
	}
	pal_scroll_view_->setInnerContainerSize(content_area_size_);

	int buttomX = 0;
	int buttomY = 0;

	for (std::list<cocos2d::ui::ImageView*>::iterator it = pa_list.begin(); it != pa_list.end(); ++it)
	{
		cocos2d::ui::ImageView* tmp = dynamic_cast<cocos2d::ui::ImageView*>(*it);
		if (!tmp)
		{
			return;
		}

		int x = buttomX;
		int y = (int)(pal_scroll_view_->getInnerContainerSize().height - buttomY);

		tmp->setPosition(Vec2(x,y));
		pal_scroll_view_->getInnerContainer()->addChild(tmp);

		buttomY += (int)(tmp->getSize().height);
	}
}

void UI_Public_Announcement::closeBtnEventBlind()
{
	cocos2d::ui::Button* close_btn = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(public_announcement_widget_,"PAL_CLOSE"));
	close_btn->addTouchEventListener(this,toucheventselector(UI_Public_Announcement::closeReleaseCallback));
}

void UI_Public_Announcement::closeReleaseCallback( Ref* pSender,cocos2d::ui::Widget::TouchEventType type )
{
	this->setVisible(false);
}

void UI_Public_Announcement::initTableView()
{

}

int UI_Public_Announcement::calculateNeededLinesNums( const char* content, int display_width, int font_size/* = FONT_SIZE*/ )
{
	int lines_num = 0;
	int head = 0;
	int one_line_nums = (int)(floor(display_width/font_size));
	std::string temp_str = content;
	string::size_type position = 0;
	do 
	{
		position = temp_str.find('\n', position);
		if (temp_str.npos == position)
		{
			lines_num += (int)(ceil( ((float)temp_str.length() - (float)head)/2 * ((float)font_size) / (float)display_width )); 
		}
		else if((int)(position - head) <= one_line_nums*2)
		{
			lines_num++;
			head = position;
			position++;
		}
		else if ((int)(position - head) > one_line_nums*2)
		{
			lines_num += (int)(ceil( (float)(position - head)/2 * ((float)font_size) / (float)display_width ));
			lines_num++;
			head = position;
			position++;
		}
	} while (position != temp_str.npos);
	
	return lines_num;
}

cocos2d::ui::Widget* UI_Public_Announcement::createPA( const char* title, int title_font_size , const char* content, int content_font_size, bool separated)
{
	float separator_y = 0;
	cocos2d::ui::ImageView *separator = NULL;
	if (separated)
	{
		separator  = cocos2d::ui::ImageView::create();
		
		separator->loadTexture( SEPARATOR_FILE );
		separator->setAnchorPoint( Vec2( 0, 1 ) );

		separator_y = separator->getSize().height;

separator->setScale9Enabled(true);
separator->setSize( Size( display_area_size_.width, separator_y ) );
	}

	cocos2d::ui::Text* title_obj = cocos2d::ui::Text::create();
	title_obj->setFontName( "DroidSansFallback" );
	//title_obj->setFontSize( title_font_size );
	title_obj->setColor( ccc3( 228, 173, 60 ) );
	title_obj->setTextHorizontalAlignment( kCCTextAlignmentLeft );
	title_obj->setString( title );
	title_obj->setAnchorPoint( Vec2( 0, 1 ) );
	title_obj->setPosition( Vec2( 0,-( GAP + separator_y ) ) );

	int lines = this->calculateNeededLinesNums(content,(int)display_area_size_.width,content_font_size);
	cocos2d::ui::TextField* content_obj = cocos2d::ui::TextField::create();
	content_obj->setTextAreaSize(Size(display_area_size_.width, (content_font_size+4)*lines));
	content_obj->setFontName("Helvetica");
	content_obj->setFontSize(content_font_size);
	content_obj->setColor(ccc3(204,176,102));
	content_obj->setTextHorizontalAlignment(kCCTextAlignmentLeft);
	content_obj->setText(content);
	content_obj->setAnchorPoint(Vec2(0,1));
	cocos2d::Size c_size = content_obj->getSize();
	content_obj->setPosition(Vec2(0,-(title_obj->getSize().height + 2*GAP + separator_y )));

	cocos2d::ui::ImageView* back_ground = cocos2d::ui::ImageView::create();
	back_ground->loadTexture(PA_BG_FILE);
	back_ground->setAnchorPoint(Vec2(0,1));

back_ground->setScale9Enabled(true);
back_ground->setSize(Size(display_area_size_.width , (title_obj->getSize().height + content_obj->getSize().height + 3* GAP + separator_y)));

	if (separator)
	{
		back_ground->addChild(separator);
	}
	back_ground->addChild(title_obj);
	back_ground->addChild(content_obj);

	return back_ground;
}

void UI_Public_Announcement::resetScrollList()
{
	if (NULL == pal_scroll_view_)
	{
		return;
	}
	pal_scroll_view_->getInnerContainer()->removeAllChildrenWithCleanup(true);
	pal_scroll_view_->setInnerContainerSize(Size(0,0));

	pa_list.clear();
	content_area_size_ = CCSizeZero;
}

void UI_Public_Announcement::update()
{
	this->refreshContent();
}

UI_Public_Announcement* UI_Public_Announcement::instance()
{
	if (instance_ == NULL)
	{
		instance_ = UI_Public_Announcement::create();
	}
	return instance_;
}

