#include "UI_HeartMethod_Quality_Up_Layer.h"
#include "UI_MainMenu_Layer.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Item_System/Item_Data.h"
#include "Item_System/Item_Mgr_Cl.h"
#include "Item_System/Item_Logic_Cl.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Common/GameMacro.h"
#include "UI_Icon_Info_Layer.h"

#include "Joiner_Guidance.h"
using namespace ui;
USING_NS_CC;
//USING_NS_CC_EXT;

UI_HeartMethod_Quality_Up_Layer::UI_HeartMethod_Quality_Up_Layer(void):
	m_HM_Quality_Up_Widget(NULL),
	m_lab_hm_name(NULL),
	m_img_head_effect(NULL),
	m_img_hm_quality_before_back(NULL),
	m_img_hm_quality_after_back(NULL),
	m_img_hm_quality_before(NULL),
	m_img_hm_quality_after(NULL),
	m_lab_role_name(NULL),
	m_img_fighting_mark(NULL),
	m_lab_quality_before_font(NULL),
	m_lab_quality_after_font(NULL),
	m_item_id(0),
	m_select_character_id(0)
{
	memset(m_img_material, 0, sizeof(m_img_material));
	memset(m_img_material_back, 0, sizeof(m_img_material_back));
	memset(m_lab_material_need_num, 0, sizeof(m_lab_material_need_num));
	memset(m_lab_quality_up_before_info, 0, sizeof(m_lab_quality_up_before_info));
	memset(m_lab_desc,0,sizeof(m_lab_desc));
	memset(m_lab_quality_up_after_info, 0, sizeof(m_lab_quality_up_after_info));
	memset(m_img_click_head_event, 0, sizeof(m_img_click_head_event));
	m_fighting_capacity = LabelAtlas::create("0123456789","pic_zhanlizhi_shuzi.png",22,33,'0');
	m_fighting_capacity->setVisible(true);

	for (int i = 0;i < Game_Data::EP_MAX;++i)
	{
		
	m_bar_item_id[i] = 0;
	}
}


UI_HeartMethod_Quality_Up_Layer::~UI_HeartMethod_Quality_Up_Layer(void)
{

}

bool UI_HeartMethod_Quality_Up_Layer::init()
{
	if( !cocos2d::Layer::init() )
	{
		return false;
	}

	m_HM_Quality_Up_Widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/XinFa_Quality_Up/XinFa_Quality_Up.ExportJson");
	addChild(m_HM_Quality_Up_Widget);
	/*********************上面的四个按钮和关闭按钮************************************/
	button_close = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"btn_close"));
	button_close->addTouchEventListener(this,toucheventselector(UI_HeartMethod_Quality_Up_Layer::buttonCloseCallback));
	//心法
	button_heart_method = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"btn_book"));
	button_heart_method->addTouchEventListener(this, toucheventselector(UI_HeartMethod_Quality_Up_Layer::buttonHeartMethodCallback));
	//合成
	button_combine = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"btn_combine"));
	button_combine->addTouchEventListener(this, toucheventselector(UI_HeartMethod_Quality_Up_Layer::buttonCombineCallback));
	//残页
	m_btn_canye=dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"btn_residual_page"));
	m_btn_canye->addTouchEventListener(this, toucheventselector(UI_HeartMethod_Quality_Up_Layer::buttonCanyeCallback));
	/*******************************************************************************/
	/**********************************左边的7个主将副将按钮和图像*****************************/
	//获取出战标记
	m_img_fighting_mark = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"img_fighting_mark"));
	//左边的显示选中的玩家
	m_img_head_effect = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"img_head_click_effect"));
	//角色栏 控件获取
	for(int i=0; i<UI_HEAD_SUM_NUM; ++i)
	{
		char imgBack[32] = {0};
		sprintf(imgBack, "img_role_head_back_%d", i);
		m_img_click_head_event[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,imgBack));
