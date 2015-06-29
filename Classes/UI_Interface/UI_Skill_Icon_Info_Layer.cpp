#include "UI_Skill_Icon_Info_Layer.h"

#include "Item_System/Item_Desc_Config_Mgr.h"

#include "Character_System/Character_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Player_Config_Mgr.h"
#include "Player_Account/Account_Data_Mgr.h"

#include "Game_Interface/game_content_interface.h"
#include "Common/GameDefine.h"
#include "Joiner_Guidance.h"

using namespace Game_Data;

using namespace ui;
UI_Skill_Icon_Info_Layer::UI_Skill_Icon_Info_Layer(void):
	m_pWidget(NULL),
	m_pImgCurSkillTextureBack(NULL),
	m_pImgCurSkillTexture(NULL),
	m_pLabSkillNameFont(NULL),		
	m_pLabSkillName(NULL),
	m_pLabCurSkillLevelFont(NULL),	
	m_pLabCurSkillLevel(NULL),
	m_pLabSkillDescFont(NULL),
	m_pTeaSkillDesc(NULL),
	m_pLabReleaseSkillOrderFont(NULL),
	m_pLabReleaseSkillPromptFont(NULL),
	m_pLabSkillLevelFont(NULL),
	m_pLabBeforeSkillUpLevel(NULL),
	m_pLabAfterSkillUpLebel(NULL),
	m_pLabHarmFont(NULL),
	m_pBeforeHarmNum(NULL),
	m_pAfterHarmNum(NULL),
	m_pLabNeedLevelFont(NULL),	
	m_pLabNeedLevel(NULL),
	m_pLabNeedMoneyFont(NULL),	
	m_pLabNeedMoney(NULL),
	m_pBtnLevelUp(NULL),
	m_pBtnLevelUpFont(NULL),
	m_select_skill_id(0),
	m_select_character_id(0)
{
	memset(m_pImgOrderPic, 0, sizeof(m_pImgOrderPic));
	memset(m_pImgArrow, 0, sizeof(m_pImgArrow));
}

UI_Skill_Icon_Info_Layer::~UI_Skill_Icon_Info_Layer(void)
{
}

bool UI_Skill_Icon_Info_Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF( !cocos2d::Layer::init() );

		m_pWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Skill_Icon_Info/Skill_Icon_Info.ExportJson");
		m_pWidget->setVisible(true);
		addChild(m_pWidget);

		initComponent();

		bRet = true;
	} while (0);

	return bRet;
}

void UI_Skill_Icon_Info_Layer::setVisible( bool visible )
{
	if (visible)
	{
		showGuide();
	}
	else
	{
		Joiner_Guidance::hideGuide();
	}
	cocos2d::Layer::setVisible(visible);
}

void UI_Skill_Icon_Info_Layer::showGuide()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if(!player) 
	{
		return;
	}
	if( GUIDE_SKILL_STEP_3 == player->get_guide_id() )
	{
		Joiner_Guidance::receiveCurPosWidget(m_pBtnLevelUp);
	}
}

void UI_Skill_Icon_Info_Layer::update()
{
	showSelectSkillInfo();
}

