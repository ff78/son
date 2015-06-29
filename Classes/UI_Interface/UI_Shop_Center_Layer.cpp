#include "UI_Shop_Center_Layer.h"

#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Item_System/Item_Config_Mgr.h"
#include "Shop_System/Shop_Config_Mgr.h"
#include "Shop_System/Shoping_Record_Mgr_Cl.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player.h"

#include "UI_MainMenu_Layer.h"
#include "UI_Trade_Layer.h"

#include "Common/GameResource.h"
#include "Common/GameDefine.h"

using namespace Game_Data;
using namespace ui;
UI_Shop_Center_Layer::UI_Shop_Center_Layer(void) : 
	m_root_widget(NULL),
	m_btn_close(NULL),
	m_tbn_first(NULL),
	m_lab_first_font(NULL),
	m_tbn_second(NULL),
	m_lab_second_font(NULL),
	m_tbn_third(NULL),
	m_lab_third_font(NULL),
	m_lab_player_cur_money(NULL),
	m_img_left_arrow(NULL),
	m_img_right_arrow(NULL),
	m_img_second_back(NULL),
	m_img_scroll_back(NULL),
	m_img_scroll_copy_back(NULL),
	m_page_view(NULL),
	m_btn_charge_money(NULL),
	m_cur_shop_type(0)
{
	memset(m_img_icon_root_back, 0, sizeof(m_img_icon_root_back));
	memset(m_img_icon_texture_back, 0, sizeof(m_img_icon_texture_back));
	memset(m_img_icon_texture, 0, sizeof(m_img_icon_texture));
	memset(m_lab_icon_name, 0, sizeof(m_lab_icon_name));

	memset(m_img_delete_line, 0, sizeof(m_img_delete_line));
	memset(m_img_original_texture, 0, sizeof(m_img_original_texture));
	memset(m_lab_original_price, 0, sizeof(m_lab_original_price));
	memset(m_img_discount_texture, 0, sizeof(m_img_discount_texture));
	memset(m_lab_discount_price, 0, sizeof(m_lab_discount_price));
	memset(m_img_light_reflect_cur_page, 0, sizeof(m_img_light_reflect_cur_page));
    memset(m_goods_id,0,sizeof(m_goods_id));
}


UI_Shop_Center_Layer::~UI_Shop_Center_Layer(void)
{
}

bool UI_Shop_Center_Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());

		m_root_widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Shop_Layer/Shop_Layer.ExportJson");
		this->addChild(m_root_widget);

		initComponent();

		bRet = true;
	} while (0);

	return bRet;
}

void UI_Shop_Center_Layer::setVisible(bool visible)
{
	cocos2d::Layer::setVisible(visible);
	if (visible)
	{
		m_tbn_first->setBrightStyle(BRIGHT_HIGHLIGHT);
		m_tbn_second->setBrightStyle(BRIGHT_NORMAL);
		m_tbn_third->setBrightStyle(BRIGHT_NORMAL);

        update();
	}
	else
	{
        m_cur_shop_type = Game_Data::ST_GOLD_SHOP;
	}
}

