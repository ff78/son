#include "UI_HeartMethod_Combine_Layer.h"

#include "Item_System/Item_Data.h"
#include "Item_System/Item_Logic_Cl.h"
#include "Item_System/Item_Mgr_Cl.h"
#include "Item_Container_System/Item_Container_Mgr_Cl.h"
#include "Item_Container_System/Item_Container_Msg_Proc_Cl.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player_Config_Mgr.h"
using namespace ui;
//#include "cocos-ext.h"
#include "UI/Actor_Layer.h"
//#include "Game_Scene.h"
#include "UI_ModalDialogue_Layer.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "UI_MainMenu_Layer.h"
#include "Item_System/Item_Data.h"
#include "Common/GameMacro.h"

#include "UI_Icon_Info_Layer.h"
#include "Joiner_Guidance.h"
#include "Function_Open_System/Function_Open_Config_Data.h"

using namespace Game_Data;

UI_HeartMethod_Combine_Layer::UI_HeartMethod_Combine_Layer(void):
    m_pMethodWidget(NULL),
    m_img_equipment_select_effect(NULL),
    m_lab_role_name(NULL),
    m_img_head_effect(NULL),
    m_img_fighting_mark(NULL),
    m_pGoodsLayer(NULL),
    m_select_equip_book_index(-1)
{
    memset(m_img_equipment_bar, 0, sizeof(m_img_equipment_bar));
    memset(m_img_equipment_bar_back, 0, sizeof(m_img_equipment_bar_back));

    memset(m_bag_item_id, 0, sizeof(m_bag_item_id));
    memset(m_bar_item_id, 0, sizeof(m_bar_item_id));
    m_select_character_id = 0;
    m_quest_item_base_id = 0;

    memset(m_img_click_head_event, 0, sizeof(m_img_click_head_event));
    memset(m_img_head_photo, 0, sizeof(m_img_head_photo));
}


UI_HeartMethod_Combine_Layer::~UI_HeartMethod_Combine_Layer(void)
{
}

