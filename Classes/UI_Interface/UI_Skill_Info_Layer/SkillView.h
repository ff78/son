#ifndef _SKILLVIEW_
#define _SKILLVIEW_

#include "cocos2d.h"

USING_NS_CC;

using namespace ui;
class SkillView :public cocos2d::Layer
{
public:
	SkillView();
	~SkillView();
	CREATE_FUNC(SkillView);
	virtual bool init();

	virtual void onExit();
	virtual void onEnter();

	void playSkill(std::vector<std::string>* actionNames);
	void changeSkill(int leftIndex, int rightIndex);
	void moveCursor();
	void hideAllCursor();

	void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
    void animationEvent(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID);
    
	void setCurrentLevelSkillText();
	void setNextLevelSkillText();

	inline void setLeftIndex(int index){ _leftIndex = index; };
	inline void setRightIndex(int index){ _rightIndex = index; };

	inline bool isUpgradable(){ return _isUpgradable; };
	inline void setUpgradable(bool able){ _isUpgradable = able; };

private:
	void onCloseCallBack(Ref* pSender, Widget::TouchEventType type);
	void onUpgradeCallBack(Ref* pSender, Widget::TouchEventType type);

	void onUpgradeFromServer();

	void initScrollView();
	void initMyIcon();
	void loadScrollView();
	void loadMyIcon();

	int				_leftIndex;
	int				_rightIndex;
	int				_scrollViewSize = 6;
	bool			_isUpgradable;

	ui::ScrollView* _scrolView;
	ImageView*		_selectedImages[4];
	Text*			_currentSkillNameText;
	Text*			_currentSkillLevelText;
	Text*			_currentSkillDescText;

	Text*			_nextSkillNameText;
	Text*			_nextSkillLevelText;
	Text*			_nextSkillDescText;

	ImageView*		_arrowImage;

	cocos2d::Layer*		  _roleLayer;
	cocos2d::Layer*		  _frontLayer;
	cocos2d::Layer*		  _midLayer;
	cocostudio::Armature* _boneArmature;
	cocos2d::Layer*		  _backLayer;

    int armatureIndex;
    int animationCount;
};
#endif