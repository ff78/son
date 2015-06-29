#include "UI_Icon_Info_Layer.h"

#include "Item_System/Item_Config_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Item_Container_System/Item_Container_Data.h"
#include "Item_Container_System/Item_Container_Mgr_Cl.h"
#include "Item_System/Item_Logic_Cl.h"
#include "Item_System/Item_Mgr_Cl.h"

#include "Character_System/Character.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Game_Interface/game_event_response.h"

#include "Common/GameDefine.h"
#include "Joiner_Guidance.h"
#include "UI_MainMenu_Layer.h"
#include "UI_Trade_Layer.h"

using namespace Game_Data;
using namespace ui;
#define ICON_INFO_FRAME_ZORDER 9999

UI_Icon_Info_Layer::UI_Icon_Info_Layer(void):
	m_pImgRootBack(NULL),
    m_pLabIconName(NULL),
    m_pLabIconLevel(NULL),
    m_pTeaForDesc(NULL),
    m_pBtnLeft(NULL),
    m_pBtnLeftFont(NULL),
    m_pBtnRight(NULL),
    m_pBtnRightFont(NULL),
	m_img_first_line(NULL),
	m_img_second_line(NULL),
	m_img_third_line(NULL)
{
    memset(m_pLabAttrArr, 0, sizeof(m_pLabAttrArr));
    memset(m_param,0,sizeof(m_param));
    memset(m_gem_id,0,sizeof(m_gem_id));
	memset(m_pLabGemAttr, 0, sizeof(m_pLabGemAttr));
}


UI_Icon_Info_Layer::~UI_Icon_Info_Layer(void)
{
}

bool UI_Icon_Info_Layer::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(!cocos2d::Layer::init());

        pWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Pop_Frame/Pop_Frame.ExportJson");
        addChild(pWidget);
		pWidget->setVisible(false);
        //关闭
        m_pBtnClose = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(pWidget,"btn_tips_close"));
        m_pBtnClose->addTouchEventListener(this, toucheventselector(UI_Icon_Info_Layer::btnCloseCallback));

        initChangePart();

        bRet = true;

    } while (0);

    return bRet;
}

void UI_Icon_Info_Layer::setVisible(bool visible)
{
    cocos2d::Layer::setVisible(visible);
    if (!visible)
    {
        memset(m_param,0,sizeof(m_param));
        memset(m_gem_id,0,sizeof(m_gem_id));
    }
}

void UI_Icon_Info_Layer::initChangePart()
{
	m_pImgRootBack = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(pWidget,"img_root_back"));

    //icon 名称
    m_pLabIconName = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(pWidget,"lab_icon_name"));
    m_pLabIconName->setVisible(false);

    //icon 等级
    m_pLabIconLevel = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(pWidget,"lab_icon_level"));
    m_pLabIconLevel->setVisible(false);

    //icon 描述
    m_pTeaForDesc = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(pWidget,"tea_for_desc"));
    m_pTeaForDesc->setVisible(false);

    //icon 属性
    char szName[64] = {0};
    for(int i=0; i<TOTAL_ATTR_NUM; ++i)
    {
        memset(szName, 0, sizeof(szName));
        sprintf(szName, "lab_attr_%d", i);
        m_pLabAttrArr[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(pWidget,szName));
    }

	//inlay info
	for(int i=0; i<GEM_INLAY_NUM; ++i)
	{
		memset(szName, 0, sizeof(szName));
		sprintf(szName, "lab_gem_inlay_%d", i);
		m_pLabGemAttr[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(pWidget,szName));
	}

    //icon 左侧按钮
    m_pBtnLeft = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(pWidget,"btn_left"));
    m_pBtnLeft->setVisible(false);
    //icon 左侧按钮  字体
    m_pBtnLeftFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(pWidget,"lab_left_font"));

    //icon 右侧按钮
    m_pBtnRight = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(pWidget,"btn_right"));
    m_pBtnRight->setVisible(false);
    //icon 右侧按钮  字体
    m_pBtnRightFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(pWidget,"lab_right_font"));

	m_img_first_line = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(pWidget,"img_first_line"));
	m_img_second_line = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(pWidget,"img_second_line"));
	m_img_third_line = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(pWidget,"img_third_line"));
}