m_img_click_head_event[i]->setTag(0);
		m_img_click_head_event[i]->addTouchEventListener(this, toucheventselector(UI_HeartMethod_Quality_Up_Layer::headPhotoClickEvent));

		char imgHead[32] = {0};
		sprintf(imgHead, "img_role_head_%d", i);
		m_img_head_photo[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,imgHead));
	}
	/*****************************************************************************************/

	/********************************中间的人物装备和战力值*************************************/
	//角色名字
	m_lab_role_name=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"lab_role_name"));
	//物品栏
	char keybar[32] = {0};
	for (int i = 0;i < 6;++i)
	{
		memset(keybar, 0, sizeof(keybar));
		SPRINTF(keybar,"img_equip_%d",i+1);
		m_img_equipment_bar_back[i] = (cocos2d::ui::ImageView*)(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,keybar));
		m_img_equipment_bar_back[i]->setTouchEnabled(false);
		m_img_equipment_bar[i] = cocos2d::ui::ImageView::create();
		m_img_equipment_bar_back[i]->getParent()->addChild(m_img_equipment_bar[i]);
		m_img_equipment_bar[i]->setZOrder(m_img_equipment_bar_back[i]->getZOrder()+1);
		m_img_equipment_bar[i]->setPosition(m_img_equipment_bar_back[i]->getPosition());
m_img_equipment_bar[i]->setTag(i);
		m_img_equipment_bar[i]->addTouchEventListener(this,toucheventselector(UI_HeartMethod_Quality_Up_Layer::click_equipment_bar));
		m_img_equipment_bar[i]->setTouchEnabled(true);
	}
	//战力值
	cocos2d::ui::ImageView* fighting_capacity_title = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"Zhanli_Title"));
	if (fighting_capacity_title)
	{
		m_fighting_capacity->setAnchorPoint(Vec2(0,0.5));
		m_fighting_capacity->setZOrder(fighting_capacity_title->getZOrder() +1 );
		fighting_capacity_title->addChild(m_fighting_capacity);
	}
	m_img_equipment_select_effect=dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"m_img_equipment_select_effect"));
	m_img_equipment_select_effect->setVisible(false);
	/*****************************************************************************************/
	/********************************右边的一些控件********************************************/
	//升品前
	//心法名
	m_lab_hm_name = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"lab_xinfa_name"));
	m_lab_hm_name->setVisible(false);
	//等级
	m_lab_before_level=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"lab_before_level"));
	m_lab_before_level->setString("");
	//图标背景框
	m_img_hm_quality_before_back = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"img_level_before"));
	//图标
	m_img_hm_quality_before = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"img_level_before_icon"));
	m_img_hm_quality_before->addTouchEventListener(this, toucheventselector(UI_HeartMethod_Quality_Up_Layer::clickMaterialCallback));

	//升品后的
	//名字
	m_lab_after_name=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"lab_after_name"));
	//等级
	m_lab_after_level=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"lab_after_level"));
	//图片框
	m_img_hm_quality_after_back = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"img_level_after"));
	//图标
	m_img_hm_quality_after = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"img_level_after_icon"));
	m_img_hm_quality_after->addTouchEventListener(this, toucheventselector(UI_HeartMethod_Quality_Up_Layer::clickMaterialCallback));
	m_lab_after_name=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"lab_after_name"));
	m_lab_after_name->setString("");
	m_lab_after_level=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"lab_after_level"));
	m_lab_after_level->setString("");

	//升品所需材料背景框
	char key[32] ={0};
	for (int i=0; i<3; ++i)
	{
		memset(key, 0, sizeof(key));
		SPRINTF(key,"img_material_%d",i+1);
		m_img_material_back[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,key));

		//升品所需材料图标
		memset(key, 0, sizeof(key));
		SPRINTF(key,"img_material_icon_%d",i+1);
		m_img_material[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,key));
		m_img_material[i]->setVisible(false);
		m_img_material[i]->setTouchEnabled(true);
