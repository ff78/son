#include "UI_Fate_Layer.h"

#include "Character_System/Player.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Acupoint_System/Acupoint_Config_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Acupoint_System/Acupoint_Mgr_Cl.h"
#include "Acupoint_System/Acupoint_Logic_Cl.h"
#include "Cool_Time_System/Cool_Time_Mgr_Cl.h"
#include "Cool_Time_System/Cool_Time_Logic_Cl.h"
//#include "Effect_Cfg_Data_Mgr.h"

#include "UI_ModalDialogue_Layer.h"
#include "UI_MainMenu_Layer.h"
#include "Joiner_Guidance.h"
using namespace ui;
USING_NS_CC;
//USING_NS_CC_EXT;

using namespace Game_Data;

const char* acupointPicBack[] = 
{
	"ui/Fate_Layer/fate_back_0.png",
	"ui/Fate_Layer/fate_back_1.png",
};

const char* acupointPic[] = 
{
	"ui/Fate_Layer/fate_0.png",
	"ui/Fate_Layer/fate_1.png",
	"ui/Fate_Layer/fate_2.png",
	"ui/Fate_Layer/fate_3.png",
	"ui/Fate_Layer/fate_4.png",
	"ui/Fate_Layer/fate_5.png",
	"ui/Fate_Layer/fate_6.png",
	"ui/Fate_Layer/fate_7.png",
};

UI_Fate_Layer::UI_Fate_Layer(void) :
	m_pRootWidget(NULL),
	m_pImgSecondBack(NULL),
	pageView(NULL),
	m_pLabAcuTitleName(NULL),
	m_pLabChongNum(NULL),
	m_pLabAcupointNameTitle(NULL),
	m_pLabBonusToAttr(NULL),
	m_pLabSuccessRate(NULL),
	m_pLabAdditionNum(NULL),
	m_pLabCurGain(NULL),
	m_pLabAllOpenGive(NULL),
	m_pLabCurChong(NULL),
	m_pLabConsumptionRepu(NULL),
	m_pLabHaveRepu(NULL),
	m_pLabConsumptionGold(NULL),
	m_pLabHaveGold(NULL),
	m_pLabCoolTimeFont(NULL),
	m_pLabCountdown(NULL),
	m_pBtnFont(NULL),
	m_pImgLeftMove(NULL),
	m_pImgRightMove(NULL),
    m_select_type(0)
{
	memset(m_pImgAcupoint, 0, sizeof(m_pImgAcupoint));
	memset(m_pLabAcupointName, 0, sizeof(m_pLabAcupointName));
	memset(m_pimg_effect,0,sizeof(m_pimg_effect));
}


UI_Fate_Layer::~UI_Fate_Layer(void)
{
}

bool UI_Fate_Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());

		m_pRootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Fate_Layer/Fate_Layer.ExportJson");
		this->addChild(m_pRootWidget);

        m_pBtnChongXue = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pRootWidget,"btn_acupoint"));
        m_pBtnChongXue->addTouchEventListener(this, toucheventselector(UI_Fate_Layer::btnOpenAcupointCallback));

		m_pImgLeftMove = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pRootWidget,"img_left_move"));
		m_pImgLeftMove->addTouchEventListener(this, toucheventselector(UI_Fate_Layer::btnLeftCallback));

		m_pImgRightMove = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pRootWidget,"img_right_move"));
		m_pImgRightMove->addTouchEventListener(this, toucheventselector(UI_Fate_Layer::btnRightCallback));

		initComponent();
		initWidget();

		bRet = true;
	} while (0);

	return bRet;
}

void UI_Fate_Layer::setVisible( bool visible )
{
	cocos2d::Layer::setVisible(visible);
	if (visible)
	{
		Joiner_Guidance::hideGuide();
        update();
		showGuide();
	}
	else
	{
		Joiner_Guidance::hideGuide();
	}
}

void UI_Fate_Layer::initComponent()
{
	cocos2d::ui::Button* btnClose = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pRootWidget,"btn_close"));
	btnClose->addTouchEventListener(this, toucheventselector(UI_Fate_Layer::btnCloseCallback));

	m_pImgSecondBack = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pRootWidget,"img_second_back"));
	cocos2d::ui::PageView* pageWidget = createPageView();
	pageWidget->setPosition(Vec2(-261.0f, -186.5f));
	m_pImgSecondBack->addChild(pageWidget);

}

