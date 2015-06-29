#ifndef __UI_FuBenDialog_H_
#define __UI_FuBenDialog_H_
#include "cocos2d.h"
//#include "cocos-ext.h"
#include "UI/Loading_Scene.h"
#include "Item_System/Item_Config_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
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
#include "ui/UIPageView.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
#include "cocostudio/CocoStudio.h"
using namespace UI;
USING_NS_CC;
//USING_NS_CC_EXT;
//USING_NS_CC;
using namespace ui;

class UI_FuBenDialog:public cocos2d::Layer
{
private:
	UI_FuBenDialog();
	virtual bool init();
	static UI_FuBenDialog* instance;
	void setVisibleAndMessage(bool isLeft,int imageId,int messageId);

	cocos2d::ui::Widget*				m_pwidget;
	cocos2d::ui::Layout*				m_ppnl_root;
	cocos2d::ui::ImageView*			m_pimg_left;
	cocos2d::ui::ImageView*			m_pimg_right;
	cocos2d::ui::Text*				m_ptea_left;
	cocos2d::ui::Text*				m_ptea_right;
	bool					is_first_;
	void setLayerVisible(float dt);
public:
	void pnlCallBack(Ref* pSender,Widget::TouchEventType type);
	static UI_FuBenDialog* sharedUI_FuBenDialog();
	void showDialogMessage(bool isLeft,int imageId,int messageId);
	void removeDialog();
	void onEnterTransitionDidFinish();
	void showRoleSpeakInfo(int messageId,cocos2d::ui::TextField* tea);

    void set_is_show(bool is_show){m_is_show = is_show;}
    bool get_is_show(){return m_is_show;}

private:
    bool    m_is_show;
};

#endif //__UI_FuBenDialog_H_