void UI_Shop_Center_Layer::initComponent()
{
	//关闭按钮
	m_btn_close = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_root_widget,"btn_close"));
	m_btn_close->addTouchEventListener(this, toucheventselector(UI_Shop_Center_Layer::buttonCloseCallback));

	//按钮切换区
	m_tbn_first = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_root_widget,"tbn_label_first"));
	m_tbn_first->addTouchEventListener(this, toucheventselector(UI_Shop_Center_Layer::buttonFirstCallback));
	m_lab_first_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_label_first_font"));
	m_lab_first_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SP_CENTER_SIVER));
	m_tbn_first->setBrightStyle(BRIGHT_HIGHLIGHT);

	m_tbn_second = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_root_widget,"tbn_label_second"));
	m_tbn_second->addTouchEventListener(this, toucheventselector(UI_Shop_Center_Layer::buttonSecondCallback));
	m_lab_second_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_label_second_font"));
	m_lab_second_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SP_CENTER_GOLD_INGOLT));

	m_tbn_third = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_root_widget,"tbn_label_third"));
	m_tbn_third->addTouchEventListener(this, toucheventselector(UI_Shop_Center_Layer::buttonThirdCallback));
	m_lab_third_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_label_third_font"));
	m_lab_third_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SP_CENTER_SPECIAL_SELLING));
	
	m_img_player_cur_money_texture = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_root_widget,"img_player_cur_silver_icon"));

	m_lab_player_cur_money  = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_root_widget,"lab_player_cur_money"));
	m_lab_player_cur_money->setString("");

	//物品滑动区
	m_img_left_arrow = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_root_widget,"img_left_arrow"));
	m_img_left_arrow->setTouchEnabled(true);
	m_img_left_arrow->addTouchEventListener(this, toucheventselector(UI_Shop_Center_Layer::leftArrowCallback));
	m_img_right_arrow = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_root_widget,"img_right_arrow"));
	m_img_right_arrow->setTouchEnabled(true);
	m_img_right_arrow->addTouchEventListener(this, toucheventselector(UI_Shop_Center_Layer::rightArrowCallback));

	m_img_second_back = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_root_widget,"img_second_back"));

	m_img_scroll_back = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_root_widget,"img_scroll_back"));
	m_img_scroll_copy_back = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_root_widget,"img_scroll_copy_back"));

	cocos2d::ui::ImageView* scroll_page_view = createPageView();
	m_img_second_back->addChild(scroll_page_view);
	scroll_page_view->setZOrder(100);

    m_cur_shop_type = Game_Data::ST_GOLD_SHOP;
}

void UI_Shop_Center_Layer::buttonCloseCallback( Ref* pSender ,Widget::TouchEventType type)
{
	setVisible(false);
}

void UI_Shop_Center_Layer::buttonFirstCallback( Ref* pSender ,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	m_page_view->scrollToPage(0);
    m_cur_shop_type = Game_Data::ST_GOLD_SHOP;

	m_tbn_first->setBrightStyle(BRIGHT_HIGHLIGHT);
	m_tbn_second->setBrightStyle(BRIGHT_NORMAL);
	m_tbn_third->setBrightStyle(BRIGHT_NORMAL);

	m_lab_btn_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SP_CENTER_GAIN_SILVER));

	controlVisibleOrNot(true);

    update();

	break;
    default:
	break;
}
}

void UI_Shop_Center_Layer::buttonSecondCallback( Ref* pSender ,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	m_page_view->scrollToPage(0);
    m_cur_shop_type = Game_Data::ST_TOKEN_SHOP;

	m_tbn_first->setBrightStyle(BRIGHT_NORMAL);
	m_tbn_second->setBrightStyle(BRIGHT_HIGHLIGHT);
	m_tbn_third->setBrightStyle(BRIGHT_NORMAL);

	m_lab_btn_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SP_CENTER_GAIN_GOLD));

	controlVisibleOrNot(true);

    update();

	break;
    default:
	break;
}
}

void UI_Shop_Center_Layer::buttonThirdCallback( Ref* pSender ,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	m_page_view->scrollToPage(0);
    m_cur_shop_type = Game_Data::ST_SPECIAL_SHOP;

	m_tbn_first->setBrightStyle(BRIGHT_NORMAL);
	m_tbn_second->setBrightStyle(BRIGHT_NORMAL);
	m_tbn_third->setBrightStyle(BRIGHT_HIGHLIGHT);

	controlVisibleOrNot(false);

    update();

	break;
    default:
	break;
}
}

void UI_Shop_Center_Layer::leftArrowCallback( Ref* pSender,Widget::TouchEventType type )
{
int curPage;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	if( m_page_view )
	{
		curPage =m_page_view->getCurPageIndex();
		if( curPage > 0 )
		{
			m_page_view->scrollToPage(--curPage);
		}
	}

	break;
    default:
	break;
}
}

void UI_Shop_Center_Layer::rightArrowCallback( Ref* pSender,Widget::TouchEventType type )
{
int curPage ;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	if( m_page_view )
	{
		curPage =m_page_view->getCurPageIndex();
		if( curPage < PAGE_SUM_NUM_S-1 )
		{
			m_page_view->scrollToPage(++curPage);
		}
	}

	break;
    default:
	break;
}
}

void UI_Shop_Center_Layer::controlVisibleOrNot( bool visible )
{
	m_btn_charge_money->setVisible(visible);
	m_btn_charge_money->setTouchEnabled(visible);
}