void UI_Fate_Layer::btnCloseCallback( Ref* pSender ,Widget::TouchEventType type)
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


cocos2d::ui::PageView* UI_Fate_Layer::createPageView()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return NULL;
	}

	pageView = cocos2d::ui::PageView::create();
	pageView->setTouchEnabled(true);
	pageView->setSize(Size(522.f, 373.f));

	acupoint_config* config = NULL; 
	for (int i = 0; i < PAGE_NUM; ++i)
	{
		cocos2d::ui::Layout* layout = cocos2d::ui::Layout::create();
		layout->setSize(Size(522.f, 373.f));

		//穴位背景
		cocos2d::ui::ImageView* imageView = cocos2d::ui::ImageView::create();
		imageView->setTouchEnabled(true);
		if( 1 == player->get_sex() )
			imageView->loadTexture(acupointPicBack[0]);
		else
			imageView->loadTexture(acupointPicBack[1]);
		imageView->setPosition(Vec2(layout->getSize().width/2, layout->getSize().height/2));
		layout->addChild(imageView);

		//页码显示
		cocos2d::ui::Text* label = cocos2d::ui::Text::create();
		label->setString(CCString::createWithFormat("page %d", (i + 1))->getCString());
		label->setFontName("page view");
label->setFontSize(30);
		label->setColor(ccc3(255, 0, 0));
		label->setPosition(Vec2(layout->getSize().width / 2, layout->getSize().height / 2));
		layout->addChild(label);
        label->setVisible(false);

		//穴位图
		cocos2d::ui::ImageView* sprite = cocos2d::ui::ImageView::create();
		sprite->setTouchEnabled(true);
		sprite->loadTexture(acupointPic[i]);
		sprite->setPosition(Vec2(imageView->getContentSize().width/2, imageView->getContentSize().height/2));
sprite->setTag(i);
		layout->addChild(sprite);

		for(int j=0; j<EACH_PAGE_ACUPOINT_NUM; ++j)
		{
			config = ACUPOINT_CONFIG_MGR::instance()->get_acupoint_config(i,j);
			m_pImgAcupoint[i][j] = cocos2d::ui::ImageView::create();
			m_pImgAcupoint[i][j]->setPosition(Vec2(config->pos_x_ - sprite->getContentSize().width/2,  sprite->getContentSize().height/2 - config->pos_y_));
			sprite->addChild(m_pImgAcupoint[i][j]);
            m_pImgAcupoint[i][j]->setVisible(false);

			m_pLabAcupointName[i][j] = cocos2d::ui::Text::create();
			m_pLabAcupointName[i][j]->setFontSize(20);
			m_pLabAcupointName[i][j]->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(config->name_));
			m_pLabAcupointName[i][j]->setPosition(Vec2(config->name_x_ - sprite->getContentSize().width/2,  sprite->getContentSize().height/2 - config->name_y_));
			sprite->addChild(m_pLabAcupointName[i][j]);
            m_pLabAcupointName[i][j]->setColor(ccc3(157, 83, 18));
		}

		//特效的UIImageView
		m_pimg_effect[i]=cocos2d::ui::ImageView::create();
		m_pimg_effect[i]->setPosition(Vec2(0,0));
		sprite->addChild(m_pimg_effect[i]);
		m_pimg_effect[i]->setVisible(false);
		pageView->addPage(layout);
	}

	pageView->addEventListenerPageView(this, pagevieweventselector(UI_Fate_Layer::pageViewEvent));

	return pageView;
}

void UI_Fate_Layer::pageSet( Ref* pSender,Widget::TouchEventType type )
{
	pageView->scrollToPage(1);
	int index = pageView->getCurPageIndex();
}

void UI_Fate_Layer::btnOpenAcupointCallback( Ref* pSender ,Widget::TouchEventType type)
{
bool is_open ;
int cost;
Game_Data::Cool_Time* cool_time ;

const char* szString;
const char* purchaseInfo ;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
    is_open = false;
    cool_time = COOL_TIME_MGR::instance()->get_cool_time(CTT_OPEN_ACUPOINT);
    if (cool_time)
    {
        if (cool_time->cool_ == 0)
        {
            is_open = true;
        } 
    }
    else
    {
        is_open = true;
    }

    if (is_open)
    {
        ACUPOINT_LOGIC::instance()->open_acupoint(m_select_type);
		changeGuide();
    } 
    else
    {
        cost = COOL_TIME_MGR::instance()->get_clean_cool_time_cost(cool_time);
        szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_CLEAN_COST);
       purchaseInfo = CCString::createWithFormat(szString,cost)->getCString();
        UI_ModalDialogue_Layer::DoModal("",purchaseInfo,UI_ModalDialogue_Layer::DT_YES_NO,[]()
        {
            COOL_TIME_LOGIC::instance()->clean_cool_time(CTT_OPEN_ACUPOINT);
        }
        );
    }
	break;
    default:
	break;
}

}

