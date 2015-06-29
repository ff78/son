#include "MyPageView.h"


//using namespace cocos2d;
//using namespace cocos2d::extension;

MyPageView* MyPageView::create(Size size,MyPageViewDelegate* pDelegate)
{
	auto page = new MyPageView;

	if (page && page->init(size, pDelegate))
	{
		page-> autorelease();
	}
	else
	{
		CC_SAFE_RELEASE(page);
	}

	return page;

}

bool MyPageView::init(Size size,MyPageViewDelegate* pDelegate)
{
	if (!ScrollView::initWithViewSize(size))
		return false;
	
	CCASSERT(pDelegate,"delegate should not be NULL!");
	setDelegate(pDelegate);
	if (_delegate)
		pageSize = _delegate->sizeForPerPage();

	pageCount = 0;
	current_index = 0;
	current_offset = 0.0f;
	//this->setTouchEnabled(false);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch, Event* evnt)
	{
		_dragging = false;
		//this->scheduleUpdate();
		if (_direction == ScrollView::Direction::HORIZONTAL)
			current_offset = this->getContentOffset().x;
		else
			current_offset = this->getContentOffset().y;
		//auto target = static_cast<Sprite*>(evnt->getCurrentTarget());
		auto target = evnt->getCurrentTarget();

		//return true;

		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0,0,s.width,s.height);
		if (rect.containsPoint(locationInNode))
		{
			return true;
		}

		return false;

	};

	listener->onTouchMoved = [&](Touch* touch,Event* evnt)
	{
		float start, end;
		if (_direction==ScrollView::Direction::HORIZONTAL)
		{
			start = touch->getStartLocation().x;
			end = touch->getLocation().x;
		}
		else
		{
			start = touch->getStartLocation().y;
			end = touch->getLocation().y;
		}
		float offset = end - start;
		if (_direction == ScrollView::Direction::HORIZONTAL)
			this->setContentOffset(Vec2(current_offset + offset * SCROLL_SPEED, 0));
		else
			this->setContentOffset(Vec2(0, current_offset + offset * SCROLL_SPEED));

	};

	listener->onTouchEnded = [&](Touch* touch,Event* evnt)
	{
		float start = current_offset, end;
		if (_direction == ScrollView::Direction::HORIZONTAL)
			end = this->getContentOffset().x;
		else
			end = this->getContentOffset().y;

		float offset = end - start;
		this->adjust(offset);
		//_dragging = true;
	};

	listener->setSwallowTouches(false);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,-1);

	return true;

}

void MyPageView::adjust(float offset)
{
	Vec2 vec;
	float xOrY;
	if (_direction == ScrollView::Direction::HORIZONTAL)
	{
		vec = Vec2( -( current_index * (pageSize.width) ),0 );
		xOrY = pageSize.width;
	}
	else
	{
		vec = Vec2(0, -(current_index * (pageSize.height) ) );
		xOrY = pageSize.height;
	}

	if (abs(offset) < 50)
	{
		this->setContentOffsetInDuration(vec, 0.15f);
		return;
	}

	int i = abs(offset/xOrY) + 1;
	if (offset < 0)
		current_index += i;
	else
		current_index -= i;

	if (current_index < 0)
		current_index = 0;
	else if (current_index>pageCount - 1)
		current_index = pageCount - 1;

	if (_direction == ScrollView::Direction::HORIZONTAL)
		vec = Vec2( -( current_index * (pageSize.width) ), 0 );
	else
		vec = Vec2( 0,-( current_index * (pageSize.height) ) );

	this->setContentOffsetInDuration(vec, 0.15f);

}

void MyPageView::setContentOffset(Vec2 offset)
{
	ScrollView::setContentOffset(offset);
	if (_delegate != nullptr)
		_delegate->pageViewDidScroll(this);
}

void MyPageView::setContentOffsetInDuration(Vec2 offset, float dt)
{
	//ScrollView::setContentOffsetInDuration(offset,dt);
	FiniteTimeAction *scroll, *expire;
	scroll = MoveTo::create(dt, offset);
	expire = CallFuncN::create( CC_CALLBACK_1(MyPageView::stoppedAnimatedScroll, this) );

	_container->runAction(Sequence::create(scroll, expire, nullptr));

	this->schedule(schedule_selector(MyPageView::performedAnimatedScroll));

}

void MyPageView::performedAnimatedScroll(float dt)
{
	if (_delegate != nullptr)
		_delegate->pageViewDidScroll(this);
	
}

void MyPageView::addPage(Node* node)
{
	if (_direction == ScrollView::Direction::HORIZONTAL)
	{
		node->setPosition( Vec2(pageCount*pageSize.width+node->getPositionX(),node->getPositionY() ) );
		this->setContentSize( Size( (pageCount+1)*pageSize.width,pageSize.height) );
	}
	else
	{
		node->setPosition( Vec2(node->getPositionX(),pageCount*pageSize.height+node->getPositionY() ) );
		this->setContentSize( Size(pageSize.width,(pageCount+1)*pageSize.height) );
	}

	//node->setTag(pageCount+MyPAGEVIEW_TAG);
	char str[10] = { 0 };
	sprintf(str, "%d", pageCount);
	node->setName(str);
	_container->addChild(node);

	pageCount++;
}

Node* MyPageView::getPageAtIndex(int index)
{

	if (index < pageCount&&index >= 0)
	{
		char name[10] = { 0 };
		sprintf(name, "%d", index);
		return _container->getChildByName(name);
	}

		//return _container->getChildByTag(index);

	return nullptr;
}

int MyPageView::getCurrentIndex()
{
	return current_index;
}

void MyPageView::stoppedAnimatedScroll(Node * node)
{
	ScrollView::stoppedAnimatedScroll(this);

	this->unschedule(schedule_selector(MyPageView::performedAnimatedScroll));

	if (_delegate != nullptr)
	{
		_delegate->myPageViewTurned();
	}
	//return current_index;
}

void MyPageView::scrollToPage(int index)
{
	if (_direction == ScrollView::Direction::HORIZONTAL)
		this->setContentOffset(Vec2( -index* COIN_WIDTH * SCROLL_SPEED, 0));
	else
		this->setContentOffset(Vec2(0, index* COIN_WIDTH * SCROLL_SPEED) );
	current_offset = index* COIN_WIDTH * SCROLL_SPEED;
	current_index = index;

}

void MyPageView::removeAllPage()
{
	_container->removeAllChildren();

	pageCount = 0;

	if (_direction == ScrollView::Direction::HORIZONTAL)
	{
		this->setContentSize(Size((pageCount + 1)*pageSize.width, pageSize.height));
	}
	else
	{
		this->setContentSize(Size(pageSize.width, (pageCount + 1)*pageSize.height));
	}



}