cocos2d::ui::ImageView* UI_Shop_Center_Layer::createPageView()
{
	//scroll view first layer
	cocos2d::ui::ImageView* img_back = cocos2d::ui::ImageView::create();
	img_back->loadTexture(PAGE_INNER_VIEW_BG_LXD/*GIFT_BG_FRAME*/);
img_back->setScale9Enabled(true);
img_back->setSize(Size(900,500));
	/*
	scroll view second layer, if things change with layer change , 
	you should place them on here , else place them on the first layer
	*/
	m_page_view = cocos2d::ui::PageView::create();
	m_page_view->setTouchEnabled(true);
	m_page_view->setSize(Size(860,440));
	m_page_view->setAnchorPoint(Vec2(0.5f, 0.5f));

	for ( int i=0; i<PAGE_SUM_NUM_S; ++i )
	{
		cocos2d::ui::Layout* layout = cocos2d::ui::Layout::create();
		layout->setSize(Size(860,440));

		for ( int j=0; j<EACH_PAGE_NUM_S; ++j )
		{
			//出售物品大背景
			m_img_icon_root_back[i][j] = cocos2d::ui::ImageView::create();
			m_img_icon_root_back[i][j]->loadTexture("pic_bg_3.png", UI_TEX_TYPE_PLIST);
			m_img_icon_root_back[i][j]->setTouchEnabled(true);
	m_img_icon_root_back[i][j]->setScale9Enabled(true);
	m_img_icon_root_back[i][j]->setSize(Size(250,120));
			m_img_icon_root_back[i][j]->setAnchorPoint(Vec2(0.5f, 0.5f));
			layout->addChild(m_img_icon_root_back[i][j]);
			m_img_icon_root_back[i][j]->setPosition(Vec2(290*(j%3)-290 + m_img_icon_root_back[i][j]->getContentSize().width + 325, 
														-140*(j/3)+140 + m_img_icon_root_back[i][j]->getContentSize().height + 100));
		m_img_icon_root_back[i][j]->setTag(i*EACH_PAGE_NUM_S+j);
			m_img_icon_root_back[i][j]->addTouchEventListener(this, toucheventselector(UI_Shop_Center_Layer::goodsSellInfoCallback));

			//出售物品icon背景
			m_img_icon_texture_back[i][j] = cocos2d::ui::ImageView::create();
			m_img_icon_texture_back[i][j]->loadTexture("pic_zhuangbeikuang_1.png", UI_TEX_TYPE_PLIST);
			m_img_icon_root_back[i][j]->addChild(m_img_icon_texture_back[i][j]);
			m_img_icon_texture_back[i][j]->setPosition(Vec2(-66, 0));

			//出售物品图标
			m_img_icon_texture[i][j] = cocos2d::ui::ImageView::create();
			m_img_icon_texture_back[i][j]->addChild(m_img_icon_texture[i][j]);

			//出售物品的数量
			m_lab_icon_number[i][j] = cocos2d::ui::Text::create();
//			m_lab_icon_number[i][j]->setFontSize(FONT_SIZE_S);
			m_img_icon_texture_back[i][j]->addChild(m_lab_icon_number[i][j]);
			m_lab_icon_number[i][j]->setPosition(Vec2(33, -33));

			//图标名称
			m_lab_icon_name[i][j] = cocos2d::ui::Text::create();
			m_lab_icon_name[i][j]->setAnchorPoint(Vec2(0.0f, 0.5f));
//			m_lab_icon_name[i][j]->setFontSize(20);
			m_lab_icon_name[i][j]->setColor(ccc3(255, 204, 11));
			m_img_icon_root_back[i][j]->addChild(m_lab_icon_name[i][j]);
			m_lab_icon_name[i][j]->setPosition(Vec2(-10, 30));

			//原始售价图标
			m_img_original_texture[i][j] = cocos2d::ui::ImageView::create();
			m_img_original_texture[i][j]->loadTexture("silver.png", UI_TEX_TYPE_PLIST);
			m_img_icon_root_back[i][j]->addChild(m_img_original_texture[i][j]);
			m_img_original_texture[i][j]->setPosition(Vec2(3, 0));

			//原价
			m_lab_original_price[i][j] = cocos2d::ui::Text::create();
			m_lab_original_price[i][j]->setAnchorPoint(Vec2(0, 0.5f));
			//m_lab_original_price[i][j]->setFontSize(FONT_SIZE_S);
			m_lab_original_price[i][j]->setColor(ccc3(255, 223, 151));
			m_img_icon_root_back[i][j]->addChild(m_lab_original_price[i][j]);
			m_lab_original_price[i][j]->setPosition(Vec2(31, 0));

			//删除线
			m_img_delete_line[i][j] = cocos2d::ui::ImageView::create();
			m_img_delete_line[i][j]->loadTexture("pic_fengexian_red.png", UI_TEX_TYPE_PLIST);
	m_img_delete_line[i][j]->setScale9Enabled(true);
	m_img_delete_line[i][j]->setSize(Size(100,4));
			m_img_icon_root_back[i][j]->addChild(m_img_delete_line[i][j]);
			m_img_delete_line[i][j]->setPosition(Vec2(37, 0));

			//折后售价图标
			m_img_discount_texture[i][j] = cocos2d::ui::ImageView::create();
			m_img_discount_texture[i][j]->loadTexture("silver.png", UI_TEX_TYPE_PLIST);
			m_img_icon_root_back[i][j]->addChild(m_img_discount_texture[i][j]);
			m_img_discount_texture[i][j]->setPosition(Vec2(5, -34));

			//折后价
			m_lab_discount_price[i][j] = cocos2d::ui::Text::create();
			m_lab_discount_price[i][j]->setAnchorPoint(Vec2(0, 0.5f));
//			m_lab_discount_price[i][j]->setFontSize(FONT_SIZE_S);
			m_lab_discount_price[i][j]->setColor(ccc3(255, 223, 151));
			m_img_icon_root_back[i][j]->addChild(m_lab_discount_price[i][j]);
			m_lab_discount_price[i][j]->setPosition(Vec2(32, -34));
		}

		//当前页数显示图标
// 		m_img_light_reflect_cur_page[i] = cocos2d::ui::ImageView::create();
// 		if( 0 == i )
// 		{
// 			m_img_light_reflect_cur_page[i]->loadTexture(CUR_PAGE_GREEN_PIC);
// 		}
// 		else
// 		{
// 			m_img_light_reflect_cur_page[i]->loadTexture(CUR_PAGE_RED_PIC);
// 		}
// 		m_img_light_reflect_cur_page[i]->setPosition(Vec2(-30+i*30, -210));
// 		img_back->addChild(m_img_light_reflect_cur_page[i]);

		m_page_view->addPage(layout);
	}

	//显示页码
	m_lab_vision_page = cocos2d::ui::Text::create();
	img_back->addChild(m_lab_vision_page);
	m_lab_vision_page->setPosition(Vec2(0, -210));
//	m_lab_vision_page->setFontSize(30);
	m_lab_vision_page->setString(CCString::createWithFormat("%d/%d", 1, PAGE_SUM_NUM_S)->getCString());

	//获取银两按钮
	m_btn_charge_money = cocos2d::ui::Button::create();
	m_btn_charge_money->loadTextures(TIDY_BUTTON_NORMAL, TIDY_BUTTON_PRESSED, TIDY_BUTTON_DISABLED);
	img_back->addChild(m_btn_charge_money);
	m_btn_charge_money->setPosition(Vec2(345, -215));
	m_btn_charge_money->setTouchEnabled(true);
	m_btn_charge_money->addTouchEventListener(this, toucheventselector(UI_Shop_Center_Layer::btnChargeMoneyCallback));

	//按钮上的字体
	m_lab_btn_font = cocos2d::ui::Text::create();
	m_btn_charge_money->addChild(m_lab_btn_font);
	m_lab_btn_font->setFontSize(FONT_SIZE_S);
	m_lab_btn_font->setColor(ccc3(255, 223, 151));
	m_lab_btn_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SP_CENTER_GAIN_SILVER));

	img_back->addChild(m_page_view);
	m_page_view->setPosition(Vec2(0, 30));

	m_page_view->addEventListenerPageView(this, pagevieweventselector(UI_Shop_Center_Layer::pageViewEvent));

	return img_back;
}

