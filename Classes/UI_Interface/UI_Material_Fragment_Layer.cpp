#include "UI_Material_Fragment_Layer.h"
#include "UI_MainMenu_Layer.h"

#include "Item_System/Item_Mgr_Cl.h"
#include "Item_System/Item_Logic_Cl.h"
#include "Item_System/Item_Config_Data.h"

#include "UI_Icon_Info_Layer.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Joiner_Guidance.h"

USING_NS_CC;
//USING_NS_CC_EXT;
using namespace ui;
using namespace Game_Data;

enum Fragment_Back_Child
{
	FBC_NUM = 123456789,
	FBC_SHOW = 987654321,
};

UI_Material_Fragment_Layer::UI_Material_Fragment_Layer(void) :
	m_pImgCombineBefore(NULL),
	m_pImgCombineBeforeTexture(NULL),
	m_pImgCombineAfter(NULL),
	m_pImgCombineAfterTexture(NULL),
	m_pTeaFragmentDesc(NULL),
	m_pTeaCombineDesc(NULL),
	m_pTeaMaterialDesc(NULL),
	m_pTeaResultDesc(NULL),
	m_pLabAutoFindWayFont(NULL),
	m_pScrollView(NULL),
	m_pImgEffect(NULL),
	m_pLayerIconInfo(NULL)
{
	memset(m_fragmentBack,0,sizeof(m_fragmentBack));
	memset(m_fragmentIconBack,0,sizeof(m_fragmentIconBack));
	memset(m_iconTexture,0,sizeof(m_iconTexture));
	memset(m_labIconName,0,sizeof(m_labIconName));
	memset(m_labIconNum,0,sizeof(m_labIconNum));
	memset(m_btnCombine,0,sizeof(m_btnCombine));
	memset(m_labBtnShow,0,sizeof(m_labBtnShow));
}

UI_Material_Fragment_Layer::~UI_Material_Fragment_Layer(void)
{
}

bool UI_Material_Fragment_Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());

		 rootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Fragment_Layer/Fragment_Layer.ExportJson");
		this->addChild(rootWidget);

		cocos2d::ui::Button* btnClose = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(rootWidget,"btn_close"));
		btnClose->addTouchEventListener(this, toucheventselector(UI_Material_Fragment_Layer::buttonCloseCallback));

		initComponentOfUI();

		//创建物品信息显示框
		m_pLayerIconInfo = UI_Icon_Info_Layer::create();
		this->addChild(m_pLayerIconInfo,THISLAYERZORDERE,THISLAYERTAG);
		m_pLayerIconInfo->setVisible(false);

		bRet = true;
	} while (0);

	return bRet;
}

