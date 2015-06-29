#include "Joiner_Guidance.h"

#include "Item_System/Item_Desc_Config_Mgr.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Junior_Guide_System/Junior_Guide_Mgr.h"
using namespace Game_Data;


Joiner_Guidance* Joiner_Guidance::m_pInstance = NULL;
Joiner_Guidance::Joiner_Guidance(void)
{
	memset(m_pImgGuideInfoBack, 0, sizeof(m_pImgGuideInfoBack));
	memset(m_pLabGuideInfo, 0, sizeof(m_pLabGuideInfo));
}


Joiner_Guidance::~Joiner_Guidance(void)
{

}


bool Joiner_Guidance::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());

		cocos2d::ui::Layout* panel = cocos2d::ui::Layout::create();

		char key[64] = "";
		for (int i = 0; i<(int)GUIDE_TYPE; ++i)
		{
			memset(key, 0, sizeof(key));
			sprintf(key, "common/junior_guide/pic_zhiyin_%d.png", i);

			m_pImgGuideInfoBack[i] = cocos2d::ui::ImageView::create();
			m_pImgGuideInfoBack[i]->loadTexture(key);
			m_pImgGuideInfoBack[i]->setVisible(false);
			m_pLabGuideInfo[i] = cocos2d::ui::Text::create();
			m_pImgGuideInfoBack[i]->addChild(m_pLabGuideInfo[i]);
			m_pLabGuideInfo[i]->setColor(ccc3(18, 14, 11));
			m_pLabGuideInfo[i]->setFontSize(GUIDE_INFO_SIZE);


			if( 0 == i )
			{
				m_pLabGuideInfo[i]->setPosition(Vec2(60,  30));
			}
			else if( 1 == i )
			{
				m_pLabGuideInfo[i]->setPosition(Vec2(60, 30));
			}
			else if( 2 == i )
			{
				m_pLabGuideInfo[i]->setPosition(Vec2(60, 20));
			}
			else if( 3 == i )
			{
				m_pLabGuideInfo[i]->setPosition(Vec2(60, 20));
			}

			panel->addChild(m_pImgGuideInfoBack[i]);
		}
		
		this->addChild(panel);

		bRet = true;

	} while (0);

	return bRet;
}

void Joiner_Guidance::setVisible(bool visible)
{
	cocos2d::Layer::setVisible(visible);

}

void Joiner_Guidance::receiveCurPosWidget( cocos2d::ui::Widget* widget )
{
	Point point = widget->getWorldPosition();
	Point anchorPoint = widget->getAnchorPoint();
	if (widget)
	{
		showGuide(point.x, point.y, widget);
	}
	else
	{
		showGuide(point.x, point.y);
	}
}

void Joiner_Guidance::receiveCurPosWidget( const Point &point )
{
	showGuide(point.x, point.y);
}

void Joiner_Guidance::showGuide(  float posX, float posY, cocos2d::ui::Widget* widget )
{
	if (!m_pInstance)
	{
		m_pInstance = Joiner_Guidance::create();
		m_pInstance->retain();	//let it leak,that's all right
	}
	CC_ASSERT(m_pInstance);
	m_pInstance->hideGuide();

	{
		int role_id = Account_Data_Mgr::instance()->get_current_role_id();
		Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
		int id = player->get_guide_id();
		junior_guide_config* config = Junior_Guide_Mgr::get_instance()->get_config_by_id(player->get_guide_id());
		if(!config) return;

//		Point point( (config->pos_x_) + posX, (config->pos_y_ + posY) );
        Point point( (config->pos_x_), (config->pos_y_) );
		
		m_pInstance->showGuideContent( point, config->desc_, config->img_index_, widget );
	}
	

    widget->addChild(m_pInstance);
//	Scene* pCurrentScene = Director::getInstance()->getRunningScene();
//	CC_ASSERT(pCurrentScene);
//	pCurrentScene->addChild(m_pInstance,50);
}

void Joiner_Guidance::hideGuide()
{
	if (m_pInstance && m_pInstance->getParent())
	{
		m_pInstance->removeFromParent();
	}
}

