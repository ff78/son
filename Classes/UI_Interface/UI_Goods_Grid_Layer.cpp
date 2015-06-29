#include "UI_Goods_Grid_Layer.h"

#include "Item_Container_System/Item_Container_Msg_Proc_Cl.h"
#include "Item_Container_System/Item_Container_Mgr_Cl.h"
#include "Item_System/Item_Mgr_Cl.h"
#include "Item_System/Item_Logic_Cl.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player_Config_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "UI_ModalDialogue_Layer.h"

#include "UI_Icon_Info_Layer.h"
#include "Joiner_Guidance.h"
#include "Common/GameResource.h"
using namespace ui;
using namespace Game_Data;


UI_Goods_Grid_Layer::UI_Goods_Grid_Layer(void) :
	btnTidy(NULL),
	btnEat(NULL),
	btnEatFont(NULL),
	btnReset(NULL),
	btnResetFont(NULL),
	m_IntCurPage(0)
{
	memset(m_pImgEffect, 0, sizeof(m_pImgEffect));
	memset(m_pImgLight, 0, sizeof(m_pImgLight));
	memset(m_pImgAllGrid, 0, sizeof(m_pImgAllGrid));
	memset(m_pImgTextureChild, 0, sizeof(m_pImgTextureChild));

	memset(m_pLabIconNum, 0, sizeof(m_pLabIconNum));
	memset(m_pImgQuaMark, 0, sizeof(m_pImgQuaMark));
	memset(m_pImgEquipMark, 0, sizeof(m_pImgEquipMark));

}


UI_Goods_Grid_Layer::~UI_Goods_Grid_Layer(void)
{
}

bool UI_Goods_Grid_Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF( !cocos2d::Layer::init() );


		bRet = true;

	} while (0);

	return bRet;
}

