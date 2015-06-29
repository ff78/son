#include "UI_HeartMethod_Layer.h"

#include "Item_System/Item_Data.h"
#include "Item_System/Item_Logic_Cl.h"
#include "Item_System/Item_Mgr_Cl.h"
#include "Item_Container_System/Item_Container_Mgr_Cl.h"
#include "Item_Container_System/Item_Container_Msg_Proc_Cl.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player_Config_Mgr.h"

//#include "cocos-ext.h"
#include "UI/Actor_Layer.h"
//#include "Game_Scene.h"
#include "UI_ModalDialogue_Layer.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "UI_MainMenu_Layer.h"
#include "Common/GameMacro.h"

#include "UI_Icon_Info_Layer.h"
#include "Joiner_Guidance.h"
#include "Function_Open_System/Function_Open_Config_Data.h"
using namespace ui;
USING_NS_CC;
//USING_NS_CC_EXT;
using namespace Game_Data;

UI_HeartMethod_Layer::UI_HeartMethod_Layer(void):
	m_pMethodWidget(NULL),
	m_img_equipment_select_effect(NULL),
	m_lab_role_name(NULL),
	m_img_icon_dlg(NULL),
    m_img_head_effect(NULL),
	m_img_fighting_mark(NULL),
	m_fighting_capacity(NULL),
	m_pGoodsLayer(NULL)
{
	memset(m_img_equipment_bar, 0, sizeof(m_img_equipment_bar));
	memset(m_img_equipment_bar_back, 0, sizeof(m_img_equipment_bar_back));

	memset(m_bag_container_id, 0, sizeof(m_bag_container_id));
	memset(m_bar_item_id, 0, sizeof(m_bar_item_id));
    m_select_character_id = 0;
    m_quest_item_base_id = 0;

	memset(m_img_click_head_event, 0, sizeof(m_img_click_head_event));
	memset(m_img_head_photo, 0, sizeof(m_img_head_photo));
	m_fighting_capacity = LabelAtlas::create("0123456789","pic_zhanlizhi_shuzi.png",22,33,'0');
	m_fighting_capacity->setVisible(true);
}


UI_HeartMethod_Layer::~UI_HeartMethod_Layer(void)
{
}