m_img_material[i]->setTag(i);
		m_img_material[i]->addTouchEventListener(this, toucheventselector(UI_HeartMethod_Quality_Up_Layer::clickMaterialCallback));

		//升品所需材料的数量
		memset(key, 0, sizeof(key));
		SPRINTF(key,"lab_need_num_%d",i+1);
		m_lab_material_need_num[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,key));
		m_lab_material_need_num[i]->setVisible(false);
	}

	for (int i=0; i<4; ++i)
	{
		//升品前的属性   
		memset(key, 0, sizeof(key));

		SPRINTF(key,"tel_quality_before_%d",i+1);
		m_lab_quality_up_before_info[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,key));
		m_lab_quality_up_before_info[i]->setVisible(false);

		//前面的描述
		SPRINTF(key,"lab_desc_%d",i);
		m_lab_desc[i]=dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,key));
		m_lab_desc[i]->setVisible(false);

		//升品后的属性
		memset(key, 0, sizeof(key));
		SPRINTF(key,"tel_quality_after_%d",i+1);
		m_lab_quality_up_after_info[i] = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,key));
		m_lab_quality_up_after_info[i]->setVisible(false);
	}
	//升品按钮 
	m_tbn_quality_up = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"tbn_level_up"));
	m_tbn_quality_up->addTouchEventListener(this,toucheventselector(UI_HeartMethod_Quality_Up_Layer::buttonQualityUpCallback));
	m_tbn_quality_up->setBright(true);
	/*****************************************************************************************/

	//"升品前" "升品后" 字样
	m_lab_quality_before_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"tel_before_quality"));
	m_lab_quality_before_font->setVisible(false);

	m_lab_quality_after_font = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"tel_after_quality"));
	m_lab_quality_after_font->setVisible(false);

	cocos2d::ui::Text*label_font= static_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"lab_quality_up_font"));
	const char*font_info = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_QUALITY_UP);
	label_font->setString(font_info);


	//创建物品信息显示框 function init()
	m_pLayerIconInfo = UI_Icon_Info_Layer::create();
	this->addChild(m_pLayerIconInfo,THISLAYERZORDERE,THISLAYERTAG);
	m_pLayerIconInfo->setVisible(false);

	/**************************左侧的人物**************************/
	 update_role();
	 ShowCharAvatar();
	 update();
	 /***********************************************************/
	return true;
}
void UI_HeartMethod_Quality_Up_Layer::click_equipment_bar(Ref* pSender,Widget::TouchEventType type)
{
	cocos2d::ui::ImageView* img;

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	CCLog("UI_HeartMethod_Quality_Up_Layer::click_equipment_bar");
	img=(cocos2d::ui::ImageView*)pSender;
	if( img )
	{
		int tag=img->getTag();
		this->m_item_id=m_bar_item_id[tag];
		if(m_item_id<=0)
			return ;
		m_img_equipment_select_effect->setVisible(true);
		m_img_equipment_select_effect->setPosition(m_img_equipment_bar_back[tag]->getPosition());

		update();

		changeGuide();
	}
	break;
    default:
	break;
}

}

void UI_HeartMethod_Quality_Up_Layer::ShowCharAvatar()
{
#if 0
	cocos2d::ui::ImageView* pView = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"img_lieutenant"));
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


void UI_HeartMethod_Quality_Up_Layer::headPhotoClickEvent(Ref* pSender,Widget::TouchEventType type)
{
	cocos2d::ui::ImageView* curImg ;
	int curImgTag;
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
	m_item_id=0;
	update_role(m_select_character_id);
	update();
	break;
    default:
	break;
}

}
void UI_HeartMethod_Quality_Up_Layer::update_role(int character_id)
{
	//设置 主角头像
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Player* player = (Player*)CHARACTER_MGR::instance()->get_character( role_id );
	if (!player)
	{
		return;
	}
	Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(character_id);
	if (!character)
	{
		return ;
	}

	//设置角色名字
	const char* pname = character->get_character_name();
	m_lab_role_name->setString(pname);
	//设置战力值
	m_fighting_capacity->setString(CCString::createWithFormat("%d",character->get_fighting_capacity())->getCString());

	//设置装备的心法啊
	Game_Data::Item** book_bar = character->get_book_array();
	for (int i = 0;i < Game_Data::EP_MAX;++i)
	{
		Game_Data::Item*item = book_bar[i];
		if (item)
		{
			m_bar_item_id[i] = item->id;
			update_grid_item(i,item->count,item->current_quality,item->config->icon,false);
		}
		else
		{
			m_bar_item_id[i] = 0;
			remove_grid_item(i,false);
		}
	}
}

