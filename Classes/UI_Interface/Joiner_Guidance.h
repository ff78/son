#ifndef __JOINER_GUIDANCE__
#define __JOINER_GUIDANCE__

#include "cocos2d.h"
//#include "cocos-ext.h"
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include "ui/UITextField.h"
#include "ui/UILoadingBar.h"
#include "ui/UILayout.h"
#include "ui/UISlider.h"
#include "ui/UICheckBox.h"
#include "ui/UIWidget.h"
#include "ui/UIScrollView.h"
#include "ui/UIDeprecated.h"
#include "ui/UIHelper.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;
USING_NS_CC;
//USING_NS_CC_EXT;

//设置引导信息提示文字的大小
#define  GUIDE_INFO_SIZE			25
#define  GUIDE_INFO_ZORDER			50
#define  GUIDE_TYPE					4

class Joiner_Guidance : public cocos2d::Layer
{
private:
	Joiner_Guidance(void);
	~Joiner_Guidance(void);

 	virtual bool init();
 	CREATE_FUNC(Joiner_Guidance);
	virtual void setVisible(bool visible);

public:
	static void receiveCurPosWidget( cocos2d::ui::Widget* widget );
	static void receiveCurPosWidget( const Point &point );
	static void showGuide( float posX = 0, float posY = 0, cocos2d::ui::Widget* widget = 0 );
	static void hideGuide();
	void showGuideContent(Point handPoint, int infoId, int img_index = 1, cocos2d::ui::Widget* widget = 0);
	void resetUI();
private:
	static Joiner_Guidance*		m_pInstance;

	cocos2d::ui::ImageView*		m_pImgGuideInfoBack[GUIDE_TYPE];		//guide information back
	cocos2d::ui::Text*			m_pLabGuideInfo[GUIDE_TYPE];			//guide information
	

};


#endif //__JOINER_GUIDANCE__

/*
class Joiner_Guidance;
Joiner_Guidance*			juniorGuide;

#include "Joiner_Guidance.h"
juniorGuide(NULL)
//手势
if(!juniorGuide)
{
juniorGuide = Joiner_Guidance::create();
this->addChild(juniorGuide);
juniorGuide->setVisible(true);
juniorGuide->setZOrder(GUIDE_INFO_ZORDER);
}
Point point(100, 100);
juniorGuide->showGuideContent(point, JUNIOR_GUIDE_ASTAR);
*/