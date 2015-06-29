#include "MyEditBox.h"
#include "Player_Account/Profile.h"
#include "Common/GameDefine.h"
#include "Common/GameResource.h"

//USING_NS_CC;
//USING_NS_CC_EXT;
//using namespace ui;

MyEditBox* MyEditBox::instance_ = NULL;

MyEditBox::MyEditBox(void)
{
	auto vec = Vec2( Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2-100);
	int posX = 650;
	int posY = 400;
	Point visibleOrigin =Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize =Director::getInstance()->getVisibleSize();

	cocos2d::Size editBoxSize = Size(visibleSize.width/10+150, 55);

	m_pEditName_ = cocos2d::extension::EditBox::create(editBoxSize, Scale9Sprite::create(REMEMBER_PASSWORD_SELECT));
	m_pEditName_->setPosition(vec);
	m_pEditName_->setFont("American Typewriter.ttf",30);
	m_pEditName_->setFontSize(25);
	m_pEditName_->setFontColor(ccRED);
	m_pEditName_->setPlaceHolder(" ");
	m_pEditName_->setPlaceholderFontColor(ccWHITE);
	m_pEditName_->setMaxLength(8);
	m_pEditName_->setReturnType( cocos2d::extension::EditBox::KeyboardReturnType::DONE);
	m_pEditName_->setDelegate(this);
	addChild(m_pEditName_);

	m_pEditPassword_ = cocos2d::extension::EditBox::create(editBoxSize, Scale9Sprite::create(REMEMBER_PASSWORD_SELECT));
	m_pEditPassword_->setPosition( vec-Vec2(0,65) );
	m_pEditPassword_->setFont("American Typewriter.ttf",30);
	m_pEditPassword_->setFontColor(ccRED);
	m_pEditPassword_->setPlaceHolder(" ");
	m_pEditPassword_->setPlaceholderFontColor(ccWHITE);
	m_pEditPassword_->setMaxLength(6);
	m_pEditPassword_->setInputFlag(cocos2d::extension::EditBox::InputFlag::PASSWORD);
	m_pEditPassword_->setInputMode(cocos2d::extension::EditBox::InputMode::SINGLE_LINE);
	m_pEditPassword_->setDelegate(this);
	addChild(m_pEditPassword_);
}

MyEditBox::~MyEditBox(void)
{
	instance_ = NULL;
}

void MyEditBox::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
	CCLog("editBox %p DidBegin !", editBox);
}

void MyEditBox::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
	CCLog("editBox %p DidEnd !", editBox);
}

void MyEditBox::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text)
{
	CCLog("editBox %p TextChanged, text: %s ", editBox, text.c_str());
	/*int length = strlen(text.c_str());
	CCLog("length = %d",length);*/
}

void MyEditBox::editBoxReturn(cocos2d::extension::EditBox* editBox)
{
//	CCLog("editBox %p was returned !");
}

std::string MyEditBox::getName()
{
	m_sName_ = m_pEditName_->getText();
	return m_sName_;
}

MyEditBox* MyEditBox::get_instance()
{
	if(instance_==NULL)
	{
		instance_ = MyEditBox::create();
	}
	return instance_;
}

std::string MyEditBox::getPassword()
{
	m_sPassW_ = m_pEditPassword_->getText();
	return m_sPassW_;
}

bool MyEditBox::init()
{
	m_pEditName_->setText(Profile::getStringForKey(PROFILE_KEY_FIRST_USERNAME,"").c_str());
	m_pEditPassword_->setText(Profile::getStringForKey(PROFILE_KEY_FIRST_PASSWORD,"").c_str());
	/*
#if ((defined WIN32 && defined DEBUG) || (1==COCOS2D_DEBUG))
	m_pEditName_->setString("test22");
	m_pEditPassword_->setString("1");
#endif
	*/
	return true;
}

/*------------------- class ChatEditBox ---------------------*/
ChatEditBox* ChatEditBox::s_pInstance = nullptr;

std::string ChatEditBox::getContent()
{
	m_sContent = m_pEditContent->getText();
	return m_sContent;
}

bool ChatEditBox::init()
{
	m_pEditContent->setText("input from this");

	return true;
}

ChatEditBox::ChatEditBox(void)
{
	int posX = 650;
	int posY = 100;
	Point visibleOrigin =Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize =Director::getInstance()->getVisibleSize();

	cocos2d::Size editBoxSize = Size(500, 55);

	m_pEditContent = cocos2d::extension::EditBox::create(editBoxSize, Scale9Sprite::create(REMEMBER_PASSWORD_SELECT));
	m_pEditContent->setFont("American Typewriter.ttf", 30);
	m_pEditContent->setFontSize(25);
	m_pEditContent->setFontColor(ccRED);
	m_pEditContent->setPlaceHolder("this is just placeholder!");
	m_pEditContent->setPlaceholderFontColor(Color3B::WHITE);
	m_pEditContent->setReturnType(cocos2d::extension::EditBox::KeyboardReturnType::DONE);
	m_pEditContent->setDelegate(this);
	addChild(m_pEditContent);
}