void UI_Fate_Layer::pageViewEvent(Ref *pSender, cocos2d::ui::PageViewEventType type)
{
#if 1
	switch (type)
	{
	case PAGEVIEW_EVENT_TURNING:
		{
			cocos2d::ui::PageView* pageView = dynamic_cast<cocos2d::ui::PageView*>(pSender);
			m_select_type = pageView->getCurPageIndex();
            update_attr();
		}
		break;

	default:
		break;
	}
#endif
}

void UI_Fate_Layer::initWidget()
{
	m_pLabAcupointNameFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_acupoint_name"));
	m_pLabAcupointNameFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(FATE_ACUPOINT_NAME));

	m_pLabSuccessRateFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_success_percentage"));
	m_pLabSuccessRateFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(FATE_ACUPOINT_SUC_RATE));

	m_pLabAddAttrFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_add_attr"));
	m_pLabAddAttrFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(FATE_ACUPOINT_ADD_ATTR));

	m_pLabNowGainFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_cur_gain"));
	m_pLabNowGainFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(FATE_ACUPOINT_NOW_GAIN));

	m_pLabAllOpenGiftFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_all_open_gift"));
	m_pLabAllOpenGiftFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(FATE_ACUPOINT_ALL_GIFT));

	m_pLabXiuLianNumFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_chong"));
	m_pLabXiuLianNumFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(FATE_ACUPOINT_XIU_NUM));

	m_pLabHasRepuFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_have_reputation"));
	m_pLabHasRepuFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(FATE_ACUPOINT_HAS_REP));

	m_pLabNeedRepuFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_reduce_reputation"));
	m_pLabNeedRepuFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(FATE_ACUPOINT_NEED_REP));

	m_pLabHasMoneyFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_have_gold_coin"));
	m_pLabHasMoneyFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(FATE_ACUPOINT_HAS_MON));

	m_pLabNeedMoneyFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_reduce_gold_coin"));
	m_pLabNeedMoneyFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(FATE_ACUPOINT_NEED_MON));

	m_pLabCoolTimeFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_cool_time"));
	m_pLabCoolTimeFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(FATE_ACUPOINT_COOL_TIME));
	m_pLabCoolTimeFont->setVisible(false);

	//(以下 cocos2d::ui::Text 内容设置 均是 obj->setString)
	//穴位重数
	m_pLabAcuTitleName = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_chong_num"));
	m_pLabAcuTitleName->setString("");
	//第 X 重
	m_pLabChongNum = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_acupoint_title_name"));
	m_pLabChongNum->setString("");
	//穴位名称
	m_pLabAcupointNameTitle = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_acupoint_name_vision"));
    m_pLabAcupointNameTitle->setString("");
	//加成属性
	m_pLabBonusToAttr = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_add_attr_vision"));
    m_pLabBonusToAttr->setString("");
	//成功率
	m_pLabSuccessRate = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_success_percentage_vision"));
    m_pLabSuccessRate->setString("");
	//成功率加成
	m_pLabAdditionNum = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_addition_num"));
	m_pLabAdditionNum->setString("");
	//现已获得
	m_pLabCurGain = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_cur_gain_vision"));
    m_pLabCurGain->setString("");
	//全通赠送
	m_pLabAllOpenGive = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_all_open_gift_vision"));
    m_pLabAllOpenGive->setString("");
	//修炼重数
	m_pLabCurChong = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_chong_vision"));
    m_pLabCurChong->setString("");
	//消耗声望
	m_pLabConsumptionRepu = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_reduce_reputation_vision"));
    m_pLabConsumptionRepu->setString("");
	//拥有声望
	m_pLabHaveRepu = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_have_reputation_vision"));
    m_pLabHaveRepu->setString("");
	//消耗银两
	m_pLabConsumptionGold = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_reduce_gold_coin_vision"));
    m_pLabConsumptionGold->setString("");
	//拥有银两
	m_pLabHaveGold = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_have_gold_coin_vision"));
    m_pLabHaveGold->setString("");

	//时间倒计时
	m_pLabCountdown = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_countdown"));
    m_pLabCountdown->setVisible(false);
	//按钮字体
	m_pBtnFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_acupoint_font"));
}