void UI_Icon_Info_Layer::btnCloseCallback( Ref* pSender ,Widget::TouchEventType type)
{

	int player_id ;
	Game_Data::Player* player;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    setVisible(false);

    player_id = Account_Data_Mgr::instance()->get_current_role_id();
    player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if( BAG_GUIDE_MID_3 == player->get_guide_id() )
    {
        player->change_guide_id(BAG_GUIDE_MID_2);
        Joiner_Guidance::showGuide();
    }
    else if( XF_GUIDE_MID_3 == player->get_guide_id() )
    {
        player->change_guide_id(XF_GUIDE_MID_2);
        Joiner_Guidance::showGuide();
    }
	break;
    default:
	break;
}

}


void UI_Icon_Info_Layer::showButton(int item_base_id, int icon, int name, int level, int current_quality, int style)
{
    resetUI();

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));

	if( style & FRAME_STYLE_INLAY )
	{
		showLayoutSecond();

        const char* string = NULL;
        Game_Data::Gem_Config* gem_config = NULL;
        for (int i = 0;i < SET_GEM_COUNT;++i)
        {
            gem_config = ITEM_CONFIG_MGR::instance()->get_gem_config(m_gem_id[i]);
            if (gem_config)
            {
                const char* attr_type = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(gem_config->attr_type);
                string = CCString::createWithFormat("%s+%d",attr_type,gem_config->attr_value)->getCString();
                m_pLabGemAttr[i]->setColor(ccc3(255, 165, 0));
            }
            else
            {
                string = DICTIONARY_CONFIG_MGR::instance()->get_gem_inlay_string(current_quality,i);
                m_pLabGemAttr[i]->setColor(ccc3(128, 128, 128));
            }

            m_pLabGemAttr[i]->setString(string);
        }
	}
	else 
	{
		showLayoutFirst();
	}

    if(style & TIPS_STYLE_OK)
    {
        const char* okButtonFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SURE_EXIT);
        m_pBtnRightFont->setString(okButtonFont);
        m_pBtnRight->setVisible(true);
		m_pBtnRight->setTouchEnabled(true);
        m_pBtnRight->addTouchEventListener(this,toucheventselector(UI_Icon_Info_Layer::btnCloseCallback));
    }
    if(style & TIPS_STYLE_EQUIP_EQUIPMENT)
    {
        const char* equipButtonFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_EQUIP);
        m_pBtnLeftFont->setString(equipButtonFont);
        m_pBtnLeft->setVisible(true);
		m_pBtnLeft->setTouchEnabled(true);
        m_pBtnLeft->addTouchEventListener(this, toucheventselector(UI_Icon_Info_Layer::btnEquipCallback));
    }
    if(style & TIPS_STYLE_SELL)
    {
        const char* sellButtonFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_SELL);
        m_pBtnRightFont->setString(sellButtonFont);
        m_pBtnRight->setVisible(true);
		m_pBtnRight->setTouchEnabled(true);
        m_pBtnRight->addTouchEventListener(this,toucheventselector(UI_Icon_Info_Layer::btnSellCallback));
    }
    if(style & TIPS_STYLE_TAKE_OFF_EQUIPMENT)
    {
        const char* takeoffButtonFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_TAKE_OFF);
        m_pBtnLeftFont->setString(takeoffButtonFont);
        m_pBtnLeft->setVisible(true);
		m_pBtnLeft->setTouchEnabled(true);
        m_pBtnLeft->addTouchEventListener(this, toucheventselector(UI_Icon_Info_Layer::btnTakeoffCallback));
    }
    if(style & TIPS_STYLE_FINDWAY)  //寻路 待加字典
    {
        const char* aStarButtonFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_ASTART);
        m_pBtnRightFont->setString(aStarButtonFont);
        m_pBtnRight->setVisible(true);
		m_pBtnRight->setTouchEnabled(true);
      m_pBtnRight->setTag(item_base_id);
        m_pBtnRight->addTouchEventListener(this, toucheventselector(UI_Icon_Info_Layer::btnAStarCallback));
    }
    if(style & TIPS_STYLE_LEVEL)
    {
        //图标等级
        m_pLabIconLevel->setString(CCString::createWithFormat("Lv.%d",level)->getCString());
        m_pLabIconLevel->setVisible(true);
    }
    if(style & TIPS_STYLE_EQUIPMENT_ATTR)
    {
        int index = 0;
        for (int i=Game_Data::EAT_HEALTH; i<MAX_ATTR_COUNT && index<2; ++i)
        {
            int curr_attr = ITEM_CONFIG_MGR::instance()->get_equipment_attr(item_base_id,level,current_quality,i); 
            if(curr_attr>0)
            {
                const char* attr_desc = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(i);
                m_pLabAttrArr[index]->setString(CCString::createWithFormat("%s:%d",attr_desc,curr_attr)->getCString());
                m_pLabAttrArr[index]->setVisible(true);
                ++index;
            }
        }
    }

    if(style & TIPS_STYLE_BOOK_ATTR)
    {
        int index = 0;
        for(int attrindex=0;attrindex<MAX_ATTR_COUNT;++attrindex)
        {
            const char* attr_desc = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(attrindex);
            int number = ITEM_CONFIG_MGR::instance()->get_book_attr(item_base_id,level,current_quality,attrindex);
            if(number != 0)
            {
                if(index<UI_HEARTMETHOD_LAYER_EQUIP_INFO)
                {
                    m_pLabAttrArr[index]->setString(CCString::createWithFormat("%s:%d",attr_desc,number)->getCString());
                    m_pLabAttrArr[index]->setVisible(true);
                    ++index;
                }
            }
        }
    }

    if(style & TIPS_STYLE_GEM_ATTR)
    {
        Game_Data::Gem_Config* config = ITEM_CONFIG_MGR::instance()->get_gem_config(item_base_id);
        if (config)
        {
            const char* attr_type = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(config->attr_type);
            m_pLabAttrArr[0]->setString(CCString::createWithFormat("%s+%d",attr_type,config->attr_value)->getCString());
            m_pLabAttrArr[0]->setVisible(true);
        }
    }

    if(style & TIPS_STYLE_EQIP_BOOK)
    {
        const char* equipButtonFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_EQUIP);
        m_pBtnLeftFont->setString(equipButtonFont);
        m_pBtnLeft->setVisible(true);
		m_pBtnLeft->setTouchEnabled(true);
        m_pBtnLeft->addTouchEventListener(this, toucheventselector(UI_Icon_Info_Layer::btnEquipBookCallback));
    }

    if (style & TIPS_STYLE_TAKE_OFF_BOOK)
    {
        const char* takeoffButtonFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_TAKE_OFF);
        m_pBtnLeftFont->setString(takeoffButtonFont);
        m_pBtnLeft->setVisible(true);
		m_pBtnLeft->setTouchEnabled(true);
        m_pBtnLeft->addTouchEventListener(this, toucheventselector(UI_Icon_Info_Layer::btnTakeoffBookCallback));
    }

    if (style & TIPS_STYLE_USE)
    {
        const char* sellButtonFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_USE);
        m_pBtnRightFont->setString(sellButtonFont);
        m_pBtnRight->setVisible(true);
		m_pBtnRight->setTouchEnabled(true);
        m_pBtnRight->addTouchEventListener(this,toucheventselector(UI_Icon_Info_Layer::btnUseCallback));
    }

    if (style & TIPS_STYLE_SET_ON_GEM)
    {
        const char* sellButtonFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(GEM_INLAY_FONT);
        m_pBtnRightFont->setString(sellButtonFont);
        m_pBtnRight->setVisible(true);
		m_pBtnRight->setTouchEnabled(true);
        m_pBtnRight->addTouchEventListener(this,toucheventselector(UI_Icon_Info_Layer::btnGemSetOnCallback));
    }

    if (style & TIPS_STYLE_SET_OFF_GEM)
    {
        const char* sellButtonFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_TAKE_OFF);
        m_pBtnRightFont->setString(sellButtonFont);
        m_pBtnRight->setVisible(true);
		m_pBtnRight->setTouchEnabled(true);
        m_pBtnRight->addTouchEventListener(this,toucheventselector(UI_Icon_Info_Layer::btnGenTakeOffCallback));
    }

    if (style & TIPS_STYLE_COMBINE_GEM)
    {
        const char* sellButtonFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMOM_COMBINE);
        m_pBtnRightFont->setString(sellButtonFont);
        m_pBtnRight->setVisible(true);
		m_pBtnRight->setTouchEnabled(true);
        m_pBtnRight->addTouchEventListener(this,toucheventselector(UI_Icon_Info_Layer::btnGemCombineCallback));
    }

    showIconInfo(item_base_id, icon, name, level, current_quality);
}