bool UI_HeartMethod_Layer::init()
{
	if ( !cocos2d::Layer::init() )
	{
		return false;
	}
	m_pGoodsLayer = UI_Goods_Grid_Layer::create();
	if(!m_pGoodsLayer)
	{
		return false;
	}
	this->addChild(m_pGoodsLayer);


	m_pMethodWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/XinFa_Main/XinFa_Main.ExportJson");
	addChild(m_pMethodWidget);

	cocos2d::ui::ImageView* imgScrollBack = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMethodWidget,"img_introduce"));
	cocos2d::ui::ImageView* imgBagGrid = m_pGoodsLayer->createHorizontalGrid(STYLE_NOTHING);
	imgScrollBack->addChild(imgBagGrid);

	for(int i=0; i<PAGE_SUM_NUM; ++i)
	{
		for(int j=0; j<EACH_PAGE_NUM; ++j)
		{
			m_pGoodsLayer->m_pImgTextureChild[i][j]->setTouchEnabled(true);
	m_pGoodsLayer->m_pImgTextureChild[i][j]->setTag(i*EACH_PAGE_NUM+j);
			m_pGoodsLayer->m_pImgTextureChild[i][j]->addTouchEventListener(this, toucheventselector(UI_HeartMethod_Layer::click_bag_grid));
		}
	}

	m_pBtnClose = (cocos2d::ui::Button*)Helper::seekWidgetByName(m_pMethodWidget,"btn_close");
	m_pBtnClose->addTouchEventListener(this,toucheventselector(UI_HeartMethod_Layer::buttonCloseCallback));

 	char key[32] = {0};

	for (int i = 0;i < 6;++i)
	{
		memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS

		sprintf_s(key,"img_equip_%d",i+1);
#else
		sprintf(key,"img_equip_%d",i+1);
#endif
		m_img_equipment_bar_back[i] = (cocos2d::ui::ImageView*)(Helper::seekWidgetByName(m_pMethodWidget,key));
		m_img_equipment_bar_back[i]->setTouchEnabled(false);
		m_img_equipment_bar[i] = cocos2d::ui::ImageView::create();
		m_img_equipment_bar_back[i]->getParent()->addChild(m_img_equipment_bar[i]);
		m_img_equipment_bar[i]->setZOrder(m_img_equipment_bar_back[i]->getZOrder()+1);
		m_img_equipment_bar[i]->setPosition(m_img_equipment_bar_back[i]->getPosition());
        m_img_equipment_bar[i]->setTag(i);
		m_img_equipment_bar[i]->addTouchEventListener(this,toucheventselector(UI_HeartMethod_Layer::click_equipment_bar));
		m_img_equipment_bar[i]->setTouchEnabled(true);
	}

	m_pBtnResidualPage = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(m_pMethodWidget,"btn_residual_page"));
	m_pBtnResidualPage->addTouchEventListener(this,toucheventselector(UI_HeartMethod_Layer::buttonResidualPageCallback));

	m_pBtnCombine = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(m_pMethodWidget,"btn_combine"));
	m_pBtnCombine->addTouchEventListener(this,toucheventselector(UI_HeartMethod_Layer::buttonCombineCallback));

	//心法升品按钮
	m_pBtnXinFaQualityUp = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pMethodWidget,"btn_quality_up"));
	m_pBtnXinFaQualityUp->addTouchEventListener(this,toucheventselector(UI_HeartMethod_Layer::buttonQualityUpCallback));


	//装备栏选中状态标示
	m_img_equipment_select_effect=dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMethodWidget,"m_img_equipment_select_effect"));
	m_img_equipment_select_effect->setVisible(false);

	//战力值
	cocos2d::ui::ImageView* fighting_capacity_title = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMethodWidget,"Zhanli_Title"));
	if (fighting_capacity_title)
	{
		m_fighting_capacity->setAnchorPoint(Vec2(0,0.5));
		m_fighting_capacity->setZOrder(fighting_capacity_title->getZOrder() +1 );
		fighting_capacity_title->addChild(m_fighting_capacity);
	}

	//显示角色名字m_lab_role_name
	m_lab_role_name=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMethodWidget,"lab_role_name"));
    m_img_head_effect = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMethodWidget,"img_head_click_effect"));

	//角色栏 控件获取
	for(int i=0; i<UI_HEAD_SUM_NUM; ++i)
	{
		char imgBack[32] = {0};
		sprintf(imgBack, "img_role_head_back_%d", i);
		m_img_click_head_event[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMethodWidget,imgBack));
        m_img_click_head_event[i]->setTag(0);
        m_img_click_head_event[i]->addTouchEventListener(this, toucheventselector(UI_HeartMethod_Layer::headPhotoClickEvent));

		char imgHead[32] = {0};
		sprintf(imgHead, "img_role_head_%d", i);
		m_img_head_photo[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMethodWidget,imgHead));
	}

	//获取标记
	m_img_fighting_mark = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMethodWidget,"img_fighting_mark"));

	//创建物品信息显示框 function init()
	m_pLayerIconInfo = UI_Icon_Info_Layer::create();
	this->addChild(m_pLayerIconInfo,THISLAYERZORDERE,THISLAYERTAG);
	m_pLayerIconInfo->setVisible(false);

	//设置人物头像
	update_role();
	ShowCharAvatar();

	return true;
}

void UI_HeartMethod_Layer::setVisible( bool visible )
{
	cocos2d::Layer::setVisible(visible);
    if (visible)
    {
		Joiner_Guidance::hideGuide();
		update_role();
        ShowCharAvatar();
        update();
		showGuide();
    }
    else
    {
        guideControl();
//		UI_MainMenu_Layer::get_instance()->showGuide();
    }
}

void UI_HeartMethod_Layer::showGuide()
{
	setTouchEvent(true);
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if(!player) return;

	if( GUIDE_XF_PINZHUANG_2 == player->get_guide_id() )
	{
		Joiner_Guidance::receiveCurPosWidget(m_pBtnResidualPage);
	}
	else if ( GUIDE_XF_STEP_2 == player->get_guide_id() )
	{
		Joiner_Guidance::receiveCurPosWidget(m_pGoodsLayer->m_pImgAllGrid[0][0]);
	}
	else if ( GUIDE_XF_STEP_3 == player->get_guide_id() )
	{
		Joiner_Guidance::receiveCurPosWidget(m_pLayerIconInfo->m_pBtnLeft);
	}
	else if ( GUIDE_XF_COMB_STEP_2 == player->get_guide_id() )
	{
		Joiner_Guidance::receiveCurPosWidget(m_pBtnCombine);
	}
	else if ( GUIDE_XF_QUA_UP_STEP_2 == player->get_guide_id() )
	{
		Joiner_Guidance::receiveCurPosWidget(m_pBtnXinFaQualityUp);
	}
}