void UI_Fate_Layer::update()
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return;
    }

    Acupoint_Map* acupoint_map = ACUPOINT_MGR::instance()->get_acupoint_map();
    Acupoint* acupoint = NULL;
    Acupoint_Map_Iter iter = acupoint_map->begin();
	for(int i=0;i<8;i++)
    {
		Acupoint_Map_Iter iter=acupoint_map->find(i);
		if(iter!=acupoint_map->end())
		{
			acupoint = iter->second;
			if (acupoint)
			{
				const char *szPath = DICTIONARY_CONFIG_MGR::instance()->get_vein_level_icon(acupoint->level_);
				if (acupoint->level_ == 0)
				{
					for(int i=0; i<EACH_PAGE_ACUPOINT_NUM; ++i)
					{
						if (i<(acupoint->pos_+1))
						{
							m_pImgAcupoint[acupoint->type_][i]->loadTexture(szPath,UI_TEX_TYPE_PLIST);
							m_pImgAcupoint[acupoint->type_][i]->setVisible(true);
						}
					}
				} 
				else
				{
					const char* last = DICTIONARY_CONFIG_MGR::instance()->get_vein_level_icon(acupoint->level_-1);
					for(int i=0; i<EACH_PAGE_ACUPOINT_NUM; ++i)
					{
						if (i<(acupoint->pos_+1))
						{
							m_pImgAcupoint[acupoint->type_][i]->loadTexture(szPath,UI_TEX_TYPE_PLIST);
						}
						else
						{
							m_pImgAcupoint[acupoint->type_][i]->loadTexture(last,UI_TEX_TYPE_PLIST);
						}

						m_pImgAcupoint[acupoint->type_][i]->setVisible(true);
					}
				}
			
				m_pimg_effect[acupoint->type_]->getVirtualRenderer()->stopAllActions();
				m_pimg_effect[acupoint->type_]->setVisible(false);
				if(acupoint->level_<5)  //是否可以充穴
				{
					if(acupoint->pos_>=24)
					{
						//第一个闪
						m_pimg_effect[acupoint->type_]->setVisible(true);
						m_pimg_effect[acupoint->type_]->setPosition(m_pImgAcupoint[acupoint->type_][0]->getPosition());
					//	Effect_Cfg_Data_Mgr::instance()->get_effect_without_position((cocos2d::Sprite*)(m_pimg_effect[acupoint->type_]->getVirtualRenderer()),getEffectId(acupoint->level_+1));
					}
					else
					{
						//下一个闪
						m_pimg_effect[acupoint->type_]->setVisible(true);
						m_pimg_effect[acupoint->type_]->setPosition(m_pImgAcupoint[acupoint->type_][acupoint->pos_+1]->getPosition());
					//	Effect_Cfg_Data_Mgr::instance()->get_effect_without_position((cocos2d::Sprite*)(m_pimg_effect[acupoint->type_]->getVirtualRenderer()),getEffectId(acupoint->level_));
					}
				}
			}
		}
		else
		{
			Game_Data::vein_config* config_vein = ACUPOINT_CONFIG_MGR::instance()->get_vein_config(i);
			CCAssert(config_vein,"config_vein cann't be null");
			
			if (config_vein->level_data_[0].open_level_ < player->get_character_level())
			{
				//第一个闪
				m_pimg_effect[i]->setVisible(true);
				m_pimg_effect[i]->setPosition(m_pImgAcupoint[i][0]->getPosition());
				//Effect_Cfg_Data_Mgr::instance()->get_effect_without_position((cocos2d::Sprite*)(m_pimg_effect[i]->getVirtualRenderer()),getEffectId(0));
			}

			
		}
	}

    m_pLabHaveRepu->setString(CCString::createWithFormat("%d",player->get_prestige())->getCString());
    m_pLabHaveGold->setString(CCString::createWithFormat("%d",player->get_gold())->getCString());

    update_attr();
    update_time();
}
string UI_Fate_Layer::getEffectId(int level)
{
	string ret="";
	switch(level)
	{
	case 0:
		ret="3008";
		break;
	case 1:
		ret="3009";
		break;
	case 2:
		ret="3010";
		break;
	case 3:
		ret="3011";
		break;
	case 4:
		ret="3012";
		break;
	case 5:
		ret="3013";
		break;
	}
	return ret;
}
void UI_Fate_Layer::update_attr()
{
    Game_Data::vein_config* config_vein = ACUPOINT_CONFIG_MGR::instance()->get_vein_config(m_select_type);
    if (!config_vein)
    {
        return;
    }
    bool is_max = false;
    int pos = 0;
    int level = 0;
    int rate = 0;
    Game_Data::acupoint_config* config_acupoint = NULL;
    Game_Data::Acupoint* acupoint = ACUPOINT_MGR::instance()->get_acupoint(m_select_type);
    if (acupoint)
    {
        if (acupoint->pos_ == (ACUPOINT_POS_MAX-1))
        {
            if (acupoint->level_ == (VEIN_LEVEL_MAX-1))
            {
                level = acupoint->level_;
                pos = acupoint->pos_;
                is_max = true;
            }
            else
            {
                level = acupoint->level_+1;
            }
        }
        else
        {
            level = acupoint->level_;
            pos = acupoint->pos_+1;
        }

        rate = acupoint->rate_;
    }
    else
    { 
        /*if (config_vein->level_data_[0].open_level_ > player->get_character_level())
        {   
            return;
        }*/
    }

    config_acupoint = ACUPOINT_CONFIG_MGR::instance()->get_acupoint_config(m_select_type,pos);
    if (!config_acupoint)
    {
        return;
    }

    //第 X 重
    const char* vein_name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(config_vein->name_);
    const char* vein_level = DICTIONARY_CONFIG_MGR::instance()->get_vein_level_string(level);
    m_pLabChongNum->setString(CCString::createWithFormat("%s",vein_name)->getCString());
	m_pLabAcuTitleName->setString(CCString::createWithFormat("%s",vein_level)->getCString());
    //修炼重数
    m_pLabCurChong->setString(CCString::createWithFormat("%d/%d",level+1,VEIN_LEVEL_MAX)->getCString());
    
    if (is_max)
    {
        m_pLabAcupointNameTitle->setString("");
        m_pLabBonusToAttr->setString("");
        m_pLabSuccessRate->setString("");
		m_pLabAdditionNum->setString("");
        m_pLabAllOpenGive->setString("");
        m_pLabConsumptionRepu->setString("");
        m_pLabConsumptionGold->setString("");  
        
        int attr = config_acupoint->level_data_[level].total_attr_;
        for (int i = 0;i < VEIN_LEVEL_MAX;++i)
        {
            attr += config_vein->level_data_[i].attr_;
        }
        const char* attr_type = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(config_acupoint->attr_type_);
        m_pLabCurGain->setString(CCString::createWithFormat("%s+%d",attr_type,attr)->getCString());
    }                                       
    else
    {
        //穴位名称
        m_pLabAcupointNameTitle->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(config_acupoint->name_));
        //加成属性
        const char* attr_type = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(config_acupoint->attr_type_);
        m_pLabBonusToAttr->setString(CCString::createWithFormat("%s+%d",attr_type,config_acupoint->level_data_[level].cur_attr_)->getCString());
        //成功率
        if (rate > 0)
        {
            m_pLabSuccessRate->setString(CCString::createWithFormat("%d%%",config_acupoint->level_data_[level].suc_rate_)->getCString());
			m_pLabAdditionNum->setString(CCString::createWithFormat("+%d%%",rate)->getCString());
        }
        else
        {
            m_pLabSuccessRate->setString(CCString::createWithFormat("%d%%",config_acupoint->level_data_[level].suc_rate_)->getCString());
            m_pLabAdditionNum->setString("");
        }
        //现已获得
        attr_type = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(config_acupoint->attr_type_);
        int attr = config_acupoint->level_data_[level].total_attr_ - config_acupoint->level_data_[level].cur_attr_;
        m_pLabCurGain->setString(CCString::createWithFormat("%s+%d",attr_type,attr)->getCString());
        //全通赠送
        attr_type = DICTIONARY_CONFIG_MGR::instance()->get_attr_string(config_vein->level_data_[level].attr_type_);
        m_pLabAllOpenGive->setString(CCString::createWithFormat("%s+%d",attr_type,config_vein->level_data_[level].attr_)->getCString());
        //消耗声望
        m_pLabConsumptionRepu->setString(CCString::createWithFormat("%d",config_acupoint->level_data_[level].prestige_cost_)->getCString());
        //消耗金币
        m_pLabConsumptionGold->setString(CCString::createWithFormat("%d",config_acupoint->level_data_[level].gold_cost_)->getCString());

		//设置颜色
		int player_id = Account_Data_Mgr::instance()->get_current_role_id();
		Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
		if (!player)
		{
			return;
		}
		if(player->get_prestige() < config_acupoint->level_data_[level].prestige_cost_)
		{
			m_pLabHaveRepu->setColor(ccc3(255,0,0));
		}
		else
		{
			m_pLabHaveRepu->setColor(ccc3(255,255,255));
		}
    }
}

