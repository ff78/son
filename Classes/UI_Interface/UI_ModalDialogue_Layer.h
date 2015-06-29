#ifndef __UI_MODAL_DIALOGUE_LAYER_H__
#define __UI_MODAL_DIALOGUE_LAYER_H__

#include "cocos2d.h"
//#include "cocos-ext.h"
#include <functional>
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include "ui/UITextField.h"
#include "ui/UILoadingBar.h"
#include "ui/UILayout.h"
#include "ui/UISlider.h"
#include "ui/UICheckBox.h"
#include "ui/UIWidget.h"
#include "ui/UIScrollView.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;
typedef std::function<void(void)> pCall;

class UI_ModalDialogue_Layer : public cocos2d::Layer
{
public:

	enum DialogueType
	{
		DT_NORMAL = 0,
		DT_OK,
		DT_YES_NO,
	};
	enum ResultTag
	{
		RT_OK = 0,
		RT_YES,
		RT_NO,
	};
private:
	UI_ModalDialogue_Layer(void);
	~UI_ModalDialogue_Layer(void);

	CREATE_FUNC(UI_ModalDialogue_Layer);

	virtual bool init();

public:
	static void DoModal(const char* szTitle,const char* szContent,DialogueType type=DT_NORMAL,pCall p=nullptr);
	static void HideModal();

private:
	void updateLayer(const char* szTitle,const char* szContent,DialogueType type,pCall p);
	void btn_Click( cocos2d::Ref* pSender,Widget::TouchEventType type );

private:
	static UI_ModalDialogue_Layer* s_pInstance;

	cocos2d::ui::Text*	m_pLabCaption;
	cocos2d::ui::Text*	m_pLabContent;
	cocos2d::ui::Button*		m_pBtn_Ok;
	cocos2d::ui::Button*		m_pBtn_Yes;
	cocos2d::ui::Button*		m_pBtn_No;

	cocos2d::ui::Text*		m_pLab_Ok;  
	cocos2d::ui::Text*		m_pLab_Yes;
	cocos2d::ui::Text*		m_pLab_No;

	DialogueType			m_Type;
	pCall					m_pFunc;
};

#endif //__UI_MODAL_DIALOGUE_LAYER_H__