void UI_HeartMethod_Layer::guideControl()
{
	m_quest_item_base_id = 0;
	UI_MainMenu_Layer::get_instance()->refreshFindWay();
	m_pLayerIconInfo->setVisible(false);

 	Joiner_Guidance::hideGuide();
}

void UI_HeartMethod_Layer::setTouchEvent(bool touchOrNot)
{
	m_pBtnClose->setTouchEnabled(touchOrNot);
	m_pBtnResidualPage->setTouchEnabled(touchOrNot);
	m_pBtnCombine->setTouchEnabled(touchOrNot);
}

void UI_HeartMethod_Layer::buttonCloseCallback( Ref* pSender ,cocos2d::ui::Widget::TouchEventType type)
{
int role_id;
Player* player;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	role_id = Account_Data_Mgr::instance()->get_current_role_id();
	player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if(!player) 
	{
			return;
	}
	if( GUIDE_XF_STEP_4 == player->get_guide_id() )
	{
		player->change_guide_id(player->get_guide_id()+1);
	}
	if( player->get_guide_id() >= GUIDE_XF_COMB_STEP_0 
		&& player->get_guide_id() < GUIDE_XF_COMB_STEP_4
		)
	{
		player->change_guide_id(GUIDE_XF_COMB_STEP_0);
	}

	setVisible(false);

	break;
    default:
	break;
}
}

//点击包裹
void UI_HeartMethod_Layer::click_bag_grid(Ref* pSender,cocos2d::ui::Widget::TouchEventType type)
{
	 uint64 container_id ;
	 int curTag;
	 int player_id;
	  Game_Data::Player* player;
if  (type==cocos2d::ui::Widget::TouchEventType::ENDED)
{

	cocos2d::ui::ImageView* imageView = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
    if (!imageView)
    {
        return;
    }

	curTag =imageView->getTag();
    player_id = Account_Data_Mgr::instance()->get_current_role_id();
    player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return;
    }

    container_id = m_bag_container_id[curTag];
    if (container_id > 0)
    {
		m_pGoodsLayer->m_pImgEffect[curTag/EACH_PAGE_NUM]->setPosition(
			m_pGoodsLayer->m_pImgAllGrid[curTag/EACH_PAGE_NUM][curTag%EACH_PAGE_NUM]->getPosition());
		m_pGoodsLayer->m_pImgEffect[curTag/EACH_PAGE_NUM]->setVisible(true);

        m_pLayerIconInfo->setVisible(true);
        refreshBagItemInfo(container_id);

        if( GUIDE_XF_STEP_2 == player->get_guide_id() )
        {
            player->change_guide_id(player->get_guide_id()+1);
            showGuide();
        }
    }
}
}

//点击装备栏
void UI_HeartMethod_Layer::click_equipment_bar(Ref* pSender,cocos2d::ui::Widget::TouchEventType type)
{
	int i;
cocos2d::ui::ImageView* imageView ;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	imageView = dynamic_cast<cocos2d::ui::ImageView*>(pSender);

	m_img_equipment_select_effect->setVisible(true);

	m_img_equipment_select_effect->setPosition(imageView->getPosition());
	i=imageView->getTag();
	refreshBarItemInfo(m_bar_item_id[imageView->getTag()]);

	break;
    default:
	break;
}
}


void UI_HeartMethod_Layer::update_grid_item(int index,int count,int quality,int icon,bool is_bag)
{
	if (is_bag)
	{
		const char* szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(icon);
		m_pGoodsLayer->m_pImgTextureChild[index/EACH_PAGE_NUM][index%EACH_PAGE_NUM]->loadTexture(szPath,UI_TEX_TYPE_PLIST);
		m_pGoodsLayer->m_pImgTextureChild[index/EACH_PAGE_NUM][index%EACH_PAGE_NUM]->setVisible(true);

		//根据品质，设置背景
		szPath = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(quality);
		m_pGoodsLayer->m_pImgAllGrid[index/EACH_PAGE_NUM][index%EACH_PAGE_NUM]->loadTexture(szPath,UI_TEX_TYPE_PLIST);
		m_pGoodsLayer->m_pImgAllGrid[index/EACH_PAGE_NUM][index%EACH_PAGE_NUM]->setVisible(true);
	} 
	else
	{
		const char* szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(icon);
		m_img_equipment_bar[index]->loadTexture(szPath,UI_TEX_TYPE_PLIST);
		m_img_equipment_bar[index]->setVisible(true);

		//根据品质，设置背景
		szPath = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(quality);
		m_img_equipment_bar_back[index]->loadTexture(szPath,UI_TEX_TYPE_PLIST);
		m_img_equipment_bar_back[index]->setVisible(true);

	}
}