void UI_Fate_Layer::update_time()
{
    Game_Data::Cool_Time* cool_time = COOL_TIME_MGR::instance()->get_cool_time(CTT_OPEN_ACUPOINT);
    if (!cool_time)
    {
        return;
    }

    int time = cool_time->length_;
    if (time > 0)
    {
        m_pLabCoolTimeFont->setVisible(true);
        m_pLabCountdown->setVisible(true);
        if (cool_time->cool_ == 0)
        {
            m_pLabCountdown->setColor(ccc3(255, 255, 255));
            m_pBtnFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_OPEN_ACUPOINT));
        } 
        else
        {
            m_pLabCountdown->setColor(ccc3(255, 0, 0));
            m_pBtnFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_RESET));
        }
    } 
    else
    {
        m_pBtnFont->setString(DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_OPEN_ACUPOINT));
        m_pLabCoolTimeFont->setVisible(false);
        m_pLabCountdown->setVisible(false);
    }    

    int hour = time/3600;
    int minute = time%3600/60;
    int second = time%3600%60;

    const char* str_hour = "";
    if (hour >= 0 && hour < 10)
    {
        str_hour = CCString::createWithFormat("0%d",hour)->getCString();
    }
    else
    {
        str_hour = CCString::createWithFormat("%d",hour)->getCString();
    }

    const char* str_minute = "";
    if (minute >= 0 && minute < 10)
    {
        str_minute = CCString::createWithFormat("0%d",minute)->getCString();
    }
    else
    {
        str_minute = CCString::createWithFormat("%d",minute)->getCString();
    }

    const char* str_second = "";
    if (second >= 0 && second < 10)
    {
        str_second = CCString::createWithFormat("0%d",second)->getCString();
    }
    else
    {
        str_second = CCString::createWithFormat("%d",second)->getCString();
    }

    const char* text_time = CCString::createWithFormat("%s:%s:%s",str_hour,str_minute,str_second)->getCString();
    m_pLabCountdown->setString(text_time);
}

