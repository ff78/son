#ifndef _UI_Ranking_List_Cell_Layer_
#define _UI_Ranking_List_Cell_Layer_

#include "cocos2d.h"

USING_NS_CC;

using namespace ui;

class UI_Ranking_List_Cell_Layer : public Layout
{
public:
	UI_Ranking_List_Cell_Layer();
	~UI_Ranking_List_Cell_Layer();
	CREATE_FUNC(UI_Ranking_List_Cell_Layer);

	virtual bool init();

	virtual void onExit();
	virtual void onEnter();

private:
	//---成员变量---//
	int							m_nCurrentCellIndex;												// 当前单元的索引

public:
	//---页面信息刷新---//
	void						RemoveCurrentCell();												// 移除当前单元
	void						RequestCurrentCellShowInfo();										// 获取当前单元的显示信息
	void						CurrentCellBeSelected(const bool bValue = false);					// 当前单元是否被选中

private:
	//---按钮方法回调---//	
	void						OnBtnBGCallBack(Ref* pSender, Widget::TouchEventType type);			// 背景图片点击回调					

private:
	//---Cocostudio文件---//
	ui::Text*					m_pRankingText;														// 名次文本
	ui::Text*					m_pNameText;														// 名字文本
	ui::Text*					m_pChangeAttributeText;												// 属性文本
	ui::Text*					m_pJobText;															// 职业文本

	ui::ImageView*				m_pSelectBoxImg;													// 选中框图片

public:
	//---获取与设置成员变量---//
	inline void		SetCurrentCellIndex(const int nIndex)
	{
		m_nCurrentCellIndex = nIndex;
	}

	inline int		GetCurrentCellIndex()
	{
		return m_nCurrentCellIndex;
	}
};

#endif