void UI_Skill_Icon_Info_Layer::initComponent()
{
	m_pImgCurSkillTextureBack = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget,"img_skill_inco_back"));

	m_pImgCurSkillTexture = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget,"img_skill_inco"));

	m_pLabSkillNameFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_skill_name_font"));
	const char* szNameFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SKILL_CURRENT_NAME);
	m_pLabSkillNameFont->setString(szNameFont);

	m_pLabSkillName = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_skill_name"));
	m_pLabSkillName->setString("");

	m_pLabCurSkillLevelFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_cur_level_font"));
	const char* szCurLevelFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SKILL_CURRENT_LEVEL);
	m_pLabCurSkillLevelFont->setString(szCurLevelFont);

	m_pLabCurSkillLevel = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_skill_level"));
	m_pLabCurSkillLevel->setString("");

	m_pLabSkillDescFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_skill_desc_font"));
	const char* szDescFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SKILL_CURRENT_DESC);
	m_pLabSkillDescFont->setString(szDescFont);

	m_pTeaSkillDesc = dynamic_cast<cocos2d::ui::TextField*>(Helper::seekWidgetByName(m_pWidget,"tea_skill_desc"));
	m_pTeaSkillDesc->setText("");

	m_pLabReleaseSkillOrderFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_skill_use_style"));
	const char* szOrderFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SKILL_RELEASE_METHOD);
	m_pLabReleaseSkillOrderFont->setString(szOrderFont);

	m_pLabReleaseSkillPromptFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_excu_order"));
	const char* szReleaseFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SKILL_RELEASE_PROMPT);
	m_pLabReleaseSkillPromptFont->setString(szReleaseFont);

	char key[32] = {0};
	for (int i = 0; i < ICON_NUM; i++)
	{
		memset(key, 0, sizeof(key));
		sprintf(key, "img_button_%d", i);
		m_pImgOrderPic[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget,key));

		if(i<(ICON_NUM-1))
		{
			memset(key, 0, sizeof(key));
			sprintf(key, "img_arrow_%d", i);
			m_pImgArrow[i] = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pWidget,key));
		}
	}

	m_pLabSkillLevelFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_level_font"));
	const char* szLevelFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SKILL_LEVEL);
	m_pLabSkillLevelFont->setString(szLevelFont);

	m_pLabBeforeSkillUpLevel = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_level_front"));
	m_pLabBeforeSkillUpLevel->setString("");

	m_pLabAfterSkillUpLebel = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_level_rear"));
	m_pLabAfterSkillUpLebel->setString("");

	m_pLabHarmFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_harm_font"));
	const char* szHarmFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SKILL_CURRENT_HARM);
	m_pLabHarmFont->setString(szHarmFont);

	m_pBeforeHarmNum = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_harm_front"));
	m_pBeforeHarmNum->setString("");

	m_pAfterHarmNum = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_harm_rear"));
	m_pAfterHarmNum->setString("");

	m_pLabNeedLevelFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_need_level_font"));
	const char* szNeedLevelFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SKILL_NEED_LEVEL);
	m_pLabNeedLevelFont->setString(szNeedLevelFont);

	m_pLabNeedLevel = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_need_level"));
	m_pLabNeedLevel->setString("");

	m_pLabNeedMoneyFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_need_money_font"));
	const char* szNeedMoneyFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SKILL_NEED_MONEY_FOR_LEVEL_UP);
	m_pLabNeedMoneyFont->setString(szNeedMoneyFont);

	m_pLabNeedMoney = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_need_money"));
	m_pLabNeedMoney->setString("");

	m_pBtnLevelUp = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget,"btn_level_up"));
	m_pBtnLevelUp->addTouchEventListener(this, toucheventselector(UI_Skill_Icon_Info_Layer::buttonLevelUpCallback));

	m_pBtnLevelUpFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pWidget,"lab_level_up_font"));
	const char* szLevelUpFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_LEVEL_UP);
	m_pBtnLevelUpFont->setString(szLevelUpFont);

	m_pBtnClose = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pWidget,"btn_close"));
	m_pBtnClose->addTouchEventListener(this, toucheventselector(UI_Skill_Icon_Info_Layer::buttonCloseCallback));
}

//升级时调用的刷新
void UI_Skill_Icon_Info_Layer::refreshUI()
{
	m_pLabSkillName->setString("");
	m_pLabCurSkillLevel->setString("");
	m_pTeaSkillDesc->setText("");
	m_pLabBeforeSkillUpLevel->setString("");
	m_pLabAfterSkillUpLebel->setString("");
	m_pBeforeHarmNum->setString("");
	m_pAfterHarmNum->setString("");
	m_pLabNeedLevel->setString("");
	m_pLabNeedMoney->setString("");
	m_pLabNeedLevelFont->setString("");
	m_pLabNeedMoneyFont->setString("");

}