void UI_Shop_Center_Layer::pageViewEvent( Ref *pSender, cocos2d::ui::PageViewEventType type )
{
	switch (type)
	{
	case PAGEVIEW_EVENT_TURNING:
		{
			cocos2d::ui::PageView* pageView = dynamic_cast<cocos2d::ui::PageView*>(pSender);
			//CCLog("pageView->getPage() = %d",pageView->getPage());
			m_lab_vision_page->setString(CCString::createWithFormat("%d/%d", pageView->getCurPageIndex()+1, PAGE_SUM_NUM_S)->getCString());
// 			if(m_int_cur_page != pageView->getPage())
// 			{
// 				m_int_cur_page = pageView->getPage();
// 				for(int i=0; i<PAGE_SUM_NUM_S; ++i)
// 				{
// 					if(i == m_int_cur_page)
// 					{
// 						m_img_light_reflect_cur_page[i]->loadTexture(CUR_PAGE_GREEN_PIC);
// 					}
// 					else
// 					{
// 						m_img_light_reflect_cur_page[i]->loadTexture(CUR_PAGE_RED_PIC);
// 					}
// 				}
// 			}
		}
		break;

	default:
		break;
	}
}

void UI_Shop_Center_Layer::goodsSellInfoCallback( Ref* pSender,Widget::TouchEventType type )
{
cocos2d::ui::ImageView* curImg;
int goods_id ;
int last_count ;
Game_Data::shoping_record* record;
 Game_Data::shop_config* shop_config;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	curImg = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
    goods_id =m_goods_id[curImg->getTag()];
    shop_config = SHOP_CONFIG_MGR::instance()->get_shop_config(goods_id);
    if (!shop_config)
    {
        return;
    }

    if (shop_config->buy_count_ > 0)
    {
        last_count = shop_config->buy_count_;
        record = SHOPING_RECORD_MGR::instance()->get_shoping_record(shop_config->base_id_);
        if (record)
        {
            if (shop_config->buy_count_ > record->buy_count_)
            {
                last_count = shop_config->buy_count_ - record->buy_count_;
            } 
            else
            {
                last_count = 0;
            }
        }

        if (last_count == 0)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(TODAY_PURCHASE_TIMES_OVER);
            return;
        }
    }
    
    UI_MainMenu_Layer::get_instance()->visibleTradeLayer(goods_id, STYLE_BUY_ATTR_GOODS);
	//UI_Buy_Layer::set_style_show_info(goods_id, STYLE_BUY_ATTR_GOODS);

	break;
    default:
	break;
}
}

