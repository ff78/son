#include "UI_Role_Info_Layer.h"

#include "Item_System/Item_Data.h"
#include "Item_System/Item_Logic_Cl.h"
#include "Item_System/Item_Mgr_Cl.h"
#include "Item_Container_System/Item_Container_Mgr_Cl.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Character.h"
#include "Character_System/Player.h"
#include "Character_System/Player_Logic_Cl.h"

//#include "cocos-ext.h"
//#include "Game_Scene.h"
#include "UI_MainMenu_Layer.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Character_System/Player_Config_Mgr.h"
#include "Common/GameMacro.h"
#include "Function_Open_System/Function_Open_Config_Data.h"

#include "UI_Icon_Info_Layer.h"
#include "Joiner_Guidance.h"

USING_NS_CC;
//USING_NS_CC_EXT;
using namespace Game_Data;
using namespace ui;
UI_Role_Info_Layer::UI_Role_Info_Layer(void) :
	m_img_head_effect(NULL),
	m_bt_fightingBtn(NULL),
	m_img_fighting_mark(NULL),
	m_lab_fighting(NULL),
	m_select_character_id(0),
	m_fighting_capacity(NULL),
	btnToRoleQuaUp(NULL),
	m_role_strenght_stroke(NULL),
	m_role_exp_stroke_label(NULL),
	loading_EXP(NULL),
	loading_Strength(NULL)
{

	memset(m_img_equipment_bar,0 ,sizeof(m_img_equipment_bar));
	memset(m_btn_equipment_bar_back,0 ,sizeof(m_btn_equipment_bar_back));
	memset(m_img_equipment_bar_pinzhi,0,sizeof(m_img_equipment_bar_pinzhi));
	memset(m_bar_item_id,0,sizeof(m_bar_item_id));

	memset(m_img_click_head_event, 0, sizeof(m_img_click_head_event));
	memset(m_img_head_photo, 0, sizeof(m_img_head_photo));

	m_fighting_capacity = LabelAtlas::create("0123456789","pic_zhanlizhi_shuzi.png",22,33,'0');
	m_fighting_capacity->setVisible(true);
}


UI_Role_Info_Layer::~UI_Role_Info_Layer(void)
{
}