void UI_Fate_Layer::showGuide()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	if( GUIDE_FATE_LEVEL_UP_2 == player->get_guide_id() )
	{
		Joiner_Guidance::receiveCurPosWidget(m_pBtnChongXue);
	}
}

void UI_Fate_Layer::changeGuide()
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return;
	}

	if( GUIDE_FATE_LEVEL_UP_2 == player->get_guide_id() )
	{
		player->change_guide_id( player->get_guide_id()+3 );
		Joiner_Guidance::hideGuide();
	}
}

void UI_Fate_Layer::btnLeftCallback( Ref* pSender ,Widget::TouchEventType type)
{
int curPage;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	if( !pageView )
	{
		return;
	}
	curPage =pageView->getCurPageIndex(); //pageView->getPage();
	//CCLog("left  curPage = %d", curPage);
	if(curPage >= 1)
		pageView->scrollToPage(curPage-1);
// 	else
// 		pageView->scrollToPage(PAGE_NUM-1);

	break;
    default:
	break;
}
}

void UI_Fate_Layer::btnRightCallback( Ref* pSender ,Widget::TouchEventType type)
{
int curPage;
switch (type)
{
    case cocos2d::ui::Widget::TouchEventType::ENDED:
	if( !pageView )
	{
		return;
	}
	
	curPage =pageView->getCurPageIndex();
	CCLog("right  curPage = %d", curPage);
	if(curPage < PAGE_NUM-1)
		pageView->scrollToPage(curPage+1);
// 	else
// 		pageView->scrollToPage(0);
	break;
    default:
	break;
}

}
