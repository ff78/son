#include "DownLoading_Layer.h"
#include "Platform_Dependence/Dependence.h"
#include "UI_Interface/UI_ModalDialogue_Layer.h"
#include "Common/GameMacro.h"
#include <string>
using namespace std;
USING_NS_CC;

namespace UI
{

	DownLoading_Layer::DownLoading_Layer()
	:m_status_label(NULL)
	{
	}

	DownLoading_Layer::~DownLoading_Layer()
	{
	}

	bool DownLoading_Layer::init()
	{
		if(!Layer::init())
		{
			return false;
		}

		cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();

		Point pt = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
		m_pSprBgk = cocos2d::Sprite::create("ui/Loading/background.jpg");
		m_pSprBgk->setPosition(pt);
		
		addChild(m_pSprBgk);

		m_status_label = LabelTTF::create();
		m_status_label->initWithString("Hello World","Helvetica",40);
		m_status_label->setPosition(pt);
		
		addChild(m_status_label);

		m_pSprLoadingBar = cocos2d::Sprite::create("ui/Loading/loading.png");
		pt.x -=m_pSprLoadingBar->getTexture()->getContentSize().width/2;
		pt.y = 40;
		m_pSprLoadingBar->setAnchorPoint(Vec2(0,0));
		m_pSprLoadingBar->setPosition(pt);
		m_pSprLoadingBar->setVisible(false);
		addChild(m_pSprLoadingBar);

		m_pSprLoadingBkg = cocos2d::Sprite::create("ui/Loading/loadingbkg.png");
		m_pSprLoadingBkg->setAnchorPoint(Vec2(0,0));
		m_pSprLoadingBkg->setPosition(pt);
		
		addChild(m_pSprLoadingBkg);
		
		return true;
	}


	void DownLoading_Layer::onProgress(int percent)
	{	
		if (m_pSprLoadingBar)
		{
			if (percent >= 100)
			{
				return;
			}

			cocos2d::Size sz = m_pSprLoadingBar->getTexture()->getContentSize();
			m_pSprLoadingBar->setTextureRect(CCRectMake(0,0,((float)percent/100)*sz.width,sz.height));

			if (!m_pSprLoadingBar->isVisible())
			{
				m_pSprLoadingBar->setVisible(true);
			}

			char temp[64]={0};
			SPRINTF(temp,"%d",percent);
			string str(temp);
			str+="%";
			m_status_label->setString(str.c_str());
		}
	}

	void DownLoading_Layer::onSuccess(ErrorCode errorCode)
	{
		
		if(errorCode==UpdateProtocol::kINSTALL)
		{
			CCLog("--------------void DownLoading_Layer::errorCode==UpdateProtocol::kINSTALL");
			UI_ModalDialogue_Layer::DoModal("", "Downloading Success,Please install new game your game!", UI_ModalDialogue_Layer::DT_OK, [&](){ this->installAPK(); } );
			
		}
		else if(errorCode==UpdateProtocol::kREBOOT)
		{
			CCLog("--------------void DownLoading_Layer::errorCode==UpdateProtocol::kREBOOT");
			m_status_label->setVisible(false);
			UI_ModalDialogue_Layer::DoModal("", "Downloading Success,Please restart your game!", UI_ModalDialogue_Layer::DT_OK, [&](){ this->quit(); } );
		}
		else if(errorCode==UpdateProtocol::kGOON)
		{
			//Scene * sc=Director::getInstance()->getRunningScene();
			//sc->removeChildByTag(UPDATELAYERTAG);
			CCLog("--------------void DownLoading_Layer::errorCode==UpdateProtocol::kGOON");
			m_status_label->setVisible(false);
			UI_ModalDialogue_Layer::DoModal("", "Downloading Success,Please restart your game!", UI_ModalDialogue_Layer::DT_OK, [&](){ this->quit(); } );

		}
	}

	void DownLoading_Layer::onError( ErrorCode errorcode )
	{
		CCLog("---------void DownLoading_Layer::onError( ErrorCode errorcode )");
		if(errorcode==UpdateProtocol::kNetwork)
		{
			UI_ModalDialogue_Layer::DoModal("", "network failed!", UI_ModalDialogue_Layer::DT_OK, [&](){ this->quit(); } );
		}
		else if(errorcode==UpdateProtocol::kCreateFile)
		{
			UI_ModalDialogue_Layer::DoModal("", "storage  failed!", UI_ModalDialogue_Layer::DT_OK, [&](){ this->quit(); } );
		}
		
	}

	void DownLoading_Layer::reboot()
	{
		/*
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		JniMethodInfo minfo;//定义Jni函数信息结构体     
		bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","reboot", "()V");
		if (!isHave)
		{
			CCLog("jni:deleteSOFile not exist ");
		}
		else
		{
			CCLog("jni:deleteSOFile exist");        //调用此函数
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
		}
#endif
		*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
        return;
#endif
        
        Director::getInstance()->end();
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
	}

	void DownLoading_Layer::onDecompressing( void )
	{
		//m_status_label->setString("onDecompressing");
	}
	void DownLoading_Layer::onGettingDownloadInfo()
	{
		m_status_label->setString("getting download info");
	}

	void DownLoading_Layer::beforeProgress( void )
	{
		m_status_label->setString("Downloading...");
	}
	void DownLoading_Layer::installAPK()
	{
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//		Dependence::installAPK();
#endif
	}
	void DownLoading_Layer::quit()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
        return;
#endif
        
        Director::getInstance()->end();
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
	}

}