bool UI_Role_Info_Layer::init()
{
	if(!cocos2d::Layer::init())
	{
		return false;
	}

	setTouchEnabled(true);

	coco_ = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/PlayerAttr/property.ExportJson");
	addChild(coco_);

	cocos2d::ui::Button* closeButton = static_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(coco_,"btn_close"));
	closeButton->addTouchEventListener(this,toucheventselector(UI_Role_Info_Layer::menuCloseCallback));

	m_img_selected_effect=dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(coco_,"img_selected_back_effect"));
	m_img_selected_effect->setVisible(false);

	m_img_head_effect = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(coco_,"img_head_click_effect"));

	//副将出战 按钮
	m_bt_fightingBtn = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(coco_,"tbn_role_fighting"));
	m_bt_fightingBtn->addTouchEventListener(this,toucheventselector(UI_Role_Info_Layer::btnCallBackFighting));
	m_bt_fightingBtn->setVisible(false);

	m_lab_fighting = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(coco_,"lab_role_fighting_font"));
	m_lab_fighting->setString("");

	//副将 出战 显示图片
	m_img_fighting_mark = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(coco_,"img_fighting_mark"));

	//战力值
	cocos2d::ui::ImageView* fighting_capacity_title = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(coco_,"Zhanli_Title"));
	if (fighting_capacity_title)
	{
		m_fighting_capacity->setAnchorPoint(Vec2(0,0.5));
		m_fighting_capacity->setZOrder(fighting_capacity_title->getZOrder() +1 );
		fighting_capacity_title->addChild(m_fighting_capacity);
	}

	char key[32] = {0};
	for (int i = 0; i < 6 ; ++i)
	{
		memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
		sprintf_s(key,"btn_equipment_%d",i+1);
#else
		sprintf(key,"btn_equipment_%d",i+1);
#endif
		m_btn_equipment_bar_back[i] = static_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(coco_,key));
		m_img_equipment_bar[i] = cocos2d::ui::ImageView::create();
		m_img_equipment_bar_pinzhi[i]=cocos2d::ui::ImageView::create();
		m_btn_equipment_bar_back[i]->getParent()->addChild(m_img_equipment_bar[i]);
		m_btn_equipment_bar_back[i]->getParent()->addChild(m_img_equipment_bar_pinzhi[i]);
		m_img_equipment_bar[i]->setZOrder(m_btn_equipment_bar_back[i]->getZOrder()+2);
		m_img_equipment_bar_pinzhi[i]->setZOrder(m_btn_equipment_bar_back[i]->getZOrder()+1);
		m_img_equipment_bar[i]->setPosition(m_btn_equipment_bar_back[i]->getPosition());
		m_img_equipment_bar_pinzhi[i]->setPosition(m_btn_equipment_bar_back[i]->getPosition());

		m_img_equipment_bar[i]->addTouchEventListener(this,toucheventselector(UI_Role_Info_Layer::equipCallBack));
	    m_img_equipment_bar[i]->setTag(i);
		m_img_equipment_bar[i]->setTouchEnabled(true);

	}
	//初始化14个属性和值
	for(int i=1;i<=14;++i)
	{
		char str1[32] = {0};
		sprintf(str1,"lab_%d",i);
		m_attr_lab[i-1]= dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(coco_,str1));

		char str2[32]={0};
		SPRINTF(str2,"value_%d",i);
		m_attr_labvalue[i-1]=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(coco_,str2));
	}

	//头像栏 操作 点击事件 与 设置头像图片
	for(int i=0; i<UI_HEAD_SUM_NUM; ++i)
	{
		char imgBack[32] = {0};
		sprintf(imgBack, "img_role_head_back_%d", i);
		m_img_click_head_event[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(coco_,imgBack));
	    m_img_click_head_event[i]->setTag(0);
		m_img_click_head_event[i]->addTouchEventListener(this, toucheventselector(UI_Role_Info_Layer::headPhotoClickEvent));

		char imgHead[32] = {0};
		sprintf(imgHead, "img_role_head_%d", i);
		m_img_head_photo[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(coco_,imgHead));
	}

	ShowCharAvatar();

	//点击到人物生品界面
	btnToRoleQuaUp = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(coco_,"btn_goods"));
	btnToRoleQuaUp->addTouchEventListener(this, toucheventselector(UI_Role_Info_Layer::btnRoleQuaCallback));

	cocos2d::ui::Text* label_font = nullptr;
	const char* font_info = nullptr;

	//title font
	label_font = static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(coco_,"lab_title_font"));
	font_info = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_ROLE);
	label_font->setString(font_info);

	//创建物品信息显示框 function init()
	m_pLayerIconInfo = UI_Icon_Info_Layer::create();
	this->addChild(m_pLayerIconInfo,THISLAYERZORDERE,THISLAYERTAG);
	m_pLayerIconInfo->setVisible(false);

	m_role_exp_stroke_label = StrokeLabelTTF::create("","",20);
	m_role_strenght_stroke = StrokeLabelTTF::create("","",20);

	m_role_exp_stroke_label->setColor(ccc3(245,215,142));
	m_role_exp_stroke_label->setStrokeColor(ccc3(14,8,0));

	m_role_strenght_stroke->setColor(ccc3(245,215,142));
	m_role_strenght_stroke->setStrokeColor(ccc3(14,8,0));

	loading_EXP = dynamic_cast<cocos2d::ui::LoadingBar*>(Helper::seekWidgetByName(coco_,"lodb_LoadingBar"));
	loading_Strength = dynamic_cast<cocos2d::ui::LoadingBar*>(Helper::seekWidgetByName(coco_,"strength_bar"));

	loading_Strength->addChild(m_role_strenght_stroke);
	loading_EXP->addChild(m_role_exp_stroke_label);

	return true;
}


void UI_Role_Info_Layer::update_role()
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

void UI_Role_Info_Layer::update_grid_item(int index,int count,int quality,int icon)
{
	m_btn_equipment_bar_back[index]->setVisible(false);
	const char* szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(icon);
	m_img_equipment_bar[index]->loadTexture(szPath,UI_TEX_TYPE_PLIST);
	m_img_equipment_bar[index]->setVisible(true);

	szPath = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(quality);
	m_img_equipment_bar_pinzhi[index]->loadTexture(szPath,UI_TEX_TYPE_PLIST);
}

void UI_Role_Info_Layer::remove_grid_item(int index)
{
	m_img_equipment_bar[index]->setVisible(false);
	m_btn_equipment_bar_back[index]->setVisible(true);
	m_img_equipment_bar_pinzhi[index]->setVisible(false);
	m_img_equipment_bar_pinzhi[index]->setVisible(false);
}