void UI_Icon_Info_Layer::showIconInfo(int item_base_id, int icon, int name, int level, int current_quality)
{
    Game_Data::Item_Config* config = ITEM_CONFIG_MGR::instance()->get_item_config(item_base_id);
    //名称显示
    const char* iconInfo = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(name);
    m_pLabIconName->setString(iconInfo);
    m_pLabIconName->setVisible(true);

    //描述显示
    iconInfo = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(config->desc);
    m_pTeaForDesc->setText(iconInfo);
    m_pTeaForDesc->setVisible(true);
}


void UI_Icon_Info_Layer::resetUI()
{
    //icon 名称
    m_pLabIconName->setVisible(false);

    //icon 等级
    m_pLabIconLevel->setVisible(false);

    //icon 描述
    m_pTeaForDesc->setVisible(false);

    //icon 属性
    for(int i=0; i<TOTAL_ATTR_NUM; ++i)
    {
        m_pLabAttrArr[i]->setVisible(false);
    }

    //icon 左侧按钮
    m_pBtnLeft->setVisible(false);
	m_pBtnLeft->setTouchEnabled(false);

    //icon 右侧按钮
    m_pBtnRight->setVisible(false);
	m_pBtnRight->setTouchEnabled(false);

    m_pBtnClose->setVisible(true);
    m_pBtnClose->setTouchEnabled(true);
}