void UI_Shop_Center_Layer::btnChargeMoneyCallback( Ref* pSender ,Widget::TouchEventType type)
{
cocos2d::ui::Button* curBtn;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	curBtn = dynamic_cast<cocos2d::ui::Button*>(pSender);
	CCLog("btnChargeMoneyCallback is answer !!!");

	break;
    default:
	break;
}
}

void UI_Shop_Center_Layer::update_grid_item(int index,int icon,int name,int money_type,int cost,int discount,int last_count)
{
	int row = index/EACH_PAGE_NUM_S;
	int col = index%EACH_PAGE_NUM_S;
    const char* szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(icon);
    m_img_icon_texture[row][col]->loadTexture(szPath, UI_TEX_TYPE_PLIST);
    m_img_icon_texture[row][col]->setVisible(true);
    const char *szName = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(name);
    m_lab_icon_name[row][col]->setString(szName);
    m_lab_icon_name[row][col]->setVisible(true);

	const char* szMoney = ITEM_CONFIG_MGR::instance()->get_gold_icon();
	if (money_type == Game_Data::MT_TOKEN_MONEY)
	{
		szMoney = ITEM_CONFIG_MGR::instance()->get_token_icon();
	}
    
    if (m_cur_shop_type == Game_Data::ST_GOLD_SHOP)
    {
        m_lab_icon_number[row][col]->setVisible(false);
    }
    if (m_cur_shop_type == Game_Data::ST_TOKEN_SHOP)
    {
        m_lab_icon_number[row][col]->setVisible(false);
    }
    else if (m_cur_shop_type == Game_Data::ST_SPECIAL_SHOP)
    {
        m_lab_icon_number[row][col]->setString(CCString::createWithFormat("%d",last_count)->getCString());
        m_lab_icon_number[row][col]->setVisible(true);
    }

    m_img_original_texture[row][col]->loadTexture(szMoney, UI_TEX_TYPE_PLIST);
    m_img_original_texture[row][col]->setVisible(true);
   m_img_discount_texture[row][col]->loadTexture(szMoney, UI_TEX_TYPE_PLIST);
    

    m_lab_original_price[row][col]->setString(CCString::createWithFormat("%d",cost)->getCString());
    m_lab_original_price[row][col]->setVisible(true);
    if (discount != 10000)
    {
        cost = cost * discount / 10000;
        m_lab_discount_price[row][col]->setString(CCString::createWithFormat("%d",cost)->getCString());
        m_lab_discount_price[row][col]->setVisible(true);
        m_img_delete_line[row][col]->setVisible(true);
        m_img_discount_texture[row][col]->setVisible(true);
    }

	show_player_info(money_type);
}

