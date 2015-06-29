#ifndef _UI_Friend_Cell_Layer_
#define _UI_Friend_Cell_Layer_

#include "cocos2d.h"

USING_NS_CC;

using namespace ui;

class UI_Friend_Cell_Layer : public Layout
{
public:
	UI_Friend_Cell_Layer();
	~UI_Friend_Cell_Layer();
	CREATE_FUNC(UI_Friend_Cell_Layer);

	virtual bool init();

	virtual void onExit();
	virtual void onEnter();

private:
	//---成员变量---//
	int							m_nCurrentCellIndex;												// 当前单元的索引
	int							m_nCurrentCellRoleID;												// 当前单元的好友ID

public:
	//---页面信息刷新---//
	void						RemoveCurrentCell();												// 移除当前单元
	void						RequestCurrentCellShowInfo();										// 获取当前单元的显示信息
	void						CurrentCellBeSelected(const bool bValue = false);					// 当前单元是否被选中
	void						DeleteCurrentFriend();												// 删除当前好友
	void						AllowToAddFriend();													// 允许添加好友

private:
	//---按钮方法回调---//	
	void						OnBtnBGCallBack(Ref* pSender, Widget::TouchEventType type);			// 背景图片点击回调						

private:
	//---Cocostudio文件---//
	ui::Text*					m_pNameText;														// 名字文本
	ui::Text*					m_pLevelText;														// 等级文本
	ui::Text*					m_pFighttingPowerText;												// 战斗力文本
	ui::Text*					m_pJobText;															// 职业文本

	ui::ImageView*				m_pSelectBoxImg;													// 选中框图片

public:
	//---获取与设置成员变量---//
	inline void		SetCurrentCellRoleID(const int nID)
	{
		m_nCurrentCellRoleID = nID;
	}

	inline int		GetCurrentCellRoleID()
	{
		return m_nCurrentCellRoleID;
	}

	inline void		SetCurrentCellIndex(const int nIndex)
	{
		m_nCurrentCellIndex = nIndex;
	}
	
};

#endif