void Joiner_Guidance::showGuideContent( Point handPoint, int infoId, int img_index, cocos2d::ui::Widget* widget/* = NULL*/ )
{
	const char* guideInfo  = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(infoId);
	
	resetUI();

	switch (img_index)
	{
	case 0:
		{
			Point point;
			Point anchorPoint;
			if ( widget )
			{
				anchorPoint = widget->getAnchorPoint();

				if ( 0.5 == anchorPoint.x )
				{
					point = Vec2(handPoint.x- m_pImgGuideInfoBack[0]->getContentSize().width/2,
						handPoint.y + widget->getContentSize().height/2);
				}
				if ( 0 == anchorPoint.x)
				{
					point = Vec2(handPoint.x - m_pImgGuideInfoBack[0]->getContentSize().width/2, handPoint.y);
				}
				if ( 0 == anchorPoint.x && 0 == anchorPoint.y )
				{
					point = Vec2(handPoint.x - m_pImgGuideInfoBack[0]->getContentSize().width/2, handPoint.y + widget->getContentSize().height/2 );
				}
			}
			else
			{
				anchorPoint = Vec2(0.5f, 0.5f);
				point = Vec2(handPoint.x - m_pImgGuideInfoBack[0]->getContentSize().width/2, handPoint.y);
			}
			
			m_pImgGuideInfoBack[0]->setPosition(point);
			m_pLabGuideInfo[0]->setString(guideInfo);

			ActionInterval* right = CCMoveTo::create(0.2f,Vec2(point.x+20, point.y));
			ActionInterval* delay = CCDelayTime::create(0.3f);
			ActionInterval* left = CCMoveTo::create(0.2f,Vec2(point.x, point.y));
			ActionInterval* action = CCSequence::create(right, delay, left, NULL);

			m_pImgGuideInfoBack[0]->runAction(CCRepeatForever::create(action));
			m_pImgGuideInfoBack[0]->setVisible(true);
		}
		break;
	case 1:
		{
			Point point(handPoint.x + m_pImgGuideInfoBack[1]->getContentSize().width/3*2, handPoint.y);
			m_pImgGuideInfoBack[1]->setPosition(point);
			
			m_pLabGuideInfo[1]->setString(guideInfo);

			ActionInterval* left = CCMoveTo::create(0.2f,Vec2(point.x-20, point.y));
			ActionInterval* right = CCMoveTo::create(0.2f,Vec2(point.x, point.y));
			ActionInterval* delay = CCDelayTime::create(0.3f);
			ActionInterval* action = CCSequence::create(left, right, delay, NULL);

			m_pImgGuideInfoBack[1]->runAction(CCRepeatForever::create(action));
			m_pImgGuideInfoBack[1]->setVisible(true);
		}
		break;
	case 2:
		{
			Point point(handPoint.x, handPoint.y + m_pImgGuideInfoBack[2]->getContentSize().height/2);
			m_pImgGuideInfoBack[2]->setPosition(point);
			
			m_pLabGuideInfo[2]->setString(guideInfo);

			ActionInterval* up = CCMoveTo::create(0.2f,Vec2(point.x, point.y+20));
			ActionInterval* delay = CCDelayTime::create(0.3f);
			ActionInterval* down = CCMoveTo::create(0.2f,Vec2(point.x, point.y));
			ActionInterval* action = CCSequence::create(up, delay, down, NULL);

			m_pImgGuideInfoBack[2]->runAction(CCRepeatForever::create(action));
			m_pImgGuideInfoBack[2]->setVisible(true);
		}
		break;
	case 3:
		{
			Point point(handPoint.x, handPoint.y - m_pImgGuideInfoBack[3]->getContentSize().height/2);
			m_pImgGuideInfoBack[3]->setPosition(point);

			m_pLabGuideInfo[3]->setString(guideInfo);

			ActionInterval* up = CCMoveTo::create(0.2f,Vec2(point.x, point.y-20));
			ActionInterval* delay = CCDelayTime::create(0.3f);
			ActionInterval* down = CCMoveTo::create(0.2f,Vec2(point.x, point.y));
			ActionInterval* action = CCSequence::create(up, delay, down, NULL);

			m_pImgGuideInfoBack[3]->runAction(CCRepeatForever::create(action));
			m_pImgGuideInfoBack[3]->setVisible(true);
		}
		break;
	default:
		break;
	}

}

void Joiner_Guidance::resetUI()
{
	for (int i=0; i<GUIDE_TYPE; ++i)
	{
		m_pImgGuideInfoBack[i]->setVisible(false);
	}
}