void UI_Icon_Info_Layer::btnEquipCallback( Ref* pSender ,Widget::TouchEventType type)
{
	int player_id ;
	int role_id ;
	Game_Data::Player* player;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    ITEM_LOGIC::instance()->equip_equipment((int)m_param[0], m_param[1]);
    setVisible(false);

    player_id = Account_Data_Mgr::instance()->get_current_role_id();
    player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if( BAG_GUIDE_MID_3 == player->get_guide_id() )
    {
        player->change_guide_id(player->get_guide_id()+1);
        UI_MainMenu_Layer::get_instance()->buttonBagInfo(NULL,Widget::TouchEventType::ENDED);
    }
	break;
    default:
	break;
}

}

void UI_Icon_Info_Layer::btnEquipBookCallback(Ref* pSender,Widget::TouchEventType type)
{
	int player_id ;
	int role_id ;
	Game_Data::Player* player;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    ITEM_LOGIC::instance()->equip_book((int)m_param[0], m_param[1]);

    player_id = Account_Data_Mgr::instance()->get_current_role_id();
    player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if( XF_GUIDE_MID_3 == player->get_guide_id())
    {
        player->change_guide_id(player->get_guide_id()+2);
        UI_MainMenu_Layer::get_instance()->buttonHeartMethod(NULL,Widget::TouchEventType::ENDED);
    }

    setVisible(false);

	break;
    default:
	break;
}
}

void UI_Icon_Info_Layer::btnTakeoffBookCallback(Ref* pSender,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    ITEM_LOGIC::instance()->take_off_book((int)m_param[0], m_param[1]);
    setVisible(false);

	break;
    default:
	break;
}
}

void UI_Icon_Info_Layer::btnSellCallback( Ref* pSender,Widget::TouchEventType type )
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	Joiner_Guidance::hideGuide();
    UI_MainMenu_Layer::get_instance()->visibleTradeLayer(m_param[1], STYLE_SELL_GOODS);
    setVisible(false);

	break;
    default:
	break;
}
}

void UI_Icon_Info_Layer::btnTakeoffCallback( Ref* pSender ,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    ITEM_LOGIC::instance()->take_off_equipmen((int)m_param[0], m_param[1]);
    setVisible(false);

	break;
    default:
	break;
}
}

