//#include "UI_Ranking_List_Layer.h"
//
//#include "Player_Account/Account_Data_Mgr.h"
//#include "Item_System/Item_Desc_Config_Mgr.h"
//
//#include "Rank_System/Rank_Mgr_Cl.h"
//#include "Rank_System/Rank_Logic_Cl.h"
//#include "UI_MainMenu_Layer.h"
//
//#include "Common/GameDefine.h"
//#include "Joiner_Guidance.h"
//
//using namespace Game_Data;
//using namespace ui;
//UI_Ranking_List_Layer::UI_Ranking_List_Layer(void) :
//	m_pRootWidget(NULL),
//	m_pBtnClose(NULL),
//	m_pRankingNum(NULL),
//	m_pBtnLevel(NULL),
//	m_pBtnFighting(NULL),
//	m_pBtnMoney(NULL),
//	m_pScrollView(NULL),
//
//	m_pBtnRoleInfoTemp(NULL),
//	m_pLabRoleRankingTemp(NULL),
//	m_pLabRoleAttrTemp(NULL),
//	m_pLabRoleNameTemp(NULL),
//	m_pLabRoleUnitedTemp(NULL),
//
//	m_pLabAttrFont(NULL)
//{
//	memset(m_pBtnRoleViewInfo, 0, sizeof(m_pBtnRoleViewInfo));
//	memset(m_pLabRoleRankingNum, 0, sizeof(m_pLabRoleRankingNum));
//	memset(m_pLabRoleAttr, 0, sizeof(m_pLabRoleAttr));
//	memset(m_pLabRoleName, 0, sizeof(m_pLabRoleName));
//	memset(m_pLabRoleUnited, 0, sizeof(m_pLabRoleUnited));
//}
//
//
//UI_Ranking_List_Layer::~UI_Ranking_List_Layer(void)
//{
//}
//
//bool UI_Ranking_List_Layer::init()
//{
//	bool bRet =false;
//	do 
//	{
//		CC_BREAK_IF(!cocos2d::Layer::init());
//
//		m_pRootWidget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Ranking_List/Ranking_List.ExportJson");
//		addChild(m_pRootWidget);
//
//		initComponent();
//
//		bRet = true;
//	} while (0);
//
//	return bRet;
//
//}
//
//void UI_Ranking_List_Layer::setVisible( bool visible )
//{
//	cocos2d::Layer::setVisible(visible);
//	if (visible)
//	{
//		Joiner_Guidance::hideGuide();
//		RANK_LOGIC::instance()->load_rank_role_level();
//		m_pImgCurSelectEffect->setPosition(m_pBtnLevel->getPosition());
//	}
//	else
//	{
////		UI_MainMenu_Layer::get_instance()->showGuide();
//	}
//}
//
//void UI_Ranking_List_Layer::initComponent()
//{
//	//关闭按钮 btn_close
//	m_pBtnClose = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pRootWidget,"btn_close"));
//	m_pBtnClose->addTouchEventListener(this, toucheventselector(UI_Ranking_List_Layer::btnCloseCallback));
//
//	//排名数值 lab_ranking_num（类的成员变量）
//	m_pRankingNum = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_ranking_num"));
//	m_pRankingNum ->setString("");
//
//	//等级按钮 btn_level
//	m_pBtnLevel = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pRootWidget,"btn_level"));
//	m_pBtnLevel->addTouchEventListener(this, toucheventselector(UI_Ranking_List_Layer::btnLevelCallback));
//
//	//战力按钮 btn_fighting
//	m_pBtnFighting = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pRootWidget,"btn_fighting"));
//	m_pBtnFighting->addTouchEventListener(this, toucheventselector(UI_Ranking_List_Layer::btnFightingCallback));
//
//	//银两按钮 btn_money
//	m_pBtnMoney = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pRootWidget,"btn_money"));
//	m_pBtnMoney->addTouchEventListener(this, toucheventselector(UI_Ranking_List_Layer::btnMoneyCallback));
//
//	//选中效果
//	m_pImgCurSelectEffect = dynamic_cast<cocos2d::ui::ImageView*>(Helper::seekWidgetByName(m_pRootWidget,"img_cur_select_effect"));
//	m_pImgCurSelectEffect->setPosition(m_pBtnLevel->getPosition());
//
//	//滑动层 ScrollView
//	m_pScrollView = dynamic_cast<cocos2d::ui::ScrollView*>(Helper::seekWidgetByName(m_pRootWidget,"ScrollView"));
//
//	//层上的按钮
//	m_pBtnRoleInfoTemp = dynamic_cast<cocos2d::ui::Button*>(Helper::seekWidgetByName(m_pRootWidget,"btn_role_info")); 
//	m_pLabRoleRankingTemp = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_role_ranking_num"));
//	m_pLabRoleAttrTemp = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_role_attr_name"));
//	m_pLabRoleNameTemp = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_role_name"));
//	m_pLabRoleUnitedTemp = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_role_united_name"));
//
//	//排行榜 lab_ranklist_font
//// 	cocos2d::ui::Text* labRanklistFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_ranklist_font"));
// 	const char* key = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(RANKING_LIST_FONT);
//// 	labRanklistFont->setString(key);
//
//	//主角 lab_role_font
//	cocos2d::ui::Text* labRoleFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_role_font"));
//	key = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ROLE_FONT);
//	labRoleFont->setString(key);
//
//	//名次 lab_mingci_font
//	cocos2d::ui::Text* labMingCiFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_mingci_font"));
//	key = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(RANKING_LIST_RANK);
//	labMingCiFont->setString(key);
//
//	//属性名称 lab_attr_font
//	m_pLabAttrFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_attr_font"));
//	key = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(RANKING_LIST_LEVEL);
//	m_pLabAttrFont->setString(key);
//
//	//名称 lab_name_font
//	cocos2d::ui::Text* labNameFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_name_font"));
//	key = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(RANKING_LIST_NAME);
//	labNameFont->setString(key);
//
//	//帮派 lab_bangpai_font
//	cocos2d::ui::Text* labBangPaiFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_bangpai_font"));
//	key = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(RANKING_LIST_GUILD);
//	labBangPaiFont->setString(key);
//
//	//你的排名 lab_ranking_font
//	cocos2d::ui::Text* labRankingFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_ranking_font"));
//	key = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(RANKING_LIST_U_RANK);
//	labRankingFont->setString(key);
//
//	//等级 lab_level_font
//	cocos2d::ui::Text* labLevelFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_level_font"));
//	key = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(RANKING_LIST_LEVEL);
//	labLevelFont->setString(key);
//
//	//战力 lab_fighting_font
//	cocos2d::ui::Text* labFightingFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_fighting_font"));
//	key = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(RANKING_LIST_FIGHT);
//	labFightingFont->setString(key);
//
//	//银两 lab_money_font
//	cocos2d::ui::Text* labMoneyFont = dynamic_cast<cocos2d::ui::Text*>(Helper::seekWidgetByName(m_pRootWidget,"lab_money_font"));
//	key = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(RANKING_LIST_GOLD);
//	labMoneyFont->setString(key);
//
//	initScrollViewInfo();
//}
//
//void UI_Ranking_List_Layer::btnCloseCallback( Ref* pSender ,Widget::TouchEventType type)
//{
//	setVisible(false);
//}
//
//void UI_Ranking_List_Layer::btnLevelCallback( Ref* pSender ,Widget::TouchEventType type)
//{
//cocos2d::ui::Button* curBtn;
//const char* key ;
//switch (type)
//{
//    case cocos2d::ui::Widget::TouchEventType::ENDED:
//	curBtn = dynamic_cast<cocos2d::ui::Button*>(pSender);
//	m_pImgCurSelectEffect->setPosition(curBtn->getPosition());
//
//	key = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(RANKING_LIST_LEVEL);
//	m_pLabAttrFont->setString(key);
//
//    RANK_LOGIC::instance()->load_rank_role_level();
//
//	break;
//    default:
//	break;
//}
//}
//
//void UI_Ranking_List_Layer::btnFightingCallback( Ref* pSender ,Widget::TouchEventType type)
//{
//cocos2d::ui::Button* curBtn;
//const char* key ;
//switch (type)
//{
//    case cocos2d::ui::Widget::TouchEventType::ENDED:
//	curBtn = dynamic_cast<cocos2d::ui::Button*>(pSender);
//	m_pImgCurSelectEffect->setPosition(curBtn->getPosition());
//	
//	key = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(RANKING_LIST_FIGHT);
//	m_pLabAttrFont->setString(key);
//
//    RANK_LOGIC::instance()->load_rank_role_fighting_capacity();
//
//	break;
//    default:
//	break;
//}
//}
//
//void UI_Ranking_List_Layer::btnMoneyCallback( Ref* pSender ,Widget::TouchEventType type)
//{
//cocos2d::ui::Button* curBtn ;
//const char* key ;
//switch (type)
//{
//    case cocos2d::ui::Widget::TouchEventType::ENDED:
//	curBtn = dynamic_cast<cocos2d::ui::Button*>(pSender);
//	m_pImgCurSelectEffect->setPosition(curBtn->getPosition());
//
//	key = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(RANKING_LIST_GOLD);
//	m_pLabAttrFont->setString(key);
//
//    RANK_LOGIC::instance()->load_rank_role_have_gold();
//
//	break;
//    default:
//	break;
//}
//}
//
//void UI_Ranking_List_Layer::btnRoleInfoCallback( Ref* pSender ,Widget::TouchEventType type)
//{
//cocos2d::ui::Button* curBtn;
//switch (type)
//{
//    case cocos2d::ui::Widget::TouchEventType::ENDED:
//	curBtn = dynamic_cast<cocos2d::ui::Button*>(pSender);
////	CCLog("curBtn Tag = %d", curBtn->getTag());
//
//	break;
//    default:
//	break;
//}
//
//}
//
//void UI_Ranking_List_Layer::initScrollViewInfo()
//{
//	m_pScrollView->setInnerContainerSize(Size(EACH_TEXTURE_WIDTH, EACH_TEXTURE_HEIGHT*RANK_MAX));
//
//	for (int i=0; i<RANK_MAX; ++i)
//	{
//		m_pBtnRoleViewInfo[i] = cocos2d::ui::Button::create();
//		m_pBtnRoleViewInfo[i]->setTouchEnabled(false);
//        m_pBtnRoleViewInfo[i]->setVisible(false);
//		m_pBtnRoleViewInfo[i]->loadTextures("pic_dikuang_2.png", "pic_dikuang_2.png", "pic_dikuang_2.png", UI_TEX_TYPE_PLIST);
//		m_pBtnRoleViewInfo[i]->setCapInsets(CCRectMake(40.0f, 48.0f, 10.0f, 17.0f));
//m_pBtnRoleViewInfo[i]->setSize(Size(EACH_TEXTURE_WIDTH, EACH_TEXTURE_HEIGHT));
//		m_pBtnRoleViewInfo[i]->setAnchorPoint(Vec2(0.0f, 0.0f));
//		m_pScrollView->getInnerContainer()->addChild(m_pBtnRoleViewInfo[i]);
//		m_pBtnRoleViewInfo[i]->setPosition(Vec2(0, m_pScrollView->getInnerContainer()->getContentSize().height-EACH_TEXTURE_HEIGHT*(i+1)));
//		m_pBtnRoleViewInfo[i]->setTag(i);
//		m_pBtnRoleViewInfo[i]->addTouchEventListener(this, toucheventselector(UI_Ranking_List_Layer::btnRoleInfoCallback));
//
//		m_pLabRoleRankingNum[i] = cocos2d::ui::Text::create();
//		m_pBtnRoleViewInfo[i]->addChild(m_pLabRoleRankingNum[i]);
//		m_pLabRoleRankingNum[i]->setPosition(m_pLabRoleRankingTemp->getPosition());
////		m_pLabRoleRankingNum[i]->setFontSize(FONT_SIZE);
//
//		m_pLabRoleAttr[i] = cocos2d::ui::Text::create();
//		m_pBtnRoleViewInfo[i]->addChild(m_pLabRoleAttr[i]);
//		m_pLabRoleAttr[i]->setPosition(m_pLabRoleAttrTemp->getPosition());
////		m_pLabRoleAttr[i]->setFontSize(FONT_SIZE);
//
//		m_pLabRoleName[i] = cocos2d::ui::Text::create();
//		m_pBtnRoleViewInfo[i]->addChild(m_pLabRoleName[i]);
//		m_pLabRoleName[i]->setPosition(m_pLabRoleNameTemp->getPosition());
////		m_pLabRoleName[i]->setFontSize(FONT_SIZE);
//
//		m_pLabRoleUnited[i] = cocos2d::ui::Text::create();
//		m_pBtnRoleViewInfo[i]->addChild(m_pLabRoleUnited[i]);
//		m_pLabRoleUnited[i]->setPosition(m_pLabRoleUnitedTemp->getPosition());
////		m_pLabRoleUnited[i]->setFontSize(FONT_SIZE);
//	}
//}
//
//void UI_Ranking_List_Layer::reset_ui()
//{
//	for (int i=0; i<RANK_MAX; ++i)
//	{
//		m_pBtnRoleViewInfo[i]->setTouchEnabled(false);
//		m_pBtnRoleViewInfo[i]->setVisible(false);
//		m_pBtnRoleViewInfo[i]->setTag(0);
//		m_pBtnRoleViewInfo[i]->setPosition(Vec2(0, m_pScrollView->getInnerContainer()->getContentSize().height-EACH_TEXTURE_HEIGHT*(i+1)));
//	}
//}
//
//void UI_Ranking_List_Layer::update(int rank_type)
//{
//	Game_Data::Rank_List rank_list;
//	int count = 0;
//    if (rank_type == Game_Data::RT_ROLE_FIGHTING_CAPACITY)
//    {
//        count = RANK_MGR::instance()->get_rank_role_fighting_capacity_list(rank_list);
//    }
//    else if (rank_type == Game_Data::RT_ROLE_HAVE_GOLD)
//    {
//        count = RANK_MGR::instance()->get_rank_role_have_gold_list(rank_list);
//    }
//    else
//    {
//        count = RANK_MGR::instance()->get_rank_role_level_list(rank_list);
//    }
//
//	m_pScrollView->setInnerContainerSize(Size(EACH_TEXTURE_WIDTH, EACH_TEXTURE_HEIGHT*count));
//	reset_ui();
//
//    int self_rank = 0;
//	int index = 0;
//	Game_Data::Rank* rank = NULL;
//	Game_Data::Rank_List_Iter iter = rank_list.begin();
//	for (;iter != rank_list.end();++iter)
//	{
//		rank = *iter;
//		if (!rank)
//		{
//			continue;
//		}
//
//        if (Account_Data_Mgr::instance()->get_current_role_id() == rank->role_id_)
//        {
//            self_rank = index + 1;
//            m_pLabRoleRankingNum[index]->setColor(ccc3(204, 176, 102));
//            m_pLabRoleAttr[index]->setColor(ccc3(204, 176, 102));
//            m_pLabRoleName[index]->setColor(ccc3(204, 176, 102));
//            m_pLabRoleUnited[index]->setColor(ccc3(204, 176, 102));
//        }
//        else
//        {
//            m_pLabRoleRankingNum[index]->setColor(ccc3(255, 255, 255));
//            m_pLabRoleAttr[index]->setColor(ccc3(255, 255, 255));
//            m_pLabRoleName[index]->setColor(ccc3(255, 255, 255));
//            m_pLabRoleUnited[index]->setColor(ccc3(255, 255, 255));
//        }
//
//		m_pBtnRoleViewInfo[index]->setTag(rank->role_id_);
//		m_pBtnRoleViewInfo[index]->setVisible(true);
//		m_pBtnRoleViewInfo[index]->setTouchEnabled(true);
//
//		m_pLabRoleRankingNum[index]->setString(CCString::createWithFormat("%d",index + 1)->getCString());
//		m_pLabRoleAttr[index]->setString(CCString::createWithFormat("%d",rank->rank_attr_)->getCString());
//		m_pLabRoleName[index]->setString(rank->name_);
//		m_pLabRoleUnited[index]->setString("");
//
//		//m_pScrollView->scrollToTop();
//		++index;
//	}
//
//    if (self_rank == 0)
//    {
//        const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(RANKING_LIST_NOT_RANK);
//        m_pRankingNum->setString(CCString::createWithFormat(szString,RANK_MAX)->getCString());
//    } 
//    else
//    {
//        m_pRankingNum->setString(CCString::createWithFormat("%d",self_rank)->getCString());
//    }
//}
