#ifndef _EDIT_BOX_CLASS_
#define _EDIT_BOX_CLASS_
#include "UI_Config_Data_Mgr.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/UIText.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
#include "Common/Utils.h"
//#include "extensions\GUI\CCEditBox.h"
class MyEditBox : public cocos2d::Layer , public cocos2d::extension::EditBoxDelegate
{
private:
	MyEditBox(void);
	virtual ~MyEditBox(void);
	CREATE_FUNC(MyEditBox);

	virtual bool init();
	
	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
	
public:
	static MyEditBox* get_instance();
	std::string getName();
	std::string getPassword();

private:
	cocos2d::extension::EditBox* m_pEditName_;
	cocos2d::extension::EditBox* m_pEditPassword_;
	std::string m_sName_;
	std::string m_sPassW_;

	static MyEditBox* instance_;
};


class ChatEditBox : public cocos2d::Layer, public cocos2d::extension::EditBoxDelegate
{
private:
	static ChatEditBox* s_pInstance;
	std::string m_sContent;
	cocos2d::extension::EditBox* m_pEditContent;
public:
	static ChatEditBox* getInstance();

	std::string getContent();
	void SetPositionAndMaxContent(int nPosX, int nPosY , int nMaxContent);

	ChatEditBox(void);
	virtual ~ChatEditBox(void);
	CREATE_FUNC(ChatEditBox);

	virtual bool init() override;

	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox) override;
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox) override;
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text) override;
	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox) override;
};

class CommonEditBox : public cocos2d::Layer, public cocos2d::extension::EditBoxDelegate
{
public:
	CommonEditBox(void);
	virtual ~CommonEditBox(void);
	CREATE_FUNC(CommonEditBox);
	virtual bool init();
	bool init(Size size, const std::string& path);
	static CommonEditBox* create(Size size, const std::string& path = "");
private:
	std::string m_sContent;
	extension::EditBox* m_pEditContent;

public:
	std::string getContent();
	void setContent(std::string str);
	void SetPositionAndMaxLength(int nPosX, int nPosY, int nMaxLength);

	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox) override;
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox) override;
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text) override;
	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox) override;
};

class BoardEditBox : public cocos2d::Layer, public cocos2d::extension::EditBoxDelegate
{
public:
	BoardEditBox(void);
	virtual ~BoardEditBox(void);
	CREATE_FUNC(BoardEditBox);

	virtual bool init();

private:
	std::string m_sContent;
	extension::EditBox* m_pEditContent;

public:
	std::string getContent();
	void setContent(std::string content);
	void SetPositionAndMaxLength(int nPosX, int nPosY, int nMaxLength);

	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox) override;
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox) override;
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text) override;
	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox) override;
};

class SearchEditBox : public cocos2d::Layer, public cocos2d::extension::EditBoxDelegate
{
public:
	SearchEditBox(void);
	virtual ~SearchEditBox(void);
	CREATE_FUNC(SearchEditBox);

	virtual bool init();

private:
	std::string m_sContent;
	extension::EditBox* m_pEditContent;

public:
	std::string getContent();
	void setContent(std::string str);
	void SetPositionAndMaxLength(int nPosX, int nPosY, int nMaxLength);

	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox) override;
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox) override;
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text) override;
	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox) override;
};

class RenameEditBox : public cocos2d::Layer, public cocos2d::extension::EditBoxDelegate
{
public:
	RenameEditBox(void);
	virtual ~RenameEditBox(void);
	CREATE_FUNC(RenameEditBox);

	virtual bool init();

private:
	std::string m_sContent;
	extension::EditBox* m_pEditContent;

public:
	std::string getContent();
	void SetPositionAndMaxLength(int nPosX, int nPosY, int nMaxLength);

	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox) override;
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox) override;
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text) override;
	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox) override;
};
#endif  //_EDIT_BOX_CLASS_