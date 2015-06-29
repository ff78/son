#ifndef __MY_PAGEVIEW__
#define __MY_PAGEVIEW__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

using namespace cocos2d;
//using namespace cocos2d::extension;

#define COIN_WIDTH 320
#define COIN_HEIGHT 160
#define COIN_GAP 40
#define COIN_COUNT 10
#define MyPAGEVIEW_TAG 10086
#define SCROLL_SPEED 1.1

class MyPageView;

class MyPageViewDelegate
{
public:
	MyPageViewDelegate(){};
	virtual ~MyPageViewDelegate(){};
	virtual Size sizeForPerPage() = 0;
	virtual void pageViewDidScroll(MyPageView* pageView){};
	virtual void myPageViewTurned() = 0;
};

class MyPageView : public cocos2d::extension::ScrollView
{
private:
	void performedAnimatedScroll(float dt);
	int current_index;
	float current_offset;

	//std::function<void(MyPageView)> adjustCallback;
	void adjust(float offset);
	Size pageSize;

	CC_SYNTHESIZE(MyPageViewDelegate*,_delegate,Delegate);

	int pageCount;
	void addPage(Node* node);
	void removeAllPage();
	Node* getPageAtIndex(int index);
	int getCurrentIndex();
	std::function<void(MyPageView*)> adjustCallback;

	void setPageSize(Size size);

	void stoppedAnimatedScroll(Node * node);

	void scrollToPage(int index);

	virtual bool init(Size size, MyPageViewDelegate* pDelegate);

	virtual void setContentOffsetInDuration(Vec2 offset, float dt);
	virtual void setContentOffset(Vec2 offset);

	static MyPageView* create(Size size, MyPageViewDelegate* pDelegate);

};
#endif