void UI_HeartMethod_Quality_Up_Layer::setSelectBook()
{
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(role_id);
	if (!character)
	{
		return ;
	}
	//设置装备的心法啊
	Game_Data::Item** book_bar = character->get_book_array();
	//设置选中哪一个
	for (int i = 0;i < Game_Data::EP_MAX;++i)
	{
		Game_Data::Item *item = book_bar[i];
		if (item)
		{
			m_img_equipment_select_effect->setVisible(true);
			m_img_equipment_select_effect->setPosition(m_img_equipment_bar_back[i]->getPosition());
			this->m_item_id=item->id;
			update();
			break;
		}
	}
}

void UI_HeartMethod_Quality_Up_Layer::update_role()
{
	//设置 主角头像
	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	m_select_character_id = role_id;
	Player* player = (Player*)CHARACTER_MGR::instance()->get_character( role_id );
	if (!player)
	{
		return;
	}
	Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(role_id);
	if (!character)
	{
		return ;
	}
	m_img_head_effect->setPosition(m_img_click_head_event[0]->getPosition());
	

	const char* picRoleHead = ITEM_CONFIG_MGR::instance()->get_icon_path(player->get_face_mode_id());
	m_img_head_photo[0]->loadTexture(picRoleHead, UI_TEX_TYPE_PLIST);
	m_img_head_photo[0]->setVisible(true);

	const char* quality_back = DICTIONARY_CONFIG_MGR::instance()->get_charactor_quality_circle_icon(player->get_character_quality());
	m_img_click_head_event[0]->loadTexture(quality_back, UI_TEX_TYPE_PLIST);
m_img_click_head_event[0]->setTag(role_id);

	//设置角色名字
	const char* pname = character->get_character_name();
	m_lab_role_name->setString(pname);
	//设置战力值
	m_fighting_capacity->setString(CCString::createWithFormat("%d",character->get_fighting_capacity())->getCString());

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

	//设置装备的心法啊
	Game_Data::Item** book_bar = character->get_book_array();
	for (int i = 0;i < Game_Data::EP_MAX;++i)
	{
		Game_Data::Item*item = book_bar[i];
		if (item)
		{
			m_bar_item_id[i] = item->id;
			update_grid_item(i,item->count,item->current_quality,item->config->icon,false);
		}
		else
		{
			m_bar_item_id[i] = 0;
			remove_grid_item(i,false);
		}
	}
}

void UI_HeartMethod_Quality_Up_Layer::setVisible( bool visible )
{
	if(visible)
	{
		update_role();


		int player_id = Account_Data_Mgr::instance()->get_current_role_id();
		Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
		if (!player)
		{
			return ;
		}

		Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(m_select_character_id);
		if (!character)
		{
			return ;
		}
		Game_Data::Item** book_bar = character->get_book_array();
		m_item_id=0;
		for (int i = 0;i < Game_Data::EP_MAX;++i)
		{
			Game_Data::Item* item = book_bar[i];
			if (item)
			{
				m_item_id = item->id;
				break;

			}

		}
		update();
		showGuide();
		setSelectBook();
	}
	else
	{
		


		update();
		m_pLayerIconInfo->setVisible(false);
		Joiner_Guidance::hideGuide();
	}
	cocos2d::Layer::setVisible(visible);
}

