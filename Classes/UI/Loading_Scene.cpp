#include "Loading_Scene.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Common/GameDefine.h"
#include "Loading_NoTouch_Layer.h"
//#include "Game/Effect_Cfg_Data_Mgr.h"
#include "Common/VisibleRect.h"
/******************************** dely ******************************/
#include "../DataModule/Little.h"
#define LITTLE_PATH "GameData/little/little"
/******************************** dely ******************************/

USING_NS_CC;

#define DEFINEZORDER 9999

namespace UI
{
    
    Loading_Scene::Loading_Scene()
    :m_nStep(0)
    ,m_pSprBgk(NULL)
    ,m_pSprLoadingBar(NULL)
    ,m_pSprLoadingBkg(NULL)
    ,loading_pattern_(NULL)
    ,comment_label_(NULL)
    ,m_no_touch_layer_(NULL)
    ,m_pRunningEffect(NULL)
    {
        commet_text_ = Game_Data::Item_Desc_Config_Mgr::instance()->get_string_by_id( LOADING_RESOUCES);
    }
    
    Loading_Scene::~Loading_Scene()
    {
    }
    
    bool Loading_Scene::init()
    {
        if (!Scene::init())
        {
            return false;
        }
        if (m_vecLoadFunc.size()>0)
        {
            cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
            Point origin = Director::getInstance()->getVisibleOrigin();
            
            //m_no_touch_layer_ = Loading_NoTouch_Layer::create();
            //if (m_no_touch_layer_)
            //{
            //    this->addChild(m_no_touch_layer_, 99999, TAG_NO_TOUCH_LAYER);
            //}
            
            
            // init background
            pt = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y-200);
            /*m_pSprBgk = cocos2d::Sprite::create("ui/Loading/background.jpg");
             m_pSprBgk->setPosition(pt);
             addChild(m_pSprBgk,DEFINEZORDER);*/
			auto colorLayer =  LayerColor::create(Color4B::BLACK);
			this->addChild(colorLayer, DEFINEZORDER+1, "color");


			srand((unsigned)time(NULL));
			int ran = rand();
			int rann = ran % 2 + 1;
			Value pre("scene_res/loading_bg_");
			Value mid(rann);
			Value suff(".png");
			Value fileName(pre.asString()+mid.asString()+suff.asString() );
			cocos2d::Sprite* sp = cocos2d::Sprite::create( fileName.asString() );
			float screenWidth = Director::getInstance()->getWinSize().width;
			float spWidth = sp->getContentSize().width;
			float scaleX = screenWidth / spWidth;
			sp->setScaleX(scaleX);

			sp->setPosition(VisibleRect::center());
			colorLayer->addChild(sp,1, "bg");

            auto loadBg = Sprite::create("ui/loading_back.png");
            loadBg->setPosition(pt);
			colorLayer->addChild(loadBg,2,"loadBg");

			auto bar = LoadingBar::create("ui/loading_bar.png");
			bar->setAnchorPoint(Vec2(0.5f, 0.5f));
			bar->setPosition(pt);
			this->addChild(bar, DEFINEZORDER+2, "bar");

            loading_pattern_ = cocos2d::Sprite::create(LOADINGPATTERN_PATH);
            loading_pattern_->setAnchorPoint(Vec2(0.5f,0.5f));
            loading_pattern_->setPosition( Vec2(pt.x - 210,pt.y+150) );
			colorLayer->addChild(loading_pattern_,3);

			/******************************** dely ******************************/
			Little::readFile(LITTLE_PATH);
			int random_num = rand();
			int tmp = random_num % 4 + 1;
			//std::string str = Little::tips[tmp].getContent();
			std::string str = Little::tips[tmp].content;

			/*UserDefault::getInstance()->setStringForKey("tip","通关副本可获得装备进阶材料");
			std::string chnStr = UserDefault::getInstance()->getStringForKey("tip");
			*/
			tipsLab = cocos2d::LabelTTF::create(str, "Arial", 24);
			tipsLab->setPosition(Vec2(pt.x, pt.y + 150));
			colorLayer->addChild(tipsLab,4);

			/******************************** dely ******************************/

            // init loading comment text
            comment_label_ = LabelTTF::create(commet_text_.c_str(), "Arial", 40);
            comment_label_->setPosition( Vec2(VisibleRect::left().x+visibleSize.width/2 , pt.y+75) );
            comment_label_->setColor(ccc3(254,255,217));
			colorLayer->addChild(comment_label_,5);
            
            this->schedule(schedule_selector(Loading_Scene::loadingUpdate),0.1f);
            updateLoadingBar();
        }
        else
        {
            onLoadFinish();
        }
        