void UI_Role_Info_Layer::setVisible(bool visible)
{
	cocos2d::Layer::setVisible(visible);

	if(visible)
	{
		Joiner_Guidance::hideGuide();
		update_role();
		ShowCharAvatar();
		update();
		showGuide();
	}
	else
	{
//		UI_MainMenu_Layer::get_instance()->showGuide();
		m_pLayerIconInfo->setVisible(false);
	}
}
void UI_Role_Info_Layer::menuCloseCallback( Ref* pSender ,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(false);
	m_img_selected_effect->setVisible(false);

	Joiner_Guidance::hideGuide();

	break;
    default:
	break;
}
}

void UI_Role_Info_Layer::set_Info(std::vector<int>& para)
{
	if(para.size() <= 0)
	{
		CCLOG("vector == NULL");
		return;
	}

}

void UI_Role_Info_Layer::update()
{
	buttonOpenOrNot();
	RefreshUI();
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	if (!player)
	{
		return;
	}

	Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(m_select_character_id);
	if (!character)
	{
		return;
	}

	m_bt_fightingBtn->setVisible(false);
	//如果选中的是 出战副将 则将出战按钮 设置成 放弃出战

	if(m_select_character_id == player->get_fight_general_id())
	{
		const char* quitFightingFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(LIEUTENANT_QUIT_FIGHTING_FONT);
		m_lab_fighting->setString(quitFightingFont);
		m_bt_fightingBtn->setVisible(true);
	}
	if(m_select_character_id != role_id && m_select_character_id != player->get_fight_general_id())
	{
		const char* fightingFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(LIEUTENANT_FIGHTING_FONT);
		m_lab_fighting->setString(fightingFont);
		m_bt_fightingBtn->setVisible(true);
	}

	memset(m_bar_item_id, 0, sizeof(m_bar_item_id));
	Game_Data::Item* item = NULL;
	Game_Data::Item** equipment_bar = character->get_equipment_array();
	for (int i = 0;i < Game_Data::EP_MAX;++i)
	{
		item = equipment_bar[i];
		if (item)
		{
			m_bar_item_id[i] = item->id;
			update_grid_item(i,1,item->current_quality,item->config->icon);
		}
		else
		{
			remove_grid_item(i);
		}
	}

	m_img_fighting_mark->setVisible(false);
	for (int i=1; i<UI_HEAD_SUM_NUM - 1; ++i)
	{
		if(m_img_click_head_event[i]->getTag() != 0 && m_img_click_head_event[i]->getTag() == player->get_fight_general_id())
		{
			m_img_fighting_mark->setPosition(Vec2(m_img_click_head_event[i]->getPosition().x-m_img_click_head_event[i]->getContentSize().width/2+m_img_fighting_mark->getContentSize().width/2+12,
				m_img_click_head_event[i]->getPosition().y-m_img_click_head_event[i]->getContentSize().height/2+m_img_fighting_mark->getContentSize().height/2+15));
			m_img_fighting_mark->setVisible(true);
		}
	}

	m_fighting_capacity->setString(CCString::createWithFormat("%d",character->get_fighting_capacity())->getCString());

}