void UI_Skill_Icon_Info_Layer::buttonLevelUpCallback( Ref* pSender,Widget::TouchEventType type )
{
int role_id;
Game_Data::Player* player;
Character* character;
Character_Skill* skill;
int need_gold ;
int self_gold;
std::vector<uint64> para;
Technical_Data* technical ;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	if ( m_select_skill_id < 0 )
		return;

	role_id = Account_Data_Mgr::instance()->get_current_role_id();
	player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(role_id));
	CC_ASSERT(player);

	character = CHARACTER_MGR::instance()->get_character( m_select_character_id );
	CC_ASSERT(character);

	skill = character->get_skill_by_index(m_select_skill_id);
	technical = TECHNICAL_MGR::instance()->GetTechnicalData(skill->skill_id);
	CC_ASSERT(skill && technical);

	/*if(skill->skill_level >= technical->levelup_max)
	{
		DICTIONARY_CONFIG_MGR::instance()->show_alert(SKILL_WAIT_FOR_OPEN);
		return;
	}

	if(character->get_character_level()<skill->skill_level*10)
	{
		DICTIONARY_CONFIG_MGR::instance()->show_alert(SKILL_NOT_REACH_REQUIRE);
		return;
	}

	need_gold = technical->learn_base_money + technical->learn_level_money * (skill->skill_level - 1);
	self_gold = player->get_gold();
	if ( self_gold < need_gold )
	{
		DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_GOLD_COIN);
		return;
	}*/

	para.push_back(skill->skill_id);
	para.push_back(m_select_character_id);
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_uplevel_skill", para);

	if( GUIDE_SKILL_STEP_3 == player->get_guide_id() )
	{
		player->change_guide_id(player->get_guide_id()+2);
		Joiner_Guidance::hideGuide();
	}
	break;
    default:
	break;
}

}

void UI_Skill_Icon_Info_Layer::buttonCloseCallback( Ref* pSender,Widget::TouchEventType type )
{
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	Joiner_Guidance::hideGuide();
	setVisible(false);

	break;
    default:
	break;
}
}

