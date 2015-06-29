#include "UI_Role_Quality_Up.h"
#include "UI_MainMenu_Layer.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Character.h"
#include "Character_System/Player.h"
#include "Network_Common//message.h"
#include "Character_System/Player_Config_Mgr.h"
#include "Character_System/Player_Logic_Cl.h"
#include "Game_Interface/game_content_interface.h"
#include "Item_System/Item_Mgr_Cl.h"

#include "UI_Icon_Info_Layer.h"
#include "Joiner_Guidance.h"
using namespace Game_Data;

using namespace ui;
UI_Role_Quality_Up::UI_Role_Quality_Up(void) : 
	m_img_role_qua_before_back(NULL),
	m_img_role_qua_after_back(NULL),
	m_img_role_quality_before(NULL),
	m_img_role_quality_after(NULL),
	m_lab_role_name_font(NULL),
	m_lab_role_name_font_after(NULL),
	m_Label_original_level(NULL),
	m_Label_after_level(NULL),
    m_img_head_effect(NULL),
    m_img_fighting_mark(NULL),
    m_character_id(0)
{
	memset(m_img_click_head_event, 0, sizeof(m_img_click_head_event));
	memset(m_img_head_icon, 0, sizeof(m_img_head_icon));
	memset(m_img_material, 0, sizeof(m_img_material));
	memset(m_lab_material_need_num, 0, sizeof(m_lab_material_need_num));
	memset(m_lab_qua_befor_attr, 0, sizeof(m_lab_qua_befor_attr));
	memset(m_lab_qua_after_attr, 0, sizeof(m_lab_qua_after_attr));
}


UI_Role_Quality_Up::~UI_Role_Quality_Up(void)
{
}

bool UI_Role_Quality_Up::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	//加载 UI 界面
	cocos2d::ui::Widget* roleQuaWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Player_Quality_Up/Player_Quality_Up.ExportJson");
	addChild(roleQuaWidget);
	
	//关闭 按钮
	cocos2d::ui::Button* btnClose = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(roleQuaWidget,"btn_close"));
	btnClose->addTouchEventListener(this, toucheventselector(UI_Role_Quality_Up::btnCloseCallback));

	//人物按钮
	cocos2d::ui::Button* btnRole = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(roleQuaWidget,"btn_role"));
	btnRole->addTouchEventListener(this, toucheventselector(UI_Role_Quality_Up::btnRoleCallback));

	//Role Name 字体设置
	m_lab_role_name_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(roleQuaWidget,"lab_role_name_font"));
	m_lab_role_name_font_after = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(roleQuaWidget,"lab_role_name_font_after"));

	//charactor level
	m_Label_original_level = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(roleQuaWidget,"Label_original_level"));
	m_Label_after_level = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(roleQuaWidget,"Label_after_level"));

	//升品按钮点击事件
	m_btn_quality_up = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(roleQuaWidget,"btn_quality_up"));
	m_btn_quality_up->addTouchEventListener(this, toucheventselector(UI_Role_Quality_Up::btnRoleQualiryUpCallback));
	m_character_id = Account_Data_Mgr::instance()->get_current_role_id();

    m_img_head_effect = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(roleQuaWidget,"img_head_effect_back"));
    //副将 出战 显示图片
    m_img_fighting_mark = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(roleQuaWidget,"img_fighting_mark"));
	//头像 点击事件 头像图标
	char szName[32] = {0};
	for(int i = 0; i < 8; ++i)
	{
        if (i<UI_HEAD_SUM_NUM)
        {
            memset(szName, 0, sizeof(szName));
            sprintf(szName, "img_role_head_back_%d", i);
            m_img_click_head_event[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(roleQuaWidget,szName));
            m_img_click_head_event[i]->setTag(0);
           m_img_click_head_event[i]->addTouchEventListener(this, toucheventselector(UI_Role_Quality_Up::imgHeadClickEventProc));

            memset(szName, 0, sizeof(szName));
            sprintf(szName, "img_role_head_%d", i);
            m_img_head_icon[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(roleQuaWidget,szName));
            m_img_head_icon[i]->setVisible(false);
        }
        

		if(i<3)
		{
			memset(szName, 0, sizeof(szName));
			sprintf(szName, "img_material_%d", i);
			m_img_material_back[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(roleQuaWidget,szName));

			//升品所需要的 3 个材料格子图片
			memset(szName, 0, sizeof(szName));
			sprintf(szName, "img_material_icon_%d", i);
			m_img_material[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(roleQuaWidget,szName));
            m_img_material[i]->setVisible(false);
           m_img_material[i]->addTouchEventListener(this, toucheventselector(UI_Role_Quality_Up::clickMaterialCallback));
          m_img_material[i]->setTag(0);
            m_img_material[i]->setTouchEnabled(true);

			memset(szName, 0, sizeof(szName));
			sprintf(szName, "lab_icon_num_%d", i);
			m_lab_material_need_num[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(roleQuaWidget,szName));
		}
	}

	//升品前后的头像背景框
	m_img_role_qua_before_back = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(roleQuaWidget,"img_quality_up_before"));
	m_img_role_qua_after_back = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(roleQuaWidget,"img_quality_up_after"));

	//升品前后的头像设置
	m_img_role_quality_before = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(roleQuaWidget,"img_role_head_before"));
	m_img_role_quality_after = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(roleQuaWidget,"img_role_head_after"));


	//生品前后的 各自8个属性
	char roleAttr[32] = {0};
	for ( int i=0; i<ROLE_QUALITY_ATTR_NUM; ++i )
	{
		memset(roleAttr, 0, sizeof(roleAttr));
		sprintf(roleAttr, "lab_qua_attr_before_%d", i);
		m_lab_qua_befor_attr[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(roleQuaWidget,roleAttr));
        //m_lab_qua_befor_attr[i]->setVisible(false);

		memset(roleAttr, 0, sizeof(roleAttr));
		sprintf(roleAttr, "lab_qua_attr_after_%d", i);
		m_lab_qua_after_attr[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(roleQuaWidget,roleAttr));
        m_lab_qua_after_attr[i]->setVisible(false);
	}

	//创建物品信息显示框 function init()
	m_pLayerIconInfo = UI_Icon_Info_Layer::create();
	this->addChild(m_pLayerIconInfo,THISLAYERZORDERE,THISLAYERTAG);
	m_pLayerIconInfo->setVisible(false);


	return true;
}