void UI_Shop_Center_Layer::remove_grid_item(int index)
{
	int row = index/EACH_PAGE_NUM_S;
	int col = index%EACH_PAGE_NUM_S;
    m_img_icon_texture[row][col]->setVisible(false);
    m_lab_icon_name[row][col]->setVisible(false);

    m_lab_original_price[row][col]->setVisible(false);
    m_lab_discount_price[row][col]->setVisible(false);
    m_img_delete_line[row][col]->setVisible(false);

    m_lab_icon_number[row][col]->setVisible(false);
    m_img_original_texture[row][col]->setVisible(false);
    m_img_discount_texture[row][col]->setVisible(false);
}

void UI_Shop_Center_Layer::update()
{
    for (int i = 0; i<GRID_NUM_S; ++i)
    {
        m_goods_id[i] = 0;
        remove_grid_item(i);
    }

    int index = 0;
    Game_Data::shop_config* shop_config = NULL;
    Game_Data::Item_Config* item_config = NULL;
    Game_Data::shop_config_map& shop_config_map = SHOP_CONFIG_MGR::instance()->get_shop_config_map_by_shop_type(m_cur_shop_type);
    Game_Data::shop_config_map_iter iter = shop_config_map.begin(); 
    for (;iter != shop_config_map.end() && index < GRID_NUM_S;++iter)
    {
        shop_config = iter->second;
        if (!shop_config)
        {
            continue;
        }

        item_config = ITEM_CONFIG_MGR::instance()->get_item_config(shop_config->item_base_id_);
        if (!item_config)
        {
            continue;
        }

        int last_count = shop_config->buy_count_;
        if (shop_config->buy_count_ > 0)
        {
            Game_Data::shoping_record* record = SHOPING_RECORD_MGR::instance()->get_shoping_record(shop_config->base_id_);
            if (record)
            {
                if (shop_config->buy_count_ > record->buy_count_)
                {
                    last_count = shop_config->buy_count_ - record->buy_count_;
                } 
                else
                {
                    last_count = 0;
                }
            }
        }
        
        m_goods_id[index] = shop_config->base_id_;
        update_grid_item(index,item_config->icon,item_config->name,shop_config->money_type_,shop_config->cost_,
            shop_config->discount_,last_count);

        ++index;
    }
}

void UI_Shop_Center_Layer::show_player_info(int money_type)
{
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if (!player)
	{
		return;
	}

	const char* szMoney = ITEM_CONFIG_MGR::instance()->get_gold_icon();
	if (money_type == Game_Data::MT_TOKEN_MONEY)
	{
		szMoney = ITEM_CONFIG_MGR::instance()->get_token_icon();
	}

	if (m_cur_shop_type == Game_Data::ST_GOLD_SHOP )
	{
		m_img_player_cur_money_texture->loadTexture(szMoney, UI_TEX_TYPE_PLIST);
		int gold = player->get_gold();
// 		if (gold >= 100000)
// 		{
// 			const char* format = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90626);
// 			m_lab_player_cur_money->setString(CCString::createWithFormat(format,gold/10000)->getCString());
// 		} 
// 		else
// 		{
			m_lab_player_cur_money->setString(CCString::createWithFormat("%d",gold)->getCString());
//		}
	}

	if (m_cur_shop_type == Game_Data::ST_TOKEN_SHOP
		|| m_cur_shop_type == Game_Data::ST_SPECIAL_SHOP )
	{
		m_img_player_cur_money_texture->loadTexture(szMoney, UI_TEX_TYPE_PLIST);
		int token = player->get_token();
// 		if (token >= 100000)
// 		{
// 			const char* format = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(90626);
// 			m_lab_player_cur_money->setString(CCString::createWithFormat(format,token/10000)->getCString());
// 		} 
// 		else
// 		{
			m_lab_player_cur_money->setString(CCString::createWithFormat("%d",token)->getCString());
//		}
	}

}