void UI_Skill_Icon_Info_Layer::showSelectSkillInfo( int skillId, int characterId )
{
	if( -1 != skillId )
	{
		m_select_skill_id = skillId;
	}
	if( -1 != characterId )
	{
		m_select_character_id = characterId;
	}

	refreshUI();

	Character* character = CHARACTER_MGR::instance()->get_character(m_select_character_id);
	if( !character )
	{
		return;
	}
	Character_Skill* skill = character->get_skill_by_index(m_select_skill_id);
	const Technical_Data* pTechData = TECHNICAL_MGR::instance()->GetTechnicalData(skill->skill_id);
	CC_ASSERT(pTechData);
	const char* szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(pTechData->icon_index);

	if( m_select_skill_id < 5 || 10 == m_select_skill_id)
	{
		const char* quality_back = DICTIONARY_CONFIG_MGR::instance()->get_skill_circle_icon(character->get_character_quality());
		m_pImgCurSkillTextureBack->loadTexture(quality_back, UI_TEX_TYPE_PLIST);
	}
	else
	{
		const char* quality_back = DICTIONARY_CONFIG_MGR::instance()->get_skill_square_icon(character->get_character_quality());
		m_pImgCurSkillTextureBack->loadTexture(quality_back, UI_TEX_TYPE_PLIST);
	}

	//技能图标
 	m_pImgCurSkillTexture->loadTexture(szPath,UI_TEX_TYPE_PLIST);
	
	const Technical_Data* pData = TECHNICAL_MGR::instance()->GetTechnicalData(skill->skill_id);

	showSkillReleaseOrder( pData );

	//技能等级
	/*m_pLabCurSkillLevel->setString(CCString::createWithFormat("LV.%d",skill->skill_level)->getCString());

	if (pData)
	{
		//技能名称
		const char* item_name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(pData->name_index);
		m_pLabSkillName->setString(item_name);

		//升级前等级
		m_pLabBeforeSkillUpLevel->setString(CCString::createWithFormat("LV.%d",skill->skill_level)->getCString());

		//升级后属性设置
		if( skill->skill_level < pData->levelup_max )
		{
			//升级后等级
			m_pLabAfterSkillUpLebel->setString(CCString::createWithFormat("LV.%d",skill->skill_level+1)->getCString());

			//升级后的伤害值
			int afterDamageNum = pData->skill_base + (skill->skill_level)*pData->upgrade_skill_grow;
			m_pAfterHarmNum->setString(CCString::createWithFormat("%d",afterDamageNum)->getCString());

			//升级等级需求显示
			const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SKILL_NEED_LEVEL);
			CCString* intToCString = CCString::createWithFormat("%d",(skill->skill_level)*10);
			CCString* getInfo = CCString::createWithFormat(szString,intToCString->getCString());
			m_pLabNeedLevelFont->setString(getInfo->getCString());

			//升级需要金钱数量 (金钱计算： 金币 = 金币基础+（等级-1）*金币成长)
			szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SKILL_NEED_MONEY_FOR_LEVEL_UP);
			int moneyNum = pData->learn_base_money + (skill->skill_level - 1) * pData->learn_level_money; 
			intToCString = CCString::createWithFormat("%d", moneyNum);
			getInfo = CCString::createWithFormat(szString, intToCString->getCString());
			m_pLabNeedMoneyFont->setString(getInfo->getCString());
		}
		else
		{
			const char* waitOpen = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SKILL_WAIT_FOR_OPEN);
			m_pLabAfterSkillUpLebel->setString(waitOpen);

			m_pAfterHarmNum->setString("0");

			//升级等级需求显示
			const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SKILL_NEED_LEVEL);
			CCString* getInfo = CCString::createWithFormat(szString,"0");
			m_pLabNeedLevelFont->setString(getInfo->getCString());

			//升级需要金钱数量 (金钱计算： 金币 = 金币基础+（等级-1）*金币成长)
			szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SKILL_NEED_MONEY_FOR_LEVEL_UP);
			getInfo = CCString::createWithFormat(szString, "0");
			m_pLabNeedMoneyFont->setString(getInfo->getCString());
		}

		//升级前的伤害值  (计算伤害公式 ： 伤害=招式基础 +（等级）* 招式成长 )
		int beforeDamageNum = pData->skill_base + (skill->skill_level-1)*pData->upgrade_skill_grow;
		m_pBeforeHarmNum->setString(CCString::createWithFormat("%d",beforeDamageNum)->getCString());

		//技能描述
		const char* item_describe = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(pData->desc_index); 
		m_pTeaSkillDesc->setText(item_describe);
	}*/

}

void UI_Skill_Icon_Info_Layer::showSkillReleaseOrder( const Technical_Data* &pData )
{

	for (int i=0; i<ICON_NUM; ++i)
	{
		m_pImgOrderPic[i]->setVisible(false);
		if(i<ICON_NUM-1)
		{
			m_pImgArrow[i]->setVisible(false);
		}
	}
	//技能出招顺序 示意图
	game_element_list_t gl = pData->get_content().get_element();
	game_element_list_t::iterator itg;
	int index_num = 0;
	vector<uint> para;
	
	for ( itg=gl.begin(); itg!=gl.end(); ++itg )
	{
		para.clear();
		Game_Data::Game_Element& element = (*itg);
		if (strcmp(element.get_command(), "skill") == 0)
		{
			element.get_para_list_in_vector(para);
			if(para.size()>0)
			{
				for (unsigned int i=0; i<para.size(); ++i)
				{
					if(0 == para[i])
					{
						m_pImgOrderPic[i]->loadTexture("Button_A_little.png", UI_TEX_TYPE_PLIST);
						m_pImgOrderPic[i]->setVisible(true);
					}
					else if(1 == para[i])
					{
						m_pImgOrderPic[i]->loadTexture("Button_B_little.png", UI_TEX_TYPE_PLIST);
						m_pImgOrderPic[i]->setVisible(true);
					}
					else if( 2 == para[i])
					{
						m_pImgOrderPic[i]->loadTexture("");
					}
					else
					{
						m_pImgOrderPic[i]->loadTexture("");
					}

					if(i<para.size()-1)
					{
						m_pImgArrow[i]->setVisible(true);
					}
				}
			}
		}
	}
}