void UI_Role_Quality_Up::setVisible( bool visible )
{
    if (visible)
    {
        m_img_head_effect->setPosition(m_img_click_head_event[0]->getPosition());
        m_character_id = Account_Data_Mgr::instance()->get_current_role_id();

        update_role();
        update();
		showGuide();
    }
	else
	{
		m_pLayerIconInfo->setVisible(false);

		Joiner_Guidance::hideGuide();
	}

    cocos2d::Layer::setVisible(visible);
}

void UI_Role_Quality_Up::update_role()
{
	//设置 主角头像
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Player* player = (Player*)CHARACTER_MGR::instance()->get_character( role_id );
	if (!player)
	{
        return;
	}

	const char* pic_head = ITEM_CONFIG_MGR::instance()->get_icon_path(player->get_face_mode_id());
	m_img_head_icon[0]->loadTexture(pic_head, UI_TEX_TYPE_PLIST);
    m_img_head_icon[0]->setVisible(true);

    const char* quality_back = DICTIONARY_CONFIG_MGR::instance()->get_charactor_quality_circle_icon(player->get_character_quality());
    m_img_click_head_event[0]->loadTexture(quality_back, UI_TEX_TYPE_PLIST);
    m_img_click_head_event[0]->setTag(role_id);

	//设置 副将头像
	for (int i = 1; i < UI_HEAD_SUM_NUM; ++i)
	{
		DeputyGeneral* general = player->get_deputy_general_by_index(i-1);
		if (general)
		{
	        pic_head = ITEM_CONFIG_MGR::instance()->get_icon_path(general->get_face_mode_id());
			m_img_head_icon[i]->loadTexture(pic_head, UI_TEX_TYPE_PLIST);
            m_img_head_icon[i]->setVisible(true);

          m_img_click_head_event[i]->setTag(general->get_database_character_id());
            quality_back = DICTIONARY_CONFIG_MGR::instance()->get_charactor_quality_circle_icon(general->get_character_quality());
		}
        else
        {
            m_img_head_icon[i]->setVisible(false);
            quality_back = DICTIONARY_CONFIG_MGR::instance()->get_charactor_quality_circle_icon(Game_Data::QT_MAX);
        }
		
		m_img_click_head_event[i]->loadTexture(quality_back, UI_TEX_TYPE_PLIST);
	}
}

