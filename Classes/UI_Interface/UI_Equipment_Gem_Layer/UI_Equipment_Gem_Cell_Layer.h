//efghi
#ifndef _UI_Equipment_Gem_Cell_Layer_
#define _UI_Equipment_Gem_Cell_Layer_

#include "cocos2d.h"

USING_NS_CC;

using namespace ui;

class UI_Equipment_Gem_Cell_Layer : public Layout
{
public:
	UI_Equipment_Gem_Cell_Layer();
	~UI_Equipment_Gem_Cell_Layer();
	CREATE_FUNC(UI_Equipment_Gem_Cell_Layer);

	virtual bool init();

	virtual void onExit();
	virtual void onEnter();

private:
	//---成员变量---//
	int							m_nCellTagID;														// 单元标识ID

	uint64						m_nCellGemID;														// 单元内宝石ID

public:
	//---页面信息刷新---//
	void						SetCurrentGemInfoForShow(const uint64 nGemID);						// 设置当前的宝石用于显示的信息
	void						ClearGemInfo();														// 清除宝石信息

private:
	//---按钮方法回调---//	
	void						OnBtnClickCellCallBack(Ref* pSender, Widget::TouchEventType type);	// 点击Cell按钮方法回调

private:
	//---Cocostudio文件---//
	ui::Text*					m_pIconTitleText;

	ui::ImageView*              m_pIconImageViwe;
	ui::ImageView*              m_pIconImageBGViwe;
	ui::ImageView*              m_pGemSelectedBoxImageViwe;											// 宝石选择框

public:
	//---获取与设置成员变量---//
	inline void SetCellTagID(const int nID)
	{
		m_nCellTagID = nID;
	}

	inline int GetCellTagID()
	{
		return m_nCellTagID;
	}

	inline int GetCellGemID()
	{
		return m_nCellGemID;
	}

	inline void SetSelectedBoxState(const bool bValue = false)
	{
		m_pGemSelectedBoxImageViwe->setVisible(bValue);
	}
};

#endif