#ifndef _UI_Bag_Gem_Layer_
#define _UI_Bag_Gem_Layer_

#include "cocos2d.h"

USING_NS_CC;

using namespace ui;

class UI_Bag_Gem_Layer : public cocos2d::Layer
{
public:
	UI_Bag_Gem_Layer();
	~UI_Bag_Gem_Layer();
	CREATE_FUNC(UI_Bag_Gem_Layer);

	virtual bool init();

	virtual void onExit();
	virtual void onEnter();

private:
	//---成员变量---//
	int										m_nCellTagID;															// 包裹每个格子的标识ID
	int										m_nCurrentSelectedTagID;												// 当前选中的材料的标识ID
	int										m_nCurrentEquipPos;														// 当前装备的位置

	map<int, Game_Data::Item_Container*>	m_mapTargetTagItem;														// 标识ID对应的ItemContainer

public:
	//---页面信息刷新---//
	void									LoadScrollView();														// 载入宝石滚动层
	void									RefreshWholeLayer();													// 刷新整个当前界面
	void									RefreshBagMaterial();													// 刷新背包里的材料
	void									RefreshMoneyAndGold();													// 刷新背包界面上的元宝和铜钱
	void									SetSelectedCellID();													// 设置当前默认选中的单元ID
	void									OpenMaterialTextAndBtn(const bool bValue_1 = false, const bool bValue_2 = false, const bool bValue_3 = false);// 打开材料的名字和按钮							
	void									ClearEachCell();														// 清除每个Cell里面的信息
	void									ChildRequestChangeLayerState(const Child_Layer_State eType);			// 子页面请求切换界面
	
	bool									SetSingleCellInfo(const int nTagID, Game_Data::Item_Container * pInfo);	// 设置单个Cell的信息

public:
	//---页面相关逻辑---//
	void									HandleSelectMaterial(const int nTagID);									// 处理选中的宝石
	void									SetSelcectedInfoForShow();												// 设置选中的材料用于显示的信息
	void									CloseCurrentLayer();													// 关闭当前界面

	bool									JudgeTargetMaterialIsExist(const int nTagID);							// 判断目标标识ID的材料是否存在
	bool									JudgeTargetMaterialCanFillIn(const int nTagID);							// 判读目标标识ID是否可以镶嵌
	bool									JudgeTargetMaterialCanCompound(const int nTagID);						// 判读目标标识ID是否可以合成

	uint64									GetTargetCellContainerID(const int nTagID);								// 获取目标单元格的ContainerID

	Game_Data::Item_Container *				GetTargetMaterialInfo(const int nTagID);								// 获取目标ID的信息

private:
	//---按钮方法回调---//	
	void									OnBtnCloseCallBack(Ref* pSender, Widget::TouchEventType type);			// 关闭按钮方法回调
	void									OnBtnFillInCallBack(Ref* pSender, Widget::TouchEventType type);			// 宝石镶嵌按钮方法回调
	void									OnBtnCompoundTextCallBack(Ref* pSender, Widget::TouchEventType type);	// 宝石合成按钮方法回调
	void									OnBtnClickMaterialCallBack(Ref* pSender, Widget::TouchEventType type);	// 点击材料的方法回调

private:
	//---Cocostudio文件---//
	ui::Text*								m_pGemNameText;				// 宝石名字文本

	ui::Button*								m_pCloseButton;				// 关闭按钮
	ui::Button*								m_pFillInButton;			// 宝石镶嵌按钮
	ui::Button*								m_pCompoundButton;			// 宝石合成按钮
	
	ui::TextAtlas*							m_pGoldTextAtlas;			// 元宝文本
	ui::TextAtlas*							m_pMoneyTextAtlas;			// 铜钱文本

	ui::ScrollView*							m_pBagGemScrollView;		// 背包滚动层
public:
	//---获取与设置成员变量---//
	inline void								SetCurrentEquipPos(const int nPos)
	{
		m_nCurrentEquipPos = nPos;
	}
};

#endif