bool UI_HeartMethod_Combine_Layer::init()
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

    m_pMethodWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/XinFa_Level_Up/XinFa_Level_Up.ExportJson");
    addChild(m_pMethodWidget);

    cocos2d::ui::ImageView* imgScrollBack = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMethodWidget,"img_introduce"));
    cocos2d::ui::ImageView* imgBagGrid = m_pGoodsLayer->createHorizontalGrid(STYLE_NOTHING | STYLE_EACH_HAS_EFFECT | STYLE_BOTH_BUTTON);
    imgScrollBack->addChild(imgBagGrid);

    m_pGoodsLayer->btnEat->addTouchEventListener(this, toucheventselector(UI_HeartMethod_Combine_Layer::btnEatCallback));
    m_pGoodsLayer->btnEatFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_EAT_MATERIAL));
    m_pGoodsLayer->btnReset->addTouchEventListener(this, toucheventselector(UI_HeartMethod_Combine_Layer::btnResetCallback));
    m_pGoodsLayer->btnResetFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_RESET));

    for(int i=0; i<PAGE_SUM_NUM; ++i)
    {
        for(int j=0; j<EACH_PAGE_NUM; ++j)
        {
           m_pGoodsLayer->m_pImgTextureChild[i][j]->setTouchEnabled(true);
          m_pGoodsLayer->m_pImgTextureChild[i][j]->setTag(i*EACH_PAGE_NUM+j);
            m_pGoodsLayer->m_pImgTextureChild[i][j]->addTouchEventListener(this, toucheventselector(UI_HeartMethod_Combine_Layer::click_bag_grid));
        }
    }

    m_pBtnClose = (cocos2d::ui::Button*)Helper::seekWidgetByName(m_pMethodWidget,"btn_close");
    m_pBtnClose->addTouchEventListener(this,toucheventselector(UI_HeartMethod_Combine_Layer::buttonCloseCallback));

    char key[32] = {0};

    for (int i = 0;i < ROLE_EQUIP_BOOK_SUM_NUM;++i)
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
        m_img_equipment_bar[i]->addTouchEventListener(this,toucheventselector(UI_HeartMethod_Combine_Layer::click_equipment_bar));
        m_img_equipment_bar[i]->setTouchEnabled(true);
    }

    m_btn_xinfa_canye = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(m_pMethodWidget,"btn_residual_page"));
    m_btn_xinfa_canye->addTouchEventListener(this,toucheventselector(UI_HeartMethod_Combine_Layer::buttonResidualPageCallback));

    m_btn_xinfa_main = dynamic_cast<cocos2d::ui::Button*>(cocos2d::ui::Helper::seekWidgetByName(m_pMethodWidget,"btn_book"));
    m_btn_xinfa_main->addTouchEventListener(this,toucheventselector(UI_HeartMethod_Combine_Layer::buttonXinFaMainCallback));

    m_btn_xinfa_quality_up = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pMethodWidget,"btn_quality_up"));
    m_btn_xinfa_quality_up->addTouchEventListener(this,toucheventselector(UI_HeartMethod_Combine_Layer::buttonQualityUpCallback));

    //装备栏选中状态标示
    m_img_equipment_select_effect = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMethodWidget,"m_img_equipment_select_effect"));
    m_img_equipment_select_effect->setVisible(false);

    //显示角色名字
    m_lab_role_name = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMethodWidget,"lab_role_name"));
    m_img_head_effect = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMethodWidget,"img_head_click_effect"));

    //角色栏 控件获取
    for(int i=0; i<UI_HEAD_SUM_NUM; ++i)
    {
        char imgBack[32] = {0};
        sprintf(imgBack, "img_role_head_back_%d", i);
        m_img_click_head_event[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMethodWidget,imgBack));
      m_img_click_head_event[i]->setTag(0);
        m_img_click_head_event[i]->addTouchEventListener(this, toucheventselector(UI_HeartMethod_Combine_Layer::headPhotoClickEvent));

        char imgHead[32] = {0};
        sprintf(imgHead, "img_role_head_%d", i);
        m_img_head_photo[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMethodWidget,imgHead));
    }

    //获取标记
    m_img_fighting_mark = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pMethodWidget,"img_fighting_mark"));


    //心法变化内容
    m_lab_xinfa_name = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMethodWidget,"lab_book_name"));
    m_lab_xinfa_level = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMethodWidget,"lab_book_level"));
    m_load_xinfa_exp = dynamic_cast<cocos2d::ui::LoadingBar*>(Helper::seekWidgetByName(m_pMethodWidget,"lod_lonadingbar"));
    m_lab_xinfa_need_money = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pMethodWidget,"lab_experience_num"));


    //设置人物头像
    update_role();
    ShowCharAvatar();

    return true;
}

void UI_HeartMethod_Combine_Layer::setVisible( bool visible )
{
    cocos2d::Layer::setVisible(visible);
    if (visible)
    {
        Joiner_Guidance::hideGuide();
        update_role();
        ShowCharAvatar();
        update();
    }
    else
    {
//        UI_MainMenu_Layer::get_instance()->showGuide();
    }
}

void UI_HeartMethod_Combine_Layer::setTouchEvent(bool touchOrNot)
{
    m_pBtnClose->setTouchEnabled(touchOrNot);
    m_btn_xinfa_canye->setTouchEnabled(touchOrNot);
    m_btn_xinfa_main->setTouchEnabled(touchOrNot);
}

void UI_HeartMethod_Combine_Layer::buttonCloseCallback( Ref* pSender ,Widget::TouchEventType type)
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

//点击包裹
void UI_HeartMethod_Combine_Layer::click_bag_grid(Ref* pSender,Widget::TouchEventType type)
{
cocos2d::ui::ImageView* imageView;
int curTag;
uint64 container_id;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    imageView = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
    if (!imageView)
    {
        return;
    }

    curTag =imageView->getTag();
    container_id = m_bag_item_id[curTag];
    if (container_id > 0 )
    {
        if( !m_pGoodsLayer->m_pImgEveryEffect[curTag/EACH_PAGE_NUM][curTag%EACH_PAGE_NUM]->isVisible() )
        {
            m_pGoodsLayer->m_pImgEveryEffect[curTag/EACH_PAGE_NUM][curTag%EACH_PAGE_NUM]->setVisible(true);
        }
        else
        {
            m_pGoodsLayer->m_pImgEveryEffect[curTag/EACH_PAGE_NUM][curTag%EACH_PAGE_NUM]->setVisible(false);
        }

        showChangeInfo();
    }
	break;
    default:
	break;
}

}

