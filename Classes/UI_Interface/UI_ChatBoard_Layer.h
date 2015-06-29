#ifndef __UI_CHAT_BOARD_LAYER__
#define __UI_CHAT_BOARD_LAYER__

#include <map>
#include <deque>
#include <string>

#include "cocos2d.h"
//#include "cocos-ext.h"
#include "Network_Common/global_macros.h"
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
#include "cocostudio/CocoStudio.h"
#include "Common/Utils.h"
USING_NS_CC;
//USING_NS_CC_EXT;
#define CHAT_CONTENT_SHOW_LENGTH  27
#define CHAT_CONTENT_LENGTH  50
#define SPILT "..."
using namespace ui;
enum CHATBOARD_UI_TAGS
{
	CHAT_NAME_LABEL_TAG = 0,
	CHAT_CONTENT_LABEL_TAG,

};

class UI_ChatBoard_Layer : public cocos2d::Layer
{
public:
	enum
	{
		MAX_HISTORY_RECORD = 16
	};

	CREATE_FUNC(UI_ChatBoard_Layer);
	UI_ChatBoard_Layer(void);
	~UI_ChatBoard_Layer(void);

public:
	virtual bool init();
	virtual void setVisible( bool visible );
	virtual void update();
public:
	void refreshChatContent(std::deque<std::string> deq);
    void addChatContent(int channel, const char* sender, const char* receiver, const char* szChatContent);
	//ֱ�Ӵ�˽��Ƶ��������˽�Ķ���
	void openPrivateChat(const char* receiver);
	// ����������¼���Ӧ����
	void textFieldEvent(Ref* pSender, cocos2d::ui::TextFiledEventType type);

private:
    void buttonCloseCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonSendCallback( Ref* pSender,Widget::TouchEventType type );
	void chatUIButtonCallback( Ref* pSender,Widget::TouchEventType type );

	//����������  ��� һ�а�ť ��ȫ�������硢���ɡ�˽�ġ�ϵͳ���棩
	void chatToAllCallback(Ref* pSender,Widget::TouchEventType type);
	void chatToWorldCallback(Ref* pSender,Widget::TouchEventType type);
	void chatToGuildCallback(Ref* pSender,Widget::TouchEventType type);
	void chatToSpecifiedPersonCallback(Ref* pSender,Widget::TouchEventType type);
	void chatForVisionSystemNoticeCallback(Ref* pSender,Widget::TouchEventType type);

	//�μ����� ��ť���رա�������Ϣ��˽�ġ���Ӻ��� ��
	void btnAddFrameCloseCallback( Ref* pSender,Widget::TouchEventType type );
	void btnOnlinePkCallback( Ref* pSender,Widget::TouchEventType type );
	void btnSecretChatCallback( Ref* pSender ,Widget::TouchEventType type);
	void addFriendForChat( Ref* pSender ,Widget::TouchEventType type);

	void btnStrangerAddCallback();
	void addFriendForChatCallback(Ref* pSender,Widget::TouchEventType type);

	std::string parseString (const char* str, const char* prase_str, size_t index);
	std::string parseName(const char* str, const char* left, const char* right);

private:
	void closeAddFriendFrame( void );
	void openAddFriendFrame( void );

private:
	std::string							m_friendName;		//��� Ҫ��Ӻ��� ������
	std::string							chat_content_str_;	//���������������������
	std::string							chat_show_content_;	//�����ʾ����������������
	cocos2d::ui::Text*					show_text_lable_;
	int									m_chatState;		//��¼��ǰ����״̬ ���������Ƿ��¼����
	//map ���� ��� ��ͬ����״̬������
	std::map<unsigned int, std::deque<std::string> > m_mapForDiff;

	static std::deque<std::string>		m_queWorldChat;		//�����������
	static std::deque<std::string>		m_queGuildChat;		//�����������
	static std::deque<std::string>		m_queSecretChat;	//˽�� ����
	static std::deque<std::string>		m_queAllChat;		//�ۺ� ����
	static std::deque<int>				m_queAllChatColor;	//�ۺ� ������ɫ

	static std::deque<std::string>		m_queFriendChat;	//˽�� ����
	static std::deque<std::string>		m_queTeamChat;		//��� ����
	static std::deque<std::string>		m_queAreaChat;		//�������

	Point								chatInputPos;		//����Layer�ĳ�ʼλ��
	Point								chatInputUpPos;		//����֮���λ��
	cocos2d::ui::TextField *	m_pInputBox;				//���������
	cocos2d::ui::Button*		m_pBtnChannel;				//��ǰƵ�� ��ť
	cocos2d::ui::Text*		m_pLabCurInfo;					//��ǰƵ����ʾ���� cocos2d::ui::Text
	cocos2d::ui::ImageView*	m_pImgAddFrame;					//������� �μ�����

	cocos2d::ui::ScrollView*	m_pScrollPanel;				//��Ϣ ������
	 

	//��� ��ť
	cocos2d::ui::Button*		m_pBtnAll;				//ȫ��
	cocos2d::ui::Button*		m_pBtnWorld;			//����
	cocos2d::ui::Button*		m_pBtnUnited;			//����
	cocos2d::ui::Button*		m_pBtnSecretChat;		//����
	cocos2d::ui::Button*		m_pBtnSystemNotice;		//ϵͳ����
	cocos2d::ui::Button*		btnOnlinePK;
	cocos2d::ui::Button*		btnSecretChat;
	cocos2d::ui::Button*		btnAddStranger;

	cocos2d::ui::Button*		txtButton[MAX_HISTORY_RECORD];
	cocos2d::ui::Widget*		m_aMsgs[MAX_HISTORY_RECORD];
	cocos2d::ui::Widget*        Pnl_Msg_Bg;
};

#endif //__UI_CHAT_BOARD_LAYER__