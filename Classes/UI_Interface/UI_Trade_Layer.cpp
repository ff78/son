#include "UI_Trade_Layer.h"

#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Item_System/Item_Config_Mgr.h"
#include "Item_System/Item_Logic_Cl.h"
#include "Shop_System/Shop_Config_Mgr.h"
#include "Item_System/Item_Mgr_Cl.h"
#include "Item_Container_System/Item_Container_Mgr_Cl.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Character.h"
#include "Character_System/Player.h"
#include "Character_System/Player_Logic_Cl.h"

#include "UI_MainMenu_Layer.h"
#include "Common/Utils.h"
using namespace Game_Data;
using namespace ui;
UI_Trade_Layer* UI_Trade_Layer::instance = 0;
UI_Trade_Layer::UI_Trade_Layer(void) : 
	m_para(0),
    m_trade_count(1)
{
}


UI_Trade_Layer::~UI_Trade_Layer(void)
{
}

bool UI_Trade_Layer::init()
{
	bool bRet = false;

	do 
	{
		CC_BREAK_IF( !cocos2d::Layer::init() );

		m_wid_root = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Buy_Layer/Buy_Layer.ExportJson");
		this->addChild(m_wid_root);
		m_wid_root->setZOrder(INT_MAX);

		initComponent();

		bRet = true;
	} while (0);

	return bRet;
}

void UI_Trade_Layer::setVisible( bool visible )
{
	cocos2d::Layer::setVisible(visible);
    if (visible)
    {
		
    }
    else
    {
        m_para = 0;
        m_trade_count = 1;
    }
}

void UI_Trade_Layer::set_style_show_info( uint64 goods_id, int style )
{
	set_goods_id(goods_id);

	if( style & STYLE_SELL_GOODS )
	{
		showSellGoodsInfo();
	}

	if ( style & STYLE_BUY_GOODS )
	{
		showBuyGoodsInfo();
	}
	
	if ( style & STYLE_BUY_ATTR_GOODS )
	{
		showBuyAttrGoodsInfo();
	}
	
	setVisible(true);
}

void UI_Trade_Layer::removeFrame()
{
	if (instance && instance->getParent())
	{
		instance->removeFromParent();
	}
}

void UI_Trade_Layer::initComponent()
{
	m_img_root = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_wid_root,"img_root_back"));
m_img_root->setScale9Enabled(true);

	m_lab_title = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_wid_root,"lab_title"));
	m_lab_title->setString("");
	m_img_line_first = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_wid_root,"img_line_first"));

	m_tea_icon_info = dynamic_cast<cocos2d::ui::TextField*>(Helper::seekWidgetByName(m_wid_root,"tea_icon_info"));
m_tea_icon_info->setText("");
	m_img_line_second = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_wid_root,"img_line_second"));

	char key[32] = {0};
	for (int i = 0; i < ATTR_SUM_NUM; i++)
	{
		memset(key, 0, sizeof(key));
		sprintf(key, "lab_attr_add_%d", i);
		m_lab_attr_add[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_wid_root,key));
		m_lab_attr_add[i]->setString("");
	}
	m_img_line_third = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_wid_root,"img_line_third"));
	
	m_lab_gain_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_wid_root,"lab_gain_font"));
	//显示购买的数量
	m_lab_trade_goods_num = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_wid_root,"lab_sell_goods_num"));
	//显示购买所需总的费用
	m_lab_gain_sum_money = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_wid_root,"lab_sell_sum_num"));
	m_lab_btn_buy_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_wid_root,"lab_sell_font"));
	m_lab_btn_cancel_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_wid_root,"lab_cancel_font"));
    m_img_money = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_wid_root,"img_gold_pic"));

	m_btn_minus = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_wid_root,"btn_minus"));

	m_btn_add = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_wid_root,"btn_plus"));
	m_btn_buy = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_wid_root,"btn_sell"));

	m_btn_cancel = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_wid_root,"btn_cancel"));
	m_btn_cancel->addTouchEventListener(this, toucheventselector(UI_Trade_Layer::buttonCancelCallback));
	m_img_line_fourth = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_wid_root,"img_line_fourth"));
}

void UI_Trade_Layer::buttonSellMinusCallback( Ref* pSender ,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    if (m_trade_count <= 1)
    {
        return;
    }

    --m_trade_count;
    updateSellGoodsInfo();

	break;
    default:
	break;
}
}

void UI_Trade_Layer::buttonBuyMinusCallback( Ref* pSender,Widget::TouchEventType type )
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	if (m_trade_count <= 1)
	{
		return;
	}

	--m_trade_count;
	updateBuyAttrGoodsInfo();

	break;
    default:
	break;
}
}