//升品按钮点击事件处理
void UI_Role_Quality_Up::btnRoleQualiryUpCallback(Ref* pSender,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	PLAYER_LOGIC::instance()->player_quality_up(m_character_id);
	changeGuide();

	break;
    default:
	break;
}
}

//界面刷新函数
void UI_Role_Quality_Up::update()
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return ;
    }

    Character* character = CHARACTER_MGR::instance()->get_character(m_character_id);
    if (!character)
    {
        return;
    }

	m_lab_role_name_font->setString(character->get_character_name());
	m_lab_role_name_font_after->setString(character->get_character_name());

	char str_tmp[32] = {0};
	memset(str_tmp, 0, sizeof(str_tmp));
	int level_number = character->get_character_level();
	sprintf(str_tmp,"LV %d",level_number );

	m_Label_original_level->setString(str_tmp);
	m_Label_after_level->setString(str_tmp);

    const char* icon = ITEM_CONFIG_MGR::instance()->get_icon_path(character->get_face_mode_id());
    m_img_role_quality_before->loadTexture(icon,UI_TEX_TYPE_PLIST);

    const char* back = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(character->get_character_quality());
    m_img_role_qua_before_back->loadTexture(back,UI_TEX_TYPE_PLIST);

    int up_quality = character->get_character_quality()+1;
    if (up_quality < Game_Data::QT_MAX)
    {
        m_img_role_quality_after->loadTexture(icon,UI_TEX_TYPE_PLIST);
        m_img_role_quality_after->setVisible(true);

        back = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(up_quality);
    }
    else
    {
        back = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(Game_Data::QT_MAX);
        m_img_role_quality_after->setVisible(false);
    }

    m_img_role_qua_after_back->loadTexture(back,UI_TEX_TYPE_PLIST);

    m_img_fighting_mark->setVisible(false);
    for (int i=1; i<6; ++i)
    {
        if(m_img_click_head_event[i]->getTag() != 0 && m_img_click_head_event[i]->getTag() == player->get_fight_general_id())
        {
            m_img_fighting_mark->setPosition(Vec2(m_img_click_head_event[i]->getPosition().x-m_img_click_head_event[i]->getContentSize().width/2+m_img_fighting_mark->getContentSize().width/2+12,
                m_img_click_head_event[i]->getPosition().y-m_img_click_head_event[i]->getContentSize().height/2+m_img_fighting_mark->getContentSize().height/2+15));
            m_img_fighting_mark->setVisible(true);
        }
    }

    update_character_attr();
    update_need_material(character->get_character_quality());
}

