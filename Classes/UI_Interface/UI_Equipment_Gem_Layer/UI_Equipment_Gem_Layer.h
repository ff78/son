#ifndef _UI_Equipment_Gem_Layer_
#define _UI_Equipment_Gem_Layer_

#include "cocos2d.h"

USING_NS_CC;

#define MAX_GEM_COUNT 5
using namespace ui;
class UI_Equipment_Gem_Layer :public cocos2d::Layer
{
public:
	UI_Equipment_Gem_Layer();
	~UI_Equipment_Gem_Layer();
	CREATE_FUNC(UI_Equipment_Gem_Layer);
	virtual bool init();

	virtual void onExit();
	virtual void onEnter();

private:
	//---成员变量---//
	int									m_nCellCount;											// 滚动层要显示的宝石的个数
	int									m_nScrollviewHeight;									// 滚动层的高度
	int									m_nCellHeight;											// 每个宝石单元的高度
	int									m_nCurrentCellID;										// 当前选择的Cell的TagID

	uint64								m_nEquipItemID;											// 当前装备的ItemID

public:
	//---装备宝石界面相关界面刷新逻辑---//
	void								RefreshEquipGemLayer();									// 刷新装备宝石界面
	void								SetSelectedCellID();									// 设置当前默认的单元ID
	void								RefreshEquipmentBaseInfo();								// 刷新物品装备的基础信息
	void								RefreshEquipmentGem();									// 刷新物品装备的宝石
	void								LoadScrollView();										// 载入宝石滚动层
	void								SetScrollViweCell();									// 载入宝石滚动层单元
	void								ShowTargetCellGemInfo();								// 显示当前选中单元的宝石的信息
	void								ShowCurrentGemDesAndBtn(const bool bvalue = false);		// 显示当前选中单元的描述信息和按钮
	void								ClearEachCell();										// 清除每个Cell里面的信息
	void								ChangeOtherLayerState(const Child_Layer_State eType);	// 切换到其余页面状态

	bool								JudgeTargetGemInCurrentEquip(const uint64 nGemID);		// 当前装备中是否存在目标宝石		
    void onCloseCallBack(Ref* pSender, ui::Widget::TouchEventType type);
private:
	//---按钮方法回调---//	
	void								OnBtnStrengthenTextCallBack(Ref* pSender, Widget::TouchEventType type);			// 强化按钮方法回调
	void								OnBtnStarUpTextCallBack(Ref* pSender, Widget::TouchEventType type);				// 升星按钮方法回调
	void								OnBtnWashCallBack(Ref* pSender, Widget::TouchEventType type);				    // 洗炼按钮方法回调
	void								onGemCallback(Ref* pSender, Widget::TouchEventType type);
	void								OnBtnSetOffGemhCallBack(Ref* pSender, Widget::TouchEventType type);				// 卸下宝石方法回调

private:
	//---Cocostudio文件---//
	ui::Button*							m_pEquipStrengthenText;									// 强化文本
	ui::Button*							m_pEquipStarUpText;										// 升星文本
	ui::Button*							m_pEquipWashText;										// 洗炼文本
	ui::Button*							_gemButtom;										// 洗炼文本

	ui::Text*							m_pEquipNameText;										// 装备名字文本
	ui::Text*							m_pEquipLevelText;										// 装备需要等级文本
	ui::Text*							m_pEquipDescribeText;									// 装备描述文本

	ui::Button*							m_pEquipSetOffGemBtn;									// 装备卸下宝石

	ui::ImageView*						m_pEquipIcon;											// 装备图片
	ui::ImageView*						m_pEquipDescribeBGImage;								// 装备描述背景图片

	ui::ScrollView*						m_pGemScrollView;										// 宝石的滚动层

    ui::Button*							m_pCloseBtn;
public:
	//---获取和设置成员变量---//
	inline void							SetCurrentEquipItemID(const uint64 nItemID)
	{
		m_nEquipItemID		= nItemID;
	}

	inline void							SetCurrentCellTagID(const int nCellTagID)
	{
		m_nCurrentCellID	= nCellTagID;
	}
};

#endif