#include "cocos2d.h"
#include <fstream>	
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Game_Interface/common.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player.h"

#include "SkillView.h"
#include "MyImageView.h"
using namespace ui;

MyImageView::MyImageView() :
_isSelected(false),
_isUpgradable(false),
_cursorImage(nullptr),
_backImage(nullptr),
_upgradeImage(nullptr),
_clone(nullptr),
_isFirstChanged(false),
_isSecondChanged(false),
_isThirdChanged(false),
_isForthChanged(false)
{
}

MyImageView::~MyImageView()
{
	_isSelected = false;
	_isUpgradable = false;
	_cursorImage = nullptr;
	_backImage = nullptr;
	_upgradeImage = nullptr;
	_clone = nullptr;

	_isFirstChanged = false;
	_isSecondChanged = false;
	_isThirdChanged = false;
	_isForthChanged = false;
}

ImageView* MyImageView::createCursor()
{
	_cursorImage = (ImageView*)this->clone();
	_cursorImage->loadTexture("img/headIcon/cursor.png");
	_cursorImage->setLocalZOrder(0);
	_cursorImage->setAnchorPoint(Vec2(0.f, 0.f));
	_cursorImage->setVisible(false);
	_cursorImage->setPosition(this->getPosition());

	return _cursorImage;

}

ImageView* MyImageView::createBackImage()
{
	_backImage = (ImageView*)this->clone();
	_backImage->loadTexture("img/headIcon/skill_back.png");
	_backImage->setAnchorPoint(Vec2(0.f, 0.f));
	_backImage->setPosition(this->getPosition());
	_backImage->setLocalZOrder(1);
	return _backImage;

}

ImageView* MyImageView::createClone()
{
	_clone = (ImageView*)this->clone();
	_clone->setAnchorPoint(Vec2(0.f, 0.f));
	_clone->setPosition(this->getPosition());
	_clone->setLocalZOrder(3);
	//_clone->onTouchBegan = nullptr;
	//_clone->onTouchMoved = nullptr;
	//_clone->onTouchEnded = nullptr;
	//_clone->onTouchCancelled = nullptr;
	return _clone;

}

bool MyImageView::init()
{
	if (!ImageView::init())
		return false;

	_cursorImage = ImageView::create();
	_cursorImage->loadTexture("img/headIcon/cursor.png");
	_cursorImage->setLocalZOrder(0);
	_cursorImage->setAnchorPoint(Vec2(0.f, 0.f));
	_cursorImage->setVisible(false);
	_cursorImage->setPosition( this->getPosition()-Vec2(12,12) );
	this->addChild(_cursorImage);

	this->loadTexture("img/headIcon/skill_back.png");
	this->setAnchorPoint( Vec2(0.f,0.f) );
	this->setLocalZOrder(2);


	_upgradeImage = ImageView::create();
	_upgradeImage->loadTexture("img/headIcon/up_up.png");
	_upgradeImage->setAnchorPoint(Vec2(0.f,0.f));
	_upgradeImage->setPosition( Vec2(0,0) );
	_upgradeImage->setVisible(false);
	this->addChild(_upgradeImage);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MyImageView::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MyImageView::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MyImageView::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(MyImageView::onTouchCancelled, this);
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;

}

void MyImageView::onExit()
{
	ImageView::onExit();
}

void MyImageView::onEnter()
{
	ImageView::onEnter();
}

void MyImageView::update(float dt)
{
	
}

bool MyImageView::onTouchBegan(Touch *touch, Event *unused_event)
{
	if ( containsTouchLocation(touch) )
		return true;
	else
		return false;
}

void MyImageView::onTouchMoved(Touch *touch, Event *unused_event)
{
	//if ( containsTouchLocation(touch) )
	//	;
	//else
	//{
		auto pos = this->convertTouchToNodeSpaceAR(touch) + Vec2(-7,-7+getTag()*100 );
		_clone->setPosition(pos);
	//}

}