void UI_Role_Info_Layer::RefreshUI()
{
	Character* character = CHARACTER_MGR::instance()->get_character(m_select_character_id);
	if (!character)
	{
		return;
	}

	//role name visible
	cocos2d::ui::Text* pBtn = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(coco_,"lab_role_name_font"));
	pBtn->setString(character->get_character_name());

	int nLevel = character->get_character_level();
	cocos2d::ui::Text* ctl = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(coco_,"lab_role_level"));
	ctl->setString(CCString::createWithFormat("LV.%d",nLevel)->getCString());

	//第一个生命
	const char* name0 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_HEALTH);
	int smvalue = character->get_character_max_hp();
	m_attr_lab[0]->setString(CCString::createWithFormat("%s:",name0)->getCString());
	m_attr_labvalue[0]->setString(CCString::createWithFormat("%d",smvalue)->getCString());

	//第二个罡气
	const char* name1 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_MAGIC);
	int gqvalue = character->get_character_max_gp();
	m_attr_lab[1]->setString(CCString::createWithFormat("%s:",name1)->getCString());
	m_attr_labvalue[1]->setString(CCString::createWithFormat("%d",gqvalue)->getCString());

	//第三个攻击
	const char* name2 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_ATTACK);
	int gjvalue = character->get_character_attack();
	m_attr_lab[2]->setString(CCString::createWithFormat("%s:",name2)->getCString());
	m_attr_labvalue[2]->setString(CCString::createWithFormat("%d",gjvalue)->getCString());

	//第四个防御
	const char* name3 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_DEFENSE);
	int fyvalue = character->get_character_define();
	m_attr_lab[3]->setString(CCString::createWithFormat("%s:",name3)->getCString());
	m_attr_labvalue[3]->setString(CCString::createWithFormat("%d",fyvalue)->getCString());

	//第五个命中
	const char* name4 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_HIT);
	int mzvalue = character->get_character_hit_ratio() - HIT_SHOW_OFFSET;
	m_attr_lab[4]->setString(CCString::createWithFormat("%s:",name4)->getCString());
	m_attr_labvalue[4]->setString(CCString::createWithFormat("%d",mzvalue)->getCString());

	//第六个闪避
	const char* name5 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_DODGE);
	int sbvalue = character->get_character_avoidance();
	m_attr_lab[5]->setString(CCString::createWithFormat("%s:",name5)->getCString());
	m_attr_labvalue[5]->setString(CCString::createWithFormat("%d",sbvalue)->getCString());

	//第七个暴击
	const char* name6 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_CRIT);
	int bjvalue = character->get_character_crit_rate() - CRIT_SHOW_OFFSET;
	m_attr_lab[6]->setString(CCString::createWithFormat("%s:",name6)->getCString());
	m_attr_labvalue[6]->setString(CCString::createWithFormat("%d",bjvalue)->getCString());

	//第八个坚韧
	const char* name7 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_TENACITY);
	int jrvalue = character->get_character_tenacity();
	m_attr_lab[7]->setString(CCString::createWithFormat("%s:",name7)->getCString());
	m_attr_labvalue[7]->setString(CCString::createWithFormat("%d",jrvalue)->getCString());

	// 第九 暴伤
	const char* name8 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_HURT);
	int bjjcvalue = character->get_character_crit()/100;
	m_attr_lab[8]->setString(CCString::createWithFormat("%s:",name8)->getCString());
	m_attr_labvalue[8]->setString(CCString::createWithFormat("%d%%",bjjcvalue)->getCString());

	// 第十 功力
	const char* name9 = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(RAT_POW);
	int xfglvalue = character->get_power();
	m_attr_lab[9]->setString(CCString::createWithFormat("%s:",name9)->getCString());
	m_attr_labvalue[9]->setString(CCString::createWithFormat("%d",xfglvalue)->getCString());

	int current_exp = character->get_exp();
	int current_level_sum_exp = character->get_player_levelup_exp();
	char keyEXP[32] = {0};
	sprintf(keyEXP,"%d/%d",current_exp,current_level_sum_exp);
	cocos2d::ui::Text* role_EXP = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(coco_,"lab_role_exp"));
	role_EXP->setVisible(false);

	m_role_exp_stroke_label->setString(keyEXP);

	loading_EXP->setPercent(current_exp*100/current_level_sum_exp);

	initStrength_bar_bg_frame();
}

void UI_Role_Info_Layer::ShowCharAvatar()
{
#if 0
	cocos2d::ui::ImageView* pView = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(coco_,"img_Role_bkg"));
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

void UI_Role_Info_Layer::btnBagCallBack(Ref* pSender,Widget::TouchEventType type)
{
	this->setVisible(false);
	UI_MainMenu_Layer::get_instance()->buttonBagInfo(NULL,Widget::TouchEventType::ENDED);
}

void UI_Role_Info_Layer::btnSkillCallBack(Ref* pSender,Widget::TouchEventType type)
{
	this->setVisible(false);
	UI_MainMenu_Layer::get_instance()->buttonSkillInfo(NULL,Widget::TouchEventType::ENDED);
}

void UI_Role_Info_Layer::btnRoleQuaCallback(Ref* pSender,Widget::TouchEventType type)
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(false);
	changeGuide();
	UI_MainMenu_Layer::get_instance()->visibleRoleQualityUp();

	break;
    default:
	break;
}
}

void UI_Role_Info_Layer::btnCallBackFighting(Ref* pSender,Widget::TouchEventType type)
{
int player_id ;
Game_Data::Player* player;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	player_id = Account_Data_Mgr::instance()->get_current_role_id();
	player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	if ( GUIDE_LIEU_FIGHT_3 == player->get_guide_id() )
	{
		player->change_guide_id( player->get_guide_id()+2 );
		Joiner_Guidance::hideGuide();
	}

	PLAYER_LOGIC::instance()->player_callup_deputy_general(m_select_character_id);

	break;
    default:
	break;
}
}