void UI_HeartMethod_Quality_Up_Layer::buttonCloseCallback( Ref* pSender ,Widget::TouchEventType type)
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

void UI_HeartMethod_Quality_Up_Layer::buttonQualityUpCallback( Ref* pSender ,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	changeGuide();
	ITEM_LOGIC::instance()->book_quality_up(m_item_id);

	break;
    default:
	break;
}
}

void UI_HeartMethod_Quality_Up_Layer::buttonHeartMethodCallback( Ref* pSender ,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(false);
	UI_MainMenu_Layer::get_instance()->buttonHeartMethod(pSender,Widget::TouchEventType::ENDED);

	break;
    default:
	break;
}
}

void UI_HeartMethod_Quality_Up_Layer::buttonCombineCallback( Ref* pSender ,Widget::TouchEventType type)
{

switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	setVisible(false);
	UI_MainMenu_Layer::get_instance()->visibleHeartMethodCombine(0);

	break;
    default:
	break;
}
}

void UI_HeartMethod_Quality_Up_Layer::update()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return ;
	}

	Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(m_select_character_id);
	if (!character)
	{
		return ;
	}

	int nLevel = character->get_character_level();
	cocos2d::ui::Text* ctl = (cocos2d::ui::Text*)(Helper::seekWidgetByName(m_HM_Quality_Up_Widget,"lab_level"));
	ctl->setString(CCString::createWithFormat("LV.%d",nLevel)->getCString());
	const char* quality_back=0;
	//设置 副将头像
	for (int i = 1; i < UI_HEAD_SUM_NUM; ++i)
	{
		DeputyGeneral* general = player->get_deputy_general_by_index(i-1);
		if (general)
		{
			const char* picRoleHead = ITEM_CONFIG_MGR::instance()->get_icon_path(general->get_face_mode_id());
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


	//设置出战状态
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


    Game_Data::Item* item = ITEM_MGR::instance()->get_item(m_item_id);
    if (!item)
    {
		m_img_equipment_select_effect->setVisible(false);
		m_lab_before_level->setString("");
		m_lab_after_level->setString("");
		m_lab_hm_name->setString("");
		m_lab_after_name->setString("");


		m_img_hm_quality_before->setVisible(false);
		m_img_hm_quality_before_back->setVisible(false);


		m_lab_quality_after_font->setVisible(false);
		m_img_hm_quality_after_back->setVisible(false);


		for (int index=0;index < 4;index++)
		{
			 m_lab_quality_up_before_info[index]->setVisible(false);
			 m_lab_quality_up_after_info[index]->setVisible(false);
			 m_lab_desc[index]->setVisible(false);

		}
		for(int i=0;i<3;i++)
		{
			m_img_material_back[i]->setVisible(false);
		}
		
		m_tbn_quality_up->setBright(false);
		m_tbn_quality_up->setTouchEnabled(false);


        return;
    }
	//设置角色名字
	const char* pname = character->get_character_name();
	m_lab_role_name->setString(pname);
	//设置战力值
	m_fighting_capacity->setString(CCString::createWithFormat("%d",character->get_fighting_capacity())->getCString());

    const char* name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(item->config->name);
	
    m_lab_hm_name->setString(name);
    m_lab_hm_name->setVisible(true);


	int item_level=item->level;
	m_lab_before_level->setString(CCString::createWithFormat("Lv:%d",item_level)->getCString());
	
    m_lab_quality_before_font->setVisible(true);
	
    const char* icon = ITEM_CONFIG_MGR::instance()->get_icon_path(item->config->icon);
    m_img_hm_quality_before->loadTexture(icon,UI_TEX_TYPE_PLIST);
    m_img_hm_quality_before->setVisible(true);

    const char* back = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(item->current_quality);
    m_img_hm_quality_before_back->loadTexture(back,UI_TEX_TYPE_PLIST);
	m_img_hm_quality_before_back->setVisible(true);

    int up_quality = item->current_quality+1;
    if (up_quality < Game_Data::QT_MAX)
    {
        const char* quality_after = DICTIONARY_CONFIG_MGR::instance()->get_quality_string(up_quality);
        m_lab_quality_after_font->setVisible(true);

        m_img_hm_quality_after->loadTexture(icon,UI_TEX_TYPE_PLIST);
        m_img_hm_quality_after->setVisible(true);

        back = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(up_quality);
		m_lab_after_name->setString(name);
		m_lab_after_level->setString("Lv.1");
    }
    else
    {
        back = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(Game_Data::QT_MAX);
        m_img_hm_quality_after->setVisible(false);
        m_lab_quality_after_font->setVisible(false);
    }

   m_img_hm_quality_after_back->loadTexture(back,UI_TEX_TYPE_PLIST);
	m_img_hm_quality_after_back->setVisible(true);

    int index = 0;
    for (int i = Game_Data::EAT_HEALTH;i < MAX_ATTR_COUNT && index < 4;++i)
    {
        int before_attr = ITEM_CONFIG_MGR::instance()->get_book_attr(item->config->base_id,item->level,item->current_quality,i);
        if (before_attr > 0)
        {
            const char* attr_desc = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(i);
            m_lab_quality_up_before_info[index]->setString(CCString::createWithFormat("%d",before_attr)->getCString());
            m_lab_quality_up_before_info[index]->setVisible(true);
			m_lab_desc[index]->setString(CCString::createWithFormat("%s:",attr_desc)->getCString());
			m_lab_desc[index]->setVisible(true);
            if (up_quality < Game_Data::QT_MAX)
            {
                int after_attr = ITEM_CONFIG_MGR::instance()->get_book_attr(item->config->base_id,item->level,up_quality,i);
                m_lab_quality_up_after_info[index]->setString(CCString::createWithFormat("%d",after_attr)->getCString());
                m_lab_quality_up_after_info[index]->setVisible(true);
            }
            else
            {
                m_lab_quality_up_after_info[index]->setVisible(false);
            }

            ++index;
        }
    }
	Game_Data::Item** book_bar = character->get_book_array();
	for (int i = 0;i < Game_Data::EP_MAX;++i)
	{
		Game_Data::Item* item = book_bar[i];
		if (item)
		{
			m_bar_item_id[i] = item->id;
			update_grid_item(i,item->count,item->current_quality,item->config->icon,false);
		}
		else
		{
			m_bar_item_id[i] = 0;
			remove_grid_item(i,false);
		}
	}
    update_need_material(item->current_quality);
}

void UI_HeartMethod_Quality_Up_Layer::update_grid_item(int index,int count,int quality,int icon,bool is_bag)
{
	if(is_bag)
		return;
	
		const char* szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(icon);
		m_img_equipment_bar[index]->loadTexture(szPath,UI_TEX_TYPE_PLIST);
		m_img_equipment_bar[index]->setVisible(true);

		//根据品质，设置背景
		szPath = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(quality);
		m_img_equipment_bar_back[index]->loadTexture(szPath,UI_TEX_TYPE_PLIST);
		m_img_equipment_bar_back[index]->setVisible(true);

	
}
void UI_HeartMethod_Quality_Up_Layer::remove_grid_item(int index,bool is_bag)
{
	if(is_bag)
		return;
	m_img_equipment_bar[index]->setVisible(false);
	//还原装备的图片
	const char* szPath = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(Game_Data::QT_MAX);
	m_img_equipment_bar_back[index]->loadTexture(szPath,UI_TEX_TYPE_PLIST);
	m_img_equipment_bar_back[index]->setVisible(true);
	
}

void UI_HeartMethod_Quality_Up_Layer::update_need_material(int cur_quality)
{
	for (int i = 0; i < 3; ++i)
	{
		m_img_material[i]->setVisible(false);
		m_lab_material_need_num[i]->setVisible(false);
		const char* back = DICTIONARY_CONFIG_MGR::instance()->get_quality_icon(Game_Data::QT_MAX);
		m_img_material_back[i]->loadTexture(back,UI_TEX_TYPE_PLIST);
		m_img_material_back[i]->setVisible(true);
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
	ITEM_CONFIG_MGR::instance()->get_quality_upgrade_need_material(Game_Data::QMT_BOOK,cur_quality,ele_list);

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
					m_img_material_back[index]->setVisible(true);
					int have_count = player->get_bag_same_item_count(item_base_id);
					m_lab_material_need_num[index]->setString(CCString::createWithFormat("%d/%d",have_count,need_count)->getCString());
					if(have_count>=need_count)
					{
						m_lab_material_need_num[index]->setColor(ccc3(0,255,0));//设置为绿色
					}
					else
					{
						m_lab_material_need_num[index]->setColor(ccc3(255,0,0));//设置为红色
					}
					m_lab_material_need_num[index]->setVisible(true);
			m_img_material[index]->setTag(item_base_id);

					++index;
				}
			}
		}
	}

	Game_Data::Player* player_not_null = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(m_select_character_id));
	if (!player)
	{
		return;
	}



	Game_Data::Item* up_item = ITEM_MGR::instance()->get_item(this->m_item_id);
	if (up_item)
	{
		int item_max_level = ITEM_CONFIG_MGR::instance()->get_book_max_level(up_item->config->base_id,up_item->current_quality);
		if (up_item->level< item_max_level)
		{
			m_tbn_quality_up->setBright(false);
			m_tbn_quality_up->setTouchEnabled(false);
			
		}
		else
		{
			m_tbn_quality_up->setBright(true);
			m_tbn_quality_up->setTouchEnabled(true);
		}
	}
}