void UI_Role_Quality_Up::update_character_attr()
{
    Character* character = CHARACTER_MGR::instance()->get_character(m_character_id);
    if (!character)
    {
        return;
    }

    Player_Base_Attr_Config_Data* base_attr = PLAYER_MGR::instance()->get_player_base_attr(character->get_static_character_id());
    if (!base_attr)
    {
        return;
    }

    Player_Level_Attr_Config_Data* level_attr = PLAYER_MGR::instance()->get_player_level_attr(base_attr->get_player_level_id(),character->get_character_level());
    if (!level_attr)
    {
        return;
    }

    //第一个生命
    const char* name0 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_HEALTH);
    int smvalue = level_attr->get_player_max_hp();
    m_lab_qua_befor_attr[0]->setString(CCString::createWithFormat("%s:%d",name0,smvalue)->getCString());

    //第二个罡气
    const char* name1 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_MAGIC);
    int gqvalue = level_attr->get_player_max_gp();
    m_lab_qua_befor_attr[1]->setString(CCString::createWithFormat("%s:%d",name1,gqvalue)->getCString());

    //第三个攻击
    const char* name2 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_ATTACK);
    int gjvalue = level_attr->get_player_attack();
    m_lab_qua_befor_attr[2]->setString(CCString::createWithFormat("%s:%d",name2,gjvalue)->getCString());

    //第四个防御
    const char* name3 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_DEFENSE);
    int fyvalue = level_attr->get_player_define();
    m_lab_qua_befor_attr[3]->setString(CCString::createWithFormat("%s:%d",name3,fyvalue)->getCString());

    //第五个命中
    const char* name4 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_HIT);
    int mzvalue = level_attr->get_player_hit_ratio() - HIT_SHOW_OFFSET;
    m_lab_qua_befor_attr[4]->setString(CCString::createWithFormat("%s:%d",name4,mzvalue)->getCString());

    //第六个闪避
    const char* name5 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_DODGE);
    int sbvalue = level_attr->get_player_avoidance();
    m_lab_qua_befor_attr[5]->setString(CCString::createWithFormat("%s:%d",name5,sbvalue)->getCString());

    //第七个暴击
    const char* name6 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_CRIT);
    int bjvalue = level_attr->get_player_crit_rate() - CRIT_SHOW_OFFSET;
    m_lab_qua_befor_attr[6]->setString(CCString::createWithFormat("%s:%d",name6,bjvalue)->getCString());

    //第八个坚韧
    const char* name7 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_TENACITY);
    int jrvalue = level_attr->get_player_tenacity();
    m_lab_qua_befor_attr[7]->setString(CCString::createWithFormat("%s:%d",name7,jrvalue)->getCString());

    //第九个暴击加成
    const char* name8 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_POW);
    int bjjcvalue = level_attr->get_player_power();
    m_lab_qua_befor_attr[8]->setString(CCString::createWithFormat("%s:%d",name8,bjjcvalue)->getCString());

    if ((character->get_character_quality() + 1) < Game_Data::QT_MAX)
    {
        base_attr = PLAYER_MGR::instance()->get_player_base_attr(character->get_static_character_id() + 1);
        if (!base_attr)
        {
            return;
        }

        level_attr = PLAYER_MGR::instance()->get_player_level_attr(base_attr->get_player_level_id(),character->get_character_level());
        if (!level_attr)
        {
            return;
        }

        //第一个生命
        int smvalue = level_attr->get_player_max_hp();
        m_lab_qua_after_attr[0]->setString(CCString::createWithFormat("%d",smvalue)->getCString());

        //第二个罡气
        int gqvalue = level_attr->get_player_max_gp();
        m_lab_qua_after_attr[1]->setString(CCString::createWithFormat("%d",gqvalue)->getCString());

        //第三个攻击
        int gjvalue = level_attr->get_player_attack();
        m_lab_qua_after_attr[2]->setString(CCString::createWithFormat("%d",gjvalue)->getCString());

        //第四个防御
        int fyvalue = level_attr->get_player_define();
        m_lab_qua_after_attr[3]->setString(CCString::createWithFormat("%d",fyvalue)->getCString());

        //第五个命中
        int mzvalue = level_attr->get_player_hit_ratio() - HIT_SHOW_OFFSET;
        m_lab_qua_after_attr[4]->setString(CCString::createWithFormat("%d",mzvalue)->getCString());

        //第六个闪避
        int sbvalue = level_attr->get_player_avoidance();
        m_lab_qua_after_attr[5]->setString(CCString::createWithFormat("%d",sbvalue)->getCString());

        //第七个暴击
        int bjvalue = level_attr->get_player_crit_rate() - CRIT_SHOW_OFFSET;
        m_lab_qua_after_attr[6]->setString(CCString::createWithFormat("%d",bjvalue)->getCString());

        //第八个坚韧
        int jrvalue = level_attr->get_player_tenacity();
        m_lab_qua_after_attr[7]->setString(CCString::createWithFormat("%d",jrvalue)->getCString());

        //第九个暴击加成
        int bjjcvalue = level_attr->get_player_power();
        m_lab_qua_after_attr[8]->setString(CCString::createWithFormat("%d",bjjcvalue)->getCString());

        for (int i = Game_Data::EAT_HEALTH;i < MAX_ATTR_COUNT;++i)
        {
            m_lab_qua_after_attr[i]->setVisible(true);
        }
    } 
    else
    {
        for (int i = Game_Data::EAT_HEALTH;i < MAX_ATTR_COUNT;++i)
        {
            m_lab_qua_after_attr[i]->setVisible(false);
        }
    }
}