ChatEditBox::~ChatEditBox(void)
{

}

ChatEditBox* ChatEditBox::getInstance()
{
	if (s_pInstance == nullptr)
		s_pInstance = new ChatEditBox;
	return s_pInstance;
}

void ChatEditBox::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
	log("ChatEditBox %p DidBegin !", editBox);
}

void ChatEditBox::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
	log("ChatEditBox %p DidEnd !", editBox);
}

void ChatEditBox::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text)
{
	log("ChatEditBox %p TextChanged, text: %s ", editBox, text.c_str());
	/*int length = strlen(text.c_str());
	CCLog("length = %d",length);*/
}

void ChatEditBox::editBoxReturn(cocos2d::extension::EditBox* editBox)
{
	log("ChatEditBox %p was returned !", editBox);

}

void ChatEditBox::SetPositionAndMaxContent(int nPosX, int nPosY, int nMaxContent)
{
	auto vec = Vec2(Director::getInstance()->getWinSize().width / 2 + nPosX, nPosY);
	m_pEditContent->setPosition(vec);
	m_pEditContent->setMaxLength(nMaxContent);
}

/************************************************************************/
// Í¨ÓÃÊäÈë¿ò
CommonEditBox::CommonEditBox(void)
{
}

CommonEditBox::~CommonEditBox(void)
{
}

CommonEditBox* CommonEditBox::create(Size size, const std::string& path)
{
	auto me = new CommonEditBox;
	if (me && me->init(size,path))
	{
		me->autorelease();
		return me;
	}
	else
	{
		delete me;
		me = NULL;
		return NULL;
	}

}

bool CommonEditBox::init()
{
	cocos2d::Size editBoxSize = Size(500, 55);
	m_pEditContent = cocos2d::extension::EditBox::create(editBoxSize, Scale9Sprite::create(REMEMBER_PASSWORD_SELECT));
	m_pEditContent->setFont("American Typewriter.ttf", 30);
	m_pEditContent->setFontSize(25);
	m_pEditContent->setFontColor(ccWHITE);
	m_pEditContent->setPlaceHolder(" ");
	m_pEditContent->setPlaceholderFontColor(Color3B::WHITE);
	m_pEditContent->setReturnType(cocos2d::extension::EditBox::KeyboardReturnType::DONE);
	m_pEditContent->setDelegate(this);
	m_pEditContent->setText("");
	addChild(m_pEditContent);

	return true;
}

bool CommonEditBox::init(Size size,const std::string& path)
{
	//m_pEditContent = cocos2d::extension::EditBox::create(size, Scale9Sprite::create(path));
	m_pEditContent = cocos2d::extension::EditBox::create(size, Scale9Sprite::create(REMEMBER_PASSWORD_SELECT));
	m_pEditContent->setFont("American Typewriter.ttf", 30);
	m_pEditContent->setFontSize(25);
	m_pEditContent->setFontColor(ccWHITE);
	m_pEditContent->setPlaceHolder(" ");
	m_pEditContent->setPlaceholderFontColor(Color3B::WHITE);
	m_pEditContent->setReturnType(cocos2d::extension::EditBox::KeyboardReturnType::DONE);
	m_pEditContent->setDelegate(this);
	m_pEditContent->setText("");
	addChild(m_pEditContent);

	return true;
}

void CommonEditBox::SetPositionAndMaxLength(int nPosX, int nPosY, int nMaxLength)
{
	auto vec = Vec2(Director::getInstance()->getWinSize().width / 2 + nPosX, nPosY);
	m_pEditContent->setPosition(vec);
	m_pEditContent->setMaxLength(nMaxLength);
}

std::string CommonEditBox::getContent()
{
	m_sContent = m_pEditContent->getText();
	return m_sContent;
}

void CommonEditBox::setContent(std::string str)
{
	m_pEditContent->setText( str.c_str() );
}

void CommonEditBox::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
	log("ChatEditBox %p DidBegin !", editBox);
}

void CommonEditBox::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
	log("ChatEditBox %p DidEnd !", editBox);
}