void UI_Icon_Info_Layer::btnUseCallback( Ref* pSender ,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    ITEM_LOGIC::instance()->use_item( m_param[1] );
    setVisible(false);

	break;
    default:
	break;
}
}

void UI_Icon_Info_Layer::btnGemSetOnCallback( Ref* pSender ,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    ITEM_LOGIC::instance()->set_on_gem((int)m_param[0], m_param[1]);
    setVisible(false);

	break;
    default:
	break;
}
}

void UI_Icon_Info_Layer::btnGenTakeOffCallback( Ref* pSender,Widget::TouchEventType type )
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    ITEM_LOGIC::instance()->set_off_gem(m_param[0], (int)m_param[1]);
    setVisible(false);

	break;
    default:
	break;
}
}

void UI_Icon_Info_Layer::btnGemCombineCallback( Ref* pSender ,Widget::TouchEventType type)
{
	int player_id ;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Logic::Game_Event_Response::instance()->on_update_operate_gem(player_id,(int)m_param[0]);
    setVisible(false);

	break;
    default:
	break;
}
}

void UI_Icon_Info_Layer::btnAStarCallback( Ref* pSender,Widget::TouchEventType type )
{
	cocos2d::ui::Button* button ;
	int item_base_id;
	 Game_Data::Item* item;
	 int quality = -1;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    button = dynamic_cast<cocos2d::ui::Button*>(pSender);
    item_base_id = button->getTag();
    quality = -1;
	Character* character ;
    if (m_param[1] == Game_Data::QMT_ROLE)
    {
        character = CHARACTER_MGR::instance()->get_character((int)m_param[0]);
        if (!character)
        {
            return;
        }

        quality = character->get_character_quality();
    }
    else if (m_param[1] == Game_Data::QMT_EQUIPMENT || m_param[1] == Game_Data::QMT_BOOK)
    {
        item = ITEM_MGR::instance()->get_item(m_param[0]);
        if (!item)
        {
            return;
        }

        quality = item->current_quality;
    }

    if (quality >= 0)
    {
        ITEM_MGR::instance()->pathfinding_quality_upgrade_need_material((int)m_param[1],quality,item_base_id);
    }

    this->getParent()->setVisible(false);

	break;
    default:
	break;
}
}

void UI_Icon_Info_Layer::set_param(std::vector<uint64>& para)
{
    for (int i = 0;i < (int)para.size() && PARAM_NUM;++i)
    {
        m_param[i] = para[i];
    }
}

void UI_Icon_Info_Layer::set_gem_id(int* gem_id)
{
    for (int i = 0;i < SET_GEM_COUNT;++i)
    {
        m_gem_id[i] = gem_id[i];
    }
}

void UI_Icon_Info_Layer::showLayoutFirst()
{
	cocos2d::Size size = Director::getInstance()->getWinSize();
m_pImgRootBack->setScale9Enabled(true);
	m_pImgRootBack->setSize(Size(270,300));
	m_pImgRootBack->setPosition(Vec2(size.width/2, size.height/2));

	m_img_first_line->setPosition(Vec2(0, -30));

	m_img_second_line->setPosition(Vec2(0, -90));

	m_img_third_line->setVisible(false);

	m_pBtnLeft->setPosition(Vec2(-75,-120));
	m_pBtnRight->setPosition(Vec2(75,-120));
}

void UI_Icon_Info_Layer::showLayoutSecond()
{
	cocos2d::Size size = Director::getInstance()->getWinSize();
m_pImgRootBack->setScale9Enabled(true);
	m_pImgRootBack->setSize(Size(270,450));
	m_pImgRootBack->setPosition(Vec2(size.width/2, size.height/2));

	
	m_img_first_line->setPosition(Vec2(0, 40));

	m_img_second_line->setPosition(Vec2(0, -20));

	m_img_third_line->setVisible(true);
	m_img_third_line->setPosition(Vec2(0, -170));

	m_pBtnLeft->setPosition(Vec2(-75,-195));
	m_pBtnRight->setPosition(Vec2(75,-195));
}