void UI_HeartMethod_Layer::remove_grid_item(int index,bool is_bag)
{
	if (is_bag)
	{
		m_pGoodsLayer->m_pImgTextureChild[index/EACH_PAGE_NUM][index%EACH_PAGE_NUM]->setVisible(false);

		//还原背景
		const char* szPath = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(Game_Data::QT_MAX);
		m_pGoodsLayer->m_pImgAllGrid[index/EACH_PAGE_NUM][index%EACH_PAGE_NUM]->loadTexture(szPath,UI_TEX_TYPE_PLIST);
		m_pGoodsLayer->m_pImgAllGrid[index/EACH_PAGE_NUM][index%EACH_PAGE_NUM]->setVisible(true);

		for( int i=0; i<PAGE_SUM_NUM; ++i )
		{
			m_pGoodsLayer->m_pImgEffect[i]->setVisible(false);
		}
	} 
	else
	{
		m_img_equipment_bar[index]->setVisible(false);
		//还原装备的图片
		const char* szPath = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(Game_Data::QT_MAX);
		m_img_equipment_bar_back[index]->loadTexture(szPath,UI_TEX_TYPE_PLIST);
		m_img_equipment_bar_back[index]->setVisible(true);
	}
}

void UI_HeartMethod_Layer::update()
{
	buttonOpenOrNot();

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

    Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(m_select_character_id);
    if (!character)
    {
        return ;
    }

	int nLevel = character->get_character_level();
	cocos2d::ui::Text* ctl = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMethodWidget,"lab_level"));
	ctl->setString(CCString::createWithFormat("LV.%d",nLevel)->getCString());

	int current_exp = character->get_exp();
	int current_level_sum_exp = character->get_player_levelup_exp();

	m_fighting_capacity->setString(CCString::createWithFormat("%d",character->get_fighting_capacity())->getCString());

	const char* pname = character->get_character_name();
	m_lab_role_name->setString(pname);

    m_img_equipment_select_effect->setVisible(false);
    memset(m_bag_container_id, 0, sizeof(m_bag_container_id));
    memset(m_bar_item_id, 0, sizeof(m_bar_item_id));
    for (int i = 0; i<GRID_NUM; ++i)
    {
        remove_grid_item(i,true);
    }

    int index = 0;
    Game_Data::Item* item = NULL;
    Game_Data::Item_Container* container = NULL;
    Game_Data::Item_Container_Map& map_bag_container = player->get_bag_item_container_map();
    Game_Data::Item_Container_Map_Iter iter = map_bag_container.begin(); 
    for (;iter != map_bag_container.end() && index < GRID_NUM;++iter)
    {
        container = iter->second;
        if (!container)
        {
            continue;
        }

        if (container->item_id > 0)
        {
            
            if (container->is_num_type == 0)
            {
                item = ITEM_MGR::instance()->get_item(container->item_id);
                if (item && item->config->type == Game_Data::IT_BOOK)
                {
                    m_bag_container_id[index] = container->id;
                    update_grid_item(index,item->count,item->current_quality,item->config->icon,true);
                    ++index;
                }
            }
        }
    }

    Game_Data::Item** book_bar = character->get_book_array();
    for (int i = 0;i < Game_Data::EP_MAX;++i)
    {
        item = book_bar[i];
        if (item)
        {
            m_bar_item_id[i] = item->id;
            update_grid_item(i,item->count,item->current_quality,item->config->icon,false);
        }
        else
        {
            remove_grid_item(i,false);
        }
    }

	//副将出战标记
	m_img_fighting_mark->setVisible(false);
	for (int i=1; i<UI_HEAD_SUM_NUM-1; ++i)
	{
		if(m_img_click_head_event[i]->getTag() != 0 && m_img_click_head_event[i]->getTag() == player->get_fight_general_id() )
		{
			m_img_fighting_mark->setPosition(Vec2(m_img_click_head_event[i]->getPosition().x-m_img_click_head_event[i]->getContentSize().width/2+m_img_fighting_mark->getContentSize().width/2+12,
					m_img_click_head_event[i]->getPosition().y-m_img_click_head_event[i]->getContentSize().height/2+m_img_fighting_mark->getContentSize().height/2+15));
			m_img_fighting_mark->setVisible(true);
		}
	}
}