//点击装备栏
void UI_HeartMethod_Combine_Layer::click_equipment_bar(Ref* pSender,Widget::TouchEventType type)
{
cocos2d::ui::ImageView* imageView;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    imageView = dynamic_cast<cocos2d::ui::ImageView*>(pSender);

    if(imageView)
    {
        m_select_equip_book_index =imageView->getTag();

        m_img_equipment_select_effect->setVisible(true);
        m_img_equipment_select_effect->setPosition(imageView->getPosition());

        showChangeInfo();
    }

	break;
    default:
	break;
}
}


void UI_HeartMethod_Combine_Layer::update_grid_item(int index,int count,int quality,int icon,bool is_bag)
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

void UI_HeartMethod_Combine_Layer::remove_grid_item(int index,bool is_bag)
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
            for (int j=0; j<EACH_PAGE_NUM; ++j)
            {
                m_pGoodsLayer->m_pImgEveryEffect[i][j]->setVisible(false);
            }
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

void UI_HeartMethod_Combine_Layer::update()
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

    const char* pname = character->get_character_name();
    m_lab_role_name->setString(pname);

    m_img_equipment_select_effect->setVisible(false);
    memset(m_bag_item_id, 0, sizeof(m_bag_item_id));
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
                    m_bag_item_id[index] = container->item_id;
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
    //设置选中效果 (以及当前的 心法 信息)
    for (int i = 0; i < Game_Data::EP_MAX; ++i)
    {
        item = book_bar[i];
        if(item)
        {
            m_bar_item_id[i] = item->id;
            m_img_equipment_select_effect->setPosition(m_img_equipment_bar_back[i]->getPosition());
            m_img_equipment_select_effect->setVisible(true);

            update_grid_item(i,item->count,item->current_quality,item->config->icon,false);
			break;
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

    if (m_select_equip_book_index < 0)
    {
        for (int i = 0; i < Game_Data::EP_MAX; ++i)
        {
            if (m_bar_item_id[i] > 0)
            {
                m_select_equip_book_index = i;
                break;
            }
        }
    }
    
    showChangeInfo();
}

void UI_HeartMethod_Combine_Layer::ShowCharAvatar()
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

void UI_HeartMethod_Combine_Layer::buttonResidualPageCallback( Ref* pSender ,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    setVisible(false);
    UI_MainMenu_Layer::get_instance()->visibleResidualPage();

	break;
    default:
	break;
}
}

void UI_HeartMethod_Combine_Layer::buttonXinFaMainCallback( Ref* pSender ,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    setVisible(false);
    UI_MainMenu_Layer::get_instance()->buttonHeartMethod(NULL,Widget::TouchEventType::ENDED);

	break;
    default:
	break;
}
}

void UI_HeartMethod_Combine_Layer::buttonQualityUpCallback( Ref* pSender,Widget::TouchEventType type )
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    setVisible(false);
    UI_MainMenu_Layer::get_instance()->visibleHeartMethodQualityUp(-1);

	break;
    default:
	break;
}
}

void UI_HeartMethod_Combine_Layer::update_role()
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