void UI_Trade_Layer::buttonBuyAddCallback( Ref* pSender ,Widget::TouchEventType type)
{
int player_id;
Game_Data::Player* player ;
Game_Data::shop_config* shop_config;
Game_Data::shoping_record* record;
 int cost ;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    player_id = Account_Data_Mgr::instance()->get_current_role_id();
    player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return;
    }

    shop_config = SHOP_CONFIG_MGR::instance()->get_shop_config((int)m_para);
    if (!shop_config)
    {
        return;
    }

    if (shop_config->buy_count_ > 0)
    {
        record = player->get_shoping_record(shop_config->base_id_);
        if (record && (record->buy_count_ + (m_trade_count + 1)) > shop_config->buy_count_)
        {
            return;
        }
    }

    if ((m_trade_count + 1) > 99)
    {
        return;
    }

    cost = shop_config->cost_ * shop_config->discount_ / 10000 * (m_trade_count + 1);
    if (shop_config->money_type_ == Game_Data::MT_GOLD_MONEY)
    {
        if (player->get_gold() < cost)
        {
            return;
        }
    }
    else
    {
        if (player->get_token() < cost)
        {   
            return;
        }
    }
    
    if (PLAYER_LOGIC::instance()->check_bag_room(player_id,shop_config->item_base_id_,(m_trade_count + 1)) == false)
    {
        return;
    } 

    ++m_trade_count;
    updateBuyAttrGoodsInfo();

	break;
    default:
	break;
}
}

void UI_Trade_Layer::buttonBuyCallback( Ref* pSender ,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    ITEM_LOGIC::instance()->buy_item((int)m_para,m_trade_count);
    setVisible(false);

	break;
    default:
	break;
}
}

void UI_Trade_Layer::buttonCancelCallback( Ref* pSender ,Widget::TouchEventType type)
{
	setVisible(false);
}

void UI_Trade_Layer::setComponentVisible(bool visible)
{
	m_img_line_first->setVisible(visible);
	m_img_line_second->setVisible(visible);
	m_img_line_third->setVisible(visible);
	m_img_line_fourth->setVisible(visible);
}

void UI_Trade_Layer::updateBuyAttrGoodsInfo()
{
    m_lab_trade_goods_num->setString(CCString::createWithFormat("%d",m_trade_count)->getCString());

    shop_config* shop_config = SHOP_CONFIG_MGR::instance()->get_shop_config((int)m_para);
    if (!shop_config)
    {
        return;
    }

    const char* szMoney = ITEM_CONFIG_MGR::instance()->get_gold_icon();
    if (shop_config->money_type_ == Game_Data::MT_TOKEN_MONEY)
    {
        szMoney = ITEM_CONFIG_MGR::instance()->get_token_icon();
    }
    m_img_money->loadTexture(szMoney, UI_TEX_TYPE_PLIST);

    int cost = shop_config->cost_ * shop_config->discount_ / 10000 * m_trade_count;
    m_lab_gain_sum_money->setString(CCString::createWithFormat("%d",cost)->getCString());
}

void UI_Trade_Layer::showAttrGoodsIconInfo()
{
	Game_Data::shop_config* shop_config = SHOP_CONFIG_MGR::instance()->get_shop_config((int)m_para);
	if (!shop_config)
	{
		return;
	}

	Game_Data::Item_Config* item_confit = ITEM_CONFIG_MGR::instance()->get_item_config(shop_config->item_base_id_);
	if ( !item_confit )
	{
		return;
	}
	
	m_lab_title->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(item_confit->name));

	if( item_confit->type == Game_Data::IT_EQUIPMENT || item_confit->type == Game_Data::IT_BOOK )
	{
		int index = 0;
		for (int i=Game_Data::EAT_HEALTH; i<MAX_ATTR_COUNT && index<ATTR_SUM_NUM; ++i)
		{
			int curr_attr = 0;
			if (item_confit->type == Game_Data::IT_EQUIPMENT)
			{
				curr_attr = ITEM_CONFIG_MGR::instance()->get_equipment_attr(item_confit->base_id,1,0,i);
			} 
			else
			{
				curr_attr = ITEM_CONFIG_MGR::instance()->get_book_attr(item_confit->base_id,1,0,i);
			}

			if(curr_attr>0)
			{
				const char* attr_desc = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(i);
				m_lab_attr_add[index]->setString(CCString::createWithFormat("%s:%d",attr_desc,curr_attr)->getCString());
				m_lab_attr_add[index]->setVisible(true);
				++index;
			}
		}
	}
	else
	{
		for (int i=0; i<ATTR_SUM_NUM; ++i)
		{
			m_lab_attr_add[i]->setVisible(false);
		}
	}

	m_tea_icon_info->setText(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(item_confit->desc));
}