void UI_HeartMethod_Layer::ShowCharAvatar()
{
#if 0
    cocos2d::ui::ImageView* pView = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMethodWidget,"img_lieutenant"));
    if(pView)
    {
        cocos2d::ui::Widget* pNode = Game_Utils::instance()->ShowCharAvatar(m_select_character_id);
        if (pNode)
        {   
            cocos2d::ui::Widget* pLastNode = (cocos2d::ui::Widget*)pView->getChildByTag(10001);
            if(pLastNode)
            {
                pView->removeChild(pLastNode, true);
            }

          pNode->setTag(10001);
            pView->addChild(pNode);
        }
    }
#endif
}

void UI_HeartMethod_Layer::buttonResidualPageCallback( Ref* pSender,cocos2d::ui::Widget::TouchEventType type )
{
	int role_id;
	Player* player;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	role_id = Account_Data_Mgr::instance()->get_current_role_id();
	player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if(!player) 
	{
		return;
	}
	if( GUIDE_XF_PINZHUANG_2 == player->get_guide_id() )
	{
		player->change_guide_id(player->get_guide_id()+1);
	}

	setVisible(false);
	UI_MainMenu_Layer::get_instance()->visibleResidualPage();

	break;
    default:
	break;
}
}

void UI_HeartMethod_Layer::buttonCombineCallback( Ref* pSender ,cocos2d::ui::Widget::TouchEventType type)
{

	int role_id ;
	Game_Data::Player* player;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	role_id = Account_Data_Mgr::instance()->get_current_role_id();
	player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if(!player) return;
	if( GUIDE_XF_COMB_STEP_2 == player->get_guide_id() )
	{
		player->change_guide_id(player->get_guide_id()+1);
		Joiner_Guidance::showGuide();
	}
	setVisible(false);
	UI_MainMenu_Layer::get_instance()->visibleHeartMethodCombine(m_select_character_id);

	break;
    default:
	break;
}
}
//关闭显示装备信息的对话框
void UI_HeartMethod_Layer::btnCallBack_Close_Icon_Info(Ref* pSender,cocos2d::ui::Widget::TouchEventType type)
{

}

void UI_HeartMethod_Layer::refreshBagItemInfo(uint64 container_id)
{
    Game_Data::Item_Container* container = ITEM_CONTAINER_MGR::instance()->get_item_container(container_id);
    if (container)
    {
        if (container->item_id > 0)
        {
            std::vector<uint64> para;
            para.push_back(m_select_character_id);
            para.push_back(container_id);
            m_pLayerIconInfo->set_param(para);
            if (container->is_num_type == 0)
            {
                Game_Data::Item* item = ITEM_MGR::instance()->get_item(container->item_id);
				#if 0
                if (item && UI_MainMenu_Layer::get_instance()->arr[Game_Data::ICON_XINFA_EQUIP_BTN])
                {
                    m_pLayerIconInfo->showButton(item->config->base_id,item->config->icon,item->config->name,item->level,item->current_quality,
                        TIPS_STYLE_EQIP_BOOK | TIPS_STYLE_LEVEL | TIPS_STYLE_BOOK_ATTR);
					m_pLayerIconInfo->setVisible(true);
                }
				else if(item)
				{
					m_pLayerIconInfo->showButton(item->config->base_id,item->config->icon,item->config->name,item->level,item->current_quality,
						TIPS_STYLE_LEVEL | TIPS_STYLE_BOOK_ATTR);
					m_pLayerIconInfo->setVisible(true);
				}
				#endif
            } 
            else
            {
                Game_Data::Item_Config* config = ITEM_CONFIG_MGR::instance()->get_item_config((int)container->item_id);
                if (config)
                {
					m_pLayerIconInfo->showButton(config->base_id, config->icon, config->name, 1, config->quality,TIPS_STYLE_OK);
					m_pLayerIconInfo->setVisible(true);
                }
            }
        }
    }
}