void MyImageView::onTouchEnded(Touch *touch, Event *unused_event)
{
	auto skillView = (SkillView*)this->getParent()->getParent()->getParent()->getParent()->getParent()->getParent();
	if (containsTouchLocation(touch))
	{
		if (_isSelected)
		{
			skillView->hideAllCursor();
			_isSelected = false;
		}
		else
		{
			skillView->hideAllCursor();
			_isSelected = true;
		}
		_cursorImage->setVisible(_isSelected);

		int index = this->getTag();
		auto actions = (std::vector<std::string>*)(this->getUserData());

		if (_cursorImage->isVisible())skillView->playSkill(actions);

		skillView->setLeftIndex(index);
		skillView->setRightIndex(index);

		skillView->setCurrentLevelSkillText();
		skillView->setNextLevelSkillText();
	}

	log("the %d move ended,first %d,second %d,third %d,forth %d", getTag(), _isFirstChanged, _isSecondChanged, _isThirdChanged, _isForthChanged);

	_clone->setPosition(this->getPosition());
	_isFirstChanged = containsFirstLocation(touch);
	_isSecondChanged = containsSecondLocation(touch);
	_isThirdChanged = containsThirdLocation(touch);
	_isForthChanged = containsForthLocation(touch);

	if (_isFirstChanged)
	{
		int left = this->getTag();
		skillView->changeSkill(left, 0);
		return;
	}
	if (_isSecondChanged)
	{
		int left = this->getTag();
		skillView->changeSkill(left, 1);
		return;
	}
	if (_isThirdChanged)
	{
		int left = this->getTag();
		skillView->changeSkill(left, 2);
		return;

	}
	if (_isForthChanged)
	{
		int left = this->getTag();
		skillView->changeSkill(left, 3);
		return;

	}


}

void MyImageView::onTouchCancelled(Touch *touch, Event *unused_event)
{

}

Rect MyImageView::getRect()
{
	//int index = getTag();
	return Rect(0,0, 86, 86);
}

bool MyImageView::containsTouchLocation(Touch* touch)
{
	return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

cocos2d::Rect MyImageView::getRectFirst()
{
	Vec2 offset( this->getParent()->getPosition() );
	return Rect(630 + 0 - offset.x, 7 + 0 - offset.y, 86, 86);
}

cocos2d::Rect MyImageView::getRectSecond()
{
	Vec2 offset(this->getParent()->getPosition());
	return Rect(630 + 22 - offset.x, 7 + 100 - offset.y, 86, 86);

}

cocos2d::Rect MyImageView::getRectThird()
{
	Vec2 offset(this->getParent()->getPosition());

	return Rect(630 + 22 + 71 - offset.x, 7 + 100 + 76 - offset.y, 86, 86);

}

cocos2d::Rect MyImageView::getRectForth()
{
	Vec2 offset(this->getParent()->getPosition());
	return Rect(630 + 22 + 71 + 101 - offset.x, 7 + 100 + 76 + 34 - offset.y, 86, 86);

}

bool MyImageView::containsFirstLocation(Touch* touch)
{
	return getRectFirst().containsPoint(convertTouchToNodeSpaceAR(touch)- Vec2(0,-100*getTag() ) );

}

bool MyImageView::containsSecondLocation(Touch* touch)
{
	return getRectSecond().containsPoint( convertTouchToNodeSpaceAR(touch) - Vec2(0,-100 * getTag() ) );

}

bool MyImageView::containsThirdLocation(Touch* touch)
{
	return getRectThird().containsPoint(convertTouchToNodeSpaceAR(touch) - Vec2(0, -100 * getTag()));

}

bool MyImageView::containsForthLocation(Touch* touch)
{
	return getRectForth().containsPoint(convertTouchToNodeSpaceAR(touch) - Vec2(0, -100 * getTag()));

}

void MyImageView::setCursor(bool visible)
{
	_isSelected = visible;
	_cursorImage->setVisible(visible);
}