void UI_HeartMethod_Quality_Up_Layer::clickMaterialCallback( Ref* pSender ,Widget::TouchEventType type)
{
	    std::vector<uint64> para;
		cocos2d::ui::ImageView* curClickImg;
		Game_Data::Item* item;
		Game_Data::Item_Config* config;
		int curImgTag;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	curClickImg = dynamic_cast<cocos2d::ui::ImageView*>(pSender);
	curImgTag = curClickImg->getTag();
	if (curImgTag == 0)
	{
		return;
	}

	item = ITEM_MGR::instance()->get_item(m_item_id);
	if (!item)
	{
		return;
	}


    para.push_back(m_item_id);
    para.push_back(Game_Data::QMT_BOOK);
    m_pLayerIconInfo->set_param(para);

	config = ITEM_CONFIG_MGR::instance()->get_item_config(curImgTag);
	m_pLayerIconInfo->showButton(curImgTag, config->icon, config->name,1,config->quality,TIPS_STYLE_FINDWAY);
	m_pLayerIconInfo->setVisible(true);

	break;
    default:
	break;
}

}

void UI_HeartMethod_Quality_Up_Layer::buttonCanyeCallback( Ref* pSender ,Widget::TouchEventType type)
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

void UI_HeartMethod_Quality_Up_Layer::showGuide()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	if( GUIDE_XF_QUA_UP_STEP_3 == player->get_guide_id() )
	{
		Joiner_Guidance::receiveCurPosWidget(m_img_equipment_bar_back[0]);
	}
	else if ( GUIDE_XF_QUA_UP_STEP_4 == player->get_guide_id() )
	{
		Joiner_Guidance::receiveCurPosWidget(m_tbn_quality_up);
	}
}

void UI_HeartMethod_Quality_Up_Layer::changeGuide()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	if( GUIDE_XF_QUA_UP_STEP_3 == player->get_guide_id() )
	{
		player->change_guide_id( player->get_guide_id()+1 );
		showGuide();
	}

	if( GUIDE_XF_QUA_UP_STEP_4 == player->get_guide_id() )
	{
		player->change_guide_id( player->get_guide_id()+3 );
		Joiner_Guidance::showGuide();
	}
}