void UI_HeartMethod_Combine_Layer::headPhotoClickEvent( Ref* pSender ,Widget::TouchEventType type)
{
 cocos2d::ui::ImageView* curImg ;
 int curImgTag;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    curImg = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
    curImgTag = curImg->getTag();
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

void UI_HeartMethod_Combine_Layer::buttonOpenOrNot()
{
  //  m_btn_xinfa_main->setVisible(UI_MainMenu_Layer::get_instance()->arr[Game_Data::ICON_XINFA_COMBINE_BTN]);
 //  m_btn_xinfa_main->setTouchEnabled(UI_MainMenu_Layer::get_instance()->arr[Game_Data::ICON_XINFA_COMBINE_BTN]);

  //  m_btn_xinfa_quality_up->setVisible(UI_MainMenu_Layer::get_instance()->arr[Game_Data::ICON_XINFA_QUA_BTN]);
  //  m_btn_xinfa_quality_up->setTouchEnabled(UI_MainMenu_Layer::get_instance()->arr[Game_Data::ICON_XINFA_QUA_BTN]);
}

void UI_HeartMethod_Combine_Layer::showChangeInfo()
{
    if (m_select_equip_book_index < 0)
    {
        m_lab_xinfa_name->setVisible(false);
        m_lab_xinfa_level->setVisible(false);
        m_load_xinfa_exp->setVisible(false);
        m_lab_xinfa_need_money->setVisible(false);
        return;
    }
    

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return ;
    }

    // 	if (m_select_index[0] < 0)
    // 	{
    // 	    return;
    // 	}

    //需要升级的心法
    Game_Data::Item* up_item = NULL;
    int item_max_level = 1;
    up_item = ITEM_MGR::instance()->get_item(m_bar_item_id[m_select_equip_book_index]);
    if ( !up_item )
    {
        return;
    }
    else
    {
        m_lab_xinfa_name->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(up_item->config->name));
    }

    item_max_level = ITEM_CONFIG_MGR::instance()->get_book_max_level(up_item->config->base_id,up_item->current_quality);

    //需要吞噬的心法存入 list （可选11个 共计12个）
    Game_Data::Item_List list_item;
    list_item.clear();
    int select_index = -1;
    Game_Data::Item* item = NULL;
    for (int i = 0; i < GRID_NUM; ++i)
    {
        item = ITEM_MGR::instance()->get_item(m_bag_item_id[i]);				//????

        if (item && m_pGoodsLayer->m_pImgEveryEffect[i/EACH_PAGE_NUM][i%EACH_PAGE_NUM]->isVisible() )
        {
            list_item.push_back(item);
        }
    }

    int up_level = 0;
    int surplus_exp = up_item->exp;
    if (list_item.size() > 0)
    {
        ITEM_MGR::instance()->show_book_level_up(up_item,&list_item,up_level,surplus_exp);
    }    

    if (up_level > 0)
    {
        if (up_item->level + up_level >= item_max_level)
        {
            up_level = item_max_level - up_item->level;
            surplus_exp = 0;
        }
    }

    int level_up_need_exp = ITEM_CONFIG_MGR::instance()->get_book_level_up_need_exp(up_item->config->base_id,up_item->level + up_level,up_item->current_quality);

    m_lab_xinfa_level->setString(CCString::createWithFormat("LV.%d",up_item->level + up_level)->getCString());
    m_load_xinfa_exp->setPercent(surplus_exp*100/level_up_need_exp);
    m_lab_xinfa_need_money->setString("XXX");

    m_lab_xinfa_name->setVisible(true);
    m_lab_xinfa_level->setVisible(true);
    m_load_xinfa_exp->setVisible(true);
    m_lab_xinfa_need_money->setVisible(true);
}

void UI_HeartMethod_Combine_Layer::btnEatCallback( Ref* pSender ,Widget::TouchEventType type)
{
int role_id;
Game_Data::Player* player;
Game_Data::Item* up_item;
    std::list<uint64> list_item_id;
    int select_index = -1;
    Game_Data::Item* item = NULL;

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    if (m_select_equip_book_index < 0)
    {
        return;
    }

    role_id = Account_Data_Mgr::instance()->get_current_role_id();
    player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
    if(!player) return;
    if( GUIDE_XF_COMB_STEP_5 == player->get_guide_id() )
    {
        setTouchEvent(false);
        player->change_guide_id(player->get_guide_id()+1);
    }

    up_item = ITEM_MGR::instance()->get_item(m_bar_item_id[m_select_equip_book_index]);
    if (!up_item)
    {
        return;
    }

    list_item_id.clear();

    for (int i = 0;i < GRID_NUM;++i)
    {
        item = ITEM_MGR::instance()->get_item(m_bag_item_id[i]);				//????

        if (item && m_pGoodsLayer->m_pImgEveryEffect[i/EACH_PAGE_NUM][i%EACH_PAGE_NUM]->isVisible() )
        {
            list_item_id.push_back(m_bag_item_id[i]);
        }
    }

    ITEM_LOGIC::instance()->book_level_up(m_bar_item_id[m_select_equip_book_index],&list_item_id);

	break;
    default:
	break;
}
}

void UI_HeartMethod_Combine_Layer::btnResetCallback( Ref* pSender ,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    for (int i = 0;i < GRID_NUM;++i)
    {
        if ( m_pGoodsLayer->m_pImgEveryEffect[i/EACH_PAGE_NUM][i%EACH_PAGE_NUM]->isVisible() )
        {
            m_pGoodsLayer->m_pImgEveryEffect[i/EACH_PAGE_NUM][i%EACH_PAGE_NUM]->setVisible(false);
        }
    }
    showChangeInfo();

	break;
    default:
	break;
}
}