void UI_Role_Quality_Up::update_need_material(int cur_quality)
{
    for (int i = 0; i < 3; ++i)
    {
        m_img_material[i]->setVisible(false);
        m_lab_material_need_num[i]->setVisible(false);
        const char* back = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(Game_Data::QT_MAX);
        m_img_material_back[i]->loadTexture(back,UI_TEX_TYPE_PLIST);
      m_img_material[i]->setTag(0);
        m_img_material[i]->setVisible(false);
    }

    if ((cur_quality+1) >= Game_Data::QT_MAX)
    {
        return;
    }
    
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return;
    }

    Game_Data::game_element_list_t ele_list;
    ITEM_CONFIG_MGR::instance()->get_quality_upgrade_need_material(Game_Data::QMT_ROLE,cur_quality,ele_list);

    int index = 0;
    Game_Data::game_element_list_t::iterator itg;
    for( itg = ele_list.begin(); itg != ele_list.end(); ++ itg)
    {
        Game_Data::Game_Element& element = (*itg);
        if(strcmp(element.get_command(),"instance") == 0 || strcmp(element.get_command(),"arena") == 0)
        {
            vector<uint> para;
            element.get_para_list_in_vector( para);
            if(para.size() > 1)
            {
                int item_base_id = para[0];
                int need_count = para[1];
                Game_Data::Item_Config* item_config = ITEM_CONFIG_MGR::instance()->get_item_config(item_base_id);
                if (item_config)
                {
                    const char* icon = ITEM_CONFIG_MGR::instance()->get_icon_path(item_config->icon);
                    m_img_material[index]->loadTexture(icon,UI_TEX_TYPE_PLIST);
                    m_img_material[index]->setVisible(true);

                    const char* back = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(item_config->quality);
                    m_img_material_back[index]->loadTexture(back,UI_TEX_TYPE_PLIST);

                    int have_count = player->get_bag_same_item_count(item_base_id);
                    m_lab_material_need_num[index]->setString(CCString::createWithFormat("%d/%d",have_count,need_count)->getCString());
                    m_lab_material_need_num[index]->setVisible(true);
					
					Color3B lab_material_num	= ccc3(0,0,0);
					do 
					{
						if (have_count >= need_count)
						{
							lab_material_num = ccc3(56,255,51); // #38ff33
							break;
						}
						if (have_count < need_count)
						{
							lab_material_num = ccc3(204,37,14); // #cc250e  
							break;
						}
					} while (false);
					
					m_lab_material_need_num[index]->setColor(lab_material_num);
                   m_img_material[index]->setTag(item_base_id);

                    ++index;
                }
            }
        }
    }
}

void UI_Role_Quality_Up::imgHeadClickEventProc(Ref* pSender,Widget::TouchEventType type)
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
	m_character_id = curImgTag;

    update();

	break;
    default:
	break;
}
}

void UI_Role_Quality_Up::btnCloseCallback(Ref* pSender,Widget::TouchEventType type)
{
	setVisible(false);
}

void UI_Role_Quality_Up::btnRoleCallback(Ref* pSender,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(false);
	UI_MainMenu_Layer::get_instance()->buttonMainRoleInfo(NULL,Widget::TouchEventType::ENDED);

	break;
    default:
	break;
}
}

void UI_Role_Quality_Up::btnBagCallback(Ref* pSender,Widget::TouchEventType type)
{
	setVisible(false);
	UI_MainMenu_Layer::get_instance()->buttonBagInfo(NULL,Widget::TouchEventType::ENDED);
}

void UI_Role_Quality_Up::btnSkillCallback(Ref* pSender,Widget::TouchEventType type)
{
	setVisible(false);
	UI_MainMenu_Layer::get_instance()->buttonSkillInfo(NULL,Widget::TouchEventType::ENDED);
}

void UI_Role_Quality_Up::clickMaterialCallback( Ref* pSender,Widget::TouchEventType type )
{
int curImgTag;
cocos2d::ui::ImageView* curClickImg ;
Character* character;
    std::vector<uint64> para;
	Game_Data::Item_Config* config;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    curClickImg = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
    curImgTag =curClickImg->getTag();
    if (curImgTag == 0)
    {
        return;
    }

    character = CHARACTER_MGR::instance()->get_character(m_character_id);
    if (!character)
    {
        return;
    }

    para.push_back(m_character_id);
    para.push_back(Game_Data::QMT_ROLE);
    m_pLayerIconInfo->set_param(para);

	config = ITEM_CONFIG_MGR::instance()->get_item_config(curImgTag);
	m_pLayerIconInfo->showButton(curImgTag, config->icon, config->name, 1, config->quality, TIPS_STYLE_FINDWAY);
	m_pLayerIconInfo->setVisible(true);

	break;
    default:
	break;
}

}

void UI_Role_Quality_Up::showGuide()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	if ( GUIDE_ROLE_QUA_3 == player->get_guide_id() )
	{
		Joiner_Guidance::receiveCurPosWidget(m_btn_quality_up);
	}
}

void UI_Role_Quality_Up::changeGuide()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	if ( GUIDE_ROLE_QUA_3 == player->get_guide_id() )
	{
		player->change_guide_id( player->get_guide_id()+3 );
		Joiner_Guidance::showGuide();
	}
}