void UI_Material_Fragment_Layer::initComponentOfUI()
{
	m_list_fragment.clear();
	m_pImgCombineBefore = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(rootWidget,"img_combine_before_back"));
	m_pImgCombineBeforeTexture = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(rootWidget,"img_texture_before"));
	m_pImgCombineAfter = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(rootWidget,"img_combine_after_back"));
	m_pImgCombineAfterTexture = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(rootWidget,"img_texture_after"));

	m_pTeaFragmentDesc = dynamic_cast<cocos2d::ui::TextField*>(Helper::seekWidgetByName(rootWidget,"tea_fragment_desc"));
	m_pTeaCombineDesc = dynamic_cast<cocos2d::ui::TextField*>(Helper::seekWidgetByName(rootWidget,"tea_combine_desc"));
	m_pTeaMaterialDesc = dynamic_cast<cocos2d::ui::TextField*>(Helper::seekWidgetByName(rootWidget,"tea_material_out_desc"));
	m_pTeaResultDesc = dynamic_cast<cocos2d::ui::TextField*>(Helper::seekWidgetByName(rootWidget,"tea_combine_out_desc"));
	m_pTeaFragmentDesc->setText("");	
	m_pTeaCombineDesc->setText("");

	m_pLabAutoFindWayFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(rootWidget,"lab_auto_find_way_font"));
	m_pLabAutoFindWayFont->setString("");

	m_pScrollView = dynamic_cast<cocos2d::ui::ScrollView*>(Helper::seekWidgetByName(rootWidget,"ScrollView"));

	cocos2d::ui::Button* btnCombine = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(rootWidget,"btn_bag"));
	btnCombine->addTouchEventListener(this, toucheventselector(UI_Material_Fragment_Layer::btnBagCallback));

	//设置提示信息 以及提示内容
	m_pImgTipsShow = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(rootWidget,"img_tips_no_material"));
	m_pImgTipsShow->setVisible(false);
	m_pLabTipsFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pImgTipsShow,"Label"));
	const char* tipsFontInfo = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(FRAGMENT_CURRENT_NO);
	m_pLabTipsFont->setString(tipsFontInfo);

	m_pImgEffect = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(rootWidget,"img_effect"));
	m_pImgEffect->setVisible(false);

	for (int i = FRAGMENT_TYPE_COUNT-1;i >= 0;--i)
	{
		//创建背景
		m_fragmentBack[i] = cocos2d::ui::ImageView::create();
		m_fragmentBack[i]->setTouchEnabled(true);
		m_fragmentBack[i]->loadTexture("frame.png", UI_TEX_TYPE_PLIST);
		m_pScrollView->addChild(m_fragmentBack[i]);
        m_fragmentBack[i]->setScale9Enabled(true);
        m_fragmentBack[i]->setSize(Size(500,115));
		m_fragmentBack[i]->setPosition(Vec2(m_pScrollView->getContentSize().width/2,
			m_fragmentBack[i]->getContentSize().height/2 + SCROLLVIEW_HEIGHT/4*i + 15));
		m_fragmentBack[i]->addTouchEventListener(this, toucheventselector(UI_Material_Fragment_Layer::selectCurMaterial));
		m_fragmentBack[i]->setTag(0);
		m_fragmentBack[i]->setVisible(false);

		//创建图标背景框 以及 图片
		m_fragmentIconBack[i] = cocos2d::ui::ImageView::create();
		m_fragmentBack[i]->addChild(m_fragmentIconBack[i]);
		m_fragmentIconBack[i]->setPosition(Vec2(-190, 0));

		m_iconTexture[i] = cocos2d::ui::ImageView::create();
		m_fragmentIconBack[i]->addChild(m_iconTexture[i]);
		m_iconTexture[i]->setTouchEnabled(m_iconTexture[i]->isVisible());
		m_iconTexture[i]->addTouchEventListener(this, toucheventselector(UI_Material_Fragment_Layer::residualPageFindWay));

		//创建图标名称 及 数量显示
		m_labIconName[i] = cocos2d::ui::Text::create();
		m_fragmentBack[i]->addChild(m_labIconName[i]);
		m_labIconName[i]->setFontSize(25);
		m_labIconName[i]->setAnchorPoint(Vec2(0.f,0.5f));
		m_labIconName[i]->setPosition(Vec2(-110,5));

		m_labIconNum[i] = cocos2d::ui::Text::create();
		m_fragmentBack[i]->addChild(m_labIconNum[i]);
		//labIconNum[i]->setTag(FBC_NUM);
		m_labIconNum[i]->setFontSize(25);
		m_labIconNum[i]->setAnchorPoint(Vec2(0, 0.5f));
		m_labIconNum[i]->setPosition(Vec2(-110,-30));

		//创建按钮 以及 按钮显示字体
		m_btnCombine[i] = cocos2d::ui::Button::create();
		m_btnCombine[i]->setTouchEnabled(true);
		m_fragmentBack[i]->addChild(m_btnCombine[i]);
		m_btnCombine[i]->loadTextures("pic_button_1.png","pic_button_2.png","pic_button_1.png",UI_TEX_TYPE_PLIST);
		m_btnCombine[i]->setPosition(Vec2(160,-20));
		m_btnCombine[i]->addTouchEventListener(this, toucheventselector(UI_Material_Fragment_Layer::compoundMaterial));

		m_labBtnShow[i] = cocos2d::ui::Text::create();
		m_btnCombine[i]->addChild(m_labBtnShow[i]);
		m_btnCombine[i]->setTag(FBC_SHOW);
		//m_labBtnShow[i]->setFontSize(25);
	}
}

void UI_Material_Fragment_Layer::setVisible( bool visible )
{
	cocos2d::Layer::setVisible(visible);
	if (visible)
	{
		showGuide();
		update(1);
	}
	else
	{
		Joiner_Guidance::hideGuide();
		m_pLayerIconInfo->setVisible(false);
	}
}

void UI_Material_Fragment_Layer::showGuide()
{
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if(!player) 
	{
		return;
	}
	if( GUIDE_BAG_COMBINE_3 == player->get_guide_id() )
	{
		if(m_btnCombine[3])
		{
			Joiner_Guidance::receiveCurPosWidget(Vec2(
				m_btnCombine[3]->getWorldPosition().x + 40, 
				m_btnCombine[3]->getWorldPosition().y + 50));
		}
	}
}

void UI_Material_Fragment_Layer::buttonCloseCallback( Ref* pSender ,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(false);

	break;
    default:
	break;
}
}

void UI_Material_Fragment_Layer::update(int change)
{	
	if (change == 1)
	{
		change_refresh();
	} 
	else
	{
		no_change_refresh();
	}
}

