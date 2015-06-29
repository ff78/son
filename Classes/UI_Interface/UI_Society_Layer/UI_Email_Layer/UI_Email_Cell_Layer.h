#ifndef _UI_Email_Cell_Layer_
#define _UI_Email_Cell_Layer_

#include "cocos2d.h"

USING_NS_CC;

using namespace ui;

class UI_Email_Cell_Layer : public Layout
{
public:
	UI_Email_Cell_Layer();
	~UI_Email_Cell_Layer();
	CREATE_FUNC(UI_Email_Cell_Layer);

	virtual bool init();

	virtual void onExit();
	virtual void onEnter();

	//---成员变量---//
	int							m_nCurrentCellIndex;												// 当前单元的索引

	bool						m_bCurrentCellBeSelected;											// 当前单元被选中
	
public:
	//---页面信息刷新---//
	void						eventShowOpen();
	void						RemoveCurrentCell();												// 移除当前单元
	void						CurrentCellBeSelected(const bool bValue = false);					// 当前单元是否被选中
	void						RequestCurrentCellShowInfo();										// 获取当前单元的显示信息

private:
	//---按钮方法回调---//	
	void						OnBtnBGCallBack(Ref* pSender, Widget::TouchEventType type);			// 背景图片点击回调		

public:
	//---Cocostudio文件---//
	ui::Text*					m_pNameText;														// 名字文本
	ui::Text*					m_pContentText;														// 内容文本
	ui::Text*					m_pDateText;														// 日期文本
	ui::Text*					m_pDaysText;														// 天数文本

	ui::ImageView*				m_pSelectBoxImg;													// 选中框图片
	ui::ImageView*				m_pOfficialImg;														// 是否为官方图片
	ui::ImageView*				m_pBeReadImg;														// 是否被阅读图片
	ui::ImageView*				m_pPresentImg;														// 附件图片

public:
	//---获取与设置成员变量---//
	// 设置当前单元的索引
	inline	void				SetCurrentCellIndex(const int nIndex)
	{
		m_nCurrentCellIndex = nIndex;
	}
};

#endif