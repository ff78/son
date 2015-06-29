#ifndef _UI_SETTLEMENT_LAYER_
#define _UI_SETTLEMENT_LAYER_

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
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
#include "cocostudio/CocoStudio.h"
#define AWARD_INFO_NUM	3

//USING_NS_CC;
//USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;
class UI_Icon_Info_Layer;
class UI_Settlement_Layer : public cocos2d::Layer
{
public:
	UI_Settlement_Layer(void);
	virtual ~UI_Settlement_Layer(void);

public:
	virtual bool init();
	CREATE_FUNC(UI_Settlement_Layer);
	virtual void setVisible( bool visible );
	void showGuide();

	void settlementCloseCallback( cocos2d::Ref* pSender ,Widget::TouchEventType type);
	void showIconInfo(cocos2d::Ref* pSender,Widget::TouchEventType type);

	void settlementConfig();
	void update();
	void setStarsVisible();

private:
    int proc_instance_result(void);
	int m_star_count;
	cocos2d::ui::Widget*			m_pSettlementWidget_;	//UI���ڵ�

	cocos2d::ui::ImageView*		cocoIconGoods[AWARD_INFO_NUM];		//��Ʒ�������� 
	cocos2d::ui::ImageView*		cocoIconGoods_Texture[AWARD_INFO_NUM];//��Ʒ����ͼƬ
	cocos2d::ui::Text*			cocoIconGoods_Num[AWARD_INFO_NUM];

	cocos2d::ui::ImageView*		m_pImgWinOrLose;		//����ʤ�� ʧ�ܵ�ͼƬ��ʾ��Ϣ
	cocos2d::ui::Text*			m_pLabExp_1;			//���� �Ϸ��� EXP ����ֵ ��ֵ
	cocos2d::ui::Text*			m_pLabMoneyAward;		//���� ��Ǯ���� ��ֵ

	cocos2d::ui::Text*			m_pLabTimeScore;		//��ֵ ʱ��÷�
	cocos2d::ui::Text*			m_pLabDeadScore;		//��ֵ �����۷�
	cocos2d::ui::Text*			m_pLabVIPScore;			//��ֵ VIP����
	cocos2d::ui::Text*			m_pLabFinalScore;		//��ֵ ���յ÷�

	cocos2d::ui::ImageView*		m_pImgStartsForLevel[3];//���� ���
	cocos2d::ui::ImageView*		m_pImgHeadPhoto_1;		//����ͷ�� 1 ͼƬ
	cocos2d::ui::ImageView*		m_pImgHeadPhoto_2;		//����ͷ�� 2 ͼƬ


	//������ʾ��Ϣ ����
	cocos2d::ui::ImageView*		m_pImgLieuHeadBack;
	cocos2d::ui::Text*			m_pLabLieuEXP;
	cocos2d::ui::ImageView*		m_pImgLieuVIP;
	cocos2d::ui::Text*			m_pLabLieuExpNum;			//���� �·��� EXP ����ֵ ��ֵ
	cocos2d::ui::Text*			m_pLabLieuVIPNum;


	//Icon ��Ϣ��ʾ��
	UI_Icon_Info_Layer*			m_pLayerIconInfo;


	//��ʾ ���������Ϣ
	std::string					m_getGainAwardInfo;
	bool						isGainOrNot;
	
	cocos2d::ui::Button*					closeButton;
	cocos2d::ui::Text*					m_lab_close_btn_font;
private:
	enum guide_step
	{
		JUNIOR_GUIDE_STEP_11 = 11,
	};
};

#endif //_UI_SETTLEMENT_LAYER_