void UI_Material_Fragment_Layer::change_refresh()
{

	reset_ui();
	Game_Data::Item_List material_fragment_list;
	int fragmentNum = ITEM_MGR::instance()->get_all_material_fragment(material_fragment_list);
	if(fragmentNum <= 0)
	{
		m_pImgTipsShow->setVisible(true);
	}
	else
	{
		m_pImgTipsShow->setVisible(false);
	}

	if(fragmentNum <= EACH_SCROLL_PAGE_NUM)
	{
		fragmentNum = EACH_SCROLL_PAGE_NUM;
	}

	int index = fragmentNum-1;
	m_pScrollView->setInnerContainerSize(Size(SCROLLVIEW_WIDTH, SCROLLVIEW_HEIGHT/4*fragmentNum)); 

	Game_Data::Item* item = NULL;
	Game_Data::Item_List_Iter iter = material_fragment_list.begin();
	for (;iter != material_fragment_list.end() && index>=0 ;++iter)
	{
		item = *iter;
		if (!item)
		{
			continue;
		}

		//背景
		m_fragmentBack[index]->setTag(item->config->base_id);
		m_fragmentBack[index]->setVisible(true);
		m_fragmentBack[index]->setTouchEnabled(true);

		if (index == fragmentNum-1)
		{
			materialShow(m_fragmentBack[index]->getTag());
			m_pImgEffect->setPosition(m_fragmentBack[index]->getPosition());
			m_pImgEffect->setVisible(true);
		}

		//图标背景框 以及 图片
		const char* string = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(item->config->quality);
		m_fragmentIconBack[index]->loadTexture(string,UI_TEX_TYPE_PLIST);

		string = ITEM_CONFIG_MGR::instance()->get_icon_path(item->config->icon);
        std::string p("icon/");
        p+=string;
		m_iconTexture[index]->loadTexture(p.c_str());
		m_iconTexture[index]->setTag(item->config->base_id);

		//图标名称 及 数量显示
		string = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(item->config->name);
		m_labIconName[index]->setString(string);

		int need_count = reinterpret_cast<Game_Data::Item_Fragment_Config*>(item->config)->need_count;
		m_labIconNum[index]->setString(CCString::createWithFormat("(%d/%d)",item->count,need_count)->getCString());

		//按钮 以及 按钮显示字体
		m_btnCombine[index]->setTag(item->config->base_id);

		string = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(EXCHANGE_COUNT);
		m_labBtnShow[index]->setString(CCString::createWithFormat(string,item->count/need_count)->getCString());

		m_list_fragment.push_back(index);
		m_pScrollView->scrollToTop(0,false);
		--index;
	}
}

void UI_Material_Fragment_Layer::no_change_refresh()
{   
	const char* string = NULL;
	Game_Data::Item* item = NULL;
	cocos2d::ui::ImageView* fragmentBack = NULL;
	cocos2d::ui::Text* labIconNum = NULL;
	cocos2d::ui::Text* labBtnShow = NULL;
	list<int>::iterator iter = m_list_fragment.begin();
	for (;iter != m_list_fragment.end();++iter)
	{
		fragmentBack = m_fragmentBack[*iter];
		if (!fragmentBack)
		{
			continue;
		}

		item = ITEM_MGR::instance()->get_material_fragment(fragmentBack->getTag());
		if (!item)
		{
			continue;
		}

		int need_count = reinterpret_cast<Game_Data::Item_Fragment_Config*>(item->config)->need_count;
		labIconNum = dynamic_cast<cocos2d::ui::Text*>(fragmentBack->getChildByTag(FBC_NUM));
		if (labIconNum)
		{
			labIconNum->setString(CCString::createWithFormat("(%d/%d)",item->count,need_count)->getCString());
		}

		labBtnShow = dynamic_cast<cocos2d::ui::Text*>(fragmentBack->getChildByTag(FBC_SHOW));
		string = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(EXCHANGE_COUNT);
		if (labBtnShow)
		{
			labBtnShow->setString(CCString::createWithFormat(string,item->count/need_count)->getCString());
		}
	}
}

void UI_Material_Fragment_Layer::reset_ui()
{
	m_pImgEffect->setVisible(false);
	cocos2d::ui::ImageView* fragmentBack = NULL;
	list<int>::iterator it = m_list_fragment.begin();
	for (;it != m_list_fragment.end();++it)
	{
		fragmentBack = m_fragmentBack[*it];
		if (fragmentBack)
		{
			fragmentBack->setVisible(false);
			fragmentBack->setTouchEnabled(false);
		fragmentBack->setTag(0);
		}

	m_btnCombine[*it]->setTag(0);
	}

	m_list_fragment.clear();

	const char* string = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(Game_Data::QT_MAX);
	m_pImgCombineBefore->loadTexture(string,UI_TEX_TYPE_PLIST);
	m_pImgCombineAfter->loadTexture(string,UI_TEX_TYPE_PLIST);

	m_pImgCombineBeforeTexture->setVisible(false);
	m_pTeaFragmentDesc->setVisible(false);
	m_pTeaMaterialDesc->setVisible(false);

	m_pImgCombineAfterTexture->setVisible(false);
	m_pTeaCombineDesc->setVisible(false);
	m_pTeaResultDesc->setVisible(false);
}