        return true;
    }
    
    void Loading_Scene::loadingUpdate(float delta)
    {
        cocos2d::Sprite* pSprite = (cocos2d::Sprite*)getChildByTag(102);
        if ( m_vecLoadFunc.size()>0 && m_nStep<(int)m_vecLoadFunc.size() )
        {
			//if (m_nStep == 0)
			//{
			//	auto frame0 = SpriteFrameCache::getInstance()->getSpriteFrameByName("loading (1).png");
			//	auto frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("loading (2).png");
			//	auto frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("loading (3).png");
			//	auto frame3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("loading (4).png");
			//	auto frame4 = SpriteFrameCache::getInstance()->getSpriteFrameByName("loading (5).png");
			//	auto frame5 = SpriteFrameCache::getInstance()->getSpriteFrameByName("loading (6).png");
			//	auto frame6 = SpriteFrameCache::getInstance()->getSpriteFrameByName("loading (7).png");
			//	auto frame7 = SpriteFrameCache::getInstance()->getSpriteFrameByName("loading (8).png");
			//	Vector<SpriteFrame*> frames;
			//	frames.pushBack(frame0);
			//	frames.pushBack(frame1);
			//	frames.pushBack(frame2);
			//	frames.pushBack(frame3);
			//	frames.pushBack(frame4);
			//	frames.pushBack(frame5);
			//	frames.pushBack(frame6);
			//	frames.pushBack(frame7);

			//	auto animation = Animation::createWithSpriteFrames(frames, 0.2f);
			//	auto animate = Animate::create(animation);
			//	auto seq = Sequence::create(animate, nullptr);
			//	_girl->runAction(RepeatForever::create(seq));
			//}
            LoadFunc p = m_vecLoadFunc[m_nStep++];
            (this->*p)();
            updateLoadingBar();
            return;
        }
        //m_pSprBgk->removeFromParent();
        //m_pSprLoadingBar->removeFromParent();
        //m_pRunningEffect->removeFromParent();
        //m_pSprLoadingBkg->removeFromParent();
		this->getChildByName("color")->removeFromParent();
		//this->getChildByName("color")->getChildByName("bg")->removeFromParent();
		//this->getChildByName("color")->getChildByName("loadBg")->removeFromParent();
		this->getChildByName("bar")->removeFromParent();
        
		//_girl->removeFromParent();
  //      loading_pattern_->removeFromParent();
  //      comment_label_->removeFromParent();
		//tipsLab->removeFromParent();
        _scheduler->unscheduleSelector(schedule_selector(Loading_Scene::loadingUpdate), this);
        onLoadFinish();
    }
    
    void Loading_Scene::updateLoadingBar()
    {
        auto barr = (LoadingBar*)(this->getChildByName("bar") );
        if (barr)
        {
            barr->setPercent( (float)(m_nStep/(float)m_vecLoadFunc.size()*100) );
            //cocos2d::Size sz = m_pSprLoadingBar->getTexture()->getContentSize();
            ////m_pRunningEffect->setPosition(Vec2(m_nStep*1.0f/m_vecLoadFunc.size()*sz.width + 210 , 100));
            //m_pSprLoadingBar->setTextureRect(CCRectMake(0,0,m_nStep*1.0f/m_vecLoadFunc.size()*sz.width,sz.height));
        }
        if (comment_label_)
        {
            int proportion = (int)(( (float)m_nStep/(float)m_vecLoadFunc.size() ) * 100);
            char buff[128] = {0};
            std::sprintf(buff ,"( %d",proportion);
            
            std::string tmp = buff;
            tmp += "% )"; 
            tmp = commet_text_ + tmp;
            comment_label_->setString(tmp.c_str());
        }
        
    }
    
    void Loading_Scene::onLoadFinish()
    {
        m_nStep = 0;
        m_vecLoadFunc.clear();
        this->removeChildByTag(TAG_NO_TOUCH_LAYER);
    }
    
    
}