void UI_Role_Info_Layer::btnCallBackMissing(Ref* pSender,Widget::TouchEventType type)
{
	CCLOG("Lieutenant throw button UI_Role_Info_Layer::btnQuitFightCallback");
}

void UI_Role_Info_Layer::equipCallBack(Ref* pSender,Widget::TouchEventType type)
{
cocos2d::ui::ImageView* imageview ;
uint64 item_id;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	imageview = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
	if (imageview)
	{
		item_id =m_bar_item_id[imageview->getTag()];
		if (item_id > 0)
		{
			m_img_selected_effect->setVisible(true);
			m_img_selected_effect->setPosition(imageview->getPosition());
			refreshDialog(item_id);
		}
	}

	break;
    default:
	break;
}
}

void UI_Role_Info_Layer::refreshDialog(uint64 item_id)
{
	Game_Data::Item* item = ITEM_MGR::instance()->get_item(item_id);
	if (item)
	{   
        m_pLayerIconInfo->set_gem_id(item->gem_id);

		m_pLayerIconInfo->showButton(item->config->base_id,item->config->icon,item->config->name,item->level,item->current_quality,
			TIPS_STYLE_OK | TIPS_STYLE_LEVEL | TIPS_STYLE_EQUIPMENT_ATTR | FRAME_STYLE_INLAY);
		m_pLayerIconInfo->setVisible(true);
	}
}


void UI_Role_Info_Layer::headPhotoClickEvent( Ref* pSender ,Widget::TouchEventType type)
{
cocos2d::ui::ImageView* curImg;
int curImgTag ;
int player_id;
Game_Data::Player* player ;
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

	player_id = Account_Data_Mgr::instance()->get_current_role_id();
	player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	if ( player_id !=m_select_character_id && GUIDE_LIEU_FIGHT_2 == player->get_guide_id() )
	{
		player->change_guide_id( player->get_guide_id()+1 );
		Joiner_Guidance::showGuide();
	}

	ShowCharAvatar();
	update();

	break;
    default:
	break;
}
}

void UI_Role_Info_Layer::initStrength_bar_bg_frame()
{

	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	cocos2d::ui::ImageView* strength_bar_bg_frame = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(coco_,"strength_bar_bg_frame"));
	cocos2d::ui::Text* strength_title = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(coco_,"strength_title"));


	if (role_id != m_select_character_id)
	{
		if (strength_title)
		{
			strength_title->setVisible(false);
		}

		if (strength_bar_bg_frame)
		{
			strength_bar_bg_frame->setVisible(false);
		}
	}
	else
	{
		Player* player = dynamic_cast<Player*>( CHARACTER_MGR::instance()->get_character(m_select_character_id) );
		if (!player)
		{
			return;
		}

		if (strength_title)
		{
			strength_title->setVisible(true);
		}

		if (strength_bar_bg_frame)
		{
			strength_bar_bg_frame->setVisible(true);
		}

		int current_strength = player->get_energy();
		int const_strngth_value = PLAYER_MAX_ENERGY;
		char keyStrength[32] = {0};
		sprintf(keyStrength,"%d/%d",current_strength,const_strngth_value);
		cocos2d::ui::Text* role_strenght = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(coco_,"strength_value"));
		role_strenght->setVisible(false);

		m_role_strenght_stroke->setString(keyStrength);

		loading_Strength->setPercent(current_strength*100/const_strngth_value);

	}
}


void UI_Role_Info_Layer::buttonOpenOrNot()
{
///	btnToRoleQuaUp->setVisible(UI_MainMenu_Layer::get_instance()->arr[Game_Data::ICON_ROLE_QUA_BTN]);
//	btnToRoleQuaUp->setTouchEnabled(UI_MainMenu_Layer::get_instance()->arr[Game_Data::ICON_ROLE_QUA_BTN]);
}

void UI_Role_Info_Layer::showGuide()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	if ( GUIDE_ROLE_QUA_2 == player->get_guide_id() )
	{
		Joiner_Guidance::receiveCurPosWidget(btnToRoleQuaUp);
	}
	else if ( GUIDE_LIEU_FIGHT_2 == player->get_guide_id() )
	{
		Joiner_Guidance::receiveCurPosWidget(m_img_click_head_event[1]);
	}
	
}

void UI_Role_Info_Layer::changeGuide()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	if ( GUIDE_ROLE_QUA_2 == player->get_guide_id() )
	{
		player->change_guide_id( player->get_guide_id()+1 );
	}
}