void UI_Material_Fragment_Layer::materialShow(int item_base_id)
{
	m_pTeaFragmentDesc->setText("");	
	m_pTeaCombineDesc->setText("");	
	m_pTeaMaterialDesc->setText("");	
	m_pTeaResultDesc->setText("");

	Game_Data::Item_Fragment_Config* fragment_config = ITEM_CONFIG_MGR::instance()->get_item_fragment_config(item_base_id);
	if (fragment_config)
	{
		const char* string = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(fragment_config->quality);
		m_pImgCombineBefore->loadTexture(string,UI_TEX_TYPE_PLIST);
		string = ITEM_CONFIG_MGR::instance()->get_icon_path(fragment_config->icon);
        std::string p("icon/");
        p+=string;
		m_pImgCombineBeforeTexture->loadTexture(p.c_str());
		m_pImgCombineBeforeTexture->setVisible(true);
		string = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(fragment_config->desc);
		m_pTeaFragmentDesc->setText(string);
		m_pTeaFragmentDesc->setVisible(true);

		string = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(fragment_config->drop_desc);
		m_pTeaMaterialDesc->setText(string);
		m_pTeaMaterialDesc->setVisible(true);

		Game_Data::Item_Config* material_config = ITEM_CONFIG_MGR::instance()->get_item_config(fragment_config->compound_id);
		if (material_config)
		{
			string = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(material_config->quality);
			m_pImgCombineAfter->loadTexture(string,UI_TEX_TYPE_PLIST);
			string = ITEM_CONFIG_MGR::instance()->get_icon_path(material_config->icon);
            std::string p("icon/");
            p+=string;
			m_pImgCombineAfterTexture->loadTexture(p.c_str());
			m_pImgCombineAfterTexture->setVisible(true);
			string = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(material_config->desc);
			m_pTeaCombineDesc->setText(string);
			m_pTeaCombineDesc->setVisible(true);

			string = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(material_config->drop_desc);
			m_pTeaResultDesc->setText(string);
			m_pTeaResultDesc->setVisible(true);
		}
	}
}

void UI_Material_Fragment_Layer::btnBagCallback( Ref* pSender ,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(false);
	UI_MainMenu_Layer::get_instance()->buttonBagInfo(NULL,Widget::TouchEventType::ENDED);

	break;
    default:
	break;
}
}

void UI_Material_Fragment_Layer::selectCurMaterial( Ref* pSender ,Widget::TouchEventType type)
{
cocos2d::ui::ImageView* curImgBack ;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	curImgBack = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
	if (curImgBack)
	{
		if (curImgBack->getTag() == 0)
		{
			return;
		}

		materialShow(curImgBack->getTag());
		m_pImgEffect->setPosition(curImgBack->getPosition());
		m_pImgEffect->setVisible(true);        
	}

	break;
    default:
	break;
}
}

void UI_Material_Fragment_Layer::compoundMaterial( Ref* pSender,Widget::TouchEventType type )
{
cocos2d::ui::Button* curImgBack;
int role_id;
Player* player ;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	curImgBack = dynamic_cast<cocos2d::ui::Button*>(pSender);
	if (curImgBack)
	{
		if (curImgBack->getTag() == 0)
		{
			return;
		}

		ITEM_LOGIC::instance()->compound_material_fragment(curImgBack->getTag(),1);

		role_id = Account_Data_Mgr::instance()->get_current_role_id();
		player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
		if(!player) 
		{
			return;
		}
		if( GUIDE_BAG_COMBINE_3 == player->get_guide_id() )
		{
			player->change_guide_id(player->get_guide_id()+2);
			Joiner_Guidance::showGuide();
		}
	}

	break;
    default:
	break;
}
}

void UI_Material_Fragment_Layer::residualPageFindWay( Ref* pSender ,Widget::TouchEventType type)
{
cocos2d::ui::ImageView* curImg ;
Game_Data::Item_Config* config = NULL;
int item_base_id;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	curImg = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
	item_base_id = curImg->getTag();

	
	config = ITEM_CONFIG_MGR::instance()->get_item_config(item_base_id);

	m_pLayerIconInfo->setVisible(true);
	m_pLayerIconInfo->showButton(config->base_id,config->icon,config->name,1,config->quality,TIPS_STYLE_FINDWAY);

	break;
    default:
	break;
}
}
