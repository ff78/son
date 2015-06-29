#ifndef __UI_UPDATELAYER_H__
#define __UI_UPDATELAYER_H__
#include "cocos2d.h"
//#include "cocos-ext.h"
#include "Update_Logic/UpdateProtocol.h"
#include "Platform_Dependence/Dependence.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include "ui/UITextField.h"
#include "ui/UILoadingBar.h"
#include "ui/UILayout.h"
#include "ui/UISlider.h"
#include "ui/UICheckBox.h"
#include "ui/UIWidget.h"
#include "ui/UIScrollView.h"
#include "ui/UIText.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
#include "cocostudio/CocoStudio.h"
//USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;
#define UPDATELAYERTAG  789345
class UI_UpdateLayer:public cocos2d::Layer,public UpdateProtocol
{
public:
	virtual bool init();
	CREATE_FUNC(UI_UpdateLayer);
	void onProgress(int persent,int current,int all );
	void onSuccess( ErrorCode errorCode );
	void onError( ErrorCode errorcode );
	virtual void onGettingDownloadInfo();
	virtual void onEnter();
	virtual void stopUpdate();
	void userStop(Ref* pSender,Widget::TouchEventType type);
private:
	void reboot();
	void installAPK();
	void quit();
	//void reDownLoad();


	cocos2d::ui::Widget*							m_widget;
	cocos2d::ui::Text*							m_lab_tips;
	cocos2d::ui::Text*							m_lab_progress;
	cocos2d::ui::LoadingBar*						m_ldb_progress;
	cocos2d::ui::Button*							m_btn_exit_update;
	cocos2d::ui::Text*							m_lab_exit_update;
	
};
#endif //__UI_UPDATELAYER_H__