void UI_Trade_Layer::showSellGoodsInfo()
{
	setComponentVisible(true);
	//m_img_root->setScale(Size(280, 210));
	m_img_line_first->setPosition(Vec2(0, 55));
	m_img_line_second->setVisible(false);
	m_img_line_third->setVisible(false);
	m_img_line_fourth->setPosition(Vec2(0, -45));

	m_lab_title->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SP_CENTER_SELL_NUM));
	m_lab_gain_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SP_CENTER_GAIN_FONT));
	m_btn_buy->addTouchEventListener(this, toucheventselector(UI_Trade_Layer::buttonSellCallback));
	m_lab_btn_buy_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_SELL));
	m_btn_add->addTouchEventListener(this, toucheventselector(UI_Trade_Layer::buttonSellAddCallback));
	m_btn_minus->addTouchEventListener(this, toucheventselector(UI_Trade_Layer::buttonSellMinusCallback));

	updateSellGoodsInfo();
}

void UI_Trade_Layer::showBuyGoodsInfo()
{
	setComponentVisible(true);
m_img_root->setSize(Size(280, 310));
	m_img_line_first->setPosition(Vec2(0, 115));
	m_img_line_second->setPosition(Vec2(0, -5));
	m_img_line_third->setVisible(false);
	m_img_line_fourth->setPosition(Vec2(0, -95));

	m_lab_title->setString("");
	m_lab_gain_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_EXPEND));
	m_btn_buy->addTouchEventListener(this, toucheventselector(UI_Trade_Layer::buttonBuyCallback));
	m_lab_btn_buy_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_PURCHASE));
	m_btn_add->addTouchEventListener(this, toucheventselector(UI_Trade_Layer::buttonBuyAddCallback));
	m_btn_minus->addTouchEventListener(this, toucheventselector(UI_Trade_Layer::buttonBuyMinusCallback));

	updateBuyAttrGoodsInfo();
	showAttrGoodsIconInfo();
}

void UI_Trade_Layer::showBuyAttrGoodsInfo()
{
	setComponentVisible(true);
m_img_root->setSize(Size(280, 380));
	m_img_line_first->setPosition(Vec2(0, 147));
	m_img_line_second->setPosition(Vec2(0, 27));
	m_img_line_third->setPosition(Vec2(0, -40));
	m_img_line_fourth->setPosition(Vec2(0, -130));

	//m_lab_title->setString("");
	m_lab_gain_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_EXPEND));
	m_btn_buy->addTouchEventListener(this, toucheventselector(UI_Trade_Layer::buttonBuyCallback));
	m_lab_btn_buy_font->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_PURCHASE));
	m_btn_add->addTouchEventListener(this, toucheventselector(UI_Trade_Layer::buttonBuyAddCallback));
	m_btn_minus->addTouchEventListener(this, toucheventselector(UI_Trade_Layer::buttonBuyMinusCallback));

	updateBuyAttrGoodsInfo();
	showAttrGoodsIconInfo();
}

void UI_Trade_Layer::buttonSellAddCallback( Ref* pSender ,Widget::TouchEventType type)
{
Item_Container* container ;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	container = ITEM_CONTAINER_MGR::instance()->get_item_container(m_para);
	if (!container)
	{
		return;
	}

	if (container->is_num_type == 0)
	{
		return;
	} 

	if (m_trade_count >= container->item_count)
	{
		return;
	}

	++m_trade_count;
	updateSellGoodsInfo();

	break;
    default:
	break;
}
}

void UI_Trade_Layer::buttonSellCallback( Ref* pSender ,Widget::TouchEventType type)
{ 
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	ITEM_LOGIC::instance()->sell_item(m_para, m_trade_count);
	setVisible(false);

	break;
    default:
	break;
}
}

void UI_Trade_Layer::updateSellGoodsInfo()
{
	m_lab_trade_goods_num->setString(CCString::createWithFormat("%d",m_trade_count)->getCString());

	const char* szMoney = ITEM_CONFIG_MGR::instance()->get_gold_icon();
	m_img_money->loadTexture(szMoney, UI_TEX_TYPE_PLIST);

	Item_Container* container = ITEM_CONTAINER_MGR::instance()->get_item_container(m_para);
	if (!container)
	{
		return;
	}

	int level = 1;
	Item* item = NULL;
	Item_Config* config = NULL; 
	if (container->is_num_type == 0)
	{
		item = ITEM_MGR::instance()->get_item(container->item_id);
		if (item)
		{
			level = item->level;
			config = item->config;
		}
	} 
	else
	{
		config = ITEM_CONFIG_MGR::instance()->get_item_config((int)container->item_id);
	}

	if (config == NULL || config->can_sell == 0)
	{
		return;
	}

	int income = ITEM_CONFIG_MGR::instance()->get_item_sell_income(config->base_id, level, m_trade_count);
	m_lab_gain_sum_money->setString(CCString::createWithFormat("%d", income)->getCString());
}
