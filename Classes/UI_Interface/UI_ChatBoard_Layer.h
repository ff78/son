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
	//直接打开私聊频道并设置私聊对象
	void openPrivateChat(const char* receiver);
	// 聊天输入框事件响应函数
	void textFieldEvent(Ref* pSender, cocos2d::ui::TextFiledEventType type);

private:
    void buttonCloseCallback( Ref* pSender ,Widget::TouchEventType type);
	void buttonSendCallback( Ref* pSender,Widget::TouchEventType type );
	void chatUIButtonCallback( Ref* pSender,Widget::TouchEventType type );

	//聊天主界面  左侧 一列按钮 （全部、世界、门派、私聊、系统公告）
	void chatToAllCallback(Ref* pSender,Widget::TouchEventType type);
	void chatToWorldCallback(Ref* pSender,Widget::TouchEventType type);
	void chatToGuildCallback(Ref* pSender,Widget::TouchEventType type);
	void chatToSpecifiedPersonCallback(Ref* pSender,Widget::TouchEventType type);
	void chatForVisionSystemNoticeCallback(Ref* pSender,Widget::TouchEventType type);

	//次级界面 按钮（关闭、人物信息、私聊、添加好友 ）
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
	std::string							m_friendName;		//存放 要添加好友 的名称
	std::string							chat_content_str_;	//存放聊天框输入的完整内容
	std::string							chat_show_content_;	//存放显示在聊天框里面的内容
	cocos2d::ui::Text*					show_text_lable_;
	int									m_chatState;		//记录当前聊天状态 （服务器是否记录？）
	//map 容器 存放 不同聊天状态的内容
	std::map<unsigned int, std::deque<std::string> > m_mapForDiff;

	static std::deque<std::string>		m_queWorldChat;		//世界聊天队列
	static std::deque<std::string>		m_queGuildChat;		//门派聊天队列
	static std::deque<std::string>		m_queSecretChat;	//私聊 队列
	static std::deque<std::string>		m_queAllChat;		//综合 队列
	static std::deque<int>				m_queAllChatColor;	//综合 队列颜色

	static std::deque<std::string>		m_queFriendChat;	//私聊 队列
	static std::deque<std::string>		m_queTeamChat;		//组队 队列
	static std::deque<std::string>		m_queAreaChat;		//区域队列

	Point								chatInputPos;		//聊天Layer的初始位置
	Point								chatInputUpPos;		//上来之后的位置
	cocos2d::ui::TextField *	m_pInputBox;				//聊天输入框
	cocos2d::ui::Button*		m_pBtnChannel;				//当前频道 按钮
	cocos2d::ui::Text*		m_pLabCurInfo;					//当前频道显示文字 cocos2d::ui::Text
	cocos2d::ui::ImageView*	m_pImgAddFrame;					//好友添加 次级界面

	cocos2d::ui::ScrollView*	m_pScrollPanel;				//消息 滚动层
	 

	//左侧 按钮
	cocos2d::ui::Button*		m_pBtnAll;				//全部
	cocos2d::ui::Button*		m_pBtnWorld;			//世界
	cocos2d::ui::Button*		m_pBtnUnited;			//门派
	cocos2d::ui::Button*		m_pBtnSecretChat;		//秘语
	cocos2d::ui::Button*		m_pBtnSystemNotice;		//系统公告
	cocos2d::ui::Button*		btnOnlinePK;
	cocos2d::ui::Button*		btnSecretChat;
	cocos2d::ui::Button*		btnAddStranger;

	cocos2d::ui::Button*		txtButton[MAX_HISTORY_RECORD];
	cocos2d::ui::Widget*		m_aMsgs[MAX_HISTORY_RECORD];
	cocos2d::ui::Widget*        Pnl_Msg_Bg;
};

#endif //__UI_CHAT_BOARD_LAYER__