void UI_HeartMethod_Layer::refreshBarItemInfo(uint64 item_id)
{
    Game_Data::Item* item = ITEM_MGR::instance()->get_item(item_id);
    if (item)
    {   
        if (item)
        {
            std::vector<uint64> para;
            para.push_back(m_select_character_id);
            para.push_back(item_id);
            m_pLayerIconInfo->set_param(para);

            m_pLayerIconInfo->showButton(item->config->base_id,item->config->icon,item->config->name,item->level,item->current_quality,
                TIPS_STYLE_TAKE_OFF_BOOK | TIPS_STYLE_LEVEL | TIPS_STYLE_BOOK_ATTR);
            m_pLayerIconInfo->setVisible(true);
        }
    }
}

void UI_HeartMethod_Layer::buttonQualityUpCallback( Ref* pSender ,cocos2d::ui::Widget::TouchEventType type)
{
int role_id;
Player* player;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    role_id = Account_Data_Mgr::instance()->get_current_role_id();
	player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if(!player) return;
	if( GUIDE_XF_QUA_UP_STEP_2 == player->get_guide_id() )
	{
		player->change_guide_id(player->get_guide_id()+1);
		Joiner_Guidance::showGuide();
	}

	UI_MainMenu_Layer::get_instance()->visibleHeartMethodQualityUp(-1);
	setVisible(false);
	break;
    default:
	break;
}

}

void UI_HeartMethod_Layer::update_role()
{
    //设置 主角头像
    int role_id = Account_Data_Mgr::instance()->get_current_role_id();
    Player* player = (Player*)CHARACTER_MGR::instance()->get_character( role_id );
    if (!player)
    {
        return;
    }

    m_img_head_effect->setPosition(m_img_click_head_event[0]->getPosition());
    m_select_character_id = role_id;

    const char* picRoleHead = ITEM_CONFIG_MGR::instance()->get_icon_path(player->get_face_mode_id());
    m_img_head_photo[0]->loadTexture(picRoleHead, UI_TEX_TYPE_PLIST);
    m_img_head_photo[0]->setVisible(true);

    const char* quality_back = DICTIONARY_CONFIG_MGR::instance()->get_charactor_quality_circle_icon(player->get_character_quality());
    m_img_click_head_event[0]->loadTexture(quality_back, UI_TEX_TYPE_PLIST);
  m_img_click_head_event[0]->setTag(role_id);

    //设置 副将头像
    for (int i = 1; i < UI_HEAD_SUM_NUM; ++i)
    {
        DeputyGeneral* general = player->get_deputy_general_by_index(i-1);
        if (general)
        {
            picRoleHead = ITEM_CONFIG_MGR::instance()->get_icon_path(general->get_face_mode_id());
            m_img_head_photo[i]->loadTexture(picRoleHead, UI_TEX_TYPE_PLIST);
            m_img_head_photo[i]->setVisible(true);

          m_img_click_head_event[i]->setTag(general->get_database_character_id());
            quality_back = DICTIONARY_CONFIG_MGR::instance()->get_charactor_quality_circle_icon(general->get_character_quality());
        }
        else
        {
            m_img_head_photo[i]->setVisible(false);
            quality_back = DICTIONARY_CONFIG_MGR::instance()->get_charactor_quality_circle_icon(Game_Data::QT_MAX);
        }

        m_img_click_head_event[i]->loadTexture(quality_back, UI_TEX_TYPE_PLIST);
    }
}

void UI_HeartMethod_Layer::headPhotoClickEvent( Ref* pSender ,cocos2d::ui::Widget::TouchEventType type)
{
int curImgTag;
cocos2d::ui::ImageView* curImg;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    curImg = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
    curImgTag =curImg->getTag();
    if (curImgTag == 0)
    {
        return;
    }

    m_img_head_effect->setPosition(curImg->getPosition());
    m_select_character_id = curImgTag;

    ShowCharAvatar();
    update();
	break;
    default:
	break;
}

} 

void UI_HeartMethod_Layer::buttonOpenOrNot()
{
//	m_pBtnCombine->setVisible(UI_MainMenu_Layer::get_instance()->arr[Game_Data::ICON_XINFA_COMBINE_BTN]);
//	m_pBtnCombine->setTouchEnabled(UI_MainMenu_Layer::get_instance()->arr[Game_Data::ICON_XINFA_COMBINE_BTN]);

//	m_pBtnXinFaQualityUp->setVisible(UI_MainMenu_Layer::get_instance()->arr[Game_Data::ICON_XINFA_QUA_BTN]);
	//m_pBtnXinFaQualityUp->setTouchEnabled(UI_MainMenu_Layer::get_instance()->arr[Game_Data::ICON_XINFA_QUA_BTN]);
}