void CommonEditBox::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text)
{
	log("ChatEditBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void CommonEditBox::editBoxReturn(cocos2d::extension::EditBox* editBox)
{
	log("ChatEditBox %p was returned !", editBox);

}

BoardEditBox::BoardEditBox(void)
{
}

BoardEditBox::~BoardEditBox(void)
{

}

bool BoardEditBox::init()
{
	cocos2d::Size editBoxSize = Size(160, 240);
	m_pEditContent = cocos2d::extension::EditBox::create(editBoxSize, Scale9Sprite::create(REMEMBER_PASSWORD_SELECT));
	m_pEditContent->setFont("American Typewriter.ttf", 30);
	m_pEditContent->setFontSize(25);
	m_pEditContent->setFontColor(ccWHITE);
	m_pEditContent->setPlaceHolder(" ");
	m_pEditContent->setPlaceholderFontColor(Color3B::WHITE);
	m_pEditContent->setReturnType(cocos2d::extension::EditBox::KeyboardReturnType::DONE);
	m_pEditContent->setDelegate(this);
	m_pEditContent->setText("Board");
	addChild(m_pEditContent);

	return true;
}

void BoardEditBox::SetPositionAndMaxLength(int nPosX, int nPosY, int nMaxLength)
{
	auto vec = Vec2(Director::getInstance()->getWinSize().width / 2 + nPosX, nPosY);
	m_pEditContent->setPosition(vec);
	m_pEditContent->setMaxLength(nMaxLength);
}

std::string BoardEditBox::getContent()
{
	m_sContent = m_pEditContent->getText();
	return m_sContent;
}

void BoardEditBox::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
	log("ChatEditBox %p DidBegin !", editBox);
}

void BoardEditBox::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
	log("ChatEditBox %p DidEnd !", editBox);
}

void BoardEditBox::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text)
{
	log("ChatEditBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void BoardEditBox::editBoxReturn(cocos2d::extension::EditBox* editBox)
{
	log("ChatEditBox %p was returned !", editBox);

}

void BoardEditBox::setContent(std::string content)
{
	m_pEditContent->setText( content.c_str() );
}



SearchEditBox::SearchEditBox(void)
{
}

SearchEditBox::~SearchEditBox(void)
{

}

bool SearchEditBox::init()
{
	cocos2d::Size editBoxSize = Size(200, 55);
	m_pEditContent = cocos2d::extension::EditBox::create(editBoxSize, Scale9Sprite::create(REMEMBER_PASSWORD_SELECT));
	m_pEditContent->setFont("American Typewriter.ttf", 30);
	m_pEditContent->setFontSize(25);
	m_pEditContent->setFontColor(ccWHITE);
	m_pEditContent->setPlaceHolder(" ");
	m_pEditContent->setPlaceholderFontColor(Color3B::WHITE);
	m_pEditContent->setReturnType(cocos2d::extension::EditBox::KeyboardReturnType::DONE);
	m_pEditContent->setDelegate(this);
	m_pEditContent->setText("Search");
	addChild(m_pEditContent);

	return true;
}

void SearchEditBox::SetPositionAndMaxLength(int nPosX, int nPosY, int nMaxLength)
{
	auto vec = Vec2(Director::getInstance()->getWinSize().width / 2 + nPosX, nPosY);
	m_pEditContent->setPosition(vec);
	m_pEditContent->setMaxLength(nMaxLength);
}

std::string SearchEditBox::getContent()
{
	m_sContent = m_pEditContent->getText();
	return m_sContent;
}

void SearchEditBox::setContent(std::string str)
{
	m_pEditContent->setText( str.c_str() );
}

void SearchEditBox::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
	log("ChatEditBox %p DidBegin !", editBox);
}

void SearchEditBox::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
	log("ChatEditBox %p DidEnd !", editBox);
}

void SearchEditBox::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text)
{
	log("ChatEditBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void SearchEditBox::editBoxReturn(cocos2d::extension::EditBox* editBox)
{
	log("ChatEditBox %p was returned !", editBox);

}


RenameEditBox::RenameEditBox(void)
{
}

RenameEditBox::~RenameEditBox(void)
{

}

bool RenameEditBox::init()
{
	cocos2d::Size editBoxSize = Size(200, 55);
	m_pEditContent = cocos2d::extension::EditBox::create(editBoxSize, Scale9Sprite::create(REMEMBER_PASSWORD_SELECT));
	m_pEditContent->setFont("American Typewriter.ttf", 30);
	m_pEditContent->setFontSize(25);
	m_pEditContent->setFontColor(ccWHITE);
	m_pEditContent->setPlaceHolder("ShowName");
	m_pEditContent->setPlaceholderFontColor(Color3B::WHITE);
	m_pEditContent->setReturnType(cocos2d::extension::EditBox::KeyboardReturnType::DONE);
	m_pEditContent->setDelegate(this);
	m_pEditContent->setText("DayAndDay");
	addChild(m_pEditContent);
	return true;
}

void RenameEditBox::SetPositionAndMaxLength(int nPosX, int nPosY, int nMaxLength)
{
	auto vec = Vec2(Director::getInstance()->getWinSize().width / 2 + nPosX, nPosY);
	m_pEditContent->setPosition(vec);
	m_pEditContent->setMaxLength(nMaxLength);
}

std::string RenameEditBox::getContent()
{
	m_sContent = m_pEditContent->getText();
	return m_sContent;
}

void RenameEditBox::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
	log("ChatEditBox %p DidBegin !", editBox);
}

void RenameEditBox::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
	log("ChatEditBox %p DidEnd !", editBox);
}

void RenameEditBox::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text)
{
	log("ChatEditBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void RenameEditBox::editBoxReturn(cocos2d::extension::EditBox* editBox)
{
	log("ChatEditBox %p was returned !", editBox);

}