cocos2d::ui::ImageView* UI_Goods_Grid_Layer::createHorizontalGrid( int style )
{
	cocos2d::ui::ImageView* imgBack = cocos2d::ui::ImageView::create();
	imgBack->loadTexture(PAGE_VIEW_BG_LXD);
imgBack->setScale9Enabled(true);
	imgBack->setSize(Size(ROOT_BACK_WIDTH, ROOT_BACK_HEIGHT));

	cocos2d::ui::PageView* pageView = cocos2d::ui::PageView::create();
	pageView->setTouchEnabled(true);
	pageView->setSize(Size(LAYOUT_WIDTH, LAYOUT_HEIGHT));
	pageView->setAnchorPoint(Vec2(0.5f, 0.5f));

	for (int i = 0; i < PAGE_SUM_NUM; ++i)
	{
		cocos2d::ui::Layout* layout = cocos2d::ui::Layout::create();
		layout->setSize(Size(LAYOUT_WIDTH, LAYOUT_HEIGHT));

		cocos2d::ui::ImageView* imageView = cocos2d::ui::ImageView::create();
		imageView->setTouchEnabled(true);
        imageView->setScale9Enabled(true);
		imageView->loadTexture(PAGE_INNER_VIEW_BG_LXD);
        imageView->setSize(Size(LAYOUT_WIDTH, LAYOUT_HEIGHT));
		imageView->setPosition(Vec2(layout->getSize().width / 2, layout->getSize().height / 2));
		layout->addChild(imageView);

		if( 0 == (style & STYLE_EACH_HAS_EFFECT) )
		{
			m_pImgEffect[i] = cocos2d::ui::ImageView::create();
			m_pImgEffect[i]->setVisible(false);
			m_pImgEffect[i]->loadTexture(BAG_GRID_FRAME_PRESSED);
			layout->addChild(m_pImgEffect[i]);
		}

		m_pImgLight[i] = cocos2d::ui::ImageView::create();
		if( 0 == i )
		{
			m_pImgLight[i]->loadTexture(CUR_PAGE_GREEN_PIC);
		}
		else
		{
			m_pImgLight[i]->loadTexture(CUR_PAGE_RED_PIC);
		}
		if(	style & STYLE_PAGE_LIGHT_LEFT )
		{
			m_pImgLight[i]->setPosition(Vec2(-160 + i*30, -170));
		}
		else
		{
			m_pImgLight[i]->setPosition(Vec2(-80 + i*30, -170));
		}
		

		for(int j=0; j<EACH_PAGE_NUM; ++j)
		{
			//背景
			m_pImgAllGrid[i][j] = cocos2d::ui::ImageView::create();
			m_pImgAllGrid[i][j]->setTouchEnabled(true);
			m_pImgAllGrid[i][j]->loadTexture(BAG_GRID_FRAME_NORMAL);
			m_pImgAllGrid[i][j]->setPosition(Vec2( m_pImgAllGrid[i][j]->getContentSize().width/2+ j%4*m_pImgAllGrid[i][j]->getContentSize().width*1.2 + 15, 
				layout->getSize().height-m_pImgAllGrid[i][j]->getContentSize().height/2-m_pImgAllGrid[i][j]->getContentSize().height*(j/4)/0.85 - 25));
			layout->addChild(m_pImgAllGrid[i][j]);
	        m_pImgAllGrid[i][j]->setTag(i*EACH_PAGE_NUM+j);

			//贴图
			m_pImgTextureChild[i][j] = cocos2d::ui::ImageView::create();
	        m_pImgTextureChild[i][j]->setTag(i*EACH_PAGE_NUM+j);
			m_pImgAllGrid[i][j]->addChild(m_pImgTextureChild[i][j]);

			if( style & STYLE_GRID_LAB_NUM )
			{
				//数量
				m_pLabIconNum[i][j] = cocos2d::ui::Text::create();
				m_pLabIconNum[i][j]->setFontSize(22);
				m_pImgTextureChild[i][j]->addChild(m_pLabIconNum[i][j]);
				m_pLabIconNum[i][j]->setPosition(Vec2(31,-31));
			}
			if ( style & STYLE_GRID_PIC_QUA )
			{
				//"品" 字标识
				m_pImgQuaMark[i][j] = cocos2d::ui::ImageView::create();
				m_pImgQuaMark[i][j]->loadTexture(MARK_QUALITY_FONT_PIC);
				m_pImgTextureChild[i][j]->addChild(m_pImgQuaMark[i][j]);
				m_pImgQuaMark[i][j]->setPosition(Vec2(-33, 33));
			}
			if ( style & STYLE_GRID_PIC_EQU )
			{
				//"装" 字标识
				m_pImgEquipMark[i][j] = cocos2d::ui::ImageView::create();
				m_pImgEquipMark[i][j]->loadTexture(MARK_EQUIP_FONT_PIC);
				m_pImgTextureChild[i][j]->addChild(m_pImgEquipMark[i][j]);
				m_pImgEquipMark[i][j]->setPosition(Vec2(33, -33));
			}
			if ( style & STYLE_EACH_HAS_EFFECT )
			{
				//每个框上都有选中效果
				m_pImgEveryEffect[i][j] = cocos2d::ui::ImageView::create();
				m_pImgEveryEffect[i][j]->loadTexture(EACH_GRID_HAS_OWN_EFFECT);
				m_pImgAllGrid[i][j]->addChild(m_pImgEveryEffect[i][j]);
			}
		}

		pageView->addPage(layout);

		imgBack->addChild(m_pImgLight[i]);
	}

	pageView->addEventListenerPageView(this, pagevieweventselector(UI_Goods_Grid_Layer::pageViewEvent));
	imgBack->addChild(pageView);
	pageView->setPosition(Vec2(0, 36));

	if ( style & STYLE_BOTH_BUTTON )
	{
		btnEat = cocos2d::ui::Button::create();
		btnEat->setTouchEnabled(true);
	    btnEat->loadTextures(TIDY_BUTTON_NORMAL, TIDY_BUTTON_PRESSED, TIDY_BUTTON_DISABLED);
		imgBack->addChild(btnEat);
		btnEat->setPosition(Vec2(-100, -220));
		btnEatFont = cocos2d::ui::Text::create();
		btnEatFont->setString("TunShi");
		btnEat->addChild(btnEatFont);
		btnEatFont->setFontSize(25);

		btnReset = cocos2d::ui::Button::create();
		btnReset->setTouchEnabled(true);
		btnReset->loadTextures(TIDY_BUTTON_NORMAL, TIDY_BUTTON_PRESSED, TIDY_BUTTON_DISABLED);
		imgBack->addChild(btnReset);
		btnReset->setPosition(Vec2(100, -220));
		btnResetFont = cocos2d::ui::Text::create();
		btnResetFont->setString("ChongZhi");
		btnReset->addChild(btnResetFont);
		btnResetFont->setFontSize(25);
	}

	if(	style & STYLE_PAGE_LIGHT_LEFT )
	{
		//整理背包 按钮
		btnTidy = cocos2d::ui::Button::create();
		btnTidy->setTouchEnabled(true);
		btnTidy->loadTextures(TIDY_BUTTON_NORMAL, TIDY_BUTTON_PRESSED, TIDY_BUTTON_DISABLED);
		imgBack->addChild(btnTidy);
		btnTidy->setPosition(Vec2(100, -180));

		//整理背包 字样
		cocos2d::ui::Text* labBtnFont = cocos2d::ui::Text::create();
//		const char* szTidyFont = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(COMMON_TIDY_BAG); 
	//	labBtnFont->setString(szTidyFont);
		//labBtnFont->setFontSize(25);
		//labBtnFont->setColor(ccc3(245,215,142));
		//btnTidy->addChild(labBtnFont);
	}
	return imgBack;
}


void UI_Goods_Grid_Layer::pageViewEvent(Ref *pSender, cocos2d::ui::PageViewEventType  type)
{

	switch (type)
	{
	case PAGEVIEW_EVENT_TURNING:
		{
			cocos2d::ui::PageView* pageView = dynamic_cast<cocos2d::ui::PageView*>(pSender);
			//CCLog(" m_IntCurPage = %d",pageView->getPage());			
			if(m_IntCurPage != pageView->getCurPageIndex())
			{
				m_IntCurPage = pageView->getCurPageIndex();
				for(int i=0; i<PAGE_SUM_NUM; ++i)
				{
					//m_pImgEffect[i]->setVisible(false);
					if(i == m_IntCurPage)
					{
						m_pImgLight[i]->loadTexture(CUR_PAGE_GREEN_PIC);
					}
					else
					{
						m_pImgLight[i]->loadTexture(CUR_PAGE_RED_PIC);
					}
				}
			}
		}
		break;

	default:
		break;
	}

}


