//efghi
#ifndef _MyImageView_
#define _MyImageView_

#include "cocos2d.h"

USING_NS_CC;

using namespace ui;

class MyImageView : public ImageView
{
public:
	MyImageView();
	~MyImageView();
	CREATE_FUNC(MyImageView);

	ImageView* createCursor();
	ImageView* createBackImage();
	ImageView* createClone();

	virtual bool init();

	virtual void onExit();
	virtual void onEnter();
	virtual void update(float dt);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);

	Rect getRect();
	bool containsTouchLocation(Touch* touch);

	Rect getRectFirst();
	bool containsFirstLocation(Touch* touch);

	Rect getRectSecond();
	bool containsSecondLocation(Touch* touch);

	Rect getRectThird();
	bool containsThirdLocation(Touch* touch);

	Rect getRectForth();
	bool containsForthLocation(Touch* touch);

	inline bool isSelected(){ return _isSelected; };
	inline void setSelected(bool isSelected){  _isSelected = isSelected; };

	inline bool isFirstChanged(){ return _isFirstChanged; };
	inline bool isSecondChanged(){ return _isSecondChanged; };
	inline bool isThirdChanged(){ return _isThirdChanged; };
	inline bool isForthChanged(){ return _isForthChanged; };

	void		setCursor(bool visible);
    std::vector<std::vector<std::string>> frontEff;
    std::vector<std::vector<float>> frontScale;
    std::vector<std::vector<std::string>> backEff;
    std::vector<std::vector<float>> backScale;
private:
	bool		_isSelected;
	bool        _isUpgradable;
	ImageView*  _cursorImage;
	ImageView*  _backImage;
	ImageView*  _upgradeImage;
	ImageView*	_clone;
	//int			_index;
	bool		_isFirstChanged = false;
	bool		_isSecondChanged = false;
	bool		_isThirdChanged = false;
	bool		_isForthChanged = false;

};
#endif